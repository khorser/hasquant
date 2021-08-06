module QuantLib.CashFlow.Leg
  (
     DurationType(..)
   , RateAveragingType
  )

  where

#include "qlEnumC2HS.h"

{#enum DurationType {} deriving(Show, Eq, Bounded) #}

{#enum RateAveragingType {} add prefix="Averaging" deriving(Show, Eq, Bounded) #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
