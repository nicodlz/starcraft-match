"""Small, bounds-checked PE32 reader. No executable is ever run."""
import hashlib
import re
import struct
from pathlib import Path


def hx(n):
    return f'0x{n:08X}'


class PE:
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        if self.take(0, 2) != b'MZ':
            raise ValueError('Not an MZ executable')
        p = self.u32(0x3c)
        if self.take(p, 4) != b'PE\0\0':
            raise ValueError('Not a PE image')
        machine, count, timestamp, _, _, optsize, flags = self.unpack('<HHIIIHH', p + 4)
        o = p + 24
        if machine != 0x14c or self.u16(o) != 0x10b or optsize < 96:
            raise ValueError('Expected x86 PE32')
        self.image_base = self.u32(o + 28)
        self.header_size = self.u32(o + 60)
        self.sections = []
        for i in range(count):
            s = o + optsize + i * 40
            name, vs, va, rs, rp, _, _, _, _, ch = self.unpack('<8sIIIIIIHHI', s)
            self.take(rp, rs)
            self.sections.append(dict(name=name.rstrip(b'\0').decode('ascii', 'replace'),
                                      rva=va, virtual_size=vs, raw_size=rs, raw_offset=rp,
                                      characteristics=ch, executable=bool(ch & 0x20000000)))
        nd = self.u32(o + 92)
        if nd > (optsize - 96) // 8:
            raise ValueError('Invalid data directory count')
        self.dirs = [self.unpack('<II', o + 96 + i * 8) for i in range(nd)]
        self.metadata = dict(schema_version=1, sha256=hashlib.sha256(self.data).hexdigest(),
                             file_size=len(self.data), machine='i386', format='PE32',
                             image_base=hx(self.image_base), entry_point=hx(self.image_base + self.u32(o + 16)),
                             timestamp_raw=timestamp, linker_version=f'{self.data[o+2]}.{self.data[o+3]}',
                             subsystem=self.u16(o+68), dll_characteristics=self.u16(o+70),
                             characteristics=flags, rich_header_present=b'Rich' in self.take(0, p),
                             version_verified=False)
        self.metadata["version_resources"] = self.version_resources()
        self.metadata["debug_records"] = self.debug_records()

    def take(self, offset, size):
        if offset < 0 or size < 0 or offset + size > len(self.data):
            raise ValueError(f'Out-of-file read at {offset:#x}, size {size}')
        return self.data[offset:offset+size]

    def unpack(self, fmt, offset):
        return struct.unpack(fmt, self.take(offset, struct.calcsize(fmt)))

    def u16(self, offset):
        return self.unpack('<H', offset)[0]

    def u32(self, offset):
        return self.unpack('<I', offset)[0]

    def offset(self, rva, size=1):
        if rva < self.header_size and rva + size <= self.header_size:
            self.take(rva, size)
            return rva
        for s in self.sections:
            delta = rva - s['rva']
            if 0 <= delta and delta + size <= s['raw_size']:
                return s['raw_offset'] + delta
        raise ValueError(f'RVA {rva:#x} is not backed by {size} file bytes')

    def region(self, address, size):
        if size <= 0:
            raise ValueError('Function size must be positive')
        rva = address - self.image_base
        if not any(s['executable'] and s['rva'] <= rva and rva+size <= s['rva']+s['raw_size'] for s in self.sections):
            raise ValueError('Function must fit in a file-backed executable section')
        return self.take(self.offset(rva, size), size)

    def cstring(self, rva):
        result = bytearray()
        for i in range(4096):
            c = self.data[self.offset(rva+i)]
            if not c:
                return result.decode('ascii', 'replace')
            result.append(c)
        raise ValueError('Unterminated string')

    def imports(self):
        if len(self.dirs) < 2 or not self.dirs[1][0]:
            return []
        rva, size = self.dirs[1]
        result = []
        for d in range(0, size - 19, 20):
            lookup, stamp, chain, name, iat = self.unpack('<IIIII', self.offset(rva+d, 20))
            if not any((lookup, stamp, chain, name, iat)):
                return result
            dll = self.cstring(name)
            for i in range(len(self.data)//4):
                value = self.u32(self.offset((lookup or iat) + i*4, 4))
                if not value:
                    break
                result.append(dict(dll=dll, name=None if value & 0x80000000 else self.cstring(value+2),
                                   ordinal=value & 0xffff if value & 0x80000000 else None,
                                   iat_address=hx(self.image_base+iat+i*4)))
            else:
                raise ValueError('Unterminated import thunk table')
        raise ValueError('Unterminated import directory')

    def exports(self):
        if not self.dirs or not self.dirs[0][0]:
            return []
        rva, size = self.dirs[0]
        v = self.unpack('<IIHHIIIIIII', self.offset(rva, 40))
        base, nf, nn, funcs, names, ords = v[5:]
        named = {}
        for i in range(nn):
            idx = self.u16(self.offset(ords+2*i, 2))
            if idx >= nf:
                raise ValueError('Invalid export ordinal')
            named[idx] = self.cstring(self.u32(self.offset(names+4*i, 4)))
        result = []
        for i in range(nf):
            va = self.u32(self.offset(funcs+4*i, 4))
            if va:
                forwarded = rva <= va < rva+size
                result.append(dict(address=None if forwarded else hx(self.image_base+va),
                                   name=named.get(i), ordinal=base+i, source='PE export',
                                   forwarder=self.cstring(va) if forwarded else None))
        return result

    def strings(self):
        result = []
        for s in self.sections:
            data = self.take(s['raw_offset'], s['raw_size'])
            for encoding, pattern in [('ascii', rb'[\x20-\x7e]{4,}'), ('utf-16le', rb'(?:[\x20-\x7e]\x00){4,}')]:
                for m in re.finditer(pattern, data):
                    result.append(dict(address=hx(self.image_base+s['rva']+m.start()),
                                       encoding=encoding, text=m.group().decode(encoding), references=[]))
        return sorted(result, key=lambda x: (x['address'], x['encoding']))

    def version_resources(self):
        if len(self.dirs) < 3 or not self.dirs[2][0]:
            return []
        root, length = self.dirs[2]
        result = []
        def resource(offset, size):
            if offset < 0 or offset + size > length:
                raise ValueError('Resource directory read out of bounds')
            return self.offset(root+offset, size)
        def walk(offset, depth, version=False):
            if depth > 3:
                raise ValueError('Invalid resource tree depth')
            h = resource(offset, 16)
            nn, ni = self.unpack('<HH', h+12)
            for i in range(nn+ni):
                name, child = self.unpack('<II', resource(offset+16+8*i, 8))
                is_version = version or (depth == 0 and name == 16)
                if child & 0x80000000:
                    if is_version or depth == 0:
                        walk(child & 0x7fffffff, depth+1, is_version)
                elif is_version:
                    rva, size, codepage, _ = self.unpack('<IIII', resource(child, 16))
                    data = self.take(self.offset(rva, size), size)
                    if len(data) < 6:
                        raise ValueError('Truncated version resource')
                    total, valuesize, typ = struct.unpack_from('<HHH', data)
                    if total > len(data):
                        raise ValueError('Invalid version resource length')
                    end = 6
                    while end+2 <= total and data[end:end+2] != b'\0\0':
                        end += 2
                    if end+2 > total or data[6:end].decode('utf-16le') != 'VS_VERSION_INFO':
                        raise ValueError('Invalid version resource key')
                    fixed = (end+2+3) & ~3
                    if valuesize < 52 or fixed+52 > total:
                        continue
                    words = struct.unpack_from('<13I', data, fixed)
                    if words[0] != 0xfeef04bd:
                        raise ValueError('Invalid fixed version signature')
                    def ver(ms, ls):
                        return '.'.join(str(x) for x in (ms>>16, ms&65535, ls>>16, ls&65535))
                    result.append(dict(file_version=ver(words[2], words[3]), product_version=ver(words[4], words[5]),
                                       address=hx(self.image_base+rva), file_flags=words[7], codepage=codepage))
        walk(0, 0)
        return result

    def debug_records(self):
        if len(self.dirs) < 7 or not self.dirs[6][0]:
            return []
        rva, size = self.dirs[6]
        if size % 28:
            raise ValueError('Invalid debug directory size')
        result = []
        for i in range(0, size, 28):
            ch, timestamp, major, minor, typ, n, va, ptr = self.unpack('<IIHHIIII', self.offset(rva+i, 28))
            data = self.take(ptr, n)
            rec = dict(type=typ, size=n, timestamp_raw=timestamp, version=f'{major}.{minor}')
            if typ == 2 and data[:4] in (b'RSDS', b'NB10'):
                start = 24 if data[:4] == b'RSDS' else 16
                rec.update(signature=data[:4].decode(), pdb_path=data[start:].split(b'\0')[0].decode('utf-8', 'replace'))
            result.append(rec)
        return result
