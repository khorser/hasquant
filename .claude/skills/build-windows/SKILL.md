---
name: build-windows
description: Build and test hasquant natively on Windows (GHC 9.10.3 + MSYS2). Use when asked to build, fix, or debug the Windows build of hasquant, or to set up a fresh Windows dev box for it.
---

# Building hasquant on Windows

[`WINDOWS.md`](../../../WINDOWS.md) is the build recipe. Do not duplicate its steps here; update it when they change.

Notes that are only relevant when an agent drives the build:

- The build is driven over SSH (`ssh -p 2222 -l Sergei -i ~/.ssh/claude
  <host>`, MSYS2's sshd — see the doc's last section for how it was set up).
  Paths on that box: `H:\ghc-9.10.3`, `H:\msys64`, `H:\boost-inc`,
  `H:\QuantLib-1.43` (CMake build dir is `build-clean`, not `build`),
  `H:\QuantLib-ghc`, `H:\hasquant`, `H:\cabal.exe`.
- Export `TMP`/`TEMP` in every non-interactive SSH command; an SSH session
  has neither, and Clang fails with an unrelated-looking
  `unable to make temporary file` error.
- Set `MSYS2_ARG_CONV_EXCL='*'` whenever you pass `H:/...` or `-optcxxH:/...`
  arguments to a native Windows binary from an MSYS2 shell; otherwise MSYS2
  rewrites them into nonsense like `H:H:/msys64/...`. The flip side: with it
  set, `/h/...` paths are *not* translated either, so pass Windows-style
  paths for everything (including `-o` outputs).
- Add `/h/ghc-9.10.3/bin` to `PATH` before any `cabal` invocation that
  needs to find `ghc` (e.g. `cabal list-bin`).
- SSH sessions get killed when the command returns, taking backgrounded
  children with them — `nohup ... &` is not enough. Launch long builds as
  `setsid nohup script.sh </dev/null >/dev/null 2>&1 & disown`, logging to a
  file, then poll that file from later connections.
- A full QuantLib rebuild is ~976 translation units and takes ~35 min on
  that box — don't kick one off to answer a question about the recipe.
  Individual `clang++ -c` runs against `H:\QuantLib-1.43\ql\...` with the
  flags from `build-clean/build.ninja` answer most "is this flag needed?"
  questions in seconds. Use `-O3 -Wall` (not `-w -O1`) when doing so: some
  of the libc++ overload-resolution failures only surface at the real
  warning/optimisation settings.
- `ninja` intermittently fails with `Permission denied` / `Access is denied`
  on `.obj.d` depfiles (virus scanning). Re-run it; it resumes.
- When a Windows-only failure can't be reproduced anywhere else, put the
  fixture in a standalone `tools/debug/*.cpp` probe -- no Haskell, no
  hasquant -- and run it from the `Windows HestonSLV probe`
  (`.github/workflows/windows-debug.yml`) `workflow_dispatch` job, which
  restores the same QuantLib cache `windows.yml` builds and never fails the
  run (a throw is the expected output, so the probe catches and prints it).
  `workflow_dispatch` only appears once the workflow file is on `master`, so
  a probe has to be merged before it can be dispatched. Compile the same
  probe locally first to get a baseline log to diff the Windows one against.
