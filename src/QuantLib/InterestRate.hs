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
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlInterestRate"
  c_interestRate :: CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> Ptr CString -> IO (Ptr CInterestRate)

-- |Standard constructor. QuantLibXL: qlInterestRate
interestRate :: Double -- ^r
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> IO InterestRate
interestRate = $(ffiConstruct 'interestRate) c_interestRate
