-- |Historical volatility estimators over caller-supplied return\/price series
-- (@ql\/models\/volatility@, @ql\/prices.hpp@) -- distinct from
-- "QuantLib.TermStructure.Volatility", which covers forward-looking implied-volatility
-- surfaces and smiles. None of these classes have any calculations of their own beyond a
-- single @calculate@ call and are never needed as an argument type elsewhere, so only
-- 'Garch11' -- whose calibrated state ('garch11Alpha' etc.) is queried repeatedly -- gets a
-- dedicated Haskell type; every GarmanKlass variant, 'ConstantEstimator', and
-- 'SimpleLocalEstimator' are bound as a single construct-and-calculate function each.
module QuantLib.VolatilityModel
  (
    Garch11Mode(..)
  , Garch11
  , garch11
  , garch11Calibrated
  , garch11Alpha
  , garch11Beta
  , garch11Omega
  , garch11LtVol
  , garch11LogLikelihood
  , garch11Forecast
  , garch11Calculate

  , garmanKlassSimpleSigma
  , garmanKlassSigma1
  , parkinsonSigma
  , garmanKlassSigma3
  , garmanKlassSigma4
  , garmanKlassSigma5
  , garmanKlassSigma6
  , constantVolatilityEstimator
  , simpleLocalVolatilityEstimator
  ) where
import Data.List.NonEmpty(NonEmpty, toList)
import QuantLib.Internal
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"

{#enum Garch11Mode{} deriving(Show, Eq, Read)#}
{#pointer *Garch11 foreign -> CGarch11 nocode#}

-- |Direct-parameter GARCH(1,1) model: @vl@ is the long-term (unconditional) volatility: the
-- model's persistence @gamma = 1 - alpha - beta@ and @omega = vl * gamma@ are derived from it.
-- Does not calibrate; use 'garch11Calibrated' to fit alpha\/beta\/vl to an observed series.
{#fun qlGarch11 as garch11{`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^vl (long-term volatility)
  ,preErrorCheck-`String'errorCheck*-
  }->`Garch11'peekGarch11*#}

-- |Calibrates a GARCH(1,1) model to an observed return series via maximum likelihood. All four
-- 'Garch11Mode' values converge to the same maximum-likelihood fit for a well-behaved series --
-- they differ only in the initial guess ('MomentMatchingGuess'\/'GammaGuess'), or run both and
-- keep the better ('BestOfTwo', the upstream default) or optimize from each in turn
-- ('DoubleOptimization'). There is no way from Haskell to supply a custom
-- 'OptimizationMethod'\/'EndCriteria' or to re-calibrate an existing model in place (upstream's
-- @calibrate@ overloads are mutators on an already-constructed object); construct a fresh model
-- if a different fit is needed.
garch11Calibrated :: NonEmpty (Day, Double) -- ^observed return series
  -> Garch11Mode -> IO Garch11
garch11Calibrated series = qlGarch11Calibrated dates vals
  where (dates, vals) = unzip (toList series)
{#fun qlGarch11Calibrated{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,`Garch11Mode'
  ,preErrorCheck-`String'errorCheck*-}->`Garch11'peekGarch11*#}

-- |the calibrated (or constructor-supplied) alpha coefficient
{#fun pure qlGarch11Alpha as garch11Alpha{withGarch11*`Garch11'}->`Double'#}
-- |the calibrated (or constructor-supplied) beta coefficient
{#fun pure qlGarch11Beta as garch11Beta{withGarch11*`Garch11'}->`Double'#}
-- |the calibrated (or derived) omega coefficient, @vl * (1 - alpha - beta)@
{#fun pure qlGarch11Omega as garch11Omega{withGarch11*`Garch11'}->`Double'#}
-- |the calibrated (or constructor-supplied) long-term volatility
{#fun pure qlGarch11LtVol as garch11LtVol{withGarch11*`Garch11'}->`Double'#}
-- |the log-likelihood of the calibrated fit; @0@ for a direct-parameter ('garch11') model
{#fun pure qlGarch11LogLikelihood as garch11LogLikelihood{withGarch11*`Garch11'}->`Double'#}

-- |one-step-ahead variance forecast: @gamma*vl + alpha*r^2 + beta*sigma2@, given the latest
-- return @r@ and the previous step's variance @sigma2@.
{#fun pure qlGarch11Forecast as garch11Forecast{withGarch11*`Garch11'
  ,`Double' -- ^r
  ,`Double' -- ^sigma2
  }->`Double'#}

-- |Runs the model's calibrated (or constructor-supplied) alpha\/beta\/omega recursion forward
-- over a return series. The output series is offset by one from the input: the first input
-- point has nothing to forecast from, so it is dropped, and one extra point is extrapolated one
-- step past the input series' last date -- an @n@-point input still produces an @n@-point
-- output, just shifted forward by one date.
garch11Calculate :: Garch11 -> NonEmpty (Day, Double) -- ^return series
  -> IO [(Day, Double)]
garch11Calculate g series = do
  (ds, vs) <- qlGarch11Calculate g dates vals
  return $ zip ds vs
  where (dates, vals) = unzip (toList series)
{#fun qlGarch11Calculate{withGarch11*`Garch11',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Garman-Klass (1980) simple estimator: @sigma^2 = ln(close\/open)^2@, scaled by @yearFraction@.
-- Input bars are @(date, open, close, high, low)@; only open\/close are used here.
garmanKlassSimpleSigma :: Double -- ^yearFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
garmanKlassSimpleSigma yearFraction bars = do
  (ds, vs) <- qlGarmanKlassSimpleSigma yearFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlGarmanKlassSimpleSigma{`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Garman-Klass Sigma1: blends 'garmanKlassSimpleSigma' with the overnight (previous close to
-- today's open) jump, weighted by @marketOpenFraction@ (the fraction of the trading day the
-- market is open). Drops the series' first bar (needs a previous close).
garmanKlassSigma1 :: Double -- ^yearFraction
  -> Double -- ^marketOpenFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
garmanKlassSigma1 yearFraction marketOpenFraction bars = do
  (ds, vs) <- qlGarmanKlassSigma1 yearFraction marketOpenFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlGarmanKlassSigma1{`Double',`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Parkinson (1980) high-low estimator: @sigma^2 = ln(high\/low)^2 \/ (4 ln 2)@, scaled by
-- @yearFraction@. Input bars are @(date, open, close, high, low)@; only high\/low are used here.
parkinsonSigma :: Double -- ^yearFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
parkinsonSigma yearFraction bars = do
  (ds, vs) <- qlParkinsonSigma yearFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlParkinsonSigma{`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Garman-Klass Sigma3: blends 'parkinsonSigma' with the overnight jump, same
-- @marketOpenFraction@ weighting as 'garmanKlassSigma1'. Drops the series' first bar.
garmanKlassSigma3 :: Double -- ^yearFraction
  -> Double -- ^marketOpenFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
garmanKlassSigma3 yearFraction marketOpenFraction bars = do
  (ds, vs) <- qlGarmanKlassSigma3 yearFraction marketOpenFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlGarmanKlassSigma3{`Double',`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Garman-Klass (1980) Sigma4 estimator, combining the high-low range with the close-open
-- return via their published coefficients. Input bars are @(date, open, close, high, low)@.
garmanKlassSigma4 :: Double -- ^yearFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
garmanKlassSigma4 yearFraction bars = do
  (ds, vs) <- qlGarmanKlassSigma4 yearFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlGarmanKlassSigma4{`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Garman-Klass (1980) Sigma5 estimator: an alternative high-low\/close-open combination to
-- 'garmanKlassSigma4', with different published coefficients.
garmanKlassSigma5 :: Double -- ^yearFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
garmanKlassSigma5 yearFraction bars = do
  (ds, vs) <- qlGarmanKlassSigma5 yearFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlGarmanKlassSigma5{`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Garman-Klass Sigma6: blends 'garmanKlassSigma5' with the overnight jump, same
-- @marketOpenFraction@ weighting as 'garmanKlassSigma1'. Drops the series' first bar.
garmanKlassSigma6 :: Double -- ^yearFraction
  -> Double -- ^marketOpenFraction
  -> NonEmpty (Day, Double, Double, Double, Double) -- ^(date, open, close, high, low) price bars
  -> IO [(Day, Double)]
garmanKlassSigma6 yearFraction marketOpenFraction bars = do
  (ds, vs) <- qlGarmanKlassSigma6 yearFraction marketOpenFraction dates opens closes highs lows
  return $ zip ds vs
  where (dates, opens, closes, highs, lows) = unzipBars bars
{#fun qlGarmanKlassSigma6{`Double',`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Smooths an already-computed volatility series with a rolling constant estimate over the
-- trailing @windowSize@ points.
constantVolatilityEstimator :: Word -- ^windowSize
  -> NonEmpty (Day, Double) -- ^volatility series
  -> IO [(Day, Double)]
constantVolatilityEstimator windowSize series = do
  (ds, vs) <- qlConstantVolatilityEstimator windowSize dates vals
  return $ zip ds vs
  where (dates, vals) = unzip (toList series)
{#fun qlConstantVolatilityEstimator{fromIntegral`Word',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Local (point-to-point) volatility estimate from a raw price series: @|ln(p_i\/p_{i-1})| \/
-- sqrt(yearFraction)@ for each consecutive pair. Drops the series' first date; an @n@-point
-- input produces an @(n-1)@-point output.
simpleLocalVolatilityEstimator :: Double -- ^yearFraction
  -> NonEmpty (Day, Double) -- ^price series
  -> IO [(Day, Double)]
simpleLocalVolatilityEstimator yearFraction series = do
  (ds, vs) <- qlSimpleLocalVolatilityEstimator yearFraction dates vals
  return $ zip ds vs
  where (dates, vals) = unzip (toList series)
{#fun qlSimpleLocalVolatilityEstimator{`Double',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

unzipBars :: NonEmpty (Day, Double, Double, Double, Double) -> ([Day], [Double], [Double], [Double], [Double])
unzipBars bars = (map d5 xs, map o5 xs, map c5 xs, map h5 xs, map l5 xs)
  where
    xs = toList bars
    d5 (d,_,_,_,_) = d
    o5 (_,o,_,_,_) = o
    c5 (_,_,c,_,_) = c
    h5 (_,_,_,h,_) = h
    l5 (_,_,_,_,l) = l
