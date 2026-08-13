#!/usr/bin/env python3
"""Run a build and hide the one GHC warning that c2hs generates in every module.

c2hs emits a fixed prelude of imports into every generated .hs, including

    import qualified Foreign.ForeignPtr as C2HSImp

which goes unused in any module whose pointer types are declared `{#pointer ... nocode#}'
-- the pattern CLAUDE.md mandates wherever Finalizable/Upcastable instances are
hand-written, i.e. nearly everywhere. The result is 28 identical warnings on a full
build, none of them actionable and none of them ours. They are not a source problem:
GHC's source span points at the nearest .chs import line (c2hs's line mapping), so the
warning appears to blame a hand-written import that is in fact fine.

That noise has a cost. It hid a genuine unused `Foreign.Ptr' import in
QuantLib/Instrument/Credit.chs through several sessions, which is what prompted this
script. The alternative -- {-# OPTIONS_GHC -Wno-unused-imports #-} per module -- would
have suppressed that real hit too, in exactly the files where it mattered, and would
need adding to every new module forever.

So: filter at the reporting layer, keep -Wunused-imports fully on.

What it will NOT hide, deliberately:
  * anything that is not a warning -- errors always pass through,
  * any warning whose message differs by even a word from the c2hs one,
  * any warning about a module other than Foreign.ForeignPtr. The real hit above was an
    *unqualified* `Foreign.Ptr' import; the c2hs artifact is a *qualified*
    `Foreign.ForeignPtr' one. Similar-looking, and only one of them is noise.
  * C++ warnings -- those are handled properly at the compiler by -isystem (see the
    Makefile), not here.

It also never hides silently: the count of suppressed warnings is printed at the end, so
a build that has gone quiet for the wrong reason is still visible.

The one case it cannot distinguish: a *hand-written* `import qualified Foreign.ForeignPtr'
that is genuinely redundant would produce the same message and be hidden. Nothing in the
tree has one, and c2hs's own import makes adding one pointless.

Usage:
    tools/quiet-build.py stack build --test --no-haddock
    stack build 2>&1 | tools/quiet-build.py
    tools/quiet-build.py --show-all stack build     # filter disabled, for checking

Exit status is the build's own, so it stays usable in CI and in `make'.
"""

import argparse
import re
import subprocess
import sys

# A GHC diagnostic header: "path/File.chs:33:1: warning: [GHC-66111] [-Wunused-imports]".
# Stack sometimes prefixes compiler output with "hasquant> ", so allow that.
HEADER = re.compile(r'^(?:[\w.-]+> )?\S.*?:\d+:\d+: (?P<kind>warning|error)\b')

# A continuation line of a diagnostic: blank, indented, or GHC's source snippet ("33 | ...").
CONTINUATION = re.compile(r'^(?:\s*$|\s|\d+ \|)')

# The c2hs artifact, matched on the message rather than the source span, which is
# misattributed. GHC normally uses curly quotes; ASCII appears under some locales.
BENIGN = re.compile(r'The qualified import of [‘\'"`]?Foreign\.ForeignPtr'
                    r'[’\'"`]? is redundant')


def is_noise(block):
    """True only for a c2hs-generated redundant-ForeignPtr *warning* in a .chs module."""
    head = block[0]
    if HEADER.match(head).group('kind') != 'warning':
        return False
    if '.chs:' not in head:
        return False
    return any(BENIGN.search(line) for line in block)


def filter_stream(lines, out, show_all):
    """Pass `lines' through to `out', dropping noise blocks. Returns the drop count."""
    dropped = 0
    block = []

    def flush():
        nonlocal dropped
        if not block:
            return
        if not show_all and HEADER.match(block[0]) and is_noise(block):
            dropped += 1
        else:
            out.writelines(block)
        block.clear()

    for line in lines:
        if HEADER.match(line):
            flush()
            block.append(line)
        elif block and CONTINUATION.match(line):
            block.append(line)
        else:
            flush()
            out.write(line)
        out.flush()
    flush()
    return dropped


def main():
    ap = argparse.ArgumentParser(
        description=__doc__.split('\n')[0],
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--show-all', action='store_true',
                    help='disable filtering; print every warning verbatim')
    ap.add_argument('command', nargs=argparse.REMAINDER,
                    help='build command to run; if omitted, filters stdin')
    args = ap.parse_args()

    if args.command:
        proc = subprocess.Popen(args.command, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True,
                                errors='replace', bufsize=1)
        dropped = filter_stream(proc.stdout, sys.stdout, args.show_all)
        status = proc.wait()
    else:
        dropped = filter_stream(sys.stdin, sys.stdout, args.show_all)
        status = 0

    if dropped:
        print(f'quiet-build: hid {dropped} c2hs Foreign.ForeignPtr import '
              f'warning(s); --show-all to see them', file=sys.stderr)
    sys.exit(status)


if __name__ == '__main__':
    main()
