# hasquant

Haskell bindings to QuantLib through c2hs and a C++ shim in `cbits/`. The library binds QuantLib directly; QuantLib-SWIG is prior art for API shape, never an implementation dependency.

hasquant is a thin pricing, curve-building, and risk kernel. Application orchestration, a composition DSL, and independent reimplementations of QuantLib's numerical machinery are out of scope. A future DSL belongs in a sibling project.

## Before inventing a workaround

Search this file, the codebase, and the relevant skill first. Reuse established c2hs enum imports, hierarchy families, secondary interfaces, marshallers, and wide-constructor machinery. These patterns carry non-obvious ABI and ownership constraints. Cross-cutting enums belong in `QuantLib.Internal.Common` to avoid import cycles.

When research exposes a reusable convention or failure mode that is not documented, update the relevant skill as part of the same task.

## Skills

Repository skills live in `.claude/skills/` and are also exposed to Codex through `.agents/skills/`. Read every applicable `SKILL.md` completely before changing code.

**Adding bindings**

- `add-quantlib-class` — bind a new QuantLib class or hierarchy member.
- `add-quantlib-method` — add a constructor, method, or getter to an already-bound class.
- `add-quantlib-adt` — choose and implement enum, live-object, or nested-ADT representations.
- `add-quantlib-options-record` — add an options-record entry point when there are more than 10 trailing defaulted parameters.
- `add-quantlib-index` — add or reconcile Ibor, overnight, or swap indexes.

**Build, test, and platform**

- `run-hasquant` — build, test, and smoke-test bindings end to end.
- `build-windows` — build and test on Windows with GHC 9.10.3 and MSYS2.
- `audit-allocations` — audit C-side allocation tracing and verify leaks, over-frees, and ownership labels.

**Reference and code generation**

- `c2hs-shim-patterns` — c2hs pragmas, shim marshalling, template dispatch, and ownership gotchas.
- `template-haskell-patterns` — maintain `QuantLib.Internal.Syntax` generators and verify their generated declarations.

**Reconciliation audits**

- `reconcile-calendars`, `reconcile-currencies`, `reconcile-daycounters` — synchronize the corresponding enums with installed QuantLib.

## Build and test

Use `run-hasquant` for commands and required gates. Product, pricing, and behavioral regressions belong in CI-run Hspec tests under `test/hspec/`. Use `test/smoke/` only for binding-specific probes Hspec cannot reliably cover: enum dispatch, marshalling, ownership, pointer lifetime, constructor order, and hierarchy wiring. Do not duplicate Hspec coverage.

After a repository change, run one clean warning-visible build and fix every real source warning it reports, including pre-existing warnings. The `run-hasquant` skill lists the two accepted generated-code/linker warnings. Run `hlint .`; do not lint individual `.chs` files.

Scale numeric tolerances to the result magnitude, normally about `1e-6` relative. Optimizer and bootstrapping results can vary around `1e-4` across architectures.

## API design

- Bind only the requested surface by default, but include a neighboring binding when it reuses the same open header, marshalling, and fixture without separate investigation.
- Do not mirror the C++ hierarchy mechanically. A class needs a dedicated Haskell type only when it has a meaningful class-specific calculation/getter or must be accepted at that exact type. Thin constructors may return an existing parent type.
- Avoid `dynamic_cast` and `dynamic_pointer_cast` in `cbits/` unless upstream itself forces a downcast. Prefer a concrete leaf type and compile-time-typed getters. If an accessor exposes a missing intermediate base, widen the Haskell family instead; use the `add-quantlib-class` hierarchy procedure.
- Upstream-erased type information cannot be recovered safely. Read both the declaration and implementation before promising a concrete accessor from a base-typed return.
- Place modules by topical family, not C++ inheritance. Keep generic root modules for hierarchy-wide operations.
- Bind few inspectors. Exclude values that merely echo construction inputs unless another bound producer computes them. Apply this per producer; an unchecked sibling binding is not precedent. If echo getters were the only reason for a leaf type, omit the leaf too.
- New setters or mutators require explicit user confirmation before implementation. Existing exceptions are engine/pricer wiring, the process-global `Settings` API, and `SimpleQuote.setValue`. Prefer construction-time options.
- Keep public APIs concrete. Internal `Finalizable` and `Upcastable` constraints are normal, but do not expose ad-hoc public typeclass constraints without a compelling need.
- Choose collection types by semantics and scale: lists for small possibly-empty collections, `NonEmpty` when emptiness is invalid, storable `RealVector`/`RealMatrix` for large homogeneous numeric data, and boxed matrices for small fixed-dimensional inputs.
- Use collections of tuples for positionally paired inputs. Keep independent grid axes separate.
- Reuse tuple conventions instead of wrapper types: `Period` is `(Int|Word, TimeUnit)`, bond price/type is `(Double, BondPriceType)`, and `Money` is `(Double, Currency)`. Matching inputs and outputs should use the same shape.
- Collapse `std::variant<Real, Handle<Quote>>`-style inputs to one `GenQuote` API. A numeric caller can use `simpleQuote`; do not expose a second flat-`Double` overload.
- Widen a small defaulted tail in place. With more than 10 trailing defaulted parameters, preserve the narrow API and add a full options-record entry point backed by the same widened C shim.
- For hot-loop callbacks, first look for a reusable inner primitive that lets Haskell drive the outer loop. Otherwise cross the FFI at the coarsest upstream-supported granularity. If neither is possible, a genuine fine-grained callback is acceptable and must follow the lifetime rules in `add-quantlib-adt`.

## Fixtures and examples

- Before inventing expected values, search `~/Src/QuantLib/test-suite/*.cpp` for a matching fixture and confirm it is constructible with current bindings. Otherwise use a meaningful self-consistency check.
- Monte Carlo golden tests need a fixed nonzero seed. Add a martingale-style forward-mean check to FX/equity process examples.
- `Calendar.advance` with `Days` counts business days. To reproduce upstream `Date + Period(n, Days)`, use plain `Data.Time.Calendar.addDays`.
- Derive an exercise/query date and its year fraction from the same source; do not independently round a time fraction into a date.
- If a historical QuantLib golden value disagrees systematically, reproduce the fixture in raw C++ against the installed library before diagnosing the binding.
- Tests that change `Settings.evaluationDate` must use `Settings.keepingSettings'`. Never hand-write the double-`performGC` nudge; use `Settings.collectGarbage` only when finalization is needed outside settings restoration.
- Document custom-payoff engine compatibility anywhere a public function accepts one; several upstream engines require a striked payoff and two bound FD engines otherwise dereference a failed cast.

## C shim and generated code

- Follow `c2hs-shim-patterns` for pointer pragmas, exception shims, marshalling, multiple inheritance, and runtime enum-to-template dispatch.
- Runtime integers selecting template arguments belong in the shared generic-lambda dispatchers in `cbits/*Aux.cpp`. Do not restore per-caller switch duplication. Dispatchers take an explicit result type; trailing `decltype(make(...))` can compile while omitting a required vtable.
- Allocation tracing is centralized in `cbits/qlaux.h`. Add tracing verbs there and use `audit-allocations`; do not add scattered `QLTRACK_ALLOCATIONS` branches.
- Factory-table constructors return the base pointer type so allocation and finalizer labels agree.
- Prefer shared low-level plumbing in `QuantLib.Internal`, `.Type`, or `.Common` over raw `foreign import ccall` declarations scattered through binding modules.
- Use `template-haskell-patterns` for all `derive*` work. Generated top-level names intentionally use `mkName`; splice placement and cross-version constructor shapes are load-bearing.

## Tracking and documentation

- Update the hierarchy tree in `QuantLib/Internal/Type.hs` whenever a hierarchy changes.
- Update affected lines in `tools/ql-methods-1.43.txt` when binding or rejecting a method. `x` means permanently reviewed and rejected; bulk exclusions must be detector-backed, and coverage audits must verify against `cbits/*.h` rather than trust the dump alone.
- Put persistent architectural gaps in README.md's Roadmap. Use `plans/README.md` only for subplan status. Remove roadmap items when their feature is completed.
- Keep `test/main/QuantLib/MainTest.hs` as a thin dispatcher; put specifications in topical `QuantLib.Spec.*` modules and shared helpers in `QuantLib.Spec.Helpers`.

## Modus operandi

Show the todo list for multi-step tasks. Keep comments short and about current purpose or rationale; do not preserve implementation history in source comments. Preserve useful upstream Haddock detail.
