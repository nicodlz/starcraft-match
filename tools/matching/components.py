"""Link whole C functions together without binding any external game code."""
import json
import pathlib
import re
import shutil
import struct
import subprocess

from .linking import (LinkError, digest, read_coff, read_pe, safe_section,
                      safe_symbol, unique_function)


def audit_component(obj, record, *, leaf=False):
    try:
        return _audit_component(obj, record, leaf=leaf)
    except LinkError:
        raise
    except (KeyError, TypeError, AttributeError, IndexError):
        raise LinkError('Malformed component linking metadata') from None


def _audit_component(obj, record, *, leaf=False):
    if record['schema_version'] != 1:
        raise LinkError('Unsupported component record version')
    provenance = record['compiler_provenance']
    if not isinstance(provenance.get('profile'), str) or not provenance['profile']:
        raise LinkError('Compiler profile required')
    for key in ('source_sha256', 'compiler_driver_sha256',
                'compiler_identity_sha256', 'compiler_profile_sha256'):
        if not isinstance(provenance.get(key), str) or not re.fullmatch('[0-9a-f]{64}', provenance[key]):
            raise LinkError('Compiler provenance hash required')
    candidate = record['candidate']
    if candidate['object_sha256'] != digest(obj.payload):
        raise LinkError('Input object provenance changed')
    retained = record['retained_functions']
    if not isinstance(retained, list) or (not leaf and not retained):
        raise LinkError('Component needs a compiled dependency')
    if leaf and retained:
        raise LinkError('Leaf contribution cannot retain dependencies')
    functions = {}
    names = set()
    spans = []
    for item in [candidate, *retained]:
        name = item['symbol']
        safe_symbol(name)
        safe_section(item['section'])
        section = unique_function(obj, name)
        address = item['address']
        alignment_code = (section.flags >> 20) & 15
        alignment = 1 << (alignment_code - 1) if alignment_code else 1
        if (not isinstance(address, int) or isinstance(address, bool)
                or not 0x400000 <= address <= 0xffffffff - section.size
                or address % alignment):
            raise LinkError('Invalid component placement/alignment')
        if (section.name != item['section'] or name in functions
                or section.name in names
                or sum(s.name == section.name and bool(s.size) for s in obj.sections) != 1):
            raise LinkError('Component selectors must be unique')
        if item is not candidate:
            if item['size'] != section.size:
                raise LinkError('Whole compiled dependency extent differs from reviewed size')
            if not isinstance(item['evidence'], list) or not item['evidence']:
                raise LinkError('Compiled dependency needs reviewed evidence')
        if any(address < end and start < address + section.size for start, end in spans):
            raise LinkError('Overlapping component placements')
        spans.append((address, address + section.size))
        functions[name] = (section, item)
        names.add(section.name)
    excluded = []
    for item in record['excluded_contexts']:
        safe_symbol(item['symbol'])
        safe_section(item['section'])
        section = unique_function(obj, item['symbol'])
        if (item['symbol'] in functions or section.name != item['section']
                or section.name in names
                or sum(s.name == section.name and bool(s.size) for s in obj.sections) != 1):
            raise LinkError('Excluded contexts need unique separate contributions')
        names.add(section.name)
        excluded.append(section)
    approved = {s.index for s, _ in functions.values()} | {s.index for s in excluded}
    for section in obj.sections:
        if not section.size or section.index in approved:
            continue
        if (section.name in ('.debug$S', '.debug$F') and not section.flags & 0xa0000000
                and section.flags & 0x02000000
                and all(kind in (6, 7) for _, kind, _ in section.relocations)):
            continue
        raise LinkError('Unapproved component contribution ' + section.name)
    bindings = record['bindings']
    for name, binding in bindings.items():
        safe_symbol(name)
        address = binding['address']
        if (name in functions or any(s.name == name and s.section != 0 for s in obj.symbols.values())
                or binding['kind'] != 'data' or not isinstance(address, int)
                or isinstance(address, bool) or not 0 <= address <= 0xffffffff):
            raise LinkError('Only external data bindings allowed; code must be compiled')
        if not isinstance(binding['evidence'], list) or not binding['evidence']:
            raise LinkError('External data binding needs reviewed evidence')
    used_bindings = set()
    edges = {name: set() for name in functions}
    relocations = {}
    for name, (section, _) in functions.items():
        relocs = []
        for offset, kind, symbol in section.relocations:
            if kind not in (6, 20):
                raise LinkError('Unsupported component relocation')
            addend = struct.unpack_from('<i', section.payload, offset)[0]
            if symbol.section > 0:
                if (symbol.section == section.index and symbol.storage == 3
                        and symbol.type == 0):
                    # Compiler-authored labels/tables stay inside this complete
                    # contribution. They cannot replace another function entry.
                    if (kind != 6 or not 0 <= symbol.value < section.size
                            or not 0 <= symbol.value + addend < section.size):
                        raise LinkError('Invalid local contribution reference')
                    address = functions[name][1]['address'] + symbol.value
                elif symbol.name not in functions:
                    raise LinkError('Reference to unretained/context function')
                else:
                    target, item = functions[symbol.name]
                    if (symbol.section != target.index or symbol.value or addend
                            or not symbol.type & 0x20):
                        raise LinkError('Internal reference must name a whole compiled function entry')
                    address = item['address']
                    edges[name].add(symbol.name)
            else:
                if (symbol.section != 0 or symbol.storage != 2 or kind != 6
                        or symbol.name not in bindings):
                    raise LinkError('Unbound external or external code reference')
                address = bindings[symbol.name]['address']
                used_bindings.add(symbol.name)
            relocs.append(dict(offset=offset, type=kind, symbol=symbol.name,
                               address=address, addend=addend))
        relocations[name] = relocs
    if set(bindings) != used_bindings:
        raise LinkError('Data bindings must exactly cover external relocations')
    if leaf and not any(symbol.section == section.index and symbol.storage == 3
                        and symbol.type == 0
                        for section, _ in functions.values()
                        for _, _, symbol in section.relocations):
        raise LinkError('Leaf profile requires compiler-owned local references')
    reached = set()
    pending = [candidate['symbol']]
    while pending:
        name = pending.pop()
        if name not in reached:
            reached.add(name)
            pending.extend(edges[name])
    if reached != set(functions):
        raise LinkError('Every retained function must be reachable from the candidate')
    return functions, excluded, relocations


def link_leaf_candidate(object_path, record, out_dir, linker='ld'):
    return link_component_candidate(object_path, record, out_dir, linker, leaf=True)


def link_component_candidate(object_path, record, out_dir, linker='ld', *, leaf=False):
    obj = read_coff(pathlib.Path(object_path).read_bytes())
    functions, excluded, relocations = audit_component(obj, record, leaf=leaf)
    executable = shutil.which(linker)
    if not executable:
        raise LinkError('Standard linker unavailable')
    version = subprocess.check_output([executable, '--version'], text=True).splitlines()[0]
    linker_hash = digest(pathlib.Path(executable).read_bytes())
    if record['linker'] != dict(sha256=linker_hash, version=version, emulation='i386pe'):
        raise LinkError('Linker identity/profile changed')
    out = pathlib.Path(out_dir)
    out.mkdir(parents=True, exist_ok=True)
    definitions = [f'{safe_symbol(n)} = 0x{b["address"]:08X};' for n, b in sorted(record['bindings'].items())]
    placements = [f'{safe_section(s.name)} 0x{i["address"]:08X} : {{ KEEP(*({safe_section(s.name)})) }}'
                  for s, i in sorted(functions.values(), key=lambda pair: pair[1]['address'])]
    discarded = ' '.join(f'*({safe_section(s.name)})' for s in excluded)
    script_text = '\n'.join(definitions + ['SECTIONS {', *placements, f'/DISCARD/ : {{ {discarded} *(.debug*) }}', '}']) + '\n'
    script = out / 'layout.ld'
    script.write_text(script_text)
    snapshot = out / 'link-input.obj'
    snapshot.write_bytes(obj.payload)
    image = out / 'candidate.exe'
    address = record['candidate']['address']
    command = [executable, '-mi386pe', '--image-base', '0x400000', '--section-alignment', '16',
               '--file-alignment', '16', '--disable-reloc-section', '--no-insert-timestamp',
               '--entry', hex(address), '-T', str(script), '-Map', str(out / 'candidate.map'),
               '-o', str(image), str(snapshot.resolve())]
    run = subprocess.run(command, capture_output=True, text=True)
    (out / 'link.stdout').write_text(run.stdout)
    (out / 'link.stderr').write_text(run.stderr)
    if run.returncode:
        raise LinkError('Standard linker rejected component: ' + run.stderr)
    raw = image.read_bytes()
    entry, sections = read_pe(raw)
    if entry != address or {s['name'] for s in sections} != {s.name for s, _ in functions.values()} or len(sections) != len(functions):
        raise LinkError('Unexpected component entry/contributions')
    linked = {}
    contributions = []
    for name, (section, item) in functions.items():
        emitted = next(s for s in sections if s['name'] == section.name)
        if emitted['address'] != item['address'] or emitted['size'] != section.size:
            raise LinkError('Whole component extent/placement changed')
        code = raw[emitted['raw_pointer']:emitted['raw_pointer'] + emitted['size']]
        occupied = set()
        for reloc in relocations[name]:
            offset = reloc['offset']
            value = (reloc['address'] + reloc['addend'] -
                     (item['address'] + offset + 4 if reloc['type'] == 20 else 0)) & 0xffffffff
            if struct.unpack_from('<I', code, offset)[0] != value:
                raise LinkError('Incorrect component relocation')
            occupied.update(range(offset, offset + 4))
        if any(a != b for i, (a, b) in enumerate(zip(section.payload, code)) if i not in occupied):
            raise LinkError('Nonrelocation component bytes changed')
        linked[name] = code
        (out / (section.name[1:] + '.bin')).write_bytes(code)
        contributions.append(dict(symbol=name, section=section.name, address=item['address'],
                                  size=len(code), sha256=digest(code), relocations=relocations[name]))
    if (digest(pathlib.Path(object_path).read_bytes()) != digest(obj.payload)
            or digest(snapshot.read_bytes()) != digest(obj.payload)
            or digest(pathlib.Path(executable).read_bytes()) != linker_hash):
        raise LinkError('Component input/linker changed during linking')
    selected, _ = functions[record['candidate']['symbol']]
    code = linked[record['candidate']['symbol']]
    category = ('leaf-standard-linked-C-contribution-v1' if leaf
                else 'component-standard-linked-C-contribution-v1')
    manifest = dict(schema_version=1, category=category,
                    record_sha256=digest(json.dumps(record, sort_keys=True, separators=(',', ':')).encode()),
                    object_sha256=digest(obj.payload), selected_section_name=selected.name,
                    whole_input_size=selected.size, linked_size=len(code), address=address,
                    linked_function_sha256=digest(code), linked_image_sha256=digest(raw),
                    script_sha256=digest(script_text.encode()), command=command,
                    compiler_provenance=record['compiler_provenance'], contributions=contributions,
                    linker=dict(executable=str(pathlib.Path(executable).resolve()), sha256=linker_hash,
                                version=version, emulation='i386pe'), normalization=False,
                    object_byte_modification=False, context_emitted=False,
                    excluded_contexts=[dict(name=s.name, size=s.size, sha256=digest(s.payload)) for s in excluded])
    (out / 'candidate.bin').write_bytes(code)
    (out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    return code, manifest
