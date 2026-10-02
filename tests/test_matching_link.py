#!/usr/bin/env python3
"""Fresh ordinary-C synthetic links and hostile synthetic COFF parser tests."""
import copy
import shutil
import importlib.util
import inspect
import json
import os
import struct
import subprocess
import unittest
import uuid
from pathlib import Path
from unittest.mock import patch

D = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('hardened_link', D / 'tools/matching/link.py')
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)
BINDINGS = [{'symbol': '_helper', 'address': 0x408000},
            {'symbol': '_counter', 'address': 0x500020}]


class FixtureTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.fixtures = D / 'src' / ('.matching-link-tests-' + uuid.uuid4().hex)
        cls.fixtures.mkdir(parents=True,exist_ok=False)
        cls.addClassCleanup(shutil.rmtree,cls.fixtures)
        cls.source=cls.fixtures/'good.c'
        cls.source.write_text('extern unsigned helper(unsigned); extern unsigned counter; '
                              'unsigned candidate(unsigned x){return helper(x)+counter;}\n')

    @staticmethod
    def output(name):
        return D / 'build/test-output' / (name + '-' + uuid.uuid4().hex)


    def link(self, source=None, **kwargs):
        values = dict(source=source or self.source, symbol='_candidate', address=0x412340,
                      bindings=BINDINGS, output_dir=self.output(self._testMethodName))
        values.update(kwargs)
        return m.compile_and_link(**values)



class IndependentTests(FixtureTests):
    def test_late_identity_unavailability_is_hard78_without_tools(self):
        with patch.object(m,'fresh_identity',side_effect=m.ToolchainUnavailable('gone')):
            with self.assertRaises(m.ToolchainMisconfigured) as caught:
                m.verify_available_identity({'status':'previously-available'})
        self.assertEqual(caught.exception.exit_code,78)
        self.assertNotIsInstance(caught.exception,m.ToolchainUnavailable)

    def test_malformed_selected_profile_types_are_configuration78(self):
        real_loads=json.loads
        for value in (None,[],17,'bad',False):
            with self.subTest(value=value):
                def loads(text,*args,**kwargs):
                    result=real_loads(text,*args,**kwargs)
                    if isinstance(result,dict) and 'msvc71-o2' in result:
                        result['msvc71-o2']=value
                    return result
                with patch.object(m.json,'loads',side_effect=loads):
                    with patch.object(m,'fresh_identity',side_effect=AssertionError('bad profile reached tools')):
                        with self.assertRaises(m.ToolchainMisconfigured) as caught:
                            self.link()
                self.assertEqual(caught.exception.exit_code,78)

    def test_malformed_profile_container_is_configuration78(self):
        for value in (None,[],17,'bad',False,{}):
            with self.subTest(value=value):
                with patch.object(m.json,'loads',return_value=value):
                    with self.assertRaises(m.ToolchainMisconfigured) as caught:
                        self.link()
                self.assertEqual(caught.exception.exit_code,78)
    def test_native_default_missing_only_is_fallback_eligible(self):
        response=subprocess.CompletedProcess([],69,json.dumps({'status':'unavailable'}),'')
        with patch.dict(m.os.environ,{},clear=True):
            with patch.object(m.subprocess,'run',return_value=response):
                with self.assertRaises(m.ToolchainUnavailable) as caught:
                    m.fresh_identity()
        self.assertEqual(caught.exception.exit_code,69)


    def test_bad_explicit_configuration_never_falls_back(self):
        with patch.dict(m.os.environ,{'SC_MSVC71_BIN':str(D/'missing-bin'),
                                     'SC_WIBO':str(D/'missing-runner')}):
            with self.assertRaises(m.ToolchainMisconfigured) as caught:
                m.fresh_identity()
        self.assertEqual(caught.exception.exit_code,78)


    def test_invalid_identity_and_false_unavailable_are_rejected(self):
        for code,identity in ((0,[]),(69,{'status':'misconfigured'}),
                              (69,{'status':'unavailable'}),(78,{'status':'misconfigured'})):
            with self.subTest(code=code,identity=identity):
                response=subprocess.CompletedProcess([],code,json.dumps(identity),'')
                with patch.dict(m.os.environ,{'SC_WIBO':str(D/'not-a-runner')}):
                    with patch.object(m.subprocess,'run',return_value=response):
                        with self.assertRaises(m.Rejected) as caught:
                            m.fresh_identity()
                self.assertNotIsInstance(caught.exception,m.ToolchainUnavailable)


    def test_compiler_environment_defaults_and_overrides(self):
        with patch.dict(m.os.environ,{},clear=True):
            self.assertNotIn('SC_WIBO',m.controlled_env(True))
            paths=m.component_paths()
            self.assertEqual(paths['wibo'],D/'.local/toolchains/wibo/wibo-i686')
        if 'SC_WIBO' in m.os.environ:
            self.assertEqual(m.component_paths()['wibo'],Path(m.os.environ['SC_WIBO']).resolve())


    def test_source_and_output_scope_reject_before_compilation(self):
        outside=self.output('scope-outside')/'not-src.c'
        outside.parent.mkdir(parents=True,exist_ok=False)
        self.addCleanup(shutil.rmtree,outside.parent)
        outside.write_text(self.source.read_text())
        with self.assertRaisesRegex(m.Rejected,'inside src'):
            self.link(outside)
        for output in (D/'other-output',D/'build'):
            with self.assertRaisesRegex(m.Rejected,'new build directory'):
                self.link(output_dir=output)


    def test_cli_bad_configuration_preserves_exit78(self):
        configuration=self.fixtures/'cli-bad-config.json'
        configuration.write_text(json.dumps({'source':str(self.source),'symbol':'_candidate',
            'address':0x412340,'bindings':BINDINGS,'output_dir':str(self.output('cli-bad'))}))
        env=dict(m.os.environ,SC_MSVC71_BIN=str(D/'no-bin'),SC_WIBO=str(D/'no-runner'),
                 PYTHONDONTWRITEBYTECODE='1')
        proc=subprocess.run([m.sys.executable,str(D/'tools/matching/link.py'),str(configuration)],
                            env=env,capture_output=True,text=True)
        self.assertEqual(proc.returncode,78)
        self.assertIn('configuration rejected',proc.stderr)


    def test_assembly_and_spliced_assembly_refused(self):
        source=self.fixtures/'assembly.c'
        for keyword in ('__asm','__a\\\nsm','_asm','asm','_Pragma','__pra\\\ngma'):
            with self.subTest(keyword=keyword):
                source.write_text('unsigned candidate(void){'+keyword+' { nop } return 0;}\n')
                with self.assertRaisesRegex(m.Rejected,'Assembly source unsupported'):
                    self.link(source,bindings=[])


    def test_spliced_digraph_directives_rejected_before_identity(self):
        source=self.fixtures/'spliced-directive.c'
        for prefix in ('%\\\n:include "hidden.h"\n',
                       '%\\\r\n:include "hidden.h"\n',
                       '%\\\r:include "hidden.h"\n',
                       '%\\ \t\n:include "hidden.h"\n',
                       '%??/\n:include "hidden.h"\n',
                       '%\\\\\n\n:include "hidden.h"\n'):
            with self.subTest(prefix=prefix):
                source.write_text(prefix+self.source.read_text())
                with patch.object(m,'fresh_identity',side_effect=AssertionError('unchecked source reached identity')):
                    with self.assertRaisesRegex(m.Rejected,'Headers/directives unsupported'):
                        self.link(source)


    def test_no_client_object_or_manifest_api(self):
        parameters = inspect.signature(m.compile_and_link).parameters
        self.assertNotIn('object_path', parameters)
        self.assertNotIn('compile_manifest', parameters)
        with self.assertRaisesRegex(m.Rejected, 'orchestrated'):
            m._link_compiled(self.fixtures/'not-an-object.obj', '_candidate', 0x412340, BINDINGS,
                             self.output('token-only'), {}, object())


    def test_unknown_profile_rejected(self):
        with self.assertRaisesRegex(m.Rejected, 'registered'):
            self.link(profile='unregistered')


    def test_changed_registered_command_flags_rejected(self):
        real_loads = json.loads
        def loads(text, *args, **kwargs):
            result = real_loads(text, *args, **kwargs)
            if isinstance(result, dict) and 'msvc71-o2' in result:
                result['msvc71-o2']['flags'] = ['/Od']
            return result
        with patch.object(m.json, 'loads', side_effect=loads):
            with self.assertRaisesRegex(m.Rejected, 'Registered profile'):
                self.link()


    def test_headers_refused_in_autonomous_subset(self):
        source = self.fixtures / 'header.c'
        for prefix in ('#define HEADER "hidden.h"\n#include HEADER\n',
                       '#inc\\\nlude "hidden.h"\n',
                       '#/**/include "hidden.h"\n',
                       '%:include "hidden.h"\n',
                       '??=include "hidden.h"\n'):
            with self.subTest(prefix=prefix):
                source.write_text(prefix + 'unsigned candidate(void){return 0;}\n')
                with self.assertRaisesRegex(m.Rejected, 'Headers/directives unsupported'):
                    self.link(source)


    def test_non_utf8_source_rejected_cleanly(self):
        source = self.fixtures / 'invalid-encoding.c'
        source.write_bytes(b'unsigned candidate(void){return 0;}\xff')
        with self.assertRaisesRegex(m.Rejected, 'valid UTF-8'):
            self.link(source)


    def test_loaded_implementation_reader_python_drift_rejected(self):
        real_digest = m.digest
        for name, path in m._LOADED_PATHS.items():
            with self.subTest(component=name):
                def changed(value):
                    return '0'*64 if Path(value).resolve()==path.resolve() else real_digest(value)
                with patch.object(m, 'digest', side_effect=changed):
                    with self.assertRaisesRegex(m.Rejected, 'Loaded implementation/reader/interpreter'):
                        self.link()


    def test_controlled_environment_drops_link_and_compiler_injection(self):
        with patch.dict(os.environ, {'LD_PRELOAD': '/bad.so', 'LD_AUDIT': '/audit.so',
                                    'LD_LIBRARY_PATH': '/bad', 'CL': '/Od', '_CL_': '/FIbad.h'}):
            for compiler in (False, True):
                env = m.controlled_env(compiler)
                self.assertFalse(any(k.startswith('LD_') for k in env))
                self.assertNotIn('CL', env)
                self.assertNotIn('_CL_', env)


    def test_ldd_fail_closed(self):
        outputs = [(127, '', 'unavailable'), (0, '', ''), (0, 'not parsed\n', ''),
                   (0, 'libbad => not found\n', ''),
                   (0, '/no/such/library.so (0x123)\n', ''),
                   (0, 'linux-vdso.so.1 (0x123)\n', '')]
        for rc, stdout, stderr in outputs:
            with self.subTest(output=(rc, stdout, stderr)):
                with patch.object(m.subprocess, 'run', return_value=subprocess.CompletedProcess([], rc, stdout, stderr)):
                    with self.assertRaises(m.Rejected):
                        m.linker_identity('/usr/bin/ld')


    def test_linker_wrapper_rejected(self):
        wrapper = self.fixtures / 'linker-wrapper'
        wrapper.write_text('#!/bin/sh\nexec /usr/bin/ld "$@"\n')
        with self.assertRaisesRegex(m.Rejected, 'no wrappers'):
            m.linker_identity(wrapper)


    def test_wrong_linker_version_rejected(self):
        real_run = subprocess.run
        for version in ('GNU ld 9.99\n','GNU ld 2.420\n',
                        'GNU ld (GNU Binutils for Ubuntu) 2.420\n',''):
            with self.subTest(version=version):
                def run(command, *args, **kwargs):
                    if '--version' in command:
                        return subprocess.CompletedProcess(command, 0, version, '')
                    return real_run(command, *args, **kwargs)
                with patch.object(m.subprocess, 'run', side_effect=run):
                    with self.assertRaisesRegex(m.Rejected, 'Supported GNU ld'):
                        m.linker_identity('/usr/bin/ld')


    def test_rva32_arithmetic_bounds(self):
        self.assertEqual(m.relocation_value(7, 0x400000, 0, 0, 0x400000), 0)
        self.assertEqual(m.relocation_value(7, 0xffffffff, 0x400000, 0, 0x400000), 0xffffffff)
        for value, addend in ((0x3fffff, 0), (0xffffffff, 0x400001)):
            with self.assertRaisesRegex(m.Rejected, 'RVA32'):
                m.relocation_value(7, value, addend, 0, 0x400000)


    def test_other_relocation_overflows(self):
        with self.assertRaisesRegex(m.Rejected, 'DIR32'):
            m.relocation_value(6, 0xfffffff8, 16, 0, 0x400000)
        with self.assertRaisesRegex(m.Rejected, 'REL32'):
            m.relocation_value(20, 0xfffffff0, 0, 0x412340, 0x400000)



class HardenedTests(FixtureTests):
    def late_default_disappearance(self,query):
        mirror=self.output('disappearance-mirror')/'root'
        mirror.mkdir(parents=True,exist_ok=False)
        self.addCleanup(shutil.rmtree,mirror.parent)
        for part in ('tools/matching','tools/analysis','tools/compilers','config','src',
                     '.local/toolchains/msvc71','.local/toolchains/wibo'):
            (mirror/part).mkdir(parents=True,exist_ok=True)
        for name in ('tools/matching/link.py','tools/analysis/pe.py','tools/compilers/msvc71',
                     'config/target.json','config/compilers.json'):
            shutil.copy2(D/name,mirror/name)
        (mirror/'tools/compilers/msvc71').chmod(0o755)
        paths=m.component_paths()
        (mirror/'.local/toolchains/msvc71/bin').symlink_to(paths['cl.exe'].parent.resolve(),target_is_directory=True)
        runner=mirror/'.local/toolchains/wibo/wibo-i686'
        runner.symlink_to(paths['wibo'].resolve())
        source=mirror/'src/good.c';source.write_text(self.source.read_text())
        spec=importlib.util.spec_from_file_location('disappearance_'+uuid.uuid4().hex,mirror/'tools/matching/link.py')
        backend=importlib.util.module_from_spec(spec);spec.loader.exec_module(backend)
        real_identity=backend.fresh_identity
        calls=0
        def identity():
            nonlocal calls
            calls+=1
            if calls==query:
                runner.unlink()  # Only this test's owned default symlink.
            return real_identity()
        output=mirror/'build/attempt'
        with patch.dict(backend.os.environ,{},clear=True):
            with patch.object(backend,'fresh_identity',side_effect=identity):
                with self.assertRaises(backend.ToolchainMisconfigured) as caught:
                    backend.compile_and_link(source,'_candidate',0x412340,BINDINGS,output)
        self.assertEqual(caught.exception.exit_code,78)
        self.assertNotIsInstance(caught.exception,backend.ToolchainUnavailable)
        self.assertEqual(calls,query)
        self.assertTrue((output/'candidate.obj').is_file())
        self.assertEqual((output/'linked.exe').is_file(),query==3)
        self.assertFalse((output/'manifest.json').exists())

    def test_real_default_disappearance_after_compilation_is_hard78(self):
        self.late_default_disappearance(2)

    def test_real_default_disappearance_after_link_is_hard78(self):
        self.late_default_disappearance(3)
    @classmethod
    def setUpClass(cls):
        super().setUpClass()
        try:
            m.fresh_identity()
        except m.ToolchainUnavailable as error:
            raise unittest.SkipTest(str(error))
        cls.good_dir = cls.output('baseline')
        cls.good, cls.manifest = m.compile_and_link(cls.source, '_candidate', 0x412340,
                                                   BINDINGS, cls.good_dir)
        cls.obj = cls.good_dir / 'candidate.obj'
        cls.raw = cls.obj.read_bytes()
        cls.selected, cls.parts, _, cls.symbols = m.read_coff(cls.obj, '_candidate')






    def test_toolchain_loss_after_available_identity_is_not_fallback(self):
        real_run=m.subprocess.run
        for status in (69,78):
            with self.subTest(status=status):
                def run(command,*args,**kwargs):
                    if '-c' in command:
                        return subprocess.CompletedProcess(command,status,'','configuration lost')
                    return real_run(command,*args,**kwargs)
                with patch.object(m.subprocess,'run',side_effect=run):
                    with self.assertRaises(m.Rejected) as caught:
                        self.link()
                self.assertNotIsInstance(caught.exception,m.ToolchainUnavailable)
                if status==78:
                    self.assertIsInstance(caught.exception,m.ToolchainMisconfigured)


    def test_uppercase_c_extension_is_supported(self):
        source=self.fixtures/'uppercase.C';source.write_text(self.source.read_text())
        result,_=self.link(source)
        self.assertEqual(result,self.good)

    def test_safe_spliced_source_is_compiled_without_rewriting(self):
        source=self.fixtures/'safe-splice.c'
        source.write_text(self.source.read_text().replace('candidate','candi\\\ndate'))
        before=source.read_bytes()
        result,manifest=self.link(source)
        self.assertEqual(result,self.good)
        self.assertEqual(source.read_bytes(),before)
        self.assertEqual(manifest['compilation']['source_sha256'],m.digest(source))





    def hostile(self, label, mutate):
        # Only a negative parser fixture: never submitted to the linker/API.
        raw = bytearray(self.raw)
        mutate(raw)
        out = D / 'build/negative-coff'
        out.mkdir(exist_ok=True)
        path = out / (label + '.obj')
        path.write_bytes(raw)
        with self.assertRaises(m.Rejected):
            m.read_coff(path, '_candidate')

    def section(self, name):
        return next(x for x in self.parts if x['name'] == name)

    def test_real_link_retains_all_metadata_and_audits_words(self):
        self.assertEqual(len(self.good), self.selected['size'])
        self.assertEqual({s['input_section'] for s in self.manifest['sections']},
                         {'.text', '.debug$S', '.debug$F'})
        debug = next(s for s in self.manifest['sections'] if s['input_section'] == '.debug$F')
        self.assertEqual(debug['relocations'][0]['type'], 'RVA32')
        self.assertEqual(debug['relocations'][0]['resolved_word'], 0x12340)
        pe = m.PE(self.good_dir / 'linked.exe')
        for description in self.manifest['sections']:
            input_part = self.section(description['input_section'])
            actual = next(s for s in pe.sections if s['name'] == description['output_section'])
            linked = pe.take(actual['raw_offset'], actual['raw_size'])
            changed = set()
            for relocation in description['relocations']:
                offset = relocation['offset']
                self.assertEqual(struct.unpack_from('<I', linked, offset)[0], relocation['resolved_word'])
                changed.update(range(offset, offset + 4))
            self.assertEqual(len(linked), len(input_part['body']))
            self.assertTrue(all(a == b for i, (a, b) in enumerate(zip(input_part['body'], linked))
                                if i not in changed))
        self.assertEqual(m.digest(self.obj), self.manifest['object_sha256'])

    def test_deterministic_fresh_compilation_link(self):
        second, manifest = self.link()
        self.assertEqual(second, self.good)
        # MSVC embeds its object output path in opaque .debug$S. Different
        # fresh directories legitimately differ; preserve that evidence.
        self.assertEqual(manifest['sections'][0], self.manifest['sections'][0])
        self.assertNotEqual(manifest['compilation']['object'],
                            self.manifest['compilation']['object'])
        self.assertNotEqual(manifest['sections'][1]['input_sha256'],
                            self.manifest['sections'][1]['input_sha256'])

    def test_fastcall_decorated_source_and_bindings(self):
        source = self.fixtures / 'fastcall.c'
        source.write_text('extern unsigned __fastcall helper(unsigned); '
                          'unsigned __fastcall candidate(unsigned x){return helper(x)+3;}\n')
        data, manifest = self.link(source, symbol='@candidate@4',
                                   bindings=[{'symbol': '@helper@4', 'address': 0x408000}])
        self.assertTrue(data)
        self.assertEqual(manifest['function_symbol'], '@candidate@4')

    def test_registered_frame_profile_fresh_compilation(self):
        data, manifest = self.link(profile='msvc71-o2-frame')
        self.assertTrue(data)
        self.assertEqual(manifest['compilation']['compiler_profile'], 'msvc71-o2-frame')
        self.assertEqual(manifest['compilation']['command'][-4:-2], ['-c', str(self.source)])
        self.assertIn('/Oy-', manifest['compilation']['command'])

    def test_local_recursive_call_whole_section(self):
        source=self.fixtures/'recursive.c'
        source.write_text('unsigned candidate(unsigned x){if(x<2)return x;'
                          'return candidate(x-1)+candidate(x-2);}\n')
        data,manifest=self.link(source,bindings=[])
        self.assertEqual(len(data),manifest['complete_size'])
        local=[r for r in manifest['sections'][0]['relocations']
               if r['type']=='REL32' and r['symbol']=='_candidate']
        self.assertTrue(local)
        for relocation in local:
            self.assertEqual(relocation['resolved_word'],
                             (-relocation['offset']-4+relocation['addend']) & 0xffffffff)


    def test_empty_identity_inventory_rejected(self):
        with self.assertRaises(m.Rejected):
            m.verify_identity({'status': 'available'})
        identity = copy.deepcopy(self.manifest['compilation']['compiler_identity'])
        identity['component_sha256'] = {}
        with self.assertRaisesRegex(m.Rejected, 'nonempty'):
            m.verify_identity(identity)

    def test_missing_component_and_component_drift_rejected(self):
        original = self.manifest['compilation']['compiler_identity']
        for changed in ('missing', 'hash'):
            identity = copy.deepcopy(original)
            if changed == 'missing':
                identity['component_sha256'].pop('driver')
            else:
                identity['component_sha256']['c2.dll'] = '0' * 64
            with self.assertRaises(m.Rejected):
                m.verify_identity(identity)

    def test_identity_digest_drift_rejected(self):
        identity = copy.deepcopy(self.manifest['compilation']['compiler_identity'])
        identity['identity_sha256'] = '0' * 64
        with self.assertRaisesRegex(m.Rejected, 'identity hash'):
            m.verify_identity(identity)



    def test_stale_output_and_object_rejected(self):
        with self.assertRaisesRegex(m.Rejected, 'stale objects'):
            self.link(output_dir=self.good_dir)

    def test_wrong_symbol_rejected_after_fresh_compilation(self):
        with self.assertRaisesRegex(m.Rejected, 'complete function'):
            self.link(symbol='_not_the_compiled_function')

    def test_actual_source_recompiled_not_old_object(self):
        source = self.fixtures / 'different.c'
        source.write_text('unsigned candidate(unsigned x){return x+17;}\n')
        result, manifest = self.link(source, bindings=[])
        self.assertNotEqual(result, self.good)
        self.assertEqual(manifest['compilation']['source_sha256'], m.digest(source))
        self.assertEqual(manifest['compilation']['object_sha256'], m.digest(manifest['compilation']['object']))


    def test_source_change_during_compilation_rejected(self):
        source = self.fixtures / 'changing.c'
        source.write_text(self.source.read_text())
        real_run = subprocess.run
        def run(cmd, *args, **kwargs):
            result = real_run(cmd, *args, **kwargs)
            if '-c' in cmd:
                source.write_text(source.read_text() + '\n')
            return result
        with patch.object(m.subprocess, 'run', side_effect=run):
            with self.assertRaisesRegex(m.Rejected, 'changed during compilation'):
                self.link(source)

    def test_source_include_added_during_identity_rejected_before_compile(self):
        source = self.fixtures / 'identity-changing.c'
        source.write_text(self.source.read_text())
        real_identity = m.fresh_identity
        real_run = m.subprocess.run
        compiler_commands = []
        def identity():
            result = real_identity()
            source.write_text('#include "uninventoried.h"\n' + self.source.read_text())
            return result
        def run(command, *args, **kwargs):
            if '-c' in command:
                compiler_commands.append(command)
            return real_run(command, *args, **kwargs)
        with patch.object(m, 'fresh_identity', side_effect=identity):
            with patch.object(m.subprocess, 'run', side_effect=run):
                with self.assertRaisesRegex(m.Rejected, 'between validation and compilation'):
                    self.link(source)
        self.assertEqual(compiler_commands, [])


    def test_section_auxiliary_extents_types_and_comdat_rejected(self):
        symptr=struct.unpack_from('<I',self.raw,8)[0]
        code_index=next(i for i,s in self.symbols.items() if s['name']==self.selected['name'])
        metadata_index=next(i for i,s in self.symbols.items() if s['name']=='.debug$F')
        code=symptr+(code_index+1)*18
        metadata=symptr+(metadata_index+1)*18
        mutations=[('aux-length',code,'<I',0xffffffff),
                   ('aux-relocs',code+4,'<H',0xffff),
                   ('aux-lines',code+6,'<H',1),
                   ('aux-selection',code+14,'<B',0xff),
                   ('aux-code-association',code+12,'<H',1),
                   ('aux-metadata-association',metadata+12,'<H',0xffff),
                   ('aux-reserved',code+15,'<B',1),
                   ('aux-high',code+16,'<H',1),
                   ('section-symbol-type',symptr+code_index*18+14,'<H',1)]
        for label,offset,fmt,value in mutations:
            with self.subTest(label=label):
                self.hostile(label,lambda raw:struct.pack_into(fmt,raw,offset,value))

    def test_duplicate_section_primary_rejected(self):
        def duplicate(raw):
            symptr,nsyms=struct.unpack_from('<II',raw,8)
            index=next(i for i,s in self.symbols.items() if s['name']==self.selected['name'])
            start=symptr+index*18
            raw[symptr+nsyms*18:symptr+nsyms*18]=raw[start:start+36]
            struct.pack_into('<I',raw,12,nsyms+2)
        self.hostile('duplicate-section-primary',duplicate)

    def test_associative_metadata_noncomdat_parent_rejected(self):
        def noncomdat_parent(raw):
            header=20+(self.selected['number']-1)*40
            flags=struct.unpack_from('<I',raw,header+36)[0]
            struct.pack_into('<I',raw,header+36,flags & ~0x1000)
            symptr=struct.unpack_from('<I',raw,8)[0]
            index=next(i for i,s in self.symbols.items() if s['name']==self.selected['name'])
            # Parent is otherwise internally consistent ordinary code; only
            # the retained debugF ASSOCIATIVE-to-ordinary relationship is bad.
            struct.pack_into('<B',raw,symptr+(index+1)*18+14,0)
        self.hostile('associative-to-ordinary-parent',noncomdat_parent)


    def test_driver_python_drift_during_identity_rejected_before_compile(self):
        original = m.implementation_identity
        real_run = m.subprocess.run
        count = 0
        commands = []
        def changing():
            nonlocal count
            result=original()
            count+=1
            if count>1:
                result['driver_python']['sha256']='0'*64
            return result
        def run(command,*args,**kwargs):
            if '-c' in command:
                commands.append(command)
            return real_run(command,*args,**kwargs)
        with patch.object(m,'implementation_identity',side_effect=changing):
            with patch.object(m.subprocess,'run',side_effect=run):
                with self.assertRaisesRegex(m.Rejected,'identity changed during execution'):
                    self.link()
        self.assertEqual(commands,[])





    def test_linker_identity_drift_rejected(self):
        real_identity = m.linker_identity
        count = 0
        def identity(path):
            nonlocal count
            result = real_identity(path)
            count += 1
            if count == 2:
                result['version'] += 'changed'
            return result
        with patch.object(m, 'linker_identity', side_effect=identity):
            with self.assertRaisesRegex(m.Rejected, 'Linker or libraries changed'):
                self.link()

    def test_metadata_output_writable_rejected(self):
        real_pe = m.PE
        def writable(path):
            pe = real_pe(path)
            next(s for s in pe.sections if s['name'] == '.dbgS')['characteristics'] |= 0x80000000
            return pe
        with patch.object(m, 'PE', side_effect=writable):
            with self.assertRaisesRegex(m.Rejected, 'permissions'):
                self.link()



    def test_missing_binding_and_address_alias_rejected(self):
        for bindings in ([BINDINGS[0]], [BINDINGS[0], dict(BINDINGS[1], address=0x408000)],
                         [dict(BINDINGS[0], address=0x412360), BINDINGS[1]]):
            with self.subTest(bindings=bindings):
                with self.assertRaises(m.Rejected):
                    self.link(bindings=bindings)

    def test_code_alias_primary_rejected(self):
        def alias(raw):
            symptr, count = struct.unpack_from('<II', raw, 8)
            at = symptr + count * 18
            raw[at:at] = struct.pack('<8sIhHBB', b'_alias\0\0', 0,
                                     self.selected['number'], 0, 2, 0)
            struct.pack_into('<I', raw, 12, count + 1)
        self.hostile('code-alias', alias)

    def test_static_code_alias_primary_rejected(self):
        def alias(raw):
            symptr, count = struct.unpack_from('<II', raw, 8)
            raw[symptr + count * 18:symptr + count * 18] = struct.pack(
                '<8sIhHBB', b'_alias\0\0', 0, self.selected['number'], 0, 3, 0)
            struct.pack_into('<I', raw, 12, count + 1)
        self.hostile('static-alias', alias)

    def test_raw_section_overlap_rejected(self):
        debug = self.section('.debug$S')
        at = 20 + (debug['number'] - 1) * 40
        self.hostile('raw-overlap', lambda raw: struct.pack_into('<II', raw, at + 16,
                     self.selected['size'], self.selected['pointer']))

    def test_raw_headers_symbols_strings_overlap_rejected(self):
        debug = self.section('.debug$F')
        at = 20 + (debug['number'] - 1) * 40
        symptr, count = struct.unpack_from('<II', self.raw, 8)
        for label, offset in [('headers', 0), ('symbols', symptr), ('strings', symptr + count * 18)]:
            self.hostile('overlap-' + label, lambda raw, offset=offset: struct.pack_into('<I', raw, at + 20, offset))

    def test_raw_relocation_data_overlap_rejected(self):
        at = 20 + (self.selected['number'] - 1) * 40
        self.hostile('relocation-data-overlap', lambda raw: struct.pack_into('<I', raw, at + 24, self.selected['pointer']))

    def test_nonascii_short_section_and_symbol_names_rejected_cleanly(self):
        symptr = struct.unpack_from('<I', self.raw, 8)[0]
        for label, offset in [('section', 20), ('symbol', symptr)]:
            self.hostile('nonascii-' + label, lambda raw, offset=offset: raw.__setitem__(offset, 255))

    def test_invalid_long_name_rejected_cleanly(self):
        symptr = struct.unpack_from('<I', self.raw, 8)[0]
        self.hostile('bad-long-name', lambda raw: struct.pack_into('<II', raw, symptr, 0, 0xffffffff))

    def test_metadata_input_permissions_rejected(self):
        at = 20 + (self.section('.debug$F')['number'] - 1) * 40 + 36
        old = struct.unpack_from('<I', self.raw, at)[0]
        for flag in (0x20000000, 0x80000000):
            self.hostile('bad-metadata-flags-' + str(flag), lambda raw, flag=flag: struct.pack_into('<I', raw, at, old | flag))

    def test_metadata_duplicate_and_empty_relocation_section_rejected(self):
        at = 20 + (self.section('.debug$F')['number'] - 1) * 40
        self.hostile('duplicate-metadata', lambda raw: raw.__setitem__(slice(at, at + 8), b'.debug$S'))
        self.hostile('empty-metadata-relocs', lambda raw: struct.pack_into('<I', raw, at + 16, 0))

    def test_unsupported_relocation_truncated_field_auxiliary_and_overlap(self):
        relptr = self.selected['relptr']
        self.hostile('bad-code-type', lambda raw: struct.pack_into('<H', raw, relptr + 8, 7))
        self.hostile('bad-field-bound', lambda raw: struct.pack_into('<I', raw, relptr, self.selected['size'] - 3))
        aux = next(i + 1 for i, symbol in self.symbols.items() if symbol['auxiliaries'])
        self.hostile('auxiliary-target', lambda raw: struct.pack_into('<I', raw, relptr + 4, aux))
        offset = struct.unpack_from('<I', self.raw, relptr)[0]
        self.hostile('field-overlap', lambda raw: struct.pack_into('<I', raw, relptr + 10, offset))

    def test_extra_data_directives_and_multiple_functions_rejected(self):
        sources = ['unsigned counter=17; unsigned candidate(void){return counter;}',
                   '#pragma comment(linker,"/alternatename:_other=_fallback")\nunsigned candidate(void){return 17;}',
                   'unsigned other(unsigned x){return x+1;} unsigned candidate(unsigned x){return other(x)+2;}']
        for i, text in enumerate(sources):
            source = self.fixtures / ('extra-' + str(i) + '.c')
            source.write_text(text + '\n')
            with self.subTest(source=source):
                with self.assertRaises(m.Rejected):
                    self.link(source, bindings=[])


if __name__ == '__main__':
    unittest.main(verbosity=2)
