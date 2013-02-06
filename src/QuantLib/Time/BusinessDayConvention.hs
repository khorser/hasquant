module QuantLib.Time.BusinessDayConvention
  (
    BusinessDayConvention(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum BusinessDayConvention

-- |Business Day conventions.
-- These conventions specify the algorithm used to adjust a date in case it is not a valid business day
data BusinessDayConvention = Following -- ^Choose the first business day after the given holiday
  | ModifiedFollowing -- ^Choose the first business day after the given holiday unless it belongs to a different month, in which case choose the first business day before the holiday
  | Preceding -- ^Choose the first business day before the given holiday
  | ModifiedPreceding -- ^Choose the first business day before the given holiday unless it belongs to a different month, in which case choose the first business day after the holiday
  | Unadjusted -- ^Do not adjust
  deriving (Show, Eq, Enum)
