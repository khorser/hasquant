module QuantLib.Index.InterestRate
  (
    InterestRateIndex
  , IborIndex
  , SwapIndex
  , OvernightIborIndex
  , BMAIndex
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

newtype OvernightIborIndex = OvernightIborIndex (ForeignPtr OvernightIborIndex)
instance ForeignObject OvernightIborIndex

newtype BMAIndex = BMAIndex (ForeignPtr BMAIndex)
instance ForeignObject BMAIndex

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
