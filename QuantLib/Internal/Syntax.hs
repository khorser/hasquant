{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    args
  , ffiCall
  , ffiCallConstruct
  , ffiCallHandleX
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

data NestedArg = IntN | DayN | DoubleN | ForeignPtrN
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

isIO :: Type -> Q Bool
isIO (AppT (AppT ArrowT _) t2) = isIO t2
isIO (ConT _) = return False
isIO (AppT (ConT n1) _) = return $ n1 == ''IO
isIO t = fail $ "Unsupported type: " ++ show t

ffiCall :: Name -> Name -> ExpQ
ffiCall hn cn = ffiCallImpl hn cn [|id|]

ffiCallConstruct :: Name -> Name -> ExpQ
ffiCallConstruct hn cn = ffiCallImpl hn cn [|construct|]

ffiCallHandleX :: Name -> Name -> ExpQ
ffiCallHandleX hn cn = ffiCallImpl hn cn [|handleExceptions|]

ffiCallImpl :: Name -> Name -> ExpQ -> ExpQ
ffiCallImpl hFun cFun extra = do
  r <- reify hFun
  case r of
    VarI _ ft _ _  -> args ft >>= uncurry (genFfiCall cFun extra)
    _ -> fail $ "Cannot reify the type of " ++ show hFun

genFfiCall :: Name -> ExpQ -> [TopArg] -> RetVal -> ExpQ
genFfiCall cn extra aa r = do
  cr <- reify cn
  isio <- case cr of
            VarI _ ft _ _  -> isIO ft
            _ -> fail $ "Cannot detect return type of C function" ++ show cn
  let doIO = isio &&
    -- C function runs in IO but Haskell function does not
    -- unsafePerformIO is needed
        (case r of
          AtomicRV _ -> True
          _ -> False)
  varNames <- mapM (\_ -> newName "x") aa
  lamE (map varP varNames)
       (if doIO
         then [|unsafePerformIO $(nakedCall doIO varNames)|]
         else nakedCall doIO varNames)
  where
    ret :: Bool -> RetVal
    ret doIO =
      case (r, doIO) of
        (AtomicRV _, False) -> r
        (AtomicRV a, True) -> IORV a
        (IORV _, False) -> r
        (IORV _, True) -> error "Nested IO not supported"

    nakedCall :: Bool -> [Name] -> ExpQ
    nakedCall doIO varNames = genFfiCallImpl doIO aa (map varE varNames) (varE cn)

    genFfiCallImpl :: Bool -> [TopArg] -> [ExpQ] -> ExpQ -> ExpQ
    genFfiCallImpl doIO [] [] c_call = [|$(unmarshal (ret doIO)) ($(appE extra c_call))|]

    genFfiCallImpl doIO (IntA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call ((fromIntegral :: Int -> CInt) $v)|]

    genFfiCallImpl doIO (BoolA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call ((fromBool :: Bool -> CInt) $v)|]

    genFfiCallImpl doIO (DoubleA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call ((realToFrac :: Double -> CDouble) $v)|]

    genFfiCallImpl doIO (WordA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call ((fromIntegral :: Word -> CUInt) $v)|]

    genFfiCallImpl doIO (DayA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call (toQlDate $v)|]

    genFfiCallImpl doIO (OptDayA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call (toQlDate $v)|]

    genFfiCallImpl doIO (EnumA:as) (v:vs) c_call =
      genFfiCallImpl doIO as vs [|$c_call (toQlEnum $v)|]

    genFfiCallImpl doIO (ForeignPtrA:as) (v:vs) c_call =
      [|withObject $v (\y -> $(genFfiCallImpl doIO as vs [|$c_call y|]))|]

    genFfiCallImpl doIO (ListA DoubleN:as) (v:vs) c_call =
      [|withAmounts $v (\y1 y2 -> $(genFfiCallImpl doIO as vs [|$c_call y1 y2|]))|]

    genFfiCallImpl _ _ _ _ = error "Unreachable code" -- make it more precise

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

-- marshal StringA _code      = [|undefined|]
-- marshal OptForeignPtrA _code = [|undefined|]
-- marshal (ListA2 _x1 _x2) _code = [|undefined|]
