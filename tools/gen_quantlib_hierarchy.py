#!/usr/bin/env python3
"""
Generate hasquant's "live object" class-hierarchy boilerplate from a plain
indented class tree, per the add-quantlib-class / add-quantlib-adt skills.

Adding a new bound QuantLib class hierarchy touches five files with a large
amount of purely mechanical, easy-to-typo boilerplate: cbits/qlaux.h,
cbits/qlTypesC2HS.h, a cbits/*.h + *.cpp shim pair (qlFreeX finalizer +
qlXAsParent upcast), QuantLib/Internal/Type.hs (the data/newtype/AnyOf/
Finalizable/Upcastable/peek/with/as/newGen machinery), and a .chs pointer
pragma. This script emits all of that from a plain-text description of the
class tree; the actual constructor/getter bindings still need to be added
by hand (they need real QuantLib signatures and per-class judgment calls --
out of scope here).

Input (stdin): one class name per line. Leading whitespace encodes the
inheritance depth -- the literal count of leading whitespace characters is
the depth, so indentation need not be consistent between siblings (a stack-
based parent search is used, not a fixed step size). Multiple depth-0 lines
form independent hierarchies (a forest), each rendered separately but
concatenated into the same six output sections. A trailing '-' on a class
name flags it as "already bound by hand elsewhere" (or by a previous run of
this script): its exact tree position still drives its descendants' depth/
naming, but no boilerplate is emitted for the flagged class itself -- only
non-flagged classes get a full block, including the connect-to-parent code,
which always names the literal immediate parent whether or not that parent
itself is flagged.

Example:

    InterestRateIndex
     BMAIndex-
      IborIndex-
       OvernightIborIndex

generates InterestRateIndex (as a hierarchy root) and OvernightIborIndex
(including its Upcastable/qlOvernightIborIndexAsIborIndex edge, naming
IborIndex literally) -- BMAIndex and IborIndex get nothing of their own.

Usage:
    python3 tools/gen_quantlib_hierarchy.py < hierarchy.txt
"""
import sys
from dataclasses import dataclass, field


@dataclass
class Node:
    name: str
    generate: bool
    depth: int
    parent: "Node | None" = None
    children: list = field(default_factory=list)
    # computed by annotate()
    peelcount: int = 0
    root_accessor: str = ""
    root_gen_name: str = ""

    @property
    def is_root(self):
        return self.parent is None

    @property
    def is_leaf(self):
        return not self.children


def parse_tree(text):
    """Parse the indented input into a forest of Node roots."""
    roots = []
    stack = []  # list of (depth, Node)
    for raw_line in text.splitlines():
        if not raw_line.strip():
            continue
        stripped = raw_line.lstrip(" \t")
        depth = len(raw_line) - len(stripped)
        name = stripped.rstrip()
        generate = not name.endswith("-")
        if not generate:
            name = name[:-1].rstrip()
        while stack and stack[-1][0] >= depth:
            stack.pop()
        parent = stack[-1][1] if stack else None
        node = Node(name=name, generate=generate, depth=depth, parent=parent)
        if parent is None:
            roots.append(node)
        else:
            parent.children.append(node)
        stack.append((depth, node))
    return roots


def annotate(root):
    """Compute peelcount/root_accessor/root_gen_name over one tree, in place."""
    root_accessor = "get" + root.name
    root_gen_name = "Gen" + root.name

    def walk(node, peelcount):
        node.root_accessor = root_accessor
        node.root_gen_name = root_gen_name
        if node.is_root:
            node.peelcount = 0
        elif node.is_leaf:
            # unused directly; leaves reuse their parent's peelcount
            node.peelcount = node.parent.peelcount
        else:
            node.peelcount = peelcount
        next_peelcount = node.peelcount + 1 if not node.is_leaf else node.peelcount
        for child in node.children:
            walk(child, next_peelcount)

    walk(root, 0)


def flatten(root):
    """All nodes in the tree, pre-order (parent before children)."""
    out = [root]
    for child in root.children:
        out.extend(flatten(child))
    return out


def gen_alias(node):
    """The 'GenP' name a child of this node references."""
    return "Gen" + node.name


def peel_chain(n):
    return "peel . " * n


def any_of_chain(n):
    return " . ".join(["newAnyOf"] * n)


# ---------------------------------------------------------------- sections


def render_qlaux(nodes):
    gen = sorted((n for n in nodes if n.generate), key=lambda n: n.name)
    lines = []
    lines.append("namespace QuantLib {")
    for n in gen:
        lines.append(f"  class {n.name};")
    lines.append("}")
    lines.append("")
    for n in gen:
        lines.append(f"using QuantLib::{n.name};")
    lines.append("")
    for n in gen:
        lines.append(f"typedef shared_ptr<{n.name}> Ql{n.name};")
    lines.append("")
    lines.append("#ifdef QLTRACK_ALLOCATIONS")
    for n in gen:
        lines.append(
            f'template <> class ObjClassName<{n.name}*> {{public: '
            f'static void output(std::ostream& os) {{os << "{n.name}";}}}};'
        )
    lines.append("#endif")
    return "\n".join(lines)


def render_qltypesc2hs(nodes):
    gen = sorted((n for n in nodes if n.generate), key=lambda n: n.name)
    return "\n".join(f"typedef struct Ql{n.name} Ql{n.name};" for n in gen)


def render_header(nodes):
    lines = ['extern "C" {']
    for n in nodes:
        if not n.generate:
            continue
        lines.append(f"void qlFree{n.name}(Ql{n.name} *o);")
        if not n.is_root:
            p = n.parent.name
            lines.append(f"Ql{p}* ql{n.name}As{p}(Ql{n.name} *o);")
    lines.append("}")
    return "\n".join(lines)


def render_cpp(nodes):
    lines = []
    for n in nodes:
        if not n.generate:
            continue
        lines.append(f"void qlFree{n.name}(Ql{n.name} *o) {{del(o);}}")
        if not n.is_root:
            p = n.parent.name
            lines.append(
                f"Ql{p}* ql{n.name}As{p}(Ql{n.name} *o) "
                f"{{return ret(new Ql{p}(*arg(o)));}}"
            )
    return "\n".join(lines)


def render_type_hs(nodes):
    gen = [n for n in nodes if n.generate]
    lines = []

    lines.append("-- data")
    for n in gen:
        lines.append(f"data C{n.name}'")

    lines.append("")
    lines.append("-- type aliases")
    for n in gen:
        if n.is_root:
            lines.append(
                f"newtype {n.root_gen_name} a = {n.root_gen_name} "
                f"{{{n.root_accessor} :: GenForeignPtr a C{n.name}'}}"
            )
            lines.append(f"type C{n.name} = ForeignPtr C{n.name}'")
            lines.append(f"type {n.name} = {n.root_gen_name} C{n.name}")
        elif n.is_leaf:
            lines.append(f"type C{n.name} = ForeignPtr C{n.name}'")
            lines.append(f"type {n.name} = {gen_alias(n.parent)} C{n.name}")
        else:
            lines.append(
                f"type {gen_alias(n)} a = {gen_alias(n.parent)} (AnyOf C{n.name}' a)"
            )
            lines.append(f"type C{n.name} = ForeignPtr C{n.name}'")
            lines.append(f"type {n.name} = {gen_alias(n)} C{n.name}")

    lines.append("")
    lines.append("-- finalizers")
    for n in gen:
        lines.append(
            f'foreign import ccall unsafe "ql.h &qlFree{n.name}" '
            f"qlFree{n.name} :: FinalizerPtr C{n.name}'"
        )

    lines.append("")
    lines.append("-- Finalizable instances")
    for n in gen:
        lines.append(f"instance Finalizable C{n.name}' where finalize = qlFree{n.name}")

    lines.append("")
    lines.append("-- upcasts")
    for n in gen:
        if n.is_root:
            continue
        p = n.parent.name
        lines.append(
            f'foreign import ccall "ql.h ql{n.name}As{p}" ql{n.name}As{p} :: '
            f"Ptr C{n.name}' -> IO (Ptr C{p}')"
        )
        lines.append(
            f"instance Upcastable C{n.name}' where "
            f"{{type Base C{n.name}' = C{p}'; upcast = ql{n.name}As{p}}}"
        )

    lines.append("")
    lines.append("-- as/peek/with/newGen")
    for n in gen:
        if n.is_root:
            lines.append(f"as{n.name} :: {n.root_gen_name} a -> IO {n.name}")
            lines.append(f"as{n.name} = transferGenForeignPtr peek{n.name} . {n.root_accessor}")
            lines.append(
                f"with{n.name} :: {n.root_gen_name} a -> (Ptr C{n.name}' -> IO b) -> IO b"
            )
            lines.append(f"with{n.name} = withGenForeignPtr . {n.root_accessor}")
            lines.append(f"peek{n.name} :: Ptr C{n.name}' -> IO {n.name}")
            lines.append(f"peek{n.name} = {n.root_gen_name} <.> newCastForeignPtr")
        elif n.is_leaf:
            p = n.parent
            lines.append(f"peek{n.name} :: Ptr C{n.name}' -> IO {n.name}")
            if p.is_root:
                lines.append(f"peek{n.name} = {n.root_gen_name} <.> newGenForeignPtr")
                lines.append(
                    f"with{n.name} :: {n.name} -> (Ptr C{n.name}' -> IO b) -> IO b"
                )
                lines.append(f"with{n.name} = withForeignPtr . ptr . {n.root_accessor}")
            else:
                lines.append(f"peek{n.name} = newGenForeignPtr >=> newGen{p.name}")
                lines.append(
                    f"with{n.name} :: {n.name} -> (Ptr C{n.name}' -> IO b) -> IO b"
                )
                lines.append(
                    f"with{n.name} = withForeignPtr . ptr . "
                    f"{peel_chain(p.peelcount)}{n.root_accessor}"
                )
        else:
            lines.append(f"as{n.name} :: {gen_alias(n)} a -> IO {n.name}")
            lines.append(
                f"as{n.name} = transferGenForeignPtr peek{n.name} . "
                f"{peel_chain(n.peelcount)}{n.root_accessor}"
            )
            lines.append(f"peek{n.name} :: Ptr C{n.name}' -> IO {n.name}")
            lines.append(f"peek{n.name} = newCastForeignPtr >=> newGen{n.name}")
            lines.append(
                f"newGen{n.name} :: GenForeignPtr a C{n.name}' -> IO ({gen_alias(n)} a)"
            )
            lines.append(
                f"newGen{n.name} = pure . {n.root_gen_name} . {any_of_chain(n.peelcount)}"
            )
            lines.append(
                f"with{n.name} :: {gen_alias(n)} a -> (Ptr C{n.name}' -> IO b) -> IO b"
            )
            lines.append(
                f"with{n.name} = withGenForeignPtr . "
                f"{peel_chain(n.peelcount)}{n.root_accessor}"
            )
        lines.append("")
    return "\n".join(lines).rstrip("\n")


def render_chs(nodes):
    lines = []
    for n in nodes:
        if not n.generate:
            continue
        lines.append(f"{{#pointer *Ql{n.name} as {n.name} foreign -> C{n.name}' nocode#}}")
    return "\n".join(lines)


def main():
    text = sys.stdin.read()
    roots = parse_tree(text)
    all_nodes = []
    for root in roots:
        annotate(root)
        all_nodes.extend(flatten(root))

    sections = [
        ("qlaux.h", render_qlaux(all_nodes)),
        ("qlTypesC2HS.h", render_qltypesc2hs(all_nodes)),
        ("*.h", render_header(all_nodes)),
        ("*.cpp", render_cpp(all_nodes)),
        ("Internal/Type.hs", render_type_hs(all_nodes)),
        ("*.chs", render_chs(all_nodes)),
    ]
    for title, body in sections:
        print(f"-- {title} --")
        print(body)


if __name__ == "__main__":
    main()
