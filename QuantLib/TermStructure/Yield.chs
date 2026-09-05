{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Yield
  (
    YieldTermStructure
  , GenYieldTermStructure
  , BondHelper
  , RateHelper
  , SwapRateHelper
  , OISRateHelper
  , FuturesRateHelper
  , OvernightIndexFutureRateHelper
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
  , withCompositeZeroYieldStructure
  , bmaSwapRateHelper
  , multipleResetsSwapRateHelper
  , fraIborRateHelper'
  , fraRateHelper'
  , fraIborRateHelper
  , futuresRateHelper'
  , futuresIborRateHelper
  , futuresRateHelper
  , overnightIndexFutureRateHelper
  , futuresRateHelperConvexityAdjustment
  , overnightIndexFutureRateHelperConvexityAdjustment
  , sofrFutureRateHelper
  , impliedQuote
  , impliedTermStructure

  , asYieldTermStructure
  , asRateHelper

  , piecewiseZeroSpreadedTermStructure
  , quantoTermStructure
  , ultimateForwardTermStructure
  , minimumCostValue
  , numberOfIterations

  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  , IterativeBootstrapOpts(..)
  , defaultIterativeBootstrapOpts
  , piecewiseYieldCurveFull
  , piecewiseYieldCurveFull'
  , piecewiseYieldCurveGlobalBootstrap'
  , piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear'
  , piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull'
  , piecewiseYieldCurveGlobalBootstrapForwardRateLinear'
  , piecewiseYieldCurveGlobalBootstrapZeroYieldLinear'
  , piecewiseYieldCurveLocalBootstrap'
  , Bootstrap(..)
  , LocalBootstrapTrait(..)
  , piecewiseYieldCurve2'
  , interpolatedZeroCurve
  , interpolatedForwardCurve
  , interpolatedDiscountCurve
  , interpolatedSpreadDiscountCurve

  , MultiCurve
  , multiCurve
  , addBootstrappedCurve
  , addNonBootstrappedCurve

  , iborIborBasisSwapRateHelper
  , overnightIborBasisSwapRateHelper
  , constNotionalCrossCurrencyBasisSwapRateHelper
  , mtMCrossCurrencyBasisSwapRateHelper
  , constNotionalCrossCurrencySwapRateHelper
  , fxSwapRateHelper
  , fxSwapRateHelper'

  , bondHelperBond
  , swapRateHelperSwap
  , oisRateHelperSwap
  ) where
import QuantLib.Internal hiding(maxDate)
import QuantLib.Internal.Common
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import Language.Haskell.TH(mkName)
import Language.Haskell.TH.Lib(varT)
import QuantLib.Quote hiding(linkTo)
import Data.Maybe(fromMaybe)
import Data.List.NonEmpty(NonEmpty, toList)
import Foreign.Ptr(FunPtr, Ptr)
import Foreign.C.Types(CUInt)
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

-- breaking recursive dependencies with Index.InterestRate TermStructure.Volatilitiy modules
-- if you put all pointer declarations in a separate module
-- ch2s will not attach finalizers to foreign ptrs in other modules
-- I don't want to create extra modules just to workaround the issue with cyclic dependencies and this will not help with finalizers anyway
{#pointer *Calendar foreign -> CCalendar nocode#}
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
{#pointer *QlMultiCurve as MultiCurve foreign -> CMultiCurve nocode#}
{#pointer *QlRateHelper as RateHelper foreign -> CRateHelper' nocode#}
{#pointer *QlSwapRateHelper as SwapRateHelper foreign -> CSwapRateHelper' nocode#}
{#pointer *QlOISRateHelper as OISRateHelper foreign -> COISRateHelper' nocode#}
{#pointer *QlFuturesRateHelper as FuturesRateHelper foreign -> CFuturesRateHelper' nocode#}
{#pointer *QlOvernightIndexFutureRateHelper as OvernightIndexFutureRateHelper foreign -> COvernightIndexFutureRateHelper' nocode#}
{#pointer *QlBondHelper as BondHelper foreign -> CBondHelper' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *FittedBondDiscountCurveFittingMethod as QlFittedBondDiscountCurveFittingMethod foreign -> CFittedBondDiscountCurveFittingMethod nocode#}

{#enum BootstrapTrait{} deriving(Show, Eq, Read)#}
{#enum PillarChoice{} deriving(Show, Eq, Read)#}
{#enum FuturesType{} deriving(Show, Eq, Read)#}

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

-- Upstream defaults accuracy/minValue/maxValue to Null<Real>() rather than to a number, so
-- those three are Maybe on the Haskell side; fromMaybeDouble supplies the sentinel, and the
-- {#fun#} specs below take a plain Double, hence the realToFrac.
nullableDouble :: Maybe Double -> Double
nullableDouble = realToFrac . fromMaybeDouble

-- |Rate helper for bootstrapping over deposit rates, taking its conventions from an ibor index.
{#fun qlDepositRateHelper1 as depositRateHelper'{withQuote*`GenQuote q',withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Rate helper for bootstrapping over deposit rates.
{#fun qlDepositRateHelper as depositRateHelper{withQuote*`GenQuote q' -- ^rate
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

-- |Bootstrap helper for a 'QuantLib.Instrument.Bond.CPIBond' -- a 'CPIBondHelper', which is a
-- plain 'BondHelper' subclass with no extra methods, so it's returned as the generic
-- 'BondHelper' type (same shape as 'fixedRateBondHelper').
{#fun qlCPIBondHelper as cpiBondHelper{withQuote*`GenQuote q',fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,`Double' -- ^baseCPI
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withSchedule*`Schedule',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^coupons
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}

-- |Returns a discount factor from the given YieldTermStructure object
{#fun qlYieldTSDiscount as discount'{withYieldTermStructure*`GenYieldTermStructure y'
  ,withDay*`Day' -- ^d
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Rate helper for bootstrapping over swap rates, built from explicit tenor\/calendar\/
-- frequency\/day-count\/index conventions rather than a 'GenSwapIndex' bundling them
-- (as 'swapRateHelper' does).
{#fun qlSwapRateHelper1 as swapRateHelper'{withQuote*`GenQuote q1' -- ^rate
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
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}

-- |Flat interest-rate curve with a fixed reference date.
{#fun qlFlatForward as flatForward{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Flat interest-rate curve whose reference date moves with the evaluation date, offset by
-- 'settlementDays' on 'calendar'.
{#fun qlFlatForward1 as flatForward'{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |The resulting interest rate has the required daycounting rule.
{#fun qlYieldTermStructureZeroRate as zeroRate'{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
{#fun qlYieldTermStructureForwardRate1 as forwardRateForPeriod{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',fromEnumQuantity`(Int,TimeUnit)'&,withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The resulting interest rate has the required day-counting rule.
{#fun qlYieldTermStructureForwardRate as forwardRate'{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',withDay*`Day',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
{#fun qlYieldTermStructureForwardRate2 as forwardRate{withYieldTermStructure*`GenYieldTermStructure y',`Double',`Double',`Compounding',`Frequency'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
{#fun qlYieldTermStructureZeroRate1 as zeroRate{withYieldTermStructure*`GenYieldTermStructure y',`Double',`Compounding',`Frequency',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlYieldTermStructureDiscount1 as discount{withYieldTermStructure*`GenYieldTermStructure y',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Rate helper for bootstrapping over FRA rates.
{#fun qlFraRateHelper as fraRateHelper{withQuote*`GenQuote q' -- ^rate
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
{#fun qlMtMCrossCurrencyBasisSwapRateHelper as mtMCrossCurrencyBasisSwapRateHelper{withQuote*`GenQuote q' -- ^basis
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

-- |Bootstrapping helper from FX swap points, tenor-relative. 'collateralCurve' discounts the
-- collateral currency; the curve being bootstrapped is for the other currency. 'fwdPoint' and
-- 'spotFx' must be quoted in the same units (points already scaled to match the spot).
{#fun qlFxSwapRateHelper as fxSwapRateHelper{withQuote*`GenQuote q1' -- ^fwdPoint
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

-- |Bootstrapping helper from FX swap points, explicit start\/end date.
{#fun qlFxSwapRateHelper2 as fxSwapRateHelper'{withQuote*`GenQuote q1' -- ^fwdPoint
  ,withQuote*`GenQuote q2' -- ^spotFx
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,`Bool' -- ^isFxBaseCurrencyCollateralCurrency
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^collateralCurve
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
-- BondPriceType (QuantLib.Instrument.Bond) is later in exposed-modules than
-- this file, so priceType is marshalled as a plain Int via fromEnum here
-- instead of a {#import#}'d enum type, per CLAUDE.md's cross-module workaround.
bondHelper :: GenQuote q -> Bond -> Bond.BondPriceType -> IO BondHelper
bondHelper cleanPrice bond priceType = bondHelper_ cleanPrice bond (fromEnum priceType)

{#fun qlBondHelper as bondHelper_{withQuote*`GenQuote q',withBond*`Bond',`Int' -- ^priceType
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}
-- oisRateHelper/oisRateHelper' keep their original 5-param signatures (below);
-- both call the same full-arity raw bindings as oisRateHelperFull/oisRateHelperFull'
-- (the options-record wrappers spliced further down in this file), hardcoding
-- upstream's own defaults for every trailing param -- widening the underlying C
-- shim was cheaper than maintaining a second near-duplicate one (see
-- cbits/qlTermStructure.cpp's qlOISRateHelper/qlOISRateHelper2).
oisRateHelper :: Word -> (Int, TimeUnit) -> GenQuote q -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure y) -> IO OISRateHelper
oisRateHelper settlementDays tenor fixedRate idx discountingCurve = do
  cal <- calendar Null
  oisRateHelper_ settlementDays tenor fixedRate idx discountingCurve
    False 0 Following Annual cal (0, Days) Nothing LastRelevantDate Nothing AveragingCompound
    Nothing Nothing cal Nothing 0 False Nothing Backward cal ModifiedFollowing

oisRateHelper' :: Day -> Day -> GenQuote q -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure y) -> IO OISRateHelper
oisRateHelper' startDate endDate fixedRate idx discountingCurve = do
  cal <- calendar Null
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
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^pricer
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
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^pricer
  ,`DateGenerationRule' -- ^rule
  ,withCalendar*`Calendar' -- ^overnightCalendar
  ,fromEnumC`BusinessDayConvention' -- ^convention (q1.k.q1. overnightConvention)
  ,preErrorCheck-`String'errorCheck*-}->`OISRateHelper'peekOISRateHelper*#}

oisRateHelperFull :: Word -> (Int, TimeUnit) -> GenQuote q -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure y) -> OISRateHelperOpts m -> IO OISRateHelper
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

oisRateHelperFull' :: Day -> Day -> GenQuote q -> OvernightIborIndex
  -> Maybe (GenYieldTermStructure y) -> OISRateHelperOpts m -> IO OISRateHelper
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

-- |Rate helper for bootstrapping over swap rates, built from a 'GenSwapIndex' bundling the
-- swap's conventions.
{#fun qlSwapRateHelper as swapRateHelper{withQuote*`GenQuote q1' -- ^rate
  ,withSwapIndex*`GenSwapIndex sidx',withMaybeQuote*`Maybe (GenQuote q2)' -- ^spread
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^fwdStart
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^couponPricer
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

-- |Rate helper for bootstrapping over FRA rates, taking its fixing/day-count conventions from an
-- ibor index instead of explicit 'Calendar'\/'BusinessDayConvention'\/'DayCounter' arguments.
{#fun qlFraRateHelper1 as fraIborRateHelper'{withQuote*`GenQuote q',fromIntegral`Word' -- ^monthsToStart
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Rate helper for bootstrapping over FRA rates, with the FRA period given as a start\/length
-- pair rather than 'fraRateHelper''s monthsToStart\/monthsToEnd.
{#fun qlFraRateHelper2 as fraRateHelper'{withQuote*`GenQuote q',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,fromIntegral`Word' -- ^lengthInMonths
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar',fromEnumC`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Rate helper for bootstrapping over FRA rates, taking its conventions from an ibor index and
-- the FRA period as a start\/length pair.
{#fun qlFraRateHelper3 as fraIborRateHelper{withQuote*`GenQuote q',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}

-- |Rate helper for bootstrapping over IborIndex futures prices, given explicit start\/end dates.
{#fun qlFuturesRateHelper1 as futuresRateHelper'{withQuote*`GenQuote q1',withDay*`Day' -- ^immStartDate
  ,withDay*`Day' -- ^endDate
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`FuturesRateHelper'peekFuturesRateHelper*#}

-- |Rate helper for bootstrapping over IborIndex futures prices, taking its conventions from an
-- ibor index.
{#fun qlFuturesRateHelper2 as futuresIborRateHelper{withQuote*`GenQuote q1',withDay*`Day' -- ^immDate
  ,withIborIndex*`GenIborIndex ibor',withMaybeQuote*`Maybe (GenQuote q2)',preErrorCheck-`String'errorCheck*-}->`FuturesRateHelper'peekFuturesRateHelper*#}

-- |Rate helper for bootstrapping over IborIndex futures prices, given explicit
-- calendar\/convention\/day-counter conventions.
{#fun qlFuturesRateHelper as futuresRateHelper{withQuote*`GenQuote q1',withDay*`Day' -- ^immDate
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

-- |Term structure bootstrapped to reprice a set of 'instruments', one interpolated segment per
-- instrument, iteratively (pillar by pillar): each bootstrapped instrument's maturity ends its
-- own segment, and reprices correctly on the resulting curve. Fixed reference date.
piecewiseYieldCurve :: Day -- ^referenceDate
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve d r dc qd t i = uncurryNested (qlPiecewiseYieldCurve d (toList r) dc qs ds t) (qlInterpolation i) where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurve{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurve', but with a reference date that moves with the evaluation date
-- (settlement days on 'calendar'), and lets extrapolation past the curve's max date be enabled.
-- @IterativeBootstrap@, upstream's default bootstrapper, with default settings -- see
-- 'piecewiseYieldCurve2'' for choosing a different bootstrapper (@GlobalBootstrap@\/
-- @LocalBootstrap@) or overriding @IterativeBootstrap@'s own settings; this is exactly
-- @piecewiseYieldCurve2' ... ('Iterative' trait interpolator 'defaultIterativeBootstrapOpts') ...@.
piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurve' s cal r dc qd t i ex =
  piecewiseYieldCurve2' s cal r dc qd (Iterative t i defaultIterativeBootstrapOpts) ex

-- |Like 'piecewiseYieldCurve', but exposes every @IterativeBootstrap@ setting through
-- 'IterativeBootstrapOpts' instead of hardcoding upstream's defaults. Start from
-- 'defaultIterativeBootstrapOpts' and override with record-update syntax; passing it
-- unchanged is exactly 'piecewiseYieldCurve'. 'ibAccuracy'\/'ibMinValue'\/'ibMaxValue' are
-- 'Maybe' because upstream defaults them to @Null\<Real\>()@ (\"pick a sensible value per
-- pillar\"), not to a number. 'ibDontThrow' is the one to reach for when a curve fails to
-- bootstrap: it substitutes the best value found so far for a pillar that won't solve,
-- rather than throwing.
piecewiseYieldCurveFull :: Day -- ^referenceDate
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> IO YieldTermStructure
piecewiseYieldCurveFull d r dc qd t i b =
  uncurryNested (qlPiecewiseYieldCurveFull d (toList r) dc qs ds t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
  where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurveFull{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |'piecewiseYieldCurve'' with the same @IterativeBootstrap@ settings 'piecewiseYieldCurveFull'
-- exposes; see there for what they mean.
piecewiseYieldCurveFull' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveFull' s cal r dc qd t i b ex =
  uncurryNested (qlPiecewiseYieldCurveFull1 s cal (toList r) dc qs ds t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b) ex
  where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurveFull1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurve'', but bootstraps with QuantLib's @GlobalBootstrap@ instead of
-- @IterativeBootstrap@ -- all instruments (and, for a 'MultiCurve' cycle, all member curves) are
-- solved for together under one optimizer, rather than pillar-by-pillar. This is what lets a
-- rate helper reference another curve's not-yet-bootstrapped handle: see the \"relinkable
-- handles\" tests in "QuantLib.Spec.TermStructure" for the two-curve cycle this exists for.
-- Hardcodes trait=Discount\/interpolator=LogLinear in its own shim (the only combination this
-- dispatch supports, per CLAUDE.md's dispatch-table-scope note) rather than taking
-- 'BootstrapTrait'\/'Interpolation' params. 'instrumentWeights' is upstream's
-- @GlobalBootstrap@ constructor's trailing @instrumentWeights@ parameter -- an empty list
-- reproduces its default (equal weighting); a non-empty one must have one entry per alive
-- instrument. The @additionalHelpers@\/@additionalDates@\/@additionalPenalties@\/
-- @additionalVariables@ overloads (functor callbacks into the optimizer) are not bound -- see
-- README's # TODO.
piecewiseYieldCurveGlobalBootstrap' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Double -- ^accuracy
  -> [Double] -- ^instrumentWeights (empty for upstream's default equal weighting)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrap' s cal r dc qd acc w ex =
  piecewiseYieldCurve2' s cal r dc qd (GlobalDiscountLogLinear acc w) ex
{#fun qlPiecewiseYieldCurveGlobalBootstrap1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurveGlobalBootstrap'', but hardcodes trait=SimpleZeroYield\/
-- interpolator=Linear instead of trait=Discount\/interpolator=LogLinear -- QuantLib-SWIG's only
-- bound @GlobalBootstrap@ combination (@GlobalLinearSimpleZeroCurve@).
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Double -- ^accuracy
  -> [Double] -- ^instrumentWeights (empty for upstream's default equal weighting)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear' s cal r dc qd acc w ex =
  piecewiseYieldCurve2' s cal r dc qd (GlobalSimpleZeroLinear acc w) ex
{#fun qlPiecewiseYieldCurveGlobalBootstrap2{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear'', but bootstraps with
-- @GlobalBootstrap@'s functor-callback constructor instead of the plain @accuracy@\/
-- @instrumentWeights@ one -- upstream QuantLib-SWIG's canned @AdditionalErrors@\/@AdditionalDates@
-- functors (see README's # TODO), constructed internally from @additionalHelpers@\/
-- @additionalDates@ rather than taking the formula itself as a parameter (it's fixed, not a
-- user-supplied callback). @additionalDates@ must have exactly @length additionalHelpers - 2@
-- entries -- @AdditionalErrors@' fixed linear-interpolation formula produces that many
-- equations, and @GlobalBootstrap@ requires equations to match unknowns; a mismatch raises a
-- 'QuantLib.Type.Error' naming both counts.
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh1) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> NonEmpty (GenRateHelper rh2) -- ^additionalHelpers
  -> [Day] -- ^additionalDates (length must be @length additionalHelpers - 2@)
  -> Double -- ^accuracy
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' s cal r dc qd ar ad acc ex =
  piecewiseYieldCurve2' s cal r dc qd (GlobalSimpleZeroLinearFull ar ad acc) ex
{#fun qlPiecewiseYieldCurveGlobalBootstrap3{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh1]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,withRateHelperArray*`[GenRateHelper rh2]'&,withDayArray*`[Day]'&,`Double',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurveGlobalBootstrap'', but hardcodes trait=ForwardRate\/interpolator=Linear
-- instead of trait=Discount\/interpolator=LogLinear -- the other two 'IterativeBootstrap' traits
-- paired with the cheapest interpolator (github issue #15).
piecewiseYieldCurveGlobalBootstrapForwardRateLinear' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Double -- ^accuracy
  -> [Double] -- ^instrumentWeights (empty for upstream's default equal weighting)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrapForwardRateLinear' s cal r dc qd acc w ex =
  piecewiseYieldCurve2' s cal r dc qd (GlobalForwardRateLinear acc w) ex
{#fun qlPiecewiseYieldCurveGlobalBootstrap4{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurveGlobalBootstrap'', but hardcodes trait=ZeroYield\/interpolator=Linear
-- instead of trait=Discount\/interpolator=LogLinear.
piecewiseYieldCurveGlobalBootstrapZeroYieldLinear' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Double -- ^accuracy
  -> [Double] -- ^instrumentWeights (empty for upstream's default equal weighting)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrapZeroYieldLinear' s cal r dc qd acc w ex =
  piecewiseYieldCurve2' s cal r dc qd (GlobalZeroYieldLinear acc w) ex
{#fun qlPiecewiseYieldCurveGlobalBootstrap5{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurve'', but bootstraps with QuantLib's @LocalBootstrap@ instead of
-- @IterativeBootstrap@ -- each interpolated segment is solved from a local window of
-- @localisation@ neighbouring instruments rather than pillar-by-pillar over the whole curve,
-- giving a localised risk profile with a smoother (non-local) interpolation method.
-- @LocalBootstrap@'s upstream 'localInterpolate' requirement is met only by @ConvexMonotone@
-- (Hagan\/West \"Interpolation Methods for Curve Construction\"), so the interpolator is
-- hardcoded to @ConvexMonotone@ in the shim -- not a 'Interpolation' parameter here, the same
-- way 'piecewiseYieldCurveGlobalBootstrap'' hardcodes its own interpolator. @localisation@\/
-- @forcePositive@\/@accuracy@ are @LocalBootstrap@'s own constructor parameters;
-- @quadraticity@\/@monotonicity@\/@convexForcePositive@ are @ConvexMonotone@'s (upstream
-- defaults 0.3\/0.7\/'True'). 'Discount' is rejected with a 'QuantLib.Type.Error': verified
-- (against a standalone reproduction with the same installed QuantLib, independent of hasquant)
-- to return numerically wrong discount factors with this bootstrapper\/interpolator pair,
-- regardless of @accuracy@ or the input quotes -- use 'ForwardRate', 'ZeroYield' or
-- 'SimpleZeroYield' instead, all three of which reprice correctly. Matches upstream's own
-- @test-suite\/piecewiseyieldcurve.cpp@, whose only @LocalBootstrap@+@ConvexMonotone@ coverage
-- uses 'ForwardRate', never 'Discount'.
piecewiseYieldCurveLocalBootstrap' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait ('Discount' is rejected, see above)
  -> Word -- ^localisation
  -> Bool -- ^forcePositive (LocalBootstrap's)
  -> Double -- ^accuracy
  -> Double -- ^quadraticity (ConvexMonotone's)
  -> Double -- ^monotonicity (ConvexMonotone's)
  -> Bool -- ^convexForcePositive (ConvexMonotone's)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
-- Not delegated to piecewiseYieldCurve2': this function's signature takes the full
-- 'BootstrapTrait' (including 'Discount', for backward compatibility) and raises a
-- 'QuantLib.Type.Error' for it at runtime via the C shim's own QL_FAIL, whereas 'Local' takes
-- 'LocalBootstrapTrait', which has no 'Discount' case to convert from -- see 'Bootstrap'.
piecewiseYieldCurveLocalBootstrap' s cal r dc qd t loc fp acc q m cfp ex =
  qlPiecewiseYieldCurveLocalBootstrap1 s cal (toList r) dc qs ds t loc fp acc q m cfp ex where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurveLocalBootstrap1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',fromIntegral`Word',`Bool',`Double',`Double',`Double',`Bool',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Selects which of QuantLib's three @PiecewiseYieldCurve@ bootstrappers 'piecewiseYieldCurve2''
-- uses, and carries exactly the parameters valid for that choice -- no combination this ADT can
-- express is rejected at runtime by 'piecewiseYieldCurve2'' (contrast 'piecewiseYieldCurveLocalBootstrap''
-- above, which still takes a full 'BootstrapTrait' and rejects 'Discount' with a
-- 'QuantLib.Type.Error': 'Local' uses 'LocalBootstrapTrait' instead, which simply has no
-- constructor for it). 'Iterative' is upstream's default bootstrapper (see 'piecewiseYieldCurve''\/
-- 'piecewiseYieldCurveFull''); the three 'Global*' constructors and 'Local' mirror
-- 'piecewiseYieldCurveGlobalBootstrap''\/'piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear''\/
-- 'piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull''\/
-- 'piecewiseYieldCurveGlobalBootstrapForwardRateLinear''\/
-- 'piecewiseYieldCurveGlobalBootstrapZeroYieldLinear''\/'piecewiseYieldCurveLocalBootstrap''
-- respectively -- see those functions' haddock for what each field means, since 'piecewiseYieldCurve2''
-- dispatches straight through to the same shims they use.
data Bootstrap rh2
  = Iterative BootstrapTrait Interpolation IterativeBootstrapOpts
  | GlobalDiscountLogLinear Double [Double] -- ^accuracy, instrumentWeights
  | GlobalSimpleZeroLinear Double [Double] -- ^accuracy, instrumentWeights
  | GlobalSimpleZeroLinearFull (NonEmpty (GenRateHelper rh2)) [Day] Double -- ^additionalHelpers, additionalDates, accuracy
  | GlobalForwardRateLinear Double [Double] -- ^accuracy, instrumentWeights
  | GlobalZeroYieldLinear Double [Double] -- ^accuracy, instrumentWeights
  | Local LocalBootstrapTrait Word Bool Double Double Double Bool
    -- ^trait, localisation, forcePositive (LocalBootstrap's), accuracy, quadraticity, monotonicity, convexForcePositive (ConvexMonotone's)

-- |'BootstrapTrait' restricted to the three traits 'piecewiseYieldCurveLocalBootstrap''\/'Local'
-- accept -- 'Discount' has no constructor here because it is numerically unusable with
-- @LocalBootstrap@\/@ConvexMonotone@ (see 'piecewiseYieldCurveLocalBootstrap''), not merely
-- undesirable, so it is unrepresentable rather than rejected at runtime.
data LocalBootstrapTrait = LForwardRate | LZeroYield | LSimpleZeroYield
  deriving (Show, Eq, Read)

fromBootstrapTrait :: LocalBootstrapTrait -> BootstrapTrait
fromBootstrapTrait LForwardRate = ForwardRate
fromBootstrapTrait LZeroYield = ZeroYield
fromBootstrapTrait LSimpleZeroYield = SimpleZeroYield

-- |Bootstraps a term structure with settlement-day reference-date semantics (see
-- 'piecewiseYieldCurve''), choosing the bootstrapper via 'Bootstrap' instead of by which function
-- you call. 'piecewiseYieldCurve''\/'piecewiseYieldCurveFull''\/'piecewiseYieldCurveGlobalBootstrap''\/
-- 'piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear''\/'piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull''\/
-- 'piecewiseYieldCurveLocalBootstrap'' are each a one-line call into this function with a
-- particular 'Bootstrap' constructor; kept as separate named entry points since 'piecewiseYieldCurve'
-- (fixed reference date, no settlement days) has no counterpart here -- @GlobalBootstrap@\/
-- @LocalBootstrap@ have no fixed-reference-date shim upstream, so a fully unified entry point can
-- only exist in this settlementDays-taking shape.
piecewiseYieldCurve2' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty (GenRateHelper rh) -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Bootstrap rh2 -- ^bootstrapper choice
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurve2' s cal r dc qd bootstrap ex = case bootstrap of
  Iterative t i b -> uncurryNested (qlPiecewiseYieldCurveFull1 s cal rs dc qs ds t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b) ex
  GlobalDiscountLogLinear acc w -> qlPiecewiseYieldCurveGlobalBootstrap1 s cal rs dc qs ds acc w ex
  GlobalSimpleZeroLinear acc w -> qlPiecewiseYieldCurveGlobalBootstrap2 s cal rs dc qs ds acc w ex
  GlobalSimpleZeroLinearFull ah ad acc -> qlPiecewiseYieldCurveGlobalBootstrap3 s cal rs dc qs ds (toList ah) ad acc ex
  GlobalForwardRateLinear acc w -> qlPiecewiseYieldCurveGlobalBootstrap4 s cal rs dc qs ds acc w ex
  GlobalZeroYieldLinear acc w -> qlPiecewiseYieldCurveGlobalBootstrap5 s cal rs dc qs ds acc w ex
  Local t loc fp acc q m cfp -> qlPiecewiseYieldCurveLocalBootstrap1 s cal rs dc qs ds (fromBootstrapTrait t) loc fp acc q m cfp ex
  where (ds, qs) = unzip qd
        rs = toList r

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

-- |Yield curve interpolating zero-yield rates directly between the given dates.
interpolatedZeroCurve :: NonEmpty (Day, Double) -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve r dc c qd i = uncurryNested (qlInterpolatedZeroCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip (toList r); (ds, qs) = unzip qd}
{#fun qlInterpolatedZeroCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Discount factors interpolated as a multiplicative spread applied on top of 'baseCurve'.
-- Upstream requires the first discount factor to be exactly @1.0@, flagging its date as the
-- curve's own reference date; a mismatched leading value throws a 'QuantLib.Type.Error'.
interpolatedSpreadDiscountCurve :: GenYieldTermStructure y
  -> NonEmpty (Day, Double) -- ^dates, dfs
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedSpreadDiscountCurve ts r i = uncurryNested (qlInterpolatedSpreadDiscountCurve ts rs rd) (qlInterpolation i) where (rd, rs) = unzip (toList r)
{#fun qlInterpolatedSpreadDiscountCurve{withYieldTermStructure*`GenYieldTermStructure y',withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |reference date based on current evaluation date
withNonEmptyBondHelperArray :: NonEmpty BondHelper -> ((CUInt, Ptr (Ptr CBondHelper')) -> IO a) -> IO a
withNonEmptyBondHelperArray = withBondHelperArray . toList

{#fun qlFittedBondDiscountCurve as fittedBondDiscountCurve{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar',withNonEmptyBondHelperArray*`NonEmpty BondHelper'&,withDayCounter*`DayCounter',withFittedBondDiscountCurveFittingMethod*`FittingMethod'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,withDoubleArray*`[Double]'& -- ^guess
  ,`Double' -- ^simplexLambda
  ,preErrorCheck-`String'errorCheck*-}->`FittedBondDiscountCurve'peekFittedBondDiscountCurve*#}

-- |curve reference date fixed for life of curve
{#fun qlFittedBondDiscountCurve1 as fittedBondDiscountCurve'{withDay*`Day',withNonEmptyBondHelperArray*`NonEmpty BondHelper'&,withDayCounter*`DayCounter',withFittedBondDiscountCurveFittingMethod*`FittingMethod'
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
-- 'piecewiseYieldCurveGlobalBootstrap''), then hand each pair of (internal handle, curve) to
-- 'addBootstrappedCurve' -- which returns an /external/ handle to reference the curve by from
-- then on, and links the internal handle to it (with ownership/observability stripped to avoid
-- shared_ptr and notification cycles) so the curves' own cross-references resolve.
{#fun qlMultiCurve as multiCurve{`Double' -- ^accuracy
  ,preErrorCheck-`String'errorCheck*-}->`MultiCurve'peekMultiCurve*#}

-- |Add a curve built with a bootstrapper (e.g. 'piecewiseYieldCurveGlobalBootstrap'') to the
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

-- |The bond the helper prices. For 'fixedRateBondHelper'\/'cpiBondHelper' this is the only way
-- to reach it, since they build the bond internally rather than taking one (unlike 'bondHelper').
{#fun qlBondHelperBond as bondHelperBond{withGenRateHelper*`BondHelper',preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |The underlying swap the helper builds from its tenor and index.
{#fun qlSwapRateHelperSwap as swapRateHelperSwap{withGenRateHelper*`SwapRateHelper',preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

-- |The underlying overnight indexed swap the helper builds from its tenor and index.
{#fun qlOISRateHelperSwap as oisRateHelperSwap{withGenRateHelper*`OISRateHelper',preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
