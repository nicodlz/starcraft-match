"""Compiled dependency artifacts and their ABI review must invalidate stale reports."""
import copy
import json
import unittest

import test_linked_freshness as baseline


class ComponentFreshnessTests(unittest.TestCase):
    def setUp(self):
        self.fixture = baseline.LinkedFreshnessTests()
        self.fixture.setUp()
        self.addCleanup(self.fixture.tearDown)
        f = self.fixture
        m = baseline.m
        (f.root / 'tools/matching/components.py').write_bytes(b'synthetic component adapter')
        f.linkconfig['mode'] = 'compiled-component-v1'
        (f.root / 'config/linkers.json').write_text(json.dumps({'external': f.linkconfig}))
        f.r['linking']['bindings']['_external']['kind'] = 'data'
        helper = dict(symbol='_helper', section='.helper', address=0x469000, size=11, evidence=['Synthetic ABI'])
        f.r['linking']['retained_functions'] = [helper]
        self.helper_catalog = dict(address='0x00469000', size=11, candidate_abi_compatible=True)
        (f.root / 'config/functions.json').write_text(json.dumps([self.helper_catalog]))
        path = f.root / 'build/0x00410000/linked/helper.bin'
        path.write_bytes(b'helper-body')
        (f.root / 'build/0x00410000/linked/scmatch.bin').write_bytes((f.root / 'build/0x00410000/candidate.bin').read_bytes())
        b = f.report['build']
        b.update(function_record_sha256=m.json_digest(f.r), linker_state=m.linker_state(f.r),
                 match_method='standard-linked-c-component')
        expected = m.linking_record(f.r, b, b['linker_state'])
        b['linking_record_sha256'] = m.json_digest(expected)
        b['linking'].update(record_sha256=b['linking_record_sha256'],
                            category='component-standard-linked-C-contribution-v1',
                            compiler_provenance=copy.deepcopy(expected['compiler_provenance']))
        b['linking']['contributions'] = [dict(symbol='_candidate', section='.scmatch', address=0x410000,
                                             size=b['linking']['linked_size'], sha256=b['candidate_sha256']),
                                        dict(symbol='_helper', section='.helper', address=0x469000,
                                             size=11, sha256=m.file_digest(path))]
        f.report['compiled_dependencies'] = [dict(address='0x00469000', size=11, sha256=m.file_digest(path),
                                                 exact_byte_match=True, catalog_record_sha256=m.json_digest(self.helper_catalog))]

    def test_complete_component_report_is_fresh(self):
        self.assertTrue(self.fixture.fresh())

    def test_compiled_helper_mutation_rejected(self):
        self.fixture.mutate('build/0x00410000/linked/helper.bin')
        self.assertFalse(self.fixture.fresh())

    def test_helper_abi_review_change_rejected(self):
        self.helper_catalog['candidate_abi_compatible'] = False
        (self.fixture.root / 'config/functions.json').write_text(json.dumps([self.helper_catalog]))
        self.assertFalse(self.fixture.fresh())

    def test_missing_contribution_or_comparison_rejected(self):
        f = self.fixture
        contributions = f.report['build']['linking']['contributions']
        f.report['build']['linking']['contributions'] = contributions[:1]
        self.assertFalse(f.fresh())
        f.report['build']['linking']['contributions'] = contributions
        f.report['compiled_dependencies'][0]['exact_byte_match'] = False
        self.assertFalse(f.fresh())

    def test_component_adapter_or_common_reader_mutation_rejected(self):
        for path in ['tools/matching/components.py', 'tools/matching/linking.py']:
            with self.subTest(path=path):
                data = (self.fixture.root / path).read_bytes()
                self.fixture.mutate(path)
                self.assertFalse(self.fixture.fresh())
                (self.fixture.root / path).write_bytes(data)


if __name__ == '__main__':
    unittest.main()
