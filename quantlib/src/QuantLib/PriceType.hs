module QuantLib.PriceType
  (
    PriceType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum PriceType

-- |Price types.
data PriceType = Bid -- ^Bid price.
  | Ask -- ^Ask price.
  | Last -- ^Last price.
  | Close -- ^Close price.
  | Mid -- ^Mid price, calculated as the arithmetic average of bid and ask prices.
  | MidEquivalent -- ^Mid equivalent price, calculated as a) the arithmetic average of bid and ask prices when both are available; b) either the bid or the ask price if any of them is available; c) the last price; or d) the close price.
  | MidSafe -- ^Safe Mid price, returns the mid price only if both bid and ask are available.
  deriving (Show, Eq, Enum)

data IntervalPriceType = IntervalOpen | IntervalClose | IntervalHigh
  | IntervalLow
  deriving (Show, Eq, Enum)

instance QLEnum IntervalPriceType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
