{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Yield
  (
    -- * Types
    -- ** Curves and helpers
    GenYieldTermStructure
  , YieldTermStructure
  , RelinkableYieldTermStructure
  , FittedBondDiscountCurve
  , MultiCurve
  , GenRateHelper
  , RateHelper
  , BondHelper
  , SwapRateHelper
  , OISRateHelper
  , FuturesRateHelper
  , OvernightIndexFutureRateHelper

    -- ** Coordinates
  , Reference(..)
  , TermPoint(..)
  , RatePoint(..)

    -- ** Bootstrap and contract configuration
  , FittingMethod(..)
  , BootstrapTrait(..)
  , PillarChoice(..)
  , FuturesType(..)
  , DepositTerms(..)
  , FraTerms(..)
  , SwapRateTerms(..)
  , OisTerms(..)
  , FxSwapTerms(..)
  , FuturesTerms(..)
  , OISRateHelperOpts(..)
  , OvernightObservation(..)
  , IterativeBootstrapOpts(..)
  , Bootstrap(..)
  , LocalBootstrapTrait(..)
  , SpreadBootstrap(..)

    -- * Constructors
    -- ** Hierarchy and handles
  , asYieldTermStructure
  , asRateHelper
  , relinkableYieldTermStructure
    -- ** Flat, fitted and derived curves
  , fittedBondDiscountCurve
  , flatForward
  , forwardSpreadedTermStructure
  , zeroSpreadedTermStructure
  , withCompositeZeroYieldStructure
  , impliedTermStructure
  , piecewiseZeroSpreadedTermStructure
  , piecewiseForwardSpreadedTermStructure
  , quantoTermStructure
  , ultimateForwardTermStructure
    -- ** Rate helpers
  , depositRateHelper
  , fixedRateBondHelper
  , fraRateHelper
  , bondHelper
  , oisRateHelper
  , defaultOisRateHelperOpts
  , defaultOvernightObservation
  , oisRateHelperWithOptions
  , swapRateHelper
  , bmaSwapRateHelper
  , multipleResetsSwapRateHelper
  , futuresRateHelper
  , overnightIndexFutureRateHelper
  , sofrFutureRateHelper
    -- ** Bootstrapped and interpolated curves
  , piecewiseYieldCurve
  , piecewiseSpreadYieldCurve
  , defaultIterativeBootstrapOpts
  , interpolatedZeroCurve
  , interpolatedSimpleZeroCurve
  , interpolatedForwardCurve
  , interpolatedDiscountCurve
  , interpolatedSpreadDiscountCurve
    -- ** Multi-curve bootstrapping
  , multiCurve
    -- ** Basis and cross-currency helpers
  , iborIborBasisSwapRateHelper
  , overnightIborBasisSwapRateHelper
  , constNotionalCrossCurrencyBasisSwapRateHelper
  , mtmCrossCurrencyBasisSwapRateHelper
  , constNotionalCrossCurrencySwapRateHelper
  , fxSwapRateHelper

    -- * Mutators
  , linkTo
  , addBootstrappedCurve
  , addNonBootstrappedCurve

    -- * Inspectors
  , HasHelperUnderlying(..)
  , rateHelperFixingDependencies
  , forwardRate
  , forwardRateBetweenTimes
  , zeroRate
  , discount
  , impliedQuote
  , futuresRateHelperConvexityAdjustment
  , overnightIndexFutureRateHelperConvexityAdjustment
  , minimumCostValue
  , numberOfIterations
  , fittingMethodSize
  , fittingMethodErrorCode
  , fittingMethodSolution
  , fittingMethodDiscount
  ) where
import QuantLib.Internal hiding(maxDate)
import QuantLib.Internal.Common
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import Language.Haskell.TH(mkName)
import Language.Haskell.TH.Lib(varT)
import QuantLib.Math(EndCriteriaType(..))
import QuantLib.Quote hiding(linkTo)
import QuantLib.TermStructure (Reference(..), TermPoint(..), RatePoint(..), setExtrapolation, HasHelperUnderlying(..))
import Data.Maybe(fromMaybe)
import Data.List.NonEmpty(NonEmpty, toList)
import Foreign.Ptr(FunPtr, Ptr)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Storable(peek)
import Foreign.C.Types(CInt, CUInt)
import qualified QuantLib.Instrument.Bond as Bond (BondPriceType)
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.CashFlow#}(RateAveragingType(..))
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency(..), DateGenerationRule(..))
{#import QuantLib.Time.Date#}(Month(..))

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- These local pointer declarations break import cycles while allowing c2hs to attach finalizers.
{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex' nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlFittedBondDiscountCurve as FittedBondDiscountCurve foreign -> CFittedBondDiscountCurve' nocode#}
{#pointer *QlRelinkableYieldTermStructure as RelinkableYieldTermStructure foreign -> CRelinkableYieldTermStructure' nocode#}
{#pointer *QlMultiCurve as MultiCurve foreign -> CMultiCurve nocode#}
{#pointer *QlRateHelper as RateHelper foreign -> CRateHelper' nocode#}
{#pointer *QlSwapRateHelper as SwapRateHelper foreign -> CSwapRateHelper' nocode#}
{#pointer *QlOISRateHelper as OISRateHelper foreign -> COISRateHelper' nocode#}
{#pointer *QlFuturesRateHelper as FuturesRateHelper foreign -> CFuturesRateHelper' nocode#}
{#pointer *QlOvernightIndexFutureRateHelper as OvernightIndexFutureRateHelper foreign -> COvernightIndexFutureRateHelper' nocode#}
{#pointer *QlBondHelper as BondHelper foreign -> CBondHelper' nocode#}
{#pointer *FittedBondDiscountCurveFittingMethod as QlFittedBondDiscountCurveFittingMethod foreign -> CFittedBondDiscountCurveFittingMethod nocode#}

{#enum BootstrapTrait{} deriving(Show, Eq, Read)#}
{#enum PillarChoice{} deriving(Show, Eq, Read)#}
{#enum FuturesType{} deriving(Show, Eq, Read)#}

-- The optional calendars use 'Nothing' for QuantLib's null calendar because a concrete
-- 'Calendar' cannot occur in this pure default value. Keep this splice before every {#fun#}:
-- c2hs appends foreign imports to the generated module, and an intervening top-level splice
-- would split declarations from the imports their wrappers use.
$(deriveOptionsRecord "OISRateHelperOpts" ["m", "p"]
  [ ("oisTelescopicValueDates", [t|Bool|], [|False|])
  , ("oisPaymentLag", [t|Int|], [|0|])
  , ("oisPaymentConvention", [t|BusinessDayConvention|], [|Following|])
  , ("oisPaymentFrequency", [t|Frequency|], [|Annual|])
  , ("oisPaymentCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("oisOvernightSpread", [t|Maybe (GenQuote $(varT (mkName "m")))|], [|Nothing|])
  , ("oisPillar", [t|PillarChoice|], [|LastRelevantDate|])
  , ("oisCustomPillarDate", [t|Maybe Day|], [|Nothing|])
  , ("oisAveragingMethod", [t|RateAveragingType|], [|AveragingCompound|])
  , ("oisEndOfMonth", [t|Maybe Bool|], [|Nothing|])
  , ("oisFixedPaymentFrequency", [t|Maybe Frequency|], [|Nothing|])
  , ("oisFixedCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("oisObservation", [t|OvernightObservation|], [|defaultOvernightObservation|])
  , ("oisPricer", [t|Maybe (GenFloatingRateCouponPricer $(varT (mkName "p")))|], [|Nothing|])
  , ("oisRule", [t|DateGenerationRule|], [|Backward|])
  , ("oisOvernightCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("oisConvention", [t|BusinessDayConvention|], [|ModifiedFollowing|])
  ])

-- Upstream defaults accuracy/minValue/maxValue to Null<Real>() rather than to a number, so
-- those three are Maybe on the Haskell side; fromMaybeDouble supplies the sentinel, and the
-- {#fun#} specs below take a plain Double, hence the realToFrac.
nullableDouble :: Maybe Double -> Double
nullableDouble = realToFrac . fromMaybeDouble

-- |How a deposit's period and fixing conventions are given. 'DepositTenor' and 'DepositFromIndex'
-- are relative to the evaluation date: the deposit starts at spot and its dates move when the
-- evaluation date does. 'DepositFromIndex' takes the tenor and conventions from the ibor index;
-- 'DepositTenor' states them and fixes on an index QuantLib names @\"no-fix\"@.
-- 'DepositOnFixingDate' is the deposit the index fixes on the given date. Its dates never move, and
-- once that date is before the evaluation date its implied quote is the stored fixing, so
-- 'rateHelperFixingDependencies' reports it.
data DepositTerms ibor
  = DepositTenor
      !(Int, TimeUnit) -- ^tenor
      !Word -- ^fixingDays
      !Calendar
      !BusinessDayConvention
      !Bool -- ^endOfMonth
      !DayCounter
  | DepositFromIndex
      !(GenIborIndex ibor)
  | DepositOnFixingDate
      !Day -- ^fixingDate
      !(GenIborIndex ibor)

-- |Rate helper for bootstrapping over deposit rates.
depositRateHelper :: GenQuote q -> DepositTerms ibor -> IO RateHelper
depositRateHelper rate terms = case terms of
  DepositTenor t fd cal conv eom dc -> depositRateHelperRaw rate t fd cal conv eom dc
  DepositFromIndex idx -> depositRateHelperFromIndexRaw rate idx
  DepositOnFixingDate d idx -> depositRateHelperOnFixingDateRaw rate d idx

-- Raw deposit bindings behind 'depositRateHelper'; one per 'DepositTerms' constructor.
{#fun qlDepositRateHelper1 as depositRateHelperFromIndexRaw{withQuote*`GenQuote q',withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlDepositRateHelper2 as depositRateHelperOnFixingDateRaw{withQuote*`GenQuote q',withDay*`Day' -- ^fixingDate
  ,withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlDepositRateHelper as depositRateHelperRaw{withQuote*`GenQuote q' -- ^rate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Fixed-coupon bond helper for curve bootstrap: builds the underlying bond internally from a
-- schedule and coupons (unlike 'bondHelper', which takes an existing 'Bond').
{#fun qlFixedRateBondHelper as fixedRateBondHelper{withQuote*`GenQuote q',fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withSchedule*`Schedule',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^coupons
  ,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}

{#fun qlYieldTSDiscount as discountAtDateRaw{withYieldTermStructure*`GenYieldTermStructure y'
  ,withDay*`Day' -- ^d
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |How a swap helper's schedule and legs are given. 'SwapRateFromIndex' takes every convention
-- from a swap index, 'SwapRateTenor' states them for a swap of the given tenor starting at spot
-- plus @fwdStart@, and both are relative to the evaluation date: the swap's dates move when it
-- does. 'SwapRateBetweenDates' is the swap between two fixed dates; once a coupon's fixing date is
-- before the evaluation date that coupon reads the stored fixing, which
-- 'rateHelperFixingDependencies' reports with the rest. @settlementDays@ ('Nothing' takes the
-- index's fixing days) and @floatConvention@ ('Nothing' takes the index's convention) exist only
-- in the forms that state their conventions.
data SwapRateTerms sidx ibor
  = SwapRateFromIndex
      !(GenSwapIndex sidx)
      !(Int, TimeUnit) -- ^fwdStart
  | SwapRateTenor
      !(Int, TimeUnit) -- ^tenor
      !Calendar
      !Frequency -- ^fixedFrequency
      !BusinessDayConvention -- ^fixedConvention
      !DayCounter -- ^fixedDayCount
      !(GenIborIndex ibor)
      !(Int, TimeUnit) -- ^fwdStart
      !(Maybe Word) -- ^settlementDays
      !(Maybe BusinessDayConvention) -- ^floatConvention
  | SwapRateBetweenDates
      !Day -- ^startDate
      !Day -- ^endDate
      !Calendar
      !Frequency -- ^fixedFrequency
      !BusinessDayConvention -- ^fixedConvention
      !DayCounter -- ^fixedDayCount
      !(GenIborIndex ibor)
      !(Maybe BusinessDayConvention) -- ^floatConvention

-- |Rate helper for bootstrapping over swap rates: a fixed-vs-ibor swap whose fair rate is the
-- quote.
swapRateHelper :: GenQuote q1 -- ^rate
  -> SwapRateTerms sidx ibor
  -> Maybe (GenQuote q2) -- ^spread
  -> Maybe (GenYieldTermStructure y) -- ^discountingCurve
  -> PillarChoice -- ^pillar
  -> Maybe Day -- ^customPillarDate
  -> Bool -- ^endOfMonth
  -> Maybe Bool -- ^useIndexedCoupons
  -> Maybe (GenFloatingRateCouponPricer frcp) -- ^couponPricer
  -> IO SwapRateHelper
swapRateHelper rate terms spread disc pillar customPillarDate eom indexed pricer = case terms of
  SwapRateFromIndex idx fwd ->
    swapRateHelperFromIndexRaw rate idx spread fwd disc pillar customPillarDate eom indexed pricer
  SwapRateTenor t cal ff fc fdc ibor fwd sd fl ->
    swapRateHelperRaw rate t cal ff fc fdc ibor spread fwd disc sd pillar customPillarDate eom indexed fl pricer
  SwapRateBetweenDates s e cal ff fc fdc ibor fl ->
    swapRateHelperBetweenDatesRaw rate s e cal ff fc fdc ibor spread disc pillar customPillarDate eom indexed fl pricer

-- Raw swap bindings behind 'swapRateHelper'; one per 'SwapRateTerms' constructor.
{#fun qlSwapRateHelper2 as swapRateHelperBetweenDatesRaw{withQuote*`GenQuote q1' -- ^rate
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withCalendar*`Calendar' -- ^calendar
  ,`Frequency' -- ^fixedFrequency
  ,fromEnumC`BusinessDayConvention' -- ^fixedConvention
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withIborIndex*`GenIborIndex ibor' -- ^iborIndex
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^spread
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^floatConvention
  ,withMaybeFloatingRateCouponPricer*`Maybe (GenFloatingRateCouponPricer frcp)' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}

{#fun qlSwapRateHelper1 as swapRateHelperRaw{withQuote*`GenQuote q1' -- ^rate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,withCalendar*`Calendar' -- ^calendar
  ,`Frequency' -- ^fixedFrequency
  ,fromEnumC`BusinessDayConvention' -- ^fixedConvention
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withIborIndex*`GenIborIndex ibor' -- ^iborIndex
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^spread
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^fwdStart
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,fromMaybeInt`Maybe Word' -- ^settlementDays
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^floatConvention
  ,withMaybeFloatingRateCouponPricer*`Maybe (GenFloatingRateCouponPricer frcp)' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}

-- |Flat interest-rate curve with either a fixed or evaluation-date-relative reference point.
flatForward :: Reference -> GenQuote q -> DayCounter -> Compounding -> Frequency
  -> IO YieldTermStructure
flatForward (ReferenceDate d) = flatForwardFixed d
flatForward (SettlementDays n cal) = flatForwardMovingRaw n cal
{#fun qlFlatForward as flatForwardFixed{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlFlatForward1 as flatForwardMovingRaw{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |The zero rate at a date or year-fraction coordinate.
zeroRate :: GenYieldTermStructure y -> RatePoint -> Compounding -> Frequency -> Bool
  -> IO InterestRate
zeroRate curve point = case point of
  RateAtDate d dc -> zeroRateAtDateRaw curve d dc
  RateAtTime t -> zeroRateAtTimeRaw curve t

{#fun qlYieldTermStructureZeroRate as zeroRateAtDateRaw{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The forward rate between two dates, in the given day-counting rule.
-- /Warning/ Dates are not adjusted for holidays.
{#fun qlYieldTermStructureForwardRate as forwardRate{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',withDay*`Day',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
{#fun qlYieldTermStructureForwardRate2 as forwardRateBetweenTimes{withYieldTermStructure*`GenYieldTermStructure y',`Double',`Double',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
{#fun qlYieldTermStructureZeroRate1 as zeroRateAtTimeRaw{withYieldTermStructure*`GenYieldTermStructure y',`Double',`Compounding',`Frequency',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |Returns a discount factor at a date or year-fraction coordinate.
discount :: GenYieldTermStructure y -> TermPoint -> Bool -> IO Double
discount curve point = case point of
  DatePoint d -> discountAtDateRaw curve d
  TimePoint t -> discountAtTimeRaw curve t

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlYieldTermStructureDiscount1 as discountAtTimeRaw{withYieldTermStructure*`GenYieldTermStructure y',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |How a FRA's period and fixing conventions are given. The @FromIndex@ variants take the
-- FRA's length and its calendar\/convention\/day-count from the ibor index; the months and
-- period variants without an index state them explicitly. 'FraImmOffsets' starts and ends the
-- FRA on the given IMM dates after spot, counting the first as 1, and takes the rest from the
-- index. All of these are relative to the evaluation date. 'FraBetweenDates' is not: it runs from
-- the start date to the end date and fixes where the index fixes for the start date, and, with
-- @useIndexedCoupon@, its implied quote is the stored fixing once that date is before the
-- evaluation date, which 'rateHelperFixingDependencies' reports.
data FraTerms ibor
  = FraMonths
      !Word -- ^monthsToStart
      !Word -- ^monthsToEnd
      !Word -- ^fixingDays
      !Calendar
      !BusinessDayConvention
      !Bool -- ^endOfMonth
      !DayCounter
  | FraMonthsFromIndex
      !Word -- ^monthsToStart
      !(GenIborIndex ibor)
  | FraPeriod
      !(Int, TimeUnit) -- ^periodToStart
      !Word -- ^lengthInMonths
      !Word -- ^fixingDays
      !Calendar
      !BusinessDayConvention
      !Bool -- ^endOfMonth
      !DayCounter
  | FraPeriodFromIndex
      !(Int, TimeUnit) -- ^periodToStart
      !(GenIborIndex ibor)
  | FraImmOffsets
      !Word -- ^immOffsetStart
      !Word -- ^immOffsetEnd
      !(GenIborIndex ibor)
  | FraBetweenDates
      !Day -- ^startDate
      !Day -- ^endDate
      !(GenIborIndex ibor)

-- |Rate helper for bootstrapping over FRA rates.
fraRateHelper :: GenQuote q
  -> FraTerms ibor
  -> PillarChoice -- ^pillar
  -> Maybe Day -- ^customPillarDate
  -> Bool -- ^useIndexedCoupon
  -> IO RateHelper
fraRateHelper rate terms = case terms of
  FraMonths s e fd cal conv eom dc -> fraRateHelperRaw rate s e fd cal conv eom dc
  FraMonthsFromIndex s idx -> fraRateHelperFromIndexRaw rate s idx
  FraPeriod p n fd cal conv eom dc -> fraRateHelperFromPeriodRaw rate p n fd cal conv eom dc
  FraPeriodFromIndex p idx -> fraIborRateHelperRaw rate p idx
  FraImmOffsets s e idx -> fraImmOffsetsRateHelperRaw rate s e idx
  FraBetweenDates s e idx -> fraBetweenDatesRateHelperRaw rate s e idx

{#fun qlFraRateHelper as fraRateHelperRaw{withQuote*`GenQuote q' -- ^rate
  ,fromIntegral`Word' -- ^monthsToStart
  ,fromIntegral`Word' -- ^monthsToEnd
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Bootstrapping helper for an ibor-ibor basis swap: pays @baseIndex + basis@, receives
-- @otherIndex@. Pass @bootstrapBaseCurve = True@ (with 'otherIndex' carrying a forecast curve)
-- to bootstrap the forecast curve for 'baseIndex', or 'False' (with 'baseIndex' carrying a
-- forecast curve) to bootstrap the forecast curve for 'otherIndex'. An exogenous discount curve
-- is always required.
{#fun qlIborIborBasisSwapRateHelper as iborIborBasisSwapRateHelper{withQuote*`GenQuote q' -- ^basis
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withIborIndex*`GenIborIndex ibor1' -- ^baseIndex
  ,withIborIndex*`GenIborIndex ibor2' -- ^otherIndex
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountHandle
  ,`Bool' -- ^bootstrapBaseCurve
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Bootstrapping helper for an overnight-ibor basis swap: pays @baseIndex + basis@, receives
-- @otherIndex@. Bootstraps the forecast curve for 'otherIndex'; 'baseIndex' needs an existing
-- forecast curve. If 'Nothing', the overnight index's own curve is used as the discount curve.
{#fun qlOvernightIborBasisSwapRateHelper as overnightIborBasisSwapRateHelper{withQuote*`GenQuote q' -- ^basis
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withOvernightIborIndex*`OvernightIborIndex' -- ^baseIndex
  ,withIborIndex*`GenIborIndex ibor' -- ^otherIndex
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountHandle
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Bootstrapping helper for a constant-notional cross-currency basis swap: the collateral is
-- paid in the quote currency, the basis is given on the base-currency leg. 'Nothing' for either
-- frequency parameter derives the corresponding leg's schedule from its index tenor (or, for the
-- quote-currency leg, falls back to the base-currency frequency if that is given).
{#fun qlConstNotionalCrossCurrencyBasisSwapRateHelper as constNotionalCrossCurrencyBasisSwapRateHelper{withQuote*`GenQuote q' -- ^basis
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withIborIndex*`GenIborIndex ibor1' -- ^baseCurrencyIndex
  ,withIborIndex*`GenIborIndex ibor2' -- ^quoteCurrencyIndex
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^collateralCurve
  ,`Bool' -- ^isFxBaseCurrencyCollateralCurrency
  ,`Bool' -- ^isBasisOnFxBaseCurrencyLeg
  ,fromMaybeEnum`Maybe Frequency' -- ^paymentFrequency
  ,fromIntegral`Int' -- ^paymentLag
  ,fromMaybeEnum`Maybe Frequency' -- ^quoteCurrencyPaymentFrequency
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Bootstrapping helper for a marked-to-market cross-currency basis swap: like
-- 'constNotionalCrossCurrencyBasisSwapRateHelper', but the notional on the MtM leg resets at
-- each payment to reflect the FX rate.
{#fun qlMtMCrossCurrencyBasisSwapRateHelper as mtmCrossCurrencyBasisSwapRateHelper{withQuote*`GenQuote q' -- ^basis
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withIborIndex*`GenIborIndex ibor1' -- ^baseCurrencyIndex
  ,withIborIndex*`GenIborIndex ibor2' -- ^quoteCurrencyIndex
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^collateralCurve
  ,`Bool' -- ^isFxBaseCurrencyCollateralCurrency
  ,`Bool' -- ^isBasisOnFxBaseCurrencyLeg
  ,`Bool' -- ^isFxBaseCurrencyLegResettable
  ,fromMaybeEnum`Maybe Frequency' -- ^paymentFrequency
  ,fromIntegral`Int' -- ^paymentLag
  ,fromMaybeEnum`Maybe Frequency' -- ^quoteCurrencyPaymentFrequency
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Bootstrapping helper for a fixed-vs-floating cross-currency par swap: quoted at par, so the
-- FX spot cancels out and isn't required. 'collateralOnFixedLeg' selects which leg is discounted
-- with 'collateralCurve' -- the other leg's discount curve is the one being bootstrapped.
{#fun qlConstNotionalCrossCurrencySwapRateHelper as constNotionalCrossCurrencySwapRateHelper{withQuote*`GenQuote q' -- ^fixedRate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,`Frequency' -- ^fixedFrequency
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withIborIndex*`GenIborIndex ibor' -- ^floatIndex
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^collateralCurve
  ,`Bool' -- ^collateralOnFixedLeg
  ,fromIntegral`Int' -- ^paymentLag
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |How an FX swap helper's dates are given. 'FxSwapTenor' is relative to the evaluation date:
-- the swap starts @fixingDays@ business days after it on @calendar@ and runs for @tenor@, and
-- @tradingCalendar@ (QuantLib's null calendar for none) is joined with @calendar@ for the spot
-- date. 'FxSwapBetweenDates' runs between two fixed dates.
data FxSwapTerms
  = FxSwapTenor
      !(Int, TimeUnit) -- ^tenor
      !Word -- ^fixingDays
      !Calendar
      !BusinessDayConvention
      !Bool -- ^endOfMonth
      !Calendar -- ^tradingCalendar
  | FxSwapBetweenDates
      !Day -- ^startDate
      !Day -- ^endDate

-- |Bootstrapping helper from FX swap points. 'collateralCurve' discounts the collateral
-- currency; the curve being bootstrapped is for the other currency. 'fwdPoint' and 'spotFx' must
-- be quoted in the same units (points already scaled to match the spot).
fxSwapRateHelper :: GenQuote q1 -- ^fwdPoint
  -> GenQuote q2 -- ^spotFx
  -> FxSwapTerms
  -> Bool -- ^isFxBaseCurrencyCollateralCurrency
  -> GenYieldTermStructure y -- ^collateralCurve
  -> IO RateHelper
fxSwapRateHelper fwdPoint spotFx terms isBase collateral = case terms of
  FxSwapTenor t fd cal conv eom trading -> fxSwapRateHelperRaw fwdPoint spotFx t fd cal conv eom isBase collateral trading
  FxSwapBetweenDates s e -> fxSwapRateHelperBetweenDatesRaw fwdPoint spotFx s e isBase collateral

-- Raw FX swap bindings behind 'fxSwapRateHelper'; one per 'FxSwapTerms' constructor.
{#fun qlFxSwapRateHelper as fxSwapRateHelperRaw{withQuote*`GenQuote q1' -- ^fwdPoint
  ,withQuote*`GenQuote q2' -- ^spotFx
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,`Bool' -- ^isFxBaseCurrencyCollateralCurrency
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^collateralCurve
  ,withCalendar*`Calendar' -- ^tradingCalendar
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlFxSwapRateHelper2 as fxSwapRateHelperBetweenDatesRaw{withQuote*`GenQuote q1' -- ^fwdPoint
  ,withQuote*`GenQuote q2' -- ^spotFx
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,`Bool' -- ^isFxBaseCurrencyCollateralCurrency
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^collateralCurve
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
-- 'BondPriceType' is marshalled as an 'Int' to avoid a c2hs cross-module enum-import cycle.
bondHelper :: GenQuote q -> GenBond b -> Bond.BondPriceType -> IO BondHelper
bondHelper cleanPrice bond priceType = bondHelper_ cleanPrice bond (fromEnum priceType)

{#fun qlBondHelper as bondHelper_{withQuote*`GenQuote q',withBond*`GenBond b',`Int' -- ^priceType
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}
-- |How an OIS helper's dates are given. 'OisTenor' is relative to the evaluation date: the swap
-- starts @settlementDays@ after it plus @forwardStart@ and runs for @tenor@. 'OisBetweenDates'
-- runs between two fixed dates; every overnight fixing it compounds over that is before the
-- evaluation date is read from the store. @forwardStart@ is a field of 'OisTenor' rather than
-- of 'OISRateHelperOpts' because QuantLib's dated constructor has none.
data OisTerms
  = OisTenor
      !Word -- ^settlementDays
      !(Int, TimeUnit) -- ^tenor
      !(Int, TimeUnit) -- ^forwardStart
  | OisBetweenDates
      !Day -- ^startDate
      !Day -- ^endDate

-- |Rate helper for bootstrapping over overnight-indexed swap rates, with QuantLib's defaults for
-- everything 'oisRateHelperWithOptions' can set. Both share the same full-arity bindings.
oisRateHelper :: OisTerms -> GenQuote q -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure y) -> IO OISRateHelper
oisRateHelper terms fixedRate idx discountingCurve = do
  cal <- calendar Null
  case terms of
    OisTenor settlementDays tenor forwardStart ->
      oisRateHelper_ settlementDays tenor fixedRate idx discountingCurve
        False 0 Following Annual cal forwardStart Nothing LastRelevantDate Nothing AveragingCompound
        Nothing Nothing cal Nothing 0 False Nothing Backward cal ModifiedFollowing
    OisBetweenDates startDate endDate ->
      oisRateHelper2_ startDate endDate fixedRate idx discountingCurve
        False 0 Following Annual cal Nothing LastRelevantDate Nothing AveragingCompound
        Nothing Nothing cal Nothing 0 False Nothing Backward cal ModifiedFollowing

{#fun qlOISRateHelper as oisRateHelper_{fromIntegral`Word' -- ^settlementDays
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,withQuote*`GenQuote q1'
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`Bool' -- ^telescopicValueDates
  ,fromIntegral`Int' -- ^paymentLag
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,`Frequency' -- ^paymentFrequency
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^forwardStart
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^overnightSpread
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`RateAveragingType' -- ^averagingMethod
  ,fromMaybeBool`Maybe Bool' -- ^endOfMonth
  ,fromMaybeEnum`Maybe Frequency' -- ^fixedPaymentFrequency
  ,withCalendar*`Calendar' -- ^fixedCalendar
  ,fromMaybeInt`Maybe Word' -- ^lookbackDays
  ,fromIntegral`Word' -- ^lockoutDays
  ,`Bool' -- ^applyObservationShift
  ,withMaybeFloatingRateCouponPricer*`Maybe (GenFloatingRateCouponPricer frcp)' -- ^pricer
  ,`DateGenerationRule' -- ^rule
  ,withCalendar*`Calendar' -- ^overnightCalendar
  ,fromEnumC`BusinessDayConvention' -- ^convention (q1.k.q1. overnightConvention)
  ,preErrorCheck-`String'errorCheck*-}->`OISRateHelper'peekOISRateHelper*#}
{#fun qlOISRateHelper2 as oisRateHelper2_{withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withQuote*`GenQuote q1'
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`Bool' -- ^telescopicValueDates
  ,fromIntegral`Int' -- ^paymentLag
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,`Frequency' -- ^paymentFrequency
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^overnightSpread
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`RateAveragingType' -- ^averagingMethod
  ,fromMaybeBool`Maybe Bool' -- ^endOfMonth
  ,fromMaybeEnum`Maybe Frequency' -- ^fixedPaymentFrequency
  ,withCalendar*`Calendar' -- ^fixedCalendar
  ,fromMaybeInt`Maybe Word' -- ^lookbackDays
  ,fromIntegral`Word' -- ^lockoutDays
  ,`Bool' -- ^applyObservationShift
  ,withMaybeFloatingRateCouponPricer*`Maybe (GenFloatingRateCouponPricer frcp)' -- ^pricer
  ,`DateGenerationRule' -- ^rule
  ,withCalendar*`Calendar' -- ^overnightCalendar
  ,fromEnumC`BusinessDayConvention' -- ^convention (q1.k.q1. overnightConvention)
  ,preErrorCheck-`String'errorCheck*-}->`OISRateHelper'peekOISRateHelper*#}

-- |'oisRateHelper' with every trailing QuantLib parameter taken from an options record.
oisRateHelperWithOptions :: OisTerms -> GenQuote q -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure y) -> OISRateHelperOpts m p -> IO OISRateHelper
oisRateHelperWithOptions terms fixedRate idx discountingCurve opts = do
  cal <- calendar Null
  let obs = oisObservation opts
      paymentCal = fromMaybe cal (oisPaymentCalendar opts)
      fixedCal = fromMaybe cal (oisFixedCalendar opts)
      overnightCal = fromMaybe cal (oisOvernightCalendar opts)
  case terms of
    OisTenor settlementDays tenor forwardStart ->
      oisRateHelper_ settlementDays tenor fixedRate idx discountingCurve
        (oisTelescopicValueDates opts) (oisPaymentLag opts) (oisPaymentConvention opts)
        (oisPaymentFrequency opts) paymentCal
        forwardStart (oisOvernightSpread opts) (oisPillar opts) (oisCustomPillarDate opts)
        (oisAveragingMethod opts) (oisEndOfMonth opts) (oisFixedPaymentFrequency opts)
        fixedCal (lookbackDays obs) (lockoutDays obs)
        (applyObservationShift obs) (oisPricer opts) (oisRule opts)
        overnightCal (oisConvention opts)
    OisBetweenDates startDate endDate ->
      oisRateHelper2_ startDate endDate fixedRate idx discountingCurve
        (oisTelescopicValueDates opts) (oisPaymentLag opts) (oisPaymentConvention opts)
        (oisPaymentFrequency opts) paymentCal
        (oisOvernightSpread opts) (oisPillar opts) (oisCustomPillarDate opts)
        (oisAveragingMethod opts) (oisEndOfMonth opts) (oisFixedPaymentFrequency opts)
        fixedCal (lookbackDays obs) (lockoutDays obs)
        (applyObservationShift obs) (oisPricer opts) (oisRule opts)
        overnightCal (oisConvention opts)

-- The 'SwapRateFromIndex' binding behind 'swapRateHelper'.
{#fun qlSwapRateHelper as swapRateHelperFromIndexRaw{withQuote*`GenQuote q1' -- ^rate
  ,withSwapIndex*`GenSwapIndex sidx',withMaybeQuote*`Maybe (GenQuote q2)' -- ^spread
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^fwdStart
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,withMaybeFloatingRateCouponPricer*`Maybe (GenFloatingRateCouponPricer frcp)' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}

-- |A yield curve offset from 'baseCurve' by a spread added to its instantaneous forward rate,
-- remaining linked to changes in either.
{#fun qlForwardSpreadedTermStructure as forwardSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |A yield curve offset from 'baseCurve' by a spread added to its zero-yield rate, remaining
-- linked to changes in either.
{#fun qlZeroSpreadedTermStructure as zeroSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |A yield curve whose zero rate is @f rate1 rate2@, where @rate1@ and @rate2@ are the
-- input curves' zero rates expressed with the given compounding and frequency. The result is
-- live in both inputs.
--
-- __The resulting curve is valid only inside the continuation, which must span its whole use.__
-- QuantLib stores @f@ and calls it whenever the curve is queried, including from any object that
-- stores the curve. Leaving the continuation frees its function pointer; a later query crashes
-- the process. @f@ must be total: an exception escaping it crosses C++ unsafely.
withCompositeZeroYieldStructure :: (Double -> Double -> Double) -- ^f(rate1, rate2)
  -> GenYieldTermStructure y1 -- ^curve1
  -> GenYieldTermStructure y2 -- ^curve2
  -> Compounding
  -> Frequency
  -> (YieldTermStructure -> IO a)
  -> IO a
withCompositeZeroYieldStructure f c1 c2 comp freq k =
  withQuoteBinaryFun f $ \fp -> qlCompositeZeroYieldStructure c1 c2 fp comp freq >>= k
{#fun qlCompositeZeroYieldStructure{withYieldTermStructure*`GenYieldTermStructure y1',withYieldTermStructure*`GenYieldTermStructure y2'
  ,id`FunPtr QuoteBinaryFun',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Rate helper for bootstrapping over BMA swap rates.
{#fun qlBMASwapRateHelper as bmaSwapRateHelper{withQuote*`GenQuote q' -- ^liborFraction
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDAys
  ,withCalendar*`Calendar',fromEnumQuantity`(Int,TimeUnit)'& -- ^bmpPeriod
  ,fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter',withBMAIndex*`BMAIndex',withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Rate helper for bootstrapping from multiple-resets swap quotes (a floating leg that resets
-- several times per fixed-leg coupon period).
{#fun qlMultipleResetsSwapRateHelper as multipleResetsSwapRateHelper{fromIntegral`Word' -- ^settlementDays
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,withQuote*`GenQuote q1' -- ^fixedRate
  ,withIborIndex*`GenIborIndex ibor'
  ,fromIntegral`Word' -- ^resetsPerCoupon
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`RateAveragingType' -- ^averagingMethod
  ,`Double' -- ^spread
  ,`Frequency' -- ^fixedFrequency
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,fromEnumC`BusinessDayConvention' -- ^fixedConvention
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- Raw FRA bindings behind 'fraRateHelper'; one per 'FraTerms' constructor.
{#fun qlFraRateHelper1 as fraRateHelperFromIndexRaw{withQuote*`GenQuote q',fromIntegral`Word' -- ^monthsToStart
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlFraRateHelper2 as fraRateHelperFromPeriodRaw{withQuote*`GenQuote q',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,fromIntegral`Word' -- ^lengthInMonths
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar',fromEnumC`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlFraRateHelper3 as fraIborRateHelperRaw{withQuote*`GenQuote q',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlFraRateHelper5 as fraImmOffsetsRateHelperRaw{withQuote*`GenQuote q',fromIntegral`Word' -- ^immOffsetStart
  ,fromIntegral`Word' -- ^immOffsetEnd
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

{#fun qlFraRateHelper4 as fraBetweenDatesRateHelperRaw{withQuote*`GenQuote q',withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |How an IborIndex futures contract's underlying deposit is given. @FuturesFromIndex@ takes
-- the deposit's length and its calendar\/convention\/day-count from the ibor index; the others
-- state them explicitly.
data FuturesTerms ibor
  = FuturesMonths
      !Day -- ^iborStartDate
      !Word -- ^lengthInMonths
      !Calendar
      !BusinessDayConvention
      !Bool -- ^endOfMonth
      !DayCounter
  | FuturesBetweenDates
      !Day -- ^iborStartDate
      !Day -- ^iborEndDate
      !DayCounter
  | FuturesFromIndex
      !Day -- ^iborStartDate
      !(GenIborIndex ibor)

-- |Rate helper for bootstrapping over IborIndex futures prices.
futuresRateHelper :: GenQuote q1 -- ^price
  -> FuturesTerms ibor
  -> Maybe (GenQuote q2) -- ^convexityAdjustment
  -> FuturesType -- ^type
  -> IO FuturesRateHelper
futuresRateHelper price terms = case terms of
  FuturesMonths d n cal conv eom dc -> futuresRateHelperRaw price d n cal conv eom dc
  FuturesBetweenDates s e dc -> futuresRateHelperBetweenDatesRaw price s e dc
  FuturesFromIndex d idx -> futuresIborRateHelperRaw price d idx

-- Raw futures bindings behind 'futuresRateHelper'; one per 'FuturesTerms' constructor.
{#fun qlFuturesRateHelper1 as futuresRateHelperBetweenDatesRaw{withQuote*`GenQuote q1',withDay*`Day' -- ^immStartDate
  ,withDay*`Day' -- ^endDate
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`FuturesRateHelper'peekFuturesRateHelper*#}

{#fun qlFuturesRateHelper2 as futuresIborRateHelperRaw{withQuote*`GenQuote q1',withDay*`Day' -- ^immDate
  ,withIborIndex*`GenIborIndex ibor',withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`FuturesRateHelper'peekFuturesRateHelper*#}

{#fun qlFuturesRateHelper as futuresRateHelperRaw{withQuote*`GenQuote q1',withDay*`Day' -- ^immDate
  ,fromIntegral`Word' -- ^lengthInMonths
  ,withCalendar*`Calendar',fromEnumC`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`FuturesRateHelper'peekFuturesRateHelper*#}

-- |The futures-vs-forward convexity adjustment this helper was built with (0 if none was given).
{#fun qlFuturesRateHelperConvexityAdjustment as futuresRateHelperConvexityAdjustment{withGenRateHelper*`FuturesRateHelper',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Rate helper for bootstrapping over overnight-index compounding futures.
{#fun qlOvernightIndexFutureRateHelper as overnightIndexFutureRateHelper{withQuote*`GenQuote q1',withDay*`Day' -- ^valueDate
  ,withDay*`Day' -- ^maturityDate
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`RateAveragingType' -- ^averagingMethod
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`OvernightIndexFutureRateHelper'peekOvernightIndexFutureRateHelper*#}

-- |The futures-vs-forward convexity adjustment this helper was built with (0 if none was given).
{#fun qlOvernightIndexFutureRateHelperConvexityAdjustment as overnightIndexFutureRateHelperConvexityAdjustment{withGenRateHelper*`OvernightIndexFutureRateHelper',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Every fixing this rate helper reads from the store, as @(index name, fixing date)@ pairs.  A
-- bootstrapped curve cannot be asked what it was built from -- @PiecewiseYieldCurve@ is a
-- template with no instruments accessor, and an @Observer@ does not expose the observables it
-- registered with -- so a curve's fixing dependencies are the union of its helpers', and this
-- answers for one helper.  It walks the helper's underlying instrument the way
-- 'QuantLib.CashFlow.fixingDependencies' walks a leg, and names each index by
-- 'QuantLib.Index.name', the key QuantLib\'s process-global fixing store uses.
--
-- A swap, OIS, basis-swap, BMA, multiple-resets, cross-currency or bond helper answers from its
-- underlying; an IBOR futures or FX swap helper, and a deposit or FRA relative to the evaluation
-- date, reads no stored fixing: @Just []@. A 'DepositOnFixingDate' deposit, or a 'FraBetweenDates'
-- FRA with an indexed coupon, reads its fixing once the fixing date is before the evaluation date,
-- and reports it from then on; on the fixing date itself it still forecasts.
-- An overnight-index or SOFR futures helper reports each business-day fixing from its period start
-- up to the evaluation date, that date's included because the future reads it when stored. On
-- QuantLib 1.43, which keeps the future private, it instead reports 'Nothing' from two weeks before
-- its period starts. Any helper type the walk has no case for reports 'Nothing' too: "cannot see
-- it", which is not the same as "needs nothing".
--
-- The dates follow the evaluation date, because a relative-date helper re-initialises its
-- schedule when that date moves: call this under the date whose fixings are being asked about.
-- Duplicates are not removed, the same as for a leg.
rateHelperFixingDependencies :: GenRateHelper rh -> IO (Maybe [(String, Day)])
rateHelperFixingDependencies h = do
  (ns, ds, ok) <- qlRateHelperFixingDependencies h
  pure $ if ok /= 0 then Just (zip ns ds) else Nothing
{#fun qlRateHelperFixingDependencies{withRateHelper*`GenRateHelper rh'
  ,preArray-`[String]'&peekCStringArray*,preArray-`[Day]'&peekDayArray*,alloca-`CInt'peek*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Rate helper for bootstrapping over CME SOFR futures. Compounds overnight SOFR from the third
-- Wednesday of 'referenceMonth'\/'referenceYear' (inclusive) to the third Wednesday of the
-- following month or quarter (exclusive), per 'referenceFreq'.
{#fun qlSofrFutureRateHelper as sofrFutureRateHelper{withQuote*`GenQuote q1',`Month' -- ^referenceMonth
  ,fromIntegral`Int' -- ^referenceYear
  ,`Frequency' -- ^referenceFreq
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |The quote value implied by the current bootstrapped state of the curve the helper was
-- last used against, i.e. what the helper's own market quote would need to be to make it
-- reprice exactly.
{#fun qlRateHelperImpliedQuote as impliedQuote{withRateHelper*`GenRateHelper rh',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A yield curve identical to 'baseCurve' but reporting a different reference date; observes
-- and stays linked to 'baseCurve'.
{#fun qlImpliedTermStructure as impliedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |A yield curve with a vector of zero-yield spreads added to 'baseCurve', interpolating
-- between the given dates with the given 'Interpolation'. Remains linked to changes in
-- 'baseCurve' or the spread quotes.
piecewiseZeroSpreadedTermStructure :: GenYieldTermStructure y
  -> NonEmpty (Day, GenQuote q)  -- ^spreads
  -> Compounding -> Frequency -> Interpolation -> IO YieldTermStructure
piecewiseZeroSpreadedTermStructure ts qd c f i = uncurryNested (qlPiecewiseZeroSpreadedTermStructure ts qs ds c f) (qlInterpolation i)
  where (ds, qs) = unzip (toList qd)
{#fun qlPiecewiseZeroSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Compounding',`Frequency'
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |A yield curve adding interpolated instantaneous-forward spreads to 'baseCurve', flat outside
-- the spread dates. Linked to the base curve and quotes; its max date is the earlier of the base
-- curve's and the last spread date. @LogLinear@ and @LogCubic@ throw: the spread is integrated.
piecewiseForwardSpreadedTermStructure :: GenYieldTermStructure y
  -> NonEmpty (Day, GenQuote q)  -- ^spreads
  -> Interpolation -> IO YieldTermStructure
piecewiseForwardSpreadedTermStructure ts qd i = uncurryNested (qlPiecewiseForwardSpreadedTermStructure ts qs ds) (qlInterpolation i)
  where (ds, qs) = unzip (toList qd)
{#fun qlPiecewiseForwardSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Quanto term structure, modelling the quanto effect in option pricing. Stays linked to all
-- four inputs.
{#fun qlQuantoTermStructure as quantoTermStructure{withYieldTermStructure*`GenYieldTermStructure y1' -- ^underlyingDividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure y3' -- ^foreignRsikFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv1' -- ^underlyingBlackVolTS
  ,`Double' -- ^strike
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv2' -- ^exchRateBlackVolTS
  ,`Double' -- ^exchRateATMlevel
  ,`Double' -- ^underlyingExchRateCorrelation
  ,preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Blends 'originalCurve' with an ultimate forward rate beyond the last liquid point, per the
-- \"UFR\" methodology used for extrapolating long-dated (e.g. Solvency II) curves.
{#fun qlUltimateForwardTermStructure as ultimateForwardTermStructure{withYieldTermStructure*`GenYieldTermStructure y' -- ^originalCurve
  ,withQuote*`GenQuote q1' -- ^lastLiquidForwardRate
  ,withQuote*`GenQuote q2' -- ^ultimateForwardRate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^firstSmoothingPoint
  ,`Double' -- ^alpha
  ,fromMaybeInt`Maybe Int' -- ^roundingDigits
  ,`Compounding'
  ,`Frequency'
  ,preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- Raw iterative-bootstrap bindings used by 'piecewiseYieldCurve'.
-- Like the public iterative choice, this exposes every @IterativeBootstrap@ setting through
-- 'IterativeBootstrapOpts' instead of hardcoding upstream's defaults. Start from
-- 'defaultIterativeBootstrapOpts' and override with record-update syntax; passing it
-- unchanged is exactly 'piecewiseYieldCurve'. 'ibAccuracy'\/'ibMinValue'\/'ibMaxValue' are
-- 'Maybe' because upstream defaults them to @Null\<Real\>()@ (\"pick a sensible value per
-- pillar\"), not to a number. 'ibDontThrow' is the one to reach for when a curve fails to
-- bootstrap: it substitutes the best value found so far for a pillar that won't solve,
-- rather than throwing.
{#fun qlPiecewiseYieldCurveFull{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseYieldCurveFull1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- Raw moving-curve bindings used by 'piecewiseYieldCurve'.
{#fun qlPiecewiseYieldCurveGlobalBootstrap1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseYieldCurveGlobalBootstrap2{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseYieldCurveGlobalBootstrap3{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh1]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,withRateHelperArray*`[GenRateHelper rh2]'&,withDayArray*`[Day]'&,`Double',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseYieldCurveGlobalBootstrap4{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseYieldCurveGlobalBootstrap5{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseYieldCurveLocalBootstrap1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',fromIntegral`Word',`Bool',`Double',`Double',`Double',`Bool',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- Raw fixed-curve bindings for the non-iterative bootstrap choices.
{#fun qlPiecewiseYieldCurveGlobalBootstrapFixed1{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlPiecewiseYieldCurveGlobalBootstrapFixed2{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlPiecewiseYieldCurveGlobalBootstrapFixed3{withDay*`Day',withRateHelperArray*`[GenRateHelper rh1]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,withRateHelperArray*`[GenRateHelper rh2]'&,withDayArray*`[Day]'&,`Double',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlPiecewiseYieldCurveGlobalBootstrapFixed4{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlPiecewiseYieldCurveGlobalBootstrapFixed5{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlPiecewiseYieldCurveLocalBootstrapFixed{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',fromIntegral`Word',`Bool',`Double',`Double',`Double',`Bool',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Selects the bootstrapper used by 'piecewiseYieldCurve' and carries exactly the
-- parameters valid for that choice. 'Iterative' uses the selected trait, interpolation, and
-- full iterative settings. The @Global*@ constructors solve all instruments together; their
-- list field contains instrument weights, with an empty list selecting equal weights.
-- 'GlobalSimpleZeroLinearFull' additionally takes helper instruments, their interpolation
-- dates (exactly two fewer than the helpers), and accuracy. 'Local' uses @ConvexMonotone@
-- interpolation and restricts the trait to 'LocalBootstrapTrait', because @Discount@ produces
-- invalid results with QuantLib's local bootstrapper.
data Bootstrap rh2
  = Iterative !BootstrapTrait !Interpolation !IterativeBootstrapOpts
  | GlobalDiscountLogLinear !Double ![Double] -- ^accuracy, instrumentWeights
  | GlobalSimpleZeroLinear !Double ![Double] -- ^accuracy, instrumentWeights
  | GlobalSimpleZeroLinearFull !(NonEmpty (GenRateHelper rh2)) ![Day] !Double -- ^additionalHelpers, additionalDates, accuracy
  | GlobalForwardRateLinear !Double ![Double] -- ^accuracy, instrumentWeights
  | GlobalZeroYieldLinear !Double ![Double] -- ^accuracy, instrumentWeights
  | Local !LocalBootstrapTrait !Word !Bool !Double !Double !Double !Bool
    -- ^trait, localisation, forcePositive (LocalBootstrap's), accuracy, quadraticity, monotonicity, convexForcePositive (ConvexMonotone's)

-- |Bootstrap traits that are numerically usable with @LocalBootstrap@ and
-- @ConvexMonotone@. @Discount@ is intentionally unrepresentable.
data LocalBootstrapTrait = LForwardRate | LZeroYield | LSimpleZeroYield
  deriving (Show, Eq, Read)

fromBootstrapTrait :: LocalBootstrapTrait -> BootstrapTrait
fromBootstrapTrait LForwardRate = ForwardRate
fromBootstrapTrait LZeroYield = ZeroYield
fromBootstrapTrait LSimpleZeroYield = SimpleZeroYield

-- |Bootstrapper for 'piecewiseSpreadYieldCurve', whose nodes are always discount-factor spreads.
-- @LogLinear@ interpolation gives piecewise-constant forward spreads, upstream's canonical choice.
data SpreadBootstrap
  = SpreadIterative !Interpolation !IterativeBootstrapOpts
  | SpreadGlobalLogLinear !Double ![Double] -- ^accuracy, instrumentWeights (empty for equal weights)

-- |Bootstraps a term structure with either a fixed or evaluation-date-relative reference point.
-- 'Bootstrap' selects iterative, global, or local construction; the final flag controls
-- extrapolation past the curve's maximum date.
piecewiseYieldCurve :: Reference
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Bootstrap rh2 -- ^bootstrapper choice
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurve reference r dc qd bootstrap ex = case (reference, bootstrap) of
  (ReferenceDate d, Iterative t i b) -> enable ex $ uncurryNested (qlPiecewiseYieldCurveFull d rs dc qs ds t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
  (SettlementDays s cal, Iterative t i b) -> uncurryNested (qlPiecewiseYieldCurveFull1 s cal rs dc qs ds t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b) ex
  (ReferenceDate d, GlobalDiscountLogLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrapFixed1 d rs dc qs ds acc w ex
  (SettlementDays s cal, GlobalDiscountLogLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrap1 s cal rs dc qs ds acc w ex
  (ReferenceDate d, GlobalSimpleZeroLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrapFixed2 d rs dc qs ds acc w ex
  (SettlementDays s cal, GlobalSimpleZeroLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrap2 s cal rs dc qs ds acc w ex
  (ReferenceDate d, GlobalSimpleZeroLinearFull ah ad acc) -> qlPiecewiseYieldCurveGlobalBootstrapFixed3 d rs dc qs ds (toList ah) ad acc ex
  (SettlementDays s cal, GlobalSimpleZeroLinearFull ah ad acc) -> qlPiecewiseYieldCurveGlobalBootstrap3 s cal rs dc qs ds (toList ah) ad acc ex
  (ReferenceDate d, GlobalForwardRateLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrapFixed4 d rs dc qs ds acc w ex
  (SettlementDays s cal, GlobalForwardRateLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrap4 s cal rs dc qs ds acc w ex
  (ReferenceDate d, GlobalZeroYieldLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrapFixed5 d rs dc qs ds acc w ex
  (SettlementDays s cal, GlobalZeroYieldLinear acc w) -> qlPiecewiseYieldCurveGlobalBootstrap5 s cal rs dc qs ds acc w ex
  (ReferenceDate d, Local t loc fp acc q m cfp) -> qlPiecewiseYieldCurveLocalBootstrapFixed d rs dc qs ds (fromBootstrapTrait t) loc fp acc q m cfp ex
  (SettlementDays s cal, Local t loc fp acc q m cfp) -> qlPiecewiseYieldCurveLocalBootstrap1 s cal rs dc qs ds (fromBootstrapTrait t) loc fp acc q m cfp ex
  where (ds, qs) = unzip qd
        rs = toList r
        enable False action = action
        enable True action = do
          curve <- action
          setExtrapolation curve True
          pure curve

-- |Bootstraps multiplicative discount-factor spreads over 'baseCurve' so that each instrument
-- reprices on the combined curve. Reference date, calendar and day counter come from the linked
-- base curve; past the last node the forward spread stays flat.
piecewiseSpreadYieldCurve :: GenYieldTermStructure y -- ^baseCurve
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> SpreadBootstrap -- ^bootstrapper choice
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseSpreadYieldCurve base r bootstrap ex = case bootstrap of
  SpreadIterative i b -> uncurryNested (qlPiecewiseSpreadYieldCurve base rs) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b) ex
  SpreadGlobalLogLinear acc w -> qlPiecewiseSpreadYieldCurveGlobalBootstrap base rs acc w ex
  where rs = toList r
{#fun qlPiecewiseSpreadYieldCurve{withYieldTermStructure*`GenYieldTermStructure y',withRateHelperArray*`[GenRateHelper rh]'&,`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlPiecewiseSpreadYieldCurveGlobalBootstrap{withYieldTermStructure*`GenYieldTermStructure y',withRateHelperArray*`[GenRateHelper rh]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Yield curve interpolating discount factors directly between the given dates.
interpolatedDiscountCurve :: NonEmpty (Day, Double) -- ^dates, dfs
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -- ^interpolator
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
interpolatedDiscountCurve r dc c qd i ex = uncurryNested (qlInterpolatedDiscountCurve rs rd dc c qs ds) (qlInterpolation i) ex
  where (rd, rs) = unzip (toList r)
        (ds, qs) = unzip qd
{#fun qlInterpolatedDiscountCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Yield curve interpolating instantaneous forward rates directly between the given dates.
interpolatedForwardCurve :: NonEmpty (Day, Double) -- ^dates, forwards
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedForwardCurve r dc c qd i = uncurryNested (qlInterpolatedForwardCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip (toList r); (ds, qs) = unzip qd}
{#fun qlInterpolatedForwardCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Yield curve interpolating zero-yield rates directly between the given dates. Always uses
-- upstream's own default compounding (@Continuous@, @Annual@); use 'interpolatedSimpleZeroCurve'
-- for simple compounding.
interpolatedZeroCurve :: NonEmpty (Day, Double) -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve r dc c qd i = uncurryNested (qlInterpolatedZeroCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip (toList r); (ds, qs) = unzip qd}
{#fun qlInterpolatedZeroCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Yield curve interpolating simply-compounded zero rates directly between the given dates.
interpolatedSimpleZeroCurve :: NonEmpty (Day, Double) -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedSimpleZeroCurve r dc c qd i = uncurryNested (qlInterpolatedSimpleZeroCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip (toList r); (ds, qs) = unzip qd}
{#fun qlInterpolatedSimpleZeroCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Discount factors interpolated as a multiplicative spread applied on top of 'baseCurve'.
-- Upstream requires the first discount factor to be exactly @1.0@, flagging its date as the
-- curve's own reference date; a mismatched leading value throws a 'QuantLib.Context.Error'.
interpolatedSpreadDiscountCurve :: GenYieldTermStructure y
  -> NonEmpty (Day, Double) -- ^dates, dfs
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedSpreadDiscountCurve ts r i = uncurryNested (qlInterpolatedSpreadDiscountCurve ts rs rd) (qlInterpolation i) where (rd, rs) = unzip (toList r)
{#fun qlInterpolatedSpreadDiscountCurve{withYieldTermStructure*`GenYieldTermStructure y',withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

withNonEmptyBondHelperArray :: NonEmpty BondHelper -> ((CUInt, Ptr (Ptr CBondHelper')) -> IO a) -> IO a
withNonEmptyBondHelperArray = withBondHelperArray . toList

-- |Construct a fitted bond discount curve with either a fixed or moving reference point.
fittedBondDiscountCurve :: Reference -> NonEmpty BondHelper -> DayCounter -> FittingMethod
  -> Double -> Word -> [Double] -> Double -> Bool -> IO FittedBondDiscountCurve
fittedBondDiscountCurve reference hs dc method accuracy maxEvaluations guess simplexLambda ex = do
  curve <- case reference of
    ReferenceDate d -> fittedBondDiscountCurveFixed d hs dc method accuracy maxEvaluations guess simplexLambda
    SettlementDays n cal -> fittedBondDiscountCurveMovingRaw n cal hs dc method accuracy maxEvaluations guess simplexLambda
  setExtrapolation curve ex
  pure curve

{#fun qlFittedBondDiscountCurve as fittedBondDiscountCurveMovingRaw{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar',withNonEmptyBondHelperArray*`NonEmpty BondHelper'&,withDayCounter*`DayCounter',withFittedBondDiscountCurveFittingMethod*`FittingMethod'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,withDoubleArray*`[Double]'& -- ^guess
  ,`Double' -- ^simplexLambda
  ,preErrorCheck-`String'errorCheck*-}->`FittedBondDiscountCurve'peekFittedBondDiscountCurve*#}

-- |curve reference date fixed for life of curve
{#fun qlFittedBondDiscountCurve1 as fittedBondDiscountCurveFixed{withDay*`Day',withNonEmptyBondHelperArray*`NonEmpty BondHelper'&,withDayCounter*`DayCounter',withFittedBondDiscountCurveFittingMethod*`FittingMethod'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,withDoubleArray*`[Double]'& -- ^guess
  ,`Double' -- ^simplexLambda
,preErrorCheck-`String'errorCheck*-}->`FittedBondDiscountCurve'peekFittedBondDiscountCurve*#}

-- |final value of cost function after optimization
{#fun qlFittedBondDiscountCurveFittingMethodMinimumCostValue as minimumCostValue{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |final number of iterations used in the optimization problem
{#fun qlFittedBondDiscountCurveFittingMethodNumberOfIterations as numberOfIterations{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |number of unknown parameters found by the fit
{#fun qlFittedBondDiscountCurveFittingMethodSize as fittingMethodSize{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preErrorCheck-`String'errorCheck*-}->`Word'fromIntegral#}

-- |why the optimization stopped
fittingMethodErrorCode :: FittedBondDiscountCurve -> IO EndCriteriaType
fittingMethodErrorCode = fmap toEnum . fittingMethodErrorCodeRaw
{#fun qlFittedBondDiscountCurveFittingMethodErrorCode as fittingMethodErrorCodeRaw{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |the fitted parameters found by the optimization
{#fun qlFittedBondDiscountCurveFittingMethodSolution as fittingMethodSolution{withFittedBondDiscountCurve*`FittedBondDiscountCurve',preArray-`RealVector'&peekRealVector*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |the discount factor at time @t@ implied by a given parameter vector, without rebuilding the curve
{#fun qlFittedBondDiscountCurveFittingMethodDiscount as fittingMethodDiscount{withFittedBondDiscountCurve*`FittedBondDiscountCurve',withDoubleArray*`[Double]'&,`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A curve behind a relinkable handle. The result /is/ a 'YieldTermStructure': pass it to
-- any curve-taking function and everything built on it keeps tracking whatever the handle
-- currently points at, so a later 'linkTo' reprices already-constructed instruments
-- without rebuilding them. 'Nothing' gives an empty handle -- meaningful rather than an
-- error, since that is what makes a rate helper discount off the curve being bootstrapped
-- -- but reading a curve value through one throws until it is linked.
{#fun qlRelinkableYieldTermStructure as relinkableYieldTermStructure{withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableYieldTermStructure'peekRelinkableYieldTermStructure*#}

-- |Point a relinkable handle at a different curve. Everything already built on the handle
-- reprices against the new curve, with no object rebuilt.
--
-- This is the one mutator in the module. The API rules here otherwise forbid new setters
-- and prefer constructing a fresh object, but relinking /is/ the capability being bound:
-- a forecast curve is cloned into every floating coupon of every instrument, so without
-- it a curve scenario means rebuilding the whole portfolio.
{#fun qlRelinkableYieldTermStructureLinkTo as linkTo{withRelinkableYieldTermStructure*`RelinkableYieldTermStructure'
  ,withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Builds a set of curves that form a genuine dependency cycle -- the scenario
-- 'RelinkableYieldTermStructure' exists for. Protocol (see the class's own upstream doc
-- comment): build each member curve's rate helpers off an empty 'relinkableYieldTermStructure'
-- (the /internal/ handle), construct the curves themselves (e.g. via
-- 'piecewiseYieldCurve'), then hand each pair of (internal handle, curve) to
-- 'addBootstrappedCurve' -- which returns an /external/ handle to reference the curve by from
-- then on, and links the internal handle to it (with ownership/observability stripped to avoid
-- shared_ptr and notification cycles) so the curves' own cross-references resolve.
{#fun qlMultiCurve as multiCurve{`Double' -- ^accuracy
  ,preErrorCheck-`String'errorCheck*-}->`MultiCurve'peekMultiCurve*#}

-- |Add a curve built with a bootstrapper (e.g. 'piecewiseYieldCurve') to the
-- cycle. See 'multiCurve' for the protocol.
{#fun qlMultiCurveAddBootstrappedCurve as addBootstrappedCurve{withMultiCurve*`MultiCurve'
  ,withRelinkableYieldTermStructure*`RelinkableYieldTermStructure' -- ^internalHandle
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^curve
  ,preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Add a curve that isn't built with a bootstrapper (e.g. a spreaded curve) to the cycle. See
-- 'multiCurve' for the protocol.
{#fun qlMultiCurveAddNonBootstrappedCurve as addNonBootstrappedCurve{withMultiCurve*`MultiCurve'
  ,withRelinkableYieldTermStructure*`RelinkableYieldTermStructure' -- ^internalHandle
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^curve
  ,preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
