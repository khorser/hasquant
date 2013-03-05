{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.OvernightIndexedSwap
  (
    overnightIndexedSwap
  , overnightIndexedSwap'

  , overnightLeg
  , overnightLegBPS
  , overnightLegNPV
  )

where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Instrument.OvernightIndexedSwapType

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
