module QuantLib.TermStructure.InflationVolatility
  (
    YoYOptionletVolatilitySurface

  , constantYoYOptionletVolatility
  , kInterpolatedYoYOptionletVolatilitySurfaceBlack
  , kInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack
  , kInterpolatedYoYOptionletVolatilitySurfaceBachelier

  , yoyOptionletVolatility
  , yoyOptionletTotalVariance

  , YoYCapFloorTermPriceSurface
  , yoyCapFloorTermPriceSurface

  , yoyCapFloorBaseDate
  , yoyCapFloorAtmYoYSwapDateRates
  , yoyCapFloorAtmYoYSwapRate
  , yoyCapFloorAtmYoYRate
  , yoyCapFloorStrikes

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
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *QlYoYOptionletVolatilitySurface as YoYOptionletVolatilitySurface foreign -> CYoYOptionletVolatilitySurface' nocode#}
{#pointer *QlYoYCapFloorTermPriceSurface as YoYCapFloorTermPriceSurface foreign -> CYoYCapFloorTermPriceSurface' nocode#}
{#pointer *QlCPICapFloorTermPriceSurface as CPICapFloorTermPriceSurface foreign -> CCPICapFloorTermPriceSurface' nocode#}
{#pointer *QlCPIVolatilitySurface as CPIVolatilitySurface foreign -> CCPIVolatilitySurface' nocode#}

-- |Constant YoY-inflation optionlet vol surface, no maturity\/strike dependence. Mirrors
-- 'QuantLib.TermStructure.Volatility.constantOptionletVolatility', taking a 'GenQuote' rather
-- than a plain 'Double' per the @std::variant@\/overload-collapse rule (the flat case is already
-- reachable via 'QuantLib.Quote.simpleQuote'). Not the only concrete leaf of this type any
-- more -- see 'kInterpolatedYoYOptionletVolatilitySurfaceBlack' for the market-quote-bootstrapped
-- alternative.
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

-- |Prices YoY cap\/floors by cap\/floor-surface intersection and put\/call parity, deriving an
-- ATM YoY swap curve as a side effect. 'Interpolation2D' chooses the cap\/floor price-grid
-- interpolator, 'Interpolation' the per-maturity one.
yoyCapFloorTermPriceSurface :: Word -- ^fixingDays
  -> (Word, TimeUnit) -- ^yyLag
  -> YoYInflationIndex -> CPIInterpolationType -> GenYieldTermStructure y -- ^nominal
  -> DayCounter -> Calendar -> BusinessDayConvention
  -> [Double] -- ^cStrikes
  -> [Double] -- ^fStrikes
  -> [(Word, TimeUnit)] -- ^cfMaturities
  -> Matrix Double -- ^cPrice
  -> Matrix Double -- ^fPrice
  -> Interpolation2D -> Interpolation
  -> IO YoYCapFloorTermPriceSurface
yoyCapFloorTermPriceSurface fixingDays yyLag yii interp nominal dc cal bdc cStrikes fStrikes cfMaturities (Matrix cr cc cd) (Matrix fr fc fd) i2d i1d =
  uncurryNested (qlYoYCapFloorTermPriceSurface fixingDays yyLag yii interp nominal dc cal bdc cStrikes fStrikes maturityNums maturityUnits cr cc cd fr fc fd (fromEnum i2d)) (qlInterpolation i1d)
  where (maturityNums, maturityUnits) = unzip cfMaturities
{#fun qlYoYCapFloorTermPriceSurface{fromIntegral`Word' -- ^fixingDays
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^yyLag
  ,withYoYInflationIndex*`YoYInflationIndex'
  ,fromEnumC`CPIInterpolationType'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominal
  ,withDayCounter*`DayCounter'
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDoubleArray*`[Double]'& -- ^cStrikes
  ,withDoubleArray*`[Double]'& -- ^fStrikes
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'& -- ^cfMaturities
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]' -- ^cPrice
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]' -- ^fPrice
  ,`Int' -- ^interpolator2D
  ,`Int',`Int',`Int' -- ^interpolator1D, approximator, approximatorArg
  ,preErrorCheck-`String'errorCheck*-}->`YoYCapFloorTermPriceSurface'peekYoYCapFloorTermPriceSurface*#}

-- |The date the surface's own YoY term structure (and hence any 'YoYOptionletVolatilitySurface'
-- stripped from it) treats as its base -- referenceDate minus the observation lag, rounded to
-- the containing inflation period's start.
{#fun qlYoYCapFloorTermPriceSurfaceBaseDate as yoyCapFloorBaseDate{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |The ATM YoY swap curve derived from cap\/floor-surface intersection, as (date, rate) pairs.
yoyCapFloorAtmYoYSwapDateRates :: YoYCapFloorTermPriceSurface -> IO [(Day, Double)]
yoyCapFloorAtmYoYSwapDateRates s = do
  (ds, rs) <- qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates s
  return $ zip ds rs
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*}->`()'#}

-- |The ATM YoY swap rate at the given maturity date, from put\/call parity on the surface's
-- cap\/floor price data.
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYSwapRate as yoyCapFloorAtmYoYSwapRate{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,withDay*`Day'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The ATM YoY inflation rate at the given maturity date and observation lag (or the surface's
-- own lag when 'Nothing'), derived from the swap-rate curve above.
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYRate as yoyCapFloorAtmYoYRate{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,withDay*`Day'
  ,fromMaybeEnumQuantity`Maybe (Word,TimeUnit)'& -- ^obsLag
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The union of cap and floor strikes in the surface's price grid -- the strikes a stripped
-- 'YoYOptionletVolatilitySurface' (via 'kInterpolatedYoYOptionletVolatilitySurfaceBlack' et al.)
-- has a bootstrapped vol curve for.
{#fun qlYoYCapFloorTermPriceSurfaceStrikes as yoyCapFloorStrikes{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preArray-`[Double]'&peekDoubleArray*}->`()'#}

-- |Strips a 'YoYOptionletVolatilitySurface' from a 'YoYCapFloorTermPriceSurface' by bootstrapping
-- a per-strike vol curve against Black-priced YoY caps\/floors (mirrors upstream's own
-- @testYoYPriceSurfaceToVol@: an @InterpolatedYoYOptionletStripper\<Linear\>@ solving each
-- strike's initial vol, then a @KInterpolatedYoYOptionletVolatilitySurface\<Linear\>@
-- interpolating across strikes -- neither is exposed as its own type, since nothing in upstream
-- reaches them from outside this one bootstrap; see this function's C shim for the full pipeline).
-- /index/\//nominalTermStructure/ price the null-vol engine the stripper solves against; /slope/
-- is the assumed initial caplet-vol slope for strikes past the edge of good price data (a
-- negative slope for typically low\/flat short-dated extreme-strike prices, per upstream's own
-- comment -- too extreme a slope can leave no arbitrage-free solution).
{#fun qlKInterpolatedYoYOptionletVolatilitySurfaceBlack as kInterpolatedYoYOptionletVolatilitySurfaceBlack{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDayCounter*`DayCounter'
  ,withGenTermStructure*`YoYCapFloorTermPriceSurface' -- ^capFloorPrices
  ,withYoYInflationIndex*`YoYInflationIndex' -- ^index
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,`Double' -- ^slope
  ,preErrorCheck-`String'errorCheck*-}->`YoYOptionletVolatilitySurface'peekYoYOptionletVolatilityStructure*#}

-- |As 'kInterpolatedYoYOptionletVolatilitySurfaceBlack', but unit-displaced Black.
{#fun qlKInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack as kInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDayCounter*`DayCounter'
  ,withGenTermStructure*`YoYCapFloorTermPriceSurface' -- ^capFloorPrices
  ,withYoYInflationIndex*`YoYInflationIndex' -- ^index
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,`Double' -- ^slope
  ,preErrorCheck-`String'errorCheck*-}->`YoYOptionletVolatilitySurface'peekYoYOptionletVolatilityStructure*#}

-- |As 'kInterpolatedYoYOptionletVolatilitySurfaceBlack', but Bachelier (normal model).
{#fun qlKInterpolatedYoYOptionletVolatilitySurfaceBachelier as kInterpolatedYoYOptionletVolatilitySurfaceBachelier{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDayCounter*`DayCounter'
  ,withGenTermStructure*`YoYCapFloorTermPriceSurface' -- ^capFloorPrices
  ,withYoYInflationIndex*`YoYInflationIndex' -- ^index
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,`Double' -- ^slope
  ,preErrorCheck-`String'errorCheck*-}->`YoYOptionletVolatilitySurface'peekYoYOptionletVolatilityStructure*#}

-- |Prices CPI cap\/floors by interpolation and put\/call parity off a market strike\/maturity
-- price grid. 'Interpolation2D' chooses the cap\/floor price-grid interpolator. @cPrice@\/
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
  -> Interpolation2D
  -> IO CPICapFloorTermPriceSurface
cpiCapFloorTermPriceSurface nom baseRate obsLag cal bdc dc zii interp yts cStrikes fStrikes cfMaturities (Matrix cr cc cd) (Matrix fr fc fd) i2d =
  qlCPICapFloorTermPriceSurface nom baseRate obsLag cal bdc dc zii interp yts cStrikes fStrikes maturityNums maturityUnits cr cc cd fr fc fd (fromEnum i2d)
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
  ,`Int' -- ^interpolator2D
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
