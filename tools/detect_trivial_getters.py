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

A getter also qualifies if its body is a bare `return field_;` preceded only
by guard statements (QL_REQUIRE/assert-shaped) that don't themselves write
to any field, or if it indexes a ctor-direct field by its sole parameter
(`return field_[i];`, matched via the `operator[]` CALL_EXPR libclang
produces for e.g. std::vector -- an ARRAY_SUBSCRIPT_EXPR is only what you'd
see for a raw C array/pointer, not a container's overloaded operator[]).

Virtual/overridden methods are NOT excluded: this project never subclasses
QuantLib or links against out-of-tree QuantLib code, so there's no call
site that only sees a base-class type with a possibly-different override --
every concrete override that exists is visible in this checkout.
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
RETURN_FIELD_RE = re.compile(
    r"\breturn\s+[A-Za-z_]\w*_\s*(?:;|\[)"
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


def may_contain_supported_return(header_rel):
    """Whether the header or its sibling implementation can contain a
    return expression supported by get_trivial_return.

    This is a completeness-preserving parse prefilter: every eligible method
    has source spelling `return field_;` or `return field_[index];`.  Headers
    with neither form cannot contribute a candidate, so there is no reason to
    pay libclang's full translation-unit cost for them.
    """
    hpp_path = QL_ROOT / header_rel
    paths = (hpp_path, hpp_path.with_suffix(".cpp"))
    for path in paths:
        try:
            if path.exists() and RETURN_FIELD_RE.search(path.read_text()):
                return True
        except UnicodeDecodeError:
            continue
    return False


# ---------------------------------------------------------------------------
# per-header clang analysis
# ---------------------------------------------------------------------------

def token_text(cursor):
    return [t.spelling for t in cursor.get_tokens()]


def base_type_str(t):
    """Canonicalized (typedef-resolved), cv/ref-stripped type spelling, for
    comparing a field's declared type against a constructor parameter's."""
    try:
        s = t.get_canonical().spelling
    except Exception:
        s = t.spelling
    for tok in ("const ", "&&", "&"):
        s = s.replace(tok, "")
    return s.strip()


def is_bare_passthrough(init_expr_cursor, param_by_name):
    """Returns the matched PARM_DECL cursor if init_expr_cursor is exactly
    one parameter reference (by identifier, not token text) -- either
    directly (primitive-typed field: a bare DECL_REF_EXPR) or as the sole
    argument of an implicit copy/converting-constructor CALL_EXPR
    (class-typed field, e.g. std::vector<T>/Handle<T>: `field_(param)`
    parses as a CALL_EXPR to the field type's constructor, not a bare
    reference), including one level of std::move/std::forward wrapping
    either shape. Else None.

    Matching by parameter *identity* here (not just name) lets the caller
    additionally check the parameter's declared type against the field's --
    needed because e.g. `std::vector<Real> locations_` initialized as
    `locations_(size)` from a `Size size` parameter is a *sizing*
    constructor (N default-valued elements), not a value copy, even though
    it structurally looks identical to a real copy/converting constructor
    call with one argument matching a parameter name."""
    node = unwrap(init_expr_cursor)
    if node.kind == CK.DECL_REF_EXPR:
        return param_by_name.get(node.spelling)
    if node.kind == CK.CALL_EXPR:
        args = list(node.get_arguments())
        if len(args) != 1:
            return None
        inner = unwrap(args[0])
        if node.spelling in ("move", "forward"):
            if inner.kind == CK.DECL_REF_EXPR:
                return param_by_name.get(inner.spelling)
            return None
        if inner.kind == CK.DECL_REF_EXPR:
            return param_by_name.get(inner.spelling)
        # one level of std::move/forward nested inside the copy-ctor arg
        if inner.kind == CK.CALL_EXPR and inner.spelling in ("move", "forward"):
            inner_args = list(inner.get_arguments())
            if len(inner_args) == 1:
                innermost = unwrap(inner_args[0])
                if innermost.kind == CK.DECL_REF_EXPR:
                    return param_by_name.get(innermost.spelling)
    return None


def collect_ctor_direct_fields(class_cursor, extra_cursors, field_types):
    """{field_name: init_expr_cursor} for fields set as a bare pass-through
    of a same-typed constructor parameter, across every CONSTRUCTOR cursor
    found either inside class_cursor (inline defs) or in extra_cursors
    (out-of-line .cpp defs matching this class's USR)."""
    direct = {}
    ctor_usr = class_cursor.get_usr()
    ctors = [c for c in class_cursor.get_children() if c.kind == CK.CONSTRUCTOR]
    ctors += [c for c in extra_cursors if c.kind == CK.CONSTRUCTOR
              and c.semantic_parent and c.semantic_parent.get_usr() == ctor_usr]

    for ctor in ctors:
        param_by_name = {c.spelling: c for c in ctor.get_children() if c.kind == CK.PARM_DECL}
        children = list(ctor.get_children())
        i = 0
        while i < len(children):
            if children[i].kind == CK.MEMBER_REF:
                field = children[i].spelling
                if i + 1 < len(children) and children[i + 1].kind != CK.MEMBER_REF:
                    param = is_bare_passthrough(children[i + 1], param_by_name)
                    field_type = field_types.get(field)
                    if (param is not None and field_type is not None
                            and base_type_str(field_type) == base_type_str(param.type)):
                        # keep only if every ctor agrees this field is a
                        # bare passthrough (never overwrite with a computed
                        # entry from another overload)
                        direct.setdefault(field, children[i + 1])
                    else:
                        direct[field] = None  # seen a computed/mismatched init -> disqualify
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


def unwrap(cursor):
    """Strip implicit-cast/materialize wrapper nodes down to the real expr.
    Only descends when there's exactly one child: a template-dependent
    multi-arg call (e.g. `field_(a, b)` inside an uninstantiated class
    template) also surfaces as UNEXPOSED_EXPR, but with one child per
    argument -- blindly taking "the first child" there would silently
    mistake a computed multi-arg init for a bare single-param passthrough."""
    while cursor.kind == CK.UNEXPOSED_EXPR:
        children = list(cursor.get_children())
        if len(children) != 1:
            break
        cursor = children[0]
    return cursor


def has_field_assignment(cursor):
    """True if any BINARY_OPERATOR `=` under cursor assigns to a `*_` field
    (regardless of RHS) -- used to reject guard statements that mutate
    state, not just ones that mutate it in a computed way."""
    for c in cursor.walk_preorder():
        if c.kind == CK.BINARY_OPERATOR:
            toks = token_text(c)
            if "=" in toks and toks.count("=") == 1 and "==" not in "".join(toks):
                eq_idx = toks.index("=")
                lhs = toks[:eq_idx]
                if lhs and lhs[-1].endswith("_"):
                    return True
    return False


def get_trivial_return(method_cursor, param_names):
    """If method's body is `return field_;` (optionally preceded by
    guard/assert statements that don't write to any field), returns
    (field_name, None). If it's `return field_[p];` where p is the
    method's sole parameter, returns (field_name, param_name). Else None."""
    body = None
    for c in method_cursor.get_children():
        if c.kind == CK.COMPOUND_STMT:
            body = c
    if body is None:
        return None
    stmts = list(body.get_children())
    if not stmts or stmts[-1].kind != CK.RETURN_STMT:
        return None
    if any(has_field_assignment(s) for s in stmts[:-1]):
        return None

    ret_children = list(stmts[-1].get_children())
    if len(ret_children) != 1:
        return None
    inner = unwrap(ret_children[0])

    # Returning a class-typed field by value is represented as an implicit
    # copy-constructor CALL_EXPR, even though the source is just
    # `return field_;` (e.g. `Date baseDate() { return baseDate_; }`).
    # Accept only the token-free implicit wrapper: an explicit conversion or
    # construction such as `return Date(field_);` remains non-trivial.
    if inner.kind == CK.CALL_EXPR:
        args = list(inner.get_arguments())
        if len(args) == 1 and token_text(inner) == token_text(args[0]):
            inner = unwrap(args[0])

    if inner.kind in (CK.MEMBER_REF_EXPR, CK.DECL_REF_EXPR):
        return inner.spelling, None

    # operator[]-shaped access, possibly wrapped in an outer implicit-convert
    # CALL_EXPR: libclang represents `field_[i]` (a container's overloaded
    # operator[]) as a CALL_EXPR named "operator[]" whose arguments are
    # [base, index] -- not an ARRAY_SUBSCRIPT_EXPR, which is raw-array-only.
    op_candidates = [inner] + (list(inner.get_children()) if inner.kind == CK.CALL_EXPR else [])
    for cand in op_candidates:
        cand = unwrap(cand)
        if cand.kind == CK.CALL_EXPR and cand.spelling == "operator[]":
            op_args = list(cand.get_arguments())
            if len(op_args) != 2:
                continue
            base = unwrap(op_args[0])
            idx = unwrap(op_args[1])
            if base.kind != CK.MEMBER_REF_EXPR:
                continue
            idx_toks = [t.spelling for t in idx.get_tokens()]
            if len(idx_toks) == 1 and idx_toks[0] in param_names:
                return base.spelling, idx_toks[0]
    return None


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

    # A sibling implementation includes its header, so one .cpp translation
    # unit gives us both the class declaration/inline bodies from the header
    # and the out-of-line definitions.  Parsing each separately roughly
    # doubled the cost of a repository-wide audit.
    tu_source = cpp_path if cpp_path.exists() else hpp_path
    tu = index.parse(str(tu_source), args=clang_args)
    def source_definitions(cursor, source_path):
        """Implementation cursors physically defined in source_path."""
        result = []
        source_resolved = source_path.resolve()

        def collect(cursor):
            for child in cursor.get_children():
                if child.location.file:
                    try:
                        in_source = Path(str(child.location.file)).resolve() == source_resolved
                    except OSError:
                        in_source = False
                    if in_source and child.kind in (
                            CK.CONSTRUCTOR, CK.CXX_METHOD, CK.DESTRUCTOR):
                        result.append(child)
                collect(child)

        collect(cursor)
        return result

    # A header can put an inline definition after the class body, at namespace
    # scope (Coupon's inspectors do).  Such a definition is not a child of
    # the class cursor either, so collect it by semantic parent just like the
    # sibling .cpp definitions.
    extra_definitions = source_definitions(tu.cursor, hpp_path)
    if cpp_path.exists():
        # Methods and constructors defined in a .cpp nested under
        # `namespace QuantLib` are not children of the translation-unit
        # cursor.  The previous top-level-only collection therefore made the
        # out-of-line half of the analysis a no-op for normal QuantLib code.
        # Restrict the recursive walk to cursors physically defined by this
        # .cpp: its included headers contain declarations (and often inline
        # definitions) which the header TU already supplies.
        extra_definitions.extend(source_definitions(tu.cursor, cpp_path))

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
        my_extra = [c for c in extra_definitions
                    if c.semantic_parent and c.semantic_parent.get_usr() == cls_usr]

        field_types = {f.spelling: f.type for f in class_cursor.get_children() if f.kind == CK.FIELD_DECL}
        direct_fields = collect_ctor_direct_fields(class_cursor, my_extra, field_types)
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
            args = list(m.get_arguments())
            if len(args) > 1:
                continue  # getters and single-index accessors only
            param_names = {a.spelling for a in args}
            result = get_trivial_return(m, param_names)
            if result is None:
                continue
            field, idx_param = result
            if field not in safe_fields:
                continue
            if idx_param is None and args:
                continue  # a bare-field return must take no args
            if idx_param is not None and not args:
                continue  # an indexed return must take the index arg
            init_expr = safe_fields[field]
            evidence = f"return {field};" if idx_param is None else f"return {field}[{idx_param}];"
            # token_text(init_expr) already spans the full `field_(...)` source
            # range for a CALL_EXPR init (implicit copy/converting ctor), so
            # don't re-wrap it in another f"{field}(...)".
            ctor_evidence = "".join(token_text(init_expr))
            if not ctor_evidence.startswith(field):
                ctor_evidence = f"{field}({ctor_evidence})"
            key = (class_cursor.spelling, m.spelling, len(args))
            results[key] = Candidate(
                header_rel, class_cursor.spelling, m.spelling, field,
                ctor_evidence, ctor_evidence, evidence,
            )

    visit(tu.cursor)
    return results


# ---------------------------------------------------------------------------

def main():
    mode_apply = "--apply" in sys.argv
    mode_check_existing = "--check-existing" in sys.argv
    shard = None
    if "--shard" in sys.argv:
        try:
            shard_arg = sys.argv[sys.argv.index("--shard") + 1]
            shard_index, shard_count = (int(part) for part in shard_arg.split("/", 1))
            if not (0 <= shard_index < shard_count):
                raise ValueError
            shard = (shard_index, shard_count)
        except (IndexError, ValueError):
            raise SystemExit("--shard expects INDEX/COUNT, with 0 <= INDEX < COUNT")
    if mode_apply and shard is not None:
        raise SystemExit("--apply cannot be combined with --shard")

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
    headers = [header for header in sorted(by_header)
               if may_contain_supported_return(header)]
    if shard is not None:
        shard_index, shard_count = shard
        headers = [header for i, header in enumerate(headers)
                   if i % shard_count == shard_index]
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
            if cls is None or argc > 1:
                continue
            cand = found.get((cls, member, argc))
            if cand:
                all_candidates.append((decl, cand))
    sys.stderr.write("\n")

    if mode_apply:
        lines, parsed2 = read_tracking_lines()
        decl_to_cand = {c[0]: c[1] for c in all_candidates}
        # Preserve the evidence for this exact apply run.  Once statuses are
        # changed there are intentionally no longer blank/? candidates to
        # reconstruct the report from.
        with REPORT_PATH.open("w") as f:
            for decl, cand in all_candidates:
                f.write(
                    f"{cand.header}\t{cand.cls}::{cand.method}\t"
                    f"field={cand.field}\tctor_init={cand.ctor_evidence}\t"
                    f"getter_body={cand.getter_evidence}\tdecl={decl}\n"
                )
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
    # Calibration shards are intentionally report-free so several can run in
    # parallel without racing on trivial_getters_report.txt.
    if mode_check_existing and shard is not None:
        print(f"{len(all_candidates)} {label} in shard {shard_index}/{shard_count}.")
        return
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
