#!/usr/bin/env bash
# Compiles and runs every remaining test/smoke/*.hs script via the run-hasquant skill's
# driver.sh (build lib:hasquant once, then compile+run each script standalone), reporting
# pass/fail per script. Skips SmokeCheck.hs (shared assertion helpers, not a runnable check
# on its own).
#
# Usage: test/smoke/run-all.sh [pattern]
#   pattern (optional): only run scripts whose basename matches this glob, e.g. 'Check*'.
#
# Run from the repo root.
set -uo pipefail

cd "$(git rev-parse --show-toplevel)"

DRIVER=.claude/skills/run-hasquant/driver.sh
PATTERN="${1:-*}"

echo "==> building lib:hasquant once" >&2
"$DRIVER" --build-only

failed=()
passed=0

for script in test/smoke/*.hs; do
  name="$(basename "${script%.hs}")"
  [ "$name" = "SmokeCheck" ] && continue
  # shellcheck disable=SC2053
  [[ "$name" == $PATTERN ]] || continue

  echo "==> $script"
  if "$DRIVER" "$script"; then
    passed=$((passed + 1))
  else
    failed+=("$script")
  fi
done

echo
echo "==> $passed passed, ${#failed[@]} failed"
if [ "${#failed[@]}" -gt 0 ]; then
  printf '    FAILED: %s\n' "${failed[@]}"
  exit 1
fi
