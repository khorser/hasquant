---
name: add-quantlib-class
description: Add a new QuantLib class binding (new hierarchy root or a class in an existing hierarchy) across the cbits/ C shim and the Haskell QuantLib/ layer. Use when asked to bind a new QuantLib C++ class, add a wrapper for a QuantLib type, or extend an existing binding hierarchy (e.g. TermStructure, Instrument, Index).
---

Adding `QlXXX` (and its wrapper) touches both the C++ shim (`cbits/`) and the Haskell FFI layer (`QuantLib/`). Before starting, ask the user (if not already clear) which concrete `.cpp` file the new definitions belong in, and which `QuantLib/*.chs` module should hold the `{#pointer}` boilerplate — these are chosen per class, not fixed.

**Before doing any of this, check whether the class needs a dedicated Haskell type at all.** Don't mirror QuantLib's C++ hierarchy 1:1 (see CLAUDE.md). Only give a class its own `CXxx'`/`Xxx` type if it has calculations/getters of its own (e.g. `FxForward`'s `fairForwardRate`, `ForwardRateAgreement`'s `forwardRate`) or must be passed around as its own type elsewhere. Otherwise — most `PricingEngine` subclasses, for instance — skip all of this and just bind a constructing function that returns the existing parent/grandparent type directly, e.g. `discountingSwapEngine :: ... -> IO PricingEngine`. There's no type boilerplate (step 4) and no `AsParent` upcast shim (step 3) to write, since there's no dedicated type to upcast from.

## Steps

1. **`cbits/qlaux.h`** — add the `typedef shared_ptr<Xxx> QlXxx;` line (alongside the existing alphabetical block of `typedef shared_ptr<...> Ql...;` lines), plus any other declarations the wrapper needs in this file. Also add both `Xxx` and `QlXxx` to ObjClassName specialiazetions guarded by `QLTRACK_ALLOCATIONS`.

2. **`cbits/qlTypesC2HS.h`** — add a fake `typedef struct QlXxx QlXxx;` def. This is a c2hs-only stand-in type (the real definition lives in C++; c2hs just needs something to point at).

3. **`cbits/<some>.cpp`** (ask the user which file if not already specified) — add `qlFreeXxx` (the finalizer, freeing the `shared_ptr` wrapper) plus any constructor/method C shims needed for this class, following the existing `try { ... } catch (std::exception& er) { return handleException<T>(e, er); }` pattern used throughout. Avoid creating new C++ files unless a new concept is introduced.

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

5. **`QuantLib/<Module>.chs`** — add the `{#pointer}` boilerplate, e.g.:
   `{#pointer *QlXxx as Xxx foreign -> CParent' nocode#}`
   then the `{#fun ...#}` bindings for the class's own methods. Ask the user which module if not already specified, but default to grouping with the closest topically-related family rather than a generic hierarchy-root file, even if the new class's C++ inheritance doesn't literally match that module's other contents — e.g. `FxForward` isn't a C++ subclass of `Forward`, but it lives in `QuantLib/Instrument/Forward.chs` anyway, alongside `ForwardRateAgreement` (also not a `Forward` subclass), because they're the same topical family of forward-settled instruments. Leave the generic root module (e.g. `QuantLib/Instrument.chs`) for universal, hierarchy-wide methods only.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.
