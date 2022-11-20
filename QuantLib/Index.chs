{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, FlexibleInstances #-}
module QuantLib.Index
  (
    Index
  , GenIndex

  , addFixing
  , fixingCalendar
  , asIndex
  )
  where

import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}

{#pointer *QlIndex as Index foreign -> CIndex' nocode#}

instance Show Index where show = qlIndexName

{#fun pure qlIndexName{withIndex*`GenIndex a'}->`String'#}

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object
{#fun qlIndexAddFixing as addFixing{withIndex*`GenIndex a',withDay*`Day',`Double',`Bool' -- ^forceOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar{withIndex*`GenIndex a',preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
