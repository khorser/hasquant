#for f in ql/**/*.hpp ; do pixi run python dump_signatures.py $f \
#  -target $(clang -dumpmachine) \
#  -isysroot $(xcrun --show-sdk-path) \
#  -resource-dir $(clang -print-resource-dir) \
#  -I/opt/homebrew/include > ${f/.hpp/.txt} ; done

#for f in ql-types/**/*.txt; do awk '{print FILENAME "|" $0}' $f ; done > ql-methods.txt
import sys
import clang.cindex

def get_type_spelling(type_obj):
    """Возвращает адекватное текстовое представление типа."""
    spelling = type_obj.spelling
    if not spelling:
        spelling = type_obj.get_canonical().spelling
    return spelling

def print_prototypes(node, current_class=""):
    if node.kind in (clang.cindex.CursorKind.CLASS_DECL, 
                     clang.cindex.CursorKind.STRUCT_DECL,
                     clang.cindex.CursorKind.CLASS_TEMPLATE):
        if node.is_definition():
            current_class = node.spelling
            for child in node.get_children():
                print_prototypes(child, current_class)
        return

    if node.kind in (clang.cindex.CursorKind.CXX_METHOD, 
                     clang.cindex.CursorKind.CONSTRUCTOR, 
                     clang.cindex.CursorKind.DESTRUCTOR,
                     clang.cindex.CursorKind.FUNCTION_DECL,
                     clang.cindex.CursorKind.FUNCTION_TEMPLATE):
        
        if not node.location.file or not node.location.file.name.endswith(sys.argv[1]):
            return

        is_constructor = (node.kind == clang.cindex.CursorKind.CONSTRUCTOR)
        ret_type = "" if is_constructor else get_type_spelling(node.result_type)
        
        args = []
        for arg in node.get_arguments():
            arg_type = get_type_spelling(arg.type)
            arg_name = arg.spelling
            args.append(f"{arg_type} {arg_name}".strip())
            
        args_str = ", ".join(args)
        class_prefix = f"{current_class}::" if current_class else ""
        const_prefix = " const" if node.is_const_method() else ""

        if ret_type:
            print(f"{ret_type} {class_prefix}{node.spelling}({args_str}){const_prefix};")
        else:
            print(f"{class_prefix}{node.spelling}({args_str}){const_prefix};")

    for child in node.get_children():
        print_prototypes(child, current_class)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python dump_signatures.py <header_file.h> [clang args...]")
        sys.exit(1)

    index = clang.cindex.Index.create()
    
    clang_args = ['-x', 'c++', '-std=c++20'] + sys.argv[2:]
    
    tu = index.parse(sys.argv[1], args=clang_args)
    
    for diag in tu.diagnostics:
        if diag.severity >= clang.cindex.Diagnostic.Error:
            sys.stderr.write(f"Clang Parse Error: {diag.spelling}\n")

    print_prototypes(tu.cursor)
