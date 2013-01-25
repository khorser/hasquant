{-# LANGUAGE MultiParamTypeClasses,FlexibleInstances,OverlappingInstances #-}
module QuantLib.Types
  (
    Day
  , Word
  -- cashflows
  , CLeg, Leg
  , CFloatingRateCouponPricer, FloatingRateCouponPricer

  -- curencies
  , CCurrency, Currency

  -- indexes
  , CIndex, Index
  , CIborIndex, IborIndex

  -- instruments
  , CInstrument, Instrument
  , CBond, Bond
  , CFixedRateBond, FixedRateBond

  -- pricingengines
  , CPricingEngine, PricingEngine

  -- termstructures
  , CRateHelper, RateHelper
  , CYieldTermStructure, YieldTermStructure
  , CVolTermStructure, VolTermStructure
  , COptionletVolStructure, OptionletVolStructure

  -- time
  , CCalendar, Calendar
  , CDayCounter, DayCounter
  , CPeriod, Period
  , CSchedule, Schedule

  -- common
  , CInterestRate, InterestRate
  , CQuote, Quote

  -- casts
  , asBond
  , withInstrument
  , withIndex
  )
where

import QuantLib.Internal.Utils
import Data.Time.Calendar(Day)
import Data.Word(Word)

class BondClass a where
  -- it is ok to keep the result of the cast
  asBond :: a -> Bond

instance BondClass FixedRateBond where
  asBond = castForeignPtr

-- cashflows
data CLeg
type Leg = ForeignPtr CLeg

instance Finalizable CLeg where
  finalize = p_freeLeg
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

data CFloatingRateCouponPricer
type FloatingRateCouponPricer = ForeignPtr CFloatingRateCouponPricer

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

-- currencies
data CCurrency
type Currency = ForeignPtr CCurrency

instance Finalizable CCurrency where
  finalize = p_freeCurrency
foreign import ccall safe "ql.h &qlFreeCurrency"
  p_freeCurrency :: FunPtr (Ptr CCurrency -> IO ())

instance NamedSingleton CCurrency where
  c_construct = c_currency
  c_name = c_currencyName
instance Show Currency where
  show = name
foreign import ccall safe "ql.h qlCurrency"
  c_currency :: CString -> Ptr CString -> IO (Ptr CCurrency)
foreign import ccall safe "ql.h qlCurrencyName"
  c_currencyName :: Ptr CCurrency -> IO CString

-- indexes
data CIndex
type Index = ForeignPtr CIndex

data CIborIndex
type IborIndex = ForeignPtr CIborIndex

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())

foreign import ccall safe "ql.h qlIborAsIndex"
  c_iborAsIndex :: Ptr CIborIndex -> Ptr CIndex

class IndexClass a where
  -- it is NOT ok to keep the argument of the function after the call
  withIndex :: a -> (Index -> IO b) -> IO b

instance IndexClass IborIndex where
  withIndex x f =
    withForeignPtr x
      (\p -> do ptr <- newForeignPtr_ (c_iborAsIndex p)
                f ptr)

-- instruments
data CInstrument
type Instrument = ForeignPtr CInstrument

data CBond
type Bond = ForeignPtr CBond

data CFixedRateBond
type FixedRateBond = ForeignPtr CFixedRateBond

instance Finalizable CBond where
  finalize = p_freeBond
instance Finalizable CFixedRateBond where
  finalize = castFunPtr p_freeBond
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())

foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> Ptr CInstrument

class InstrumentClass a where
  -- it is NOT ok to keep the argument of the function after the call
  withInstrument :: a -> (Instrument -> IO b) -> IO b

instance InstrumentClass Bond where
  withInstrument x f =
    withForeignPtr x
    (\p -> do ptr <- newForeignPtr_ (c_bondAsInstrument p)
              f ptr)

instance InstrumentClass FixedRateBond where
  withInstrument = withInstrument . asBond

-- pricingengines
data CPricingEngine
type PricingEngine = ForeignPtr CPricingEngine

instance Finalizable CPricingEngine where
  finalize = p_freePricingEngine
foreign import ccall safe "ql.h &qlFreePricingEngine"
  p_freePricingEngine :: FunPtr (Ptr CPricingEngine -> IO ())

-- termstructures
data CRateHelper
type RateHelper = ForeignPtr CRateHelper

data CYieldTermStructure
type YieldTermStructure = ForeignPtr CYieldTermStructure

data CVolTermStructure
type VolTermStructure = ForeignPtr CVolTermStructure

data COptionletVolStructure
type OptionletVolStructure = ForeignPtr COptionletVolStructure

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
type Calendar = ForeignPtr CCalendar

data CDayCounter
type DayCounter = ForeignPtr CDayCounter

data CPeriod
type Period = ForeignPtr CPeriod

data CSchedule
type Schedule = ForeignPtr CSchedule

instance Finalizable CCalendar where
  finalize = p_freeCalendar
foreign import ccall safe "ql.h &qlFreeCalendar"
  p_freeCalendar :: FunPtr (Ptr CCalendar -> IO ())

instance NamedSingleton CCalendar where
  c_construct = c_calendar
  c_name = c_calendarName
instance Show Calendar where
  show = name
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
instance Show DayCounter where
  show = name
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
type InterestRate = ForeignPtr CInterestRate

data CQuote
type Quote = ForeignPtr CQuote

instance Finalizable CInterestRate where
  finalize = p_freeInterestRate
foreign import ccall safe "ql.h &qlFreeInterestRate"
  p_freeInterestRate :: FunPtr (Ptr CInterestRate -> IO ())

instance Finalizable CQuote where
  finalize = p_freeQuote
foreign import ccall safe "ql.h &qlFreeQuote"
  p_freeQuote :: FunPtr (Ptr CQuote -> IO ())
