:: compile C++ files
mkdir cpp
%DEVLIBS%\MinGW\bin\mingw32-make.exe -f M EXTRA="-I%DEVLIBS%\QuantLib-1.2.1 -I%DEVLIBS%\boost_1_50_0 -DQLTRACK_ALLOCATIONS"
