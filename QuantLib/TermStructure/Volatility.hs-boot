module QuantLib.TermStructure.Volatility
  (
    BlackVolTermStructure
  )
    where

import QuantLib.Internal(ForeignObject(..))

import Foreign.ForeignPtr(ForeignPtr)

newtype BlackVolTermStructure = BlackVolTermStructure (ForeignPtr BlackVolTermStructure)
instance ForeignObject BlackVolTermStructure

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
