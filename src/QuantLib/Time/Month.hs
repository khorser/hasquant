module QuantLib.Time.Month
  (
    Month(..)
  )
where

import QuantLib.Internal.Enum

instance QLEnum Month

data Month = January | February | March | April | May | June | July | August
  | September | October | November | December
  deriving (Show, Eq, Enum)
