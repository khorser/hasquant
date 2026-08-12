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
| 3 GC liveness | ✅ pass | `smoke/CheckHandleGC.hs`, 3 checks |
| 4 Growth loop | ✅ pass | RSS flat 200 → 20000 iterations |
| 5 trackAllocations | ✅ pass | lifecycle events identical to baseline, line for line |
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

### F8. `Handle<YieldTermStructure>` now appears exactly once in `cbits/` — as an invariant

F6 established that all 76 explicit constructions were *harmless* (copy constructors). Leaving
them was still wrong, and this is the point the audit missed on the first pass:

`Handle<YieldTermStructure>(…)` is **the** spelling that creates a fresh, detached Link when its
argument is a `shared_ptr`. Keeping 76 instances of that spelling around — all benign — normalises
it. A future one that *is* a detachment would blend into the crowd, and caveat 1 says nothing else
can catch it: not the compiler, not a green build, not the test suite, not a crash.

So all of them were removed:

- 74 × `Handle<YieldTermStructure>(*arg(x))` → `*arg(x)`. The argument already *is* the handle;
  passing it through binds `const Handle&` directly instead of copy-constructing a temporary.
- 1 × `x ? Handle<YieldTermStructure>(*arg(x)) : Handle<YieldTermStructure>()` →
  `qlNullableHandle(arg(x))`, the one shared null-handling helper.
- 2 local `typedef Handle<YieldTermStructure> YieldTermStructureHandle;` in
  `qlTermStructure.cpp` (naming parameter types in the swap-index and ibor-index function-pointer
  tables) deleted, their 84 uses renamed to `QlYieldTermStructure`. A separate name now implies a
  distinction that no longer exists.

**The invariant, which is what makes this worth doing:**

```
grep -rn 'Handle<YieldTermStructure>' cbits/    # must return exactly one line:
cbits/qlaux.h:555:typedef Handle<YieldTermStructure> QlYieldTermStructure;
```

Any second hit is either a fresh Link (a caveat-1 detachment bug) or a redundant alias. This
turns caveat 1 from "audit 76 sites by hand" into "one grep", and belongs in CLAUDE.md.

Net effect on the diff: −2 lines. Verified after the change: `make` clean, 104 examples /
0 failures, liveness checks byte-identical (`0.9048374180359595`, `48911.41160693682`), growth
loop still flat (20.12 MB at N=200, 20.10 MB at N=20,000).

Credit where due: this was the user's catch, not the audit's.

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

### GC liveness (step 3) — pass

`smoke/CheckHandleGC.hs`, all three checks pass:

```
OK   derived curve outlives its dropped base       0.9048374180359595
OK   engine outlives its dropped curve             48911.41160693682
OK   a different curve gives a different NPV       2% and 5% flat curves must not price the same
```

Checks 1 and 2 build a curve inside a function that returns something *else* (a derived curve;
an engine), so no Haskell reference to the curve survives the return, then `performGC` twice and
read through the consumer, requiring the reference value **exactly**. Check 3 is the negative
control — a 2% and a 5% curve must not price the same — so a build where the two halves disagreed
about the parameter type could not pass on a coincidence.

### Growth loop (step 4) — pass, flat

Peak RSS of the whole process, N iterations each building and dropping a curve, a derived curve,
an engine and the upcast intermediates:

| N | Max RSS |
| --- | --- |
| 200 | 20.19 MB |
| 2,000 | 20.30 MB |
| 20,000 | 20.30 MB |

**100× the work for +0.6%, and byte-identical between 2,000 and 20,000.** No Link leak, no cycle
— which is the half `alloc-summary.py` structurally cannot see.

### trackAllocations (step 5) — pass, and stronger than "no new leaks"

Run on both builds with the flag, after `rm -rf .stack-work/dist/*/*/build/cbits` and with
`strings … | grep -c allocated` confirming tracing was actually compiled in (per CLAUDE.md — a
flag-only change does not rebuild `cxx-sources`, and an untraced run looks like a clean one).

**The two `alloc-summary.py` summaries are identical** (`diff` clean): 135,822 tracked allocations
across 157 classes in both, the same three pre-existing over-frees (`Calendar` ×9, `DayCounter`,
`Region`) and the same three still-live objects (`BespokeCalendar` ×2, `PolymorphicPathGenerator`)
on **both** builds. Those are pre-existing and unrelated to curves — established by running the
control, not by assuming it.

Event counts, line for line:

| Event | Baseline | Handle | Δ |
| --- | --- | --- | --- |
| `allocated` | 132,797 | 132,797 | 0 |
| `returned` | 3,023 | 3,023 | 0 |
| `deleting` | 135,065 | 135,065 | 0 |
| `deleted` | 135,065 | 135,065 | 0 |
| `arg` | 430,106 | 495,657 | +65,551 |

The object lifecycle is **unchanged**. The whole 7.8% trace growth is `arg()`, which is
pass-through and not a lifecycle event — it comes from the new `curvePtr`/`curveRef`/
`qlNullableHandle(Handle*)` helpers each calling `arg()` once.

---

## Verdict

**The prerequisite is met. `Handle<YieldTermStructure>` is on par with `shared_ptr` under Haskell
GC — indistinguishable on every metric measured.** Proceed with the implementation in
`relinkable-plan.md`.

Summary of the six plan concerns:

| Plan concern | Outcome |
| --- | --- |
| Exposure 1 — two heap objects per curve | Not detectable: RSS −0.2%, growth loop flat |
| Exposure 2 — GC mutating the observer graph | Closed analytically (F2): nothing is `-threaded`, C finalizers run inside GC, so a finalizer can never unregister an Observer during a QuantLib call |
| Exposure 3 — reference cycles | None: growth loop flat to 20,000 iterations |
| Exposure 4 — extra indirection | Not detectable, and smaller than assumed (F5): `operator->` chaining makes method calls compile identically |
| Upcast-intermediate lifetime | Safe: all four consumers store the Handle **by value** (F3) |
| Caveat 1 — silent detachment | Zero sites; all 76 constructions audited exhaustively (F6) |

### Carry into the implementation

- **Keep the spike's C++ diff** — it is the real thing, not a throwaway. `a94ed4d`.
- **Keep `curvePtr`/`curveRef`** (F7) — greppable derefs are caveat 1's only defence.
- **Add the F8 invariant to CLAUDE.md** as a standing constraint: `Handle<YieldTermStructure>`
  must appear exactly once in `cbits/`, in the `qlaux.h` typedef. Anything else is a fresh Link.
  This is the cheapest possible check for caveat 1 and the only one that scales.
- **Promote `smoke/CheckHandleGC.hs`'s liveness checks** into the test suite alongside the relink
  checks once the flag is dropped, per the plan's "Porting the relink checks". Keep the growth
  loop in `smoke/` — it takes an argument and is not a pass/fail assertion.
- **Note in CLAUDE.md** that F2's argument depends on nothing being `-threaded`; adding
  `-threaded` would reopen exposure 2 against a QuantLib built without
  `QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN` (F1).
- Still to do from the plan, untouched by this spike: the Haskell side
  (`RelinkableYieldTermStructure` as an `Upcastable` member of the `YieldTermStructure`
  hierarchy), `linkTo`/`currentLink`, dropping the flag, and the documentation upkeep.
