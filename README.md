Haskell bindings to [QuantLib](https://www.quantlib.org/), the free/open-source C++ library for quantitative finance — rates, bonds, options, swaps, credit, inflation, and equity derivatives, with the associated term structures, indexes, and pricing engines. Around 1000 constructors and non-trivial methods are bound so far, covering roughly a tenth of QuantLib's surface.

I deliberately kept the API low-level rather than build a framework on top of it, so it composes into whatever higher-level API you actually need instead of imposing one. The only departure from a thin wrapper is enums and ADTs standing in for things that are classes on the C++ side (see "On Types" below) — everything else maps close to 1:1 onto the underlying QuantLib call.

This started as a hand-written project in 2012 (see "Project History" below) and has gone through several architecture rewrites since. The core design — the pointer-ownership model, the enum/ADT scheme, the C shim conventions — is hand-designed and predates any AI involvement. More recently I've used AI assistance to extend coverage faster (new classes, methods, day counters, indexes), but every generated binding is reviewed against the pattern it's supposed to follow, checked against the upstream C++ signature, and covered by a test before it's considered done — see "Testing" below for what that actually means in practice.

Examples live in `main/test/QuantLib/MainTest.hs` and `test/QuantLib/Example`. They're direct translations of QuantLib's own examples and test suite, not idiomatic Haskell — the goal there is fidelity to a known-correct reference, not style.

Haddock documentation is published at https://khorser.github.io/hasquant

# Testing

Bindings aren't just compiled and eyeballed. Where QuantLib's own `test-suite/*.cpp` covers a class or scenario, the corresponding hasquant test reuses its inputs and cached expected values directly, rather than deriving numbers by hand or relying on self-consistency alone. Enum-dispatched cases (currencies, calendars, day counters, index variants) get a standalone `smoke/` check that constructs every case and asserts on the output — this is what caught a real bug where two enum cases silently aliased to the wrong upstream values despite a clean build and passing test suite. New method/class bindings are cross-checked against `tools/ql-methods-1.43.txt`, a line-by-line tracking dump of every constructor and non-trivial method upstream, so coverage claims are verifiable rather than asserted.

# Building

The current version was mostly tested with GHC-9.10.3, but it should work with newer or reasonably older versions (at least as old as 8.10.6), since I deliberately avoided advanced language features.

Linux and macOS are the primary, well-tested platforms. Windows builds work too, but QuantLib has to be rebuilt with GHC's own bundled Clang first — see [`WINDOWS.md`](WINDOWS.md) for the (short) recipe.

## Stack

Minimal build: `stack build --no-haddock --no-test`

Run tests: `stack build --test --no-haddock`

Build and run examples: `stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example`, also `--flag hasquant:buildExample` is required if you want to use HLS with examples.

Build and run examples enabling tracking of memory allocations (log every object as it
is created and deleted):
`stack build --no-haddock --flag hasquant:buildExample --flag hasquant:trackAllocations $* && stack exec hasquant_example`

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

The repo contains docker compose files for a custom Linux x86_64 image. You can use it like this:
`docker compose run --rm -it hasquant sh -c 'stack build --flag hasquant:buildExample --no-haddock && stack exec hasquant_example && stack test'`

The config mounts `/root/.stack`, `/root/.ghcup` and `/hasquant/.stack-work` as named volumes so
everything installed with stack/ghcup will persist.

# On Types

I deliberately avoided typeclasses, as the code quickly becomes polluted by typeclass constraints.

## How to read types

If you see a function accepting `CallableBond`, you can pass only instances of callable bonds.
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

# TODO
- (Perpetual) Add more classes and methods. You will need to update `cbits/qlaux.h`, `qlTypesC2HS.hs`, and then add some boilerplate to corresponding `.h`, `.cpp`, `Internal/Type.hs` and `.chs` files. This can be simplified with scripting/LLMs. Refer to `CLAUDE.md`, `.claude/skills`, and `tools` for more detailed information useful even for manual steps.
- Add more nonempty lists or vectors for some functions where applicable
- Use QuantLib Handles/RelinkableHandle for volatility structures to support native QuantLib semantics (done for yield curves and quotes: see `relinkableYieldTermStructure`/`linkTo` and `QuantLib.Quote.relinkableQuote`/`linkTo`)
- Design a declarative embedded DSL
- Review interfaces for consistency, add obviously missing features and fix contradictions to the current design
- See [github issues](https://github.com/khorser/hasquant) for more formalized tasks

# Project History

## 0.1.0.0 (2012-2013)

Initial implementation. Two projects: qlc (C part like wxcore) and quantlib.

The latter used Template Haskell to build code that marshalls data, given a foreign declaration and a function signature.

Tried to separate exceptions into two types: checked (via Either) and unchecked (IO).

Some ideas of handling C++ templates were taken from QuantLibXL.

All broke with the next Haskell release (7.8?), where you could no longer use TH to define a function when its signature is known (I used the signature to build the actual marshalling of arguments).

Heavy use of typeclasses to express inheritance (with lots of extensions used).

Due to some quirks in the interaction between TH and foreign code, I had to create a custom cabal `Setup.hs` because TH had to load my C code during compilation.

Some code was generated by scripts using Doxygen files.

``` haskell
  vanillaSwap :: VanillaSwapType -- ^type
    -> Double -- ^nominal
    -> Schedule -- ^fixedSchedule
    -> Double -- ^fixedRate
    -> DayCounter -- ^fixedDayCount
    -> Schedule -- ^floatSchedule
    -> IborIndex -- ^iborIndex
    -> Double -- ^spread
    -> DayCounter -- ^floatingDayCount
    -> BusinessDayConvention -- ^paymentConvention
    -> IO VanillaSwap
  vanillaSwap = $(ffiCall 'vanillaSwap) c_vanillaSwap -- automatic generation of marshalling code

  foreign import ccall safe "ql.h qlVanillaSwap"
    c_vanillaSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr CSchedule -> Ptr CIborIndex -> CDouble -> Ptr CDayCounter -> CInt -> Ptr CString -> IO (Ptr CVanillaSwap)
```

## 0.2.0.0 (2021)

Migrated to C2HS, which actually resulted in more manageable code.

Typeclasses were used again to express inheritance relations and to use marshalling provided by C2HS.

Haddock comments on function arguments were lost in the process.

## 0.2.5.0 (2022)

Got rid of typeclasses, which required introducing more boilerplate and more manual marshalling to work around some C2HS shortcomings.

But now I'm able to avoid some dangerous extensions.

Revived allocation tracking in C++ code to ensure all objects are freed properly.

Restored Haddock comments on function arguments.

Without typeclasses, the inheritance can be expressed even better — if you don't look at the code underlying it ;)

E.g., you don't need to chain asXXX casts, and in most cases you don't need the casts at all.

As part of the effort, I generalized arguments (e.g., `GenBond a` instead of `Bond`).

Eventually, some typeclasses emerged again, but they're not visible to the end user.

## 0.2.6.0 (2026)

Finished migration to the new approach without explicit typeclasses — time to publish.

## 0.2.7.0 (2026)

Polished FFI helpers and reduced technical debt. Updated static data, added inflation.

## 0.4.0.0 (2026)

Extended the functionality, added more instruments and asset classes
