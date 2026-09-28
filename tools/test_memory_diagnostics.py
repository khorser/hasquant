"""Regression checks for crash-address recovery and allocation chronology."""
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent


def load(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / (name + '.py'))
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


symbolize = load('symbolize-windows-trace')


class Allocations(unittest.TestCase):
    def check_trace(self, trace, expected, fragment):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'trace'
            path.write_text(trace)
            run = subprocess.run([sys.executable, str(ROOT / 'alloc-summary.py'), str(path)],
                                 capture_output=True, text=True, check=False)
        self.assertEqual(run.returncode, expected, run.stdout + run.stderr)
        self.assertIn(fragment, run.stdout)

    def test_legitimate_reuse(self):
        self.check_trace(('returned Foo: 0x1\ndeleting Foo: 0x1\ndeleted Foo: 0x1\n') * 2,
                         0, 'nothing leaked')

    def test_overfree_hidden_by_later_acquisition(self):
        self.check_trace('returned Foo: 0x1\ndeleting Foo: 0x1\ndeleting Foo: 0x1\n'
                         'returned Foo: 0x1\n', 1, 'line 3: Foo 0x1')

    def test_label_mismatch(self):
        self.check_trace('returned Foo: 0x1\ndeleting Bar: 0x1\n', 1, 'line 2: Bar 0x1')

    def test_payload_and_wrapper(self):
        self.check_trace('allocated Payload: 0x1\nreturned Wrapper: 0x2\n'
                         'deleting Wrapper: 0x2\n', 0, 'nothing leaked')

    def test_namespaced_labels(self):
        self.check_trace('allocated hasquant::Callback: 0x1\n'
                         'returned hasquant::Owner: 0x2\n'
                         'deleting hasquant::Owner: 0x2\n', 0, 'nothing leaked')

    def test_leak(self):
        self.check_trace('returned Foo: 0x1\n', 1, 'STILL LIVE AT EXIT')

    def test_malformed(self):
        self.check_trace('unreadable\nreturned Foo: 0x1\ndeleting Foo: 0x1\n',
                         1, 'did not match')

    def test_empty(self):
        self.check_trace('', 1, '0 tracked allocations')


class Addresses(unittest.TestCase):
    TRACE = (r'libunwind: pc not in table, pc=0x7FF763A9AB94' '\n'
             r' * 0xc0ed5ed350 0x7ff764f1e75d D:\a\hasquant_test.exe+0x187e75d' '\n'
             r' * 0xc0ed5ed3b0 0x7ff764fd6d6e D:\a\hasquant_test.exe+0x1936d6e' '\n')

    def test_supplied_trace(self):
        self.assertEqual(symbolize.trace_frames(self.TRACE)[0],
                         ('hasquant_test.exe', 0x3fab94))

    def test_aslr_independent(self):
        trace = 'pc=0x10001234\n * 0x200 0x10005000 test/hasquant_test.exe+0x5000\n'
        self.assertEqual(symbolize.trace_frames(trace)[0], ('hasquant_test.exe', 0x1234))

    def test_conflicting_bases(self):
        trace = self.TRACE.replace('0x7ff764fd6d6e', '0x7ff864fd6d6e')
        self.assertEqual(len(symbolize.trace_frames(trace)), 2)

    def test_pc_outside_image(self):
        self.assertEqual(len(symbolize.trace_frames(self.TRACE, image_size=0x1000)), 2)

    def test_unknown_module_pc(self):
        trace = self.TRACE.replace('0x7FF763A9AB94', '0x7ff900001234')
        self.assertEqual(len(symbolize.trace_frames(trace)), 2)

    def test_explicit_map_and_trace_cli(self):
        with tempfile.TemporaryDirectory() as tmp:
            trace = Path(tmp) / 'trace.txt'
            symbols = Path(tmp) / 'symbols.map'
            trace.write_text(self.TRACE)
            symbols.write_text('0000000140000000 A __ImageBase\n'
                               '00000001403fab00 T callback\n')
            run = subprocess.run([sys.executable, str(ROOT / 'symbolize-windows-trace.py'),
                                  '--map', str(symbols), str(trace)],
                                 capture_output=True, text=True, check=False)
            self.assertEqual(run.returncode, 0, run.stderr)
            self.assertIn('hasquant_test.exe+0x3fab94\tcallback+0x94', run.stdout)

    def test_no_runtime_base(self):
        self.assertEqual(symbolize.trace_frames('pc=0x1234 hasquant_test.exe+0x5000'),
                         [('hasquant_test.exe', 0x5000)])


if __name__ == '__main__':
    unittest.main()
