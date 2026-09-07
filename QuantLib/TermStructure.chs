module QuantLib.TermStructure
  (
    TermStructure
  , GenTermStructure
  , Reference(..)
  , CalendarReference(..)
  , TermPoint(..)
  , TermInterval(..)
  , asTermStructure
  , referenceDate
  , maxDate
  , allowsExtrapolation
  , setExtrapolation
  ) where
import QuantLib.Internal hiding(maxDate)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}

-- |A term-structure reference point. 'ReferenceDate' stays fixed for the object's lifetime;
-- 'SettlementDays' follows the global evaluation date using the supplied calendar.
data Reference
  = ReferenceDate Day
  | SettlementDays Word Calendar
  deriving (Eq, Show)

-- |Reference-point variants for constructors that take a calendar independently in both
-- upstream overloads.
data CalendarReference
  = CalendarReferenceDate Day
  | CalendarSettlementDays Word
  deriving (Eq, Show)

-- |A date or year-fraction coordinate measured from a term structure's reference date.
data TermPoint = DatePoint Day | TimePoint Double
  deriving (Eq, Show)

-- |A same-representation interval. Keeping both endpoints in one constructor prevents mixed
-- date/time intervals that upstream does not accept.
data TermInterval
  = DateInterval Day Day
  | TimeInterval Double Double
  deriving (Eq, Show)

-- |the date at which discount = 1.0 and/or variance = 0.0
{#fun qlTermStructureReferenceDate as referenceDate{withTermStructure*`GenTermStructure t',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |the latest date for which the curve can return values
{#fun qlTermStructureMaxDate as maxDate{withTermStructure*`GenTermStructure t',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Whether calls beyond the term structure's maximum date are allowed by default.
{#fun qlTermStructureAllowsExtrapolation as allowsExtrapolation{withTermStructure*`GenTermStructure t'}->`Bool'#}

-- |Enable or disable default extrapolation for any term structure.
{#fun qlTermStructureSetExtrapolation as setExtrapolation{withTermStructure*`GenTermStructure t',`Bool'}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
