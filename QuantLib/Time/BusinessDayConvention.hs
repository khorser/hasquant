{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.BusinessDayConvention
  (
    BusinessDayConvention(..)
  )

where

import Data.Typeable(Typeable)

data BusinessDayConvention = Following | ModifiedFollowing | Preceding
  | ModifiedPreceding | Unadjusted
  deriving (Show, Eq, Enum, Typeable)
