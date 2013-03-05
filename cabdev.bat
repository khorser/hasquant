cabaldev ghc-pkg unregister quantlib
cabaldev install --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.2.1 --extra-include-dirs=%DEVLIBS%/boost_1_50_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.2.1/ql/bin/15b474156460f41fe64f8ba9fcb070b1 qlc/
cabaldev install --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.2.1 --extra-include-dirs=%DEVLIBS%/boost_1_50_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.2.1/ql/bin/15b474156460f41fe64f8ba9fcb070b1 -f addSelfDep qlc/
set PATH=%CD%\qlc\dist\build;%PATH%
cabaldev --enable-tests quantlib/
endlocal

