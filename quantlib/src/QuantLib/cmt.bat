@echo off
:: compile C++ files
mingw32-make.exe -f M EXTRA="-L%DEVLIBS%\QuantLib-1.3\ql\bin\15b474156460f41fe64f8ba9fcb070b1 -isystem %DEVLIBS%\QuantLib-1.3 -isystem %DEVLIBS%\boost_1_53_0 -DQLTRACK_ALLOCATIONS %*" libql.dll
