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
  , fairRate
  , fairSpread
  , fixedLeg
  , fixedLegBPS
  , fixedLegNPV
  , floatingLeg
  , floatingLegBPS
  , floatingLegNPV

  , bmaLeg
  , bmaLegBPS
  , bmaLegNPV
  , fairLiborFraction
  , fairLiborSpread
  , liborFraction
  , liborLeg
  , liborLegBPS
  , liborLegNPV
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
swap' = $(ffiCall 'swap') c_swap'

foreign import ccall safe "ql.h qlSwap1"
  c_swap' :: CUInt -> Ptr (Ptr CLeg) -> Ptr CInt -> Ptr CString -> IO (Ptr CSwap)

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
bmaSwap = $(ffiCall 'bmaSwap) c_bmaSwap

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
fixedLeg = $(ffiCall 'fixedLeg) c_fixedLeg

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
floatingLeg = $(ffiCall 'floatingLeg) c_floatingLeg

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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
