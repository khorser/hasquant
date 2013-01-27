{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    args
  , ffiCall
  )
where

import Control.Monad(liftM, liftM2)
import Language.Haskell.TH
import QuantLib.Internal.Date
import QuantLib.Internal.Utils
import QuantLib.Internal.Enum(QLEnum)

-- All QLEnum instances should be imported here!
import QuantLib.Compounding()
import QuantLib.Time.BusinessDayConvention()
import QuantLib.Time.Date()
import QuantLib.Time.DateGenerationRule()
import QuantLib.Time.Frequency()
import QuantLib.Time.Unit()

data NestedArg = IntN | DayN | DoubleN | ForeignPtrN
  deriving (Show, Eq)

-- XXX use GADTs/SYB/Uniplate?
data TopArg = IntA | WordA | DayA | StringA | DoubleA
  | OptDayA | ForeignPtrA | OptForeignPtrA
  | ListA NestedArg | ListA2 NestedArg NestedArg
  | EnumA
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double]

isEnum :: Name -> Q Bool
isEnum n = do
  ClassI _ instances <- reify ''QLEnum
  return $ n `elem` map getEnumTypeName instances
  where getEnumTypeName (InstanceD [] (AppT _ (ConT x)) []) = x
        getEnumTypeName x = error $ "Error getting QLEnum instances: " ++ show x

nameToTop :: Name -> TopArg
nameToTop n | n == ''Int = IntA
nameToTop n | n == ''Word = WordA
nameToTop n | n == ''Day = DayA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop n = error $ "Not supported top type: " ++ show n

nestedNameToTop :: Name -> Q NestedArg
nestedNameToTop n | n == ''Int = return IntN
nestedNameToTop n | n == ''Day = return DayN
nestedNameToTop n | n == ''Double = return DoubleN
nestedNameToTop n =
  tryForeignPtr n >>=
    either (\x -> fail $ "Error parsing nested arg" ++ show x)
      (\_ -> return ForeignPtrN)

topArgs :: Type -> Q TopArg
topArgs (ConT n) | isAtomicTop n = return $ nameToTop n
topArgs (ConT n) = do
  e <- isEnum n
  if e
    then return EnumA
    else tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing top arg: " ++ x)
          (\_ -> return ForeignPtrA)
topArgs (AppT (ConT m) (ConT n)) | m == ''Maybe =
  if n == ''Day
    then return OptDayA
  else
    tryForeignPtr n >>=
      either (\x -> fail $ "Error parsing optional top arg: " ++ x)
        (\_ -> return OptForeignPtrA)
topArgs (AppT ListT (ConT n)) = liftM ListA (nestedNameToTop n)
topArgs (AppT
          ListT
          (AppT
            (AppT (TupleT 2) (ConT n1))
            (ConT n2))) =
              liftM2 ListA2 (nestedNameToTop n1) (nestedNameToTop n2)
topArgs t = fail $ "Unsupported top-level arg type: " ++ show t

data AtomicRet = IntR | WordR | DayR | DoubleR | StringR
  | EnumR | OptDayR | ForeignPtrR
  deriving (Show, Eq)

data RetVal = AtomicRV AtomicRet | IORV AtomicRet
  deriving (Show, Eq)

tryForeignPtr :: Name -> Q (Either String Name)
tryForeignPtr n = do
  r <- reify n
  return $
    case r of
      TyConI (TySynD _ [] (AppT (ConT p) (ConT target)))
        -> if p == ''ForeignPtr
             then Right target
             else Left $ "Unsupported synonym type: " ++ show n
                ++ " reified as " ++ show r
      _ -> Left $ "Unsupported type: " ++ show n ++ " reified as "
              ++ show r

nameToRetVal :: Name -> Q AtomicRet
nameToRetVal n | n == ''Int = return IntR
nameToRetVal n | n == ''Word = return WordR
nameToRetVal n | n == ''Day = return DayR
nameToRetVal n | n == ''Double = return DoubleR
nameToRetVal n | n == ''String = return StringR
nameToRetVal n = do
  e <- isEnum n
  if e
    then return EnumR
    else tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing ret type: " ++ x)
            (\_ -> return ForeignPtrR)

compArgToRetVal :: Type -> Q AtomicRet
compArgToRetVal (AppT (ConT m) (ConT d)) | m == ''Maybe && d == ''Day =
  return OptDayR
compArgToRetVal (ConT n) = nameToRetVal n
compArgToRetVal t = fail $ "Unsupported compound type arg: " ++ show t

compToRetVal :: Type -> Q RetVal
compToRetVal (AppT (ConT n1) t2) | n1 == ''IO =
  liftM IORV $ compArgToRetVal t2
compToRetVal t = liftM AtomicRV $ compArgToRetVal t

-- use WriterT?
args :: Type -> Q ([TopArg], RetVal)
args (AppT (AppT ArrowT t1) t2) = do
  top <- topArgs t1
  (rest, ret) <- args t2
  return (top : rest, ret)
args (ConT n) = liftM ((,) [] . AtomicRV) $ nameToRetVal n
args t@(AppT _ _) = liftM ((,) []) $ compToRetVal t 
args t = fail $ "Unsupported type: " ++ show t

ffiCall :: Name -> ExpQ
ffiCall n = do
  r <- reify n
  case r of
    VarI _ ft _ _  -> args ft >>= uncurry genFfiCall
    _ -> fail $ "Cannot reify type of: " ++ show n

genFfiCall :: [TopArg] -> RetVal -> ExpQ
genFfiCall a r = stringE $ show (a, r)
