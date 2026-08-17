module QuantLib.Instrument.CapFloor
  (
    CapFloor
  , cap
  , collar
  , floor
  , atmRate
  , impliedVolatility
  , optionlet
  ) where
import Prelude hiding(floor)

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.InterestRate#}(VolatilityType)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlCapFloor as CapFloor foreign -> CCapFloor' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}

-- |constructs a cap: pays the excess of the floating leg's rate over each exercise rate, if positive
{#fun qlCap as cap{withLeg*`GenLeg l' -- ^floatingLeg
  ,withDoubleArray*`[Double]'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
-- |constructs a collar: a cap struck at the cap rates combined with a floor struck at the floor rates
{#fun qlCollar as collar{withLeg*`GenLeg l' -- ^floatingLeg
  ,withDoubleArray*`[Double]'& -- ^capRates
  ,withDoubleArray*`[Double]'& -- ^floorRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
-- |constructs a floor: pays the excess of each exercise rate over the floating leg's rate, if positive
{#fun qlFloor as floor{withLeg*`GenLeg l' -- ^floatingLeg
  ,withDoubleArray*`[Double]'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
-- |returns the fair (at-the-money) rate for the cap/floor's underlying floating leg, discounted on the given curve
{#fun qlCapFloorAtmRate as atmRate{withGenInstrument*`CapFloor',withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |implied term volatility
{#fun qlCapFloorImpliedVolatility as impliedVolatility{withGenInstrument*`CapFloor',`Double' -- ^price
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^disc
  ,`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Returns the n-th optionlet as a new CapFloor with only one cash flow.
{#fun qlCapFloorOptionlet as optionlet{withGenInstrument*`CapFloor',fromIntegral`Word' -- ^n
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
