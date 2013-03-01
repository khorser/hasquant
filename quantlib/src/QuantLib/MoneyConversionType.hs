module QuantLib.MoneyConversionType
  (
    MoneyConversionType(..)
  )
where

import QuantLib.Internal.Enum

data MoneyConversionType = MoneyNoConversion -- ^do not perform conversions
  | MoneyBaseCurrencyConversion -- ^convert both operands to the base currency before converting
  | MoneyAutomatedConversion -- ^return the result in the currency of the first operand
  deriving (Show, Eq, Enum)
instance QLEnum MoneyConversionType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
