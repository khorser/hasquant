module QuantLib.Currency
  (
   MoneyConversionType(..)
  , Ccy(..)
  , Currency(..)
  , currency
  )
  where

import QuantLib.Utility
import QuantLib.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum MoneyConversionType {} deriving(Show, Eq, Bounded) #}

{#enum Ccy {} deriving(Show, Eq, Bounded) #}

{#pointer *Currency foreign  finalizer qlFreeCurrency newtype #}

{#fun pure qlCurrencyName {`Currency'} -> `String' peekDynString* #}

instance Named Currency where
  name = qlCurrencyName

{#fun qlCurrency as currency {`Ccy', preErrorCheck- `String' errorCheck*-} -> `Currency' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
