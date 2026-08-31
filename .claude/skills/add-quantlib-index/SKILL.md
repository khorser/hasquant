---
name: add-quantlib-index
description: Add a new QuantLib index (Ibor, overnight, or swap index) binding, or reconcile hasquant's index enums against what's actually available upstream. Use when asked to add, bind, or expose a market index (e.g. a new IBOR tenor/currency, an overnight rate index like SOFR/SONIA, or a swap-rate index), or to check/audit/sync the list of supported indexes — sourced from /opt/homebrew/include/ql/indexes/.
---

QuantLib indexes use two shapes here. Inspect the constructor when the class name is ambiguous.

## Which kind is it?

1. **Enum-like named market-convention variant** — a subclass of `IborIndex`, `OvernightIndex`, or `SwapIndex` whose constructor takes *only* the shared shape (a tenor `Period` and/or one or two `YieldTermStructure` handles) with everything else (currency, calendar, day counter, fixing lag) hardcoded by QuantLib inside the subclass itself. `Sofr`, `Sonia`, `Euribor`, `EuriborSwapIsdaFixA` are all this shape. These are dispatched through a shared enum + factory-table pattern, not given their own binding. The named inflation indices (`UKRPI`, `EUHICP`, ..., under `ql/indexes/inflation/`) are a *simpler* variant of this same shape: their constructors take **no** shared-shape parameter at all (not even a tenor/handle — just an optional term-structure handle we don't expose, see `QuantLib.Index.Inflation`), so their table's constructor template takes no argument (`&makeZeroInflationIndex<UKRPI>`) instead of the usual tenor/handle ones. One upstream exception to watch for: `AUCPI`/`YYAUCPI` require explicit `(Frequency, bool revised)` args (no default ctor) unlike every other named inflation index — these two stay hand-written lambdas in the table rather than using its `make*` template, with real market convention values hardcoded (`Quarterly, false` for AU, since AU CPI publishes quarterly unlike the monthly RPI/HICP/CPI indices).
2. **New node/leaf object** — anything that doesn't fit the shared constructor shape above (extra required constructor parameters, a genuinely new base type, or a class outside the `Ibor`/`Overnight`/`Swap`/named-inflation index families, e.g. `bmaindex.hpp`, `equityindex.hpp`, or a *generic* `ZeroInflationIndex`/`YoYInflationIndex` constructor taking a custom family/`Region`/currency — not yet bound, see README's `# TODO`). Follow [[add-quantlib-class]] and [[add-quantlib-method]] instead of this skill.

Check the class's constructor in its header under `/opt/homebrew/include/ql/indexes/` (concrete classes mostly live in `ibor/`, `swap/`) to decide.

## Case 1: enum-like index

There are several parallel enum+table pairs, each following the same lockstep-append rule as [[reconcile-currencies]]/[[reconcile-calendars]] (append only within your group, don't reorder, keep enum and table the same length):

| Kind | Enum (`cbits/qlEnumObjects.h`) | Table (`cbits/qlTermStructure.cpp`) | Factory fn | Shared shape |
|---|---|---|---|---|
| IBOR, standard tenor | `enum IborIndexType` | `iborIndices[]`'s Standard block | `qlCreateIbor` | `(Period tenor, YieldTermStructureHandle ts)` |
| IBOR, daily tenor | `enum IborDailyTenorIndexType` | `iborIndices[]`'s DailyTenor block | `qlCreateIbor` | `(Size fixingDays, YieldTermStructureHandle ts)` |
| IBOR, overnight | `enum IborONIndexType` | `iborIndices[]`'s Overnight block | `qlCreateIbor` | `(YieldTermStructureHandle ts)` |
| Overnight (true O/N compounding index, e.g. SOFR/SONIA) | `enum OvernightIborIndexType` | `onIndices[]` (`makeONIndex`) | `qlCreateONIndex` | `(YieldTermStructureHandle ts)` |
| Swap-rate | `enum LiborSwapIndexType` | `swapIndices[]` (`makeSwapIndex`) | `qlCreateLiborSwapIndex` | `(Period tenor, YieldTermStructureHandle h1, YieldTermStructureHandle h2)` |
| Zero inflation | `enum ZeroInflationIndexType` | `zeroInflationIndices[]` | `qlCreateZeroInflationIndex` | *(none)* |
| YoY inflation | `enum YoYInflationIndexType` | `yoyInflationIndices[]` | `qlCreateYoYInflationIndex` | *(none)* |

Each enum's comment states which table (or block of the table) it must match the order of, and vice versa — a mismatch is a silent wrong-index-constructed bug, not a compile error, exactly like the currency/calendar tables.

**IBOR is split into three enums, not one.** `iborIndices[]` is a single flat C++ array, but it's laid out as three contiguous blocks (Standard, then DailyTenor, then Overnight — see the block comments in `cbits/qlTermStructure.cpp`), each with its own C enum. `IborIndexType`/`IborDailyTenorIndexType` end with a trailing `...Last` sentinel value (not a real index — it only marks "insert new values above this line" and is stripped out on the Haskell side); `IborONIndexType`, being the last block, has none. This exists because — unlike Overnight/Swap, where every variant takes the exact same constructor shape — IBOR variants need one of three differently-shaped runtime arguments (a `(Period, ts)` tenor, an `(fixingDays, ts)` pair, or just `(ts)`), so `QuantLib/Index/InterestRate.chs` layers a hand-written `IborConstructor` wrapper ADT on top of the three raw enums (`iborIndex :: IborConstructor -> ...`) instead of exposing them directly, unlike `OvernightIborIndexType`/`LiborSwapIndexType`, which callers use as bare enum values with no wrapper.

**Index hierarchy note (inflation-specific):** unlike Ibor/Overnight/Swap indices (which collapse straight into their family's single Haskell type), `ZeroInflationIndex`/`YoYInflationIndex` sit under a real intermediate `InflationIndex` Haskell type (`Index -> InflationIndex -> {Zero,YoY}`, mirroring `InterestRateIndex`'s own 3-level shape in `Internal/Type.hs`), even though today nothing needs to treat "any inflation index" polymorphically. This was a deliberate choice (not the usual "leaf directly under the root" shape a Case-1 family would otherwise get) specifically to leave room for the generic-constructor Case-2 follow-up noted above, without a later restructuring. If you're adding a similar enum-dispatched family that has no foreseeable generic-constructor follow-up, prefer the flatter direct-leaf shape (`GenIndex a` with a single `AnyOf`, like `IborIndex`/`SwapIndex` sit under `InterestRateIndex`) — this extra level is the exception, not the default.

Steps:
1. Confirm the new index class's constructor matches the shared shape for its family (check the header under `ql/indexes/ibor/` or `ql/indexes/swap/`). For IBOR specifically, this also decides which of the three enums/blocks it belongs to — Standard (`(Period, ts)`), DailyTenor (a settlement-days `Size`/`int`, e.g. subclasses of `DailyTenorLibor`), or Overnight (no tenor argument at all, e.g. `FooLiborON`).
2. Append the new variant name to the matching `enum` in `cbits/qlEnumObjects.h` — for IBOR, insert directly above that enum's trailing `...Last` sentinel (or at the end, for `IborONIndexType`, which has none).
3. Append the matching entry to the matching table/block in `cbits/qlTermStructure.cpp`, at the same relative position, e.g. for an overnight index: `, &makeONIndex<NewIndexName>`. Each table has a `make*` function template just above the `extern "C"` block (they live there because a template cannot be declared with C linkage); pick the one whose constructor shape matches — the Ibor table has three (`makeIborIndex` for a tenor `Period`, `makeIborIndexTS` for a bare curve, `makeIborIndexMonths` for a plain month count). An index whose constructor fits none of them keeps a hand-written lambda in the table, as `AUCPI`/`YYAUCPI` do; if you write one, spell its return type as the table's base index type (that is what the existing `static_cast<ZeroInflationIndex *>` in those two lambdas is for) — the table's `using make*Idx = Base *(*)(...)` alias rejects anything else at compile time, which is also what stops a subclass-returning entry from silently mislabelling its `alloc()` trace.
4. No `.chs`/`Internal/Type.hs` changes needed for a new *case* of an existing enum. `OvernightIborIndexType`/`LiborSwapIndexType` are exposed as flat c2hs enums in `QuantLib/Index/InterestRate.chs` and consumed directly as plain enum arguments by `qlCreateONIndex`/`qlCreateLiborSwapIndex` — no generation machinery involved, since these are flat enums with a uniform shape, not parameterized per case. IBOR's three split enums are consumed by `deriveIborConstructor` (`QuantLib/Internal/Syntax.hs`), a TH combinator that reifies all three at build time and regenerates the `IborConstructor` wrapper ADT and its dispatch functions from them — so a new Standard/DailyTenor/Overnight IBOR case is *also* zero-touch on the Haskell side; you never edit `IborConstructor` by hand.

## Reconciling existing index enums against upstream

Same idea as [[reconcile-currencies]]/[[reconcile-calendars]]: QuantLib periodically adds new named overnight/Libor/swap indexes, and hasquant's enums silently fall behind since there's no compile-time signal for a missing case. Worth checking whenever asked to "add index support" generally, not just for one named index.

For each family, diff the enum in `cbits/qlEnumObjects.h` against the concrete subclasses declared upstream:
- Overnight → grep `/opt/homebrew/include/ql/indexes/ibor/*.hpp` for `public OvernightIndex` vs `enum OvernightIborIndexType`.
- IBOR/Libor-style → same directory, `public IborIndex` (note: many concrete Libor variants subclass an intermediate class like `Libor`/`DailyTenorLibor` rather than `IborIndex` directly, so a plain `public IborIndex` grep will undercount — check the actual class hierarchy in the header, don't trust the grep count alone). Diff against all three IBOR enums combined (`IborIndexType`/`IborDailyTenorIndexType`/`IborONIndexType`), and check the class's own constructor shape (see step 1 above) to know which one a missing variant belongs to.
- Swap-rate → `/opt/homebrew/include/ql/indexes/swap/*.hpp` vs `enum LiborSwapIndexType`.

Do this diff fresh each time rather than trusting a cached list — hasquant's `OvernightIborIndexType` was found to be missing 9 upstream overnight indexes as of one prior check, and QuantLib adds more with each release. Adding each is a Case 1 append (enum + an `onIndices[]`/`iborIndices[]`/`swapIndices[]` entry), not a new binding.

## Case 2: new node/leaf object

Not an enum case — treat it as a new class in the `Index`/`IborIndex`/`OvernightIndex`/`SwapIndex` hierarchy (or a wholly new hierarchy for something like `EquityIndex`/`InflationIndex`) and follow [[add-quantlib-class]]. Its own constructor becomes a `qlXxx(...)` shim function (not a table entry), following [[add-quantlib-method]] for the constructor and any additional methods.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

**Case 1:** the change touches no `.chs` file, so the run-hasquant skill's stale-build gotcha applies — confirmed here by checking the generated `dist-newstyle/.../QuantLib/Index/InterestRate.hs` (or the `.stack-work/...` equivalent) after such a change. Clean-build if in doubt, and confirm at the value level with a `smoke/` script that constructs one of the new cases and prints something derived from it.
