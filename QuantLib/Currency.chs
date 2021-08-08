module QuantLib.Currency
  (
   MoneyConversionType(..)
  , Ccy(..)
  , Currency
  , currency
  , currency'
  , code
  , format
  , fractionsPerUnit
  , fractionSymbol
  , code'
  , symbol
  )
  where

import QuantLib.Utility
{#import QuantLib.Math #}
import QuantLib.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum MoneyConversionType {} deriving(Show, Eq, Bounded) #}

{#enum Ccy {} deriving(Show, Eq, Bounded) #}

{#pointer *Currency foreign finalizer qlFreeCurrency newtype #}

instance ForeignObject Currency where
  withObject = withCurrency
  
{#fun pure qlCurrencyName {`Currency'} -> `String' peekDynString* #}

instance Named Currency where
  name = qlCurrencyName

{#fun qlCurrency as currency {`Ccy', preErrorCheck- `String' errorCheck*-} -> `Currency' #}

{#fun pure qlCurrencyCode as code {`Currency'} -> `String' peekDynString* #}

{#fun pure qlCurrencyFormat as format {`Currency'} -> `String' peekDynString* #}

{#fun pure qlCurrencyFractionsPerUnit as fractionsPerUnit {`Currency'} -> `Int' #}

{#fun pure qlCurrencyFractionSymbol as fractionSymbol {`Currency'} -> `String' #}

{#fun pure qlCurrencyNumericCode as code' {`Currency'} -> `Int' #}

{#fun pure qlCurrencySymbol as symbol {`Currency'} -> `String' #}

{#fun qlCreateCurrency as currency' {`String' , `String' , `Int' , `String' , `String' , `Int' , withMaybeObject* `Maybe Rounding', `String', withMaybeObject* `Maybe Currency', preErrorCheck- `String' errorCheck*-} -> `Currency' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
