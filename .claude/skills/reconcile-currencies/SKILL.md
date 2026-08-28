---
name: reconcile-currencies
description: Check whether hasquant's currency enum is missing any currencies that exist in the installed QuantLib, or contains stale/renamed ones. Use when asked to reconcile, audit, sync, or update the list of supported currencies.
---

hasquant represents currencies as a fixed enum + a matching factory table, not individual bindings. Three things must be compared and kept in lockstep:

1. **`enum Ccy`** in `cbits/qlEnumObjects.h` — the ordered list of currency codes hasquant knows about.
2. **`ccys[]`** (an array of `makeCcy` function pointers) in `cbits/qlMisc.cpp` — one `&makeCurrency<XxxCurrency>` entry per enum value, in the **same order**. `makeCurrency` is the one-line function template just above the table; its return type is spelled `Currency *` rather than `C *` on purpose, since `alloc()` takes the trace label from its argument's static type and these are freed through `Currency *`. The comment above each says as much: `enum Ccy` must match the order of `ccys[]` and vice versa.
3. **QuantLib's own currency classes**, declared across `/opt/homebrew/include/ql/currencies/*.hpp` (`africa.hpp`, `america.hpp`, `asia.hpp`, `crypto.hpp`, `europe.hpp`, `oceania.hpp`, plus the aggregate `all.hpp`) — the source of truth for which `XxxCurrency` classes actually exist upstream.

## Steps

1. Extract the full `Ccy` enum list from `cbits/qlEnumObjects.h`.
2. Extract the full `ccys[]` entry list from `cbits/qlMisc.cpp`, in order — confirm it's the same length and same order as the enum (a mismatch here is a silent, dangerous bug: wrong currency gets constructed at runtime with no compile error).
3. Grep `/opt/homebrew/include/ql/currencies/*.hpp` for `class XxxCurrency` declarations to get QuantLib's full currency list.
4. Diff:
   - Currencies in QuantLib but missing from `Ccy`/`ccys[]` → candidates to add.
   - Currencies in `Ccy`/`ccys[]` but no longer declared upstream (renamed/removed, e.g. legacy pre-euro currencies) → candidates to flag, not necessarily remove (existing users may depend on them).
5. When adding a new currency, append (don't reorder) both `enum Ccy` in `cbits/qlEnumObjects.h` and the matching `&makeCurrency<...>` entry in `cbits/qlMisc.cpp`'s `ccys[]` at the same relative position, to keep the two lists in lockstep.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

This change touches no `.chs` file, so the run-hasquant skill's stale-build gotcha applies: clean-build if in doubt, and confirm at the value level with a `smoke/` script that constructs one of the new currencies and prints something derived from it.
