:: compile C++ files
mkdir cpp
%DEVLIBS%\MinGW\bin\mingw32-make.exe -f M EXTRA="-lstdc++ -L%DEVLIBS%\QuantLib-1.2.1-noopt\ql\bin\d750f55955fa5ad66fec54f46f00c080 -I%DEVLIBS%\QuantLib-1.2.1-noopt -I%DEVLIBS%\boost_1_50_0 -DQLTRACK_ALLOCATIONS -g -O0" %*
