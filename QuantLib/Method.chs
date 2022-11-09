module QuantLib.Method
  (
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

import QuantLib.Type
import QuantLib.Internal
import QuantLib.Internal.Type

{#pointer *PolymorphicPathGenerator as PathGenerator foreign -> CPathGenerator nocode#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
