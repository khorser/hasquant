module QuantLib.Date
  (
    minDate
  , maxDate
  , isLeap
  )
where

import Data.Time.Calendar
import QuantLib.Internal

-- |returns the earliest date allowed in QuantLib (qlDateMinDate)
minDate :: Day
minDate = fromQlSerialNumber c_minDateSerialNumber

-- |returns the latest date allowed in QuantLib (qlDateMaxDate)
maxDate :: Day
maxDate = fromQlSerialNumber c_maxDateSerialNumber

year :: Day -> Integer
year x = y where (y, _, _) = toGregorian x

-- |returns TRUE if a year is leap
isLeap :: [Day] -> [Bool]
isLeap = map (isLeapYear . year)
