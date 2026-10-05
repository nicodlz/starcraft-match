"""Synthetic compiled-dependency linking; no game bytes needed."""
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from matching.components import audit_component, link_component_candidate
from matching.linking import LinkError, read_coff, unique_function


class ComponentTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not shutil.which('clang') or not shutil.which('ld'):
            raise unittest.SkipTest('Clang and GNU ld required')
        cls.temp = tempfile.TemporaryDirectory(prefix='synthetic-component-')
        cls.addClassCleanup(cls.temp.cleanup)
        cls.root = Path(cls.temp.name)
        cls.source = cls.root / 'fixture.c'
        cls.source.write_bytes((Path(__file__).parent / 'fixtures/linked_component.c').read_bytes())
        cls.obj = cls.root / 'fixture.obj'
        cls.flags = ['--target=i686-pc-windows-msvc', '-O2', '-ffreestanding',
                     '-fno-addrsig', '-fno-ident', '-ffunction-sections']
        subprocess.run(['clang', *cls.flags, '-c', str(cls.source), '-o', str(cls.obj)], check=True)
        cls.data = cls.obj.read_bytes()
        cls.parsed = read_coff(cls.data)
        cls.linker = Path(shutil.which('ld'))

    def record(self):
        helper = unique_function(self.parsed, '_helper@4')
        return dict(schema_version=1,
                    candidate=dict(symbol='_component@4', section='.root', address=0x423000,
                                   object_sha256=hashlib.sha256(self.data).hexdigest()),
                    retained_functions=[dict(symbol='_helper@4', section='.helper', address=0x469000,
                                             size=helper.size, evidence=['Independent synthetic C'])],
                    bindings={'_fixed_state': dict(address=0x512000, kind='data', evidence=['Synthetic state'])},
                    excluded_contexts=[dict(symbol='_context', section='.context')],
                    compiler_provenance=dict(profile='synthetic-clang-i686-o2',
                                             source_sha256=hashlib.sha256(self.source.read_bytes()).hexdigest(),
                                             compiler_driver_sha256=hashlib.sha256(Path(shutil.which('clang')).read_bytes()).hexdigest(),
                                             compiler_identity_sha256=hashlib.sha256(subprocess.check_output(['clang', '--version'])).hexdigest(),
                                             compiler_profile_sha256=hashlib.sha256(json.dumps(self.flags).encode()).hexdigest()),
                    linker=dict(sha256=hashlib.sha256(self.linker.read_bytes()).hexdigest(),
                                version=subprocess.check_output(['ld', '--version'], text=True).splitlines()[0],
                                emulation='i386pe'))

    def test_real_callee_emitted_and_call_points_to_it(self):
        code, manifest = link_component_candidate(self.obj, self.record(), self.root / 'baseline')
        self.assertEqual(len(manifest['contributions']), 2)
        root = next(c for c in manifest['contributions'] if c['section'] == '.root')
        call = next(r for r in root['relocations'] if r['type'] == 20)
        displacement = struct.unpack_from('<I', code, call['offset'])[0]
        self.assertEqual((displacement + 0x423000 + call['offset'] + 4) & 0xffffffff, 0x469000)
        helper = unique_function(self.parsed, '_helper@4')
        # This synthetic helper has one DIR32 reference; other bytes must be unchanged.
        emitted = (self.root / 'baseline/helper.bin').read_bytes()
        relocation_bytes = {i for off, _, _ in helper.relocations for i in range(off, off + 4)}
        self.assertEqual(len(emitted), helper.size)
        self.assertTrue(all(a == b for i, (a, b) in enumerate(zip(helper.payload, emitted)) if i not in relocation_bytes))
        self.assertFalse(manifest['normalization'])
        self.assertFalse(manifest['object_byte_modification'])

    def test_deterministic_component_image(self):
        _, a = link_component_candidate(self.obj, self.record(), self.root / 'first')
        _, b = link_component_candidate(self.obj, self.record(), self.root / 'second')
        self.assertEqual(a['linked_image_sha256'], b['linked_image_sha256'])

    def test_external_code_and_defined_symbol_rebinding_rejected(self):
        for name in ['_helper@4', '_missing_code']:
            r = self.record()
            r['bindings'][name] = dict(address=0x400000, kind='code', evidence=['Synthetic'])
            with self.assertRaisesRegex(LinkError, 'code must be compiled'):
                audit_component(self.parsed, r)

    def test_unapproved_or_trimmed_helper_rejected(self):
        r = self.record()
        r['retained_functions'] = []
        with self.assertRaises(LinkError):
            audit_component(self.parsed, r)
        r = self.record()
        r['retained_functions'][0]['size'] -= 1
        with self.assertRaisesRegex(LinkError, 'extent'):
            audit_component(self.parsed, r)

    def test_overlapping_placements_rejected(self):
        r = self.record()
        r['retained_functions'][0]['address'] = r['candidate']['address']
        with self.assertRaisesRegex(LinkError, 'Overlapping'):
            audit_component(self.parsed, r)

    def test_missing_and_extra_data_bindings_rejected(self):
        r = self.record()
        r['bindings'] = {}
        with self.assertRaisesRegex(LinkError, 'Unbound'):
            audit_component(self.parsed, r)
        r = self.record()
        r['bindings']['_unused_data'] = dict(address=0x512004, kind='data', evidence=['Synthetic'])
        with self.assertRaisesRegex(LinkError, 'exactly cover'):
            audit_component(self.parsed, r)

    def test_context_called_as_dependency_rejected(self):
        r = self.record()
        r['retained_functions'][0] = dict(symbol='_context', section='.context', address=0x469000,
                                         size=unique_function(self.parsed, '_context').size, evidence=['Synthetic'])
        r['excluded_contexts'] = [dict(symbol='_helper@4', section='.helper')]
        with self.assertRaisesRegex(LinkError, 'unretained'):
            audit_component(self.parsed, r)

    def test_missing_context_approval_rejected(self):
        r = self.record()
        r['excluded_contexts'] = []
        with self.assertRaisesRegex(LinkError, 'Unapproved'):
            audit_component(self.parsed, r)

    def test_unreachable_retained_function_rejected(self):
        r = self.record()
        r['retained_functions'].append(dict(symbol='_context', section='.context', address=0x470000,
                                           size=unique_function(self.parsed, '_context').size, evidence=['Synthetic']))
        r['excluded_contexts'] = []
        with self.assertRaisesRegex(LinkError, 'reachable'):
            audit_component(self.parsed, r)

    def test_provenance_and_linker_changes_rejected(self):
        r = self.record()
        r['candidate']['object_sha256'] = '0' * 64
        with self.assertRaisesRegex(LinkError, 'provenance changed'):
            audit_component(self.parsed, r)
        r = self.record()
        r['linker']['version'] = 'other'
        with self.assertRaisesRegex(LinkError, 'Linker identity'):
            link_component_candidate(self.obj, r, self.root / 'wrong-linker')

    def test_malformed_metadata_rejected(self):
        for r in [{}, dict(self.record(), compiler_provenance=None)]:
            with self.assertRaises(LinkError):
                audit_component(self.parsed, r)


if __name__ == '__main__':
    unittest.main()
