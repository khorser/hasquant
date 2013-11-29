@echo off
:: compile C++ files
mkdir cobj 2>nul
mingw32-make.exe -f M EXTRA="-L%DEVLIBS%\QuantLib-1.3-noopt\ql\bin\d750f55955fa5ad66fec54f46f00c080 -isystem %DEVLIBS%\QuantLib-1.3-noopt -isystem %DEVLIBS%\boost_1_53_0 -DQLTRACK_ALLOCATIONS -g -O0 %*" dll
