{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Swap
  (
    swap'
  , swap
  , assetSwap'
  , assetSwap
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
  , fairRate
  , fairSpread
  , fixedLeg
  , fixedLegBPS
  , fixedLegNPV
  , floatingLeg
  , floatingLegBPS
  , floatingLegNPV
  )

where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Date
import QuantLib.Time.BusinessDayConvention
import QuantLib.Types
import qualified QuantLib.Instrument.BMASwapType as BMASwapType
import qualified QuantLib.Instrument.VanillaSwapType as VanillaSwapType

-- |Multi leg constructor.
swap' :: [(Leg, Bool)] -- ^(legs, payer)
  -> IO Swap
swap' = $(ffiConstruct 'swap') c_swap'

foreign import ccall safe "ql.h qlSwap1"
  c_swap' :: CUInt -> Ptr (Ptr CLeg) -> Ptr CInt -> Ptr CString -> IO (Ptr CSwap)

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
assetSwap' = $(ffiConstruct 'assetSwap') c_assetSwap'

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
assetSwap = $(ffiConstruct 'assetSwap) c_assetSwap

foreign import ccall safe "ql.h qlAssetSwap"
  c_assetSwap :: CInt -> Ptr CBond -> CDouble -> Ptr CIborIndex -> CDouble -> Ptr CSchedule -> Ptr CDayCounter -> CInt -> Ptr CString -> IO (Ptr CAssetSwap)

bmaSwap :: BMASwapType.BMASwapType -- ^type
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
bmaSwap = $(ffiConstruct 'bmaSwap) c_bmaSwap

foreign import ccall safe "ql.h qlBMASwap"
  c_bmaSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> CDouble -> Ptr CIborIndex -> Ptr CDayCounter -> Ptr CSchedule -> Ptr CBMAIndex -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CBMASwap)

vanillaSwap :: VanillaSwapType.VanillaSwapType -- ^type
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
vanillaSwap = $(ffiConstruct 'vanillaSwap) c_vanillaSwap

foreign import ccall safe "ql.h qlVanillaSwap"
  c_vanillaSwap :: CInt -> CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr CSchedule -> Ptr CIborIndex -> CDouble -> Ptr CDayCounter -> CInt -> Ptr CString -> IO (Ptr CVanillaSwap)

-- |The cash flows belonging to the first leg are paid; the ones belonging to the second leg are received.
swap :: Leg -- ^firstLeg
  -> Leg -- ^secondLeg
  -> IO Swap
swap = $(ffiConstruct 'swap) c_swap

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
leg = $(ffiConstruct 'leg) c_leg

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

maturityDate :: Swap -> IO Day
maturityDate = $(ffiCallX 'maturityDate) c_maturityDate

foreign import ccall safe "ql.h qlSwapMaturityDate"
  c_maturityDate :: Ptr CSwap -> Ptr CString -> IO CDate

npvDateDiscount :: Swap -> IO Double
npvDateDiscount = $(ffiCallX 'npvDateDiscount) c_npvDateDiscount

foreign import ccall safe "ql.h qlSwapNpvDateDiscount"
  c_npvDateDiscount :: Ptr CSwap -> Ptr CString -> IO CDouble

startDate :: Swap -> IO Day
startDate = $(ffiCallX 'startDate) c_startDate

foreign import ccall safe "ql.h qlSwapStartDate"
  c_startDate :: Ptr CSwap -> Ptr CString -> IO CDate

startDiscounts :: Swap
  -> Word -- ^j
  -> IO Double
startDiscounts = $(ffiCallX 'startDiscounts) c_startDiscounts

foreign import ccall safe "ql.h qlSwapStartDiscounts"
  c_startDiscounts :: Ptr CSwap -> CUInt -> Ptr CString -> IO CDouble

fairRate :: VanillaSwap -> IO Double
fairRate = $(ffiCallX 'fairRate) c_fairRate

foreign import ccall safe "ql.h qlVanillaSwapFairRate"
  c_fairRate :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

fairSpread :: VanillaSwap -> IO Double
fairSpread = $(ffiCallX 'fairSpread) c_fairSpread

foreign import ccall safe "ql.h qlVanillaSwapFairSpread"
  c_fairSpread :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

fixedLeg :: VanillaSwap -> IO Leg
fixedLeg = $(ffiConstruct 'fixedLeg) c_fixedLeg

foreign import ccall safe "ql.h qlVanillaSwapFixedLeg"
  c_fixedLeg :: Ptr CVanillaSwap -> Ptr CString -> IO (Ptr CLeg)

fixedLegBPS :: VanillaSwap -> IO Double
fixedLegBPS = $(ffiCallX 'fixedLegBPS) c_fixedLegBPS

foreign import ccall safe "ql.h qlVanillaSwapFixedLegBPS"
  c_fixedLegBPS :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

fixedLegNPV :: VanillaSwap -> IO Double
fixedLegNPV = $(ffiCallX 'fixedLegNPV) c_fixedLegNPV

foreign import ccall safe "ql.h qlVanillaSwapFixedLegNPV"
  c_fixedLegNPV :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

floatingLeg :: VanillaSwap -> IO Leg
floatingLeg = $(ffiConstruct 'floatingLeg) c_floatingLeg

foreign import ccall safe "ql.h qlVanillaSwapFloatingLeg"
  c_floatingLeg :: Ptr CVanillaSwap -> Ptr CString -> IO (Ptr CLeg)

floatingLegBPS :: VanillaSwap -> IO Double
floatingLegBPS = $(ffiCallX 'floatingLegBPS) c_floatingLegBPS

foreign import ccall safe "ql.h qlVanillaSwapFloatingLegBPS"
  c_floatingLegBPS :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

floatingLegNPV :: VanillaSwap -> IO Double
floatingLegNPV = $(ffiCallX 'floatingLegNPV) c_floatingLegNPV

foreign import ccall safe "ql.h qlVanillaSwapFloatingLegNPV"
  c_floatingLegNPV :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble
