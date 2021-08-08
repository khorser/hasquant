module QuantLib.Schedule
  (
    ActualActualConvention(..)
  , Thirty360Convention(..)
  , Actual365FixedConvention(..)
  , DayCounterConstructor(..)

  , DayCounter
  , dayCounter
  , days
  , years

  , Schedule
  , schedule
  , fromDates
  , until
  , dates
  )

where

import Prelude hiding(until)

import QuantLib.Type
import QuantLib.Date
import QuantLib.Utility
import QuantLib.Period(TimeUnit)
{#import QuantLib.Calendar #}(Calendar)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *DayCounter foreign finalizer qlFreeDayCounter newtype #}

instance ForeignObject DayCounter where
  withObject = withDayCounter
  
{#fun pure qlDayCounterName {`DayCounter'} -> `String' peekDynString* #}

instance Show DayCounter where
  show = qlDayCounterName

{#enum ActualActualConvention {} deriving(Show, Eq, Bounded) #}
{#enum Thirty360Convention {} deriving(Show, Eq, Bounded) #}
{#enum Actual365FixedConvention {} deriving(Show, Eq, Bounded) #}

{#enum DayCounterType {} deriving(Show, Eq, Bounded) #}

data DayCounterConstructor = 
  Actual360
  | Actual364
  | Actual365Fixed Actual365FixedConvention
  | ActualActual ActualActualConvention -- TODO add the second (Schedule) argument
  | Business252 Calendar
  | OneDayCounter
  | SimpleDayCounter | Thirty360 Thirty360Convention
  | Thirty365
 deriving (Show, Eq)

dayCounterType :: DayCounterConstructor -> DayCounterType
dayCounterType Actual360 = DayCounterActual360
dayCounterType Actual364 = DayCounterActual364
dayCounterType (Actual365Fixed _) = DayCounterActual365Fixed
dayCounterType (ActualActual _) = DayCounterActualActual
dayCounterType OneDayCounter = DayCounterOneDayCounter
dayCounterType SimpleDayCounter = DayCounterSimpleDayCounter
dayCounterType (Thirty360 _) = DayCounterThirty360
dayCounterType Thirty365 = DayCounterThirty365
dayCounterType x = error $ "Internal error: no type for Day Counter " ++ (show x)

convention :: DayCounterConstructor -> Int
convention (Actual365Fixed x) = fromEnum x
convention (ActualActual x) = fromEnum x
convention (Thirty360 x) = fromEnum x
convention _ = {#const NO_ENUM #}

{#fun qlDayCounter {`DayCounterType', `Int', preErrorCheck- `String' errorCheck*-} -> `DayCounter' #}

{#fun qlDayCounterBusiness252 {withObject* `Calendar', preErrorCheck- `String' errorCheck*-}-> `DayCounter' #}

dayCounter :: DayCounterConstructor -> IO DayCounter
dayCounter (Business252 x) = qlDayCounterBusiness252 x
dayCounter x = qlDayCounter (dayCounterType x) (convention x)

-- |Returns the number of days between two dates.
{#fun qlDayCounterDayCount as days {`DayCounter', fromDay* `Day', fromDay* `Day'} -> `Int' #}

-- |Returns the period between two dates as a fraction of year.
{#fun qlDayCounterYearFraction as years {`DayCounter', fromDay* `Day', fromDay* `Day', fromMaybeDay* `Maybe Day', fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double' #}

{#pointer *Schedule foreign finalizer qlFreeSchedule newtype #}

instance ForeignObject Schedule where
  withObject = withSchedule

{#fun qlSchedule as schedule {fromMaybeDay* `Maybe Day', fromDay* `Day', fromEnumQuantity `(Int, TimeUnit)'&, withObject *`Calendar',
  `BusinessDayConvention', `BusinessDayConvention', `DateGenerationRule',
  `Bool', fromMaybeDay* `Maybe Day', fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Schedule' #}

-- TODO add other parameters, provide a more user-friendly way to build schedules
{#fun qlSchedule1 as fromDates {withDayArray* `[Day]'&, withObject* `Calendar', `BusinessDayConvention', preErrorCheck- `String' errorCheck*-} -> `Schedule' #}

-- |truncated schedule
-- XXX Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
{#fun qlScheduleUntil as until {`Schedule', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Schedule' #}

-- |returns the dates for the given Schedule object
{#fun qlScheduleDates as dates {`Schedule', preArray- `[Day]'& peekDayArray*} -> `()' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
