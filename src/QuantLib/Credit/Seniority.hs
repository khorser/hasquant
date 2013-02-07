module QuantLib.Credit.Seniority
  (
    Seniority(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Seniority

-- |Seniority of a bond.
-- They are also ISDA tier/seniorities used for CDS conventional spreads.
data Seniority = SecDom | SnrFor | SubLT2 | JrSubT2 | PrefT1 | NoSeniority
  | SeniorSec | SeniorUnSec | SubTier1 | SubUpperTier2 | SubLoweTier2
  deriving (Show, Eq, Enum)
