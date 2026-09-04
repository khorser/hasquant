Haskell bindings to [QuantLib](https://www.quantlib.org/).

Supported functionality includes
- yield, credit, inflation, and volatility curves;
- IBOR, overnight, swap, and inflation indexes;
- fixed, floating, amortizing, callable, and convertible bonds;
- vanilla, barrier, Asian, compound, variance, and basket options;
- vanilla, CMS, OIS, CDS, zero-coupon, and portfolio-credit (synthetic CDO, nth-to-default) swaps and instruments;
- risk statistics (VaR, expected shortfall, ...) over caller-supplied samples;
- and analytic, tree, finite-difference, and Monte Carlo engines from Black-Scholes through SABR and Heston.

hasquant is a close-to-1:1 `c2hs` wrapper over QuantLib's C++ API, not a framework. It binds 1,600+ constructors and non-trivial methods (over 15% of QuantLib's surface) and deliberately excludes 2000+ methods (mostly mutators or getters that only repeat constructor inputs).

Type safety is a primary API goal. Phantom-typed pointers (`GenBond a`, `GenQuote a`, …) preserve the relevant part of QuantLib's object hierarchy in Haskell, so invalid object combinations are compile-time errors rather than failed casts at runtime. The C++ shim uses no runtime downcasts; bindings expose a concrete leaf type when one is needed. Enums mirror upstream values explicitly.

hasquant does not depend on [QuantLib-SWIG](https://github.com/lballabio/QuantLib-SWIG). References to it identify prior art for API-shape decisions only.

The ownership model, enum/ADT design, and C-shim conventions predate AI assistance. AI now helps extend coverage, but each binding is checked against upstream signatures and established patterns, then tested.

Examples are in `test/example/QuantLib/Example`; most deliberately follow QuantLib examples and tests, prioritizing fidelity to the upstream fixture over idiomatic Haskell. `QuickStart` is the readability-oriented exception. The Hspec suite is dispatched from `test/main/QuantLib/MainTest.hs`.

Published package: https://hackage.haskell.org/package/hasquant. Current Haddock: https://khorser.github.io/hasquant.

# Quick Example

Build and price a five-year SOFR OIS:

``` haskell
import Data.List.NonEmpty (NonEmpty(..))

let today = 2 `january` 2024
setEvaluationDate (Just today)

cal <- calendar TARGET
settle <- advance cal today (2, Days) Following False
let maturity = addGregorianYearsClip 5 settle

dc <- dayCounter (Actual360 False)
curve <- interpolatedZeroCurve
  ((settle, 0.030) :|
    [ (addGregorianYearsClip 1 settle, 0.032)
    , (addGregorianYearsClip 2 settle, 0.034)
    , (addGregorianYearsClip 5 settle, 0.036)
    , (addGregorianYearsClip 10 settle, 0.038)
    ]) dc cal [] Linear

sofr <- overnightIborIndex Sofr (Just curve)

sched <- schedule (Just settle) maturity (1, Years) cal
  ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

ois <- overnightIndexedSwap Payer 10000000 sched 0.035 dc sofr 0.0
  0 Following cal False AveragingCompound Nothing 0 False

engine <- discountingSwapEngine curve (Just False) Nothing Nothing
setPricingEngine ois engine

npv ois >>= print       -- 70994.8441727506
fairRate ois >>= print  -- 3.6554153626327204e-2
```

This is `QuantLib.Example.QuickStart.run`, compiled by `stack exec hasquant_example` and covered by `test/hspec/QuantLib/Spec/Examples.hs`.

# Goals and Scope

hasquant provides pricing, curve-building, and risk primitives; callers own orchestration. `app/SofrXva` owns CSV parsing and pipeline wiring, and uses hasquant for curve construction and discounting.

Two things follow from that split:

- Calendar, currency, day-counter, and index enums are usable without a pricing engine.
- Monte Carlo tests and examples use fixed nonzero RNG seeds; QuantLib treats `seed = 0` as entropy.

Out of scope:

- Reimplementing or independently binding QuantLib's interpolation, optimization, linear-algebra, and RNG internals, unless another binding needs one exposed.
- A declarative composition DSL; any such DSL belongs in a sibling project.

## Roadmap
- Add classes and methods using the repository skills.
- Evaluate whether some [OpenSourceRiskEngine](https://opensourcerisk.org) functionality should be bound
- Join forces with [HQuantLib](https://github.com/paulrzcz/hquantlib): a bivariate copula CDF catalogue
- Build a declarative composition DSL as a sibling project.
- Expose that DSL through an agent-callable tool, so an LLM can construct and price products through validated hasquant operations rather than generated pricing logic.
- Review interfaces for consistency, add obviously missing features and fix contradictions to the current design
- See [github issues](https://github.com/khorser/hasquant/issues) for more formalized tasks

# Testing

Tests reuse QuantLib fixtures and cached values when available. Enum-dispatched bindings also get smoke tests that construct and check representative values; these catch stale or incorrect enum mappings that can survive a clean build and the ordinary test suite.

`tools/ql-methods-1.43.txt` tracks constructors and non-trivial methods. Coverage: https://khorser.github.io/hasquant/coverage/hpc_index.html.

# Building

GHC 9.10 is the primary development version. GHC 8.10.6 (`base >= 4.14`) is the supported floor and is checked with lts-18.8. GitHub CI also tests with GHC 9.6.7, 9.8.4, 9.12.4, 9.14.1.

Install QuantLib 1.43 or later: [Linux](https://www.quantlib.org/install/linux.shtml), [macOS](https://www.quantlib.org/install/macosx.shtml), or [CMake](https://www.quantlib.org/install/cmake.shtml).

Linux and macOS are the primary, well-tested platforms. Windows builds work too, but QuantLib has to be rebuilt with GHC's own bundled Clang first — see [`WINDOWS.md`](WINDOWS.md) for the recipe.

## Stack

Minimal build: `stack build --no-haddock --no-test`

Run tests: `stack build --test --no-haddock`

Build and run examples: `stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`.
The example executable is `buildable: False` without that flag, so HLS also needs it — add `package hasquant` / `flags: +buildExample` to a local `cabal.project.local` to edit `main/exe` with HLS.

To trace allocations:
`stack build --no-haddock --flag hasquant:buildExample --flag hasquant:trackAllocations && stack exec hasquant_example`

The trace defaults to stderr. Use a file to keep program output separate:

`QLTRACK_ALLOCATIONS=/tmp/trace.log stack exec hasquant_example`

`tools/alloc-summary.py /tmp/trace.log` pairs allocations and frees, reports live objects and double frees, and exits nonzero on an accounting failure.

**Caution:** Cabal and Stack do not rebuild `cxx-sources` when only a flag changes. Before enabling `trackAllocations`, delete `build/cbits` and confirm a built object contains `allocated` before trusting an empty trace.

Run GHCi: `stack ghci --ghci-options $(find .stack-work \( -name "*.so" -o -name "*.dylib" \) -print -quit)`

## Cabal

Standard build: `cabal configure --disable-documentation && cabal build`

Build with documentation: `cabal configure --enable-documentation && cabal build`

Build example: `cabal configure -f buildExample --disable-documentation && cabal build`

Build example and tests: `cabal configure -f buildExample --enable-tests --disable-documentation && cabal build`

## Docker

Use the Linux x86_64 image for GHC 8.10.6:
`docker compose build`, then `docker compose run --rm -it hasquant stack --resolver lts-18.8 test`.

Drop `-it` when running without a TTY (CI, or a scripted check) — it fails there.

The image persists Stack, GHCup, and Cabal caches and keeps build outputs off the host.

# On Types

Public APIs use concrete types; typeclasses are almost entirely internal plumbing. This is deliberate: public constraints would expose implementation details and can rule out otherwise valid callers, while concrete types and explicit upcasts keep the library type-safe without limiting the abstractions users can build above it.

The practical exception is collections of related QuantLib objects. Types such as `[GenQuote q]` and `NonEmpty (GenRateHelper rh)` carry one shared phantom parameter, so every element must have the same type. Supporting an arbitrary mixture of sibling types directly would require existential wrappers or additional public constraints throughout higher-level APIs. Instead, callers explicitly upcast elements to their common parent before putting them in one list.

Container types also communicate intent. Ordinary lists are used for small or genuinely optional collections; `NonEmpty` makes required schedules, helpers, notionals, and curve nodes impossible to omit accidentally. Large homogeneous numeric data—Monte Carlo paths, regression data, and volatility grids—uses storable `RealVector` and `RealMatrix` values, avoiding the allocation overhead of boxed lists while retaining explicit dimensions. These distinctions put useful invariants and performance expectations in the API instead of leaving them to documentation and runtime checks.

## How to read types

`CallableBond` accepts only callable bonds. `GenBond a` accepts `Bond` and its derivatives:
``` haskell
type Bond = GenBond CBond
type FixedRateBond = GenBond CFixedRateBond
type ConvertibleBond = GenBond CConvertibleBond
type CallableBond = GenBond CCallableBond
```

`GenInstrument a` (for example, `npv`) accepts every instrument. An implicit upcast allocates a temporary C-side handle and frees it after the call, so reuse `asBond` or `asInstrument` when making repeated calls through a common parent type.
