ghc-pkg unregister quantlib
call cabal configure --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.2.1 --extra-include-dirs=%DEVLIBS%/boost_1_50_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.2.1/ql/bin/8f9e26465fec6fb65803b3f74e8765a6
call cabal build
call cabal install --with-gcc=g++ --extra-include-dirs=%DEVLIBS%/QuantLib-1.2.1 --extra-include-dirs=%DEVLIBS%/boost_1_50_0 --extra-lib-dirs=%DEVLIBS%/QuantLib-1.2.1/ql/bin/8f9e26465fec6fb65803b3f74e8765a6
