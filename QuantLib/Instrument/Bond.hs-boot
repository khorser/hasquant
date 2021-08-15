module QuantLib.Instrument.Bond
  (
    Bond
  )

  where

import QuantLib.Internal(ForeignObject(..))

import Foreign.ForeignPtr(ForeignPtr)

newtype Bond = Bond (ForeignPtr Bond)
instance ForeignObject Bond

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
