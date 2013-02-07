module QuantLib.PositionType
  (
    PositionType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum PositionType

data PositionType = Long | Short deriving (Show, Eq, Enum)
