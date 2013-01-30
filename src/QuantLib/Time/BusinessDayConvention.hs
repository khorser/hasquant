{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.BusinessDayConvention
  (
    BusinessDayConvention(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum BusinessDayConvention

data BusinessDayConvention = Following | ModifiedFollowing | Preceding
  | ModifiedPreceding | Unadjusted
  deriving (Show, Eq, Enum, Typeable)
