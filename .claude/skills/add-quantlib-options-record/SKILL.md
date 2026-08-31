---
name: add-quantlib-options-record
description: Bind a QuantLib constructor or method that has a long list of trailing defaulted parameters (more than 10, OISRateHelper-scale) by adding a second, full-arity entry point whose trailing params are bundled into a TH-generated options record. Use when a binding to widen has far more optional parameters than the usual handful, or when asked about deriveOptionsRecord, default<Name> records, or a wide-arity constructor.
---

## When this applies

Use only for more than **10** trailing defaulted parameters. Otherwise widen the existing binding and make each defaulted parameter required.

For a wide constructor, keep the narrow signature and add a second full-arity function taking an options record.

## Shape

Worked example, all in `QuantLib/TermStructure/Yield.chs`: `OISRateHelperOpts` / `defaultOISRateHelperOpts` / `oisRateHelperFull` / `oisRateHelperFull'`.

Three layers:

1. **Raw c2hs binding at full C arity**, unexported, trailing-underscore name — `oisRateHelper_`, `oisRateHelper2_`. Widen the *C shim* to full arity rather than maintaining a second near-duplicate one (`cbits/qlTermStructure.cpp`'s `qlOISRateHelper`/`qlOISRateHelper2`).
2. **The existing narrow public functions** keep their original signature and now call that same raw binding, hardcoding upstream's defaults positionally (`oisRateHelper`, `oisRateHelper'`).
3. **The new full-arity public functions** take the leading required args plus one `XxxOpts` record, and expand it into the raw binding (`oisRateHelperFull`, `oisRateHelperFull'`).

Callers override only what they need:

```haskell
oisRateHelperFull days tenor rate idx curve
  defaultOISRateHelperOpts { oisPaymentLag = 2, oisTelescopicValueDates = True }
```

## Steps

1. Widen the C shim in `cbits/` to full upstream arity (see [[add-quantlib-method]] for the marshalling of each parameter shape).
2. Widen the raw `{#fun#}` binding to match, and rename it with a trailing `_` if it wasn't already internal. Don't export it.
3. Rewrite the existing narrow public function(s) as ordinary Haskell wrappers over the raw binding, passing upstream's defaults positionally. Their exported signatures must not change.
4. Add the `$(deriveOptionsRecord ...)` splice — see placement gotcha below. Signature (`QuantLib.Internal.Syntax`):
   `deriveOptionsRecord :: String -> [String] -> [(String, TypeQ, ExpQ)] -> DecsQ` — record name, its type-variable names, then one `(field name, type, default expr)` per field. It generates the record type plus a `default<RecName>` value.
5. Write the full-arity wrapper by hand, projecting each field out of the record.
6. Export `XxxOpts(..)`, `defaultXxxOpts`, and the full-arity function(s) from the module.
7. Update `tools/ql-methods-1.43.txt`: the widened shim now matches upstream's arity, so its status becomes `v` (see [[add-quantlib-method]]).

## Gotchas

- **Splice placement.** `$(deriveOptionsRecord ...)` must go *before every* `{#fun#}` hook in the `.chs` file — put it right after the file's pointer/enum declarations, never between two `{#fun#}` hooks. c2hs always appends its raw `foreign import` stubs at the physical end of the generated module regardless of where a `{#fun#}` hook appears in the source, so a top-level TH splice in between splits the file into declaration groups that can't see each other, breaking every earlier `{#fun#}` wrapper's reference to its own (always-last) stub.
- **Explicit types at the splice site, not reification.** `deriveOptionsRecord` deliberately takes field types verbatim rather than reifying the target function's type: trailing params can each carry their own independent type variable (`fixedRate :: GenQuote a` vs `overnightSpread :: Maybe (GenQuote m)`), and re-deriving which of a reified `ForallT`'s bound variables belong on the record has no precedent in `Internal/Syntax.hs` — `deriveCrossEnum`/`deriveIborConstructor` only ever reify enum/data-constructor shapes, never a function type. The type checker still catches drift at the hand-written wrapper in step 5.
- **Fresh type variables need antiquotation.** A field type mentioning a type variable not otherwise in scope must be built with `varT`/`$(...)` inside the `[t| |]` quote — TH type quotes don't auto-quantify free variables the way an ordinary signature does:
  `("oisOvernightSpread", [t|Maybe (GenQuote $(varT (mkName "m")))|], [|Nothing|])`
  and `"m"` must also appear in the record's type-variable list (argument 2).
- **No pure default available.** A field whose type only exists in IO — `Calendar`, obtainable only via `calendar Null :: IO Calendar` — is `Maybe`-wrapped with a `Nothing` default, and the hand-written wrapper substitutes the real value with `fromMaybe` after constructing one. That's why `OISRateHelperOpts`'s three calendar fields are `Maybe Calendar` while the raw binding takes a plain `Calendar`.
- **Fields not used by every overload.** When two overloads share one options record, mark the ones a given wrapper ignores in the field's comment — e.g. `oisForwardStart` is ignored by `oisRateHelperFull'`, since the second C constructor has no `forwardStart` parameter.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before a full `stack build --test --no-haddock`. Check that the *narrow* entry points still typecheck at their original signatures — that's the property this pattern exists to preserve.
