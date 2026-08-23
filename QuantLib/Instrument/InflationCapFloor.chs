module QuantLib.Instrument.InflationCapFloor
  (
    YoYInflationCapFloor
  , yoyInflationCap
  , yoyInflationCollar
  , yoyInflationFloor
  , yoyInflationCapFloorAtmRate
  , yoyInflationCapFloorOptionlet
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Common

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlYoYInflationCapFloor as YoYInflationCapFloor foreign -> CYoYInflationCapFloor' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}

-- |Constructs a YoY-inflation cap: pays the excess of the YoY leg's rate over each exercise
-- rate, if positive. Unlike a nominal cap, the first optionlet is live (YoY inflation sets in
-- arrears, so there is no reason to omit it -- see upstream's own note on
-- 'YoYInflationCapFloor').
{#fun qlYoYInflationCap as yoyInflationCap{withLeg*`GenLeg l' -- ^yoyLeg
  ,withDoubleArray*`[Double]'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCapFloor'peekYoYInflationCapFloor*#}

-- |Constructs a YoY-inflation collar: a cap struck at the cap rates combined with a floor
-- struck at the floor rates.
{#fun qlYoYInflationCollar as yoyInflationCollar{withLeg*`GenLeg l' -- ^yoyLeg
  ,withDoubleArray*`[Double]'& -- ^capRates
  ,withDoubleArray*`[Double]'& -- ^floorRates
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCapFloor'peekYoYInflationCapFloor*#}

-- |Constructs a YoY-inflation floor: pays the excess of each exercise rate over the YoY leg's
-- rate, if positive.
{#fun qlYoYInflationFloor as yoyInflationFloor{withLeg*`GenLeg l' -- ^yoyLeg
  ,withDoubleArray*`[Double]'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCapFloor'peekYoYInflationCapFloor*#}

-- |The fair (at-the-money) rate for the cap\/floor's underlying YoY leg, discounted on the
-- given curve.
{#fun qlYoYInflationCapFloorAtmRate as yoyInflationCapFloorAtmRate{withGenInstrument*`YoYInflationCapFloor'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the n-th optionlet as a new YoYInflationCapFloor with only one cash flow.
{#fun qlYoYInflationCapFloorOptionlet as yoyInflationCapFloorOptionlet{withGenInstrument*`YoYInflationCapFloor'
  ,fromIntegral`Word' -- ^n
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCapFloor'peekYoYInflationCapFloor*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
