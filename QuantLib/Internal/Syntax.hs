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
  | ListA NestedArg | ListA2 NestedArg NestedArg
  -- TODO enum
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double]

nameToTop :: Name -> TopArg
nameToTop n | n == ''Int = IntA
nameToTop n | n == ''Word = WordA
nameToTop n | n == ''Day = DayA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop _ = error "Not supported yet"

nestedNameToTop :: Name -> NestedArg
nestedNameToTop n | n == ''Int = IntN
nestedNameToTop n | n == ''Day = DayN
nestedNameToTop n | n == ''Double = DoubleN
-- TODO ForeignPtr
nestedNameToTop _ = error "Not supported yet"

topArgs :: Type -> Q TopArg
topArgs (ConT n) | isAtomicTop n = return $ nameToTop n
topArgs (ConT n) = do
  r <- reify n
  case r of
    TyConI (TySynD _ _ (AppT (ConT p) _))
      -> if p == ''ForeignPtr
           then return ForeignPtrA
           else fail $ "Unsupported top arg synonym type: "
            ++ show n ++ " reified as " ++ show r
    _ -> fail $ "Unsupported top arg type: " ++ show n
            ++ " reified as " ++ show r
topArgs (AppT (ConT m) (ConT n)) | m == ''Maybe =
  if n == ''Day
    then return OptDayA
  else do
    r <- reify n
    case r of
      TyConI (TySynD _ _ (AppT (ConT p) _))
        -> if p == ''ForeignPtr
             then return OptForeignPtrA
             else fail $ "Unsupported optional top arg synonym type: "
              ++ show n ++ " reified as " ++ show r
      _ -> fail $ "Unsupported optional top arg type: " ++ show n
              ++ " reified as " ++ show r
topArgs (AppT ListT (ConT n)) = return $ ListA (nestedNameToTop n)
topArgs (AppT
          ListT
          (AppT
            (AppT
              (TupleT 2)
              (ConT n1))
            (ConT n2))) = return $ ListA2 (nestedNameToTop n1) (nestedNameToTop n2)
topArgs t = fail $ "Unsupported top-level arg type: " ++ show t

data AtomicRet = IntR | WordR | DayR | DoubleR | StringR
  | OptDayR | ForeignPtrR
  deriving (Show, Eq)

data RetVal = AtomicRV AtomicRet | IORV AtomicRet
  deriving (Show, Eq)

nameToRetVal :: Name -> Q AtomicRet
nameToRetVal n | n == ''Int = return IntR
nameToRetVal n | n == ''Word = return WordR
nameToRetVal n | n == ''Day = return DayR
nameToRetVal n | n == ''Double = return DoubleR
nameToRetVal n | n == ''String = return StringR
nameToRetVal n = do
  r <- reify n
  case r of
    TyConI (TySynD _ _ (AppT (ConT p) _))
      -> if p == ''ForeignPtr
           then return ForeignPtrR
           else fail $ "Unsupported return synonym type: " ++ show n
            ++ " reified as " ++ show r
    _ -> fail $ "Unsupported return type: " ++ show n ++ " reified as "
            ++ show r

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
