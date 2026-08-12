# Spike: does `Handle<YieldTermStructure>` behave under Haskell GC on par with `shared_ptr`?

Executes the **PREREQUISITE** section of `relinkable-plan.md`. That section states the bar:
not "it works" but "**at least on par** with `shared_ptr`". This file is the running record —
findings go in as they land, so an interrupted session can resume without re-deriving anything.

Started 2026-08-12 on `relinkable-handles-2` @ `d96a113`.

**Verdict so far: not yet reached.** See "Results" at the bottom.

---

## Findings already established (no spike build needed)

These close plan items analytically. Recorded here so they are not re-measured.

### F1. QuantLib's thread-safe observer pattern is OFF in this build

`/opt/homebrew/include/ql/config.hpp:65` — `/* #undef QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN */`.
So `observable.hpp` takes its non-thread-safe branch (`observable.hpp:54`).

### F2. …which does not matter, because nothing here is concurrent

This is what closes **plan exposure 2** ("GC now mutates the observer graph more often").

- **No `-threaded` anywhere.** `hasquant.cabal` has three `ghc-options` lines (90, 159, 210 —
  library, exe, test) and none carries it; `package.yaml` never mentions it. `smoke/` binaries
  are built with a plain `cabal exec -- ghc` invocation, also non-threaded.
- **Finalizers are C `FinalizerPtr`s**, attached via `newForeignPtr finalize`
  (`QuantLib/Internal/Type.hs:25,364`), not `Conc.newForeignPtr`/`addFinalizer`. GHC runs C
  finalizers inside the GC itself, not on the Haskell finalizer thread.

In a non-threaded RTS the GC cannot run while a foreign call is in progress, so a finalizer can
never unregister an Observer *during* a QuantLib call. The extra volume of graph mutation is
therefore irrelevant: it is the same guarantee the codebase relies on today, just exercised
more often. **Exposure 2 is closed by construction.** (It would reopen if anything ever adds
`-threaded`; note that in CLAUDE.md when the change lands.)

### F3. Every consumer stores the handle BY VALUE

This closes the plan's **upcast-intermediate lifetime audit**: `freeUpcast` deleting the upcast
intermediate right after the consuming call returns is safe, because the consumer has already
copied it (and thereby co-owns the Link). Verified in the installed headers:

| Consumer | Member declaration |
| --- | --- |
| `DiscountingSwapEngine` | `Handle<YieldTermStructure> discountCurve_;` (`discountingswapengine.hpp:51`) |
| `IborIndex` | `Handle<YieldTermStructure> termStructure_;` (`iborindex.hpp:66`) |
| `SwapRateHelper` | `Handle<YieldTermStructure> discountHandle_;` (`ratehelpers.hpp:285`) |
| `OISRateHelper` | `Handle<YieldTermStructure> discountHandle_;` (`oisratehelper.hpp:122`) |

Constructors take them by value or `const&` and store by value. No consumer retains a reference
to the caller's `Handle`.

Incidental confirmation of the plan's Part 1 analysis: the rate helpers hold their own private
`RelinkableHandle<YieldTermStructure> termStructureHandle_` (`ratehelpers.hpp:120,191,281,328,416`;
`oisratehelper.hpp:120`) — the bootstrap self-reference is internal to C++, nothing to bind.

### F4. `Handle(shared_ptr)` is `explicit`, both overloads

`handle.hpp:81,84` — the `const&` and `&&` forms are both `explicit`. So a fresh (detached) Link
can never arise from an implicit conversion; every detachment is somewhere a person deliberately
wrote `Handle<YTS>(...)`. This is the structural fact that makes caveat 1 tractable.

---

## Ordered steps

Each step gates the next. **If any fails, stop** — the H-sibling design on `relinkable-handles`
is a working fallback without exposures 1, 2 or 4 on the default path.

### Step 0 — Baseline, measured BEFORE any edit ⬅ current

Baseline on `d96a113`, **not** on `ai`: `relinkable-handles-2` carries the Multicurve example,
so `ai` is not apples-to-apples.

Measure the built test binary directly, not via `stack test` — otherwise peak RSS is stack's,
not the program's:

```
BIN=.stack-work/dist/aarch64-osx/ghc-9.10.3/build/hasquant_test/hasquant_test
/usr/bin/time -l $BIN --skip LONG 2>&1 | tail -20     # darwin: -l gives max RSS
```

Wall time 3× for stability. Record max RSS and the three wall times below.

### Step 1 — The typedef spike

Scratch branch off `relinkable-handles-2`. **Not actually throwaway**: this base never had the
H-sibling commits, so the worklist's *deletion* items (H siblings, `GenYieldTermStructureHandle`,
the `#ifdef`s, `mk*` helpers) do not exist here. What remains *is* most of the real
implementation's C++ half — commit it and keep it if the measurements pass.

Scope, per the plan's mechanical worklist minus the deletions:

- `cbits/qlaux.h:551` — the typedef.
- `cbits/qlaux.h:1119` — `qlNullableHandle` gains its `Handle*` form (`p ? *p : Handle<T>()`).
- 14 constructors returning `QlYieldTermStructure*` — wrap the `shared_ptr`.
- 4 observer shims — `arg(o)->m()` → `(*arg(o))->m()`.
- `qlYieldTermStructureAsTermStructure` — one extra star.
- `qlNullableHandle` call sites: 18 in `qlPricingEngine.cpp`, 2 in `qlInstrument.cpp`.

Expect **zero `.chs` changes** — `withYieldTermStructure`/`withMaybeYieldTermStructure` keep
their names and types.

Drive it with `make` (fast, C++ only, and its deps list `qlaux.h` explicitly so it is not
subject to the staleness trap below). Iterate until clean.

### ⚠ The trap that will bite in step 2

The typedef changes the **ABI of every function touching curves**, and it is a header-only edit.
CLAUDE.md already documents that neither cabal nor stack reliably rebuilds `cxx-sources` when
only a header changes. A partial rebuild links `shared_ptr`-shaped objects against `Handle`-shaped
callers: no error, silent garbage — precisely the failure class this spike exists to rule out.

**So: `rm -rf .stack-work/dist/*/*/build/cbits` before every Haskell build in this spike, and
treat any odd number as stale-first, bug-second.**

### Step 2 — Pinned values must not move

`stack build --test --no-haddock` then `stack test --ta '--skip LONG'`. Every `Example` spec
value is recorded to ~1e-6 relative. **Any movement is a bug, not noise** — this is the
replacement for the flag-off byte-identity property the plan gives up (caveat 7).

### Step 3 — Plain-path GC liveness

New exposure under this design: today the consumer holds a `shared_ptr` copy directly, so there
is nothing to check; afterwards it goes through a Link. `smoke/CheckRelinkable.hs` check 3 covers
only the *relinkable* path, so this needs its own script.

Shape: build a curve → hand it to an engine → drop every Haskell reference → `performGC` twice →
reprice → require the correct value.

### Step 4 — Growth loop (the one thing `alloc-summary.py` cannot see)

The Link is internal to C++ and never traced — only `Handle` objects appear, as `ret()`/`del()`
pairs. So the analyzer sees the Haskell-owned half only, and a Link leak or a reference cycle is
invisible to it. Cover it by construction volume instead:

Construct and drop many curves *and* many upcast intermediates in a loop, `performGC`
periodically, print RSS every k iterations. Flat = no cycle, no Link leak. Monotonic growth is
the signature of exactly the failure mode the analyzer is blind to.

Cycle risk to keep in mind while reading the result: a `Link` owns its curve strongly. Upstream
avoids the obvious cycle by linking a rate helper's `termStructureHandle_` to the curve being
bootstrapped through a `shared_ptr` with `null_deleter()` — deliberately non-owning. If any path
ends up with an *owning* handle back to a curve that transitively owns the handle, nothing dies
and no test can see it.

### Step 5 — `trackAllocations` + `tools/alloc-summary.py`

Over the smoke scripts and the test suite: no leaks, no over-frees.

**Confirm tracing is actually compiled in before trusting an empty trace** (CLAUDE.md): flag-only
changes do not rebuild `cxx-sources`, and the failure is silent. `strings <built .o> | grep -c
allocated` must be nonzero. Delete the whole `build/cbits` directory to force it — `touch` and
deleting individual `.o`s were both found insufficient.

Trace destination via the `QLTRACK_ALLOCATIONS` env var; no recompile needed to redirect.

### Step 6 — After-numbers, same method as step 0

Peak RSS and wall time, same binary-level measurement, same machine. "On par" is the bar; record
both numbers in the commit message.

Plan exposure 4 (one extra indirection per curve method call, `arg(o)->discount(…)` →
`(*arg(o))->discount(…)`) is what the wall-time half is for — curve evaluation is the bootstrap
hot path, so it gets measured rather than assumed.

---

## Results

| Step | Status | Notes |
| --- | --- | --- |
| F1–F4 | ✅ closed | Exposure 2 and the upcast-lifetime audit closed analytically |
| 0 Baseline | ✅ done | 185.3 MB / 44.10e9 instr |
| 1 Typedef spike | ✅ done | 3 files, +40/−24, **zero `.chs` changes** |
| 2 Pinned values | ✅ pass | 101 skip-LONG and 104 full, 0 failures, no value moved |
| 3 GC liveness | not started | |
| 4 Growth loop | not started | |
| 5 trackAllocations | not started | |
| 6 After-numbers | ✅ pass | RSS −0.2%, instructions −0.1% — both inside noise |

### F5. The typedef spike came out far smaller than the worklist implied

`cbits/qlaux.h`, `cbits/qlTermStructure.cpp`, `cbits/qlInstrument.cpp` — **+40/−24, and no `.chs`
file changed at all**, confirming the plan's central claim that
`withYieldTermStructure`/`withMaybeYieldTermStructure` keep their names and types.

Three predicted work items turned out to be **no-ops**, and the reason is worth keeping:

- **The 4 observer shims needed no change.** `(*arg(o))->discount(…)` already works, because C++
  chains `operator->` until it yields a raw pointer: `Handle::operator->` returns
  `const shared_ptr<T>&`, whose own `operator->` then yields `YieldTermStructure*`. The
  expression is identical for both types. The plan's "one extra star" was only needed where a
  `YieldTermStructure&` or a `shared_ptr` is passed *as an argument*, not where a method is
  called through it.
- **`qlPricingEngine.cpp` needed no change at all** — all 18 of its curve uses go through
  `qlNullableHandle`, so the new `Handle*` overload absorbed them.
- **All 76 `Handle<YieldTermStructure>(...)` constructions were already correct** (below).

What did need editing: 12 argument-position derefs in `qlInstrument.cpp` (`BondFunctions::` /
`CashFlows::` free functions), 10 return-position wraps in `qlTermStructure.cpp` where
`alloc()` hands back a **raw** pointer that `Handle` has no constructor for, and
`qlYieldTermStructureAsTermStructure`.

### F6. Zero silent-detachment sites exist — caveat 1 audited exhaustively

The governing risk (caveat 1: a fresh Link, same type, same ABI, no compiler or test can see it).
All **76** `Handle<YieldTermStructure>(…)` constructions across `cbits/` are one of:

- `Handle<YieldTermStructure>(*arg(x))` — with `x` a `QlYieldTermStructure*`, so `*arg(x)` is now
  a `Handle` and this is the **copy constructor**: Link shared, relinking propagates. ✅
- `Handle<YieldTermStructure>()` — a deliberate empty handle. ✅

Verified mechanically, not by eye: extracted every construction, checked none deviates from those
two forms, then resolved the declared parameter type of all 22 distinct identifiers involved.
Two (`ts`, `x0`) are reused across unrelated functions, so their five sites were resolved
individually — all `QlYieldTermStructure*`.

This is the payoff of the design: the sites that would have needed hand-checking became copy
constructions *automatically*, because the argument type changed underneath them.

The **one deliberate detachment** is `qlYieldTermStructureAsTermStructure`
(`qlTermStructure.cpp:627`, caveat 2), now written `curvePtr(arg(o))` so it is greppable rather
than a one-character difference.

### F7. Named accessors instead of star-counting

`*arg(h)`, `**arg(h)` and `***arg(h)` are all well-formed on a curve handle and mean three
different things — the wrong one inside a 200-character argument list *is* caveat 1. Added to
`qlaux.h` next to `qlNullableHandle`:

```c
template <class T> const shared_ptr<T>& curvePtr(Handle<T> *p) {return **arg(p);}
template <class T> const T& curveRef(Handle<T> *p) {return ***arg(p);}
```

Keep these in the real implementation. They make every deliberate deref greppable, which is the
only defence caveat 1 has.

### Baseline (step 0)

`d96a113`, `hasquant_test --skip LONG`, 101 examples / 0 failures, 3× on the same machine:

| Run | Wall (real) | Max RSS | Instructions retired |
| --- | --- | --- | --- |
| 1 | 3.24 s | 185,139,200 | 44,406,866,187 |
| 2 | 3.22 s | 185,434,112 | 43,686,718,416 |
| 3 | 3.21 s | 185,221,120 | 44,208,887,353 |
| **mean** | **3.22 s** | **185.3 MB** | **44.10e9** |

**Max RSS is the tight metric** — spread 0.16%, so a real regression from two heap objects per
curve instead of one would show clearly.

**Instructions retired is the right metric for exposure 4**, not wall time: it is measured
directly rather than inferred from a 3.2 s timer, though the spread here is 1.6% (GC scheduling),
so treat anything under ~2% as noise. Wall time is too coarse to resolve the extra indirection at
all and is recorded only as a sanity check.

### After (step 6)

Same binary-level method, same machine, same session. 101 examples / 0 failures.

| Run | Wall (real) | Max RSS | Instructions retired |
| --- | --- | --- | --- |
| 1 | 3.22 s | 184,860,672 | 43,991,443,506 |
| 2 | 3.22 s | 184,909,824 | 44,233,522,298 |
| 3 | 3.22 s | 184,975,360 | 43,997,274,524 |
| **mean** | **3.22 s** | **184.9 MB** | **44.07e9** |

**Verdict: on par, indistinguishable.**

| Metric | Before | After | Δ |
| --- | --- | --- | --- |
| Max RSS | 185.3 MB | 184.9 MB | **−0.2%** |
| Instructions | 44.10e9 | 44.07e9 | **−0.1%** |
| Wall | 3.22 s | 3.22 s | 0% |

Both deltas are *negative* and well inside the measured spread (0.16% RSS, 1.6% instructions), so
the honest reading is "no detectable difference", not "faster".

- **Exposure 1 (two heap objects per curve) does not register.** A `Link` is a few dozen bytes
  and the suite builds tens of curves, against a 185 MB footprint. Real, but ~4 orders of
  magnitude below the noise floor.
- **Exposure 4 (one extra indirection per curve method call) does not register either** — and
  F5 explains why it is even smaller than assumed: method calls through the handle compile to
  the *same* code via `operator->` chaining, so the extra indirection only exists at the
  argument-position sites, not in the bootstrap inner loop.

Full suite including LONG: 104 examples, 0 failures, 26.23 s (baseline 26.46 s).
