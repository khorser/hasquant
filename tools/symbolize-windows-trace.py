#!/usr/bin/env python3
"""Symbolize a GHC RTS Windows crash stack trace against a Windows CI test-binary upload.

The RTS prints frames as `<path>\\hasquant_test.exe+0x<offset>`, where the offset is
an RVA. Each such frame is mapped to the nearest preceding symbol in the upload's
`hasquant_test.map` (`nm -n --demangle` output), with GHC z-encoded names decoded.
With `--exe` and an available llvm-symbolizer, C++ frames also get file:line.

Usage:
    tools/symbolize-windows-trace.py ARTIFACT_DIR [TRACE_FILE]
    tools/symbolize-windows-trace.py --map M [--exe E] [--image-base 0x...] [TRACE_FILE]

The trace is read from TRACE_FILE or stdin; paste the whole CI log if convenient.
"""

import argparse
import bisect
import os
import re
import shutil
import struct
import subprocess
import sys

FRAME_RE = re.compile(r"([^\s\\/]+\.(?:exe|dll))\+0x([0-9a-fA-F]+)")
TEXT_TYPES = set("tTwWiI")

Z_CODES = {
    "zz": "z", "ZZ": "Z", "zm": "-", "zi": ".", "zu": "_", "zd": "$", "zp": "+",
    "zl": "<", "zg": ">", "zh": "#", "ze": "=", "zv": "|", "zc": ":", "zs": "/",
    "za": "&", "zb": "!", "zn": "\\", "zq": "'", "zt": "*", "zr": "%",
    "ZL": "(", "ZR": ")", "ZM": "[", "ZN": "]", "ZC": ":", "ZS": " ",
}


def zdecode(name):
    """Decode GHC's z-encoding; leaves non-GHC (e.g. C++) names alone."""
    if re.search(r"[\s:(<]", name) or not re.search(r"zi|zm|_(?:info|closure)$", name):
        return name
    out, i = [], 0
    while i < len(name):
        pair = name[i:i + 2]
        if pair in Z_CODES:
            out.append(Z_CODES[pair])
            i += 2
            continue
        tup = re.match(r"Z(\d+)([TH])", name[i:])
        if tup:
            n = int(tup.group(1))
            out.append("(" + "," * (n - 1) + ")" if tup.group(2) == "T" else "(#" + "," * (n - 1) + "#)")
            i += tup.end()
            continue
        out.append(name[i])
        i += 1
    return "".join(out)


def read_text(path):
    raw = open(path, "rb").read()
    if raw.startswith((b"\xff\xfe", b"\xfe\xff")):
        return raw.decode("utf-16")
    return raw.decode("utf-8-sig", errors="replace")


def load_map(path):
    addrs, names, image_base = [], [], None
    for line in read_text(path).splitlines():
        parts = line.split(None, 2)
        if len(parts) < 3 or not re.fullmatch(r"[0-9a-fA-F]+", parts[0]):
            continue
        addr, kind, name = int(parts[0], 16), parts[1], parts[2]
        if name == "__ImageBase":
            image_base = addr
        if kind in TEXT_TYPES:
            addrs.append(addr)
            names.append(name)
    order = sorted(range(len(addrs)), key=addrs.__getitem__)
    return [addrs[i] for i in order], [names[i] for i in order], image_base


def pe_image_base(exe):
    with open(exe, "rb") as f:
        f.seek(0x3C)
        pe = struct.unpack("<I", f.read(4))[0]
        f.seek(pe + 24)
        magic = struct.unpack("<H", f.read(2))[0]
        if magic == 0x20B:  # PE32+
            f.seek(pe + 24 + 24)
            return struct.unpack("<Q", f.read(8))[0]
        f.seek(pe + 24 + 28)
        return struct.unpack("<I", f.read(4))[0]


def find_symbolizer():
    for cand in (os.environ.get("LLVM_SYMBOLIZER"), shutil.which("llvm-symbolizer"),
                 "/opt/homebrew/opt/llvm/bin/llvm-symbolizer", "/usr/local/opt/llvm/bin/llvm-symbolizer"):
        if cand and os.path.exists(cand):
            return cand
    return None


def line_info(symbolizer, exe, addrs):
    if not (symbolizer and exe and addrs):
        return {}
    res = subprocess.run([symbolizer, "--obj=" + exe, "--no-inlines", "--relativenames"],
                         input="\n".join(hex(a) for a in addrs) + "\n",
                         capture_output=True, text=True)
    blocks = [b.splitlines() for b in res.stdout.strip().split("\n\n")]
    info = {}
    for addr, block in zip(addrs, blocks):
        if len(block) >= 2 and not block[1].startswith("??"):
            info[addr] = block[1]
    return info


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("artifact", nargs="?", help="downloaded windows-test-bin-* directory")
    ap.add_argument("trace", nargs="?", help="file holding the stack trace (default: stdin)")
    ap.add_argument("--map", help="nm map (default: ARTIFACT/ci-bin/hasquant_test.map)")
    ap.add_argument("--exe", help="unstripped exe (default: ARTIFACT/ci-bin/unstripped/hasquant_test.exe)")
    ap.add_argument("--image-base", help="override the image base, e.g. 0x140000000")
    args = ap.parse_args()

    if args.artifact:
        root = args.artifact
        if os.path.isdir(os.path.join(root, "ci-bin")):
            root = os.path.join(root, "ci-bin")
        args.map = args.map or os.path.join(root, "hasquant_test.map")
        exe = os.path.join(root, "unstripped", "hasquant_test.exe")
        args.exe = args.exe or (exe if os.path.exists(exe) else None)
    if not args.map:
        ap.error("give ARTIFACT_DIR or --map")

    addrs, names, map_base = load_map(args.map)
    if args.image_base:
        base = int(args.image_base, 16)
    elif args.exe:
        base = pe_image_base(args.exe)
    elif map_base is not None:
        base = map_base
    else:
        base = 0x140000000
        print("warning: image base unknown, assuming 0x140000000", file=sys.stderr)

    trace = read_text(args.trace) if args.trace else sys.stdin.read()
    frames = [(m.group(1), int(m.group(2), 16)) for m in FRAME_RE.finditer(trace)]
    if not frames:
        sys.exit("no <module>+0x<offset> frames found in the trace")

    exe_addrs = [base + off for mod, off in frames if mod.lower() == "hasquant_test.exe"]
    symbolizer = find_symbolizer()
    lines = line_info(symbolizer, args.exe, exe_addrs)

    print(f"image base {base:#x}, {len(addrs)} text symbols"
          + ("" if symbolizer else " (no llvm-symbolizer: no file:line)"))
    for mod, off in frames:
        if mod.lower() != "hasquant_test.exe":
            print(f"{mod}+{off:#x}\t(other module)")
            continue
        addr = base + off
        i = bisect.bisect_right(addrs, addr) - 1
        sym = f"{zdecode(names[i])}+{addr - addrs[i]:#x}" if i >= 0 else "??"
        loc = f"\t{lines[addr]}" if addr in lines else ""
        print(f"{mod}+{off:#x}\t{sym}{loc}")


if __name__ == "__main__":
    main()
