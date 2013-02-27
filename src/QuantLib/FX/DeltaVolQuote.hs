module QuantLib.FX.DeltaVolQuote
  (
    AtmType(..)
  , DeltaType(..)
  )
where

import QuantLib.Internal.Enum

data AtmType = AtmNull | AtmSpot | AtmFwd | AtmDeltaNeutral
  | AtmVegaMax | AtmGammaMax | AtmPutCall50
  deriving (Show, Eq, Enum)
instance QLEnum AtmType

data DeltaType = QuoteSpot | QuoteFwd | QuotePaSpot | QuotePaFwd
  deriving (Show, Eq, Enum)
instance QLEnum DeltaType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
