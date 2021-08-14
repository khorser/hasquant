module QuantLib.Process
  (
    ProcessDiscretization(..)
  , ExtendedBlackScholesMertonProcessDiscretization(..)
  , HestonProcessDiscretization(..)
  , GJRGARCHProcessDiscretization(..)
  , HybridHestonHullWhiteProcessDiscretization(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#enum ProcessDiscretization {} deriving(Show,Eq)#}

{#enum ExtendedBlackScholesMertonProcessDiscretization {} deriving(Show, Eq)#}

{#enum HestonProcessDiscretization {} deriving(Show, Eq)#}

{#enum GJRGARCHProcessDiscretization {} deriving(Show, Eq)#}

{#enum HybridHestonHullWhiteProcessDiscretization {} deriving(Show, Eq)#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
