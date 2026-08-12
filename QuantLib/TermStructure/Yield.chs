{-# LANGUAGE FunctionalDependencies, FlexibleInstances, TemplateHaskell #-}
module QuantLib.TermStructure.Yield
  (
    YieldTermStructure
  , GenYieldTermStructure
  , BondHelper
  , RateHelper
  , SwapRateHelper
  , OISRateHelper
  , FittingMethod(..)
  , FittedBondDiscountCurve
  , fittedBondDiscountCurve
  , fittedBondDiscountCurve'
  , RelinkableYieldTermStructure
  , relinkableYieldTermStructure
  , linkTo
  , GenRateHelper

  , BootstrapTrait(..)
  , PillarChoice(..)
  , FuturesType(..)
  , CPIInterpolationType(..)
  , depositRateHelper'
  , depositRateHelper
  , fixedRateBondHelper
  , cpiBondHelper
  , discount'
  , swapRateHelper'
  , flatForward
  , flatForward'
  , zeroRate'
  , forwardRateForPeriod
  , forwardRate'
  , forwardRate
  , zeroRate
  , discount
  , fraRateHelper
  , bondHelper
  , oisRateHelper
  , oisRateHelper'
  , OISRateHelperOpts(..)
  , defaultOISRateHelperOpts
  , oisRateHelperFull
  , oisRateHelperFull'
  , swapRateHelper
  , forwardSpreadedTermStructure
  , zeroSpreadedTermStructure
  , bmaSwapRateHelper
  , fraIborRateHelper'
  , fraRateHelper'
  , fraIborRateHelper
  , futuresRateHelper'
  , futuresIborRateHelper
  , futuresRateHelper
  , impliedQuote
  , impliedTermStructure

  , asYieldTermStructure
  , asRateHelper

  , piecewiseZeroSpreadedTermStructure
  , quantoTermStructure
  , minimumCostValue
  , numberOfIterations

  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  , interpolatedZeroCurve
  , interpolatedForwardCurve
  , interpolatedDiscountCurve

  , underlying
  ) where
import QuantLib.Internal hiding(maxDate)
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import Language.Haskell.TH(mkName)
import Language.Haskell.TH.Lib(varT)
import QuantLib.Quote
import Data.Maybe(fromMaybe)
import qualified QuantLib.Instrument.Bond as Bond (BondPriceType)
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.CashFlow#}(RateAveragingType(..))
{#import QuantLib.Time.Calendar#}(BusinessDayConvention(..))
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency(..), DateGenerationRule(..))

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- breaking recursive dependencies with Index.InterestRate TermStructure.Volatilitiy modules
-- if you put all pointer declarations in a separate module
-- ch2s will not attach finalizers to foreign ptrs in other modules
-- I don't want to create extra modules just to workaround the issue with cyclic dependencies and this will not help with finalizers anyway
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlOvernightIndex as OvernightIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlSwap as Swap foreign -> CSwap' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap' nocode#}
{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap' nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlFittedBondDiscountCurve as FittedBondDiscountCurve foreign -> CFittedBondDiscountCurve' nocode#}
{#pointer *QlRelinkableYieldTermStructure as RelinkableYieldTermStructure foreign -> CRelinkableYieldTermStructure' nocode#}
{#pointer *QlRateHelper as RateHelper foreign -> CRateHelper' nocode#}
{#pointer *QlSwapRateHelper as SwapRateHelper foreign -> CSwapRateHelper' nocode#}
{#pointer *QlOISRateHelper as OISRateHelper foreign -> COISRateHelper' nocode#}
{#pointer *QlBondHelper as BondHelper foreign -> CBondHelper' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *FittedBondDiscountCurveFittingMethod as QlFittedBondDiscountCurveFittingMethod foreign -> CFittedBondDiscountCurveFittingMethod nocode#}

{#enum BootstrapTrait{} deriving(Show, Eq)#}
{#enum PillarChoice{} deriving(Show, Eq)#}
{#enum FuturesType{} deriving(Show, Eq)#}

-- OISRateHelperOpts bundles every trailing param oisRateHelper/oisRateHelper' hardcode
-- (see the comment above them, further down), pre-populated with upstream's own
-- defaults via defaultOISRateHelperOpts, overridden through record-update syntax at
-- the call site -- see the add-quantlib-options-record skill for why this exists as a
-- second entry point instead of widening oisRateHelper/oisRateHelper'
-- themselves. The three Calendar fields are Maybe here (unlike the raw binding's plain
-- Calendar) since a real Calendar is only obtainable in IO (`calendar Null`) and can't
-- live in a pure default record value -- oisRateHelperFull/oisRateHelperFull'
-- substitute a fresh Null calendar for Nothing, same as the narrow constructors do
-- today. This splice must stay textually before every {#fun#}-generated binding in
-- this file: c2hs always appends its raw foreign-import stubs at the physical end of
-- the generated module regardless of where in the .chs a {#fun#} hook appears, and a
-- top-level TH splice anywhere in between would otherwise split the file into
-- declaration groups that can't see each other, breaking every earlier {#fun#}
-- wrapper's reference to its own (always-last) foreign-import stub.
$(deriveOptionsRecord "OISRateHelperOpts" ["m"]
  [ ("oisTelescopicValueDates", [t|Bool|], [|False|])
  , ("oisPaymentLag", [t|Int|], [|0|])
  , ("oisPaymentConvention", [t|BusinessDayConvention|], [|Following|])
  , ("oisPaymentFrequency", [t|Frequency|], [|Annual|])
  , ("oisPaymentCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("oisForwardStart", [t|(Int, TimeUnit)|], [|(0, Days)|]) -- ^ignored by oisRateHelperFull' (ctor2 has no forwardStart)
  , ("oisOvernightSpread", [t|Maybe (GenQuote $(varT (mkName "m")))|], [|Nothing|])
  , ("oisPillar", [t|PillarChoice|], [|LastRelevantDate|])
  , ("oisCustomPillarDate", [t|Maybe Day|], [|Nothing|])
  , ("oisAveragingMethod", [t|RateAveragingType|], [|AveragingCompound|])
  , ("oisEndOfMonth", [t|Maybe Bool|], [|Nothing|])
  , ("oisFixedPaymentFrequency", [t|Maybe Frequency|], [|Nothing|])
  , ("oisFixedCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("oisLookbackDays", [t|Maybe Word|], [|Nothing|])
  , ("oisLockoutDays", [t|Word|], [|0|])
  , ("oisApplyObservationShift", [t|Bool|], [|False|])
  , ("oisPricer", [t|Maybe FloatingRateCouponPricer|], [|Nothing|])
  , ("oisRule", [t|DateGenerationRule|], [|Backward|])
  , ("oisOvernightCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("oisConvention", [t|BusinessDayConvention|], [|ModifiedFollowing|])
  ])

{#fun qlDepositRateHelper1 as depositRateHelper'{withQuote*`GenQuote a',withIborIndex*`GenIborIndex b',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlDepositRateHelper as depositRateHelper{withQuote*`GenQuote a' -- ^rate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFixedRateBondHelper as fixedRateBondHelper{withQuote*`GenQuote a',fromIntegral`Word',`Double',withSchedule*`Schedule',withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',`BusinessDayConvention',`Double',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}
-- |Bootstrap helper for a 'QuantLib.Instrument.Bond.CPIBond' -- a 'CPIBondHelper', which is a
-- plain 'BondHelper' subclass with no extra methods, so it's returned as the generic
-- 'BondHelper' type (same shape as 'fixedRateBondHelper').
{#fun qlCPIBondHelper as cpiBondHelper{withQuote*`GenQuote a',fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,`Double' -- ^baseCPI
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withSchedule*`Schedule',withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}

-- |Returns a discount factor from the given YieldTermStructure object
{#fun qlYieldTSDiscount as discount'{withYieldTermStructure*`GenYieldTermStructure a'
  ,withDay*`Day' -- ^d
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapRateHelper1 as swapRateHelper'{withQuote*`GenQuote a' -- ^rate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,withCalendar*`Calendar' -- ^calendar
  ,`Frequency' -- ^fixedFrequency
  ,`BusinessDayConvention' -- ^fixedConvention
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withIborIndex*`GenIborIndex b' -- ^iborIndex
  ,withMaybeQuote*`Maybe (GenQuote s)' -- ^spread
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^fwdStart
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure d)' -- ^discountingCurve
  ,fromMaybeInt`Maybe Word' -- ^settlementDays
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^floatConvention
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}
{#fun qlFlatForward as flatForward{withDay*`Day',withQuote*`GenQuote a',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlFlatForward1 as flatForward'{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar',withQuote*`GenQuote a',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
-- |The resulting interest rate has the required daycounting rule.
{#fun qlYieldTermStructureZeroRate as zeroRate'{withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
{#fun qlYieldTermStructureForwardRate1 as forwardRateForPeriod{withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',fromEnumQuantity`(Int,TimeUnit)'&,withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |The resulting interest rate has the required day-counting rule.
{#fun qlYieldTermStructureForwardRate as forwardRate'{withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',withDay*`Day',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
{#fun qlYieldTermStructureForwardRate2 as forwardRate{withYieldTermStructure*`GenYieldTermStructure a',`Double',`Double',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
{#fun qlYieldTermStructureZeroRate1 as zeroRate{withYieldTermStructure*`GenYieldTermStructure a',`Double',`Compounding',`Frequency',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlYieldTermStructureDiscount1 as discount{withYieldTermStructure*`GenYieldTermStructure a',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlFraRateHelper as fraRateHelper{withQuote*`GenQuote a' -- ^rate
  ,fromIntegral`Word' -- ^monthsToStart
  ,fromIntegral`Word' -- ^monthsToEnd
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
-- BondPriceType (QuantLib.Instrument.Bond) is later in exposed-modules than
-- this file, so priceType is marshalled as a plain Int via fromEnum here
-- instead of a {#import#}'d enum type, per CLAUDE.md's cross-module workaround.
bondHelper :: GenQuote a -> Bond -> Bond.BondPriceType -> IO BondHelper
bondHelper cleanPrice bond priceType = bondHelper_ cleanPrice bond (fromEnum priceType)

{#fun qlBondHelper as bondHelper_{withQuote*`GenQuote a',withBond*`Bond',`Int' -- ^priceType
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}
-- oisRateHelper/oisRateHelper' keep their original 5-param signatures (below);
-- both call the same full-arity raw bindings as oisRateHelperFull/oisRateHelperFull'
-- (the options-record wrappers spliced further down in this file), hardcoding
-- upstream's own defaults for every trailing param -- widening the underlying C
-- shim was cheaper than maintaining a second near-duplicate one (see
-- cbits/qlTermStructure.cpp's qlOISRateHelper/qlOISRateHelper2).
oisRateHelper :: Word -> (Int, TimeUnit) -> GenQuote a -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure b) -> IO OISRateHelper
oisRateHelper settlementDays tenor fixedRate idx discountingCurve = do
  cal <- calendar Null
  oisRateHelper_ settlementDays tenor fixedRate idx discountingCurve
    False 0 Following Annual cal (0, Days) Nothing LastRelevantDate Nothing AveragingCompound
    Nothing Nothing cal Nothing 0 False Nothing Backward cal ModifiedFollowing

oisRateHelper' :: Day -> Day -> GenQuote a -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure b) -> IO OISRateHelper
oisRateHelper' startDate endDate fixedRate idx discountingCurve = do
  cal <- calendar Null
  oisRateHelper2_ startDate endDate fixedRate idx discountingCurve
    False 0 Following Annual cal Nothing LastRelevantDate Nothing AveragingCompound
    Nothing Nothing cal Nothing 0 False Nothing Backward cal ModifiedFollowing

{#fun qlOISRateHelper as oisRateHelper_{fromIntegral`Word' -- ^settlementDays
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,withQuote*`GenQuote a'
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure b)' -- ^discountingCurve
  ,`Bool' -- ^telescopicValueDates
  ,fromIntegral`Int' -- ^paymentLag
  ,`BusinessDayConvention' -- ^paymentConvention
  ,`Frequency' -- ^paymentFrequency
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^forwardStart
  ,withMaybeQuote*`Maybe (GenQuote m)' -- ^overnightSpread
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`RateAveragingType' -- ^averagingMethod
  ,fromMaybeBool`Maybe Bool' -- ^endOfMonth
  ,fromMaybeEnum`Maybe Frequency' -- ^fixedPaymentFrequency
  ,withCalendar*`Calendar' -- ^fixedCalendar
  ,fromMaybeInt`Maybe Word' -- ^lookbackDays
  ,fromIntegral`Word' -- ^lockoutDays
  ,`Bool' -- ^applyObservationShift
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^pricer
  ,`DateGenerationRule' -- ^rule
  ,withCalendar*`Calendar' -- ^overnightCalendar
  ,`BusinessDayConvention' -- ^convention (a.k.a. overnightConvention)
  ,preErrorCheck-`String'errorCheck*-}->`OISRateHelper'peekOISRateHelper*#}
{#fun qlOISRateHelper2 as oisRateHelper2_{withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withQuote*`GenQuote a'
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure b)' -- ^discountingCurve
  ,`Bool' -- ^telescopicValueDates
  ,fromIntegral`Int' -- ^paymentLag
  ,`BusinessDayConvention' -- ^paymentConvention
  ,`Frequency' -- ^paymentFrequency
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,withMaybeQuote*`Maybe (GenQuote m)' -- ^overnightSpread
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`RateAveragingType' -- ^averagingMethod
  ,fromMaybeBool`Maybe Bool' -- ^endOfMonth
  ,fromMaybeEnum`Maybe Frequency' -- ^fixedPaymentFrequency
  ,withCalendar*`Calendar' -- ^fixedCalendar
  ,fromMaybeInt`Maybe Word' -- ^lookbackDays
  ,fromIntegral`Word' -- ^lockoutDays
  ,`Bool' -- ^applyObservationShift
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^pricer
  ,`DateGenerationRule' -- ^rule
  ,withCalendar*`Calendar' -- ^overnightCalendar
  ,`BusinessDayConvention' -- ^convention (a.k.a. overnightConvention)
  ,preErrorCheck-`String'errorCheck*-}->`OISRateHelper'peekOISRateHelper*#}

oisRateHelperFull :: Word -> (Int, TimeUnit) -> GenQuote a -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure b) -> OISRateHelperOpts m -> IO OISRateHelper
oisRateHelperFull settlementDays tenor fixedRate idx discountingCurve opts = do
  cal <- calendar Null
  oisRateHelper_ settlementDays tenor fixedRate idx discountingCurve
    (oisTelescopicValueDates opts) (oisPaymentLag opts) (oisPaymentConvention opts)
    (oisPaymentFrequency opts) (fromMaybe cal (oisPaymentCalendar opts))
    (oisForwardStart opts) (oisOvernightSpread opts) (oisPillar opts) (oisCustomPillarDate opts)
    (oisAveragingMethod opts) (oisEndOfMonth opts) (oisFixedPaymentFrequency opts)
    (fromMaybe cal (oisFixedCalendar opts)) (oisLookbackDays opts) (oisLockoutDays opts)
    (oisApplyObservationShift opts) (oisPricer opts) (oisRule opts)
    (fromMaybe cal (oisOvernightCalendar opts)) (oisConvention opts)

oisRateHelperFull' :: Day -> Day -> GenQuote a -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure b) -> OISRateHelperOpts m -> IO OISRateHelper
oisRateHelperFull' startDate endDate fixedRate idx discountingCurve opts = do
  cal <- calendar Null
  oisRateHelper2_ startDate endDate fixedRate idx discountingCurve
    (oisTelescopicValueDates opts) (oisPaymentLag opts) (oisPaymentConvention opts)
    (oisPaymentFrequency opts) (fromMaybe cal (oisPaymentCalendar opts))
    (oisOvernightSpread opts) (oisPillar opts) (oisCustomPillarDate opts)
    (oisAveragingMethod opts) (oisEndOfMonth opts) (oisFixedPaymentFrequency opts)
    (fromMaybe cal (oisFixedCalendar opts)) (oisLookbackDays opts) (oisLockoutDays opts)
    (oisApplyObservationShift opts) (oisPricer opts) (oisRule opts)
    (fromMaybe cal (oisOvernightCalendar opts)) (oisConvention opts)

{#fun qlSwapRateHelper as swapRateHelper{withQuote*`GenQuote a',withSwapIndex*`GenSwapIndex b',withMaybeQuote*`Maybe (GenQuote m)',fromEnumQuantity`(Int,TimeUnit)'&,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure c)'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}
{#fun qlForwardSpreadedTermStructure as forwardSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure b',withQuote*`GenQuote a',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlZeroSpreadedTermStructure as zeroSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure b',withQuote*`GenQuote a',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlBMASwapRateHelper as bmaSwapRateHelper{withQuote*`GenQuote a' -- ^liborFraction
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDAys
  ,withCalendar*`Calendar',fromEnumQuantity`(Int,TimeUnit)'& -- ^bmpPeriod
  ,`BusinessDayConvention',withDayCounter*`DayCounter',withBMAIndex*`BMAIndex',withIborIndex*`GenIborIndex b',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFraRateHelper1 as fraIborRateHelper'{withQuote*`GenQuote a',fromIntegral`Word' -- ^monthsToStart
  ,withIborIndex*`GenIborIndex b'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFraRateHelper2 as fraRateHelper'{withQuote*`GenQuote a',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,fromIntegral`Word' -- ^lengthInMonths
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar',`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFraRateHelper3 as fraIborRateHelper{withQuote*`GenQuote a',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,withIborIndex*`GenIborIndex b'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFuturesRateHelper1 as futuresRateHelper'{withQuote*`GenQuote a',withDay*`Day' -- ^immStartDate
  ,withDay*`Day' -- ^endDate
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote m)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFuturesRateHelper2 as futuresIborRateHelper{withQuote*`GenQuote a',withDay*`Day' -- ^immDate
  ,withIborIndex*`GenIborIndex b',withMaybeQuote*`Maybe (GenQuote m)',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFuturesRateHelper as futuresRateHelper{withQuote*`GenQuote a',withDay*`Day' -- ^immDate
  ,fromIntegral`Word' -- ^lengthInMonths
  ,withCalendar*`Calendar',`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote m)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlRateHelperImpliedQuote as impliedQuote{withRateHelper*`GenRateHelper a',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlImpliedTermStructure as impliedTermStructure{withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

piecewiseZeroSpreadedTermStructure :: GenYieldTermStructure b
  -> [(Day, GenQuote a)]  -- ^spreads
  -> Compounding -> Frequency -> IO YieldTermStructure
piecewiseZeroSpreadedTermStructure ts qd = qlPiecewiseZeroSpreadedTermStructure ts qs ds where (ds, qs) = unzip qd
{#fun qlPiecewiseZeroSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure b',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlQuantoTermStructure as quantoTermStructure{withYieldTermStructure*`GenYieldTermStructure a' -- ^underlyingDividendTS
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^foreignRsikFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^underlyingBlackVolTS
  ,`Double' -- ^strike
  ,withBlackVolTermStructure*`GenBlackVolTermStructure e' -- ^exchRateBlackVolTS
  ,`Double' -- ^exchRateATMlevel
  ,`Double' -- ^underlyingExchRateCorrelation
  ,preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
piecewiseYieldCurve :: Day -- ^referenceDate
  -> [GenRateHelper b] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote a)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve d r dc qd t i = uncurryNested (qlPiecewiseYieldCurve d r dc qs ds t) (qlInterpolation i) where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurve{withDay*`Day',withRateHelperArray*`[GenRateHelper b]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [GenRateHelper b] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote a)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurve' s cal r dc qd t i ex = uncurryNested (qlPiecewiseYieldCurve1 s cal r dc qs ds t) (qlInterpolation i) ex where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurve1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper b]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

interpolatedDiscountCurve :: [(Day, Double)] -- ^dates, dfs
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote a)] -- ^jumps
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedDiscountCurve r dc c qd i = uncurryNested (qlInterpolatedDiscountCurve rs rd dc c qs ds) (qlInterpolation i)
  where (rd, rs) = unzip r
        (ds, qs) = unzip qd
{#fun qlInterpolatedDiscountCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

interpolatedForwardCurve :: [(Day, Double)] -- ^dates, forwards
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote a)] -- ^jumps
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedForwardCurve r dc c qd i = uncurryNested (qlInterpolatedForwardCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip r; (ds, qs) = unzip qd}
{#fun qlInterpolatedForwardCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

interpolatedZeroCurve :: [(Day, Double)] -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote a)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve r dc c qd i = uncurryNested (qlInterpolatedZeroCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip r; (ds, qs) = unzip qd}
{#fun qlInterpolatedZeroCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
-- |reference date based on current evaluation date
{#fun qlFittedBondDiscountCurve as fittedBondDiscountCurve{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar',withBondHelperArray*`[BondHelper]'&,withDayCounter*`DayCounter',withFittedBondDiscountCurveFittingMethod*`FittingMethod'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,withDoubleArray*`[Double]'& -- ^guess
  ,`Double' -- ^simplexLambda
  ,preErrorCheck-`String'errorCheck*-}->`FittedBondDiscountCurve'peekFittedBondDiscountCurve*#}
-- |curve reference date fixed for life of curve
{#fun qlFittedBondDiscountCurve1 as fittedBondDiscountCurve'{withDay*`Day',withBondHelperArray*`[BondHelper]'&,withDayCounter*`DayCounter',withFittedBondDiscountCurveFittingMethod*`FittingMethod'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,withDoubleArray*`[Double]'& -- ^guess
  ,`Double' -- ^simplexLambda
,preErrorCheck-`String'errorCheck*-}->`FittedBondDiscountCurve'peekFittedBondDiscountCurve*#}

-- |final value of cost function after optimization
{#fun qlFittedBondDiscountCurveFittingMethodMinimumCostValue as minimumCostValue{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |final number of iterations used in the optimization problem
{#fun qlFittedBondDiscountCurveFittingMethodNumberOfIterations as numberOfIterations{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |A curve behind a relinkable handle. The result /is/ a 'YieldTermStructure': pass it to
-- any curve-taking function and everything built on it keeps tracking whatever the handle
-- currently points at, so a later 'linkTo' reprices already-constructed instruments
-- without rebuilding them. 'Nothing' gives an empty handle -- meaningful rather than an
-- error, since that is what makes a rate helper discount off the curve being bootstrapped
-- -- but reading a curve value through one throws until it is linked.
{#fun qlRelinkableYieldTermStructure as relinkableYieldTermStructure{withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure a)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableYieldTermStructure'peekRelinkableYieldTermStructure*#}

-- |Point a relinkable handle at a different curve. Everything already built on the handle
-- reprices against the new curve, with no object rebuilt.
--
-- This is the one mutator in the module. The API rules here otherwise forbid new setters
-- and prefer constructing a fresh object, but relinking /is/ the capability being bound:
-- a forecast curve is cloned into every floating coupon of every instrument, so without
-- it a curve scenario means rebuilding the whole portfolio.
{#fun qlRelinkableYieldTermStructureLinkTo as linkTo{withRelinkableYieldTermStructure*`RelinkableYieldTermStructure'
  ,withYieldTermStructure*`GenYieldTermStructure a',preErrorCheck-`String'errorCheck*-}->`()'#}

-- TODO use the class or decide it's not needed
class HelperUnderlying a b | a -> b where underlying :: a -> IO b

instance HelperUnderlying BondHelper Bond where underlying = qlBondHelperBond
{#fun qlBondHelperBond{withGenRateHelper*`BondHelper',preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

instance HelperUnderlying SwapRateHelper VanillaSwap where underlying = qlSwapRateHelperSwap
{#fun qlSwapRateHelperSwap{withGenRateHelper*`SwapRateHelper',preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

instance HelperUnderlying OISRateHelper OvernightIndexedSwap where underlying = qlOISRateHelperSwap
{#fun qlOISRateHelperSwap{withGenRateHelper*`OISRateHelper',preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
