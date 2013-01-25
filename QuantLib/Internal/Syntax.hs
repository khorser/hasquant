{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
where

import Language.Haskell.TH
import QuantLib.Internal.Date
import QuantLib.Internal.Utils

topLevel :: Name -> Bool
topLevel n = n `elem` [''Int, ''Word, ''Day, ''String, ''Double]

data Arg = Top Name | OptTop Name | List Name | List2 Name Name

fft :: Name -> ExpQ
fft n =
  do TyConI (TySynD _ _ (AppT (ConT p) _)) <- reify n
     return (LitE $ StringL (show $ p == ''ForeignPtr))

ffe :: Name -> ExpQ
ffe n =
  do VarI _ ft _ _ <- reify n
     let s = a ft
     return (LitE $ StringL s)

a :: Type -> String
a x = case x of
          AppT (AppT ArrowT t1) t2 -> a t1 ++ " -> " ++ a t2
          AppT ListT t1 -> "[" ++ a t1 ++ "]"
          AppT (AppT (TupleT 2) t1) t2 -> "(" ++ a t1 ++ ", " ++ a t2 ++ ")"
          AppT (AppT (AppT (TupleT 3) t1) t2) t3 -> "(" ++ a t1 ++ ", " ++ a t2 ++ ", " ++ a t3 ++ ")"
          AppT t1 t2 -> "(" ++ a t1 ++ " " ++ a t2 ++ ")"
          ConT t -> show t
          _ -> fail $ "Unsupported argument type: " ++ show x
