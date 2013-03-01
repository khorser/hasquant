module QuantLib.Compounding
  (
    Compounding(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Compounding

-- |Interest rate coumpounding rule
data Compounding = Simple -- ^$ 1+rt $
  | Compounded -- ^$ (1+r)^t $
  | Continuous -- ^$ e^{rt} $
  | SimpleThenCompounded -- ^Simple up to the first period then Compounded
  deriving (Show, Eq, Enum)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
