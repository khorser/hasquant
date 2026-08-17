# hasquant/SWIG gap-closing subplans

Each `gap-NN-*.md` file is a self-contained execution unit for one binding gap identified against QuantLib-SWIG (`~/Src/QuantLib-extra/QuantLib-SWIG`) and the installed QuantLib 1.43 headers. A fresh session should be able to execute a subplan using only that file, the skill it names, and the repo's `CLAUDE.md` — without reading this index or any other subplan.

Full rationale, cross-item findings, and the verification trail behind this list live in the planning session's plan file (`~/.claude/plans/lovely-imagining-glade.md`, 2026-08-14) — not duplicated here.

## Status

| # | Subplan | Item | Status |
|---|---|---|---|
| 01 | `gap-01-bachelier-engines.md` | `BachelierSwaptionEngine` / `BachelierCapFloorEngine` | ready to execute |
| 02 | `gap-02-swaptionvolatilitymatrix.md` | `SwaptionVolatilityMatrix` | ready to execute |
| 03 | `gap-03-optionletstripper.md` | `OptionletStripper1` + `StrippedOptionletAdapter` | ready to execute |
| 04 | `gap-04-fxswapratehelper.md` | `FxSwapRateHelper` | ready to execute |
| 05 | `gap-05-overnight-future-ratehelpers.md` | `OvernightIndexFutureRateHelper` / `SofrFutureRateHelper` | ready to execute |
| 06 | `gap-06-amortizing-bonds.md` | `AmortizingFixedRateBond` / `AmortizingFloatingRateBond` | ready to execute |
| 07 | `gap-07-isdacdsengine.md` | `IsdaCdsEngine` | ready to execute |
| 08 | `gap-08-globalbootstrap-functors-spike.md` | `GlobalBootstrap` canned functors (spike) | ready to execute |
| 09 | `gap-09-piecewiseblackvariancesurface.md` | `PiecewiseBlackVarianceSurface::makeFromGrid` | ready to execute |
| 10 | `gap-10-blackvolatilitysurfacedelta.md` | `BlackVolatilitySurfaceDelta` | ready to execute |
| 11 | `gap-11-simplezeroyield-trait.md` | `SimpleZeroYield` bootstrap trait | ready to execute |
| 12 | `gap-12-sabrswaptionvolatilitycube.md` | `SabrSwaptionVolatilityCube` / `InterpolatedSwaptionVolatilityCube` | done |

All 11 subplans are written. Recommended execution order matches the numbering (roughly value/effort, with `gap-11` before `gap-08` if both are picked up together, since `gap-08`'s spike example depends on `gap-11`'s `SimpleZeroYield` trait — see `gap-08`'s own note for the fallback if run out of order). Each subplan is independent otherwise and can be executed in any order, in separate sessions.

`gap-12` was the follow-on this section used to defer under "Pending, not scheduled" (the `SwaptionVolatilityCube`/`SabrSwaptionVolatilityCube` item named in `gap-02`'s own doc-upkeep note) — it's now done, see that file for what was actually built.

## Shared "definition of done"

Every subplan's execution must satisfy all of the following before it's marked `done` (subplans reference this list rather than repeating it):

- `tools/quiet-build.py stack build --test --no-haddock` clean, no new warnings
- `stack test --ta '--skip LONG'` passes
- `hlint` clean run
- lts-18.8 docker gate passes: `docker compose run --rm hasquant sh -c 'stack build --resolver lts-18.8 --flag hasquant:buildExample --no-haddock && stack --resolver lts-18.8 test'`
- `tools/ql-methods-1.43.txt` lines flipped to `v`/`u` for every method/constructor touched
- New `describe` block added to the correct `main/test/QuantLib/Spec/*` module (never `MainTest.hs` directly)
- `smoke/` script added if the item is enum-dispatched (see each subplan's own note on whether this applies)
- `QuantLib/Internal/Type.hs` hierarchy tree updated if a new type was added
- README `# TODO` line removed/updated if the item resolves one

## Project convention established during planning

The options-record threshold (widen-in-place vs. TH-generated options record) is **10 trailing defaulted parameters**. CLAUDE.md's "Wide constructors" bullet and the `add-quantlib-options-record` skill now both state this; they are the authority, this line is just the record of where it came from.
