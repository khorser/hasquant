## 0.7.0.0 (2026)

The headline delivery is Haskell callbacks reaching into QuantLib's hot loops instead of stopping at the FFI boundary: `qlLsmRegress`/`lsmRegressMulti` let a Haskell-defined payoff drive Longstaff-Schwartz regression (single-asset and basket), `qlOptimize` hands `CostFunction`/`OptimizationMethod` to a Haskell-side objective, and `FdmBackwardSolver` rollback (`fdmRollback`) exposes the operator and step-condition per timestep as Haskell-driven callbacks, with `FdmInnerValueCalculator` (`fdmSolve`) going one step further to callback per grid node. Each is backed by a worked example (`AmericanLSM`, `HaskellLSM` — which benchmarks `lsmRegress` against a hand-rolled Haskell regression, `Fdm`) rather than just a binding.

Also finished issue #20's SWIG-parity pass in the FD area (`Glued1dMesher`, `FdmInnerValueCalculator`'s native subclasses), generalized `HistoricalRatesAnalysis` to any index with the full risk-statistics surface, exposed `StatisticsTrait` across the remaining MC pricing engines, and added a `QuickStart` example (an OIS swap priced off a hardcoded zero curve) as the README's front door. `app/SofrXva` grew into a real standalone SOFR-OIS exposure-profile executable, with CVA/DVA and a PFE percentile overlay on the NPV plot. An HPC coverage report now publishes alongside Haddock. ~1500 constructors/methods bound, up from ~1300.

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
