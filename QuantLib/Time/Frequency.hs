{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.Frequency
  (
    Frequency(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Frequency

data Frequency = NoFrequency | Annual | Semiannual | EveryFourthMonth
  | Quarterly | Bimonthly | Monthly | Biweekly | EveryFourthWeek | Weekly
  | Daily | Once | OtherFrequency
 deriving (Show, Eq, Enum, Typeable, Bounded)
