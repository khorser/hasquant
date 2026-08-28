Haskell bindings to [QuantLib](https://www.quantlib.org/), the free/open-source C++ library for quantitative finance — rates, bonds, options, swaps, credit, inflation, and equity derivatives, with the associated term structures, indexes, and pricing engines. 1500+ constructors and non-trivial methods are bound so far, covering roughly 15% of QuantLib's surface.

hasquant gives Haskell direct access to production-grade pricing, curve-building, and risk models from QuantLib. Rather than wrapping it in a new framework, it stays a thin, close-to-1:1 layer over the C++ API, so it composes into whatever architecture you're already building instead of dictating one.

Coverage already spans the parts of QuantLib people actually reach for in practice: yield/credit/inflation/volatility term structures and their bootstrapping helpers, IBOR/overnight/swap/inflation indexes, fixed and floating bonds (including amortizing, callable, and convertible), vanilla and exotic options (barrier, Asian, compound, variance, basket), swaps (vanilla, CMS, OIS, CDS, zero-coupon), and the corresponding pricing engines — analytic, tree, finite-difference, and Monte Carlo — for models from Black-Scholes through SABR and Heston.

Type safety is held to a noticeably higher bar than a typical C++ binding. QuantLib's class hierarchies are mirrored with phantom-typed pointers (`GenBond a`, `GenQuote a`, …) rather than one flat handle type, so passing the wrong kind of object is a compile error, not a runtime crash; upcasting is the only implicit conversion, and it's structurally guaranteed safe. Declarations on the C++ and Haskell sides are kept in step by `c2hs` rather than by hand-written FFI stubs. The C++ shim layer has zero `dynamic_cast`/`dynamic_pointer_cast` call sites — classes that need runtime-checked downcasts upstream get a dedicated leaf type instead — and enum-like C++ types are bound with explicit value mirroring rather than an unchecked numeric cast, closing off a whole class of silent-corruption bugs that plain FFI bindings are prone to.

The main departures from a thin wrapper are enums and ADTs standing in for things that are classes on the C++ side (see "On Types" below), and the ownership layer that makes the pointer types safe; individual calls still map close to 1:1 onto the underlying QuantLib call. Coverage is curated rather than exhaustive: getters that only echo a value the caller already passed to the constructor are deliberately left unbound, so the binding surface tracks what's actually useful to call rather than every method QuantLib happens to expose.

This started as a hand-written project in 2012 (see "Project History" below) and has gone through several architecture rewrites since. The core design — the pointer-ownership model, the enum/ADT scheme, the C shim conventions — is hand-designed and predates any AI involvement. More recently I've used AI assistance to extend coverage faster: new classes, methods, day counters, indexes. Every generated binding is still reviewed against the pattern it's supposed to follow, checked against the upstream C++ signature, and covered by a test before it counts as done — see "Testing" below for what that means in practice.

Worked examples live in `test/example/QuantLib/Example`. Most are direct translations of QuantLib's own examples and test suite, not idiomatic Haskell — the goal there is fidelity to a known-correct reference, not style; `QuickStart` (see "Quick Example" below) is the one written for readability instead. The test suite proper is `test/main/QuantLib/MainTest.hs`, a dispatcher over the topic modules in `test/hspec/QuantLib/Spec`.

The package is published on Hackage at https://hackage.haskell.org/package/hasquant, with Haddock documentation for the current `master` available at https://khorser.github.io/hasquant

# Quick Example

Build a hand-generated schedule, a discount curve from a handful of hardcoded zero rates, an overnight-indexed swap off both, and price it:

``` haskell
let today = 2 `january` 2024
setEvaluationDate (Just today)

cal <- calendar TARGET
settle <- advance cal today (2, Days) Following False
let maturity = addGregorianYearsClip 5 settle

dc <- dayCounter (Actual360 False)
curve <- interpolatedZeroCurve
  [ (settle, 0.030)
  , (addGregorianYearsClip 1 settle, 0.032)
  , (addGregorianYearsClip 2 settle, 0.034)
  , (addGregorianYearsClip 5 settle, 0.036)
  , (addGregorianYearsClip 10 settle, 0.038)
  ] dc cal [] Linear

sofr <- overnightIborIndex Sofr (Just curve)

sched <- schedule (Just settle) maturity (1, Years) cal
  ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

ois <- overnightIndexedSwap Payer 10000000 sched 0.035 dc sofr 0.0
  0 Following cal False AveragingCompound Nothing 0 False

engine <- discountingSwapEngine curve (Just False) Nothing Nothing
setPricingEngine ois engine

npv ois >>= print       -- 70994.8441727506
fairRate ois >>= print  -- 3.6554153626327204e-2
```

This is `QuantLib.Example.QuickStart`'s `run` (`test/example/QuantLib/Example/QuickStart.hs`), a real, compiled, tested example — not just illustrative prose — wired into `stack exec hasquant_example` and pinned by a test in `test/hspec/QuantLib/Spec/Examples.hs`, so this snippet can't silently drift from working code.

# Goals and Scope

hasquant's job is to be the pricing/curve-building/risk kernel other things call into — a building block and backend "calculator" for higher-level actions, from cash flow discounting up through Monte Carlo exposure simulations — not a framework that dictates how those actions get orchestrated. `app/SofrXva` is the model of that split in practice: it owns its own CSV parsing and pipeline wiring, and calls into hasquant only for curve construction and discounting.

Two things follow from that split:

- **Reference data is a first-class use, not a side effect of pricing.** The calendar/currency/day-counter/index enums (kept in sync with installed QuantLib via the `reconcile-*` skills) are useful on their own — a consumer can depend on hasquant purely for holiday calendars or index conventions and never touch a pricing engine.
- **Same inputs, reproducible outputs.** Monte Carlo bindings and examples are built on a fixed nonzero RNG seed (never `seed = 0`, which QuantLib treats as "seed from entropy") specifically so a calculator built on hasquant gets consistent results run to run.

Out of scope, deliberately:
- QuantLib's own numerical backbone — interpolation, optimization, linear algebra, RNG internals. Haskell already has libraries for that; hasquant won't reimplement or independently bind them unless a concrete binding actually needs one exposed.
- A declarative embedded DSL for composing actions — that would mean hasquant deciding how callers compose pricing calls, which cuts against staying a thin backend. If it happens, it's a sibling project built on top of hasquant rather than something inside it (see Roadmap below).

## Roadmap
- (Perpetual) Add more classes and methods. You will need to update `cbits/qlaux.h`, `cbits/qlTypesC2HS.h`, and then add some boilerplate to corresponding `.h`, `.cpp`, `Internal/Type.hs` and `.chs` files. This can be simplified with scripting/LLMs. Refer to `CLAUDE.md`, `.claude/skills`, and `tools` for more detailed information useful even for manual steps.
- Evaluate whether some [OpenSourceRiskEngine](https://opensourcerisk.org) functionality should be bound
- Add more nonempty lists or vectors for some functions where applicable
- A declarative embedded DSL for composing hasquant calls, as a separate sibling project — not started, kept here so the intent stays visible
- An agent-callable tool interface over the composition DSL above, so an LLM builds and prices products by calling into validated hasquant algorithms instead of generating pricing logic itself — e.g. an agent parses a term sheet's free text, then calls the tool to actually construct and price the product. Term-sheet parsing stays LLM territory; product construction and pricing goes through the tool. Depends on the DSL existing first, since the tool would be the DSL's agent-facing entry point. Open questions: tool grain (one coarse "build and price" call vs. several narrower calls the agent chains itself — coarse is safer against hallucinated intermediate steps) and transport (MCP or similar, as a thin wrapper — this wrapper lives in the sibling project, not inside hasquant itself, per the scope split above)
- Review interfaces for consistency, add obviously missing features and fix contradictions to the current design
- See [github issues](https://github.com/khorser/hasquant/issues) for more formalized tasks

# Testing

Bindings aren't just compiled and eyeballed. Where QuantLib's own `test-suite/*.cpp` covers a class or scenario, the corresponding hasquant test reuses its inputs and cached expected values directly, rather than deriving numbers by hand or relying on self-consistency alone. Enum-dispatched cases (currencies, calendars, day counters, index variants) get a standalone `test/smoke/` check that constructs the cases and asserts on the output — this is what caught a real bug where two enum cases silently aliased to the wrong upstream values despite a clean build and a passing test suite.

Coverage is tracked rather than claimed: `tools/ql-methods-1.43.txt` is a line-by-line dump of every constructor and non-trivial method in QuantLib's headers, and each new binding flips its line as it lands. An HPC coverage report for the test suite against `master` is published at https://khorser.github.io/hasquant/coverage/hpc_index.html

# Building

Day-to-day development happens on GHC-9.10. GHC-8.10.6 (`base >= 4.14`) is the supported floor and is verified on every change against the lts-18.8 Docker image below; newer versions should work too, as the public API sticks to widely available language features.

First you need QuantLib version 1.43 or higher, see installation documentation for [Linux](https://www.quantlib.org/install/linux.shtml), [MacOS](https://www.quantlib.org/install/macosx.shtml),
or cross-platform [CMake-based build](https://www.quantlib.org/install/cmake.shtml)

Linux and macOS are the primary, well-tested platforms. Windows builds work too, but QuantLib has to be rebuilt with GHC's own bundled Clang first — see [`WINDOWS.md`](WINDOWS.md) for the recipe.

## Stack

Minimal build: `stack build --no-haddock --no-test`

Run tests: `stack build --test --no-haddock`

Build and run examples: `stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`.
The example executable is `buildable: False` without that flag, so HLS also needs it — add `package hasquant` / `flags: +buildExample` to a local `cabal.project.local` to edit `main/exe` with HLS.

Build and run examples enabling tracking of memory allocations (log every object as it
is created and deleted):
`stack build --no-haddock --flag hasquant:buildExample --flag hasquant:trackAllocations && stack exec hasquant_example`

The trace goes to stderr by default. Set the `QLTRACK_ALLOCATIONS` environment variable
to send it to a file instead, which is usually what you want — redirecting stderr also
swallows the program's own output, and a trace is only useful next to the values it
explains:

`QLTRACK_ALLOCATIONS=/tmp/trace.log stack exec hasquant_example`

A raw trace is thousands of interleaved lines. `tools/alloc-summary.py /tmp/trace.log`
pairs allocations with frees by pointer and reports what is still live, grouped by
class, listing double frees separately from ordinary leaks; it exits non-zero if
anything is unaccounted for, so it can gate a check.

**One trap worth knowing:** neither cabal nor stack recompiles `cxx-sources` when only
a flag changes, so turning `trackAllocations` on for an already-built tree reports
success and produces a library with no tracing in it — an empty trace and no error.
Delete the built C++ objects (the `build/cbits` directory) first, and confirm with
`strings <a built .o> | grep -c allocated` before trusting an empty result.

Run GHCi: `stack ghci --ghci-options $(find .stack-work \( -name "*.so" -o -name "*.dylib" \) -print -quit)`

## Cabal

Standard build: `cabal configure --disable-documentation && cabal build`

Build with documentation: `cabal configure --enable-documentation && cabal build`

Build example: `cabal configure -f buildExample --disable-documentation && cabal build`

Build example and tests: `cabal configure -f buildExample --enable-tests --disable-documentation && cabal build`

## Docker

The repo contains docker compose files for a custom Linux x86_64 image. You can use it like this to run tests using GHC-8.10.6:
`docker compose build`, `docker compose run --rm -it hasquant stack --resolver lts-18.8 test`

Drop `-it` when running without a TTY (CI, or a scripted check) — it fails there.

The config mounts `~/.stack`, `~/.ghcup`, and `~/.cabal` as named volumes so everything installed with stack/ghcup/cabal will persist across runs.
`/hasquant/.stack-work` and `/hasquant/dist-newstyle` are mounted as anonymous volumes to avoid polluting host filesystem.

# On Types

I deliberately kept typeclasses out of public signatures, as the code quickly becomes polluted by typeclass constraints. A few remain as internal plumbing, but you never have to satisfy one yourself.

## How to read types

If you see a function accepting `CallableBond`, you can pass only callable bonds.
But if a function accepts `GenBond a`, you can pass a `Bond` or any of its derivatives: `FixedRateBond`, `ConvertibleBond`, `CallableBond`.
This works thanks to the following definition:
``` haskell
type Bond = GenBond CBond
type FixedRateBond = GenBond CFixedRateBond
type ConvertibleBond = GenBond CConvertibleBond
type CallableBond = GenBond CCallableBond
```

And if a function accepts `GenInstrument a` (like `npv`), you can pass any instrument at all.
While this is convenient, it leads to some allocation and deallocation on each call, so you might consider using `asBond` and `asInstrument` to get an object of the required type.
