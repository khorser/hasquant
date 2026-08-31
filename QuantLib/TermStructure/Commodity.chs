module QuantLib.TermStructure.Commodity
  (
    CommodityCurve
  , commodityCurve
  , commodityCurveName
  , commodityCurveCommodityType
  , commodityCurveUnitOfMeasure
  , commodityCurveCurrency
  , commodityCurveNodes
  , commodityCurveEmpty
  , commodityCurveBasisOfCurve
  , setCommodityCurveBasisOfCurve
  , commodityCurvePrice
  , commodityCurveBasisOfPrice
  , ExchangeContract
  , ExchangeContracts
  , commodityCurvePriceNearby
  , commodityCurveUnderlyingPriceDate
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import Data.List.NonEmpty(NonEmpty, toList)

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
commodityCurve :: String -> CommodityType -> Currency -> UnitOfMeasure -> Calendar
  -> NonEmpty (Day, Double) -> DayCounter -> IO CommodityCurve
commodityCurve name ct ccy uom cal nodes dc = qlCommodityCurve name ct ccy uom cal dates prices dc
  where (dates, prices) = unzip (toList nodes)

{#fun qlCommodityCurve
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
{#fun qlCommodityCurveCommodityType as commodityCurveCommodityType{withGenTermStructure*`CommodityCurve',preErrorCheck-`String'errorCheck*-}->`CommodityType'peekCommodityType*#}

-- |The unit of measure this curve's prices are quoted in.
{#fun qlCommodityCurveUnitOfMeasure as commodityCurveUnitOfMeasure{withGenTermStructure*`CommodityCurve',preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |The currency this curve's prices are quoted in.
{#fun qlCommodityCurveCurrency as commodityCurveCurrency{withGenTermStructure*`CommodityCurve',preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}

-- |The curve's nodes, as @(date, price)@ pairs in construction order.
commodityCurveNodes :: CommodityCurve -> IO [(Day, Double)]
commodityCurveNodes curve = do
  dates <- qlCommodityCurveDates curve
  prices <- qlCommodityCurvePrices curve
  pure (zip dates prices)
{#fun qlCommodityCurveDates as qlCommodityCurveDates{withGenTermStructure*`CommodityCurve',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlCommodityCurvePrices as qlCommodityCurvePrices{withGenTermStructure*`CommodityCurve',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Whether this curve has any nodes.
{#fun pure qlCommodityCurveEmpty as commodityCurveEmpty{withGenTermStructure*`CommodityCurve'}->`Bool'#}

-- |The basis curve this curve was chained to via 'setCommodityCurveBasisOfCurve', if any.
{#fun qlCommodityCurveBasisOfCurve as commodityCurveBasisOfCurve{withGenTermStructure*`CommodityCurve'}->`Maybe CommodityCurve'peekMaybeCommodityCurve*#}

-- |Chain this curve to a basis curve: prices returned by 'commodityCurvePrice'\/'commodityCurveBasisOfPrice'
-- then include the basis curve's price on top of this curve's own. Confirmed with the user as the
-- one 'CommodityCurve' mutator worth binding (unlike @setPrices@, which stays unbound).
{#fun qlCommodityCurveSetBasisOfCurve as setCommodityCurveBasisOfCurve{withGenTermStructure*`CommodityCurve',withGenTermStructure*`CommodityCurve',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |A dated exchange contract: a code, its expiration date, and the start/end dates of the
-- underlying delivery period it corresponds to. A plain tuple, per the @Money@/'Quantity'-as-tuple
-- convention -- it carries no calculation of its own upstream, only three inspectors that would
-- just be tuple projections.
type ExchangeContract = (String, Day, Day, Day) -- ^code, expirationDate, underlyingStartDate, underlyingEndDate

-- |QuantLib's @std::map\<Date,ExchangeContract\>@: a set of exchange contracts, keyed by the date
-- 'commodityCurvePriceNearby'\/'commodityCurveUnderlyingPriceDate' roll onto (upstream's own
-- @lower_bound@ walk finds the first key at or after the query date, then steps @nearbyOffset - 1@
-- further). Marshalled as an association list, not an actual 'Data.Map.Map' -- the C shim rebuilds
-- the real @std::map@ itself so key order doesn't need to be pre-sorted on the Haskell side.
type ExchangeContracts = [(Day, ExchangeContract)]

-- |Split an 'ExchangeContracts' into the five parallel lists the low-level bindings below take.
-- Not a single combined marshaller: c2hs's @&@ tuple-splitter only ever consumes two C arguments
-- (confirmed against its source, same reasoning as 'QuantLib.Commodity.Quantity'), so each list is
-- passed as its own flat, individually-marshalled argument instead of one bundled continuation.
splitExchangeContracts :: ExchangeContracts -> ([Day], [String], [Day], [Day], [Day])
splitExchangeContracts ecs =
  ( map fst ecs
  , [c | (_, (c, _, _, _)) <- ecs]
  , [x | (_, (_, x, _, _)) <- ecs]
  , [s | (_, (_, _, s, _)) <- ecs]
  , [e | (_, (_, _, _, e)) <- ecs] )

{#fun qlCommodityCurvePrice as qlCommodityCurvePrice_
  {withGenTermStructure*`CommodityCurve'
  ,withDay*`Day'
  ,withDayArray*`[Day]'&
  ,withStringArray*`[String]'&
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,`Int' -- ^nearbyOffset
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The curve's price for a date, plus any chained basis curve's price, rolling forward onto
-- nearby exchange contracts when @nearbyOffset > 0@ (upstream's own @price@ never touches
-- @exchangeContracts@ otherwise). 'commodityCurvePrice' is this with no exchange contracts and
-- offset @0@, which reproduces the flat (no-rolling) case exactly.
commodityCurvePriceNearby :: CommodityCurve -> Day -> ExchangeContracts -> Int -> IO Double
commodityCurvePriceNearby curve date ecs nearbyOffset =
  qlCommodityCurvePrice_ curve date keys codes expirations starts ends nearbyOffset
  where (keys, codes, expirations, starts, ends) = splitExchangeContracts ecs

-- |The curve's price for a date, plus any chained basis curve's price. This is
-- 'commodityCurvePriceNearby' with no exchange contracts and offset @0@ -- the flat (no
-- nearby-rolling) case, which never touches @exchangeContracts@ upstream either way.
commodityCurvePrice :: CommodityCurve -> Day -> IO Double
commodityCurvePrice curve date = commodityCurvePriceNearby curve date [] 0

-- |The chained basis curve's price alone (excluding this curve's own price), for a date.
{#fun qlCommodityCurveBasisOfPrice as commodityCurveBasisOfPrice{withGenTermStructure*`CommodityCurve',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCommodityCurveUnderlyingPriceDate as qlCommodityCurveUnderlyingPriceDate_
  {withGenTermStructure*`CommodityCurve'
  ,withDay*`Day'
  ,withDayArray*`[Day]'&
  ,withStringArray*`[String]'&
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,`Int' -- ^nearbyOffset
  ,preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |The date whose price a nearby roll (@nearbyOffset > 0@) actually reads: the underlying
-- contract's start date at the @nearbyOffset@\'th exchange contract at or after @date@. Throws if
-- @nearbyOffset <= 0@, or if fewer than @nearbyOffset@ contracts are available from @date@ onward.
commodityCurveUnderlyingPriceDate :: CommodityCurve -> Day -> ExchangeContracts -> Int -> IO Day
commodityCurveUnderlyingPriceDate curve date ecs nearbyOffset =
  qlCommodityCurveUnderlyingPriceDate_ curve date keys codes expirations starts ends nearbyOffset
  where (keys, codes, expirations, starts, ends) = splitExchangeContracts ecs

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
