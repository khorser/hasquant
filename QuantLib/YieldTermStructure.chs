module QuantLib.YieldTermStructure
  (
    YieldTermStructure

  , depositRateHelper'
  )
  where

import QuantLib.Internal
{#import QuantLib.Quote #}
import {-# SOURCE #-} QuantLib.InterestRateIndex

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- breaking recursive dependencies with InterestRateIndex module
-- if you put all pointer declarations in a separate module ch2s will not attach finalizers to foreign ptrs
-- created in other modules so we must do something about it
-- on the other hand I don't want to create extra modules to workaround the issue with cyclic dependencies
{#pointer *QlIborIndex as IborIndex foreign finalizer qlFreeIborIndex newtype nocode #}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign finalizer qlFreeYieldTermStructure newtype #}

instance ForeignObject YieldTermStructure where
  withObject = withYieldTermStructure

{#pointer *QlRateHelper as RateHelper foreign finalizer qlFreeRateHelper newtype #}

instance ForeignObject RateHelper where
  withObject = withRateHelper

{#fun qlDepositRateHelper1 as depositRateHelper' {withObject* `Quote', withObject* `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
