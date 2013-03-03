cabal-dev ghc-pkg unregister quantlib
cabal-dev install --with-cabal-install=%HOME%\.cabal-%CABALENV%\cabal_bin\cabal.exe --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.2.1 --extra-include-dirs=%DEVLIBS%/boost_1_50_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.2.1/ql/bin/15b474156460f41fe64f8ba9fcb070b1 qlc/
cabal-dev install --with-cabal-install=%HOME%\.cabal-%CABALENV%\cabal_bin\cabal.exe --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.2.1 --extra-include-dirs=%DEVLIBS%/boost_1_50_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.2.1/ql/bin/15b474156460f41fe64f8ba9fcb070b1 -f addSelfDep qlc/
set PATH=%CD%\qlc\dist\build;%PATH%
cabal-dev install --with-cabal-install=%HOME%\.cabal-%CABALENV%\cabal_bin\cabal.exe --enable-tests quantlib/
endlocal

