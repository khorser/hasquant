module QuantLib.TermStructure.InflationVolatility
  (
    YoYOptionletVolatilitySurface

  , constantYoYOptionletVolatility

  , yoyOptionletVolatility
  , yoyOptionletTotalVariance
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.Time.Schedule#}(Frequency)
import QuantLib.Internal.Common

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYOptionletVolatilitySurface as YoYOptionletVolatilitySurface foreign -> CYoYOptionletVolatilitySurface' nocode#}

-- |Constant YoY-inflation optionlet vol surface, no maturity\/strike dependence -- the only
-- concrete leaf bound here. Mirrors 'QuantLib.TermStructure.Volatility.constantOptionletVolatility',
-- taking a 'GenQuote' rather than a plain 'Double' per the @std::variant@\/overload-collapse
-- rule (the flat case is already reachable via 'QuantLib.Quote.simpleQuote').
{#fun qlConstantYoYOptionletVolatility as constantYoYOptionletVolatility{withQuote*`GenQuote q'
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDayCounter*`DayCounter'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,`Frequency'
  ,`Bool' -- ^indexIsInterpolated
  ,`Double' -- ^minStrike
  ,`Double' -- ^maxStrike
  ,`VolatilityType'
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`YoYOptionletVolatilitySurface'peekYoYOptionletVolatilityStructure*#}

-- |The volatility for a given maturity date and strike, observed with the given observation
-- lag (or the surface's own lag when 'Nothing').
{#fun qlYoYOptionletVolatilitySurfaceVolatility as yoyOptionletVolatility{withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface'
  ,withDay*`Day'
  ,`Double' -- ^strike
  ,fromMaybeEnumQuantity`Maybe (Word,TimeUnit)'& -- ^obsLag
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The total integrated variance for a given exercise date and strike -- useful because it
-- scales out time from the optionlet pricing formulae. As 'yoyOptionletVolatility', a
-- 'Nothing' observation lag uses the surface's own.
{#fun qlYoYOptionletVolatilitySurfaceTotalVariance as yoyOptionletTotalVariance{withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface'
  ,withDay*`Day'
  ,`Double' -- ^strike
  ,fromMaybeEnumQuantity`Maybe (Word,TimeUnit)'& -- ^obsLag
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
