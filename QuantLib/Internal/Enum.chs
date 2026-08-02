-- internal utilities to convert special enums: either complex ones or represented as QuantLib objects that I didn't want to expose so I represented them as ADTs
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
  , QlTypePayoff

  , CallabilityType(..)
  , Callability(..)
  , QlCallability

  , Claim(..)
  , QlClaim
  , withClaim

  , FittingMethod(..)
  , QlFittedBondDiscountCurveFittingMethod
  , withFittedBondDiscountCurveFittingMethod

  , FdmSchemeType(..)
  , FdmScheme(..)
  , QlFdmSchemeDesc
  , withFdmSchemeDesc

  , Constraint(..)
  , QlConstraint
  , withConstraint
  , withMaybeConstraint
  , OptimizationMethod(..)
  , QlOptimizationMethod
  , withOptimizationMethod
  , EndCriteria(..)
  , QlEndCriteria
  , withEndCriteria

  , QlRounding
  , RoundingType(..)
  , Rounding(..)
  , withRounding
  , withMaybeRounding

  , withCallability
  , withCallabilityArray

  , QlLmVolatilityModel
  , LmVolatilityModel(..)
  , QlLmCorrelationModel
  , LmCorrelationModel(..)
  , withLmCorrelationModel
  , withLmVolatilityModel

  , TimeUnit(..)

  , withEuropeanExercise
  , withSwingExercise
  , withBermudanExercise
  , withExercise
  , withPercentageStrikePayoff
  , withPlainVanillaPayoff
  , withStrikedPayoff
  , withTypePayoff
  , withBasketPayoff
  , withPayoff

  , strikedPayoff
  , percentageStrikePayoff
  , plainVanillaPayoff
  , swingExercise
  ) where
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.C.Types(CUInt)
import Foreign.Marshal.Utils(fromBool, withMany)
import Foreign.Marshal.Array(withArray)
import Control.Exception(finally)

import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

-- this enum is not special, just used in many places and was put here to avoid cyclic dependencies
{#enum TimeUnit{} deriving(Show, Eq, Bounded)#}
{#enum ApproximationType{} add prefix="Approximation" deriving(Show, Eq)#}
{#enum InterpolationType{} add prefix="Interpolation" deriving(Show, Eq)#}
{#enum ExerciseType{} add prefix = "ExerciseType" deriving (Show, Eq)#}
{#enum OptionType{} deriving (Show, Eq)#}
{#enum PositionType{} deriving (Show, Eq)#}
{#enum BondPriceType{} deriving (Show, Eq)#}
{#enum CallabilityType{} add prefix="Callability" deriving(Show, Eq)#}
{#enum FdmSchemeType{} deriving(Show, Eq)#}
{#enum RoundingType{} deriving (Show, Eq)#}

-- Payoff/Exercise pointer hierarchy: the Finalizable/Upcastable instances and raw phantom
-- tags (CPayoff' etc.) live in QuantLib.Internal.Type alongside every other class hierarchy;
-- these are just c2hs-local aliases so {#fun#} specs below can keep writing the bare `QlX'
-- names, resolving to a raw, unwrapped Ptr (no auto-generated foreign-pointer code) since
-- construction/upcasting is handled by hand in the with* functions further down.
type QlPayoff = Ptr CPayoff'
type QlBasketPayoff = Ptr CBasketPayoff'
type QlTypePayoff = Ptr CTypePayoff'
type QlStrikedTypePayoff = Ptr CStrikedTypePayoff'
type QlPercentageStrikePayoff = Ptr CPercentageStrikePayoff'
type QlPlainVanillaPayoff = Ptr CPlainVanillaPayoff'
type QlExercise = Ptr CExercise'
type QlEuropeanExercise = Ptr CEuropeanExercise'
type QlAmericanExercise = Ptr CAmericanExercise'
type QlSwingExercise = Ptr CSwingExercise'
type QlBermudanExercise = Ptr CBermudanExercise'
-- identity peek function: c2hs {#fun#} return specs always need a named out-marshaller,
-- even when (as here) construction should just hand back the raw, un-wrapped pointer.
peekPtr :: Ptr a -> IO (Ptr a)
peekPtr = pure
{#pointer *QlPayoff nocode#}
{#pointer *QlBasketPayoff nocode#}
{#pointer *QlTypePayoff nocode#}
{#pointer *QlStrikedTypePayoff nocode#}
{#pointer *QlPercentageStrikePayoff nocode#}
{#pointer *QlPlainVanillaPayoff nocode#}
{#pointer *QlExercise nocode#}
{#pointer *QlEuropeanExercise nocode#}
{#pointer *QlAmericanExercise nocode#}
{#pointer *QlSwingExercise nocode#}
{#pointer *QlBermudanExercise nocode#}
{#pointer *QlCallability foreign -> CQlCallability nocode#}
{#pointer *OptimizationMethod as QlOptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *EndCriteria as QlEndCriteria foreign -> CEndCriteria nocode#}
{#pointer *Constraint as QlConstraint foreign -> CConstraint nocode#}
{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}
{#pointer *FittedBondDiscountCurveFittingMethod as QlFittedBondDiscountCurveFittingMethod foreign -> CFittedBondDiscountCurveFittingMethod nocode#}
{#pointer *QlClaim as Claim foreign -> CQlClaim nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlLmCorrelationModel foreign -> CLmCorrelationModel nocode#}
{#pointer *QlLmVolatilityModel foreign -> CLmVolatilityModel nocode#}
{#pointer *Rounding as QlRounding foreign -> CRounding nocode#}

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
  NaturalSpline !Bool
  | Parabolic !Bool
  | Kruger
  | FritschButland
  deriving (Show, Eq)

data Interpolation =
  BackwardFlat
  | ForwardFlat
  | Linear
  | LogLinear
  | Cubic !Approximation
  | LogCubic !Approximation
  | Abcd
  deriving (Show, Eq)

data EuropeanExercise = EuropeanExercise Day
-- | Use 'swingExerice' to construct 'Exercise'
data SwingExercise =
    SwingListExercise ![(Day, Word)] -- ^(dates, seconds)
    | SwingIntervalExercise !Day !Day !Word -- ^stepSizeSecs
data BermudanExercise =
    BermudanExercise ![Day] !Bool
    | Swing SwingExercise
data Exercise =
    AmericanExercise
      !(Maybe Day) -- ^earliestDate
      !Day -- ^latestDate
      !Bool -- ^paoffAtExpiry
    | Early !ExerciseType !Bool
    | Vanilla !ExerciseType
    | European !EuropeanExercise
    | Bermudan !BermudanExercise

{#fun qlExercise{`ExerciseType',preErrorCheck-`String'errorCheck*-}->`QlExercise'peekPtr*#}
{#fun qlAmericanExercise{withDay*`Day',withDay*`Day',`Bool',preErrorCheck-`String'errorCheck*-}->`QlAmericanExercise'peekPtr*#}
{#fun qlAmericanExercise1{withDay*`Day',`Bool',preErrorCheck-`String'errorCheck*-}->`QlAmericanExercise'peekPtr*#}
{#fun qlBermudanExercise{withDayArray*`[Day]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`QlBermudanExercise'peekPtr*#}
{#fun qlEarlyExercise{`ExerciseType',`Bool',preErrorCheck-`String'errorCheck*-}->`QlExercise'peekPtr*#}
{#fun qlEuropeanExercise{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`QlEuropeanExercise'peekPtr*#}
{#fun qlSwingExercise{withDayArray*`[Day]'&,withIntArray*`[Word]'&,preErrorCheck-`String'errorCheck*-}->`QlSwingExercise'peekPtr*#}
{#fun qlSwingExercise1{withDay*`Day',withDay*`Day',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`QlSwingExercise'peekPtr*#}

withEuropeanExercise :: EuropeanExercise -> (QlEuropeanExercise -> IO a) -> IO a
withEuropeanExercise (EuropeanExercise d) f = qlEuropeanExercise d >>= newCastForeignPtr >>= flip withGenForeignPtr f

withSwingExercise :: SwingExercise -> (QlSwingExercise -> IO a) -> IO a
withSwingExercise (SwingListExercise ds) f = uncurry qlSwingExercise (unzip ds) >>= newCastForeignPtr >>= flip withGenForeignPtr f
withSwingExercise (SwingIntervalExercise d1 d2 s) f = qlSwingExercise1 d1 d2 s >>= newCastForeignPtr >>= flip withGenForeignPtr f

withBermudanExercise :: BermudanExercise -> (QlBermudanExercise -> IO a) -> IO a
withBermudanExercise (BermudanExercise d p) f = qlBermudanExercise d p >>= newCastForeignPtr >>= flip withGenForeignPtr f
withBermudanExercise (Swing e) f = withSwingExercise e (\sp -> upcast sp >>= \bp -> f bp `finally` freeUpcast bp)

withExercise :: Exercise -> (QlExercise -> IO a) -> IO a
withExercise (AmericanExercise Nothing d p) f = qlAmericanExercise1 d p >>= newGenForeignPtr >>= flip withGenForeignPtr f
withExercise (AmericanExercise (Just d0) d p) f = qlAmericanExercise d0 d p >>= newGenForeignPtr >>= flip withGenForeignPtr f
withExercise (Early t p) f = qlEarlyExercise t p >>= newCastForeignPtr >>= flip withGenForeignPtr f
withExercise (Vanilla t) f = qlExercise t >>= newCastForeignPtr >>= flip withGenForeignPtr f
withExercise (European e) f = withEuropeanExercise e (\ep -> upcast ep >>= \xp -> f xp `finally` freeUpcast xp)
withExercise (Bermudan e) f = withBermudanExercise e (\bp -> upcast bp >>= \xp -> f xp `finally` freeUpcast xp)

-- | use 'percentageStrikePayoff' to construct 'Payoff'
data PercentageStrikePayoff = PercentageStrikePayoff
      !OptionType -- ^type
      !Double -- ^moneyness

-- | use 'plainVanillaPayoff' to construct 'Payoff'
data PlainVanillaPayoff = PlainVanillaPayoff
      !OptionType -- ^type
      !Double -- ^strike

-- | use 'strikedPayoff' to construct 'Payoff'
data StrikedPayoff =
  AssetOrNothing
    !OptionType -- ^type
    !Double -- ^strike
  | CashOrNothing
      !OptionType -- ^type
      !Double -- ^strike
      !Double -- ^cashPayoff
  | Gap
      !OptionType -- ^type
      !Double -- ^strike
      !Double -- ^secondStrike
  | PercentageStrike !PercentageStrikePayoff
  | PlainVanilla !PlainVanillaPayoff
  | SuperFund
      !Double -- ^strike
      !Double -- ^secondStrike
  | SuperSharePayoff
      !Double -- ^strike
      !Double -- ^secondStrike
      !Double -- ^cashPayoff

withPercentageStrikePayoff :: PercentageStrikePayoff -> (QlPercentageStrikePayoff -> IO a) -> IO a
withPercentageStrikePayoff (PercentageStrikePayoff t m) f = qlPercentageStrikePayoff t m >>= newCastForeignPtr >>= flip withGenForeignPtr f

withPlainVanillaPayoff :: PlainVanillaPayoff -> (QlPlainVanillaPayoff -> IO a) -> IO a
withPlainVanillaPayoff (PlainVanillaPayoff t s) f = qlPlainVanillaPayoff t s >>= newCastForeignPtr >>= flip withGenForeignPtr f

withStrikedPayoff :: StrikedPayoff -> (QlStrikedTypePayoff -> IO a) -> IO a
withStrikedPayoff (AssetOrNothing t s) f = qlAssetOrNothingPayoff t s >>= newCastForeignPtr >>= flip withGenForeignPtr f
withStrikedPayoff (CashOrNothing t s c) f = qlCashOrNothingPayoff t s c >>= newCastForeignPtr >>= flip withGenForeignPtr f
withStrikedPayoff (Gap t s ss) f = qlGapPayoff t s ss >>= newCastForeignPtr >>= flip withGenForeignPtr f
withStrikedPayoff (PercentageStrike p) f = withPercentageStrikePayoff p (\pp -> upcast pp >>= \sp -> f sp `finally` freeUpcast sp)
withStrikedPayoff (PlainVanilla p) f = withPlainVanillaPayoff p (\pp -> upcast pp >>= \sp -> f sp `finally` freeUpcast sp)
withStrikedPayoff (SuperFund s ss) f = qlSuperFundPayoff s ss >>= newCastForeignPtr >>= flip withGenForeignPtr f
withStrikedPayoff (SuperSharePayoff s ss c) f = qlSuperSharePayoff s ss c >>= newCastForeignPtr >>= flip withGenForeignPtr f

data TypePayoff = Striked !StrikedPayoff
  | Floating !OptionType -- ^type
data BasketPayoff =
    Average
      !Payoff -- ^p
      !Word -- ^n
  | AverageMultiple
      !Payoff -- ^p
      ![Double] -- ^a
  | Max
      !Payoff -- ^p
  | Min
      !Payoff -- ^p
  | Spread
      !Payoff -- ^p

withTypePayoff :: TypePayoff -> (QlTypePayoff -> IO a) -> IO a
withTypePayoff (Floating t) f = qlFloatingTypePayoff t >>= newCastForeignPtr >>= flip withGenForeignPtr f
withTypePayoff (Striked s) f = withStrikedPayoff s (\sp -> upcast sp >>= \tp -> f tp `finally` freeUpcast tp)

withBasketPayoff :: BasketPayoff -> (QlBasketPayoff -> IO a) -> IO a
withBasketPayoff (Average p n) f = withPayoff p (\pp -> qlAverageBasketPayoff pp n >>= newCastForeignPtr >>= flip withGenForeignPtr f)
withBasketPayoff (AverageMultiple p a) f = withPayoff p (\pp -> qlAverageBasketPayoff1 pp a >>= newCastForeignPtr >>= flip withGenForeignPtr f)
withBasketPayoff (Max p) f = withPayoff p (\pp -> qlMaxBasketPayoff pp >>= newCastForeignPtr >>= flip withGenForeignPtr f)
withBasketPayoff (Min p) f = withPayoff p (\pp -> qlMinBasketPayoff pp >>= newCastForeignPtr >>= flip withGenForeignPtr f)
withBasketPayoff (Spread p) f = withPayoff p (\pp -> qlSpreadBasketPayoff pp >>= newCastForeignPtr >>= flip withGenForeignPtr f)

data Payoff =
    DoubleStickyRatchet
      !Double -- ^type1
      !Double -- ^type2
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^gearing3
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^spread3
      !Double -- ^initialValue1
      !Double -- ^initialValue2
      !Double -- ^accrualFactor
  | ForwardType
      !PositionType -- ^type
      !Double -- ^strike
  | RatchetMax
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^gearing3
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^spread3
      !Double -- ^initialValue1
      !Double -- ^initialValue2
      !Double -- ^accrualFactor
  | RatchetMin
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^gearing3
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^spread3
      !Double -- ^initialValue1
      !Double -- ^initialValue2
      !Double -- ^accrualFactor
  | Ratchet
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^initialValue
      !Double -- ^accrualFactor
  | StickyMax
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^gearing3
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^spread3
      !Double -- ^initialValue1
      !Double -- ^initialValue2
      !Double -- ^accrualFactor
  | StickyMin
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^gearing3
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^spread3
      !Double -- ^initialValue1
      !Double -- ^initialValue2
      !Double -- ^accrualFactor
  | Sticky
      !Double -- ^gearing1
      !Double -- ^gearing2
      !Double -- ^spread1
      !Double -- ^spread2
      !Double -- ^initialValue
      !Double -- ^accrualFactor
  | Type !TypePayoff
  | Basket !BasketPayoff


{#fun qlAssetOrNothingPayoff{`OptionType',`Double',preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'peekPtr*#}
{#fun qlAverageBasketPayoff{`QlPayoff',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'peekPtr*#}
{#fun qlCashOrNothingPayoff{`OptionType',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'peekPtr*#}
{#fun qlDoubleStickyRatchetPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlFloatingTypePayoff{`OptionType',preErrorCheck-`String'errorCheck*-}->`QlTypePayoff'peekPtr*#}
{#fun qlForwardTypePayoff{`PositionType',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlGapPayoff{`OptionType',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'peekPtr*#}
{#fun qlMaxBasketPayoff{`QlPayoff',preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'peekPtr*#}
{#fun qlMinBasketPayoff{`QlPayoff',preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'peekPtr*#}
{#fun qlPercentageStrikePayoff{`OptionType',`Double',preErrorCheck-`String'errorCheck*-}->`QlPercentageStrikePayoff'peekPtr*#}
{#fun qlPlainVanillaPayoff{`OptionType',`Double',preErrorCheck-`String'errorCheck*-}->`QlPlainVanillaPayoff'peekPtr*#}
{#fun qlRatchetMaxPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlRatchetMinPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlRatchetPayoff{`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlSpreadBasketPayoff{`QlPayoff',preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'peekPtr*#}
{#fun qlStickyMaxPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlStickyMinPayoff{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlStickyPayoff{`Double',`Double',`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlPayoff'peekPtr*#}
{#fun qlSuperFundPayoff{`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'peekPtr*#}
{#fun qlSuperSharePayoff{`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlStrikedTypePayoff'peekPtr*#}
{#fun qlAverageBasketPayoff1{`QlPayoff',withDoubleArray*`[Double]'&,preErrorCheck-`String'errorCheck*-}->`QlBasketPayoff'peekPtr*#}

withPayoff :: Payoff -> (QlPayoff -> IO a) -> IO a
withPayoff (DoubleStickyRatchet t1 t2 g1 g2 g3 s1 s2 s3 i1 i2 a) f = qlDoubleStickyRatchetPayoff t1 t2 g1 g2 g3 s1 s2 s3 i1 i2 a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (ForwardType t s) f = qlForwardTypePayoff t s >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (RatchetMax g1 g2 g3 s1 s2 s3 i1 i2 a) f = qlRatchetMaxPayoff g1 g2 g3 s1 s2 s3 i1 i2 a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (RatchetMin g1 g2 g3 s1 s2 s3 i1 i2 a) f = qlRatchetMinPayoff g1 g2 g3 s1 s2 s3 i1 i2 a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (Ratchet g1 g2 s1 s2 i a) f = qlRatchetPayoff g1 g2 s1 s2 i a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (StickyMax g1 g2 g3 s1 s2 s3 i1 i2 a) f = qlStickyMaxPayoff g1 g2 g3 s1 s2 s3 i1 i2 a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (StickyMin g1 g2 g3 s1 s2 s3 i1 i2 a) f = qlStickyMinPayoff g1 g2 g3 s1 s2 s3 i1 i2 a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (Sticky g1 g2 s1 s2 i a) f = qlStickyPayoff g1 g2 s1 s2 i a >>= newCastForeignPtr >>= flip withGenForeignPtr f
withPayoff (Type t) f = withTypePayoff t (\tp -> upcast tp >>= \pp -> f pp `finally` freeUpcast pp)
withPayoff (Basket b) f = withBasketPayoff b (\bp -> upcast bp >>= \pp -> f pp `finally` freeUpcast pp)

data Callability =
  Soft
    !(Double, BondPriceType)
    !Day
    !Double -- ^trigger
  | Callability
      !(Double, BondPriceType)
      !CallabilityType
      !Day

callability :: Callability -> IO (Standalone CQlCallability)
callability (Soft (p, t) d tg) = qlSoftCallability p t d tg
callability (Callability (p, t) ct d) = qlCallability p t ct d

newtype EnumMeta a b = EnumMeta (a -> IO (Standalone b))

withEnumType :: EnumMeta a b -> a -> (Ptr b -> IO c) -> IO c
withEnumType (EnumMeta t) x f = t x >>= (`withStandalone` f)

withMaybeEnumType :: EnumMeta a b -> Maybe a -> (Ptr b -> IO c) -> IO c
withMaybeEnumType (EnumMeta t) x f = maybe (f nullPtr) (\xx -> t xx >>= (`withStandalone` f)) x

withEnumTypeArray :: EnumMeta a b -> [a] -> ((CUInt, Ptr (Ptr b)) -> IO c) -> IO c
withEnumTypeArray m x f = withMany (withEnumType m) x (`withArray` (\px -> f (fromIntegral $ length x, px)))

callabilityMeta :: EnumMeta Callability CQlCallability
callabilityMeta = EnumMeta callability

withCallability :: Callability -> (Ptr CQlCallability -> IO a) -> IO a
withCallability = withEnumType callabilityMeta

withCallabilityArray :: [Callability] -> ((CUInt, Ptr (Ptr CQlCallability)) -> IO c) -> IO c
withCallabilityArray = withEnumTypeArray callabilityMeta

constraintMeta :: EnumMeta Constraint CConstraint
constraintMeta = EnumMeta constraint

roundingMeta :: EnumMeta Rounding CRounding
roundingMeta = EnumMeta rounding

withMaybeConstraint :: Maybe Constraint -> (Ptr CConstraint -> IO a) -> IO a
withMaybeConstraint = withMaybeEnumType constraintMeta

withMaybeRounding :: Maybe Rounding -> (Ptr CRounding -> IO a) -> IO a
withMaybeRounding = withMaybeEnumType roundingMeta

withConstraint :: Constraint -> (Ptr CConstraint -> IO a) -> IO a
withConstraint = withEnumType constraintMeta

withRounding :: Rounding -> (Ptr CRounding -> IO a) -> IO a
withRounding = withEnumType roundingMeta

fittedBondDiscountFittingMethodMeta :: EnumMeta FittingMethod CFittedBondDiscountCurveFittingMethod
fittedBondDiscountFittingMethodMeta = EnumMeta fittingMethod

withFittedBondDiscountCurveFittingMethod :: FittingMethod -> (Ptr CFittedBondDiscountCurveFittingMethod -> IO a) -> IO a
withFittedBondDiscountCurveFittingMethod = withEnumType fittedBondDiscountFittingMethodMeta

endCriteriaMeta :: EnumMeta EndCriteria CEndCriteria
endCriteriaMeta = EnumMeta endCriteria

withEndCriteria :: EndCriteria -> (Ptr CEndCriteria -> IO a) -> IO a
withEndCriteria = withEnumType endCriteriaMeta

fdmSchemeDescMeta :: EnumMeta FdmScheme CFdmSchemeDesc
fdmSchemeDescMeta = EnumMeta fdmScheme

withFdmSchemeDesc :: FdmScheme -> (Ptr CFdmSchemeDesc -> IO a) -> IO a
withFdmSchemeDesc = withEnumType fdmSchemeDescMeta

optimizationMethodMeta :: EnumMeta OptimizationMethod COptimizationMethod
optimizationMethodMeta = EnumMeta optimizationMethod

withOptimizationMethod :: OptimizationMethod -> (Ptr COptimizationMethod -> IO a) -> IO a
withOptimizationMethod = withEnumType optimizationMethodMeta

-- Payoff/Exercise with* functions are now defined directly, near their ADTs, using
-- Upcastable/GenForeignPtr (see QuantLib.Internal.Type) instead of EnumMeta'/IsQlPayoff/IsQlExercise.

-- |callability leaving to the holder the possibility to convert
{#fun qlSoftCallability{`Double',`BondPriceType',withDay*`Day',`Double',preErrorCheck-`String'errorCheck*-}->`QlCallability'peekCallability*#}
{#fun qlCallability{`Double',`BondPriceType',`CallabilityType',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`QlCallability'peekCallability*#}

data FittingMethod =
  CubicBSplines
    ![Double] -- ^knotVector (year fraction)
    !Bool -- ^constrainAtZero
  | ExponentialSplines !Bool
  | NelsonSiegel
  | SimplePolynomial
    !Word -- ^degree
    !Bool -- ^constrainAtZero
  | Svensson
  deriving (Show, Eq)

fittingMethod :: FittingMethod -> IO QlFittedBondDiscountCurveFittingMethod
fittingMethod (CubicBSplines k c) = qlCubicBSplinesFitting k c
fittingMethod (ExponentialSplines c) = qlExponentialSplinesFitting c
fittingMethod NelsonSiegel = qlNelsonSiegelFitting
fittingMethod (SimplePolynomial d c) = qlSimplePolynomialFitting d c
fittingMethod Svensson = qlSvenssonFitting

{#fun qlCubicBSplinesFitting{withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlExponentialSplinesFitting{`Bool',preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlNelsonSiegelFitting{preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlSimplePolynomialFitting{fromIntegral`Word',`Bool',preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlSvenssonFitting{preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}

data FdmScheme =
  FdmScheme
    !FdmSchemeType -- ^type
    !Double -- ^theta
    !Double -- ^mu
  | CraigSneyd
  | Douglas
  | ExplicitEuler
  | Hundsdorfer
  | ImplicitEuler
  | ModifiedCraigSneyd
  | ModifiedHundsdorfer

{#fun qlFdmSchemeDesc{`FdmSchemeType',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescCraigSneyd{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescDouglas{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescExplicitEuler{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescHundsdorfer{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescImplicitEuler{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescModifiedCraigSneyd{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}
{#fun qlFdmSchemeDescModifiedHundsdorfer{preErrorCheck-`String'errorCheck*-}->`QlFdmSchemeDesc'peekFdmSchemeDesc*#}

fdmScheme :: FdmScheme -> IO QlFdmSchemeDesc
fdmScheme (FdmScheme t th mu) = qlFdmSchemeDesc t th mu
fdmScheme CraigSneyd = qlFdmSchemeDescCraigSneyd
fdmScheme Douglas = qlFdmSchemeDescDouglas
fdmScheme ExplicitEuler = qlFdmSchemeDescExplicitEuler
fdmScheme Hundsdorfer = qlFdmSchemeDescHundsdorfer
fdmScheme ImplicitEuler = qlFdmSchemeDescImplicitEuler
fdmScheme ModifiedCraigSneyd = qlFdmSchemeDescModifiedCraigSneyd
fdmScheme ModifiedHundsdorfer = qlFdmSchemeDescModifiedHundsdorfer

data Constraint =
  Boundary
    !Double -- ^low
    !Double -- ^high
  | Composite
    !Constraint -- ^c1
    !Constraint -- ^c2
  | NoConstraint
  | PositiveConstraint

constraint :: Constraint -> IO QlConstraint
constraint (Boundary l h) = qlBoundaryConstraint l h
constraint (Composite c1 c2) = qlCompositeConstraint c1 c2
constraint NoConstraint = qlNoConstraint
constraint PositiveConstraint = qlPositiveConstraint

{#fun qlBoundaryConstraint{`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlConstraint'peekConstraint*#}
{#fun qlCompositeConstraint{withConstraint*`Constraint',withConstraint*`Constraint',preErrorCheck-`String'errorCheck*-}->`QlConstraint'peekConstraint*#}
{#fun qlNoConstraint{preErrorCheck-`String'errorCheck*-}->`QlConstraint'peekConstraint*#}
{#fun qlPositiveConstraint{preErrorCheck-`String'errorCheck*-}->`QlConstraint'peekConstraint*#}

data OptimizationMethod =
  LevenbergMarquardt
    !Double -- ^epsfcn
    !Double -- ^xtol
    !Double -- ^gtol
  | Simplex !Double -- ^lambda, characteristic length

optimizationMethod :: OptimizationMethod -> IO QlOptimizationMethod
optimizationMethod (LevenbergMarquardt e x g) = qlLevenbergMarquardt e x g
optimizationMethod (Simplex l) = qlSimplex l
{#fun qlLevenbergMarquardt{`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlOptimizationMethod'peekOptimizationMethod*#}
{#fun qlSimplex{`Double',preErrorCheck-`String'errorCheck*-}->`QlOptimizationMethod'peekOptimizationMethod*#}

data EndCriteria =
  EndCriteria
    !Word -- ^maxIterations
    !Word -- ^maxStationaryStateIterations
    !Double -- ^rootEpsilon
    !Double -- ^functionEpsilon
    !Double -- ^gradientNormEpsilon

endCriteria :: EndCriteria -> IO QlEndCriteria
endCriteria (EndCriteria m1 m2 e f g) = qlEndCriteria m1 m2 e f g
{#fun qlEndCriteria{fromIntegral`Word',fromIntegral`Word',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlEndCriteria'peekEndCriteria*#}

data Rounding = NoRounding
  | Rounding
    !Int -- ^precision
    !RoundingType
    !Int -- ^digit
  deriving (Show, Eq)

rounding :: Rounding -> IO QlRounding
rounding NoRounding = qlRounding
rounding (Rounding p t d) = qlRounding1 p t d

{#fun qlRounding{preErrorCheck-`String'errorCheck*-}->`QlRounding'peekRounding*#}
{#fun qlRounding1{`Int',`RoundingType',`Int',preErrorCheck-`String'errorCheck*-}->`QlRounding'peekRounding*#}

data LmCorrelationModel = ConstWrapperCorrelation LmCorrelationModel
  | ExponentialCorrelation Word -- ^size
    !Double -- ^rho
  | LinearExponentialCorrelation Word -- ^size
    !Double -- ^rho
    !Double -- ^beta
    !Word -- ^factors
  deriving (Show, Eq)

{#fun qlLmConstWrapperCorrelationModel{withStandalone*`QlLmCorrelationModel',preErrorCheck-`String'errorCheck*-}->`QlLmCorrelationModel'peekLmCorrelationModel*#}
{#fun qlLmExponentialCorrelationModel{fromIntegral`Word',`Double',preErrorCheck-`String'errorCheck*-}->`QlLmCorrelationModel'peekLmCorrelationModel*#}
{#fun qlLmLinearExponentialCorrelationModel{fromIntegral`Word',`Double',`Double',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`QlLmCorrelationModel'peekLmCorrelationModel*#}

correlationModel :: LmCorrelationModel -> IO QlLmCorrelationModel
correlationModel (ConstWrapperCorrelation m) = correlationModel m >>= qlLmConstWrapperCorrelationModel
correlationModel (ExponentialCorrelation s r) = qlLmExponentialCorrelationModel s r
correlationModel (LinearExponentialCorrelation s r b f) = qlLmLinearExponentialCorrelationModel s r b f

correlationModelMeta :: EnumMeta LmCorrelationModel CLmCorrelationModel
correlationModelMeta = EnumMeta correlationModel

withLmCorrelationModel :: LmCorrelationModel -> (Ptr CLmCorrelationModel -> IO a) -> IO a
withLmCorrelationModel = withEnumType correlationModelMeta

data LmVolatilityModel = ConstWrapperVolatility LmVolatilityModel
  | FixedVolatility ![Double] ![Double]
  | LinearExponentialVolatility ![Double] -- ^fixing times
    !Double -- ^a
    !Double -- ^b
    !Double -- ^c
    !Double -- ^d
  deriving (Show, Eq)

{#fun qlLmConstWrapperVolatilityModel{withStandalone*`QlLmVolatilityModel',preErrorCheck-`String'errorCheck*-}->`QlLmVolatilityModel'peekLmVolatilityModel*#}
{#fun qlLmFixedVolatilityModel{withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,preErrorCheck-`String'errorCheck*-}->`QlLmVolatilityModel'peekLmVolatilityModel*#}
{#fun qlLmLinearExponentialVolatilityModel{withDoubleArray*`[Double]'&,`Double',`Double',`Double',`Double',preErrorCheck-`String'errorCheck*-}->`QlLmVolatilityModel'peekLmVolatilityModel*#}

volatilityModel :: LmVolatilityModel -> IO QlLmVolatilityModel
volatilityModel (ConstWrapperVolatility m) = volatilityModel m >>= qlLmConstWrapperVolatilityModel
volatilityModel (FixedVolatility d1 d2) = qlLmFixedVolatilityModel d1 d2
volatilityModel (LinearExponentialVolatility s a b c d) = qlLmLinearExponentialVolatilityModel s a b c d

volatilityModelMeta :: EnumMeta LmVolatilityModel CLmVolatilityModel
volatilityModelMeta = EnumMeta volatilityModel

withLmVolatilityModel :: LmVolatilityModel -> (Ptr CLmVolatilityModel -> IO a) -> IO a
withLmVolatilityModel = withEnumType volatilityModelMeta

data Claim = FaceValue | FaceValueAccrual Bond
claimMeta :: EnumMeta Claim CQlClaim
claimMeta = EnumMeta claim

withClaim :: Claim -> (Ptr CQlClaim -> IO a) -> IO a
withClaim = withEnumType claimMeta

claim :: Claim -> IO QlClaim
claim FaceValue = qlFaceValueClaim
claim (FaceValueAccrual b) = qlFaceValueAccrualClaim b

-- |Claim on a notional
{#fun qlFaceValueClaim{preErrorCheck-`String'errorCheck*-}->`QlClaim'peekClaim*#}
-- |Claim on the notional of a reference security, including accrual
{#fun qlFaceValueAccrualClaim{withBond*`Bond',preErrorCheck-`String'errorCheck*-}->`QlClaim'peekClaim*#}

strikedPayoff :: StrikedPayoff -> Payoff
strikedPayoff = Type . Striked

percentageStrikePayoff :: PercentageStrikePayoff -> Payoff
percentageStrikePayoff = Type . Striked . PercentageStrike

plainVanillaPayoff :: PlainVanillaPayoff -> Payoff
plainVanillaPayoff = Type . Striked . PlainVanilla

swingExercise :: SwingExercise -> Exercise
swingExercise = Bermudan . Swing

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
