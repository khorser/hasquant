#!/usr/bin/env python3
"""Regression tests for out-of-line trivial-getter discovery.

Run from tools/ with:
    pixi run python -m unittest test_detect_trivial_getters.py
"""
import unittest

import clang.cindex

import detect_trivial_getters as detector


class OutOfLineDefinitionsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.index = clang.cindex.Index.create()
        cls.args = detector.get_mac_clang_args()

    def candidates(self, header):
        return detector.analyze_header(header, self.index, self.args)

    def test_coupon_constructor_and_getter_in_cpp_are_matched(self):
        found = self.candidates("ql/cashflows/coupon.hpp")
        candidate = found[("Coupon", "nominal", 0)]
        self.assertEqual(candidate.field, "nominal_")
        self.assertEqual(candidate.getter_evidence, "return nominal_;")

    def test_indexed_cash_flow_out_of_line_constructor_is_matched(self):
        found = self.candidates("ql/cashflows/indexedcashflow.hpp")
        expected = {
            "notional": "notional_",
            "baseDate": "baseDate_",
            "fixingDate": "fixingDate_",
            "index": "index_",
            "growthOnly": "growthOnly_",
        }
        for method, field in expected.items():
            with self.subTest(method=method):
                self.assertEqual(found[("IndexedCashFlow", method, 0)].field, field)


if __name__ == "__main__":
    unittest.main()
