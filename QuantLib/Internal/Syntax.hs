{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    args
  , ffiCall
  , ffiCallIO
  , ffiConstruct
  , ffiCallX
  , ffiCallXIO
  )
where

import Control.Monad(liftM, liftM2)
import Language.Haskell.TH
import QuantLib.Internal.Date
import QuantLib.Internal.Utils
import QuantLib.Internal.Enum

-- All QLEnum instances should be imported here!
import QuantLib.Compounding()
import QuantLib.Time.BusinessDayConvention()
import QuantLib.Time.Date()
import QuantLib.Time.DateGenerationRule()
import QuantLib.Time.Frequency()
import QuantLib.Time.Unit()

data NestedArg = DayN | DoubleN | ForeignPtrN
  deriving (Show, Eq)

-- XXX use GADTs/SYB/Uniplate?
data TopArg = IntA | WordA | DayA | StringA | DoubleA | BoolA
  | OptDayA | ForeignPtrA | OptForeignPtrA
  | ListA NestedArg | ListA2 NestedArg NestedArg
  | EnumA
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double, ''Bool]

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
nameToTop n | n == ''Bool = BoolA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop n = error $ "Not supported top type: " ++ show n

nestedNameToTop :: Name -> Q NestedArg
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
  | EnumR | OptDayR | ForeignPtrR | UnitR
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
compArgToRetVal (TupleT 0) = return UnitR
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
args (ConT n) = do
    r <- nameToRetVal n
    return ([], AtomicRV r)
args t@(AppT _ _) = do
    r <- compToRetVal t
    return ([], r)
args t = fail $ "Unsupported type: " ++ show t

-- isIO :: Type -> Q Bool
-- isIO (AppT (AppT ArrowT _) t2) = isIO t2
-- isIO (ConT _) = return False
-- isIO (AppT (ConT n1) _) = return $ n1 == ''IO
-- isIO t = fail $ "Unsupported type: " ++ show t

ffiCall :: Name -> Name -> ExpQ
ffiCall hn cn = ffiCallImpl False hn cn [|id|]

ffiCallIO :: Name -> Name -> ExpQ
ffiCallIO hn cn = ffiCallImpl True hn cn [|id|]

ffiConstruct :: Name -> Name -> ExpQ
ffiConstruct hn cn = ffiCallImpl False hn cn [|construct|]

ffiCallX :: Name -> Name -> ExpQ
ffiCallX hn cn = ffiCallImpl False hn cn [|handleExceptions|]

ffiCallXIO :: Name -> Name -> ExpQ
ffiCallXIO hn cn = ffiCallImpl True hn cn [|handleExceptions|]

ffiCallImpl :: Bool -> Name -> Name -> ExpQ -> ExpQ
ffiCallImpl io hFun cFun extra = do
  r <- reify hFun
  case r of
    VarI _ ft _ _  -> args ft >>= uncurry (genFfiCall io cFun extra)
    _ -> fail $ "Cannot reify the type of " ++ show hFun

genFfiCall :: Bool -> Name -> ExpQ -> [TopArg] -> RetVal -> ExpQ
genFfiCall io cn extra aa r = do
  cr <- reify cn
  varNames <- mapM (\_ -> newName "x") aa
  lamE (map varP varNames)
       (if io 
         then [|unsafePerformIO $(nakedCall varNames)|]
         else nakedCall varNames)
  where
    ret :: RetVal
    ret =
      case (r, io) of
        (AtomicRV _, False) -> r
        (AtomicRV a, True) -> IORV a
        (IORV _, False) -> r
        (IORV _, True) -> error "Nested IO not supported"

    nakedCall :: [Name] -> ExpQ
    nakedCall varNames = genFfiCallImpl aa (map varE varNames) (varE cn)

    genFfiCallImpl :: [TopArg] -> [ExpQ] -> ExpQ -> ExpQ
    genFfiCallImpl [] [] c_call = [|$(unmarshal ret) ($(appE extra c_call))|]

    genFfiCallImpl (IntA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call ((fromIntegral :: Int -> CInt) $v)|]

    genFfiCallImpl (BoolA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call ((fromBool :: Bool -> CInt) $v)|]

    genFfiCallImpl (DoubleA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call ((realToFrac :: Double -> CDouble) $v)|]

    genFfiCallImpl (WordA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call ((fromIntegral :: Word -> CUInt) $v)|]

    genFfiCallImpl (DayA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call (toQlDate $v)|]

    genFfiCallImpl (OptDayA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call (toQlDate $v)|]

    genFfiCallImpl (StringA:as) (v:vs) c_call =
      [|withCString $v (\y -> $(genFfiCallImpl as vs [|$c_call y|]))|]

    genFfiCallImpl (EnumA:as) (v:vs) c_call =
      genFfiCallImpl as vs [|$c_call (toQlEnum $v)|]

    genFfiCallImpl (ForeignPtrA:as) (v:vs) c_call =
      [|withObject $v (\y -> $(genFfiCallImpl as vs [|$c_call y|]))|]

    genFfiCallImpl (OptForeignPtrA:as) (v:vs) c_call =
      [|maybeWithObject $v (\y -> $(genFfiCallImpl as vs [|$c_call y|]))|]

    genFfiCallImpl (ListA DoubleN:as) (v:vs) c_call =
      [|withAmounts $v (\y1 y2 -> $(genFfiCallImpl as vs [|$c_call y1 y2|]))|]

    genFfiCallImpl (ListA ForeignPtrN:as) (v:vs) c_call =
      [|withObjects $v (\y1 y2 -> $(genFfiCallImpl as vs [|$c_call y1 y2|]))|]

    genFfiCallImpl (ListA DayN:as) (v:vs) c_call =
      [|withDays $v (\y1 y2 -> $(genFfiCallImpl as vs [|$c_call y1 y2|]))|]

    genFfiCallImpl (ListA2 _ _:_as) (_v:_vs) _c_call = error "Not supported yet"

    genFfiCallImpl (a:_) _ _ = error $ "Unsupported type " ++ show a

    genFfiCallImpl _ _ _ = error "Impossible"

unmarshal :: RetVal -> ExpQ
unmarshal (AtomicRV r) = [|$(unmarshalA r)|]
unmarshal (IORV r) = [|liftM $(unmarshalA r)|]

unmarshalA :: AtomicRet -> ExpQ
unmarshalA IntR    = [|fromIntegral :: CInt -> Int|]
unmarshalA WordR   = [|fromIntegral :: CUInt -> Word|]
unmarshalA DayR    = [|fromQlDate|]
unmarshalA DoubleR = [|realToFrac :: CDouble -> Double|]
unmarshalA StringR = [|undefined|]
unmarshalA EnumR   = [|fromQlEnum|]
unmarshalA OptDayR = [|fromQlDate|]
unmarshalA ForeignPtrR = [|id|] -- works with construct only?
unmarshalA UnitR   = [|id|]
