import ctypes
import hashlib
import importlib.machinery
import importlib.util
import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT/'tools'))
from analysis.pe import PE
from matching.compare import coff_function, compare


def fixture(path):
    """Original synthetic PE fixture, not Blizzard bytes."""
    data = bytearray(0x600)
    data[:2] = b'MZ'; struct.pack_into('<I', data, 0x3c, 0x80)
    data[0x80:0x84] = b'PE\0\0'
    struct.pack_into('<HHIIIHH', data, 0x84, 0x14c, 1, 0, 0, 0, 224, 0x102)
    o = 0x98
    struct.pack_into('<H', data, o, 0x10b)
    struct.pack_into('<I', data, o+16, 0x1000)
    struct.pack_into('<I', data, o+28, 0x400000)
    struct.pack_into('<I', data, o+60, 0x200)
    struct.pack_into('<I', data, o+92, 16)
    struct.pack_into('<8sIIIIIIHHI', data, o+224, b'.text', 0x500, 0x1000, 0x400, 0x200, 0, 0, 0, 0, 0x60000020)
    data[0x200:0x203] = b'\x31\xc0\xc3'
    data[0x210:0x216] = b'HELLO\0'
    data[0x220:0x22c] = 'WORLD\0'.encode('utf-16le')
    # Import descriptor and terminated thunk list.
    struct.pack_into('<II', data, o+104, 0x1100, 40)
    struct.pack_into('<IIIII', data, 0x300, 0x1140, 0, 0, 0x1130, 0x1140)
    data[0x330:0x337] = b'X.dll\0\0'
    struct.pack_into('<III', data, 0x340, 0x1160, 0x80000003, 0)
    data[0x360:0x367] = b'\0\0Test\0'
    path.write_bytes(data)


class PipelineTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.p = Path(self.tmp.name)/'fixture.exe'
        fixture(self.p)

    def test_pe_mapping_metadata_imports_strings(self):
        pe = PE(self.p)
        self.assertEqual(pe.region(0x401000, 3), b'\x31\xc0\xc3')
        self.assertEqual(pe.metadata['sha256'], hashlib.sha256(self.p.read_bytes()).hexdigest())
        self.assertEqual(pe.imports()[0]['name'], 'Test')
        self.assertEqual(pe.imports()[1]['ordinal'], 3)
        self.assertEqual(pe.exports(), [])
        self.assertTrue({'HELLO', 'WORLD'} <= {s['text'] for s in pe.strings()})
        with self.assertRaises(ValueError): pe.region(0x4013ff, 2)
        with self.assertRaises(ValueError): pe.region(0x401000, 0)
        # The virtual tail is not file-backed.
        with self.assertRaises(ValueError): pe.offset(0x1400)

    def test_bad_and_truncated_input(self):
        self.p.write_bytes(b'MZ')
        with self.assertRaises(ValueError): PE(self.p)
        fixture(self.p)
        data = bytearray(self.p.read_bytes()); data[0x98:0x9a] = b'\x0b\x02'
        self.p.write_bytes(data)
        with self.assertRaises(ValueError): PE(self.p)

    @unittest.skipUnless(shutil.which('objdump'), 'objdump missing')
    def test_literal_match_diff_and_no_fake_scores(self):
        exact = compare(b'\x31\xc0\xc3', b'\x31\xc0\xc3', 0x401000)
        self.assertTrue(exact['exact_byte_match'])
        diff = compare(b'\x31\xc0\xc3', b'\xb8\x01\0\0\0\xc3', 0x401000)
        self.assertFalse(diff['exact_byte_match'])
        self.assertTrue(diff['differences'])
        self.assertIsNone(diff['instruction_similarity'])
        self.assertIsNone(diff['cfg_similarity'])

    @unittest.skipUnless(shutil.which('clang'), 'clang missing')
    def test_coff_compile_reproducible_and_relocations_rejected(self):
        obj = Path(self.tmp.name)/'candidate.obj'
        profile = json.loads((ROOT/'config/compilers.json').read_text())['clang-i686-scaffold']
        cmd = ['clang', *profile['flags'], '-c', 'src/units/sub_004020B0.c', '-o', str(obj)]
        subprocess.run(cmd, cwd=ROOT, check=True)
        data = coff_function(obj, '_sub_004020B0')
        subprocess.run(cmd, cwd=ROOT, check=True)
        self.assertEqual(data, coff_function(obj, '_sub_004020B0'))
        with self.assertRaises(ValueError): coff_function(obj, '_missing')
        src = Path(self.tmp.name)/'reloc.c'
        src.write_text('extern int other(void); int reloc(void) { return other(); }')
        subprocess.run(['clang', *profile['flags'], '-c', str(src), '-o', str(obj)], cwd=ROOT, check=True)
        with self.assertRaises(ValueError): coff_function(obj, '_reloc')

    @unittest.skipUnless(shutil.which('gcc'), 'gcc missing')
    def test_candidate_truth_table_on_native_host(self):
        # Scaffold semantics only; this does not call the original or validate its ABI.
        lib = Path(self.tmp.name)/'candidate.so'
        subprocess.run(['gcc', '-shared', '-fPIC', '-std=c11', '-Iinclude',
                        'src/units/sub_004020B0.c', '-o', str(lib)], cwd=ROOT, check=True)
        fn = ctypes.CDLL(str(lib)).sub_004020B0
        fn.argtypes = [ctypes.c_void_p]; fn.restype = ctypes.c_int
        for mask in range(16):
            data = bytearray(0x128)
            struct.pack_into('<I', data, 0xdc, 0x400 if mask & 1 else 0x80000000)
            for bit, offset in [(2, 0x117), (4, 0x119), (8, 0x124)]:
                data[offset] = 255 if mask & bit else 0
            buffer = ctypes.create_string_buffer(bytes(data))
            self.assertEqual(fn(buffer), int(mask != 0))

    @unittest.skipUnless(shutil.which('git'), 'git missing')
    def test_publication_guard_rejects_renamed_binary_and_private_paths(self):
        repo = Path(self.tmp.name)/'repo'
        (repo/'tools').mkdir(parents=True)
        guard = repo/'tools/check-publication'
        shutil.copyfile(ROOT/'tools/check-publication', guard)
        subprocess.run(['git', 'init', '-q', str(repo)], check=True)
        fixture = repo/'renamed.txt'
        fixture.write_bytes(b'MZ synthetic fixture, not an executable')
        subprocess.run(['git', 'add', 'renamed.txt'], cwd=repo, check=True)
        result = subprocess.run([sys.executable, str(guard), '--staged'], capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('renamed.txt', result.stderr)
        fixture.write_text('ordinary source documentation')
        subprocess.run(['git', 'add', 'renamed.txt'], cwd=repo, check=True)
        subprocess.run([sys.executable, str(guard), '--staged'], check=True, capture_output=True)
        (repo/'.local').mkdir()
        (repo/'.local/private.txt').write_text('private output')
        subprocess.run(['git', 'add', '.local/private.txt'], cwd=repo, check=True)
        result = subprocess.run([sys.executable, str(guard), '--staged'], capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('.local/private.txt', result.stderr)

    def test_unverified_binary_cannot_match(self):
        result = subprocess.run([str(ROOT/'tools/decomp'), 'match', '0x004020B0', '--binary', str(self.p)],
                                capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('Unsupported SHA-256', result.stderr)

    def test_cli_synthetic_analysis_deterministic_and_private_only(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'.local') as out:
            cmd = [str(ROOT/'tools/decomp'), 'analyze', '--allow-unverified', '--binary', str(self.p), '--out', out]
            subprocess.run(cmd, check=True, capture_output=True)
            initial = {p.name: p.read_bytes() for p in Path(out).glob('*.json')}
            subprocess.run(cmd, check=True, capture_output=True)
            self.assertEqual(initial, {p.name: p.read_bytes() for p in Path(out).glob('*.json')})
            funcs = json.loads(initial['functions.json'])
            self.assertEqual(len(funcs), 1)
            self.assertIsNone(funcs[0]['size'])
            self.assertFalse(funcs[0]['boundary_verified'])
        result = subprocess.run(cmd[:-1]+[str(ROOT/'docs')], capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('Generated artifacts', result.stderr)

if __name__ == '__main__':
    (ROOT/'.local').mkdir(exist_ok=True)
    unittest.main()
