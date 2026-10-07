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
m|make: cbits compile check
l|hlint .
p|pick project file, build + test
c|clean dist-newstyle
d|docker: build image
8|docker: GHC 8.10 gate
s|docker: shell'

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
    m) make EXTRA="${EXTRA:--std=c++17 -isystem/opt/homebrew/opt/boost/include}" "$@" ;;
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
      printf '%s\n' "$TABLE" | fzf --disabled --no-sort --reverse \
        --delimiter='|' --with-nth=1,2 --header='press key to run, q/esc quits' \
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
