module QuantLib.PricingEngine
  (
    PricingEngine
  , BlackCalculator
  , BlackScholesCalculator

  , asBlackCalculator
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal

{#pointer *QlPricingEngine as PricingEngine foreign finalizer qlFreePricingEngine newtype#}
instance ForeignObject PricingEngine where
  withObject = withPricingEngine
  constructor = PricingEngine
  finalizer = qlFreePricingEngine

{#pointer *QlBlackCalculator as BlackCalculator foreign finalizer qlFreeBlackCalculator newtype#}
instance ForeignObject BlackCalculator where
  withObject = withBlackCalculator
  constructor = BlackCalculator
  finalizer = qlFreeBlackCalculator

{#pointer *QlBlackScholesCalculator as BlackScholesCalculator foreign finalizer qlFreeBlackScholesCalculator newtype#}
instance ForeignObject BlackScholesCalculator where
  withObject = withBlackScholesCalculator
  constructor = BlackScholesCalculator
  finalizer = qlFreeBlackScholesCalculator
{#fun qlBlackScholesCalculatorAsBlackCalculator as asBlackCalculator {`BlackScholesCalculator'} -> `BlackCalculator'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
