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
import QuantLib.Quote(Quote)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar)
import QuantLib.Time.DayCounter(DayCounter)

data CVolTermStructure
type VolTermStructure = Object CVolTermStructure

data COptionletVolStructure
type OptionletVolStructure = Object COptionletVolStructure

--foreign import ccall safe "ql.h &qlFreeRateHelper"
--  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())
--
--foreign import ccall safe "ql.h qlDepositRateHelper"
--  c_depositRateHelper :: Ptr CQuote -> Ptr CPeriod -> CUInt -> Ptr CCalendar
--    -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)

--instance Finalizable CRateHelper where
--  finalize = p_freeRateHelper

-- |(qlConstantOptionletVolatility)
constantOptionletVol :: Word -> Calendar -> BusinessDayConvention -> Quote
  -> DayCounter -> IO OptionletVolStructure
constantOptionletVol = undefined
