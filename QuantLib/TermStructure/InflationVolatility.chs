module QuantLib.TermStructure.InflationVolatility
  (
    -- * Types
    YoYOptionletVolatilitySurface
  , YoYCapFloorTermPriceSurface
  , CPICapFloorTermPriceSurface
  , CPIVolatilitySurface
    -- ** Pricing model
  , YoyOptionletModel(..)

    -- * Constructors
    -- ** YoY volatility and price surfaces
  , constantYoyOptionletVolatility
  , kInterpolatedYoyOptionletVolatilitySurface
  , yoyCapFloorTermPriceSurface
    -- ** CPI surfaces
  , cpiCapFloorTermPriceSurface
  , constantCpiVolatility

    -- * Inspectors
    -- ** YoY volatility
  , yoyOptionletVolatility
  , yoyOptionletTotalVariance
    -- ** YoY cap-floor prices
  , yoyCapFloorBaseDate
  , yoyCapFloorAtmYoySwapDateRates
  , yoyCapFloorAtmYoySwapTimeRates
  , yoyCapFloorAtmYoySwapRate
  , yoyCapFloorAtmYoyRate
  , yoyCapFloorStrikes
    -- ** CPI volatility
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
-- 'QuantLib.TermStructure.Volatility.constantOptionletVolatility', taking a t'GenQuote' rather
-- than a plain 'Double' per the @std::variant@\/overload-collapse rule (the flat case is already
-- reachable via 'QuantLib.Quote.simpleQuote'). Not the only concrete leaf of this type any
-- more -- see 'kInterpolatedYoyOptionletVolatilitySurface' for the market-quote-bootstrapped
-- alternative.
{#fun qlConstantYoYOptionletVolatility as constantYoyOptionletVolatility{withQuote*`GenQuote q'
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
--
-- @Nothing@ preserves QuantLib's moving reference date and swap helpers. @Just start@
-- books the price grid at the current evaluation date; any other @start@ is refused. Its reference
-- date is fixed at construction and its derived ATM curve uses QuantLib fixed-start swap helpers,
-- with the same native pillar dates. This prevents later process-date restoration from rebuilding
-- a swap after its maturity. Rebuild a booked grid to value it on another evaluation date.
-- The intersection, parity, interpolation and bootstrapping calculations remain QuantLib's.
yoyCapFloorTermPriceSurface :: Maybe Day -- ^Fixed swap start, equal to the construction evaluation date; Nothing selects moving dates.
  -> Word -- ^fixingDays
  -> (Word, TimeUnit) -- ^yyLag
  -> GenYoYInflationIndex yidx -> CPIInterpolationType -> GenYieldTermStructure y -- ^nominal
  -> DayCounter -> Calendar -> BusinessDayConvention
  -> [Double] -- ^cStrikes
  -> [Double] -- ^fStrikes
  -> [(Word, TimeUnit)] -- ^cfMaturities
  -> RealMatrix -- ^cPrice
  -> RealMatrix -- ^fPrice
  -> Interpolation2D -> Interpolation
  -> IO YoYCapFloorTermPriceSurface
yoyCapFloorTermPriceSurface startDate fixingDays yyLag yii interp nominal dc cal bdc cStrikes fStrikes cfMaturities (RealMatrix cr cc cd) (RealMatrix fr fc fd) i2d i1d =
  uncurryNested (qlYoYCapFloorTermPriceSurface startDate fixingDays yyLag yii interp nominal dc cal bdc cStrikes fStrikes maturityNums maturityUnits cr cc cd fr fc fd (fromEnum i2d)) (qlInterpolation i1d)
  where (maturityNums, maturityUnits) = unzip cfMaturities
{#fun qlYoYCapFloorTermPriceSurface{withMaybeDay*`Maybe Day' -- ^Fixed start, or moving dates.
  ,fromIntegral`Word' -- ^fixingDays
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^yyLag
  ,withYoYInflationIndex*`GenYoYInflationIndex yidx'
  ,fromEnumC`CPIInterpolationType'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominal
  ,withDayCounter*`DayCounter'
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention'
  ,withDoubleArray*`[Double]'& -- ^cStrikes
  ,withDoubleArray*`[Double]'& -- ^fStrikes
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'& -- ^cfMaturities
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector' -- ^cPrice
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector' -- ^fPrice
  ,`Int' -- ^interpolator2D
  ,`Int',`Int',`Int' -- ^interpolator1D, approximator, approximatorArg
  ,preErrorCheck-`String'errorCheck*-}->`YoYCapFloorTermPriceSurface'peekYoYCapFloorTermPriceSurface*#}

-- |The date the surface's own YoY term structure (and hence any 'YoYOptionletVolatilitySurface'
-- stripped from it) treats as its base -- referenceDate minus the observation lag, rounded to
-- the containing inflation period's start.
{#fun qlYoYCapFloorTermPriceSurfaceBaseDate as yoyCapFloorBaseDate{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |The ATM YoY swap curve derived from cap\/floor-surface intersection, as (date, rate) pairs.
yoyCapFloorAtmYoySwapDateRates :: YoYCapFloorTermPriceSurface -> IO [(Day, Double)]
yoyCapFloorAtmYoySwapDateRates s = do
  (ds, rs) <- qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates s
  return $ zip ds rs
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preIntArray-`[Day]'&peekDayArray*,preDoubleArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The same ATM YoY swap curve as 'yoyCapFloorAtmYoySwapDateRates', but with maturities as year
-- fractions from the surface's reference date rather than dates.
yoyCapFloorAtmYoySwapTimeRates :: YoYCapFloorTermPriceSurface -> IO [(Double, Double)]
yoyCapFloorAtmYoySwapTimeRates s = do
  (ts, rs) <- qlYoYCapFloorTermPriceSurfaceAtmYoYSwapTimeRates s
  return $ zip ts rs
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYSwapTimeRates{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preDoubleArray-`[Double]'&peekDoubleArray*,preDoubleArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The ATM YoY swap rate at the given maturity date, from put\/call parity on the surface's
-- cap\/floor price data.
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYSwapRate as yoyCapFloorAtmYoySwapRate{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,withDay*`Day'
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The ATM YoY inflation rate at the given maturity date and observation lag (or the surface's
-- own lag when 'Nothing'), derived from the swap-rate curve above.
{#fun qlYoYCapFloorTermPriceSurfaceAtmYoYRate as yoyCapFloorAtmYoyRate{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,withDay*`Day'
  ,fromMaybeEnumQuantity`Maybe (Word,TimeUnit)'& -- ^obsLag
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The union of cap and floor strikes in the surface's price grid -- the strikes a stripped
-- 'YoYOptionletVolatilitySurface' (via 'kInterpolatedYoyOptionletVolatilitySurface')
-- has a bootstrapped vol curve for.
{#fun qlYoYCapFloorTermPriceSurfaceStrikes as yoyCapFloorStrikes{withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,preDoubleArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Pricing model for stripping YoY cap/floor price quotes.
{#enum YoyOptionletModel{} deriving(Show, Eq, Read)#}

-- |Strip a native per-strike volatility curve and interpolate across strikes. The optional
-- initial volatility bracket replaces QuantLib's fixed 1e-5 to 0.08 bounds; Nothing uses the
-- unmodified native stripper. An explicit bracket uses its protected native objective, Brent
-- solver (accuracy 1e-7), helpers and piecewise bootstrap, changing only those bounds.
-- Bounds must be finite, positive and strictly ordered. The slope is the native relative
-- initial caplet-volatility slope outside reliable short-end prices. LogCubic is unsupported
-- because the native stripper default-constructs its interpolator. The index and nominal curve
-- price the null-vol engine the stripper solves against.
kInterpolatedYoyOptionletVolatilitySurface
  :: YoyOptionletModel
  -> Word -- ^Business-day settlement lag of the volatility surface.
  -> Calendar -> BusinessDayConvention -> DayCounter
  -> YoYCapFloorTermPriceSurface -- ^Quoted cap/floor term prices to strip.
  -> GenYoYInflationIndex yidx -- ^YoY index used to price the stripping helpers.
  -> GenYieldTermStructure y -- ^Nominal discount curve used to price the stripping helpers.
  -> Double -- ^Initial relative caplet-volatility slope per year.
  -> Maybe (Double, Double) -- ^Optional (lower, upper) initial annual volatility bounds, per square root year: log-rate units for Black, log(1+rate) for unit-displaced Black, absolute decimal-rate units for Bachelier.
  -> Interpolation
  -> IO YoYOptionletVolatilitySurface
kInterpolatedYoyOptionletVolatilitySurface model settlementDays cal bdc dc prices index nominal slope bracket i1d =
  let (useBracket, lower, upper) = case bracket of Nothing -> (False, 1e-5, 0.08); Just (lo, hi) -> (True, lo, hi)
  in uncurryNested (qlKInterpolatedYoYOptionletVolatilitySurface model settlementDays cal bdc dc prices index nominal slope useBracket lower upper) (qlInterpolation i1d)
{#fun qlKInterpolatedYoYOptionletVolatilitySurface{fromEnumC`YoyOptionletModel'
  ,fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter'
  ,withGenTermStructure*`YoYCapFloorTermPriceSurface'
  ,withYoYInflationIndex*`GenYoYInflationIndex yidx'
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,`Double',`Bool',`Double',`Double'
  ,`Int',`Int',`Int'
  ,preErrorCheck-`String'errorCheck*-}->`YoYOptionletVolatilitySurface'peekYoYOptionletVolatilityStructure*#}

-- |Prices CPI cap\/floors by interpolation and put\/call parity off a market strike\/maturity
-- price grid. 'Interpolation2D' chooses the cap\/floor price-grid interpolator. @cPrice@\/
-- @fPrice@ are plain price matrices (rows = strikes, columns = maturities), not quote-linked
-- like 'QuantLib.TermStructure.Volatility.capFloorTermVolSurface's volatility matrix.
cpiCapFloorTermPriceSurface :: Double -- ^nominal
  -> Double -- ^baseRate
  -> (Word, TimeUnit) -- ^observationLag
  -> Calendar -> BusinessDayConvention -> DayCounter
  -> GenZeroInflationIndex zidx -> CPIInterpolationType -> GenYieldTermStructure y
  -> [Double] -- ^cStrikes
  -> [Double] -- ^fStrikes
  -> [(Word, TimeUnit)] -- ^cfMaturities
  -> RealMatrix -- ^cPrice
  -> RealMatrix -- ^fPrice
  -> Interpolation2D
  -> IO CPICapFloorTermPriceSurface
cpiCapFloorTermPriceSurface nom baseRate obsLag cal bdc dc zii interp yts cStrikes fStrikes cfMaturities (RealMatrix cr cc cd) (RealMatrix fr fc fd) i2d =
  qlCPICapFloorTermPriceSurface nom baseRate obsLag cal bdc dc zii interp yts cStrikes fStrikes maturityNums maturityUnits cr cc cd fr fc fd (fromEnum i2d)
  where (maturityNums, maturityUnits) = unzip cfMaturities
{#fun qlCPICapFloorTermPriceSurface{`Double',`Double',fromEnumQuantity`(Word,TimeUnit)'&
  ,withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter'
  ,withZeroInflationIndex*`GenZeroInflationIndex zidx',fromEnumC`CPIInterpolationType'
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,withDoubleArray*`[Double]'& -- ^cStrikes
  ,withDoubleArray*`[Double]'& -- ^fStrikes
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'& -- ^cfMaturities
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector' -- ^cPrice
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector' -- ^fPrice
  ,`Int' -- ^interpolator2D
  ,preErrorCheck-`String'errorCheck*-}->`CPICapFloorTermPriceSurface'peekCPICapFloorTermPriceSurface*#}

-- |Constant CPI (zero-inflation) volatility surface, no maturity\/strike dependence -- the only
-- concrete leaf bound here, mirroring 'constantYoyOptionletVolatility'. No engine or coupon
-- pricer consumes this in QL 1.43 (see this type's own haddock in "QuantLib.Internal.Type"), so
-- it is queryable via 'cpiVolatility'\/'cpiTotalVariance' but not otherwise wired up.
{#fun qlConstantCPIVolatility as constantCpiVolatility{withQuote*`GenQuote q'
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
