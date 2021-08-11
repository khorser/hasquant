module QuantLib.YieldTermStructure
  (
    YieldTermStructure
  )
  where

import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlYieldTermStructure as YieldTermStructure foreign finalizer qlFreeYieldTermStructure newtype #}

instance ForeignObject YieldTermStructure where
  withObject = withYieldTermStructure

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
