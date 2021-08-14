module QuantLib.VolatilityTermStructure
  (
    BlackVarianceSurfaceExtrapolation
  , ExtendedBlackVarianceSurfaceExtrapolation
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#enum BlackVarianceSurfaceExtrapolation {} deriving(Show, Eq)#}

{#enum ExtendedBlackVarianceSurfaceExtrapolation {} deriving(Show, Eq)#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
