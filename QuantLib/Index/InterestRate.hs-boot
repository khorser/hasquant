module QuantLib.Index.InterestRate
  (
    InterestRateIndex
  , IborIndex
  , SwapIndex
  )
  where

import QuantLib.Internal(ForeignObject(..))

import Foreign.ForeignPtr(ForeignPtr)

newtype InterestRateIndex = InterestRateIndex (ForeignPtr InterestRateIndex)
instance ForeignObject InterestRateIndex

newtype IborIndex = IborIndex (ForeignPtr IborIndex)
instance ForeignObject IborIndex

newtype SwapIndex = SwapIndex (ForeignPtr SwapIndex)
instance ForeignObject SwapIndex

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
