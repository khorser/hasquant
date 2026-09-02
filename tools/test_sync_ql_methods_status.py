#!/usr/bin/env python3
"""Unit tests for conservative ql-method status reconciliation."""
import importlib.util
import unittest
from pathlib import Path

spec = importlib.util.spec_from_file_location("sync", Path(__file__).with_name("sync_ql_methods_status.py"))
sync = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sync)


def row(n, status, header, decl):
    return n, f"|{status}|{header}|{decl}\n", ["", status, header, decl]


class SyncTest(unittest.TestCase):
    def test_promotes_exact_imported_shim_only(self):
        changes, ambiguous = sync.planned_changes([row(1, "", "ql/foo.hpp", "Foo::Foo(int x);")], {"qlFoo": 1}, {"qlFoo"})
        self.assertEqual(changes, {1: ("v", "imported shim")})
        self.assertEqual(ambiguous, [])

    def test_never_downgrades_existing_marker_or_applies_ambiguity(self):
        rows = [row(1, "v", "ql/foo.hpp", "Foo::Foo(int x);"), row(2, "", "ql/foo.hpp", "Foo::Foo(int x);")]
        changes, ambiguous = sync.planned_changes(rows, {"qlFoo": 3}, {"qlFoo"})
        self.assertEqual(changes, {})
        self.assertEqual(ambiguous, [])

    def test_marks_only_same_header_constructor_alternatives(self):
        rows = [row(1, "v", "ql/foo.hpp", "Foo::Foo(int x);"), row(2, "", "ql/foo.hpp", "Foo::Foo(double x);"), row(3, "", "ql/bar.hpp", "Foo::Foo(double x);")]
        changes, _ = sync.planned_changes(rows, {}, set(), exclude_constructors=True)
        self.assertEqual(changes, {2: ("x", "alternative constructor")})

    def test_does_not_guess_a_second_overload_from_a_numbered_shim(self):
        rows = [row(1, "v", "ql/foo.hpp", "Foo::f(int x);"), row(2, "", "ql/foo.hpp", "Foo::f(int x, int y);")]
        changes, ambiguous = sync.planned_changes(rows, {"qlFooF": 2, "qlFooF1": 3}, {"qlFooF", "qlFooF1"})
        self.assertEqual(changes, {})
        self.assertEqual(ambiguous, [])

    def test_nonpublic_scan_cannot_overwrite_a_confirmed_binding(self):
        rows = [row(1, "v", "ql/foo.hpp", "Foo::Foo();"), row(2, "", "ql/foo.hpp", "Foo::f();")]
        changes, _ = sync.planned_changes(rows, {}, set(), nonpublic={1, 2})
        self.assertEqual(changes, {2: ("x", "private/protected QuantLib declaration")})

    def test_render_preserves_non_tracking_lines(self):
        rows = [row(1, "", "ql/foo.hpp", "Foo::Foo();"), (2, "comment\n", ["comment"])]
        self.assertEqual(sync.render(rows, {1: ("v", "test")}), "|v|ql/foo.hpp|Foo::Foo();\ncomment\n")


if __name__ == "__main__":
    unittest.main()
