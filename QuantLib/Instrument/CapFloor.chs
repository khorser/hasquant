{-# LANGUAGE MultiParamTypeClasses, TypeOperators #-}
module QuantLib.Instrument.CapFloor
  (
    CapFloor
  , cap
  , collar
  , floor
  , atmRate
  , impliedVolatility
  , optionlet
  )
  where

import Prelude hiding(floor)

import QuantLib.Type
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg nocode#}

{#pointer *QlCapFloor as CapFloor foreign -> CCapFloor nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument nocode#}
{#fun qlCapFloorAsInstrument{withCapFloor*`CapFloor'}->`Instrument'peekInstrument*#}
instance CapFloor`Derives` Instrument where cast = qlCapFloorAsInstrument

{#fun qlCap as cap{withLeg*`GenLeg a', withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}

{#fun qlCollar as collar{withLeg*`GenLeg a', withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}

{#fun qlFloor as floor{withLeg*`GenLeg a', withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}

{#fun qlCapFloorAtmRate as atmRate{withCapFloor*`CapFloor',withYieldTermStructure*`YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |implied term volatility
{#fun qlCapFloorImpliedVolatility as impliedVolatility{withCapFloor*`CapFloor',`Double',withYieldTermStructure*`YieldTermStructure',`Double',`Double', fromIntegral`Word',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the n-th optionlet as a new CapFloor with only one cash flow.
{#fun qlCapFloorOptionlet as optionlet{withCapFloor*`CapFloor', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`CapFloor'peekCapFloor*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
