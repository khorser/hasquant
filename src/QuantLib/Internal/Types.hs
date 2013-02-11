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
  , CInterestRateIndex
  , CIborIndex
  , CSwapIndex

  -- instruments
  , CInstrument
  , CBond
  , CFixedRateBond
  , CForward
  , CFixedRateBondForward
  , CForwardRateAgreement
  , CSwap
  , CVanillaSwap

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
  , CSimpleQuote
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
data CInterestRateIndex
data CIborIndex
data CSwapIndex

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex
instance Finalizable CIndex where
  finalize = p_freeIndex
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())
foreign import ccall safe "ql.h &qlFreeIndex"
  p_freeIndex :: FunPtr (Ptr CIndex -> IO ())

instance Upcastable CIborIndex CInterestRateIndex where
  c_upcast = c_IborIndexAsInterestRateIndex
foreign import ccall safe "ql.h qlIborIndexAsInterestRateIndex"
  c_IborIndexAsInterestRateIndex :: Ptr CIborIndex -> IO (Ptr CInterestRateIndex)

instance Finalizable CInterestRateIndex where
  finalize = p_freeInterestRateIndex
foreign import ccall safe "ql.h &qlFreeInterestRateIndex"
  p_freeInterestRateIndex :: FunPtr (Ptr CInterestRateIndex -> IO ())
instance Upcastable CInterestRateIndex CIndex where
  c_upcast = c_InterestRateIndexAsIndex
foreign import ccall safe "ql.h qlInterestRateIndexAsIndex"
  c_InterestRateIndexAsIndex :: Ptr CInterestRateIndex -> IO (Ptr CIndex)

instance Finalizable CSwapIndex where
  finalize = p_freeSwapIndex
foreign import ccall safe "ql.h &qlFreeSwapIndex"
  p_freeSwapIndex :: FunPtr (Ptr CSwapIndex -> IO ())
instance Upcastable CSwapIndex CInterestRateIndex where
  c_upcast = c_SwapIndexAsInterestRateIndex
foreign import ccall safe "ql.h qlSwapIndexAsInterestRateIndex"
  c_SwapIndexAsInterestRateIndex :: Ptr CSwapIndex -> IO (Ptr CInterestRateIndex)

-- instruments
data CInstrument
data CBond
data CFixedRateBond
data CForward
data CFixedRateBondForward
data CForwardRateAgreement

instance Finalizable CBond where
  finalize = p_freeBond
instance Finalizable CFixedRateBond where
  finalize = p_freeFixedRateBond
instance Finalizable CInstrument where
  finalize = p_freeInstrument
instance Finalizable CForward where
  finalize = p_freeForward
instance Finalizable CFixedRateBondForward where
  finalize = p_freeFixedRateBondForward
instance Finalizable CForwardRateAgreement where
  finalize = p_freeForwardRateAgreement
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h &qlFreeFixedRateBond"
  p_freeFixedRateBond :: FunPtr (Ptr CFixedRateBond -> IO ())
foreign import ccall safe "ql.h &qlFreeInstrument"
  p_freeInstrument :: FunPtr (Ptr CInstrument -> IO ())
foreign import ccall safe "ql.h &qlFreeForward"
  p_freeForward :: FunPtr (Ptr CForward -> IO ())
foreign import ccall safe "ql.h &qlFreeFixedRateBondForward"
  p_freeFixedRateBondForward :: FunPtr (Ptr CFixedRateBondForward -> IO ())
foreign import ccall safe "ql.h &qlFreeForwardRateAgreement"
  p_freeForwardRateAgreement :: FunPtr (Ptr CForwardRateAgreement -> IO ())

instance Upcastable CFixedRateBond CBond where
  c_upcast = c_fixedRateBondAsBond
instance Upcastable CBond CInstrument where
  c_upcast = c_bondAsInstrument
instance Upcastable CFixedRateBondForward CForward where
  c_upcast = c_fixedRateBondForwardAsForward
instance Upcastable CForwardRateAgreement CForward where
  c_upcast = c_forwardRateAgreementAsForward
instance Upcastable CForward CInstrument where
  c_upcast = c_forwardAsInstrument
foreign import ccall safe "ql.h qlFixedRateBondAsBond"
  c_fixedRateBondAsBond :: Ptr CFixedRateBond -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> IO (Ptr CInstrument)
foreign import ccall safe "ql.h qlFixedRateBondForwardAsForward"
  c_fixedRateBondForwardAsForward :: Ptr CFixedRateBondForward -> IO (Ptr CForward)
foreign import ccall safe "ql.h qlForwardAsInstrument"
  c_forwardAsInstrument :: Ptr CForward -> IO (Ptr CInstrument)
foreign import ccall safe "ql.h qlForwardRateAgreementAsForward"
  c_forwardRateAgreementAsForward :: Ptr CForwardRateAgreement -> IO (Ptr CForward)

data CVanillaSwap
instance Finalizable CVanillaSwap where
  finalize = p_freeVanillaSwap
foreign import ccall safe "ql.h &qlFreeVanillaSwap"
  p_freeVanillaSwap :: FunPtr (Ptr CVanillaSwap -> IO ())
instance Upcastable CVanillaSwap CSwap where
  c_upcast = c_VanillaSwapAsSwap
foreign import ccall safe "ql.h qlVanillaSwapAsSwap"
  c_VanillaSwapAsSwap :: Ptr CVanillaSwap -> IO (Ptr CSwap)
data CSwap
instance Finalizable CSwap where
  finalize = p_freeSwap
foreign import ccall safe "ql.h &qlFreeSwap"
  p_freeSwap :: FunPtr (Ptr CSwap -> IO ())
instance Upcastable CSwap CInstrument where
  c_upcast = c_SwapAsInstrument
foreign import ccall safe "ql.h qlSwapAsInstrument"
  c_SwapAsInstrument :: Ptr CSwap -> IO (Ptr CInstrument)

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

data CSimpleQuote
instance Finalizable CSimpleQuote where
  finalize = p_freeSimpleQuote
foreign import ccall safe "ql.h &qlFreeSimpleQuote"
  p_freeSimpleQuote :: FunPtr (Ptr CSimpleQuote -> IO ())
instance Upcastable CSimpleQuote CQuote where
  c_upcast = c_SimpleQuoteAsQuote
foreign import ccall safe "ql.h qlSimpleQuoteAsQuote"
  c_SimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)
