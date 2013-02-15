{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.OvernightIndexedSwap
  (
    overnightIndexedSwap
  , overnightIndexedSwap'
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
overnightIndexedSwap = $(ffiConstruct 'overnightIndexedSwap) c_overnightIndexedSwap

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
overnightIndexedSwap' = $(ffiConstruct 'overnightIndexedSwap') c_overnightIndexedSwap'

foreign import ccall safe "ql.h qlOvernightIndexedSwap1"
  c_overnightIndexedSwap' :: CInt -> CUInt -> Ptr CDouble -> Ptr CSchedule -> CDouble -> Ptr CDayCounter -> Ptr COvernightIndex -> CDouble -> Ptr CString -> IO (Ptr COvernightIndexedSwap)
