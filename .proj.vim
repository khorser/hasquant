" settings for the Proj plugin
let g:ghcmod_ghc_options = ['-Lsrc/QuantLib', '-lql']
set path+=../../../qlc/cpp,**,../../test/**
set wildignore+=*.o,*.obj,*.hi

command -nargs=1 Cgrep vimgrep <args> ../../../qlc/cpp/*.cpp ../../../qlc/cpp/*.h
command -nargs=1 Hgrep vimgrep <args> **/*.hs
command -nargs=1 Tgrep vimgrep <args> ../../test/**/*.hs

command -nargs=1 Qgrep vimgrep <args> /build/quantlib/QuantLib/ql/**/*.hpp
command -nargs=1 QCgrep vimgrep <args> /build/quantlib/QuantLib/ql/**/*.cpp
command -nargs=1 Qtag :new<bar>:lcd /build/quantlib/QuantLib/ql<bar>tjump <args>

NeoComplCacheEnable
compiler ghc
set makeprg=h
" TODO add something for CPP files

" vim: set ft=vim ts=8 sts=2 sw=2 et:
