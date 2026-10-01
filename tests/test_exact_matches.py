"""Optional real-executable regression; proprietary input is never copied into fixtures."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
BINARY = ROOT/'original/StarCraft.exe'


@unittest.skipUnless(BINARY.is_file() and shutil.which('clang') and shutil.which('objdump'),
                     'Requires local pinned executable, clang and objdump')
class ExactMatchProofTests(unittest.TestCase):
    def test_real_proof_and_deliberate_source_regression(self):
        # Private source-only checkout; original is read in place using --binary.
        # The negative test never edits the real source catalog or its reports.
        (ROOT/'.local').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='proof-regression-', dir=ROOT/'.local') as tmp:
            checkout = Path(tmp)
            for directory in ('tools', 'config', 'include', 'src'):
                shutil.copytree(ROOT/directory, checkout/directory, ignore=shutil.ignore_patterns('__pycache__'))
            cmd = [str(checkout/'tools/decomp'), 'verify-matches', '--binary', str(BINARY)]
            success = subprocess.run(cmd, capture_output=True, text=True)
            self.assertEqual(success.returncode, 0, success.stdout+success.stderr)
            summary_path = checkout/'analysis/proof-of-concept.json'
            summary = json.loads(summary_path.read_text())
            self.assertEqual(summary['verified_exact_functions'], 4)
            self.assertEqual(sum(r['original_size'] for r in summary['functions']), 37)
            for row in summary['functions']:
                self.assertTrue(row['exact_byte_match'])
                self.assertTrue(row['abi_compatible'])
                self.assertEqual(row['original_size'], row['recompiled_size'])
                report = json.loads((checkout/'analysis/matches'/f'{row["address"]}.json').read_text())
                self.assertEqual(report['differences'], [])
                self.assertEqual(report['build']['candidate_sha256'], report['original_region_sha256'])
            source = checkout/'src/game/sub_00488780.c'
            text = source.read_text()
            self.assertIn('return SC_PAUSE_STATE;', text)
            source.write_text(text.replace('return SC_PAUSE_STATE;', 'return SC_PAUSE_STATE ^ 1u;'))
            failure = subprocess.run(cmd, capture_output=True, text=True)
            self.assertNotEqual(failure.returncode, 0)
            self.assertIn('required exact match failed', failure.stderr)
            self.assertFalse(summary_path.exists(), 'Old successful proof must not survive failed verification')
            failed_report = json.loads((checkout/'analysis/matches/0x00488780.json').read_text())
            self.assertFalse(failed_report['exact_byte_match'])
            self.assertTrue(failed_report['differences'])


if __name__ == '__main__':
    unittest.main()
