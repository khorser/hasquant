{-# LANGUAGE TemplateHaskell, StandaloneDeriving, EmptyDataDecls #-}
-- internal utilities to convert special enums: either complex ones or represented as QuantLib objects that I didn't want to expose so I represented them as ADTs
{-# OPTIONS_GHC -Wno-unused-top-binds #-}
module QuantLib.Internal.Common
  (
    qlInterpolation
  , qlInterpolation'
  , Approximation(..)
  , Interpolation(..)
  , Interpolation2D(..)

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

  , CPIInterpolationType(..)

  , Constraint(..)
  , QlConstraint
  , withConstraint
  , withMaybeConstraint
  , OptimizationMethod(..)
  , QlOptimizationMethod
  , withOptimizationMethod
  , withMaybeOptimizationMethod
  , EndCriteria(..)
  , QlEndCriteria
  , withEndCriteria
  , withMaybeEndCriteria

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
  , BusinessDayConvention(..)

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

  , CalibrationBasketType(..)

  , UnitOfMeasureType(..)
  , PaymentTermEventType(..)
  , PricingErrorLevel(..)
  , peekPricingErrorLevelArray
  , DeliverySchedule(..)
  , QuantityPeriodicity(..)

  , AdditionalResultType(..)
  , AdditionalResultVal(..)
  , RawResultPtr
  , RawResult(..)
  , convertResult
  , peekAdditionalResults
  ) where
import Foreign.Ptr(Ptr, nullPtr, castPtr)
import Foreign.C.Types(CUInt, CInt, CDouble)
import Foreign.C.String(CString, peekCString)
import Foreign.Storable(Storable(..))
import Foreign.Marshal.Utils(withMany)
import Foreign.Marshal.Array(withArray, peekArray)
import Control.Exception(finally)

import QuantLib.Internal
import QuantLib.Internal.Type hiding(ptr)
import QuantLib.Internal.Syntax

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

-- this enum is not special, just used in many places and was put here to avoid cyclic dependencies
{#enum TimeUnit{} deriving(Show, Eq, Read, Bounded)#}
-- moved from QuantLib.Time.Calendar, its "natural" home, for the same reason as TimeUnit above --
-- needed directly here for RebatedExercise's rebatePaymentConvention param. Like TimeUnit, every
-- cross-module use marshals through a manual fromEnumC/toEnumC/fromMaybeEnum function rather than
-- a bare c2hs backtick spec: a bare `` `BusinessDayConvention' `` needs the type's own module's
-- .chi already built, which this other-modules-listed module isn't guaranteed to have by the time
-- an early exposed-modules file (e.g. QuantLib.Time.Calendar itself) is processed.
{#enum BusinessDayConvention{} deriving(Show, Eq, Read)#}
{#enum ApproximationType{} add prefix="Approximation__" deriving(Show, Eq, Read)#}
{#enum InterpolationType{} add prefix="Interpolation" deriving(Show, Eq, Read)#}
-- 2-D interpolators for a BlackVarianceSurface. Unlike InterpolationType/ApproximationType
-- above (merged into the public Interpolation ADT by deriveCrossEnum), this enum is itself the
-- public type: setInterpolation on a surface is a member template over a default-constructed
-- interpolator, so there is no approximator to pair it with. Declared here rather than in
-- QuantLib.TermStructure.Volatility for the usual cross-module {#import#} ordering reason.
{#enum Interpolation2D{} deriving (Show, Eq, Read, Bounded)#}
{#enum ExerciseType{} add prefix = "ExerciseType" deriving (Show, Eq, Read)#}
{#enum OptionType{} deriving (Show, Eq, Read)#}
{#enum PositionType{} deriving (Show, Eq, Read)#}
{#enum BondPriceType{} deriving (Show, Eq, Read)#}
{#enum CallabilityType{} add prefix="Callability" deriving(Show, Eq, Read)#}
{#enum FdmSchemeType{} deriving(Show, Eq, Read)#}
{#enum RoundingType{} deriving (Show, Eq, Read)#}
-- experimental/commodities: cross-cutting the same way TimeUnit is (UnitOfMeasureType is used by
-- both UnitOfMeasure itself and, in a later stage, CommodityPricingHelper/EnergyCommodity).
-- Quantity's C tag is renamed QuantityUnit in cbits/qlEnumC2HS.h to avoid colliding with the
-- Quantity class bound in QuantLib.Commodity.
{#enum UnitOfMeasureType{} deriving (Show, Eq, Read, Bounded)#}
{#enum PaymentTermEventType{} deriving (Show, Eq, Read, Bounded)#}
-- experimental/commodities/commodity.hpp (PricingError::Level) and
-- experimental/commodities/energycommodity.hpp (EnergyCommodity::DeliverySchedule,
-- EnergyCommodity::QuantityPeriodicity), homed here for the same cross-cutting reason as
-- UnitOfMeasureType above (used by both EnergyCommodity's leaf constructors and
-- CommodityPricingHelper::createPricingPeriods, both in QuantLib.Instrument.Energy -- a later
-- stage than this module).
{#enum PricingErrorLevel{} deriving (Show, Eq, Read, Bounded)#}
peekPricingErrorLevelArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [PricingErrorLevel]
peekPricingErrorLevelArray = peekIntArray' toEnumC
-- Confirmed clash (a real one, caught by the build, not assumed): 4 of DeliverySchedule's 8 tags
-- (Daily/Weekly/Monthly/Quarterly) collide with QuantLib.Time.Schedule's own Frequency enum, whose
-- module this file is imported into unqualified. Prefixed Haskell-side only (c2hs's own "add
-- prefix", not a cbits/qlEnumC2HS.h rename) -- same targeted-rename convention as
-- UnitOfMeasureType's Quantity->QuantityUnit above, not a blanket defensive prefix.
{#enum DeliverySchedule{} add prefix = "Delivery" deriving (Show, Eq, Read, Bounded)#}
{#enum QuantityPeriodicity{} deriving (Show, Eq, Read, Bounded)#}
-- flat/linear interpolation of a CPI index between its publication dates -- skips the
-- deprecated AsIndex upstream case, so cbits/qlEnumObjects.h's values (and thus this
-- c2hs-derived enum's fromEnum) start at 1, not 0; see that header's comment for why a
-- renumbered-from-0 enum here would silently alias to the wrong upstream case. Declared here
-- (not in QuantLib.TermStructure.Inflation, its "natural" home) for the same reason as
-- TimeUnit above: needed by several modules whose build order can't all safely {#import#} that
-- module (built before it, or -- for QuantLib.TermStructure.Yield -- mutually dependent with
-- it already).
{#enum CPIInterpolationType{} deriving (Show, Eq, Read, Bounded)#}
{#enum CalibrationBasketType{} deriving (Show, Eq, Read, Bounded)#}

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
type QlRebatedExercise = Ptr CRebatedExercise'
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
{#pointer *QlRebatedExercise nocode#}
{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *QlCallability foreign -> CQlCallability nocode#}
{#pointer *QlOptimizationMethod as QlOptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *QlEndCriteria as QlEndCriteria foreign -> CEndCriteria nocode#}
{#pointer *Constraint as QlConstraint foreign -> CConstraint nocode#}
{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}
{#pointer *FittedBondDiscountCurveFittingMethod as QlFittedBondDiscountCurveFittingMethod foreign -> CFittedBondDiscountCurveFittingMethod nocode#}
{#pointer *QlClaim as Claim foreign -> CQlClaim nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlLmCorrelationModel foreign -> CLmCorrelationModel nocode#}
{#pointer *QlLmVolatilityModel foreign -> CLmVolatilityModel nocode#}
{#pointer *Rounding as QlRounding foreign -> CRounding nocode#}

-- monotonic flag for CubicInterpolation::Spline/::Parabolic -- tells deriveCrossEnum to give
-- these two values a runtime Bool field instead of cross-producting named sub-values (same
-- pattern as Actual360Convention etc. in CalendarEnum.chs). Order matters here in a way it
-- doesn't for the ApproximationType enum itself: these two type synonyms (and ApproximationExtra
-- below) must be declared textually *above* the deriveCrossEnum splice, since a TH splice can
-- only see top-level declarations that already exist earlier in the same module -- classifySub's
-- lookupTypeName would silently miss them (falling back to NoSub, dropping the Bool field) if
-- they were moved below the splice.
type NaturalSplineMonotonic = Bool
type ParabolicMonotonic = Bool

-- every Approximation case is driven by ApproximationType itself, so unlike
-- CalendarExtra/DayCounterExtra/IborExtra there are no non-enum-driven cases to add here
data ApproximationExtra

$(deriveCrossEnum CrossEnumSpec
    { crossTypeName = "Approximation"
    , crossMapperFn = "qlApproximation"
    , crossMainEnum = ''ApproximationType
    , crossSubSuffix = "Monotonic"
    , crossExtraType = ''ApproximationExtra
    })

deriving instance Show Approximation
deriving instance Eq Approximation
deriving instance Read Approximation

-- Remaining cpp<->hs lockstep, unlike CalendarConstructor/DayCounterConstructor/IborConstructor:
-- those own a full C-side array/table, so *every* lockstep edit needed for a new value stays
-- inside cbits/. Approximation/Interpolation instead get dispatched via symbolic switch-case on
-- the shared enum (cbits/qlTermStructure.cpp's setInterpolation, and ~18 duplicated
-- switch(interpolator){switch(approximator){...}} sites in cbits/qlTermStructureAux.cpp, one per
-- PiecewiseYieldCurve trait/interpolator instantiation). Adding a new ApproximationType/
-- InterpolationType value to cbits/qlEnumObjects.h is zero-touch here on the Haskell side
-- (deriveCrossEnum picks it up automatically, defaulting to a nullary constructor unless a
-- <Value>Monotonic marker is added above), but each cbits switch still needs a matching
-- `case hasquant::NewValue:` by hand -- a missed one isn't a compile error, just a runtime
-- QL_FAIL("Unsupported ..."), exactly the pre-existing gap Abcd fell into (see the comment next
-- to setInterpolation's default case in qlTermStructure.cpp).

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

-- | > Exercise
-- >  American
-- >  Early
-- >  Vanilla
-- >  EuropeanExercise
-- >  BermudanExercise
-- >    SwingExercise
-- >  Rebated (wraps another Exercise)
data Exercise =
    American
      !(Maybe Day) -- ^earliestDate
      !Day -- ^latestDate
      !Bool -- ^paoffAtExpiry
    | Early !ExerciseType !Bool
    | Vanilla !ExerciseType
    | European !EuropeanExercise
    | Bermudan !BermudanExercise
    | Rebated
        !Exercise -- ^wrapped exercise
        !Double -- ^rebate
        !Word -- ^rebateSettlementDays
        !Calendar -- ^rebatePaymentCalendar
        !BusinessDayConvention -- ^rebatePaymentConvention

{#fun qlExercise{`ExerciseType',preErrorCheck-`String'errorCheck*-}->`QlExercise'peekPtr*#}
{#fun qlAmericanExercise{withDay*`Day',withDay*`Day',`Bool',preErrorCheck-`String'errorCheck*-}->`QlAmericanExercise'peekPtr*#}
{#fun qlAmericanExercise1{withDay*`Day',`Bool',preErrorCheck-`String'errorCheck*-}->`QlAmericanExercise'peekPtr*#}
{#fun qlBermudanExercise{withDayArray*`[Day]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`QlBermudanExercise'peekPtr*#}
{#fun qlEarlyExercise{`ExerciseType',`Bool',preErrorCheck-`String'errorCheck*-}->`QlExercise'peekPtr*#}
{#fun qlEuropeanExercise{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`QlEuropeanExercise'peekPtr*#}
{#fun qlSwingExercise{withDayArray*`[Day]'&,withIntArray*`[Word]'&,preErrorCheck-`String'errorCheck*-}->`QlSwingExercise'peekPtr*#}
{#fun qlSwingExercise1{withDay*`Day',withDay*`Day',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`QlSwingExercise'peekPtr*#}
{#fun qlRebatedExercise{`QlExercise',`Double',fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',preErrorCheck-`String'errorCheck*-}->`QlRebatedExercise'peekPtr*#}

withEuropeanExercise :: EuropeanExercise -> (QlEuropeanExercise -> IO a) -> IO a
withEuropeanExercise (EuropeanExercise d) f = qlEuropeanExercise d >>= newCastForeignPtr >>= flip withGenForeignPtr f

withSwingExercise :: SwingExercise -> (QlSwingExercise -> IO a) -> IO a
withSwingExercise (SwingListExercise ds) f = uncurry qlSwingExercise (unzip ds) >>= newCastForeignPtr >>= flip withGenForeignPtr f
withSwingExercise (SwingIntervalExercise d1 d2 s) f = qlSwingExercise1 d1 d2 s >>= newCastForeignPtr >>= flip withGenForeignPtr f

withBermudanExercise :: BermudanExercise -> (QlBermudanExercise -> IO a) -> IO a
withBermudanExercise (BermudanExercise d p) f = qlBermudanExercise d p >>= newCastForeignPtr >>= flip withGenForeignPtr f
withBermudanExercise (Swing e) f = withSwingExercise e (\sp -> upcast sp >>= \bp -> f bp `finally` freeUpcast bp)

withExercise :: Exercise -> (QlExercise -> IO a) -> IO a
withExercise (American Nothing d p) f = qlAmericanExercise1 d p >>= newGenForeignPtr >>= flip withGenForeignPtr f
withExercise (American (Just d0) d p) f = qlAmericanExercise d0 d p >>= newGenForeignPtr >>= flip withGenForeignPtr f
withExercise (Early t p) f = qlEarlyExercise t p >>= newCastForeignPtr >>= flip withGenForeignPtr f
withExercise (Vanilla t) f = qlExercise t >>= newCastForeignPtr >>= flip withGenForeignPtr f
withExercise (European e) f = withEuropeanExercise e (\ep -> upcast ep >>= \xp -> f xp `finally` freeUpcast xp)
withExercise (Bermudan e) f = withBermudanExercise e (\bp -> upcast bp >>= \xp -> f xp `finally` freeUpcast xp)
withExercise (Rebated e rebate days cal bdc) f = withExercise e (\ep -> qlRebatedExercise ep rebate days cal bdc >>= newGenForeignPtr >>= flip withGenForeignPtr f)

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

-- | > Payoff
-- >  DoubleStickyRatchet
-- >  ForwardType
-- >  RatchettMax
-- >  RatchetMin
-- >  StickyMax
-- >  StickyMin
-- >  Sticky
-- >  TypePayoff
-- >    Floating
-- >    Striked
-- >      AssetOrNothing
-- >      CashOrNothing
-- >      Gap
-- >      PercentageStrike
-- >      PlainVanilla
-- >      SuperFund
-- >      SuperSharePayoff
-- >  BasketPayoff
-- >    Average
-- >    AverageMultiple
-- >    Max
-- >    Min
-- >    Spread
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

withMaybeEndCriteria :: Maybe EndCriteria -> (Ptr CEndCriteria -> IO a) -> IO a
withMaybeEndCriteria = withMaybeEnumType endCriteriaMeta

fdmSchemeDescMeta :: EnumMeta FdmScheme CFdmSchemeDesc
fdmSchemeDescMeta = EnumMeta fdmScheme

withFdmSchemeDesc :: FdmScheme -> (Ptr CFdmSchemeDesc -> IO a) -> IO a
withFdmSchemeDesc = withEnumType fdmSchemeDescMeta

optimizationMethodMeta :: EnumMeta OptimizationMethod COptimizationMethod
optimizationMethodMeta = EnumMeta optimizationMethod

withOptimizationMethod :: OptimizationMethod -> (Ptr COptimizationMethod -> IO a) -> IO a
withOptimizationMethod = withEnumType optimizationMethodMeta

withMaybeOptimizationMethod :: Maybe OptimizationMethod -> (Ptr COptimizationMethod -> IO a) -> IO a
withMaybeOptimizationMethod = withMaybeEnumType optimizationMethodMeta

-- Payoff/Exercise with* functions are now defined directly, near their ADTs, using
-- Upcastable/GenForeignPtr (see QuantLib.Internal.Type) instead of EnumMeta'/IsQlPayoff/IsQlExercise.

-- |callability leaving to the holder the possibility to convert
{#fun qlSoftCallability{`Double',`BondPriceType',withDay*`Day',`Double',preErrorCheck-`String'errorCheck*-}->`QlCallability'peekCallability*#}
{#fun qlCallability{`Double',`BondPriceType',`CallabilityType',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`QlCallability'peekCallability*#}

-- Every constructor below binds the QuantLib overload's leading optimizationMethod param via a
-- trailing Maybe OptimizationMethod field (Nothing -> upstream's own empty-shared_ptr default,
-- letting the fit fall back to LevenbergMarquardt). OptimizationMethod's hasquant-side handle
-- (QlOptimizationMethod) is a shared_ptr box, not a raw Haskell-finalized pointer -- see the
-- qlaux.h comment above the QlEndCriteria/QlOptimizationMethod typedefs -- so a caller-supplied
-- one can safely be copied into FittingMethod's own shared_ptr member (and survive
-- FittedBondDiscountCurve cloning the fitting method) regardless of when Haskell's own box is
-- collected.
data FittingMethod =
  CubicBSplines
    ![Double] -- ^knotVector (year fraction)
    !Bool -- ^constrainAtZero
    ![Double] -- ^weights
    ![Double] -- ^l2
    !Double -- ^minCutoffTime
    !Double -- ^maxCutoffTime
    !(Maybe Constraint)
    !(Maybe OptimizationMethod)
  | ExponentialSplines
    !Bool -- ^constrainAtZero
    ![Double] -- ^weights
    ![Double] -- ^l2
    !Double -- ^minCutoffTime
    !Double -- ^maxCutoffTime
    !Word -- ^numCoeffs
    !(Maybe Double) -- ^fixedKappa
    !(Maybe Constraint)
    !(Maybe OptimizationMethod)
  | NelsonSiegel
    ![Double] -- ^weights
    ![Double] -- ^l2
    !Double -- ^minCutoffTime
    !Double -- ^maxCutoffTime
    !(Maybe Constraint)
    !(Maybe OptimizationMethod)
  | SimplePolynomial
    !Word -- ^degree
    !Bool -- ^constrainAtZero
    ![Double] -- ^weights
    ![Double] -- ^l2
    !Double -- ^minCutoffTime
    !Double -- ^maxCutoffTime
    !(Maybe Constraint)
    !(Maybe OptimizationMethod)
  | Svensson
    ![Double] -- ^weights
    ![Double] -- ^l2
    !Double -- ^minCutoffTime
    !Double -- ^maxCutoffTime
    !(Maybe Constraint)
    !(Maybe OptimizationMethod)

fittingMethod :: FittingMethod -> IO QlFittedBondDiscountCurveFittingMethod
fittingMethod (CubicBSplines k c w l2 mn mx cn om) = qlCubicBSplinesFitting k c w l2 mn mx om cn
fittingMethod (ExponentialSplines c w l2 mn mx n fk cn om) = qlExponentialSplinesFitting c w l2 mn mx n fk om cn
fittingMethod (NelsonSiegel w l2 mn mx cn om) = qlNelsonSiegelFitting w l2 mn mx om cn
fittingMethod (SimplePolynomial d c w l2 mn mx cn om) = qlSimplePolynomialFitting d c w l2 mn mx om cn
fittingMethod (Svensson w l2 mn mx cn om) = qlSvenssonFitting w l2 mn mx om cn

{#fun qlCubicBSplinesFitting{withDoubleArray*`[Double]'&,`Bool'
  ,withDoubleArray*`[Double]'& -- ^weights
  ,withDoubleArray*`[Double]'& -- ^l2
  ,`Double' -- ^minCutoffTime
  ,`Double' -- ^maxCutoffTime
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withMaybeConstraint*`Maybe Constraint'
  ,preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlExponentialSplinesFitting{`Bool'
  ,withDoubleArray*`[Double]'& -- ^weights
  ,withDoubleArray*`[Double]'& -- ^l2
  ,`Double' -- ^minCutoffTime
  ,`Double' -- ^maxCutoffTime
  ,fromIntegral`Word' -- ^numCoeffs
  ,fromMaybeDouble`Maybe Double' -- ^fixedKappa
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withMaybeConstraint*`Maybe Constraint'
  ,preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlNelsonSiegelFitting{withDoubleArray*`[Double]'& -- ^weights
  ,withDoubleArray*`[Double]'& -- ^l2
  ,`Double' -- ^minCutoffTime
  ,`Double' -- ^maxCutoffTime
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withMaybeConstraint*`Maybe Constraint'
  ,preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlSimplePolynomialFitting{fromIntegral`Word',`Bool'
  ,withDoubleArray*`[Double]'& -- ^weights
  ,withDoubleArray*`[Double]'& -- ^l2
  ,`Double' -- ^minCutoffTime
  ,`Double' -- ^maxCutoffTime
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withMaybeConstraint*`Maybe Constraint'
  ,preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}
{#fun qlSvenssonFitting{withDoubleArray*`[Double]'& -- ^weights
  ,withDoubleArray*`[Double]'& -- ^l2
  ,`Double' -- ^minCutoffTime
  ,`Double' -- ^maxCutoffTime
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withMaybeConstraint*`Maybe Constraint'
  ,preErrorCheck-`String'errorCheck*-}->`QlFittedBondDiscountCurveFittingMethod'peekFittedBondDiscountCurveFittingMethod*#}

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
    !Bool -- ^useCostFunctionsJacobian
  | Simplex !Double -- ^lambda, characteristic length

optimizationMethod :: OptimizationMethod -> IO QlOptimizationMethod
optimizationMethod (LevenbergMarquardt e x g j) = qlLevenbergMarquardt e x g j
optimizationMethod (Simplex l) = qlSimplex l
{#fun qlLevenbergMarquardt{`Double',`Double',`Double',`Bool',preErrorCheck-`String'errorCheck*-}->`QlOptimizationMethod'peekOptimizationMethod*#}
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

-- |One value from QuantLib's `Instrument::additionalResults()` map. QuantLib stores the map as
-- `ext::any`, so this Haskell view picks three concrete shapes -- `Real` (`Double`), `std::string`
-- (`String`), `std::vector<Real>` (`[Double]`) -- plus an `UnsupportedVal` fallback recording the
-- value's C++ RTTI type name, so no key is ever silently dropped or mislabelled.
data AdditionalResultVal = RealVal Double | StringVal String | RealVectorVal [Double] | UnsupportedVal String
  deriving (Show, Eq)

-- |Discriminants for `QlAdditionalResult.type`, bound from `enum AdditionalResultType` in
-- `cbits/qlInstrument.h` (read from the header, not hardcoded).
{#enum AdditionalResultType {} deriving (Show, Eq, Read) #}

-- |Registers `struct QlAdditionalResult*` with c2hs as `RawResultPtr`, `nocode` since we supply
-- the Haskell type ourselves (below) rather than a c2hs-generated wrapper. This is what lets the
-- `additionalResults` `{#fun#}` binding (in `QuantLib.Instrument`)'s low-level array-of-structs
-- out-parameter (C type `struct QlAdditionalResult **`) be typed `Ptr RawResultPtr` =
-- `Ptr (Ptr RawResult)`, instead of defaulting to an opaque `Ptr (Ptr ())`.
{#pointer *QlAdditionalResult as RawResultPtr nocode#}
type RawResultPtr = Ptr RawResult

-- |One raw `QlAdditionalResult` entry, peeked field-by-field via c2hs `{#get#}` hooks. Its
-- `Storable` instance (`sizeOf`/`alignment` from `{#sizeof#}`/`{#alignof#}`, both read straight
-- from the C struct layout, not hand-computed) is what lets `peekStructArray`
-- (`QuantLib.Internal`) walk the C array via a plain `peekArray`, rather than hand-rolled pointer
-- arithmetic.
data RawResult = RawResult
  { rKey :: CString, rType :: CInt, rDval :: CDouble
  , rSval :: CString, rVarr :: Ptr CDouble, rVlen :: CUInt }

instance Storable RawResult where
  sizeOf _ = {#sizeof QlAdditionalResult #}
  alignment _ = {#alignof QlAdditionalResult #}
  peek p = RawResult <$> {#get QlAdditionalResult.key #} p
                      <*> {#get QlAdditionalResult.type #} p
                      <*> {#get QlAdditionalResult.dval #} p
                      <*> {#get QlAdditionalResult.sval #} p
                      <*> {#get QlAdditionalResult.varr #} p
                      <*> {#get QlAdditionalResult.vlen #} p
  poke = error "RawResult is peek-only (read from C, never constructed in Haskell)"

-- |Convert one raw entry into its keyed Haskell value. `sval`/`varr` are only read for the
-- discriminant that owns them; their buffers are released in bulk afterwards, by
-- `qlFreeAdditionalResults`, not per-field here.
convertResult :: RawResult -> IO (String, AdditionalResultVal)
convertResult r = do
  key <- peekCString (rKey r)
  val <- case toEnum (fromIntegral (rType r)) of
    AdditionalResultDouble -> return (RealVal (realToFrac (rDval r)))
    AdditionalResultString -> StringVal <$> peekCString (rSval r)
    AdditionalResultDoubleVector -> RealVectorVal . map realToFrac
                                       <$> peekArray (fromIntegral (rVlen r)) (rVarr r)
    AdditionalResultUnknown -> UnsupportedVal <$> peekCString (rSval r)
  return (key, val)

-- |Peek the C array of `QlAdditionalResult` into a keyed list, then release the whole array (keys,
-- `sval`/`varr` buffers, and the array itself) in one `qlFreeAdditionalResults` call.
peekAdditionalResults :: Ptr CUInt -> Ptr RawResultPtr -> IO [(String, AdditionalResultVal)]
peekAdditionalResults = peekStructArray convertResult (\l p -> qlFreeAdditionalResults l (castPtr p))

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
