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
            catalog = json.loads((checkout/'config/functions.json').read_text())
            expected = {r['address']: r for r in catalog if r.get('match_expectation') == 'exact'}
            self.assertEqual(summary['verified_exact_functions'], len(expected))
            self.assertEqual({r['address'] for r in summary['functions']}, set(expected))
            initial_proof = {'0x00488780', '0x00496FF0', '0x004CE6B0', '0x004DC540'}
            self.assertTrue(initial_proof <= set(expected), 'The initial proof must remain covered')
            self.assertGreaterEqual(sum(r['original_size'] for r in summary['functions']), 37)
            for row in summary['functions']:
                self.assertTrue(row['exact_byte_match'])
                self.assertTrue(row['abi_compatible'])
                self.assertEqual(row['original_size'], row['recompiled_size'])
                report = json.loads((checkout/'analysis/matches'/f'{row["address"]}.json').read_text())
                self.assertEqual(report['differences'], [])
                self.assertEqual(report['build']['candidate_sha256'], report['original_region_sha256'])
            task_cmd = [str(checkout/'tools/decomp'), 'task', '0x00488780', '--binary', str(BINARY)]
            subprocess.run(task_cmd, check=True, capture_output=True)
            task_path = checkout/'analysis/task.json'
            task = json.loads(task_path.read_text())
            self.assertTrue(task['match_report_current'])
            self.assertIsNotNone(task['match_report'])
            report_path = checkout/'analysis/matches/0x00488780.json'
            stale = json.loads(report_path.read_text())
            stale['build']['compiler_sha256'] = '0' * 64
            report_path.write_text(json.dumps(stale))
            subprocess.run(task_cmd, check=True, capture_output=True)
            task = json.loads(task_path.read_text())
            self.assertFalse(task['match_report_current'])
            self.assertIsNone(task['match_report'])
            status = subprocess.check_output([str(checkout/'tools/decomp'), 'status'], text=True)
            self.assertEqual(json.loads(status)['exact_match'], len(expected) - 1)
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
