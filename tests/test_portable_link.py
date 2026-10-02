#!/usr/bin/env python3
"""Only synthetic autonomous C sources; hostile COFF copies are negative parser tests."""
import inspect
import json
import struct
import shutil
import types
import unittest
import uuid
from pathlib import Path
from unittest.mock import patch

D=Path(__file__).resolve().parents[1]
m=types.ModuleType('portable_link');m.__file__=str(D/'tools/matching/portable.py')
exec(compile((D/'tools/matching/portable.py').read_bytes(),m.__file__,'exec'),m.__dict__)
B=[{'symbol':'_helper','address':0x408000},{'symbol':'_external_data','address':0x500020}]

class PortableTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.fixtures=D/'src'/('synthetic-portable-'+uuid.uuid4().hex)
        cls.fixtures.mkdir(parents=True)
        cls.addClassCleanup(shutil.rmtree,cls.fixtures,ignore_errors=True)
        cls.source=cls.fixtures/'call-data.c'
        cls.source.write_text('extern unsigned helper(unsigned); extern unsigned external_data; '
                              'unsigned synthetic(unsigned x){return helper(x)+external_data;}\n')
        cls.good_dir=cls.output('baseline')
        cls.good,cls.manifest=m.compile_and_link(cls.source,'_synthetic',0x412340,B,cls.good_dir)
        cls.obj=cls.good_dir/'candidate.obj';cls.raw=cls.obj.read_bytes()
        cls.parser=dict(read_coff=m.read_coff,Rejected=m.Rejected)
        cls.selected,cls.material,cls.needed,cls.symbols=cls.parser['read_coff'](cls.obj,'_synthetic')

    @staticmethod
    def output(label):return D/'build/test-output'/(label+'-'+uuid.uuid4().hex)
    def link(self,source=None,**kw):
        args=dict(source=source or self.source,symbol='_synthetic',address=0x412340,bindings=B,
                  output_dir=self.output(self._testMethodName));args.update(kw)
        return m.compile_and_link(**args)
    def source_fixture(self,name,text):
        p=self.fixtures/(name+'.c');p.write_text(text);return p
    def negative(self,name,mutate):
        data=bytearray(self.raw);mutate(data)
        p=D/'build/negative-coff'/(name+'.obj');p.parent.mkdir(exist_ok=True);p.write_bytes(data)
        with self.assertRaises(self.parser['Rejected']):self.parser['read_coff'](p,'_synthetic')

    def test_call_and_external_dword_whole_link(self):
        self.assertEqual(len(self.good),self.selected['size'])
        self.assertEqual({r['type'] for r in self.manifest['sections'][0]['relocations']},{'DIR32','REL32'})
        pe=m.PE(self.good_dir/'linked.exe')
        self.assertEqual(self.good,pe.region(0x412340,len(self.good)))
        self.assertFalse(self.manifest['proof_eligible']);self.assertIsNone(self.manifest['abi_compatible'])
        self.assertEqual(m.digest(self.obj),self.manifest['object_sha256'])
        self.assertIn('exception',self.manifest['empty_section_policy'])

    def test_binding_change_changes_complete_bytes(self):
        changed=[dict(x) for x in B];changed[0]['address']+=0x100
        data,manifest=self.link(bindings=changed)
        self.assertEqual(len(data),len(self.good));self.assertNotEqual(data,self.good)
        self.assertNotEqual(manifest['candidate_sha256'],self.manifest['candidate_sha256'])

    def test_recursive_local_relocation(self):
        p=self.source_fixture('recursive','unsigned synthetic(unsigned x){if(x<2)return x;'
                              'return synthetic(x-1)+synthetic(x-2);}\n')
        data,manifest=self.link(p,bindings=[])
        local=[r for r in manifest['sections'][0]['relocations'] if r['type']=='REL32' and r['symbol']=='_synthetic']
        self.assertTrue(local);self.assertEqual(len(data),manifest['complete_size'])
        for r in local:self.assertEqual(r['resolved_word'],(-r['offset']-4+r['addend']) & 0xffffffff)

    def test_nonempty_data_rejected(self):
        p=self.source_fixture('extra-data','static volatile unsigned data=3; unsigned synthetic(unsigned x){return data+x;}\n')
        with self.assertRaisesRegex(m.Rejected,'nonempty'):self.link(p,bindings=[])

    def test_nonempty_addrsig_rejected(self):
        p=self.source_fixture('addrsig','extern volatile unsigned external_data; unsigned synthetic(unsigned x){return external_data+x;}\n')
        with self.assertRaisesRegex(m.Rejected,'nonempty'):self.link(p,bindings=[B[1]])

    def test_compile_warning_rejected(self):
        p=self.source_fixture('warning','unsigned char synthetic(void){return 256;}\n')
        with self.assertRaisesRegex(m.Rejected,'warned'):self.link(p,bindings=[])

    def test_unknown_relocation_rejected(self):
        self.negative('unknown-reloc',lambda data:struct.pack_into('<H',data,self.selected['relptr']+8,99))

    def test_overlapping_relocation_rejected(self):
        self.negative('overlap',lambda data:struct.pack_into('<I',data,self.selected['relptr']+10,self.material[0]['relocations'][0]['offset']))

    def test_section_aux_number_mismatch_rejected(self):
        symptr=struct.unpack_from('<I',self.raw,8)[0]
        index=next(i for i,s in self.symbols.items() if s['section']==self.selected['number'] and s['storage']==3)
        self.negative('aux-number',lambda data:struct.pack_into('<h',data,symptr+(index+1)*18+12,0))

    def test_empty_input_user_symbol_rejected(self):
        symbols={i:dict(item) for i,item in self.symbols.items()}
        empty=next(item for item in symbols.values() if item['storage']==3 and item['section']>0
                   and item['auxiliaries']==1 and item['name'] not in {x['name'] for x in self.material})
        symbols[max(symbols)+1]=dict(name='_empty_user',section=empty['section'],storage=3,
                                   auxiliaries=0,value=0,type=0,auxiliary_data=b'')
        with self.assertRaisesRegex(m.Rejected,'data/user symbol'):
            m.audited_empty_sections(self.material,symbols)

    def test_associative_metadata_requires_comdat_parent(self):
        # Independently assembled hostile metadata fixture around synthetic C code.
        body=self.selected['body'];debug=b'\0'*4;headers=100
        relptr=headers+len(body)+len(debug);symptr=relptr+10
        header=struct.pack('<HHIIIHH',0x14c,2,0,symptr,5,0,0)
        sec1=struct.pack('<8sIIIIIIHHI',b'.text',0,0,len(body),headers,0,0,0,0,0x60000020)
        sec2=struct.pack('<8sIIIIIIHHI',b'.debug$F',0,0,4,headers+len(body),relptr,0,1,0,0x42001040)
        def symbol(name,sec,typ=0,storage=3,aux=1):
            return struct.pack('<8sIhHBB',name,0,sec,typ,storage,aux)
        aux1=struct.pack('<IHHIhBBH',len(body),0,0,0,1,0,0,0)
        aux2=struct.pack('<IHHIhBBH',4,1,0,0,1,5,0,0)
        table=symbol(b'.text',1)+aux1+symbol(b'.debug$F',2)+aux2+symbol(b'_synth',1,0x20,2,0)
        raw=header+sec1+sec2+body+debug+struct.pack('<IIH',0,4,7)+table+struct.pack('<I',4)
        p=D/'build/negative-coff'/'noncomdat-parent.obj';p.parent.mkdir(exist_ok=True);p.write_bytes(raw)
        with self.assertRaisesRegex(self.parser['Rejected'],'COMDAT'):
            self.parser['read_coff'](p,'_synth')

    def test_registered_profile_only(self):
        with self.assertRaisesRegex(m.Rejected,'Only registered'):self.link(profile='clang-i686-scaffold-narrow')

    def test_profile_drift_during_real_compile_rejected(self):
        profile=D/'build/test-output'/('profile-'+uuid.uuid4().hex+'.json');profile.parent.mkdir(exist_ok=True)
        profile.write_bytes(m.PROFILE_PATH.read_bytes());original_run=m.subprocess.run
        def run(cmd,*args,**kw):
            result=original_run(cmd,*args,**kw)
            if '-c' in cmd:profile.write_bytes(profile.read_bytes()+b'\n')
            return result
        with patch.object(m,'PROFILE_PATH',profile),patch.object(m.subprocess,'run',side_effect=run):
            with self.assertRaisesRegex(m.Rejected,'profile changed'):self.link()

    def test_source_drift_before_real_compile_rejected(self):
        p=self.source_fixture('source-drift',self.source.read_text());identity=m.compiler_identity
        def changed():
            result=identity();p.write_text(p.read_text()+'\n');return result
        with patch.object(m,'compiler_identity',side_effect=changed):
            with self.assertRaisesRegex(m.Rejected,'changed before compiler'):self.link(p)

    def test_client_object_and_manifest_not_api(self):
        parameters=inspect.signature(m.compile_and_link).parameters
        self.assertNotIn('object_path',parameters);self.assertNotIn('compile_manifest',parameters)
        with self.assertRaisesRegex(m.Rejected,'orchestrated'):
            m._link_compiled(self.obj,'_synthetic',0x412340,B,self.good_dir,{},object())

    def test_autonomous_source_contract(self):
        for i,text in enumerate(('#include <x>\nunsigned synthetic(void){return 1;}','unsigned synthetic(void){ __asm__("nop");return 1;}')):
            p=self.source_fixture('unsupported'+str(i),text)
            with self.assertRaisesRegex(m.Rejected,'autonomous'):m.validate_source(p)

    def test_stale_output_rejected(self):
        with self.assertRaisesRegex(m.Rejected,'stale'):self.link(output_dir=self.good_dir)

    def test_missing_binding_rejected(self):
        with self.assertRaisesRegex(m.Rejected,'Missing unresolved'):self.link(bindings=[B[0]])

    def test_binding_alias_rejected(self):
        duplicate=[B[0],dict(B[1],address=B[0]['address'])]
        with self.assertRaisesRegex(m.Rejected,'Address alias'):self.link(bindings=duplicate)

    def test_binding_abi_fields_not_silently_accepted(self):
        extra=[dict(B[0],abi='cdecl'),B[1]]
        with self.assertRaisesRegex(m.Rejected,'exact symbol/address'):self.link(bindings=extra)

    def test_fresh_compile_is_deterministic(self):
        data,manifest=self.link()
        self.assertEqual(data,self.good);self.assertNotEqual(manifest['compilation']['object'],str(self.obj))

    def assert_source_rejected_before_compiler(self,label,payload):
        p=self.fixtures/(label+'.c');p.write_bytes(payload)
        with patch.object(m,'compiler_identity',side_effect=AssertionError('compiler identity reached')) as identity:
            with self.assertRaises(m.Rejected):self.link(p,bindings=[])
            identity.assert_not_called()

    def test_exact_peer_directive_probe(self):
        payload=b'%\\\n:include <stddef.h>\nunsigned candidate(void) { return sizeof(size_t); }\n'
        self.assertEqual(m.hashlib.sha256(payload).hexdigest(),'910937fde3ee5ec3f3e78966857e5ba265969a2647c5945d087cc3c2aa2d1129')
        self.assert_source_rejected_before_compiler('exact-peer-probe',payload)

    def test_digraph_splice_line_endings(self):
        for i,newline in enumerate((b'\n',b'\r\n',b'\r')):
            with self.subTest(newline=newline):
                self.assert_source_rejected_before_compiler('digraph-eol'+str(i),
                    b'%\\'+newline+b':include <stddef.h>\nunsigned synthetic(void){return sizeof(size_t);}\n')

    def test_splice_whitespace_extensions(self):
        for i,space in enumerate((b' ',b'\t',b'\v',b'\f',b' \t\v\f')):
            for j,newline in enumerate((b'\n',b'\r\n',b'\r')):
                with self.subTest(space=space,newline=newline):
                    self.assert_source_rejected_before_compiler('space-splice'+str(i)+'-'+str(j),
                        b'%\\'+space+newline+b':include <stddef.h>\nunsigned synthetic(void){return 0;}\n')

    def test_phase1_trigraph_backslash_then_phase2(self):
        for i,newline in enumerate((b'\n',b'\r\n',b'\r')):
            for j,space in enumerate((b'',b' \t')):
                with self.subTest(newline=newline,space=space):
                    self.assert_source_rejected_before_compiler('trigraph-splice'+str(i)+'-'+str(j),
                        b'%??/'+space+newline+b':include <stddef.h>\nunsigned synthetic(void){return 0;}\n')

    def test_spliced_markers_and_nested_continuations(self):
        probes=(b'?\\\n?=',b'??\\\r\n=',b'?\\\n?\\\r=',b'%\\\n\\\r\n:',
                b'%\\\\\n\n:',b'??=',b'#',b'%:')
        for i,marker in enumerate(probes):
            with self.subTest(marker=marker):
                self.assert_source_rejected_before_compiler('combined-marker'+str(i),
                    marker+b'include <stddef.h>\nunsigned synthetic(void){return 0;}\n')

    def test_spliced_assembly_and_pragmas(self):
        for i,identifier in enumerate((b'__as\\\nm__',b'__as??/\r\nm',b'_Prag\\\rma',b'__prag??/ \nma')):
            with self.subTest(identifier=identifier):
                self.assert_source_rejected_before_compiler('spliced-forbidden'+str(i),
                    b'unsigned synthetic(void){'+identifier+b'("anything");return 0;}\n')

    def test_utf8_and_invalid_encoding_rejected_before_identity(self):
        for i,payload in enumerate(('/* café */ unsigned synthetic(void){return 0;}\n'.encode('utf8'),
                                    b'/* \xff */ unsigned synthetic(void){return 0;}\n',
                                    b'\xef\xbb\xbfunsigned synthetic(void){return 0;}\n')):
            with self.subTest(payload=payload):self.assert_source_rejected_before_compiler('nonascii'+str(i),payload)

    def test_safe_splice_compiles_captured_bytes_unchanged(self):
        p=self.fixtures/'safe-splice.c'
        payload=b'extern unsigned external_data; unsigned synthetic(unsigned x){return external_\\\ndata+x;}\n'
        p.write_bytes(payload)
        data,manifest=self.link(p,bindings=[B[1]])
        self.assertTrue(data)
        self.assertEqual(Path(manifest['compilation']['source_snapshot']).read_bytes(),payload)
        self.assertEqual(manifest['compilation']['source_sha256'],m.hashlib.sha256(payload).hexdigest())
        self.assertIn(b'\\\n',payload)

    def test_validate_source_uses_one_captured_payload(self):
        original=Path.read_bytes;reads=[]
        def read(path):
            result=original(path)
            if path.resolve()==self.source.resolve():reads.append(result)
            return result
        with patch.object(Path,'read_bytes',read):path,payload=m.validate_source(self.source)
        self.assertEqual(reads,[payload]);self.assertEqual(path,self.source.resolve())

    def test_initial_compiler_absence_only_is_unavailable69(self):
        with patch.object(m.shutil,'which',return_value=None):
            with self.assertRaises(m.ToolchainUnavailable) as caught:self.link()
        self.assertEqual(caught.exception.exit_code,69)

    def test_compiler_identity_disappears_after_available_is_hard_error(self):
        with patch.object(m,'compiler_identity',side_effect=m.ToolchainUnavailable('gone')):
            with self.assertRaises(m.Rejected) as caught:
                m.verify_compilation(self.manifest['compilation'],self.obj)
        self.assertEqual(caught.exception.exit_code,1)
        self.assertNotIsInstance(caught.exception,m.ToolchainUnavailable)

    def test_compiler_exit69_after_identity_available_is_hard_error(self):
        original=m.subprocess.run
        def run(cmd,*args,**kw):
            if '-c' in cmd:return m.subprocess.CompletedProcess(cmd,69,'','')
            return original(cmd,*args,**kw)
        with patch.object(m.subprocess,'run',side_effect=run):
            with self.assertRaises(m.Rejected) as caught:self.link()
        self.assertEqual(caught.exception.exit_code,1)
        self.assertNotIsInstance(caught.exception,m.ToolchainUnavailable)

    def test_profile_misconfiguration_is78_not_unavailability(self):
        profile=D/'build/test-output'/('bad-profile-'+uuid.uuid4().hex+'.json')
        config=json.loads(m.PROFILE_PATH.read_bytes());config[m.PROFILE_NAME]['flags']=['-O0']
        profile.write_text(json.dumps(config))
        with patch.object(m,'PROFILE_PATH',profile):
            with self.assertRaises(m.ToolchainMisconfigured) as caught:self.link()
        self.assertEqual(caught.exception.exit_code,78)

    def test_received_path_selects_real_clang_but_subprocess_env_is_controlled(self):
        selected=self.fixtures/'clang';selected.symlink_to(Path('/usr/bin/clang').resolve())
        with patch.dict(m.os.environ,{'PATH':str(self.fixtures),'LD_PRELOAD':'untrusted','CPATH':'untrusted'}):
            identity=m.compiler_identity()
        self.assertEqual(identity['selected_path'],str(selected))
        self.assertEqual(identity['discovery_path'],str(self.fixtures))
        self.assertEqual(m.controlled_env()['PATH'],'/usr/bin:/bin')
        self.assertNotIn('LD_PRELOAD',m.controlled_env());self.assertNotIn('CPATH',m.controlled_env())

    def test_independent_actual_call_and_data_addresses_change_separately(self):
        # Third-party objdump determines field offsets; no backend relocation
        # descriptions or relocation_value serve as the address oracle.
        proc=m.subprocess.run(['/usr/bin/objdump','-r',str(self.obj)],capture_output=True,text=True,
                              env=m.controlled_env(),check=True)
        offsets={symbol:int(offset,16) for offset,symbol in
                 m.re.findall(r'^([0-9a-fA-F]+)\s+(?:DISP32|dir32)\s+(_helper|_external_data)\s*$',proc.stdout,m.re.M)}
        self.assertEqual(set(offsets),{'_helper','_external_data'})
        def image_code(path):
            raw=path.read_bytes();peoff=struct.unpack_from('<I',raw,0x3c)[0]
            self.assertEqual(raw[peoff:peoff+4],b'PE\0\0')
            count=struct.unpack_from('<H',raw,peoff+6)[0];opt=struct.unpack_from('<H',raw,peoff+20)[0]
            imagebase=struct.unpack_from('<I',raw,peoff+24+28)[0]
            for index in range(count):
                start=peoff+24+opt+index*40
                if raw[start:start+8].rstrip(b'\0')==b'.match':
                    virtual,rva,size,pointer=struct.unpack_from('<IIII',raw,start+8)
                    self.assertEqual(virtual,size);self.assertEqual(imagebase+rva,0x412340)
                    self.assertEqual(size,len(self.good));return raw[pointer:pointer+size]
            self.fail('Missing complete .match section')
        for which in (0,1):
            bindings=[dict(x) for x in B];bindings[which]['address']+=0x1230
            data,manifest=self.link(bindings=bindings)
            image=Path(manifest['compilation']['object']).parent/'linked.exe';code=image_code(image)
            self.assertEqual(code,data)
            offset=offsets['_helper'];actual_call=0x412340+offset+4+struct.unpack_from('<i',code,offset)[0]
            actual_data=struct.unpack_from('<I',code,offsets['_external_data'])[0]
            self.assertEqual(actual_call,bindings[0]['address']);self.assertEqual(actual_data,bindings[1]['address'])
            self.assertEqual(manifest['backend'],'clang-i686-scaffold-real-link')

    def test_raw_isolated_coff_extractor_rejects_unresolved_call_and_data(self):
        path=D/'tools/matching/compare.py'
        namespace={'__name__':'portable_test_compare','__file__':str(path)}
        exec(compile(path.read_bytes(),str(path),'exec'),namespace)
        with self.assertRaisesRegex(ValueError,'link/relocate first'):
            namespace['coff_function'](self.obj,'_synthetic')

    def test_all_nonmapping_selected_profile_values_are_misconfigured78(self):
        original=json.loads(m.PROFILE_PATH.read_bytes())
        for value in (None,[],['bad'],'bad',42,False,1.5):
            with self.subTest(value=value):
                config=dict(original);config[m.PROFILE_NAME]=value
                path=D/'build/test-output'/('bad-selected-'+uuid.uuid4().hex+'.json')
                path.write_text(json.dumps(config))
                with patch.object(m,'PROFILE_PATH',path),patch.object(m,'compiler_identity') as identity:
                    with self.assertRaises(m.ToolchainMisconfigured) as caught:self.link()
                    identity.assert_not_called()
                self.assertEqual(caught.exception.exit_code,78)

    def test_nonmapping_profile_file_and_missing_profile_are_misconfigured78(self):
        for value in (None,[],['bad'],'bad',42,False,1.5,{}):
            with self.subTest(value=value):
                path=D/'build/test-output'/('bad-container-'+uuid.uuid4().hex+'.json')
                path.write_text(json.dumps(value))
                with patch.object(m,'PROFILE_PATH',path),patch.object(m,'compiler_identity') as identity:
                    with self.assertRaises(m.ToolchainMisconfigured) as caught:self.link()
                    identity.assert_not_called()
                self.assertEqual(caught.exception.exit_code,78)

if __name__=='__main__':unittest.main(verbosity=2)
