module QuantLib.TermStructure.Volatility
  (
    BlackVolTermStructure
  , OptionletVolatilityStructure
  , SwaptionVolatilityStructure
  )
    where

import QuantLib.Internal(ForeignObject(..))

import Foreign.ForeignPtr(ForeignPtr)

newtype BlackVolTermStructure = BlackVolTermStructure (ForeignPtr BlackVolTermStructure)
instance ForeignObject BlackVolTermStructure

newtype SwaptionVolatilityStructure = SwaptionVolatilityStructure (ForeignPtr SwaptionVolatilityStructure)
instance ForeignObject SwaptionVolatilityStructure

newtype OptionletVolatilityStructure = OptionletVolatilityStructure (ForeignPtr OptionletVolatilityStructure)
instance ForeignObject OptionletVolatilityStructure

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
