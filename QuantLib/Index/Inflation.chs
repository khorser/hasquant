module QuantLib.Index.Inflation
  (
    InflationIndex
  , ZeroInflationIndex
  , YoYInflationIndex
  , GenInflationIndex
  , GenZeroInflationIndex
  , GenYoYInflationIndex

  , asInflationIndex

  , ZeroInflationIndexType(..)
  , zeroInflationIndex
  , zeroInflationIndex'
  , YoYInflationIndexType(..)
  , yoyInflationIndex
  , yoyInflationIndex'
  , yoyInflationIndexFromZero

  , Region
  , RegionType(..)
  , region
  , region'

  , fixing
  , yoyFixing
  , needsForecast
  , yoyNeedsForecast
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency, TimeUnit)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlInflationIndex as InflationIndex foreign -> CInflationIndex' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *Region foreign -> CRegion nocode#}
{#pointer *QlZeroInflationTermStructure as ZeroInflationTermStructure foreign -> CZeroInflationTermStructure' nocode#}
{#pointer *QlYoYInflationTermStructure as YoYInflationTermStructure foreign -> CYoYInflationTermStructure' nocode#}

{#enum ZeroInflationIndexType{} deriving (Show, Eq, Read)#}
{#enum YoYInflationIndexType{} deriving (Show, Eq, Read)#}
{#enum RegionType{} deriving (Show, Eq, Read, Bounded)#}

-- |A named zero inflation index (RPI/HICP/CPI family). Constructs with no historical
-- fixings and no linked term structure -- add fixings via 'QuantLib.Index.addFixing'.
{#fun qlCreateZeroInflationIndex as zeroInflationIndex{`ZeroInflationIndexType',preErrorCheck-`String'errorCheck*-}->`ZeroInflationIndex'peekZeroInflationIndex*#}

-- |A named quoted year-on-year inflation index.
{#fun qlCreateYoYInflationIndex as yoyInflationIndex{`YoYInflationIndexType',preErrorCheck-`String'errorCheck*-}->`YoYInflationIndex'peekYoYInflationIndex*#}

-- |One of the 6 named geographical/economic regions QuantLib ships (used for the pre-baked
-- named indices, e.g. 'UKRPI' uses 'UKRegion' internally). See 'region\'' for an arbitrary
-- custom region.
{#fun qlRegion as region{`RegionType',preErrorCheck-`String'errorCheck*-}->`Region'peekRegion*#}

-- |An arbitrary custom region, given its name and ISO code.
{#fun qlCreateRegion as region'{`String',`String',preErrorCheck-`String'errorCheck*-}->`Region'peekRegion*#}

-- |A custom zero inflation index (arbitrary family name/region/currency), with no historical
-- fixings -- add fixings via 'QuantLib.Index.addFixing'.
{#fun qlZeroInflationIndex as zeroInflationIndex'{`String' -- ^familyName
  ,withRegion*`Region'
  ,`Bool' -- ^revised
  ,`Frequency'
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^availabilityLag
  ,withCurrency*`Currency'
  ,withMaybeZeroInflationTermStructure*`Maybe ZeroInflationTermStructure'
  ,preErrorCheck-`String'errorCheck*-}->`ZeroInflationIndex'peekZeroInflationIndex*#}

-- |A custom quoted year-on-year inflation index (arbitrary family name/region/currency); needs
-- its own past fixings added via 'QuantLib.Index.addFixing'. See 'yoyInflationIndexFromZero'
-- for a YoY index defined instead as a ratio of an existing 'ZeroInflationIndex'\'s fixings.
{#fun qlYoYInflationIndex as yoyInflationIndex'{`String' -- ^familyName
  ,withRegion*`Region'
  ,`Bool' -- ^revised
  ,`Frequency'
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^availabilityLag
  ,withCurrency*`Currency'
  ,withMaybeYoYInflationTermStructure*`Maybe YoYInflationTermStructure'
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationIndex'peekYoYInflationIndex*#}

-- |A year-on-year index defined as the ratio of an existing 'ZeroInflationIndex'\'s fixings;
-- stores no fixings of its own.
{#fun qlYoYInflationIndexFromZero as yoyInflationIndexFromZero{withZeroInflationIndex*`ZeroInflationIndex'
  ,withMaybeYoYInflationTermStructure*`Maybe YoYInflationTermStructure'
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationIndex'peekYoYInflationIndex*#}

-- |The (possibly forecast) fixing at the given date; for a date with no linked term
-- structure this returns the stored historical fixing added via 'QuantLib.Index.addFixing'.
{#fun qlZeroInflationIndexFixing as fixing{withZeroInflationIndex*`ZeroInflationIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The (possibly forecast) year-on-year fixing at the given date; for a date with no linked
-- term structure this returns the stored historical fixing added via 'QuantLib.Index.addFixing'.
{#fun qlYoYInflationIndexFixing as yoyFixing{withYoYInflationIndex*`YoYInflationIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Whether 'fixing' at the given date would have to be forecast rather than served from a stored
-- historical fixing -- true once the date falls after the latest period a fixing could plausibly
-- already be published for, given the index's publication lag.
{#fun pure qlZeroInflationIndexNeedsForecast as needsForecast{withZeroInflationIndex*`ZeroInflationIndex',withDay*`Day'}->`Bool'#}

-- |The year-on-year counterpart of 'needsForecast', for 'yoyFixing'.
{#fun pure qlYoYInflationIndexNeedsForecast as yoyNeedsForecast{withYoYInflationIndex*`YoYInflationIndex',withDay*`Day'}->`Bool'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
