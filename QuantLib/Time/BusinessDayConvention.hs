module QuantLib.Time.BusinessDayConvention
  (
    BusinessDayConvention(..)
  )
where

data BusinessDayConvention = Following | ModifiedFollowing | Preceding | ModifiedPreceding | Unadjusted deriving Show
