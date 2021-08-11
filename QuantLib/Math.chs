module QuantLib.Math
  (
    RoundingType(..)
  , Rounding
  , rounding
  , rounding'
  , applyRounding
  )
where

import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"

{#enum RoundingType {} deriving (Show, Eq, Bounded) #}

{#pointer *Rounding foreign finalizer qlFreeRounding newtype #}

instance ForeignObject Rounding where
  withObject = withRounding

{#fun qlRounding as rounding {preErrorCheck- `String' errorCheck*-} -> `Rounding' #}

{#fun qlRounding1 as rounding' {`Int', `RoundingType', `Int', preErrorCheck- `String' errorCheck*-} -> `Rounding' #}

{#fun pure qlRound as applyRounding {`Rounding', `Double'} -> `Double' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
