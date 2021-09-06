{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.Index
  (
    Index

  , addFixing
  , fixingCalendar
  , asIndex
  )
  where

import QuantLib.Type
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}

{#pointer *QlIndex as Index foreign finalizer qlFreeIndex newtype#}
instance ForeignObject Index where
  withObject = withIndex
  constructor = Index
  finalizer = qlFreeIndex
instance Show Index where show = qlIndexName

{#fun pure qlIndexName{`Index'}->`String'#}

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given InterestRateIndex object
{#fun qlIndexAddFixing as addFixing{`Index', withDay*`Day',`Double',`Bool', preErrorCheck-`String'errorCheck*-}->`()'#}

-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar{`Index', preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

asIndex :: (a`Derives` Index) => a -> IO Index
asIndex = cast

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
