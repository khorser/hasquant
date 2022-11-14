module QuantLib.Syntax
  (
    free1st
  )
where

import Control.Monad(replicateM)
import Language.Haskell.TH

-- |make a function with the first argument put at the last position, sort of any arity flip to make it easier to chain calls
free1st :: Name -> ExpQ
free1st n = do
  VarI fn as _ <- reify n
  let an = arity as
  vars <- replicateM an (newName "x")
  let vd = reverse vars
  return $ LamE (map VarP (tail vd ++ [head vd])) (foldr (\v e -> AppE e (VarE v)) (VarE fn) vars)
  where
    arity as = arity' as
      where
        arity' (AppT (AppT ArrowT _) x) = 1 + arity' x
        arity' (ForallT _ _ a@(AppT _ _)) = arity' a
        arity' (AppT _ _) = 0
        arity' x = error $ "Unsupported signature part: " ++ show x ++ ", full arguments: " ++ show as

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
