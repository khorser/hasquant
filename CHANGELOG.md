## 0.9.0.0 (2026)

- Breaking: `piecewiseDefaultCurve` returns a `PiecewiseDefaultCurve`, a
  `DefaultProbabilityTermStructure` leaf. Every curve argument still accepts it; convert with
  `asDefaultProbabilityTermStructure` where a concrete `DefaultProbabilityTermStructure` is
  stored. `defaultCurveNodes` reads its bootstrapped nodes: the reference date, then each
  helper's pillar, with the value its trait interpolates. The interpolated curve of that trait
  on these nodes is the same curve.

- Breaking: hazard shifts use `shiftedHazardRateCurve` and `HazardRateShift`.
  Replace `spreadedHazardRateCurve base q` with `shiftedHazardRateCurve base
  (ParallelHazardShift q)`, and `factorSpreadedHazardRateCurve base q` with
  `shiftedHazardRateCurve base (RelativeHazardShift q)`. Those cases retain their native
  numerical behavior; parallel queries now refuse negative or non-finite hazards.
  `KeyRateHazardShifts` and `BucketHazardShifts` add live linear and square
  spread shapes without re-interpolating the base curve; their survival correction uses
  QuantLib interpolation primitives. Shaped queries refuse negative or non-finite hazards.

- Breaking: `piecewiseBlackVarianceSurface` takes its nodes as `PiecewiseVarianceNodes` and an
  `extrapolate` flag. `VarianceGrid dates strikes vols` is the former rectangular grid;
  `VarianceSlices` gives each expiry its own (strike, volatility) nodes, so strike sets can differ
  between expiries. Pass `False` to keep the former behaviour. The surface's strike range is
  unbounded, so only this flag decides whether a section reads outside its strikes; the
  Haddock describes the domain a caller must check itself.
- Added `fxCashSpotQuote`, the cash value at the evaluation date of an FX spot quoted for
  settlement after a business-day lag. It is defined by hasquant rather than QuantLib, which
  has no quote observing yield curves, and it stays live in the spot, both curves, relinks and
  the evaluation date.
- Breaking: matrix inspectors are ordinary functions rather than record fields. Replace
  `m.matrixData` with `matrixData m` (and likewise for the other matrix inspectors), and import
  inspectors explicitly instead of through `Matrix(..)` or `RealMatrix(..)`. Construct a new
  matrix with the checked smart constructors instead of updating record fields.
- QuantLib 1.44 is the default for development, documentation and release builds; 1.43 remains supported.
- `QuantLib.Math` exports `Matrix` abstractly, with the `matrixRows`, `matrixColumns` and
  `matrixData` inspectors, so matrices processes return (`stdDeviation`, `covariance`,
  `diffusion`) can be read without `QuantLib.Internal`. Build one with `boxedRealMatrix` or
  `objectMatrix`, which check its shape.
- Breaking: `piecewiseZeroInflationCurve` and `piecewiseYoyInflationCurve` return the new
  `PiecewiseZeroInflationCurve` and `PiecewiseYoYInflationCurve` leaves, whose bootstrapped
  nodes `zeroInflationNodes` and `yoyInflationNodes` read. `ZeroInflationTermStructure` and
  `YoYInflationTermStructure` are now families (`GenZeroInflationTermStructure`,
  `GenYoYInflationTermStructure`): rate, implied-quote and index inputs accept either leaf, and
  `asZeroInflationTermStructure`/`asYoYInflationTermStructure` convert where a concrete type is
  stored.

## 0.8.0.0 (2026)

- Added value-based Settings snapshots with checked restoration, preserving floating dates
  and observer settings, and native fixing-history name normalization for context owners.
- Added QuantLib 1.44 support, while retaining compatibility with 1.43. New bindings include
  Rough Heston pricing, mark-to-market cross-currency basis swaps, FX reset cash flows, and
  Gaussian1d (GSR) swaptions on overnight-indexed swaps. Calls requiring 1.44, and non-default
  values of arguments added in 1.44, report `UnsupportedQuantLibVersion` on 1.43.
- Deprecated the `ItalyExchange` calendar, following QuantLib 1.44; it will be removed when
  hasquant adopts QuantLib 1.45. Use `TARGET` instead.
- `OvernightIndexedSwap` is now a `FixedVsFloatingSwap`; its fair-rate and fixed-leg inspectors
  come from the generic `FixedVsFloatingSwap` instances.
- Expanded term-structure and bootstrap-helper support, including dated helper constructors and
  implied-quote calculations on caller-supplied curves. Several existing constructor signatures
  changed to expose additional configuration.
- Extended model and engine support, including an exact-mean option for Heston–Hull–White pricing
  that avoids numerical failures in the upstream approximation. `analyticH1HwEngine` now requires
  an `H1HwMean` argument and rejects a negative equity/rate correlation with either integration control.
- Split Longstaff-Schwartz regression into `lsmFit` (basis coefficients) and `lsmEvaluate`, which
  reproduce `lsmRegress`/`lsmRegressMulti` bit for bit within one build; `lsmEvaluatorIdentity`
  names that build so stored coefficients can be refused elsewhere.
- Improved simulation and fixing inspection: `pathGeneratorSequence` exposes the random variates
  actually consumed, and inflation fixing dependencies now follow the dates and interpolation
  rules QuantLib uses.
- Improved callback validation, exception safety, and object ownership across the FFI, including
  a fix for a MultiCurve ownership cycle.

## 0.7.0.0 (2026)

The final broad API-coverage batch adds Haskell callbacks for payoffs, optimization, regression and
finite-difference workflows, wider pricing and curve support, index history analysis with the
matrix decompositions that feed PCA and correlation salvaging, a standalone SOFR-OIS exposure
example, and substantially more upstream-derived test coverage. Collections now
encode emptiness and numeric scale more precisely, and the C++ shims share more of their template
dispatch and allocation plumbing.

Many functions have been renamed and/or compacted where a single function accepts a sum type and
calls different internal functions depending on its arguments. The breaking rename is an attempt to make the API easier to explore and discover; the compact
API is still in flux.

Another breaking change is the removal of the `QuantLib.Syntax` module and its Template Haskell partial-call helpers.

## 0.6.0.0 (2026)

Rethought multiple inheritance for secondary interfaces (`AffineModel`, `Gaussian1dModel`): instead of a second `Upcastable` node, each leaf now gets a standalone, eagerly-materialized upcast (e.g. `hullWhiteAsAffineModel`). This traded a pure wrap at the call site for an explicit `IO`-sequenced conversion, so a few call sites that used to be pure functions are now `IO` actions — a small, deliberate cost for one fewer hand-rolled sum type per interface. Also generalized several accessor return types one `AnyOf` layer deeper (`SwaptionHelper`, `FixedVsFloatingSwap`) to keep them cast-free, and added a further batch of bindings: Gaussian1d model instruments/engines, YoY/CPI inflation vol surfaces and cap/floors, commodities, cross-currency swaps, and BlackAtmVolCurve/SabrVolSurface/OptionletStripper2.

## 0.5.0.2 (2026)

Support for RelinkableHandle has finally landed. As it turned out the current model is a perfect fit for it: term structures, quotes, and vol surfaces now relink uniformly, so building on top of a live quote or curve propagates updates correctly. Also removed all remaining `dynamic_cast` usage from the C++ shim in favor of dedicated typed bindings, and added a batch of further instrument/engine bindings (SABR vol cubes, Heston FD engines, CDS/counterparty engines, amortizing bonds, exchange rates, CMS legs, and more).
Added GitHub Actions to test various platforms and GHC versions.

## 0.4.0.0 (2026)

Extended the functionality, added more instruments and asset classes: equity index/cash-flow/total-return-swap, variance and compound options, zero-coupon swaps, further inflation-linked instruments, SABR smile sections, and several rate/vol-related bindings. Widened many existing constructors to their full upstream arity, and added Windows build support.

## 0.2.7.0 (2026)

Polished FFI helpers and reduced technical debt. Updated static data, added inflation.

## 0.2.6.0 (2026)

Finished migration to the new approach without explicit typeclasses — time to publish.

## 0.2.5.0 (2022)

Got rid of typeclasses, which required introducing more boilerplate and more manual marshalling to work around some C2HS shortcomings.

But now I'm able to avoid some dangerous extensions.

Revived allocation tracking in C++ code to ensure all objects are freed properly.

Restored Haddock comments on function arguments.

Without typeclasses, the inheritance can be expressed even better — if you don't look at the code underlying it ;)

E.g., you don't need to chain asXXX casts, and in most cases you don't need the casts at all.

As part of the effort, I generalized arguments (e.g., `GenBond a` instead of `Bond`).

Eventually, some typeclasses emerged again, but they're not visible to the end user.

## 0.2.0.0 (2021)

Migrated to C2HS, which actually resulted in more manageable code.

Typeclasses were used again to express inheritance relations and to use marshalling provided by C2HS.

Haddock comments on function arguments were lost in the process.

## 0.1.0.0 (2012-2013)

Initial implementation. Two projects: qlc (C part like wxcore) and quantlib.

The latter used Template Haskell to build code that marshalls data, given a foreign declaration and a function signature.

Tried to separate exceptions into two types: checked (via Either) and unchecked (IO).

Some ideas of handling C++ templates were taken from QuantLibXL.

All broke with the next Haskell release (7.8?), where you could no longer use TH to define a function when its signature is known (I used the signature to build the actual marshalling of arguments).

Heavy use of typeclasses to express inheritance (with lots of extensions used).

Due to some quirks in the interaction between TH and foreign code, I had to create a custom cabal `Setup.hs` because TH had to load my C code during compilation.

Some code was generated by scripts using Doxygen files.

``` haskell
  vanillaSwap :: VanillaSwapType -- ^type
    -> Double -- ^nominal
    -> Schedule -- ^fixedSchedule
    -> Double -- ^fixedRate
    -> DayCounter -- ^fixedDayCount
    -> Schedule -- ^floatSchedule
    -> IborIndex -- ^iborIndex
    -> Double -- ^spread
    -> DayCounter -- ^floatingDayCount
    -> BusinessDayConvention -- ^paymentConvention
    -> IO VanillaSwap
  vanillaSwap = $(ffiCall 'vanillaSwap) c_vanillaSwap -- automatic generation of marshalling code

  foreign import ccall safe "ql.h qlVanillaSwap"
    c_vanillaSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr CSchedule -> Ptr CIborIndex -> CDouble -> Ptr CDayCounter -> CInt -> Ptr CString -> IO (Ptr CVanillaSwap)
```
