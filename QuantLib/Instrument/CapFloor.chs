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
{#import QuantLib.Instrument#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg nocode#}

{#pointer *QlCapFloor as CapFloor foreign finalizer qlFreeCapFloor newtype#}
instance ForeignObject CapFloor where
  withObject = withCapFloor
  constructor = CapFloor
  finalizer = qlFreeCapFloor
{#fun qlCapFloorAsInstrument{`CapFloor'}->`Instrument'peekObject*#}
instance CapFloor`Derives` Instrument where cast = qlCapFloorAsInstrument

{#fun qlCap as cap{withLeg*`GenLeg a', withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`CapFloor'#}

{#fun qlCollar as collar{withLeg*`GenLeg a', withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`CapFloor'#}

{#fun qlFloor as floor{withLeg*`GenLeg a', withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`CapFloor'#}

{#fun qlCapFloorAtmRate as atmRate{`CapFloor',`YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |implied term volatility
{#fun qlCapFloorImpliedVolatility as impliedVolatility{`CapFloor',`Double',`YieldTermStructure',`Double',`Double', fromIntegral`Word',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the n-th optionlet as a new CapFloor with only one cash flow.
{#fun qlCapFloorOptionlet as optionlet{`CapFloor', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`CapFloor'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
