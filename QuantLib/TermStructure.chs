{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.TermStructure
  (
    TermStructure
  , GenTermStructure
  , asTermStructure
  , referenceDate
  , maxDate
  ) where
import QuantLib.Internal hiding(maxDate)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}

-- |the date at which discount = 1.0 and/or variance = 0.0
{#fun qlTermStructureReferenceDate as referenceDate{withTermStructure*`GenTermStructure a',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlTermStructureMaxDate as maxDate{withTermStructure*`GenTermStructure a',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
