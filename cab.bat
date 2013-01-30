setlocal
set PATH=%CD%\qlc\dist\build;%PATH%
call cabal configure --enable-tests
call cabal build -v
call cabal test
call cabal install
endlocal
