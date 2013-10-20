" rename FFI C functions according to their binding
function! Subst()
  let ll = getline(1,'$')
  let new = {}
  for l in ll
    let m = matchlist(l, '^\(\k\+\) = \$(ffi\w\+ ''\1) \(c_\k\+\)$')
    if !empty(m)
      exec '%s/\<'.m[2].'\>/_c'.m[1].'/g'
    endif
  endfor
  exec '%s/\<_c/c_/g'
endfunction
" vim: set ts=8 sts=2 sw=2 et:
