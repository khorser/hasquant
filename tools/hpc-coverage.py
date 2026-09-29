#!/usr/bin/env python3
"""Drive `cabal test --enable-coverage` so it actually instruments the c2hs-bound modules.

Every c2hs-generated .hs (QuantLib.CashFlow, QuantLib.Instrument.*, QuantLib.Time.Calendar,
...) carries `{-# LINE n "Foo.chs" #-}` pragmas remapping each declaration back to .chs
source positions. GHC's HPC pass respects those pragmas when assigning tick locations, and
then can't reconcile a tick whose file is "Foo.chs" (a preprocessor input, never itself
compiled) with the module it's instrumenting -- so it silently records zero ticks for the
whole module instead of erroring. A plain `cabal test --enable-coverage` therefore only ever
measures the hand-written modules (QuantLib.Internal*, everything under test/), never the
generated binding layer -- confirmed by a manual spike: stripping the LINE pragmas from one
generated module by hand took its .mix file from 0 tick entries to 3170.

This script automates that spike for every c2hs-generated module in one shot:

  1. Delete hasquant's build directory and `cabal build --enable-coverage` once, to
     materialize fresh .chs -> .hs output (LINE pragmas intact).
  2. Strip the `{-# LINE ... "*.chs" #-}` lines from every generated .hs in place.
  3. Delete the package's cabal-install build cache (`cache/build`), which otherwise reports
     the library up to date because no tracked source changed, then `cabal test
     --enable-coverage <extra args>`. Cabal's preprocessor sees the .hs is newer than the
     .chs and skips c2hs, and GHC recompiles the now-pragma-free source with -fhpc because
     its hash changed.
  4. Fail unless a known c2hs module's .mix has ticks, then print the report paths.

Budget the time of two full library builds plus a test run; not meant to run on every edit.
"""
import re
import shutil
import subprocess
import sys
from pathlib import Path

LINE_PRAGMA = re.compile(r'^\{-# LINE \d+ "[^"]*\.chs" #-\}\n?$')
MIX_TICK = re.compile(r'\bExpBox\b|\bTopLevelBox\b|\bLocalBox\b|\bBinBox\b')
GUARD_MODULE = "QuantLib.CashFlow"
COVERAGE = ["--enable-tests", "--enable-coverage"]


def run(cmd, **kw):
    print(f"==> {' '.join(cmd)}", flush=True)
    subprocess.run(cmd, check=True, **kw)


def build_dirs():
    return sorted(Path("dist-newstyle/build").glob("*/ghc-*/hasquant-*"))


def strip_line_pragmas(build_dir: Path):
    touched = []
    for hs in sorted((build_dir / "build" / "QuantLib").rglob("*.hs")):
        lines = hs.read_text().splitlines(keepends=True)
        if not any(LINE_PRAGMA.match(line) for line in lines):
            continue
        hs.write_text("".join(line for line in lines if not LINE_PRAGMA.match(line)))
        touched.append(hs)
    return touched


def guard_module_ticks(build_dir: Path):
    mixes = list(build_dir.rglob(f"{GUARD_MODULE}.mix"))
    return max((len(MIX_TICK.findall(m.read_text())) for m in mixes), default=0)


def main():
    test_args = sys.argv[1:] or ["--test-options=--skip=LONG"]

    for d in build_dirs():
        shutil.rmtree(d)
    run(["cabal", "build", "all", *COVERAGE])

    dirs = build_dirs()
    if len(dirs) != 1:
        sys.exit(f"expected one hasquant build dir, found {dirs}")
    build_dir = dirs[0]

    touched = strip_line_pragmas(build_dir)
    print(f"==> stripped LINE pragmas from {len(touched)} generated modules")
    if not touched:
        sys.exit("nothing to strip -- is the build dir path still build/QuantLib/*.hs? aborting.")

    (build_dir / "cache" / "build").unlink()
    run(["cabal", "test", "all", *COVERAGE, *test_args])

    ticks = guard_module_ticks(build_dir)
    if ticks == 0:
        sys.exit(f"{GUARD_MODULE}.mix has no ticks -- the stripped sources were not recompiled.")
    print(f"==> {GUARD_MODULE}.mix has {ticks} ticks")

    for index in sorted(build_dir.rglob("hpc_index.html")):
        print(index)


if __name__ == "__main__":
    main()
