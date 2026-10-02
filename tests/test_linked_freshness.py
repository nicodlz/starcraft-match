"""Portable probes of actual decomp linked freshness format; no game/compiler needed."""
import copy,hashlib,importlib.machinery,json,pathlib,tempfile,unittest
from unittest.mock import patch
ROOT=pathlib.Path(__file__).resolve().parents[1]
DECOMP=ROOT/'tools/decomp'
m=importlib.machinery.SourceFileLoader('integrated_freshness_review',str(DECOMP)).load_module()
def sha(data):return hashlib.sha256(data).hexdigest()
class LinkedFreshnessTests(unittest.TestCase):
 def setUp(self):
  self.tmp=tempfile.TemporaryDirectory();self.root=pathlib.Path(self.tmp.name)
  for p in ['config','tools/matching','build/0x00410000/linked']:(self.root/p).mkdir(parents=True,exist_ok=True)
  for p,data in {'source.c':b'int candidate(void){return 1;}','header.h':b'#define VALUE 1','tools/decomp':b'synthetic engine snapshot','tools/matching/linking.py':b'synthetic adapter snapshot','compiler':b'synthetic compiler binary','linker':b'synthetic linker binary','build/0x00410000/candidate.bin':b'synthetic linked function','build/0x00410000/candidate.obj':b'synthetic COFF','build/0x00410000/linked/link-input.obj':b'synthetic COFF','build/0x00410000/linked/candidate.exe':b'synthetic linked image','build/0x00410000/linked/layout.ld':b'synthetic script'}.items():
   (self.root/p).write_bytes(data)
  for p in ['compiler','linker']:(self.root/p).chmod(0o700)
  self.profile={'executable':str(self.root/'compiler'),'flags':['/O2']}
  self.linkconfig=dict(executable=str(self.root/'linker'),emulation='i386pe',image_base='0x00400000',section_alignment=16,file_alignment=16,timestamps=False,base_relocations=False,mode='external-only-whole-contribution-v1')
  (self.root/'config/compilers.json').write_text(json.dumps({'historical':self.profile}))
  (self.root/'config/linkers.json').write_text(json.dumps({'external':self.linkconfig}))
  self.r=dict(address='0x00410000',candidate_source='source.c',candidate_symbol='_candidate',compiler_profile='historical',binary_sha256='a'*64,known_structures=['header.h'],candidate_abi_compatible=True,linking=dict(schema_version=1,profile='external',section='.scmatch',bindings={'_external':dict(address=0x410100,kind='code',evidence=['synthetic'])},excluded_contexts=[]))
  self.patches=[patch.object(m,'ROOT',self.root),patch.object(m,'compiler_identity',return_value=None),patch.object(m.subprocess,'check_output',return_value='Synthetic ld version1\n')]
  for p in self.patches:p.start()
  b=dict(source_sha256=m.file_digest(self.root/'source.c'),headers_sha256={'header.h':m.file_digest(self.root/'header.h')},compiler_profile_config=copy.deepcopy(self.profile),compiler_sha256=m.compiler_digest(self.profile['executable']),compiler_identity=None,engine_sha256=m.file_digest(self.root/'tools/decomp'),function_record_sha256=m.json_digest(self.r),linker_state=m.linker_state(self.r),match_method='standard-linked-c-external',source_only_fallback_for=None,source_only_compile=False,candidate_sha256=m.file_digest(self.root/'build/0x00410000/candidate.bin'),object_sha256=m.file_digest(self.root/'build/0x00410000/candidate.obj'),linking_record_sha256='b'*64)
  b['linking']=dict(linked_function_sha256=b['candidate_sha256'],whole_input_size=25,linked_size=25,address=0x410000,record_sha256=b['linking_record_sha256'],category='external-standard-linked-C-contribution-v1',linked_image_sha256=m.file_digest(self.root/'build/0x00410000/linked/candidate.exe'),script_sha256=m.file_digest(self.root/'build/0x00410000/linked/layout.ld'),object_sha256=b['object_sha256'])
  expected=m.linking_record(self.r,b,b['linker_state'])
  b['linking_record_sha256']=m.json_digest(expected)
  b['linking'].update(record_sha256=b['linking_record_sha256'],compiler_provenance=copy.deepcopy(expected['compiler_provenance']),linker={k:b['linker_state'][k] for k in ('executable','sha256','version','emulation')},selected_section_name=self.r['linking']['section'],whole_input_size=(self.root/'build/0x00410000/candidate.bin').stat().st_size,linked_size=(self.root/'build/0x00410000/candidate.bin').stat().st_size)
  self.report=dict(binary_sha256='a'*64,abi_compatible=True,build=b)
 def tearDown(self):
  for p in reversed(self.patches):p.stop()
  self.tmp.cleanup()
 def fresh(self):return m.report_is_fresh(self.r,self.report)
 def mutate(self,path):(self.root/path).write_bytes(b'changed')
 def test_baseline_linked_manifest_is_fresh(self):self.assertTrue(self.fresh())
 def test_missing_header_inventory_rejects(self):
  self.report['build']['headers_sha256']={};self.assertFalse(self.fresh())
 def test_missing_link_manifest_rejects(self):
  del self.report['build']['linking'];self.assertFalse(self.fresh())
 def test_adapter_change_rejects(self):
  self.mutate('tools/matching/linking.py');self.assertFalse(self.fresh())
 def test_linker_binary_change_rejects(self):
  self.mutate('linker');self.assertFalse(self.fresh())
 def test_linker_version_change_rejects(self):
  with patch.object(m.subprocess,'check_output',return_value='Synthetic ld version2\n'):self.assertFalse(self.fresh())
 def test_link_record_digest_corruption_rejects(self):
  self.report['build']['linking']['record_sha256']='different';self.assertFalse(self.fresh())
 def test_fallback_report_rejects(self):
  self.report['build']['source_only_fallback_for']='historical';self.assertFalse(self.fresh())
 def test_linked_function_digest_corruption_rejects(self):
  self.report['build']['linking']['linked_function_sha256']='different';self.assertFalse(self.fresh())
 def test_compiler_replacement_same_process_rejects(self):
  self.assertTrue(self.fresh());self.mutate('compiler');self.assertFalse(self.fresh())
 def test_source_mutation_rejects(self):
  self.mutate('source.c');self.assertFalse(self.fresh())
 def test_header_mutation_rejects(self):
  self.mutate('header.h');self.assertFalse(self.fresh())
 def test_engine_mutation_rejects(self):
  self.mutate('tools/decomp');self.assertFalse(self.fresh())
 def test_record_binding_change_rejects(self):
  self.r['linking']['bindings']['_external']['address']+=16;self.assertFalse(self.fresh())
 def test_profile_mutation_rejects(self):
  (self.root/'config/compilers.json').write_text(json.dumps({'historical':dict(self.profile,flags=['/O1'])}));self.assertFalse(self.fresh())
 def test_linker_config_mutation_rejects(self):
  (self.root/'config/linkers.json').write_text(json.dumps({'external':dict(self.linkconfig,section_alignment=32)}));self.assertFalse(self.fresh())
 def test_candidate_bin_mutation_rejects(self):
  self.mutate('build/0x00410000/candidate.bin');self.assertFalse(self.fresh())
 def test_candidate_object_mutation_rejects(self):
  self.mutate('build/0x00410000/candidate.obj');self.assertFalse(self.fresh())
 def test_image_script_snapshot_mutations_reject(self):
  for path in ['build/0x00410000/linked/candidate.exe','build/0x00410000/linked/layout.ld','build/0x00410000/linked/link-input.obj']:
   with self.subTest(path=path):
    data=(self.root/path).read_bytes();self.mutate(path);self.assertFalse(self.fresh());(self.root/path).write_bytes(data)
 def test_missing_artifact_rejects(self):
  (self.root/'build/0x00410000/linked/candidate.exe').unlink();self.assertFalse(self.fresh())
 def test_source_only_object_marker_rejects(self):
  self.report['build']['source_only_compile']=True;self.assertFalse(self.fresh())
 def test_abi_mismatch_rejects(self):
  self.report['abi_compatible']=False;self.assertFalse(self.fresh())
 def test_placement_extent_category_corruption_rejects(self):
  for key,value in [('address',0x410010),('linked_size',26),('category','unknown')]:
   with self.subTest(key=key):
    old=self.report['build']['linking'][key];self.report['build']['linking'][key]=value;self.assertFalse(self.fresh());self.report['build']['linking'][key]=old
 def test_match_method_corruption_rejects(self):
  self.report['build']['match_method']='isolated-coff';self.assertFalse(self.fresh())
 def test_coordinated_digest_corruption_rejects(self):
  self.report['build']['linking_record_sha256']='f'*64
  self.report['build']['linking']['record_sha256']='f'*64
  self.assertFalse(self.fresh())
 def test_compiler_provenance_mirror_corruption_rejects(self):
  self.report['build']['linking']['compiler_provenance']['source_sha256']='f'*64
  self.assertFalse(self.fresh())
 def test_linker_mirror_corruption_rejects(self):
  self.report['build']['linking']['linker']['version']='forged version'
  self.assertFalse(self.fresh())
 def test_section_mirror_corruption_rejects(self):
  self.report['build']['linking']['selected_section_name']='.other'
  self.assertFalse(self.fresh())
 def test_consistent_extent_corruption_rejects(self):
  self.report['build']['linking']['whole_input_size']+=1
  self.report['build']['linking']['linked_size']+=1
  self.assertFalse(self.fresh())
if __name__=='__main__':unittest.main(verbosity=2)
