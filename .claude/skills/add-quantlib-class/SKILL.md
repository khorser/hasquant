---
name: add-quantlib-class
description: Add a new QuantLib class binding (new hierarchy root or a class in an existing hierarchy) across the cbits/ C shim and the Haskell QuantLib/ layer. Use when asked to bind a new QuantLib C++ class, add a wrapper for a QuantLib type, or extend an existing binding hierarchy (e.g. TermStructure, Instrument, Index).
---

Adding `QlXXX` touches `cbits/` and `QuantLib/`. Select the matching domain `.cpp` and `.chs` module before starting.

**First, check whether the class needs a dedicated Haskell type at all** — apply AGENTS.md's "don't mirror the C++ hierarchy 1:1" rule. If it doesn't (most `PricingEngine` subclasses, for instance), just bind a constructing function returning the existing parent/grandparent type, e.g. `discountingSwapEngine :: ... -> IO PricingEngine`: no type boilerplate (step 4) and no `AsParent` upcast shim (step 3), since there's no dedicated type to upcast from.

Do not include or exclude a singleton-like class by analogy. Inspect its upstream inheritance and constructors: confirm `Singleton<T>`, deleted or inaccessible construction/copy/move operations, and process-global `instance()` state. A genuine singleton normally binds as free functions over `X::instance()`, with no Haskell object type.

Read upstream documentation for every exposed constructor and method. Add concise Haddock covering behavior, units, formulas, warnings, limitations, and intentional scope cuts.

## Steps

1. **`cbits/qlaux.h`** — add the `using QlXxx = shared_ptr<Xxx>;` line (alongside the existing alphabetical block of `using Ql... = shared_ptr<...>;` lines), plus any other declarations the wrapper needs in this file. Also add `QL_TRACE_NAME(Xxx)` and `QL_TRACE_NAME(QlXxx)` to the trace-label table guarded by `QLTRACK_ALLOCATIONS`.

2. **`cbits/qlTypesC2HS.h`** — add a fake `typedef struct QlXxx QlXxx;` def. This is a c2hs-only stand-in type (the real definition lives in C++; c2hs just needs something to point at).

3. **The matching existing `cbits/*.cpp` domain file** — add `qlFreeXxx` (the finalizer, freeing the `shared_ptr` wrapper) plus the constructor/method shims, following the established exception pattern. Create a new translation unit only for a genuinely new domain; template instantiations belong in the domain's existing Aux file.

4. **`QuantLib/Internal/Type.hs`** — add type and marshalling boilerplate. The shape differs depending on whether this is a **new hierarchy root** or a **class in an existing hierarchy**:

   - **New hierarchy root** (nothing to downcast from), e.g. `TermStructure`:
     - `data CXxx'` (empty data type, the c2hs pointer tag)
     - `newtype GenXxx a = GenXxx {getXxx :: GenForeignPtr a CXxx'}`
     - `type CXxx = ForeignPtr CXxx'`
     - `type Xxx = GenXxx CXxx`
     - `foreign import ccall unsafe "ql.h &qlFreeXxx" qlFreeXxx :: FinalizerPtr CXxx'`
     - `instance Finalizable CXxx' where finalize = qlFreeXxx`
     - `asXxx`, `withXxx`, `withGenXxx`, `peekXxx` functions (mirror `asTermStructure`/`withTermStructure`/`peekTermStructure` in this file).

   - **Class within an existing hierarchy that itself has (or may have) further subclasses**, e.g. `YieldTermStructure` under `TermStructure`:
     - `data CXxx'` (pointer tag) and `type CXxx = ForeignPtr CXxx'`
     - `type Xxx = GenParent (AnyOf CXxx' a)` — nest inside the parent's `Gen*` newtype via `AnyOf`, don't create a new `Gen*`/finalizer of your own.
     - `foreign import ccall "ql.h qlXxxAsParent" qlXxxAsParent :: Ptr CXxx' -> IO (Ptr CParent')` — the upcast function (must already exist as a C shim from step 3, or be added there).
     - `instance Upcastable CXxx' where {type Base CXxx' = CParent'; upcast = qlXxxAsParent}`
     - `asXxx`, `withXxx`, `peekXxx` using `peel`/`newAnyOf` (mirror `asYieldTermStructure`/`withYieldTermStructure`/`peekYieldTermStructure` in this file).

   - **Leaf class with no subclasses of its own**, e.g. `ForwardRateAgreement`/`FxForward` under `Instrument`: same as above but skip the `AnyOf` polymorphism entirely, since nothing ever needs to treat it as "some more-specific-than-parent type, exact subtype unknown" — `type Xxx = GenParent CXxx` (mirror `ForwardRateAgreement`/`FxForward` in `Internal/Type.hs`). Simpler than the `AnyOf` shape above; use this whenever the class is a dead end in the hierarchy.

   **Choose hierarchy levels from actual consumer signatures, not from constructor implementation classes.** If a downstream QuantLib API takes a concrete intermediate base, that base must be a real Haskell type/family member so it can be passed without a downcast; make constructors for its implementation subclasses return that required type. Do not add separate leaves for those implementation subclasses unless a bound API takes one specifically, or it has a calculation/getter that must remain concrete. For example, `LognormalCmsSpreadPricer` takes `CmsCouponPricer`, so CMS pricer constructors return a `CmsCouponPricer` leaf under `FloatingRateCouponPricer`; no separate `LinearTsrPricer` leaf is warranted merely because that is the class constructed.

   A family root returned at its own concrete type peeks with `newCastForeignPtr`; a leaf that must upcast on access peeks with `newGenForeignPtr`. After promoting a former leaf into a family root, change its own peek function accordingly. Array helpers peel once for every `AnyOf` layer below the outer `Gen*`; a root and a leaf at the same depth use the same peel count. These mistakes can compile while walking the wrong hierarchy at runtime.

5. **`QuantLib/<Module>.chs`** — add the `{#pointer}` boilerplate, e.g.:
   `{#pointer *QlXxx as Xxx foreign -> CParent' nocode#}`
   then the `{#fun ...#}` bindings for the class's own methods. Choose the existing module by topical family, per AGENTS.md's module-placement rule; add a module only when no existing family fits.

## Update tools/ql-methods-*.txt

After the binding compiles, update `tools/ql-methods-1.43.txt` for **every** constructor/method the new class exposes, not just the first — see [[add-quantlib-method]] for the status vocabulary.

Before treating an empty `ql/experimental/` header as a missing binding, check its size and deprecation message. QuantLib 1.43 contains forwarding and `this file is empty and will disappear` stubs; zero tracker entries for those files means the class is absent or moved, not overlooked.

## Verification

Run `make` for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

When changing `tools/gen_quantlib_hierarchy.py`, run it against already-bound hierarchies and diff the generated declarations with `QuantLib/Internal/Type.hs`. Exercise the affected root, intermediate, and deepest-leaf shapes; wrong `AnyOf` nesting and upcast depth can compile.
