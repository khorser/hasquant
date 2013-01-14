{-# LANGUAGE ForeignFunctionInterface #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.TermStructure.Volatility
  (
  -- makers
    constantOptionletVol
  )
where

import QuantLib.Internal
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

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
