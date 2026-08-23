---
name: run-hasquant
description: Build hasquant, run its test suite, and drive it via a compiled smoke-test program. Use when asked to build hasquant, run its tests, verify a new QuantLib binding actually works, or exercise a specific function end-to-end.
---

`hasquant` is a Haskell library (FFI bindings to QuantLib via c2hs, with a
C++ shim in `cbits/`) — there is no server or GUI to launch. "Running" it
means: build the C++ shim + Haskell layer, run the hspec test suite, and
(the part a README won't tell you) compile-and-run a standalone `smoke/*.hs`
program against the built library — this repo's own established way to
prove a binding actually works, not just that the build succeeded. Drive it
via `.claude/skills/run-hasquant/driver.sh`.

All paths below are relative to the repo root.

## Prerequisites

QuantLib 1.43 and GHC/stack/cabal are expected to already be installed
(this repo's `CLAUDE.md` documents the full dev setup, including the
GHC 8.10 Docker gate — not repeated here). Nothing further was needed to
run the commands below.

## Build

```bash
make                                   # C++-only compile check, fast, no Haskell rebuild
stack build --test --no-haddock        # full build; prefer through tools/quiet-build.py, see Gotchas
```

**GHC 8.10 gate.** The package supports GHC 8.10.6 / base 4.14.3.0, its
declared floor (`base >=4.14`, set in `package.yaml` — `hasquant.cabal` is
hpack-generated, so edit the former and let `stack build` regenerate the
latter). Nothing merges until this passes:

```bash
docker compose run --rm hasquant sh -c 'stack build --resolver lts-18.8 --flag hasquant:buildExample --no-haddock && stack --resolver lts-18.8 test'
```

(no `-it`, which fails without a TTY). It catches two things the local
GHC 9.10 build cannot: post-8.10 `base` functions creeping in — often *via*
an hlint suggestion, e.g. `Data.Functor.unzip` (base 4.19+) — and types 9.10
infers but 8.10 rejects (a `let`-bound helper containing a list literal
under `OverloadedLists` over-generalised to an `IsList`-polymorphic type and
failed with `Illegal equational constraint`; fix: give the helper an
explicit signature).

## Run (agent path)

The driver builds `lib:hasquant` via `cabal`, registers it in a global GHC
environment file (not written into the repo), then compiles and runs a
`smoke/*.hs` program against it:

```bash
.claude/skills/run-hasquant/driver.sh smoke/CheckSabrSmileSection.hs
```

```
==> cabal build lib:hasquant
==> cabal install --lib hasquant (registers a global GHC environment file, not in-repo)
==> compiling smoke/CheckSabrSmileSection.hs
==> running /tmp/hasquant-smoke-CheckSabrSmileSection
OK   ShiftedLognormal strike=0.01 vol   0.4197993819773641
...
SabrInterpolatedSmileSection: OK, calibrated smile reproduces the generating SABR vols
```

Just build and register the library (no smoke script) with:

```bash
.claude/skills/run-hasquant/driver.sh --build-only
```

There's no existing smoke script for what you're checking? Write one in
`smoke/` (see any file there for the pattern: import the relevant
`QuantLib.*` modules, construct objects, assert on the results, `error` on
failure) and pass its path to the driver — that's the whole point of the
harness.

Compiled binaries land at `/tmp/hasquant-smoke-<name>`; build artifacts at
`/tmp/hasquant-smoke-<name>_build/`.

## Run (human path)

Same idea, spelled out manually (this is what the driver automates):

```bash
cabal build lib:hasquant
cabal install --lib hasquant --force-reinstalls   # only needed once, or after an API change
cabal exec -- ghc -ismoke -package hasquant smoke/CheckSabrSmileSection.hs \
  -o /tmp/checksabr -outputdir /tmp/checksabr_build
/tmp/checksabr
```

## Test

```bash
stack test --ta '--skip LONG'          # fast path: ~3s, skips tests marked (LONG)
stack build --test --no-haddock        # full suite: ~26s, 141 examples
```

Both pass clean on the current `HEAD`.

Slow tests are marked by suffixing `(LONG)` to the `it`/`describe`
description. The effective threshold is ~2.5s, not tens of seconds: measure
before labelling, and re-check existing labels (the equity option block was
labelled `(LONG)` while running in 0.5s).

## Gotchas

- **Build through `tools/quiet-build.py` to see warnings that matter** —
  `tools/quiet-build.py stack build --test --no-haddock`, or pipe into it.
  c2hs emits `import qualified Foreign.ForeignPtr as C2HSImp` into every
  generated module, unused wherever pointer types are `{#pointer ...
  nocode#}` (nearly everywhere), so a full build carries 28 identical,
  unactionable `-Wunused-imports` warnings, blamed on an innocent `.chs`
  import line by c2hs's line mapping. The script drops exactly that block
  and nothing else, and prints how many it hid. Don't reach for `{-#
  OPTIONS_GHC -Wno-unused-imports #-}` instead: the noise had already
  hidden a real unused `Foreign.Ptr` import in `Instrument/Credit.chs` and
  two live `-Wname-shadowing` warnings in
  `test/example/QuantLib/Example/MulticurveBootstrapping.hs`, which a
  per-module pragma would also have suppressed. C++ noise is *not* handled
  here — that's `-isystem` in the `Makefile` and `package.yaml`.
- **After testing: no new compilation warnings, and a clean `hlint` run.**
  Check a hint actually holds before applying it — two here turned out
  wrong. `Avoid NonEmpty.unzip` fires on the bare name `unzip` in *any*
  module importing `Data.List.NonEmpty`, with no type resolution: it flags
  plain `Prelude.unzip` over ordinary lists, and importing
  `Data.Functor.unzip` explicitly doesn't silence it. For a genuinely wrong
  hint, add a targeted `- ignore: {name: ..., within: Module}` to
  `.hlint.yaml` with the evidence in a comment rather than contorting the
  code.
- **`trackAllocations` needs the built C++ objects deleted, or it silently
  does nothing.** Neither `cabal build --flag trackAllocations` nor `stack
  build --flag hasquant:trackAllocations` recompiles `cxx-sources` when
  only a flag changes — both report `Up to date` while producing a library
  with no tracing in it. `touch cbits/*.cpp` and deleting
  `dist-newstyle/.../build/cbits/*.o` did not trigger it; deleting the
  whole `build/cbits` directory did. Confirm tracing is compiled in before
  trusting an empty trace: `strings <built .o> | grep -c allocated`.

  Trace destination is the `QLTRACK_ALLOCATIONS` **env var** when set,
  falling back to the compile-time path the flag bakes in. Pair the result
  with `tools/alloc-summary.py <trace>`, which matches allocations to
  frees by pointer and reports what is still live, grouped by class; it
  flags over-frees (double free, or freeing through the wrong type)
  separately from ordinary leaks. **Reading the trace correctly is the
  whole difficulty** — the tool got it wrong twice before its first real
  trace:
  - `ret()` is the pointer handed to Haskell and pairs with `del()`.
  - `del()` traces *twice* (`deleting` then `deleted`) for one free;
    counting both reports everything as double-freed.
  - `arg()` is pass-through, not a lifecycle event.
  - `alloc()` is ambiguous: in `ret(new
    QlYieldTermStructure(alloc(new FlatForward(...))))` the alloc'd object
    goes into a `shared_ptr` and correctly never has a matching free, but
    a value type like `DayCounter` is alloc'd, returned directly, and *is*
    freed later. Same verb, opposite expectation, distinguishable only per
    pointer.

  Don't re-derive this from the raw log; if you change the tool, re-run it
  against a hand-written trace seeding a leak, a double free, and one of
  each `alloc()` case — a permissive bug here looks exactly like a clean
  result.
- **`stack build` and `cabal build` are two independent build systems
  here** and don't share installed-package state. The test suite
  (`stack test`) and the smoke-script driver (`cabal exec -- ghc
  -package hasquant`) go through different toolchains — building with
  `stack` does not make `cabal exec` see the new code. Rebuild with
  `cabal build lib:hasquant` (the driver's first step) before running a
  smoke script, even right after a `stack build`.
- **`cabal install --lib hasquant` fails if already registered**
  ("Packages requested to install already exist in environment file") —
  the driver passes `--force-reinstalls` to make re-registering after an
  API change idempotent.
- **Don't use `cabal install --lib hasquant --package-env .`** — that
  writes a `.ghc.environment.*` file into the repo root, an untracked
  stray that `git status` will flag. Plain `cabal install --lib
  hasquant` registers a *global* environment file under
  `~/.ghc/<arch>/environments/default` instead, which is what the
  driver does.
- **A stale build can pass tests against old generated code.** Editing a C
  header (e.g. `cbits/qlEnumObjects.h`) without touching any `.chs` file
  leaves `cabal build`/`stack build` silently stale: neither tracks that a
  `.chs` file's `#include`d header changed, so the build reports success
  without re-running c2hs, and tests then pass against the *old* generated
  code. Do a clean build if in doubt. This is exactly why the smoke
  scripts exist and why this driver is the harness to reach for after any
  enum/header-only change, not just `stack test`.

  A compiled build is not proof that generated enum cases actually
  changed. `test/smoke/` holds standalone end-to-end value-level checks
  for that, run via `cabal exec -- ghc -package hasquant test/smoke/Foo.hs
  -o /tmp/foo && /tmp/foo`. **Whenever you add an enum-dispatched case** (a
  new currency, calendar, or index variant — see the `reconcile-*`/
  `add-quantlib-index` skills), add or extend a `test/smoke/` script that
  constructs the new case and prints something derived from it, and
  actually run it. This is what catches the staleness above and any
  enum/factory-table order mismatch; `test/` won't, since it doesn't know
  about cases it was never written to check.
- **A new hspec test that sets `Settings.evaluationDate` must wrap its body in
  `Settings.keepingSettings'`, not a manual trailing `performGC`.**
  `QuantLib.Settings.keepingSettings'` is a `bracket`-based helper that
  already runs `performGC` right before restoring the saved `Settings`
  singleton — on normal completion *and* on an exception, which a manual
  trailing call does not cover. Nearly every hspec test that mutates the
  evaluation date is already wrapped in it
  (`test/hspec/QuantLib/Spec/DatesAndSchedule.hs` has dozens of examples);
  don't add a second, redundant `performGC` on top. This matters especially
  for a test anchored to a fixed historical date with a long internal
  schedule (a term price surface, a piecewise curve with a maturity decades
  out): without the bracket's GC, a still-alive `LazyObject` from that test
  can crash an unrelated *later* test once a subsequent
  `Settings.setEvaluationDate` call notifies observers and the old object's
  now-past termination date trips `effective date ... later than or equal
  to termination date ...` deep in QuantLib. `keepingSettings'`/
  `keepingSettings`'s own restore-on-exception behavior has a direct
  regression test in `test/hspec/QuantLib/Spec/DatesAndSchedule.hs`
  (`describe "settings"`) — extend it, don't re-derive it, if this ever
  needs re-verifying.
- **A smoke script must not `try`/`catch` on `QuantLib.Type.Error`.**
  Compiled standalone from the repo root, ghc finds `QuantLib/Type.hs` as
  *source* and recompiles it, so the script's `Error` is a different type
  from the one the installed library throws: `try` never matches, and the
  script dies with the very message it was written to catch — with no type
  error, since both sides typecheck against their own `Error`. Catch
  `SomeException` instead (`test/smoke/CheckIterativeBootstrap.hs` does,
  with the reason inline).
