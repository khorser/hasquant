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
- **If the standalone probe *passes* on Windows while the suite still fails,
  the difference is process state, not arithmetic -- run the same probe body
  from inside a GHC process.** Guard the probe's `main` with a
  `-D..._NO_MAIN` and export its sections as `extern "C"`, then link the
  object into a `base`-only Haskell driver (`tools/debug/HestonSLVProbe.hs`,
  built without `-threaded` to match `hasquant_test`) with
  `ghc <driver>.hs <probe>.o -lQuantLib -optl<libc++.a> ...`. Have both
  binaries dump the x86 FP environment (MXCSR's FTZ/DAZ/RC bits, the x87
  control word, `fegetround`) around each stage: a divergence there explains
  a libQuantLib call that throws under the RTS and returns without it.
  Keeping hasquant out of that driver is deliberate -- it isolates the RTS.
- **The third rung is a hasquant-linked driver, and it only needs
  `cabal build lib:hasquant`** -- not `cabal build all --enable-tests`. Write
  `cabal.project.local` exactly as `windows.yml` does, build the library
  alone, then `cabal exec -- ghc -package hasquant <driver>.hs <probe>.o`
  with the same `-optl` libc++ flags. Running the fixture outside hspec
  splits two causes the suite conflates: a throw means hasquant's own path
  (shim marshalling, or what its dylib does to the process), while a pass
  means the trigger is elsewhere in the suite's randomized order. Gate it on
  a `workflow_dispatch` boolean so one dispatch can cover all three rungs.
- **By the time Haskell code runs on Windows the x87 precision control is at
  53-bit (control word `0x027f`, PC=2), where a `clang++`-linked binary has
  64-bit extended (`0x037f`, PC=3).** Every 80-bit `long double`
  operation is therefore silently rounded to double, so anything routing
  `double` maths through `long double` -- every `boost::math` distribution,
  via its default `promote_double` policy -- can fail to converge or return
  garbage only under GHC. Dump the control word with `fnstcw` before
  theorising; `PC=(cw >> 8) & 3`.
  - The individual functions are *not* broken: `ldexpl`, `logl`, `expl`,
    `powl`, `sqrtl` all return correct values in both links, and
    `-lmingwex` changes nothing. The one-line check that does separate them
    is whether `1.0L + ldexpl(1, -63) != 1.0L`, and the same call under
    `policies::promote_double<false>` is exact in both.
  - Restore it with `fldcw`, not `_controlfp_s`: MSVC's CRT documents
    `_MCW_PC` as unsupported on x64. Haskell's own `Double` arithmetic uses
    SSE and is governed by MXCSR, so changing the x87 word does not affect
    it. A namespace-scope initializer does not stick -- it compiles, links,
    and the test still fails -- and GHC's weak-symbol RTS hooks
    (`defaultsHook` and friends) are the wrong shape twice over: one-shot
    per process for a per-thread register, and a library defining one
    collides with any program that defines the same. hasquant exposes
    `QuantLib.Settings.setExtendedPrecision` for the caller to invoke at
    startup instead of hooking the marshalling path.
  - When diagnosing, note that mingw's `printf` has no `%Lg`: it prints
    subnormal nonsense (`…e-312`) for a long double in the *passing* binary
    too, so cast to `double` for display, and distrust an `…e-312` figure in
    a boost error message as evidence about the value itself.
