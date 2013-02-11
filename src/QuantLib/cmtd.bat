:: compile C++ files
mkdir cpp
mingw32-make.exe -f M EXTRA="-L%DEVLIBS%\QuantLib-1.2.1-noopt\ql\bin\d750f55955fa5ad66fec54f46f00c080 -isystem %DEVLIBS%\QuantLib-1.2.1-noopt -isystem %DEVLIBS%\boost_1_50_0 -DQLTRACK_ALLOCATIONS -g -O0" dll %*
