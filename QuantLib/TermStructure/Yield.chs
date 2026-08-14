{-# LANGUAGE TemplateHaskell #-}
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
  , overnightIndexFutureRateHelper
  , sofrFutureRateHelper
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
  , IterativeBootstrapOpts(..)
  , defaultIterativeBootstrapOpts
  , piecewiseYieldCurveFull
  , piecewiseYieldCurveFull'
  , piecewiseYieldCurveGlobalBootstrap'
  , piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear'
  , piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull'
  , interpolatedZeroCurve
  , interpolatedForwardCurve
  , interpolatedDiscountCurve

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
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import Language.Haskell.TH(mkName)
import Language.Haskell.TH.Lib(varT)
import QuantLib.Quote hiding(linkTo)
import Data.Maybe(fromMaybe)
import qualified QuantLib.Instrument.Bond as Bond (BondPriceType)
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.CashFlow#}(RateAveragingType(..))
{#import QuantLib.Time.Calendar#}(BusinessDayConvention(..))
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

-- IterativeBootstrapOpts bundles every constructor parameter of QuantLib's
-- @IterativeBootstrap@ (@ql\/termstructures\/iterativebootstrap.hpp@), which is the
-- bootstrapper 'piecewiseYieldCurve'\/'piecewiseYieldCurve'' use and whose settings they
-- hardcode to upstream's defaults. Shape borrowed from QuantLib-SWIG's @_IterativeBootstrap@
-- struct. Same splice-placement constraint as OISRateHelperOpts above.
$(deriveOptionsRecord "IterativeBootstrapOpts" []
  [ ("ibAccuracy", [t|Maybe Double|], [|Nothing|])
  , ("ibMinValue", [t|Maybe Double|], [|Nothing|])
  , ("ibMaxValue", [t|Maybe Double|], [|Nothing|])
  , ("ibMaxAttempts", [t|Word|], [|1|])
  , ("ibMaxFactor", [t|Double|], [|2.0|])
  , ("ibMinFactor", [t|Double|], [|2.0|])
  , ("ibDontThrow", [t|Bool|], [|False|])
  , ("ibDontThrowSteps", [t|Word|], [|10|])
  , ("ibMaxEvaluations", [t|Word|], [|100|])
  ])

-- Upstream defaults accuracy/minValue/maxValue to Null<Real>() rather than to a number, so
-- those three are Maybe on the Haskell side; fromMaybeDouble supplies the sentinel, and the
-- {#fun#} specs below take a plain Double, hence the realToFrac.
nullableDouble :: Maybe Double -> Double
nullableDouble = realToFrac . fromMaybeDouble

{#fun qlDepositRateHelper1 as depositRateHelper'{withQuote*`GenQuote q',withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlDepositRateHelper as depositRateHelper{withQuote*`GenQuote q' -- ^rate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar' -- ^calendar
  ,`BusinessDayConvention' -- ^convention
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFixedRateBondHelper as fixedRateBondHelper{withQuote*`GenQuote q',fromIntegral`Word',`Double',withSchedule*`Schedule',withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',`BusinessDayConvention',`Double',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}
-- |Bootstrap helper for a 'QuantLib.Instrument.Bond.CPIBond' -- a 'CPIBondHelper', which is a
-- plain 'BondHelper' subclass with no extra methods, so it's returned as the generic
-- 'BondHelper' type (same shape as 'fixedRateBondHelper').
{#fun qlCPIBondHelper as cpiBondHelper{withQuote*`GenQuote q',fromIntegral`Word' -- ^settlementDays
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
{#fun qlYieldTSDiscount as discount'{withYieldTermStructure*`GenYieldTermStructure y'
  ,withDay*`Day' -- ^d
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapRateHelper1 as swapRateHelper'{withQuote*`GenQuote q1' -- ^rate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,withCalendar*`Calendar' -- ^calendar
  ,`Frequency' -- ^fixedFrequency
  ,`BusinessDayConvention' -- ^fixedConvention
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
{#fun qlFlatForward as flatForward{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
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

{#fun qlFraRateHelper as fraRateHelper{withQuote*`GenQuote q' -- ^rate
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

-- |Bootstrapping helper for an ibor-ibor basis swap: pays @baseIndex + basis@, receives
-- @otherIndex@. Pass @bootstrapBaseCurve = True@ (with 'otherIndex' carrying a forecast curve)
-- to bootstrap the forecast curve for 'baseIndex', or 'False' (with 'baseIndex' carrying a
-- forecast curve) to bootstrap the forecast curve for 'otherIndex'. An exogenous discount curve
-- is always required.
{#fun qlIborIborBasisSwapRateHelper as iborIborBasisSwapRateHelper{withQuote*`GenQuote q' -- ^basis
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar' -- ^calendar
  ,`BusinessDayConvention' -- ^convention
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
  ,`BusinessDayConvention' -- ^convention
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
  ,`BusinessDayConvention' -- ^convention
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
  ,`BusinessDayConvention' -- ^convention
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
  ,`BusinessDayConvention' -- ^convention
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
  ,`BusinessDayConvention' -- ^convention
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
  ,`BusinessDayConvention' -- ^paymentConvention
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
  ,`BusinessDayConvention' -- ^convention (q1.k.q1. overnightConvention)
  ,preErrorCheck-`String'errorCheck*-}->`OISRateHelper'peekOISRateHelper*#}
{#fun qlOISRateHelper2 as oisRateHelper2_{withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withQuote*`GenQuote q1'
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountingCurve
  ,`Bool' -- ^telescopicValueDates
  ,fromIntegral`Int' -- ^paymentLag
  ,`BusinessDayConvention' -- ^paymentConvention
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
  ,`BusinessDayConvention' -- ^convention (q1.k.q1. overnightConvention)
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

{#fun qlSwapRateHelper as swapRateHelper{withQuote*`GenQuote q1',withSwapIndex*`GenSwapIndex sidx',withMaybeQuote*`Maybe (GenQuote q2)',fromEnumQuantity`(Int,TimeUnit)'&,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^endOfMonth
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,withMaybeFloatingRateCouponPricer*`Maybe FloatingRateCouponPricer' -- ^couponPricer
  ,preErrorCheck-`String'errorCheck*-}->`SwapRateHelper'peekSwapRateHelper*#}
{#fun qlForwardSpreadedTermStructure as forwardSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlZeroSpreadedTermStructure as zeroSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlBMASwapRateHelper as bmaSwapRateHelper{withQuote*`GenQuote q' -- ^liborFraction
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDAys
  ,withCalendar*`Calendar',fromEnumQuantity`(Int,TimeUnit)'& -- ^bmpPeriod
  ,`BusinessDayConvention',withDayCounter*`DayCounter',withBMAIndex*`BMAIndex',withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFraRateHelper1 as fraIborRateHelper'{withQuote*`GenQuote q',fromIntegral`Word' -- ^monthsToStart
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFraRateHelper2 as fraRateHelper'{withQuote*`GenQuote q',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,fromIntegral`Word' -- ^lengthInMonths
  ,fromIntegral`Word' -- ^fixingDays
  ,withCalendar*`Calendar',`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFraRateHelper3 as fraIborRateHelper{withQuote*`GenQuote q',fromEnumQuantity`(Int,TimeUnit)'& -- ^periodToStart
  ,withIborIndex*`GenIborIndex ibor'
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,`Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFuturesRateHelper1 as futuresRateHelper'{withQuote*`GenQuote q1',withDay*`Day' -- ^immStartDate
  ,withDay*`Day' -- ^endDate
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFuturesRateHelper2 as futuresIborRateHelper{withQuote*`GenQuote q1',withDay*`Day' -- ^immDate
  ,withIborIndex*`GenIborIndex ibor',withMaybeQuote*`Maybe (GenQuote q2)',preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlFuturesRateHelper as futuresRateHelper{withQuote*`GenQuote q1',withDay*`Day' -- ^immDate
  ,fromIntegral`Word' -- ^lengthInMonths
  ,withCalendar*`Calendar',`BusinessDayConvention',`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`FuturesType' -- ^type
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlOvernightIndexFutureRateHelper as overnightIndexFutureRateHelper{withQuote*`GenQuote q1',withDay*`Day' -- ^valueDate
  ,withDay*`Day' -- ^maturityDate
  ,withOvernightIborIndex*`OvernightIborIndex'
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`RateAveragingType' -- ^averagingMethod
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlSofrFutureRateHelper as sofrFutureRateHelper{withQuote*`GenQuote q1',`Month' -- ^referenceMonth
  ,fromIntegral`Int' -- ^referenceYear
  ,`Frequency' -- ^referenceFreq
  ,withMaybeQuote*`Maybe (GenQuote q2)' -- ^convexityAdjustment
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`RateHelper'peekRateHelper*#}
{#fun qlRateHelperImpliedQuote as impliedQuote{withRateHelper*`GenRateHelper rh',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlImpliedTermStructure as impliedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

piecewiseZeroSpreadedTermStructure :: GenYieldTermStructure y
  -> [(Day, GenQuote q)]  -- ^spreads
  -> Compounding -> Frequency -> IO YieldTermStructure
piecewiseZeroSpreadedTermStructure ts qd = qlPiecewiseZeroSpreadedTermStructure ts qs ds where (ds, qs) = unzip qd
{#fun qlPiecewiseZeroSpreadedTermStructure{withYieldTermStructure*`GenYieldTermStructure y',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

{#fun qlQuantoTermStructure as quantoTermStructure{withYieldTermStructure*`GenYieldTermStructure y1' -- ^underlyingDividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure y3' -- ^foreignRsikFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv1' -- ^underlyingBlackVolTS
  ,`Double' -- ^strike
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv2' -- ^exchRateBlackVolTS
  ,`Double' -- ^exchRateATMlevel
  ,`Double' -- ^underlyingExchRateCorrelation
  ,preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
piecewiseYieldCurve :: Day -- ^referenceDate
  -> [GenRateHelper rh] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve d r dc qd t i = uncurryNested (qlPiecewiseYieldCurve d r dc qs ds t) (qlInterpolation i) where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurve{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [GenRateHelper rh] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurve' s cal r dc qd t i ex = uncurryNested (qlPiecewiseYieldCurve1 s cal r dc qs ds t) (qlInterpolation i) ex where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurve1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurve', but exposes every @IterativeBootstrap@ setting through
-- 'IterativeBootstrapOpts' instead of hardcoding upstream's defaults. Start from
-- 'defaultIterativeBootstrapOpts' and override with record-update syntax; passing it
-- unchanged is exactly 'piecewiseYieldCurve'. 'ibAccuracy'\/'ibMinValue'\/'ibMaxValue' are
-- 'Maybe' because upstream defaults them to @Null\<Real\>()@ (\"pick a sensible value per
-- pillar\"), not to a number. 'ibDontThrow' is the one to reach for when a curve fails to
-- bootstrap: it substitutes the best value found so far for a pillar that won't solve,
-- rather than throwing.
piecewiseYieldCurveFull :: Day -- ^referenceDate
  -> [GenRateHelper rh] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> IO YieldTermStructure
piecewiseYieldCurveFull d r dc qd t i b =
  uncurryNested (qlPiecewiseYieldCurveFull d r dc qs ds t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
  where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurveFull{withDay*`Day',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`BootstrapTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |'piecewiseYieldCurve'' with the same @IterativeBootstrap@ settings 'piecewiseYieldCurveFull'
-- exposes; see there for what they mean.
piecewiseYieldCurveFull' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [GenRateHelper rh] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveFull' s cal r dc qd t i b ex =
  uncurryNested (qlPiecewiseYieldCurveFull1 s cal r dc qs ds t) (qlInterpolation i)
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
  -> [GenRateHelper rh] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Double -- ^accuracy
  -> [Double] -- ^instrumentWeights (empty for upstream's default equal weighting)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrap' s cal r dc qd acc w ex = qlPiecewiseYieldCurveGlobalBootstrap1 s cal r dc qs ds acc w ex where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurveGlobalBootstrap1{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Double',withDoubleArray*`[Double]'&,`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

-- |Like 'piecewiseYieldCurveGlobalBootstrap'', but hardcodes trait=SimpleZeroYield\/
-- interpolator=Linear instead of trait=Discount\/interpolator=LogLinear -- QuantLib-SWIG's only
-- bound @GlobalBootstrap@ combination (@GlobalLinearSimpleZeroCurve@).
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [GenRateHelper rh] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> Double -- ^accuracy
  -> [Double] -- ^instrumentWeights (empty for upstream's default equal weighting)
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear' s cal r dc qd acc w ex = qlPiecewiseYieldCurveGlobalBootstrap2 s cal r dc qs ds acc w ex where (ds, qs) = unzip qd
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
  -> [GenRateHelper rh1] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps
  -> [GenRateHelper rh2] -- ^additionalHelpers
  -> [Day] -- ^additionalDates (length must be @length additionalHelpers - 2@)
  -> Double -- ^accuracy
  -> Bool -- ^extrapolate past the curve's max date
  -> IO YieldTermStructure
piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' s cal r dc qd ar ad acc ex =
  qlPiecewiseYieldCurveGlobalBootstrap3 s cal r dc qs ds ar ad acc ex where (ds, qs) = unzip qd
{#fun qlPiecewiseYieldCurveGlobalBootstrap3{fromIntegral`Word',withCalendar*`Calendar',withRateHelperArray*`[GenRateHelper rh1]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,withRateHelperArray*`[GenRateHelper rh2]'&,withDayArray*`[Day]'&,`Double',`Bool',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

interpolatedDiscountCurve :: [(Day, Double)] -- ^dates, dfs
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedDiscountCurve r dc c qd i = uncurryNested (qlInterpolatedDiscountCurve rs rd dc c qs ds) (qlInterpolation i)
  where (rd, rs) = unzip r
        (ds, qs) = unzip qd
{#fun qlInterpolatedDiscountCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

interpolatedForwardCurve :: [(Day, Double)] -- ^dates, forwards
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedForwardCurve r dc c qd i = uncurryNested (qlInterpolatedForwardCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip r; (ds, qs) = unzip qd}
{#fun qlInterpolatedForwardCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}

interpolatedZeroCurve :: [(Day, Double)] -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Day, GenQuote q)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve r dc c qd i = uncurryNested (qlInterpolatedZeroCurve rs rd dc c qs ds) (qlInterpolation i) where {(rd, rs) = unzip r; (ds, qs) = unzip qd}
{#fun qlInterpolatedZeroCurve{withDoubleArray*`[Double]'&,withDayArray*`[Day]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
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
