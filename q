#!/bin/sh
# Single launcher for hasquant builds, tests and Docker gates.
#   ./q              fzf menu; press an action's key (q/esc quits)
#   ./q KEY [ARGS]   run an action directly, ARGS go to cabal
SELF=$(cd "$(dirname "$0")" && pwd)/$(basename "$0")
cd "$(git rev-parse --show-toplevel)" || exit 1

TABLE='b|build all (lib + tests)
t|build + test, skip LONG
a|build + test all, detailed output
T|build + test with trackAllocations (rm build/cbits after flag changes)
e|run example
E|run example with trackAllocations
r|repl lib:hasquant
g|build + test with GHC 9.12.4
f|final gate: flagged build via quiet-build.py
m|make: cbits compile check, Homebrew QuantLib
M|make: cbits compile check, own QuantLib (QL_OWN)
h|make: cbits compile check, QuantLib head (QL_HEAD)
l|hlint .
p|pick project file, build + test
c|clean dist-newstyle
d|docker: build image
8|docker: GHC 8.10 gate
s|docker: shell'

# QuantLib installs for the make actions; override via the environment.
QL_BREW=${QL_BREW:-/opt/homebrew/opt/quantlib}
QL_OWN=${QL_OWN:-$HOME/opt/quantlib-1.43}
QL_HEAD=${QL_HEAD:-$HOME/Src/QuantLib}

# Per-checkout object dir; holds a header-only cmake configure for ql/config.hpp.
head_dir() { echo "cobj/head-$(basename "$QL_HEAD")"; }
head_cflags() {
  cfg=$(head_dir)/cmake; mkdir -p "$(head_dir)"
  [ -f "$cfg/ql/config.hpp" ] ||
    cmake -S "$QL_HEAD" -B "$cfg" -DCMAKE_BUILD_TYPE=Release >"$cfg.log" 2>&1 ||
    { echo "cmake configure failed, see $cfg.log" >&2; return 1; }
  echo "-I$cfg -I$QL_HEAD"
}

pick_project() {
  ls cabal.project.lts-* cabal.project.unpinned 2>/dev/null | fzf --prompt='project file> '
}

run() {
  key=$1; shift
  case $key in
    b) cabal build all --enable-tests "$@" ;;
    t) cabal build all --enable-tests "$@" &&
       cabal run hasquant_test --enable-tests "$@" -- --skip=LONG ;;
    a) cabal build all --enable-tests "$@" &&
       cabal test all --enable-tests --test-show-details=always "$@" ;;
    T) cabal build all --enable-tests -f trackAllocations "$@" &&
       cabal test all --enable-tests -f trackAllocations --test-options=--skip=LONG "$@" ;;
    e) cabal run hasquant_example -f buildExample "$@" ;;
    E) cabal run hasquant_example -f buildExample -f trackAllocations "$@" ;;
    r) cabal repl lib:hasquant "$@" ;;
    g) cabal build all -v2 -w ghc-9.12.4 --enable-tests -f buildExample -f buildSofrXva "$@" &&
       cabal run -w ghc-9.12.4 hasquant_test --enable-tests "$@" -- --skip=LONG ;;
    f) tools/quiet-build.py cabal build all --enable-tests -f buildExample -f buildSofrXva "$@" ;;
    m) make OBJDIR=cobj/brew QUANTLIB_CONFIG="$QL_BREW/bin/quantlib-config" "$@" ;;
    M) make OBJDIR=cobj/own QUANTLIB_CONFIG="$QL_OWN/bin/quantlib-config" "$@" ;;
    h) fl=$(head_cflags) || return 1
       make OBJDIR="$(head_dir)" QL_CFLAGS="$fl" "$@" ;;
    l) hlint . "$@" ;;
    p) pf=$(pick_project) || return 1
       [ -n "$pf" ] || return 1
       cabal build all --project-file="$pf" --enable-tests "$@" &&
       cabal test all --project-file="$pf" --enable-tests --test-options=--skip=LONG "$@" ;;
    c) printf 'rm -rf dist-newstyle? [y/N] '
       read -r ans
       [ "$ans" = y ] && { echo "Cleaning up"; rm -rf dist-newstyle; } ;;
    d) UID=$(id -u) GID=$(id -g) docker compose build "$@" ;;
    8) docker compose run --rm hasquant sh -c 'ghcup install ghc 8.10.6 && cabal update && cabal build all --project-file=cabal.project.lts-18.8 --enable-tests -f buildExample -f buildSofrXva && cabal test all --project-file=cabal.project.lts-18.8 --enable-tests -f buildExample -f buildSofrXva' ;;
    s) docker compose run --rm -t hasquant bash ;;
    *) echo "unknown action: $key" >&2; return 2 ;;
  esac
}

case ${1:-} in
  --menu-run)  # invoked by fzf: run, then pause so output stays readable
    # fzf's become leaves stdin non-blocking; reopen the terminal.
    exec </dev/tty
    run "$2"; rc=$?
    printf '\n[exit %s] press enter to return ' "$rc"
    read -r _
    exec "$SELF"
    ;;
  '')
    if command -v fzf >/dev/null 2>&1; then
      binds=$(printf '%s\n' "$TABLE" | while IFS='|' read -r k _; do
        printf '%s:become(sh %s --menu-run %s),' "$k" "$SELF" "$k"
      done)
      printf '%s\n' "$TABLE" |
        while IFS='|' read -r k d; do printf '\033[1;33m%s\033[0m   %s\n' "$k" "$d"; done |
        fzf --ansi --disabled --no-sort --reverse --header='press key to run, q/esc quits' \
        --bind "${binds}q:abort" --bind 'enter:become(sh '"$SELF"' --menu-run {1})'
      exit 0
    fi
    printf '%s\n' "$TABLE" | tr '|' ' '
    printf 'key> '; read -r k
    [ -n "$k" ] && run "$k"
    ;;
  *)
    k=$1; shift
    run "$k" "$@"
    ;;
esac
