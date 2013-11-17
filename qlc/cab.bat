ghc-pkg unregister quantlib
call cabal configure --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.3 --extra-include-dirs=%DEVLIBS%/boost_1_53_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.3/ql/bin/15b474156460f41fe64f8ba9fcb070b1
call cabal build
call cabal install --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.3 --extra-include-dirs=%DEVLIBS%/boost_1_53_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.3/ql/bin/15b474156460f41fe64f8ba9fcb070b1 --haddock-html --haddock-hoogle
