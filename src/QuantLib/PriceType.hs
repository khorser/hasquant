{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.PriceType
  (
    PriceType(..)
  )

where

import Data.Typeable(Typeable)
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
  deriving (Show, Eq, Enum, Typeable, Bounded)
