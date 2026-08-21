module QuantLib.Index.Commodity
  (
    CommodityIndex

  , commodityIndex

  , commodityIndexCommodityType
  , commodityIndexCurrency
  , commodityIndexUnitOfMeasure
  , commodityIndexForwardCurve
  , commodityIndexLotQuantity
  , commodityIndexForwardPrice
  , commodityIndexLastQuoteDate
  , commodityIndexEmpty
  , commodityIndexForwardCurveEmpty
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Commodity(CommodityType, UnitOfMeasure)

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
{#fun qlCommodityIndex as commodityIndex
  {`String' -- ^name
  ,withCommodityType*`CommodityType'
  ,withCurrency*`Currency'
  ,withUnitOfMeasure*`UnitOfMeasure'
  ,withCalendar*`Calendar'
  ,`Double' -- ^lotQuantity
  ,withMaybeCommodityCurve*`Maybe CommodityCurve' -- ^forwardCurve
  ,preErrorCheck-`String'errorCheck*-}->`CommodityIndex'peekCommodityIndex*#}

-- |The commodity type this index prices.
{#fun qlCommodityIndexCommodityType as commodityIndexCommodityType{withCommodityIndex*`CommodityIndex'}->`CommodityType'peekCommodityType*#}

-- |The currency this index's prices are quoted in.
{#fun qlCommodityIndexCurrency as commodityIndexCurrency{withCommodityIndex*`CommodityIndex'}->`Currency'peekCurrency*#}

-- |The unit of measure this index's prices are quoted in.
{#fun qlCommodityIndexUnitOfMeasure as commodityIndexUnitOfMeasure{withCommodityIndex*`CommodityIndex'}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |The forward curve used to forecast this index's future fixings, if any.
{#fun qlCommodityIndexForwardCurve as commodityIndexForwardCurve{withCommodityIndex*`CommodityIndex'}->`Maybe CommodityCurve'peekMaybeCommodityCurve*#}

-- |The lot quantity, as given at construction.
{#fun pure qlCommodityIndexLotQuantity as commodityIndexLotQuantity{withCommodityIndex*`CommodityIndex'}->`Double'#}

-- |The forecast forward price for a date, from the forward curve.
{#fun qlCommodityIndexForwardPrice as commodityIndexForwardPrice{withCommodityIndex*`CommodityIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The most recent date with a stored historical fixing. Throws if none has been added yet --
-- check 'commodityIndexEmpty' first if that's a possibility.
{#fun qlCommodityIndexLastQuoteDate as commodityIndexLastQuoteDate{withCommodityIndex*`CommodityIndex',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Whether this index has any stored historical fixings.
{#fun pure qlCommodityIndexEmpty as commodityIndexEmpty{withCommodityIndex*`CommodityIndex'}->`Bool'#}

-- |Whether this index has no forward curve, or an empty one.
{#fun pure qlCommodityIndexForwardCurveEmpty as commodityIndexForwardCurveEmpty{withCommodityIndex*`CommodityIndex'}->`Bool'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
