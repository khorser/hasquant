# Building hasquant on Windows

There are two independent C++ toolchains on a typical Windows Haskell dev
box, and they are not ABI-compatible:

- **GHC's bundled toolchain** (`h:\ghc-9.10.3\mingw\`) — Clang 14.0.6 with
  **libc++**. GHC's RTS was built with it.
- **MSYS2's toolchain** (`h:\msys64\mingw64\`) — GCC with **libstdc++**.
  This is where Boost lives, and Boost is the only thing QuantLib needs
  from it.

The recipe is therefore: build *everything* — QuantLib, the C++ shim, the
final executable — with **GHC's own `clang++`**.

There are two equally working approaches: install `cmake`, `ninja`, and `boost`
OR use MSYS2 and expose **only Boost's headers** from it. Exposing all of `h:\msys64\mingw64\include` causes
multiple issues: MSYS2's `math.h`/`stdlib.h` shadow libc++'s
own versions and you get a long tail of `std::isnan` / `std::abs`
overload-resolution errors deep inside QuantLib. Step 1 avoids that in one line.

## Paths used below

Search-and-replace these if your layout differs; nothing depends on the
drive letter. `cmd` wants backslashes, CMake and the `-optcxx`/`-optl`
flags want forward slashes — that's why both spellings appear.

| Path               | What it is                                          |
|--------------------|-----------------------------------------------------|
| `h:/ghc-9.10.3`    | GHC install (bundles Clang + libc++ under `mingw\`) |
| `h:/boost-inc`     | Boost-only include dir created in Step 1            |
| `h:/QuantLib-ghc`  | where Step 2 installs QuantLib                      |

## Prerequisites

- GHC 9.10.3 and `cabal.exe`. You do **not** need a separate C++ compiler —
  GHC bundles a complete Clang/libc++ toolchain.
- QuantLib 1.43 source at `h:\QuantLib-1.43` (update paths in commands below if it's in another directory)

### If you have MSYS2 installed

- Install extra packages:
  ```
  pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
  ```

### Without MSYS

Download and extract cmake (e.g., `https://github.com/Kitware/CMake/releases/download/v4.4.2/cmake-4.4.2-windows-x86_64.zip`), ninja (e.g., `https://github.com/ninja-build/ninja/releases/download/v1.13.2/ninja-win.zip`), and boost (e.g., `https://archives.boost.io/release/1.91.0/source/boost_1_91_0.7z`)

## Step 1 — Expose Boost

### From MSYS2

From a plain (non-elevated) `cmd`:

```
mkdir h:\boost-inc
mklink /J h:\boost-inc\boost h:\msys64\mingw64\include\boost
```

### Without MSYS2

Make sure `h:\boost-inc` (or whatever directory you decided to use) contains `boost` subdirectory with `version.hpp` inside.

## Step 2 — Build and install QuantLib with GHC's clang++

### MSYS2

In `MSYS2 MINGW64`: 

```
cd h:/QuantLib-1.43/build
cmake -G Ninja \
  -DCMAKE_CXX_COMPILER=h:/ghc-9.10.3/mingw/bin/clang++.exe \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=h:/QuantLib-ghc \
  -DBoost_NO_BOOST_CMAKE=ON -DBoost_INCLUDE_DIR=h:/boost-inc \
  -DCMAKE_CXX_FLAGS="-include vector" \
  -DQL_BUILD_EXAMPLES=OFF -DQL_BUILD_TEST_SUITE=OFF \
  ..
ninja
ninja install
```

### Without MSYS2

```
cd /c h:\QuantLib-1.43\build

h:\cmake-4.4.2-windows-x86_64\bin\cmake.exe -G Ninja ^
  -DCMAKE_CXX_COMPILER=h:/ghc-9.10.3/mingw/bin/clang++.exe ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_INSTALL_PREFIX=h:/QuantLib-ghc ^
  -DBoost-NO_BOOST_CMAKE=ON ^
  -DBoost_INCLUDE_DIR=h:/boost_1_91_0 ^
  -DCMAKE_CXX_FLAGS="-include vector" ^
  -DQL_BUILD_EXAMPLES=OFF ^
  -DQL_BUILD_TEST_SUITE=OFF ^
  -DCMAKE_MAKE_PROGRAM=h:/ninja.exe ^
  ..
h:\ninja build
h:\ninja install
```

### Notes

- `Boost_NO_BOOST_CMAKE=ON` — without it CMake finds MSYS2's
  `BoostConfig.cmake`, which points back at the full
  `h:/msys64/mingw64/include` and undoes Step 1.
- `-include vector` — `ql/time/calendars/islamicholidays.cpp` uses
  `std::vector` without including it. libstdc++ pulls the definition in
  transitively; libc++'s `<iosfwd>` only forward-declares it. One flag is
  cheaper than patching the source.

This is a full ~976-translation-unit build; expect it to take a while. It
installs headers to `h:\QuantLib-ghc\include` and
`h:\QuantLib-ghc\lib\libQuantLib.a`. No QuantLib sources need patching.

If `ninja` dies with `error opening '….obj.d': Permission denied` or
`remove(….obj.d): Access is denied`, that's on-access virus scanning, not
your build. Just re-run `ninja` — it resumes where it stopped.

## Step 3 — Point hasquant at that QuantLib

In the hasquant root copy `cabal.project.local.WINDOWS` to `cabal.project.local` and adjust paths in it according to your setup.

## Step 4 — Build and run

```
cd h:\hasquant
h:\cabal.exe build all
h:\cabal.exe test
```

**After changing any C++ or link flag, run `cabal clean` first.** Cabal's
staleness tracking for `cxx-sources` does not notice flag changes, so you
can silently link `.cpp` objects compiled under the previous settings.

---

## Why the flags in Step 3 are what they are

- **`-pgmcxx …/clang++`** — compiles `cbits/*.cpp` with the same compiler
  QuantLib was built with. Getting this wrong gives
  `duplicate section … has different size` at link time: two C++ ABIs
  colliding.
- **`-optl …/libc++.a …/libc++abi.a …/libunwind.a`** — GHC's static C++
  runtime. Passed as raw paths, not `-lc++`, so the linker can't pick the
  *dynamic* `libc++.dll.a` and end up with
  `multiple definition of std::runtime_error::what()`. Without these you
  get undefined `std::__1::…` symbols from both the shim and
  `libQuantLib.a`.
- **`-optcxx-isystem -optcxxh:/boost-inc`** — the shim's `#include <ql/…>`
  transitively needs Boost.
- **Nothing else is needed.** GHC 9.10.3 already links with
  `-fuse-ld=lld` and already puts its own mingw runtime on the library
  path, so no `--ld-path`, no `-lmingwex`/`-lmingw32`.
- **Do not set `-pgml`.** GHC's Template Haskell bytecode linker then
  probes MSYS2's library dirs and chokes on `libmingwex.a`
  (`unknown symbol 'fileno'`).
- `package.yaml` links `stdc++` on non-Windows only. Don't remove that
  guard — linking MSYS2's `libstdc++` alongside GHC's `libc++` produces
  `duplicate symbol: std::__1::basic_ostream<…>::operator<<(int)` and
  hundreds like it.

## Versions this was last verified against

GHC 9.10.3 (bundled Clang 14.0.6 and `ld.lld` 14.0.6), cabal-install
3.16.1.0, CMake 4.3.3, Ninja, MSYS2 with Boost 1.91, QuantLib 1.43 — clean
build of all three stages, 84/84 tests passing.
