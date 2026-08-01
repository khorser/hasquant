---
name: add-quantlib-class
description: Add a new QuantLib class binding (new hierarchy root or a class in an existing hierarchy) across the cbits/ C shim and the Haskell QuantLib/ layer. Use when asked to bind a new QuantLib C++ class, add a wrapper for a QuantLib type, or extend an existing binding hierarchy (e.g. TermStructure, Instrument, Index).
---

Adding `QlXXX` (and its wrapper) touches both the C++ shim (`cbits/`) and the Haskell FFI layer (`QuantLib/`). Before starting, ask the user (if not already clear) which concrete `.cpp` file the new definitions belong in, and which `QuantLib/*.chs` module should hold the `{#pointer}` boilerplate — these are chosen per class, not fixed.

## Steps

1. **`cbits/qlaux.h`** — add the `typedef shared_ptr<Xxx> QlXxx;` line (alongside the existing alphabetical block of `typedef shared_ptr<...> Ql...;` lines), plus any other declarations the wrapper needs in this file.

2. **`cbits/qlTypesC2HS.h`** — add a fake `typedef struct QlXxx QlXxx;` def. This is a c2hs-only stand-in type (the real definition lives in C++; c2hs just needs something to point at).

3. **`cbits/<some>.cpp`** (ask the user which file if not already specified) — add `qlFreeXxx` (the finalizer, freeing the `shared_ptr` wrapper) plus any constructor/method C shims needed for this class, following the existing `try { ... } catch (std::exception& er) { return handleException<T>(e, er); }` pattern used throughout.

4. **`QuantLib/Internal/Type.hs`** — add type and marshalling boilerplate. The shape differs depending on whether this is a **new hierarchy root** or a **class in an existing hierarchy**:

   - **New hierarchy root** (nothing to downcast from), e.g. `TermStructure`:
     - `data CXxx'` (empty data type, the c2hs pointer tag)
     - `newtype GenXxx a = GenXxx {getXxx :: GenForeignPtr a CXxx'}`
     - `type CXxx = ForeignPtr CXxx'`
     - `type Xxx = GenXxx CXxx`
     - `foreign import ccall unsafe "ql.h &qlFreeXxx" qlFreeXxx :: FinalizerPtr CXxx'`
     - `instance Finalizable CXxx' where finalize = qlFreeXxx`
     - `asXxx`, `withXxx`, `withGenXxx`, `peekXxx` functions (mirror `asTermStructure`/`withTermStructure`/`peekTermStructure` in this file).

   - **Class within an existing hierarchy**, e.g. `YieldTermStructure` under `TermStructure`:
     - `data CXxx'` (pointer tag) and `type CXxx = ForeignPtr CXxx'`
     - `type Xxx = GenParent (AnyOf CXxx' a)` — nest inside the parent's `Gen*` newtype via `AnyOf`, don't create a new `Gen*`/finalizer of your own.
     - `foreign import ccall "ql.h qlXxxAsParent" qlXxxAsParent :: Ptr CXxx' -> IO (Ptr CParent')` — the upcast function (must already exist as a C shim from step 3, or be added there).
     - `instance Upcastable CXxx' where {type Base CXxx' = CParent'; upcast = qlXxxAsParent}`
     - `asXxx`, `withXxx`, `peekXxx` using `peel`/`newAnyOf` (mirror `asYieldTermStructure`/`withYieldTermStructure`/`peekYieldTermStructure` in this file).

5. **`QuantLib/<Module>.chs`** (ask the user which module if not already specified) — add the `{#pointer}` boilerplate, e.g.:
   `{#pointer *QlXxx as Xxx foreign -> CParent' nocode#}`
   then the `{#fun ...#}` bindings for the class's own methods.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `cabal build`.
