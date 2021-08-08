cabal configure --enable-tests --disable-documentation --ghc-options=-dynamic && cabal build $* && cabal run hasquant_test -- --skip=LONG
