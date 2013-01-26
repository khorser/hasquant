{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
where

import Control.Monad(liftM)
import Language.Haskell.TH
import QuantLib.Internal.Date
import QuantLib.Internal.Utils

data NestedArg = IntN | DayN | DoubleN | ForeignPtrN
  deriving (Show, Eq)

data TopArg = IntA | WordA | DayA | StringA | DoubleA
  | OptDayA | ForeignPtrA | OptForeignPtrA
  | List NestedArg | List2 NestedArg NestedArg
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double]

data AtomicRet = IntR | WordR | DayR | DoubleR | OptDayR | ForeignPtrR
  deriving (Show, Eq)

data RetVal = AtomicRV AtomicRet | IORV AtomicRet
  deriving (Show, Eq)

nameToTop :: Name -> TopArg
nameToTop n | n == ''Int = IntA
nameToTop n | n == ''Word = WordA
nameToTop n | n == ''Day = DayA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop _ = error "Not supported yet"

topArgs :: Type -> Q TopArg
topArgs (ConT n) | isAtomicTop n = return $ nameToTop n
topArgs t = fail $ "Unsupported top-level arg type: " ++ show t

nameToRetVal :: Name -> Q AtomicRet
nameToRetVal n | n == ''Int = return IntR
nameToRetVal n | n == ''Word = return WordR
nameToRetVal n | n == ''Day = return DayR
nameToRetVal n | n == ''Double = return DoubleR
nameToRetVal n = do
  r <- reify n
  case r of
    TyConI (TySynD _ _ (AppT (ConT p) _))
      -> if p == ''ForeignPtr
           then return ForeignPtrR
           else fail $ "Unsupported synonym type: " ++ show r
    _ -> fail $ "Unsupported return type: " ++ show r

compArgToRetVal :: Type -> Q AtomicRet
compArgToRetVal (AppT (ConT m) (ConT d)) | m == ''Maybe && d == ''Day =
  return OptDayR
compArgToRetVal (ConT n) = nameToRetVal n
compArgToRetVal t = fail $ "Unsupported compound type arg: " ++ show t

compToRetVal :: Type -> Q RetVal
compToRetVal (AppT (ConT n1) t2) | n1 == ''IO = do
  r <- compArgToRetVal t2
  return $ IORV r
compToRetVal t = liftM AtomicRV $ compArgToRetVal t

-- use WriterT?
args :: Type -> Q ([TopArg], RetVal)
args (AppT (AppT ArrowT t1) t2) = do
  top <- topArgs t1
  (rest, ret) <- args t2
  return (top : rest, ret)
args (ConT n) = do
  r <- nameToRetVal n
  return ([], AtomicRV r)
args t@(AppT _ _) = do
  r <- compToRetVal t 
  return ([], r)
args t = fail $ "Unsupported type: " ++ show t

ffe :: Name -> ExpQ
ffe n = do
  VarI _ ft _ _ <- reify n
  s <- args ft
  return (LitE $ StringL (show s))

-- fft :: Name -> ExpQ
-- fft n =
--   do TyConI (TySynD _ _ (AppT (ConT p) _)) <- reify n
--      return (LitE $ StringL (show $ p == ''ForeignPtr))
-- 
-- ffe :: Name -> ExpQ
-- ffe n =
--   do VarI _ ft _ _ <- reify n
--      let s = a ft
--      return (LitE $ StringL s)
-- 
-- a :: Type -> String
-- a x = case x of
--           AppT (AppT ArrowT t1) t2 -> a t1 ++ " -> " ++ a t2
--           AppT ListT t1 -> "[" ++ a t1 ++ "]"
--           AppT (AppT (TupleT 2) t1) t2 -> "(" ++ a t1 ++ ", " ++ a t2 ++ ")"
--           AppT (AppT (AppT (TupleT 3) t1) t2) t3 -> "(" ++ a t1 ++ ", " ++ a t2 ++ ", " ++ a t3 ++ ")"
--           AppT t1 t2 -> "(" ++ a t1 ++ " " ++ a t2 ++ ")"
--           ConT t -> show t
--           _ -> fail $ "Unsupported argument type: " ++ show x
