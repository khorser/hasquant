module QuantLib.Quote
  (
     Quote
   , PriceType(..)
   , IntervalPriceType(..)
   , AtmType(..)
   , DeltaType(..)
  )

  where

import QuantLib.Internal
import Foreign.ForeignPtr(newForeignPtr)
import Control.Monad((>=>))

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#pointer *QlQuote as Quote foreign finalizer qlFreeQuote newtype#}

instance ForeignObject Quote where
  withObject = withQuote
  peekObject = newForeignPtr qlFreeQuote >=> return . Quote

{#enum PriceType {} deriving(Show, Eq, Bounded)#}

{#enum IntervalPriceType{} add prefix="IntervalPrice" deriving(Show, Eq, Bounded)#}

{#enum AtmType {} deriving(Show, Eq, Bounded)#}

{#enum DeltaType {} deriving(Show, Eq, Bounded)#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
