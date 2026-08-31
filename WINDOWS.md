# Building hasquant on Windows

GHC and MSYS2 C++ toolchains are ABI-incompatible:

- **GHC's bundled toolchain** (`h:\ghc-9.10.3\mingw\`) — Clang 14.0.6 with
  **libc++**. GHC's RTS was built with it.
- **MSYS2's toolchain** (`h:\msys64\mingw64\`) — GCC with **libstdc++**;
  use only its Boost headers.

Build QuantLib, the shim, and the executable with **GHC's `clang++`**.

Install `cmake`, `ninja`, and `boost`, or expose only MSYS2's Boost headers. Do not add all of `h:\msys64\mingw64\include`: its `math.h` and `stdlib.h` shadow libc++ headers and break QuantLib overload resolution.

## Paths used below

Replace these paths for your setup. `cmd` uses backslashes; CMake and `-optcxx`/`-optl` use forward slashes.

| Path               | What it is                                          |
|--------------------|-----------------------------------------------------|
| `h:/ghc-9.10.3`    | GHC install (bundles Clang + libc++ under `mingw\`) |
| `h:/boost-inc`     | Boost-only include dir created in Step 1            |
| `h:/QuantLib-ghc`  | where Step 2 installs QuantLib                      |

## Prerequisites

- GHC 9.10.3 and `cabal.exe`; GHC includes the required Clang/libc++ toolchain. GHC 9.14.1 was also tested.
- QuantLib 1.43 source at `h:\QuantLib-1.43`.

### If you have MSYS2 installed

- Install extra packages:
  ```
  pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
  ```

### Without MSYS

Download and extract cmake (e.g., `https://github.com/Kitware/CMake/releases/download/v4.4.2/cmake-4.4.2-windows-x86_64.zip`), ninja (e.g., `https://github.com/ninja-build/ninja/releases/download/v1.13.2/ninja-win.zip`), and boost (e.g., `https://archives.boost.io/release/1.91.0/source/boost_1_91_0.7z`)

## Step 1 — Expose Boost

### From MSYS2

In a non-elevated `cmd`:

```
mkdir h:\boost-inc
mklink /J h:\boost-inc\boost h:\msys64\mingw64\include\boost
```

### Without MSYS2

Ensure `h:\boost-inc` contains `boost\version.hpp`.

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

- `Boost_NO_BOOST_CMAKE=ON` prevents CMake from restoring MSYS2's full include directory.
- `-include vector` supplies a missing direct include in QuantLib's Islamic-holiday source; libc++ does not provide it transitively.

The ~976-translation-unit build installs headers to `h:\QuantLib-ghc\include` and the library to `h:\QuantLib-ghc\lib\libQuantLib.a`; it needs no source patches.

If `ninja` reports access denied for `.obj.d`, on-access virus scanning is usually responsible; rerun it to resume.

## Step 3 — Point hasquant at that QuantLib

Copy `cabal.project.local.WINDOWS` to `cabal.project.local` and adjust its paths.

## Step 4 — Build and run

```
cd h:\hasquant
h:\cabal.exe build all
h:\cabal.exe test
```

**After changing a C++ or link flag, run `cabal clean`.** Cabal does not track `cxx-sources` flag changes and can link stale objects.

---

## Flag rationale

- **`-pgmcxx …/clang++`** compiles `cbits/*.cpp` with QuantLib's compiler, avoiding ABI collisions.
- **`-optl …/libc++.a …/libc++abi.a …/libunwind.a`** — GHC's static C++
  runtime. Passed as raw paths, not `-lc++`, so the linker can't pick the
  *dynamic* `libc++.dll.a` and end up with
  `multiple definition of std::runtime_error::what()`. Without these you
  get undefined `std::__1::…` symbols from both the shim and
  `libQuantLib.a`.
- **`-optcxx-isystem -optcxxh:/boost-inc`** — the shim's `#include <ql/…>`
  transitively needs Boost.
- GHC already configures `lld` and its MinGW runtime; do not add `--ld-path`, `-lmingwex`, or `-lmingw32`.
- **Do not set `-pgml`.** GHC's Template Haskell bytecode linker then
  probes MSYS2's library dirs and chokes on `libmingwex.a`
  (`unknown symbol 'fileno'`).
- `package.yaml` links `stdc++` on non-Windows only. Don't remove that
  guard — linking MSYS2's `libstdc++` alongside GHC's `libc++` produces
  `duplicate symbol: std::__1::basic_ostream<…>::operator<<(int)` and
  hundreds like it.

## Versions this was last verified against

GHC 9.10.3 (bundled Clang 14.0.6 and `ld.lld` 14.0.6) and GHC 9.14.1, cabal-install
3.16.1.0, CMake 4.3.3, Ninja, MSYS2 with Boost 1.91, QuantLib 1.43 — clean build of all three stages
