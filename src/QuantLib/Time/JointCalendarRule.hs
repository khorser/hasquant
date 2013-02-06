{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.JointCalendarRule
  (
    JointCalendarRule(..)
  )
where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

-- |rules for joining calendars
data JointCalendarRule = 
  JoinHolidays -- ^A date is a holiday for the joint calendar if it is a holiday for any of the given calendars
  | JoinBusinessDays -- ^A date is a business day for the joint calendar if it is a business day for any of the given calendars
  deriving (Show, Eq, Enum, Typeable, Bounded)

instance QLEnum JointCalendarRule
