" settings for the Proj plugin
let g:ghcmod_ghc_options = ['-Lsrc/QuantLib', '-lql']
set path+=../../../qlc/cbits,**,../../test/**,..
set wildignore+=*.o,*.obj,*.hi

command -nargs=1 Cgrep vimgrep <args> ../../../qlc/cbits/*.cpp ../../../qlc/cbits/*.h
command -nargs=1 Hgrep vimgrep <args> **/*.hs
command -nargs=1 Tgrep vimgrep <args> ../../test/**/*.hs

command -nargs=1 Qlgrep vimgrep <args> /build/quantlib/QuantLib/ql/**/*.hpp
command -nargs=1 Qlcgrep vimgrep <args> /build/quantlib/QuantLib/ql/**/*.cpp
command -nargs=1 Qltag :new<bar>:lcd /build/quantlib/QuantLib/ql<bar>tjump <args>

NeoComplCacheEnable

function g:NecoghcExtraBrowseOptions(mod)
  if a:mod =~ '^QuantLib'
    return ['-g', expand('-L$PROJECT_ROOT/hasquant/quantlib/src/QuantLib'), '-g', '-lql']
  else
    return []
  endif
endfunction

command H compiler ghc<bar>set makeprg=./h<bar>make
command C compiler gcc<bar>set makeprg=./cm<bar>make

so ~/.vim/plugin_lazy/haskellFold.vim

" vim: set ft=vim ts=8 sts=2 sw=2 et:
