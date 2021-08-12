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
{#import QuantLib.YieldTermStructure#}
{#import QuantLib.Schedule#}(Schedule(..), DayCounter(..))
{#import QuantLib.Currency#}(Currency(..))
{#import QuantLib.Calendar#}(Calendar(..))
{#import QuantLib.Period#}(TimeUnit)
import Foreign.Ptr
import Foreign.ForeignPtr
import Control.Monad

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlIndex as Index foreign finalizer qlFreeIndex newtype#}

instance ForeignObject Index where
  withObject = withIndex

{#pointer *QlInterestRateIndex as InterestRateIndex foreign finalizer qlFreeInterestRateIndex newtype#}

instance ForeignObject InterestRateIndex where
  withObject = withInterestRateIndex

{#pointer *QlBMAIndex as BMAIndex foreign finalizer qlFreeBMAIndex newtype#}

instance ForeignObject BMAIndex where
  withObject = withBMAIndex

{#pointer *QlOvernightIndex as OvernightIndex foreign finalizer qlFreeOvernightIndex newtype#}

instance ForeignObject OvernightIndex where
  withObject = withOvernightIndex

{#pointer *QlIborIndex as IborIndex foreign finalizer qlFreeIborIndex newtype#}

instance ForeignObject IborIndex where
  withObject = withIborIndex

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object
{#fun qlIndexAddFixing as addFixing {`Index', fromDay* `Day', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `()'#}

{#fun qlBMAIndex as bmaIndex {withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `BMAIndex'#}

-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule {`BMAIndex', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Schedule'#}

-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing {`InterestRateIndex', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

peekCalendar :: Ptr Calendar -> IO Calendar
peekCalendar = newForeignPtr_ >=> return . Calendar

-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar {`Index', preErrorCheck- `String' errorCheck*-} -> `Calendar' peekCalendar*#}

{#fun qlInterestRateIndexCurrency as currency {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `Currency'#}

{#fun qlInterestRateIndexDayCounter as dayCounter {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `DayCounter'#}

{#fun pure qlInterestRateIndexFixingDays as fixingDays {`InterestRateIndex'} -> `Word' fromIntegral#}

{#fun qlInterestRateIndexTenor as tenor {`InterestRateIndex', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
