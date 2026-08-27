module QuantLib.Commodity
  (
    CommodityType
  , commodityType
  , nullCommodityType
  , commodityTypeCode
  , commodityTypeName
  , commodityTypeEmpty

  , UnitOfMeasure
  , UnitOfMeasureType(..)
  , unitOfMeasure
  , unitOfMeasureName
  , unitOfMeasureCode
  , unitOfMeasureType
  , unitOfMeasureEmpty
  , lotUnitOfMeasure
  , barrelUnitOfMeasure
  , mtUnitOfMeasure
  , mbUnitOfMeasure
  , gallonUnitOfMeasure
  , litreUnitOfMeasure
  , kilolitreUnitOfMeasure
  , tokyoKilolitreUnitOfMeasure

  , PaymentTerm
  , PaymentTermEventType(..)
  , paymentTerm
  , paymentTermName
  , paymentTermEventType
  , paymentTermOffsetDays
  , paymentTermCalendar
  , paymentTermEmpty
  , paymentTermGetPaymentDate

  , Quantity
  , roundedQuantity
  , closeQuantity
  , closeEnoughQuantity

  , CommodityUnitCost

  , DateInterval
  , isDateBetween
  , intersection

  , PricingPeriod
  , pricingPeriodStartDate
  , pricingPeriodEndDate
  , pricingPeriodPaymentDate
  , pricingPeriodQuantity
  , PricingPeriods
  , pricingPeriod

  , UnitOfMeasureConversion
  , UnitOfMeasureConversionType(..)
  , unitOfMeasureConversion
  , unitOfMeasureConversionSource
  , unitOfMeasureConversionTarget
  , unitOfMeasureConversionCommodityType
  , unitOfMeasureConversionType
  , unitOfMeasureConversionFactor
  , unitOfMeasureConversionCode
  , convertQuantity
  , chainUnitOfMeasureConversion

  , lookupUomConversion
  , addUomConversion
  , clearUomConversions

  , commoditySettingsCurrency
  , setCommoditySettingsCurrency
  , commoditySettingsUnitOfMeasure
  , setCommoditySettingsUnitOfMeasure
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Common
import Foreign.Marshal.Alloc(alloca)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *CommodityType foreign -> CCommodityType nocode#}
{#pointer *UnitOfMeasure foreign -> CUnitOfMeasure nocode#}
{#pointer *PaymentTerm foreign -> CPaymentTerm nocode#}
{#pointer *UnitOfMeasureConversion foreign -> CUnitOfMeasureConversion nocode#}

{#enum UnitOfMeasureConversionType{} deriving(Show, Eq, Read)#}

-- |Construct a custom commodity type identified by its code (e.g. \"HO\") and descriptive name
-- (e.g. \"Heating Oil\"). QuantLib has no fixed enum of commodity types -- every instance is
-- user-registered by code, the same way a custom 'QuantLib.Currency.currency'' is.
{#fun qlCommodityType as commodityType{`String' -- ^code
  ,`String' -- ^name
  ,preErrorCheck-`String'errorCheck*-}->`CommodityType'peekCommodityType*#}

-- |The fixed placeholder commodity type QuantLib itself uses where no real commodity type
-- applies (e.g. in unit-of-measure-only conversions).
{#fun qlNullCommodityType as nullCommodityType{preErrorCheck-`String'errorCheck*-}->`CommodityType'peekCommodityType*#}

-- |The commodity code, e.g. \"HO\".
{#fun pure qlCommodityTypeCode as commodityTypeCode{withCommodityType*`CommodityType'}->`String'peekDynString*#}

-- |The descriptive name, e.g. \"Heating Oil\".
{#fun pure qlCommodityTypeName as commodityTypeName{withCommodityType*`CommodityType'}->`String'peekDynString*#}

-- |Whether this is a usable instance (as opposed to one built via a default constructor).
{#fun pure qlCommodityTypeEmpty as commodityTypeEmpty{withCommodityType*`CommodityType'}->`Bool'#}

-- |Construct a custom unit of measure from its descriptive name (e.g. \"Barrels\"), code (e.g.
-- \"BBL\"), and type (mass/volume/energy/quantity).
{#fun qlUnitOfMeasure as unitOfMeasure{`String' -- ^name
  ,`String' -- ^code
  ,fromEnumC`UnitOfMeasureType'
  ,preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |The descriptive name, e.g. \"Barrels\".
{#fun pure qlUnitOfMeasureName as unitOfMeasureName{withUnitOfMeasure*`UnitOfMeasure'}->`String'peekDynString*#}

-- |The code, e.g. \"BBL\", \"MT\".
{#fun pure qlUnitOfMeasureCode as unitOfMeasureCode{withUnitOfMeasure*`UnitOfMeasure'}->`String'peekDynString*#}

-- |The unit's type (mass/volume/energy/quantity).
{#fun pure qlUnitOfMeasureUnitType as unitOfMeasureType{withUnitOfMeasure*`UnitOfMeasure'}->`UnitOfMeasureType'toEnumC#}

-- |Whether this is a usable instance (as opposed to one built via a default constructor).
{#fun pure qlUnitOfMeasureEmpty as unitOfMeasureEmpty{withUnitOfMeasure*`UnitOfMeasure'}->`Bool'#}

-- |The lot, a dimensionless 'UnitOfMeasure::Quantity' unit.
{#fun qlLotUnitOfMeasure as lotUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |Barrels (BBL), the base petroleum volume unit.
{#fun qlBarrelUnitOfMeasure as barrelUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |Metric tonnes (MT).
{#fun qlMTUnitOfMeasure as mtUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |Thousand barrels (MB).
{#fun qlMBUnitOfMeasure as mbUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |US gallons.
{#fun qlGallonUnitOfMeasure as gallonUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |Litres.
{#fun qlLitreUnitOfMeasure as litreUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |Kilolitres.
{#fun qlKilolitreUnitOfMeasure as kilolitreUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}
-- |Tokyo kilolitres.
{#fun qlTokyoKilolitreUnitOfMeasure as tokyoKilolitreUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |Construct a payment term: a named offset (in calendar-adjusted days) from either the trade
-- date or the pricing-period end date.
{#fun qlPaymentTerm as paymentTerm{`String' -- ^name
  ,fromEnumC`PaymentTermEventType'
  ,`Int' -- ^offsetDays
  ,withCalendar*`Calendar'
  ,preErrorCheck-`String'errorCheck*-}->`PaymentTerm'peekPaymentTerm*#}

-- |The payment term's name, e.g. \"Pricing end + 5 days\".
{#fun pure qlPaymentTermName as paymentTermName{withPaymentTerm*`PaymentTerm'}->`String'peekDynString*#}

-- |Whether the offset is measured from the trade date or the pricing date.
{#fun pure qlPaymentTermEventType_ as paymentTermEventType{withPaymentTerm*`PaymentTerm'}->`PaymentTermEventType'toEnumC#}

-- |The number of (calendar-adjusted) offset days.
{#fun pure qlPaymentTermOffsetDays as paymentTermOffsetDays{withPaymentTerm*`PaymentTerm'}->`Int'#}

-- |The calendar used to adjust the payment date.
{#fun qlPaymentTermCalendar as paymentTermCalendar{withPaymentTerm*`PaymentTerm',preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

-- |Whether this is a usable instance (as opposed to one built via a default constructor).
{#fun pure qlPaymentTermEmpty as paymentTermEmpty{withPaymentTerm*`PaymentTerm'}->`Bool'#}

-- |Applies the term's offset (and calendar adjustment) to a trade or pricing-period-end date to
-- get the actual payment date.
{#fun qlPaymentTermGetPaymentDate as paymentTermGetPaymentDate
  {withPaymentTerm*`PaymentTerm',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |An amount of a commodity: a 'CommodityType', a 'UnitOfMeasure', and a plain amount. Marshalled
-- as a flat triple rather than a wrapper type (per the @Money@-as-tuple convention) -- and, unlike
-- 'CommodityUnitCost' below, its three inspectors are just tuple projections, so they need no
-- binding at all. c2hs's @&@ tuple-splitter only ever consumes two C arguments (confirmed against
-- its source, not just by trial), so every function below that takes or returns a 'Quantity'
-- marshals it as three flat 'CommodityType'\/'UnitOfMeasure'\/'Double' arguments instead of one
-- combined tuple.
type Quantity = (CommodityType, UnitOfMeasure, Double)

{#fun pure qlQuantityRoundedAmount as quantityRoundedAmount{withUnitOfMeasure*`UnitOfMeasure',`Double'}->`Double'#}

-- |Round a quantity's amount per its unit of measure's rounding convention. The commodity type and
-- unit of measure are unaffected by rounding, so they're carried straight through in Haskell
-- rather than round-tripped through the C++ call.
roundedQuantity :: Quantity -> Quantity
roundedQuantity (ct, uom, amount) = (ct, uom, quantityRoundedAmount uom amount)

{#fun qlQuantityClose as qlQuantityClose_
  {withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,`Int',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Whether two quantities are close to within @n@ ULPs (default 42 upstream), after converting
-- the second to the first's unit of measure if their units differ (which throws unless a
-- conversion is reachable -- see 'lookupUomConversion').
closeQuantity :: Quantity -> Quantity -> Int -> IO Bool
closeQuantity (ct1, uom1, amt1) (ct2, uom2, amt2) n = qlQuantityClose_ ct1 uom1 amt1 ct2 uom2 amt2 n

{#fun qlQuantityCloseEnough as qlQuantityCloseEnough_
  {withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,`Int',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |As 'closeQuantity', but using QuantLib's relative (rather than absolute) closeness test.
closeEnoughQuantity :: Quantity -> Quantity -> Int -> IO Bool
closeEnoughQuantity (ct1, uom1, amt1) (ct2, uom2, amt2) n = qlQuantityCloseEnough_ ct1 uom1 amt1 ct2 uom2 amt2 n

-- |A commodity's unit cost: a cash amount (a @(Double, Currency)@ pair, standing in for
-- QuantLib's @Money@) per 'UnitOfMeasure'. A plain tuple, like 'Quantity' -- it carries no
-- calculation of its own upstream.
type CommodityUnitCost = (Double, Currency, UnitOfMeasure)

-- |A date range, inclusive of both ends. No C++ call is needed for either operation below --
-- 'Day' (from @Data.Time.Calendar@) already has the 'Ord' instance QuantLib's own comparisons rely
-- on, so both are plain Haskell functions rather than shim calls.
type DateInterval = (Day, Day)

-- |Whether a date falls within the interval, optionally excluding either end.
isDateBetween :: DateInterval
              -> Day -- ^date
              -> Bool -- ^includeFirst
              -> Bool -- ^includeLast
              -> Bool
isDateBetween (startDate, endDate) date includeFirst includeLast =
  (if includeFirst then date >= startDate else date > startDate) &&
  (if includeLast then date <= endDate else date < endDate)

-- |The overlap of two date intervals, or 'Nothing' if they don't overlap at all (upstream returns
-- a default-constructed, both-dates-null 'DateInterval' in this case; a 'Maybe' is the natural
-- Haskell equivalent).
intersection :: DateInterval -> DateInterval -> Maybe DateInterval
intersection (s1, e1) (s2, e2)
  | (s1 < s2 && e1 < s2) || (s1 > e2 && e1 > e2) = Nothing
  | otherwise = Just (max s1 s2, min e1 e2)

-- |A 'DateInterval' over which a fixed 'Quantity' of a commodity is priced, paid on
-- 'pricingPeriodPaymentDate'. Unlike 'Quantity'\/'CommodityUnitCost', this is a real record
-- rather than a tuple, per the user's explicit choice -- it's used as a named unit across every
-- energy-swap constructor (Stage 6), where a flat tuple would be unreadable positionally.
data PricingPeriod = PricingPeriod
  { pricingPeriodStartDate :: Day
  , pricingPeriodEndDate :: Day
  , pricingPeriodPaymentDate :: Day
  , pricingPeriodQuantity :: Quantity
  } deriving (Show, Eq)

type PricingPeriods = [PricingPeriod]

-- |Construct a 'PricingPeriod', enforcing upstream's @DateInterval@ invariant that the end date
-- is not before the start date.
pricingPeriod :: Day -> Day -> Day -> Quantity -> PricingPeriod
pricingPeriod startDate endDate
  | endDate < startDate = error "pricingPeriod: end date must be >= start date"
  | otherwise = PricingPeriod startDate endDate

-- |Construct a conversion factor between two units of measure for a given commodity type: a unit
-- of @source@ is worth @conversionFactor@ units of @target@.
{#fun qlUnitOfMeasureConversion as unitOfMeasureConversion
  {withCommodityType*`CommodityType'
  ,withUnitOfMeasure*`UnitOfMeasure' -- ^source
  ,withUnitOfMeasure*`UnitOfMeasure' -- ^target
  ,`Double' -- ^conversionFactor
  ,preErrorCheck-`String'errorCheck*-}->`UnitOfMeasureConversion'peekUnitOfMeasureConversion*#}

-- |The source unit of measure.
{#fun qlUnitOfMeasureConversionSource as unitOfMeasureConversionSource{withUnitOfMeasureConversion*`UnitOfMeasureConversion',preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |The target unit of measure.
{#fun qlUnitOfMeasureConversionTarget as unitOfMeasureConversionTarget{withUnitOfMeasureConversion*`UnitOfMeasureConversion',preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |The commodity type this conversion applies to.
{#fun qlUnitOfMeasureConversionCommodityType as unitOfMeasureConversionCommodityType{withUnitOfMeasureConversion*`UnitOfMeasureConversion',preErrorCheck-`String'errorCheck*-}->`CommodityType'peekCommodityType*#}

-- |Whether the conversion was given directly, or derived by chaining two other conversions.
{#fun pure qlUnitOfMeasureConversionType_ as unitOfMeasureConversionType{withUnitOfMeasureConversion*`UnitOfMeasureConversion'}->`UnitOfMeasureConversionType'#}

-- |The conversion factor: a unit of the source is worth this many units of the target.
{#fun pure qlUnitOfMeasureConversionFactor as unitOfMeasureConversionFactor{withUnitOfMeasureConversion*`UnitOfMeasureConversion'}->`Double'#}

-- |A code identifying the conversion, e.g. \"Heating OilMTBBL\".
{#fun pure qlUnitOfMeasureConversionCode as unitOfMeasureConversionCode{withUnitOfMeasureConversion*`UnitOfMeasureConversion'}->`String'peekDynString*#}

{#fun qlUnitOfMeasureConversionConvert as qlUnitOfMeasureConversionConvert_
  {withUnitOfMeasureConversion*`UnitOfMeasureConversion'
  ,withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,alloca-`CommodityType'peekCommodityTypePtr*
  ,alloca-`UnitOfMeasure'peekUnitOfMeasurePtr*
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Apply the conversion factor to a quantity, converting it from the conversion's source to its
-- target unit of measure (or vice versa). Throws if the quantity's unit of measure is on neither
-- side of the conversion.
convertQuantity :: UnitOfMeasureConversion -> Quantity -> IO Quantity
convertQuantity conv (ct, uom, amount) = do
  (amount', ct', uom') <- qlUnitOfMeasureConversionConvert_ conv ct uom amount
  pure (ct', uom', amount')

-- |Combine two conversions sharing a common unit of measure into a derived conversion between
-- their other two units. Throws if the conversions don't share a common unit.
{#fun qlUnitOfMeasureConversionChain as chainUnitOfMeasureConversion
  {withUnitOfMeasureConversion*`UnitOfMeasureConversion'
  ,withUnitOfMeasureConversion*`UnitOfMeasureConversion'
  ,preErrorCheck-`String'errorCheck*-}->`UnitOfMeasureConversion'peekUnitOfMeasureConversion*#}

-- |Look up a (possibly derived, via triangulation) conversion between two units of measure for a
-- given commodity type. Throws if none can be found. Pre-populated with a set of known petroleum
-- conversion factors even before any 'addUomConversion' call.
{#fun qlUnitOfMeasureConversionManagerLookup as lookupUomConversion
  {withCommodityType*`CommodityType'
  ,withUnitOfMeasure*`UnitOfMeasure' -- ^source
  ,withUnitOfMeasure*`UnitOfMeasure' -- ^target
  ,`UnitOfMeasureConversionType'
  ,preErrorCheck-`String'errorCheck*-}->`UnitOfMeasureConversion'peekUnitOfMeasureConversion*#}

-- |Register a conversion with the global unit-of-measure conversion repository, replacing any
-- existing conversion between the same commodity type and pair of units.
{#fun qlUnitOfMeasureConversionManagerAdd as addUomConversion{withUnitOfMeasureConversion*`UnitOfMeasureConversion'}->`()'#}

-- |Reset the unit-of-measure conversion repository back to its built-in set of known petroleum
-- conversion factors, discarding anything added via 'addUomConversion'.
{#fun qlUnitOfMeasureConversionManagerClear as clearUomConversions{}->`()'#}

-- |The global commodity currency setting (defaults to USD).
{#fun qlCommoditySettingsCurrency as commoditySettingsCurrency{preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}

-- |Set the global commodity currency setting.
{#fun qlCommoditySettingsSetCurrency as setCommoditySettingsCurrency{withCurrency*`Currency'}->`()'#}

-- |The global commodity unit-of-measure setting (defaults to barrels).
{#fun qlCommoditySettingsUnitOfMeasure as commoditySettingsUnitOfMeasure{preErrorCheck-`String'errorCheck*-}->`UnitOfMeasure'peekUnitOfMeasure*#}

-- |Set the global commodity unit-of-measure setting.
{#fun qlCommoditySettingsSetUnitOfMeasure as setCommoditySettingsUnitOfMeasure{withUnitOfMeasure*`UnitOfMeasure'}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
