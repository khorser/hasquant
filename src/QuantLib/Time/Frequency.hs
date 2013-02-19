module QuantLib.Time.Frequency
  (
    Frequency(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Frequency

-- |Frequency of events
data Frequency = NoFrequency -- ^null frequency
  | Annual -- ^once a year
  | Semiannual -- ^twice a year
  | EveryFourthMonth -- ^every fourth month
  | Quarterly -- ^every third month
  | Bimonthly -- ^every second month
  | Monthly -- ^once a month
  | Biweekly -- ^every second week
  | EveryFourthWeek -- ^every fourth week
  | Weekly -- ^once a week
  | Daily -- ^once a day
  | Once -- ^only once, e.g., a zero-coupon
  | OtherFrequency -- ^some other unknown frequency
 deriving (Show, Eq, Enum)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
