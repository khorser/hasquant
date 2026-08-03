module QuantLib.Time.Schedule
  (
    DayCounterConstructor(..)
  , DayCounter
  , dayCounter
  , days
  , years

  , Schedule
  , schedule
  , fromDates
  , until
  , dates
  , DateGenerationRule(..)

  , fromFrequency
  , toFrequency
  , parse
  , add
  , divide
  , lessThan
  , normalize
  , TimeUnit(..)
  , Frequency(..)
  ) where
import Prelude hiding(until)

import QuantLib.Time.Date
import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum(TimeUnit(..))
import QuantLib.Internal.CalendarEnum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum DateGenerationRule{} deriving(Show, Eq)#}
{#enum Frequency{} deriving(Show, Eq, Bounded)#}

{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *Schedule foreign -> CSchedule nocode#}

{#fun qlDayCounter{`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}
{#fun qlDayCounterBusiness252{withCalendar*`Calendar',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}
{#fun qlDayCounterActualActualBond as actualActualBond'{withSchedule*`Schedule',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}
{#fun qlDayCounterActualActualISMA as actualActualISMA'{withSchedule*`Schedule',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}

dayCounter :: DayCounterConstructor -> IO DayCounter
dayCounter (Business252 x) = qlDayCounterBusiness252 x
dayCounter (ActualActualBond' sched) = actualActualBond' sched
dayCounter (ActualActualISMA' sched) = actualActualISMA' sched
dayCounter x = uncurry qlDayCounter $ mapDayCounter x

-- |Returns the number of days between two dates.
{#fun qlDayCounterDayCount as days{withDayCounter*`DayCounter',withDay*`Day',withDay*`Day'}->`Int'#}

-- |Returns the period between two dates as a fraction of year.
{#fun qlDayCounterYearFraction as years{withDayCounter*`DayCounter',withDay*`Day',withDay*`Day',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSchedule as schedule{withMaybeDay*`Maybe Day' -- ^effectiveDate
  ,withDay*`Day' -- ^terminationDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,withCalendar*`Calendar' -- ^calendar
  ,`BusinessDayConvention' -- ^convention
  ,`BusinessDayConvention' -- ^terminationDateConvention
  ,`DateGenerationRule' -- ^rule
  ,`Bool' -- ^endOfMonth
  ,withMaybeDay*`Maybe Day' -- ^firstDate
  ,withMaybeDay*`Maybe Day' -- ^nextToLastDate
  ,preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}

-- TODO add other parameters, provide a more user-friendly way to build schedules
{#fun qlSchedule1 as fromDates{withDayArray*`[Day]'&,withCalendar*`Calendar',`BusinessDayConvention',preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}
-- |truncated schedule
-- TODO Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
{#fun qlScheduleUntil as until{withSchedule*`Schedule',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}
-- |returns the dates for the given Schedule object
{#fun qlScheduleDates as dates{withSchedule*`Schedule',preArray-`[Day]'&peekDayArray*}->`()'#}
-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
{#fun qlPeriodFromFrequency1 as fromFrequency{`Frequency',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Word'fromIntegral#}
-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
{#fun qlPeriodToFrequency1 as toFrequency{fromEnumQuantity`Word,TimeUnit'&,preErrorCheck-`String'errorCheck*-}->`Frequency'#}
{#fun qlPeriodParserParse1 as parse{`String',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlPeriodAdd1 as addPeriods{fromEnumQuantity`Int,TimeUnit'&,fromEnumQuantity`Int,TimeUnit'&,preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

add :: (Int, TimeUnit) -> (Int, TimeUnit) -> IO (Int, TimeUnit)
add = addPeriods

{#fun qlPeriodDivide1 as divide{fromEnumQuantity`Int,TimeUnit'&,`Int',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}
-- less than
{#fun qlPeriodsLT1 as lessThan{fromEnumQuantity`Int,TimeUnit'&,fromEnumQuantity`Int,TimeUnit'&,preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlPeriodNormalize1 as normalize{fromEnumQuantity`Int,TimeUnit'&,preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
