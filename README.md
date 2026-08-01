This is a Haskell binding to a subset of [QuantLib library](https://www.quantlib.org/), a free/open-source library for quantitative finance.

I deliberately kept the API low-level to simplify its use in higher-level APIs.
The only exceptions are enums and ADTs used for some things implemented as classes in C++.

Examples can be found in `main/test/QuantLib/MainTest.hs` and `test/QuantLib/Example`.
Beware: I didn't try too hard to write idiomatic Haskell code there, just translated QuantLib examples.

For now, Haddock documentation is available at https://khorser.github.io/hasquant

# Building

The current version was tested with GHC-9.10.3 only, but it should work with relatively newer or older versions, since I deliberately avoided advanced language features.

Currently, only Linux and macOS are supported; Windows should be easy to support once I figure out the proper way to supply paths to custom libraries in cabal.

## Stack

Standard build with documentation: `stack build --haddock --no-test`

Run tests: `stack build --test --no-haddock`

Build and run examples: `stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`

Build and run examples enabling tracking of memory allocations (print all created and deleted objects to stderr):
`stack build --no-haddock  --flag hasquant:buildExample --flag hasquant:trackAllocations $* && stack exec hasquant_example`

Run GHCi: `stack ghci --ghci-options $(find .stack-work \( -name "*.so" -o -name "*.dylib" \) -print -quit)`

## Cabal

`cabal configure --disable-documentation && cabal build`

`cabal configure --enable-documentation && cabal build`

`cabal configure -f buildExample --disable-documentation && cabal build`

`cabal configure -f buildExample --enable-tests --disable-documentation && cabal build`

## Docker

The repo contains docker compose files for a custom Linux x86_64 image. You can use it like this:
`docker compose run --rm -it hasquant stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`

# On Types

I deliberately avoided typeclasses, as the code quickly becomes polluted by typeclass constraints.

## How to read types.

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
- Support Windows
- Add more
 - classes. You will need to update `cbits/qlaux.h`, `qlTypesC2HS.hs`, and then add some boilerplate to corresponding `.h`, `.cpp`, `Internal/Type.hs` and `.chs` files
 - methods. Since the last time I looked into it, QuantLib has added more interesting methods. It looks like a good task for an LLM.
 - method arguments. Some methods were refactored and updated to support more arguments. Particularly, look for TODO items in cbits.
- Add more nonempty lists or vectors for some functions where applicable
- Use some QuantLib handles for quotes and curves to support standard semantics
- Design a declarative embedded DSL
- Add HLS integration in Docker
- Add generic `ZeroInflationIndex`/`YoYInflationIndex` constructors (custom family name/`Region`/currency), not just the 8/7 pre-baked named indices (`UKRPI`, `EUHICP`, ...) added so far. `QuantLib.Index.Inflation`'s `Index -> InflationIndex -> {ZeroInflationIndex, YoYInflationIndex}` hierarchy was deliberately built as a real 3-level Haskell type hierarchy (mirroring `InterestRateIndex`), rather than collapsed into single-level leaves, specifically so this can be added later without restructuring. Would also need a `Region` binding (`ql/indexes/region.hpp`), currently unbound.
- `Pillar::Choice` is not exposed anywhere `BootstrapHelper`-derived helpers are bound (`RateHelper`s in `QuantLib.TermStructure.Yield`, and `ZeroCouponInflationSwapHelper`/`YearOnYearInflationSwapHelper` in `QuantLib.TermStructure.Inflation`) -- always uses the upstream default (`Pillar::LastRelevantDate`). Add a Haskell parameter if a caller ever needs `MaturityDate`/`CustomDate` pillars instead.
- Finish migration of following enums

```
QlPayoff | qlFreePayoff
QlPercentageStrikePayoff | qlFreePercentageStrikePayoff
QlPlainVanillaPayoff | qlFreePlainVanillaPayoff
QlBasketPayoff | qlFreeBasketPayoff
QlStrikedTypePayoff | qlFreeStrikedTypePayoff
QlTypePayoff | qlFreeTypePayoff

Payoff =
    DoubleStickyRatchet
      Double -- ^type1
      Double -- ^type2
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | ForwardType
      PositionType -- ^type
      Double -- ^strike
  | RatchetMax
      Double -- ^gearing1
      Double -- ^gearing
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | RatchetMin
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | Ratchet
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^initialValue
      Double -- ^accrualFactor
  | StickyMax
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | StickyMin
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | Sticky
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^initialValue
      Double -- ^accrualFactor
  | Type TypePayoff
  | Basket BasketPayoff
>TypePayoff =
  Striked StrikedPayoff
  | Floating
      OptionType -- ^type
>>StrikedPayoff =
  AssetOrNothing
    OptionType -- ^type
    Double -- ^strike
  | CashOrNothing
      OptionType -- ^type
      Double -- ^strike
      Double -- ^cashPayoff
  | Gap
      OptionType -- ^type
      Double -- ^strike
      Double -- ^secondStrike
  | PercentageStrike PercentageStrikePayoff
  | PlainVanilla PlainVanillaPayoff
  | SuperFund
      Double -- ^strike
      Double -- ^secondStrike
  | SuperSharePayoff
      Double -- ^strike
      Double -- ^secondStrike
      Double -- ^cashPayoff
>>>PercentageStrikePayoff = PercentageStrikePayoff
      OptionType -- ^type
      Double -- ^moneyness
>>>PlainVanillaPayoff = PlainVanillaPayoff
      OptionType -- ^type
      Double -- ^strike
>BasketPayoff =
    Average
      Payoff -- ^p
      Word -- ^n
  | AverageMultiple
      Payoff -- ^p
      [Double] -- ^a
  | Max
      Payoff -- ^p
  | Min
      Payoff -- ^p
  | Spread
      Payoff -- ^p

Exercise =
    AmericanExercise
      (Maybe Day) -- ^earliestDate
      Day -- ^latestDate
      Bool -- ^payoffAtExpiry
    | Early ExerciseType Bool
    | Vanilla ExerciseType
    | European EuropeanExercise
    | Bermudan BermudanExercise
>EuropeanExercise = EuropeanExercise Day
>BermudanExercise =
    BermudanExercise [Day] Bool
    | Swing SwingExercise
>>SwingExercise = 
    SwingListExercise [(Day, Word)] -- ^(dates, seconds)
    | SwingIntervalExercise Day Day Word -- ^stepSizeSecs

QlExercise | qlFreeExercise
QlAmericanExercise | qlFreeAmericanExercise
QlEuropeanExercise | qlFreeEuropeanExercise
QlBermudanExercise | qlFreeBermudanExercise
QlSwingExercise | qlFreeSwingExercise
```

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
  vanillaSwap = $(ffiCall 'vanillaSwap) c_vanillaSwap

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
