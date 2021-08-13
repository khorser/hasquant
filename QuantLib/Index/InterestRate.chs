module QuantLib.Index.InterestRate
  (
    InterestRateIndex
  , BMAIndex
  , OvernightIndex
  , IborIndex
  , SwapIndex
  , OvernightIndexedSwapIndex

  , bmaIndex

  , fixingSchedule
  , forecastFixing
  , currency
  , dayCounter
  , fixingDays
  , tenor

  , asIndex
  , bmaIndexAsInterestRateIndex
  , swapIndexAsInterestRateIndex
  , overnightIndexedSwapIndexAsSwapIndex
  , iborIndexAsInterestRateIndex
  , overnightIndexAsIborIndex
  )
  where

import QuantLib.Internal
{#import QuantLib.YieldTermStructure#}
{#import QuantLib.Index#}(Index)
{#import QuantLib.Time.Schedule#}(Schedule, DayCounter)
{#import QuantLib.Currency#}(Currency)
{#import QuantLib.Time.Period#}(TimeUnit)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

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

{#pointer *QlSwapIndex as SwapIndex foreign finalizer qlFreeSwapIndex newtype#}

instance ForeignObject SwapIndex where
  withObject = withSwapIndex
  peekObject = newForeignPtr qlFreeSwapIndex >=> return . SwapIndex

{#pointer *QlOvernightIndexedSwapIndex as OvernightIndexedSwapIndex foreign finalizer qlFreeOvernightIndexedSwapIndex newtype#}

instance ForeignObject OvernightIndexedSwapIndex where
  withObject = withOvernightIndexedSwapIndex
  peekObject = newForeignPtr qlFreeOvernightIndexedSwapIndex >=> return . OvernightIndexedSwapIndex

{#fun qlBMAIndex as bmaIndex {withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `BMAIndex' peekObject*#}

-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule {`BMAIndex', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Schedule' peekObject*#}

-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing {`InterestRateIndex', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlInterestRateIndexCurrency as currency {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `Currency' peekObject*#}

{#fun qlInterestRateIndexDayCounter as dayCounter {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `DayCounter' peekObject*#}

{#fun pure qlInterestRateIndexFixingDays as fixingDays {`InterestRateIndex'} -> `Word' fromIntegral#}

{#fun qlInterestRateIndexTenor as tenor {`InterestRateIndex', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlInterestRateIndexAsIndex as asIndex {`InterestRateIndex'} -> `Index' peekObject*#}

{#fun qlBMAIndexAsInterestRateIndex as bmaIndexAsInterestRateIndex {`BMAIndex'} -> `InterestRateIndex'#}

{#fun qlSwapIndexAsInterestRateIndex as swapIndexAsInterestRateIndex {`SwapIndex'} -> `InterestRateIndex'#}

{#fun qlOvernightIndexedSwapIndexAsSwapIndex as overnightIndexedSwapIndexAsSwapIndex {`OvernightIndexedSwapIndex'} -> `SwapIndex'#}

{#fun qlIborIndexAsInterestRateIndex as iborIndexAsInterestRateIndex {`IborIndex'} -> `InterestRateIndex'#}

{#fun qlOvernightIndexAsIborIndex as overnightIndexAsIborIndex {`OvernightIndex'} -> `IborIndex'#}
-- vim: set ff=unix ts=8 sts=2 sw=2 et:
