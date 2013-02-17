-- |rounding methods
-- The rounding methods follow the OMG specification available at ftp://ftp.omg.org/pub/docs/formal/00-06-29.pdf /Warning/ the names of the Floor and Ceiling methods might be misleading. Check the provided reference.
module QuantLib.Math.RoundingType
  (
    RoundingType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum RoundingType

data RoundingType = None -- ^do not round: return the number unmodified
  | Up -- ^the first decimal place past the precision will be rounded up. This differs from the OMG rule which rounds up only if the decimal to be rounded is greater than or equal to the rounding digit
  | Down -- ^all decimal places past the precision will be truncated
  | Closest -- ^the first decimal place past the precision will be rounded up if greater than or equal to the rounding digit; this corresponds to the OMG round-up rule. When the rounding digit is 5, the result will be the one closest to the original number, hence the name.
  | Floor -- ^positive numbers will be rounded up and negative numbers will be rounded down using the OMG round up and round down rules
  | Ceiling -- ^positive numbers will be rounded down and negative numbers will be rounded up using the OMG round up and round down rules
  deriving (Show, Eq, Enum)
