{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.TermStructure.Volatility
  (
    constantOptionletVolatility'
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

foreign import ccall safe "ql.h qlConstantOptionletVol1"
  c_constantOptionletVol' :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolatilityStructure)

-- |Constant caplet volatility, no time-strike dependence. QuantLibXL: qlConstantOptionletVolatility
-- floating reference date, floating market data
constantOptionletVolatility' :: Word -- ^settlementDays
 -> Calendar -- ^cal
 -> BusinessDayConvention -- ^bdc
 -> Quote -- ^volatility
 -> DayCounter -- ^dc
 -> IO OptionletVolatilityStructure
constantOptionletVolatility' = $(ffiCall 'constantOptionletVolatility') c_constantOptionletVol'

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
