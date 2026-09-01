#!/usr/bin/env python3
"""Reconcile ``ql-methods`` markers with bindings, conservatively.

The tracking file is curated data.  The default is report-only and existing
markers are never downgraded from a name/arity heuristic.  With ``--apply``
the tool applies only deterministic additions: blank exact shim matches are
``v``; blank narrower matches are ``u``; optional constructor-family and
non-public scans mark exclusions ``x``.  Ambiguous mappings stay untouched.
"""
import argparse
import re
import sys
from pathlib import Path
from collections import defaultdict

REPO_ROOT = Path(__file__).resolve().parent.parent
CBITS_DIR = REPO_ROOT / "cbits"
CHS_DIR = REPO_ROOT / "QuantLib"
DEFAULT_TARGET = REPO_ROOT / "tools" / "ql-methods-1.43.txt"
DEFAULT_QL_ROOT = Path.home() / "Src" / "QuantLib"

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
CHS_IMPORT_RE = re.compile(r'(?:\{#fun\s+|foreign\s+import\s+ccall\s+"[^\"]*\b)(ql[A-Za-z0-9_]+)')


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


def imported_shims(chs_dir=CHS_DIR):
    """A header declaration alone is not proof a C shim is publicly bound."""
    names = set()
    for path in Path(chs_dir).rglob("*.chs"):
        names.update(CHS_IMPORT_RE.findall(path.read_text(errors="replace")))
    return names


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


def classify(cls, member, argc, decl, base_index, imported):
    if is_noise(member) or argc is None:
        return None
    base, self_offset = candidate_base_and_offset(cls, member, decl)
    raw_argcs = [argc for name, argcs in base_index.items() if name == base
                 for argc in argcs if name in {TRAILING_DIGITS_RE.sub("", n) for n in imported}]
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


def read_tracking(target):
    rows = []
    for number, line in enumerate(Path(target).read_text().splitlines(keepends=True), 1):
        parts = line.rstrip("\n").split("|", 3)
        rows.append((number, line, parts))
    return rows


def nonpublic_line_numbers(rows, ql_root):
    """Find declarations whose resolved overloads are all private/protected."""
    try:
        import clang.cindex
    except ImportError as error:
        raise RuntimeError("--exclude-nonpublic needs python clang.cindex") from error
    pending = defaultdict(list)
    for number, _, parts in rows:
        # A confirmed binding wins over access heuristics; private/protected
        # candidates are the inventory cleanup target, not existing v/u.
        if len(parts) != 4 or parts[1].strip() not in ("", "?"):
            continue
        cls, member, argc = parse_decl(parts[3])
        if cls and not is_noise(member):
            pending[parts[2]].append((number, cls, member, argc))
    sources = {(Path(ql_root) / header).resolve(): header for header in pending}
    umbrella = Path(ql_root) / "ql" / "quantlib.hpp"
    if not umbrella.exists():
        raise RuntimeError(f"QuantLib umbrella header not found: {umbrella}")
    index = clang.cindex.Index.create()
    tu = index.parse(str(umbrella), args=["-x", "c++", "-std=c++20", f"-I{ql_root}", "-I/opt/homebrew/include"])
    access = defaultdict(set)
    seen_headers = set()
    def walk(cursor, owner=None, header=None):
        location = Path(cursor.location.file.name).resolve() if cursor.location.file else None
        here = sources.get(location)
        if here:
            header = here
            seen_headers.add(here)
            if cursor.kind in (clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL):
                owner = cursor.spelling
            elif owner and cursor.kind in (clang.cindex.CursorKind.CXX_METHOD, clang.cindex.CursorKind.CONSTRUCTOR):
                member = owner if cursor.kind == clang.cindex.CursorKind.CONSTRUCTOR else cursor.spelling
                access[(header, owner, member, len(list(cursor.get_arguments())))].add(cursor.access_specifier)
        for child in cursor.get_children():
            walk(child, owner, header)
    walk(tu.cursor)
    # quantlib.hpp intentionally omits some experimental/internal headers.
    # Parse those declarations directly rather than silently treating them as
    # public just because the umbrella header did not transitively include
    # them.
    for header in sorted(set(pending) - seen_headers):
        source = Path(ql_root) / header
        if source.exists():
            walk(index.parse(str(source), args=["-x", "c++", "-std=c++20", f"-I{ql_root}", "-I/opt/homebrew/include"]).cursor)
    found = set()
    for header, entries in pending.items():
        for number, cls, member, argc in entries:
            matches = access.get((header, cls, member, argc), set())
            if matches and all(x != clang.cindex.AccessSpecifier.PUBLIC for x in matches):
                found.add(number)
    return found


def planned_changes(rows, signatures, imported, exclude_constructors=False, nonpublic=frozenset()):
    base_index = build_base_index(signatures)
    changes, ambiguous = {}, []
    # A shim name is not an overload identity: qlFoo, qlFoo1, ... are chosen
    # by binding order and may also represent a deliberately collapsed
    # collection API.  Never promote a second overload by heuristic when its
    # class/member family already has curated evidence; constructor policy can
    # then exclude the remaining overloads explicitly.
    confirmed = set()
    for _, _, parts in rows:
        if len(parts) == 4 and parts[1].strip() in ("v", "u"):
            cls, member, _ = parse_decl(parts[3])
            if cls and member:
                confirmed.add((parts[2], cls, member))
    for number, _, parts in rows:
        if len(parts) != 4 or parts[1].strip() != "":
            continue
        _, _, _, decl = parts
        cls, member, argc = parse_decl(decl)
        if cls and member and (parts[2], cls, member) in confirmed:
            continue
        marker = classify(cls, member, argc, decl, base_index, imported)
        if marker in ("v", "u"):
            changes[number] = (marker, "imported shim")
        elif marker == "?":
            ambiguous.append(number)
    for number in nonpublic:
        if rows[number - 1][2][1].strip() in ("", "?"):
            changes[number] = ("x", "private/protected QuantLib declaration")
    if exclude_constructors:
        supported = set()
        for number, _, parts in rows:
            if len(parts) != 4:
                continue
            cls, member, _ = parse_decl(parts[3])
            status = changes.get(number, (parts[1].strip(), ""))[0]
            if cls and member == cls and status in ("v", "u"):
                supported.add((parts[2], cls))
        for number, _, parts in rows:
            if len(parts) != 4 or parts[1].strip() != "":
                continue
            cls, member, _ = parse_decl(parts[3])
            if cls and member == cls and (parts[2], cls) in supported:
                changes.setdefault(number, ("x", "alternative constructor"))
    return changes, ambiguous


def render(rows, changes):
    out = []
    for number, line, parts in rows:
        if number not in changes:
            out.append(line)
        else:
            _, _, header, decl = parts
            out.append(f"|{changes[number][0]}|{header}|{decl}\n")
    return "".join(out)


# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", nargs="?", type=Path, default=DEFAULT_TARGET)
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--exclude-constructors", action="store_true")
    parser.add_argument("--exclude-nonpublic", action="store_true")
    parser.add_argument("--quantlib-root", type=Path, default=DEFAULT_QL_ROOT)
    args = parser.parse_args()
    rows = read_tracking(args.target)
    nonpublic = nonpublic_line_numbers(rows, args.quantlib_root) if args.exclude_nonpublic else set()
    changes, ambiguous = planned_changes(rows, extract_shim_signatures(CBITS_DIR), imported_shims(), args.exclude_constructors, nonpublic)
    for number in sorted(changes):
        _, _, parts = rows[number - 1]
        print(f"{number}: |{parts[1]}| -> |{changes[number][0]}| ({changes[number][1]}) {parts[3]}")
    print(f"{len(changes)} deterministic changes; {len(ambiguous)} ambiguous shim matches left unchanged", file=sys.stderr)
    if args.apply and changes:
        args.target.write_text(render(rows, changes))


if __name__ == "__main__":
    main()
