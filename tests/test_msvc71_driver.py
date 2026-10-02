"""Portable tests: synthetic runner/components only; no Microsoft/game binaries."""
import argparse
import contextlib
import importlib.machinery
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest import mock

ROOT = next(p for p in Path(__file__).resolve().parents if (p/'config/target.json').is_file())
sys.path.insert(0, str(ROOT/'tools'))
loader = importlib.machinery.SourceFileLoader('msvc71_pipeline_test', str(ROOT/'tools/decomp'))
spec = importlib.util.spec_from_loader(loader.name, loader)
DECOMP = importlib.util.module_from_spec(spec)
loader.exec_module(DECOMP)

# The stand-in produces a text marker, never an executable or authentic COFF.
FAKE_RUNNER = r'''
import json, os
from pathlib import Path
import sys
args = sys.argv[1:]
if any(os.environ.get(k) for k in ('CL', '_CL_', 'INCLUDE', 'LIB')):
    sys.exit(44)
if args[:2] == ['path', '-w']:
    print('Z:' + args[2].replace('/', '\\'))
    sys.exit(0)
flags = args[1:]
if not flags:
    print('Microsoft C/C++ Optimizing Compiler Version 13.10.3077 for 80x86')
    sys.exit(0)
source = flags[flags.index('/c')+1]
source = Path(source[2:].replace('\\', '/'))
if 'SYNTAX_ERROR' in source.read_text():
    print('synthetic compiler syntax error', file=sys.stderr)
    sys.exit(3)
output = next(a[3:] for a in flags if a.startswith('/Fo'))
output = Path(output[2:].replace('\\', '/'))
output.write_text(json.dumps({'flags': flags}))
if '/QQignored' in flags:
    print('warning D4002: ignoring unknown option', file=sys.stderr)
'''


class HistoricalDriverTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root/'config').mkdir()
        (self.root/'config/target.json').write_text('{}')
        self.driver = self.root/'tools/compilers/msvc71'
        self.driver.parent.mkdir(parents=True)
        shutil.copyfile(ROOT/'tools/compilers/msvc71', self.driver)
        self.bin = self.root/'fixture/bin'
        self.bin.mkdir(parents=True)
        for name in ('cl.exe', 'c1.dll', 'c1xx.dll', 'c2.dll', 'msobj71.dll',
                     'mspdb71.dll', 'msvcr71.dll', 'msvcp71.dll', 'dbghelp.dll'):
            (self.bin/name).write_text('synthetic component ' + name)
        self.runner = self.root/'fixture/runner'
        self.runner.write_text('#!' + sys.executable + '\n' + FAKE_RUNNER)
        self.runner.chmod(0o755)
        self.source = self.root/'source with spaces.c'
        self.source.write_text('unsigned synthetic(unsigned x) { return x + 1u; }\n')
        self.output = self.root/'output with spaces.obj'
        self.env = dict(os.environ, SC_MSVC71_BIN=str(self.bin), SC_WIBO=str(self.runner))
        self.flags = ['/nologo', '/O2', '/Oy', '/Gy', '/Zl', '/G6']

    def invoke(self, args, env=None):
        return subprocess.run([sys.executable, str(self.driver), *args],
                              env=self.env if env is None else env,
                              capture_output=True, text=True)

    def compile(self, extra=(), env=None):
        return self.invoke([*self.flags, *extra, '-c', str(self.source), '-o', str(self.output)], env)

    def test_identity_hashes_dependencies_and_runner_deterministically(self):
        p = self.invoke(['--identity-json'])
        self.assertEqual(p.returncode, 0, p.stderr)
        before = json.loads(p.stdout)
        self.assertEqual(len(before['component_sha256']), 11)
        self.assertEqual(before, json.loads(self.invoke(['--identityJSON']).stdout))
        (self.bin/'c1xx.dll').write_text('different synthetic component')
        after = json.loads(self.invoke(['--identity-json']).stdout)
        self.assertNotEqual(before['identity_sha256'], after['identity_sha256'])
        self.assertNotEqual(before['component_sha256']['c1xx.dll'], after['component_sha256']['c1xx.dll'])

    def test_windows_paths_and_explicit_include_definitions(self):
        p = self.compile(['-I', str(self.root/'include with spaces'), '-DFACTOR=7', '-UOLD'])
        self.assertEqual(p.returncode, 0, p.stderr)
        flags = json.loads(self.output.read_text())['flags']
        self.assertIn('/DFACTOR=7', flags)
        self.assertIn('/UOLD', flags)
        self.assertTrue(any(x.startswith('/IZ:') for x in flags))
        self.assertTrue(flags[flags.index('/c')+1].startswith('Z:'))

    def test_ambient_compiler_inputs_are_removed(self):
        env = dict(self.env, CL='/invalid', _CL_='/invalid', INCLUDE='/implicit', LIB='/implicit')
        p = self.compile(env=env)
        self.assertEqual(p.returncode, 0, p.stderr)

    def test_default_absence_is_optional_but_explicit_bad_path_is_configuration_error(self):
        env = dict(self.env)
        env.pop('SC_MSVC71_BIN')
        env.pop('SC_WIBO')
        p = self.invoke(['--identity-json'], env)
        self.assertEqual(p.returncode, 69)
        self.assertEqual(json.loads(p.stdout)['status'], 'unavailable')
        p = self.invoke(['--identity-json'], dict(self.env, SC_MSVC71_BIN=str(self.root/'missing')))
        self.assertEqual(p.returncode, 78)
        self.assertEqual(json.loads(p.stdout)['status'], 'misconfigured')

    def test_partial_default_installation_is_not_silently_optional(self):
        default_bin = self.root/'.local/toolchains/msvc71/bin'
        default_bin.mkdir(parents=True)
        (default_bin/'cl.exe').write_text('synthetic partial install')
        env = dict(self.env)
        env.pop('SC_MSVC71_BIN')
        env.pop('SC_WIBO')
        p = self.invoke(['--identity-json'], env)
        self.assertEqual(p.returncode, 78)
        self.assertEqual(json.loads(p.stdout)['status'], 'misconfigured')

    def test_ignored_flags_and_compiler_failure_preserve_previous_object(self):
        self.output.write_text('previous good object')
        p = self.compile(['/QQignored'])
        self.assertEqual(p.returncode, 78)
        self.assertEqual(self.output.read_text(), 'previous good object')
        self.source.write_text('SYNTAX_ERROR')
        p = self.compile()
        self.assertEqual(p.returncode, 3)
        self.assertEqual(self.output.read_text(), 'previous good object')

    def test_unsupported_flags_fail_before_compilation(self):
        for extra in (['/GS-'], ['-O2'], ['/Foelsewhere.obj']):
            p = self.compile(extra)
            self.assertEqual(p.returncode, 78, p.stderr)
            self.assertFalse(self.output.exists())


class HistoricalPipelineTests(unittest.TestCase):
    def test_identity_distinguishes_absence_and_bad_configuration(self):
        profile = {'executable': 'synthetic-driver', 'identity_arguments': ['--identity-json']}
        for status, code, exception in [('unavailable', 69, DECOMP.OptionalCompilerUnavailable),
                                        ('misconfigured', 78, OSError), ('unavailable', 0, OSError)]:
            result = SimpleNamespace(stdout=json.dumps({'status': status}), stderr='', returncode=code)
            with mock.patch.object(DECOMP.subprocess, 'run', return_value=result):
                with self.assertRaises(exception) as caught:
                    DECOMP.compiler_identity(profile)
            if status == 'misconfigured' or code == 0:
                self.assertNotIsInstance(caught.exception, DECOMP.OptionalCompilerUnavailable)

    def test_only_build_all_can_fall_back_and_marks_source_only(self):
        record = {'address': '0x00001000', 'candidate_source': 'synthetic.c', 'compiler_profile': 'historic'}
        profiles = {'historic': {'optional_portable_profile': 'portable'}, 'portable': {}}
        def read(path):
            return [record] if Path(path).name == 'functions.json' else profiles
        def build(r):
            if r['compiler_profile'] == 'historic':
                raise DECOMP.OptionalCompilerUnavailable('synthetic absent toolchain')
            return b'synthetic marker', {}
        with mock.patch.object(DECOMP, 'read', side_effect=read), mock.patch.object(DECOMP, 'build', side_effect=build) as built:
            with contextlib.redirect_stdout(io.StringIO()) as output:
                DECOMP.build_all()
            fallback = built.call_args_list[1].args[0]
            self.assertEqual(fallback['compiler_profile'], 'portable')
            self.assertEqual(fallback['source_only_fallback_for'], 'historic')
            self.assertEqual(fallback['match_expectation'], 'exploratory')
            self.assertIn('source-only fallback', output.getvalue())
            built.side_effect = OSError('synthetic bad configuration')
            with self.assertRaises(OSError):
                DECOMP.build_all()
            self.assertEqual(len(built.call_args_list), 3)

    def test_identity_components_and_fallback_manifest_invalidate_historical_freshness(self):
        import hashlib
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            source = root/'synthetic.c'
            source.write_text('unsigned synthetic(void) { return 1u; }\n')
            historical = {'executable': 'synthetic-wrapper', 'flags': ['/O2'],
                          'identity_arguments': ['--identity-json'],
                          'optional_portable_profile': 'portable'}
            portable = {'executable': 'synthetic-portable', 'flags': ['-O2']}
            profiles = {'historic': historical, 'portable': portable}
            record = {'address': '0x00001000', 'candidate_source': 'synthetic.c',
                      'compiler_profile': 'historic', 'binary_sha256': '0'*64}
            identity = {'status': 'available', 'component_sha256': {'c1.dll': '1'*64}}
            build = {'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
                     'headers_sha256': {}, 'compiler_profile_config': historical,
                     'compiler_sha256': 'a'*64, 'compiler_identity': identity,
                     'function_record_sha256': hashlib.sha256(json.dumps(record, sort_keys=True).encode()).hexdigest()}
            report = {'build': build, 'binary_sha256': record['binary_sha256']}
            with mock.patch.object(DECOMP, 'ROOT', root), \
                 mock.patch.object(DECOMP, 'read', return_value=profiles), \
                 mock.patch.object(DECOMP, 'compiler_digest', return_value='a'*64), \
                 mock.patch.object(DECOMP, 'compiler_identity', return_value=identity) as current_identity:
                self.assertTrue(DECOMP.report_is_fresh(record, report))
                # Wrapper/source/profile hashes remain identical; only c1 changes.
                current_identity.return_value = {'status': 'available',
                                                 'component_sha256': {'c1.dll': '2'*64}}
                self.assertFalse(DECOMP.report_is_fresh(record, report))
                current_identity.return_value = identity
                self.assertTrue(DECOMP.report_is_fresh(record, report))
                fallback_record = dict(record, compiler_profile='portable',
                                       source_only_fallback_for='historic', match_expectation='exploratory')
                fallback_build = dict(build, compiler_profile_config=portable,
                                      compiler_identity=None, source_only_fallback_for='historic',
                                      function_record_sha256=hashlib.sha256(
                                          json.dumps(fallback_record, sort_keys=True).encode()).hexdigest())
                self.assertFalse(DECOMP.report_is_fresh(record,
                                 {'build': fallback_build, 'binary_sha256': record['binary_sha256']}))
                current_identity.return_value = None
                self.assertTrue(DECOMP.report_is_fresh(fallback_record,
                                {'build': fallback_build, 'binary_sha256': record['binary_sha256']}))

    def test_proof_does_not_fall_back_on_optional_absence(self):
        record = {'address': '0x00001000', 'candidate_source': 'synthetic.c', 'compiler_profile': 'historic',
                  'match_expectation': 'exact', 'binary_sha256': '0'*64, 'boundary_verified': True, 'size': 1}
        with tempfile.TemporaryDirectory() as temp:
            proof = Path(temp)/'proof.json'
            proof.write_text('old success')
            with mock.patch.object(DECOMP, 'private', return_value=proof), \
                 mock.patch.object(DECOMP, 'read', return_value=[record]), \
                 mock.patch.object(DECOMP, 'function', return_value=record), \
                 mock.patch.object(DECOMP, 'binary', return_value=SimpleNamespace(metadata={'sha256': '0'*64})), \
                 mock.patch.object(DECOMP, 'build', side_effect=DECOMP.OptionalCompilerUnavailable('synthetic absence')) as built:
                with self.assertRaises(DECOMP.OptionalCompilerUnavailable):
                    DECOMP.verify_matches(argparse.Namespace(binary='unused synthetic path'))
                self.assertEqual(built.call_count, 1)
                self.assertFalse(proof.exists())


if __name__ == '__main__':
    unittest.main()
