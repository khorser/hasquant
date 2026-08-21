module QuantLib.TermStructure.Commodity
  (
    CommodityCurve
  , commodityCurve
  , commodityCurveName
  , commodityCurveCommodityType
  , commodityCurveUnitOfMeasure
  , commodityCurveCurrency
  , commodityCurveDates
  , commodityCurvePrices
  , commodityCurveEmpty
  , commodityCurveBasisOfCurve
  , setCommodityCurveBasisOfCurve
  , commodityCurvePrice
  , commodityCurveBasisOfPrice
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Time.Date(Day)
import QuantLib.Commodity(CommodityType, UnitOfMeasure)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *CommodityType foreign -> CCommodityType nocode#}
{#pointer *UnitOfMeasure foreign -> CUnitOfMeasure nocode#}
{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *QlCommodityCurve as CommodityCurve foreign -> CCommodityCurve' nocode#}

-- |Construct a commodity price curve: a named, interpolated (forward-flat) price curve over a
-- fixed set of dates, for a given commodity type\/currency\/unit of measure. QuantLib's no-dates
-- constructor (populated later via the mutator @setPrices@) is not bound -- per the standing
-- setter-confirmation rule, only 'setCommodityCurveBasisOfCurve' was confirmed, not @setPrices@ --
-- so this with-dates constructor is the only way to build one.
{#fun qlCommodityCurve as commodityCurve
  {`String' -- ^name
  ,withCommodityType*`CommodityType'
  ,withCurrency*`Currency'
  ,withUnitOfMeasure*`UnitOfMeasure'
  ,withCalendar*`Calendar'
  ,withDayArray*`[Day]'&
  ,withDoubleArray*`[Double]'&
  ,withDayCounter*`DayCounter'
  ,preErrorCheck-`String'errorCheck*-}->`CommodityCurve'peekCommodityCurve*#}

-- |The curve's name, as given at construction.
{#fun qlCommodityCurveName as commodityCurveName{withGenTermStructure*`CommodityCurve'}->`String'peekDynString*#}

-- |The commodity type this curve prices.
{#fun qlCommodityCurveCommodityType as commodityCurveCommodityType{withGenTermStructure*`CommodityCurve'}->`CommodityType'peekCommodityType*#}

-- |The unit of measure this curve's prices are quoted in.
{#fun qlCommodityCurveUnitOfMeasure as commodityCurveUnitOfMeasure{withGenTermStructure*`CommodityCurve'}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |The currency this curve's prices are quoted in.
{#fun qlCommodityCurveCurrency as commodityCurveCurrency{withGenTermStructure*`CommodityCurve'}->`Currency'peekCurrency*#}

-- |The curve's node dates, as given at construction.
{#fun qlCommodityCurveDates as commodityCurveDates{withGenTermStructure*`CommodityCurve',preArray-`[Day]'&peekDayArray*}->`()'#}

-- |The curve's node prices, as given at construction. Paired positionally with 'commodityCurveDates'
-- -- upstream's own @nodes()@ getter is just their zip, so it isn't bound separately (per "bind
-- few inspectors").
{#fun qlCommodityCurvePrices as commodityCurvePrices{withGenTermStructure*`CommodityCurve',preArray-`[Double]'&peekDoubleArray*}->`()'#}

-- |Whether this curve has any nodes.
{#fun pure qlCommodityCurveEmpty as commodityCurveEmpty{withGenTermStructure*`CommodityCurve'}->`Bool'#}

-- |The basis curve this curve was chained to via 'setCommodityCurveBasisOfCurve', if any.
{#fun qlCommodityCurveBasisOfCurve as commodityCurveBasisOfCurve{withGenTermStructure*`CommodityCurve'}->`Maybe CommodityCurve'peekMaybeCommodityCurve*#}

-- |Chain this curve to a basis curve: prices returned by 'commodityCurvePrice'\/'commodityCurveBasisOfPrice'
-- then include the basis curve's price on top of this curve's own. Confirmed with the user as the
-- one 'CommodityCurve' mutator worth binding (unlike @setPrices@, which stays unbound).
{#fun qlCommodityCurveSetBasisOfCurve as setCommodityCurveBasisOfCurve{withGenTermStructure*`CommodityCurve',withGenTermStructure*`CommodityCurve'}->`()'#}

-- |The curve's price for a date, plus any chained basis curve's price. This binds only
-- upstream's @nearbyOffset <= 0@ case (no rolling onto nearby exchange contracts) -- the
-- nearby-rolling overload needs a @std::map<Date,ExchangeContract>@ marshaller that nothing else
-- in this module needs yet, and there's no upstream test to pin it against.
{#fun qlCommodityCurvePrice as commodityCurvePrice{withGenTermStructure*`CommodityCurve',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The chained basis curve's price alone (excluding this curve's own price), for a date.
{#fun qlCommodityCurveBasisOfPrice as commodityCurveBasisOfPrice{withGenTermStructure*`CommodityCurve',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
