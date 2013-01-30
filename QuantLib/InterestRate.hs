{-# LANGUAGE TemplateHaskell #-}
module QuantLib.InterestRate
  (
  -- makers
    interestRate
  )
where

import QuantLib.Compounding(Compounding)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlInterestRate"
  c_interestRate :: CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> Ptr CString -> IO (Ptr CInterestRate)

-- | (qlInterestRate)
interestRate :: Double -> DayCounter -> Compounding -> Frequency
  -> IO InterestRate
interestRate = $(ffiConstruct 'interestRate) c_interestRate
