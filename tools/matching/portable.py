#!/usr/bin/env python3
"""Source-only Clang PE32 linkage with strict whole-section provenance audits."""
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if Path(__file__).resolve() != ROOT/'tools/matching/portable.py':
    raise RuntimeError('Portable module must live at tools/matching/portable.py')
PROFILE_PATH = ROOT / 'config/compilers.json'
PROFILE_NAME = 'clang-i686-scaffold'
EXPECTED_FLAGS = ['--target=i686-pc-windows-msvc','-std=c11','-O2',
                  '-ffreestanding','-fno-stack-protector','-fno-ident',
                  '-ffunction-sections','-Iinclude']

class Rejected(ValueError):
    exit_code=1

class ToolchainUnavailable(Rejected):
    """Only initial default compiler absence; no prior available identity exists."""
    exit_code=69

class ToolchainMisconfigured(Rejected):
    exit_code=78

def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

_LOADED_PATHS={'prototype':Path(__file__).resolve(),
               'pe_reader':ROOT/'tools/analysis/pe.py',
               'python':Path(sys.executable).resolve()}
_LOADED_BYTES={name:path.read_bytes() for name,path in _LOADED_PATHS.items()}
_LOADED_HASHES={name:hashlib.sha256(payload).hexdigest() for name,payload in _LOADED_BYTES.items()}
_PE_NAMESPACE={'__name__':'portable_snapshot_pe_reader','__file__':str(_LOADED_PATHS['pe_reader'])}
exec(compile(_LOADED_BYTES['pe_reader'],str(_LOADED_PATHS['pe_reader']),'exec'),_PE_NAMESPACE)
PE=_PE_NAMESPACE['PE']
del _LOADED_BYTES
_COMPILATION_TOKEN=object()

def controlled_env():
    return {'PATH':'/usr/bin:/bin','LC_ALL':'C','LANG':'C','SOURCE_DATE_EPOCH':'0'}

def implementation_identity():
    inventory={name:{'path':str(path),'sha256':digest(path)} for name,path in _LOADED_PATHS.items()}
    if any(inventory[name]['sha256']!=expected for name,expected in _LOADED_HASHES.items()):
        raise Rejected('Loaded implementation/reader/Python changed')
    return inventory

def profile_snapshot(profile):
    if profile != PROFILE_NAME:
        raise Rejected('Only registered clang-i686-scaffold profile supported')
    payload=PROFILE_PATH.read_bytes()
    try:config=json.loads(payload)[profile]
    except (ValueError,KeyError,TypeError) as error:
        raise ToolchainMisconfigured('Malformed registered profile') from error
    if not isinstance(config,dict):
        raise ToolchainMisconfigured('Selected registered profile must be an object')
    if (config.get('executable')!='clang' or config.get('flags')!=EXPECTED_FLAGS
        or config.get('identity_arguments') is not None):
        raise ToolchainMisconfigured('Registered portable profile differs from supported contract')
    return {'path':str(PROFILE_PATH.resolve()),'sha256':hashlib.sha256(payload).hexdigest(),
            'name':profile,'configuration':config}

def compiler_identity():
    discovery_path=os.environ.get('PATH',controlled_env()['PATH'])
    # Received PATH selects only the executable (including CI symlinks).
    # Every compiler/linker/version subprocess still uses the controlled env.
    path=shutil.which('clang',path=discovery_path)
    if path is None:
        raise ToolchainUnavailable('Registered Clang executable unavailable')
    selected=Path(path)
    resolved=selected.resolve()
    if resolved.read_bytes()[:4]!=b'\x7fELF':
        raise Rejected('Only actual ELF Clang executable accepted; no wrapper')
    components={str(resolved):digest(resolved),str(Path('/usr/bin/ldd').resolve()):digest('/usr/bin/ldd'),
                str(Path('/bin/bash').resolve()):digest('/bin/bash')}
    if Path('/usr/bin/ldd').read_bytes().splitlines()[0]!=b'#!/bin/bash':
        raise Rejected('Unsupported ldd interpreter')
    dependencies=subprocess.run(['/usr/bin/ldd',str(resolved)],cwd=ROOT,env=controlled_env(),
                                capture_output=True,text=True,timeout=60)
    if dependencies.returncode or dependencies.stderr or not dependencies.stdout.strip():
        raise Rejected('Clang dynamic dependency enumeration failed')
    count=0
    for line in dependencies.stdout.splitlines():
        line=line.strip()
        if re.fullmatch(r'linux-vdso[^ ]* \(0x[0-9a-fA-F]+\)',line):continue
        match=re.fullmatch(r'(?:[^ ]+ => )?(/[^ ]+) \(0x[0-9a-fA-F]+\)',line)
        if not match or not Path(match[1]).is_file():
            raise Rejected('Unresolved/unparsed compiler dependency: '+line)
        lib=Path(match[1]).resolve();components[str(lib)]=digest(lib);count+=1
    if not count:
        raise Rejected('Compiler dependency inventory empty')
    version=subprocess.run([str(resolved),'--version'],cwd=ROOT,env=controlled_env(),
                           capture_output=True,text=True,timeout=60)
    if version.returncode or version.stderr or not re.search(r'\bclang version\b',version.stdout):
        raise Rejected('Real Clang version query failed')
    return {'profile_executable':'clang','discovery_path':discovery_path,'selected_path':str(selected),'resolved_path':str(resolved),
            'version':version.stdout,'executable_sha256':components[str(resolved)],
            'component_sha256':components}

def autonomous_logical_text(text):
    """Conservative C phase-1/phase-2 view; never used as compiler input."""
    phase1=text.replace('??/','\\')
    logical=phase1
    # Repeated removal is conservative when consecutive continuations combine.
    # Horizontal whitespace matches compiler extension spellings as well.
    while True:
        spliced=re.sub(r'\\[ \t\v\f]*(?:\r\n|\n|\r)','',logical)
        if spliced==logical:
            return logical
        logical=spliced

def validate_source(source):
    path=Path(source).resolve()
    if not path.is_relative_to(ROOT/'src') or path.suffix.lower()!='.c' or not path.is_file():
        raise Rejected('Only autonomous C sources inside src accepted')
    # Exactly this captured payload is validated, hashed and compiler-snapshotted.
    payload=path.read_bytes()
    try: text=payload.decode('ascii')
    except UnicodeError as error: raise Rejected('Only ASCII autonomous C source supported') from error
    logical=autonomous_logical_text(text)
    if (not payload or '\0' in text
        or any(marker in view for view in (text,logical) for marker in ('#','%:','??='))
        or any(re.search(r'\b(?:asm|__asm|__asm__|_Pragma|__pragma)\b',view)
               for view in (text,logical))):
        raise Rejected('Headers/directives/assembly/pragmas unsupported; autonomous C source required')
    return path,payload

def verify_compilation(manifest,object_path):
    if implementation_identity()!=manifest['implementation_identity']:
        raise Rejected('Implementation changed during compilation/link')
    if profile_snapshot(manifest['compiler_profile'])!=manifest['registered_profile']:
        raise Rejected('Registered profile changed during compilation/link')
    try:
        current_compiler=compiler_identity()
    except ToolchainUnavailable as error:
        raise Rejected('Previously available compiler disappeared during compilation/link') from error
    if current_compiler!=manifest['compiler_identity']:
        raise Rejected('Compiler executable/version/components changed during compilation/link')
    source=Path(manifest['source'])
    if source.resolve()!=source or digest(source)!=manifest['source_sha256']:
        raise Rejected('Source bytes/path changed during compilation/link')
    if digest(manifest['source_snapshot'])!=manifest['source_sha256']:
        raise Rejected('Compiler source snapshot changed during compilation/link')
    if digest(object_path)!=manifest['object_sha256']:
        raise Rejected('Fresh compiler object changed during link')

def compile_and_link(source,symbol,address,bindings,output_dir,
                     profile=PROFILE_NAME,image_base=0x400000):
    """Accept only C source/profile; raw objects and producer manifests are not inputs."""
    implementation=implementation_identity()
    if not isinstance(symbol,str) or not re.fullmatch(r'[A-Za-z_@][A-Za-z0-9_@]*',symbol):
        raise Rejected('Invalid C symbol')
    registered=profile_snapshot(profile)
    source,payload=validate_source(source)
    source_hash=hashlib.sha256(payload).hexdigest()
    out=Path(output_dir).resolve()
    if not out.is_relative_to(ROOT/'build') or out==ROOT/'build' or out.exists():
        raise Rejected('Output must be a new build directory; no stale objects')
    identity=compiler_identity()
    out.mkdir(parents=True)
    obj=out/'candidate.obj'
    snapshot=out/'source-snapshot.c'
    snapshot.write_bytes(payload)
    if digest(source)!=source_hash or profile_snapshot(profile)!=registered or implementation_identity()!=implementation:
        raise Rejected('Source/profile/implementation changed before compiler')
    cmd=[identity['resolved_path'],*registered['configuration']['flags'],
         '-c',str(snapshot),'-o',str(obj)]
    proc=subprocess.run(cmd,cwd=ROOT,env=controlled_env(),capture_output=True,text=True,timeout=120)
    if proc.returncode==78:
        raise ToolchainMisconfigured('Clang compilation configuration rejected: '+proc.stdout+proc.stderr)
    # Exit 69 here is a hard error: compiler identity was already available.
    if proc.returncode or re.search(r'\bwarning\b',proc.stdout+proc.stderr,re.I) or not obj.is_file():
        raise Rejected('Fresh Clang compilation failed/warned: '+proc.stdout+proc.stderr)
    manifest={'source':str(source),'source_snapshot':str(snapshot),'source_sha256':source_hash,'object':str(obj),
              'object_sha256':digest(obj),'compiler_profile':profile,'registered_profile':registered,
              'compiler_identity':identity,'command':cmd,'compiler_environment':controlled_env(),
              'working_directory':str(ROOT),'stdout':proc.stdout,'stderr':proc.stderr,
              'returncode':proc.returncode,'implementation_identity':implementation,
              'proof_eligible':False,'abi_compatible':None}
    verify_compilation(manifest,obj)
    (out/'compilation.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return _link_compiled(obj,symbol,address,bindings,out,manifest,_COMPILATION_TOKEN,image_base)


# Exact whole-input section/relocation audit; no producer objects accepted by the API.
def read_coff(path, wanted):
    data = Path(path).read_bytes()
    def unpack(fmt, offset):
        size = struct.calcsize(fmt)
        if offset < 0 or offset + size > len(data):
            raise Rejected('Truncated COFF metadata')
        return struct.unpack_from(fmt, data, offset)
    machine, ns, _, symptr, nsyms, optsize, _ = unpack('<HHIIIHH', 0)
    if machine != 0x14c or optsize or not ns or not nsyms:
        raise Rejected('Only ordinary i386 COFF objects supported')
    strings = symptr + nsyms * 18
    stringsize = unpack('<I', strings)[0]
    if stringsize < 4 or strings + stringsize > len(data):
        raise Rejected('Malformed string table')
    def long_name(off):
        if not 4 <= off < stringsize:
            raise Rejected('Invalid long name')
        try:
            end = data.index(b'\0', strings + off, strings + stringsize)
            return ascii_name(data[strings + off:end])
        except (ValueError, UnicodeError) as error:
            raise Rejected('Malformed name') from error
    def ascii_name(raw):
        try:
            value = raw.decode("ascii")
        except UnicodeDecodeError as error:
            raise Rejected("Invalid non-ASCII COFF name") from error
        if not re.fullmatch(r"[A-Za-z_@.$][A-Za-z0-9_@.$]*", value):
            raise Rejected("Invalid COFF name")
        return value
    def symbol_name(raw):
        if raw[:4] == b'\0' * 4:
            return long_name(struct.unpack('<I', raw[4:])[0])
        return ascii_name(raw.rstrip(b'\0'))
    ranges = []
    def occupy(start, size, label):
        if not size:
            return
        if start < 0 or start + size > len(data):
            raise Rejected('Truncated raw range: ' + label)
        if any(start < end and begin < start + size for begin, end, _ in ranges):
            raise Rejected('Overlapping raw COFF ranges: ' + label)
        ranges.append((start, start + size, label))
    occupy(0, 20 + ns * 40, 'headers')
    occupy(symptr, nsyms * 18, 'symbols')
    occupy(strings, stringsize, 'strings')
    symbols = {}
    i = 0
    while i < nsyms:
        raw, value, sec, typ, storage, aux = unpack('<8sIhHBB', symptr + i * 18)
        if i + 1 + aux > nsyms or storage == 105:
            raise Rejected('Malformed auxiliaries or unsupported weak external')
        symbols[i] = dict(name=symbol_name(raw), value=value, section=sec,
                          type=typ, storage=storage, auxiliaries=aux,
                          auxiliary_data=data[symptr+(i+1)*18:symptr+(i+1+aux)*18])
        i += 1 + aux
    externals = [s for s in symbols.values() if s['storage'] == 2]
    if len({s['name'] for s in externals}) != len(externals):
        raise Rejected('Duplicate external COFF name')
    functions = [s for s in symbols.values() if s['section'] > 0 and s['type'] & 0x20]
    if len(functions) != 1 or functions[0]['name'] != wanted or functions[0]['value']:
        raise Rejected('Exactly one complete function at section offset zero required')
    selected = functions[0]['section']
    if any(s['storage'] == 2 and s['section'] > 0 and s['name'] != wanted for s in symbols.values()):
        raise Rejected('Secondary external definition or function alias unsupported')
    sections = []
    for number in range(1, ns + 1):
        raw, _, _, size, ptr, relptr, lineptr, nrel, nline, flags = unpack('<8sIIIIIIHHI', 20 + (number - 1) * 40)
        if raw.startswith(b'/'):
            try: name = long_name(int(raw[1:].rstrip(b'\0')))
            except ValueError as error: raise Rejected('Invalid section name') from error
        else: name = ascii_name(raw.rstrip(b'\0'))
        if lineptr or nline:
            raise Rejected('COFF line-number tables unsupported')
        occupy(ptr, size, 'section ' + name)
        occupy(relptr, nrel * 10, 'relocations ' + name)
        if nrel and not size:
            raise Rejected('Relocations on empty section would be ambiguous')
        if flags & 0x1000000 or ptr + size > len(data) or relptr + 10 * nrel > len(data):
            raise Rejected('Malformed/overflow relocation or section table')
        if number != selected and (size or nrel) and name not in ('.debug$S', '.debug$F'):
            raise Rejected('Additional nonempty code/data/directive section unsupported')
        if name in ('.debug$S', '.debug$F') and flags & 0xA0000000:
            raise Rejected('Metadata has executable/writable input flags')
        sections.append(dict(number=number, name=name, size=size, pointer=ptr, relptr=relptr,
                             nrel=nrel, flags=flags))
    if not 1 <= selected <= ns:
        raise Rejected('Invalid function section')
    primary_names={}
    primary_locations=set()
    section_symbols=set()
    for item in symbols.values():
        sec=item['section']
        if not -2 <= sec <= ns:
            raise Rejected('Invalid symbol section index')
        is_section=(item['storage']==3 and sec>0
                    and item['name']==sections[sec-1]['name'] and item['value']==0)
        if is_section:
            if sec in section_symbols or item['auxiliaries']!=1 or item['type']!=0:
                raise Rejected('Duplicate/malformed section symbol auxiliary')
            section_symbols.add(sec)
            length,nrel,nline,checksum,association,selection,reserved,high=struct.unpack(
                '<IHHIhBBH',item['auxiliary_data'])
            section=sections[sec-1]
            if length!=section['size'] or nrel!=section['nrel'] or nline or reserved or high:
                raise Rejected('Inconsistent section auxiliary extent/relocations')
            comdat=bool(section['flags'] & 0x1000)
            if comdat:
                if sec==selected:
                    valid=selection==1 and association==sec
                else:
                    valid=(section['name']=='.debug$F' and selection==5 and association==selected
                           and bool(sections[selected-1]['flags'] & 0x1000))
            else:
                valid=selection==0 and association==sec
            if not valid:
                raise Rejected('Unsupported/inconsistent COMDAT selection/association')
            continue
        if item['auxiliaries'] and not (item['name']=='.file' and sec==-2
                                      and item['storage']==103 and item['type']==0):
            raise Rejected('Unsupported primary symbol auxiliaries')
        if item['name'] in primary_names:
            raise Rejected('Duplicate primary symbol name')
        primary_names[item['name']]=item
        if sec==selected:
            if item['value']>=sections[selected-1]['size']:
                raise Rejected('Code symbol outside complete section')
            key=(sec,item['value'])
            if key in primary_locations:
                raise Rejected('Defined code alias unsupported')
            primary_locations.add(key)
    if section_symbols!=set(range(1,ns+1)):
        raise Rejected('Exactly one validated section symbol required per section')
    selected_section = sections[selected - 1]
    if not selected_section['size'] or not selected_section['flags'] & 0x20000000:
        raise Rejected('Function must occupy a nonempty executable section')
    if not re.fullmatch(r'\.text(?:\$[A-Za-z0-9_@]+)?', selected_section['name']):
        raise Rejected('Prototype supports only ordinary isolated .text sections')
    material = [selected_section] + [x for x in sections if x['size'] and x['number'] != selected]
    if len({x['name'] for x in material}) != len(material):
        raise Rejected('Ambiguous duplicate input metadata section')
    needed = set()
    for section in material:
        body = data[section['pointer']:section['pointer'] + section['size']]
        section['body'] = body
        relocations, occupied = [], set()
        for i in range(section['nrel']):
            offset, index, kind = unpack('<IIH', section['relptr'] + i * 10)
            permitted = (6, 20) if section['number'] == selected else (7,)
            if kind not in permitted or offset + 4 > len(body) or index not in symbols:
                raise Rejected('Unsupported/malformed function or metadata relocation')
            covered = set(range(offset, offset + 4))
            if occupied & covered:
                raise Rejected('Overlapping relocation fields')
            occupied |= covered
            target = symbols[index]
            if target['section'] == 0:
                if target['value'] or target['storage'] != 2:
                    raise Rejected('Common/nonexternal undefined symbol unsupported')
                needed.add(target['name'])
            elif target['section'] != selected or target['value'] >= selected_section['size']:
                raise Rejected('Target outside selected function unsupported')
            relocations.append(dict(offset=offset, kind=kind, target=target,
                                    addend=struct.unpack_from('<i' if kind == 20 else '<I', body, offset)[0]))
        section['relocations'] = relocations
    undefined = [x for x in symbols.values() if x['section'] == 0]
    if len({x['name'] for x in undefined}) != len(undefined) or {x['name'] for x in undefined} != needed:
        raise Rejected('Ambiguous or unused undefined symbols')
    return selected_section, material, needed, symbols

def linker_identity(resolved):
    resolved=Path(resolved).resolve()
    if resolved.read_bytes()[:4]!=b'\x7fELF':
        raise Rejected('Only the real dynamic ELF linker is supported; no wrappers')
    if Path('/usr/bin/ldd').read_bytes().splitlines()[0] != b'#!/bin/bash':
        raise Rejected('Unsupported ldd interpreter contract')
    env=controlled_env()
    proc=subprocess.run(['/usr/bin/ldd',str(resolved)],env=env,cwd=ROOT,
                        capture_output=True,text=True,timeout=60)
    if proc.returncode or proc.stderr or not proc.stdout.strip():
        raise Rejected('ldd dependency enumeration failed')
    components={str(resolved):digest(resolved),str(Path('/usr/bin/ldd').resolve()):digest('/usr/bin/ldd'),
                str(Path('/bin/bash').resolve()):digest('/bin/bash')}
    count=0
    for line in proc.stdout.splitlines():
        line=line.strip()
        if re.fullmatch(r'linux-vdso[^ ]* \(0x[0-9a-fA-F]+\)',line):
            continue
        match=re.fullmatch(r'(?:[^ ]+ => )?(/[^ ]+) \(0x[0-9a-fA-F]+\)',line)
        if not match or not Path(match[1]).is_file():
            raise Rejected('Unresolved/unparsed linker dependency: '+line)
        path=Path(match[1]).resolve();components[str(path)]=digest(path);count+=1
    if not count:
        raise Rejected('Dynamic linker dependency inventory is empty')
    version=subprocess.run([str(resolved),'--version'],env=env,cwd=ROOT,
                           capture_output=True,text=True,timeout=60)
    first_line=version.stdout.splitlines()[0] if version.stdout else ''
    if version.returncode or version.stderr or not re.fullmatch(r'GNU ld(?: \([^\r\n]*\))? 2\.42',first_line):
        raise Rejected('Supported GNU ld 2.42 identity required')
    return {'executable':str(resolved),'version':version.stdout,'component_sha256':components}

def relocation_value(kind,value,addend,place,image_base):
    calculated=value+addend
    if kind==20:
        calculated-=place+4
        if not -2**31<=calculated<2**31:
            raise Rejected('REL32 signed displacement overflow')
    elif kind==7:
        calculated-=image_base
        if not 0<=calculated<2**32:
            raise Rejected('RVA32 image-relative arithmetic overflow')
    elif kind==6:
        if not 0<=calculated<2**32:
            raise Rejected('DIR32 arithmetic overflow')
    else:
        raise Rejected('Unsupported relocation type')
    return calculated & 0xffffffff

def audited_empty_sections(material,symbols):
    empty_sections=[]
    material_names={section['name'] for section in material}
    for item in symbols.values():
        if (item['storage']==3 and item['section']>0 and item['auxiliaries']==1
            and item['name'] not in material_names):
            length,nrel,nline,_,_,_,_,_=struct.unpack('<IHHIhBBH',item['auxiliary_data'])
            if length or nrel or nline:
                raise Rejected('Attempt to exclude nonempty/unreviewed input section')
            if any(other is not item and other['section']==item['section']
                   for other in symbols.values()):
                raise Rejected('Excluded empty section has a data/user symbol')
            empty_sections.append(item['name'])
    return sorted(set(empty_sections))


def _link_compiled(object_path, symbol, address, bindings, output_dir, compile_manifest,
                   token, image_base=0x400000):
    """Retain/link every supported metadata section and audit every relocation."""
    if not re.fullmatch(r'[A-Za-z_@][A-Za-z0-9_@]*', symbol):
        raise Rejected('Unsupported C symbol spelling')
    if token is not _COMPILATION_TOKEN:
        raise Rejected('Only orchestrated fresh compilation may be linked')
    verify_compilation(compile_manifest,object_path)
    original_hash = digest(object_path)
    if compile_manifest['object_sha256'] != original_hash or digest(compile_manifest['source']) != compile_manifest['source_sha256']:
        raise Rejected('Fresh source/object changed')
    selected, material, needed, symbols = read_coff(object_path,symbol)
    if (type(address) is not int or type(image_base) is not int
        or not 0 <= image_base < 2**32 or image_base % 65536
        or address < image_base + 4096 or address + selected['size'] > 2**32):
        raise Rejected('Candidate address/image base outside supported PE32 range')
    current = address
    for section in material:
        section['address'] = current
        section['output_name'] = {'.debug$S':'.dbgS', '.debug$F':'.dbgF'}.get(section['name'], '.match')
        if current + section['size'] > 2**32:
            raise Rejected('Full function/metadata layout extent overflow')
        current = (current + section['size'] + 15) & ~15
    absolute, addresses = {}, set()
    defined = {s['name'] for s in symbols.values() if s['section'] != 0}
    if not isinstance(bindings,list) or any(not isinstance(b,dict) or set(b)!={'symbol','address'} for b in bindings):
        raise Rejected('Bindings must be exact symbol/address records in a list')
    for binding in bindings:
        name, target = binding['symbol'], binding['address']
        if not isinstance(name, str) or not re.fullmatch(r'[A-Za-z_@][A-Za-z0-9_@]*', name):
            raise Rejected('Unsupported binding name')
        if name in absolute or name in defined:
            raise Rejected('Duplicate/shadowing symbol collision')
        if type(target) is not int or not 0 < target < 2**32:
            raise Rejected('Absolute symbol outside uint32 range')
        if target in addresses or any(s['address'] <= target < s['address'] + s['size'] for s in material):
            raise Rejected('Address alias/function/metadata collision')
        absolute[name] = target
        addresses.add(target)
    if set(absolute) != needed:
        raise Rejected('Missing unresolved external or extraneous binding')
    for section in material:
        section['expected'] = []
        for r in section['relocations']:
            target = r['target']
            value = absolute[target['name']] if target['section'] == 0 else address + target['value']
            word=relocation_value(r['kind'],value,r['addend'],section['address']+r['offset'],image_base)
            section['expected'].append((r['offset'],word))
    out = Path(output_dir).resolve()
    if not out.is_relative_to(ROOT/'build') or out==ROOT/'build':
        raise Rejected('Link output must remain inside a build subdirectory')
    if not out.is_dir():
        raise Rejected('Compilation output directory disappeared')
    script, image = out / 'placement.ld', out / 'linked.exe'
    text = 'OUTPUT_FORMAT(pei-i386)\nENTRY("' + symbol + '")\n'
    text += ''.join('"%s" = 0x%08X;\n' % (n,v) for n,v in sorted(absolute.items()))
    text += 'SECTIONS {\n'
    for section in material:
        inputs = '.text .text$*' if section is selected else section['name']
        text += ' %s 0x%08X : { *(%s) }\n' % (section['output_name'], section['address'], inputs)
        text += ' ASSERT(SIZEOF(%s) == %d, "Complete section extent changed")\n' % (section['output_name'],section['size'])
    # Clang emits empty .data/.bss/.llvm_addrsig sections. GNU ld may synthesize
    # a one-byte orphan .data unless those proven-empty inputs are excluded.
    # This never discards a nonempty section or relocation: read_coff already
    # validated every section-primary aux; recheck each zero extent explicitly.
    empty_sections=audited_empty_sections(material,symbols)
    if empty_sections:
        text += ' /DISCARD/ : { '+''.join('*("%s") ' % n for n in sorted(set(empty_sections)))+'}\n'
    text += '}\n'
    script.write_text(text)
    resolved = str(Path('/usr/bin/ld').resolve())
    before_link = linker_identity(resolved)
    cmd = [resolved, '-m', 'i386pe', '--image-base', hex(image_base), '--disable-auto-import',
           '--disable-auto-image-base', '--disable-dynamicbase', '--disable-reloc-section',
           '--no-insert-timestamp', '--section-alignment', '1', '--file-alignment', '1',
           '-T', str(script), '-o', str(image), str(Path(object_path).resolve())]
    if image.exists():
        image.unlink()
    link_env = controlled_env()
    proc = subprocess.run(cmd,capture_output=True,text=True,env=link_env,cwd=ROOT,timeout=120)
    if proc.returncode or proc.stderr:
        raise Rejected('Linker failed or warned: '+proc.stdout+proc.stderr)
    verify_compilation(compile_manifest,object_path)
    pe = PE(image)
    if len(pe.sections) != len(material) or pe.image_base != image_base or int(pe.metadata['entry_point'],0) != address:
        raise Rejected('Ambiguous linked sections or placement')
    raw=image.read_bytes()
    peoff=struct.unpack_from('<I',raw,0x3c)[0]
    if any(raw[peoff+24+96:peoff+24+96+16*8]):
        raise Rejected('Unexpected linked data directory')
    descriptions=[]
    candidate=None
    for section in material:
        hits=[s for s in pe.sections if s['name']==section['output_name']]
        if len(hits)!=1:
            raise Rejected('Ambiguous/missing linked section')
        actual=hits[0]
        if (pe.image_base+actual['rva']!=section['address']
            or actual['virtual_size']!=section['size'] or actual['raw_size']!=section['size']
            or actual['executable'] != (section is selected)
            or (section is not selected and actual['characteristics'] & 0x80000000)):
            raise Rejected('Linked section extent/address/permissions differ')
        linked=(pe.region(section['address'],section['size']) if section is selected
                else pe.take(actual['raw_offset'],actual['raw_size']))
        changed=set()
        for offset,value in section['expected']:
            if struct.unpack_from('<I',linked,offset)[0]!=value:
                raise Rejected('Real linker resolution differs from independent arithmetic audit')
            changed.update(range(offset,offset+4))
        if any(a!=b for i,(a,b) in enumerate(zip(section['body'],linked)) if i not in changed):
            raise Rejected('Linker modified a byte outside audited relocation fields')
        descriptions.append(dict(input_section=section['name'],output_section=section['output_name'],
            address=section['address'],complete_size=section['size'],function=section is selected,
            input_characteristics=section['flags'],linked_characteristics=actual['characteristics'],
            input_sha256=hashlib.sha256(section['body']).hexdigest(),linked_sha256=hashlib.sha256(linked).hexdigest(),
            relocations=[dict(offset=r['offset'],type={6:'DIR32',7:'RVA32',20:'REL32'}[r['kind']],
                              symbol=r['target']['name'],addend=r['addend'],resolved_word=value)
                         for r,(_,value) in zip(section['relocations'],section['expected'])]))
        if section is selected:
            candidate=linked
    if candidate is None or digest(object_path)!=original_hash:
        raise Rejected('Missing full function or changed input object')
    after_link = linker_identity(resolved)
    if after_link != before_link:
        raise Rejected('Linker or libraries changed during execution')
    verify_compilation(compile_manifest,object_path)
    manifest=dict(schema_version=1,backend='clang-i686-scaffold-real-link',
        coff_dialect='clang-i386-section-number-self',experimental=True,proof_eligible=False,abi_compatible=None,function_symbol=symbol,candidate_address=address,
        complete_size=len(candidate),image_base=image_base,object_sha256=original_hash,bindings=bindings,
        compilation=compile_manifest,sections=descriptions,link_command=cmd,
        audited_empty_input_sections=sorted(set(empty_sections)),
        empty_section_policy="Explicit Clang empty-input-only exception to NO-DISCARD policy: only zero-size/zero-relocation/zero-user-symbol inputs excluded; every admitted nonempty section retained",
        linker_identity=before_link,
        implementation_identity=compile_manifest['implementation_identity'],
        prototype_sha256=compile_manifest['implementation_identity']['prototype']['sha256'],
        pe_reader_sha256=compile_manifest['implementation_identity']['pe_reader']['sha256'],
        script_sha256=digest(script),image_sha256=digest(image),candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        controlled_environment=link_env,working_directory=str(ROOT))
    (out/'candidate.bin').write_bytes(candidate)
    verify_compilation(compile_manifest,object_path)
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return candidate,manifest


if __name__=='__main__':
    try:
        config=json.loads(Path(sys.argv[1]).read_text())
        allowed={'source','symbol','address','bindings','output_dir','profile','image_base'}
        if not isinstance(config,dict) or set(config)-allowed:
            raise Rejected('Only source/profile orchestration accepted; no object/client manifest')
        candidate,manifest=compile_and_link(**config)
        print(json.dumps({'complete_size':len(candidate),'candidate_sha256':manifest['candidate_sha256'],
                          'experimental':True,'proof_eligible':False}))
    except (Rejected,OSError,TypeError,KeyError,ValueError) as error:
        print(str(error),file=sys.stderr)
        sys.exit(getattr(error,'exit_code',1))
