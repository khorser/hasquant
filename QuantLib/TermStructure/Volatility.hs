{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Volatility
  (
  -- makers
    constantOptionletVol
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

foreign import ccall safe "ql.h qlConstantOptionletVol"
  c_constantOptionletVol :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolStructure)

-- |(qlConstantOptionletVolatility)
constantOptionletVol :: Word -> Calendar -> BusinessDayConvention -> Quote
  -> DayCounter -> IO OptionletVolStructure
constantOptionletVol = $(ffiConstruct 'constantOptionletVol 'c_constantOptionletVol)
