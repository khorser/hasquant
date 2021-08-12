module QuantLib.Model
  (
   CalibrationErrorType(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

{#enum CalibrationErrorType {} deriving(Show, Eq, Bounded)#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
