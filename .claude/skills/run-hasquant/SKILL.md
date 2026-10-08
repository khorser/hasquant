---
name: run-hasquant
description: Build hasquant, run its test suite, and drive it via a compiled smoke-test program. Use when asked to build hasquant, run its tests, verify a new QuantLib binding actually works, or exercise a specific function end-to-end.
---

hasquant is a library, not a service. Running it means building the shim and Haskell layer, running Hspec, and compiling a standalone smoke program with `.claude/skills/run-hasquant/driver.sh` when end-to-end binding coverage is needed.

All paths below are relative to the repo root.

## Prerequisites

QuantLib 1.43 or 1.44, GHCup, GHC 9.10.3 and Cabal are expected to be installed. `cabal.project` pins dependencies to Stackage lts-24.56; README.md's "Pinned dependencies" lists the other project files. The GHC 8.10 compatibility gate uses the repository's Docker Compose setup below.

## Launcher

`./q` opens an fzf menu of the commands below (build, test, trackAllocations, GHC 9.12, `make` against Homebrew/own/head QuantLib, hlint, Docker image and GHC 8.10 gate), one hotkey each; `./q KEY [cabal args]` runs one directly. The action table is in `q`.

## Build

```bash
make                                   # C++-only compile check, fast, no Haskell rebuild
cabal build all --enable-tests         # full build; prefer through tools/quiet-build.py, see Gotchas

# final gate: also compile the two flagged executables, as CI does
tools/quiet-build.py cabal build all --enable-tests -f buildExample -f buildSofrXva
```

Plain `make` uses the `quantlib-config` on `PATH`; `brew unlink quantlib` removes it. Pick a
QuantLib with `QUANTLIB_CONFIG=<prefix>/bin/quantlib-config` (or raw `QL_CFLAGS`) and give each one
its own `OBJDIR` so switching does not rebuild everything (`-MD` tracks QuantLib headers). `./q m`,
`M` and `h` do this for Homebrew, the own install (`QL_OWN`, default `~/opt/quantlib-1.43`) and a
head checkout (`QL_HEAD`, default `~/Src/QuantLib`; a header-only cmake configure under
`cobj/head-<checkout>/` supplies `ql/config.hpp`). The head action builds whatever the checkout
holds; pull it first. Use the same QuantLib installation as `cabal.project.local` to keep header
layouts consistent.

The `app/SofrXva` executable and `test/example` are behind the default-off
`buildSofrXva`/`buildExample` flags, so a plain `cabal build all` leaves
them uncompiled and can miss API breakage. Every CI job builds both
(`.github/workflows/{linux,macos,windows}.yml`), so run the flagged build
once before declaring a change done.

`test/smoke/*.hs` is the same invisibility class and is larger: those probes
are in no cabal target at all — `driver.sh` compiles them one at a time — so
a rename or arity change leaves them stale with every gate green. After any
API change, grep `test/smoke/` for the affected names and re-run `driver.sh`
on each hit; compiling them *is* the check.

**GHC 8.10 gate.** The package supports GHC 8.10.6 / base 4.14.3.0, its
declared floor (`base >=4.14` in `hasquant.cabal`, which is edited directly).
Nothing merges until this passes:

```bash
docker compose run --rm hasquant sh -c 'ghcup install ghc 8.10.6 && cabal update && cabal build all --project-file=cabal.project.lts-18.8 --enable-tests -f buildExample -f buildSofrXva && cabal test all --project-file=cabal.project.lts-18.8 --enable-tests -f buildExample -f buildSofrXva --test-options="+RTS -V0 -RTS"'
```

(no `-it`, which fails without a TTY). The image bakes in only GHC 9.10.3;
`ghcup install` is a no-op once 8.10.6 is in the `ghcup-root` volume, and the
lts-18.8 snapshot's `with-compiler: ghc-8.10.6` selects it. The gate's project
file reads `cabal.project.lts-18.8.local`, so a host `cabal.project.local`
bind-mounted into the container does not leak in. Keep the same flags on both
commands; dropping the executable flags for `test` reconfigures and rebuilds
the library.
It catches two things the local
GHC 9.10 build cannot: post-8.10 `base` functions creeping in — often *via*
an hlint suggestion, e.g. `Data.Functor.unzip` (base 4.19+) — and types 9.10
infers but 8.10 rejects (a `let`-bound helper containing a list literal
under `OverloadedLists` over-generalised to an `IsList`-polymorphic type and
failed with `Illegal equational constraint`; fix: give the helper an
explicit signature).

`+RTS -V0` works around Rosetta on Apple Silicon (compose pins `linux/amd64`).
Rosetta appears to corrupt in-flight x87 state when a signal lands, and GHC
8.10's non-threaded RTS ticker is a `SIGVTALRM` timer. Boost's `long double`
math then fails sporadically, e.g. `non_central_chi_squared_distribution<long
double>::cdf: Random variate x is -nan` in the Heston-SLV FDM test. Not
reproduced with GHC 9.10.3 or on the native amd64 CI legs.

In case you need multiple rebuilds, prefer `docker compose run --rm -t hasquant bash` and execute commands in it to keep build artifacts.

## Run (agent path)

The driver builds `lib:hasquant` via `cabal`, registers it in a global GHC
environment file (not written into the repo), then compiles and runs a
`test/smoke/*.hs` program against it:

```bash
.claude/skills/run-hasquant/driver.sh test/smoke/CheckCalendars.hs
```

```
==> cabal build lib:hasquant
==> cabal install --lib hasquant (registers a global GHC environment file, not in-repo)
==> compiling test/smoke/CheckCalendars.hs
==> running /tmp/hasquant-smoke-CheckCalendars
...
PolandSettlement: Saturday is weekend = True
PolandWSE: Saturday is weekend = True
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

The driver also compiles `MarshallingFixture.cpp` for the result-marshalling and
temporary-ownership probes; no manual fixture build is needed for those scripts. The temporary
probe also materializes `Internal.Callback.chs`, since it compiles `Internal.Type` from source.

Compiled binaries land at `/tmp/hasquant-smoke-<name>`; build artifacts at
`/tmp/hasquant-smoke-<name>_build/`.

## Run (human path)

Same idea, spelled out manually (this is what the driver automates):

```bash
cabal build lib:hasquant
cabal install --lib hasquant --force-reinstalls   # only needed once, or after an API change
cabal exec -- ghc -itest/smoke -package hasquant test/smoke/CheckCalendars.hs \
  -o /tmp/checkcalendars -outputdir /tmp/checkcalendars_build
/tmp/checkcalendars
```

## Test

```bash
cabal test all --enable-tests --test-options=--skip=LONG   # fast path, skips tests marked (LONG)
cabal test all --enable-tests                              # full suite
```

Both pass clean on the current `HEAD`.

For version-dependent expectations, reuse `QuantLib.Spec.Helpers.quantLibAtMost143`.
It parses major/minor numerically, including suffixes such as `1.44-rc`; do not compare
version strings lexically. hasquant applies QuantLib 1.44's direct mixed-compounding restrictions on both supported versions.
For a version upgrade, build and run the suite against both matching header/library installations.
New calls on 1.43 must throw `UnsupportedQuantLibVersion`, and so must non-default values of new
arguments; test both with `unsupportedQuantLib144`. Only the bootstrap initial guess is skipped.

Slow tests are marked by suffixing `(LONG)` to the `it`/`describe`
description. The effective threshold is ~2.5s, not tens of seconds: measure
before labelling, and re-check existing labels (the equity option block was
labelled `(LONG)` while running in 0.5s).

## Coverage

Plain `cabal test --enable-coverage` runs, but is close to
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
python3 tools/hpc-coverage.py                                  # default: --test-options=--skip=LONG
python3 tools/hpc-coverage.py --test-options='--match /Quote/'  # other cabal test args
```

It always deletes hasquant's `dist-newstyle/build/*/ghc-*/hasquant-*`
directory first (needs a clean build to regenerate `.chs → .hs` output
before it can strip anything) and runs two full library builds, so budget
the time of two builds plus a test run — not something to run on every
edit. After stripping, it deletes the package's `cache/build` file:
cabal-install tracks only package sources, so without that it reports the
library up to date and the stripped `.hs` is never compiled. Command-line
`--ghc-options=-fforce-recomp` does not help; cabal leaves it out of the
configuration hash. The script fails if `QuantLib.CashFlow.mix` ends up
with no ticks. The report path prints at the end:

```
dist-newstyle/build/<arch>/ghc-<ver>/hasquant-<ver>/t/hasquant_test/hpc/vanilla/html/hpc_index.html
```

The generated `.hs` files keep their `LINE` pragmas stripped until the next
clean build, so GHC error locations for them point at the `.hs` instead of
the `.chs` in the meantime (irrelevant for a passing build, only matters if
you're mid-debugging a `.chs`-side compile error when you run this).

A **gcov/`--coverage`-on-`cbits/`** route was tried first and abandoned:
GHC's in-process TH interpreter segfaulted loading a `--coverage`-
instrumented `.dylib` for modules with real TH splices, and forcing
`-fexternal-interpreter` swapped that for a "duplicate object code" load
error from gcov's global counter symbols. The example-side splices that
originally exposed this have since been removed, but the route has not been
retested and library-side generator splices remain. Revisit it only if the
Haskell-side HPC route above turns out insufficient.

## Gotchas

- **A successful macOS link does not prove QuantLib's headers and library match.**
  `-undefined dynamic_lookup` can leave a new constructor symbol unresolved, and a
  test can terminate at its first affected call. Before testing against an upstream
  checkout, refresh its library with `cmake --build <checkout>/build --target ql_library`.
  Compare `nm -g <library> | c++filt` with the header if a constructor signature differs.
- **A segfault at the first cbits call usually means a `Date` layout mismatch.** Check which
  `ql/config.hpp` the shim saw: an `-isystem` for the QuantLib include dir demotes it behind
  Homebrew's `QL_HIGH_RESOLUTION_DATE` headers; use `-optcxx--system-header-prefix=ql/` instead.
- **Do not trust `cabal repl` or `ghci` numeric results that cross into `cbits/`.** Known-good
  pricing calls can return `0.0` in the interpreter while the compiled test binary is correct.
  Inspect intermediate values through a temporary trace in a compiled `cabal test`/`cabal run`
  path, then remove it.
- **After a repository change, run one clean warning-visible build and fix every real
  source warning it reports, including pre-existing warnings.** Use
  `rm -rf dist-newstyle` followed by
  `tools/quiet-build.py cabal build all --enable-tests -f buildExample -f buildSofrXva`; an incremental build can hide
  warnings in untouched modules. The accepted noise is the macOS linker's redundant `-U` warning. The helper suppresses only c2hs's generated
  `Foreign.ForeignPtr` unused-import block; do not hide real warnings with a module-wide pragma.
  Fix partial-function warnings with an exhaustive `case`, not another incomplete pattern.

  Run `hlint .`, not per-file linting of `.chs` inputs. Check a hint is type-correct before
  applying it; for a proven false positive, add a narrow `.hlint.yaml` exception with a short
  reason.
- **`trackAllocations` needs the built C++ objects deleted, or it silently
  does nothing.** `cabal build -f trackAllocations` does not recompile
  `cxx-sources` when only a flag changes — it reports `Up to date` while producing a library
  with no tracing in it. `touch cbits/*.cpp` and deleting
  `dist-newstyle/.../build/cbits/*.o` did not trigger it; deleting the
  whole `build/cbits` directory did. Confirm tracing is compiled in before
  trusting an empty trace: `strings <built .o> | grep -c allocated`.

  The trace destination is the `QLTRACK_ALLOCATIONS` **env var** when set,
  falling back to the compile-time path the flag bakes in. Pair the result
  with `tools/alloc-summary.py <trace>`, which matches allocations to
  frees by pointer and reports what is still live, grouped by class; it
  flags over-frees (double free, or freeing through the wrong type)
  separately from ordinary leaks. Interpret the trace as follows:
  - `ret()` is the pointer handed to Haskell and pairs with `del()`.
  - `del()` traces *twice* (`deleting` then `deleted`) for one free;
    counting both reports everything as double-freed.
  - `arg()` is pass-through, not a lifecycle event.
  - `alloc()` is ambiguous: in `ret(new
    QlYieldTermStructure(alloc(new FlatForward(...))))` the alloc'd object
    goes into a `shared_ptr` and correctly never has a matching free, but
    a value type like `DayCounter` is alloc'd, returned directly, and *is*
    freed later. Interpret this verb per pointer and ownership path.

  Don't re-derive this from the raw log; if you change the tool, re-run it
  against a hand-written trace seeding a leak, a double free, and one of
  each `alloc()` case — a permissive bug here looks exactly like a clean
  result.
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
  leaves `cabal build` silently stale: it does not track that a
  `.chs` file's `#include`d header changed, so the build reports success
  without re-running c2hs, and tests then pass against the *old* generated
  code. Do a clean build if in doubt. This is exactly why the smoke
  scripts exist and why this driver is the harness to reach for after any
  enum/header-only change, not just `cabal test`.

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
- **Never spell a GC nudge by hand: `QuantLib.Context.collectGarbage` is
  the one exported name for it.** It is `performGC >> performGC`, with
  haddock saying plainly that `performGC` only *schedules* finalizers, so it
  is a nudge rather than a guarantee. If a site ever needs a `threadDelay`
  for the finalizer thread to actually get scheduled, add it *inside*
  `collectGarbage` and re-run everything -- do not re-scatter the idiom
  across call sites, which is exactly the state it was consolidated out of.
- **A new hspec test that sets `Context.evaluationDate` must wrap its body in
  `Context.keepingSettingsGc`, not a manual trailing `collectGarbage`.**
  `QuantLib.Context.keepingSettingsGc` is a `bracket`-based helper that
  already runs `collectGarbage` right before restoring the saved `Settings`
  singleton — on normal completion *and* on an exception, which a manual
  trailing call does not cover. Nearly every hspec test that mutates the
  evaluation date is already wrapped in it
  (`test/hspec/QuantLib/Spec/DatesAndSchedule.hs` has dozens of examples);
  don't add a second, redundant `collectGarbage` on top -- nor a mid-body
  double GC, which is what the three sites in
  `test/hspec/QuantLib/Spec/TermStructure.hs` did before `keepingSettingsGc`
  itself was strengthened to the double sweep, and which were deleted then.
  This matters especially
  for a test anchored to a fixed historical date with a long internal
  schedule (a term price surface, a piecewise curve with a maturity decades
  out): without the bracket's GC, a still-alive `LazyObject` from that test
  can crash an unrelated *later* test once a subsequent
  `Context.setEvaluationDate` call notifies observers and the old object's
  now-past termination date trips `effective date ... later than or equal
  to termination date ...` deep in QuantLib. `keepingSettingsGc`/
  `keepingSettings`'s own restore-on-exception behavior has a direct
  regression test in `test/hspec/QuantLib/Spec/DatesAndSchedule.hs`
  (`describe "settings"`) — extend it, don't re-derive it, if this ever
  needs re-verifying.
- **Native fair spreads can leave residuals with compounded overnight spreads.**
  QuantLib 1.44 RC's MTM NPV/BPS spread calculation does not exactly reprice the combined
  overnight/stub fixture with `compoundSpread` enabled; raw C++ matches the binding.
  Check such options fixtures against discounted live leg cash flows. Keep exact par
  checks on ordinary non-compounded spreads, and document the native limitation.
- **Reproduce a suspicious zero or garbage upstream result in raw C++ before blaming a binding.**
  Compile a probe with `c++ -std=c++17 $(quantlib-config --cflags) -isystem/opt/homebrew/include
  probe.cpp -L/opt/homebrew/lib -lQuantLib`; `quantlib-config` omits the Boost include path. Upstream
  smile sections can `catch (...)` and return `0.0` (`Gaussian1dSmileSection::volatilityImpl`), so
  call the uncaught inner step (`optionPrice`) to see the error. QuantLib 1.43's fixing-date
  `MakeSwaption` constructor leaves its nominal uninitialized; `qlGaussian1dSwaptionVolatility`
  works around it with shim subclasses overriding the virtual `optionPrice`/`smileSectionImpl`.
- **A smoke script must not `try`/`catch` on `QuantLib.Context.Error`.**
  `Error` is defined in `QuantLib.Internal` and re-exported by
  `QuantLib.Context`. Compiled standalone from the repo root, ghc finds
  `QuantLib/Internal.hs` as *source* (via `Context.chs`'s import) and
  recompiles it, so the script's `Error` is a different type from the one
  the installed library throws: `try` never matches, and the script dies
  with the very message it was written to catch — with no type error,
  since both sides typecheck against their own `Error`. Catch
  `SomeException` instead (`test/smoke/CheckIterativeBootstrap.hs` does,
  with the reason inline).
