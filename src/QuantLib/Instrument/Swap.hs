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
