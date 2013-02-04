{-# LANGUAGE MultiParamTypeClasses #-}
module QuantLib.Internal.Types
  (
  -- cashflows
    CLeg
  , CFloatingRateCouponPricer

  -- curencies
  , CCurrency

  -- indexes
  , CIndex
  , CIborIndex

  -- instruments
  , CInstrument
  , CBond
  , CFixedRateBond

  -- pricingengines
  , CPricingEngine

  -- termstructures
  , CRateHelper
  , CYieldTermStructure
  , CVolTermStructure
  , COptionletVolStructure

  -- time
  , CCalendar
  , CDayCounter
  , CPeriod
  , CSchedule

  -- common
  , CInterestRate
  , CQuote
  )
where

import QuantLib.Internal.Utils

-- cashflows
data CLeg

instance Finalizable CLeg where
  finalize = p_freeLeg
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

data CFloatingRateCouponPricer

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

-- currencies
data CCurrency

instance Finalizable CCurrency where
  finalize = p_freeCurrency
foreign import ccall safe "ql.h &qlFreeCurrency"
  p_freeCurrency :: FunPtr (Ptr CCurrency -> IO ())

instance NamedSingleton CCurrency where
  c_construct = c_currency
  c_name = c_currencyName
foreign import ccall safe "ql.h qlCurrency"
  c_currency :: CString -> Ptr CString -> IO (Ptr CCurrency)
foreign import ccall safe "ql.h qlCurrencyName"
  c_currencyName :: Ptr CCurrency -> IO CString

-- indexes
data CIndex
data CIborIndex

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex
instance Finalizable CIndex where
  finalize = p_freeIndex
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())
foreign import ccall safe "ql.h &qlFreeIndex"
  p_freeIndex :: FunPtr (Ptr CIndex -> IO ())

instance Upcastable CIborIndex CIndex where
  c_upcast = c_iborAsIndex
foreign import ccall safe "ql.h qlIborAsIndex"
  c_iborAsIndex :: Ptr CIborIndex -> IO (Ptr CIndex)

-- instruments
data CInstrument
data CBond
data CFixedRateBond

instance Finalizable CBond where
  finalize = p_freeBond
instance Finalizable CFixedRateBond where
  finalize = p_freeFixedRateBond
instance Finalizable CInstrument where
  finalize = p_freeInstrument
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h &qlFreeFixedRateBond"
  p_freeFixedRateBond :: FunPtr (Ptr CFixedRateBond -> IO ())
foreign import ccall safe "ql.h &qlFreeInstrument"
  p_freeInstrument :: FunPtr (Ptr CInstrument -> IO ())

instance Upcastable CFixedRateBond CBond where
  c_upcast = c_fixedRateBondAsBond
instance Upcastable CBond CInstrument where
  c_upcast = c_bondAsInstrument
foreign import ccall safe "ql.h qlFixedRateBondAsBond"
  c_fixedRateBondAsBond :: Ptr CFixedRateBond -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> IO (Ptr CInstrument)

-- pricingengines
data CPricingEngine

instance Finalizable CPricingEngine where
  finalize = p_freePricingEngine
foreign import ccall safe "ql.h &qlFreePricingEngine"
  p_freePricingEngine :: FunPtr (Ptr CPricingEngine -> IO ())

-- termstructures
data CRateHelper
data CYieldTermStructure
data CVolTermStructure
data COptionletVolStructure

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper
foreign import ccall safe "ql.h &qlFreeRateHelper"
  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())

instance Finalizable CYieldTermStructure
  where finalize = p_freeYieldTermStructure
foreign import ccall safe "ql.h &qlFreeYieldTermStructure"
  p_freeYieldTermStructure :: FunPtr (Ptr CYieldTermStructure -> IO ())

instance Finalizable COptionletVolStructure where
  finalize = p_freeOptionletVolStructure
foreign import ccall safe "ql.h &qlFreeOptionletVolatilityStructure"
  p_freeOptionletVolStructure :: FunPtr (Ptr COptionletVolStructure -> IO ())

-- time
data CCalendar
data CDayCounter
data CPeriod
data CSchedule

instance Finalizable CCalendar where
  finalize = p_freeCalendar
foreign import ccall safe "ql.h &qlFreeCalendar"
  p_freeCalendar :: FunPtr (Ptr CCalendar -> IO ())

instance NamedSingleton CCalendar where
  c_construct = c_calendar
  c_name = c_calendarName
foreign import ccall safe "ql.h qlCalendar"
  c_calendar :: CString -> Ptr CString -> IO (Ptr CCalendar)
foreign import ccall safe "ql.h qlCalendarName"
  c_calendarName :: Ptr CCalendar -> IO CString

instance Finalizable CDayCounter where
  finalize = p_freeDayCounter
foreign import ccall safe "ql.h &qlFreeDayCounter"
  p_freeDayCounter :: FunPtr (Ptr CDayCounter -> IO ())

instance NamedSingleton CDayCounter where
  c_construct = c_dayCounter
  c_name = c_dayCounterName
foreign import ccall safe "ql.h qlDayCounter"
  c_dayCounter :: CString -> Ptr CString -> IO (Ptr CDayCounter)
foreign import ccall safe "ql.h qlDayCounterName"
  c_dayCounterName :: Ptr CDayCounter -> IO CString

instance Finalizable CPeriod where
  finalize = p_freePeriod
foreign import ccall safe "ql.h &qlFreePeriod"
  p_freePeriod :: FunPtr (Ptr CPeriod -> IO ())

instance Finalizable CSchedule where
  finalize = p_freeSchedule
foreign import ccall safe "ql.h &qlFreeSchedule"
  p_freeSchedule :: FunPtr (Ptr CSchedule -> IO ())

-- common
data CInterestRate
data CQuote

instance Finalizable CInterestRate where
  finalize = p_freeInterestRate
foreign import ccall safe "ql.h &qlFreeInterestRate"
  p_freeInterestRate :: FunPtr (Ptr CInterestRate -> IO ())

instance Finalizable CQuote where
  finalize = p_freeQuote
foreign import ccall safe "ql.h &qlFreeQuote"
  p_freeQuote :: FunPtr (Ptr CQuote -> IO ())
