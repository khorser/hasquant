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

-- |Look up one of the built-in ISO 4217 currencies by its enum tag.
{#fun qlCurrency as currency{`Ccy',preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}

-- |The currency's ISO 4217 three-letter code, e.g. \"USD\".
{#fun pure qlCurrencyCode as code{withCurrency*`Currency'}->`String'peekDynString*#}

-- |The number of fractional units (e.g. cents) in one unit of the currency.
{#fun pure qlCurrencyFractionsPerUnit as fractionsPerUnit{withCurrency*`Currency'}->`Int'#}

-- |The currency's fractional-unit symbol, e.g. \"¢\".
{#fun pure qlCurrencyFractionSymbol as fractionSymbol{withCurrency*`Currency'}->`String'#}

-- |The currency's ISO 4217 numeric code, e.g. 840 for USD.
{#fun pure qlCurrencyNumericCode as code'{withCurrency*`Currency'}->`Int'#}

-- |The currency's symbol, e.g. \"$\".
{#fun pure qlCurrencySymbol as symbol{withCurrency*`Currency'}->`String'#}

-- |Construct a custom currency from its name, codes, symbols, rounding convention and an
-- optional triangulation currency used for indirect exchange.
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
  ,preErrorCheck-`String'errorCheck*-
  }->`ExchangeRate'peekExchangeRate*#}

-- |The rate itself: a unit of the source currency is worth this many units of the target.
{#fun qlExchangeRateRate as rate{withExchangeRate*`ExchangeRate'}->`Double'#}

-- |Whether the rate was given directly or derived by chaining two other rates.
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
  {withExchangeRate*`ExchangeRate', withDay*`Day', withDay*`Day'
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

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

-- |The global 'Money' arithmetic setting controlling how amounts in different currencies are
-- combined (no conversion, convert to the base currency, or convert automatically).
{#fun qlMoneySettingsConversionType as moneyConversionType{}->`MoneyConversionType'#}

-- |Set the global 'Money' arithmetic conversion setting.
{#fun qlMoneySettingsSetConversionType as setMoneyConversionType{`MoneyConversionType'}->`()'#}

-- |The global base currency used by 'MoneyConversionType' base-currency conversion, if set.
{#fun qlMoneySettingsBaseCurrency as moneyBaseCurrency{preErrorCheck-`String'errorCheck*-}->`Maybe Currency'peekMaybeCurrency*#}

-- |Set the global base currency used by 'MoneyConversionType' base-currency conversion.
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
