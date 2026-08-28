---
name: reconcile-calendars
description: Check whether hasquant's calendar enum is missing any countries/markets that exist in the installed QuantLib, or is out of sync with it. Use when asked to reconcile, audit, sync, or add support for a calendar, country, or market.
---

Trickier than [[reconcile-currencies]]: calendars are keyed by country, but several countries have multiple sub-markets (e.g. `UnitedStates::Market` has `Settlement`, `NYSE`, `GovernmentBond`, `NERC`, `LiborImpact`, `FederalReserve`), so there's an extra layer of per-country enums to keep in sync, and a Template Haskell macro that stitches them together.

## Files involved

1. **`enum CalendarCountry`** in `cbits/qlEnumObjects.h` — the ordered list of countries. Comment above it says it "should match with the order of `qlMisc.cpp:calendars`".
2. **`calendars[]`** (an array of `makeCal` function pointers, `Calendar *(*)(int market)`) in `cbits/qlMisc.cpp` — one entry per country, same order as `CalendarCountry`, built from the two constructor templates just above the table: `&makeMarketCalendar<UnitedStates>` for a country with sub-markets (it casts the `market` int to that country's own `Market` enum), `&makeCalendar<Japan>` for one without (it ignores the argument). Both return `Calendar *`, not the concrete type — `alloc()` labels the trace from that, and these are freed through `Calendar *`.
3. **Per-country `Market` enums** in `cbits/qlEnumC2HS.h`, e.g. `enum UnitedStatesMarket {Settlement, NYSE, GovernmentBond, NERC, LiborImpact, FederalReserve};` — only exists for countries that have a nested `Market` enum in QuantLib. Must match QuantLib's own enum values, in order.
4. **`QuantLib/Internal/CalendarEnum.chs`** — the Haskell side:
   - `{#enum CalendarCountry{} add prefix = "Country__" deriving(Show, Eq)#}` for the country list.
   - one `{#enum XxxMarket{} add prefix = "Xxx__" deriving(Show, Eq)#}` per parameterized country (only for countries that have step 3's enum).
   - all of it gets combined by `$(mergeEnums "CalendarConstructor" "mapCalendar" ''CalendarCountry "Market" ''CalendarExtra)` (a TH macro) — a new parameterized country needs its `XxxMarket` c2hs `{#enum#}` added here too, following the naming convention `<Country>Market` / prefix `"<Country>__"`, so `mergeEnums` picks it up automatically by matching the `Country ++ "Market"` type name.
5. **Upstream source of truth**: `/opt/homebrew/include/ql/time/calendars/*.hpp`, one header per country. Check each header for a nested `class Market` / `enum Market` inside the `Calendar::Xxx` class to know whether step 3 applies.

## Steps

1. List countries in `cbits/qlEnumObjects.h`'s `CalendarCountry` and diff against the headers in `ql/time/calendars/` to find brand-new countries. Do this diff fresh each time — QuantLib adds new countries with each release.
2. Confirm `calendars[]` in `cbits/qlMisc.cpp` is the same length/order as `CalendarCountry` (a mismatch silently constructs the wrong country's calendar at runtime — no compile error).
3. For every country already in scope — not just new ones — check its header for a nested `Market` enum and compare against what hasquant currently does for it. Three cases:
   - **No `Market` enum, or exactly one value** (e.g. `Chile::Market {SSE}`): treat as market-less — use `&makeCalendar<Chile>`, which ignores the `market` argument and calls the constructor with its default, same as `Japan`/`HongKong`.
   - **Already-parameterized country whose `Market` enum gained new values upstream** (found in practice: `UnitedStates` gained `SOFR`; `Israel` gained `SHIR`/`Telbor`) — append the new value(s) to the existing `enum XxxMarket {...}` in `cbits/qlEnumC2HS.h`, in upstream order. No `.chs`/`calendars[]` change needed — the existing `{#enum XxxMarket{}#}` line and `(Xxx::Market) market` cast pick up new values automatically on rebuild.
   - **A country currently treated as market-less that gained a `Market` enum with more than one value** (found in practice: `Australia`, `NewZealand`, `Poland` all went from no-argument constructors to `explicit Xxx(Market market = ...)`) — this needs *promoting*: add `enum XxxMarket {...}` to `cbits/qlEnumC2HS.h`, add `{#enum XxxMarket{} add prefix = "Xxx__" deriving(Show, Eq)#}` to `QuantLib/Internal/CalendarEnum.chs`, and change the `calendars[]` entry from `&makeCalendar<Australia>` to `&makeMarketCalendar<Australia>`. Double check the class's actual constructor signature upstream first (some `Market` enums exist without ever being wired into a constructor overload).
4. When adding a brand-new country: append (don't reorder) `CalendarCountry` in `qlEnumObjects.h` and the matching entry in `qlMisc.cpp`'s `calendars[]` at the same relative position — same lockstep-append rule as [[reconcile-currencies]].

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

A `cbits/`-only change touches no `.chs` file, so the run-hasquant skill's stale-build gotcha applies: clean-build if in doubt, and confirm at the value level with a `smoke/` script that constructs one of the new calendars and prints something derived from it.
