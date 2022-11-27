module QuantLib.Syntax
  (
    free1st
  , free2nd
  , free1st'
  , free2nd'
  , freeNth
  , freeNth'
  )
where

import Control.Monad(replicateM)
import Language.Haskell.TH

-- |make a function with the first argument put at the last position, sort of any arity flip to make it easier to chain monadic calls
free1st :: Name -> ExpQ
free1st = freeNth 1

free2nd :: Name -> ExpQ
free2nd = freeNth 2

-- |make a function with the first argument put at the last position with user supplied arity
free1st' :: Int -> ExpQ
free1st' = freeNth' 1

free2nd' :: Int -> ExpQ
free2nd' = freeNth' 2

genFreeNth :: Int -> Int -> Name -> ExpQ
genFreeNth i an fn = do
  vars <- replicateM an (newName "x")
  let (h, t) = splitAt i $ reverse vars
      (hh, ht) = splitAt (i-1) h
  return $ LamE (map VarP (hh ++ t ++ ht)) (foldr (\v e -> AppE e (VarE v)) (VarE fn) vars)

freeNth :: Int -> Name -> ExpQ
freeNth i n = do
  VarI _ as _ <- reify n
  genFreeNth i (arity as) n
  where
    arity as = arity' as
      where
        arity' (AppT (AppT ArrowT _) x) = 1 + arity' x
        arity' (ForallT _ _ a@(AppT _ _)) = arity' a
        arity' (AppT _ _) = 0
        arity' x = error $ "Unsupported signature part: " ++ show x ++ ", full arguments: " ++ show as

freeNth' :: Int -> Int -> ExpQ
freeNth' i an = do
  n <- newName "f"
  LamE [VarP n] <$> genFreeNth i an n

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
