{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.AssetSwap
  (
    assetSwap
  , assetSwap'
  )

where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Date
import QuantLib.Types

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
