#!/usr/bin/env python3
"""Drive `stack test --coverage` so it actually instruments the c2hs-bound modules.

Every c2hs-generated .hs (QuantLib.CashFlow, QuantLib.Instrument.*, QuantLib.Time.Calendar,
...) carries `{-# LINE n "Foo.chs" #-}` pragmas remapping each declaration back to .chs
source positions. GHC's HPC pass respects those pragmas when assigning tick locations, and
then can't reconcile a tick whose file is "Foo.chs" (a preprocessor input, never itself
compiled) with the module it's instrumenting -- so it silently records zero ticks for the
whole module instead of erroring. A plain `stack test --coverage` therefore only ever
measures the hand-written modules (QuantLib.Internal*, everything under test/), never the
generated binding layer -- confirmed by a manual spike: stripping the LINE pragmas from one
generated module by hand took its .mix file from 0 tick entries to 3170.

This script automates that spike for every c2hs-generated module in one shot:

  1. `stack build --coverage` once, to materialize fresh .chs -> .hs output (LINE pragmas
     intact).
  2. Strip the `{-# LINE ... "*.chs" #-}` lines from every generated .hs in place.
  3. Delete those modules' compiled .hi/.o/.dyn_hi/.dyn_o -- required because stack's own
     up-to-date check is keyed on the .chs input's hash, not the .hs output, so it won't
     notice the edit and won't recompile on its own (same class of caching gotcha as
     `trackAllocations`, see CLAUDE.md/run-hasquant skill).
  4. `stack build --coverage` again -- cabal's preprocessor step sees the .hs is newer than
     the .chs and skips re-running c2hs, so GHC compiles the now-pragma-free source with
     -fhpc for real.
  5. `stack test --coverage <extra args>`, and print the report paths stack emits.

Needs a clean build to start from (deletes and regenerates c2hs output), so this always
begins with `stack clean hasquant`. Requires network/build time comparable to a full
`stack build --test`; not meant to run on every edit.
"""
import re
import subprocess
import sys
from pathlib import Path

LINE_PRAGMA = re.compile(r'^\{-# LINE \d+ "[^"]*\.chs" #-\}\n?$')


def run(cmd, **kw):
    print(f"==> {' '.join(cmd)}")
    subprocess.run(cmd, check=True, **kw)


def stack_path(what):
    return subprocess.run(
        ["stack", "path", what], check=True, capture_output=True, text=True
    ).stdout.strip()


def strip_line_pragmas(build_dir: Path):
    quantlib_dir = build_dir / "QuantLib"
    touched = []
    for hs in sorted(quantlib_dir.rglob("*.hs")):
        text = hs.read_text()
        lines = text.splitlines(keepends=True)
        if not any(LINE_PRAGMA.match(line) for line in lines):
            continue
        stripped = [line for line in lines if not LINE_PRAGMA.match(line)]
        hs.write_text("".join(stripped))
        touched.append(hs)
    return touched


def clear_compiled_outputs(hs_files):
    for hs in hs_files:
        for ext in (".hi", ".o", ".dyn_hi", ".dyn_o"):
            candidate = hs.with_suffix(ext)
            candidate.unlink(missing_ok=True)


def main():
    extra_test_args = sys.argv[1:] or ["--ta", "--skip LONG"]

    run(["stack", "clean", "hasquant"])
    run(["stack", "build", "--coverage", "--no-haddock"])

    dist_dir = Path(stack_path("--dist-dir"))
    build_dir = dist_dir / "build"

    touched = strip_line_pragmas(build_dir)
    print(f"==> stripped LINE pragmas from {len(touched)} generated modules")
    if not touched:
        print("nothing to strip -- is the build dir path still QuantLib/*.hs? aborting.")
        sys.exit(1)

    clear_compiled_outputs(touched)
    run(["stack", "build", "--coverage", "--no-haddock"])

    run(["stack", "test", "--coverage", *extra_test_args])


if __name__ == "__main__":
    main()
