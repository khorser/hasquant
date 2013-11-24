{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Index
  (
    addFixing
  , bmaIndex
  , fixingSchedule
  , forecastFixing

  , fixingCalendar
  , currency
  , dayCounter
  , fixingDays
  , tenor
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Enum(fromQlEnum)
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Time.Unit(Unit)
import QuantLib.Types

foreign import ccall safe "ql.h qlIndexAddFixing"
  c_addFixing :: Ptr CIndex -> CDate -> CDouble -> CInt -> Ptr CString -> IO ()

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object
addFixing :: Index
  -> Day -- ^fixingDate
  -> Double -- ^fixing
  -> Bool -- ^forceOverwrite
  -> IO ()
addFixing = $(ffiCallX 'addFixing) c_addFixing

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

-- |returns the calendar defining valid fixing dates
fixingCalendar :: Index
  -> IO Calendar
fixingCalendar = $(ffiCall 'fixingCalendar) c_fixingCalendar

foreign import ccall safe "ql.h qlIndexFixingCalendar"
  c_fixingCalendar :: Ptr CIndex -> Ptr CString -> IO (Ptr CCalendar)

currency :: InterestRateIndex
  -> IO Currency
currency = $(ffiCall 'currency) c_currency

foreign import ccall safe "ql.h qlInterestRateIndexCurrency"
  c_currency :: Ptr CInterestRateIndex -> Ptr CString -> IO (Ptr CCurrency)

dayCounter :: InterestRateIndex
  -> IO DayCounter
dayCounter = $(ffiCall 'dayCounter) c_dayCounter

foreign import ccall safe "ql.h qlInterestRateIndexDayCounter"
  c_dayCounter :: Ptr CInterestRateIndex -> Ptr CString -> IO (Ptr CDayCounter)

fixingDays :: InterestRateIndex
  -> Word
fixingDays = $(ffiCallPure 'fixingDays) c_fixingDays

foreign import ccall safe "ql.h qlInterestRateIndexFixingDays"
  c_fixingDays :: Ptr CInterestRateIndex -> IO CUInt

tenor :: InterestRateIndex -> Either String (Int, Unit)
tenor o = purifyExceptions $ do
  (n, u) <- withObject o (getIntPair . c_tenor)
  e <- fromQlEnum (show ''Unit) u
  return (n, e)

foreign import ccall safe "ql.h qlInterestRateIndexTenor"
  c_tenor :: Ptr CInterestRateIndex -> Ptr CInt -> Ptr CString -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
