#!/usr/bin/env python3
"""Pair up a QLTRACK_ALLOCATIONS trace and report what was never freed.

The trace is a flat log emitted by the alloc/ret/arg/del helpers in cbits/qlaux.h
when the library is built with -DQLTRACK_ALLOCATIONS (the `trackAllocations` cabal
flag). Raw, it is thousands of interleaved lines and answers nothing on its own.

There are two *independent* lifecycles in the trace, and conflating them makes every
object look either leaked or double-freed:

  returned Foo: 0x...   <- ret(): a pointer handed out to Haskell
  allocated Foo: 0x...  <- alloc(): a heap object, see below
  deleting Foo: 0x...   <- del(): freed, normally by a ForeignPtr finalizer
  deleted  Foo: 0x...   <- del() again, after the delete; the SAME event as `deleting'
  arg Foo: 0x...        <- arg(): pure pass-through, not a lifecycle event

The subtlety is that alloc() serves two purposes and only the pointer tells them
apart. In `ret(new QlYieldTermStructure(alloc(new FlatForward(...))))' the alloc'd
FlatForward is handed to a shared_ptr, which owns it from then on, so it has
deliberately no matching free line -- ever. But a plain value type like DayCounter is
alloc'd and returned directly, and *is* freed by del() later. Same verb, opposite
expectation. So an alloc'd pointer that is never released is only a leak if something
else ever released a pointer of that same kind; otherwise it is shared_ptr-owned and
expected. Reporting all of them as leaks (an earlier version of this script) or none
of them (the version after that) is wrong in both directions.

Usage:
    QLTRACK_ALLOCATIONS=/tmp/trace.log <your program>
    tools/alloc-summary.py /tmp/trace.log
    tools/alloc-summary.py /tmp/trace.log --only Handle,YieldTermStructure
    tools/alloc-summary.py /tmp/trace.log --census   # also list shared_ptr payloads

Exit status is 1 if the wrapper ledger does not balance.

Class names come from typeid().name(), so templates arrive mangled
(PN8QuantLib6HandleINS_18YieldTermStructureEEE); they are run through `c++filt -t`
when it is available, since an unreadable name defeats the grouping.

Caveat before trusting a non-zero count: an address freed and then reused by the
allocator looks like two allocations of the same pointer, so pointers are tracked as a
running balance rather than a set. A *negative* balance -- more frees than allocations
-- is the pathology worth acting on (a double free, or a pointer freed through the
wrong type) and is reported separately from an ordinary leak.
"""
import argparse
import collections
import re
import shutil
import subprocess
import sys

# "returned Foo: 0x...", "deleting Foo: 0x...", "allocated Foo: 0x..."
# A null pointer prints as a bare "0", not "0x0" -- accept it so those lines don't
# inflate the unparsed count and make a healthy trace look half-unreadable.
LINE = re.compile(r'^(?P<verb>\w+(?: \w+)?) (?P<cls>[^:]+): (?P<ptr>0x[0-9a-f]+|0)\s*$')

# `deleted' is the second trace of the same del() call as `deleting' -- counting both
# would report every object as double-freed.
ACQUIRE = {'returned', 'allocated', 'Duplicate string'}
RELEASE = {'deleting', 'Freeing string'}
# `Duplicating string'/`Freed string' are the leading halves of the same DUP()/qlFreeString()
# pairs whose `Duplicate string'/`Freeing string' halves are counted above -- same reason
# `deleted' is ignored. Without them here every string event inflates the unparsed count.
IGNORE = {'deleted', 'arg', 'Duplicating string', 'Freed string'}
# The verb that may legitimately go unpaired, when the pointer went into a shared_ptr.
SHARED = 'allocated'


def demangle(names):
    """Best-effort c++filt -t over a set of typeid() names; identity if unavailable."""
    names = sorted(names)
    tool = shutil.which('c++filt')
    if not tool or not names:
        return {n: n for n in names}
    try:
        out = subprocess.run([tool, '-t'], input='\n'.join(names), text=True,
                             capture_output=True, check=True).stdout.split('\n')
    except (subprocess.SubprocessError, OSError):
        return {n: n for n in names}
    if len(out) < len(names):
        return {n: n for n in names}
    # c++filt echoes anything it cannot demangle, so a failed name is just itself.
    return {n: (d.strip() or n) for n, d in zip(names, out)}


def parse(path):
    balance = collections.Counter()    # (cls, ptr) -> live count
    acquired = collections.Counter()   # cls -> acquisitions
    shared_only = {}                   # (cls, ptr) -> every acquisition was alloc()
    freed_kinds = set()                # classes something ever released
    unparsed = 0
    with open(path) as fh:
        for line in fh:
            line = line.rstrip('\n')
            if not line:
                continue
            m = LINE.match(line)
            if not m:
                unparsed += 1
                continue
            verb, cls, ptr = m.group('verb'), m.group('cls'), m.group('ptr')
            if verb in ACQUIRE:
                balance[(cls, ptr)] += 1
                acquired[cls] += 1
                key = (cls, ptr)
                shared_only[key] = shared_only.get(key, True) and verb == SHARED
            elif verb in RELEASE:
                balance[(cls, ptr)] -= 1
                freed_kinds.add(cls)
            elif verb not in IGNORE:
                unparsed += 1
    return balance, acquired, shared_only, freed_kinds, unparsed


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('trace', help='trace file written by QLTRACK_ALLOCATIONS')
    ap.add_argument('--only', help='comma-separated class-name substrings to report')
    ap.add_argument('--census', action='store_true',
                    help='also list the shared_ptr-owned payloads (never freed by design)')
    args = ap.parse_args()

    balance, acquired, shared_only, freed_kinds, unparsed = parse(args.trace)

    names = demangle(set(acquired) | {c for c, _ in balance})
    keep = args.only.split(',') if args.only else None

    def wanted(cls):
        return keep is None or any(k in cls or k in names[cls] for k in keep)

    leaked, overfreed, shared = (collections.Counter() for _ in range(3))
    for (cls, ptr), n in balance.items():
        if not wanted(cls):
            continue
        if n < 0:
            overfreed[names[cls]] += -n
        elif n > 0:
            # Unpaired, but expected if it only ever came from alloc() and nothing of
            # this kind is freed explicitly anywhere -- then a shared_ptr owns it.
            if shared_only.get((cls, ptr)) and cls not in freed_kinds:
                shared[names[cls]] += n
            else:
                leaked[names[cls]] += n

    total = sum(n for cls, n in acquired.items() if wanted(cls))
    kinds = len([c for c in acquired if wanted(c)])
    print(f'{total} tracked allocations across {kinds} classes')
    if unparsed:
        print(f'({unparsed} lines did not match the trace format and were skipped)')

    if overfreed:
        print('\nFREED MORE OFTEN THAN ALLOCATED (double free, or freed through the wrong type):')
        for cls, n in overfreed.most_common():
            print(f'  {n:6d}  {cls}')

    if leaked:
        print('\nSTILL LIVE AT EXIT:')
        for cls, n in leaked.most_common():
            print(f'  {n:6d}  {cls}')
    else:
        print('\nnothing leaked' + (' in the selected classes' if keep else ''))

    if args.census:
        print('\nshared_ptr-owned payloads (no explicit free is expected for these):')
        for cls, n in shared.most_common():
            print(f'  {n:6d}  {cls}')

    return 1 if (leaked or overfreed) else 0


if __name__ == '__main__':
    sys.exit(main())
