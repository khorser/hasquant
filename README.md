Haskell bindings to [QuantLib](https://www.quantlib.org/).

Supported functionality includes
- yield, credit, inflation, and volatility curves;
- IBOR, overnight, swap, and inflation indexes;
- fixed, floating, amortizing, callable, and convertible bonds;
- vanilla, barrier, Asian, compound, variance, and basket options;
- vanilla, CMS, OIS, CDS, zero-coupon, and portfolio-credit (synthetic CDO, nth-to-default) swaps and instruments;
- risk statistics (VaR, expected shortfall, ...) over caller-supplied samples;
- large numeric vectors as `vector`'s storable `Vector Double` and dense matrices compatible with hmatrix;
- and analytic, tree, finite-difference, and Monte Carlo engines from Black-Scholes through SABR and Heston.

hasquant is a close-to-1:1 `c2hs` wrapper over QuantLib's C++ API, not a framework. It binds 2,000+ constructors and non-trivial methods (around 20% of QuantLib's surface) and deliberately excludes 2,000+ methods (mostly mutators or getters that only repeat constructor inputs).

Type safety is a primary API goal. Phantom-typed pointers (`GenBond a`, `GenQuote a`, …) preserve the relevant part of QuantLib's object hierarchy in Haskell, so invalid object combinations are compile-time errors rather than failed casts at runtime. The C++ shim uses runtime downcasts only where QuantLib's architecture dictates them; otherwise, bindings expose a concrete leaf type when one is needed. Enums mirror upstream values explicitly.

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
  0 Following cal False AveragingCompound Nothing Nothing 0 False

engine <- discountingSwapEngine curve (Just False) Nothing Nothing
setPricingEngine ois engine

npv ois >>= print       -- 70994.8441727506
fairRate ois >>= print  -- 3.6554153626327204e-2
```

This is `QuantLib.Example.QuickStart.run`, run by `cabal run hasquant_example -f buildExample` and covered by `test/hspec/QuantLib/Spec/Examples.hs`.

# Goals and Scope

hasquant provides pricing, curve-building, and risk primitives; callers own orchestration. `app/SofrXva` owns CSV parsing and pipeline wiring, and uses hasquant for curve construction and discounting.

Two things follow from that split:

- Calendar, currency, day-counter, and index enums are usable without a pricing engine.
- Monte Carlo tests and examples use fixed nonzero RNG seeds; QuantLib treats `seed = 0` as entropy.

Out of scope: reimplementing or independently binding QuantLib's interpolation, optimization, linear-algebra, and RNG internals, unless another binding needs one exposed.

## Roadmap
- Bind QuantLib 1.44 rough Heston models/engines and MTM cross-currency swap products.
- Identify which [OpenSourceRiskEngine](https://opensourcerisk.org) functionality should be bound, e.g. `https://github.com/OpenSourceRisk/Engine/blob/master/QuantExt/qle/indexes/fallbackiborindex.hpp`
- Build a declarative embedded DSL as a sibling project to define contracts, portfolios, market data, and calculation scenarios (unpublished WIP), use it for XVA and other complext calculations
- Expose that DSL through an agent-callable tool, so an LLM can construct and price products through validated hasquant operations rather than generated pricing logic.
- Drop the exact-mean H1-HW engine (`cbits/qlExactMeanH1HwEngine.h`) and bind QuantLib's own once it ships an exact E[sqrt v] option for `AnalyticH1HWEngine`
- See [github issues](https://github.com/khorser/hasquant/issues) for more formalized tasks

# Testing

Tests reuse QuantLib fixtures and cached values when available. Enum-dispatched bindings also get smoke tests that construct and check representative values; these catch stale or incorrect enum mappings that can survive a clean build and the ordinary test suite.

`tools/ql-methods-1.43.txt` and `tools/ql-methods-1.44.txt` track constructors and non-trivial methods. Coverage: https://khorser.github.io/hasquant/coverage/hpc_index.html.

# QuantLib version policy

Starting with QuantLib 1.44, hasquant supports the two most recent QuantLib release series:
initially 1.43 and 1.44. Release candidates are tested ahead of the corresponding final release.

The public Haskell API is shared across supported versions. Calls requiring the newer QuantLib
version raise `UnsupportedQuantLibVersion` (call name, minimum required version, linked version)
when used with the preceding version. Arguments introduced in the newer version are accepted but
ignored on the preceding version, including their native validation and callback execution.

Newer validation and safety restrictions may also be applied when running against the preceding
version. Numerical results and other upstream behavior can still differ between versions.

# Building

GHC 9.10 is the primary development version. GHC 8.10.6 (`base >= 4.14`) is the supported floor and is checked against Stackage lts-18.8. GitHub CI also tests with GHC 9.6.7, 9.8.4, 9.12.4, 9.14.1.

Install QuantLib 1.43 or 1.44 (currently 1.44 RC): [Linux](https://www.quantlib.org/install/linux.shtml), [macOS](https://www.quantlib.org/install/macosx.shtml), or [CMake](https://www.quantlib.org/install/cmake.shtml).

Linux and macOS are the primary, well-tested platforms. Windows builds work too, but QuantLib has to be rebuilt with GHC's own bundled Clang first — see [`WINDOWS.md`](WINDOWS.md) for the recipe.

hasquant never uses intraday dates, so prefer a QuantLib built without `QL_HIGH_RESOLUTION_DATE` (check `ql/config.hpp`). With it, every `Date` operation goes through boost `posix_time`. In a GSR-calibration-heavy workload that was 59% of CPU, and turning it off cut run times from 309 s to 156 s and from 76 s to 28 s, with bit-identical results. Homebrew's formula turns it on (`--enable-intraday`); CMake leaves it off by default:

```
cmake -S QuantLib-1.43 -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/opt/quantlib-1.43 \
  -DCMAKE_INSTALL_NAME_DIR=$HOME/opt/quantlib-1.43/lib -DQL_BUILD_EXAMPLES=OFF -DQL_BUILD_TEST_SUITE=OFF
cmake --build build -j && cmake --install build
brew unlink quantlib
```

To use custom built QuantLib copy `cabal.project.local.customQL` to `cabal.project.local` and update the paths.

## Cabal

Build everything, including tests and the flagged executables:
`cabal build all --enable-tests -f buildExample -f buildSofrXva`

Run tests: `cabal test all --enable-tests` (add `--test-options=--skip=LONG` for the fast path)

Build and run examples: `cabal run hasquant_example -f buildExample`.
The example executable is `buildable: False` without that flag, so HLS also needs it — add `package hasquant` / `flags: +buildExample` to `cabal.project.local` to edit `main/exe` with HLS.

To trace allocations:
`cabal run hasquant_example -f buildExample -f trackAllocations`

The trace defaults to stderr. Use a file to keep program output separate:

`QLTRACK_ALLOCATIONS=/tmp/trace.log cabal run hasquant_example -f buildExample -f trackAllocations`

`tools/alloc-summary.py /tmp/trace.log` pairs allocations and frees, reports live objects and double frees, and exits nonzero on an accounting failure.

**Caution:** Cabal does not rebuild `cxx-sources` when only a flag changes. Before enabling `trackAllocations`, delete `build/cbits` and confirm a built object contains `allocated` before trusting an empty trace.

Run GHCi: `cabal repl lib:hasquant`

### Pinned dependencies

Dependencies are pinned to Stackage snapshots stored as cabal constraint files in `cabal/`:

| Project file | GHC | Snapshot |
|---|---|---|
| `cabal.project` (default) | 9.10.3 | lts-24.56 |
| `cabal.project.lts-22.44` | 9.6.7 | lts-22.44 |
| `cabal.project.lts-18.8` | 8.10.6 | lts-18.8 |
| `cabal.project.unpinned` | others | none |

Select a non-default project with `--project-file=<file>`, which then reads `<file>.local` instead of `cabal.project.local`.
Each snapshot's `with-compiler` selects the matching versioned `ghc-X.Y.Z` binary installed by GHCup.
To add or refresh a snapshot, run `tools/stackage-cabal-config.sh lts-X.Y` and import the generated `cabal/stackage-lts-X.Y.config` from a project file.

## Docker

The Linux x86_64 image runs the GHC 8.10.6 compatibility gate:
`docker compose build`, then
`docker compose run --rm -it hasquant sh -c 'ghcup install ghc 8.10.6 && cabal update && cabal build all --project-file=cabal.project.lts-18.8 --enable-tests -f buildExample -f buildSofrXva && cabal test all --project-file=cabal.project.lts-18.8 --enable-tests -f buildExample -f buildSofrXva'`.

Drop `-it` when running without a TTY (CI, or a scripted check) — it fails there.

The image persists GHCup and Cabal caches and keeps build outputs off the host.

# On Types

Public APIs use concrete types by default. Public capability classes are reserved for genuine
multiple-inheritance interfaces and operations shared by related types with the same signature and
semantics. Blanket constraints still expose implementation details and can rule out otherwise valid
callers; concrete types and explicit upcasts remain the better choice when no common capability is
being expressed.

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

Cash flows follow the same pattern: `GenCashFlow cf` is the common root, with
`GenFloatingRateCoupon`, `GenIndexedCashFlow`, and `GenDigitalCoupon` preserving useful
intermediate families. A homogeneous subtype list can be passed directly to `cashFlowLeg`;
heterogeneous lists explicitly materialize `CashFlow` elements with `asCashFlow` first.
