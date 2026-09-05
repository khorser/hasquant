---
name: add-quantlib-method
description: Add a single new method binding to a QuantLib class that already has a hasquant binding (shim .h/.cpp + c2hs .chs import). Use when asked to bind, add, or expose one more method/getter on an existing bound class — not for adding a whole new class (see add-quantlib-class for that).
---

Adding a method to an existing class normally changes only its `.h`, `.cpp`, and `.chs` files. Use [[add-quantlib-class]] if the class is missing.

`arg()`, `ret()`, `alloc()` (in `cbits/qlaux.h`) are pure identity/tracing passthroughs — `template <class T> T arg(T p) {return TP("arg", p);}`. They do **no** dereferencing themselves; getting the pointer indirection right is on you, and it depends on the parameter's type.

The shims should be defined inside `extern "C"` blocks in `CPP` files for type checking to work. If you define C++ helpers, they should be outside the block inside an anonymous namespace, usually you can find it above the `extern "C"` block, don't create a new one.

## 0. Read the upstream declaration and documentation — don't guess either

Before writing anything, find the method's actual declaration in QuantLib's own header under `/opt/homebrew/include/ql/` (the class's base-class header specifically — per project convention, bind base-class methods only, not overloads on concrete subclasses). Read off, verbatim: the exact method name, parameter types and order, constness, and return type. Everything in steps 1-3 below is a mechanical consequence of that real signature, not something to infer from the method name alone or from a superficially similar sibling binding.

Read the upstream Doxygen comment for both the method and its class while that header is open. Add a `-- |` Haddock comment to every public new binding, carrying the relevant behavior, formulas, warnings, and units in clear Haskell-facing language. Do not replace it with a generic label or omit upstream caveats; document intentional scope cuts too. A constructor binding needs the class-level documentation as well as any constructor-specific notes. Constructor-echo inspectors that are deliberately not bound need no documentation.

Before binding an inspector, check every producer of its return type that hasquant actually exposes. Exclude a value that merely echoes a constructor input unless another bound producer computes, calibrates, interpolates, or looks it up. A sibling binding that has not been checked is not precedent. If such getters were the only reason to introduce a dedicated leaf type, return the existing parent type instead.

**Document every public input argument too.** Put a `-- ^parameterName` annotation immediately after each Haskell-visible argument marshaller in the `{#fun#}` declaration, in the same left-to-right order as the upstream signature. Use the upstream parameter name where it is meaningful; explain non-obvious sentinels, `Maybe`/empty-handle behavior, units, and flags in the surrounding Haddock. Do not annotate c2hs-only out/error plumbing such as `preErrorCheck`. Split long declarations across lines rather than leaving a constructor's argument order undocumented.

Default to assuming the method **can throw** — QuantLib almost universally validates via `QL_REQUIRE`/`QL_ENSURE` internally even when the header gives no hint. Only treat it as non-throwing (step 3) if the header shows a trivial inline field return with no validation, like `qlInterestRateRate`/`InterestRate::rate()`. When in doubt, throw: a spuriously `pure` Haskell import over a function that actually throws is undefined behavior once the C++ exception unwinds past the FFI boundary, whereas a throwing convention on a method that never throws just costs an unused `try/catch`.

If the method you're being asked for doesn't exist verbatim in the upstream header — don't invent a plausible-sounding substitute. Say so.

## 1. Argument marshalling — pick the right dereference depth

- **Parameter is `QlXxx* o`** (a hierarchy/polymorphic class — check `cbits/qlaux.h` for an existing `using QlXxx = shared_ptr<Xxx>;`): `o` is a pointer to a `shared_ptr<Xxx>`, so you need one extra dereference to reach the object: `(*arg(o))->method(...)`.
  Example: `qlTermStructureReferenceDate`: `(*arg(o))->referenceDate()`.
- **Parameter is `Xxx* o`** (a plain value type — listed with no `Ql` prefix in `cbits/qlTypesC2HS.h`'s "fake typedefs" block, e.g. `Calendar`, `DayCounter`, `InterestRate`, `Period`, `Schedule`, `Currency`): `o` is a direct pointer to the object, one level shallower: `arg(o)->method(...)`.
  Example: `qlInterestRateRate`: `arg(o)->rate()`.

Getting this wrong (using the wrong dereference depth for the type) compiles fine in some cases but is a classic source of the closest near-misses in this codebase — double check which bucket the type is in before writing the body.

## 2. Return value construction

- **Primitive** (`double`, `int`, `bool`) — return directly, no wrapping. A `Date` return is serialized: `.serialNumber()` (mirrors every other date-returning binding).
- **`std::string`/`const char*`** — must be heap-duplicated for the FFI boundary: `tracedup(arg(o)->name().c_str())`.
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

   Add the upstream-derived `-- |` Haddock comment immediately above it, as required by step 0, and a `-- ^parameterName` annotation to every public input argument. It should explain useful semantics and caveats, not merely repeat the Haskell function name.

## 5. Less-common parameter/return shapes

### Choose the public collection type before choosing a marshaller

An upstream `std::vector<T>` does not imply a Haskell `[T]`. Choose among the established public shapes using three separate concerns:

1. **Ergonomics — `[a]`.** Use an ordinary list for small collections that may validly be empty: optional/default schedules, exclusions, constraints, and similar inputs callers commonly construct with list syntax. Do not force `NonEmpty` merely because the successful examples happen to contain elements.
2. **Semantic invariant — `NonEmpty a`.** Use `NonEmpty` when upstream requires at least one element, construction with zero elements is meaningless, or the implementation would otherwise call `head`/depend on a first node. Typical cases are curve/bootstrap helpers, required notionals or coupons, exercise dates, calibration helpers, and required surface nodes. Marshal with an existing `withNonEmpty*Array` helper, or add the direct `toList`-based counterpart beside the matching list marshaller.
3. **Performance — `RealVector` / `RealMatrix`.** Use the storable numeric containers for homogeneous `Double` data that can contain hundreds, thousands, or tens of thousands of values: Monte Carlo paths, regression data, PDE vectors, and dense volatility/local-vol grids. Destructure `RealMatrix` into its row/column counts and `RealVector` payload, and marshal with `withRealVectorRaw`; return numeric bulk data with `peekRealVector`. Do not mechanically convert small fixed-dimensional correlation/covariance matrices where boxed `Matrix Double` is clearer and allocation volume is negligible.

These choices can combine: a required set of a few object pointers is normally `NonEmpty (GenX a)`, while a required dense numeric grid is still `RealMatrix` because its dimensions already carry the structural invariant and performance dominates.

### Prefer zipped records to parallel public collections

When two or more upstream arrays describe the same observations positionally, expose one collection of tuples and unzip it only in the Haskell wrapper immediately before the raw c2hs hook. Examples include `(date, value)`, `(strike, quote)`, `(helper, weight)`, and `(tenor, quote, flag)`. Use `NonEmpty (a, b)` when the observation set must also be non-empty. This prevents unequal lengths by construction and keeps related data together at call sites.

Do not zip independent matrix axes: expiries, strikes, and a volatility matrix describe a Cartesian grid, not pairwise observations, so they remain separate axis collections plus `RealMatrix`. Likewise, do not zip parameters whose lengths intentionally follow different QuantLib broadcasting/default rules.

### `std::vector<T>` parameters

After making the public-shape decision above, the C shim still takes a `(len, T*)` pair built from a raw array, not a real `std::vector` at the boundary. `Cap` shows the `NonEmpty` shape for required exercise rates:
```cpp
QlCapFloor* qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e) {
  try {return ret(new QlCapFloor(alloc(new Cap(*arg(floatingLeg), std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen)))));
  } catch (std::exception& er) {return handleException<QlCapFloor*>(e, er);}}
```
```
{#fun qlCap as cap{withLeg*`GenLeg a' -- ^floatingLeg
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
```
The `&` after `withNonEmptyDoubleArray*` splices the marshaller's `(CUInt, Ptr CDouble)` pair into two consecutive C params — one Haskell `NonEmpty Double` argument, two C arguments. An empty-valid list uses the corresponding `withDoubleArray`; a `vector<Date>` uses the same boundary shape via the `qlaux.h` helper `qlDateVector(int *dates, unsigned len)` on the C++ side.

Object-pointer element type (`vector<shared_ptr<T>>`): the C shim takes `(len, QlT**)`, built into a real vector via `qlaux.h`'s `template <class T> std::vector<T> qlVector(T **vals, size_t len)`. Example, `Swap`'s multi-leg constructor:
```cpp
QlSwap* qlSwap1(unsigned legsLen, Leg** legs, unsigned payerLen, int *payer, char **e) {
  try {return ret(new QlSwap(alloc(new Swap(qlVector(legs, legsLen), std::vector<bool>(payer, payer+payerLen)))));
  } catch (std::exception& er) {return handleException<QlSwap*>(e, er);}}
```
```
{#fun qlSwap1{withLegArray*`[Leg]'&,withBoolArray*`[Bool]'&,preErrorCheck-`String'errorCheck*-}->`Swap'peekSwap*#}
```
`withLegArray = withGenArray withLeg` — every array-taking class needs its own `with<T>Array = withGenArray with<T>` defined once in `Internal/Type.hs` (mirrors `withQuoteArray`, `withRateHelperArray`, `withCalibrationHelperArray`, `withInstrumentArray`, ...); add one if missing, don't invent a different combinator.

### `std::vector<T>` return values

Primitive element type: **out-parameters**, not a return value — `(unsigned *len, T **out)` appended before `char **e`, with the C++ body allocating via `qlaux.h`'s `qlAllocateDoubles`/`qlAllocateInts` and copying into it:
```cpp
void qlBondNotionals(QlBond* o, unsigned *len, double **ns, char **e) {
  try {const std::vector<double>& notionals = (*arg(o))->notionals(); *len = notionals.size(); *ns = qlAllocateDoubles(*len); std::copy(notionals.begin(), notionals.end(), *ns);
  } catch (std::exception& er) {(void)handleException<double*>(e, er);}}
```
```
{#fun qlBondNotionals as notionals{withBond*`GenBond a',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
```
`preArray`/`peekDoubleArray`/`peekIntArray'` are generic combinators already in `QuantLib/Internal.hs` — reuse them, don't write a new allocator per type. The `.chs` return spec is still `` ->`()' `` (the real "return value" travels through the out-param marshaller in the arg list, not the arrow).

Object-pointer element type: hasquant **never** marshals `vector<shared_ptr<T>>` back element-by-element. It only works when the vector itself already has a named alias type (`Leg`/`CouponLeg` — QuantLib's own typedefs for `vector<shared_ptr<CashFlow>>`/`vector<shared_ptr<Coupon>>`), returned as a single opaque `Leg*`/`CouponLeg*`, e.g. `Leg* qlSwapLeg(QlSwap* o, unsigned j, char **e) {try {return ret(new Leg((*arg(o))->leg(j)));} ...}`. If a method returns a raw, unaliased `vector<shared_ptr<T>>` with no existing named type, there's no established pattern for it — don't invent an element-wise marshaller; flag it for manual design instead.

### `Handle<T>` parameters — nullable, not a plain pointer

`Handle<T>` is QuantLib's "possibly-empty, observable" wrapper — map it to `Maybe` on the Haskell side, using `qlaux.h`'s `template <class T> Handle<T> qlNullableHandle(shared_ptr<T> *p) {return p ? Handle<T>(*(arg(p))) : Handle<T>();}` on the C++ side:
```cpp
try {return ret(new QlForwardRateAgreement(alloc(new ForwardRateAgreement(*arg(index), Date(valueDate), Date(maturityDate), (Position::Type)type, strikeForwardRate, notionalAmount, qlNullableHandle(arg(discountCurve))))));
```
The Haskell marshaller is a **per-type** `withMaybe<T>`, hand-written once in `Internal/Type.hs` alongside `with<T>` (not a generic combinator):
```haskell
withMaybeYieldTermStructure :: Maybe (GenYieldTermStructure a) -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withMaybeYieldTermStructure x f = maybe (f nullPtr) (`withYieldTermStructure` f) x
```
used as `withMaybeYieldTermStructure*\`Maybe (GenYieldTermStructure y)'` in `.chs` (see `forwardRateAgreement` in `QuantLib/Instrument/Forward.chs`, `swapRateHelper` in `QuantLib/TermStructure/Yield.chs`, `discountingBondEngine` in `QuantLib/PricingEngine.chs`). `withMaybeQuote` is the same pattern for `Handle<Quote>`. If the class doesn't have a `withMaybe<T>` yet, add one (same shape) rather than passing it non-nullably and dropping the "empty handle" case.

### `ext::optional<T>` parameters/returns

Only `bool` and (separately) `Date` have established conversions. `ext::optional<bool>`: C-side sentinel via `qlaux.h`'s `qlOptBool` (`-1` = empty), Haskell-side via `QuantLib/Internal.hs`'s generic `fromMaybeBool :: Maybe Bool -> CInt` / `toMaybeBool :: CInt -> Maybe Bool` — as a param: `fromMaybeBool\`Maybe Bool'`; as a return: `{#fun qlSettingsIncludeTodaysCashFlows as includeTodaysCashFlows{}->\`Maybe Bool' toMaybeBool#}` (backed by `int qlSettingsIncludeTodaysCashFlows() {return qlOptBool(Settings::instance().includeTodaysCashFlows());}`). `ext::optional<Date>`/defaulted `Date` params use the analogous `qlNullableDate`/`withMaybeDay` pair. Don't assume this generalizes to arbitrary `ext::optional<T>` — for any other `T` there's no established combinator; add one deliberately rather than guessing a shape.

### Default-valued C++ parameters — one full-arity shim, not two

hasquant does **not** emit two arities for a method with trailing default arguments. Every defaulted parameter becomes a **required** Haskell argument typed to carry the "use the default" sentinel — `Maybe`/nullable via the same `Handle<T>`/`ext::optional<T>` machinery above. Example, `DiscountingSwapEngine`'s constructor (`Handle<YieldTermStructure> discountCurve = Handle<YieldTermStructure>(), const ext::optional<bool>& includeSettlementDateFlows = ext::nullopt, Date settlementDate = Date(), Date npvDate = Date()`) binds as one shim with four required Haskell args:
```
{#fun qlDiscountingSwapEngine as discountingSwapEngine{withYieldTermStructure*`GenYieldTermStructure a',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
```
(Note this particular binding types `discountCurve` non-nullably, so its `Handle<T>()`-default case isn't reachable from Haskell at all — a defaulted `Handle<T>` doesn't *have* to become `Maybe`; it's a per-binding judgment call whether the empty-handle case is worth exposing.) Don't confuse this with genuine C++ **overloads** (distinct signatures, not one signature's defaults) — those get separate numbered C shims, see below.

With more than 10 trailing defaulted parameters, preserve the narrow binding and add a second options-record entry point instead — see [[add-quantlib-options-record]].

### Numbered overloads

When a class has multiple real overloads of the same name, each gets its own C shim with a numeric suffix on the second and later ones — the first keeps the bare name: `qlOISRateHelper`/`qlOISRateHelper2`, `qlJointCalendar2`/`qlJointCalendar3`/`qlJointCalendar4`. The numbering isn't necessarily contiguous from 1 and isn't derivable from the C++ signature — it reflects whatever order bindings were historically added in. If you're adding a second overload of an existing binding, just pick the next unused suffix; don't try to make it "meaningful."

### Static methods, and default values, are now visible in the dump

`tools/dump_signatures.py` includes `static` and parameter defaults. `tools/ql-methods-1.43.txt` does not, so check the header when working from that dump; `tools/reconcile_signatures.py` ignores those fields when matching entries.

A true static/singleton accessor takes no self-parameter at all: `Settings::instance()`'s shim is `int qlSettingsEvaluationDate() {return Settings::instance().evaluationDate()...;}`, bound as `{#fun qlSettingsEvaluationDate as evaluationDate{}->\`Day'toDay#}` — the empty `{}` argument list is the tell. `tools/gen_quantlib_method.py` now does this automatically when it sees a `static` prefix: no receiver pointer/bound-class requirement, and the C++ call is qualified directly as `Class::member(...)` rather than dereferencing a receiver — see `qlCashFlowsYield` (generated from the `static Rate CashFlows::yield(...)` declaration above) for the shape. It also flags every defaulted parameter with a note pointing at the "one full-arity shim" convention above, rather than silently guessing whether to `Maybe`-wrap it — auto-generating the nullable marshalling for an arbitrary parameter type isn't reliable without an existing `Handle<T>`/`ext::optional<T>`-style convention for that specific type, so it's left as a flagged, human judgment call.

Do not classify a class as a singleton from its surface API or by analogy. Check its inheritance from `Singleton<T>`, whether copy/move or ordinary construction is deleted or inaccessible, and whether `instance()` owns process-global state. Bind a genuine singleton as free functions over `X::instance()` rather than inventing a Haskell object.

## Update tools/ql-methods-*.txt

After the binding compiles, grep the method/class name in `tools/ql-methods-1.43.txt` (the current version's tracking dump) and set that line's status character to match what you just did: `v` if the shim's arg count matches the upstream declaration exactly, `u` if it deliberately binds fewer args (a documented scope cut, e.g. an omitted optional parameter). This is the same status vocabulary `tools/sync_ql_methods_status.py`/`tools/reconcile_signatures.py` already use (blank = unreviewed candidate, `x` = permanently excluded, `v`/`u`/`?` as above) — updating it inline as you add each binding keeps the file current without needing another bulk resync pass later. Some blank lines got auto-marked `x` by `tools/detect_trivial_getters.py`, a one-off libclang-based scan for getters that just return a field set verbatim from a constructor parameter and never written anywhere else with a computed value (report mode by default; `--apply` writes the marks) — if you're ever re-deriving why a getter is excluded, check there before assuming it was a manual call.

## Verification

Run `make` for a quick C++-only compile check before doing a full `stack build --test --no-haddock`.

When changing `tools/gen_quantlib_method.py`, generate bindings for already-bound methods covering the affected shapes and diff them against the hand-written `.h`, `.cpp`, and `.chs` implementations. Treat marshaller, pointer-depth, enum-cast, exception, and naming differences as bugs unless they are documented human-judgment fields.
