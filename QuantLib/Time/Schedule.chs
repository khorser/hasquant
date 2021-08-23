module QuantLib.Time.Schedule
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
  )

where

import Prelude hiding(until)
import Control.Exception(throwIO)

import QuantLib.Type
import QuantLib.Time.Date
import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
import QuantLib.Internal.Calendar

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *DayCounter foreign finalizer qlFreeDayCounter newtype#}
instance ForeignObject DayCounter where
  withObject = withDayCounter
  constructor = DayCounter
  finalizer = qlFreeDayCounter
instance Show DayCounter where show = qlDayCounterName
instance Eq DayCounter where x == y = show x == show y
  
{#fun pure qlDayCounterName {`DayCounter'} -> `String' peekDynString*#}

{#enum ActualActualConvention {} add prefix = "ActualActual" deriving(Show, Eq)#}
{#enum Thirty360Convention {} add prefix = "Thirty360" deriving(Show, Eq)#}
{#enum Actual365FixedConvention {} add prefix = "Actual365Fixed" deriving(Show, Eq)#}

{#enum DateGenerationRule {} deriving(Show, Eq)#}

{#enum DayCounterType {} add prefix = "DayCounter" deriving(Show, Eq)#}

data DayCounterConstructor = 
  Actual360
  | Actual364
  | Actual365Fixed Actual365FixedConvention
  | ActualActual ActualActualConvention -- TODO add the second (Schedule) argument
  | Business252 Calendar
  | One
  | Simple
  | Thirty360 Thirty360Convention
  | Thirty365
 deriving (Show, Eq)

dayCounterType :: DayCounterConstructor -> IO DayCounterType
dayCounterType Actual360 = return DayCounterActual360
dayCounterType Actual364 = return DayCounterActual364
dayCounterType (Actual365Fixed _) = return DayCounterActual365Fixed
dayCounterType (ActualActual _) = return DayCounterActualActual
dayCounterType One = return DayCounterOneDayCounter
dayCounterType Simple = return DayCounterSimpleDayCounter
dayCounterType (Thirty360 _) = return DayCounterThirty360
dayCounterType Thirty365 = return DayCounterThirty365
dayCounterType x = throwIO $ EnumConversion $ "No type for Day Counter " ++ show x

convention :: DayCounterConstructor -> Int
convention (Actual365Fixed x) = fromEnum x
convention (ActualActual x) = fromEnum x
convention (Thirty360 x) = fromEnum x
convention _ = {#const NO_ENUM#}

{#fun qlDayCounter {`DayCounterType', `Int', preErrorCheck- `String' errorCheck*-} -> `DayCounter'#}

{#fun qlDayCounterBusiness252 {`Calendar', preErrorCheck- `String' errorCheck*-}-> `DayCounter'#}

dayCounter :: DayCounterConstructor -> IO DayCounter
dayCounter (Business252 x) = qlDayCounterBusiness252 x
dayCounter x = dayCounterType x >>= flip qlDayCounter (convention x)

-- |Returns the number of days between two dates.
{#fun qlDayCounterDayCount as days {`DayCounter', withDay* `Day', withDay* `Day'} -> `Int'#}

-- |Returns the period between two dates as a fraction of year.
{#fun qlDayCounterYearFraction as years {`DayCounter', withDay* `Day', withDay* `Day', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#pointer *Schedule foreign finalizer qlFreeSchedule newtype#}
instance ForeignObject Schedule where
  withObject = withSchedule
  constructor = Schedule
  finalizer = qlFreeSchedule

{#fun qlSchedule as schedule {withMaybeDay* `Maybe Day', withDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, withObject *`Calendar',
  `BusinessDayConvention', `BusinessDayConvention', `DateGenerationRule',
  `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Schedule'#}

-- TODO add other parameters, provide a more user-friendly way to build schedules
{#fun qlSchedule1 as fromDates {withDayArray* `[Day]'&, `Calendar', `BusinessDayConvention', preErrorCheck- `String' errorCheck*-} -> `Schedule'#}

-- |truncated schedule
-- XXX Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
{#fun qlScheduleUntil as until {`Schedule', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Schedule'#}

-- |returns the dates for the given Schedule object
{#fun qlScheduleDates as dates {`Schedule', preArray- `[Day]'& peekDayArray*} -> `()'#}

{#enum TimeUnit {} deriving(Show, Eq, Bounded)#}

{#enum Frequency {} deriving(Show, Eq, Bounded)#}

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
{#fun qlPeriodFromFrequency1 as fromFrequency {`Frequency', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
{#fun qlPeriodToFrequency1 as toFrequency {fromEnumQuantity `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Frequency'#}

{#fun qlPeriodParserParse1 as parse {`String', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlPeriodAdd1 as addPeriods {fromEnumQuantity `Int, TimeUnit'&, fromEnumQuantity `Int, TimeUnit'&, preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#} 

add :: (Int, TimeUnit) -> (Int, TimeUnit) -> IO (Int, TimeUnit)
add = addPeriods

{#fun qlPeriodDivide1 as divide {fromEnumQuantity `Int, TimeUnit'&, `Int', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- less than
{#fun qlPeriodsLT1 as lessThan {fromEnumQuantity `Int, TimeUnit'&, fromEnumQuantity `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Bool'#}

{#fun qlPeriodNormalize1 as normalize {fromEnumQuantity `Int, TimeUnit'&, preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
