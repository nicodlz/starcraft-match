"""Portable adversarial native-link auditing, using independent synthetic bytes."""
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from matching.linking import LinkError, digest, read_coff
from matching.ltcg import layout_object, link_ltcg_candidate, parse_map


class NativeLtcgTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.obj = self.root / 'input.obj'
        self.obj.write_bytes(struct.pack('<HHHH', 0, 0xffff, 1, 0x14c) + b'independent synthetic intermediate')
        self.record = dict(schema_version=1, candidate=dict(symbol='_root', section='.text$b',
                           address=0x400200, size=6, object_sha256=digest(self.obj.read_bytes())),
                           retained_functions=[dict(symbol='_child', section='.text$d', address=0x400220,
                                                    size=6, evidence=['Independent synthetic fixture'])],
                           bindings={}, excluded_contexts=[], compiler_provenance={},
                           linker=dict(executable='synthetic', sha256='a' * 64, version='synthetic', emulation='i386pe'))
        self.map = '\n'.join([
            ' 0001:00000000 00000000H .text CODE',
            ' 0001:00000000 00000020H .text$a CODE',
            ' 0001:00000020 00000006H .text$b CODE',
            ' 0001:00000026 0000001aH .text$c CODE',
            ' 0001:00000040 00000006H .text$d CODE',
            ' 0000:00000000 ___safe_se_handler_count 00000000 <absolute>',
            ' 0000:00000000 ___safe_se_handler_table 00000000 <absolute>',
            ' 0001:00000000 _sc_layout_1 004001e0 layout.obj',
            ' 0001:00000020 _root 00400200 f link-input.obj',
            ' 0001:00000026 _sc_layout_2 00400206 layout.obj',
            ' 0001:00000040 _child 00400220 f link-input.obj',
        ])
        self.image = bytearray(0x230)
        b = self.image
        b[:2] = b'MZ'
        struct.pack_into('<I', b, 0x3c, 0x80)
        b[0x80:0x84] = b'PE\0\0'
        struct.pack_into('<HHIIIHH', b, 0x84, 0x14c, 1, 0, 0, 0, 224, 0x103)
        o = 0x98
        struct.pack_into('<H', b, o, 0x10b)
        struct.pack_into('<III', b, o + 28, 0x400000, 16, 16)
        struct.pack_into('<II', b, o + 56, 0x230, 0x1e0)
        struct.pack_into('<I', b, o + 92, 16)
        struct.pack_into('<8sIIIIIIHHI', b, o + 224, b'.text', 0x46, 0x1e0, 0x50, 0x1e0,
                         0, 0, 0, 0, 0x60000020)
        # Independent root calls child; child returns the value 1.
        b[0x200:0x206] = b'\xe8\x1b\0\0\0\xc3'
        b[0x220:0x226] = b'\xb8\x01\0\0\0\xc3'

    def run_link(self):
        actual_run = subprocess.run
        def fake(command, **kwargs):
            if command[0] != 'synthetic-linker':
                return actual_run(command, **kwargs)
            def output(flag):
                value = next(arg[len(flag):] for arg in command if arg.startswith(flag))
                return Path(value[2:].replace('\\', '/'))
            output('/out:').write_bytes(self.image)
            output('/map:').write_text(self.map)
            return SimpleNamespace(returncode=0, stdout='', stderr='')
        with patch('matching.ltcg.subprocess.run', side_effect=fake):
            return link_ltcg_candidate(self.obj, self.record, self.root / 'out', 'synthetic-linker')

    def test_whole_contributions_and_zero_layout_audited(self):
        code, manifest = self.run_link()
        self.assertEqual(code, self.image[0x200:0x206])
        self.assertEqual([row['size'] for row in manifest['contributions']], [6, 6])
        self.assertFalse(manifest['placement_space_counted'])
        self.assertEqual(self.obj.read_bytes(), (self.root / 'out/link-input.obj').read_bytes())

    def test_auxiliary_layout_contains_no_function_code_or_relocations(self):
        obj = read_coff(layout_object([('.text$a', 32)], {'_independent_data': 0x500000}))
        self.assertEqual(obj.sections[0].payload, bytes(32))
        self.assertFalse(obj.sections[0].relocations)
        symbol = next(s for s in obj.symbols.values() if s.name == '_independent_data')
        self.assertEqual((symbol.value, symbol.section, symbol.type), (0x500000, -1, 0))

    def test_complete_map_extent_and_symbol_ownership_enforced(self):
        original = self.map
        for mutated in [original.replace('00000006H .text$b', '00000005H .text$b'),
                        original.replace('_child 00400220', '_child 00400221'),
                        original.replace('_root 00400200 f link-input.obj', '_root 00400200 f layout.obj'),
                        original + '\n 0000:00000000 _unreviewed 00500000 <absolute>']:
            with self.subTest(map=mutated):
                self.map = mutated
                with self.assertRaises(LinkError):
                    self.run_link()
        self.map = original

    def test_zero_layout_and_no_imports_required(self):
        self.image[0x1e0] = 1
        with self.assertRaises(LinkError):
            self.run_link()
        self.image[0x1e0] = 0
        struct.pack_into('<II', self.image, 0x98 + 104, 0x220, 8)
        with self.assertRaises(LinkError):
            self.run_link()

    def test_external_indirect_and_unreachable_code_rejected(self):
        for root in [b'\xe8\xdb\xff\xff\xff\xc3', b'\xff\xd0\x90\x90\x90\xc3', b'\x90' * 5 + b'\xc3']:
            with self.subTest(root=root):
                self.image[0x200:0x206] = root
                with self.assertRaises(LinkError):
                    self.run_link()

    def test_non_gl_input_and_bad_placements_rejected(self):
        self.record['candidate']['section'] = '.text$d'
        with self.assertRaises(LinkError):
            self.run_link()
        self.record['candidate']['section'] = '.text$b'
        self.obj.write_bytes(b'ordinary COFF is not opaque GL')
        self.record['candidate']['object_sha256'] = digest(self.obj.read_bytes())
        with self.assertRaises(LinkError):
            self.run_link()

    def test_duplicate_native_map_records_rejected(self):
        with self.assertRaises(LinkError):
            parse_map(self.map + '\n 0001:00000020 _root 00400200 f link-input.obj')


if __name__ == '__main__':
    unittest.main()
