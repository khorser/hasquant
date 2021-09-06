{-# LANGUAGE MultiParamTypeClasses, FlexibleInstances #-}
-- internal utilities to convert special enums: either complex ones or represented as QuantLib objects that I didn't want to exposure so I represented them as ADTs
module QuantLib.Internal.Enum
  (
    qlInterpolation
  , qlInterpolation'
  , Approximation(..)
  , Interpolation(..)

  , ExerciseType(..)
  , Exercise(..)
  , QlExercise
  , EuropeanExercise(..)
  , BermudanExercise(..)
  , QlEuropeanExercise
  , QlBermudanExercise
  , SwingExercise(..)
  , QlSwingExercise

  , OptionType(..)
  , PositionType(..)
  , BondPriceType(..)

  , StrikedPayoff(..)
  , PlainVanillaPayoff(..)
  , PercentageStrikePayoff(..)
  , QlPlainVanillaPayoff
  , QlPercentageStrikePayoff
  , QlStrikedTypePayoff
  , Payoff(..)
  , QlPayoff
  , BasketPayoff(..)
  , QlBasketPayoff
  , TypePayoff(..)
  , QlTypePayoff(..)

  , CallabilityType(..)
  , Callability(..)
  , QlCallability

  , FittingMethod(..)
  , FittingMethodObject

  , FdmSchemeType(..)
  , FdmScheme(..)
  , FdmSchemeDesc

  , Constraint(..)
  , QlConstraint
  , OptimizationMethod(..)
  , QlOptimizationMethod
  , EndCriteria(..)
  , QlEndCriteria

  , QlRounding
  , RoundingType(..)
  , Rounding(..)

  , withCallability
  , withCallabilityArray
  )
where

import Control.Monad((>=>))
import Foreign.Marshal.Utils(fromBool, withMany)
import Foreign.Marshal.Array(withArray)
import QuantLib.Internal
import QuantLib.Internal.Type
import Foreign.Ptr
import Foreign.C.Types

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

{#enum ApproximationType{} add prefix="Approximation" deriving(Show, Eq)#}

{#enum InterpolationType{} add prefix="Interpolation" deriving(Show, Eq)#}

qlApproximation :: Approximation -> (Int, Int)
qlApproximation (NaturalSpline x) = (fromEnum ApproximationNaturalSpline, fromBool x)
qlApproximation (Parabolic x) = (fromEnum ApproximationParabolic, fromBool x)
qlApproximation Kruger = (fromEnum ApproximationKruger, 0)
qlApproximation FritschButland = (fromEnum ApproximationFritschButland, 0)

qlInterpolation :: Interpolation -> (Int, (Int, Int))
qlInterpolation BackwardFlat = (fromEnum InterpolationBackwardFlat, (0, 0))
qlInterpolation ForwardFlat = (fromEnum InterpolationForwardFlat, (0, 0))
qlInterpolation Linear = (fromEnum InterpolationLinear, (0, 0))
qlInterpolation LogLinear = (fromEnum InterpolationLogLinear, (0, 0))
qlInterpolation (Cubic x) = (fromEnum InterpolationCubic, qlApproximation x)
qlInterpolation (LogCubic x) = (fromEnum InterpolationLogCubic, qlApproximation x)
qlInterpolation Abcd = (fromEnum InterpolationAbcd, (0, 0))

qlInterpolation' :: Maybe Interpolation -> (Int, (Int, Int))
qlInterpolation' Nothing = (fromIntegral qlNullInteger, (0, 0))
qlInterpolation' (Just i) = qlInterpolation i

data Approximation =
  NaturalSpline Bool
  | Parabolic Bool
  | Kruger
  | FritschButland
  deriving (Show, Eq)

data Interpolation =
  BackwardFlat
  | ForwardFlat
  | Linear
  | LogLinear
  | Cubic Approximation
  | LogCubic Approximation
  | Abcd
  deriving (Show, Eq)

{#pointer *QlExercise foreign finalizer qlFreeExercise newtype#}
instance ForeignObject QlExercise where
  withObject = withQlExercise
  constructor = QlExercise
  finalizer = qlFreeExercise

class IsQlExercise a where
  asQlExercise :: a -> IO QlExercise

{#pointer *QlEuropeanExercise foreign finalizer qlFreeEuropeanExercise newtype#}
instance ForeignObject QlEuropeanExercise where
  withObject = withQlEuropeanExercise
  constructor = QlEuropeanExercise
  finalizer = qlFreeEuropeanExercise
{#fun qlEuropeanExerciseAsExercise{`QlEuropeanExercise'}->`QlExercise'#}
instance IsQlExercise QlEuropeanExercise where asQlExercise = qlEuropeanExerciseAsExercise

{#pointer *QlAmericanExercise foreign finalizer qlFreeAmericanExercise newtype#}
instance ForeignObject QlAmericanExercise where
  withObject = withQlAmericanExercise
  constructor = QlAmericanExercise
  finalizer = qlFreeAmericanExercise
{#fun qlAmericanExerciseAsExercise{`QlAmericanExercise'}->`QlExercise'#}
instance IsQlExercise QlAmericanExercise where asQlExercise = qlAmericanExerciseAsExercise

{#pointer *QlSwingExercise foreign finalizer qlFreeSwingExercise newtype#}
instance ForeignObject QlSwingExercise where
  withObject = withQlSwingExercise
  constructor = QlSwingExercise
  finalizer = qlFreeSwingExercise
{#fun qlSwingExerciseAsExercise{`QlSwingExercise'}->`QlExercise'#}
instance IsQlExercise QlSwingExercise where asQlExercise = qlSwingExerciseAsExercise

{#pointer *QlBermudanExercise foreign finalizer qlFreeBermudanExercise newtype#}
instance ForeignObject QlBermudanExercise where
  withObject = withQlBermudanExercise
  constructor = QlBermudanExercise
  finalizer = qlFreeBermudanExercise
{#fun qlBermudanExerciseAsExercise{`QlBermudanExercise'}->`QlExercise'#}
instance IsQlExercise QlBermudanExercise where asQlExercise = qlBermudanExerciseAsExercise


data EuropeanExercise = EuropeanExercise Day
instance EnumObject EuropeanExercise QlEuropeanExercise where toObject (EuropeanExercise d) = qlEuropeanExercise d

data SwingExercise = 
    SwingListExercise [(Day, Word)] -- ^(dates, seconds)
    | SwingIntervalExercise Day Day Word -- ^stepSizeSecs
instance EnumObject SwingExercise QlSwingExercise where
  toObject (SwingListExercise ds) = uncurry qlSwingExercise (unzip ds)
  toObject (SwingIntervalExercise d1 d2 s) = qlSwingExercise1 d1 d2 s

data BermudanExercise =
    BermudanExercise [Day] Bool
    | Swing SwingExercise
instance EnumObject BermudanExercise QlBermudanExercise where
  toObject (BermudanExercise d p) = qlBermudanExercise d p
  toObject (Swing e) = toObject e >>= qlSwingExerciseAsBermudanExercise

{#enum ExerciseType{} add prefix = "ExerciseType" deriving (Show, Eq)#}

data Exercise =
    AmericanExercise
      (Maybe Day) -- ^earliestDate
      Day -- ^latestDate
      Bool -- ^paoffAtExpiry
    | Early ExerciseType Bool
    | Vanilla ExerciseType
    | European EuropeanExercise
    | Bermudan BermudanExercise

{#fun qlExercise{`ExerciseType', preErrorCheck-`String'errorCheck*-}->`QlExercise'#}
{#fun qlAmericanExercise{withDay*`Day', withDay*`Day',`Bool', preErrorCheck-`String'errorCheck*-}->`QlAmericanExercise'#}
{#fun qlAmericanExercise1{withDay*`Day',`Bool', preErrorCheck-`String'errorCheck*-}->`QlAmericanExercise'#}
{#fun qlBermudanExercise{withDayArray*`[Day]'&,`Bool', preErrorCheck-`String'errorCheck*-}->`QlBermudanExercise'#}
{#fun qlEarlyExercise{`ExerciseType',`Bool', preErrorCheck-`String'errorCheck*-}->`QlExercise'#}
{#fun qlEuropeanExercise{withDay*`Day', preErrorCheck-`String'errorCheck*-}->`QlEuropeanExercise'#}
{#fun qlSwingExercise{withDayArray*`[Day]'&, withIntArray*`[Word]'&, preErrorCheck-`String'errorCheck*-}->`QlSwingExercise'#}
{#fun qlSwingExercise1{withDay*`Day', withDay*`Day', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`QlSwingExercise'#}
{#fun qlSwingExerciseAsBermudanExercise{`QlSwingExercise'}->`QlBermudanExercise'#}

exercise :: Exercise -> IO QlExercise
exercise (AmericanExercise Nothing d p) = qlAmericanExercise1 d p >>= asQlExercise
exercise (AmericanExercise (Just d0) d p) = qlAmericanExercise d0 d p >>= asQlExercise
exercise (Early t p) = qlEarlyExercise t p
exercise (Vanilla t) = qlExercise t
exercise (European e) = toObject e >>= asQlExercise
exercise (Bermudan e) = toObject e >>= asQlExercise

instance EnumObject Exercise QlExercise where toObject = exercise

{#enum OptionType{} deriving (Show, Eq)#}

{#enum PositionType{} deriving (Show, Eq)#}

{#enum BondPriceType{} deriving (Show, Eq)#}

data PercentageStrikePayoff = PercentageStrikePayoff
      OptionType -- ^type
      Double -- ^moneyness
instance EnumObject PercentageStrikePayoff QlPercentageStrikePayoff where toObject (PercentageStrikePayoff t m) = qlPercentageStrikePayoff t m

data PlainVanillaPayoff = PlainVanillaPayoff
      OptionType -- ^type
      Double -- ^strike
instance EnumObject PlainVanillaPayoff QlPlainVanillaPayoff where toObject (PlainVanillaPayoff t s) = qlPlainVanillaPayoff t s

data StrikedPayoff =
  AssetOrNothing
    OptionType -- ^type
    Double -- ^strike
  | CashOrNothing
      OptionType -- ^type
      Double -- ^strike
      Double -- ^cashPayoff
  | Gap
      OptionType -- ^type
      Double -- ^strike
      Double -- ^secondStrike
  | PercentageStrike PercentageStrikePayoff
  | PlainVanilla PlainVanillaPayoff
  | SuperFund
      Double -- ^strike
      Double -- ^secondStrike
  | SuperSharePayoff
      Double -- ^strike
      Double -- ^secondStrike
      Double -- ^cashPayoff
instance EnumObject StrikedPayoff QlStrikedTypePayoff where toObject = strikedPayoff

strikedPayoff :: StrikedPayoff -> IO QlStrikedTypePayoff
strikedPayoff (AssetOrNothing t s) = qlAssetOrNothingPayoff t s
strikedPayoff (CashOrNothing t s c) = qlCashOrNothingPayoff t s c
strikedPayoff (Gap t s ss) = qlGapPayoff t s ss
strikedPayoff (PercentageStrike p) = toObject p >>= qlPercentageStrikePayoffAsStrikedTypePayoff
strikedPayoff (PlainVanilla p) = toObject p >>= qlPlainVanillaPayoffAsStrikedTypePayoff
strikedPayoff (SuperFund s ss) = qlSuperFundPayoff s ss
strikedPayoff (SuperSharePayoff s ss c) = qlSuperSharePayoff s ss c

data TypePayoff =
  Striked StrikedPayoff
  | Floating
      OptionType -- ^type
instance EnumObject TypePayoff QlTypePayoff where
  toObject (Striked p) = toObject p >>= qlStrikedTypePayoffAsTypePayoff
  toObject (Floating t) = qlFloatingTypePayoff t

data BasketPayoff =
    Average
      Payoff -- ^p
      Word -- ^n
  | AverageMultiple
      Payoff -- ^p
      [Double] -- ^a
  | Max
      Payoff -- ^p
  | Min
      Payoff -- ^p
  | Spread
      Payoff -- ^p
instance EnumObject BasketPayoff QlBasketPayoff where toObject = basketPayoff

basketPayoff (Average p n) = payoff p >>= (`qlAverageBasketPayoff` n)
basketPayoff (AverageMultiple p a) = payoff p >>= (`qlAverageBasketPayoff1` a)
basketPayoff (Max p) = payoff p >>= qlMaxBasketPayoff
basketPayoff (Min p) = payoff p >>= qlMinBasketPayoff
basketPayoff (Spread p) = payoff p >>= qlSpreadBasketPayoff

data Payoff =
    DoubleStickyRatchet
      Double -- ^type1
      Double -- ^type2
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | ForwardType
      PositionType -- ^type
      Double -- ^strike
  | RatchetMax
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | RatchetMin
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | Ratchet
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^initialValue
      Double -- ^accrualFactor
  | StickyMax
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | StickyMin
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | Sticky
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^initialValue
      Double -- ^accrualFactor
  | Type TypePayoff
  | Basket BasketPayoff

{#pointer *QlPayoff foreign finalizer qlFreePayoff newtype#}
instance ForeignObject QlPayoff where
  withObject = withQlPayoff
  constructor = QlPayoff
  finalizer = qlFreePayoff

class IsQlPayoff a where
  asQlPayoff :: a -> IO QlPayoff

{#pointer *QlBasketPayoff foreign finalizer qlFreeBasketPayoff newtype#}
instance ForeignObject QlBasketPayoff where
  withObject = withQlBasketPayoff
  constructor = QlBasketPayoff
  finalizer = qlFreeBasketPayoff
{#fun qlBasketPayoffAsPayoff{`QlBasketPayoff'}->`QlPayoff'#}
instance IsQlPayoff QlBasketPayoff where asQlPayoff = qlBasketPayoffAsPayoff

{#pointer *QlTypePayoff foreign finalizer qlFreeTypePayoff newtype#}
instance ForeignObject QlTypePayoff where
  withObject = withQlTypePayoff
  constructor = QlTypePayoff
  finalizer = qlFreeTypePayoff
{#fun qlTypePayoffAsPayoff{`QlTypePayoff'}->`QlPayoff'#}
instance IsQlPayoff QlTypePayoff where asQlPayoff = qlTypePayoffAsPayoff

{#pointer *QlStrikedTypePayoff foreign finalizer qlFreeStrikedTypePayoff newtype#}
instance ForeignObject QlStrikedTypePayoff where
  withObject = withQlStrikedTypePayoff
  constructor = QlStrikedTypePayoff
  finalizer = qlFreeStrikedTypePayoff
{#fun qlStrikedTypePayoffAsTypePayoff{`QlStrikedTypePayoff'}->`QlTypePayoff'#}
instance IsQlPayoff QlStrikedTypePayoff where asQlPayoff = qlStrikedTypePayoffAsTypePayoff >=> asQlPayoff

{#pointer *QlPercentageStrikePayoff foreign finalizer qlFreePercentageStrikePayoff newtype#}
instance ForeignObject QlPercentageStrikePayoff where
  withObject = withQlPercentageStrikePayoff
  constructor = QlPercentageStrikePayoff
  finalizer = qlFreePercentageStrikePayoff
{#fun qlPercentageStrikePayoffAsStrikedTypePayoff{`QlPercentageStrikePayoff'}->`QlStrikedTypePayoff'#}
instance IsQlPayoff QlPercentageStrikePayoff where asQlPayoff = qlPercentageStrikePayoffAsStrikedTypePayoff >=> asQlPayoff

{#pointer *QlPlainVanillaPayoff foreign finalizer qlFreePlainVanillaPayoff newtype#}
instance ForeignObject QlPlainVanillaPayoff where
  withObject = withQlPlainVanillaPayoff
  constructor = QlPlainVanillaPayoff
  finalizer = qlFreePlainVanillaPayoff
{#fun qlPlainVanillaPayoffAsStrikedTypePayoff{`QlPlainVanillaPayoff'}->`QlStrikedTypePayoff'#}
instance IsQlPayoff QlPlainVanillaPayoff where asQlPayoff = qlPlainVanillaPayoffAsStrikedTypePayoff >=> asQlPayoff

{#fun qlAssetOrNothingPayoff{`OptionType',`Double', preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'#}
{#fun qlAverageBasketPayoff{`QlPayoff', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'#}
{#fun qlCashOrNothingPayoff{`OptionType',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'#}
{#fun qlDoubleStickyRatchetPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlFloatingTypePayoff{`OptionType', preErrorCheck-`String'errorCheck*-}->`QlTypePayoff'#}
{#fun qlForwardTypePayoff{`PositionType',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlGapPayoff{`OptionType',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'#}
{#fun qlMaxBasketPayoff{`QlPayoff', preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'#}
{#fun qlMinBasketPayoff{`QlPayoff', preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'#}
{#fun qlPercentageStrikePayoff{`OptionType',`Double', preErrorCheck-`String'errorCheck*-}->`QlPercentageStrikePayoff'#}
{#fun qlPlainVanillaPayoff{`OptionType',`Double', preErrorCheck-`String'errorCheck*-}->`QlPlainVanillaPayoff'#}
{#fun qlRatchetMaxPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlRatchetMinPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlRatchetPayoff{`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlSpreadBasketPayoff{`QlPayoff', preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'#}
{#fun qlStickyMaxPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlStickyMinPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlStickyPayoff{`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlPayoff'#}
{#fun qlSuperFundPayoff{`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'#}
{#fun qlSuperSharePayoff{`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'#}
{#fun qlAverageBasketPayoff1{`QlPayoff', withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'#}

instance EnumObject Payoff QlPayoff where toObject = payoff

payoff :: Payoff -> IO QlPayoff
payoff (DoubleStickyRatchet t1 t2 g1 g2 g3 s1 s2 s3 i1 i2 a) = qlDoubleStickyRatchetPayoff t1 t2 g1 g2 g3 s1 s2 s3 i1 i2 a
payoff (ForwardType t s) = qlForwardTypePayoff t s
payoff (RatchetMax g1 g2 g3 s1 s2 s3 i1 i2 a) = qlRatchetMaxPayoff g1 g2 g3 s1 s2 s3 i1 i2 a
payoff (RatchetMin g1 g2 g3 s1 s2 s3 i1 i2 a) = qlRatchetMinPayoff g1 g2 g3 s1 s2 s3 i1 i2 a
payoff (Ratchet g1 g2 s1 s2 i a) = qlRatchetPayoff g1 g2 s1 s2 i a
payoff (StickyMax g1 g2 g3 s1 s2 s3 i1 i2 a) = qlStickyMaxPayoff g1 g2 g3 s1 s2 s3 i1 i2 a
payoff (StickyMin g1 g2 g3 s1 s2 s3 i1 i2 a) = qlStickyMinPayoff g1 g2 g3 s1 s2 s3 i1 i2 a
payoff (Sticky g1 g2 s1 s2 i a) = qlStickyPayoff g1 g2 s1 s2 i a
payoff (Type s) = toObject s >>= asQlPayoff
payoff (Basket b) = toObject b >>= asQlPayoff

data Callability =
  Soft
    Double -- ^price
    BondPriceType
    Day
    Double -- ^trigger
  | Callability
      Double
      BondPriceType
      CallabilityType
      Day

{#enum CallabilityType{} add prefix="Callability" deriving(Show, Eq)#}

{#pointer *QlCallability foreign -> CQlCallability nocode#}

callability :: Callability -> IO (SimpleType CQlCallability)
callability (Soft p t d tg) = qlSoftCallability p t d tg
callability (Callability p t ct d) = qlCallability p t ct d

newtype EnumMeta a b = EnumMeta (a -> IO (SimpleType b)) 

withEnumType :: EnumMeta a b -> a -> (Ptr b -> IO c) -> IO c
withEnumType (EnumMeta t) x f = t x >>= (`withSimpleType` f)

withEnumTypeArray :: EnumMeta a b -> [a] -> ((CUInt, Ptr (Ptr b)) -> IO c) -> IO c
withEnumTypeArray m x f = withMany (withEnumType m) x (`withArray` (\px -> f (fromIntegral $ length x, px)))

callabilityMeta :: EnumMeta Callability CQlCallability
callabilityMeta = EnumMeta callability

withCallability :: Callability -> (Ptr CQlCallability -> IO a) -> IO a
withCallability = withEnumType callabilityMeta

withCallabilityArray :: [Callability] -> ((CUInt, Ptr (Ptr CQlCallability)) -> IO c) -> IO c
withCallabilityArray = withEnumTypeArray callabilityMeta

-- |callability leaving to the holder the possibility to convert
{#fun qlSoftCallability{`Double',`BondPriceType', withDay*`Day',`Double', preErrorCheck-`String'errorCheck*-}->`QlCallability'peekCallability*#}

{#fun qlCallability{`Double',`BondPriceType',`CallabilityType', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`QlCallability'peekCallability*#}

{#pointer *FittedBondDiscountCurveFittingMethod as FittingMethodObject foreign finalizer qlFreeFittedBondDiscountCurveFittingMethod newtype#}
instance ForeignObject FittingMethodObject where
  withObject = withFittingMethodObject
  constructor = FittingMethodObject
  finalizer = qlFreeFittedBondDiscountCurveFittingMethod

instance EnumObject FittingMethod FittingMethodObject where toObject = fittingMethod

data FittingMethod =
  CubicBSplines
    [Double] -- ^knotVector (year fraction)
    Bool -- ^constrainAtZero
  | ExponentialSplines Bool
  | NelsonSiegel
  | SimplePolynomial
    Word -- ^degree
    Bool -- ^constrainAtZero
  | Svensson
  deriving (Show, Eq)

fittingMethod :: FittingMethod -> IO FittingMethodObject
fittingMethod (CubicBSplines k c) = qlCubicBSplinesFitting k c
fittingMethod (ExponentialSplines c) = qlExponentialSplinesFitting c
fittingMethod NelsonSiegel = qlNelsonSiegelFitting
fittingMethod (SimplePolynomial d c) = qlSimplePolynomialFitting d c
fittingMethod Svensson = qlSvenssonFitting

{#fun qlCubicBSplinesFitting{withDoubleArray*`[Double]'&,`Bool', preErrorCheck-`String'errorCheck*-}->`FittingMethodObject'#}
{#fun qlExponentialSplinesFitting{`Bool', preErrorCheck-`String'errorCheck*-}->`FittingMethodObject'#}
{#fun qlNelsonSiegelFitting{preErrorCheck-`String'errorCheck*-}->`FittingMethodObject'#}
{#fun qlSimplePolynomialFitting{fromIntegral`Word',`Bool', preErrorCheck-`String'errorCheck*-}->`FittingMethodObject'#}
{#fun qlSvenssonFitting{preErrorCheck-`String'errorCheck*-}->`FittingMethodObject'#}

{#enum FdmSchemeType{} deriving(Show, Eq)#}

data FdmScheme = 
  FdmScheme
    FdmSchemeType -- ^type
    Double -- ^theta
    Double -- ^mu
  | CraigSneyd
  | Douglas
  | ExplicitEuler
  | Hundsdorfer
  | ImplicitEuler
  | ModifiedCraigSneyd
  | ModifiedHundsdorfer

{#pointer *FdmSchemeDesc foreign finalizer qlFreeFdmSchemeDesc newtype#}
instance ForeignObject FdmSchemeDesc where
  withObject = withFdmSchemeDesc
  constructor = FdmSchemeDesc
  finalizer = qlFreeFdmSchemeDesc

{#fun qlFdmSchemeDesc{`FdmSchemeType',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescCraigSneyd{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescDouglas{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescExplicitEuler{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescHundsdorfer{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescImplicitEuler{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescModifiedCraigSneyd{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}
{#fun qlFdmSchemeDescModifiedHundsdorfer{preErrorCheck-`String'errorCheck*-}->`FdmSchemeDesc'#}

fdmScheme :: FdmScheme -> IO FdmSchemeDesc
fdmScheme (FdmScheme t th mu) = qlFdmSchemeDesc t th mu
fdmScheme CraigSneyd = qlFdmSchemeDescCraigSneyd
fdmScheme Douglas = qlFdmSchemeDescDouglas
fdmScheme ExplicitEuler = qlFdmSchemeDescExplicitEuler
fdmScheme Hundsdorfer = qlFdmSchemeDescHundsdorfer
fdmScheme ImplicitEuler = qlFdmSchemeDescImplicitEuler
fdmScheme ModifiedCraigSneyd = qlFdmSchemeDescModifiedCraigSneyd
fdmScheme ModifiedHundsdorfer = qlFdmSchemeDescModifiedHundsdorfer

instance EnumObject FdmScheme FdmSchemeDesc where toObject = fdmScheme

{#pointer *Constraint as QlConstraint foreign finalizer qlFreeConstraint newtype#}
instance ForeignObject QlConstraint where
  withObject = withQlConstraint
  constructor = QlConstraint
  finalizer = qlFreeConstraint
instance EnumObject Constraint QlConstraint where toObject = constraint

data Constraint =
  Boundary
    Double -- ^low
    Double -- ^high
  | Composite
    Constraint -- ^c1
    Constraint -- ^c2
  | NoConstraint
  | PositiveConstraint

constraint :: Constraint -> IO QlConstraint
constraint (Boundary l h) = qlBoundaryConstraint l h
constraint (Composite c1 c2) = qlCompositeConstraint c1 c2
constraint NoConstraint = qlNoConstraint
constraint PositiveConstraint = qlPositiveConstraint

{#fun qlBoundaryConstraint{`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlConstraint'#}
{#fun qlCompositeConstraint{withEnumObject*`Constraint', withEnumObject*`Constraint', preErrorCheck-`String'errorCheck*-}->`QlConstraint'#}
{#fun qlNoConstraint{preErrorCheck-`String'errorCheck*-}->`QlConstraint'#}
{#fun qlPositiveConstraint{preErrorCheck-`String'errorCheck*-}->`QlConstraint'#}

{#pointer *OptimizationMethod as QlOptimizationMethod foreign finalizer qlFreeOptimizationMethod newtype#}
instance ForeignObject QlOptimizationMethod where
  withObject = withQlOptimizationMethod
  constructor = QlOptimizationMethod
  finalizer = qlFreeOptimizationMethod

data OptimizationMethod =
  LevenbergMarquardt
    Double -- ^epsfcn
    Double -- ^xtol
    Double -- ^gtol
  | Simplex
    Double -- ^lambda, characteristic length

instance EnumObject OptimizationMethod QlOptimizationMethod where
  toObject (LevenbergMarquardt e x g) = qlLevenbergMarquardt e x g
  toObject (Simplex l) = qlSimplex l
{#fun qlLevenbergMarquardt{`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlOptimizationMethod'#}
{#fun qlSimplex{`Double', preErrorCheck-`String'errorCheck*-}->`QlOptimizationMethod'#}

data EndCriteria = 
  EndCriteria
    Word -- ^maxIterations
    Word -- ^maxStationaryStateIterations
    Double -- ^rootEpsilon
    Double -- ^functionEpsilon
    Double -- ^gradientNormEpsilon

{#pointer *EndCriteria as QlEndCriteria foreign finalizer qlFreeEndCriteria newtype#}
instance ForeignObject QlEndCriteria where
  withObject = withQlEndCriteria
  constructor = QlEndCriteria
  finalizer = qlFreeEndCriteria
instance EnumObject EndCriteria QlEndCriteria where toObject (EndCriteria m1 m2 e f g) = qlEndCriteria m1 m2 e f g
{#fun qlEndCriteria{fromIntegral`Word', fromIntegral`Word',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`QlEndCriteria'#}

{#enum RoundingType{} deriving (Show, Eq)#}
{#pointer *Rounding as QlRounding foreign finalizer qlFreeRounding newtype#}
instance ForeignObject QlRounding where
  withObject = withQlRounding
  constructor = QlRounding
  finalizer = qlFreeRounding

data Rounding = NoRounding
  | Rounding
    Int -- ^precision
    RoundingType
    Int -- ^digit
  deriving (Show, Eq)
instance EnumObject Rounding QlRounding where
  toObject NoRounding = qlRounding
  toObject (Rounding p t d) = qlRounding1 p t d

{#fun qlRounding{preErrorCheck-`String'errorCheck*-}->`QlRounding'#}
{#fun qlRounding1{`Int',`RoundingType',`Int', preErrorCheck-`String'errorCheck*-}->`QlRounding'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
