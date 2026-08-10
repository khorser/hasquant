module QuantLib.Instrument.Variance
  (
    VarianceSwap

  , varianceSwap

  , strike
  , position
  , startDate
  , maturityDate
  , notional
  , variance
  ) where
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Internal.Enum#}(PositionType)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlVarianceSwap as VarianceSwap foreign -> CVarianceSwap' nocode#}

-- |Variance swap: pays off the difference between realized and strike variance, scaled by notional. This class does not manage seasoned variance swaps.
{#fun qlVarianceSwap as varianceSwap{fromEnumC`PositionType',`Double' -- ^strike
  ,`Double' -- ^notional
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^maturityDate
  ,preErrorCheck-`String'errorCheck*-}->`VarianceSwap'peekVarianceSwap*#}

{#fun qlVarianceSwapStrike as strike{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlVarianceSwapPosition as position{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`PositionType'#}
{#fun qlVarianceSwapStartDate as startDate{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlVarianceSwapMaturityDate as maturityDate{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlVarianceSwapNotional as notional{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Realized variance -- requires a pricing engine to be set first
{#fun qlVarianceSwapVariance as variance{withGenInstrument*`VarianceSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
