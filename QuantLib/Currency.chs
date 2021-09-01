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

import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Rounding as QlRounding foreign newtype nocode#}

{#enum MoneyConversionType {} deriving(Show, Eq)#}

{#enum Ccy {} deriving(Show, Eq)#}

{#pointer *Currency foreign -> CCurrency nocode#}

{#fun qlCurrency as currency {`Ccy', preErrorCheck- `String' errorCheck*-} -> `Currency' peekCurrency*#}

{#fun pure qlCurrencyCode as code {withSimpleType* `Currency'} -> `String' peekDynString*#}

{#fun pure qlCurrencyFormat as format {withSimpleType* `Currency'} -> `String' peekDynString*#}

{#fun pure qlCurrencyFractionsPerUnit as fractionsPerUnit {withSimpleType* `Currency'} -> `Int'#}

{#fun pure qlCurrencyFractionSymbol as fractionSymbol {withSimpleType* `Currency'} -> `String'#}

{#fun pure qlCurrencyNumericCode as code' {withSimpleType* `Currency'} -> `Int'#}

{#fun pure qlCurrencySymbol as symbol {withSimpleType* `Currency'} -> `String'#}

{#fun qlCreateCurrency as currency' {`String' , `String' , `Int' , `String' , `String' , `Int' , withMaybeEnumObject* `Maybe Rounding', `String', withMaybeSimpleType* `Maybe Currency', preErrorCheck- `String' errorCheck*-} -> `Currency' peekCurrency*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
