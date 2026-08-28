---
name: audit-allocations
description: Audit cbits/ for gaps in the trackAllocations tracing instrumentation (untracked new/delete/malloc/free sites, alloc/free class-name mismatches, partial-construction exception safety) and verify with tools/alloc-summary.py. Use when asked to review, extend, or fix trackAllocations coverage, or to check cbits/ for memory leaks/double-frees.
---

Procedure for auditing whether every allocation/deallocation in the C++ shim (`cbits/`) is
visible to the `trackAllocations` tracing mechanism, and for checking `cbits/` for real
leaks/double-frees along the way. Read `c2hs-shim-patterns` first if you're new to `cbits/`
marshalling conventions generally — this skill is specifically about the tracing/memory-safety
angle, not shim-writing mechanics.

## The tracing mechanism

Defined in `cbits/qlaux.h`, gated by the `trackAllocations` cabal flag (`-DQLTRACK_ALLOCATIONS=<path>`,
falling back to the `QLTRACK_ALLOCATIONS` env var at runtime):

- `arg(p)` — pass-through read of a pointer received from Haskell; not a lifecycle event.
- `alloc(p)` — marks a freshly-`new`'d object as "allocated." Ambiguous by design: for an object
  immediately absorbed into a `shared_ptr` control block (`ret(new QlX(alloc(new X(...))))`), it
  deliberately has no matching free, ever. For a plain value type returned and freed directly
  later (`return alloc(leg);`, freed via `qlFreeLeg`/`del()`), it *is* expected to pair with a
  free. `tools/alloc-summary.py` tells the two apart per-pointer, not per-class.
- `ret(p)` — marks a pointer as "returned to Haskell"; always pairs with `del()`.
- `del(p)` — the generic free: `delete p` plus a `deleting`/`deleted` trace pair (skips tracing,
  but still deletes, when `p` is null — see "Null pointers" below).
- `DUP(p)` / `qlFreeString(p)` — the `strdup`/`free` equivalents for `char*`.
- `TP`/`TP2` macros — the low-level primitives `alloc`/`ret`/`del` are built from; reach for these
  directly only where the generic templates don't fit (see "Array frees" below).
- `retPtrArray(p)` / `allocAs<Base>(p)` — see "Two label helpers" below.

Verify with `tools/alloc-summary.py <trace>`, which pairs `returned`/`allocated`/`Duplicate string`
(acquire) against `deleting`/`Freeing string` (release) per `(class, pointer)`, ignoring `deleted`/
`arg`. A negative final balance is reported as **over-freed** (double free, or freed through the
wrong type); a positive one as a **leak**, unless every acquisition of that pointer was via `alloc()`
and nothing of that class is ever freed anywhere (then it's a `shared_ptr` payload, not a leak —
`--census` lists these separately). Exit code is 1 if anything leaked or over-freed.

**Build gotcha** (see `run-hasquant` skill for the full procedure): the `trackAllocations` flag
alone does not force `cbits` to recompile. Delete `.stack-work/dist/*/build/cbits` and the stale
`libHShasquant*` artifacts before rebuilding, and confirm tracing actually compiled in with
`strings <built .o> | grep -c allocated` before trusting an empty/clean trace.

## Checklist

**1. Every raw `new`/`malloc`/`strdup`/`calloc` routes through `alloc`/`ret`/`DUP`.** Grep for
each and check the exceptions:
- `delete[]`/array frees can't use the generic `del()` template (it does scalar `delete`) — use a
  manual `TP2("deleting", p); ...; TP2("deleted", p);` pair instead, guarded by `if (p)` (see
  `qlFreeInts`/`qlFreeDoubles`/`qlFreePointerArray` in `cbits/qlMisc.cpp` for the pattern, and
  `qlFreeAdditionalResults`/`qlFreePathGenerator` for hand-written multi-field/forward-declared
  cases that predate this being pulled into reusable primitive allocators).
- A pointer reinterpreted to a narrower/different type before freeing (`qlFreeUInts` frees an
  `unsigned*` that was actually allocated as `int*` — there's no `qlAllocateUInts`) must be traced
  under the type it was *actually allocated as*, not its free-time type, or the class names won't
  match. Delegate to the already-traced free (`qlFreeUInts` calls `qlFreeInts` after a
  `reinterpret_cast`) rather than duplicating the body under the wrong label.

**2. Hand-rolled `T*[n]`/`T**[n]` local spines freed via a *different* generic free function.**
Any local pointer-array built with plain `new T*[n]` that Haskell frees via `peekPtrArray`/`peekCStringArray`-style helpers in `QuantLib/Internal.hs` — which call
the generic `qlFreePointerArray`/`qlFreeStringArray` — needs its allocation traced under the
*generic* function's label, not its own concrete type, or the alloc and free land under different
class names. Use `retPtrArray(new T*[n]())` (in `cbits/qlaux.h`) for this rather than a raw cast:
it traces the spine under `void**` (matching `qlFreePointerArray`'s parameter type) while `p`
itself keeps its real `T**` type all the way through — no `(void**)` cast anywhere. Also fix the
**exception-path cleanup**: route it through the same traced free function/`del()` per element,
not a raw `delete`/`delete[]`, or the exception path will silently escape tracing.

**3. A constructor's `alloc()`/`ret()` argument has a narrower static type than its declared
return type.** `alloc()`/`ret()`'s template argument is deduced from the *argument expression's*
static type, not the function's return type. `return alloc(new Derived(...));` inside a function
declared to return `Base*` traces the allocation under `Derived`, while the matching `qlFreeBase`'s
`del()` — parameter-typed as `Base*` — traces the free under `Base`: a spurious leak (`Derived`
never freed) plus a spurious over-free (`Base` freed with no matching alloc), despite correct
actual memory behavior. Use `allocAs<Base>(new Derived(...))` (in `cbits/qlaux.h`) instead of a
bare `alloc()`: it traces the allocation under the `Base*` label while still returning the real
`Derived*` value, so the enclosing `return` upcasts it to `Base*` itself — a compiler-checked
conversion, not a cast. (`qlCubicBSplinesFitting`/`qlExponentialSplinesFitting`/etc. in
`cbits/qlTermStructure.cpp`, all returning `FittedBondDiscountCurveFittingMethod*` from a `new`
of one of five concrete subclasses, is the worked example — a real, silent, pre-existing case of
this found by cross-checking a "still live"/"over-freed" pair in `alloc-summary.py`'s output
against the constructor's argument type, not by code inspection alone.)

**4. Partial-construction/exception safety.** For any function allocating **more than one**
independent heap object, or filling a struct/array with **more than one** pointer field per
element, before its final return: verify every earlier-succeeded allocation is either already
owned by RAII (a local `shared_ptr`/vector-of-`shared_ptr` adopted it in the same full-expression
as the `new`) by the time a later step can throw, or is freed — and, per (1)/(2)/(3), *traced* — in
the `catch`, for every element already filled *and* for a partially-filled current element. A
value-initialised array (`new T[n]()`, trailing `()`) makes every not-yet-filled slot null-safe to
pass to a null-guarded free, which is the standard idiom here (see `qlInstrumentAdditionalResults`
and its many siblings for the pattern).

**4b. An exception path that frees an already-`ret()`/`alloc()`-traced pointer must use `del()`,
not a raw `delete` — and this is the one exception-path shape point 5 below does *not* cover.**
The two look almost identical, and the difference is *when* the tracing verb runs relative to the
throw point:

```cpp
// Point 5's accepted shape: `raw' is traced only on the success path, so the catch's silent
// `delete' is CORRECT -- no "allocated" line exists to pair with.
X *raw = 0; try { raw = new X(...); return ret(new QlX(alloc(raw))); } catch (...) { delete raw; }

// This shape: `ct' is ALREADY traced as "returned" before the second allocation can throw, so a
// raw `delete' in the catch escapes tracing and reports as a permanent leak of that class.
CommodityType *ct = 0; UnitOfMeasure *uom = 0;
try { ct = ret(new CommodityType(...)); uom = ret(new UnitOfMeasure(...)); ... }
catch (...) { del(ct); del(uom); }   // del(), not delete
```

Both out-params must also be hoisted above the `try` and null-initialised, so the catch can release
whichever ones got as far as being traced — the same value-initialisation reasoning as point 4, one
scalar at a time instead of an array. `qlUnitOfMeasureConversionConvert` (`cbits/qlMisc.cpp`) and
`qlEnergyCommodityQuantity` (`cbits/qlInstrument.cpp`) are the worked examples. Rule of thumb: scan
the `try` for the *last* tracing verb that runs before each throw point, not just for `new`.

**5. The narrow "double-free on `shared_ptr` control-block `bad_alloc`" pattern is known,
accepted, and not worth re-flagging.** `X *raw = 0; try { raw = new X(...); ...; return
ret(new QlX(alloc(raw))); } catch (...) { delete raw; }` has a theoretical double-free window if
the *outer* `new QlX(...)` itself throws `bad_alloc` after already adopting `raw` — but this shape
is used throughout the codebase (dozens of sites), only triggers on allocation failure at exactly
that point, and isn't specific to any one binding. Recognize it and move on rather than treating
each occurrence as a new finding.

**6. Null pointers create permanent tracing noise if not guarded.** `del(p)`/`qlFreeInts(p)`/etc.
called with `p == nullptr` (a legitimately no-op free — freeing null is always safe in C++) has no
matching `alloc()`/`ret()` event, since those only ever wrap a real construction. If traced
unconditionally, every such call shows up as a permanent, unexplainable single-pointer over-free
for that class (`alloc-summary.py` reports pointer `"0"` specifically). `del()` and the manual
array-free helpers in `cbits/qlMisc.cpp` all guard with `if (p) {...}` before tracing (still
performing the delete/`delete[]` unconditionally, since that's already a no-op on null) — keep any
new free function consistent with this.

**7. A `cbits`-local type used with `alloc()`/`ret()` needs its own `ObjClassName` label, or the
trace carries a mangled `typeid().name()`.** `ObjClassName`'s primary template (`cbits/qlaux.h`)
falls back to `typeid(T).name()`, so a missing specialization compiles fine and only degrades the
trace — which is why these go unnoticed. Two placements, and the choice is forced:
- A type nameable from `qlaux.h` — declared by a QuantLib header, or forward-declarable there —
  gets its specialization in `qlaux.h`'s own table, adding a forward declaration to the
  `namespace QuantLib { ... }` block plus a `using` if needed (`FdmStepConditionComposite`), or a
  bare `class Foo;` for a `cbits`-local one (`PolymorphicPathGenerator`, `qlaux.h:650`/`:1111`).
- A type in a **anonymous namespace** cannot be named from `qlaux.h` at all. Its specialization has
  to live in the same `.cpp`, at namespace scope, after the class definitions and before the first
  `alloc()` use, guarded by `#ifdef QLTRACK_ALLOCATIONS` — see the `Hs*` callback classes in
  `cbits/qlPricingEngine.cpp` and `cbits/qlInstrument.cpp`.

`char**`/`void**` deliberately have no specialization (only `void*` does): both sides of a spine's
lifecycle get the same fallback label, and `alloc-summary.py` pairs per `(class, pointer)`, so they
balance correctly under the mangled name.

## Two label helpers (avoid raw casts)

`cbits/qlaux.h` has `tracevalAs<Label>(text, val)`/the `TPAS` macro underneath `retPtrArray` and
`allocAs`: they let the trace *label* differ from `val`'s real static type without casting `val`
itself. Prefer these over a hand-written `(OtherType)ret(...)`/`(OtherType)alloc(...)` cast:
casting the pointer value risks silently converting between unrelated types, while `retPtrArray`/
`allocAs` only ever change which `ObjClassName` the trace line names, and — for `allocAs` — rely on
the compiler's own derived-to-base upcast at the `return` for type safety instead of a C-style cast.

## Verification loop

1. Rebuild with tracing per the `run-hasquant` skill's gotcha (clean `build/cbits` first).
2. Exercise the code paths touched — ideally the full test suite (`stack test`), since a single
   run's trace covers whatever it happens to call; a fix to a rarely-exercised function needs a
   targeted `test/smoke/` script or hspec case if the suite doesn't already reach it.
3. `python3 tools/alloc-summary.py <trace>`; confirm exit code 0 ("nothing leaked", no
   "FREED MORE OFTEN THAN ALLOCATED" section).
4. Investigate every reported class before assuming it's a real bug or dismissing it as noise —
   this session's audit found genuine tooling false positives (null-pointer frees, per point 6)
   sitting right next to a genuine pre-existing bug (the base/derived mismatch, per point 3) in the
   same `alloc-summary.py` output; a per-pointer breakdown (group the trace by `(class, pointer)`
   and print entries whose acquire/release counts don't match) separates the two faster than
   reading the raw trace.
5. Rebuild clean (no tracking flag) and confirm no new compiler warnings, per this repo's usual
   "clean all compiler warnings" standard.
