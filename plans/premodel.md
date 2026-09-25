# Plan: hasquant changes for the stochastic-process design (hasquant-dsl sessions/models-session.md)

## Context

A design session in the sibling project hasquant-dsl (`sessions/models-session.md`) planned XVA model extensions:
- a joint LGM1F–FX model (one rate factor per currency plus log-FX),
- two-stage GSR calibration (constant σ first, then dated σ steps),
- then G2, stochastic credit and Heston.

The moderator accepted every default in the decision record (§25–26). Three decisions shape hasquant's part:
- There is no new native dependency: ORE/QuantExt is not bound.
- The joint kernel is written **in Haskell inside hasquant-dsl**. It draws normals from hasquant's `gaussianRsg`, one FFI crossing per path.
- hasquant gets **no C++ `StochasticProcess`** and **no new C++ plumbing**, including for G2.

**Result of this review:** every QuantLib surface the design needs is already bound in hasquant (inventory below). **No hasquant change is required to start the hasquant-dsl work.** The work below is small:
- Phase 1 turns two claims the record left unverified into CI tests, using QuantLib's own fixtures.
- Phase 1 also makes the two bound engines usable as oracles for hasquant-dsl.
- Phase 2 corrects two Haddock comments.
- Phase 3 is conditional. It is needed only if stochastic credit (Q3) later calibrates to CDS options.

hasquant repo: `github.com/khorser/hasquant`, checked out at `../hasquant` beside hasquant-dsl. QuantLib 1.43.

## Rules the implementing agent must follow (from hasquant `AGENTS.md`)

- Read `AGENTS.md` and each applicable `.claude/skills/*/SKILL.md` first. Phases 1–2 need `run-hasquant`. Phase 3 also needs `add-quantlib-class`, `add-quantlib-method` and `c2hs-shim-patterns`.
- Show the todo list.
- Work on branch `models-oracles` off `master`, and open one PR at the end. Never commit to `master`.
- Make **one commit per phase**, and each commit must build and pass its tests.
- If a gate cannot run in your environment (for example no docker for the GHC 8.10 gate), say so in the PR. Never report an unrun gate as passed.
- A QuantLib source checkout may be absent. The fixture values you need are copied into this plan.
- Behavioural tests go in Hspec under `test/hspec/QuantLib/Spec/*.hs`, not in `test/smoke/`.
- Tests that set the evaluation date wrap their body in `Context.keepingSettingsGc`.
- Scale tolerances to the result's magnitude. Use QuantLib's fixture tolerances where given.
- Keep comments to two lines at most, stating current purpose. Don't record history in comments.
- Gates before each commit:
  - one clean, warning-visible build: `tools/quiet-build.py stack build --test --no-haddock --flag hasquant:buildExample --flag hasquant:buildSofrXva`;
  - `stack test`;
  - `hlint .`;
  - the GHC 8.10 docker gate from `run-hasquant` (`docker compose run --rm hasquant sh -c 'stack build --resolver lts-18.8 --flag hasquant:buildExample --flag hasquant:buildSofrXva --no-haddock && stack --resolver lts-18.8 test'`).
- Phases 1–2 change no API, so `test/smoke/` does not need recompiling. Phase 3 adds API, so grep `test/smoke/` for affected names as the skill says.
- **Out of scope. Do not add these:**
  - a C++ LGM or cross-asset process, or any ORE code;
  - a `StochasticProcess.size` getter;
  - numerical integrators;
  - G2 or Heston parameter getters (the generic `params` already returns them);
  - an index "clone on a curve" (index constructors already take `Maybe` curve);
  - a batched RNG call.

  The design places all of these in hasquant-dsl, or has decided they are not needed.

## Inventory: what hasquant-dsl will use (verified bound; no change)

| Design need | Binding(s) | Location |
|---|---|---|
| Normals for the Haskell SDE (fixed width = stateSize × steps) | `gaussianRsg`, `sobolGaussianRsg`, `nextSequence`, `lastSequence`, `rsgDimension` | `QuantLib/Method.chs:403-445` |
| Stage 1/2 GSR calibration | `gsr`, `gsrWithReversions`, `calibrate`, `calibrateVolatilitiesIterative`, `calibrateReversionsIterative`, `moveVolatility`, `volatilities` (`HasVolatilities Gsr`), `reversions`, `params` | `QuantLib/Model.chs:438-500, 669-671, 737` |
| Swaption helpers | `swaptionHelper` (`SpanTenors`/`SpanFromDate`/`SpanDates`), `modelValue`, `marketValue`, `calibrationError` | `QuantLib/Model.chs:775-860` |
| GSR swaption and zero-bond pricing | `gaussian1dSwaptionEngine`, `gaussian1dZerobond`, `stateProcess` | `QuantLib/PricingEngine.chs:988`; `Model.chs` |
| Oracle: constant Hull–White | `hullWhite`, `discountBond`, `jamshidianSwaptionEngine` | `Model.chs:419`; `PricingEngine.chs:985` |
| Oracle: FX option with a stochastic domestic rate | `analyticBsmHullWhiteEngine` | `PricingEngine.chs:780` |
| G2 standalone (Q5) | `g2`, `g2SwaptionEngine`, `g2Process`, `g2ForwardProcess`, `params` | `Model.chs`; `PricingEngine.chs:122`; `Process.chs:59-60` |
| Heston (Q4) and its oracles | `hestonProcess` (with `HestonProcessDiscretization`), `hestonModel`, `hestonModelHelper`, `analyticHestonEngine`, `hybridHestonHullWhiteProcess`, `analyticHestonHullWhiteEngine` | `Process.chs:64, 68, 123, 504`; `Model.chs:316, 759`; `PricingEngine.chs:118-119` |
| Overnight-accumulator admission check | `valueDate`, `maturityDate`, `forecastFixing`, `dayCounter`, `fixingDays`, `tenor`, `fixingCalendar`; `iborIndex` and `overnightIborIndex` take `Maybe` curve, so an index can be rebuilt on a probe curve | `Index/InterestRate.chs:63-73, 263, 313`; `Index.chs:80` |
| FX-vol calibration Black prices | `blackFormula` | `PricingEngine.chs:2100` |
| State-feature regression (exposure v2) | `lsmRegress`, `lsmRegressMulti`, `lsmBasisSize` | `Method.chs:479+` |
| Credit curves (Q3 baseline) | `flatHazardRate`, `piecewiseDefaultCurve`, `creditDefaultSwap`, `midPointCdsEngine`, `cdsOption`, CDS-option `impliedVolatility` | `TermStructure/Credit.chs`; `Instrument/Credit.chs:14, 109-115`; `PricingEngine.chs:1036` |

## Phase 1: pin the two upstream contracts hasquant-dsl will build on (Hspec only)

### 1a. GSR with constant parameters equals Hull–White (ports the rest of `gsr.cpp::testGsrModel`)

**Why:** the record lists "GSR's steps are Hull–White parameters" as unverified. The GSR→LGM parameter map in hasquant-dsl depends on it. `gsrReversionSpec` already ports the "n+1 equal reversions" half of this test (`test/hspec/QuantLib/Spec/Model.hs:153-175`). The Hull–White comparison is not ported yet.

**Where:** add one `it` inside `gsrReversionSpec`. That lets it reuse the spec's `where`-local `flatCurve` (`Spec/Model.hs:213-221`), which is a 3% continuous Act/365F flat forward referenced at T+2 TARGET. Both models share that curve, so the equivalence holds as in upstream.

**Fixture:** QuantLib `test-suite/gsr.cpp:534-600`. Reproduce it as follows:
- **Curve:** `flatCurve`, as above.
- **Models:**
  - `model = gsr ts (q 0.01) [] (q 0.01) 50.0`
  - `model2 = gsrWithReversions ts (q 0.01, q 0.01) [(refDate + 6i months, (q 0.01, q 0.01)) | i <- [1..59]] 50.0`
  - `hw = hullWhite ts 0.01 0.01` (reversion a, then sigma)
- **Grid:** `w` runs from 0.1 to 50 in steps of 5. `t` runs from w+0.1 to 50 in steps of 2.5. `xw` runs from −0.10 to 0.10 in steps of 0.01.
  - Use integer loop counters (for example `xw = -0.10 + 0.01*k`, k = 0..20) to avoid drift from floating-point accumulation.
  - The test may run a subset of this grid, for example w ∈ {0.1, 10.1, 30.1, 45.1}, to keep runtime down.
- **Dates first, times from dates.** `gaussian1dZerobond` (`Model.chs:586`) takes `Day`s only: maturity, `Maybe` reference date, y, and a `Maybe` curve.
  - Generate the grid as dates: `wDate = addDays n settlement` and `tDate` likewise.
  - Derive `w = timeFromReference ts wDate` and `t = timeFromReference ts tDate` (`TermStructure.chs:138`), so both models see identical times.
  - Choose day offsets that approximate the upstream grid, for example w ≈ 0.1, 10.1, 30.1, 45.1 years and t = w + 0.1 + 2.5k up to 50 years.
- **At each grid point:**
  - `sp <- asStochasticProcess =<< stateProcess gModel`. `stateProcess` returns `StochasticProcess1D` (`Model.chs:658`); `asStochasticProcess` is exported from `QuantLib.Process`.
  - `e <- expectation sp 0 [0] w` and `sd <- stdDeviation sp 0 [0] w`. Both take `[Double]` x0 (`Process.chs:396, 407`). `stdDeviation` returns a 1×1 `Matrix Double`; `expectation` returns a 1-element result. Take element 0 of each.
  - `yw = (xw − e) / sd`.
  - `rw = xw + 0.03`.
- **Assertion:** `|gsrZerobond − hwBond| ≤ 1e-8`, for both `model` and `model2`.
  - `gsrZerobond = gaussian1dZerobond gModel tDate (Just wDate) yw Nothing`, on the `asGaussian1dModel` view as at `Spec/Model.hs:164-171`.
  - `hwBond = discountBond hwAffine w t [rw]` (`Model.chs:552`), on the `AffineModel` view of `hw` (`AsAffineModel`). See the `discountBond` use at `Spec/Model.hs:311-339`.
- **Name:** something like `"prices zero bonds as the Hull-White model with the same constant reversion and volatility"`.

### 1b. `analyticBsmHullWhiteEngine` fixture (ports `hybridhestonhullwhiteprocess.cpp::testBsmHullWhiteEngine`)

**Why:** the record says "nothing external checks the FX formula". hasquant-dsl will use this engine as the oracle for its joint-model FX option formula when the foreign rate is deterministic. It has no Hspec coverage today: grep of `test/hspec` for `analyticBsmHullWhiteEngine` finds nothing.

**Where:** `test/hspec/QuantLib/Spec/PricingEngine.hs`.

**Fixture:** QuantLib `test-suite/hybridhestonhullwhiteprocess.cpp:62-145`.
- **Evaluation date:** use a fixed date (for example 2024-01-15), not "today". Maturity is evaluation date + 20 years.
- **Market:**
  - day counter Actual365Fixed;
  - spot 100;
  - dividend (foreign) flat rate 4%;
  - risk-free (domestic) flat rate 5.25%;
  - flat Black vol 25%.
- **Hull–White model:** `hullWhite rTS 0.00883 0.00526`, with a = 0.00883 and σ = 0.00526.
- **Option:**
  - process: `blackScholesMertonProcess spot qTS rTS volTS`;
  - European exercise at maturity;
  - call at strike `fwd = 100·qTS.discount(T)/rTS.discount(T)`.
- **Cases:** for each (corr, expectedVol):
  - (−0.75, 0.217064577)
  - (−0.25, 0.243995801)
  - (0.0, 0.256402830)
  - (0.25, 0.268236596)
  - (0.75, 0.290461343)
- **Assertions:**
  - `npv = NPV` with `analyticBsmHullWhiteEngine corr process hw`.
  - The implied vol of `npv` under a plain `analyticEuropeanEngine`/BSM process is within 1e-8 of `expectedVol`. Use the vanilla-option `impliedVolatility` (`Instrument/Option.chs:456-466`) with accuracy 1e-10 and at most 100 evaluations.
  - With a BSM process at flat vol `expectedVol`, `analyticEuropeanEngine` reproduces `npv` to relative 1e-8.
  - As upstream does, compare delta (absolute 1e-8) and gamma and theta (relative to `npv`, 1e-8) through the bound `HasGreeks` class (`Instrument/Option.chs:373`).
- **Name:** something like `"reproduces testBsmHullWhiteEngine's implied volatilities across equity/short-rate correlations"`.

### Commit
`Pin GSR/Hull-White equivalence and the BSM-Hull-White engine to QuantLib fixtures`

## Phase 2: Haddock corrections that matter to the design (no API change)

1. **`QuantLib/Model.chs:419` (`hullWhite`).** The first `Double` is labelled `-- ^y`. It is the mean reversion `a`, because QuantLib's signature is `HullWhite(termStructure, Real a, Real sigma)`. Relabel it `-- ^a (mean reversion)`.
2. **`QuantLib/Method.chs:417-418` (`gaussianRsg` doc).** It currently says ``@dimension@ ... for a path set, @assets * timesteps@``. Generalise that to "(normals drawn per step) × timesteps". For `pathGenerator` parity the per-step count is the process's `factors`. A Haskell-evolved model may draw more normals per step than it has Brownian drivers.
   - Also state that `sobolGaussianRsg` has a maximum dimension. The maximum depends on the direction-integer set and on QuantLib's build-time `PPMT_MAX_DIM`. A larger dimension raises an exception. Do not quote a number.
3. **CHANGELOG.md:** add a line only if recent entries also record doc and test-only changes. Otherwise skip it.

### Commit
`Correct the Hull-White reversion label and the gaussianRsg dimension contract`

## Phase 3 (conditional, do NOT start now): `BlackCdsOptionEngine` for Q3 stochastic credit

Start this only when hasquant-dsl's Q3 work decides to calibrate stochastic credit to CDS options. It is the only QuantLib surface in the design that is missing. The accepted order is G2, then credit, then Heston, so this comes after G2.

- **Upstream:** `ql/experimental/credit/blackcdsoptionengine.hpp`, `BlackCdsOptionEngine(Handle<DefaultProbabilityTermStructure>, Real recoveryRate, Handle<YieldTermStructure> termStructure, Handle<Quote> vol)`. It is listed unbound at `tools/ql-methods-1.43.txt:1337`.
- **Binding:**
  - Follow `add-quantlib-method` to add a constructor that returns `PricingEngine`, next to `midPointCdsEngine` in `PricingEngine.chs`, with a matching shim in `cbits/qlPricingEngine.{h,cpp}`.
  - Use `GenQuote` for `vol`, following the AGENTS rule for quote-or-value inputs.
  - Mark line 1337 `v` in `tools/ql-methods-1.43.txt`. The getters on lines 1339-1340 stay `x`, because they echo construction inputs.
- **Hspec:** port `test-suite/cdsoption.cpp::testCached`:
  - Evaluation date 2007-12-10, TARGET.
  - Risk-free: flat forward 2% Act/360.
  - Dates: expiry = advance(today, 9M); start = advance(expiry, 1M); maturity = advance(start, 7Y).
  - Schedule: quarterly, ModifiedFollowing, Forward generation.
  - Credit: hazard rate 0.001 (`flatHazardRate`, 0 settlement days, TARGET, Act/360); recovery 0.4.
  - Swap: notional 1e6. The strike is the `fairSpread` of a seller CDS at 0.001 priced by `midPointCdsEngine`.
  - Option: vol quote 0.20, European exercise at expiry.
  - Expected NPV is 270.976348 within 1e-5, for both the seller and the buyer underlying.
- **Commit:** `Bind BlackCdsOptionEngine`, plus the CHANGELOG entry this repo uses for new bindings.

## Verification

- **Phase 1:**
  - `stack test` passes, and the new `it`s appear in the output.
  - Temporarily perturb one input (for example the HW σ to 0.011, or one expected vol in its 4th decimal) and confirm the test fails. Revert before committing.
- **Phase 2:** a warning-clean build, then `stack haddock --no-haddock-deps` renders the changed docs. `hlint .` passes.
- **All phases:** the GHC 8.10 docker gate passes. `git status` is clean after each commit.
- **Downstream check:** the user runs this locally after merge; it is not a gate for the cloud agent. In `../hasquant-dsl`, run `cabal build all roundtrip rpa-controls`. Phases 1–2 change no API, so it should still compile.

## What stays in hasquant-dsl (for the reader; not this plan's work)

This is the decision record's work list, all Haskell in hasquant-dsl:
- the PathCube storage and provider rewrite;
- H and ζ, the conditional moments, the Hull–White→LGM map, and the `semidefinite` Cholesky returning L;
- the valuation slice with a pathwise 1/N_d;
- two-stage calibration;
- conditional exposure;
- then G2 → credit → Heston;
- the CDI (1+r·w) ticket.

When those items need an oracle, they use the Phase 1 tests' setups:
- GSR ↔ Hull–White for the H/ζ swaption gate;
- BSM–Hull–White for the FX option formula with the foreign rate deterministic.
