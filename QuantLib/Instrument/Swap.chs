{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Instrument.Swap
  (
    Swaption
  , NonstandardSwaption
  , Swap
  , FixedVsFloatingSwap
  , VanillaSwap
  , NonstandardSwap
  , AssetSwap
  , OvernightIndexedSwap
  , BMASwap
  , ZeroCouponInflationSwap
  , YearOnYearInflationSwap
  , CPISwap
  , ZeroCouponSwap
  , EquityTotalReturnSwap
  , VarianceSwap
  , VarianceOption

  , asSwap

  , impliedVolatility
  , SwapType(..)
  , SwaptionPriceType(..)
  , CPIInterpolationType(..)
  , CalibrationBasketType(..)

  , swap'
  , swap
  , bmaSwap
  , vanillaSwap
  , nonstandardSwapFromVanilla
  , nonstandardSwap
  , nonstandardSwap'
  , makeVanillaSwap
  , makeCms
  , zeroCouponInflationSwap
  , zcisFairRate
  , yearOnYearInflationSwap
  , yoyFairRate
  , cpiSwap
  , cpiSwapFairRate
  , zeroCouponSwap
  , zeroCouponSwap'
  , fairFixedPayment
  , fairFixedRate
  , equityTotalReturnSwapIbor
  , equityTotalReturnSwapOvernight
  , equityLegNPV
  , interestRateLegNPV
  , fairMargin
  , varianceSwap
  , variance
  , varianceOption

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
  , nonstandardSwaptionFromSwaption
  , nonstandardSwaption
  , calibrationBasket

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
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.CashFlow#}(RateAveragingType)
import QuantLib.CashFlow(cmsLeg, iborLeg)
{#import QuantLib.Time.Calendar#}(adjust, advance)
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
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum SwapType{} deriving(Show, Eq)#}
{#enum SwaptionPriceType{} add prefix="Swaption" deriving(Show, Eq)#}

{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlSwaption as Swaption foreign -> CSwaption' nocode#}
{#pointer *QlSwap as Swap foreign -> CSwap' nocode#}
{#pointer *QlFixedVsFloatingSwap as FixedVsFloatingSwap foreign -> CFixedVsFloatingSwap' nocode#}
{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap' nocode#}
{#pointer *QlNonstandardSwap as NonstandardSwap foreign -> CNonstandardSwap' nocode#}
{#pointer *QlNonstandardSwaption as NonstandardSwaption foreign -> CNonstandardSwaption' nocode#}
{#pointer *QlBlackCalibrationHelper as BlackCalibrationHelper foreign -> CBlackCalibrationHelper' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlAssetSwap as AssetSwap foreign -> CAssetSwap' nocode#}
{#pointer *QlBMASwap as BMASwap foreign -> CBMASwap' nocode#}
{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap' nocode#}
{#pointer *QlZeroCouponInflationSwap as ZeroCouponInflationSwap foreign -> CZeroCouponInflationSwap' nocode#}
{#pointer *QlYearOnYearInflationSwap as YearOnYearInflationSwap foreign -> CYearOnYearInflationSwap' nocode#}
{#pointer *QlCPISwap as CPISwap foreign -> CCPISwap' nocode#}
{#pointer *QlZeroCouponSwap as ZeroCouponSwap foreign -> CZeroCouponSwap' nocode#}
{#pointer *QlEquityTotalReturnSwap as EquityTotalReturnSwap foreign -> CEquityTotalReturnSwap' nocode#}
{#pointer *QlEquityIndex as EquityIndex foreign -> CEquityIndex' nocode#}

-- |implied volatility
{#fun qlSwaptionImpliedVolatility as impliedVolatility{withSwaption*`Swaption',`Double' -- ^price
  ,withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,`SwaptionPriceType' -- ^priceType
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
  ,withIborIndex*`GenIborIndex ibor',withDayCounter*`DayCounter' -- ^liborDayCount
  ,withSchedule*`Schedule' -- ^bmaSchedule
  ,withBMAIndex*`BMAIndex',withDayCounter*`DayCounter' -- ^bmaDayCount
  ,preErrorCheck-`String'errorCheck*-}->`BMASwap'peekBMASwap*#}

-- |Fixed-rate vs floating-rate (Ibor) swap; if no payment convention is given, the floating leg's is used.
{#fun qlVanillaSwap as vanillaSwap{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule' -- ^fixedSchedule
  ,`Double' -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withSchedule*`Schedule' -- ^floatSchedule
  ,withIborIndex*`GenIborIndex ibor',
  `Double' -- ^spread
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^paymentConvention
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

-- |Converts an existing 'VanillaSwap' into a 'NonstandardSwap' (upstream's own conversion
-- constructor, @NonstandardSwap(const FixedVsFloatingSwap&)@).
{#fun qlNonstandardSwap1 as nonstandardSwapFromVanilla{withVanillaSwap*`VanillaSwap'
  ,preErrorCheck-`String'errorCheck*-}->`NonstandardSwap'peekNonstandardSwap*#}

-- |'VanillaSwap' generalized to per-period fixed/floating nominals and fixed rates, plus
-- optional intermediate\/final notional exchange -- a single 'Double' gearing\/spread shared
-- across all floating periods. See 'nonstandardSwap'' for a per-period gearing\/spread.
{#fun qlNonstandardSwap as nonstandardSwap{`SwapType'
  ,withDoubleArray*`[Double]'& -- ^fixedNominal
  ,withDoubleArray*`[Double]'& -- ^floatingNominal
  ,withSchedule*`Schedule' -- ^fixedSchedule
  ,withDoubleArray*`[Double]'& -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withSchedule*`Schedule' -- ^floatingSchedule
  ,withIborIndex*`GenIborIndex ibor'
  ,`Double' -- ^gearing
  ,`Double' -- ^spread
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,`Bool' -- ^intermediateCapitalExchange
  ,`Bool' -- ^finalCapitalExchange
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^paymentConvention
  ,preErrorCheck-`String'errorCheck*-}->`NonstandardSwap'peekNonstandardSwap*#}

-- |As 'nonstandardSwap', but with a per-period gearing and spread instead of one shared value.
{#fun qlNonstandardSwap2 as nonstandardSwap'{`SwapType'
  ,withDoubleArray*`[Double]'& -- ^fixedNominal
  ,withDoubleArray*`[Double]'& -- ^floatingNominal
  ,withSchedule*`Schedule' -- ^fixedSchedule
  ,withDoubleArray*`[Double]'& -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withSchedule*`Schedule' -- ^floatingSchedule
  ,withIborIndex*`GenIborIndex ibor'
  ,withDoubleArray*`[Double]'& -- ^gearing
  ,withDoubleArray*`[Double]'& -- ^spread
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,`Bool' -- ^intermediateCapitalExchange
  ,`Bool' -- ^finalCapitalExchange
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^paymentConvention
  ,preErrorCheck-`String'errorCheck*-}->`NonstandardSwap'peekNonstandardSwap*#}

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
  -> GenIborIndex ibor
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
    floatSchedule index 0.0 floatDayCount (Just floatConv) Nothing

-- |Haskell equivalent of QuantLib's fluent @MakeCms@ builder, in the style of
-- 'makeVanillaSwap' above -- not a binding of the @MakeCms@ C++ class at all, but a plain
-- function composing already-bound primitives ('QuantLib.Time.Schedule.schedule',
-- 'QuantLib.CashFlow.cmsLeg', 'QuantLib.CashFlow.iborLeg', 'swap''). The result is a plain
-- 'Swap' (a CMS swap has no calc\/getter of its own beyond generic 'Swap''s), with no
-- 'FloatingRateCouponPricer' attached -- attach one to the CMS leg afterwards via
-- @setCouponPricer =<< 'leg' result 0@ ('swap'' is used instead of 'swap' precisely so the
-- CMS leg is always leg 0, regardless of 'SwapType') and 'QuantLib.CashFlow.setCouponPricer'
-- before pricing.
--
-- Unlike @MakeCms@, @cmsLegTenor@\/@cmsLegDayCount@ are required arguments here rather than
-- defaulted (upstream hardcodes 3 Months\/@Actual360@); pass those literals to reproduce
-- @MakeCms@'s own defaults. Not covered at all (no parameter): an explicit effective date
-- override, CMS-leg\/floating-leg termination-date-convention\/rule\/end-of-month\/
-- first-date\/next-to-last-date overrides (always @ModifiedFollowing@\/@Backward@\/@False@\/
-- unset, matching @MakeCms@'s own defaults for the CMS leg), CMS coupon gearing\/caps\/floors
-- (use 'QuantLib.CashFlow.cmsLegFull' and 'swap' directly for those), an ATM-spread lookup, a
-- discounting term structure or custom pricing engine (use 'QuantLib.Instrument.setPricingEngine'
-- on the result instead). A 'Nothing' @settlementDays@ behaves as @Just 0@, rather than
-- replicating upstream's index-@valueDate@-based spot-date convention (matching
-- 'makeVanillaSwap''s own choice here).
makeCms
  :: (Word, TimeUnit)             -- ^swapTenor
  -> GenSwapIndex sidx            -- ^cms index
  -> GenIborIndex ibor            -- ^floating-leg index
  -> Double                       -- ^floating-leg spread
  -> (Int, TimeUnit)              -- ^forwardStart
  -> Maybe Int                    -- ^settlementDays
  -> (Word, TimeUnit)             -- ^cmsLegTenor
  -> DayCounter                   -- ^cmsLegDayCount
  -> Maybe Calendar               -- ^cmsLegCalendar
  -> Maybe Calendar               -- ^floatingLegCalendar
  -> Maybe Double                 -- ^nominal
  -> Maybe SwapType                -- ^'Payer' pays the CMS leg (receives floating); 'Receiver' the reverse
  -> IO Swap
makeCms (swLen, swUnit) swapIndex iborIndex iborSpread forwardStart mSettlementDays
    cmsTenor cmsDayCount mCmsCalendar mFloatCalendar mNominal mType = do
  idxCalendar <- fixingCalendar swapIndex
  floatTenor <- tenor iborIndex
  floatDayCount <- dayCounter iborIndex
  refDate <- evaluationDate
  let floatConv = businessDayConvention iborIndex
      floatCalendar = fromMaybe idxCalendar mFloatCalendar
      cmsCalendar = fromMaybe idxCalendar mCmsCalendar
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
  cmsSchedule <- schedule (Just swapStartDate) endDate cmsTenor cmsCalendar
    ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
  floatSchedule <- schedule (Just swapStartDate) endDate floatTenor floatCalendar
    floatConv floatConv Backward False Nothing Nothing
  cmsLegResult <- cmsLeg cmsSchedule swapIndex [nominal] cmsDayCount ModifiedFollowing
    [] [] [] [] [] False False
  floatLegResult <- iborLeg floatSchedule iborIndex [nominal] floatDayCount floatConv
    [] [] [iborSpread] [] [] False False
  -- 'swap'' (not 'swap') so the CMS leg is always leg 0 of the result regardless of
  -- 'SwapType' -- attach a pricer via @setCouponPricer =<< 'leg' result 0@ before pricing.
  swap' [(cmsLegResult, swapType == Payer), (floatLegResult, swapType == Receiver)]

-- |The cash flows belonging to the first leg are paid; the ones belonging to the second leg are received.
{#fun qlSwap as swap{withLeg*`GenLeg l1',withLeg*`GenLeg l2',preErrorCheck-`String'errorCheck*-}->`Swap'peekSwap*#}

-- |Discount factor at leg j's end date.
{#fun qlSwapEndDiscounts as endDiscounts{withSwap*`GenSwap s',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The j-th leg's cash flows.
{#fun qlSwapLeg as leg{withSwap*`GenSwap s',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of leg j.
{#fun qlSwapLegBPS as legBPS{withSwap*`GenSwap s',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of leg j.
{#fun qlSwapLegNPV as legNPV{withSwap*`GenSwap s',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Discount factor at leg j's start date.
{#fun qlSwapStartDiscounts as startDiscounts{withSwap*`GenSwap s',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |An option on a 'VanillaSwap'.
{#fun qlSwaption as swaption{withVanillaSwap*`VanillaSwap',withExercise*`Exercise',`SettlementType',`SettlementMethod',preErrorCheck-`String'errorCheck*-}->`Swaption'peekSwaption*#}

-- |Converts an existing 'Swaption' into a 'NonstandardSwaption' (upstream's own conversion
-- constructor).
{#fun qlNonstandardSwaption1 as nonstandardSwaptionFromSwaption{withSwaption*`Swaption'
  ,preErrorCheck-`String'errorCheck*-}->`NonstandardSwaption'peekNonstandardSwaption*#}

-- |An option on a 'NonstandardSwap'.
{#fun qlNonstandardSwaption as nonstandardSwaption{withNonstandardSwap*`NonstandardSwap',withExercise*`Exercise',`SettlementType',`SettlementMethod',preErrorCheck-`String'errorCheck*-}->`NonstandardSwaption'peekNonstandardSwaption*#}

-- |Auto-generates a basket of plain 'Swaption's used to calibrate a model to price a
-- 'NonstandardSwaption' -- either ATM swaptions adapted to the exercise dates ('Naive') or
-- swaptions whose maturity\/strike\/nominal match the underlying's NPV, delta and gamma at each
-- exercise date ('MaturityStrikeByDeltaGamma').
{#fun qlNonstandardSwaptionCalibrationBasket as calibrationBasket{withNonstandardSwaption*`NonstandardSwaption'
  ,withSwapIndex*`GenSwapIndex sidx' -- ^standardSwapBase
  ,withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv' -- ^swaptionVolatility
  ,fromEnumC`CalibrationBasketType'
  ,preArray-`[BlackCalibrationHelper]'&peekBlackCalibrationHelperArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- AssetSwap
-- |Bullet bond vs Libor swap (par or market asset swap, per /parAssetSwap/).
{#fun qlAssetSwap as assetSwap{`Bool' -- ^payBondCoupon
  ,withBond*`Bond',`Double' -- ^bondCleanPrice
  ,withIborIndex*`GenIborIndex ibor',`Double' -- spread
  ,withSchedule*`Schedule' -- ^floatSchedule
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,`Bool' -- ^parAssetSwap
  ,`Double' -- ^gearing
  ,fromMaybeDouble`Maybe Double' -- ^nonParRepayment
  ,withMaybeDay*`Maybe Day' -- ^dealMaturity
  ,preErrorCheck-`String'errorCheck*-}->`AssetSwap'peekAssetSwap*#}
-- OvernightIndexedSwap
-- |Fixed vs compounded-overnight-rate swap, with a single flat nominal for both legs.
{#fun qlOvernightIndexedSwap as overnightIndexedSwap{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule',`Double'  -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDC
  ,withOvernightIborIndex*`OvernightIborIndex',`Double' -- ^spread
  ,fromIntegral`Int' -- ^paymentLag
  ,fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,`Bool' -- ^telescopicValueDates
  ,`RateAveragingType' -- ^averagingMethod
  ,fromMaybeInt`Maybe Word' -- ^lookbackDays
  ,fromIntegral`Word' -- ^lockoutDays
  ,`Bool' -- ^applyObservationShift
  ,preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}

-- |As 'overnightIndexedSwap', but with a per-period nominal schedule instead of a single flat nominal.
{#fun qlOvernightIndexedSwap1 as overnightIndexedSwap'{`SwapType',withDoubleArray*`[Double]'& -- ^nominals
  ,withSchedule*`Schedule' -- ^schedule
  ,`Double' -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDC
  ,withOvernightIborIndex*`OvernightIborIndex',`Double' -- ^spread
  ,fromIntegral`Int' -- ^paymentLag
  ,fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,`Bool' -- ^telescopicValueDates
  ,`RateAveragingType' -- ^averagingMethod
  ,fromMaybeInt`Maybe Word' -- ^lookbackDays
  ,fromIntegral`Word' -- ^lockoutDays
  ,`Bool' -- ^applyObservationShift
  ,preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}

-- |The swap's maturity date, or 'Nothing' if the swap has no legs.
{#fun qlSwapMaturityDate as maturityDate{withSwap*`GenSwap s',preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}

-- |The swap's start date, or 'Nothing' if the swap has no legs.
{#fun qlSwapStartDate as startDate{withSwap*`GenSwap s',preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}

-- |Discount factor at the instrument's NPV date.
{#fun qlSwapNpvDateDiscount as npvDateDiscount{withSwap*`GenSwap s',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The BMA leg's cash flows.
{#fun qlBMASwapBmaLeg as bmaLeg{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the BMA leg.
{#fun qlBMASwapBmaLegBPS as bmaLegBPS{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the BMA leg.
{#fun qlBMASwapBmaLegNPV as bmaLegNPV{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The Libor fraction that would make the swap's NPV zero.
{#fun qlBMASwapFairLiborFraction as fairLiborFraction{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The Libor spread that would make the swap's NPV zero.
{#fun qlBMASwapFairLiborSpread as fairLiborSpread{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The fraction of the Libor rate paid on the Libor leg.
{#fun qlBMASwapLiborFraction as liborFraction{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The Libor leg's cash flows.
{#fun qlBMASwapLiborLeg as liborLeg{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the Libor leg.
{#fun qlBMASwapLiborLegBPS as liborLegBPS{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the Libor leg.
{#fun qlBMASwapLiborLegNPV as liborLegNPV{withBMASwap*`BMASwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The underlying bond's cash flows.
{#fun qlAssetSwapBondLeg as bondLeg{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |The bond's clean price, as passed to the constructor.
{#fun qlAssetSwapCleanPrice as cleanPrice{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The clean price that would make the swap's NPV zero.
{#fun qlAssetSwapFairCleanPrice as fairCleanPrice{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The non-par repayment that would make the swap's NPV zero.
{#fun qlAssetSwapFairNonParRepayment as fairNonParRepayment{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The non-par repayment, as passed to the constructor.
{#fun qlAssetSwapNonParRepayment as nonParRepayment{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Whether this is a par asset swap.
{#fun qlAssetSwapParSwap as parSwap{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Whether the bond coupon is paid (rather than netted against the floating leg).
{#fun qlAssetSwapPayBondCoupon as payBondCoupon{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |The overnight leg's cash flows.
{#fun qlOvernightIndexedSwapOvernightLeg as overnightLeg{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the overnight leg.
{#fun qlOvernightIndexedSwapOvernightLegBPS as overnightLegBPS{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the overnight leg.
{#fun qlOvernightIndexedSwapOvernightLegNPV as overnightLegNPV{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- Inflation-linked swaps
-- |A zero-coupon inflation-indexed swap (ZCIIS): a single fixed-vs-CPI-ratio exchange at
-- maturity. Per-leg NPV\/BPS use the generic 'leg'\/'legNPV'\/'legBPS' (leg 0 = fixed, leg 1 =
-- inflation).
{#fun qlZeroCouponInflationSwap as zeroCouponInflationSwap{`SwapType',`Double' -- ^nominal
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^fixedRate
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`Bool' -- ^adjustInfObsDates
  ,withCalendar*`Calendar' -- ^infCalendar
  ,fromEnumC`BusinessDayConvention' -- ^infConvention
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwap'peekZeroCouponInflationSwap*#}

-- |The fixed rate that would make the swap's NPV zero.
{#fun qlZeroCouponInflationSwapFairRate as zcisFairRate{withZeroCouponInflationSwap*`ZeroCouponInflationSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A year-on-year inflation-indexed swap: fixed leg vs a YoY-inflation-linked leg. Per-leg
-- NPV\/BPS use the generic 'leg'\/'legNPV'\/'legBPS' (leg 0 = fixed, leg 1 = YoY).
{#fun qlYearOnYearInflationSwap as yearOnYearInflationSwap{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule' -- ^fixedSchedule
  ,`Double' -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withSchedule*`Schedule' -- ^yoySchedule
  ,withYoYInflationIndex*`YoYInflationIndex'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,fromEnumC`CPIInterpolationType' -- ^interpolation
  ,`Double' -- ^spread
  ,withDayCounter*`DayCounter' -- ^yoyDayCount
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,preErrorCheck-`String'errorCheck*-}->`YearOnYearInflationSwap'peekYearOnYearInflationSwap*#}

-- |The fixed rate that would make the swap's NPV zero.
{#fun qlYearOnYearInflationSwapFairRate as yoyFairRate{withYearOnYearInflationSwap*`YearOnYearInflationSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The spread that would make the swap's NPV zero.
{#fun qlYearOnYearInflationSwapFairSpread{withYearOnYearInflationSwap*`YearOnYearInflationSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A fixed-x-CPI-ratio leg (subtracting the inflation notional if
-- /subtractInflationNominal/) vs a float+spread leg -- QuantLib's general-purpose inflation
-- swap, also usable to replicate a single-cashflow ZCIIS (see 'zeroCouponInflationSwap').
-- Per-leg NPV\/BPS use the generic 'leg'\/'legNPV'\/'legBPS' (leg 0 = CPI, leg 1 = float).
{#fun qlCPISwap as cpiSwap{`SwapType',`Double' -- ^nominal
  ,`Bool' -- ^subtractInflationNominal
  ,`Double' -- ^spread
  ,withDayCounter*`DayCounter' -- ^floatDayCount
  ,withSchedule*`Schedule' -- ^floatSchedule
  ,fromEnumC`BusinessDayConvention' -- ^floatRoll
  ,fromIntegral`Word' -- ^fixingDays
  ,withIborIndex*`GenIborIndex ibor' -- ^floatIndex
  ,`Double' -- ^fixedRate
  ,`Double' -- ^baseCPI
  ,withDayCounter*`DayCounter' -- ^fixedDayCount
  ,withSchedule*`Schedule' -- ^fixedSchedule
  ,fromEnumC`BusinessDayConvention' -- ^fixedRoll
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withZeroInflationIndex*`ZeroInflationIndex' -- ^fixedIndex
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,fromMaybeDouble`Maybe Double' -- ^inflationNominal
  ,preErrorCheck-`String'errorCheck*-}->`CPISwap'peekCPISwap*#}

-- |The fixed rate that would make the swap's NPV zero.
{#fun qlCPISwapFairRate as cpiSwapFairRate{withCPISwap*`CPISwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The spread that would make the swap's NPV zero.
{#fun qlCPISwapFairSpread{withCPISwap*`CPISwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Zero-coupon swap quoted in terms of a known fixed cash flow. \"payer\"\/\"receiver\" refer to the fixed leg.
{#fun qlZeroCouponSwap as zeroCouponSwap{`SwapType',`Double' -- ^baseNominal
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^maturityDate
  ,`Double' -- ^fixedPayment
  ,withIborIndex*`GenIborIndex ibor',withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^paymentDelay
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponSwap'peekZeroCouponSwap*#}

-- |Zero-coupon swap quoted in terms of a fixed rate.
{#fun qlZeroCouponSwap1 as zeroCouponSwap'{`SwapType',`Double' -- ^baseNominal
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^maturityDate
  ,`Double' -- ^fixedRate
  ,withDayCounter*`DayCounter' -- ^fixedDayCounter
  ,withIborIndex*`GenIborIndex ibor',withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^paymentDelay
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponSwap'peekZeroCouponSwap*#}

-- |The fixed payment that would make the swap's NPV zero.
{#fun qlZeroCouponSwapFairFixedPayment as fairFixedPayment{withZeroCouponSwap*`ZeroCouponSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The fixed rate, under the given day counter, that would make the swap's NPV zero.
{#fun qlZeroCouponSwapFairFixedRate as fairFixedRate{withZeroCouponSwap*`ZeroCouponSwap',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Exchanges the total return of an 'EquityIndex' for a set of floating cash flows linked to an
-- 'IborIndex'. /type/ (payer\/receiver) refers to the equity leg.
{#fun qlEquityTotalReturnSwapIbor as equityTotalReturnSwapIbor{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule'
  ,withEquityIndex*`EquityIndex'
  ,withIborIndex*`GenIborIndex ibor' -- ^interestRateIndex
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^margin
  ,`Double' -- ^gearing
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^paymentDelay
  ,preErrorCheck-`String'errorCheck*-}->`EquityTotalReturnSwap'peekEquityTotalReturnSwap*#}

-- |As 'equityTotalReturnSwapIbor', but with the floating leg linked to an overnight index instead
-- -- fixings are compounded over the accrual period.
{#fun qlEquityTotalReturnSwapOvernight as equityTotalReturnSwapOvernight{`SwapType',`Double' -- ^nominal
  ,withSchedule*`Schedule'
  ,withEquityIndex*`EquityIndex'
  ,withOvernightIborIndex*`OvernightIborIndex' -- ^interestRateIndex
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^margin
  ,`Double' -- ^gearing
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^paymentDelay
  ,preErrorCheck-`String'errorCheck*-}->`EquityTotalReturnSwap'peekEquityTotalReturnSwap*#}

-- |NPV of the equity total-return leg.
{#fun qlEquityTotalReturnSwapEquityLegNPV as equityLegNPV{withEquityTotalReturnSwap*`EquityTotalReturnSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the interest-rate leg.
{#fun qlEquityTotalReturnSwapInterestRateLegNPV as interestRateLegNPV{withEquityTotalReturnSwap*`EquityTotalReturnSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The margin that would make the swap's NPV zero.
{#fun qlEquityTotalReturnSwapFairMargin as fairMargin{withEquityTotalReturnSwap*`EquityTotalReturnSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

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
instance HasFixedLeg (GenFixedVsFloatingSwap f) where
  fairRate = qlFixedVsFloatingSwapFairRate
  fixedLeg = qlFixedVsFloatingSwapFixedLeg
  fixedLegBPS = qlFixedVsFloatingSwapFixedLegBPS
  fixedLegNPV = qlFixedVsFloatingSwapFixedLegNPV

class HasSpread a where
  fairSpread :: a -> IO Double
instance HasSpread (GenFixedVsFloatingSwap f) where
  fairSpread = qlFixedVsFloatingSwapFairSpread
instance HasSpread OvernightIndexedSwap where
  fairSpread = qlOvernightIndexedSwapFairSpread
instance HasSpread AssetSwap where
  fairSpread = qlAssetSwapFairSpread
instance HasSpread CreditDefaultSwap where
  fairSpread = qlCreditDefaultSwapFairSpread
instance HasSpread YearOnYearInflationSwap where
  fairSpread = qlYearOnYearInflationSwapFairSpread
instance HasSpread CPISwap where
  fairSpread = qlCPISwapFairSpread

class HasFloatingLeg a where
  floatingLeg :: a -> IO Leg
  floatingLegBPS :: a -> IO Double
  floatingLegNPV :: a -> IO Double
instance HasFloatingLeg (GenFixedVsFloatingSwap f) where
  floatingLeg = qlFixedVsFloatingSwapFloatingLeg
  floatingLegBPS = qlFixedVsFloatingSwapFloatingLegBPS
  floatingLegNPV = qlFixedVsFloatingSwapFloatingLegNPV
instance HasFloatingLeg AssetSwap where
  floatingLeg = qlAssetSwapFloatingLeg
  floatingLegBPS = qlAssetSwapFloatingLegBPS
  floatingLegNPV = qlAssetSwapFloatingLegNPV

-- |The spread that would make the swap's NPV zero.
{#fun qlFixedVsFloatingSwapFairSpread{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The spread that would make the swap's NPV zero.
{#fun qlAssetSwapFairSpread{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The fixed rate that would make the swap's NPV zero.
{#fun qlFixedVsFloatingSwapFairRate{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The fixed leg's cash flows.
{#fun qlFixedVsFloatingSwapFixedLeg{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the fixed leg.
{#fun qlFixedVsFloatingSwapFixedLegBPS{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the fixed leg.
{#fun qlFixedVsFloatingSwapFixedLegNPV{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The fixed rate that would make the swap's NPV zero.
{#fun qlOvernightIndexedSwapFairRate{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The fixed leg's cash flows.
{#fun qlOvernightIndexedSwapFixedLeg{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the fixed leg.
{#fun qlOvernightIndexedSwapFixedLegBPS{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the fixed leg.
{#fun qlOvernightIndexedSwapFixedLegNPV{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The spread that would make the swap's NPV zero.
{#fun qlOvernightIndexedSwapFairSpread{withOvernightIndexedSwap*`OvernightIndexedSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the running spread that, given the quoted recovery rate, will make the running-only CDS have an NPV of 0.This calculation does not take any upfront into account, even if one was given.
{#fun qlCreditDefaultSwapFairSpread{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The floating leg's cash flows.
{#fun qlFixedVsFloatingSwapFloatingLeg{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the floating leg.
{#fun qlFixedVsFloatingSwapFloatingLegBPS{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the floating leg.
{#fun qlFixedVsFloatingSwapFloatingLegNPV{withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The floating leg's cash flows.
{#fun qlAssetSwapFloatingLeg{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Basis-point sensitivity of the floating leg.
{#fun qlAssetSwapFloatingLegBPS{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the floating leg.
{#fun qlAssetSwapFloatingLegNPV{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#pointer *QlVarianceSwap as VarianceSwap foreign -> CVarianceSwap' nocode#}

-- |Variance swap: pays off the difference between realized and strike variance, scaled by notional. This class does not manage seasoned variance swaps.
{#fun qlVarianceSwap as varianceSwap{fromEnumC`PositionType',`Double' -- ^strike
  ,`Double' -- ^notional
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^maturityDate
  ,preErrorCheck-`String'errorCheck*-}->`VarianceSwap'peekVarianceSwap*#}

-- |Realized variance -- requires a pricing engine to be set first
{#fun qlVarianceSwapVariance as variance{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#pointer *QlPayoff nocode#}
{#pointer *QlVarianceOption as VarianceOption foreign -> CVarianceOption' nocode#}

-- |Variance option: an option on realized variance, priced (e.g. via 'integralHestonVarianceOptionEngine')
-- against a payoff on the variance level rather than the underlying price. This class does not
-- manage seasoned variance options.
{#fun qlVarianceOption as varianceOption{withPayoff*`Payoff'
  ,`Double' -- ^notional
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^maturityDate
  ,preErrorCheck-`String'errorCheck*-}->`VarianceOption'peekVarianceOption*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
