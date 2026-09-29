#!/bin/sh
cabal build all --enable-tests "$@" && cabal run hasquant_test --enable-tests "$@" -- --skip=LONG
