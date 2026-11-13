#!/usr/bin/env python3
"""Detect drift between upstream YoY inflation code and the copies kept in cbits/.

BracketedYoyOptionletStripper::initialize copies InterpolatedYoYOptionletStripper::initialize,
changing only the root bracket. FixedStartYoyPriceSurface restates
InterpolatedYoYCapFloorTermPriceSurface::calculateYoYTermStructure with fixed-start helpers.
"""

import argparse
import hashlib
from pathlib import Path
import re
import subprocess
import sys

SHIM = Path(__file__).resolve().parent.parent / "cbits" / "qlTermStructureAux.cpp"
STRIPPER = "ql/experimental/inflation/interpolatedyoyoptionletstripper.hpp"
SURFACE = "ql/experimental/inflation/yoycapfloortermpricesurface.hpp"
BRACKET_LINES = {
    "Real lo = 0.00001, hi = 0.08;": "Real lo = lower_, hi = upper_;",
    "Real guess = (hi+lo)/2.0;": "Real guess = lo + (hi-lo)/2.0;",
}
# sha256 of calculateYoYTermStructure with comments and whitespace removed (QuantLib 1.43, 1.44).
ATM_CURVE_SHA256 = "c86dc1c692362949fcc4e93a6c19e1eb253752675239cb88fd5fd152d188a10e"


def include_dir(explicit):
    if explicit:
        return Path(explicit)
    prefix = subprocess.run(["quantlib-config", "--prefix"], check=True, capture_output=True, text=True)
    return Path(prefix.stdout.strip()) / "include"


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def body_after(text, marker):
    """The brace-delimited body following the first occurrence of marker."""
    start = text.index("{", text.index(marker))
    depth = 0
    for position in range(start, len(text)):
        depth += {"{": 1, "}": -1}.get(text[position], 0)
        if depth == 0:
            return text[start + 1:position]
    raise ValueError(f"unterminated body after {marker!r}")


def code_lines(body):
    return [line.strip() for line in strip_comments(body).splitlines() if line.strip()]


def check_stripper(upstream, shim):
    theirs = code_lines(body_after(upstream, "initialize(const ext::shared_ptr<YoYCapFloorTermPriceSurface> &s"))
    ours = code_lines(body_after(shim, "Real slope) const override"))
    expected = [BRACKET_LINES.get(line, line) for line in theirs]
    missing = [line for line in BRACKET_LINES if line not in theirs]
    if missing:
        return [f"upstream initialize no longer contains: {line}" for line in missing]
    if expected == ours:
        return []
    for index, (want, have) in enumerate(zip(expected, ours)):
        if want != have:
            return [f"stripper copy differs at code line {index + 1}:", f"  upstream: {want}", f"  cbits:    {have}"]
    return [f"stripper copy has {len(ours)} code lines, upstream has {len(expected)}"]


def atm_curve_hash(upstream):
    body = body_after(upstream, "calculateYoYTermStructure() const {")
    return hashlib.sha256("".join(strip_comments(body).split()).encode()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--include-dir", help="QuantLib include directory (default: quantlib-config --prefix)")
    parser.add_argument("--print-hash", action="store_true", help="print the upstream ATM-curve hash and exit")
    args = parser.parse_args()
    root = include_dir(args.include_dir)
    surface = (root / SURFACE).read_text()
    if args.print_hash:
        print(atm_curve_hash(surface))
        return 0
    problems = check_stripper((root / STRIPPER).read_text(), SHIM.read_text())
    found = atm_curve_hash(surface)
    if found != ATM_CURVE_SHA256:
        problems.append("upstream calculateYoYTermStructure changed; re-review FixedStartYoyPriceSurface "
                        f"and update ATM_CURVE_SHA256 to {found}")
    for problem in problems:
        print(problem, file=sys.stderr)
    if not problems:
        print("YoY upstream copies match", root)
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
