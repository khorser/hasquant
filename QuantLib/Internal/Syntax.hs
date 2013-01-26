{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
where

import Language.Haskell.TH
import QuantLib.Internal.Date
import QuantLib.Internal.Utils

data NestedArg = IntN | DayN | DoubleN | ForeignPtrN

data TopArg = IntA | WordA | DayA | StringA | DoubleA
  | OptDayA | ForeignPtrA | OptForeignPtrA
  | List NestedArg | List2 NestedArg NestedArg

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double]

data RetVal = IntR | DayR | StringR | DoubleR
  | OptDayR | ForeignPtrR | IOR RetVal

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

nameToRetVal :: Name -> RetVal
nameToRetVal n | n == ''Int = IntR
nameToRetVal n | n == ''Day = DayR
nameToRetVal n | n == ''String = StringR
nameToRetVal n | n == ''Double = DoubleR
nameToRetVal n = error $ "Return type not supported: " ++ show n

compToRetVal :: Name -> Type -> RetVal
--compToRetVal n1 _ | n1 == ''ForeignPtr = ForeignPtrR -- won't work until the type if reified!
--compToRetVal n1 n2 | n1 == ''Maybe && n2 == ''Day = OptDayR
compToRetVal n1 t2 | n1 == ''IO = undefined
compToRetVal n1 n2 = error $ "Compound return type not supported: " ++ show n1 ++ " " ++ show n2

-- use WriterT?
args :: Type -> Q ([TopArg], RetVal)
args (AppT (AppT ArrowT t1) t2) = do
  top <- topArgs t1
  (rest, ret) <- args t2
  return (top : rest, ret)
args (ConT n) = return ([], nameToRetVal n)
args (AppT (ConT n1) t2) = return ([], compToRetVal n1 t2)
args t = fail $ "Unsupported type: " ++ show t

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
