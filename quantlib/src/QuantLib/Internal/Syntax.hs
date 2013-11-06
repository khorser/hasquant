{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    ffiCall
  , ffiCallPure
  , ffiCallX
  , ffiCallPureX

  , qlEnumsInfo
  )
where

import Control.Applicative((<$>), (<*>))
import Control.Monad(liftM)
import Foreign.Marshal.Utils(fromBool, toBool)
import Language.Haskell.TH
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal.Date
import QuantLib.Internal.Enum
import QuantLib.Internal.Types
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
import QuantLib.Math.RNGTrait()
import QuantLib.Method.BinomialTree()
import QuantLib.Method.BoundaryCondition()
import QuantLib.Method.FdmScheme()
import QuantLib.Model.CalibrationErrorType()
import QuantLib.MoneyConversionType()
import QuantLib.Instrument.CallabilityType()

-- QLLitEnum instances
import QuantLib.Math.Interpolation()
import QuantLib.ProcessDiscretization()
import QuantLib.TermStructure.Trait() -- QLLitEnum and QLEnum

data NestedArg = DayN | DoubleN | WordN | ForeignPtrN | EnumN Name | BoolN | YearFractionN
  deriving (Show, Eq)

-- XXX use SYB/Uniplate to traverse with comfort?
-- XXX use GADTs to make the structure conform to the handled cases
data TopArg = IntA | WordA | DayA | StringA | DoubleA | BoolA | YearFractionA
  | OptDayA | ForeignPtrA | OptForeignPtrA | OptBoolA | OptIntA | OptWordA | OptDoubleA
  | ListA NestedArg | ListA2 NestedArg NestedArg
  | EnumA Name | LitEnumA | OptLitEnumA | MatrixDoubleA | MatrixForeignPtrA
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double, ''Bool, ''YearFraction]

qlEnums :: Name -> Q [Name]
qlEnums en = reify en >>= \(ClassI _ instances) ->
  return $ map getEnumTypeName instances
  where
    getEnumTypeName :: Dec -> Name
    getEnumTypeName (InstanceD [] (AppT _ (ConT x)) []) = x
    getEnumTypeName x = error $ "Unsupported pattern in instance declaration: " ++ show x

-- return expression [(String, Int)] - [(enum name, enum lenght)]
qlEnumsInfo :: ExpQ
qlEnumsInfo = qlEnums ''QLEnum >>= listE . f
  where
    f = map (\x -> tupE[stringE $ show x, enumSizeE x])
    enumSizeE :: Name -> ExpQ
    enumSizeE n = reify n >>= \(TyConI (DataD _ _ _ cs _)) ->
      litE $ integerL (fromIntegral $ length cs)

-- For different types we have different sets of acceptable cases.
-- This combinator streamlines the work accepting a list of pairs (predicate, value to return)
-- Introduce an infix ||-like operator?
seqParse :: (Monad m, Show a) => Name -> [(Name -> m Bool, a)] -> m a
seqParse n as = seqParse' as
  where seqParse' [] = error $ "No matching alternative found while parsing " ++ show n ++ ", options considered: " ++ show (map snd as)
        seqParse' ((p, r):xs) = p n >>= \m -> if m then return r else seqParse' xs

isEnum :: Name -> Q Bool
isEnum n = elem n <$> qlEnums ''QLEnum

isLitEnum :: Name -> Q Bool
isLitEnum n = elem n <$> qlEnums ''QLLitEnum

isForeignPtr :: Name -> Q Bool
isForeignPtr n = f <$> reify n
  where
    f (TyConI (TySynD _ [] (AppT (ConT p) (ConT _target)))) | p == ''ForeignPtr = True
    f (TyConI (DataD [] p _ _ _)) | p == ''ForeignPtr = True
    f _ = False

nameToTop :: Name -> TopArg
nameToTop n | n == ''Int = IntA
nameToTop n | n == ''Word = WordA
nameToTop n | n == ''Day = DayA
nameToTop n | n == ''Bool = BoolA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop n | n == ''YearFraction = YearFractionA
nameToTop n = error $ "Unsupported top type: " ++ show n

nestedNameToTop :: Name -> Q NestedArg
nestedNameToTop n | n == ''Day = return DayN
nestedNameToTop n | n == ''Double = return DoubleN
nestedNameToTop n | n == ''Bool = return BoolN
nestedNameToTop n | n == ''YearFraction = return YearFractionN
nestedNameToTop n | n == ''Word = return WordN
nestedNameToTop n = seqParse n [(isEnum, EnumN n), (isForeignPtr, ForeignPtrN)]

topArgType :: Type -> Q TopArg
topArgType (ConT n) | isAtomicTop n = return $ nameToTop n
topArgType (ConT n) = seqParse n [(isEnum, EnumA n), (isLitEnum, LitEnumA), (isForeignPtr, ForeignPtrA)]
topArgType (AppT (ConT m) (ConT n)) | m == ''Maybe = maybeType n
  where
    maybeType t | t == ''Day = return OptDayA
    maybeType t | t == ''Bool = return OptBoolA
    maybeType t | t == ''Int = return OptIntA
    maybeType t | t == ''Double = return OptDoubleA
    maybeType t | t == ''Word = return OptWordA
    maybeType t = seqParse t [(isLitEnum, OptLitEnumA), (isForeignPtr, OptForeignPtrA)]
topArgType (AppT ListT (ConT n)) = ListA <$> nestedNameToTop n
topArgType (AppT
          ListT
          (AppT
            (AppT (TupleT 2) (ConT n1))
            (ConT n2))) =
              ListA2 <$> nestedNameToTop n1 <*> nestedNameToTop n2
topArgType (AppT (ConT m) (ConT n)) | m == ''Matrix =
  if n == ''Double
    then return MatrixDoubleA
    else seqParse n  [(isForeignPtr, MatrixForeignPtrA)]
topArgType (AppT c@(ConT m) (VarT _)) | m == ''ForeignPtr = topArgType c
topArgType t = fail $ "Unsupported top-level arg type: " ++ show t

data AtomicRet = IntR | WordR | DayR | DoubleR | BoolR
  | EnumR Name | OptDayR | ForeignPtrR | UnitR
  | DayListR | YearFractionR | StringR
  deriving (Show, Eq)

data RetVal = AtomicRV AtomicRet | IORV AtomicRet | EitherRV AtomicRet
  deriving (Show, Eq)

nameToRetVal :: Name -> Q AtomicRet
nameToRetVal n | n == ''Int = return IntR
nameToRetVal n | n == ''Word = return WordR
nameToRetVal n | n == ''Day = return DayR
nameToRetVal n | n == ''Double = return DoubleR
nameToRetVal n | n == ''Bool = return BoolR
nameToRetVal n | n == ''YearFraction = return YearFractionR
nameToRetVal n | n == ''String = return StringR
nameToRetVal n = seqParse n [(isEnum, EnumR n), (isForeignPtr, ForeignPtrR)]

compArgToRetVal :: Type -> Q AtomicRet
compArgToRetVal (AppT (ConT m) (ConT d)) | (m, d) == (''Maybe, ''Day) =
  return OptDayR
compArgToRetVal (AppT ListT (ConT n)) | n == ''Day = return DayListR
compArgToRetVal (AppT (ConT n) _) | n == ''ForeignPtr = return ForeignPtrR
compArgToRetVal (ConT n) = nameToRetVal n
compArgToRetVal (TupleT 0) = return UnitR
compArgToRetVal t = fail $ "Unsupported compound type ret value: " ++ show t

compToRetVal :: Type -> Q RetVal
compToRetVal (AppT (ConT n1) t2)
  | n1 == ''IO = IORV <$> compArgToRetVal t2
compToRetVal (AppT (AppT (ConT n1) (ConT n2)) t2)
  | (n1, n2) == (''Either, ''String) = EitherRV <$> compArgToRetVal t2
compToRetVal t = AtomicRV <$> compArgToRetVal t

-- use WriterT to clean up this mess?
parseSignature :: Type -> Q ([TopArg], RetVal)
-- strip forall
parseSignature (ForallT _ _ app@(AppT _ _)) = parseSignature app
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
parseSignature t = fail $ "Unsupported signature: " ++ show t

data IOAction = Straight | Pure | Unmarshal | Purify
  deriving (Show, Eq)

ffiCall :: Name -> ExpQ
ffiCall hn = ffiCallImpl hn Straight

ffiCallPure :: Name -> ExpQ
ffiCallPure hn = ffiCallImpl hn Pure

ffiCallX :: Name -> ExpQ
ffiCallX hn = ffiCallImpl hn Unmarshal

ffiCallPureX :: Name -> ExpQ
ffiCallPureX hn = ffiCallImpl hn Purify

ffiCallImpl :: Name -> IOAction -> ExpQ
ffiCallImpl hFun extra = reify hFun >>= f
  where
    f (VarI _ ft _ _) = parseSignature ft >>= uncurry (genFfiCall extra)
    f _ = fail $ "Cannot reify the type of " ++ show hFun

genFfiCall :: IOAction -> [TopArg] -> RetVal -> ExpQ
genFfiCall extra aa r = do
  varNames <- mapM (\_ -> newName "x") aa
  cFunName <- newName "fun"
  lamE (map varP (cFunName : varNames)) [|$(call varNames cFunName extra)|]
  where
    call varNames cFunName Pure   = [|unsafePerformIO $(nakedCall varNames cFunName)|]
    call varNames cFunName Purify = [|purifyExceptions $(nakedCall varNames cFunName)|]
    call varNames cFunName _      = [|$(nakedCall varNames cFunName)|]

    ret :: RetVal
    ret =
      case (r, extra) of
        (AtomicRV _, Straight) -> r
        (AtomicRV a, Pure) -> IORV a
        (IORV _, Straight) -> r
        (IORV _, Unmarshal) -> r
        (EitherRV _, Purify) -> r
        _ -> error $ "Return type " ++ show r ++ " is incompatible with call type " ++ show extra

    finalCCall :: ExpQ -> ExpQ
    finalCCall c_call =
      case r of
        (AtomicRV ForeignPtrR) -> error "IO is required to return ForeignPtr"
        (IORV ForeignPtrR) -> [|construct $(appE (postCall extra) c_call)|]
        -- last argument is a pointer to the length of the returned array
        (AtomicRV DayListR) -> [|getArray $(appE (postCall extra) c_call)|]
        _ -> appE (postCall extra) c_call

    postCall Straight = [|id|]
    postCall Pure = [|id|]
    postCall Unmarshal = [|unmarshalExceptions|]
    postCall Purify = [|unmarshalExceptions|]

    nakedCall :: [Name] -> Name -> ExpQ
    nakedCall varNames cFunName = genFfiCallImpl (zip aa (map varE varNames)) (varE cFunName)

    genFfiCallImpl :: [(TopArg, ExpQ)] -> ExpQ -> ExpQ
    genFfiCallImpl [] c_call = [|$(unmarshal ret) ($(finalCCall c_call))|]

    genFfiCallImpl ((IntA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((fromIntegral :: Int -> CInt) $v)|]

    genFfiCallImpl ((OptIntA, v):as) c_call =
      genFfiCallImpl as [|$c_call (maybe nullInteger (fromIntegral :: Int -> CInt) $v)|]

    genFfiCallImpl ((BoolA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((fromBool :: Bool -> CInt) $v)|]

    genFfiCallImpl ((OptBoolA, v):as) c_call =
      genFfiCallImpl as [|$c_call (maybe (-1::CInt) (fromBool :: Bool -> CInt) $v)|]

    genFfiCallImpl ((DoubleA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((realToFrac :: Double -> CDouble) $v)|]

    genFfiCallImpl ((OptDoubleA, v):as) c_call =
      genFfiCallImpl as [|$c_call (maybe nullReal (realToFrac :: Double -> CDouble) $v)|]

    genFfiCallImpl ((WordA, v):as) c_call =
      genFfiCallImpl as [|$c_call ((fromIntegral :: Word -> CUInt) $v)|]

    genFfiCallImpl ((OptWordA, v):as) c_call =
      genFfiCallImpl as [|$c_call (maybe (fromIntegral nullInteger) (fromIntegral :: Word -> CUInt) $v)|]

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

    genFfiCallImpl ((MatrixDoubleA, v):as) c_call =
      [|withDoubles (matrixData $v) (\_ y -> $(genFfiCallImpl as
        [|$c_call ((fromIntegral::Word->CUInt) $ matrixRows $v) ((fromIntegral::Word->CUInt) $ matrixColumns $v) y |]))|]

    genFfiCallImpl ((MatrixForeignPtrA, v):as) c_call =
      [|withObjects (matrixData $v) (\_ y -> $(genFfiCallImpl as
        [|$c_call ((fromIntegral::Word->CUInt) $ matrixRows $v) ((fromIntegral::Word->CUInt) $ matrixColumns $v) y |]))|]

    genFfiCallImpl ((ListA DoubleN, v):as) c_call =
      [|withDoubles $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA ForeignPtrN, v):as) c_call =
      [|withObjects $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA DayN, v):as) c_call =
      [|withDays $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA BoolN, v):as) c_call =
      [|withArrayULenT fromBool $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA WordN, v):as) c_call =
      [|withArrayULenT (fromIntegral :: Word -> CUInt) $v (\y1 y2 ->
          $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA YearFractionN, v):as) c_call =
      [|withDoubles $v (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA (EnumN n), v):as) c_call =
      [|withArrayULenT (toQlEnum $(stringE $ show n)) $v
        (\y1 y2 -> $(genFfiCallImpl as [|$c_call y1 y2|]))|]

    genFfiCallImpl ((ListA2 DoubleN DayN, v):as) c_call =
      [|withDoubles (map fst $v) (\n ams -> withDays (map snd $v)
        (\_ ds -> $(genFfiCallImpl as [|$c_call n ams ds|])))|]

    genFfiCallImpl ((ListA2 ForeignPtrN DayN, v):as) c_call =
      [|withObjects (map fst $v) (\n os -> withDays (map snd $v)
        (\_ ds -> $(genFfiCallImpl as [|$c_call n os ds|])))|]

    genFfiCallImpl ((ListA2 ForeignPtrN BoolN, v):as) c_call =
      [|withObjects (map fst $v) (\n os -> withArrayULenT (fromBool . snd) $v
        (\_ bs -> $(genFfiCallImpl as [|$c_call n os bs|])))|]

    genFfiCallImpl ((ListA2 DayN WordN, v):as) c_call =
      [|withDays (map fst $v) (\n ds -> withArrayULenT ((fromIntegral :: Word -> CUInt) . snd) $v
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
unmarshal (EitherRV StringR) = [|getString|]
unmarshal (EitherRV r) = [|liftM $(unmarshalA r)|]

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
