This is a Haskell binding to a subset of [QuantLib library](https://www.quantlib.org/), a free/open-source library for quantitative finance.

I deliberately kept the API low-level to simplify its use in higher-level APIs.
The only exceptions are enums and ADTs used for some things implemented as classes in C++.

Examples can be found in `main/test/QuantLib/MainTest.hs` and `test/QuantLib/Example`.
Beware: I didn't try too hard to write idiomatic Haskell code there, just translated QuantLib examples.

For now, Haddock documentation is available at https://khorser.github.io/hasquant

# Building

The current version was mostly tested with GHC-9.10.3, but it should work with newer or reasonably older versions (at least from 8.10.6), since I deliberately avoided advanced language features.

Linux and macOS are the primary, well-tested platforms. Windows builds are also possible, but the process currently involves several non-obvious toolchain workarounds — see [`.claude/skills/build-windows/SKILL.md`](.claude/skills/build-windows/SKILL.md) for the full, tested recipe if you want to try it.

## Stack

Minimal build: `stack build --no-haddock --no-test`

Run tests: `stack build --test --no-haddock`

Build and run examples: `stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`, also `--flag hasquant:buildExample` is required if you want to use HLS with examples.

Build and run examples enabling tracking of memory allocations (print all created and deleted objects to stderr):
`stack build --no-haddock --flag hasquant:buildExample --flag hasquant:trackAllocations $* && stack exec hasquant_example`

Run GHCi: `stack ghci --ghci-options $(find .stack-work \( -name "*.so" -o -name "*.dylib" \) -print -quit)`

## Cabal

Standard build: `cabal configure --disable-documentation && cabal build`

Build with documentation: `cabal configure --enable-documentation && cabal build`

Build example: `cabal configure -f buildExample --disable-documentation && cabal build`

Build example and tests: `cabal configure -f buildExample --enable-tests --disable-documentation && cabal build`

## Docker

The repo contains docker compose files for a custom Linux x86_64 image. You can use it like this:
`docker compose run --rm -it hasquant stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`

# On Types

I deliberately avoided typeclasses, as the code quickly becomes polluted by typeclass constraints.

## How to read types

If you see a function accepting `CallableBond`, you can pass only instances of callable bonds.
But if a function accepts `GenBond a`, you can pass a `Bond` or any of its derivatives: `FixedRateBond`, `ConvertibleBond`, `CallableBond`.
This works thanks to the following definition:
``` haskell
type Bond = GenBond CBond
type FixedRateBond = GenBond CFixedRateBond
type ConvertibleBond = GenBond CConvertibleBond
type CallableBond = GenBond CCallableBond
```

And if a function accepts `GenInstrument a` (like `npv`), you can pass any instrument at all.
While this is convenient, it leads to some allocation and deallocation on each call, so you might consider using `asBond` and `asInstrument` to get an object of the required type.

# TODO
- Publish on Hackage
- Add more (can be simplified with scripting/LLMs. Refer to `CLAUDE.md`, `.claude/skills`, and `tools` for more detailed information):
  - classes. You will need to update `cbits/qlaux.h`, `qlTypesC2HS.hs`, and then add some boilerplate to corresponding `.h`, `.cpp`, `Internal/Type.hs` and `.chs` files
  - methods. Since the last time I looked into it, QuantLib has added more interesting methods
  - method arguments. Some methods were refactored and updated to support more arguments. Particularly, look for TODO items in cbits
- Add more nonempty lists or vectors for some functions where applicable
- Use some QuantLib handles for quotes and curves to support native QuantLib semantics
- Design a declarative embedded DSL
- Add HLS integration in Docker
- `Pillar::Choice` is not exposed anywhere `BootstrapHelper`-derived helpers are bound (`RateHelper`s in `QuantLib.TermStructure.Yield`, and `ZeroCouponInflationSwapHelper`/`YearOnYearInflationSwapHelper` in `QuantLib.TermStructure.Inflation`) -- always uses the upstream default (`Pillar::LastRelevantDate`). Add a Haskell parameter if a caller ever needs `MaturityDate`/`CustomDate` pillars instead.
- `experimental/commodities`
- `experimental/termstructures`
- `shortratemodels` example: the two RelinkableHandle-dependent tests (`testHullWhiteUpdatesR0WhenTermStructureRelinks`, `testExtendedCoxIngersollRossUpdatesWhenTermStructureRelinks`) are not ported -- no `RelinkableHandle<YieldTermStructure>`/`linkTo` concept exists in hasquant; a separate, bigger project, not a small addition. The other 7 tests are ported in `QuantLib.Example.ShortRateModels`.
- `SwaptionHelper::underlying()` isn't exposed -- `swaptionHelper` currently collapses into the generic `BlackCalibrationHelper` type like `capHelper` does, but `underlying()` (-> `FixedVsFloatingSwap`/`VanillaSwap`) is declared only on `SwaptionHelper` upstream, not on `BlackCalibrationHelper` or `CapHelper` -- so there's nothing to unify via a shared typeclass. Give `SwaptionHelper` its own dedicated leaf type instead (justified now that it has a getter `capHelper` doesn't -- see `add-quantlib-class`'s leaf-type pattern, like `FxForward`), with `underlying :: SwaptionHelper -> IO VanillaSwap`; it still upcasts into `calibrate`'s existing `GenCalibrationHelper a` polymorphism, no new typeclass needed. Not needed by any currently-ported example.
- migrate `Gaussian1dModels` example from QuantLib -- needs a whole new model/instrument/engine family, not currently bound at all: swaption engines (`Gaussian1dNonstandardSwaptionEngine`, `Gaussian1dFloatFloatSwaptionEngine`), `NonstandardSwap`/`NonstandardSwaption` (incl. `calibrationBasket`/`BasketGeneratingEngine`), `FloatFloatSwap`/`FloatFloatSwaption`, `RebatedExercise`, `LinearTsrPricer`, and a generic `Instrument::additionalResults()`/`result<T>(name)` extraction mechanism (no analog exists in hasquant). Disproportionate in scope to a single example port -- worth its own project if wanted later.
- review interfaces for consistency, add obviously missing features and fix contradictions to the current design
- add CPIBondHelper, CPILeg, all inflation bonds and swaps

# Project History

## 0.1.0.0 (2012-2013)

Initial implementation. Two projects: qlc (C part like wxcore) and quantlib.

The latter used Template Haskell to build code that marshalls data, given a foreign declaration and a function signature.

Tried to separate exceptions into two types: checked (via Either) and unchecked (IO).

Some ideas of handling C++ templates were taken from QuantLibXL.

All broke with the next Haskell release (7.8?), where you could no longer use TH to define a function when its signature is known (I used the signature to build the actual marshalling of arguments).

Heavy use of typeclasses to express inheritance (with lots of extensions used).

Due to some quirks in the interaction between TH and foreign code, I had to create a custom cabal `Setup.hs`.

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

## 0.2.0.0 (2021)

Migrated to C2HS, which actually resulted in more manageable code.

Typeclasses were used again to express inheritance relations and to use marshalling provided by C2HS.

Haddock comments on function arguments were lost in the process.

## 0.2.5.0 (2022)

Got rid of typeclasses, which required introducing more boilerplate and more manual marshalling to work around some C2HS shortcomings.

But now I'm able to avoid some dangerous extensions.

Revived allocation tracking in C++ code to ensure all objects are freed properly.

Restored Haddock comments on function arguments.

Without typeclasses, the inheritance can be expressed even better — if you don't look at the code underlying it ;)

E.g., you don't need to chain asXXX casts, and in most cases you don't need the casts at all.

As part of the effort, I generalized arguments (e.g., `GenBond a` instead of `Bond`).

Eventually, some typeclasses emerged again, but they're not visible to the end user.

## 0.2.6.0 (2026)

Finished migration to the new approach without explicit typeclasses — time to publish.

## 0.2.7.0 (2026)

Polished FFI helpers and reduced technical debt. Updated static data, added inflation.
