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
  , YoYInflationIndexType(..)
  , yoyInflationIndex

  , fixing
  , yoyFixing
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlInflationIndex as InflationIndex foreign -> CInflationIndex' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}

{#enum ZeroInflationIndexType{} deriving (Show, Eq)#}
{#enum YoYInflationIndexType{} deriving (Show, Eq)#}

-- |A named zero inflation index (RPI/HICP/CPI family). Constructs with no historical
-- fixings and no linked term structure -- add fixings via 'QuantLib.Index.addFixing'.
{#fun qlCreateZeroInflationIndex as zeroInflationIndex{`ZeroInflationIndexType',preErrorCheck-`String'errorCheck*-}->`ZeroInflationIndex'peekZeroInflationIndex*#}
-- |A named quoted year-on-year inflation index.
{#fun qlCreateYoYInflationIndex as yoyInflationIndex{`YoYInflationIndexType',preErrorCheck-`String'errorCheck*-}->`YoYInflationIndex'peekYoYInflationIndex*#}

-- |The (possibly forecast) fixing at the given date; for a date with no linked term
-- structure this returns the stored historical fixing added via 'QuantLib.Index.addFixing'.
{#fun qlZeroInflationIndexFixing as fixing{withZeroInflationIndex*`ZeroInflationIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlYoYInflationIndexFixing as yoyFixing{withYoYInflationIndex*`YoYInflationIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
