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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
