{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Index.Ibor
  (
  -- types
    CIborIndex
  , IborIndex
  -- makers
  , iborIndex
  )
where

import QuantLib.Currency(Currency, CCurrency)
import QuantLib.Internal
import QuantLib.TermStructure.Yield(YieldTermStructure, CYieldTermStructure)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DayCounter(DayCounter, CDayCounter)
import QuantLib.Time.Period(Period, CPeriod)

data CIborIndex
type IborIndex = Object CIborIndex

foreign import ccall safe "ql.h qlIborIndex"
  c_iborIndex :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex

-- | (qlIborIndex)
iborIndex :: String -> Period -> Word -> Currency -> Calendar
  -> BusinessDayConvention -> Bool -> DayCounter -> Maybe YieldTermStructure
  -> IO IborIndex
iborIndex famname tenor settlDays ccy cal conv eom dayCounter fwd =
  withCString famname
  (\n ->
    withObject4 tenor ccy cal dayCounter
    (\t cur c dc ->
      maybeWithObject fwd
      (construct . c_iborIndex n
                                      t
                                      (fromIntegral settlDays)
                                      cur
                                      c
                                      (toQlEnum conv)
                                      (fromBool eom)
                                      dc)))
