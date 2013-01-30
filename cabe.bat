setlocal
set PATH=%CD%\qlc\dist\build;%PATH%
call cabal configure -f buildExample & call cabal build
dist\build\QL-Example\QL-Example.exe
endlocal
