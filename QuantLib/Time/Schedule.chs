-- DayCounterConstructor is declared in QuantLib.Internal.CalendarEnum, but its Read instance
-- needs `calendar` (QuantLib.Time.Calendar), and CalendarEnum -> Schedule -> CalendarEnum
-- would be a cycle if the instance lived there instead -- see deriveReadPlain's comment in
-- Internal/Syntax.hs. Deliberate, not a stray orphan.
{-# OPTIONS_GHC -Wno-orphans #-}
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
import QuantLib.Internal.Type
import QuantLib.Internal.Common
import QuantLib.Internal.CalendarEnum
import QuantLib.Time.Calendar (calendar)
import System.IO.Unsafe(unsafePerformIO)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum DateGenerationRule{} deriving(Show, Eq, Read)#}
{#enum Frequency{} deriving(Show, Eq, Read, Bounded)#}

{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *Schedule foreign -> CSchedule nocode#}
{#pointer *Calendar foreign -> CCalendar nocode#}

-- |Constructs a day counter of the given type and (where applicable) convention.
{#fun qlDayCounter{`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}

-- |Business/252 day count convention, counting business days per the given calendar.
{#fun qlDayCounterBusiness252{withCalendar*`Calendar',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}

-- |Actual/Actual (Bond) day counter, using the given schedule's reference periods.
{#fun qlDayCounterActualActualBond as actualActualBond'{withSchedule*`Schedule',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}

-- |Actual/Actual (ISMA) day counter, using the given schedule's reference periods.
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

-- |Builds a payment schedule by generating dates between effective and termination dates according to the given tenor and rule.
{#fun qlSchedule as schedule{withMaybeDay*`Maybe Day' -- ^effectiveDate
  ,withDay*`Day' -- ^terminationDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,fromEnumC`BusinessDayConvention' -- ^terminationDateConvention
  ,`DateGenerationRule' -- ^rule
  ,`Bool' -- ^endOfMonth
  ,withMaybeDay*`Maybe Day' -- ^firstDate
  ,withMaybeDay*`Maybe Day' -- ^nextToLastDate
  ,preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}

-- |Builds a payment schedule from an explicit list of dates, without checking them for plausibility.
{#fun qlSchedule1 as fromDates{withDayArray*`[Day]'&
  ,withCalendar*`Calendar' -- ^calendar
  ,fromEnumC`BusinessDayConvention' -- ^convention
  ,fromMaybeEnum`Maybe BusinessDayConvention' -- ^terminationDateConvention
  ,fromMaybeEnumQuantity`Maybe (Word, TimeUnit)'& -- ^tenor
  ,fromMaybeEnum`Maybe DateGenerationRule' -- ^rule
  ,fromMaybeBool`Maybe Bool' -- ^endOfMonth
  ,preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}

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

-- |Parses a period from its short-format string representation (e.g. \"6M\").
{#fun qlPeriodParserParse1 as parse{`String',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

{#fun qlPeriodAdd1 as addPeriods{fromEnumQuantity`Int,TimeUnit'&,fromEnumQuantity`Int,TimeUnit'&,preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |Adds two periods together.
add :: (Int, TimeUnit) -> (Int, TimeUnit) -> IO (Int, TimeUnit)
add = addPeriods

-- |Divides a period's length by an integer divisor.
{#fun qlPeriodDivide1 as divide{fromEnumQuantity`Int,TimeUnit'&,`Int',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |Compares two periods, converting to a common time unit as needed.
{#fun qlPeriodsLT1 as lessThan{fromEnumQuantity`Int,TimeUnit'&,fromEnumQuantity`Int,TimeUnit'&,preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Normalizes a period to the coarsest equivalent time unit (e.g. 12M to 1Y).
{#fun qlPeriodNormalize1 as normalize{fromEnumQuantity`Int,TimeUnit'&,preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- Same NOINLINE reasoning as QuantLib.Time.Calendar's own unsafeCalendar (which this can't
-- reuse: DayCounterConstructor's Read instance needs its own top-level NOINLINE binding, not
-- a shared one, so GHC can't float/duplicate-inline this call site independently of that
-- one's).
unsafeCalendar :: CalendarConstructor -> Calendar
unsafeCalendar = unsafePerformIO . calendar
{-# NOINLINE unsafeCalendar #-}

-- Hand-written, not `deriving`/TH-spliced: DayCounterConstructor's Business252 case carries a
-- live Calendar field (see QuantLib.Internal.Syntax.deriveReadPlain's comment for why the
-- generated part is spliced back in CalendarEnum.chs instead of here).
-- ActualActualBond'/ActualActualISMA' carry a Schedule, which has no small enum-shaped
-- readable proxy at all -- they get no alternative here, so parsing their name deliberately
-- falls through to the standard Read "no parse" failure.
instance Read DayCounterConstructor where
  readsPrec d r = readDayCounterConstructorPlain d r
    ++ readParen (d > 10) (\r' ->
         [ (Business252 c, s1)
         | ("Business252", s0) <- lex r'
         , (p, s1) <- readsPrec 11 s0, let c = unsafeCalendar p
         ]) r

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
