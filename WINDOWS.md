# Building hasquant on Windows

There are two independent C++ toolchains on a typical Windows Haskell dev
box, and they are not ABI-compatible:

- **GHC's bundled toolchain** (`H:\ghc-9.10.3\mingw\`) — Clang 14.0.6 with
  **libc++**. GHC's RTS was built with it.
- **MSYS2's toolchain** (`H:\msys64\mingw64\`) — GCC with **libstdc++**.
  This is where Boost lives, and Boost is the only thing QuantLib needs
  from it.

The recipe is therefore: build *everything* — QuantLib, the C++ shim, the
final executable — with **GHC's own `clang++`**, and expose **only Boost's
headers** from MSYS2. Exposing all of `H:\msys64\mingw64\include` instead
is what makes this hard: MSYS2's `math.h`/`stdlib.h` then shadow libc++'s
own versions and you get a long tail of `std::isnan` / `std::abs`
overload-resolution errors deep inside QuantLib. Step 1 avoids that in one
line.

## Paths used below

Search-and-replace these if your layout differs; nothing depends on the
drive letter. `cmd` wants backslashes, CMake and the `-optcxx`/`-optl`
flags want forward slashes — that's why both spellings appear.

| Path | What it is |
| --- | --- |
| `H:\ghc-9.10.3` | GHC install (bundles Clang + libc++ under `mingw\`) |
| `H:\msys64` | MSYS2 install (source of Boost headers) |
| `H:\boost-inc` | Boost-only include dir created in Step 1 |
| `H:\QuantLib-1.43` | QuantLib source checkout |
| `H:\QuantLib-ghc` | where Step 2 installs QuantLib |
| `H:\cabal.exe` | `cabal-install` binary |
| `H:\hasquant` | this repo's checkout |

## Prerequisites

- GHC 9.10.3 and `cabal.exe`. You do **not** need a separate C++ compiler —
  GHC bundles a complete Clang/libc++ toolchain.
- MSYS2 with:
  ```
  pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
  ```
- QuantLib 1.43 source at `H:\QuantLib-1.43`.

## Step 1 — Expose Boost, and nothing else, from MSYS2

From a plain (non-elevated) `cmd`:

```
mkdir H:\boost-inc
mklink /J H:\boost-inc\boost H:\msys64\mingw64\include\boost
```

Now `-isystem H:/boost-inc` gives the compiler Boost without dragging in
MSYS2's C headers.

## Step 2 — Build and install QuantLib with GHC's clang++

```
mkdir H:\QuantLib-1.43\build
cd H:\QuantLib-1.43\build
cmake -G Ninja ^
  -DCMAKE_CXX_COMPILER=H:/ghc-9.10.3/mingw/bin/clang++.exe ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_INSTALL_PREFIX=H:/QuantLib-ghc ^
  -DBoost_NO_BOOST_CMAKE=ON -DBoost_INCLUDE_DIR=H:/boost-inc ^
  -DCMAKE_CXX_FLAGS="-include vector" ^
  -DQL_BUILD_EXAMPLES=OFF -DQL_BUILD_TEST_SUITE=OFF ^
  ..
ninja
ninja install
```

Two of those need a word:

- `Boost_NO_BOOST_CMAKE=ON` — without it CMake finds MSYS2's
  `BoostConfig.cmake`, which points back at the full
  `H:/msys64/mingw64/include` and undoes Step 1.
- `-include vector` — `ql/time/calendars/islamicholidays.cpp` uses
  `std::vector` without including it. libstdc++ pulls the definition in
  transitively; libc++'s `<iosfwd>` only forward-declares it. One flag is
  cheaper than patching the source.

This is a full ~976-translation-unit build; expect it to take a while. It
installs headers to `H:\QuantLib-ghc\include` and
`H:\QuantLib-ghc\lib\libQuantLib.a`. No QuantLib sources need patching.

If `ninja` dies with `error opening '….obj.d': Permission denied` or
`remove(….obj.d): Access is denied`, that's on-access virus scanning, not
your build. Just re-run `ninja` — it resumes where it stopped.

## Step 3 — Point hasquant at that QuantLib

Create `cabal.project.local` in the repo root (`ghc-options:` is one long
line):

```
ignore-project: False
tests: True

package hasquant
  extra-include-dirs: H:/QuantLib-ghc/include
  extra-lib-dirs: H:/QuantLib-ghc/lib
  ghc-options: -pgmcxx H:/ghc-9.10.3/mingw/bin/clang++ -optl H:/ghc-9.10.3/mingw/lib/libc++.a -optl H:/ghc-9.10.3/mingw/lib/libc++abi.a -optl H:/ghc-9.10.3/mingw/lib/libunwind.a -optcxx-isystem -optcxxH:/boost-inc
```

## Step 4 — Build and run

```
cd H:\hasquant
set TMP=H:\msys64\tmp
set TEMP=H:\msys64\tmp
H:\cabal.exe build all
H:\cabal.exe test
```

`TMP`/`TEMP` must be set when driving this over SSH — an SSH session has
neither, and Clang then fails with `unable to make temporary file` rather
than anything mentioning `TMP`.

To locate the test binary instead of running it through `cabal test` (needs
`H:\ghc-9.10.3\bin` on `PATH`):

```
H:\cabal.exe list-bin hasquant_test
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
- **`-optcxx-isystem -optcxxH:/boost-inc`** — the shim's `#include <ql/…>`
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

## Setting up SSH access (optional)

Driving the build from a real terminal beats a Windows console window.

1. In MSYS2: `pacman -S openssh`, then
   ```
   ssh-keygen -A
   mkpasswd -l > /etc/passwd
   mkgroup  -l > /etc/group
   chmod 700 /etc/ssh
   chmod 600 /etc/ssh/ssh_host_*_key
   mkdir -p /var/empty
   ```
2. Pick a non-default port in `/etc/ssh/sshd_config` (e.g. `Port 2222`) —
   Windows' own OpenSSH may already own 22.
3. Test in the foreground (`/usr/sbin/sshd -d -p 2222`), then run it for
   real (`/usr/sbin/sshd -p 2222`).
4. Open the port in Windows Defender Firewall (inbound, TCP).
5. Put your key in `~/.ssh/authorized_keys`, then
   `chmod 700 ~/.ssh && chmod 600 ~/.ssh/authorized_keys`. If key auth
   silently falls back to a password prompt, NTFS permissions are too open
   for sshd; from a Windows terminal:
   ```
   icacls "H:\msys64\home\<user>\.ssh" /inheritance:r /grant:r <user>:F
   icacls "H:\msys64\home\<user>\.ssh\authorized_keys" /inheritance:r /grant:r <user>:F
   ```
   `sshd -d` will say `Authentication refused: bad ownership or modes`.

## Versions this was last verified against

GHC 9.10.3 (bundled Clang 14.0.6 and `ld.lld` 14.0.6), cabal-install
3.16.1.0, CMake 4.3.3, Ninja, MSYS2 with Boost 1.91, QuantLib 1.43 — clean
build of all three stages, 84/84 tests passing.
