module QuantLib.TermStructure.InflationVolatility
  (
    YoYOptionletVolatilitySurface

  , constantYoYOptionletVolatility

  , yoyOptionletVolatility
  , yoyOptionletTotalVariance

  , CPICapFloorTermPriceSurface
  , cpiCapFloorTermPriceSurface

  , CPIVolatilitySurface
  , constantCPIVolatility

  , cpiVolatility
  , cpiTotalVariance
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
{#pointer *QlCPICapFloorTermPriceSurface as CPICapFloorTermPriceSurface foreign -> CCPICapFloorTermPriceSurface' nocode#}
{#pointer *QlCPIVolatilitySurface as CPIVolatilitySurface foreign -> CCPIVolatilitySurface' nocode#}

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

-- |Prices CPI cap\/floors by interpolation and put\/call parity off a market strike\/maturity
-- price grid (hardcoded to the @Bilinear@ 'Interpolator2D', the only instantiation upstream's
-- own test-suite uses -- see this type's haddock in "QuantLib.Internal.Type"). @cPrice@\/
-- @fPrice@ are plain price matrices (rows = strikes, columns = maturities), not quote-linked
-- like 'QuantLib.TermStructure.Volatility.capFloorTermVolSurface's volatility matrix.
cpiCapFloorTermPriceSurface :: Double -- ^nominal
  -> Double -- ^baseRate
  -> (Word, TimeUnit) -- ^observationLag
  -> Calendar -> BusinessDayConvention -> DayCounter
  -> ZeroInflationIndex -> CPIInterpolationType -> GenYieldTermStructure y
  -> [Double] -- ^cStrikes
  -> [Double] -- ^fStrikes
  -> [(Word, TimeUnit)] -- ^cfMaturities
  -> Matrix Double -- ^cPrice
  -> Matrix Double -- ^fPrice
  -> IO CPICapFloorTermPriceSurface
cpiCapFloorTermPriceSurface nom baseRate obsLag cal bdc dc zii interp yts cStrikes fStrikes cfMaturities (Matrix cr cc cd) (Matrix fr fc fd) =
  qlCPICapFloorTermPriceSurface nom baseRate obsLag cal bdc dc zii interp yts cStrikes fStrikes maturityNums maturityUnits cr cc cd fr fc fd
  where (maturityNums, maturityUnits) = unzip cfMaturities
{#fun qlCPICapFloorTermPriceSurface{`Double',`Double',fromEnumQuantity`(Word,TimeUnit)'&
  ,withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter'
  ,withZeroInflationIndex*`ZeroInflationIndex',fromEnumC`CPIInterpolationType'
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,withDoubleArray*`[Double]'& -- ^cStrikes
  ,withDoubleArray*`[Double]'& -- ^fStrikes
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'& -- ^cfMaturities
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]' -- ^cPrice
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]' -- ^fPrice
  ,preErrorCheck-`String'errorCheck*-}->`CPICapFloorTermPriceSurface'peekCPICapFloorTermPriceSurface*#}

-- |Constant CPI (zero-inflation) volatility surface, no maturity\/strike dependence -- the only
-- concrete leaf bound here, mirroring 'constantYoYOptionletVolatility'. No engine or coupon
-- pricer consumes this in QL 1.43 (see this type's own haddock in "QuantLib.Internal.Type"), so
-- it is queryable via 'cpiVolatility'\/'cpiTotalVariance' but not otherwise wired up.
{#fun qlConstantCPIVolatility as constantCPIVolatility{withQuote*`GenQuote q'
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDayCounter*`DayCounter'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,`Frequency'
  ,`Bool' -- ^indexIsInterpolated
  ,preErrorCheck-`String'errorCheck*-}->`CPIVolatilitySurface'peekCPIVolatilitySurface*#}

-- |The volatility for a given maturity date and strike, observed with the given observation
-- lag (or the surface's own lag when 'Nothing').
{#fun qlCPIVolatilitySurfaceVolatility as cpiVolatility{withGenVolatilityTermStructure*`CPIVolatilitySurface'
  ,withDay*`Day'
  ,`Double' -- ^strike
  ,fromMaybeEnumQuantity`Maybe (Word,TimeUnit)'& -- ^obsLag
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The total integrated variance for a given exercise date and strike. As 'cpiVolatility', a
-- 'Nothing' observation lag uses the surface's own.
{#fun qlCPIVolatilitySurfaceTotalVariance as cpiTotalVariance{withGenVolatilityTermStructure*`CPIVolatilitySurface'
  ,withDay*`Day'
  ,`Double' -- ^strike
  ,fromMaybeEnumQuantity`Maybe (Word,TimeUnit)'& -- ^obsLag
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
