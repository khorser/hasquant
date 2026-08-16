# gap-12: SabrSwaptionVolatilityCube / InterpolatedSwaptionVolatilityCube

**Status: done.** This file records what was actually built, for future reference — not a plan to execute.

## What was missing

hasquant could build a flat swaption vol (`constantSwaptionVolatility`/`'`) and a fixed ATM expiry×tenor grid (`swaptionVolatilityMatrix'`), but nothing with a strike-dependent smile. This was the single biggest remaining hole in the vol-surface coverage, and the named follow-on deferred by `gap-02`.

## What was bound

Two new dedicated leaf types under the `SwaptionVolatilityStructure` hierarchy (see the updated haddock tree above `type SwaptionVolatilityStructure = ...` in `QuantLib/Internal/Type.hs`) — **not** the generic-return-type + `dynamic_cast`-getter pattern used for `sabrInterpolatedSmileSection`. Each concrete class has its own real getters (`sparseSabrParameters` etc., `atmStrike`), so per CLAUDE.md's "introduce a dedicated type when the class has its own calc/getter" rule each earns a leaf; every diagnostic below takes the concrete pointer directly, with zero `dynamic_pointer_cast`s added by this item.

- **`sabrSwaptionVolatilityCube`** (`QuantLib/TermStructure/Volatility.chs`) — the full SABR-calibrated cube constructor. `endCriteria`/`optMethod` are hardcoded to QuantLib-internal defaults, not exposed (same ownership hazard as `sabrInterpolatedSmileSection`/`FittedBondDiscountCurve`'s fitting methods — `EndCriteria`/`OptimizationMethod` are raw Haskell-GC-finalized pointers, not `shared_ptr`-boxed). Calibration is lazy (`LazyObject`); construction can succeed even for inputs that will later fail to calibrate.
- **`interpolatedSwaptionVolatilityCube`** — the non-SABR, linear-interpolation sibling. No `EndCriteria`/`OptimizationMethod` hazard (never calibrates). Reuses every marshalling piece built for the SABR cube.
- **Diagnostics**: `sparseSabrParameters`, `denseSabrParameters`, `marketVolCube`, `volCubeAtmCalibrated` (all `SabrSwaptionVolatilityCube -> IO (Matrix Double)`) and per-leaf `sabrSwaptionVolatilityCubeAtmStrike`/`'` and `interpolatedSwaptionVolatilityCubeAtmStrike`/`'`.

## New infrastructure

- **Outward-`Matrix` marshalling** — did not exist anywhere in the codebase before this (every prior `Matrix`/`qlHandleMatrix`/`qlRealMatrix` crossed the C boundary inward only). Composed from two existing idioms: the 1D out-array idiom (`qlAllocateDoubles` + `unsigned* len`/`double** vs`, precedent `qlGsrVolatility`) and the single-scalar out-param idiom (`prePtr-`Word'peekWord*`, precedent `qlCashFlowsNpvbps`'s `prePtr-`Double'peekDouble*`). New helper `peekWord :: Ptr CUInt -> IO Word` added to `QuantLib/Internal.hs`.
- `QuantLib.Math`'s `Matrix` export widened from bare `Matrix` to `Matrix(..)` — the first time a getter returns a `Matrix` value to a caller, who then needs `matrixRows`/`matrixColumns`/`matrixData` to do anything with it.

## Known gotcha (documented in the `isAtmCalibrated` Haddock and the test comments)

`isAtmCalibrated = True` requires `atmVolStructure` to be a discrete grid structure (e.g. `swaptionVolatilityMatrix'`, not a flat `constantSwaptionVolatility'`) — upstream's ATM-recalibration path (`fillVolatilityCube`) `dynamic_pointer_cast`s it to `SwaptionVolatilityDiscrete` and dereferences the result unchecked, segfaulting (`boost::shared_ptr` "px != 0" assertion) otherwise. Not a hasquant bug — a precondition of the upstream constructor worth knowing before setting that flag.

## Deferred, not built

`sparseSabrParameters`/`marketVolCube` etc. cover per-node SABR params for the whole grid; typed `SabrSmileSection`-specific getters (`alpha`/`beta`/`nu`/`rho` on an individual smile section) were considered and **dropped** — for the smile section's *other* producer (standalone `sabrSmileSection`/`sabrSmileSection'` constructors), those getters would be a pure echo of constructor input, and that isn't sufficient justification on its own once the redundancy with the Matrix diagnostics (which already report the same calibrated values, just for every node at once) is factored in.

## Verification

`stack test --ta '--skip LONG'` (new `describe "swaption volatility cubes"` block in `main/test/QuantLib/Spec/TermStructure.hs`), clean `hlint QuantLib smoke test main Setup.hs`, clean `tools/quiet-build.py stack build --test --no-haddock` (28 known hidden c2hs warnings only). lts-18.8 docker gate (GHC 8.10.6) passed: 146 examples, 0 failures, including the new `swaption volatility cubes` block.
