module QuantLib.Index.InterestRate
  (
    InterestRateIndex
--  , BMAIndex
--  , OvernightIndex
  , IborIndex
  )
  where

import QuantLib.Internal(ForeignObject(..))

import Foreign.ForeignPtr(ForeignPtr)

newtype InterestRateIndex = InterestRateIndex (ForeignPtr InterestRateIndex)

newtype IborIndex = IborIndex (ForeignPtr IborIndex)

instance ForeignObject IborIndex

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
