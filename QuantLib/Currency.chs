module QuantLib.Currency
  (
   MoneyConversionType(..)
  , ExchangeRateType(..)
  , Ccy(..)
  , Currency
  , currency
  , currency'
  , code
  , fractionsPerUnit
  , fractionSymbol
  , code'
  , symbol
  , ExchangeRate
  , exchangeRate
  , rate
  , exchangeRateType
  , exchange
  , chainExchangeRate
  , addExchangeRate
  , lookupExchangeRate
  , clearExchangeRates
  , moneyConversionType
  , setMoneyConversionType
  , moneyBaseCurrency
  , setMoneyBaseCurrency
  , convertToBaseCurrency
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
import QuantLib.Time.Date(Day)
import Foreign.Marshal.Alloc(alloca)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Rounding as QlRounding foreign newtype nocode#}

{#enum MoneyConversionType{} deriving(Show, Eq)#}
{#enum ExchangeRateType{} deriving(Show, Eq)#}
{#enum Ccy{} deriving(Show, Eq)#}

{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *Rounding as QlRounding foreign -> CRounding nocode#}
{#pointer *ExchangeRate foreign -> CExchangeRate nocode#}

{#fun qlCurrency as currency{`Ccy',preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}
{#fun pure qlCurrencyCode as code{withCurrency*`Currency'}->`String'peekDynString*#}
{#fun pure qlCurrencyFractionsPerUnit as fractionsPerUnit{withCurrency*`Currency'}->`Int'#}
{#fun pure qlCurrencyFractionSymbol as fractionSymbol{withCurrency*`Currency'}->`String'#}
{#fun pure qlCurrencyNumericCode as code'{withCurrency*`Currency'}->`Int'#}
{#fun pure qlCurrencySymbol as symbol{withCurrency*`Currency'}->`String'#}
{#fun qlCreateCurrency as currency'{`String' -- ^name
  ,`String' -- ^code
  ,`Int' -- ^numericCode
  ,`String' -- ^symbol
  ,`String' -- ^fractionSymbol
  ,`Int' -- ^fractionsPerUnit
  ,withMaybeRounding*`Maybe Rounding'
  ,withMaybeCurrency*`Maybe Currency' -- ^triangulationCurrency
  ,preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}

-- |Construct a Direct exchange rate: a unit of @source@ is worth @rate@ units of @target@.
{#fun qlExchangeRate as exchangeRate
  {withCurrency*`Currency' -- ^source
  ,withCurrency*`Currency' -- ^target
  ,`Double' -- ^rate
  }->`ExchangeRate'peekExchangeRate*#}
{#fun qlExchangeRateRate as rate{withExchangeRate*`ExchangeRate'}->`Double'#}
{#fun qlExchangeRateType_ as exchangeRateType{withExchangeRate*`ExchangeRate'}->`ExchangeRateType'#}
-- |Apply an exchange rate to a cash amount (a @(Double, Currency)@ pair, standing in for
-- QuantLib's @Money@), returning the converted amount as a pair in the other currency of the
-- rate. Throws if the given currency is on neither side of the rate.
{#fun qlExchangeRateExchange as exchange
  {withExchangeRate*`ExchangeRate'
  ,withMoney*`(Double, Currency)'& -- ^amount
  ,alloca-`Currency'peekCurrencyPtr*
  ,preErrorCheck-`String'errorCheck*-
  }->`Double'#}
-- |Combine two exchange rates sharing a common currency into a derived rate between their
-- other two currencies. Throws if the rates don't share a common currency.
{#fun qlExchangeRateChain as chainExchangeRate
  {withExchangeRate*`ExchangeRate'
  ,withExchangeRate*`ExchangeRate'
  ,preErrorCheck-`String'errorCheck*-}->`ExchangeRate'peekExchangeRate*#}

-- |Register an exchange rate with the global exchange-rate repository, valid between the given
-- dates (inclusive). Use 'minDate'/'maxDate' for an always-valid rate.
{#fun qlExchangeRateManagerAdd as addExchangeRate
  {withExchangeRate*`ExchangeRate', withDay*`Day', withDay*`Day'}->`()'#}
-- |Look up a (possibly derived) exchange rate between two currencies at a given date (or the
-- current evaluation date if 'Nothing'). Throws if no rate can be found. Pre-populated with a
-- set of known historical rates even before any 'addExchangeRate' call.
{#fun qlExchangeRateManagerLookup as lookupExchangeRate
  {withCurrency*`Currency', withCurrency*`Currency'
  ,withMaybeDay*`Maybe Day', `ExchangeRateType'
  ,preErrorCheck-`String'errorCheck*-}->`ExchangeRate'peekExchangeRate*#}
-- |Reset the exchange-rate repository back to its built-in set of known historical rates,
-- discarding anything added via 'addExchangeRate'.
{#fun qlExchangeRateManagerClear as clearExchangeRates{}->`()'#}

{#fun qlMoneySettingsConversionType as moneyConversionType{}->`MoneyConversionType'#}
{#fun qlMoneySettingsSetConversionType as setMoneyConversionType{`MoneyConversionType'}->`()'#}
{#fun qlMoneySettingsBaseCurrency as moneyBaseCurrency{}->`Maybe Currency'peekMaybeCurrency*#}
{#fun qlMoneySettingsSetBaseCurrency as setMoneyBaseCurrency{withCurrency*`Currency'}->`()'#}
-- |Convert a cash amount to the configured base currency (via 'setMoneyBaseCurrency'), using
-- 'lookupExchangeRate' and rounding the result per the target currency's convention. Throws if
-- no base currency is set or no rate path exists.
{#fun qlConvertToBaseCurrency as convertToBaseCurrency
  {withMoney*`(Double, Currency)'& -- ^amount
  ,alloca-`Currency'peekCurrencyPtr*
  ,preErrorCheck-`String'errorCheck*-
  }->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
