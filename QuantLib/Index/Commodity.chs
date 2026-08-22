module QuantLib.Index.Commodity
  (
    CommodityIndex

  , commodityIndex

  , commodityIndexForwardPrice
  , commodityIndexLastQuoteDate
  , commodityIndexEmpty
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *CommodityType foreign -> CCommodityType nocode#}
{#pointer *UnitOfMeasure foreign -> CUnitOfMeasure nocode#}
{#pointer *QlCommodityCurve as CommodityCurve foreign -> CCommodityCurve' nocode#}
{#pointer *QlCommodityIndex as CommodityIndex foreign -> CCommodityIndex' nocode#}

-- |A named commodity index, whose fixings forecast from an optional forward 'CommodityCurve'
-- (or fall back to a stored historical fixing when none is given -- add one via
-- 'QuantLib.Index.addFixing'). Upstream's constructor also takes an
-- @ExchangeContracts@\/nearby-offset pair for rolling onto nearby exchange contracts; this binds
-- only the no-rolling case (a null @exchangeContracts@ and offset 0), the same scope this module's
-- 'QuantLib.TermStructure.Commodity.CommodityCurve' already narrowed 'commodityCurvePrice' to.
-- No inspector is bound for commodity type\/currency\/unit of measure\/lot quantity\/forward
-- curve: each is a plain, never-mutated echo of this constructor's own argument -- the caller
-- already holds whatever it passed in, so a getter would tell it nothing new.
{#fun qlCommodityIndex as commodityIndex
  {`String' -- ^name
  ,withCommodityType*`CommodityType'
  ,withCurrency*`Currency'
  ,withUnitOfMeasure*`UnitOfMeasure'
  ,withCalendar*`Calendar'
  ,`Double' -- ^lotQuantity
  ,withMaybeCommodityCurve*`Maybe CommodityCurve' -- ^forwardCurve
  ,preErrorCheck-`String'errorCheck*-}->`CommodityIndex'peekCommodityIndex*#}

-- |The forecast forward price for a date, from the forward curve.
{#fun qlCommodityIndexForwardPrice as commodityIndexForwardPrice{withCommodityIndex*`CommodityIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The most recent date with a stored historical fixing. Throws if none has been added yet --
-- check 'commodityIndexEmpty' first if that's a possibility.
{#fun qlCommodityIndexLastQuoteDate as commodityIndexLastQuoteDate{withCommodityIndex*`CommodityIndex',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Whether this index has any stored historical fixings.
{#fun pure qlCommodityIndexEmpty as commodityIndexEmpty{withCommodityIndex*`CommodityIndex'}->`Bool'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
