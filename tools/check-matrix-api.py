#!/usr/bin/env python3
"""Compile public matrix accessors and require unchecked construction to fail."""

import argparse
from pathlib import Path
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project-file", default="cabal.project")
    parser.add_argument("--builddir", default="dist-newstyle")
    args = parser.parse_args()
    command = [
        "cabal", "exec", f"--project-file={args.project_file}",
        f"--builddir={args.builddir}", "--", "ghc", "-v0", "-fno-code",
        "-i", "-package", "hasquant",
    ]
    with tempfile.TemporaryDirectory(prefix="hasquant-matrix-api-") as directory:
        path = Path(directory) / "MatrixApi.hs"

        def compile_body(body):
            path.write_text("module MatrixApi where\nimport QuantLib.Math\n" + body)
            return subprocess.run(
                command + ["-outputdir", directory, str(path)],
                capture_output=True, text=True, check=False,
            )

        positive = compile_body("""
boxed :: Matrix Double -> (Word, Word, [Double])
boxed m = (matrixRows m, matrixColumns m, matrixData m)
contiguous :: RealMatrix -> (Word, Word, RealVector)
contiguous m = (realMatrixRows m, realMatrixColumns m, realMatrixData m)
""")
        if positive.returncode:
            raise SystemExit(positive.stdout + positive.stderr)
        print("PASS: all six public matrix accessors compile")

        for matrix_type, field, value in [
            ("Matrix Double", "matrixRows", "2"),
            ("Matrix Double", "matrixColumns", "2"),
            ("Matrix Double", "matrixData", "[]"),
            ("RealMatrix", "realMatrixRows", "2"),
            ("RealMatrix", "realMatrixColumns", "2"),
            ("RealMatrix", "realMatrixData", "undefined"),
        ]:
            result = compile_body(
                f"bad :: {matrix_type} -> {matrix_type}\n"
                f"bad m = m {{ {field} = {value} }}\n"
            )
            diagnostics = (result.stdout + result.stderr).lower()
            field_error = ("not a record selector" in diagnostics
                           or "not in scope: record field" in diagnostics)
            if not result.returncode or not field_error or field.lower() not in diagnostics:
                raise SystemExit(f"Unexpected result for {field}:\n{diagnostics}")
            print(f"PASS: record update through {field} is rejected")

        for constructor, data in [("Matrix", "[]"), ("RealMatrix", "undefined")]:
            result = compile_body(f"bad = {constructor} 1 1 {data}\n")
            diagnostics = (result.stdout + result.stderr).lower()
            hidden_error = ("data constructor" in diagnostics
                            or "illegal term-level use of the type constructor" in diagnostics)
            if not result.returncode or not hidden_error or constructor.lower() not in diagnostics:
                raise SystemExit(f"Unexpected result for {constructor}:\n{diagnostics}")
            print(f"PASS: {constructor} constructor is hidden")


if __name__ == "__main__":
    main()
