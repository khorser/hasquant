#for f in ql/**/*.hpp ; do pixi run python dump_signatures.py $f \
#  -I/opt/homebrew/include ; done > ql-methods.txt

import sys
import subprocess
import clang.cindex

HEADER_FIELD = ""

def get_mac_clang_args():
    try:
        sdk_path = subprocess.check_output(['xcrun', '--show-sdk-path'], text=True).strip()
        target = subprocess.check_output(['clang', '-dumpmachine'], text=True).strip()
        resource_dir = subprocess.check_output(['clang', '-print-resource-dir'], text=True).strip()

        return [
            '-x', 'c++',
            '-std=c++20',
            '-target', target,
            '-isysroot', sdk_path,
            '-resource-dir', resource_dir,
            f'-I{sdk_path}/usr/include',
            f'-I{sdk_path}/usr/include/c++/v1'
        ]
    except Exception as e:
        sys.stderr.write(f"Warning: Failed to auto-detect macOS SDK paths: {e}\n")
        return ['-x', 'c++', '-std=c++20']

def is_deprecated(node):
    for child in node.get_children():
        if child.kind.is_attribute():
            if "deprecated" in child.spelling.lower() or "deprecated" in child.kind.name.lower():
                return True
    return False

def get_base_classes(class_cursor):
    bases = []
    for child in class_cursor.get_children():
        if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
            base_decl = child.type.get_declaration()
            if base_decl and base_decl.is_definition():
                bases.append(base_decl)
    return bases

def get_all_ancestor_method_signatures(class_cursor, visited=None):
    """visited guards against infinite recursion on CRTP-style hierarchies
    (e.g. `class Derived : public Base<Derived>`), where a naive walk of
    base classes never terminates."""
    if visited is None:
        visited = set()
    ancestor_methods = set()

    for base in get_base_classes(class_cursor):
        usr = base.get_usr()
        if usr in visited:
            continue
        visited.add(usr)

        for child in base.get_children():
            if child.kind == clang.cindex.CursorKind.CXX_METHOD:
                args_types = ", ".join([arg.type.spelling for arg in child.get_arguments()])
                sig_key = f"{child.spelling}({args_types})"
                ancestor_methods.add(sig_key)

        ancestor_methods.update(get_all_ancestor_method_signatures(base, visited))

    return ancestor_methods

def has_overridden_methods(node):
    try:
        overridden = list(node.get_overridden_cursors())
        return len(overridden) > 0
    except (AttributeError, TypeError):
        return False

def join_tokens(tokens):
    """Best-effort reassembly of a default-value expression from its tokens."""
    no_space_before = {"(", ")", ",", "::", "<", ">", ";", ".", "->"}
    no_space_after = {"(", "::", "<", ".", "->"}
    out = []
    for i, t in enumerate(tokens):
        if i > 0 and t not in no_space_before and tokens[i - 1] not in no_space_after:
            out.append(" ")
        out.append(t)
    return "".join(out)

def format_arg(arg):
    """'Type name' or 'Type name = default' if the parameter has a default value."""
    base = f"{arg.type.spelling} {arg.spelling}".strip()
    tokens = [t.spelling for t in arg.get_tokens()]
    try:
        eq = tokens.index("=")
    except ValueError:
        return base
    return f"{base} = {join_tokens(tokens[eq + 1:])}"

def print_filtered_prototypes(node, current_class_cursor=None):
    if node.kind in (clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL,
                     clang.cindex.CursorKind.CLASS_TEMPLATE):
        if is_deprecated(node):
            return

        if node.is_definition():
            for child in node.get_children():
                print_filtered_prototypes(child, current_class_cursor=node)
            return

    if node.kind in (clang.cindex.CursorKind.CXX_METHOD, 
                     clang.cindex.CursorKind.CONSTRUCTOR, 
                     clang.cindex.CursorKind.FUNCTION_DECL):
        
        current_class_name = current_class_cursor.spelling if current_class_cursor else ""

        if current_class_cursor and node.access_specifier != clang.cindex.AccessSpecifier.PUBLIC:
            return

        if is_deprecated(node):
            return

        if current_class_cursor:
            if has_overridden_methods(node):
                return

            args_types = ", ".join([arg.type.spelling for arg in node.get_arguments()])
            current_sig_key = f"{node.spelling}({args_types})"
            
            ancestor_signatures = get_all_ancestor_method_signatures(current_class_cursor)
            if current_sig_key in ancestor_signatures:
                return  # Метод уже есть у родителя

        if not node.location.file or not node.location.file.name.endswith(sys.argv[1]):
            return

        ret_type = node.result_type.spelling if node.kind != clang.cindex.CursorKind.CONSTRUCTOR else ""
        args = [format_arg(arg) for arg in node.get_arguments()]
        args_str = ", ".join(args)

        class_prefix = f"{current_class_name}::" if current_class_name else ""
        const_prefix = " const" if node.is_const_method() else ""
        static_prefix = "static " if node.kind == clang.cindex.CursorKind.CXX_METHOD and node.is_static_method() else ""

        if ret_type:
            print(f"{HEADER_FIELD}|{static_prefix}{ret_type} {class_prefix}{node.spelling}({args_str}){const_prefix};")
        else:
            print(f"{HEADER_FIELD}|{static_prefix}{class_prefix}{node.spelling}({args_str}){const_prefix};")

    for child in node.get_children():
        print_filtered_prototypes(child, current_class_cursor)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python dump_signatures.py <header_file.h> [clang args...]")
        sys.exit(1)

    HEADER_FIELD = sys.argv[1]

    index = clang.cindex.Index.create()
    clang_args = get_mac_clang_args() + sys.argv[2:]
    tu = index.parse(sys.argv[1], args=clang_args)

    for diag in tu.diagnostics:
        if diag.severity >= clang.cindex.Diagnostic.Error:
            sys.stderr.write(f"Clang Parse Error: {diag.spelling}\n")

    print_filtered_prototypes(tu.cursor)
