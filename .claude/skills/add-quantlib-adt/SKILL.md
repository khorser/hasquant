---
name: add-quantlib-adt
description: Decide whether a new QuantLib value type needs a flat tag-based enum, a live/held object, or a nested-ADT-with-on-demand-materialization (Payoff/Exercise-style) -- and build the nested-ADT case if that's the fit. Use when adding a new QuantLib value type, payoff, exercise, or similar structure, or when unsure whether a new binding needs its own pointer type at all.
---

## First: which of the three patterns actually fits?

Choose the representation before binding a value type. Reuse these patterns rather than inventing another one.

1. **Flat tag, no real substructure** — the QuantLib type is fully described by picking one of a fixed set of variants, each with at most a couple of scalar/enum parameters (`DayCounter`, `Calendar`, `Currency`, `BusinessDayConvention`). See `[[reconcile-daycounters]]` for the full mechanism (`mergeEnums` TH machinery, int-indexed factory tables, the `*Extra` escape hatch for non-enum parameters).

2. **Live object, held and passed to many different consumers over its lifetime** — the QuantLib type is a genuine C++ class users construct once and then pass around, query, or feed into other constructors repeatedly (`Option`, `Quote`, `Bond`, `Index`, `TermStructure`, ...). See `[[add-quantlib-class]]` for the full mechanism (`Upcastable`/`GenForeignPtr`/`AnyOf`, the `Gen*`-phantom pattern that lets one value satisfy multiple ancestor-typed consumers).

3. **Nested value type with real structure, but never held long-term** — the QuantLib type has genuine multi-level substructure (a payoff can itself contain another payoff; an exercise can be one of several shapes each with their own sub-cases), but every consumer just builds the underlying C++ object once, hands it to a single C++ constructor call, and is done — nothing ever holds the intermediate object or passes it to a second, different consumer later. This is the shape covered by the rest of this skill.

The deciding question: **does anything ever need to hold a constructed value and pass it to more than one place, or query it after construction?** If yes, it's pattern 2 even if it also has nested substructure. If no — built fresh, used immediately by exactly one C call, discarded — pattern 3 applies, and the `Gen*`/`AnyOf` phantom-flexibility machinery can be skipped entirely (see below for why it isn't needed).

## Pattern 3: nested ADT + on-demand materialization (worked example: Payoff/Exercise, `QuantLib/Internal/Common.chs`)

### 1. The ADTs themselves

Plain Haskell sum types, one per structural level, in the module that will own them (`Enum.chs` for Payoff/Exercise) — ordinary nested `data`/constructors mirroring the upstream class hierarchy's shape, nothing QuantLib-specific about this part. Each level a consumer needs to accept *directly* (not just as a case nested inside a bigger ADT) gets its own type, e.g. `PlainVanillaPayoff`, `StrikedPayoff`, `TypePayoff`, `BasketPayoff`, `Payoff`.

### 2. Pointer-hierarchy plumbing lives in `QuantLib/Internal/Type.hs`, not alongside the ADT

Even though the ADTs live in `Enum.chs`, the C++ pointer-hierarchy machinery for materializing them (phantom tags, `Finalizable`, `Upcastable`) goes in `Type.hs`, matching every other hierarchy in the codebase — see `[[add-quantlib-class]]` step 4 for the exact declaration shape (`data CXxx'`, `foreign import ccall unsafe "ql.h &qlFreeXxx" ...`, `instance Finalizable CXxx' where finalize = qlFreeXxx`, and for non-root levels `instance Upcastable CXxx' where {type Base CXxx' = CParent'; upcast = qlXxxAsParent}` with `qlXxxAsParent` a plain `foreign import ccall` — **not** a c2hs `{#fun#}` binding). One block per ADT level that has an upstream `qlXxxAsYyy` cast shim.

`Enum.chs` can't define these itself: it already imports `Type.hs`, and `Type.hs` can't import the ADTs back without a cycle. This means `Finalizable`, `Upcastable`, `GenForeignPtr`, `newCastForeignPtr`, `newGenForeignPtr`, `freeUpcast`, and `withGenForeignPtr` — normally private to `Type.hs`, since every other hierarchy only ever needs `Type.hs`'s own finished `with*`/`peek*`/`as*` functions — need to be **added to `Type.hs`'s export list**. This is the one export-surface widening this pattern requires; nothing else in `Type.hs`'s privacy story changes.

### 3. `with*` functions: no `Gen*`/`AnyOf` needed

Unlike pattern 2, skip the `Gen*` newtype / `AnyOf` phantom-flexibility wrapper entirely — there's no long-lived value that needs to satisfy multiple different-specificity consumers, so there's nothing for the phantom to buy. Instead, write one CPS-style `with*` function per ADT level, in `Enum.chs`, with the same signature shape it would have had if hand-rolled: `withX :: X -> (Ptr CX' -> IO a) -> IO a` — in practice spelled via a `type QlX = Ptr CX'` alias kept for backward-compatible signatures, paired with a `{#pointer *QlX nocode#}` declaration and a `peekPtr`-out-marshaller on the raw C constructor bindings (see the `c2hs-shim-patterns` skill's `{#pointer#}` section for exactly why both of those are needed and what happens if you get the pragma flags wrong). Each case in the function body is one of:

- **Own-level construction** (the C constructor already returns exactly this level): `qlConstructX ... >>= newCastForeignPtr >>= flip withGenForeignPtr f`.
- **A different, more-specific leaf constructed directly by this case, one hop from here, with no separate ADT/`with*` function of its own** (e.g. `AmericanExercise` inside `Exercise`, which has no standalone `withAmericanExercise`): `qlConstructLeaf ... >>= newGenForeignPtr >>= flip withGenForeignPtr f` (`newGenForeignPtr` bakes in exactly one `Upcastable` hop).
- **A nested ADT that already has its own `with*` function**: delegate to it and add exactly one manual upcast, freed immediately after use: `withSubX sub (\subPtr -> upcast subPtr >>= \p -> f p \`finally\` freeUpcast p)`. This is the composable case — it's what lets `Payoff`'s `Type` case reach 3 hops deep (`PlainVanillaPayoff -> StrikedPayoff -> TypePayoff -> Payoff`) by nesting three single-hop delegations, one per level, instead of hand-computing a multi-hop `newAnyOf` chain up front.
- **A field that's itself the general ADT one level up** (e.g. `BasketPayoff`'s `Average :: Payoff -> Word -> BasketPayoff`): that's a genuine recursive *materialize*, not an upcast — call `withPayoff` (or whichever ADT it nests) recursively for that field, then construct directly at this level: `withPayoff p (\pp -> qlAverageBasketPayoff pp n >>= newCastForeignPtr >>= flip withGenForeignPtr f)`.

### 4. The C++ side is unchanged from every other hierarchy

The `Ql*AsY` upcast shims this needs (`cbits/*.cpp`) are the standard `ret(new QlY(*arg(o)))` shape described in the `c2hs-shim-patterns` skill. If the type already has them from a previous implementation, nothing there changes.

## Stored Haskell callbacks

If a C++ object stores a Haskell callback and invokes it later, the `FunPtr` bracket must span the object's whole use, not only its constructor. Represent the callback-bearing case in the Haskell ADT and expose a continuation such as `withCustomPayoff`; free the callback only after the continuation finishes. An argument-position marshaller would free it as soon as construction returned.

Before exposing a callback abstraction, inspect its consumers. Prefer an upstream inner primitive that lets Haskell own the outer loop; otherwise batch the callback to the coarsest granularity the upstream algorithm supports. Keep a fine-grained callback only when upstream itself consumes one element at a time.

Custom payoff compatibility is consumer-specific. Most pricing engines require a built-in `StrikedTypePayoff`; `FdBlackScholesVanillaEngine` and `FdHestonVanillaEngine` can dereference a failed cast. Use the custom striked-payoff form for those engines and document compatibility on every public consumer that accepts a custom payoff. The supplied option type and strike guide the grid; they do not redefine the callback payoff.

## Verification

Run `make` for a quick C++-only compile check, then a **full** (not incremental) `stack build --test --no-haddock` — this pattern touches `{#pointer#}` declarations across multiple `.chs` files, and an incremental build here once reported success while still running stale code. A wrong hop count still type-checks, so add or extend a `smoke/` script exercising the *deepest* case (most upcast hops) end to end: construct via the deepest nested case, consume it, print something derived (e.g. `isExpired`) — see `smoke/CheckPayoffExerciseUpcast.hs`.
