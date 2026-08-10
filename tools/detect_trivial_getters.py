#!/usr/bin/env python3
"""
Detect QuantLib getters that just return a field set verbatim from a
constructor parameter (optionally also plain-setter-writable, but never
computed/derived anywhere), and flag the corresponding blank/`?` lines in
tools/ql-methods-1.43.txt as `x` candidates -- see CLAUDE.md's "we rarely
bind inspector/getter methods" policy.

Two-phase by design (see tools/sync_ql_methods_status.py for the same
read-all/write-all pattern this mirrors for --apply):

    python3 tools/detect_trivial_getters.py                  # report mode
    python3 tools/detect_trivial_getters.py --check-existing  # calibrate against |v| lines
    python3 tools/detect_trivial_getters.py --apply           # mutate the tracking file

Requires ~/Src/QuantLib checked out at v1.43 (matching this tracking file's
version) and libclang able to parse it: `-I<QL_ROOT> -I/opt/homebrew/include`
(boost lives there) is enough, since ql/qldefines.hpp falls back to
ql/config.ansi.hpp when HAVE_CONFIG_H isn't defined.

Key technique: libclang exposes a constructor's member-initializer list as
alternating MEMBER_REF / init-expr children of the CONSTRUCTOR cursor, for
both inline (header) and out-of-line (sibling .cpp) definitions -- this is
what lets us tell `field_(param)` (direct pass-through) apart from
`field_(a * b)` (computed) without a full expression evaluator.
"""
import re
import subprocess
import sys
from pathlib import Path

import clang.cindex

REPO_ROOT = Path(__file__).resolve().parent.parent
TARGET = REPO_ROOT / "tools" / "ql-methods-1.43.txt"
QL_ROOT = Path.home() / "Src" / "QuantLib"
REPORT_PATH = REPO_ROOT / "tools" / "trivial_getters_report.txt"

CK = clang.cindex.CursorKind


def get_mac_clang_args():
    try:
        sdk_path = subprocess.check_output(["xcrun", "--show-sdk-path"], text=True).strip()
        target = subprocess.check_output(["clang", "-dumpmachine"], text=True).strip()
        resource_dir = subprocess.check_output(["clang", "-print-resource-dir"], text=True).strip()
        return [
            "-x", "c++", "-std=c++20",
            "-target", target,
            "-isysroot", sdk_path,
            "-resource-dir", resource_dir,
            f"-I{sdk_path}/usr/include",
            f"-I{sdk_path}/usr/include/c++/v1",
            f"-I{QL_ROOT}",
            "-I/opt/homebrew/include",
        ]
    except Exception as e:
        sys.stderr.write(f"Warning: Failed to auto-detect macOS SDK paths: {e}\n")
        return ["-x", "c++", "-std=c++20", f"-I{QL_ROOT}", "-I/opt/homebrew/include"]


# ---------------------------------------------------------------------------
# tracking-file line parsing (mirrors sync_ql_methods_status.py exactly)
# ---------------------------------------------------------------------------

DECL_RE = re.compile(
    r"(?:([\w]+)::)?(~?[\w]+|operator\S*)\s*(?:<[^>]*>)?\s*\((.*)\)\s*(const)?\s*;?\s*$"
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
    m = DECL_RE.search(decl)
    if not m:
        return None, None, None
    cls, member, params = m.group(1), m.group(2), m.group(3)
    params = params.strip()
    argc = 0 if not params else len(split_top_level_commas(params))
    return cls, member, argc


def read_tracking_lines():
    lines = TARGET.read_text().splitlines(keepends=True)
    parsed = []
    for i, line in enumerate(lines):
        stripped = line.rstrip("\n")
        parts = stripped.split("|", 3)
        if len(parts) < 4:
            parsed.append(None)
            continue
        _, status, header, decl = parts
        parsed.append((status, header, decl))
    return lines, parsed


# ---------------------------------------------------------------------------
# per-header clang analysis
# ---------------------------------------------------------------------------

def token_text(cursor):
    return [t.spelling for t in cursor.get_tokens()]


def is_bare_passthrough(init_expr_cursor, param_names):
    """True if init_expr_cursor's tokens are exactly one param name, or
    std::move(param)/std::forward<...>(param)."""
    toks = token_text(init_expr_cursor)
    toks = [t for t in toks if t not in ("(", ")")]
    if len(toks) == 1:
        return toks[0] in param_names
    if len(toks) >= 3 and toks[0] in ("std", "::"):
        pass
    joined = "".join(toks)
    for p in param_names:
        if joined in (f"std::move{p}", f"std::forward<>{p}", f"move{p}"):
            return True
    if len(toks) >= 2 and toks[-1] in param_names and toks[0] in ("move", "forward", "std"):
        return True
    return False


def collect_ctor_direct_fields(class_cursor, extra_cursors):
    """{field_name: param_name} for fields set as a bare pass-through of a
    constructor parameter, across every CONSTRUCTOR cursor found either
    inside class_cursor (inline defs) or in extra_cursors (out-of-line .cpp
    defs matching this class's USR)."""
    direct = {}
    ctor_usr = class_cursor.get_usr()
    ctors = [c for c in class_cursor.get_children() if c.kind == CK.CONSTRUCTOR]
    ctors += [c for c in extra_cursors if c.kind == CK.CONSTRUCTOR
              and c.semantic_parent and c.semantic_parent.get_usr() == ctor_usr]

    for ctor in ctors:
        param_names = {c.spelling for c in ctor.get_children() if c.kind == CK.PARM_DECL}
        children = list(ctor.get_children())
        i = 0
        while i < len(children):
            if children[i].kind == CK.MEMBER_REF:
                field = children[i].spelling
                if i + 1 < len(children) and children[i + 1].kind != CK.MEMBER_REF:
                    if is_bare_passthrough(children[i + 1], param_names):
                        # keep only if every ctor agrees this field is a
                        # bare passthrough (never overwrite with a computed
                        # entry from another overload)
                        direct.setdefault(field, children[i + 1])
                    else:
                        direct[field] = None  # seen a computed init -> disqualify
            i += 1
    return {f: v for f, v in direct.items() if v is not None}


def collect_computed_field_writes(class_cursor, extra_cursors, ctor_direct_fields):
    """Field names written anywhere (ctor, setter, calculate(), etc.) with
    something other than a bare parameter/this pass-through."""
    computed = set()

    def scan_body(body_cursor, param_names):
        for c in body_cursor.walk_preorder():
            if c.kind == CK.BINARY_OPERATOR:
                toks = token_text(c)
                if "=" in toks and toks.count("=") == 1 and "==" not in "".join(toks):
                    eq_idx = toks.index("=")
                    lhs, rhs = toks[:eq_idx], toks[eq_idx + 1:]
                    if len(lhs) >= 1 and lhs[-1].endswith("_"):
                        field = lhs[-1]
                        rhs_joined = "".join(rhs)
                        ok = len(rhs) == 1 and rhs[0] in param_names
                        if not ok:
                            computed.add(field)

    all_cursors = list(class_cursor.get_children()) + list(extra_cursors)
    methods = [c for c in all_cursors if c.kind in (CK.CXX_METHOD, CK.CONSTRUCTOR, CK.DESTRUCTOR)]
    for m in methods:
        params = {c.spelling for c in m.get_children() if c.kind == CK.PARM_DECL}
        params.add("this")
        for c in m.get_children():
            if c.kind == CK.COMPOUND_STMT:
                scan_body(c, params)
    return computed


def get_trivial_return_field(method_cursor):
    """If method's body is exactly `return field_;`, return field_'s name,
    else None."""
    body = None
    for c in method_cursor.get_children():
        if c.kind == CK.COMPOUND_STMT:
            body = c
    if body is None:
        return None
    stmts = list(body.get_children())
    if len(stmts) != 1 or stmts[0].kind != CK.RETURN_STMT:
        return None
    ret_children = list(stmts[0].get_children())
    if len(ret_children) != 1:
        return None
    inner = ret_children[0]
    # unwrap implicit casts etc. down to a MEMBER_REF_EXPR / DECL_REF_EXPR
    while inner.kind in (CK.UNEXPOSED_EXPR,) and list(inner.get_children()):
        inner = list(inner.get_children())[0]
    if inner.kind in (CK.MEMBER_REF_EXPR, CK.DECL_REF_EXPR):
        return inner.spelling
    return None


def is_virtual(method_cursor):
    try:
        if method_cursor.is_virtual_method():
            return True
        if list(method_cursor.get_overridden_cursors()):
            return True
    except (AttributeError, TypeError):
        pass
    return False


class Candidate:
    def __init__(self, header, cls, method, field, param, ctor_evidence, getter_evidence):
        self.header = header
        self.cls = cls
        self.method = method
        self.field = field
        self.param = param
        self.ctor_evidence = ctor_evidence
        self.getter_evidence = getter_evidence


def analyze_header(header_rel, index, clang_args):
    """-> {(class, method): Candidate} for every trivial-getter candidate
    found in this header (inline) and its sibling .cpp (out-of-line defs)."""
    hpp_path = QL_ROOT / header_rel
    if not hpp_path.exists():
        return {}
    cpp_path = hpp_path.with_suffix(".cpp")

    tu = index.parse(str(hpp_path), args=clang_args)
    extra_children = []
    if cpp_path.exists():
        cpp_tu = index.parse(str(cpp_path), args=clang_args)
        extra_children = list(cpp_tu.cursor.get_children())

    results = {}

    def visit(node):
        if node.kind in (CK.CLASS_DECL, CK.STRUCT_DECL, CK.CLASS_TEMPLATE) and node.is_definition():
            if node.location.file and str(node.location.file) == str(hpp_path):
                handle_class(node)
            for c in node.get_children():
                visit(c)
            return
        for c in node.get_children():
            visit(c)

    def handle_class(class_cursor):
        cls_usr = class_cursor.get_usr()
        my_extra = [c for c in extra_children if c.semantic_parent and c.semantic_parent.get_usr() == cls_usr]

        direct_fields = collect_ctor_direct_fields(class_cursor, my_extra)
        if not direct_fields:
            return
        computed = collect_computed_field_writes(class_cursor, my_extra, direct_fields)
        safe_fields = {f: v for f, v in direct_fields.items() if f not in computed}
        if not safe_fields:
            return

        candidates_methods = list(class_cursor.get_children()) + my_extra
        for m in candidates_methods:
            if m.kind != CK.CXX_METHOD:
                continue
            if m.access_specifier != clang.cindex.AccessSpecifier.PUBLIC:
                continue
            if list(m.get_arguments()):
                continue  # getters only: zero args
            if is_virtual(m):
                continue
            field = get_trivial_return_field(m)
            if field is None or field not in safe_fields:
                continue
            init_expr = safe_fields[field]
            results[(class_cursor.spelling, m.spelling)] = Candidate(
                header_rel, class_cursor.spelling, m.spelling, field,
                "".join(token_text(init_expr)),
                f"{field}({''.join(token_text(init_expr))})",
                "".join(token_text(m)) if False else f"return {field};",
            )

    visit(tu.cursor)
    return results


# ---------------------------------------------------------------------------

def main():
    mode_apply = "--apply" in sys.argv
    mode_check_existing = "--check-existing" in sys.argv

    _, parsed = read_tracking_lines()

    target_statuses = {"v"} if mode_check_existing else {" ", "?"}

    by_header = {}
    for entry in parsed:
        if entry is None:
            continue
        status, header, decl = entry
        if status not in target_statuses:
            continue
        by_header.setdefault(header, []).append(decl)

    index = clang.cindex.Index.create()
    clang_args = get_mac_clang_args()

    all_candidates = []
    headers = sorted(by_header)
    for n, header in enumerate(headers, 1):
        sys.stderr.write(f"\r[{n}/{len(headers)}] {header}" + " " * 20)
        sys.stderr.flush()
        try:
            found = analyze_header(header, index, clang_args)
        except Exception as e:
            sys.stderr.write(f"\nWarning: failed to parse {header}: {e}\n")
            continue
        if not found:
            continue
        for decl in by_header[header]:
            cls, member, argc = parse_decl(decl)
            if cls is None or argc != 0:
                continue
            cand = found.get((cls, member))
            if cand:
                all_candidates.append((decl, cand))
    sys.stderr.write("\n")

    if mode_apply:
        lines, parsed2 = read_tracking_lines()
        decl_to_cand = {c[0]: c[1] for c in all_candidates}
        out = []
        changed = 0
        for line, entry in zip(lines, parsed2):
            if entry is None:
                out.append(line)
                continue
            status, header, decl = entry
            if status in {" ", "?"} and decl in decl_to_cand:
                newline = "\n" if line.endswith("\n") else ""
                out.append(f"|x|{header}|{decl}{newline}")
                changed += 1
            else:
                out.append(line)
        TARGET.write_text("".join(out))
        print(f"Marked {changed} lines as |x|.")
        return

    label = "|v| lines flagged (should be ~0)" if mode_check_existing else "candidates"
    out_path = REPORT_PATH
    with out_path.open("w") as f:
        for decl, cand in all_candidates:
            f.write(
                f"{cand.header}\t{cand.cls}::{cand.method}\t"
                f"field={cand.field}\tctor_init={cand.ctor_evidence}\t"
                f"getter_body={cand.getter_evidence}\tdecl={decl}\n"
            )
    print(f"{len(all_candidates)} {label}. Report written to {out_path}")


if __name__ == "__main__":
    main()
