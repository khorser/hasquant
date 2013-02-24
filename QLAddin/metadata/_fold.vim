" fold expr for QLAddin metadata XML files
" use: set foldexpr=FoldExpr(v:lnum) foldmethod=expr
function! FoldExpr(lnum)
  let l = getline(a:lnum)
  if match(l, '^\s\+<\(Procedure\|Constructor\|Member\)') > -1
    return '>1'
  elseif match(l, '^\s\+</\(Procedure\|Constructor\|Member\)') > -1
    return '<1'
  else
    return '='
endfun

" vim: set ft=vim ts=8 sts=2 sw=2 et:

