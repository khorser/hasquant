module QuantLib.Index
  (
    Index

  , addFixing
  , fixingCalendar
  )
  where

import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(Calendar)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlIndex as Index foreign finalizer qlFreeIndex newtype#}

instance ForeignObject Index where
  withObject = withIndex
  peekObject = newForeignPtr qlFreeIndex >=> return . Index

{#fun pure qlIndexName {`Index'} -> `String'#}

instance Show Index where show = qlIndexName

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object
{#fun qlIndexAddFixing as addFixing {`Index', fromDay* `Day', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `()'#}

-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar {`Index', preErrorCheck- `String' errorCheck*-} -> `Calendar' peekObject*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
