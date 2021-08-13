module QuantLib.InterestRateIndex
  (
    InterestRateIndex
  , BMAIndex
  , OvernightIndex
  , IborIndex

  , addFixing
  , bmaIndex

  , fixingSchedule
  , forecastFixing
  , fixingCalendar
  , currency
  , dayCounter
  , fixingDays
  , tenor
  )
  where

import QuantLib.Internal
import Foreign.ForeignPtr(newForeignPtr)
import Control.Monad((>=>))
{#import QuantLib.YieldTermStructure#}
{#import QuantLib.Schedule#}(Schedule(..), DayCounter(..))
{#import QuantLib.Currency#}(Currency(..))
{#import QuantLib.Calendar#}(Calendar)
{#import QuantLib.Period#}(TimeUnit)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlIndex as Index foreign finalizer qlFreeIndex newtype#}

instance ForeignObject Index where
  withObject = withIndex
  peekObject = newForeignPtr qlFreeIndex >=> return . Index

{#pointer *QlInterestRateIndex as InterestRateIndex foreign finalizer qlFreeInterestRateIndex newtype#}

instance ForeignObject InterestRateIndex where
  withObject = withInterestRateIndex
  peekObject = newForeignPtr qlFreeInterestRateIndex >=> return . InterestRateIndex

{#pointer *QlBMAIndex as BMAIndex foreign finalizer qlFreeBMAIndex newtype#}

instance ForeignObject BMAIndex where
  withObject = withBMAIndex
  peekObject = newForeignPtr qlFreeBMAIndex >=> return . BMAIndex

{#pointer *QlOvernightIndex as OvernightIndex foreign finalizer qlFreeOvernightIndex newtype#}

instance ForeignObject OvernightIndex where
  withObject = withOvernightIndex
  peekObject = newForeignPtr qlFreeOvernightIndex >=> return . OvernightIndex

{#pointer *QlIborIndex as IborIndex foreign finalizer qlFreeIborIndex newtype#}

instance ForeignObject IborIndex where
  withObject = withIborIndex
  peekObject = newForeignPtr qlFreeIborIndex >=> return . IborIndex

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object
{#fun qlIndexAddFixing as addFixing {`Index', fromDay* `Day', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `()'#}

{#fun qlBMAIndex as bmaIndex {withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `BMAIndex' peekObject*#}

-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule {`BMAIndex', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Schedule' peekObject*#}

-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing {`InterestRateIndex', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar {`Index', preErrorCheck- `String' errorCheck*-} -> `Calendar' peekObject*#}

{#fun qlInterestRateIndexCurrency as currency {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `Currency' peekObject*#}

{#fun qlInterestRateIndexDayCounter as dayCounter {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `DayCounter' peekObject*#}

{#fun pure qlInterestRateIndexFixingDays as fixingDays {`InterestRateIndex'} -> `Word' fromIntegral#}

{#fun qlInterestRateIndexTenor as tenor {`InterestRateIndex', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
