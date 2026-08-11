module QuantLib.Index.Equity
  (
    EquityIndex

  , equityIndex

  , currency
  , equityInterestRateCurve
  , equityDividendCurve
  , spot
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
-- Historical fixings are added via 'QuantLib.Index.addFixing'.
{#fun qlEquityIndex as equityIndex{`String' -- ^name
  ,withCalendar*`Calendar' -- ^fixingCalendar
  ,withCurrency*`Currency'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^interest
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure z)' -- ^dividend
  ,withMaybeQuote*`Maybe (GenQuote a)' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`EquityIndex'peekEquityIndex*#}

{#fun qlEquityIndexCurrency as currency{withEquityIndex*`EquityIndex',preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}
{#fun qlEquityIndexInterestRateCurve as equityInterestRateCurve{withEquityIndex*`EquityIndex',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlEquityIndexDividendCurve as equityDividendCurve{withEquityIndex*`EquityIndex',preErrorCheck-`String'errorCheck*-}->`YieldTermStructure'peekYieldTermStructure*#}
{#fun qlEquityIndexSpot as spot{withEquityIndex*`EquityIndex',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
