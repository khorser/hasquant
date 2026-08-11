# Building hasquant on Windows

This works, but it's fragile — the whole recipe exists to route around one
core problem: **there are two separate C++ toolchains on a typical Windows
Haskell dev box, and they are not compatible with each other.**

1. **GHC's own bundled toolchain** (`H:\ghc-9.10.3\mingw\...`) — this is what GHC's
   RTS (runtime system) was built with. It ships a full, self-contained
   Clang/LLVM install (Clang 14.0.6 with GHC 9.10.3), including its own C++
   standard library: **libc++** (not the GNU one).
2. **MSYS2's toolchain** (`H:\msys64\mingw64\...`) — a normal, independent
   MSYS2 install. Its GCC uses the GNU C++ standard library: **libstdc++**.
   This is where Boost lives, because GHC doesn't ship Boost.

QuantLib needs Boost. Boost only exists in MSYS2's world. But GHC's RTS
needs GHC's own world. Mixing the two — compiling QuantLib with one
toolchain and linking it against Haskell's RTS from the other — produces
linker errors that look unrelated to each other but all trace back to this
one root cause.

**The fix that actually works:** compile *everything* — QuantLib, the C++
shim, and the final executable — with **GHC's own bundled `clang++`**, and
only reach into MSYS2 for two things it doesn't have any alternative for:
Boost's headers, and a newer `lld` linker (GHC's bundled one is old enough
to have a real bug — see Step 5).

If you're picking this up cold, read through once before touching anything —
the steps build on each other and skipping ahead will cost you the same
debugging loop this doc exists to save you from.

## Paths used below

Everything below is written against the layout of the box this was tested
on. If yours differs, these are the only six strings to search and replace —
nothing in the recipe depends on the specific drive letter, and paths are
spelled out literally throughout so the blocks stay copy-pasteable.

| Path | What it is |
| --- | --- |
| `H:\ghc-9.10.3` | GHC install (bundles Clang/libc++ under `mingw\`) |
| `H:\msys64` | MSYS2 install (Boost headers, `ld.lld`) |
| `H:\QuantLib-1.43` | QuantLib source checkout |
| `H:\QuantLib-ghc` | where QuantLib gets installed by Step 4 |
| `H:\cabal.exe` | `cabal-install` binary |
| `H:\hasquant` | this repo's checkout |

Note that some blocks below spell the same directory with forward slashes
(`H:/ghc-9.10.3/...`) — that's deliberate: CMake, the `#include` lines and
GHC's `-optcxx`/`-optl` flags all want forward slashes, while `cd`/`set`
in a `cmd` window want backslashes.

## Prerequisites

- Windows box with GHC 9.10.3 and `cabal.exe`. GHC's own install already
  bundles a full Clang/libc++ toolchain — you do **not** need to install a
  separate C++ compiler for GHC's side of things.
- MSYS2, with these `mingw64`-environment packages:
  ```
  pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-cmake \
            mingw-w64-x86_64-ninja mingw-w64-x86_64-lld
  ```
  `mingw-w64-x86_64-lld` is the one easy to miss — it is **not** pulled in
  by the base `mingw-w64-x86_64-toolchain` meta-package (that one's
  GCC/`ld.bfd`-based) and is a separate, explicit install. It's needed
  only for its `ld.lld.exe` binary (Step 5) — a recent LLVM linker to
  replace GHC's own bundled, much older one. You do not need MSYS2's
  `clang`/`clang++` for anything in this recipe; every C++ compile step
  uses GHC's own bundled `clang++` instead (Step 1 and Step 5).
- QuantLib 1.43 source checked out at `H:\QuantLib-1.43`.
- (Recommended) SSH access into the box, so you can drive the whole build
  from a normal terminal instead of clicking through a Windows console —
  see "Setting up SSH access" at the bottom if you need this from scratch.

## Step 1 — Create the compatibility header

GHC's bundled libc++ and MSYS2's mingw C headers don't fully agree with
each other on a handful of standard math/string functions. Without this
fix, you'll hit compile errors like `no member named 'isnan' in namespace
'std'` scattered across dozens of files, in ways that seem to appear and
disappear depending on which file happens to include what first.

This has to exist *before* the `cmake` invocation in Step 2, which passes
it via `-include` — CMake's own compiler sanity check fails if the file is
missing.

Create `H:\QuantLib-1.43\build\mingw_libcxx_cmath_fix.h`:

```cpp
#ifndef MINGW_LIBCXX_CMATH_FIX_H
#define MINGW_LIBCXX_CMATH_FIX_H
#include <math.h>
#ifdef __cplusplus
#undef isnan
#undef isinf
#undef isnormal
#undef isfinite
#undef signbit
#undef fpclassify
inline bool isnan(double x) { return __builtin_isnan(x); }
inline bool isinf(double x) { return __builtin_isinf(x); }
inline bool isnormal(double x) { return __builtin_isnormal(x); }
inline bool isfinite(double x) { return __builtin_isfinite(x); }
inline bool signbit(double x) { return __builtin_signbit(x); }
inline int fpclassify(double x) { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x); }
#include "H:/ghc-9.10.3/mingw/include/c++/v1/stdlib.h"
#include "H:/ghc-9.10.3/mingw/include/c++/v1/wctype.h"
#include <cstdlib>
#include <cwctype>
#include <vector>
#endif
#endif
```

**Why this is shaped exactly like this — don't reorder it casually:**

- The `#undef` + real-function-definition block *must* come before the
  `#include <cstdlib>` / `#include <vector>` lines at the bottom. Those
  headers transitively pull in `<cmath>`, and `<cmath>` only exposes
  `std::isnan` etc. if a real (non-macro) `::isnan` is already visible
  *at the moment it's processed*. Define-then-include, always in that
  order — if a future edit needs to add another header to this file,
  add it at the bottom, after the function definitions, not above them.
- The `#include "H:/ghc-9.10.3/.../stdlib.h"` and `wctype.h` lines use **absolute
  paths** into GHC's own bundled libc++, not `<stdlib.h>` / `<wctype.h>`
  in angle brackets. This is because once `-isystem H:/msys64/mingw64/include`
  is added (needed for Boost, see Step 5), angle-bracket includes for these
  two headers resolve to MSYS2's plain C versions instead of GHC's
  libc++-aware wrapper versions — silently losing the extra C++ overloads
  libc++ adds (e.g. `abs(double)`, `iswspace` in `std::`). Pointing at the
  exact file sidesteps the ambiguity.
- Do **not** add your own `abs(long)` / `abs(long long)` overloads here —
  libc++'s own `stdlib.h` wrapper already declares the full overload set
  including `float`/`double`/`long double`; redeclaring any of them
  yourself produces a "missing exception specification" conflict.

## Step 2 — Configure QuantLib to build with GHC's clang++, not MSYS2's

Don't reuse an existing QuantLib build directory — start fresh, or you'll
end up fighting stale CMake cache settings from an earlier attempt.

```
mkdir H:\QuantLib-1.43\build
cd H:\QuantLib-1.43\build
cmake -G Ninja ^
  -DCMAKE_CXX_COMPILER=H:/ghc-9.10.3/mingw/bin/clang++.exe ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_INSTALL_PREFIX=H:/QuantLib-ghc ^
  -DBoost_INCLUDE_DIR=H:/msys64/mingw64/include ^
  -DCMAKE_CXX_FLAGS="-include H:/QuantLib-1.43/build/mingw_libcxx_cmath_fix.h -fno-implicit-modules -fno-implicit-module-maps" ^
  -DQL_BUILD_EXAMPLES=OFF -DQL_BUILD_TEST_SUITE=OFF -DQL_BUILD_BENCHMARK=OFF ^
  ..
```

## Step 3 — Fix the parts of QuantLib that need libc++/mingw workarounds

Two known gaps that Step 1's header doesn't cover, because they're not
generic mingw/libc++ mismatches — they're places where QuantLib's own code
relied on GCC/libstdc++-specific leniency:

1. **One file is missing `#include <vector>`.** libc++'s `<iosfwd>` only
   forward-declares `std::vector` (unlike libstdc++, which tends to pull
   in the full definition transitively). If you hit `implicit
   instantiation of undefined template 'std::vector<...>'` in some
   `ql/time/calendars/*.cpp` file, that file is missing a direct
   `#include <vector>` — but this is already covered by the fix header's
   own `#include <vector>` at the bottom, so you shouldn't actually hit
   this if you're using the header from Step 1 unmodified.

2. **Two experimental features don't compile at all under libc++ and are
   excluded.** `ql/experimental/asian/analytic_{cont,discr}_geom_av_price_heston.cpp`
   (a niche Asian-option pricing engine) and the four files under
   `ql/experimental/catbonds/` (catastrophe bonds) each hit a deeper,
   unresolved incompatibility between libc++'s `<complex>`/`<random>`
   headers and this specific GHC-bundled Clang/libc++ version — the
   symptom is `reference to unresolved using declaration` for things like
   `isnan`/`signbit` *inside* `<complex>` itself, which no amount of the
   Step 1 fix header resolves. hasquant doesn't bind either of these
   QuantLib features, so simply excluding them from the build is fine.
   Comment out these six lines in `ql/CMakeLists.txt`'s source list
   (search for the filenames — they appear once each, prefixed with four
   spaces):
   ```
   experimental/asian/analytic_cont_geom_av_price_heston.cpp
   experimental/asian/analytic_discr_geom_av_price_heston.cpp
   experimental/catbonds/catbond.cpp
   experimental/catbonds/catrisk.cpp
   experimental/catbonds/montecarlocatbondengine.cpp
   experimental/catbonds/riskynotional.cpp
   ```
   If you ever need these features, that's a separate investigation —
   don't just delete this exclusion without solving the underlying
   `<complex>`/`<random>` issue first, or the build will fail again in a
   much less obvious way (mid-build, deep in an unrelated-looking file).

## Step 4 — Build and install QuantLib

```
cd H:\QuantLib-1.43\build
ninja
ninja install
```

This installs headers to `H:\QuantLib-ghc\include` and the static library to
`H:\QuantLib-ghc\lib\libQuantLib.a`. It's a genuinely full build (~970 translation
units) — expect it to take a while.

If you hit new compile errors not covered above, they'll almost always be
more instances of the same two failure families from Step 1/3 (a missing
`std::` overload, or a file needing `<complex>`/`<random>` that nothing
here has been tested against) — check which family it is before reaching
for a new fix.

## Step 5 — Configure hasquant to use this QuantLib build

Create/replace `cabal.project.local` in the hasquant repo root (the
`ghc-options:` line is a single long line — no line breaks):

```
ignore-project: False
tests: True

package hasquant
  extra-include-dirs: H:/QuantLib-ghc/include
  extra-lib-dirs: H:/QuantLib-ghc/lib
  ghc-options: -pgmcxx H:/ghc-9.10.3/mingw/bin/clang++ -optl--ld-path=H:/msys64/mingw64/bin/ld.lld.exe -optl-LH:/ghc-9.10.3/mingw/x86_64-w64-mingw32/lib -optl-lmingwex -optl-lmingw32 -optl H:/ghc-9.10.3/mingw/lib/libc++.a -optl H:/ghc-9.10.3/mingw/lib/libc++abi.a -optl H:/ghc-9.10.3/mingw/lib/libunwind.a -optcxx-isystem -optcxxH:/msys64/mingw64/include -optcxx-include -optcxxH:/QuantLib-1.43/build/mingw_libcxx_cmath_fix.h -optcxx-fno-implicit-modules -optcxx-fno-implicit-module-maps
```

Walking through what each piece does and why it's there:

- **`-pgmcxx H:/ghc-9.10.3/mingw/bin/clang++`** — tells GHC to compile the
  `cbits/*.cpp` shim with GHC's own bundled `clang++`, matching what
  QuantLib was built with in Step 2. If you accidentally leave this
  pointing at MSYS2's `clang++`, or don't set it at all, you'll get
  cryptic `duplicate section ... has different size` linker errors —
  that's the linker noticing two incompatible C++ ABIs colliding.

- **`-optl--ld-path=H:/msys64/mingw64/bin/ld.lld.exe`** — forces the
  *final link* to use MSYS2's `lld` (a recent LLVM release) instead of
  GHC's own bundled `lld`, which ships with GHC's ancient Clang 14.0.6.
  This one is subtle and worth understanding: Clang encodes things like
  `operator new` and certain exception-handling helpers as COFF "weak
  external symbols with a default fallback" — a real, standard PE/COFF
  feature. GHC's old bundled `lld` (and GNU `ld.bfd`, if you're tempted
  to reach for it — don't) doesn't handle this correctly, and produces
  `undefined reference to operator new(unsigned long long)` and
  similar errors that look like a missing-library problem but aren't. A
  newer `lld` handles it fine. Do **not** try `-fuse-ld=bfd` here — it
  looks superficially promising (it clears the very first linker error
  you'll hit) but leads to a much deeper rabbit hole of the same
  underlying COFF-weak-symbol problem resurfacing differently at every
  subsequent stage.

- **`-optl-LH:/ghc-9.10.3/mingw/x86_64-w64-mingw32/lib -optl-lmingwex
  -optl-lmingw32`** — explicitly links GHC's own bundled mingw C runtime
  import libraries. Without this, you'll see `undefined reference to
  strdup` / `getpid` / `mkdir` / `wcsdup` from `libHSrts` itself — GHC's
  RTS needs its own mingw runtime, not MSYS2's, and forcing `--ld-path`
  above apparently stops GHC's driver from adding these automatically.

- **`-optl H:/ghc-9.10.3/mingw/lib/libc++.a -optl H:/ghc-9.10.3/mingw/lib/libc++abi.a
  -optl H:/ghc-9.10.3/mingw/lib/libunwind.a`** — explicitly links GHC's own
  static C++ runtime. Pass these as raw file paths (not `-l` flags) to
  avoid ld picking the *dynamic* `libc++.dll.a` instead, which would
  otherwise clash with the static `libc++abi.a` (both define overlapping
  symbols, producing `multiple definition of std::runtime_error::what()`
  and friends).

- **`-optcxx-isystem -optcxxH:/msys64/mingw64/include`** — needed so the
  shim's own `cbits/*.cpp` files (which `#include <ql/...>` and
  therefore transitively hit Boost) can find Boost's headers.

- **`-optcxx-include -optcxxH:/QuantLib-1.43/build/mingw_libcxx_cmath_fix.h`** —
  applies the *same* compatibility header from Step 1 to the shim's own
  compilation, for the same reasons.

- **`-optcxx-fno-implicit-modules -optcxx-fno-implicit-module-maps`** —
  disables Clang's implicit module cache for the shim compile, matching
  the QuantLib build flags, avoiding a possible source of stale-state
  confusion (Clang can cache a parsed system header's state keyed on the
  header file itself, independent of surrounding `-include`/macro state —
  better to just turn this off than debug it if it ever bites).

**Do not set `-pgml`** (the linker-driver override) directly — if you do,
GHC's own internal Template Haskell bytecode linker starts probing
MSYS2's library directories too, and chokes trying to parse
`H:\msys64\mingw64\lib\libmingwex.a` (`unknown symbol 'fileno'` and
similar). `-pgmcxx` alone is enough; final-link behavior is controlled via
the `-optl-...` flags above instead.

## Step 6 — Build and run

```
cd H:\hasquant
set TMP=H:\msys64\tmp
set TEMP=H:\msys64\tmp
H:\cabal.exe build
H:\cabal.exe test
```

Setting `TMP`/`TEMP` explicitly matters if you're driving this over SSH —
an SSH session's environment usually lacks both, and Clang then fails with
a confusing `unable to make temporary file: No such file or directory`
instead of anything mentioning `TMP`.

To run the test executable directly rather than through `cabal test`, ask
cabal where it landed instead of hardcoding the version-stamped path
(this needs `H:\ghc-9.10.3\bin` on `PATH`):

```
H:\cabal.exe list-bin hasquant_test
```

Plain execution of that `.exe` from an MSYS2 bash shell (including over
SSH) works fine.

**Whenever you change `-pgmcxx` or any other C++/link flag, run `cabal
clean` first.** Cabal's staleness tracking for `cxx-sources` does not
reliably detect that a flag change requires recompiling `cbits/*.cpp` — if
you skip this, you can end up linking a `.cpp` object that was compiled by
a *previous* setting (e.g. still MSYS2's `clang++`) against a QuantLib
built by GHC's `clang++`, producing the same ABI-mismatch symptoms as
skipping `-pgmcxx` in the first place, and it's very easy to misdiagnose
as a new bug rather than stale state.

## Setting up SSH access (optional, but makes iterating much faster)

If you'd rather drive the whole build from a normal terminal than a
Windows console window:

1. Install and start MSYS2's OpenSSH server:
   ```
   pacman -S openssh
   ssh-keygen -A
   mkpasswd -l > /etc/passwd
   mkgroup -l > /etc/group
   chmod 700 /etc/ssh
   chmod 600 /etc/ssh/ssh_host_*_key
   mkdir -p /var/empty
   ```
2. Pick a non-default port in `/etc/ssh/sshd_config` (e.g. `Port 2222`) if
   Windows' own built-in OpenSSH feature might already own port 22.
3. Test it first in the foreground (`/usr/sbin/sshd -d -p 2222`) so you
   can see errors immediately, then run it for real
   (`/usr/sbin/sshd -p 2222`) once it's clean.
4. Open the port in Windows Defender Firewall (inbound rule, TCP, your
   chosen port).
5. For key-based login: put your public key in
   `~/.ssh/authorized_keys` under the MSYS2 home directory, then
   `chmod 700 ~/.ssh && chmod 600 ~/.ssh/authorized_keys`. If key auth
   silently falls back to a password prompt, it's almost always NTFS
   permissions being too open for sshd's taste — from a Windows terminal:
   ```
   icacls "C:\msys64\home\<user>\.ssh" /inheritance:r /grant:r <user>:F
   icacls "C:\msys64\home\<user>\.ssh\authorized_keys" /inheritance:r /grant:r <user>:F
   ```
   Confirm by running `sshd -d` and watching for an explicit
   `Authentication refused: bad ownership or modes` line when you try to
   connect.

## Versions this was last verified against

GHC 9.10.3 (bundled Clang 14.0.6), cabal-install 3.16.1.0, MSYS2 with
Boost 1.91 and `ld.lld` 22.1.7, QuantLib 1.43.
