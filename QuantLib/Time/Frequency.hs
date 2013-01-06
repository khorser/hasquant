{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.Frequency
  (
    Frequency(..)
  )

where

import Data.Typeable(Typeable)

data Frequency = NoFrequency | Annual | Semiannual | EveryFourthMonth
  | Quarterly | Bimonthly | Monthly | Biweekly | EveryFourthWeek | Weekly
  | Daily | Once | OtherFrequency
 deriving (Show, Eq, Enum, Typeable)
