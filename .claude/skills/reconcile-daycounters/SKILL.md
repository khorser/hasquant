---
name: reconcile-daycounters
description: Check whether hasquant's day counter enum and BusinessDayConvention are missing anything that exists in the installed QuantLib. Use when asked to reconcile, audit, sync, or add support for a day counter or business day convention.
---

Two mostly-unrelated things to check; do both.

## BusinessDayConvention

A plain flat enum, no per-value parameterization — `enum BusinessDayConvention {...}` in `cbits/qlEnumC2HS.h`, compared directly against `/opt/homebrew/include/ql/time/businessdayconvention.hpp`'s `enum BusinessDayConvention`. Just diff the value lists; append (in upstream order) if anything's missing. No factory table, no lockstep-array concern here — c2hs exposes it as a single `{#enum#}` in `QuantLib/Time/Calendar.chs`.

## Day counters

Same int-indexed enum + factory-table shape as [[reconcile-currencies]]/[[reconcile-calendars]], **plus** a second, separate mechanism for day counters that don't fit that shape.

### Files involved

1. **`enum DayCounterType`** in `cbits/qlEnumObjects.h` — ordered list, comment says it must match `qlMisc.cpp:dayCounters`.
2. **`dayCounters[]`** (`makeDayCounter` lambdas, `DayCounter *(*)(int convention)`) in `cbits/qlMisc.cpp` — one lambda per type, same order. Types with a real `Convention` sub-choice cast the int to that enum, e.g. `new ActualActual((ActualActual::Convention) conv)`; types with a plain upstream `bool` cast it to `bool`, e.g. `new Actual360((bool) conv)`; types with no choice at all ignore it, e.g. `new Actual364()`.
3. **Per-type sub-choice markers** in `cbits/qlEnumC2HS.h` + `QuantLib/Internal/CalendarEnum.chs` — either a real `Convention` enum (`enum ActualActualConvention`, `enum Thirty360Convention`, `enum Actual365FixedConvention` in `qlEnumC2HS.h`, each exposed via `{#enum XxxConvention{} add prefix = "Xxx__" deriving(Show, Eq)#}`) for types with a real multi-value convention upstream, or a `type XxxConvention = Bool` synonym (declared directly in `CalendarEnum.chs`, no C header involved) for types whose only upstream parameter is a plain `bool` (e.g. `type Actual360Convention = Bool`). Same "single value → don't bother, real choice → expose" rule as calendar `Market` enums, just with a second way to say "yes, there's a choice, and it's a bool."
4. **`QuantLib/Internal/CalendarEnum.chs`**: `{#enum DayCounterType{} add prefix = "DayCounter__" deriving(Show, Eq)#}`, one `{#enum XxxConvention{}...#}` or `type XxxConvention = Bool` per parameterized type, and `$(mergeEnums "DayCounterConstructor" "mapDayCounter" ''DayCounterType "Convention" ''DayCounterExtra)` — the same TH machinery as calendars, just named `"Convention"` instead of `"Market"`. `mergeEnums` (`QuantLib/Internal/Syntax.hs`) looks up a type named `<Value><suffix>` for every main enum value and classifies it: not found → plain nullary constructor; a real enum → cross-product with its named values (`Actual365FixedStandard`, ...); a `type X = Bool` synonym → **one** constructor carrying a runtime `Bool` field (`Actual360 :: Bool -> DayCounterConstructor`) instead of picking among fixed named values, since there's nothing to pick among until someone actually calls it.
5. **The escape hatch — `DayCounterExtra`**: for day counters whose constructor doesn't fit `DayCounter *(*)(int)` at all — takes something that isn't a plain int/enum/bool, e.g. `Business252(Calendar)` or the `Schedule`-taking `ActualActualBond'`/`ActualActualISMA'` below. (A plain `bool` upstream arg, like `Actual36525`/`Actual366`/`Actual360`'s `includeLastDay`, is **not** this case anymore — it gets a `type XxxConvention = Bool` marker per item 3 above and flows through the generic `qlDayCounter`/`mergeEnums` path instead, since `mergeEnums` now understands bools directly. Reserve `DayCounterExtra` for args that are genuinely neither an int, enum, nor bool — objects like `Calendar`/`Schedule`.) These get their own dedicated C shim function (not a `dayCounters[]` entry), e.g. `qlDayCounterBusiness252(Calendar*, char**)`, an `Extra__Xxx !FieldType` case added to `data DayCounterExtra = ...` in `CalendarEnum.chs`, and a `{#fun qlDayCounterXxx{...}#}` binding plus a `dayCounter (Xxx x) = qlDayCounterXxx x` pattern clause in `QuantLib/Time/Schedule.chs`, added **before** the catch-all `dayCounter x = uncurry qlDayCounter $ mapDayCounter x`. Note `mergeEnums` strips the `Extra__` prefix, so the usable Haskell constructor is just `Xxx` (`Business252`, `ActualActualBond'`, ...), not `Extra__Xxx`.
6. **Upstream source of truth**: `/opt/homebrew/include/ql/time/daycounters/*.hpp`, one header per type (excluding `all.hpp`, `yearfractiontodate.hpp`).

### Steps

1. Diff `DayCounterType` against the headers in `ql/time/daycounters/` for brand-new types.
2. Confirm `dayCounters[]` is the same length/order as `DayCounterType`.
3. For every type in scope, check its real constructor signature upstream (not just whether a `Market`/`Convention`-shaped enum happens to exist) to decide which of the four buckets above it falls into — int-indexed with no choice, int-indexed with a real `Convention` enum, int-indexed with a plain `bool` (the `type XxxConvention = Bool` marker), or `DayCounterExtra` escape hatch for non-int/enum/bool args. Types that *look* covered by the simple array (e.g. `Business252` briefly looked "missing" from `DayCounterType` during one check) may already be fully wired via `DayCounterExtra` instead — check there before concluding something's a gap.
4. When adding a brand-new int-indexed type: append (don't reorder) `DayCounterType` in `qlEnumObjects.h` and the matching lambda in `qlMisc.cpp`'s `dayCounters[]` at the same relative position — same lockstep-append rule as currencies/calendars.

### `DayCounterExtra` can add a capability *alongside* an unchanged existing entry

Not every `DayCounterExtra` case is for a net-new day counter. `ActualActual`'s real constructor is `ActualActual(Convention c, Schedule schedule = Schedule())` — the `Schedule` matters for `ISMA`/`Bond` specifically (the other 5 conventions never touch it), but the existing `dayCounters[]`-based entry (giving the already-used, schedule-less `ActualActualBond`/`ActualActualISDA`/... constructors) silently defaults to an empty `Schedule()`. When this kind of gap shows up in an *already-covered* type, don't replace the existing `DayCounterType` entry or touch its callers — add **separate, additional** `DayCounterExtra` cases alongside the untouched original.

Prefer **specific, dedicated constructors over a generic parameterized one** here: rather than one `ActualActual :: ActualActualConvention -> Schedule -> DayCounterConstructor` taking the convention as an argument, add `ActualActualBond' :: Schedule -> DayCounterConstructor` and `ActualActualISMA' :: Schedule -> DayCounterConstructor` (the `'` suffix matches this codebase's existing "alternate parameter list" convention, e.g. `swap`/`swap'`, `cleanPrice`/`cleanPrice'`) — one dedicated case per convention that actually needs the schedule, each hardcoding its `ActualActual::Convention` value inside its own C++ shim function (`qlDayCounterActualActualBond`/`qlDayCounterActualActualISMA`, each taking only a `Schedule*`, no convention parameter at all). This is both a better fit for how the rest of the library is designed (concrete named functions, not generic enum-driven ones — same reasoning as reusing `ActualActualBond` instead of inventing a raw-enum reference) and sidesteps a real c2hs limitation entirely (see below) rather than working around it.

`mergeEnums`'s auto-generated nullary constructors (`ActualActualBond`, `ActualActualISDA`, ...) and the manually-added `Extra__ActualActualBond'`/`Extra__ActualActualISMA'` cases (stripped to `ActualActualBond'`/`ActualActualISMA'`) coexist fine in the same `DayCounterConstructor` sum type as long as the names differ — no need to migrate existing callers just to add an opt-in capability.

### Two more gotchas hit while adding the `ActualActual` schedule case

- **c2hs cross-module `{#import#}` ordering is fragile for internal (`other-modules`) targets — enum types only, and often avoidable.** This is a general project constraint, not specific to day counters — see the relevant bullet in CLAUDE.md for the full explanation and the dedicated-constructor workaround.
- **A new `DayCounterExtra` field's type needs `Show`/`Eq`.** `CalendarEnum.chs` has blanket `deriving instance Show DayCounterConstructor` / `deriving instance Eq DayCounterConstructor` at the bottom, which requires every field of every case to support them. `Calendar`, `Bool`, and similar already do; `Schedule` didn't, and needed real instances added in `QuantLib/Internal/Type.hs` (mirroring `Calendar`'s `unsafePerformIO`-based pattern, but built from `qlScheduleDates` + `preArray`/`peekDayArray` since `Schedule` has no simple "name" accessor like `Calendar`/`Currency`/`DayCounter` do). This is unaffected by the dedicated-constructor-vs-generic-argument choice above — either way, a bare `Schedule` field ends up in `DayCounterExtra`.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

**Gotcha:** same as [[reconcile-currencies]]/[[reconcile-calendars]] — editing only `cbits/` files (no `.chs` touched) can leave the incremental build silently stale under both `cabal build` and `stack build`. If in doubt, do a clean build, and verify end-to-end at the value level (construct one of the new day counters and check a day-count/year-fraction actually differs the way it should — e.g. via a script in `smoke/`), not just "the build succeeded."
