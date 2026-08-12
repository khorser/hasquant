# Draft comment for issue #1 ("Support MultiCurve")

Not posted — text staged here for review. Written against the `relinkable-handles`
branch (commits `6a6f5e8`..`f3c4daf`).

---

`RelinkableHandle` is **not** a prerequisite for sequential multi-curve, so the note on
this issue ("probably would need RelinkableHandle first") can be struck.

The self-referential part of bootstrapping is internal to C++: every rate helper owns a
private `RelinkableHandle<YieldTermStructure> termStructureHandle_`
(`ratehelpers.hpp:120,191,281,328,416`; `oisratehelper.hpp:120`) and clones its index
onto the curve being bootstrapped — there is nothing there for a binding to expose. And
upstream's own `MulticurveBootstrapping.cpp` never actually re-links: it makes exactly
two `linkTo` calls, each once, immediately after its curve is bootstrapped. That is
semantically `Handle<T>(shared_ptr)`, which every curve-taking binding here already
builds internally.

That is now demonstrated rather than argued: `test/QuantLib/Example/MulticurveBootstrapping.hs`
ports the upstream example — EONIA discount curve from deposits and dated/undated OIS,
then a Euribor 6M forecast curve whose swap helpers discount off it, then two swaps
priced on the pair — using **no new bindings**. It reproduces upstream's own assertion
that the 5-year swap reprices to the 5-year market quote it was bootstrapped from
(`|fairRate - 0.007620| < 1e-8`) at ~4e-13, and carries a negative control: the same
helpers with no discounting curve give a curve whose 5-year swap no longer reprices to
its own quote.

## Optional `RelinkableHandle` support has landed anyway

Separately from the above, relinking is a real capability that was missing, and for an
**index's forecast curve** there was no workaround at all — a swap clones its
`IborIndex` into every floating coupon at construction, so changing the forecast curve
meant rebuilding every instrument. (The discount curve was already swappable via
`setPricingEngine`.)

So `flag(relinkableHandles)` (default **off**) adds `RelinkableYieldTermStructure`,
`linkTo`/`currentLink`, and `H`-suffixed siblings of the curve-taking functions:

- indexes — `iborIndexH`, `overnightIborIndexH`, `overnightIndexH`, `bmaIndexH`,
  `liborSwapIndexH`, `swapIndexH'`
- rate helpers — `swapRateHelperH`, `swapRateHelperH'`, `oisRateHelperH{,'}`,
  `oisRateHelperFullH{,'}`
- engines — `discountingSwapEngineH`, `discountingBondEngineH`

Existing signatures are untouched; the flag only ever *adds* entry points, so a
half-applied flag fails at link time rather than misbehaving at runtime. Build with
`cabal build --flag relinkableHandles` — `stack` does not re-run c2hs for this flag and
silently produces a flag-off library while reporting success.

The type is a two-level hierarchy (`YieldTermStructureHandle` with
`RelinkableYieldTermStructure` under it) precisely so `MultiCurve`'s external plain
handles will fit the same signatures with no redesign.

## What is actually still missing for multi-curve

Neither item involves handles:

1. **Basis and cross-currency curves.** `basisswapratehelpers.hpp` and
   `crosscurrencyratehelpers.hpp` are unbound
   (`tools/ql-methods-1.43.txt:2571-2588`), needed for tenor-basis and cross-currency
   bootstrapping.

2. **The cyclic `MultiCurve` class** additionally needs `GlobalBootstrap`, which is
   unbound (all 35 methods across `globalbootstrap.hpp`/`multicurve.hpp` unmarked at
   `tools/ql-methods-1.43.txt:8886-9047`). Cycle members must use a compatible
   bootstrap class; `IterativeBootstrap` will not do. `cbits/qlTermStructureAux.cpp`
   already carries 72 explicit `PiecewiseYieldCurve<...>` instantiations in 998 lines
   and never names a bootstrap type, so adding that dimension roughly doubles them.
   `MultiCurve::addBootstrappedCurve` also takes `shared_ptr<YieldTermStructure>&&` and
   documents that the curve "can not be used afterwards", which needs a consume-and-
   invalidate ownership pattern with no precedent in this codebase.
