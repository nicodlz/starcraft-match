"""Portable synthetic tests: Clang+i386 COFF+GNUld only; all binaries temporary."""
import copy,hashlib,json,pathlib,shutil,struct,subprocess,sys,tempfile,unittest
P=pathlib.Path(__file__).resolve().parent
sys.path.insert(0,str(P.parent/'tools'))
from matching.linking import LinkError,read_coff,read_pe,audit,link_external_candidate

class PortableLinkTests(unittest.TestCase):
 @classmethod
 def setUpClass(cls):
  if not shutil.which('clang') or not shutil.which('ld'):raise unittest.SkipTest('Clang and GNUld required')
  cls.temp=tempfile.TemporaryDirectory(prefix='synthetic-link-',dir=None);cls.dir=pathlib.Path(cls.temp.name)
  cls.addClassCleanup(cls.temp.cleanup)
  cls.source=cls.dir/'fixture.c';cls.source.write_bytes((P/'fixtures/linked_candidate.c').read_bytes());cls.obj=cls.dir/'fixture.obj'
  cls.flags=['--target=i686-pc-windows-msvc','-std=c90','-O2','-ffreestanding','-fno-ident','-fno-addrsig','-ffunction-sections']
  subprocess.run(['clang',*cls.flags,'-c',str(cls.source),'-o',str(cls.obj)],check=True)
  cls.data=cls.obj.read_bytes();cls.parsed=read_coff(cls.data);cls.linker=pathlib.Path(shutil.which('ld'));cls.compiler=pathlib.Path(shutil.which('clang'))
  cls.identity=subprocess.check_output(['clang','--version'],text=True)
  cls.code,cls.manifest=link_external_candidate(cls.obj,cls.record(),cls.dir/'baseline')
 @classmethod
 def record(cls):
  return dict(schema_version=1,candidate=dict(symbol='_candidate@4',section='.cand',address=0x423450,object_sha256=hashlib.sha256(cls.data).hexdigest()),bindings={'@fast_target@8':dict(address=0x456780,kind='code',evidence=['independent synthetic C declaration']), '_fixed_global':dict(address=0x512340,kind='data',evidence=['independent synthetic C declaration'])},excluded_contexts=[dict(symbol='_wrapper',section='.ctx')],linker=dict(sha256=hashlib.sha256(cls.linker.read_bytes()).hexdigest(),version=subprocess.check_output([str(cls.linker),'--version'],text=True).splitlines()[0],emulation='i386pe'),compiler_provenance=dict(profile='synthetic-clang-i686-o2',source_sha256=hashlib.sha256(cls.source.read_bytes()).hexdigest(),compiler_driver_sha256=hashlib.sha256(cls.compiler.read_bytes()).hexdigest(),compiler_identity_sha256=hashlib.sha256(cls.identity.encode()).hexdigest(),compiler_profile_sha256=hashlib.sha256(json.dumps(cls.flags).encode()).hexdigest()))
 def corrupt(self,action):
  data=bytearray(self.data);action(data);return bytes(data)
 def test_decorated_bindings_and_entire_contribution(self):
  section,contexts,relocs=audit(self.parsed,self.record());self.assertEqual(len(self.code),section.size);self.assertEqual(len(contexts),1)
  for r in self.manifest['relocations']:
   operand=struct.unpack_from('<I',self.code,r['offset'])[0]
   if r['type']==20:operand=(operand+0x423450+r['offset']+4)&0xffffffff
   self.assertEqual(operand,self.record()['bindings'][r['symbol']]['address'])
  self.assertEqual(len(relocs),2)
 def test_deterministic_standard_link(self):
  code,m=link_external_candidate(self.obj,self.record(),self.dir/'repeat')
  self.assertEqual(code,self.code);self.assertEqual(m['linked_image_sha256'],self.manifest['linked_image_sha256'])
 def test_default_extractor_remains_strict(self):
  from matching.compare import coff_function
  with self.assertRaises(ValueError):coff_function(self.obj, '_candidate@4')
  sec,_,_=audit(self.parsed,self.record());self.assertEqual(len(sec.relocations),2);self.assertFalse(self.manifest['object_byte_modification'])
 def test_missing_context_approval(self):
  r=self.record();r['excluded_contexts']=[]
  with self.assertRaisesRegex(LinkError,'Unapproved'):audit(self.parsed,r)
 def test_unbound_and_extra_bindings(self):
  r=self.record();del r['bindings']['_fixed_global']
  with self.assertRaisesRegex(LinkError,'Unbound'):audit(self.parsed,r)
  r=self.record();r['bindings']['_extra']=dict(address=0x700000,kind='code',evidence=['synthetic'])
  with self.assertRaisesRegex(LinkError,'exactly cover'):audit(self.parsed,r)
 def test_input_and_linker_identity_mismatch(self):
  r=self.record();r['candidate']['object_sha256']='0'*64
  with self.assertRaisesRegex(LinkError,'provenance changed'):audit(self.parsed,r)
  r=self.record();r['linker']['version']='incorrect'
  with self.assertRaisesRegex(LinkError,'Linker identity'):link_external_candidate(self.obj,r,self.dir/'wrong-linker')
 def test_truncated_coff(self):
  for n in [0,19,60,len(self.data)-1]:
   with self.subTest(size=n),self.assertRaises(LinkError):read_coff(self.data[:n])
 def test_bad_string_reference(self):
  sp=struct.unpack_from('<I',self.data,8)[0];idx=next(i for i,s in self.parsed.symbols.items() if len(s.name)>8)
  with self.assertRaises(LinkError):read_coff(self.corrupt(lambda b:struct.pack_into('<II',b,sp+idx*18,0,0xffffffff)))
 def test_bad_relocation_range(self):
  sec,_,_=audit(self.parsed,self.record());rp=struct.unpack_from('<I',self.data,20+(sec.index-1)*40+24)[0]
  with self.assertRaisesRegex(LinkError,'relocation range'):read_coff(self.corrupt(lambda b:struct.pack_into('<I',b,rp,sec.size)))
 def test_bad_section_aux_extent(self):
  sp=struct.unpack_from('<I',self.data,8)[0];sec,_,_=audit(self.parsed,self.record());idx=next(i for i,s in self.parsed.symbols.items() if s.section==sec.index and s.type==0 and s.name==sec.name)
  with self.assertRaisesRegex(LinkError,'section auxiliary'):read_coff(self.corrupt(lambda b:struct.pack_into('<I',b,sp+(idx+1)*18,sec.size+1)))
 def test_bad_symbol_aux_count(self):
  sp=struct.unpack_from('<I',self.data,8)[0];last=max(self.parsed.symbols)
  with self.assertRaisesRegex(LinkError,'Auxiliary count'):read_coff(self.corrupt(lambda b:b.__setitem__(sp+last*18+17,255)))
 def test_pe_header_bounds_and_non_ascii_name(self):
  raw=(self.dir/'baseline/candidate.exe').read_bytes()
  for n in [0,63,100]:
   with self.subTest(size=n),self.assertRaises(LinkError):read_pe(raw[:n])
  data=bytearray(raw);pe=struct.unpack_from('<I',data,0x3c)[0];opt=struct.unpack_from('<H',data,pe+20)[0];section=pe+24+opt;data[section]=255
  with self.assertRaisesRegex(LinkError,'encoding'):read_pe(bytes(data))
 def test_pe_import_and_bad_flags(self):
  raw=(self.dir/'baseline/candidate.exe').read_bytes();pe=struct.unpack_from('<I',raw,0x3c)[0];data=bytearray(raw);struct.pack_into('<II',data,pe+24+96+8,0x1000,20)
  with self.assertRaisesRegex(LinkError,'Imports'):read_pe(bytes(data))
  data=bytearray(raw);opt=struct.unpack_from('<H',data,pe+20)[0];section=pe+24+opt;flags=struct.unpack_from('<I',data,section+36)[0];struct.pack_into('<I',data,section+36,flags|0x80000000)
  with self.assertRaisesRegex(LinkError,'flags'):read_pe(bytes(data))
 def test_pe_raw_section_cannot_overlap_headers(self):
  data=bytearray((self.dir/'baseline/candidate.exe').read_bytes());pe=struct.unpack_from('<I',data,0x3c)[0];opt=struct.unpack_from('<H',data,pe+20)[0];struct.pack_into('<I',data,pe+24+opt+20,16)
  with self.assertRaisesRegex(LinkError,'extent'):read_pe(bytes(data))
 def test_symbol_and_section_injection_rejected(self):
  r=self.record();r['candidate']['symbol']='_candidate";bad'
  with self.assertRaisesRegex(LinkError,'symbol syntax'):audit(self.parsed,r)
  r=self.record();r['candidate']['section']='.cand)'
  with self.assertRaisesRegex(LinkError,'section'):audit(self.parsed,r)

if __name__=='__main__':unittest.main(verbosity=2)
