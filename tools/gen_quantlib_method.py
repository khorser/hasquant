#!/usr/bin/env python3
"""
Generate hasquant method-binding boilerplate from C++ QuantLib prototypes.

Reads one prototype per line from stdin -- either a line from the clang-
extracted dump (tools/ql-methods-1.43.txt, format
`<flag>|<flag2>|<header path>|<C++ declaration>;`) or a bare declaration
(e.g. hand-typed, or grepped straight out of a QuantLib header) -- and
emits a best-effort cbits/*.h declaration, cbits/*.cpp implementation, and
QuantLib/*.chs {#fun#} binding for each one, following the conventions in
.claude/skills/add-quantlib-method/SKILL.md.

This is NOT a bulletproof translator. Its job is to save the mechanical
part of binding a method whose receiver class is already bound -- picking
the right pointer-dereference depth, the exception/char**e convention, and
a correctly-shaped .chs line -- not to guess at anything it isn't sure of.
Whenever a parameter, return type, or method shape isn't recognized, the
line is rendered as a SKIPPED block with the specific reason instead of a
plausible-looking-but-wrong shim. In particular:
  - static vs. instance methods are NOT distinguishable from a bare
    declaration (dump_signatures.py drops the `static` keyword) -- every
    non-constructor method is assumed to take a receiver; a comment flags
    this assumption so a human can check the real header.
  - overload C-name suffixes (qlXFoo, qlXFoo1, qlXFoo2, ...) are assigned
    deterministically in input order, which will NOT generally match
    existing hand-written suffixes (those reflect historical addition
    order, not something derivable from the signature) -- treat them as
    placeholders to rename, not final names.
  - the receiver class, and every parameter/return class, must already be
    bound (found in the scraped registries below) or the line is skipped
    with a "bind the class first" reason -- this tool never bootstraps a
    new class (see tools/gen_quantlib_hierarchy.py / add-quantlib-class).

Classification is driven by registries scraped live from the current
cbits/ and QuantLib/ trees (which classes are hierarchy vs. plain-value,
which already have with<T>/peek<T>/with<T>Array/withMaybe<T>, which enums
are declared and how they're conventionally marshalled) rather than
hardcoded lists, so it stays correct as classes are added -- including by
tools/gen_quantlib_hierarchy.py.

Usage:
    grep '::Bond::' tools/ql-methods-1.43.txt | python3 tools/gen_quantlib_method.py
    echo 'Real Bond::cleanPrice(Real accruedAmount) const;' | python3 tools/gen_quantlib_method.py
"""
import re
import sys
import glob
import os
from dataclasses import dataclass, field

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

NUMERIC_DOUBLE = {"Real", "Rate", "Spread", "Time", "DiscountFactor",
                  "Volatility", "Probability", "Decimal", "double", "float"}
NUMERIC_INT = {"Integer", "Natural", "Size", "BigInteger", "BigNatural",
               "int", "unsigned", "unsigned int", "long", "short", "Month", "Year", "Day"}
BOOL_TYPES = {"bool"}
STRING_TYPES = {"std::string", "string"}


# ------------------------------------------------------------- registries


@dataclass
class Registries:
    hierarchy_classes: set = field(default_factory=set)   # ClassName (Ql-prefixed in qlTypesC2HS.h)
    plain_value_classes: set = field(default_factory=set)  # ClassName (bare in qlTypesC2HS.h)
    with_argtype: dict = field(default_factory=dict)      # ClassName -> arg type text, e.g. "GenBond a" or "Calendar"
    peek_rettype: dict = field(default_factory=dict)       # ClassName -> return type text, e.g. "Bond"
    with_array: set = field(default_factory=set)           # ClassName with an existing with<T>Array
    with_maybe: set = field(default_factory=set)           # ClassName with an existing withMaybe<T>
    enum_chs_name: dict = field(default_factory=dict)      # normalized C++ name -> chs type name
    enum_bare_ok: set = field(default_factory=set)         # chs enum names seen used bare elsewhere
    enum_fromEnumC: set = field(default_factory=set)       # chs enum names seen used via fromEnumC
    chs_file_for_class: dict = field(default_factory=dict)  # ClassName -> a .chs file that already binds it


def _chs_and_hs_files():
    files = glob.glob(os.path.join(ROOT, "QuantLib", "**", "*.chs"), recursive=True)
    files += glob.glob(os.path.join(ROOT, "QuantLib", "**", "*.hs"), recursive=True)
    return files


def build_registries() -> Registries:
    reg = Registries()

    c2hs_path = os.path.join(ROOT, "cbits", "qlTypesC2HS.h")
    with open(c2hs_path) as f:
        for line in f:
            m = re.match(r"typedef struct (\w+) \1;", line.strip())
            if not m:
                continue
            name = m.group(1)
            if name.startswith("Ql") and len(name) > 2 and name[2].isupper():
                reg.hierarchy_classes.add(name[2:])
            else:
                reg.plain_value_classes.add(name)

    with_re = re.compile(r"^with(?P<name>[A-Z]\w*)\s*::\s*(?P<argty>.+?)\s*->\s*\(")
    peek_re = re.compile(r"^peek(?P<name>[A-Z]\w*)\s*::\s*Ptr\s+\S+\s*->\s*IO\s+(?P<retty>.+?)\s*$")
    pointer_re = re.compile(r"\{#pointer\s+\*Ql?(?P<cname>\w+?)'?\s+as\s+(?P<hsname>\w+)")
    enum_decl_re = re.compile(r"\{#enum\s+([\w:]+)")
    fromenumc_re = re.compile(r"fromEnumC`(\w+)'")
    bare_backtick_re = re.compile(r"(fromEnumC)?`(\w+)'")

    for path in _chs_and_hs_files():
        with open(path, errors="ignore") as f:
            text = f.read()
        for line in text.splitlines():
            stripped = line.strip()
            m = with_re.match(stripped)
            if m:
                name, argty = m.group("name"), m.group("argty")
                if name.startswith("Maybe"):
                    reg.with_maybe.add(name[len("Maybe"):])
                elif name.endswith("Array"):
                    pass  # tracked separately below via a simpler suffix check
                else:
                    reg.with_argtype.setdefault(name, argty)
            m = peek_re.match(stripped)
            if m:
                reg.peek_rettype.setdefault(m.group("name"), m.group("retty"))
            m = re.match(r"^with(\w+)Array\s*::", stripped)
            if m:
                reg.with_array.add(m.group(1))
            m = re.match(r"^withMaybe(\w+)\s*::", stripped)
            if m:
                reg.with_maybe.add(m.group(1))
            m = pointer_re.search(stripped)
            if m:
                hsname = m.group("hsname")
                relpath = os.path.relpath(path, ROOT)
                stem = os.path.splitext(os.path.basename(relpath))[0]
                current = reg.chs_file_for_class.get(hsname)
                if current is None or (stem == hsname and os.path.splitext(os.path.basename(current))[0] != hsname):
                    reg.chs_file_for_class[hsname] = relpath
            m = enum_decl_re.search(stripped)
            if m:
                cpp_name = m.group(1)
                chs_name = cpp_name.split("::")[-1]
                reg.enum_chs_name[cpp_name] = chs_name
                reg.enum_chs_name[chs_name] = chs_name

        for m in fromenumc_re.finditer(text):
            reg.enum_fromEnumC.add(m.group(1))
        for m in bare_backtick_re.finditer(text):
            if m.group(1):
                continue
            reg.enum_bare_ok.add(m.group(2))

    return reg


# ------------------------------------------------------------------ parse


@dataclass
class ParsedProto:
    raw: str
    cls: str
    member: str
    is_ctor: bool
    is_dtor: bool
    is_operator: bool
    ret_type: str
    params: list  # list of (type_str, name, default_text_or_None)
    is_static: bool = False


def split_top_level(s, sep=","):
    """Split on sep, ignoring occurrences nested inside <...> or (...)."""
    parts = []
    depth = 0
    cur = []
    for ch in s:
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        if ch == sep and depth == 0:
            parts.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if cur:
        parts.append("".join(cur))
    return [p.strip() for p in parts if p.strip()]


PROTO_RE = re.compile(
    r"^(?P<ret>.*?)\b(?P<qualified>(?P<cls>[\w]+)::(?P<member>~?[\w]+|operator\S*))"
    r"\s*(?:<[^>]*>)?\s*\((?P<params>.*)\)\s*(?P<const>const)?\s*;?\s*$"
)


def strip_param_default(p):
    """('type name', default_text_or_None) -- splits off a top-level ` = ...` suffix
    (dump_signatures.py now captures C++ default values; older dumps never had one)."""
    depth = 0
    for i, ch in enumerate(p):
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        elif ch == "=" and depth == 0:
            return p[:i].rstrip(), p[i + 1:].strip()
    return p, None


def parse_line(line: str):
    line = line.rstrip("\n")
    if not line.strip():
        return None, None
    flag = None
    decl = line
    if "|" in line:
        fields = line.split("|")
        if len(fields) >= 4:
            flag = fields[1].strip()
            decl = fields[3].strip()
        else:
            return None, "malformed dump line (expected 4 `|`-fields)"
    if flag in ("x", "v"):
        return None, None  # silently excluded / already-handled, not an error

    decl = decl.strip()
    if not decl.endswith(";"):
        decl = decl + ";"

    is_static = decl.startswith("static ")
    if is_static:
        decl = decl[len("static "):]

    m = PROTO_RE.match(decl)
    if not m:
        return None, f"could not parse declaration: {decl!r}"

    cls = m.group("cls")
    member = m.group("member")
    ret = m.group("ret").strip()
    raw_params = m.group("params").strip()

    if "operator" in member:
        return None, "operator overload -- not bindable via a named C shim, skip"

    is_dtor = member.startswith("~")
    is_ctor = (not is_dtor) and member == cls and ret == ""

    params = []
    for p in split_top_level(raw_params):
        p, default_text = strip_param_default(p)
        pm = re.match(r"^(.*[\s>&*])(\w+)$", p)
        if pm:
            ptype, pname = pm.group(1).strip(), pm.group(2)
        else:
            ptype, pname = p.strip(), None
        params.append((ptype, pname, default_text))

    return ParsedProto(decl, cls, member, is_ctor, is_dtor, False, ret, params, is_static), None


# ------------------------------------------------------------- classify


@dataclass
class Marshal:
    ok: bool
    c_params: list = field(default_factory=list)   # [(c_type, c_name), ...] this Haskell value expands to
    cpp_expr: str = ""                              # C++ expression yielding the value, using c_params' names
    chs_frag: str = ""                              # the .chs marshaller text for this argument
    note: str = ""                                  # reason, if not ok
    # return-only fields:
    c_ret_type: str = ""
    cpp_wrap: str = ""                               # format string with {expr} placeholder
    chs_ret: str = ""
    extra_c_out_params: list = field(default_factory=list)  # for vector-return out-params
    chs_out_frag: str = ""                           # the .chs arg-list fragment for those out-params


def strip_cv(t: str) -> str:
    t = t.strip()
    t = re.sub(r"^const\s+", "", t)
    t = re.sub(r"[\s&*]+$", "", t)
    t = t.strip()
    return t


def lookup_enum(t: str, bare: str, reg: Registries):
    """Match a (possibly qualified, e.g. Position::Type) C++ enum spelling against
    the scraped {#enum#} registry. Qualified names are conventionally bound with
    their ::-separated components concatenated (Position::Type -> PositionType,
    DateGeneration::Rule -> DateGenerationRule), not just the last component."""
    concat = t.replace("::", "")
    return (reg.enum_chs_name.get(t) or reg.enum_chs_name.get(concat)
            or reg.enum_chs_name.get(bare))


def split_template(t: str):
    """If t is Outer<Inner>, return (Outer, Inner); else None."""
    m = re.match(r"^([\w:]+)\s*<(.+)>$", t.strip())
    if not m:
        return None
    return m.group(1), m.group(2).strip()


def classify_arg(type_str: str, pname: str, reg: Registries, letters) -> Marshal:
    t = strip_cv(type_str)
    cname = pname or f"x{len(letters.used)}"

    if t in NUMERIC_DOUBLE:
        return Marshal(True, [("double", cname)], cname, f"`Double'")
    if t in NUMERIC_INT:
        return Marshal(True, [("int", cname)], cname, f"`Int'")
    if t in BOOL_TYPES:
        return Marshal(True, [("int", cname)], cname, f"`Bool'")
    if t in STRING_TYPES or t in ("const char *", "char *"):
        return Marshal(True, [("char*", cname)], f"std::string({cname})", f"`String'")
    if t == "Date":
        return Marshal(True, [("int", cname)], f"Date({cname})", f"withDay*`Day'")

    tmpl = split_template(t)
    if tmpl:
        outer, inner = tmpl
        outer_bare = outer.split("::")[-1]

        if outer_bare == "optional":
            if inner == "bool":
                return Marshal(True, [("int", cname)], f"qlOptBool({cname})", f"fromMaybeBool`Maybe Bool'")
            if inner == "Date":
                return Marshal(True, [("int", cname)], f"qlNullableDate({cname})", f"withMaybeDay*`Maybe Day'")
            return Marshal(False, note=f"unsupported ext::optional<{inner}> -- only bool/Date have an established Maybe-marshalling convention")

        if outer_bare == "Handle":
            cls = strip_cv(inner).split("::")[-1]
            if cls not in reg.hierarchy_classes:
                return Marshal(False, note=f"Handle<{cls}> -- '{cls}' is not a bound hierarchy class")
            if cls not in reg.with_maybe:
                return Marshal(False, note=f"Handle<{cls}> needs a withMaybe{cls} combinator in Internal/Type.hs (none found) -- add one alongside with{cls}")
            return Marshal(True, [(f"Ql{cls}*", cname)], f"qlNullableHandle(arg({cname}))",
                            f"withMaybe{cls}*`Maybe (Gen{cls} {letters.next()})'")

        if outer_bare in ("shared_ptr",):
            cls = strip_cv(inner).split("::")[-1]
            return classify_hierarchy_arg(cls, cname, reg, letters)

        if outer_bare == "vector":
            elem = strip_cv(inner)
            if elem in NUMERIC_DOUBLE:
                return Marshal(True, [("unsigned", cname + "Len"), ("double*", cname)],
                                f"std::vector<double>({cname}, {cname}+{cname}Len)",
                                f"withDoubleArray*`[Double]'&")
            if elem in NUMERIC_INT or elem == "Date":
                ctor = f"qlDateVector({cname}, {cname}Len)" if elem == "Date" else \
                       f"std::vector<{elem}>({cname}, {cname}+{cname}Len)"
                return Marshal(True, [("unsigned", cname + "Len"), ("int*", cname)], ctor,
                                f"with{'DayArray' if elem == 'Date' else 'IntArray'}*`[{'Day' if elem == 'Date' else 'Int'}]'&")
            etmpl = split_template(elem)
            if etmpl and etmpl[0].split("::")[-1] == "shared_ptr":
                ecls = strip_cv(etmpl[1]).split("::")[-1]
                if ecls not in reg.hierarchy_classes:
                    return Marshal(False, note=f"vector<shared_ptr<{ecls}>> -- '{ecls}' is not a bound hierarchy class")
                if ecls not in reg.with_array:
                    return Marshal(False, note=f"vector<shared_ptr<{ecls}>> needs a with{ecls}Array combinator (= withGenArray with{ecls}) in Internal/Type.hs -- none found")
                return Marshal(True, [("unsigned", cname + "Len"), (f"Ql{ecls}**", cname)],
                                f"qlVector({cname}, {cname}Len)", f"with{ecls}Array*`[{ecls}]'&")
            return Marshal(False, note=f"vector<{elem}> -- element type not recognized, needs manual handling")

    # bare class name (no template wrapper) -- e.g. `const Bond&`, `Calendar`
    bare = t.split("::")[-1]
    enum_name = lookup_enum(t, bare, reg)
    if enum_name:
        cast_expr = f"({t}){cname}"
        if enum_name in reg.enum_bare_ok and enum_name not in reg.enum_fromEnumC:
            return Marshal(True, [("int", cname)], cast_expr, f"`{enum_name}'")
        return Marshal(True, [("int", cname)], cast_expr, f"fromEnumC`{enum_name}'")

    return classify_hierarchy_arg(bare, cname, reg, letters)


def classify_hierarchy_arg(cls: str, cname: str, reg: Registries, letters) -> Marshal:
    if cls in reg.hierarchy_classes:
        argty = reg.with_argtype.get(cls)
        if argty is None:
            return Marshal(False, note=f"class '{cls}' is a bound hierarchy type but has no with{cls} in the registry -- verify it's fully bound")
        if re.match(r"^Gen\w+ \w+$", argty):
            base = argty.split()[0]
            chs_ty = f"{base} {letters.next()}"
        else:
            chs_ty = cls
        return Marshal(True, [(f"Ql{cls}*", cname)], f"*arg({cname})", f"with{cls}*`{chs_ty}'")
    if cls in reg.plain_value_classes:
        if cls not in reg.with_argtype:
            return Marshal(False, note=f"class '{cls}' is a bound plain-value type but has no with{cls} in the registry -- verify it's fully bound")
        return Marshal(True, [(f"{cls}*", cname)], f"arg({cname})", f"with{cls}*`{cls}'")
    return Marshal(False, note=f"type '{cls}' not found in either the hierarchy or plain-value registry -- bind the class first (see add-quantlib-class)")


def classify_return(type_str: str, reg: Registries) -> Marshal:
    t = strip_cv(type_str) if type_str else "void"
    if t in ("", "void"):
        return Marshal(True, c_ret_type="void", cpp_wrap="{expr};", chs_ret="`()'")
    if t in NUMERIC_DOUBLE:
        return Marshal(True, c_ret_type="double", cpp_wrap="return {expr};", chs_ret="`Double'")
    if t in NUMERIC_INT:
        return Marshal(True, c_ret_type="int", cpp_wrap="return {expr};", chs_ret="`Int'")
    if t in BOOL_TYPES:
        return Marshal(True, c_ret_type="int", cpp_wrap="return {expr};", chs_ret="`Bool'")
    if t in STRING_TYPES:
        return Marshal(True, c_ret_type="const char*", cpp_wrap="return DUP(({expr}).c_str());", chs_ret="`String'")
    if t == "Date":
        return Marshal(True, c_ret_type="int", cpp_wrap="return ({expr}).serialNumber();", chs_ret="`Day'toDay")

    tmpl = split_template(t)
    if tmpl:
        outer, inner = tmpl
        outer_bare = outer.split("::")[-1]
        if outer_bare == "optional" and inner == "bool":
            return Marshal(True, c_ret_type="int", cpp_wrap="return qlOptBool({expr});", chs_ret="`Maybe Bool'toMaybeBool")
        if outer_bare == "shared_ptr":
            cls = strip_cv(inner).split("::")[-1]
            return classify_hierarchy_return(cls, reg)
        if outer_bare == "vector":
            elem = strip_cv(inner)
            if elem in NUMERIC_DOUBLE:
                return Marshal(True, c_ret_type="void",
                                cpp_wrap="{{const std::vector<double>& _v = {expr}; *len = _v.size(); *out = qlAllocateDoubles(*len); std::copy(_v.begin(), _v.end(), *out);}}",
                                chs_ret="`()'", extra_c_out_params=[("unsigned*", "len"), ("double**", "out")],
                                chs_out_frag="preArray-`[Double]'&peekDoubleArray*")
            if elem in NUMERIC_INT:
                return Marshal(True, c_ret_type="void",
                                cpp_wrap="{{const std::vector<" + elem + ">& _v = {expr}; *len = _v.size(); *out = qlAllocateInts(*len); std::copy(_v.begin(), _v.end(), *out);}}",
                                chs_ret="`()'", extra_c_out_params=[("unsigned*", "len"), ("int**", "out")],
                                chs_out_frag="preArray-`[Int]'&peekIntArray*")
            if elem == "Date":
                return Marshal(True, c_ret_type="void",
                                cpp_wrap="{{const std::vector<Date>& _v = {expr}; *len = _v.size(); *out = qlAllocateInts(*len); for (size_t i=0;i<_v.size();++i) (*out)[i]=_v[i].serialNumber();}}",
                                chs_ret="`()'", extra_c_out_params=[("unsigned*", "len"), ("int**", "out")],
                                chs_out_frag="preArray-`[Day]'&peekDayArray*")
            return Marshal(False, note=f"vector<{elem}> return -- hasquant never marshals object vectors element-wise; only supported via an existing named alias type (e.g. Leg/CouponLeg) matching this exact vector -- check if '{t}' already has one, else needs manual handling")

    bare = t.split("::")[-1]
    enum_name = lookup_enum(t, bare, reg)
    if enum_name:
        if enum_name in reg.enum_fromEnumC and enum_name not in reg.enum_bare_ok:
            return Marshal(False, note=f"enum '{enum_name}' is only ever seen used via fromEnumC (an arg-direction-only conversion) -- its return-direction marshalling is unconfirmed, verify by hand")
        return Marshal(True, c_ret_type="int", cpp_wrap="return {expr};", chs_ret=f"`{enum_name}'")

    return classify_hierarchy_return(bare, reg)


def classify_hierarchy_return(cls: str, reg: Registries) -> Marshal:
    if cls in reg.hierarchy_classes:
        peek = reg.peek_rettype.get(cls)
        if peek is None:
            return Marshal(False, note=f"type '{cls}' has no peek{cls} -- likely a nested-ADT type (see add-quantlib-adt) not meant to be returned as a live handle; needs manual handling")
        return Marshal(True, c_ret_type=f"Ql{cls}*", cpp_wrap="return ret(new Ql" + cls + "(alloc(new " + cls + "({expr}))));", chs_ret=f"`{cls}'peek{cls}*")
    if cls in reg.plain_value_classes:
        peek = reg.peek_rettype.get(cls)
        if peek is None:
            return Marshal(False, note=f"type '{cls}' has no peek{cls} -- needs manual handling")
        return Marshal(True, c_ret_type=f"{cls}*", cpp_wrap="return ret(new " + cls + "({expr}));", chs_ret=f"`{cls}'peek{cls}*")
    return Marshal(False, note=f"return type '{cls}' not found in either registry -- bind the class first (see add-quantlib-class)")


class Letters:
    def __init__(self):
        self.used = []

    def next(self):
        letter = chr(ord('a') + len(self.used))
        self.used.append(letter)
        return letter


# --------------------------------------------------------------- render


def pascal(name: str) -> str:
    return name[0].upper() + name[1:] if name else name


def render_skip(proto: ParsedProto, reason: str) -> str:
    return f"// ---- {proto.raw} ----\n-- SKIPPED --\n{reason}\n"


def render_method(proto: ParsedProto, reg: Registries, c_name: str, overload_index: int = 0) -> str:
    letters = Letters()

    self_ctype = None
    self_cexpr_hierarchy = None
    self_chs = ""
    if not proto.is_ctor and not proto.is_static:
        if proto.cls in reg.hierarchy_classes:
            self_ctype = f"Ql{proto.cls}*"
            self_cexpr_hierarchy = True
        elif proto.cls in reg.plain_value_classes:
            self_ctype = f"{proto.cls}*"
            self_cexpr_hierarchy = False
        else:
            return None, f"receiver class '{proto.cls}' not yet bound -- run add-quantlib-class first"
        # reserve the receiver's type variable (if polymorphic) BEFORE arg letters,
        # so it reads `a`, matching a receiver-first argument list.
        argty = reg.with_argtype.get(proto.cls, proto.cls)
        if re.match(r"^Gen\w+ \w+$", argty):
            base = argty.split()[0]
            self_chs = f"with{proto.cls}*`{base} {letters.next()}'"
        else:
            self_chs = f"with{proto.cls}*`{proto.cls}'"
    elif proto.is_ctor:
        if proto.cls not in reg.hierarchy_classes and proto.cls not in reg.plain_value_classes:
            return None, f"receiver class '{proto.cls}' not yet bound -- run add-quantlib-class first"
    # else: static method -- no receiver at all, `proto.cls` is just a namespace-like
    # qualifier for the call and need not be a bound pointer type.

    arg_marshals = []
    has_default = []
    for ptype, pname, default_text in proto.params:
        m = classify_arg(ptype, pname, reg, letters)
        if not m.ok:
            return None, f"parameter '{(ptype + ' ' + (pname or '')).strip()}' -- {m.note}"
        arg_marshals.append(m)
        has_default.append((pname, default_text))

    ret_type = "" if proto.is_ctor else proto.ret_type
    if proto.is_ctor:
        # constructors always "return" the class itself
        if proto.cls in reg.hierarchy_classes:
            retm = Marshal(True, c_ret_type=f"Ql{proto.cls}*",
                            cpp_wrap="return ret(new Ql" + proto.cls + "(alloc(new " + proto.cls + "({expr}))));",
                            chs_ret=f"`{proto.cls}'peek{proto.cls}*")
        else:
            retm = Marshal(True, c_ret_type=f"{proto.cls}*",
                            cpp_wrap="return ret(new " + proto.cls + "({expr}));",
                            chs_ret=f"`{proto.cls}'peek{proto.cls}*")
    else:
        retm = classify_return(ret_type, reg)
        if not retm.ok:
            return None, f"return type '{ret_type}' -- {retm.note}"

    # ---- assemble C parameter list ----
    c_params = []
    if self_ctype is not None:
        c_params.append((self_ctype, "o"))
    for m in arg_marshals:
        c_params.extend(m.c_params)
    for ct, cn in retm.extra_c_out_params:
        c_params.append((ct, cn))
    c_params.append(("char**", "e"))

    h_params_str = ", ".join(f"{ct} {cn}" for ct, cn in c_params)
    h_decl = f"{retm.c_ret_type} {c_name}({h_params_str});"

    # ---- assemble .cpp body ----
    cpp_args = [m.cpp_expr for m in arg_marshals]
    if proto.is_ctor:
        call_expr = ", ".join(cpp_args)
    elif proto.is_static:
        call_expr = f"{proto.cls}::{proto.member}({', '.join(cpp_args)})"
    else:
        recv = f"(*arg(o))" if self_cexpr_hierarchy else "arg(o)"
        call_expr = f"{recv}->{proto.member}({', '.join(cpp_args)})"

    body_stmt = retm.cpp_wrap.format(expr=call_expr)
    err_ret = f"handleException<{retm.c_ret_type}>(e, er)" if retm.c_ret_type != "void" else "handleException<int>(e, er)"
    err_stmt = f"return {err_ret};" if retm.c_ret_type != "void" else f"(void){err_ret};"
    cpp_impl = (
        f"{retm.c_ret_type} {c_name}({h_params_str}) {{\n"
        f"  try {{{body_stmt}\n"
        f"  }} catch (std::exception& er) {{{err_stmt}}}}}\n"
    )

    # ---- assemble .chs {#fun#} line ----
    chs_args = ([self_chs] if self_chs else []) + [m.chs_frag for m in arg_marshals]
    if retm.chs_out_frag:
        chs_args.append(retm.chs_out_frag)
    chs_args.append("preErrorCheck-`String'errorCheck*-")
    hs_name = proto.member[0].lower() + proto.member[1:]
    if overload_index > 0:
        hs_name = f"{hs_name}{overload_index}"
    chs_line = f"{{#fun {c_name} as {hs_name}{{{','.join(chs_args)}}}->{retm.chs_ret}#}}"

    sibling_file = reg.chs_file_for_class.get(proto.cls, "(no existing .chs file found for this class -- pick one per add-quantlib-class)")

    notes = []
    if not proto.is_ctor and not proto.is_static:
        notes.append("-- NOTE: no `static` keyword seen -- confirmed instance method if this line came from a current dump_signatures.py run; if from the old ql-methods-1.43.txt dump, static-ness wasn't captured there and this is still just an assumption -- verify against the upstream header")
    for pname, default_text in has_default:
        if default_text is not None:
            notes.append(f"-- NOTE: parameter `{pname}` has a C++ default (= {default_text}) -- per the skill, consider wrapping it as `Maybe` (required arg here, substituting the literal default at the call site when Nothing) rather than binding it as unconditionally required")
    notes.append("-- NOTE: defaults to the throwing convention (char **e / try-catch) per the skill's safe-default rule; hand-simplify to `pure` only if you confirm this is a trivial non-throwing field access")
    notes.append(f"-- also add `{hs_name}` to the export list of {sibling_file}")

    out = [f"// ---- {proto.raw} ----"]
    out.append("-- .h --")
    out.append(h_decl)
    out.append("-- .cpp --")
    out.append(cpp_impl.rstrip("\n"))
    out.append("-- .chs --")
    out.append("-- |TODO: describe")
    out.append(chs_line)
    out.extend(notes)
    return "\n".join(out) + "\n", None


def main():
    reg = build_registries()
    lines = sys.stdin.read().splitlines()

    parsed = []
    for line in lines:
        proto, err = parse_line(line)
        if proto is None:
            if err:
                print(f"// ---- {line.strip()} ----\n-- SKIPPED --\n{err}\n")
            continue
        if proto.is_dtor:
            print(render_skip(proto, "destructor -- handled by Finalizable, not user-bindable"))
            continue
        parsed.append(proto)

    counts = {}
    for proto in parsed:
        key = (proto.cls, proto.member)
        counts[key] = counts.get(key, 0)

    for proto in parsed:
        key = (proto.cls, proto.member)
        n = counts[key]
        counts[key] = n + 1
        base_name = f"ql{proto.cls}" if proto.is_ctor else f"ql{proto.cls}{pascal(proto.member)}"
        c_name = base_name if n == 0 else f"{base_name}{n}"

        block, err = render_method(proto, reg, c_name, overload_index=n)
        if block is None:
            print(render_skip(proto, err))
        else:
            print(block)
            if n > 0:
                base_hs_name = proto.member[0].lower() + proto.member[1:]
                print(f"-- NOTE: overload #{n} -- both the C name suffix '{n}' and the Haskell name suffix on `{base_hs_name}{n}` are placeholders (input order), NOT derived from the real signature; rename each by parameter semantics (they must end up distinct or the module won't compile) and check for collisions with existing bindings\n")


if __name__ == "__main__":
    main()
