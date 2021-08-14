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
{#import QuantLib.Math#}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum MoneyConversionType {} deriving(Show, Eq)#}

{#enum Ccy {} deriving(Show, Eq)#}

{#pointer *Currency foreign finalizer qlFreeCurrency newtype#}

instance ForeignObject Currency where
  withObject = withCurrency
  peekObject = newForeignPtr qlFreeCurrency >=> return . Currency
  
{#fun pure qlCurrencyName {`Currency'} -> `String' peekDynString*#}

instance Show Currency where show = qlCurrencyName
instance Eq Currency where x == y = show x == show y

{#fun qlCurrency as currency {`Ccy', preErrorCheck- `String' errorCheck*-} -> `Currency'#}

{#fun pure qlCurrencyCode as code {`Currency'} -> `String' peekDynString*#}

{#fun pure qlCurrencyFormat as format {`Currency'} -> `String' peekDynString*#}

{#fun pure qlCurrencyFractionsPerUnit as fractionsPerUnit {`Currency'} -> `Int'#}

{#fun pure qlCurrencyFractionSymbol as fractionSymbol {`Currency'} -> `String'#}

{#fun pure qlCurrencyNumericCode as code' {`Currency'} -> `Int'#}

{#fun pure qlCurrencySymbol as symbol {`Currency'} -> `String'#}

{#fun qlCreateCurrency as currency' {`String' , `String' , `Int' , `String' , `String' , `Int' , withMaybeObject* `Maybe Rounding', `String', withMaybeObject* `Maybe Currency', preErrorCheck- `String' errorCheck*-} -> `Currency'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
