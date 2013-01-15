{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls,MultiParamTypeClasses #-}
module QuantLib.Types
  (
    CRateHelper
  , RateHelper

  , CCurrency
  , Currency

  , CIndex
  , Index

  , CInstrument
  , Instrument

  , CInterestRate
  , InterestRate

  , CPricingEngine
  , PricingEngine

  , CQuote
  , Quote

  , CFloatingRateCouponPricer
  , FloatingRateCouponPricer

  , CLeg
  , Leg

  , CIborIndex
  , IborIndex

  , CBond
  , Bond

  , CFixedRateBond
  , FixedRateBond

  , CVolTermStructure
  , VolTermStructure

  , COptionletVolStructure
  , OptionletVolStructure

  , CYieldTermStructure
  , YieldTermStructure

  , CCalendar
  , Calendar

  , CDayCounter
  , DayCounter

  , CPeriod
  , Period

  , CSchedule
  , Schedule
  )
where

import QuantLib.Internal

data CRateHelper
type RateHelper = Object CRateHelper

data CCurrency
type Currency = Object CCurrency

data CIndex
type Index = Object CIndex

data CInstrument
type Instrument = Object CInstrument

data CInterestRate
type InterestRate = Object CInterestRate

data CPricingEngine
type PricingEngine = Object CPricingEngine

data CQuote
type Quote = Object CQuote

data CFloatingRateCouponPricer
type FloatingRateCouponPricer = Object CFloatingRateCouponPricer

data CLeg
type Leg = Object CLeg

data CIborIndex
type IborIndex = Object CIborIndex

data CBond
type Bond = Object CBond

data CFixedRateBond
type FixedRateBond = Object CFixedRateBond

data CVolTermStructure
type VolTermStructure = Object CVolTermStructure

data COptionletVolStructure
type OptionletVolStructure = Object COptionletVolStructure

data CYieldTermStructure
type YieldTermStructure = Object CYieldTermStructure

data CCalendar
type Calendar = Object CCalendar

data CDayCounter
type DayCounter = Object CDayCounter

data CPeriod
type Period = Object CPeriod

data CSchedule
type Schedule = Object CSchedule

instance Finalizable CCurrency where
  finalize = p_freeCurrency
instance NamedSingleton CCurrency where
  c_construct = c_currency
  c_name = c_currencyName
foreign import ccall safe "ql.h &qlFreeCurrency"
  p_freeCurrency :: FunPtr (Ptr CCurrency -> IO ())
foreign import ccall safe "ql.h &qlFreeInterestRate"
  p_freeInterestRate :: FunPtr (Ptr CInterestRate -> IO ())

instance Finalizable CInterestRate where
  finalize = p_freeInterestRate
foreign import ccall safe "ql.h &qlFreePricingEngine"
  p_freePricingEngine :: FunPtr (Ptr CPricingEngine -> IO ())

instance Finalizable CPricingEngine where
  finalize = p_freePricingEngine

instance Finalizable CQuote where
  finalize = p_freeQuote
foreign import ccall safe "ql.h &qlFreeQuote"
  p_freeQuote :: FunPtr (Ptr CQuote -> IO ())

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

instance Finalizable CLeg where
  finalize = p_freeLeg
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex
instance IsA CIndex CIndex where
  cast = id
instance IsA CIndex CIborIndex where
  cast = c_iborAsIndex
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())
foreign import ccall safe "ql.h qlIborAsIndex"
  c_iborAsIndex :: Ptr CIborIndex -> Ptr CIndex

instance Finalizable CBond where
  finalize = p_freeBond
instance Finalizable CFixedRateBond where
  finalize = castFinalizer p_freeBond
instance IsA CBond CBond where
  cast = id
instance IsA CBond CFixedRateBond where
  cast = castPtr
instance IsA CInstrument CBond where
  cast = c_bondAsInstrument
instance IsA CInstrument CFixedRateBond where
  cast = c_bondAsInstrument . cast -- delegating to the Bond casting interface
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> Ptr CInstrument

instance Finalizable COptionletVolStructure where
  finalize = p_freeOptionletVolStructure
foreign import ccall safe "ql.h &qlFreeOptionletVolatilityStructure"
  p_freeOptionletVolStructure :: FunPtr (Ptr COptionletVolStructure -> IO ())

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper
foreign import ccall safe "ql.h &qlFreeRateHelper"
  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())

instance Finalizable CYieldTermStructure
  where finalize = p_freeYieldTermStructure
foreign import ccall safe "ql.h &qlFreeYieldTermStructure"
  p_freeYieldTermStructure :: FunPtr (Ptr CYieldTermStructure -> IO ())

instance Finalizable CCalendar where
  finalize = p_freeCalendar
instance NamedSingleton CCalendar where
  c_construct = c_calendar
  c_name = c_calendarName
foreign import ccall safe "ql.h &qlFreeCalendar"
  p_freeCalendar :: FunPtr (Ptr CCalendar -> IO ())
foreign import ccall safe "ql.h qlCalendar"
  c_calendar :: CString -> Ptr CString -> IO (Ptr CCalendar)
foreign import ccall safe "ql.h qlCalendarName"
  c_calendarName :: Ptr CCalendar -> IO CString

instance Finalizable CDayCounter where
  finalize = p_freeDayCounter
instance NamedSingleton CDayCounter where
  c_construct = c_dayCounter
  c_name = c_dayCounterName
foreign import ccall safe "ql.h &qlFreeDayCounter"
  p_freeDayCounter :: FunPtr (Ptr CDayCounter -> IO ())
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
foreign import ccall safe "ql.h qlCurrency"
  c_currency :: CString -> Ptr CString -> IO (Ptr CCurrency)
foreign import ccall safe "ql.h qlCurrencyName"
  c_currencyName :: Ptr CCurrency -> IO CString

instance IsA CInstrument CInstrument where
  cast = id
