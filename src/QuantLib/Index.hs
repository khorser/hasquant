{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Index
  (
    addFixing
  , bmaIndex
  , fixingSchedule
  , forecastFixing
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlIndexAddFixing"
  c_indexAddFixing :: Ptr CIndex -> CDate -> CDouble -> CInt -> Ptr CString
    -> IO ()

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object. QuantLibXL: qlIndexAddFixings
addFixing :: Index
  -> Day -- ^fixingDate
  -> Double -- ^fixing
  -> Bool -- ^forceOverwrite
  -> IO ()
addFixing = $(ffiCallX 'addFixing) c_indexAddFixing

bmaIndex :: Maybe YieldTermStructure -- ^h
  -> IO BMAIndex
bmaIndex = $(ffiCall 'bmaIndex) c_bmaIndex

foreign import ccall safe "ql.h qlBMAIndex"
  c_bmaIndex :: Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CBMAIndex)

-- |This method returns a schedule of fixing dates between start and end.
fixingSchedule :: BMAIndex
  -> Day -- ^start
  -> Day -- ^end
  -> IO Schedule
fixingSchedule = $(ffiCall 'fixingSchedule) c_fixingSchedule

foreign import ccall safe "ql.h qlBMAIndexFixingSchedule"
  c_fixingSchedule :: Ptr CBMAIndex -> CDate -> CDate -> Ptr CString -> IO (Ptr CSchedule)

-- |It can be overridden to implement particular conventions.
forecastFixing :: InterestRateIndex
  -> Day -- ^fixingDate
  -> IO Double
forecastFixing = $(ffiCallX 'forecastFixing) c_forecastFixing

foreign import ccall safe "ql.h qlInterestRateIndexForecastFixing"
  c_forecastFixing :: Ptr CInterestRateIndex -> CDate -> Ptr CString -> IO CDouble
