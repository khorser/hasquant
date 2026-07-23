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

import QuantLib.Type
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlCapFloor as CapFloor foreign -> CCapFloor' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}

{#fun qlCap as cap{withLeg*`GenLeg a' -- ^floatingLeg
  ,withDoubleArray*`[Double]'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
{#fun qlCollar as collar{withLeg*`GenLeg a' -- ^floatingLeg
  ,withDoubleArray*`[Double]'& -- ^capRates
  ,withDoubleArray*`[Double]'& -- ^floorRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
{#fun qlFloor as floor{withLeg*`GenLeg a' -- ^floatingLeg
  ,withDoubleArray*`[Double]'& -- ^exerciseRates
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}
{#fun qlCapFloorAtmRate as atmRate{withGenInstrument*`CapFloor',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |implied term volatility
{#fun qlCapFloorImpliedVolatility as impliedVolatility{withGenInstrument*`CapFloor',`Double' -- ^price
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^disc
  ,`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Returns the n-th optionlet as a new CapFloor with only one cash flow.
{#fun qlCapFloorOptionlet as optionlet{withGenInstrument*`CapFloor',fromIntegral`Word' -- ^n
  ,preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
