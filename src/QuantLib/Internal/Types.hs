{-# LANGUAGE MultiParamTypeClasses #-}
module QuantLib.Internal.Types
  (
  -- cashflow
    CLeg
  , CFloatingRateCouponPricer

  -- currency
  , CCurrency

  -- indices
  , CIndex
  , CInterestRateIndex
  , CIborIndex
  , CSwapIndex
  , COvernightIndex
  , COvernightIndexedSwapIndex
  , CBMAIndex

  -- instruments
  , CInstrument
  , CBond
  , CFixedRateBond
  , CForward
  , CFixedRateBondForward
  , CForwardRateAgreement
  , CSwap
  , CVanillaSwap
  , COvernightIndexedSwap
  , CBMASwap
  , CAssetSwap

  -- pricingengines
  , CPricingEngine

  -- termstructures
  , CRateHelper
  , CSwapRateHelper
  , COISRateHelper
  , CYieldTermStructure
  , CVolTermStructure
  , COptionletVolStructure
  , CBondHelper
  , CFittedBondDiscountCurveFittingMethod
  , CFittedBondDiscountCurve

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

data COvernightIndex
instance Finalizable COvernightIndex where
  finalize = p_freeOvernightIndex
foreign import ccall safe "ql.h &qlFreeOvernightIndex"
  p_freeOvernightIndex :: FunPtr (Ptr COvernightIndex -> IO ())
instance Upcastable COvernightIndex CIborIndex where
  c_upcast = c_OvernightIndexAsIborIndex
foreign import ccall safe "ql.h qlOvernightIndexAsIborIndex"
  c_OvernightIndexAsIborIndex :: Ptr COvernightIndex -> IO (Ptr CIborIndex)

data COvernightIndexedSwapIndex
instance Finalizable COvernightIndexedSwapIndex where
  finalize = p_freeOvernightIndexedSwapIndex
foreign import ccall safe "ql.h &qlFreeOvernightIndexedSwapIndex"
  p_freeOvernightIndexedSwapIndex :: FunPtr (Ptr COvernightIndexedSwapIndex -> IO ())
instance Upcastable COvernightIndexedSwapIndex CSwapIndex where
  c_upcast = c_OvernightIndexedSwapIndexAsSwapIndex
foreign import ccall safe "ql.h qlOvernightIndexedSwapIndexAsSwapIndex"
  c_OvernightIndexedSwapIndexAsSwapIndex :: Ptr COvernightIndexedSwapIndex -> IO (Ptr CSwapIndex)

data CBMAIndex
instance Finalizable CBMAIndex where
  finalize = p_freeBMAIndex
foreign import ccall safe "ql.h &qlFreeBMAIndex"
  p_freeBMAIndex :: FunPtr (Ptr CBMAIndex -> IO ())
instance Upcastable CBMAIndex CInterestRateIndex where
  c_upcast = c_BMAIndexAsInterestRateIndex
foreign import ccall safe "ql.h qlBMAIndexAsInterestRateIndex"
  c_BMAIndexAsInterestRateIndex :: Ptr CBMAIndex -> IO (Ptr CInterestRateIndex)

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

data CAssetSwap
instance Finalizable CAssetSwap where
  finalize = p_freeAssetSwap
foreign import ccall safe "ql.h &qlFreeAssetSwap"
  p_freeAssetSwap :: FunPtr (Ptr CAssetSwap -> IO ())
instance Upcastable CAssetSwap CSwap where
  c_upcast = c_AssetSwapAsSwap
foreign import ccall safe "ql.h qlAssetSwapAsSwap"
  c_AssetSwapAsSwap :: Ptr CAssetSwap -> IO (Ptr CSwap)

data COvernightIndexedSwap
instance Finalizable COvernightIndexedSwap where
  finalize = p_freeOvernightIndexedSwap
foreign import ccall safe "ql.h &qlFreeOvernightIndexedSwap"
  p_freeOvernightIndexedSwap :: FunPtr (Ptr COvernightIndexedSwap -> IO ())
instance Upcastable COvernightIndexedSwap CSwap where
  c_upcast = c_OvernightIndexedSwapAsSwap
foreign import ccall safe "ql.h qlOvernightIndexedSwapAsSwap"
  c_OvernightIndexedSwapAsSwap :: Ptr COvernightIndexedSwap -> IO (Ptr CSwap)

data CBMASwap
instance Finalizable CBMASwap where
  finalize = p_freeBMASwap
foreign import ccall safe "ql.h &qlFreeBMASwap"
  p_freeBMASwap :: FunPtr (Ptr CBMASwap -> IO ())
instance Upcastable CBMASwap CSwap where
  c_upcast = c_BMASwapAsSwap
foreign import ccall safe "ql.h qlBMASwapAsSwap"
  c_BMASwapAsSwap :: Ptr CBMASwap -> IO (Ptr CSwap)

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

data CSwapRateHelper
instance Finalizable CSwapRateHelper where
  finalize = p_freeSwapRateHelper
foreign import ccall safe "ql.h &qlFreeSwapRateHelper"
  p_freeSwapRateHelper :: FunPtr (Ptr CSwapRateHelper -> IO ())
instance Upcastable CSwapRateHelper CRateHelper where
  c_upcast = c_SwapRateHelperAsRateHelper
foreign import ccall safe "ql.h qlSwapRateHelperAsRateHelper"
  c_SwapRateHelperAsRateHelper :: Ptr CSwapRateHelper -> IO (Ptr CRateHelper)

instance Finalizable CYieldTermStructure
  where finalize = p_freeYieldTermStructure
foreign import ccall safe "ql.h &qlFreeYieldTermStructure"
  p_freeYieldTermStructure :: FunPtr (Ptr CYieldTermStructure -> IO ())

instance Finalizable COptionletVolStructure where
  finalize = p_freeOptionletVolStructure
foreign import ccall safe "ql.h &qlFreeOptionletVolatilityStructure"
  p_freeOptionletVolStructure :: FunPtr (Ptr COptionletVolStructure -> IO ())

data CBondHelper
instance Finalizable CBondHelper where
  finalize = p_freeBondHelper
foreign import ccall safe "ql.h &qlFreeBondHelper"
  p_freeBondHelper :: FunPtr (Ptr CBondHelper -> IO ())
instance Upcastable CBondHelper CRateHelper where
  c_upcast = c_BondHelperAsRateHelper
foreign import ccall safe "ql.h qlBondHelperAsRateHelper"
  c_BondHelperAsRateHelper :: Ptr CBondHelper -> IO (Ptr CRateHelper)

data COISRateHelper
instance Finalizable COISRateHelper where
  finalize = p_freeOISRateHelper
foreign import ccall safe "ql.h &qlFreeOISRateHelper"
  p_freeOISRateHelper :: FunPtr (Ptr COISRateHelper -> IO ())
instance Upcastable COISRateHelper CRateHelper where
  c_upcast = c_OISRateHelperAsRateHelper
foreign import ccall safe "ql.h qlOISRateHelperAsRateHelper"
  c_OISRateHelperAsRateHelper :: Ptr COISRateHelper -> IO (Ptr CRateHelper)

data CFittedBondDiscountCurveFittingMethod
instance Finalizable CFittedBondDiscountCurveFittingMethod where
  finalize = p_freeFittedBondDiscountCurveFittingMethod
foreign import ccall safe "ql.h &qlFreeFittedBondDiscountCurveFittingMethod"
  p_freeFittedBondDiscountCurveFittingMethod :: FunPtr (Ptr CFittedBondDiscountCurveFittingMethod -> IO ())

data CFittedBondDiscountCurve
instance Finalizable CFittedBondDiscountCurve where
  finalize = p_freeFittedBondDiscountCurve
foreign import ccall safe "ql.h &qlFreeFittedBondDiscountCurve"
  p_freeFittedBondDiscountCurve :: FunPtr (Ptr CFittedBondDiscountCurve -> IO ())
instance Upcastable CFittedBondDiscountCurve CYieldTermStructure where
  c_upcast = c_FittedBondDiscountCurveAsYieldTermStructure
foreign import ccall safe "ql.h qlFittedBondDiscountCurveAsYieldTermStructure"
  c_FittedBondDiscountCurveAsYieldTermStructure :: Ptr CFittedBondDiscountCurve -> IO (Ptr CYieldTermStructure)

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
