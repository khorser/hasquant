{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.InterestRate
  (
  -- makers
    interestRate
  )
where

import QuantLib.Compounding(Compounding)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Internal
import QuantLib.Types

foreign import ccall safe "ql.h qlInterestRate"
  c_interestRate :: CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> Ptr CString -> IO (Ptr CInterestRate)

-- | (qlInterestRate)
interestRate :: Double -> DayCounter -> Compounding -> Frequency
  -> IO InterestRate
interestRate r dc comp freq =
  withObject dc
  (\c -> construct $ c_interestRate (realToFrac r)
                                    c
                                    (toQlEnum comp)
                                    (toQlEnum freq))
