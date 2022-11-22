{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
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
  , assetSwap'

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
  )
  where

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
{#import QuantLib.Instrument.Bond#}(Bond)
{#import QuantLib.Instrument.Option#}(Option)
{#import QuantLib.Instrument.Credit#}(CreditDefaultSwap)

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex' nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex' nocode#}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum SwapType{} deriving(Show, Eq)#}

{#pointer *Leg foreign -> CLeg nocode#}

{#pointer *QlSwaption as Swaption foreign -> CSwaption nocode#}

{#fun qlSwaptionAsOption{withSwaption*`Swaption'}->`Option'peekOption*#}
instance Swaption`Derives` Option where cast = qlSwaptionAsOption

{#pointer *QlSwap as Swap foreign -> CSwap nocode#}

{#fun qlSwapAsInstrument{withSwap*`Swap'}->`Instrument'peekInstrument*#}
instance Swap`Derives` Instrument where cast = qlSwapAsInstrument

asSwap:: (a`Derives` Swap) => a -> IO Swap
asSwap = cast

{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap nocode#}

{#fun qlVanillaSwapAsSwap{withVanillaSwap*`VanillaSwap'}->`Swap'peekSwap*#}
instance VanillaSwap`Derives` Swap where cast = qlVanillaSwapAsSwap

{#pointer *QlAssetSwap as AssetSwap foreign -> CAssetSwap nocode#}

{#fun qlAssetSwapAsSwap{withAssetSwap*`AssetSwap'}->`Swap'peekSwap*#}
instance AssetSwap`Derives` Swap where cast = qlAssetSwapAsSwap

{#pointer *QlBMASwap as BMASwap foreign -> CBMASwap nocode#}

{#fun qlBMASwapAsSwap{withBMASwap*`BMASwap'}->`Swap'peekSwap*#}
instance BMASwap`Derives` Swap where cast = qlBMASwapAsSwap

{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap nocode#}

{#fun qlOvernightIndexedSwapAsSwap{withOvernightIndexedSwap*`OvernightIndexedSwap'}->`Swap'peekSwap*#}
instance OvernightIndexedSwap`Derives` Swap where cast = qlOvernightIndexedSwapAsSwap

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

-- |The cash flows belonging to the first leg are paid; the ones belonging to the second leg are received.
{#fun qlSwap as swap{withLeg*`GenLeg a',withLeg*`GenLeg a',preErrorCheck-`String'errorCheck*-}->`Swap'peekSwap*#}
{#fun qlSwapEndDiscounts as endDiscounts{withSwap*`Swap',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapLeg as leg{withSwap*`Swap',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlSwapLegBPS as legBPS{withSwap*`Swap',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapLegNPV as legNPV{withSwap*`Swap',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwapStartDiscounts as startDiscounts{withSwap*`Swap',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSwaption as swaption{withVanillaSwap*`VanillaSwap',withExercise*`Exercise',`SettlementType',preErrorCheck-`String'errorCheck*-}->`Swaption'peekSwaption*#}

-- AssetSwap
{#fun qlAssetSwap1 as assetSwap'{`Bool' -- ^parAssetSwap
  ,withBond*`Bond',`Double' -- ^bondCleanPrice
  ,`Double' -- ^nonParRepayment
  ,`Double' -- ^gearing
  ,withIborIndex*`GenIborIndex a',`Double' -- ^spread
  ,withDayCounter*`DayCounter' -- ^floatingDayCount
  ,withMaybeDay*`Maybe Day' -- ^dealMaturity
  ,`Bool' -- ^payBondCoupon
  ,preErrorCheck-`String'errorCheck*-}->`AssetSwap'peekAssetSwap*#}
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
{#fun qlSwapMaturityDate as maturityDate{withSwap*`Swap',preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}
{#fun qlSwapStartDate as startDate{withSwap*`Swap',preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}
{#fun qlSwapNpvDateDiscount as npvDateDiscount{withSwap*`Swap',preErrorCheck-`String'errorCheck*-}->`Double'#}
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
{#fun qlCreditDefaultSwapFairSpread{withCreditDefaultSwap*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFloatingLeg{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlVanillaSwapFloatingLegBPS{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFloatingLegNPV{withVanillaSwap*`VanillaSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFloatingLeg{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlAssetSwapFloatingLegBPS{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFloatingLegNPV{withAssetSwap*`AssetSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
