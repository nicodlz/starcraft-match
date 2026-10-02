"""Private opt-in external-only i386 COFF linker adapter.

No code/object modification, byte normalization, or defined-symbol rebinding.
The default repository COFF extractor is deliberately not imported or changed.
"""
from dataclasses import dataclass
import hashlib,json,pathlib,re,shutil,struct,subprocess

class LinkError(ValueError):
    pass

@dataclass(frozen=True)
class Symbol:
    index:int
    name:str
    value:int
    section:int
    type:int
    storage:int

@dataclass(frozen=True)
class Section:
    index:int
    name:str
    size:int
    flags:int
    payload:bytes|None
    relocations:tuple

@dataclass(frozen=True)
class Object:
    payload:bytes
    sections:tuple
    symbols:dict


def digest(data):return hashlib.sha256(data).hexdigest()

def read_coff(data):
    """Validate bounded standard COFF; reject unsupported auxiliary formats."""
    if not isinstance(data,bytes):raise LinkError('COFF input must be immutable bytes')
    spans=[]
    def region(offset,size,label,claim=False):
        if offset<0 or size<0 or offset+size>len(data):raise LinkError('Truncated '+label)
        if claim and size:
            if any(offset<b and a<offset+size for a,b,_ in spans):raise LinkError('Overlapping '+label)
            spans.append((offset,offset+size,label))
        return data[offset:offset+size]
    def unpack(fmt,offset,label):return struct.unpack(fmt,region(offset,struct.calcsize(fmt),label))
    machine,count,_,symptr,nsyms,optsize,fileflags=unpack('<HHIIIHH',0,'COFF header')
    if machine!=0x14c or optsize or fileflags&2:raise LinkError('Expected relocatable i386 COFF')
    if not count or count>4096 or nsyms>1000000:raise LinkError('Unsupported section/symbol count')
    region(0,20+count*40,'headers',True)
    if not symptr or not nsyms:raise LinkError('Missing symbol table')
    region(symptr,nsyms*18,'symbol table',True)
    strings=symptr+nsyms*18;strlen=unpack('<I',strings,'string size')[0]
    if strlen<4:raise LinkError('Invalid string-table length')
    stringdata=region(strings,strlen,'string table',True)
    def string(offset):
        if not 4<=offset<strlen:raise LinkError('Invalid string-table reference')
        end=stringdata.find(b'\0',offset)
        if end<0:raise LinkError('Unterminated COFF name')
        try:return stringdata[offset:end].decode('ascii')
        except UnicodeDecodeError:raise LinkError('Unsupported non-ASCII name')
    def symbol_name(raw):
        if raw[:4]==b'\0'*4:return string(struct.unpack('<I',raw[4:])[0])
        try:return raw.rstrip(b'\0').decode('ascii')
        except UnicodeDecodeError:raise LinkError('Unsupported non-ASCII name')
    rawsections=[]
    for i in range(count):
        sh=unpack('<8sIIIIIIHHI',20+i*40,'section header');n,_,_,size,ptr,relptr,lineptr,nrel,nline,flags=sh
        if n.startswith(b'/'):
            try:nm=string(int(n[1:].rstrip(b'\0')))
            except ValueError:raise LinkError('Malformed section string reference')
        else:nm=symbol_name(n)
        if not nm:raise LinkError('Empty section name')
        if flags&0x01000000 or nrel==0xffff:raise LinkError('Relocation overflow format unsupported')
        if nline or lineptr:raise LinkError('Legacy COFF line tables unsupported')
        if flags&0x00f00000>0x00e00000:raise LinkError('Invalid COFF section alignment')
        if size:
            if ptr:payload=region(ptr,size,'section data',True)
            elif flags&0x80 and not flags&0x20000000:payload=None
            else:raise LinkError('Missing nonempty section data')
        else:payload=b''
        if nrel:
            if not relptr:raise LinkError('Missing relocation table')
            region(relptr,nrel*10,'relocation table',True)
        elif relptr:raise LinkError('Unexpected empty relocation pointer')
        rawsections.append((nm,size,flags,payload,relptr,nrel))
    symbols={};auxrecords=[];i=0
    while i<nsyms:
        raw,value,sec,typ,storage,aux=unpack('<8sIhHBB',symptr+18*i,'symbol')
        nm=symbol_name(raw)
        if not nm or sec < -2 or sec>count or storage not in (2,3,103):raise LinkError('Unsupported symbol definition')
        if i+aux>=nsyms:raise LinkError('Auxiliary count exceeds symbol table')
        sym=Symbol(i,nm,value,sec,typ,storage);symbols[i]=sym
        if aux:
            if storage==103 and sec==-2 and typ==0:pass
            elif storage==3 and sec>0 and typ==0 and nm==rawsections[sec-1][0] and value==0 and aux==1:
                length,nr,nl,_,num,selection,reserved,high=unpack('<IHHIHBBH',symptr+18*(i+1),'section auxiliary')
                owner=rawsections[sec-1]
                if length!=owner[1] or nr!=owner[5] or nl or reserved or selection not in (0,1,2,3,4,5,6,7):raise LinkError('Invalid section auxiliary definition')
                assoc=num+(high<<16)
                if selection==5 and not 1<=assoc<=count:raise LinkError('Invalid associative COMDAT auxiliary')
                if bool(owner[2]&0x1000)!=(selection!=0):raise LinkError('COMDAT flag/auxiliary mismatch')
                auxrecords.append((sec,selection,assoc))
            else:raise LinkError('Unsupported symbol auxiliary format')
        elif storage==103:raise LinkError('Missing filename auxiliary')
        i+=aux+1
    sections=[]
    for i,(name,size,flags,payload,rp,nr) in enumerate(rawsections,1):
        relocations=[];used=set()
        for j in range(nr):
            off,idx,kind=unpack('<IIH',rp+j*10,'relocation')
            if idx not in symbols:raise LinkError('Relocation references auxiliary/missing symbol')
            if payload is None or off+4>size or used.intersection(range(off,off+4)):raise LinkError('Invalid/overlapping relocation range')
            used.update(range(off,off+4));relocations.append((off,kind,symbols[idx]))
        sections.append(Section(i,name,size,flags,payload,tuple(relocations)))
    return Object(data,tuple(sections),symbols)


def safe_symbol(name):
    if not isinstance(name,str) or not re.fullmatch(r'[A-Za-z_@][A-Za-z_0-9@]*',name):raise LinkError('Unsupported linker symbol syntax')
    return '"'+name+'"'

def safe_section(name):
    if not isinstance(name,str) or not re.fullmatch(r'\.[A-Za-z0-9_]{1,7}',name):raise LinkError('Selected section must have safe short PE name')
    return name

def unique_function(obj,name):
    hits=[s for s in obj.symbols.values() if s.name==name and s.section>0 and s.type&0x20]
    if len(hits)!=1:raise LinkError('Expected one function '+name)
    sym=hits[0];section=obj.sections[sym.section-1]
    functions=[s for s in obj.symbols.values() if s.section==sym.section and s.type&0x20]
    if sym.value or len(functions)!=1 or not section.size or not section.flags&0x20000000 or section.payload is None:raise LinkError('Need complete single-function executable contribution at offset zero')
    return section


def _audit(obj,record):
    if not isinstance(record,dict) or record.get('schema_version')!=1:raise LinkError('Unsupported linking record version')
    if not isinstance(record.get('candidate'),dict) or not isinstance(record.get('bindings'),dict) or not isinstance(record.get('excluded_contexts',[]),list):raise LinkError('Malformed candidate/bindings/context metadata')
    provenance=record.get('compiler_provenance')
    if not isinstance(provenance,dict) or not isinstance(provenance.get('profile'),str) or not provenance['profile']:raise LinkError('Compiler provenance/profile required')
    for field in ('source_sha256','compiler_driver_sha256','compiler_identity_sha256','compiler_profile_sha256'):
        if not isinstance(provenance.get(field),str) or not re.fullmatch(r'[0-9a-f]{64}',provenance[field]):raise LinkError('Compiler provenance hash required: '+field)
    cand=record['candidate'];safe_symbol(cand['symbol']);safe_section(cand['section'])
    selected=unique_function(obj,cand['symbol'])
    if selected.name!=cand['section'] or sum(s.name==selected.name and bool(s.size) for s in obj.sections)!=1:raise LinkError('Selected compiler section name is not unique')
    address=cand['address']
    if not isinstance(address,int) or isinstance(address,bool) or not 0x400000<=address<=0xffffffff-selected.size:raise LinkError('Invalid candidate address')
    ac=(selected.flags>>20)&15;alignment=1<<(ac-1) if ac else 1
    if address%alignment:raise LinkError('Candidate placement violates compiler alignment')
    if cand.get('object_sha256')!=digest(obj.payload):raise LinkError('Input object provenance changed')
    approved={}
    for item in record.get('excluded_contexts',[]):
        name=item['symbol'];safe_symbol(name)
        if name in approved or name==cand['symbol']:raise LinkError('Duplicate/selected excluded context')
        context=unique_function(obj,name)
        if context.name!=item['section'] or context.name==selected.name:raise LinkError('Context contribution cannot be selected/excluded separately')
        safe_section(context.name);approved[name]=context
    excluded={s.index:s for s in approved.values()}
    if len(excluded)!=len(approved):raise LinkError('Multiple context functions share section')
    for sec in obj.sections:
        if sec.index==selected.index or not sec.size:continue
        if sec.index in excluded:continue
        if sec.name in ('.debug$S','.debug$F') and not sec.flags&0xa0000000 and sec.flags&0x02000000 and all(k in (6,7) for _,k,_ in sec.relocations):continue
        raise LinkError('Unapproved nonempty code/data contribution '+sec.name)
    if any(s.name==ctx.name and s.size and s.index not in excluded for ctx in excluded.values() for s in obj.sections):raise LinkError('Context section selector would discard unapproved contribution')
    bindings=record.get('bindings',{});relocations=[];targets=set()
    for name,binding in bindings.items():
        safe_symbol(name);a=binding['address']
        if not isinstance(a,int) or isinstance(a,bool) or not 0<=a<=0xffffffff or binding.get('kind') not in ('code','data'):raise LinkError('Invalid external binding')
        if not isinstance(binding.get('evidence'),list) or not binding['evidence']:raise LinkError('External binding requires evidence attribution')
    for off,kind,sym in selected.relocations:
        if kind not in (6,20):raise LinkError('Unsupported candidate relocation type')
        if sym.section!=0 or sym.storage!=2 or any(s.name==sym.name and s.section!=0 for s in obj.symbols.values()):raise LinkError('Defined local/absolute helper rebinding is prohibited')
        if sym.name not in bindings:raise LinkError('Unbound external relocation '+sym.name)
        binding=bindings[sym.name]
        if kind==20 and binding['kind']!='code':raise LinkError('REL32 call requires code binding')
        targets.add(sym.name);relocations.append(dict(offset=off,type=kind,symbol=sym.name,address=binding['address'],addend=struct.unpack_from('<i',selected.payload,off)[0]))
    if set(bindings)!=targets:raise LinkError('Bindings must exactly cover external relocations')
    return selected,list(excluded.values()),relocations


def audit(obj,record):
    try:return _audit(obj,record)
    except LinkError:raise
    except (KeyError,TypeError,AttributeError,IndexError):raise LinkError('Malformed linking metadata')


def read_pe(data):
    """Bounded fixed-profile linked PE32 reader; no implicit section loss."""
    if not isinstance(data,bytes):raise LinkError('Linked PE input must be immutable bytes')
    def rd(fmt,p):
        n=struct.calcsize(fmt)
        if p<0 or p+n>len(data):raise LinkError('Truncated linked PE')
        return struct.unpack_from(fmt,data,p)
    if len(data)<64 or data[:2]!=b'MZ':raise LinkError('Invalid linked PE signature')
    pe=rd('<I',0x3c)[0]
    if pe<64 or pe%4 or data[pe:pe+4]!=b'PE\0\0':raise LinkError('Invalid linked PE signature')
    machine,count,_,sp,ns,opt,fileflags=rd('<HHIIIHH',pe+4)
    if machine!=0x14c or not 1<=count<=4096 or opt!=224 or not fileflags&2 or not fileflags&0x100:raise LinkError('Invalid linked i386 PE header/flags')
    o=pe+24
    if rd('<H',o)[0]!=0x10b:raise LinkError('Invalid linked PE32')
    if o+opt+40*count>len(data):raise LinkError('Truncated linked PE section headers')
    base=rd('<I',o+28)[0];entry=base+rd('<I',o+16)[0]
    alignment,filealign=rd('<II',o+32);imagesize,headersize=rd('<II',o+56)
    if base!=0x400000 or alignment!=16 or filealign!=16 or headersize<o+opt+40*count or headersize>len(data) or headersize%filealign or not imagesize or imagesize%alignment:raise LinkError('Invalid linked PE layout/header extent')
    nd=rd('<I',o+92)[0]
    if nd!=16:raise LinkError('Invalid PE data directories')
    for idx in range(nd):
        if rd('<II',o+96+8*idx)!=(0,0):raise LinkError('Imports/base relocations or other data directories prohibited')
    if bool(sp)!=bool(ns) or ns>1000000 or sp and (sp<headersize or sp+18*ns+4>len(data)):raise LinkError('Invalid linked PE symbol table')
    spans=[(0,headersize)];virtual=[];sections=[]
    for i in range(count):
        name,size,rva,rawsize,ptr,relptr,lineptr,nr,nl,flags=rd('<8sIIIIIIHHI',o+opt+i*40)
        try:nm=name.rstrip(b'\0').decode('ascii')
        except UnicodeDecodeError:raise LinkError('Invalid linked PE section name encoding')
        if not re.fullmatch(r'\.[A-Za-z0-9_]{1,7}',nm):raise LinkError('Invalid linked PE section name')
        if nr or nl or relptr or lineptr or not size or not rawsize or ptr<headersize or ptr%filealign or rawsize%filealign or ptr+rawsize>len(data) or size>rawsize:raise LinkError('Invalid linked file-backed section extent')
        if rva%alignment or rva<headersize or rva+size>imagesize or base+rva+size>0x100000000:raise LinkError('Invalid linked virtual section extent')
        if flags&0xe0000020!=0x60000020 or flags&0xc0:raise LinkError('Unexpected linked code section flags')
        if any(ptr<b and a<ptr+rawsize for a,b in spans) or any(rva<b and a<rva+size for a,b in virtual):raise LinkError('Overlapping linked PE sections/header')
        spans.append((ptr,ptr+rawsize));virtual.append((rva,rva+size))
        sections.append(dict(name=nm,size=size,address=base+rva,raw_size=rawsize,raw_pointer=ptr,flags=flags))
    if sp:
        strings=sp+ns*18;strlen=rd('<I',strings)[0]
        if strlen<4 or strings+strlen>len(data) or any(sp<b and a<strings+strlen for a,b in spans):raise LinkError('Invalid/overlapping linked symbol table')
    return entry,sections


def link_external_candidate(object_path,record,out_dir,linker='ld'):
    """Produce audited linked bytes plus deterministic linking provenance."""
    obj=read_coff(pathlib.Path(object_path).read_bytes());selected,excluded,relocs=audit(obj,record)
    executable=shutil.which(linker)
    if not executable:raise LinkError('Standard linker unavailable')
    identity=subprocess.check_output([executable,'--version'],text=True).splitlines()[0]
    linker_hash=digest(pathlib.Path(executable).read_bytes())
    expected=record.get('linker',{})
    if not isinstance(expected,dict):raise LinkError('Malformed linker metadata')
    if expected.get('sha256')!=linker_hash or expected.get('version')!=identity or expected.get('emulation')!='i386pe':raise LinkError('Linker identity/profile changed')
    out=pathlib.Path(out_dir);out.mkdir(parents=True,exist_ok=True)
    address=record['candidate']['address'];script=out/'layout.ld'
    script_text='\n'.join(f'{safe_symbol(n)} = 0x{b["address"]:08X};' for n,b in sorted(record['bindings'].items()))+'\nSECTIONS {\n'+f'{safe_section(selected.name)} 0x{address:08X} : {{ KEEP(*({safe_section(selected.name)})) }}\n/DISCARD/ : {{ '+' '.join(f'*({safe_section(n)})' for n in sorted({s.name for s in excluded}))+' *(.debug*) }\n}\n'
    script.write_text(script_text);image=out/'candidate.exe'
    snapshot=out/'link-input.obj';snapshot.write_bytes(obj.payload)
    cmd=[executable,'-mi386pe','--image-base','0x400000','--section-alignment','16','--file-alignment','16','--disable-reloc-section','--no-insert-timestamp','--entry',hex(address),'-T',str(script),'-Map',str(out/'candidate.map'),'-o',str(image),str(snapshot.resolve())]
    run=subprocess.run(cmd,capture_output=True,text=True);(out/'link.stdout').write_text(run.stdout);(out/'link.stderr').write_text(run.stderr)
    if run.returncode:raise LinkError('Standard linker rejected input: '+run.stderr)
    linked_image=image.read_bytes();entry,sections=read_pe(linked_image)
    nonempty=sections
    if len(nonempty)!=1:raise LinkError('Uncounted/extra contribution emitted')
    s=nonempty[0]
    if entry!=address or s['address']!=address or s['name']!=selected.name or s['size']!=selected.size or not s['flags']&0x20000000:raise LinkError('Whole selected extent/placement changed')
    code=linked_image[s['raw_pointer']:s['raw_pointer']+s['size']];occupied=set()
    for r in relocs:
        off=r['offset'];value=(r['address']+r['addend']-(address+off+4 if r['type']==20 else 0))&0xffffffff
        if struct.unpack_from('<I',code,off)[0]!=value:raise LinkError('Incorrect standard linker relocation')
        occupied.update(range(off,off+4))
    if any(a!=b for i,(a,b) in enumerate(zip(selected.payload,code)) if i not in occupied):raise LinkError('Nonrelocation bytes changed')
    # Re-read inputs after linking to avoid a concurrently replaced object/linker.
    if digest(pathlib.Path(object_path).read_bytes())!=digest(obj.payload) or digest(snapshot.read_bytes())!=digest(obj.payload) or digest(pathlib.Path(executable).read_bytes())!=linker_hash:raise LinkError('Input/linker changed during linking')
    manifest=dict(schema_version=1,category='external-standard-linked-C-contribution-v1',record_sha256=digest(json.dumps(record,sort_keys=True,separators=(',',':')).encode()),object_sha256=digest(obj.payload),selected_section_index=selected.index,selected_section_name=selected.name,whole_input_size=selected.size,linked_size=len(code),address=address,unlinked_section_sha256=digest(selected.payload),linked_function_sha256=digest(code),linked_image_sha256=digest(linked_image),linker=dict(executable=str(pathlib.Path(executable).resolve()),sha256=linker_hash,version=identity,emulation='i386pe'),command=cmd,script_sha256=digest(script_text.encode()),relocations=relocs,excluded_contexts=[dict(index=s.index,name=s.name,size=s.size,sha256=digest(s.payload)) for s in excluded],compiler_provenance=record.get('compiler_provenance'),normalization=False,object_byte_modification=False,context_emitted=False,original_comparison_performed=False)
    (out/'candidate.bin').write_bytes(code);(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return code,manifest
