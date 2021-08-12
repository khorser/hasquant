module QuantLib.InterestRateIndex
  (
    InterestRateIndex
  , BMAIndex
  , OvernightIndex
  , IborIndex
  )
  where

import QuantLib.Internal
{#import QuantLib.YieldTermStructure #}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlInterestRateIndex as InterestRateIndex foreign finalizer qlFreeInterestRateIndex newtype #}

instance ForeignObject InterestRateIndex where
  withObject = withInterestRateIndex

{#pointer *QlBMAIndex as BMAIndex foreign finalizer qlFreeBMAIndex newtype #}

instance ForeignObject BMAIndex where
  withObject = withBMAIndex

{#pointer *QlOvernightIndex as OvernightIndex foreign finalizer qlFreeOvernightIndex newtype #}

instance ForeignObject OvernightIndex where
  withObject = withOvernightIndex

{#pointer *QlIborIndex as IborIndex foreign finalizer qlFreeIborIndex newtype #}

instance ForeignObject IborIndex where
  withObject = withIborIndex

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
