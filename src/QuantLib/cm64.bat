:: compile C++ files
mkdir cpp
mingw32-make.exe -f M EXTRA="-isystem %DEVLIBS%\QuantLib-1.2.1 -isystem %DEVLIBS%\boost_1_50_0 -L%DEVLIBS%\QuantLib-1.2.1\ql\bin\8f9e26465fec6fb65803b3f74e8765a6" dll %*
