{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.AssetSwap
  (
    assetSwap
  , assetSwap'

  , bondLeg
  , cleanPrice
  , fairCleanPrice
  , fairNonParRepayment
  , fairSpread
  , floatingLeg
  , floatingLegBPS
  , floatingLegNPV
  , nonParRepayment
  , parSwap
  , payBondCoupon
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

fairSpread :: AssetSwap -> IO Double
fairSpread = $(ffiCallX 'fairSpread) c_fairSpread

foreign import ccall safe "ql.h qlAssetSwapFairSpread"
  c_fairSpread :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

floatingLeg :: AssetSwap -> IO Leg
floatingLeg = $(ffiCall 'floatingLeg) c_floatingLeg

foreign import ccall safe "ql.h qlAssetSwapFloatingLeg"
  c_floatingLeg :: Ptr CAssetSwap -> Ptr CString -> IO (Ptr CLeg)

floatingLegBPS :: AssetSwap -> IO Double
floatingLegBPS = $(ffiCallX 'floatingLegBPS) c_floatingLegBPS

foreign import ccall safe "ql.h qlAssetSwapFloatingLegBPS"
  c_floatingLegBPS :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

floatingLegNPV :: AssetSwap -> IO Double
floatingLegNPV = $(ffiCallX 'floatingLegNPV) c_floatingLegNPV

foreign import ccall safe "ql.h qlAssetSwapFloatingLegNPV"
  c_floatingLegNPV :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
