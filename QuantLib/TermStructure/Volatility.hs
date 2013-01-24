module QuantLib.TermStructure.Volatility
  (
  -- makers
    constantOptionletVol
  )
where

import QuantLib.Internal.Enum
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

foreign import ccall safe "ql.h qlConstantOptionletVol"
  c_constantOptionletVol :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolStructure)

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
