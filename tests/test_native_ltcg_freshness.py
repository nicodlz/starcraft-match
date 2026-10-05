"""Native map, layout and Wine identity participate in proof freshness."""
import copy
import json
import unittest
from unittest.mock import patch

import test_component_freshness as baseline


class NativeFreshnessTests(unittest.TestCase):
    def setUp(self):
        self.component = baseline.ComponentFreshnessTests()
        self.component.setUp()
        self.addCleanup(self.component.doCleanups)
        self.fixture = f = self.component.fixture
        self.m = m = baseline.baseline.m
        for name in ('ltcg.py', 'compare.py'):
            (f.root / 'tools/matching' / name).write_bytes(b'independent adapter snapshot')
        f.linkconfig.update(mode='native-msvc71-ltcg-component-v1', timestamps=True,
                            identity_arguments=['--identity-json'])
        (f.root / 'config/linkers.json').write_text(json.dumps({'external': f.linkconfig}))
        f.r['size'] = f.report['build']['linking']['linked_size']
        self.identity = dict(version='Independent native fixture', status='available', runtime_sha256='a' * 64)
        self.identity_patch = patch.object(m, 'compiler_identity', side_effect=lambda p:
                                          copy.deepcopy(self.identity) if p.get('mode') else None)
        self.identity_patch.start()
        self.addCleanup(self.identity_patch.stop)
        b = f.report['build']
        b.update(function_record_sha256=m.json_digest(f.r), linker_state=m.linker_state(f.r),
                 match_method='native-msvc71-ltcg-c-component')
        expected = m.linking_record(f.r, b, b['linker_state'])
        b['linking_record_sha256'] = m.json_digest(expected)
        native = b['linking']
        native.update(record_sha256=b['linking_record_sha256'], category='native-msvc71-ltcg-C-contribution-v1',
                      compiler_provenance=expected['compiler_provenance'],
                      linker={k: b['linker_state'][k] for k in ('executable', 'sha256', 'version', 'emulation')},
                      intermediate_format='opaque-msvc71-GL', contribution_extent_source='native-linker-map',
                      normalization=False, object_byte_modification=False,
                      original_byte_input=False, placement_space_counted=False)
        for name, key in [('layout.json', 'script_sha256'), ('layout.obj', 'layout_object_sha256'), ('native.map', 'map_sha256')]:
            path = f.root / 'build/0x00410000/linked' / name
            path.write_bytes(b'independent native auxiliary ' + name.encode())
            native[key] = m.file_digest(path)

    def test_complete_native_report_is_fresh(self):
        self.assertTrue(self.fixture.fresh())

    def test_runtime_or_map_layout_replacement_invalidates(self):
        f = self.fixture
        for name in ('native.map', 'layout.obj', 'layout.json'):
            path = 'build/0x00410000/linked/' + name
            original = (f.root / path).read_bytes()
            f.mutate(path)
            self.assertFalse(f.fresh())
            (f.root / path).write_bytes(original)
        self.identity['runtime_sha256'] = 'b' * 64
        self.assertFalse(f.fresh())

    def test_normalization_and_extent_claims_rejected(self):
        native = self.fixture.report['build']['linking']
        for key in ('normalization', 'object_byte_modification', 'original_byte_input', 'placement_space_counted'):
            native[key] = True
            self.assertFalse(self.fixture.fresh())
            native[key] = False
        native['contribution_extent_source'] = 'guessed end boundary'
        self.assertFalse(self.fixture.fresh())


if __name__ == '__main__':
    unittest.main()
