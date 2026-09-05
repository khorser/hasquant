---
name: run-hasquant
description: Build hasquant, run its test suite, and drive it via a compiled smoke-test program. Use when asked to build hasquant, run its tests, verify a new QuantLib binding actually works, or exercise a specific function end-to-end.
---

hasquant is a library, not a service. Running it means building the shim and Haskell layer, running Hspec, and compiling a standalone smoke program with `.claude/skills/run-hasquant/driver.sh` when end-to-end binding coverage is needed.

All paths below are relative to the repo root.

## Prerequisites

QuantLib 1.43 and GHC/Stack/Cabal are expected to be installed. The GHC 8.10 compatibility gate uses the repository's Docker Compose setup below.

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
`test/smoke/*.hs` program against it:

```bash
.claude/skills/run-hasquant/driver.sh test/smoke/CheckSabrSmileSection.hs
```

```
==> cabal build lib:hasquant
==> cabal install --lib hasquant (registers a global GHC environment file, not in-repo)
==> compiling test/smoke/CheckSabrSmileSection.hs
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
`test/smoke/` (see any file there for the pattern: import the relevant
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
cabal exec -- ghc -itest/smoke -package hasquant test/smoke/CheckSabrSmileSection.hs \
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

## Coverage

Plain `stack test --coverage --ta '--skip LONG'` runs, but is close to
useless here: every c2hs-generated binding module (`QuantLib.CashFlow`,
`QuantLib.Instrument.*`, `QuantLib.Time.Calendar`, …) reports `0/0` — not
low coverage, *zero instrumentable expressions* — even though these
modules contain real monadic marshalling code (`withLeg a1 $ \a1' -> ...
>>= \res -> ...`), not bare `foreign import`s. The generated `.hs` carries
`{-# LINE n "Foo.chs" #-}` pragmas remapping every declaration back to
`.chs` source positions; GHC's HPC pass assigns tick locations respecting
those pragmas, then can't reconcile a tick claiming to be in `Foo.chs` (a
preprocessor input, never itself compiled) with the module it's
instrumenting, and silently records nothing rather than erroring. Confirmed
by hand: stripping the `LINE` pragmas from one generated module's `.hs` and
recompiling it standalone with `-fhpc` took its `.mix` file from 0 tick
entries to 3170.

`tools/hpc-coverage.py` automates the fix — for every c2hs-generated
module, force a clean rebuild, strip the `LINE` pragmas from the generated
`.hs` before GHC compiles it, then run the suite:

```bash
python3 tools/hpc-coverage.py                    # default: --ta '--skip LONG'
python3 tools/hpc-coverage.py --ta ''             # pass through other stack test args
```

It always starts with `stack clean hasquant` (needs a clean build to
regenerate `.chs → .hs` output before it can strip anything) and runs two
full library builds, so budget the time of two `stack build`s plus a test
run — not something to run on every edit. Report locations print at the
end; the useful one is the per-component report for `hasquant_test`, e.g.:

```
.stack-work/install/<arch>/<snapshot>/<ghc>/hpc/hasquant/hasquant_test/hpc_index.html
```

(there's also a `hpc/combined/all/hpc_index.html` "unified" report, but its
totals don't reconcile with the sum of its own listed per-module rows on
this codebase — something about how stack merges `.tix` data across
components inflates it; don't trust it as a percentage). `.stack-work` is
already gitignored, so the report needs no separate cleanup — but note the
generated `.hs` files under `.stack-work` now permanently have their `LINE`
pragmas stripped until the next `stack clean`/fresh c2hs run, which makes
GHC error locations for anything compiled from them point at the `.hs`
instead of the `.chs` in the meantime (irrelevant for a passing build, only
matters if you're mid-debugging a `.chs`-side compile error when you run
this).

A **gcov/`--coverage`-on-`cbits/`** route was tried first and abandoned:
GHC's in-process TH interpreter segfaults loading a `--coverage`-
instrumented `.dylib` for any module with a real TH splice (i.e. any
`$(free1st/free2nd/...)` use from `QuantLib.Syntax`, which is most of
`test/example/`), and forcing `-fexternal-interpreter` swaps that for a
"duplicate object code" load error from gcov's global counter symbols
instead. Not revisited unless the Haskell-side HPC route above turns out
insufficient.

## Gotchas

- **Do not trust `cabal repl` or `ghci` numeric results that cross into `cbits/`.** Known-good
  pricing calls can return `0.0` in the interpreter while the compiled test binary is correct.
  Inspect intermediate values through a temporary trace in a compiled `cabal test`/`cabal run`
  path, then remove it.
- **After a repository change, run one clean warning-visible build and fix every real
  source warning it reports, including pre-existing warnings.** Use
  `stack clean hasquant` followed by
  `tools/quiet-build.py stack build --test --no-haddock`; an incremental build can hide
  warnings in untouched modules. The accepted noise is Stack's non-portable `cpp-options: -P`
  note and the linker's redundant `-U` warning. The helper suppresses only c2hs's generated
  `Foreign.ForeignPtr` unused-import block; do not hide real warnings with a module-wide pragma.
  Fix partial-function warnings with an exhaustive `case`, not another incomplete pattern.

  Run `hlint .`, not per-file linting of `.chs` inputs. Check a hint is type-correct before
  applying it; for a proven false positive, add a narrow `.hlint.yaml` exception with a short
  reason.
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
- **Never spell a GC nudge by hand: `QuantLib.Settings.collectGarbage` is
  the one exported name for it.** It is `performGC >> performGC`, with
  haddock saying plainly that `performGC` only *schedules* finalizers, so it
  is a nudge rather than a guarantee. If a site ever needs a `threadDelay`
  for the finalizer thread to actually get scheduled, add it *inside*
  `collectGarbage` and re-run everything -- do not re-scatter the idiom
  across call sites, which is exactly the state it was consolidated out of.
- **A new hspec test that sets `Settings.evaluationDate` must wrap its body in
  `Settings.keepingSettings'`, not a manual trailing `collectGarbage`.**
  `QuantLib.Settings.keepingSettings'` is a `bracket`-based helper that
  already runs `collectGarbage` right before restoring the saved `Settings`
  singleton — on normal completion *and* on an exception, which a manual
  trailing call does not cover. Nearly every hspec test that mutates the
  evaluation date is already wrapped in it
  (`test/hspec/QuantLib/Spec/DatesAndSchedule.hs` has dozens of examples);
  don't add a second, redundant `collectGarbage` on top -- nor a mid-body
  double GC, which is what the three sites in
  `test/hspec/QuantLib/Spec/TermStructure.hs` did before `keepingSettings'`
  itself was strengthened to the double sweep, and which were deleted then.
  This matters especially
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
