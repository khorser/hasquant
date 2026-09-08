module QuantLib.Time.Date
  (
    -- * Date values and fields
    Day
  , minDate
  , maxDate
  , today
  , isLeap
  , year
  , month
  , weekday

    -- * Calendar enums
  , Month(..)
  , Weekday(..)
  , ImmMonth(..)

    -- * Month constructors
  , january
  , february
  , march
  , april
  , may
  , june
  , july
  , august
  , september
  , october
  , november
  , december

    -- * Date queries and arithmetic
  , dayOfYear

  , endOfMonth
  , isEndOfMonth
  , nextWeekday
  , nthWeekday

    -- * IMM dates and codes
  , immCode
  , immDate
  , isImmCode
  , isImmDate
  , nextImmCode
  , nextImmCodeFromCode
  , nextImmDate
  , nextImmDateFromCode

  , addPeriod

    -- * ECB maintenance dates
  , addEcbDate
  , ecbCode
  , ecbDateFromCode
  , ecbDate
  , isEcbCode
  , isEcbDate
  , knownEcbDates
  , nextEcbCodeFromCode
  , nextEcbCode
  , nextEcbDateFromCode
  , nextEcbDate
  , nextEcbDatesFromCode
  , nextEcbDates
  , removeEcbDate
  ) where
import Data.Time.Calendar(toGregorian, isLeapYear, fromGregorian)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)

import QuantLib.Internal
import QuantLib.Internal.Common

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"

{#enum Month{} deriving(Show, Eq, Read, Bounded, Ord)#}
{#enum Weekday{} deriving(Show, Eq, Read, Bounded, Ord)#}
{#enum ImmMonth{} deriving(Show, Eq, Read, Bounded, Ord)#}

year :: Day -> Int
year x = fromIntegral y where (y, _, _) = toGregorian x

-- |returns TRUE if the given date's year is leap
isLeap :: Day -> Bool
isLeap = isLeapYear . fromIntegral . year

month :: Day -> Month
month x = let (_, m, _) = toGregorian x in toEnum m

-- |helper function that is convenient for use as an infix operator
january :: Int -> Int -> Day
january d y = fromGregorian (fromIntegral y) 1 d
february :: Int -> Int -> Day
february d y = fromGregorian (fromIntegral y) 2 d
march :: Int -> Int -> Day
march d y = fromGregorian (fromIntegral y) 3 d
april :: Int -> Int -> Day
april d y = fromGregorian (fromIntegral y) 4 d
may :: Int -> Int -> Day
may d y = fromGregorian (fromIntegral y) 5 d
june :: Int -> Int -> Day
june d y = fromGregorian (fromIntegral y) 6 d
july :: Int -> Int -> Day
july d y = fromGregorian (fromIntegral y) 7 d
august :: Int -> Int -> Day
august d y = fromGregorian (fromIntegral y) 8 d
september :: Int -> Int -> Day
september d y = fromGregorian (fromIntegral y) 9 d
october :: Int -> Int -> Day
october d y = fromGregorian (fromIntegral y) 10 d
november :: Int -> Int -> Day
november d y = fromGregorian (fromIntegral y) 11 d
december :: Int -> Int -> Day
december d y = fromGregorian (fromIntegral y) 12 d

-- |the day of the week for the given date
{#fun qlWeekday as weekday{withDay*`Day'}->`Weekday'#}

today :: IO Day
today = do
  now <- getCurrentTime
  tz <- getTimeZone now
  return $ localDay $ utcToLocalTime tz now

-- |One-based (Jan 1st = 1)
{#fun qlDateDayOfYear as dayOfYear{withDay*`Day'}->`Int'#}

-- |last day of the month to which the given date belongs
{#fun qlDateEndOfMonth as endOfMonth{withDay*`Day'}->`Day'toDay#}

-- |whether a date is the last day of its month
{#fun qlDateIsEndOfMonth as isEndOfMonth{withDay*`Day'}->`Bool'#}

-- |next given weekday following or equal to the given date
-- E.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002.see http://www.cpearson.com/excel/DateTimeWS.htm
{#fun qlDateNextWeekday as nextWeekday{withDay*`Day',`Weekday'}->`Day'toDay#}

-- |n-th given weekday in the given month and year
-- E.g., the 4th Thursday of March, 1998 was March 26th, 1998.see http://www.cpearson.com/excel/DateTimeWS.htm
-- /Warning/ It raises an exception unless the n-th falls in 1..5
{#fun qlDateNthWeekday as nthWeekday{fromIntegral`Word',`Weekday',`Month',`Int',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |returns the IMM code for the given date (e.g. H3 for March 20th, 2013). /Warning/ It raises an exception if the input date is not an IMM date
{#fun qlIMMCode as immCode{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`String'peekDynString*#}

-- |returns the IMM date for the given IMM code (e.g. March 20th, 2013 for H3). /Warning/ It raises an exception if the input string is not an IMM code
{#fun qlIMMDate as immDate{`String',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |returns whether or not the given string is an IMM code
{#fun pure qlIMMIsIMMcode as isImmCode{`String' -- ^immCode
  ,`Bool' -- ^mainCycle
  }->`Bool'#}

-- |returns whether or not the given date is an IMM date
{#fun qlIMMIsIMMdate as isImmDate{withDay*`Day',`Bool' -- ^mainCycle
  }->`Bool'#}

-- |next IMM code following the given code
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextCode1 as nextImmCodeFromCode{`String',`Bool' -- ^mainCycle
  ,withDay*`Day',preErrorCheck-`String'errorCheck*-}->`String'peekDynString*#}

-- |next IMM code following the given date
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextCode as nextImmCode{withDay*`Day',`Bool' -- ^mainCycle
  }->`String'peekDynString*#}

-- |next IMM date following the given IMM code
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextDate1 as nextImmDateFromCode{`String',`Bool' -- ^mainCycle
  ,withDay*`Day' -- ^referenceDate
  ,preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |next IMM date following the given date
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextDate as nextImmDate{withDay*`Day',`Bool' -- ^mainCycle
  }->`Day'toDay#}

-- |the given date advanced by a period
{#fun qlAddPeriod as addPeriod{withDay*`Day',fromEnumQuantity`Int,TimeUnit'&,preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |adds a date to the set of known ECB maintenance period start dates
{#fun qlECBAddDate as addEcbDate{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |returns the ECB code for the given date (e.g. MAR10 for March xxth, 2010).Warning It raises an exception if the input date is not an ECB date
{#fun qlECBCode as ecbCode{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`String'peekDynString*#}

-- |returns the ECB date for the given ECB code (e.g. March xxth, 2013 for MAR10).WarningIt raises an exception if the input string is not an ECB code
{#fun qlECBDate1 as ecbDateFromCode{`String',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |maintenance period start date in the given month/year
{#fun qlECBDate as ecbDate{`Month',`Int',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |returns whether or not the given string is an ECB code
{#fun qlECBIsECBcode as isEcbCode{`String',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |returns whether or not the given date is a maintenance period start date
{#fun qlECBIsECBdate as isEcbDate{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |the set of known ECB maintenance period start dates
{#fun qlECBKnownDates as knownEcbDates{preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |next ECB code following the given code
{#fun qlECBNextCode1 as nextEcbCodeFromCode{`String',preErrorCheck-`String'errorCheck*-}->`String'#}

-- |next ECB code following the given date
{#fun qlECBNextCode as nextEcbCode{withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`String'#}

-- |next maintenance period start date following the given ECB code
{#fun qlECBNextDate1 as nextEcbDateFromCode{`String',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |next maintenance period start date following the given date
{#fun qlECBNextDate as nextEcbDate{withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |next maintenance period start dates following the given code
{#fun qlECBNextDates1 as nextEcbDatesFromCode{`String',withMaybeDay*`Maybe Day',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |next maintenance period start dates following the given date
{#fun qlECBNextDates as nextEcbDates{withMaybeDay*`Maybe Day',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |removes a date from the set of known ECB maintenance period start dates
{#fun qlECBRemoveDate as removeEcbDate{withDay*`Day',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
