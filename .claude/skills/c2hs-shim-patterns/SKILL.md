---
name: c2hs-shim-patterns
description: Reference for c2hs pragma flags, C shim marshalling patterns, and known gotchas when writing or debugging a .chs binding or a cbits/ C++ shim function. Use when writing a {#fun#}/{#pointer#} declaration, adding a shim in cbits/, choosing a marshaller (alloca-, preArray, a with*/peek* pair), naming a GenX type variable, or hitting a cryptic c2hs/GHC type-mismatch error while binding a QuantLib method.
---

Patterns and gotchas for the c2hs (`.chs`) layer and the C++ shim layer
(`cbits/`) that binds QuantLib. These are referenced by the
`add-quantlib-class`, `add-quantlib-adt`, `add-quantlib-method`, and
`add-quantlib-options-record` skills — read this one directly when you're
past "what class am I binding" and into "why won't this pragma/marshaller
compile."

## `{#pointer#}` flags and bare-backtick return specs

**`{#pointer#}` flags decide what a bare-backtick `{#fun#}` return spec
(`` ->`T' ``, no named out-marshaller) produces.** The wrong combination
compiles-then-crashes or fails type-checking confusingly rather than
erroring at the pragma:

- `{#pointer *T foreign finalizer F newtype#}` (c2hs owns the type)
  generates a `ForeignPtr`-wrapped newtype `T` with finalizer `F`; a bare
  `` ->`T' `` auto-wraps the raw returned pointer into `T`.
- `{#pointer *T foreign -> X nocode#}` (used when `T`'s
  `Finalizable`/`Upcastable` instances are hand-written in
  `QuantLib/Internal/Type.hs` — the pattern for every class hierarchy:
  Option, Quote, Bond, Payoff/Exercise, …) says `T` is a
  `ForeignPtr`-managed value shaped like `X` but suppresses the wrapper. A
  bare `` ->`T' `` still tries to auto-wrap into a `ForeignPtr`, which
  fails (`Couldn't match type 'ForeignPtr X' with '...'`) unless `T`
  really is that shape.
- `{#pointer *T nocode#}` (no `foreign`, no `-> X`) is what you want for a
  genuinely raw `Ptr T` (e.g. to hand off for hand-written `Upcastable`
  upcasting). A bare `` ->`T' `` here marshals `T` *by value* and GHC
  rejects it (`T cannot be marshalled in a foreign call`). c2hs has no
  built-in passthrough out-marshaller, so write and name one: `peekPtr ::
  Ptr a -> IO (Ptr a); peekPtr = pure`, then `` ->`T'peekPtr* ``.

## New pointer types need a C-parser-visible typedef

**A brand-new pointer type needs `typedef struct T T;` in
`cbits/qlTypesC2HS.h` before any `.chs`/`qlMisc.h`-style header can name
it**, even though the real C++ type is only ever forward-declared in
`qlaux.h` (`class T;` + `using QuantLib::T;`). c2hs parses `#include`d C
headers with its own small C parser (not full C++), and a bare `T
*foo(...)` where `T` is unknown to that parser fails at the `{#fun#}`'s own
`#include`, not at the pragma: `c2hs: C header contains errors: ...
Syntax error ! The symbol '*' does not fit here`, pointing at the *return
type*, which reads like a totally unrelated declaration is broken. Add the
`typedef` (alongside the ~40 existing ones, e.g. `typedef struct Currency
Currency;`).

## Multi-output shims

**A `{#fun#}` with more than one output value** (an out-parameter beyond
the trailing `char **e` error slot, e.g. a shim returning both a `double`
and a `Currency*`) uses c2hs's `alloca-` marshaller on the extra pointer
argument: `alloca-\`T'peekT*` allocates space, passes the pointer to C, and
after the call peeks the result — a stock c2hs idiom, first used here in
`ExchangeRate.exchange`/`convertToBaseCurrency`. Three non-obvious points:

- The generated Haskell type tuples as *(primary C return value, then each
  `alloca-`/other-output arg, in argument-list order)* — a shim returning
  `Currency*` as its primary value with the `double` as an out-param lands
  the tuple as `(Currency, Double)`, not `(Double, Currency)`; get the
  ordering you want by choosing which value is the primary C return.
- `alloca` needs `import Foreign.Marshal.Alloc(alloca)` in the `.chs` file
  — c2hs emits a call to a bare `alloca` and expects it in scope.
- The out-param is uninitialized memory until the C function writes it, so
  the shim **must** write a safe default (e.g. `*outCcy = 0;`) before any
  code that can throw — a null `ForeignPtr` finalizes safely; garbage does
  not.

**A `{#fun#}` with no primary return value and two output params** (a
length + a `T**`/`double*` array, no `char**` slot involved) uses
`preArray` (`QuantLib/Internal.hs`), not `alloca-`. `alloca-` (see above)
allocates space for exactly *one* extra `Storable` out-param alongside a
primary C return value; passing it two out-params for a void-returning
shim fails at c2hs's own hook-expansion step (`Function arity mismatch!
Parameter marshallers are missing`) before GHC ever sees it. `preArray ::
((Ptr CUInt, Ptr (Ptr a)) -> IO b) -> IO b` is the existing generic helper
for exactly this shape (length pointer + array-of-pointer pointer), used
with c2hs's `&` splitter and a `peekXArray`-style out-marshaller:
`preArray-`[X]'&peekXArray*` (see `qlBlackCalibrationHelperTimes`'s
`times`, and `calibrationBasket` in `QuantLib/Instrument/Swap.chs`, both
against `peek*Array :: Ptr CUInt -> Ptr (Ptr a) -> IO [b]`). Passing a bare
`alloca-` there still compiles enough to run c2hs but fails
arity-checking, not type-checking — check which of the two you have
(primary return + 1 extra out-param, vs. no primary return + a
length/array pair) before picking the marshaller.

## Yield curves are `Handle`s, not `shared_ptr`s

**A yield curve is a `Handle`, not a `shared_ptr`** — `typedef
Handle<YieldTermStructure> QlYieldTermStructure` (`cbits/qlaux.h`). That is
what lets a `RelinkableYieldTermStructure` be an ordinary member of the
`YieldTermStructure` hierarchy rather than needing sibling functions: it
upcasts through `Upcastable` like anything else, and because the upcast
copy-constructs `Handle` from `RelinkableHandle` over the same `T`, the
copy shares `link_` so relinking still reaches everything built on it.
Consequences:

- **No code in `cbits/` may *construct* a `Handle<YieldTermStructure>`** —
  `grep -rn 'Handle<YieldTermStructure>(' cbits/` must return nothing, and
  that one grep replaces a 76-site hand audit. (The bare name legitimately
  appears in the two `qlaux.h` typedefs and in comments; the trailing `(`
  marks a construction.) A `Handle` copy-constructed from a `Handle`
  **shares** the Link; one constructed from a `shared_ptr` gets a
  **fresh** one and silently stops tracking relinks. Nothing catches that:
  both type-check, both link, both are memory-safe, and a detached Link
  returns the *correct* value for the curve it was detached holding — so
  every pinned test value still passes. The whole symptom is an NPV that
  stops moving, which is why the relink tests are before/after comparisons
  rather than value assertions. Pass the handle through (`*arg(x)`, or
  `qlNullableHandle(arg(x))` when nullable) instead of rewrapping.
- **Deref with `curvePtr`/`curveRef` (`qlaux.h`), not stars.** `*arg(h)`,
  `**arg(h)` and `***arg(h)` are all well-formed on a curve handle and
  mean three different things; picking the wrong one inside a long
  argument list is exactly the failure above. Named accessors keep every
  deliberate deref greppable. Method calls need neither — `(*arg(o))
  ->discount(…)` works unchanged, because C++ chains `operator->` until it
  reaches a raw pointer.
- **There is no `Handle<Base>` conversion.** `Link` is a nested class of
  `Handle<T>`, so `Handle<Derived>::Link` and `Handle<Base>::Link` are
  unrelated types and no Link-preserving cross-level conversion exists.
  `asTermStructure` therefore hands back a snapshot that does not follow
  relinks; that is deliberate and documented, not a bug to fix.
- **Ownership under GC was measured, not assumed** —
  `relinkable-spike.md` has the numbers (RSS −0.2%, growth loop flat to
  20,000 iterations, allocation-trace lifecycle counts identical to a
  control). Don't re-run it for a new handle-shaped type; it established a
  property of `Handle<T>`. One caveat it depends on: nothing here is
  `-threaded`, and finalizers are C `FinalizerPtr`s that GHC runs inside
  the GC, so a finalizer can never mutate QuantLib's observer graph during
  a call. This build has `QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN` **off**,
  so adding `-threaded` would reopen that.

## Upcast shims

**Every `Ql*AsY` upcast shim in `cbits/` is `ret(new QlY(*arg(o)))`** — a
fresh, independently-owned handle sharing the underlying QuantLib object
via `shared_ptr` refcounting, not a non-owning pointer reinterpretation.
This is exactly the ownership pattern `Upcastable`/`AnyOf`/`freeUpcast`
assume (free the upcast intermediate immediately after the consuming call
returns); reuse it for a new hierarchy edge without re-deriving it.

## Multiple inheritance (secondary interfaces)

**Multiple inheritance where the second base is an interface needed by one
consumer** (`AffineModel`, needed only by `analyticCapFloorEngine`;
`Gaussian1dModel`, only by `Gaussian1dSwaptionEngine`): don't add a second
`Upcastable` node — `Upcastable` is single-parent (one `Base` per type), so
a second real base has nowhere to go. Mirror the `AffineModel` pattern in
`Internal/Type.hs` (search `CAffineModel'`): keep the leaf's one
`Upcastable` instance pointed at its true hierarchy parent, and separately
add a standalone (non-`Upcastable`) `qlXAsInterfaceY :: Ptr CX' -> IO (Ptr
CInterfaceY')` shim per leaf, a hand-written nested ADT (`data InterfaceY
= X X | Z Z`), and a `withInterfaceY` that pattern-matches and calls
`withUpcast qlXAsInterfaceY f` per case. The consuming engine takes the
concrete ADT directly (`` withAffineModel*`AffineModel' ``), not a
polymorphic `GenXxx m`. ADT adaptors are for passing an object as an
argument; common/overloaded methods are mostly modelled as type classes
instead (`HasImpliedVol`, `HasQuanto`).

## Cross-module enum imports

**Don't move `QuantLib.Internal.*` from `other-modules` to
`exposed-modules`** to work around a c2hs cross-module `{#import#}`
ordering problem. It only affects **enum** types referenced inside a
`{#fun#}` in another module, since `{#import M#}(Type)` needs `M`'s `.chi`
file to already exist, and `other-modules` isn't part of the
ordered-by-list-position scheme `exposed-modules` uses (reordering, even
fully serial `-j1` builds, doesn't fix it). Avoid the problem instead: add
dedicated constructors that hardcode the enum value inside their own C++
shim (`ActualActualBond' :: Schedule -> DayCounterConstructor`, see the
`reconcile-daycounters` skill), so no enum crosses a module boundary. If a
parameterized enum genuinely must cross (rare), marshal it as a plain
`Int`/`CInt` in the low-level, unexported `{#fun#}` glue only, converting
via `fromEnum` at its one call site — the public constructor stays fully
typed. Pointer/foreign types (like `Schedule`) never hit this: just
re-declare a local `{#pointer#}` in the file that needs it. This applies
even when every use of the type in that file goes through a hand-written
`with*`/`peek*` marshaller rather than a bare backtick — c2hs still needs
the local declaration to know the raw C pointee type for the `{#fun#}`'s
underlying FFI import. Skip it and c2hs silently defaults the pointee to
`()`; the error doesn't surface at the missing declaration but downstream,
as a `Couldn't match type '()' with 'CFoo''`/`Couldn't match 'Ptr (Ptr
(Ptr ()))' with '...'` at the `with*`/`peek*` call site, which reads like
a bug in that function rather than a missing import. Hit twice in the
`NonstandardSwaption`/`calibrationBasket` work: once for `Calendar`
(already covered above), once for
`QlBlackCalibrationHelper`/`QlSwapIndex`/`QlSwaptionVolatilityStructure`
in `Swap.chs`, none of which that file had previously needed as bare
types.

## Fighting the wrong layer

**A `{#fun#}` argument type reading `import Foreign.ForeignPtr(ForeignPtr)`
plus a bare `GenX (ForeignPtr a)' `` annotation is a sign you're fighting
the wrong layer.** That shape only type-checks against a marshaller whose
*output* pointer type genuinely varies with the argument
(`withGenVolatilityTermStructure :: GenVolatilityTermStructure (ForeignPtr
v) -> (Ptr v -> IO b) -> IO b`), which is wrong for any `{#fun#}` binding a
low-level import fixed to one concrete `Ptr CFoo'`. If several sibling
leaf types (e.g. `BlackVolTermStructure`, `SwaptionVolatilityStructure`)
need to accept relinkable handles polymorphically, each needs its own
dedicated `GenX`/`withX` pair in `Internal/Type.hs` performing a *real*
upcast to a fixed `Ptr CX'` (mirror
`GenBlackVolTermStructure`/`withBlackVolTermStructure`), not a shared
generic-over-`p` helper. Once that dedicated `withX` exists, the `.chs`
consumer site needs no `ForeignPtr` import at all — just
`{#pointer#}`-declare the type as usual and write `withX*`GenX y'`, exactly
like `withYieldTermStructure*`GenYieldTermStructure y'`. Reaching for a raw
Haskell FFI import inside a `.chs` file to route around a type mismatch is
almost always wrong for the same reason: the fix belongs in
`Internal/Type.hs`'s existing `Gen*`/`with*`/`peek*` API.

## `GenX` mnemonics

**`GenX` type variables are named by mnemonic, not `a`/`b`/`c`.** Every
polymorphic `GenX a` argument (across `Internal/Type.hs` and every `.chs`
call site) uses a fixed short mnemonic tied to the exact `GenX` wrapper
name, not to its position in the hierarchy — `GenTermStructure` is `t` and
`GenYieldTermStructure` is `y`, kept distinct even though one is defined in
terms of the other. This makes a mismatched-family argument visually
obvious and stops two unrelated arguments from silently unifying on a
leftover `a`/`b`. When a family appears more than once in one signature,
number the variables by argument order, reset per signature (`GenQuote q1
-> GenQuote q2 -> ...`); a single occurrence stays bare (`GenQuote q`).
Mnemonic table:

| GenX | mnem | GenX | mnem | GenX | mnem |
|---|---|---|---|---|---|
| GenQuote | `q` | GenIndex | `idx` | GenGeneralizedBlackScholesProcess | `gbs` |
| GenInstrument | `i` | GenInterestRateIndex | `ridx` | GenCalibratedModel | `m` |
| GenOption | `o` | GenInflationIndex | `iidx` | GenHestonModel | `hm` |
| GenTermStructure | `t` | GenZeroInflationIndex | `zidx` | GenShortRateModel | `sm` |
| GenYieldTermStructure | `y` | GenYoYInflationIndex | `yidx` | GenBatesModel | `bm` |
| GenVolatilityTermStructure | `v` | GenIborIndex | `ibor` | GenBatesDoubleExpModel | `bdem` |
| GenLeg | `l` | GenSwapIndex | `sidx` | GenOneFactorAffineModel | `om` |
| GenRateHelper | `rh` | GenOptionletVolatilityStructure | `ov` | GenForward | `f` |
| GenCalibrationHelper | `ch` | GenSwaptionVolatilityStructure | `sv` | GenSwap | `s` |
| GenBlackCalculator | `bc` | GenBlackVolTermStructure | `bv` | GenBond | `b` |
| | | GenStochasticProcess | `p` | GenMultiAssetOption | `mo` |
| | | GenStochasticProcess1D | `p1d` | GenOneAssetOption | `oo` |
| | | GenHestonProcess | `hp` | GenFixedVsFloatingSwap | `fvf` |
| | | GenBlackCalibrationHelper | `bch` | | |

Applies only to the actual type-variable occurrence (inside a backtick
`` `GenQuote a' `` annotation or an explicit Haskell signature), never to a
Haddock argument-name comment like `-- ^a` that happens to share the old
letter by coincidence (it names an unrelated QuantLib model parameter,
e.g. mean-reversion "a" in `blackKarasinski`). Where a shared mnemonic
would collide with an already-meaningful generic variable in the same
signature (e.g. `Bond`'s `b` colliding with the usual `(Ptr CBond' -> IO
b) -> IO b` continuation-result `b`), rename the *other*, unrelated
variable instead (to `r`) — see `withBond`/`withGenBond` in
`Internal/Type.hs`.

## Enum export and numbering

**Don't export c2hs's raw double-underscore enum constructors**
(`ActualActual__Bond`, from `add prefix = "ActualActual__"`) through any
public module — they read as generated, not like the rest of the API. Give
a user-facing case a proper dedicated constructor instead of exporting the
enum type.

**Mirror upstream's explicit enum values when it skips a deprecated
leading case.** `CPI::InterpolationType` is `AsIndex = 0, Flat = 1, Linear
= 2`, so the `cbits/qlEnumObjects.h` enum must say `CPIFlat = 1, CPILinear
= 2` rather than renumbering from 0 — renumbering silently aliases each
hasquant case to upstream's *next lower* one, and the C++ cast is
unchecked so it builds and passes with no warning. This shipped undetected
for a full session. Guard any such enum with a `test/smoke/` check that
constructs both cases from identical inputs and asserts the outputs differ
(see `test/smoke/CheckInflation.hs`'s Flat-vs-Linear NPV check); a comment
doesn't catch it. Keep the fix on the C/C++ side (the header's values,
plus the one hand-written Haskell marshaller if one exists); don't add a
Haskell-side abstraction for it.

## Strategy-tag builder structs

**A C++ builder struct with a strategy-tag field plus per-strategy
parameters** (upstream's own `Settings`-with-`.withX`-chain shape, e.g.
`LinearTsrPricer::Settings`) **collapses to a Haskell ADT that the public
function unpacks into flat shim arguments** (a tag int, a param double,
one `haveX`-style bool per optional group, plus that group's values) — not
a `withMoney`-style `&` tuple-splitter, which is only for a genuinely
fixed-shape value. A strategy struct's shape varies by branch, so the
ADT-to-flat-args unpacking happens in ordinary Haskell in the public
wrapper (see `linearTsrPricer`/`LinearTsrPricerSettings` next to the raw
`qlLinearTsrPricer` `{#fun#}` in `QuantLib/CashFlow.chs`), and the C++
shim does one `switch` on the plain tag int (with an explicit `default:
QL_FAIL`, not an unchecked cast to the C++ enum — same aliasing risk as
the bullet above) calling the matching `.withX(...)` overload. Where
upstream also has a same-named-but-fewer-args overload (e.g.
`withRateBound()` vs `withRateBound(lower, upper)`) that changes behavior
beyond supplying defaults (`LinearTsrPricer::Settings::defaultBounds_`
gates a real branch in `lineartsrpricer.cpp`), thread that distinction
through as its own `Maybe`/bool rather than always calling the
more-specific overload with hardcoded defaults — and cover it with a
`smoke/`-style value check under the specific input (there,
`VolatilityType::Normal`) where the two overloads actually diverge, since
a flat-vol/lognormal fixture may make them indistinguishable and hide a
broken `haveX` wire-through.

## `PiecewiseYieldCurve` with `GlobalBootstrap`

**`PiecewiseYieldCurve<Traits, Interpolator, GlobalBootstrap>` must be
constructed by naming the curve type first, not
`GlobalBootstrap<CurveType>(...)` directly** —
`qlTermStructureAux.cpp`'s `qlPiecewiseYieldCurveAux1` spells the
bootstrap argument `CurveType::bootstrap_type(accuracy)`.
`PiecewiseYieldCurve` stores its bootstrapper as a **value** member
(`Bootstrap<this_curve> bootstrap_;`, self-referential: the curve is the
bootstrapper's own template argument), which every `Bootstrap`
implementation relies on being able to leave lazily-instantiated until
`this_curve` is complete — `IterativeBootstrap` (the default) has no
virtual functions, so its member bodies stay uninstantiated until called.
`GlobalBootstrap` overrides pure virtuals from
`MultiCurveBootstrapContributor`, and `[temp.inst]` instantiates a class's
virtual member function *bodies* together with the class itself — so
naming `GlobalBootstrap<CurveType>` directly needs `CurveType` complete
while `CurveType` is mid-instantiation, producing a hard "field has
incomplete type" error (reproduced with both Apple clang and Homebrew
g++-16 against QuantLib 1.43 — not a compiler bug). Naming `CurveType`
first via `::bootstrap_type` makes it the outer instantiation. Don't
"simplify" the shim back to the direct spelling — it silently
reintroduces the compile failure.
