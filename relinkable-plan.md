# Relinkable handles, take 2: make `QlYieldTermStructure` a `Handle`

Status: **plan only, nothing implemented.** Supersedes the H-sibling design currently on
`relinkable-handles`. Written 2026-08-12.

## The one-line change

```c
// cbits/qlaux.h:553
typedef shared_ptr<YieldTermStructure> QlYieldTermStructure;   // before
typedef Handle<YieldTermStructure>     QlYieldTermStructure;   // after
```

Everything below is consequence and verification.

## Why this beats what is on the branch now

The shipped design adds an `H`-suffixed sibling per consumption point: a separate `extern "C"`
function taking `QlYieldTermStructureHandle*`, plus a separate `{#fun#}`, both inside
`#ifdef QL_RELINKABLE_HANDLES`. It works, and it is additively gated so a half-applied flag is
a link error rather than a silent pointer-type mismatch. But it duplicates every signature it
touches, it forced `mkOISRateHelper`/`mkSwapRateHelper1` to exist so a 27-parameter enum-cast
list would not be hand-copied, and the H half is invisible to the test suite (which builds
flag-off), so only `smoke/` can see it.

Making the curve type itself a `Handle` removes the reason for any of that:

- **One C function per site.** No `#ifdef` in `cbits`, no duplicated parameter lists, the
  `mk*` factoring helpers go away.
- **One Haskell function per site, with its current signature.** `RelinkableYieldTermStructure`
  becomes a *member of the `YieldTermStructure` hierarchy*, so every existing
  `GenYieldTermStructure a` parameter accepts it through the ordinary `Upcastable` machinery.
  `iborIndex Euribor6M (Just curve)` and `iborIndex Euribor6M (Just h)` both compile, unchanged.
- **Net negative diff.** It deletes the H siblings, the `GenYieldTermStructureHandle` type, and
  the `cxx-options` half of the flag.
- **The compiler enumerates the work.** `Handle<T>` converts implicitly *from* `shared_ptr<T>`
  but not the reverse, so every site that genuinely needs a bare `shared_ptr` fails to build the
  moment the typedef changes. `make` produces the complete worklist; no hand-auditing of ~130
  call sites.

## Why it is sound (evidence, not assertion)

**Returns are fine.** The objection that killed this idea earlier — "changing the typedef breaks
every return position" — is wrong. `Handle<T>` constructs from a `shared_ptr<T>`
(`handle.hpp:79`, explicit) and `operator*` returns `const shared_ptr<T>&` (`handle.hpp:89`), so
a `Handle` serves both roles. Anywhere a bare `shared_ptr` is genuinely required, `*arg(x)`
recovers it.

**The hierarchy is tiny.** `YieldTermStructure` has exactly one subtype
(`FittedBondDiscountCurve`), two upcast shims touch it, 14 shim functions return it, there are
no containers of curves, and one finalizer. The full inventory is in "Mechanical worklist" below.

**The relinkable upcast is Link-preserving.**
`qlRelinkableYieldTermStructureAsYieldTermStructure(o) = ret(new QlYieldTermStructure(*arg(o)))`
copy-constructs a `Handle<YieldTermStructure>` from a `RelinkableHandle<YieldTermStructure>` —
same `T`, so it shares `link_`. This is byte-for-byte the existing
`qlRelinkableYieldTermStructureAsHandle`, already proven by `smoke/CheckRelinkable.hs` check 4.

**Cross-*level* handle conversion is impossible, and never needed.** `Handle<T>` has no
converting constructor from `Handle<U>`, and `Link` is a nested class of `Handle<T>`, so
`Handle<Derived>::Link` and `Handle<Base>::Link` are unrelated types. Any cross-level rewrap
makes a fresh Link and **silently detaches relinking** — no crash, no type error, an NPV that
never moves. This never bites here because `Handle<TermStructure>` appears nowhere in QuantLib's
headers and the Haskell `TermStructure` root binds only `referenceDate`/`maxDate`. Do not
introduce a `Handle<Base>` anywhere.

**Shim consumption is already handle-shaped.** Across the three `cbits` files with curve
parameters there are 45 `qlNullableHandle(...)` calls and 76 explicit
`Handle<YieldTermStructure>(...)` constructions. The only bare `arg(fwd)`/`arg(ts)` uses are
either already-`Handle` H variants or unrelated `Forward` instruments.

## PREREQUISITE — verify `Handle` ownership under Haskell GC before committing to this

**Decided: this gates the full implementation.** The claim to establish is not "it works" but
"it is *at least on par* with `shared_ptr`". Do this first, on a throwaway spike, before the
mechanical rewrite.

### The argument that it should be on par

Today: Haskell holds a `ForeignPtr` to a heap `shared_ptr<YieldTermStructure>`, finalized by
`qlFreeYieldTermStructure` (`delete`). A consumer copies the `shared_ptr`, so the refcount is
≥ 2 and Haskell dropping its reference merely decrements.

After: Haskell holds a `ForeignPtr` to a heap `Handle<YieldTermStructure>`, finalized the same
way. `Handle` owns a `shared_ptr<Link>`; `Link` owns the `shared_ptr<YieldTermStructure>`. A
consumer copies the `Handle`, so the Link refcount is ≥ 2 and Haskell dropping its reference
merely decrements. **Same shape, one level deeper**, and lifetime is strictly *longer*, never
shorter — the Link keeps the curve alive even when Haskell has dropped every reference to both.
`smoke/CheckRelinkable.hs` check 3 already demonstrates exactly this for the handle path.

### What is genuinely new, and must be measured

1. **Two heap objects per curve instead of one** (`Handle` + `Link`), plus one more per upcast
   intermediate. Allocation volume goes up on the default path for every user.
2. **Every curve's `Link` registers as an Observer of the curve** (`registerAsObserver = true`,
   the upstream default). QuantLib's Observer/Observable graph is raw-pointer-based with
   back-registration, and destruction unregisters. Haskell finalizers run at arbitrary times,
   possibly on the finalizer thread — so GC now mutates the observer graph *more often* than it
   does today. This is not a new class of hazard (today's finalizer can already destroy a
   `TermStructure` and unregister it), but the volume increases. QuantLib's observer pattern is
   not thread-safe unless `QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN` is set — **check whether the
   installed build defines it**, and note that this is a pre-existing exposure this change
   amplifies rather than creates.
3. **Reference cycles.** A `Link` owns its curve strongly. Upstream avoids the obvious cycle —
   a rate helper's `termStructureHandle_` links to the curve being bootstrapped via a
   `shared_ptr` with `null_deleter()`, precisely so the helper does not own the curve that owns
   it. Confirm that survives: if any path ends up with an *owning* handle back to a curve that
   transitively owns the handle, the curve never dies and the leak is invisible to every test.
4. **One extra indirection per curve method call.** `arg(o)->discount(…)` becomes
   `(*arg(o))->discount(…)`. Negligible per call, but curve evaluation is the bootstrapping hot
   path, so it is worth a runtime comparison rather than an assumption.

### How to verify

- **Liveness across GC on the *plain* path.** Extend the smoke coverage: build a curve, hand it
  to an engine, drop every Haskell reference, `performGC` twice, reprice, and require the
  correct value. Today the plain path has no such exposure (the consumer holds a `shared_ptr`
  copy directly); after this change it goes through a Link, so it needs its own check rather
  than relying on check 3, which only covers the relinkable path.
- **`trackAllocations` + `tools/alloc-summary.py`** over the full smoke suite and the test
  suite: no leaks, no over-frees. This is what the analyzer was built and hardened for. Note the
  `Link` is internal to C++ and never traced — only the `Handle` objects appear, as `ret()`/
  `del()` pairs — so the tool sees the Haskell-owned half and *cannot* prove the Link half.
  Cover that with the loop test below.
- **Growth loop.** Construct and drop many curves (and many upcast intermediates) in a loop with
  periodic `performGC`, and watch RSS. Flat means no cycle and no Link leak; monotonic growth is
  the signature of exactly the failure `alloc-summary.py` cannot see.
- **Before/after comparison, since "on par" is the bar:** peak RSS and wall time for
  `stack test --ta '--skip LONG'`, measured on the same machine on the spike branch and on `ai`.
  Record both numbers in the eventual commit message.
- **Upcast-intermediate lifetime audit.** `freeUpcast` deletes the upcast intermediate
  immediately after the consuming call returns. That is only safe if every consumer *copies* the
  `Handle` rather than storing a reference to it. QuantLib consistently takes
  `const Handle<T>&` and stores by value, and this is the same assumption `Ql*AsY` already makes
  for `shared_ptr` — but the assumption is now load-bearing for a second type, so spot-check the
  consumers this plan actually routes through it (`DiscountingSwapEngine`, `IborIndex`,
  `SwapRateHelper`, `OISRateHelper`).

**If any of this fails, stop.** The H-sibling design on `relinkable-handles` is a working
fallback and does not have exposure 1, 2 or 4 on the default path.

## Costs and caveats, accepted going in

### 1. The silent-failure mode: an NPV that never moves

This is the caveat that governs how everything else gets verified, so it is first.

A `Handle<T>` copy-constructed from another `Handle<T>` **shares** the `shared_ptr<Link>`; a
`Handle<T>` constructed from a `shared_ptr<T>` gets a **fresh** Link. Both are the same C++
type, the same size, the same ABI, and both are perfectly valid objects. Nothing distinguishes
them:

- **The compiler cannot.** Both constructions type-check. There is no attribute, no warning.
- **A green build cannot.** The symbol resolves either way.
- **The test suite cannot.** A detached Link still yields the *correct* value for the curve it
  was detached holding. Every pinned expected value in `main/test/QuantLib/Spec/` would still
  match to 1e-12. The suite computes each NPV once; detachment is only observable across a
  relink.
- **A crash cannot.** There is no dangling pointer — the fresh Link owns the curve properly. The
  program is memory-safe and wrong.

The entire observable symptom is: you call `linkTo`, and the NPV does not move. That is why
`smoke/CheckRelinkable.hs` is written as before/after comparisons with exact equality on the
"relink back" leg, and why its comments spell out what each check would look like on failure.
Any new consumption point that is supposed to track relinking needs the same treatment; a build
and a passing test suite prove nothing about it.

Two structural facts make this tractable rather than a 130-site verification problem:

- **`Handle(shared_ptr)` is `explicit`** (`handle.hpp:79`), so a fresh Link cannot be created by
  accident through an implicit conversion. Every detachment point is a place someone deliberately
  wrote `Handle<YTS>(...)` or dereferenced with `*`.
- **All ~130 Haskell call sites funnel through one marshaller** (`withYieldTermStructure` /
  `withMaybeYieldTermStructure`) and one upcast shim. There is a single code path to get right,
  so a handful of smoke checks genuinely cover it — unlike the H-sibling design, where each
  sibling was its own path.

There are exactly two *deliberate* detachment points in this plan, and both need a haddock note
saying so: `asTermStructure` (caveat 2) and `currentLink` (caveat 3).

A related and nastier variant: a detached Link may also be the *only* owner of the curve. Detach
it, drop the Haskell reference, let GC run, and the stale-value bug becomes a use-after-free.
This is why the growth loop and the GC liveness checks above are not optional extras.

### 2. `asTermStructure` loses the Link

`qlYieldTermStructureAsTermStructure` must deref to a `shared_ptr` (there is no
`Handle<TermStructure>` — see "Cross-*level* handle conversion" above), so `referenceDate` /
`maxDate` read through it are a snapshot: after a `linkTo`, a previously obtained
`TermStructure` still reports the old curve's dates. Surface is two methods and two call sites
(`main/test/QuantLib/Spec/TermStructure.hs:107,121`). Haddock note on `asTermStructure`, plus a
smoke check that pins the behaviour as intended rather than leaving it to be rediscovered as a
bug.

### 3. `currentLink` returns a snapshot

It hands back the curve the handle points at *right now*, rewrapped in a fresh Handle with its
own Link. That is the correct meaning of `currentLink`, but under the new design the result has
the same Haskell type as the handle itself, so the distinction is invisible at the call site —
`currentLink h >>= f` does not track relinks, `f h` does. Haddock must say this explicitly.

### 4. Observer topology changes on the default path

Every curve gains a `Link` that is both `Observer` (of the curve) and `Observable` (to
consumers), so notification chains get one hop longer and a curve with many consumers now fans
out through a single Link rather than registering each consumer directly. This is the standard
upstream configuration, so it is not exotic — but it changes when `LazyObject`s invalidate, and
therefore potentially how many times things recalculate. **The suite pins values, not recalc
counts, so a change here passes silently either way.** Known unknown, deliberately not covered.

### 5. Empty curves become representable

`discount` on a curve that is an empty handle throws where it was previously unreachable. Only
arises from `relinkableYieldTermStructure Nothing`. Note also that `Maybe YieldTermStructure`
now has two spellings of "absent" — `Nothing` and `Just <empty handle>` — which coincide in
behaviour because the shim maps `Nothing` to an empty handle anyway. Fine, but be deliberate
about it rather than surprised by it.

### 6. Not stageable

A typedef change is atomic: one commit, compiler-driven, no intermediate green state. That is a
feature relative to hand-editing 120 signatures, but there is no module-by-module rollout and no
partial landing.

### 7. Flag-off byte-identity is gone

It was a property held by construction (the flag only ever *added* symbols). It becomes a tested
property instead: pinned test values must not move. Weaker, but the pinned values are recorded
to ~1e-6 relative across every example, so the net is small.

## Mechanical worklist

Driven by `make`. Expect the compiler to find more than this list; that is the point.

### `cbits/qlaux.h`
- Change the typedef (line 553). Move the explanatory comment currently attached to
  `QlYieldTermStructureHandle` (lines 555-560) up to it.
- Delete `QlYieldTermStructureHandle` and its `#ifdef`. Keep
  `typedef RelinkableHandle<YieldTermStructure> QlRelinkableYieldTermStructure;` — it stays
  gated only if the flag survives (see "The flag" below).
- `qlNullableHandle` (line 1119) currently takes `shared_ptr<T>*`. Add/replace with the
  `Handle*` form: `p ? *p : Handle<T>()`. Keeps null handling in one place and avoids
  allocating for the `Nothing` case.

### `cbits/qlTermStructure.cpp` / `.h`
- 14 constructors returning `QlYieldTermStructure*` — wrap their `shared_ptr` in the new type:
  `qlFlatForward`, `qlPiecewiseYieldCurve`, `qlInterpolatedDiscountCurve`,
  `qlInterpolatedForwardCurve`, `qlInterpolatedZeroCurve`, `qlForwardSpreadedTermStructure`,
  `qlImpliedTermStructure`, `qlPiecewiseZeroSpreadedTermStructure`, `qlQuantoTermStructure`,
  `qlZeroSpreadedTermStructure`, `qlEquityIndexDividendCurve`,
  `qlEquityIndexInterestRateCurve`, `qlFittedBondDiscountCurveAsYieldTermStructure`,
  `qlYieldTermStructureHandleCurrentLink`.
- The 4 observer shims: `arg(o)->method(...)` → `(*arg(o))->method(...)`.
- `qlFittedBondDiscountCurveAsYieldTermStructure` (line 641): `Handle<YTS>(shared_ptr<FBDC>)`
  works by `shared_ptr` covariance plus the explicit ctor. Fresh Link, which is correct — a
  `shared_ptr`-backed curve has no Link to preserve.
- `qlYieldTermStructureAsTermStructure` (line 649): one extra star,
  `ret(new QlTermStructure(*(*arg(o))))`.
- **Delete** every `*H` function added by `a442d72` and `0c2c570`
  (`qlCreateIborH`, `qlIborIndexH`, `qlLiborH`, `qlDailyTenorLiborH`, `qlBmaIndexH`,
  `qlOvernightIborIndexH`, `qlOvernightIndexH`, `qlLiborSwapIndexH`, `qlSwapIndexH`,
  the six rate-helper H siblings) and the `mkOISRateHelper`/`mkOISRateHelper2`/
  `mkSwapRateHelper1` factoring helpers that only existed to serve them.
- Rename `qlRelinkableYieldTermStructureAsHandle` →
  `qlRelinkableYieldTermStructureAsYieldTermStructure`; body unchanged.
- `qlYieldTermStructureHandleCurrentLink` → `qlRelinkableYieldTermStructureCurrentLink`, and
  note in a comment that the returned curve is a **fresh Handle with its own Link** — a
  snapshot, not a tracking reference. Passing the relinkable handle itself is the tracking form.

### `cbits/qlPricingEngine.cpp` / `.h`
- 18 `qlNullableHandle` sites become `*arg(x)` (or the new nullable form).
- Delete `qlDiscountingSwapEngineH` and `qlDiscountingBondEngineH`.
- `DiscountingBondEngine(*arg(ts), ...)` at line 113 already reads correctly once `ts` is a
  Handle.

### `cbits/qlInstrument.cpp`
- 2 `qlNullableHandle` sites.

### `QuantLib/Internal/Type.hs`
- **Delete** `GenYieldTermStructureHandle`, `CYieldTermStructureHandle{,'}`,
  `peekYieldTermStructureHandle`, `withYieldTermStructureHandle`,
  `withGenYieldTermStructureHandle` and their exports (lines 355-365, 1185-1215).
- Add `CRelinkableYieldTermStructure'` as a member of the `YieldTermStructure` hierarchy:
  ```haskell
  instance Upcastable CRelinkableYieldTermStructure' where
    { type Base CRelinkableYieldTermStructure' = CYieldTermStructure'
    ; upcast = qlRelinkableYieldTermStructureAsYieldTermStructure }
  ```
  with `peekRelinkableYieldTermStructure` producing a
  `GenYieldTermStructure CRelinkableYieldTermStructure` (via the existing `AnyOf`/`newAnyOf`
  path used by every other hierarchy member).
- `withYieldTermStructure`/`withMaybeYieldTermStructure` keep their names and types; only the
  `Ptr CYieldTermStructure'` they hand out is now a `Handle*` on the C side. **No `.chs` file
  changes at all** for the ~130 existing marshaller uses.
- Update the `TermStructure` haddock ASCII tree (line ~1185) to list
  `RelinkableYieldTermStructure` under `YieldTermStructure`. Delete the separate
  `YieldTermStructureHandle` tree.
- Haddock note on `asTermStructure` about the snapshot semantics (cost 2 above).

### `QuantLib/TermStructure/Yield.chs`
- Keep `relinkableYieldTermStructure`, `linkTo`, `currentLink`. `linkTo`'s second argument is
  now a `GenYieldTermStructure a`, so the shim derefs: `arg(h)->linkTo(*arg(c))`.
- **Delete** the six rate-helper `*H` bindings added by `0c2c570` and the `#ifdef` around the
  imports they needed.
- `linkTo` is the one mutator; its haddock must say why it exists (it is the requested feature,
  and the API rules otherwise forbid new setters).

### `QuantLib/Index/InterestRate.chs`
- **Delete** all nine `*H` bindings added by `a442d72`.

### `QuantLib/PricingEngine.chs`
- **Delete** `discountingSwapEngineH`, `discountingBondEngineH`.

### The flag — **decided: drop it entirely**
`flag(relinkableHandles)` would gate three Haskell functions over an unconditional C++ base,
which does not earn a toggle. Remove:
- the flag declaration (`package.yaml:26-28`) and the regenerated `hasquant.cabal` half;
- the `cxx-options`/`cpp-options` condition block (`package.yaml:97-99`);
- every `#ifdef QL_RELINKABLE_HANDLES` in `cbits/` and every `#ifdef` in the `.chs` files.

Consequences, all good:
- The half-applied-flag hazard disappears — there is no flag to half-apply, so the additive
  gating rule that exists to mitigate it no longer applies to this feature.
- This feature leaves the `cxx-sources`-staleness trap documented in CLAUDE.md (which bites when
  only a *flag* changes and the C++ objects are not rebuilt).
- **Relinking becomes visible to the normal test suite.** Move the relink checks out of
  `smoke/CheckRelinkable.hs` into `main/test/QuantLib/Spec/TermStructure.hs` as a `describe`
  block, so they run on every `stack test` and in the lts-18.8 gate instead of only when someone
  remembers to build a smoke binary. Keep a reduced `smoke/CheckRelinkable.hs` for the
  stale-build guard specifically (the reason `smoke/` exists is that editing a C header without
  touching a `.chs` leaves the build silently stale, which `test/` cannot catch).
- `flag(trackAllocations)` is untouched.

## Verification

Step 0 is the GC/ownership prerequisite above; do not start the rewrite until it passes. Then,
in order — do not skip 1, it generates the worklist.

1. `make` — C++-only compile check. Iterate until clean. This is the exhaustive site finder.
2. `stack build --test --no-haddock` then `stack test --ta '--skip LONG'`.
3. **Pinned values must not move.** Every `Example` spec value is recorded to ~1e-6 relative;
   this is the replacement for byte-identical flag-off. Any movement is a bug, not noise.
4. The relink checks (now in the test suite, see "The flag") must all pass after a **clean** C++
   rebuild — `rm -rf dist-newstyle/*/build/cbits`, since neither cabal nor stack reliably
   rebuilds `cxx-sources` when only a header changes.
5. Re-run every `smoke/` script — they exercise curve construction and would catch a botched
   return-position conversion.
6. `hlint` clean, no new warnings.
7. GHC 8.10 gate, with the clean first (stale named volumes have produced false divergences):
   `docker compose run --rm hasquant sh -c 'stack --resolver lts-18.8 clean hasquant && stack build --resolver lts-18.8 --flag hasquant:buildExample --no-haddock && stack --resolver lts-18.8 test'`

### Porting the relink checks
The nine checks in `smoke/CheckRelinkable.hs` and — more importantly — their rationale comments
carry over almost verbatim; only the API spelling changes (`iborIndexH idx fwdH` →
`iborIndex idx (Just fwdH)`, etc.). With the flag gone they move into
`main/test/QuantLib/Spec/TermStructure.hs`. Time the block before deciding on a `(LONG)` label
— check 5 bootstraps three times. Keep all of:
- check 3 (ownership across GC — the handle and its curve are dropped and collected before
  repricing), and **add its plain-curve twin**, which is new exposure under this design;
- check 4 (the **forecast** curve: the case with no workaround, since a swap clones its
  `IborIndex` into every floating coupon);
- check 5's *relative* tolerance and the comment explaining why it differs from the
  exact-equality checks (relinking makes `IterativeBootstrap` re-solve, landing ~4e-13 from the
  first solve; the 2%-vs-5% signal is ~1e-3, nine orders clear).

Two new checks this design needs and the old one did not, both pinning a *deliberate* detachment
as intended behaviour rather than leaving it to be rediscovered as a bug:
- **`asTermStructure` snapshot** (caveat 2): read `referenceDate` through it, `linkTo` a curve
  with a different reference date, read again, assert it did **not** move.
- **`currentLink` snapshot** (caveat 3): same shape — a curve obtained via `currentLink` must
  not track subsequent relinks, whereas passing the handle itself must.

A reduced `smoke/CheckRelinkable.hs` stays behind for the stale-build guard specifically: `test/`
cannot catch a C header edit that leaves the generated code stale, which is the reason `smoke/`
exists at all.

## Documentation upkeep

- **CLAUDE.md:** delete the additive-gating bullet and the "**Flag-gated bindings must be
  verified with `cabal`, not `stack`**" bullet insofar as they are about `relinkableHandles` —
  both describe a flag that no longer exists. (Keep whatever in them applies to
  `trackAllocations`.) Rewrite the "Curves are normally passed as `shared_ptr` and wrapped into
  a `Handle` inside the shim" bullet under "API design": the new rule is the opposite — curves
  *are* handles, and passing a relinkable one is an ordinary hierarchy upcast, needing no
  sibling function. Add two standing constraints, both of which cost a session if rediscovered:
  the `Handle<Derived>`→`Handle<Base>` impossibility, and the silent-detachment failure mode
  (caveat 1) with the note that only a before/after relink comparison can detect it.
- **README:** delete the `relinkableHandles` flag section added by `d9b9541` and document
  relinking as an ordinary feature. Strike the `RelinkableHandle` item from `# TODO`.
- **`QuantLib/Internal/Type.hs`:** the ASCII trees, per above.
- **`tools/ql-methods-1.43.txt`:** `handle.hpp`'s `RelinkableHandle` ctor / `linkTo` /
  `currentLink` / `empty` stay marked bound.
- **`ISSUE-1-COMMENT.md`:** the analysis half (Part 1 — `RelinkableHandle` is *not* a
  prerequisite for multi-curve, evidenced by the ported example) stands unchanged. The design
  half must be rewritten for this approach. Still **not posted** — text staged for review.

## Branching

**Branch off `ai`, do not undo `relinkable-handles`.** Confirmed topology as of writing:

- `ai` tip is `095d921`, and has moved past what was merged into `relinkable-handles`. It
  already contains its own copies of the tracking work (`095d921`) and the example
  check-values coverage (`657b28d`), plus `eef53da "Simplify internal imports and exports"`
  which `relinkable-handles` does not have.
- Everything on `relinkable-handles` that this plan keeps is either already on `ai` or is one of
  three cherry-picks.

So:

```
git switch -c relinkable-handles-2 ai
```

Cherry-pick, in this order:
1. `f3c4daf` — the `MulticurveBootstrapping` example plus its `Spec/Examples.hs` block. Uses
   **no** flag-gated code, so it applies as-is. Expect a small conflict in
   `tools/alloc-summary.py` (the commit carries a 4-line tweak that `ai` already has); take
   `ai`'s.
2. `7496b18` — `ISSUE-1-COMMENT.md`. Applies clean; rewrite its design section afterwards.
3. `smoke/CheckRelinkable.hs` — **port by hand**, not cherry-pick. It is spread across three
   commits (`6a6f5e8`, `6475fbc`, `a442d72`, `0c2c570`) and every check needs its API spelling
   changed. Copy the file out first: `git show relinkable-handles:smoke/CheckRelinkable.hs`.

Leave `relinkable-handles` in place as the record of the H-sibling design; it is a working,
tested implementation and worth being able to diff against.

## Not in scope

- `GlobalBootstrap` (unbound; required for cyclic `MultiCurve`, `IterativeBootstrap` will not do).
- The `MultiCurve` class itself. Note it fits this design better than any alternative considered:
  its **external** handles are plain `Handle`s, which *are* `YieldTermStructure` now, and its
  **internal** handles are `RelinkableYieldTermStructure`. Both are accepted everywhere with no
  signature change.
- `basisswapratehelpers.hpp` / `crosscurrencyratehelpers.hpp` — the actual remaining
  construction gap for issue #1, unrelated to handles.
- Posting the issue #1 comment (outward-facing; the user's call).

## Rejected alternatives, and why

Recorded so they are not re-derived.

- **Phantom types alone.** Already in use where they work (`GenYieldTermStructureHandle h`
  accepting both handle kinds). Cannot go further: curve-vs-handle differ at the C ABI, not at
  the type level.
- **ADT / GADT adaptor at each call site** (`Fixed curve` / `Linked handle`, the `AffineModel`
  pattern). Makes the wrapper mandatory at every call site — the thing explicitly ruled out.
- **Typeclass `IsCurve c => ... -> Maybe c -> ...`.** Source-compatible for `Just curve`, but
  every bare `Nothing` at a curve position becomes ambiguous, and it is a public typeclass
  constraint, which the API rules push against.
- **`data Curve r where Fixed :: … -> Curve 'False; Linked :: … -> Curve 'True`** (phantom-indexed
  GADT, consumers polymorphic and unconstrained in `r`). Genuinely good — source-compatible
  including bare `Nothing`, and `linkTo :: Curve 'True -> …` is statically safe. Rejected for
  three reasons: a `Bool` index is one state short for MultiCurve (it conflates "handle-backed"
  with "relinkable", but MultiCurve's external handles are marshal-as-handle/no-`linkTo`); the
  migration is all-or-nothing or else carries a silent-snapshot footgun on unconverted sites;
  and it puts a type-level index in every public curve signature, reversing CLAUDE.md's
  "concrete, dedicated types even at the cost of a few near-duplicate functions". The `Handle`
  typedef gets the same single-type property with none of these.
- **Unifying the C parameter type only, keeping plain + `H` Haskell siblings.** A strict subset
  of this plan (it is the same C-side change) that keeps the Haskell duplication for no benefit.
