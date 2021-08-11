module QuantLib.Index
  (
    BMAIndex
  , OvernightIndex
  , IborIndex
  )
  where

import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

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
