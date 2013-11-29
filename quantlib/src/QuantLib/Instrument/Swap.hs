{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Swap
  (
    swap'
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

  , impliedVolatility
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
  )

where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Date
import QuantLib.SettlementType(SettlementType)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Types
import QuantLib.Instrument.BMASwapType(BMASwapType)
import QuantLib.Instrument.VanillaSwapType(VanillaSwapType)
import QuantLib.Instrument.OvernightIndexedSwapType(OvernightIndexedSwapType)

-- |Multi leg constructor.
swap' :: [(Leg, Bool)] -- ^(legs, payer)
  -> IO Swap
swap' = $(ffiCall 'swap') c_swap'

foreign import ccall safe "ql.h qlSwap1"
  c_swap' :: CUInt -> Ptr (Ptr CLeg) -> Ptr CInt -> Ptr CString -> IO (Ptr CSwap)

bmaSwap :: BMASwapType -- ^type
  -> Double -- ^nominal
  -> Schedule -- ^liborSchedule
  -> Double -- ^liborFraction
  -> Double -- ^liborSpread
  -> IborIndex -- ^liborIndex
  -> DayCounter -- ^liborDayCount
  -> Schedule -- ^bmaSchedule
  -> BMAIndex -- ^bmaIndex
  -> DayCounter -- ^bmaDayCount
  -> IO BMASwap
bmaSwap = $(ffiCall 'bmaSwap) c_bmaSwap

foreign import ccall safe "ql.h qlBMASwap"
  c_bmaSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> CDouble -> Ptr CIborIndex -> Ptr CDayCounter -> Ptr CSchedule -> Ptr CBMAIndex -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CBMASwap)

vanillaSwap :: VanillaSwapType -- ^type
  -> Double -- ^nominal
  -> Schedule -- ^fixedSchedule
  -> Double -- ^fixedRate
  -> DayCounter -- ^fixedDayCount
  -> Schedule -- ^floatSchedule
  -> IborIndex -- ^iborIndex
  -> Double -- ^spread
  -> DayCounter -- ^floatingDayCount
  -> BusinessDayConvention -- ^paymentConvention
  -> IO VanillaSwap
vanillaSwap = $(ffiCall 'vanillaSwap) c_vanillaSwap

foreign import ccall safe "ql.h qlVanillaSwap"
  c_vanillaSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr CSchedule -> Ptr CIborIndex -> CDouble -> Ptr CDayCounter -> CInt -> Ptr CString -> IO (Ptr CVanillaSwap)

-- |The cash flows belonging to the first leg are paid; the ones belonging to the second leg are received.
swap :: Leg -- ^firstLeg
  -> Leg -- ^secondLeg
  -> IO Swap
swap = $(ffiCall 'swap) c_swap

foreign import ccall safe "ql.h qlSwap"
  c_swap :: Ptr CLeg -> Ptr CLeg -> Ptr CString -> IO (Ptr CSwap)

endDiscounts :: Swap
  -> Word -- ^j
  -> IO Double
endDiscounts = $(ffiCallX 'endDiscounts) c_endDiscounts

foreign import ccall safe "ql.h qlSwapEndDiscounts"
  c_endDiscounts :: Ptr CSwap -> CUInt -> Ptr CString -> IO CDouble

leg :: Swap
  -> Word -- ^j
  -> IO Leg
leg = $(ffiCall 'leg) c_leg

foreign import ccall safe "ql.h qlSwapLeg"
  c_leg :: Ptr CSwap -> CUInt -> Ptr CString -> IO (Ptr CLeg)

legBPS :: Swap
  -> Word -- ^j
  -> IO Double
legBPS = $(ffiCallX 'legBPS) c_legBPS

foreign import ccall safe "ql.h qlSwapLegBPS"
  c_legBPS :: Ptr CSwap -> CUInt -> Ptr CString -> IO CDouble

legNPV :: Swap
  -> Word -- ^j
  -> IO Double
legNPV = $(ffiCallX 'legNPV) c_legNPV

foreign import ccall safe "ql.h qlSwapLegNPV"
  c_legNPV :: Ptr CSwap -> CUInt -> Ptr CString -> IO CDouble

maturityDate :: Swap -> Either QLError (Maybe Day)
maturityDate = $(ffiCallPureX 'maturityDate) c_maturityDate

foreign import ccall safe "ql.h qlSwapMaturityDate"
  c_maturityDate :: Ptr CSwap -> Ptr CString -> IO CDate

npvDateDiscount :: Swap -> IO Double
npvDateDiscount = $(ffiCallX 'npvDateDiscount) c_npvDateDiscount

foreign import ccall safe "ql.h qlSwapNpvDateDiscount"
  c_npvDateDiscount :: Ptr CSwap -> Ptr CString -> IO CDouble

startDate :: Swap -> Either QLError (Maybe Day)
startDate = $(ffiCallPureX 'startDate) c_startDate

foreign import ccall safe "ql.h qlSwapStartDate"
  c_startDate :: Ptr CSwap -> Ptr CString -> IO CDate

startDiscounts :: Swap
  -> Word -- ^j
  -> IO Double
startDiscounts = $(ffiCallX 'startDiscounts) c_startDiscounts

foreign import ccall safe "ql.h qlSwapStartDiscounts"
  c_startDiscounts :: Ptr CSwap -> CUInt -> Ptr CString -> IO CDouble

bmaLeg :: BMASwap -> IO Leg
bmaLeg = $(ffiCall 'bmaLeg) c_bmaLeg

foreign import ccall safe "ql.h qlBMASwapBmaLeg"
  c_bmaLeg :: Ptr CBMASwap -> Ptr CString -> IO (Ptr CLeg)

bmaLegBPS :: BMASwap -> IO Double
bmaLegBPS = $(ffiCallX 'bmaLegBPS) c_bmaLegBPS

foreign import ccall safe "ql.h qlBMASwapBmaLegBPS"
  c_bmaLegBPS :: Ptr CBMASwap -> Ptr CString -> IO CDouble

bmaLegNPV :: BMASwap -> IO Double
bmaLegNPV = $(ffiCallX 'bmaLegNPV) c_bmaLegNPV

foreign import ccall safe "ql.h qlBMASwapBmaLegNPV"
  c_bmaLegNPV :: Ptr CBMASwap -> Ptr CString -> IO CDouble

fairLiborFraction :: BMASwap -> IO Double
fairLiborFraction = $(ffiCallX 'fairLiborFraction) c_fairLiborFraction

foreign import ccall safe "ql.h qlBMASwapFairLiborFraction"
  c_fairLiborFraction :: Ptr CBMASwap -> Ptr CString -> IO CDouble

fairLiborSpread :: BMASwap -> IO Double
fairLiborSpread = $(ffiCallX 'fairLiborSpread) c_fairLiborSpread

foreign import ccall safe "ql.h qlBMASwapFairLiborSpread"
  c_fairLiborSpread :: Ptr CBMASwap -> Ptr CString -> IO CDouble

liborFraction :: BMASwap -> IO Double
liborFraction = $(ffiCallX 'liborFraction) c_liborFraction

foreign import ccall safe "ql.h qlBMASwapLiborFraction"
  c_liborFraction :: Ptr CBMASwap -> Ptr CString -> IO CDouble

liborLeg :: BMASwap -> IO Leg
liborLeg = $(ffiCall 'liborLeg) c_liborLeg

foreign import ccall safe "ql.h qlBMASwapLiborLeg"
  c_liborLeg :: Ptr CBMASwap -> Ptr CString -> IO (Ptr CLeg)

liborLegBPS :: BMASwap -> IO Double
liborLegBPS = $(ffiCallX 'liborLegBPS) c_liborLegBPS

foreign import ccall safe "ql.h qlBMASwapLiborLegBPS"
  c_liborLegBPS :: Ptr CBMASwap -> Ptr CString -> IO CDouble

liborLegNPV :: BMASwap -> IO Double
liborLegNPV = $(ffiCallX 'liborLegNPV) c_liborLegNPV

foreign import ccall safe "ql.h qlBMASwapLiborLegNPV"
  c_liborLegNPV :: Ptr CBMASwap -> Ptr CString -> IO CDouble

-- |implied volatility
impliedVolatility :: Swaption
  -> Double -- ^price
  -> YieldTermStructure -- ^discountCurve
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> IO Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

foreign import ccall safe "ql.h qlSwaptionImpliedVolatility"
  c_impliedVolatility :: Ptr CSwaption -> CDouble -> Ptr CYieldTermStructure -> CDouble -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

swaption :: VanillaSwap -- ^swap
  -> Exercise -- ^exercise
  -> SettlementType -- ^delivery
  -> IO Swaption
swaption = $(ffiCall 'swaption) c_swaption

foreign import ccall safe "ql.h qlSwaption"
  c_swaption :: Ptr CVanillaSwap -> Ptr CExercise -> CInt -> Ptr CString -> IO (Ptr CSwaption)

-- AssetSwap
assetSwap' :: Bool -- ^parAssetSwap
  -> Bond -- ^bond
  -> Double -- ^bondCleanPrice
  -> Double -- ^nonParRepayment
  -> Double -- ^gearing
  -> IborIndex -- ^iborIndex
  -> Double -- ^spread
  -> DayCounter -- ^floatingDayCount
  -> Maybe Day -- ^dealMaturity
  -> Bool -- ^payBondCoupon
  -> IO AssetSwap
assetSwap' = $(ffiCall 'assetSwap') c_assetSwap'

foreign import ccall safe "ql.h qlAssetSwap1"
  c_assetSwap' :: CInt -> Ptr CBond -> CDouble -> CDouble -> CDouble -> Ptr CIborIndex -> CDouble -> Ptr CDayCounter -> CDate -> CInt -> Ptr CString -> IO (Ptr CAssetSwap)

assetSwap :: Bool -- ^payBondCoupon
  -> Bond -- ^bond
  -> Double -- ^bondCleanPrice
  -> IborIndex -- ^iborIndex
  -> Double -- ^spread
  -> Schedule -- ^floatSchedule
  -> DayCounter -- ^floatingDayCount
  -> Bool -- ^parAssetSwap
  -> IO AssetSwap
assetSwap = $(ffiCall 'assetSwap) c_assetSwap

foreign import ccall safe "ql.h qlAssetSwap"
  c_assetSwap :: CInt -> Ptr CBond -> CDouble -> Ptr CIborIndex -> CDouble -> Ptr CSchedule -> Ptr CDayCounter -> CInt -> Ptr CString -> IO (Ptr CAssetSwap)

bondLeg :: AssetSwap -> IO Leg
bondLeg = $(ffiCall 'bondLeg) c_bondLeg

foreign import ccall safe "ql.h qlAssetSwapBondLeg"
  c_bondLeg :: Ptr CAssetSwap -> Ptr CString -> IO (Ptr CLeg)

cleanPrice :: AssetSwap -> IO Double
cleanPrice = $(ffiCallX 'cleanPrice) c_cleanPrice

foreign import ccall safe "ql.h qlAssetSwapCleanPrice"
  c_cleanPrice :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

fairCleanPrice :: AssetSwap -> IO Double
fairCleanPrice = $(ffiCallX 'fairCleanPrice) c_fairCleanPrice

foreign import ccall safe "ql.h qlAssetSwapFairCleanPrice"
  c_fairCleanPrice :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

fairNonParRepayment :: AssetSwap -> IO Double
fairNonParRepayment = $(ffiCallX 'fairNonParRepayment) c_fairNonParRepayment

foreign import ccall safe "ql.h qlAssetSwapFairNonParRepayment"
  c_fairNonParRepayment :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

nonParRepayment :: AssetSwap -> IO Double
nonParRepayment = $(ffiCallX 'nonParRepayment) c_nonParRepayment

foreign import ccall safe "ql.h qlAssetSwapNonParRepayment"
  c_nonParRepayment :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

parSwap :: AssetSwap -> IO Bool
parSwap = $(ffiCallX 'parSwap) c_parSwap

foreign import ccall safe "ql.h qlAssetSwapParSwap"
  c_parSwap :: Ptr CAssetSwap -> Ptr CString -> IO CInt

payBondCoupon :: AssetSwap -> IO Bool
payBondCoupon = $(ffiCallX 'payBondCoupon) c_payBondCoupon

foreign import ccall safe "ql.h qlAssetSwapPayBondCoupon"
  c_payBondCoupon :: Ptr CAssetSwap -> Ptr CString -> IO CInt

-- OvernightIndexedSwap
overnightIndexedSwap :: OvernightIndexedSwapType -- ^type
  -> Double -- ^nominal
  -> Schedule -- ^schedule
  -> Double -- ^fixedRate
  -> DayCounter -- ^fixedDC
  -> OvernightIndex -- ^overnightIndex
  -> Double -- ^spread
  -> IO OvernightIndexedSwap
overnightIndexedSwap = $(ffiCall 'overnightIndexedSwap) c_overnightIndexedSwap

foreign import ccall safe "ql.h qlOvernightIndexedSwap"
  c_overnightIndexedSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr COvernightIndex -> CDouble -> Ptr CString -> IO (Ptr COvernightIndexedSwap)

overnightIndexedSwap' :: OvernightIndexedSwapType -- ^type
  -> [Double] -- ^nominals
  -> Schedule -- ^schedule
  -> Double -- ^fixedRate
  -> DayCounter -- ^fixedDC
  -> OvernightIndex -- ^overnightIndex
  -> Double -- ^spread
  -> IO OvernightIndexedSwap
overnightIndexedSwap' = $(ffiCall 'overnightIndexedSwap') c_overnightIndexedSwap'

foreign import ccall safe "ql.h qlOvernightIndexedSwap1"
  c_overnightIndexedSwap' :: CInt -> CUInt -> Ptr CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr COvernightIndex -> CDouble -> Ptr CString -> IO (Ptr COvernightIndexedSwap)

overnightLeg :: OvernightIndexedSwap -> IO Leg
overnightLeg = $(ffiCall 'overnightLeg) c_overnightLeg

foreign import ccall safe "ql.h qlOvernightIndexedSwapOvernightLeg"
  c_overnightLeg :: Ptr COvernightIndexedSwap -> Ptr CString -> IO (Ptr CLeg)

overnightLegBPS :: OvernightIndexedSwap -> IO Double
overnightLegBPS = $(ffiCallX 'overnightLegBPS) c_overnightLegBPS

foreign import ccall safe "ql.h qlOvernightIndexedSwapOvernightLegBPS"
  c_overnightLegBPS :: Ptr COvernightIndexedSwap -> Ptr CString -> IO CDouble

overnightLegNPV :: OvernightIndexedSwap -> IO Double
overnightLegNPV = $(ffiCallX 'overnightLegNPV) c_overnightLegNPV

foreign import ccall safe "ql.h qlOvernightIndexedSwapOvernightLegNPV"
  c_overnightLegNPV :: Ptr COvernightIndexedSwap -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
