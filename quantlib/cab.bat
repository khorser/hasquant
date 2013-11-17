@echo off
setlocal
set PATH=%CD%\..\qlc\dist\build;%PATH%
call cabal configure --enable-tests & call cabal build & call cabal test & call cabal install --haddock-html --haddock-hoogle
endlocal
