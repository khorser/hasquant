{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.TermStructure.Volatility
  (
  -- types
    CVolTermStructure
  , VolTermStructure
  , COptionletVolStructure
  , OptionletVolStructure
  -- makers
  , constantOptionletVol
  )
where

import QuantLib.Internal
import QuantLib.Quote(Quote, CQuote)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DayCounter(DayCounter, CDayCounter)

data CVolTermStructure
type VolTermStructure = Object CVolTermStructure

data COptionletVolStructure
type OptionletVolStructure = Object COptionletVolStructure

foreign import ccall safe "ql.h &qlFreeOptionletVolatilityStructure"
  p_freeOptionletVolStructure :: FunPtr (Ptr COptionletVolStructure -> IO ())

foreign import ccall safe "ql.h qlConstantOptionletVol"
  c_constantOptionletVol :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolStructure)

instance Finalizable COptionletVolStructure where
  finalize = p_freeOptionletVolStructure

-- |(qlConstantOptionletVolatility)
constantOptionletVol :: Word -> Calendar -> BusinessDayConvention -> Quote
  -> DayCounter -> IO OptionletVolStructure
constantOptionletVol settlDays cal conv quote dayCount =
  withObject3 cal quote dayCount
  (\c q dc -> construct $ c_constantOptionletVol (fromIntegral settlDays)
                                               c
                                               (toQlEnum conv)
                                               q
                                               dc)
