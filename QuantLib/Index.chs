module QuantLib.Index
  (
    Index
  , GenIndex

  , addFixing
  , fixingCalendar
  , fixing
  , hasHistoricalFixing
  , isValidFixingDate
  , addFixings
  , clearFixings
  , asIndex
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *QlIndex as Index foreign -> CIndex' nocode#}
-- |stores the historical fixing at the given date; the date must be the actual calendar date of the fixing, not a settlement date
{#fun qlIndexAddFixing as addFixing{withIndex*`GenIndex idx',withDay*`Day',`Double' -- ^fixing
  ,`Bool' -- ^forceOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar{withIndex*`GenIndex idx',preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}
-- |returns the fixing at the given date, forecasting it if not available and /forecastTodaysFixing/ is true
{#fun qlIndexFixing as fixing{withIndex*`GenIndex idx',withDay*`Day',`Bool' -- ^forecastTodaysFixing
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |whether a historical fixing has been stored for the given date
{#fun qlIndexHasHistoricalFixing as hasHistoricalFixing{withIndex*`GenIndex idx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}
-- |whether the given date is a valid fixing date for this index
{#fun qlIndexIsValidFixingDate as isValidFixingDate{withIndex*`GenIndex idx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}
-- |stores historical fixings at the given dates; the date and value lists must have equal length
{#fun qlIndexAddFixings as addFixings{withIndex*`GenIndex idx',withDayArray*`[Day]'&,withDoubleArrayRaw*`[Double]',`Bool' -- ^forceOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |clears all stored historical fixings for this index
{#fun qlIndexClearFixings as clearFixings{withIndex*`GenIndex idx',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
