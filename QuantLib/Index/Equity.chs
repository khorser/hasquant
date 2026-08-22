module QuantLib.Index.Equity
  (
    EquityIndex

  , equityIndex
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *QlIndex as Index foreign -> CIndex' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlEquityIndex as EquityIndex foreign -> CEquityIndex' nocode#}

-- |A named equity total-return index, forecasting future fixings from an
-- optional risk-free interest rate curve and dividend curve, and an optional
-- spot 'QuantLib.Quote.Quote' -- today's fixing is used when no spot is given.
-- Historical fixings are added via 'QuantLib.Index.addFixing'. No inspector is bound for
-- currency\/interest curve\/dividend curve\/spot: each is a plain, never-mutated echo of this
-- constructor's own argument, same shape as the currency\/interest\/dividend\/spot fields on
-- 'QuantLib.Index.Commodity.CommodityIndex' -- the caller already holds whatever it passed in.
{#fun qlEquityIndex as equityIndex{`String' -- ^name
  ,withCalendar*`Calendar' -- ^fixingCalendar
  ,withCurrency*`Currency'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y1)' -- ^interest
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y2)' -- ^dividend
  ,withMaybeQuote*`Maybe (GenQuote q)' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`EquityIndex'peekEquityIndex*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
