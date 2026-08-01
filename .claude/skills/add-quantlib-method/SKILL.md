---
name: add-quantlib-method
description: Add a single new method binding to a QuantLib class that already has a hasquant binding (shim .h/.cpp + c2hs .chs import). Use when asked to bind, add, or expose one more method/getter on an existing bound class — not for adding a whole new class (see add-quantlib-class for that).
---

Adding one method to an already-bound class only touches the shim `.h`/`.cpp` and the `.chs` module — `cbits/qlaux.h`, `cbits/qlTypesC2HS.h`, and `QuantLib/Internal/Type.hs` are already set up for the class and don't need changes (see [[add-quantlib-class]] if the class itself is missing).

`arg()`, `ret()`, `alloc()` (in `cbits/qlaux.h`) are pure identity/tracing passthroughs — `template <class T> T arg(T p) {return TP("arg", p);}`. They do **no** dereferencing themselves; getting the pointer indirection right is on you, and it depends on the parameter's type.

## 0. Get the real signature from QuantLib itself — don't guess it

Before writing anything, find the method's actual declaration in QuantLib's own header under `/opt/homebrew/include/ql/` (the class's base-class header specifically — per project convention, bind base-class methods only, not overloads on concrete subclasses). Read off, verbatim: the exact method name, parameter types and order, constness, and return type. Everything in steps 1-3 below is a mechanical consequence of that real signature, not something to infer from the method name alone or from a superficially similar sibling binding.

Default to assuming the method **can throw** — QuantLib methods almost universally validate via `QL_REQUIRE`/`QL_ENSURE` internally even when the header gives no hint — and only treat it as non-throwing (step 3) if you can see in the header that it's a trivial inline field return with no validation, the same way `qlInterestRateRate`/`InterestRate::rate()` is. When in doubt, throwing is the safe default: a spuriously `pure` Haskell import over a function that actually throws is a real correctness bug (undefined behavior on the Haskell side when the C++ exception unwinds past the FFI boundary), whereas a throwing convention on a method that never actually throws just costs an unused `try/catch`.

If the method you're being asked for doesn't exist verbatim in the upstream header — don't invent a plausible-sounding substitute. Say so.

## 1. Argument marshalling — pick the right dereference depth

- **Parameter is `QlXxx* o`** (a hierarchy/polymorphic class — check `cbits/qlaux.h` for an existing `typedef shared_ptr<Xxx> QlXxx;`): `o` is a pointer to a `shared_ptr<Xxx>`, so you need one extra dereference to reach the object: `(*arg(o))->method(...)`.
  Example: `qlTermStructureReferenceDate`: `(*arg(o))->referenceDate()`.
- **Parameter is `Xxx* o`** (a plain value type — listed with no `Ql` prefix in `cbits/qlTypesC2HS.h`'s "fake typedefs" block, e.g. `Calendar`, `DayCounter`, `InterestRate`, `Period`, `Schedule`, `Currency`): `o` is a direct pointer to the object, one level shallower: `arg(o)->method(...)`.
  Example: `qlInterestRateRate`: `arg(o)->rate()`.

Getting this wrong (using the wrong dereference depth for the type) compiles fine in some cases but is a classic source of the closest near-misses in this codebase — double check which bucket the type is in before writing the body.

## 2. Return value construction

- **Primitive** (`double`, `int`, `bool`) — return directly, no wrapping. A `Date` return is serialized: `.serialNumber()` (mirrors every other date-returning binding).
- **`std::string`/`const char*`** — must be heap-duplicated for the FFI boundary: `DUP(arg(o)->name().c_str())`.
- **New QuantLib object** — construct then wrap through `ret()`:
  - Hierarchy/polymorphic class: `ret(new QlXxx(alloc(new Xxx(...))))` (or `alloc(dynamic_cast<Xxx*>(...))` if downcasting from an existing pointer).
  - Plain value type: `ret(new Xxx(...))` directly, no `Ql`/`alloc()` wrapper needed.

## 3. Exception convention — must match the Haskell import exactly

- **Can throw** (most methods): C signature takes a trailing `char **e`, body wraps in `try { ... } catch (std::exception& er) { return handleException<T>(e, er); }`. The `.chs` import then needs `preErrorCheck-\`String'errorCheck*-` before the return-type arrow, e.g.:
  `{#fun qlTermStructureReferenceDate as referenceDate{withTermStructure*\`GenTermStructure a',preErrorCheck-\`String'errorCheck*-}->\`Day'toDay#}`
- **Cannot throw** (rare — only when you're sure, e.g. a plain field access): no `char **e` parameter, no try/catch, one-liner body. The `.chs` import is `{#fun pure qlXxx as xxx{...}->...#}` with **no** `preErrorCheck`/`errorCheck` marshalling at all. Do not mix the two conventions — a `pure` Haskell import against a C function that can actually throw is a real bug, not just a style choice.

## 4. Add the `{#fun#}` declaration to the `.chs` file

Two edits, not one — easy to forget the first:

1. **Export list** — add the new Haskell function name to the `module QuantLib.Xxx (...) where` export list at the top of the file. If you skip this, it compiles but nothing outside the module can call it.
2. **The `{#fun#}` line itself**, placed near the other methods of the same class:

   `{#fun <CFunctionName> as <haskellName>{<arg marshaller>,<arg marshaller>,...}->\`<ReturnType>'<out marshaller>#}`

   Per-argument marshaller, left to right in the same order as the C signature:
   - Plain value/enum passed by value (`Double`, `Bool`, `Int`, `Compounding`, `Frequency`, ...): just the backtick type, no marshaller name — `` `Double' ``.
   - Pointer/wrapped type (foreign object, `Day`, etc.): `withXxx*` immediately before the backtick type — e.g. `withTermStructure*\`GenTermStructure a'`, `withDayCounter*\`DayCounter'`, `withDay*\`Day'`. `withXxx` must already exist in `QuantLib/Internal/Type.hs` (it does, for any already-bound class/value-type — see [[add-quantlib-class]] if not).
   - Trailing error-out param (only if the method can throw): `preErrorCheck-\`String'errorCheck*-` — always this exact boilerplate, always last.

   **Non-leaf argument types:** if the C++ parameter's declared type is a hierarchy *base* class (e.g. `const TermStructure&`, `shared_ptr<Index>` — not a concrete leaf like `YieldTermStructure`), type it in the `.chs` signature as `GenXxx a` (e.g. `` withTermStructure*`GenTermStructure a' ``), never the concrete alias `` `TermStructure' `` — `GenXxx a` is what lets callers pass any concrete subtype (`YieldTermStructure`, `CreditTermStructure`, ...) without an explicit upcast, via the same `AnyOf`/`Upcastable` polymorphism used throughout this file (see [[add-quantlib-class]]). This is the existing convention throughout the codebase — e.g. `withYieldTermStructure*\`GenYieldTermStructure b'`, `withQuote*\`GenQuote a'`.

   If a single method has more than one such polymorphic argument, **give each one its own type variable** (`a`, `b`, `c`, ...) — never reuse the same letter for two independent hierarchy parameters. Reusing a variable forces both arguments to be the *same* concrete subtype at the call site, which is usually wrong (and not something the underlying C++ signature actually requires). Real examples in this codebase get this right — `qlCashFlowsNpv`'s `` withLeg*`GenLeg a',withYieldTermStructure*`GenYieldTermStructure b' `` uses distinct `a`/`b` for two unrelated hierarchies — but it's worth double-checking existing bindings too: `qlSwap` in `QuantLib/Instrument/Swap.chs` reuses `` `GenLeg a' `` for *both* of its independent leg arguments, which (since `Leg`/`CouponLeg` are genuinely different concrete instantiations of `GenLeg`) looks like exactly this mistake — treat it as a cautionary example, not a pattern to copy.

   Return marshaller, after `->`:
   - Plain value: just `` `Type' ``, e.g. `` `Double' ``.
   - Needs conversion: `` `Type'convFn* ``, e.g. `` `Day'toDay `` (serial-number date), `` `InterestRate'peekInterestRate* `` (wrap a returned foreign object — `peekXxx` must exist in `Internal/Type.hs`, same as `withXxx`).

   Add a `-- |` doc comment line above it — the existing modules do this for every binding, usually paraphrasing QuantLib's own doc comment for that method from the upstream header.

## Verification

Run `make` (see CLAUDE.md) for a quick C++-only compile check before doing a full `cabal build`.
