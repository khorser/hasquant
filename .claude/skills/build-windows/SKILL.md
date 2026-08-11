---
name: build-windows
description: Build and test hasquant natively on Windows (GHC 9.10.3 + MSYS2). Use when asked to build, fix, or debug the Windows build of hasquant, or to set up a fresh Windows dev box for it.
---

# Building hasquant on Windows

The full, tested recipe lives in the repo's user-facing documentation:
[`WINDOWS.md`](../../../WINDOWS.md). Read that file — it is the
single source of truth. Do not duplicate its steps here; fix them there.

Notes that are only relevant when an agent drives the build:

- The build is driven over SSH (`ssh -p 2222 -l Sergei -i ~/.ssh/claude
  <host>`, MSYS2's sshd — see the doc's last section for how it was set up).
  Paths on that box: `H:\ghc-9.10.3`, `H:\msys64`, `H:\QuantLib-1.43`,
  `H:\QuantLib-ghc`, `H:\hasquant`, `H:\cabal.exe`.
- Export `TMP`/`TEMP` in every non-interactive SSH command; an SSH session
  has neither, and Clang fails with an unrelated-looking
  `unable to make temporary file` error.
- Add `/h/ghc-9.10.3/bin` to `PATH` before any `cabal` invocation that
  needs to find `ghc` (e.g. `cabal list-bin`).
- A full QuantLib rebuild is ~970 translation units and takes well over an
  hour — never kick one off to answer a question about the recipe. Check
  the existing `H:\QuantLib-ghc` install and `H:\QuantLib-1.43\build`
  instead.
