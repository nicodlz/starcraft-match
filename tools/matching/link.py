#!/usr/bin/env python3
"""Fresh standalone C compilation and audited whole COFF/PE linking."""
import hashlib
import json
import re
import struct
import subprocess
import sys
import os
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
if Path(__file__).resolve() != ROOT/'tools/matching/link.py':
    raise RuntimeError('Link backend must reside at tools/matching/link.py')
sys.path.insert(0, str(ROOT / 'tools'))
_LOADED_PATHS = {'prototype': Path(__file__).resolve(),
                 'pe_reader': ROOT/'tools/analysis/pe.py',
                 'orchestrator_python': Path(sys.executable).resolve()}
_LOADED_BYTES = {name:path.read_bytes() for name,path in _LOADED_PATHS.items()}
_LOADED_HASHES = {name:hashlib.sha256(data).hexdigest()
                  for name,data in _LOADED_BYTES.items()}
# Execute exactly the reader snapshot whose hash is recorded. Ordinary import
# could reuse an older cached module or bytecode after an on-disk source edit.
_PE_NAMESPACE = {'__name__':'private_hardened_pe_reader',
                 '__file__':str(_LOADED_PATHS['pe_reader'])}
exec(compile(_LOADED_BYTES['pe_reader'],str(_LOADED_PATHS['pe_reader']),'exec'),_PE_NAMESPACE)
PE = _PE_NAMESPACE['PE']
del _LOADED_BYTES

class Rejected(ValueError):
    pass

class ToolchainUnavailable(Rejected):
    """Missing default toolchain only; caller may explicitly select fallback."""
    exit_code = 69

class ToolchainMisconfigured(Rejected):
    """Invalid/partial/explicit toolchain configuration must not fall back."""
    exit_code = 78

def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def implementation_identity():
    paths={**_LOADED_PATHS, 'driver_python':Path('/usr/bin/python3').resolve()}
    hashes={name:digest(path) for name,path in paths.items()}
    if any(hashes[name]!=expected for name,expected in _LOADED_HASHES.items()):
        raise Rejected('Loaded implementation/reader/interpreter changed on disk')
    return {name:{'path':str(paths[name]),'sha256':value} for name,value in hashes.items()}

def verify_implementation(expected):
    if implementation_identity()!=expected:
        raise Rejected('Implementation/reader/Python identity changed during execution')

_COMPILATION_TOKEN = object()
COMPILER_NAMES = frozenset(('cl.exe','c1.dll','c1xx.dll','c2.dll','msobj71.dll',
    'mspdb71.dll','msvcr71.dll','msvcp71.dll','dbghelp.dll','driver','wibo'))

def controlled_env(compiler=False):
    env={'PATH':'/usr/bin:/bin','LC_ALL':'C','LANG':'C'}
    if compiler:
        # Preserve whether configuration was explicit: the public driver uses
        # this to distinguish absent defaults (69) from bad configuration (78).
        for name in ('SC_MSVC71_BIN','SC_WIBO'):
            if name in os.environ:
                env[name]=str(Path(os.environ[name]).expanduser().resolve())
    return env

def component_paths():
    env=controlled_env(True)
    return {name: (ROOT/'tools/compilers/msvc71' if name=='driver' else
        Path(env.get('SC_WIBO',str(ROOT/'.local/toolchains/wibo/wibo-i686'))) if name=='wibo'
        else Path(env.get('SC_MSVC71_BIN',str(ROOT/'.local/toolchains/msvc71/bin')))/name)
        for name in COMPILER_NAMES}

def verify_identity(identity):
    if not isinstance(identity,dict) or (identity.get('status'),identity.get('compiler'),
        identity.get('version'),identity.get('target'),identity.get('schema_version')) != (
        'available','MSVC','13.10.3077','Windows i386',1):
        raise Rejected('Available pinned compiler identity required')
    hashes=identity.get('component_sha256')
    if not isinstance(hashes,dict) or set(hashes)!=COMPILER_NAMES:
        raise Rejected('Exact nonempty compiler component inventory required')
    for name,path in component_paths().items():
        h=hashes[name]
        if not isinstance(h,str) or not re.fullmatch('[0-9a-f]{64}',h) or digest(path)!=h:
            raise Rejected('Compiler component identity changed: '+name)
    contents={k:v for k,v in identity.items() if k!='identity_sha256'}
    h=hashlib.sha256(json.dumps(contents,sort_keys=True).encode()).hexdigest()
    if identity.get('identity_sha256')!=h:
        raise Rejected('Compiler identity hash differs')

def fresh_identity():
    proc=subprocess.run([str(ROOT/'tools/compilers/msvc71'),'--identity-json'],
        env=controlled_env(True),cwd=ROOT,capture_output=True,text=True,timeout=60)
    if proc.returncode==78:
        raise ToolchainMisconfigured('MSVC toolchain configuration rejected: '+proc.stdout+proc.stderr)
    try: identity=json.loads(proc.stdout)
    except json.JSONDecodeError as error: raise Rejected('Malformed compiler identity') from error
    if not isinstance(identity,dict):
        raise Rejected('Compiler identity must be an object')
    if (proc.returncode==69 and not proc.stderr and identity.get('status')=='unavailable'
        and not any(name in os.environ for name in ('SC_MSVC71_BIN','SC_WIBO'))):
        raise ToolchainUnavailable('Default MSVC toolchain unavailable')
    if proc.returncode or proc.stderr:
        raise Rejected('Compiler identity query failed: '+proc.stdout+proc.stderr)
    verify_identity(identity)
    return identity

def verify_available_identity(expected):
    """After availability has been established, absence is configuration drift."""
    try:
        identity=fresh_identity()
    except ToolchainUnavailable as error:
        raise ToolchainMisconfigured('Available MSVC toolchain disappeared during identity recheck') from error
    if identity!=expected:
        raise ToolchainMisconfigured('Available MSVC compiler identity changed')

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

def compile_and_link(source,symbol,address,bindings,output_dir,profile='msvc71-o2',image_base=0x400000):
    """Public API accepts C source only, never an object or producer manifest."""
    implementation=implementation_identity()
    if not isinstance(symbol,str) or not re.fullmatch(r'[A-Za-z_@][A-Za-z0-9_@]*',symbol):
        raise Rejected('Invalid C symbol spelling')
    if profile not in ('msvc71-o2','msvc71-o2-frame'):
        raise Rejected('Only registered historical profiles allowed')
    source=Path(source).resolve();out=Path(output_dir).resolve()
    if not source.is_relative_to(ROOT/'src') or source.suffix.lower()!='.c' or not source.is_file():
        raise Rejected('Only autonomous C sources inside src allowed')
    if not out.is_relative_to(ROOT/'build') or out==ROOT/'build' or out.exists():
        raise Rejected('Output must be a new build directory; no stale objects')
    source_bytes=source.read_bytes()
    source_hash=hashlib.sha256(source_bytes).hexdigest()
    try:
        text=source_bytes.decode('utf-8')
    except UnicodeDecodeError as error:
        raise Rejected('Source must be valid UTF-8') from error
    # This intentionally narrow source subset excludes directives even when
    # hidden by line splicing, comments, digraphs, or trigraphs. No external
    # preprocessing dependency may evade the source hash.
    lexical=text.replace('??/','\\')
    while True:
        joined=re.sub(r'\\[ \t\f\v]*(?:\r\n|\r|\n)','',lexical)
        if joined==lexical:
            break
        lexical=joined
    if any(marker in value for value in (text,lexical) for marker in ('#','%:','??=')):
        raise Rejected('Headers/directives unsupported; autonomous source required')
    if any('??/' in value or re.search(r'\b(?:__asm|_asm|asm|_Pragma|__pragma)\b',value)
           for value in (text,lexical)):
        raise Rejected('Assembly source unsupported; C-derived code without pragmas required')
    profiles_file=ROOT/'config/compilers.json';profiles_hash=digest(profiles_file)
    try:
        profiles=json.loads(profiles_file.read_text())
    except json.JSONDecodeError as error:
        raise ToolchainMisconfigured('Malformed registered compiler profile JSON') from error
    if not isinstance(profiles,dict) or not isinstance(profiles.get(profile),dict):
        raise ToolchainMisconfigured('Registered compiler profile must be an object')
    config=profiles[profile]
    expected=['/nologo','/O2','/Oy','/Gy','/Zl','/G6'] if profile=='msvc71-o2' else ['/nologo','/O2','/Gy','/Zl','/G6','/Oy-']
    if (config.get('executable')!='./tools/compilers/msvc71' or config.get('flags')!=expected
        or config.get('identity_arguments')!=['--identity-json']):
        raise ToolchainMisconfigured('Registered profile does not match bounded supported contract')
    identity=fresh_identity()
    if digest(source)!=source_hash:
        raise Rejected('Source changed between validation and compilation')
    out.mkdir(parents=True);obj=out/'candidate.obj'
    command=[str(ROOT/config['executable']),*config['flags'],'-c',str(source),'-o',str(obj)]
    if digest(source)!=source_hash:
        raise Rejected('Source changed immediately before compilation')
    verify_implementation(implementation)
    proc=subprocess.run(command,env=controlled_env(True),cwd=ROOT,capture_output=True,text=True,timeout=120)
    if proc.returncode==78:
        raise ToolchainMisconfigured('MSVC compilation configuration rejected: '+proc.stdout+proc.stderr)
    if proc.returncode==69:
        # Identity was available before compilation: disappearance is drift,
        # not the initial missing-default condition eligible for fallback.
        raise ToolchainMisconfigured('Available MSVC toolchain disappeared during compilation')
    if proc.returncode or re.search(r'\bwarning\b',proc.stdout+proc.stderr,re.I) or not obj.is_file():
        raise Rejected('Fresh compilation failed/warned: '+proc.stdout+proc.stderr)
    if digest(source)!=source_hash or digest(profiles_file)!=profiles_hash:
        raise Rejected('Source/profile/compiler changed during compilation')
    verify_available_identity(identity)
    verify_implementation(implementation)
    manifest={'source':str(source),'source_sha256':source_hash,'object':str(obj),'object_sha256':digest(obj),
        'command':command,'compiler_profile':profile,'compiler_profile_config':config,
        'profiles_sha256':profiles_hash,'compiler_identity':identity,
        'toolchain_components':[{'name':n,'path':str(path),'sha256':identity['component_sha256'][n]}
            for n,path in sorted(component_paths().items())],
        'compiler_environment':controlled_env(True),'working_directory':str(ROOT),
        'stdout':proc.stdout,'stderr':proc.stderr,'returncode':proc.returncode,
        'implementation_identity':implementation,
        'orchestrator_python':implementation['orchestrator_python']['path'],
        'orchestrator_python_sha256':implementation['orchestrator_python']['sha256'],
        'driver_python':implementation['driver_python']['path'],
        'driver_python_sha256':implementation['driver_python']['sha256']}
    return _link_compiled(obj,symbol,address,bindings,out,manifest,_COMPILATION_TOKEN,image_base)

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
                    valid=selection==1 and association==0
                else:
                    valid=(section['name']=='.debug$F' and selection==5 and association==selected
                           and bool(sections[selected-1]['flags'] & 0x1000))
            else:
                valid=selection==0 and association==0
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

def _link_compiled(object_path, symbol, address, bindings, output_dir, compile_manifest,
                   token, image_base=0x400000):
    """Retain/link every supported metadata section and audit every relocation."""
    if not re.fullmatch(r'[A-Za-z_@][A-Za-z0-9_@]*', symbol):
        raise Rejected('Unsupported C symbol spelling')
    if token is not _COMPILATION_TOKEN:
        raise Rejected('Only orchestrated fresh compilation may be linked')
    verify_implementation(compile_manifest['implementation_identity'])
    original_hash = digest(object_path)
    if compile_manifest['object_sha256'] != original_hash or digest(compile_manifest['source']) != compile_manifest['source_sha256']:
        raise Rejected('Fresh source/object changed')
    verify_identity(compile_manifest['compiler_identity'])
    selected, material, needed, symbols = read_coff(object_path, symbol)
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
    # All nonempty sections were either selected or included explicitly above.
    # Only zero-length input sections remain; they contain no bytes or relocations.
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
    verify_implementation(compile_manifest['implementation_identity'])
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
    verify_available_identity(compile_manifest['compiler_identity'])
    if digest(compile_manifest['source']) != compile_manifest['source_sha256']:
        raise Rejected('Source changed during link')
    if digest(ROOT/'config/compilers.json') != compile_manifest['profiles_sha256']:
        raise Rejected('Registered profiles changed during link')
    verify_implementation(compile_manifest['implementation_identity'])
    manifest=dict(schema_version=1,experimental=True,function_symbol=symbol,candidate_address=address,
        complete_size=len(candidate),image_base=image_base,object_sha256=original_hash,bindings=bindings,
        compilation=compile_manifest,sections=descriptions,link_command=cmd,
        linker_identity=before_link,
        implementation_identity=compile_manifest['implementation_identity'],
        prototype_sha256=compile_manifest['implementation_identity']['prototype']['sha256'],
        pe_reader_sha256=compile_manifest['implementation_identity']['pe_reader']['sha256'],
        script_sha256=digest(script),image_sha256=digest(image),candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        controlled_environment=link_env,working_directory=str(ROOT))
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return candidate,manifest

if __name__=='__main__':
    try:
        config=json.loads(Path(sys.argv[1]).read_text())
        allowed={'source','symbol','address','bindings','output_dir','profile','image_base'}
        if not isinstance(config,dict) or set(config)-allowed:
            raise Rejected('Unsupported orchestration input; no object or client manifest accepted')
        candidate,manifest=compile_and_link(**config)
        print(json.dumps({'size':len(candidate),'sha256':manifest['candidate_sha256'],'experimental':True}))
    except (Rejected,OSError,TypeError,KeyError,json.JSONDecodeError) as error:
        print(str(error),file=sys.stderr)
        sys.exit(getattr(error,'exit_code',1))
