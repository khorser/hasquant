@echo off
setlocal
set PATH=%CD%\..\qlc\dist\build;%PATH%
:: tests fail to build under Win64. See more info in the cabal file
call cabal configure & call cabal build & call cabal install --haddock-html --haddock-hoogle
endlocal
