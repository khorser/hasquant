module QuantLib.Instrument.Swap
  (
    Swap
  , VanillaSwap
  , OvernightIndexedSwap
  )

  where

import QuantLib.Internal(ForeignObject(..))

import Foreign.ForeignPtr(ForeignPtr)

newtype Swap = Swap (ForeignPtr Swap)
instance ForeignObject Swap

newtype VanillaSwap = VanillaSwap (ForeignPtr VanillaSwap)
instance ForeignObject VanillaSwap

newtype OvernightIndexedSwap = OvernightIndexedSwap (ForeignPtr OvernightIndexedSwap)
instance ForeignObject OvernightIndexedSwap

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
