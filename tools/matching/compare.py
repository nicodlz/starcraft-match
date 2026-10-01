"""Literal byte comparison and common-base textual disassembly diff.
No semantic, relocation-normalized or CFG score is claimed.
"""
import difflib
import re
import struct
import subprocess
import tempfile
from pathlib import Path


def disassemble(data, base=0):
    with tempfile.TemporaryDirectory() as tmp:
        p = Path(tmp) / 'region.bin'
        p.write_bytes(data)
        out = subprocess.check_output(['objdump', '-D', '-b', 'binary', '-m', 'i386', '-M', 'intel',
                                       '--insn-width=16', f'--adjust-vma={base}', str(p)], text=True)
    instructions = []
    for line in out.splitlines():
        m = re.match(r'^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2}\s+)+)\s*(.*)$', line)
        if m:
            instructions.append(dict(address=f'0x{int(m[1], 16):08X}', bytes=m[2].split(), text=m[3].strip()))
    if sum(len(i['bytes']) for i in instructions) != len(data):
        raise ValueError('Disassembler did not account for every byte')
    return instructions


def coff_function(path, symbol):
    """Require an isolated COFF section: no guessed end boundary or relocations."""
    data = Path(path).read_bytes()
    def read(fmt, p):
        n = struct.calcsize(fmt)
        if p < 0 or p+n > len(data):
            raise ValueError('Truncated COFF')
        return struct.unpack_from(fmt, data, p)
    machine, ns, _, symptr, nsyms, optsize, _ = read('<HHIIIHH', 0)
    if machine != 0x14c or optsize:
        raise ValueError('Expected i386 COFF object')
    strings = symptr + nsyms*18
    stringsize = read('<I', strings)[0]
    def name(raw):
        if raw[:4] == b'\0'*4:
            off = struct.unpack('<I', raw[4:])[0]
            if not 4 <= off < stringsize:
                raise ValueError('Invalid COFF name')
            end = data.index(b'\0', strings+off, strings+stringsize)
            return data[strings+off:end].decode()
        return raw.rstrip(b'\0').decode()
    symbols = []
    i = 0
    while i < nsyms:
        raw, value, sec, typ, storage, aux = read('<8sIhHBB', symptr+i*18)
        symbols.append((name(raw), value, sec, typ, storage))
        i += 1+aux
    hits = [s for s in symbols if s[0] == symbol and s[2] > 0 and s[3] & 0x20]
    if len(hits) != 1:
        raise ValueError(f'Expected one function symbol {symbol}')
    _, value, sec, _, _ = hits[0]
    sh = read('<8sIIIIIIHHI', 20+(sec-1)*40)
    size, ptr, nrel, flags = sh[3], sh[4], sh[7], sh[9]
    if value or nrel or not flags & 0x20000000:
        raise ValueError('Need isolated executable section at offset zero with no relocations; link/relocate first')
    if any(s[2] == sec and s[3] & 0x20 and s[0] != symbol for s in symbols):
        raise ValueError('Multiple functions in candidate section')
    if ptr+size > len(data) or not size:
        raise ValueError('Invalid COFF section')
    return data[ptr:ptr+size]


def compare(original, candidate, address):
    a = disassemble(original, address)
    b = disassemble(candidate, address)
    return dict(schema_version=1, engine='literal-bytes-and-objdump-diff-v1',
                original_size=len(original), recompiled_size=len(candidate),
                exact_byte_match=original == candidate, instruction_similarity=None,
                cfg_similarity=None, semantic_match=None, relocation_aware=False,
                original_disassembly=a, candidate_disassembly=b,
                differences=list(difflib.unified_diff([i['text']+'\n' for i in a],
                                                     [i['text']+'\n' for i in b],
                                                     fromfile='original', tofile='candidate')))
