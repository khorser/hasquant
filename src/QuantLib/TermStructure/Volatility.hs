{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.TermStructure.Volatility
  (
    constantOptionletVol
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

foreign import ccall safe "ql.h qlConstantOptionletVol"
  c_constantOptionletVol :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolStructure)

-- |Constant caplet volatility, no time-strike dependence. QuantLibXL: qlConstantOptionletVolatility
-- floating reference date, floating market data
constantOptionletVol :: Word -- ^settlementDays
 -> Calendar -- ^cal
 -> BusinessDayConvention -- ^bdc
 -> Quote -- ^volatility
 -> DayCounter -- ^dc
 -> IO OptionletVolStructure
constantOptionletVol = $(ffiConstruct 'constantOptionletVol) c_constantOptionletVol
