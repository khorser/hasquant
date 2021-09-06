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
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Index.InterestRate#}(IborIndex, BMAIndex, OvernightIborIndex)
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Index
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
{#import QuantLib.Instrument.Bond#}(Bond)
{#import QuantLib.Instrument.Option#}(Option)
{#import QuantLib.Instrument.Credit#}(CreditDefaultSwap)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum SwapType{} deriving(Show, Eq)#}

{#pointer *Leg foreign -> CLeg nocode#}

{#pointer *QlSwaption as Swaption foreign finalizer qlFreeSwaption newtype#}
instance ForeignObject Swaption where
  withObject = withSwaption
  constructor = Swaption
  finalizer = qlFreeSwaption
{#fun qlSwaptionAsOption{`Swaption'}->`Option'peekObject*#}
instance Swaption`Derives` Option where cast = qlSwaptionAsOption

{#pointer *QlSwap as Swap foreign finalizer qlFreeSwap newtype#}
instance ForeignObject Swap where
  withObject = withSwap
  constructor = Swap
  finalizer = qlFreeSwap
{#fun qlSwapAsInstrument{`Swap'}->`Instrument'peekObject*#}
instance Swap`Derives` Instrument where cast = qlSwapAsInstrument

asSwap:: (a`Derives` Swap) => a -> IO Swap
asSwap = cast

{#pointer *QlVanillaSwap as VanillaSwap foreign finalizer qlFreeVanillaSwap newtype#}
instance ForeignObject VanillaSwap where
  withObject = withVanillaSwap
  constructor = VanillaSwap
  finalizer = qlFreeVanillaSwap
{#fun qlVanillaSwapAsSwap{`VanillaSwap'}->`Swap'#}
instance VanillaSwap`Derives` Swap where cast = qlVanillaSwapAsSwap

{#pointer *QlAssetSwap as AssetSwap foreign finalizer qlFreeAssetSwap newtype#}
instance ForeignObject AssetSwap where
  withObject = withAssetSwap
  constructor = AssetSwap
  finalizer = qlFreeAssetSwap
{#fun qlAssetSwapAsSwap{`AssetSwap'}->`Swap'#}
instance AssetSwap`Derives` Swap where cast = qlAssetSwapAsSwap

{#pointer *QlBMASwap as BMASwap foreign finalizer qlFreeBMASwap newtype#}
instance ForeignObject BMASwap where
  withObject = withBMASwap
  constructor = BMASwap
  finalizer = qlFreeBMASwap
{#fun qlBMASwapAsSwap{`BMASwap'}->`Swap'#}
instance BMASwap`Derives` Swap where cast = qlBMASwapAsSwap

{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign finalizer qlFreeOvernightIndexedSwap newtype#}
instance ForeignObject OvernightIndexedSwap where
  withObject = withOvernightIndexedSwap
  constructor = OvernightIndexedSwap
  finalizer = qlFreeOvernightIndexedSwap
{#fun qlOvernightIndexedSwapAsSwap{`OvernightIndexedSwap'}->`Swap'#}
instance OvernightIndexedSwap`Derives` Swap where cast = qlOvernightIndexedSwapAsSwap

-- |implied volatility
{#fun qlSwaptionImpliedVolatility as impliedVolatility{`Swaption',`Double',`YieldTermStructure',`Double',`Double', fromIntegral`Word',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Multi leg constructor.
swap' :: [(Leg, Bool)] -- ^(legs, payer)
  -> IO Swap
swap' = (uncurry qlSwap1) . unzip
{#fun qlSwap1{withLegArray*`[Leg]'&, withBoolArray*`[Bool]'&, preErrorCheck-`String'errorCheck*-}->`Swap'#}

{#fun qlBMASwap as bmaSwap{`SwapType',`Double', withSchedule*`Schedule',`Double',`Double',`IborIndex', withDayCounter*`DayCounter', withSchedule*`Schedule',`BMAIndex', withDayCounter*`DayCounter', preErrorCheck-`String'errorCheck*-}->`BMASwap'#}

{#fun qlVanillaSwap as vanillaSwap{`SwapType',`Double', withSchedule*`Schedule',`Double', withDayCounter*`DayCounter', withSchedule*`Schedule',`IborIndex',`Double', withDayCounter*`DayCounter',`BusinessDayConvention', preErrorCheck-`String'errorCheck*-}->`VanillaSwap'#}

-- |The cash flows belonging to the first leg are paid; the ones belonging to the second leg are received.
{#fun qlSwap as swap{withLeg*`GenLeg a', withLeg*`GenLeg a', preErrorCheck-`String'errorCheck*-}->`Swap'#}

{#fun qlSwapEndDiscounts as endDiscounts{`Swap', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlSwapLeg as leg{`Swap', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlSwapLegBPS as legBPS{`Swap', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlSwapLegNPV as legNPV{`Swap', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlSwapStartDiscounts as startDiscounts{`Swap', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlSwaption as swaption{`VanillaSwap', withEnumObject*`Exercise',`SettlementType', preErrorCheck-`String'errorCheck*-}->`Swaption'#}

-- AssetSwap
{#fun qlAssetSwap1 as assetSwap'{`Bool', withObject*`Bond',`Double',`Double',`Double',`IborIndex',`Double', withDayCounter*`DayCounter', withMaybeDay*`Maybe Day',`Bool', preErrorCheck-`String'errorCheck*-}->`AssetSwap'#}

{#fun qlAssetSwap as assetSwap{`Bool', withObject*`Bond',`Double',`IborIndex',`Double', withSchedule*`Schedule', withDayCounter*`DayCounter',`Bool', preErrorCheck-`String'errorCheck*-}->`AssetSwap'#}

-- OvernightIndexedSwap
{#fun qlOvernightIndexedSwap as overnightIndexedSwap{`SwapType',`Double', withSchedule*`Schedule',`Double', withDayCounter*`DayCounter',`OvernightIborIndex',`Double', preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'#}

{#fun qlOvernightIndexedSwap1 as overnightIndexedSwap'{`SwapType', withDoubleArray*`[Double]'&, withSchedule*`Schedule',`Double', withDayCounter*`DayCounter',`OvernightIborIndex',`Double', preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'#}

{#fun qlSwapMaturityDate as maturityDate{`Swap', preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}

{#fun qlSwapStartDate as startDate{`Swap', preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}

{#fun qlSwapNpvDateDiscount as npvDateDiscount{`Swap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapBmaLeg as bmaLeg{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlBMASwapBmaLegBPS as bmaLegBPS{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapBmaLegNPV as bmaLegNPV{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapFairLiborFraction as fairLiborFraction{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapFairLiborSpread as fairLiborSpread{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapLiborFraction as liborFraction{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapLiborLeg as liborLeg{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlBMASwapLiborLegBPS as liborLegBPS{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBMASwapLiborLegNPV as liborLegNPV{`BMASwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlAssetSwapBondLeg as bondLeg{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlAssetSwapCleanPrice as cleanPrice{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlAssetSwapFairCleanPrice as fairCleanPrice{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlAssetSwapFairNonParRepayment as fairNonParRepayment{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlAssetSwapNonParRepayment as nonParRepayment{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlAssetSwapParSwap as parSwap{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Bool'#}

{#fun qlAssetSwapPayBondCoupon as payBondCoupon{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Bool'#}

{#fun qlOvernightIndexedSwapOvernightLeg as overnightLeg{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlOvernightIndexedSwapOvernightLegBPS as overnightLegBPS{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlOvernightIndexedSwapOvernightLegNPV as overnightLegNPV{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

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

{#fun qlVanillaSwapFairSpread{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFairSpread{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFairRate{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFixedLeg{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlVanillaSwapFixedLegBPS{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFixedLegNPV{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFairRate{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFixedLeg{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlOvernightIndexedSwapFixedLegBPS{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFixedLegNPV{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOvernightIndexedSwapFairSpread{`OvernightIndexedSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Returns the running spread that, given the quoted recovery rate, will make the running-only CDS have an NPV of 0.This calculation does not take any upfront into account, even if one was given.
{#fun qlCreditDefaultSwapFairSpread{withObject*`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFloatingLeg{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlVanillaSwapFloatingLegBPS{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVanillaSwapFloatingLegNPV{`VanillaSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFloatingLeg{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlAssetSwapFloatingLegBPS{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAssetSwapFloatingLegNPV{`AssetSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
