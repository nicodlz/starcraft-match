"""Orchestration checks using independently authored C, without game input."""
import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import unittest
import uuid
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('linked_decomp', ROOT/'tools/decomp')
# The extensionless executable requires an explicit loader.
from importlib.machinery import SourceFileLoader
spec = importlib.util.spec_from_loader('linked_decomp', SourceFileLoader('linked_decomp', str(ROOT/'tools/decomp')))
d = importlib.util.module_from_spec(spec)
spec.loader.exec_module(d)


class LinkRecordTests(unittest.TestCase):
    def test_binding_inventory_rejects_ambiguous_records(self):
        good = {'linkage': {'method': 'coff-ld-i386-v1', 'bindings': [
            {'symbol': '_helper', 'address': 0x408000}]}}
        self.assertEqual(d.reviewed_linkage(good), good['linkage'])
        for bindings in ([{'symbol': '', 'address': 1}],
                         [{'symbol': '_helper', 'address': True}],
                         [{'symbol': '_helper', 'address': 1}] * 2,
                         [{'symbol': '_helper', 'address': 1}, {'symbol': '_other', 'address': 1}]):
            with self.subTest(bindings=bindings), self.assertRaises(ValueError):
                d.reviewed_linkage({'linkage': {'method': 'coff-ld-i386-v1', 'bindings': bindings}})
        with self.assertRaises(ValueError):
            d.reviewed_linkage({'linkage': {'method': 'guess', 'bindings': []}})

    def test_malformed_link_report_is_stale(self):
        for manifest in (None, [], {'link_manifest': None}):
            self.assertFalse(d.report_is_fresh({'linkage': {}, 'compiler_profile': 'clang-i686-scaffold'},
                                              {'build': manifest}))


@unittest.skipUnless(shutil.which('clang') and shutil.which('ld'), 'Clang and GNU ld required')
class LinkedPipelineTests(unittest.TestCase):
    def setUp(self):
        self.directory = ROOT/'src'/('synthetic-pipeline-' + uuid.uuid4().hex)
        self.directory.mkdir(parents=True)
        self.addCleanup(shutil.rmtree, self.directory, ignore_errors=True)
        self.source = self.directory/'candidate.c'
        self.source.write_text('extern unsigned helper(unsigned); extern unsigned counter; '
                               'unsigned candidate(unsigned x){return helper(x)+counter;}\n')
        self.r = dict(address='0x00412340', compiler_profile='clang-i686-scaffold',
                      candidate_source=str(self.source.relative_to(ROOT)), candidate_symbol='_candidate',
                      candidate_abi_compatible=True, binary_sha256='a'*64,
                      linkage={'method': 'coff-ld-i386-v1', 'bindings': [
                          {'symbol': '_helper', 'address': 0x408000},
                          {'symbol': '_counter', 'address': 0x500020}]})

    def test_real_link_freshness_and_source_only_qualification(self):
        data, build = d.build(self.r)
        self.assertTrue(data)
        self.assertFalse(build['candidate_abi_compatible'])
        self.assertFalse(build['link_proof_eligible'])
        report = {'build': build, 'binary_sha256': self.r['binary_sha256']}
        self.assertTrue(d.report_is_fresh(self.r, report))
        changed = copy.deepcopy(self.r)
        changed['linkage']['bindings'][0]['address'] += 16
        self.assertFalse(d.report_is_fresh(changed, report))
        self.source.write_text(self.source.read_text() + '\n')
        self.assertFalse(d.report_is_fresh(self.r, report))
        self.source.write_text(self.source.read_text()[:-1])
        self.assertTrue(d.report_is_fresh(self.r, report))
        artifact = Path(build['linked_build_directory'])/'linked.exe'
        artifact.write_bytes(artifact.read_bytes() + b'corrupt')
        self.assertFalse(d.report_is_fresh(self.r, report))

    def test_unresolved_binding_is_hard_failure(self):
        self.r['linkage']['bindings'].pop()
        with self.assertRaises(ValueError):
            d.build(self.r)

    def test_failed_rebuild_removes_old_match_report(self):
        from argparse import Namespace
        output = ROOT/'analysis/matches'/f'{self.r["address"]}.json'
        if output.exists():
            self.skipTest('Synthetic address already has a local report')
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text('{"old":true}')
        self.addCleanup(output.unlink, missing_ok=True)
        pe = type('SyntheticBinary', (), {'metadata': {'sha256': self.r['binary_sha256']}})()
        record = dict(self.r, boundary_verified=True, size=32)
        with patch.object(d, 'function', return_value=record), patch.object(d, 'binary', return_value=pe), \
             patch.object(d, 'build', side_effect=ValueError('Unresolved binding')):
            with self.assertRaises(ValueError):
                d.match(Namespace(address=record['address'], binary='synthetic', require_exact=True))
        self.assertFalse(output.exists())


if __name__ == '__main__':
    unittest.main(verbosity=2)
