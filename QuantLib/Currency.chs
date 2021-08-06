module QuantLib.Currency
  (
   MoneyConversionType(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

{#enum MoneyConversionType {} deriving(Show, Eq, Bounded) #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
