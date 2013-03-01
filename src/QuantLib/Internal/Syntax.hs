{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    ffiCall
  , ffiCallIO
  , ffiCallX
  )
where

import Control.Monad(liftM, liftM2)
import Foreign.Marshal.Utils(fromBool, toBool)
import Language.Haskell.TH
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal.Date
import QuantLib.Internal.Enum
import QuantLib.Internal.Utils
import QuantLib.Types

-- All QLEnum instances must be imported here!
import QuantLib.CashFlow.DurationType()
import QuantLib.Compounding()
import QuantLib.Credit.ProtectionSide()
import QuantLib.Credit.Seniority()
import QuantLib.ExerciseType()
import QuantLib.Instrument.AverageType()
import QuantLib.Instrument.BMASwapType()
import QuantLib.Instrument.BarrierType()
import QuantLib.Instrument.OptionType()
import QuantLib.Instrument.OvernightIndexedSwapType()
import QuantLib.Instrument.VanillaSwapType()
import QuantLib.Math.RoundingType()
import QuantLib.Method.LsmBasisSystemPolynomType()
import QuantLib.PositionType()
import QuantLib.PriceType()
import QuantLib.PricingEngine.Parameter()
import QuantLib.SettlementType()
import QuantLib.Time.BusinessDayConvention()
import QuantLib.Time.DateGenerationRule()
import QuantLib.Time.Frequency()
import QuantLib.Time.IMMMonth()
import QuantLib.Time.JointCalendarRule()
import QuantLib.Time.Month()
import QuantLib.Time.Unit()
import QuantLib.Time.Weekday()
import QuantLib.FX.DeltaVolQuote()
import QuantLib.Math.EndCriteriaType()
import QuantLib.Math.HistogramAlgorithm()
import QuantLib.Method.BoundaryCondition()
import QuantLib.Model.CalibrationErrorType()
import QuantLib.MoneyConversionType()

-- QLLitEnum instances
import QuantLib.Math.Interpolation()
import QuantLib.ProcessDiscretization()
import QuantLib.TermStructure.Trait() -- QLLitEnum and QLEnum

data NestedArg = DayN | DoubleN | WordN | ForeignPtrN | EnumN Name | BoolN | YearFractionN
  deriving (Show, Eq)

-- XXX use GADTs/SYB/Uniplate?
data TopArg = IntA | WordA | DayA | StringA | DoubleA | BoolA | YearFractionA
  | OptDayA | ForeignPtrA | OptForeignPtrA | OptBoolA
  | ListA NestedArg | ListA2 NestedArg NestedArg
  | EnumA Name | LitEnumA | OptLitEnumA
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double, ''Bool, ''YearFraction]

data EnumType = IntEnum | LitEnum
enumType :: Name -> Q (Maybe EnumType)
enumType n = do
  ClassI _ instances <- reify ''QLEnum
  if n `elem` map getEnumTypeName instances
    then return (Just IntEnum)
    else do
      ClassI _ litinstances <- reify ''QLLitEnum
      return $
        if n `elem` map getEnumTypeName litinstances
          then Just LitEnum
          else Nothing
  where getEnumTypeName (InstanceD [] (AppT _ (ConT x)) []) = x
        getEnumTypeName x = error $ "Unsupported pattern in instance declaration: " ++ show x

nameToTop :: Name -> TopArg
nameToTop n | n == ''Int = IntA
nameToTop n | n == ''Word = WordA
nameToTop n | n == ''Day = DayA
nameToTop n | n == ''Bool = BoolA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop n | n == ''YearFraction = YearFractionA
nameToTop n = error $ "Not supported top type: " ++ show n

nestedNameToTop :: Name -> Q NestedArg
nestedNameToTop n | n == ''Day = return DayN
nestedNameToTop n | n == ''Double = return DoubleN
nestedNameToTop n | n == ''Bool = return BoolN
nestedNameToTop n | n == ''YearFraction = return YearFractionN
nestedNameToTop n | n == ''Word = return WordN
nestedNameToTop n = do
  e <- enumType n
  case e of
    (Just IntEnum) -> return $ EnumN n
    _ -> tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing nested arg: " ++ show x)
            (\_ -> return ForeignPtrN)

topArgType :: Type -> Q TopArg
topArgType (ConT n) | isAtomicTop n = return $ nameToTop n
topArgType (ConT n) = do
  e <- enumType n
  case e of
    (Just IntEnum) -> return $ EnumA n
    (Just LitEnum) -> return LitEnumA
    _ -> tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing top arg: " ++ x)
          (\_ -> return ForeignPtrA)
topArgType (AppT (ConT m) (ConT n)) | m == ''Maybe =
  if n == ''Day
    then return OptDayA
    else
      if n == ''Bool
        then return OptBoolA
        else do
          en <- enumType n
          case en of
            (Just LitEnum) -> return OptLitEnumA
            _ -> tryForeignPtr n >>=
                  either (\x -> fail $ "Error parsing optional top arg: " ++ x)
                    (\_ -> return OptForeignPtrA)
topArgType (AppT ListT (ConT n)) = liftM ListA (nestedNameToTop n)
topArgType (AppT
          ListT
          (AppT
            (AppT (TupleT 2) (ConT n1))
            (ConT n2))) =
              liftM2 ListA2 (nestedNameToTop n1) (nestedNameToTop n2)
topArgType t = fail $ "Unsupported top-level arg type: " ++ show t

data AtomicRet = IntR | WordR | DayR | DoubleR | BoolR
  | EnumR Name | OptDayR | ForeignPtrR | UnitR
  | DayListR | YearFractionR | StringR
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
nameToRetVal n | n == ''Bool = return BoolR
nameToRetVal n | n == ''YearFraction = return YearFractionR
nameToRetVal n | n == ''String = return StringR
nameToRetVal n = do
  e <- enumType n
  case e of
    (Just IntEnum) -> return $ EnumR n
    (Just LitEnum) -> fail $ "Literal enum not supported" ++ show n
    _ -> tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing ret type: " ++ x)
            (\_ -> return ForeignPtrR)

compArgToRetVal :: Type -> Q AtomicRet
compArgToRetVal (AppT (ConT m) (ConT d)) | m == ''Maybe && d == ''Day =
  return OptDayR
compArgToRetVal (AppT ListT (ConT n)) | n == ''Day = return DayListR
compArgToRetVal (ConT n) = nameToRetVal n
compArgToRetVal (TupleT 0) = return UnitR
compArgToRetVal t = fail $ "Unsupported compound type arg: " ++ show t

compToRetVal :: Type -> Q RetVal
compToRetVal (AppT (ConT n1) t2) | n1 == ''IO =
  liftM IORV $ compArgToRetVal t2
compToRetVal t = liftM AtomicRV $ compArgToRetVal t

-- use WriterT to clean up this mess?
parseSignature :: Type -> Q ([TopArg], RetVal)
parseSignature (AppT (AppT ArrowT t1) t2) = do
  top <- topArgType t1
  (rest, ret) <- parseSignature t2
  return (top : rest, ret)
parseSignature (ConT n) = do
    r <- nameToRetVal n
    return ([], AtomicRV r)
parseSignature t@(AppT _ _) = do
    r <- compToRetVal t
    return ([], r)
parseSignature t = fail $ "Unsupported type: " ++ show t

ffiCall :: Name -> ExpQ
ffiCall hn = ffiCallImpl False hn [|id|]

ffiCallIO :: Name -> ExpQ
ffiCallIO hn = ffiCallImpl True hn [|id|]

ffiCallX :: Name -> ExpQ
ffiCallX hn = ffiCallImpl False hn [|handleExceptions|]

ffiCallImpl :: Bool -> Name -> ExpQ -> ExpQ
ffiCallImpl io hFun extra = do
  r <- reify hFun
  case r of
    VarI _ ft _ _  -> parseSignature ft >>= uncurry (genFfiCall io extra)
    _ -> fail $ "Cannot reify the type of " ++ show hFun

genFfiCall :: Bool -> ExpQ -> [TopArg] -> RetVal -> ExpQ
genFfiCall io extra aa r = do
  varNames <- mapM (\_ -> newName "x") aa
  cFunName <- newName "fun"
  lamE (map varP (cFunName : varNames))
       (if io
         then [|unsafePerformIO $(nakedCall varNames cFunName)|]
         else nakedCall varNames cFunName)
  where
    ret :: RetVal
    ret =
      case (r, io) of
        (AtomicRV _, False) -> r
        (AtomicRV a, True) -> IORV a
        (IORV _, False) -> r
        (IORV _, True) -> error "Nested IO is not supported"

    finalCCall :: ExpQ -> ExpQ
    finalCCall c_call =
      case r of
        (AtomicRV ForeignPtrR) -> error "IO is required to return ForeignPtr"
        (IORV ForeignPtrR) -> [|construct $(appE extra c_call)|]
        -- last argument is pointer to the length of the returned array
        (AtomicRV DayListR) -> [|getArray $(appE extra c_call)|]
        _ -> appE extra c_call

    nakedCall :: [Name] -> Name -> ExpQ
    nakedCall varNames cFunName = genFfiCallImpl (zip aa (map varE varNames)) (varE cFunName)

    genFfiCallImpl :: [(TopArg, ExpQ)] -> ExpQ -> ExpQ
    genFfiCallImpl [] c_call = [|$(unmarshal ret) ($(finalCCall c_call))|]

    genFfiCallImpl ((IntA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((fromIntegral :: Int -> CInt) $v)|]

    genFfiCallImpl ((BoolA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((fromBool :: Bool -> CInt) $v)|]

    genFfiCallImpl ((OptBoolA, v):as) c_call =
      genFfiCallImpl as [|$c_call (maybe (-1::CInt) (fromBool :: Bool -> CInt) $v)|]

    genFfiCallImpl ((DoubleA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((realToFrac :: Double -> CDouble) $v)|]

    genFfiCallImpl ((WordA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((fromIntegral :: Word -> CUInt) $v)|]

    genFfiCallImpl ((DayA, v):as) c_call =
      genFfiCallImpl as [|$c_call (toQlDate $v)|]

    genFfiCallImpl ((OptDayA, v):as) c_call =
      genFfiCallImpl as [|$c_call (toQlDate $v)|]

    genFfiCallImpl ((YearFractionA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((realToFrac :: Double -> CDouble) $v)|]

    genFfiCallImpl ((StringA, v):as) c_call =
      [|withCString $v (\y -> $(genFfiCallImpl as [|$c_call y|]))|]

    genFfiCallImpl ((EnumA n, v):as) c_call =
      genFfiCallImpl as [|$c_call (toQlEnum $(stringE $ show n) $v)|]

    genFfiCallImpl ((LitEnumA, v):as) c_call =
      [|withLitEnum $v (\y -> $(genFfiCallImpl as [|$c_call y|]))|]

    genFfiCallImpl ((OptLitEnumA, v):as) c_call =
      [|withOptLitEnum $v (\y -> $(genFfiCallImpl as [|$c_call y|]))|]

    genFfiCallImpl ((ForeignPtrA, v):as) c_call =
      [|withObject $v (\y -> $(genFfiCallImpl as [|$c_call y|]))|]

    genFfiCallImpl ((OptForeignPtrA, v):as) c_call =
      [|maybeWithObject $v (\y -> $(genFfiCallImpl as [|$c_call y|]))|]

    genFfiCallImpl ((ListA DoubleN, v):as) c_call =
      [|withDoubles $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA ForeignPtrN, v):as) c_call =
      [|withObjects $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA DayN, v):as) c_call =
      [|withDays $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA BoolN, v):as) c_call =
      [|withArrayULen (map fromBool $v) (\y1 y2 ->
          $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA WordN, v):as) c_call =
      [|withArrayULen (map (fromIntegral :: Word -> CUInt) $v) (\y1 y2 ->
          $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA YearFractionN, v):as) c_call =
      [|withDoubles $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA (EnumN n), v):as) c_call =
      [|withArrayULen (map (toQlEnum $(stringE $ show n)) $v)
        (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA2 DoubleN DayN, v):as) c_call =
      [|withDoubles (map fst $v) (\n ams -> withDays (map snd $v)
        (\_ ds -> $(genFfiCallImpl as [|$c_call n ams ds|])))|]

    genFfiCallImpl ((ListA2 ForeignPtrN DayN, v):as) c_call =
      [|withObjects (map fst $v) (\n os -> withDays (map snd $v)
        (\_ ds -> $(genFfiCallImpl as [|$c_call n os ds|])))|]

    genFfiCallImpl ((ListA2 ForeignPtrN BoolN, v):as) c_call =
      [|withObjects (map fst $v) (\n os -> withArrayULen (map (fromBool . snd) $v)
        (\_ bs -> $(genFfiCallImpl as [|$c_call n os bs|])))|]

    genFfiCallImpl ((ListA2 DayN WordN, v):as) c_call =
      [|withDays (map fst $v) (\n ds -> withArrayULen (map ((fromIntegral :: Word -> CUInt) . snd) $v)
        (\_ ws -> $(genFfiCallImpl as [|$c_call n ds ws|])))|]

    genFfiCallImpl ((ListA2 ForeignPtrN DoubleN, v):as) c_call =
      [|withObjects (map fst $v) (\n os -> withDoubles (map snd $v)
        (\_ ds -> $(genFfiCallImpl as [|$c_call n os ds|])))|]

    genFfiCallImpl ((t@(ListA2 _ _), _v):_as) _c_call =
      error $ show t ++ " Not supported yet"

unmarshal :: RetVal -> ExpQ
unmarshal (AtomicRV r) = [|$(unmarshalA r)|]
unmarshal (IORV StringR) = [|getString|]
unmarshal (IORV r) = [|liftM $(unmarshalA r)|]

unmarshalA :: AtomicRet -> ExpQ
unmarshalA IntR    = [|fromIntegral :: CInt -> Int|]
unmarshalA WordR   = [|fromIntegral :: CUInt -> Word|]
unmarshalA DayR    = [|fromQlDate|]
unmarshalA DoubleR = [|realToFrac :: CDouble -> Double|]
unmarshalA YearFractionR = [|realToFrac :: CDouble -> Double|]
unmarshalA BoolR = [|toBool :: CInt -> Bool|]
unmarshalA (EnumR n) = [|fromQlEnum $(stringE $ show n)|]
unmarshalA OptDayR = [|fromQlDate|]
unmarshalA ForeignPtrR = [|id|] -- this case is handled separately in finalCCall
unmarshalA UnitR   = [|id|]
unmarshalA DayListR = [|map fromQlDate|]
unmarshalA StringR = error "String unmarshalling needs IO"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
