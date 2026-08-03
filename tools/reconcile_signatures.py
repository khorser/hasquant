#!/usr/bin/env python3
"""
Reconcile the old, hand-curated QuantLib method-signature dump against a
fresh one produced by an improved extractor, carrying forward the curated
status (blank/x/v) onto whatever survives.

Old dump (tools/ql-methods-1.43.txt): 4 pipe-delimited fields,
`|status|header|declaration;` where status is blank (candidate), x
(permanently excluded -- destructor/operator/template noise), or v
(already-handled value-type singleton constructor).

New dump (tools/ql-methods-new.txt): 2 pipe-delimited fields,
`header|declaration` -- no status field, and header lacks the old dump's
leading "ql/" prefix. Produced by a rewritten dump_signatures.py that scans
public members only, skips [[deprecated]], de-duplicates identical-signature
overrides of an ancestor method (keeping only the ancestor's copy), no
longer emits destructors or function templates at all, and -- unlike the
version that produced the old dump -- captures the `static` keyword and
each parameter's C++ default value. Declaration-text equality is therefore
compared after normalize_decl() strips those two (the old dump never had
them), while the *printed* text always keeps whatever richer form is
available, so an otherwise-unchanged method gets its new dump's static/
default info folded in for free.

Algorithm per old-dump line, in order:
  1. Declaration matches in new after normalize_decl() -> print using the
     new declaration's (possibly richer) text, keeping the old status
     (stdout).
  2. Destructor or operator -> drop silently (never in new by construction /
     not sensibly name-matchable -- operator names collide across unrelated
     types).
  3. Same class+member, new arg count strictly greater than old, searched
     only among new entries that are not themselves an exact match to some
     *other* old line -> adjust status (v->u; x/blank unchanged), print with
     the new declaration (stdout).
  4. Same (member name, arg count) exists in new under a different class ->
     drop silently (superseded by override-dedup; the surviving copy was
     already handled in step 1).
  5. Otherwise -> print old line unchanged to stderr (genuinely gone).

New-dump lines never consumed above are printed to stdout with an empty
status (brand new candidates) -- except destructors/operators, which are
excluded here too (never bindable via a named C shim).

Usage:
    python3 tools/reconcile_signatures.py tools/ql-methods-1.43.txt tools/ql-methods-new.txt
"""
import re
import sys

DECL_RE = re.compile(
    r'(?:([\w]+)::)?(~?[\w]+|operator\S*)\s*(?:<[^>]*>)?\s*\((.*)\)\s*(const)?\s*;?\s*$'
)


def parse_old(path):
    out = []
    for line in open(path):
        line = line.rstrip("\n")
        if not line.strip():
            continue
        parts = line.split("|", 3)
        if len(parts) < 4:
            continue
        _, status, header, decl = parts
        out.append((status, header, decl))
    return out


def parse_new(path):
    out = []
    for line in open(path):
        line = line.rstrip("\n")
        if not line.strip():
            continue
        parts = line.split("|", 1)
        if len(parts) < 2:
            continue
        header, decl = parts
        out.append((header, decl))
    return out


DECL_SPLIT_RE = re.compile(r'^(.*?)\((.*)\)(\s*const)?\s*;?\s*$')


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


def strip_param_default(param):
    depth = 0
    for i, ch in enumerate(param):
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        elif ch == "=" and depth == 0:
            return param[:i].rstrip()
    return param


def normalize_decl(decl):
    """Declaration text with the `static` keyword and per-parameter defaults
    stripped, so an old dump (which never had either) can still match an
    otherwise-unchanged entry in a new dump that now captures both."""
    d = decl.strip()
    if d.startswith("static "):
        d = d[len("static "):]
    m = DECL_SPLIT_RE.match(d)
    if not m:
        return d
    prefix, params_str, const = m.group(1), m.group(2).strip(), m.group(3) or ""
    if not params_str:
        norm_params = ""
    else:
        norm_params = ", ".join(
            strip_param_default(p).strip() for p in split_top_level_commas(params_str)
        )
    return f"{prefix}({norm_params}){const};"


def parse_decl(decl):
    """(class-or-None, member, arg-count) or (None, None, None) if unparseable."""
    m = DECL_RE.search(decl)
    if not m:
        return None, None, None
    cls, member, params = m.group(1), m.group(2), m.group(3)
    params = params.strip()
    if not params:
        return cls, member, 0
    depth = 0
    argc = 1
    for ch in params:
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        elif ch == "," and depth == 0:
            argc += 1
    return cls, member, argc


def is_noise(member):
    return member is None or member.startswith("~") or "operator" in member


def normalize_header(header):
    return header if header.startswith("ql/") else "ql/" + header


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <old-dump> <new-dump>", file=sys.stderr)
        sys.exit(1)
    old = parse_old(sys.argv[1])
    new = parse_new(sys.argv[2])

    old_decl_norm_set = set(normalize_decl(d) for _, _, d in old)
    new_norm_to_raw = {}
    for header, decl in new:
        new_norm_to_raw.setdefault(normalize_decl(decl), (header, decl))

    new_by_classmember = {}
    new_by_memberargc = {}
    for header, decl in new:
        cls, member, argc = parse_decl(decl)
        if member is None:
            continue
        new_by_classmember.setdefault((cls, member), []).append((argc, header, decl))
        new_by_memberargc.setdefault((member, argc), set()).add(cls)

    stdout_lines = []
    stderr_lines = []
    consumed_new = set()

    for status, header, decl in old:
        match = new_norm_to_raw.get(normalize_decl(decl))
        if match is not None:
            _, new_decl = match
            # keep the OLD header, not the new one: multiple distinct old
            # entries can share the exact same (often unqualified, no
            # `Class::` prefix -- a clang quirk with out-of-line template
            # method definitions) declaration text, so matching purely on
            # normalized text and using the new dump's header would collapse
            # them into one arbitrarily-chosen line and silently drop the
            # rest. The old header, being unique per old-dump line, doesn't
            # have this problem.
            stdout_lines.append(f"|{status}|{header}|{new_decl}")
            continue

        cls, member, argc = parse_decl(decl)
        if is_noise(member):
            continue

        candidates = [
            c
            for c in new_by_classmember.get((cls, member), [])
            if c[0] is not None and argc is not None and c[0] > argc
            and normalize_decl(c[2]) not in old_decl_norm_set
        ]
        if candidates:
            candidates.sort(key=lambda c: c[0])
            _, _, new_decl = candidates[0]
            new_status = "u" if status == "v" else status
            stdout_lines.append(f"|{new_status}|{header}|{new_decl}")
            consumed_new.add(new_decl)
            continue

        other_classes = new_by_memberargc.get((member, argc), set()) - {cls}
        if other_classes:
            continue

        stderr_lines.append(f"|{status}|{header}|{decl}")

    for header, decl in new:
        if normalize_decl(decl) in old_decl_norm_set or decl in consumed_new:
            continue
        _, member, _ = parse_decl(decl)
        if is_noise(member):
            continue
        stdout_lines.append(f"||{normalize_header(header)}|{decl}")

    seen = set()
    for line in stdout_lines:
        if line not in seen:
            seen.add(line)
            print(line)

    seen = set()
    for line in stderr_lines:
        if line not in seen:
            seen.add(line)
            print(line, file=sys.stderr)


if __name__ == "__main__":
    main()
