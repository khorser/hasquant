# pixi run python dump_inheritance.py /opt/homebrew/include/ql/termstructures/yieldtermstructure.hpp -I/opt/homebrew/include
import sys
import subprocess
import clang.cindex

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

def dump_inheritance(node, target_file, visited_classes=None):
    if visited_classes is None:
        visited_classes = set()

    if node.kind in (clang.cindex.CursorKind.CLASS_DECL, 
                     clang.cindex.CursorKind.STRUCT_DECL,
                     clang.cindex.CursorKind.CLASS_TEMPLATE):
        
        if node.is_definition():
            class_name = node.spelling
            
            if node.location.file and node.location.file.name.endswith(target_file):
                if class_name and class_name not in visited_classes:
                    visited_classes.add(class_name)
                    
                    parents = []
                    for child in node.get_children():
                        if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                            # Извлекаем тип базового класса
                            base_type = child.type.get_canonical().spelling
                            # Если хотим чистые имена без 'class ' или 'struct ':
                            base_name = child.type.spelling or child.spelling
                            parents.append(base_name)
                    
                    if parents:
                        print(f"{class_name}:{','.join(parents)}")
                    else:
                        print(f"{class_name}:")

    for child in node.get_children():
        dump_inheritance(child, target_file, visited_classes)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python dump_inheritance.py <header_file.h> [clang args...]")
        sys.exit(1)

    target_header = sys.argv[1]
    index = clang.cindex.Index.create()
    
    clang_args = get_mac_clang_args() + sys.argv[2:]
    tu = index.parse(target_header, args=clang_args)

    # Выводим ошибки парсинга, если они есть
    for diag in tu.diagnostics:
        if diag.severity >= clang.cindex.Diagnostic.Error:
            sys.stderr.write(f"Clang Parse Error: {diag.spelling}\n")

    dump_inheritance(tu.cursor, target_header)
