module QuantLib.Instrument.Option
  (
    ExerciseType(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum ExerciseType {} deriving(Show, Eq)#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
