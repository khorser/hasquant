#!/usr/bin/env python3
"""
One-off sync of tools/ql-methods-1.43.txt status markers against the actual
cbits/ C shim functions.

For each `|status|header|decl;` line, look for a plausibly-matching cbits/
shim function (by hasquant's ql<Class><Method>[N] naming convention) and,
if found, compare arg counts (accounting for the shim's implicit self
pointer and trailing `char **e`):
  - shim strictly fewer args than the QL declaration -> |u| (needs update)
  - shim arg count matches                            -> |v|
  - shim found but comparison is ambiguous             -> |?|
  - no shim found, or current status is `x`            -> line untouched

Not bulletproof by design -- this is a one-off initial sync; further
curation is expected to happen by hand afterwards.

Usage:
    python3 tools/sync_ql_methods_status.py [path-to-ql-methods-file]
"""
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
CBITS_DIR = REPO_ROOT / "cbits"
DEFAULT_TARGET = REPO_ROOT / "tools" / "ql-methods-1.43.txt"

# Same declaration regex reconcile_signatures.py already validated against
# this exact file's syntax.
DECL_RE = re.compile(
    r'(?:([\w]+)::)?(~?[\w]+|operator\S*)\s*(?:<[^>]*>)?\s*\((.*)\)\s*(const)?\s*;?\s*$'
)


def split_top_level_commas(s):
    parts = []
    depth = 0
    cur = []
    for ch in s:
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    parts.append("".join(cur))
    return parts


def parse_decl(decl):
    """(class-or-None, member, arg-count) or (None, None, None)."""
    m = DECL_RE.search(decl)
    if not m:
        return None, None, None
    cls, member, params = m.group(1), m.group(2), m.group(3)
    params = params.strip()
    if not params:
        return cls, member, 0
    return cls, member, len(split_top_level_commas(params))


# ---------------------------------------------------------------------------
# cbits/*.h shim signature extraction
# ---------------------------------------------------------------------------

FUNC_NAME_RE = re.compile(r"\bql[A-Za-z0-9_]*\b")


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    return text


def extract_shim_signatures(cbits_dir):
    """{full_shim_name: argc} scanning every ql<Whatever>(...) call-shaped
    token in cbits/*.h, balance-matching parens to find the param list and
    dropping a trailing `char **e`."""
    sigs = {}
    for path in sorted(cbits_dir.glob("*.h")):
        text = strip_comments(path.read_text(errors="replace"))
        for m in FUNC_NAME_RE.finditer(text):
            name = m.group(0)
            j = m.end()
            while j < len(text) and text[j].isspace():
                j += 1
            if j >= len(text) or text[j] != "(":
                continue
            start = j
            depth = 0
            k = start
            while k < len(text):
                if text[k] == "(":
                    depth += 1
                elif text[k] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                k += 1
            else:
                continue
            params_str = text[start + 1 : k].strip()
            if not params_str:
                argc = 0
            else:
                params = [p.strip() for p in split_top_level_commas(params_str)]
                if params and re.fullmatch(r"char\s*\*\*\s*\w+", params[-1]):
                    params = params[:-1]
                argc = len(params)
            # keep the max if a name is (re-)declared more than once --
            # doesn't matter which single declaration wins for our purposes
            if name not in sigs or argc > sigs[name]:
                sigs[name] = argc
    return sigs


TRAILING_DIGITS_RE = re.compile(r"\d+$")


def build_base_index(sigs):
    """{base_name (trailing digits stripped): [argc, ...]}"""
    index = {}
    for name, argc in sigs.items():
        base = TRAILING_DIGITS_RE.sub("", name)
        index.setdefault(base, []).append(argc)
    return index


# ---------------------------------------------------------------------------
# classification
# ---------------------------------------------------------------------------

def is_noise(member):
    return member is None or member.startswith("~") or "operator" in member


def candidate_base_and_offset(cls, member, decl):
    is_static = decl.lstrip().startswith("static ")
    if cls is not None:
        is_ctor = member == cls
        if is_ctor:
            return "ql" + cls, 0
        method = member[0].upper() + member[1:]
        return "ql" + cls + method, 0 if is_static else 1
    # free function, no Class:: prefix
    method = member[0].upper() + member[1:]
    return "ql" + method, 0


def classify(cls, member, argc, decl, base_index):
    if is_noise(member) or argc is None:
        return None
    base, self_offset = candidate_base_and_offset(cls, member, decl)
    raw_argcs = base_index.get(base)
    if not raw_argcs:
        return None
    adjusted = [c - self_offset for c in raw_argcs if c - self_offset >= 0]
    if not adjusted:
        return "?"
    if argc in adjusted:
        return "v"
    if any(a < argc for a in adjusted):
        return "u"
    return "?"


# ---------------------------------------------------------------------------

def main():
    target = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_TARGET

    sigs = extract_shim_signatures(CBITS_DIR)
    base_index = build_base_index(sigs)

    lines = target.read_text().splitlines(keepends=True)
    out = []
    counts = {"v": 0, "u": 0, "?": 0, "unchanged_same": 0, "untouched": 0}

    for line in lines:
        stripped = line.rstrip("\n")
        parts = stripped.split("|", 3)
        if len(parts) < 4:
            out.append(line)
            counts["untouched"] += 1
            continue
        _, status, header, decl = parts
        if status == "x":
            out.append(line)
            counts["untouched"] += 1
            continue

        cls, member, argc = parse_decl(decl)
        new_status = classify(cls, member, argc, decl, base_index)
        if new_status is None:
            out.append(line)
            counts["untouched"] += 1
            continue

        if new_status == status:
            counts["unchanged_same"] += 1
        else:
            counts[new_status] += 1
        newline = "\n" if line.endswith("\n") else ""
        out.append(f"|{new_status}|{header}|{decl}{newline}")

    target.write_text("".join(out))

    print(
        f"assigned: {counts['v']} new v, {counts['u']} new u, {counts['?']} new ? "
        f"(+{counts['unchanged_same']} already matched their new status); "
        f"{counts['untouched']} lines untouched"
    )


if __name__ == "__main__":
    main()
