"""Native MSVC LTCG: complete mapped C contributions, never patched code.

The auxiliary COFF supplies only absolute data symbols and zero-filled placement
space. It contains no reconstructed function, ABI shim or original game bytes.
Opaque /GL input is not represented as auditable ordinary machine-code COFF.
"""
import json
from pathlib import Path
import re
import struct
import subprocess

from .compare import disassemble
from .linking import LinkError, digest, read_coff, read_pe, safe_symbol

TEXT_ADDRESS = 0x4001e0
METHOD = 'native-msvc71-ltcg-c-component'
CATEGORY = 'native-msvc71-ltcg-C-contribution-v1'


def layout_object(spaces, bindings):
    """Create an independent layout object; never read or modify candidate code."""
    strings = bytearray(struct.pack('<I', 4))

    def name(value):
        raw = value.encode('ascii')
        if len(raw) <= 8:
            return raw.ljust(8, b'\0')
        offset = len(strings)
        strings.extend(raw + b'\0')
        return struct.pack('<II', 0, offset)

    headers, payload, symbols = bytearray(), bytearray(), bytearray()
    for index, (section, size) in enumerate(spaces, 1):
        if not re.fullmatch(r'\.text\$[a-z]', section) or not 0 < size <= 0x1000000:
            raise LinkError('Invalid zero-only layout contribution')
        offset = 20 + 40 * len(spaces) + len(payload)
        headers.extend(struct.pack('<8sIIIIIIHHI', name(section), 0, 0, size, offset,
                                   0, 0, 0, 0, 0x60100020))
        payload.extend(bytes(size))
        symbols.extend(struct.pack('<8sIhHBB', name('_sc_layout_' + str(index)), 0, index, 0, 2, 0))
    for symbol, value in sorted(bindings.items()):
        safe_symbol(symbol)
        if not isinstance(value, int) or isinstance(value, bool) or not 0 <= value <= 0xffffffff:
            raise LinkError('Invalid absolute data binding')
        symbols.extend(struct.pack('<8sIhHBB', name(symbol), value, -1, 0, 2, 0))
    struct.pack_into('<I', strings, 0, len(strings))
    offset = 20 + len(headers) + len(payload)
    raw = (struct.pack('<HHIIIHH', 0x14c, len(spaces), 0, offset, len(symbols) // 18, 0, 0)
           + headers + payload + symbols + strings)
    # Independently parse generated auxiliary input, including bounds and names.
    obj = read_coff(raw)
    if any(s.relocations or any(s.payload) for s in obj.sections):
        raise LinkError('Layout object must contain only zero placement space')
    return raw


def parse_map(text):
    contributions, symbols = {}, {}
    for line in text.splitlines():
        section = re.fullmatch(r'\s+([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+'
                               r'([0-9a-fA-F]{8})H\s+(\S+)\s+(CODE|DATA)\s*', line)
        if section:
            segment, offset, size, name, kind = section.groups()
            if name in contributions:
                raise LinkError('Duplicate native map contribution')
            contributions[name] = dict(segment=int(segment, 16), offset=int(offset, 16),
                                       size=int(size, 16), kind=kind)
            continue
        symbol = re.fullmatch(r'\s+([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+'
                              r'([0-9a-fA-F]{8})\s+(.*?)\s*', line)
        if symbol:
            segment, offset, name, address, origin = symbol.groups()
            if name in symbols:
                raise LinkError('Duplicate native map symbol')
            symbols[name] = dict(segment=int(segment, 16), offset=int(offset, 16),
                                 address=int(address, 16), function=origin.startswith('f '), origin=origin)
    if not contributions or not symbols:
        raise LinkError('Missing complete native map records')
    return contributions, symbols


def audit_control_flow(functions, codes):
    """No external/indirect code bindings; all retained callees must be reached."""
    by_address = {item['address']: item['symbol'] for item in functions}
    edges = {item['symbol']: set() for item in functions}
    for item in functions:
        start, end = item['address'], item['address'] + item['size']
        instructions = disassemble(codes[item['symbol']], start)
        entries = {int(insn['address'], 0) for insn in instructions}
        for insn in instructions:
            text = insn['text']
            if '(bad)' in text or '.byte' in text:
                raise LinkError('Invalid native instruction contribution')
            op = text.split()[0]
            if op in ('call', 'jmp') or op.startswith('j') or op.startswith('loop'):
                target = re.fullmatch(r'\S+\s+(?:0x)?([0-9a-fA-F]+)', text)
                if not target:
                    raise LinkError('Indirect native control flow is unsupported')
                address = int(target[1], 16)
                if op == 'call':
                    if address not in by_address:
                        raise LinkError('Native call must name a whole retained C function')
                    edges[item['symbol']].add(by_address[address])
                elif not start <= address < end or address not in entries:
                    raise LinkError('Native branch leaves its complete C contribution')
    reached, pending = set(), [functions[0]['symbol']]
    while pending:
        name = pending.pop()
        if name not in reached:
            reached.add(name)
            pending.extend(edges[name])
    if reached != set(edges):
        raise LinkError('Unreachable native compiled dependency')


def link_ltcg_candidate(object_path, record, out_dir, linker):
    if record['schema_version'] != 1 or record['excluded_contexts']:
        raise LinkError('Native LTCG requires a complete context-free component')
    original = Path(object_path).read_bytes()
    if digest(original) != record['candidate']['object_sha256']:
        raise LinkError('Native intermediate object provenance changed')
    # Identify old MSVC's opaque i386 intermediate format without interpreting it.
    if original[:8] != struct.pack('<HHHH', 0, 0xffff, 1, 0x14c):
        raise LinkError('Native LTCG requires MSVC i386 /GL intermediate input')
    functions = [record['candidate'], *record['retained_functions']]
    ordered = sorted(functions, key=lambda item: item['address'])
    if ordered != functions or len(functions) > 12:
        raise LinkError('Native root must precede its compiled dependencies')
    spaces, cursor, seen = [], TEXT_ADDRESS, set()
    for index, item in enumerate(functions):
        safe_symbol(item['symbol'])
        section = '.text$' + chr(ord('b') + index * 2)
        if (item['section'] != section or item['symbol'] in seen
                or not isinstance(item['size'], int) or isinstance(item['size'], bool)
                or not 0 < item['size'] <= 0x1000000
                or not isinstance(item['address'], int) or item['address'] % 16
                or item['address'] <= cursor or item['address'] + item['size'] > 0x100000000):
            raise LinkError('Invalid complete native placement')
        spaces.append(('.text$' + chr(ord('a') + index * 2), item['address'] - cursor))
        seen.add(item['symbol'])
        cursor = item['address'] + item['size']
    bindings = {}
    for name, binding in record['bindings'].items():
        if name in seen or binding['kind'] != 'data' or not binding['evidence']:
            raise LinkError('Only reviewed native data bindings allowed')
        bindings[name] = binding['address']
    out = Path(out_dir)
    out.mkdir(parents=True, exist_ok=True)
    snapshot, layout, image, mapfile = [out / n for n in ('link-input.obj', 'layout.obj', 'candidate.exe', 'native.map')]
    snapshot.write_bytes(original)
    layout.write_bytes(layout_object(spaces, bindings))
    layout_spec = dict(text_address=TEXT_ADDRESS, zero_only_spaces=spaces, data_bindings=bindings)
    layout_text = json.dumps(layout_spec, sort_keys=True, indent=2) + '\n'
    (out / 'layout.json').write_text(layout_text)

    def win(path):
        return 'Z:' + str(path.resolve()).replace('/', '\\')

    command = [linker, '/nologo', '/dll', '/noentry', '/nodefaultlib', '/ltcg', '/fixed',
               '/machine:x86', '/base:0x400000', '/align:16', '/filealign:16',
               '/include:' + functions[0]['symbol'],
               *['/include:_sc_layout_' + str(i) for i in range(1, len(spaces) + 1)],
               '/out:' + win(image), '/map:' + win(mapfile), win(snapshot), win(layout)]
    image.unlink(missing_ok=True)
    mapfile.unlink(missing_ok=True)
    run = subprocess.run(command, capture_output=True, text=True, timeout=120)
    (out / 'link.log').write_text(run.stdout + run.stderr)
    warnings = re.findall(r'\bwarning (LNK\d+)\b', run.stdout + run.stderr)
    if run.returncode or any(w != 'LNK4108' for w in warnings) or re.search(
            r'\b(?:error|fatal error) LNK\d+', run.stdout + run.stderr):
        raise LinkError('Native linker rejected complete component: ' + run.stdout + run.stderr)
    raw = image.read_bytes()
    entry, sections = read_pe(raw)
    if (entry != 0x400000 or len(sections) != 1 or sections[0]['name'] != '.text'
            or sections[0]['address'] != TEXT_ADDRESS or sections[0]['size'] != cursor - TEXT_ADDRESS):
        raise LinkError('Native image profile or complete extent changed')
    mapped, symbols = parse_map(mapfile.read_text())
    expected = {'.text': (0, 0)} if '.text' in mapped else {}
    previous = TEXT_ADDRESS
    for (section, size), item in zip(spaces, functions):
        expected[section] = (previous - TEXT_ADDRESS, size)
        expected[item['section']] = (item['address'] - TEXT_ADDRESS, item['size'])
        previous = item['address'] + item['size']
    if (set(mapped) != set(expected) or any(mapped[name] != dict(segment=1, offset=offset, size=size, kind='CODE')
                                          for name, (offset, size) in expected.items())):
        raise LinkError('Native map must cover whole declared C contributions and zero layout only')
    allowed_symbols = seen | set(bindings) | {'___safe_se_handler_count', '___safe_se_handler_table'}
    allowed_symbols |= {'_sc_layout_' + str(i) for i in range(1, len(spaces) + 1)}
    if set(symbols) != allowed_symbols:
        raise LinkError('Unexpected native symbol or omitted data binding')
    for name, value in [*bindings.items(), ('___safe_se_handler_count', 0), ('___safe_se_handler_table', 0)]:
        sym = symbols[name]
        if sym['segment'] or sym['address'] != value or sym['function'] or sym['origin'] != '<absolute>':
            raise LinkError('Native absolute data symbol differs from reviewed binding')
    text = raw[sections[0]['raw_pointer']:sections[0]['raw_pointer'] + sections[0]['size']]
    contributions, codes = [], {}
    previous = TEXT_ADDRESS
    for index, item in enumerate(functions, 1):
        symbol = symbols[item['symbol']]
        offset = item['address'] - TEXT_ADDRESS
        if (not symbol['function'] or symbol['segment'] != 1 or symbol['address'] != item['address']
                or symbol['offset'] != offset or not symbol['origin'].endswith('link-input.obj')):
            raise LinkError('Native function must be an entire compiler-generated contribution')
        gap = symbols['_sc_layout_' + str(index)]
        if (gap['function'] or gap['segment'] != 1 or gap['address'] != previous
                or gap['offset'] != previous - TEXT_ADDRESS or not gap['origin'].endswith('layout.obj')
                or any(text[previous - TEXT_ADDRESS:offset])):
            raise LinkError('Native layout space must remain zero and outside compared functions')
        code = text[offset:offset + item['size']]
        codes[item['symbol']] = code
        (out / (item['section'][1:] + '.bin')).write_bytes(code)
        contributions.append(dict(symbol=item['symbol'], section=item['section'], address=item['address'],
                                  size=len(code), sha256=digest(code)))
        previous = item['address'] + item['size']
    audit_control_flow(functions, codes)
    if (Path(object_path).read_bytes() != original or snapshot.read_bytes() != original
            or layout.read_bytes() != layout_object(spaces, bindings)):
        raise LinkError('Native input changed while linking')
    code = codes[functions[0]['symbol']]
    manifest = dict(schema_version=1, category=CATEGORY, compiler_provenance=record['compiler_provenance'],
                    record_sha256=digest(json.dumps(record, sort_keys=True, separators=(',', ':')).encode()),
                    object_sha256=digest(original), selected_section_name=functions[0]['section'],
                    whole_input_size=len(code), linked_size=len(code), address=functions[0]['address'],
                    linked_function_sha256=digest(code), linked_image_sha256=digest(raw),
                    script_sha256=digest(layout_text.encode()), layout_object_sha256=digest(layout.read_bytes()),
                    map_sha256=digest(mapfile.read_bytes()), command=command, contributions=contributions,
                    linker={k: record['linker'][k] for k in ('executable', 'sha256', 'version', 'emulation')},
                    intermediate_format='opaque-msvc71-GL', contribution_extent_source='native-linker-map',
                    normalization=False, object_byte_modification=False, original_byte_input=False,
                    placement_space_counted=False, context_emitted=False, excluded_contexts=[])
    (out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    return code, manifest
