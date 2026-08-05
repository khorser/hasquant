{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Instrument.Swap
  (
    Swaption
  , Swap
  , VanillaSwap
  , AssetSwap
  , OvernightIndexedSwap
  , BMASwap

  , asSwap

  , impliedVolatility
  , SwapType(..)

  , swap'
  , swap
  , bmaSwap
  , vanillaSwap
  , makeVanillaSwap

  , endDiscounts
  , leg
  , legBPS
  , legNPV
  , maturityDate
  , npvDateDiscount
  , startDate
  , startDiscounts

  , bmaLeg
  , bmaLegBPS
  , bmaLegNPV
  , fairLiborFraction
  , fairLiborSpread
  , liborFraction
  , liborLeg
  , liborLegBPS
  , liborLegNPV

  , swaption

  -- AssetSwap
  , assetSwap

  , bondLeg
  , cleanPrice
  , fairCleanPrice
  , fairNonParRepayment
  , nonParRepayment
  , parSwap
  , payBondCoupon

  -- OvernightIndexedSwap
  , overnightIndexedSwap
  , overnightIndexedSwap'

  , overnightLeg
  , overnightLegBPS
  , overnightLegNPV

  , HasFixedLeg(..)
  , HasFloatingLeg(..)
  , HasSpread(..)
  ) where
import Data.Maybe(fromMaybe)
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Time.Calendar#}(BusinessDayConvention(..), adjust, advance)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
import QuantLib.Time.Schedule(schedule, DateGenerationRule(..))
import QuantLib.Time.Date(addPeriod)
import QuantLib.Settings(evaluationDate)
import QuantLib.Index(fixingCalendar)
import QuantLib.Index.InterestRate(tenor, dayCounter, businessDayConvention)

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex' nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlOption as Option foreign -> COption' nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlCreditDefaultSwap as CreditDefaultSwap foreign -> CCreditDefaultSwap' nocode#}
{#pointer *Schedule as Schedule foreign -> CSchedule nocode#}
{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *QlExercise nocode#}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum SwapType{} deriving(Show, Eq)#}

{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlSwaption as Swaption foreign -> CSwaption' nocode#}
{#pointer *QlSwap as Swap foreign -> CSwap' nocode#}
{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap' nocode#}
{#pointer *QlAssetSwap as AssetSwap foreign -> CAssetSwap' nocode#}
{#pointer *QlBMASwap as BMASwap foreign -> CBMASwap' nocode#}
{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap' nocode#}

-- |implied volatility
{#fun qlSwaptionImpliedVolatility as impliedVolatility{withSwaption*`Swaption',`Double' -- ^price
  ,withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Multi leg constructor.
swap' :: [(Leg, Bool)] -- ^(legs, payer)
  -> IO Swap
swap' = (uncurry qlSwap1) . unzip
{#fun qlSwap1{withLegArray*`[Leg]'&,withBoolArray*`[Bool]'&,preErrorCheck-`String'errorCheck*-}->`Swap'peekSwap*#}
-- |Swap paying Libor against BMA coupons
{#fun qlBMASwap as bmaSwap{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule' -- ^liborSchedule
  ,`Double' -- ^liborFraction
  ,`Double' -- ^liborSpread
  ,withIborIndex*`GenIborIndex a',withDayCounter*`DayCounter' -- ^liborDayCount
  ,withSchedule*`Schedule' -- ^bmaSchedule
  ,withBMAIndex*`BMAIndex',withDayCounter*`DayCounter' -- ^bmaDayCount
  ,preErrorCheck-`String'errorCheck*-}->`BMASwap'peekBMASwap*#}
{#fun qlVanillaSwap as vanillaSwap{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule' -- ^fixedSchedule
  ,`Double' -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withSchedule*`Schedule' -- ^floatSchedule
  ,withIborIndex*`GenIborIndex a',
  `Double' -- ^spread
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,`BusinessDayConvention' -- ^paymentConvention
  ,preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

-- | Haskell equivalent of QuantLib's fluent @MakeVanillaSwap@ builder -- a
-- single function with 'Maybe'-wrapped optional parameters instead of
-- chained @.with*@ calls, covering the subset of @makevanillaswap.hpp@'s
-- fields named in the parameters below. Not covered at all (no parameter):
-- explicit effective\/termination date overrides, a settlement calendar
-- distinct from the floating-leg one, floating-leg tenor\/convention\/
-- termination convention\/day count overrides (always taken from the
-- index, matching upstream's own defaults), @withRule@ variants (always
-- @DateGeneration::Backward@), end-of-month\/first-date\/next-to-last-date
-- overrides, a floating-leg spread other than @0@, a discounting term
-- structure or custom pricing engine (use 'setPricingEngine' on the
-- result instead), indexed\/at-par coupon overrides, and payment
-- convention (always the floating leg's, matching upstream's own default
-- when unset). @fixedLegTenor@\/@fixedLegDayCount@ are required arguments
-- here rather than optional with upstream's currency-based inference. A
-- 'Nothing' @settlementDays@ behaves as @Just 0@, rather than replicating
-- upstream's index-@valueDate@-based spot-date convention.
makeVanillaSwap
  :: (Word, TimeUnit)             -- ^swapTenor
  -> GenIborIndex a
  -> Double                       -- ^fixedRate
  -> (Int, TimeUnit)              -- ^forwardStart
  -> Maybe Int                    -- ^settlementDays
  -> (Word, TimeUnit)             -- ^fixedLegTenor
  -> DayCounter                   -- ^fixedLegDayCount
  -> Maybe BusinessDayConvention  -- ^fixedLegConvention
  -> Maybe BusinessDayConvention  -- ^fixedLegTerminationDateConvention
  -> Maybe Calendar               -- ^fixedLegCalendar
  -> Maybe Calendar               -- ^floatingLegCalendar
  -> Maybe Double                 -- ^nominal
  -> Maybe SwapType
  -> IO VanillaSwap
makeVanillaSwap (swLen, swUnit) index fixedRate forwardStart mSettlementDays
    fixedTenor fixedDayCount mFixedConvention mFixedTerminationConvention mFixedCalendar
    mFloatCalendar mNominal mType = do
  idxCalendar <- fixingCalendar index
  floatTenor <- tenor index
  floatDayCount <- dayCounter index
  refDate <- evaluationDate
  let floatConv = businessDayConvention index
      floatCalendar = fromMaybe idxCalendar mFloatCalendar
      fixedCalendar = fromMaybe idxCalendar mFixedCalendar
      fixedConvention = fromMaybe ModifiedFollowing mFixedConvention
      fixedTerminationConvention = fromMaybe ModifiedFollowing mFixedTerminationConvention
      settlementDays = fromMaybe 0 mSettlementDays
      nominal = fromMaybe 1.0 mNominal
      swapType = fromMaybe Payer mType
      (fsLen, _) = forwardStart
  spotDate <- advance floatCalendar refDate (settlementDays, Days) Following False
  startDate0 <- addPeriod spotDate forwardStart
  swapStartDate <- case compare fsLen 0 of
    LT -> adjust floatCalendar startDate0 Preceding
    GT -> adjust floatCalendar startDate0 Following
    EQ -> pure startDate0
  endDate <- addPeriod swapStartDate (fromIntegral swLen, swUnit)
  fixedSchedule <- schedule (Just swapStartDate) endDate fixedTenor fixedCalendar
    fixedConvention fixedTerminationConvention Backward False Nothing Nothing
  floatSchedule <- schedule (Just swapStartDate) endDate floatTenor floatCalendar
    floatConv floatConv Backward False Nothing Nothing
  vanillaSwap swapType nominal fixedSchedule fixedRate fixedDayCount
    floatSchedule index 0.0 floatDayCount floatConv

-- |The cash flows belonging to the first leg are paid; the ones belonging to the second leg are received.
{#fun qlSwap as swap{withLeg*`GenLeg a',withLeg*`GenLeg b',preErrorCheck-`String'errorCheck*-}->`Swap'peekSwap*#}
{#fun qlSwapEndDiscounts as endDiscounts{withSwap*`GenSwap a',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapLeg as leg{withSwap*`GenSwap a',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlSwapLegBPS as legBPS{withSwap*`GenSwap a',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapLegNPV as legNPV{withSwap*`GenSwap a',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapStartDiscounts as startDiscounts{withSwap*`GenSwap a',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwaption as swaption{withVanillaSwap*`VanillaSwap',withExercise*`Exercise',`SettlementType',preErrorCheck-`String'errorCheck*-}->`Swaption'peekSwaption*#}

-- AssetSwap
{#fun qlAssetSwap as assetSwap{`Bool' -- ^payBondCoupon
  ,withBond*`Bond',`Double' -- ^bondCleanPrice
  ,withIborIndex*`GenIborIndex a',`Double' -- spread
  ,withSchedule*`Schedule' -- ^floatSchedule
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,`Bool' -- ^parAssetSwap
  ,preErrorCheck-`String'errorCheck*-}->`AssetSwap'peekAssetSwap*#}
-- OvernightIndexedSwap
{#fun qlOvernightIndexedSwap as overnightIndexedSwap{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule',`Double'  -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDC
  ,withOvernightIborIndex*`OvernightIborIndex',`Double' -- ^spread
  ,preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}
{#fun qlOvernightIndexedSwap1 as overnightIndexedSwap'{`SwapType',withDoubleArray*`[Double]'& -- ^nominals
  ,withSchedule*`Schedule' -- ^schedule
  ,`Double' -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDC
  ,withOvernightIborIndex*`OvernightIborIndex',`Double' -- ^spread
  ,preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}
{#fun qlSwapMaturityDate as maturityDate{withSwap*`GenSwap a',preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}
{#fun qlSwapStartDate as startDate{withSwap*`GenSwap a',preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}
{#fun qlSwapNpvDateDiscount as npvDateDiscount{withSwap*`GenSwap a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapBmaLeg as bmaLeg{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlBMASwapBmaLegBPS as bmaLegBPS{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapBmaLegNPV as bmaLegNPV{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapFairLiborFraction as fairLiborFraction{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapFairLiborSpread as fairLiborSpread{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapLiborFraction as liborFraction{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapLiborLeg as liborLeg{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlBMASwapLiborLegBPS as liborLegBPS{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBMASwapLiborLegNPV as liborLegNPV{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapBondLeg as bondLeg{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlAssetSwapCleanPrice as cleanPrice{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFairCleanPrice as fairCleanPrice{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFairNonParRepayment as fairNonParRepayment{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapNonParRepayment as nonParRepayment{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapParSwap as parSwap{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlAssetSwapPayBondCoupon as payBondCoupon{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlOvernightIndexedSwapOvernightLeg as overnightLeg{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlOvernightIndexedSwapOvernightLegBPS as overnightLegBPS{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapOvernightLegNPV as overnightLegNPV{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

class HasFixedLeg a where
  fairRate :: a -> IO Double
  fixedLeg :: a -> IO Leg
  fixedLegBPS :: a -> IO Double
  fixedLegNPV :: a -> IO Double
instance HasFixedLeg OvernightIndexedSwap where
  fairRate = qlOvernightIndexedSwapFairRate
  fixedLeg = qlOvernightIndexedSwapFixedLeg
  fixedLegBPS = qlOvernightIndexedSwapFixedLegBPS
  fixedLegNPV = qlOvernightIndexedSwapFixedLegNPV
instance HasFixedLeg VanillaSwap where
  fairRate = qlVanillaSwapFairRate
  fixedLeg = qlVanillaSwapFixedLeg
  fixedLegBPS = qlVanillaSwapFixedLegBPS
  fixedLegNPV = qlVanillaSwapFixedLegNPV

class HasSpread a where
  fairSpread :: a -> IO Double
instance HasSpread VanillaSwap where
  fairSpread = qlVanillaSwapFairSpread
instance HasSpread OvernightIndexedSwap where
  fairSpread = qlOvernightIndexedSwapFairSpread
instance HasSpread AssetSwap where
  fairSpread = qlAssetSwapFairSpread
instance HasSpread CreditDefaultSwap where
  fairSpread = qlCreditDefaultSwapFairSpread

class HasFloatingLeg a where
  floatingLeg :: a -> IO Leg
  floatingLegBPS :: a -> IO Double
  floatingLegNPV :: a -> IO Double
instance HasFloatingLeg VanillaSwap where
  floatingLeg = qlVanillaSwapFloatingLeg
  floatingLegBPS = qlVanillaSwapFloatingLegBPS
  floatingLegNPV = qlVanillaSwapFloatingLegNPV
instance HasFloatingLeg AssetSwap where
  floatingLeg = qlAssetSwapFloatingLeg
  floatingLegBPS = qlAssetSwapFloatingLegBPS
  floatingLegNPV = qlAssetSwapFloatingLegNPV

{#fun qlVanillaSwapFairSpread{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFairSpread{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFairRate{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFixedLeg{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlVanillaSwapFixedLegBPS{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFixedLegNPV{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFairRate{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFixedLeg{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlOvernightIndexedSwapFixedLegBPS{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFixedLegNPV{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFairSpread{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Returns the running spread that, given the quoted recovery rate, will make the running-only CDS have an NPV of 0.This calculation does not take any upfront into account, even if one was given.
{#fun qlCreditDefaultSwapFairSpread{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFloatingLeg{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlVanillaSwapFloatingLegBPS{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFloatingLegNPV{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFloatingLeg{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlAssetSwapFloatingLegBPS{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFloatingLegNPV{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
