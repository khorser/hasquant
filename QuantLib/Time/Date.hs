module QuantLib.Time.Date
  (
    minDate
  , maxDate
  , isLeap
  , isValid
  )
where

import Data.Time.Calendar(toGregorian, isLeapYear, Day)

import QuantLib.Internal(fromQlDateSerialNumber,
  c_minDateSerialNumber, c_maxDateSerialNumber, isValid)

-- |returns the earliest date allowed in QuantLib (qlDateMinDate)
minDate :: Day
minDate = fromQlDateSerialNumber c_minDateSerialNumber

-- |returns the latest date allowed in QuantLib (qlDateMaxDate)
maxDate :: Day
maxDate = fromQlDateSerialNumber c_maxDateSerialNumber

year :: Day -> Integer
year x = y where (y, _, _) = toGregorian x

-- |returns TRUE if a year is leap (qlDateIsLeap), reimplemented in Haskell
isLeap :: Day -> Bool
isLeap = isLeapYear . year
