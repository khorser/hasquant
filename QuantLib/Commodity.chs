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
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
import QuantLib.Time.Date(Day)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *CommodityType foreign -> CCommodityType nocode#}
{#pointer *UnitOfMeasure foreign -> CUnitOfMeasure nocode#}
{#pointer *PaymentTerm foreign -> CPaymentTerm nocode#}

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
{#fun qlPaymentTermCalendar as paymentTermCalendar{withPaymentTerm*`PaymentTerm'}->`Calendar'peekCalendar*#}

-- |Whether this is a usable instance (as opposed to one built via a default constructor).
{#fun pure qlPaymentTermEmpty as paymentTermEmpty{withPaymentTerm*`PaymentTerm'}->`Bool'#}

-- |Applies the term's offset (and calendar adjustment) to a trade or pricing-period-end date to
-- get the actual payment date.
{#fun qlPaymentTermGetPaymentDate as paymentTermGetPaymentDate
  {withPaymentTerm*`PaymentTerm',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
