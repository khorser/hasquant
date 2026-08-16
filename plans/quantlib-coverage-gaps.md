# hasquant vs. QuantLib-Python: coverage gap analysis

Compares hasquant's current QuantLib bindings against what `QuantLib-Python-Docs`
(the SWIG Python binding's documentation) documents, to find and prioritise gaps
for a future binding roadmap. Sourced by cataloguing both sides independently,
then verifying every "possibly missing" item with a direct grep of `QuantLib/`
and `cbits/` (not just `tools/ql-methods-1.43.txt`'s status marks, which are
known unreliable at the per-overload level — see CLAUDE.md).

## Summary

hasquant's coverage is broad and in places deeper than the documented Python
surface — multi-curve bootstrapping, a wide exotic-option set, credit, and
inflation instruments all exceed what QuantLib-Python-Docs shows. But two
structural gaps stand out as high-value: no swaption volatility cube (only a
flat matrix), and no finite-difference Heston pricing engines. Below that is
a long tail of individually narrow items.

## Tier 1 — high-value gaps

| Item | Why it matters | Evidence |
|---|---|---|
| **Swaption volatility cubes** (`SwaptionVolCube1`, `SwaptionVolCube2`, SABR-based) | Central to any swaption/CMS desk workflow; the single biggest hole in the vol-surface coverage | hasquant only binds the flat `swaptionVolatilityMatrix'`; confirmed absent via grep of `QuantLib/`/`cbits/` |
| **FD Heston engine family** (`FdHestonVanillaEngine`, `FdHestonBarrierEngine`, `FdHestonDoubleBarrierEngine`, `FdHestonHullWhiteVanillaEngine`) | FD is the standard method for American/barrier payoffs under Heston; hasquant has analytic/MC Heston engines but no FD ones | Confirmed absent via grep |

## Tier 2 — medium-value gaps

- ~~**CMS leg builder and pricers**~~ — **closed.** This row was stale even when first written: `cmsLeg`/`cmsLegFull` (including caps/floors, i.e. `CappedFlooredCmsCoupon`) were already bound in `CashFlow.chs` by the time this doc was drafted, alongside `analyticHaganPricer`/`numericHaganPricer`. The one real remaining gap, `LinearTsrPricer`, is now bound too (`linearTsrPricer` in `CashFlow.chs`), and a `makeCms` convenience (in the `makeVanillaSwap` style — plain Haskell composing `schedule`/`cmsLeg`/`iborLeg`/`swap`, not a `MakeCms` C++ binding) is in `QuantLib/Instrument/Swap.chs`.
- `NonstandardSwap`/`NonstandardSwaption`, `FloatFloatSwap`/`FloatFloatSwaption` — needed for amortizing/accreting or dual-index swaps. Confirmed absent via grep.
- `Money` and `ExchangeRate`/`ExchangeRateManager` — foundational for multi-currency cashflow amounts, not just curve FX. Only `MoneyConversionType` (an enum tag) exists; no `Money` value type or FX-rate object. Confirmed absent via grep.
- `PartialTimeBarrierOption` + `AnalyticPartialTimeBarrierOptionEngine` — hasquant has `BarrierOption`/`DoubleBarrierOption` but not the partial-time variant. Confirmed absent via grep.
- `CmsRateBond` — a documented, real-world FRN variant. Confirmed absent via grep.
- `CustomIborIndex` (QL 1.39+) — user-defined Ibor conventions outside hasquant's fixed enum set. Confirmed absent via grep.
- Named swap-index conventions (`UsdLiborSwapIsdaFixAm/Pm`, `GbpLiborSwapIsdaFix`, etc.) — functionally covered already by the generic `liborSwapIndex`, so this is a convenience gap rather than a capability gap; medium-low.

## Tier 3 — low-value / niche gaps

- `OptionletStripper2`, ZABR smile section/model, CPI/YoY volatility surfaces (`CPIVolatilitySurface`, `YoYOptionletVolatilitySurface`) — real gaps but narrow audience.
- `TurnbullWakemanAsianEngine`, `FdBlackScholesAsianEngine`, forward-start option engines (`ForwardEuropeanEngine`, `MCForwardEuropeanBSEngine`, `AnalyticHestonForwardEuropeanEngine`), `AnalyticPTDHestonEngine` — each a single specific engine for an already-representable instrument; low breadth impact. Confirmed absent via grep.
- **Math-tools category as a whole** (standalone interpolation objects, 1-D root solvers, statistics/distribution classes, RNG/low-discrepancy sequence generators, a first-class `SABRInterpolation`/`Array` type) — extensively documented on the python side, essentially entirely absent as user-facing objects in hasquant (only reachable indirectly as enum-selected strategies inside curve/engine constructors). Ranked low deliberately: these are generic numerics with mature Haskell-ecosystem alternatives (`hmatrix`, `statistics`, `random`), not instrument/pricing coverage — this is a scope judgment, not an oversight.
- YoY inflation cap/floor/collar (`YoYInflationCap/Floor/Collar`), `FXImpliedCurve` — **low-confidence rows**: the python doc itself only stubs these (no documented signature), so they're weak evidence of real demand.
- `Cliquet`/`Quanto` option variants — **not actually gaps**: the python doc stubs them, but hasquant already has `cliquetOption` and the full `Quanto*` family (`quantoVanillaOption`, `quantoBarrierOption`, `quantoForwardVanillaOption`). Listed here only to flag that the python-doc stub should not be read as "unbound on both sides."

## Out of scope by design (not ranked)

These are python-documented items that CLAUDE.md's conventions deliberately exclude — listing them as gaps would contradict the project's own design rules:

- All `Make*` fluent builders (`MakeOIS`, `MakeSchedule`, `MakeCapFloor`, `Make*Engine`) — hasquant binds the underlying constructor directly instead. `makeVanillaSwap` is the one existing exception.
- `Period` as a dedicated type — deliberately marshalled as `(Int, TimeUnit)` throughout.
- `Handle`/`RelinkableHandle` as user-visible generic classes — handled internally via the `Upcastable`/`Handle` plumbing; `relinkable*` constructors cover the user-facing relinking need.
- `ConstNotionalCrossCurrencySwap` family — explicitly marked `x` (permanently excluded) in `tools/ql-methods-1.43.txt`.
- Plain-`Double` overloads of anything with a `Handle<Quote>` sibling — ruled out by the `std::variant<Real, Handle<Quote>>` collapsing convention.

## Where hasquant exceeds the python docs

- **Convertible bonds**: three real constructors (`convertibleFixedCouponBond`, `convertibleFloatingRateBond`, `convertibleZeroCouponBond`) vs. a python-doc stub with no signature.
- **ECB-date helpers** (`addECBDate`, `ecbCode`, `nextECBDate`, ...) — not documented on the python side at all.
- **Multi-curve bootstrap** (`multiCurve`/`addBootstrappedCurve`/`addNonBootstrappedCurve`) — no equivalent documented in QuantLib-Python-Docs.
- A wider bound exotic-option set (basket/himalaya/pagoda/margrabe/quanto-barrier) than what's documented in `instruments/options.rst`.

## Companion fix: `tools/ql-methods-1.43.txt` corrections

While cataloguing hasquant's actual bindings for this comparison, five status
marks in the tracking file were found to contradict what's really bound
(verified directly against `cbits/*.cpp` shims and `.chs` export lists, not just
trusted from the file) and corrected from `?` to `v`:

- `Cap`, `Floor`, `Collar` (`ql/instruments/capfloor.hpp`) — all three have exact-arity C shims (`qlCap`/`qlFloor`/`qlCollar` in `cbits/qlInstrument.cpp`) and are exported from `QuantLib/Instrument/CapFloor.chs`.
- `ConvertibleZeroCouponBond`, `CallableZeroCouponBond` — both have exact-arity shims (`qlConvertibleZeroCouponBond`, `qlCallableZeroCouponBond`) and are exported from `QuantLib/Instrument/Bond.chs`.

No cases were found in the other, more dangerous direction (a class marked `v`/`u`
that turns out to have no real shim) among the ~50 classes sampled for this task —
those sampled include every Tier 1-3 gap candidate above (all correctly marked
absent/unreviewed, none falsely `v`) and the classes CLAUDE.md already names as
previously having a stale Quote/plain-number mark (`FlatForward`,
`BlackConstantVol`, `LocalConstantVol`, `ConstantCapFloorTermVolatility`,
`ConstantOptionletVolatility`, `ConstantSwaptionVolatility`, `FlatHazardRate`,
`CallableBondConstantVolatility`, `BachelierCapFloorEngine`, `BlackCapFloorEngine`,
`BlackSwaptionEngine`, `BachelierSwaptionEngine`, `LocalVolSurface`,
`SabrInterpolatedSmileSection`, `Gsr`, `CounterpartyAdjSwapEngine`,
`SwaptionVolatilityMatrix`, `HestonModelHelper`) — all of which are already
correctly marked from prior sessions' fixes. This was a scoped pass over classes
touched by this comparison, not an exhaustive re-audit of the 10,739-line file.
