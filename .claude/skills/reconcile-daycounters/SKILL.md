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
2. **`dayCounters[]`** (`makeDayCounter` lambdas, `DayCounter *(*)(int convention)`) in `cbits/qlMisc.cpp` — one lambda per type, same order. Types with a real `Convention` sub-choice cast the int, e.g. `new ActualActual((ActualActual::Convention) conv)`; types without one ignore it, e.g. `new Actual360()`.
3. **Per-type `Convention` enums** in `cbits/qlEnumC2HS.h` (e.g. `enum ActualActualConvention`, `enum Thirty360Convention`, `enum Actual365FixedConvention`) — only for types with a real multi-value `Convention` enum upstream, exact same "single value → don't bother, real choice → expose" rule as calendar `Market` enums.
4. **`QuantLib/Internal/CalendarEnum.chs`**: `{#enum DayCounterType{} add prefix = "DayCounter__" deriving(Show, Eq)#}`, one `{#enum XxxConvention{} add prefix = "Xxx__" deriving(Show, Eq)#}` per parameterized type, and `$(mergeEnums "DayCounterConstructor" "mapDayCounter" ''DayCounterType "Convention" ''DayCounterExtra)` — the same TH machinery as calendars, just named `"Convention"` instead of `"Market"`.
5. **The escape hatch — `DayCounterExtra`**: for day counters whose constructor doesn't fit `DayCounter *(*)(int)` at all — takes something other than a plain int/enum, e.g. `Business252(Calendar)`, or `Actual36525`/`Actual366`'s plain `bool includeLastDay` (represented as a `Bool` field directly rather than manufacturing a 2-value `Convention` enum for it — a deliberate choice made when these two were added; prefer this over inventing an enum when the upstream parameter is naturally non-enum, e.g. a bool or an object). These get their own dedicated C shim function (not a `dayCounters[]` entry), e.g. `qlDayCounterBusiness252(Calendar*, char**)` / `qlDayCounterActual36525(int includeLastDay, char**)`, an `Extra__Xxx !FieldType` case added to `data DayCounterExtra = ...` in `CalendarEnum.chs`, and a `{#fun qlDayCounterXxx{...}#}` binding plus a `dayCounter (Xxx x) = qlDayCounterXxx x` pattern clause in `QuantLib/Time/Schedule.chs`, added **before** the catch-all `dayCounter x = uncurry qlDayCounter $ mapDayCounter x`. Note `mergeEnums` strips the `Extra__` prefix, so the usable Haskell constructor is just `Xxx` (`Business252`, `Actual36525`, ...), not `Extra__Xxx`.
6. **Upstream source of truth**: `/opt/homebrew/include/ql/time/daycounters/*.hpp`, one header per type (excluding `all.hpp`, `yearfractiontodate.hpp`).

### Steps

1. Diff `DayCounterType` against the headers in `ql/time/daycounters/` for brand-new types.
2. Confirm `dayCounters[]` is the same length/order as `DayCounterType`.
3. For every type in scope, check its real constructor signature upstream (not just whether a `Market`/`Convention`-shaped enum happens to exist) to decide which of the three buckets above it falls into — int-indexed with no choice, int-indexed with a real `Convention` enum, or `DayCounterExtra` escape hatch. Types that *look* covered by the simple array (e.g. `Business252` briefly looked "missing" from `DayCounterType` during one check) may already be fully wired via `DayCounterExtra` instead — check there before concluding something's a gap.
4. When adding a brand-new int-indexed type: append (don't reorder) `DayCounterType` in `qlEnumObjects.h` and the matching lambda in `qlMisc.cpp`'s `dayCounters[]` at the same relative position — same lockstep-append rule as currencies/calendars.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

**Gotcha:** same as [[reconcile-currencies]]/[[reconcile-calendars]] — editing only `cbits/` files (no `.chs` touched) can leave the incremental build silently stale under both `cabal build` and `stack build`. If in doubt, do a clean build, and verify end-to-end at the value level (construct one of the new day counters and check a day-count/year-fraction actually differs the way it should — e.g. via a script in `smoke/`), not just "the build succeeded."
