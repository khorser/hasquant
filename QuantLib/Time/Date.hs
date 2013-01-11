{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.Date
  (
  -- accessors
    minDate
  , maxDate
  , isLeap
  , isValid
  , Weekday(..)
  , Month(..)
  )
where

import Data.Time.Calendar(toGregorian, isLeapYear)
import Data.Typeable(Typeable)

import QuantLib.Internal

-- |returns the earliest date allowed in QuantLib (qlDateMinDate)
minDate :: Day
minDate = fromQlDate c_minDateSerialNumber

-- |returns the latest date allowed in QuantLib (qlDateMaxDate)
maxDate :: Day
maxDate = fromQlDate c_maxDateSerialNumber

year :: Day -> Integer
year x = y where (y, _, _) = toGregorian x

-- |returns TRUE if a year is leap (qlDateIsLeap), reimplemented in Haskell
isLeap :: Day -> Bool
isLeap = isLeapYear . year

data Weekday = Sunday | Monday | Tuesday | Wednesday | Thursday | Friday
  | Saturday
  | Sun | Mon | Tue | Wed | Thu | Fri | Sat
  deriving (Show, Eq, Enum, Typeable)

data Month = January | February | March | April | May | June | July | August
  | September | October | November | December
  | Jan | Feb | Mar | Apr | Jun | Jul | Aug | Sep | Oct | Nov | Dec
  deriving (Show, Eq, Enum, Typeable)
