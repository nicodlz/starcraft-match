"""Native-tool identity and environment tests, with a synthetic Wine stand-in."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class NativeLinkDriverTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.driver = self.root / 'tools/compilers/mslink71'
        self.driver.parent.mkdir(parents=True)
        shutil.copyfile(ROOT / 'tools/compilers/mslink71', self.driver)
        self.bin = self.root / 'bin'
        self.bin.mkdir()
        (self.bin / 'link.exe').write_bytes(b'independent synthetic linker')
        self.runtime = self.root / 'runtime'
        self.runtime.mkdir()
        (self.runtime / 'kernel32.dll').write_bytes(b'independent synthetic library')
        self.runner = self.root / 'runner'
        self.runner.write_text('#!' + sys.executable + '\n' + '''
import os, sys
if any(os.environ.get(k) for k in ('CL', '_CL_', 'INCLUDE', 'LIB', 'LINK', '_LINK_', 'WINEDLLOVERRIDES')):
    sys.exit(44)
if sys.argv[1:] == ['--version']:
    print('wine-9.0 (independent synthetic fixture)')
    sys.exit(0)
print('Microsoft (R) Incremental Linker Version 7.10.3077')
sys.exit(76)
''')
        self.runner.chmod(0o755)
        self.env = dict(os.environ, SC_MSVC71_BIN=str(self.bin), SC_WINE32=str(self.runner),
                        SC_WINE32_RUNTIME_ROOT=str(self.runtime),
                        SC_WINE32_PREFIX=str(self.root / '.local/prefix'))

    def invoke(self, env=None):
        return subprocess.run([sys.executable, str(self.driver), '--identity-json'],
                              env=self.env if env is None else env, capture_output=True, text=True)

    def test_runtime_replacement_changes_identity(self):
        before = self.invoke()
        self.assertEqual(before.returncode, 0, before.stderr)
        first = json.loads(before.stdout)
        self.assertEqual(first['status'], 'available')
        self.assertEqual(first, json.loads(self.invoke().stdout))
        (self.runtime / 'kernel32.dll').write_bytes(b'replaced synthetic library')
        self.assertNotEqual(first['identity_sha256'], json.loads(self.invoke().stdout)['identity_sha256'])

    def test_ambient_compiler_linker_and_wine_options_cleared(self):
        env = dict(self.env, **{k: 'injected' for k in ('CL', '_CL_', 'INCLUDE', 'LIB', 'LINK', '_LINK_', 'WINEDLLOVERRIDES')})
        proc = self.invoke(env)
        self.assertEqual(proc.returncode, 0, proc.stderr)

    def test_missing_explicit_runtime_is_optional_not_success(self):
        env = dict(self.env)
        env.pop('SC_WINE32_RUNTIME_ROOT')
        proc = self.invoke(env)
        self.assertEqual(proc.returncode, 69)
        self.assertEqual(json.loads(proc.stdout)['status'], 'unavailable')

    def test_runtime_must_exclude_prefix_and_external_symlinks(self):
        env = dict(self.env, SC_WINE32_PREFIX=str(self.runtime / '.local/prefix'))
        self.assertEqual(self.invoke(env).returncode, 78)
        (self.runtime / 'external').symlink_to(self.bin / 'link.exe')
        self.assertEqual(self.invoke().returncode, 78)


if __name__ == '__main__':
    unittest.main()
