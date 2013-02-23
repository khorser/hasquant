module QuantLib.Credit.ProtectionSide
  (
    ProtectionSide(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum ProtectionSide

data ProtectionSide = Buyer | Seller
  deriving (Show, Eq, Enum)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
