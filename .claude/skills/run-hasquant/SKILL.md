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

## Gotchas

- **Build through `tools/quiet-build.py`, not raw `stack build`.** c2hs
  injects an unused `Foreign.ForeignPtr` import into every generated
  module, producing 28 identical unactionable `-Wunused-imports`
  warnings that bury real ones: `python3 tools/quiet-build.py stack
  build --test --no-haddock`.
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
- **A stale build can pass tests against old generated code.** Editing
  a C header (e.g. `cbits/qlEnumObjects.h`) without touching any `.chs`
  file leaves `cabal build`/`stack build` silently stale — see
  `CLAUDE.md`'s "Stale builds" section. This is exactly why the smoke
  scripts exist and why this driver is the harness to reach for after
  any enum/header-only change, not just `stack test`.
