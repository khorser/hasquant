#!/usr/bin/env bash
# Drives hasquant the way this repo actually verifies bindings: compile a
# standalone smoke/*.hs program against the built library and run it.
# See ../../CLAUDE.md's "Stale builds, and keeping smoke/ current" section
# for why this exists (a compiled `stack build` is not proof that generated
# code, e.g. from an edited cbits/ header or a new enum case, actually
# changed) -- this script is the harness for that check.
#
# Usage:
#   .claude/skills/run-hasquant/driver.sh <smoke/Foo.hs> [-- extra ghc args]
#   .claude/skills/run-hasquant/driver.sh --build-only   # just (re)build + register lib:hasquant
#
# Run from the repo root (paths below are relative to it).
set -euo pipefail

cd "$(git rev-parse --show-toplevel)"

echo "==> cabal build lib:hasquant" >&2
cabal build lib:hasquant

echo "==> cabal install --lib hasquant (registers a global GHC environment file, not in-repo)" >&2
cabal install --lib hasquant --force-reinstalls >/dev/null

if [ "${1:-}" = "--build-only" ]; then
  echo "==> lib:hasquant built and registered" >&2
  exit 0
fi

SCRIPT="${1:?usage: driver.sh <smoke/Foo.hs> [-- extra ghc args]}"
shift
[ "${1:-}" = "--" ] && shift

NAME="$(basename "${SCRIPT%.hs}")"
OUT="/tmp/hasquant-smoke-${NAME}"
BUILD_DIR="${OUT}_build"

echo "==> compiling ${SCRIPT}" >&2
cabal exec -- ghc -ismoke -package hasquant "$SCRIPT" -o "$OUT" -outputdir "$BUILD_DIR" "$@"

echo "==> running ${OUT}" >&2
"$OUT"
