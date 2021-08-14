module QuantLib.YieldTermStructure
  (
    YieldTermStructure

  , depositRateHelper'
  )
  where

import QuantLib.Internal
{#import QuantLib.Quote#}(Quote)
import {-# SOURCE #-} QuantLib.Index.InterestRate

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- breaking recursive dependencies with InterestRateIndex module
-- if you put all pointer declarations in a separate module
-- ch2s will not attach finalizers to foreign ptrs in other modules
-- I don't want to create extra modules just to workaround the issue with cyclic dependencies and this will not help with finalizers anyway
{#pointer *QlIborIndex as IborIndex foreign newtype nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign finalizer qlFreeYieldTermStructure newtype#}

instance ForeignObject YieldTermStructure where
  withObject = withYieldTermStructure
  peekObject = newForeignPtr qlFreeYieldTermStructure >=> return . YieldTermStructure

{#pointer *QlRateHelper as RateHelper foreign finalizer qlFreeRateHelper newtype#}

instance ForeignObject RateHelper where
  withObject = withRateHelper
  peekObject = newForeignPtr qlFreeRateHelper >=> return . RateHelper

{#fun qlDepositRateHelper1 as depositRateHelper' {withObject* `Quote', withObject* `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#enum CurveTrait {} deriving(Show, Eq)#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
