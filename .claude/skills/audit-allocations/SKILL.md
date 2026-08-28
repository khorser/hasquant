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

- `arg(p)` — pass-through read of a pointer received from Haskell; not a lifecycle event. The one
  verb that traces unconditionally, nulls included, since `alloc-summary.py` ignores `arg` lines.
- `alloc(p)` — marks a freshly-`new`'d object as "allocated." Ambiguous by design: for an object
  immediately absorbed into a `shared_ptr` control block (`ret(new QlX(alloc(new X(...))))`), it
  deliberately has no matching free, ever. For a plain value type returned and freed directly
  later (`return alloc(leg.release());`, freed via `qlFreeLeg`/`del()`), it *is* expected to pair
  with a free. `tools/alloc-summary.py` tells the two apart per-pointer, not per-class.
- `allocShared(p)` — `alloc()` for an object about to be owned by a `shared_ptr`: adopts and traces
  in one expression, so nothing can leak between the two. This is what a shim uses instead of
  holding a raw pointer across a `try` block (see point 4b).
- `ret(p)` — marks a pointer as "returned to Haskell"; always pairs with `del()`.
- `del(p)` / `delArray(p)` — the generic frees: `delete p` / `delete[] p` plus a `deleting`/`deleted`
  trace pair. Both are null-safe and never trace a null (see "Null pointers" below).
- `delWith(p, freeFn)` — `del()` for an object whose actual `delete` has to run in another
  translation unit (a type only forward-declared here), e.g. `qlFreePathGenerator`.
- `tracedup(p)` / `qlFreeString(p)` — the `strdup`/`free` equivalents for `char*`.
- `retPtrArray(p)` / `allocAs<Base>(p)` — see "Two label helpers" below.

**Where the on/off switch lives.** `qlaux.h` has exactly one `#ifdef QLTRACK_ALLOCATIONS`, around
the `ObjClassName` table, `traceStream()`, `emit()` and the `inline constexpr bool
trackAllocations`. Every verb above is built on `traceAs<Label>(what, p)`, whose whole body —
including the null test — sits inside `if constexpr (trackAllocations)`. Because `traceAs` is a
template, the discarded branch is never instantiated when the flag is off, so nothing to do with
tracing is compiled at all. **Do not host an `if constexpr (trackAllocations)` in a non-template
function** (a `qlFree*` shim, say): there the discarded statement is still fully type-checked, which
is exactly what this arrangement avoids. Call a verb instead; adding a new one belongs in `qlaux.h`
next to the others. The only things left in a `.cpp` that may name
`QLTRACK_ALLOCATIONS` are `traceStream()`'s definition (`qlMisc.cpp`) and a `QL_TRACE_NAME` block
for a type that cannot be named from `qlaux.h` (point 7).

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

**1. Every raw `new`/`malloc`/`strdup`/`calloc` routes through `alloc`/`allocShared`/`ret`/`tracedup`.**
Grep for each and check the exceptions:
- `delete[]`/array frees use `delArray(p)`, not `del(p)` (which does a scalar `delete`) — see
  `qlFreeInts`/`qlFreeDoubles`/`qlFreePointerArray`/`qlFreeStringArray` in `cbits/qlMisc.cpp` and
  `qlFreeAdditionalResults` in `cbits/qlInstrument.cpp`. A free whose `delete` lives in another
  translation unit uses `delWith(p, auxFree)` (`qlFreePathGenerator`, `qlFreeGaussianRsg`). Neither
  needs a hand-written null guard or a hand-written trace pair — that is what the verb is for.
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

**4b. Hold a not-yet-handed-out allocation in a smart pointer, not a raw pointer above the `try`.**
The old shape here was a raw pointer hoisted above the `try` and released by `del()` in the `catch`;
it is gone from `cbits/`, and a new one should not appear. Two replacements, by destination:

```cpp
// Destined for a shared_ptr: adopt and trace in one expression. If anything later in the try
// throws, the shared_ptr releases it -- there is nothing for the catch to do.
auto ts = allocShared(qlPiecewiseDefaultCurveAux(...));
if (extrapolate) ts->enableExtrapolation();
return ret(new QlDefaultProbabilityTermStructure(ts));

// Handed to Haskell as a bare pointer: unique_ptr until every allocation has succeeded, then
// release + ret() at the hand-off. ret() therefore runs only on pointers actually handed out, so
// a half-built result is never traced as returned and needs no compensating free.
std::unique_ptr<CommodityType> ct(new CommodityType(q.commodityType()));
std::unique_ptr<UnitOfMeasure> uom(new UnitOfMeasure(q.unitOfMeasure()));
*outCt = ret(ct.release());
*outUom = ret(uom.release());
```

`qlUnitOfMeasureConversionConvert` (`cbits/qlMisc.cpp`), `qlEnergyCommodityQuantity`
(`cbits/qlInstrument.cpp`) and `qlLeg`/`qlLegToCouponLeg` are the worked examples of the second
shape; every `qlPiecewise*`/`qlInterpolated*` curve in `cbits/qlTermStructure.cpp` is the first.
The rule of thumb that motivated the old text still holds and is what these shapes satisfy
structurally: scan for the *last tracing verb that runs before each throw point*, and make sure
nothing already traced as `returned` can be dropped without a matching free.

**5. The old `X *raw = 0; try { ... } catch (...) { delete raw; }` shape is gone — don't reintroduce
it, and don't re-flag its absence.** It carried a real (if narrow) double-free window: if the outer
`new QlX(...)` threw `bad_alloc` *after* adopting `raw`, the `catch` deleted it a second time. It
was used at ~25 sites and accepted as not worth chasing; the `allocShared`/`unique_ptr` shapes in
point 4b close it structurally, so the window no longer exists anywhere in `cbits/`. The
still-common one-liner `return ret(new QlX(alloc(new X(...))));` has no such window — there is no
second reference to leak or double-free — and needs no conversion.

**6. Null pointers would create permanent tracing noise, and the guard is central — don't re-add a
local one.** `del(p)`/`qlFreeInts(p)`/etc. called with `p == nullptr` (a legitimately no-op free —
freeing null is always safe in C++) has no matching `alloc()`/`ret()` event, since those only ever
wrap a real construction. Traced unconditionally, every such call would show up as a permanent,
unexplainable single-pointer over-free for that class (`alloc-summary.py` reports pointer `"0"`
specifically). The `if (p)` test lives once, inside `traceAs` in `qlaux.h`, so every verb inherits
it and no free function needs its own — an `if (p)` in a `qlFree*` shim now means a *semantic*
null check (the callee is not null-safe), not a tracing one. `arg()` is the deliberate exception:
it traces nulls, and `alloc-summary.py` ignores its lines.

**7. A `cbits`-local type used with `alloc()`/`ret()` needs its own `ObjClassName` label, or the
trace carries a mangled `typeid().name()`.** `ObjClassName`'s primary template (`cbits/qlaux.h`)
falls back to `typeid(T).name()`, so a missing specialization compiles fine and only degrades the
trace — which is why these go unnoticed. Write one as `QL_TRACE_NAME(Foo)` (the macro stringizes
the type, so the label cannot drift from it) or `QL_TRACE_NAME_AS(Foo, "Label")` for the rare case
where they differ — `void` → `"Ptr"` is the only one today. Two placements, and the choice is
forced:
- A type nameable from `qlaux.h` — declared by a QuantLib header, or forward-declarable there —
  gets its specialization in `qlaux.h`'s own table, adding a forward declaration to the
  `namespace QuantLib { ... }` block plus a `using` if needed (`FdmStepConditionComposite`), or a
  bare `class Foo;` for a `cbits`-local one (`PolymorphicPathGenerator`, `qlaux.h:648`/`:1117`).
- A type in a **anonymous namespace** cannot be named from `qlaux.h` at all. Its specialization has
  to live in the same `.cpp`, at namespace scope, after the class definitions and before the first
  `alloc()` use, guarded by `#ifdef QLTRACK_ALLOCATIONS` — see the `Hs*` callback classes in
  `cbits/qlPricingEngine.cpp` and `cbits/qlInstrument.cpp`.

`char**`/`void**` deliberately have no specialization (only `void*` does): both sides of a spine's
lifecycle get the same fallback label, and `alloc-summary.py` pairs per `(class, pointer)`, so they
balance correctly under the mangled name.

## Two label helpers (avoid raw casts)

`cbits/qlaux.h` has `traceAs<Label>(what, p)` underneath `retPtrArray` and
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
   "FREED MORE OFTEN THAN ALLOCATED" section). If it reports *no trace file*, nothing was
   traced at all — the stream is opened on first use, so a run that traces nothing leaves no
   file rather than an empty one. That is the flag-didn't-recompile-`cbits` gotcha above,
   not a clean result, and the script exits 1 for it.
4. Investigate every reported class before assuming it's a real bug or dismissing it as noise —
   this session's audit found genuine tooling false positives (null-pointer frees, per point 6)
   sitting right next to a genuine pre-existing bug (the base/derived mismatch, per point 3) in the
   same `alloc-summary.py` output; a per-pointer breakdown (group the trace by `(class, pointer)`
   and print entries whose acquire/release counts don't match) separates the two faster than
   reading the raw trace.
5. Confirm no new compiler warnings, per this repo's usual "clean all compiler warnings"
   standard — and check **all four combinations**, not just the local clean rebuild:
   flag-off *and* flag-on, under clang (`make` / `make EXTRA='-DQLTRACK_ALLOCATIONS=\"/dev/fd/2\"'`)
   *and* under the container's GCC:

   ```
   docker compose run --rm hasquant sh -c 'for f in cbits/ql*.cpp; do g++ -c -Wall -Wextra -pedantic \
     -std=c++17 -Icbits $(quantlib-config --cflags | sed "s/-I/-isystem/g") -o /tmp/o.o $f || exit 1; done'
   ```

   Neither axis is redundant. The lts-18.8 gate only ever builds **flag-off**, so a warning that
   only appears with tracing compiled in can hide indefinitely; and GCC diagnoses things clang
   does not — `-Wuse-after-free` on `qlFreeString`'s `trace("Freed string", p)` after `free(p)` is
   the worked example, invisible on macOS in either flag state. (Fix for that shape: capture the
   address as a `uintptr_t` before the free and `reinterpret_cast` it back for printing; a
   `void *addr = p;` copy does *not* satisfy GCC, since copies of a freed pointer are equally
   invalid.)
