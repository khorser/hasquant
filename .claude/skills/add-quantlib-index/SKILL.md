---
name: add-quantlib-index
description: Add a new QuantLib index (Ibor, overnight, or swap index) binding, or reconcile hasquant's index enums against what's actually available upstream. Use when asked to add, bind, or expose a market index (e.g. a new IBOR tenor/currency, an overnight rate index like SOFR/SONIA, or a swap-rate index), or to check/audit/sync the list of supported indexes — sourced from /opt/homebrew/include/ql/indexes/.
---

QuantLib index classes fall into two shapes in this codebase, and which one applies isn't always obvious from the class name alone — **ask the user** if it's not clear which applies before starting.

## Which kind is it?

1. **Enum-like named market-convention variant** — a subclass of `IborIndex`, `OvernightIndex`, or `SwapIndex` whose constructor takes *only* the shared shape (a tenor `Period` and/or one or two `YieldTermStructure` handles) with everything else (currency, calendar, day counter, fixing lag) hardcoded by QuantLib inside the subclass itself. `Sofr`, `Sonia`, `Euribor`, `EuriborSwapIsdaFixA` are all this shape. These are dispatched through a shared enum + lambda-table pattern, not given their own binding. The named inflation indices (`UKRPI`, `EUHICP`, ..., under `ql/indexes/inflation/`) are a *simpler* variant of this same shape: their constructors take **no** shared-shape parameter at all (not even a tenor/handle — just an optional term-structure handle we don't expose, see `QuantLib.Index.Inflation`), so the lambda table uses zero-arg lambdas (`[]{return static_cast<ZeroInflationIndex *>(new UKRPI());}`) instead of the usual one/two-arg ones. One upstream exception to watch for: `AUCPI`/`YYAUCPI` require explicit `(Frequency, bool revised)` args (no default ctor) unlike every other named inflation index — hardcode real market convention values in the lambda (`Quarterly, false` for AU, since AU CPI publishes quarterly unlike the monthly RPI/HICP/CPI indices).
2. **New node/leaf object** — anything that doesn't fit the shared constructor shape above (extra required constructor parameters, a genuinely new base type, or a class outside the `Ibor`/`Overnight`/`Swap`/named-inflation index families, e.g. `bmaindex.hpp`, `equityindex.hpp`, or a *generic* `ZeroInflationIndex`/`YoYInflationIndex` constructor taking a custom family/`Region`/currency — not yet bound, see README's `# TODO`). Follow [[add-quantlib-class]] and [[add-quantlib-method]] instead of this skill.

Check the class's constructor in its header under `/opt/homebrew/include/ql/indexes/` (concrete classes mostly live in `ibor/`, `swap/`) to decide.

## Case 1: enum-like index

There are three parallel enum+table pairs, each following the same lockstep-append rule as [[reconcile-currencies]]/[[reconcile-calendars]] (append only, don't reorder, keep both lists the same length):

| Kind | Enum (`cbits/qlEnumObjects.h`) | Table (`cbits/qlTermStructure.cpp`) | Factory fn | Shared shape |
|---|---|---|---|---|
| IBOR / Libor-style | `enum IborIndexType` | `iborIndices[]` (`makeIborIndex`) | `qlCreateIbor` | `(Period tenor, YieldTermStructureHandle ts)` |
| Overnight | `enum OvernightIborIndexType` | `onIndices[]` (`makeONIndex`) | `qlCreateONIndex` | `(YieldTermStructureHandle ts)` |
| Swap-rate | `enum LiborSwapIndexType` | `swapIndices[]` (`makeSwapIndex`) | `qlCreateLiborSwapIndex` | `(Period tenor, YieldTermStructureHandle h1, YieldTermStructureHandle h2)` |
| Zero inflation | `enum ZeroInflationIndexType` | `zeroInflationIndices[]` | `qlCreateZeroInflationIndex` | *(none)* |
| YoY inflation | `enum YoYInflationIndexType` | `yoyInflationIndices[]` | `qlCreateYoYInflationIndex` | *(none)* |

Each enum's comment states which table it must match the order of, and vice versa — a mismatch is a silent wrong-index-constructed bug, not a compile error, exactly like the currency/calendar tables.

**Index hierarchy note (inflation-specific):** unlike Ibor/Overnight/Swap indices (which collapse straight into their family's single Haskell type), `ZeroInflationIndex`/`YoYInflationIndex` sit under a real intermediate `InflationIndex` Haskell type (`Index -> InflationIndex -> {Zero,YoY}`, mirroring `InterestRateIndex`'s own 3-level shape in `Internal/Type.hs`), even though today nothing needs to treat "any inflation index" polymorphically. This was a deliberate choice (not the usual "leaf directly under the root" shape a Case-1 family would otherwise get) specifically to leave room for the generic-constructor Case-2 follow-up noted above, without a later restructuring. If you're adding a similar enum-dispatched family that has no foreseeable generic-constructor follow-up, prefer the flatter direct-leaf shape (`GenIndex a` with a single `AnyOf`, like `IborIndex`/`SwapIndex` sit under `InterestRateIndex`) — this extra level is the exception, not the default.

Steps:
1. Confirm the new index class's constructor matches the shared shape for its family (check the header under `ql/indexes/ibor/` or `ql/indexes/swap/`).
2. Append the new variant name to the matching `enum` in `cbits/qlEnumObjects.h`.
3. Append the matching lambda to the matching table in `cbits/qlTermStructure.cpp`, at the same relative position, e.g. for an overnight index: `, [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new NewIndexName(ts));}`.
4. No `.chs`/`Internal/Type.hs` changes needed for a new *case* of an existing enum — all three enums are already exposed as flat c2hs enums in `QuantLib/Index/InterestRate.chs` (`{#enum OvernightIborIndexType{} deriving (Show, Eq)#}`, `{#enum LiborSwapIndexType{} deriving (Show, Eq)#}`, `{#enum IborIndexType{} add prefix = "Ibor" deriving (Show, Eq)#}`, each also listed in the module's export list) and consumed directly as plain enum arguments by `qlCreateONIndex`/`qlCreateLiborSwapIndex`/`qlCreateIbor` respectively — no `mergeEnums`/per-variant Market-style machinery here (unlike calendars), since these are flat enums, not parameterized per case.

## Reconciling existing index enums against upstream

Same idea as [[reconcile-currencies]]/[[reconcile-calendars]]: QuantLib periodically adds new named overnight/Libor/swap indexes, and hasquant's enums silently fall behind since there's no compile-time signal for a missing case. Worth checking whenever asked to "add index support" generally, not just for one named index.

For each family, diff the enum in `cbits/qlEnumObjects.h` against the concrete subclasses declared upstream:
- Overnight → grep `/opt/homebrew/include/ql/indexes/ibor/*.hpp` for `public OvernightIndex` vs `enum OvernightIborIndexType`.
- IBOR/Libor-style → same directory, `public IborIndex` (note: many concrete Libor variants subclass an intermediate class like `Libor`/`DailyTenorLibor` rather than `IborIndex` directly, so a plain `public IborIndex` grep will undercount — check the actual class hierarchy in the header, don't trust the grep count alone).
- Swap-rate → `/opt/homebrew/include/ql/indexes/swap/*.hpp` vs `enum LiborSwapIndexType`.

Do this diff fresh each time rather than trusting a cached list — hasquant's `OvernightIborIndexType` was found to be missing 9 upstream overnight indexes as of one prior check, and QuantLib adds more with each release. Adding each is a Case 1 append (enum + `onIndices[]`/`iborIndices[]`/`swapIndices[]` lambda), not a new binding.

## Case 2: new node/leaf object

Not an enum case — treat it as a new class in the `Index`/`IborIndex`/`OvernightIndex`/`SwapIndex` hierarchy (or a wholly new hierarchy for something like `EquityIndex`/`InflationIndex`) and follow [[add-quantlib-class]]. Its own constructor becomes a `qlXxx(...)` shim function (not a table entry), following [[add-quantlib-method]] for the constructor and any additional methods.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

**Case 1 gotcha:** editing only `cbits/qlEnumObjects.h`/`cbits/qlTermStructure.cpp` (no `.chs` file touched) can leave the incremental build silently stale — under both `cabal build` and `stack build`, neither tracks that a `.chs` file's `#include`d C header changed, so either may report success (`cabal`: "Up to date") without ever re-running c2hs, and a subsequent `cabal test`/`stack test` will pass against the *old* generated enum. Confirmed by checking the generated `dist-newstyle/.../QuantLib/Index/InterestRate.hs`'s (or the stack-equivalent `.stack-work/...` path) timestamp/content after such a change. If in doubt, do a clean build (`cabal clean` / `stack clean`, or delete the specific generated `.hs`) before rebuilding, and verify end-to-end at the value level (construct one of the new cases and print something derived from it — e.g. via a script in `smoke/`), not just "the build succeeded."
