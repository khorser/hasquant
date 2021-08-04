module QuantLib.Quote
  (
     PriceType(..)
   , IntervalPriceType(..)
   , AtmType(..)
   , DeltaType(..)
  )

  where

#include "qlEnum.h"

{#enum PriceType {} deriving(Show, Eq, Bounded) #}

{#enum IntervalPriceType{} add prefix="IntervalPrice" deriving(Show, Eq, Bounded) #}

{#enum AtmType {} deriving(Show, Eq, Bounded) #}

{#enum DeltaType {} deriving(Show, Eq, Bounded) #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
