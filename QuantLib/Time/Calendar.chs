module QuantLib.Time.Calendar
  (
    JointCalendarRule(..)
  , CalendarConstructor(..)

  , Calendar
  , calendar
  , adjust
  , advance
  , addHoliday
  , advance'
  , businessDaysBetween
  , endOfMonth
  , isBusinessDay
  , isEndOfMonth
  , isHoliday
  , isWeekend
  , removeHoliday
  , holidays
  , BusinessDayConvention(..)
  )
  where

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Time.Date#}(Weekday)
import {-# SOURCE #-} QuantLib.Time.Schedule(TimeUnit)
import QuantLib.Internal.CalendarEnum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}

{#enum BusinessDayConvention {} deriving(Show, Eq)#}

{#fun qlCalendar {`Int',`Int', preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

calendar :: CalendarConstructor -> IO Calendar
calendar (Bespoke n w) = qlBespokeCalendar n w
calendar (Joint2 c1 c2 r) = qlJointCalendar2 c1 c2 r
calendar (Joint3 c1 c2 c3 r) = qlJointCalendar3 c1 c2 c3 r
calendar (Joint4 c1 c2 c3 c4 r) = qlJointCalendar4 c1 c2 c3 c4 r
calendar x = uncurry qlCalendar $ mapCalendar x

-- |Adjusts a non-business day to the appropriate near business day with respect to the given convention
{#fun qlCalendarAdjust as adjust {withCalendar*`Calendar', withDay*`Day',`BusinessDayConvention'}->`Day'toDay#}

-- |Advances the given date of the given number of business days and returns the result
{#fun qlCalendarAdvance as advance {withCalendar*`Calendar', withDay*`Day', fromEnumQuantity`(Int, TimeUnit)'&,`BusinessDayConvention',`Bool'}->`Day'toDay#}

-- |Adds a date to the set of holidays for the given calendar.
{#fun qlCalendarAddHoliday as addHoliday {withCalendar*`Calendar', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Advances the given date as specified by the given period and returns the result. The input date is not modified.
{#fun qlCalendarAdvance1 as advance' {withCalendar*`Calendar', withDay*`Day', fromEnumQuantity`Int, TimeUnit'&,`BusinessDayConvention',`Bool', preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Calculates the number of business days between two given dates and returns the result.
{#fun qlCalendarBusinessDaysBetween as businessDaysBetween {withCalendar*`Calendar', withDay*`Day', withDay*`Day',`Bool',`Bool', preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |last business day of the month to which the given date belongs
{#fun qlCalendarEndOfMonth as endOfMonth {withCalendar*`Calendar', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Returns true iff the date is a business day for the given market.
{#fun qlCalendarIsBusinessDay as isBusinessDay {withCalendar*`Calendar', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Returns true iff the date is last business day for the month in given market.
{#fun qlCalendarIsEndOfMonth as isEndOfMonth {withCalendar*`Calendar', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Returns true iff the date is a holiday for the given market.
{#fun qlCalendarIsHoliday as isHoliday {withCalendar*`Calendar', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Returns true iff the weekday is part of the weekend for the given market.
{#fun qlCalendarIsWeekend as isWeekend {withCalendar*`Calendar',`Weekday', preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Removes a date from the set of holidays for the given calendar.
{#fun qlCalendarRemoveHoliday as removeHoliday {withCalendar*`Calendar', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`()'#}

{#fun qlBespokeCalendar {`String', withEnumArray*`[Weekday]'&, preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

{#fun qlJointCalendar3 {withCalendar*`Calendar', withCalendar*`Calendar', withCalendar*`Calendar', fromEnumC`JointCalendarRule', preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

{#fun qlJointCalendar2 {withCalendar*`Calendar', withCalendar*`Calendar', fromEnumC`JointCalendarRule', preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

{#fun qlJointCalendar4 {withCalendar*`Calendar', withCalendar*`Calendar', withCalendar*`Calendar', withCalendar*`Calendar', fromEnumC`JointCalendarRule', preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

-- |Returns the holidays between two dates.
{#fun qlCalendarHolidayList as holidays {withCalendar*`Calendar', withDay*`Day', withDay*`Day',`Bool', preArray-`[Day]'&peekDayArray*, preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
