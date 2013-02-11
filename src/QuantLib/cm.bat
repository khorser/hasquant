:: compile C++ files
mkdir cpp
mingw32-make.exe -f M EXTRA="-isystem %DEVLIBS%\QuantLib-1.2.1 -isystem %DEVLIBS%\boost_1_50_0 -L%DEVLIBS%\QuantLib-1.2.1\ql\bin\15b474156460f41fe64f8ba9fcb070b1" dll %*
