## 0.8.0.0 (2026)

Adds the remaining comparable term structures: piecewise forward-spreaded curves, bootstrapped
spread yield curves (`SpreadBootstrap`), interpolated simple-zero and zero-inflation curves, the
ZABR swaption volatility cube, and Gaussian one-factor implied swaption volatilities.

Breaking change: `piecewiseZeroInflationCurve`, `piecewiseYoyInflationCurve` and
`interpolatedYoyInflationCurve` take a `Maybe Seasonality` before the interpolation, supporting
multiplicative and Kerkhof price seasonality at construction.

GSR gains piecewise reversions: `gsrWithReversions` pairs a reversion with each volatility step,
`calibrateReversionsIterative` fits them one helper at a time, and `reversions` reads them back.
The `qlGsr` shim now takes a reversion array; `gsr` keeps its single-reversion signature.
`markovFunctional` accepts any swaption volatility structure, such as a `SwaptionVolatilityMatrix`.

On QuantLib 1.43, `gaussian1dSwaptionVolatility` works around an uninitialized `MakeSwaption`
nominal by pricing its smile sections with a unit nominal; newer versions use upstream directly.
`extendedBlackVarianceSurface` reports an exception on QuantLib 1.43 instead of invoking its
out-of-bounds implementation.

`rateHelperFixingDependencies` now reads the cross-currency helpers' legs instead of reporting
`Nothing`. Overnight-index and SOFR futures helpers used to report `Just []`, although they read
past fixings once their reference period has started. From two weeks before that start they now
report `Nothing`, because QuantLib keeps their future private. A helper type the walk has no case
for now reports `Nothing` too, instead of `Just []`. On QuantLib 1.44 the walk also reads the
overnight-overnight basis and overnight-indexed funding helpers through their `swap()`.

Breaking change: `depositRateHelper` takes a `DepositTerms`, the way `fraRateHelper` takes a
`FraTerms`, and `depositRateHelperFromIndex` is gone. `DepositTenor` holds the former explicit
arguments, and `DepositFromIndex` holds the index. The new `DepositOnFixingDate` binds QuantLib's
fixed-date deposit. `FraTerms` gains `FraImmOffsets`, a FRA between two IMM dates after spot, and
`FraBetweenDates`, the fixed-date FRA. The two fixed-date forms are the only deposit and FRA
helpers that read a stored fixing, once their fixing date has passed. `rateHelperFixingDependencies`
reports that fixing from the day after it, for the FRA only with an indexed coupon.

Breaking change: `swapRateHelper` takes a `SwapRateTerms`, and `swapRateHelperFromConventions` is
gone. `SwapRateFromIndex` holds the former `swapRateHelper`'s swap index and forward start.
`SwapRateTenor` holds the former explicit conventions, forward start, settlement days and float
convention. The new `SwapRateBetweenDates` binds QuantLib's swap between two fixed dates. The
arguments every form shares follow the terms: spread, discounting curve, pillar, custom pillar
date, end of month, indexed coupons and pricer.

Breaking change: `oisRateHelper` and `oisRateHelperWithOptions` take an `OisTerms` first, where
`OisTenor` holds the former settlement days, tenor and forward start and `OisBetweenDates` holds
the former `oisRateHelperBetweenDates` dates. `oisRateHelperBetweenDates` and
`oisRateHelperBetweenDatesWithOptions` are gone. Likewise `fxSwapRateHelper` takes an
`FxSwapTerms`: `FxSwapTenor` holds the tenor, fixing days, calendar, convention, end of month and
trading calendar, and `FxSwapBetweenDates` holds the former `fxSwapRateHelperBetweenDates` dates.

Breaking change: `zeroCouponInflationSwapHelper` and `yearOnYearInflationSwapHelper` take an
`InflationSwapPeriod` where they took the maturity: `InflationSwapToMaturity` is the former
form, and the new `InflationSwapBetweenDates` binds QuantLib's swap between two fixed dates.
Both helpers used to interpolate linearly whatever they were given: their shim read
`CPIFlat`, which is 1, as linear. `CPIFlat` now gives flat observation.

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
