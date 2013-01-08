{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.InterestRate
  (
    InterestRate
  , interestRate
  , CInterestRate
  )
where

import Foreign.C.Types(CInt(CInt), CDouble(CDouble))
import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Compounding(Compounding)
import QuantLib.Time.DayCounter(DayCounter, CDayCounter)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Internal

data CInterestRate
type InterestRate = Object CInterestRate

foreign import ccall safe "ql.h qlInterestRate"
  c_interestRate :: CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> Ptr CString -> IO (Ptr CInterestRate)
foreign import ccall safe "ql.h &qlFreeInterestRate"
  p_freeInterestRate :: FunPtr (Ptr CInterestRate -> IO ())

instance Finalizable CInterestRate where
  finalize = p_freeInterestRate

-- | (qlInterestRate)
interestRate :: Double -> DayCounter -> Compounding -> Frequency
  -> IO InterestRate
interestRate r dc comp freq =
  withObject dc
  (\c -> construct $ c_interestRate (realToFrac r)
                                    c
                                    (toQlEnum comp)
                                    (toQlEnum freq))
