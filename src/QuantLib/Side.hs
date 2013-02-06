module QuantLib.Side
  (
    Side(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Side

data Side = Long | Short deriving (Show, Eq, Enum)
