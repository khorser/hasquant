module QuantLib.Example.FittedBondCurve
  (
    Result(..)
  , run
  )
where

import Control.Monad(forM_, (>=>))
import Data.Time.Calendar
import Text.Printf

import qualified QuantLib.CashFlow.Leg as CF
import QuantLib.CashFlow.DurationType
import QuantLib.Compounding
import QuantLib.Instrument.Bond
import QuantLib.Math.Interpolation
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Trait
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.Time.Unit
import QuantLib.Instances
import QuantLib.Types

data Result = Result { cleanPriceR :: Double
  } deriving Show

run :: IO Result
run = do
  cal <- nullCalendar
  tod1 <- today
  tod <- adjust cal tod1 Following
  setEvaluationDate tod
  dc <- simple

  p <- period bondSettleDays Days
  bondSettle <- advance' cal tod p Following False
  putStrLn $ "Bond settlement date: " ++ show bondSettle
  cleanQuotes <- mapM simpleQuote cleanPrices

  (iA, iB) <- step1 tod dc cal bondSettle cleanQuotes
                >>= \(ts0, instrA, instrB, curves) ->
                  step2 tod dc cal ts0 instrA instrB curves >> return (drop 1 instrA, drop 1 instrB)

  newtod <- advance cal tod 24 Months ModifiedFollowing False
  setEvaluationDate newtod
  newBondSettle <- advance cal newtod bondSettleDays Days Following False

  (ts00, curves) <- step3 newtod dc cal newBondSettle iA iB
  mapM_ (\(price, q, i) -> do
      b <- underlying i
      ytm <- yield'' b price dc Compounded Annual newtod 1e-10 100 0.05
      dur <- duration' b ytm dc Compounded Annual Modified newtod
      let dp = -dur * price * 5 / 10000
      setValue q (price + dp)) $
        zip3 (drop 1 cleanPrices) (drop 1 cleanQuotes) iA
  printRates ts00 dc newBondSettle newtod curves iA

  return $ Result 5.6
  where
    bondSettleDays = 0
    curveSettleDays = 0
    cleanPrices = replicate 15 100.0
    lengths = [2, 4, 6, 8, 10, 12, 14, 16,
               18, 20, 22, 24, 26, 28, 30]
    coupons = [0.0200, 0.0225, 0.0250, 0.0275, 0.0300,
                0.0325, 0.0350, 0.0375, 0.0400, 0.0425,
                0.0450, 0.0475, 0.0500, 0.0525, 0.0550]
    tolerance = 1e-10
    maxEvals = 5000

    parRate :: YieldTermStructure -> [Day] -> DayCounter -> IO ()
    parRate ts ds dc = do
      dfs <- mapM (\(d1, d2) -> do
              dt <- yearFraction dc d1 d2 d1 d2
              df <- TS.discount ts d2 False
              return $ df * dt) $
                zip (init ds) (drop 1 ds)
      df1 <- TS.discount ts (head ds) False
      df2 <- TS.discount ts (last ds) False
      printf "%.3f " $ 100.0 * (df1 - df2) / sum dfs

    printRates ts0 dc bondSettle tod curves instrA = do
      refDate <- asTermStructure ts0 >>= TS.referenceDate
      _ <- printf "Reference date: %s, iterations: " $ show refDate
      forM_ curves (TS.numberOfIterations >=> printf "%d ")
      putStrLn ""

      forM_ instrA $
        \h -> do
          bcfs <- underlying h >>= cashFlows
          let (Right cfs) = CF.cashFlows bcfs False bondSettle
          let ds = map (\(_, d, _) -> d) $ filter (\(_, _, oc) -> not oc) cfs
          _ <- yearFraction dc tod (last ds) tod (last ds) >>= printf "Tenor %5.2fY: "
          parRate ts0 (bondSettle:ds) dc
          forM_ curves $
            \c -> do
              ts <- asYieldTermStructure c
              parRate ts (bondSettle:ds) dc
          putStrLn ""

    step1 tod dc cal bondSettle cleanQuotes = do
      helpers <- mapM (\(q, l, c) -> do
        mat <- advance cal bondSettle l Years Following False
        bondPeriod <- fromFrequency Annual
        s <- schedule (Just bondSettle) mat bondPeriod cal
          ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

        qq <- asQuote q
        hA <- TS.fixedRateBondHelper qq (fromIntegral bondSettleDays) 100.0 s [c] dc ModifiedFollowing 100.0 Nothing
        hB <- TS.fixedRateBondHelper qq (fromIntegral bondSettleDays) 100.0 s [c] dc ModifiedFollowing 100.0 Nothing
                >>= asRateHelper
        return (hA, hB)) $
          zip3 cleanQuotes lengths coupons

      let (instrA, instrB) = unzip helpers

      ts0 <- TS.piecewiseYieldCurve' curveSettleDays cal instrB dc [] 1e-12 Discount LogLinear

      -- results depend on optimization options used to build QLC
      fittings <- sequence [TS.exponentialSplinesFitting True,
                    TS.simplePolynomialFitting 3 True,
                    TS.nelsonSiegelFitting,
                    TS.cubicBSplinesFitting [-30.0, -20.0,  0.0,  5.0, 10.0, 15.0, 20.0,  25.0, 30.0, 40.0, 50.0] True,
                    TS.svenssonFitting]

      curves <- mapM
          (\f -> TS.fittedBondDiscountCurve curveSettleDays cal instrA dc f tolerance maxEvals [] 1.0)
          fittings
      printRates ts0 dc bondSettle tod curves instrA
      return (ts0, instrA, instrB, curves)

    step2 tod dc cal ts0 instrA _ curves = do
      newtoday <- advance cal tod 23 Months ModifiedFollowing False
      setEvaluationDate newtoday
      bondSettle <- advance cal newtoday bondSettleDays Days Following False

      printRates ts0 dc bondSettle newtoday curves instrA


    step3 tod dc cal bondSettle iA iB = do
      ts00 <- TS.piecewiseYieldCurve' curveSettleDays cal iB dc [] 1e-12 Discount LogLinear

      -- results depend on optimization options used to build QLC
      fittings <- sequence [TS.exponentialSplinesFitting True,
                    TS.simplePolynomialFitting 3 True,
                    TS.nelsonSiegelFitting,
                    TS.cubicBSplinesFitting [-30.0, -20.0,  0.0,  5.0, 10.0, 15.0, 20.0,  25.0, 30.0, 40.0, 50.0] True,
                    TS.svenssonFitting]

      curves <- mapM
          (\f -> TS.fittedBondDiscountCurve curveSettleDays cal iA dc f tolerance maxEvals [] 1.0)
          fittings
      printRates ts00 dc bondSettle tod curves iA
      return (ts00, curves)

{- QuantLib FittedBond example output for version 1.2.1 built with -O3

Today's date: February 19th, 2013
Bonds' settlement date: February 19th, 2013
Calculating fit for 15 bonds.....

(a) exponential splines
reference date : February 19th, 2013
number of iterations : 6498

(b) simple polynomial
reference date : February 19th, 2013
number of iterations : 306

(c) Nelson-Siegel
reference date : February 19th, 2013
number of iterations : 1144

(d) cubic B-splines
reference date : February 19th, 2013
number of iterations : 649

(e) Svensson
reference date : February 19th, 2013
number of iterations : 4225

Output par rates for each curve. In this case,
par rates should equal coupons for these par bonds.

 tenor | coupon | bstrap |    (a) |    (b) |    (c) |    (d) |    (e)
 2.000 |  2.000 |  2.000 |  2.000 |  2.010 |  2.060 |  1.771 |  2.008
 4.000 |  2.250 |  2.250 |  2.250 |  2.256 |  2.266 |  2.398 |  2.225
 6.000 |  2.500 |  2.500 |  2.500 |  2.501 |  2.484 |  2.657 |  2.511
 8.000 |  2.750 |  2.750 |  2.750 |  2.747 |  2.716 |  2.748 |  2.771
10.000 |  3.000 |  3.000 |  3.000 |  2.993 |  2.960 |  2.905 |  3.012
12.000 |  3.250 |  3.250 |  3.250 |  3.241 |  3.214 |  3.195 |  3.247
14.000 |  3.500 |  3.500 |  3.500 |  3.491 |  3.477 |  3.521 |  3.486
16.000 |  3.750 |  3.750 |  3.750 |  3.743 |  3.746 |  3.796 |  3.731
18.000 |  4.000 |  4.000 |  4.000 |  3.996 |  4.017 |  4.016 |  3.985
20.000 |  4.250 |  4.250 |  4.250 |  4.252 |  4.286 |  4.232 |  4.245
22.000 |  4.500 |  4.500 |  4.500 |  4.507 |  4.548 |  4.478 |  4.510
24.000 |  4.750 |  4.750 |  4.750 |  4.761 |  4.797 |  4.745 |  4.772
26.000 |  5.000 |  5.000 |  5.000 |  5.011 |  5.028 |  5.014 |  5.025
28.000 |  5.250 |  5.250 |  5.250 |  5.254 |  5.236 |  5.267 |  5.258
30.000 |  5.500 |  5.500 |  5.500 |  5.485 |  5.416 |  5.485 |  5.464



Now add 23 months to today. Par rates should be
automatically recalculated because today's date
changes.  Par rates will NOT equal coupons (YTM
will, with the correct compounding), but the
piecewise yield curve par rates can be used as
a benchmark for correct par rates.

(a) exponential splines
reference date : January 19th, 2015
number of iterations : 1459

(b) simple polynomial
reference date : January 19th, 2015
number of iterations : 263

(c) Nelson-Siegel
reference date : January 19th, 2015
number of iterations : 980

(d) cubic B-splines
reference date : January 19th, 2015
number of iterations : 640

(e) Svensson
reference date : January 19th, 2015
number of iterations : 3061



 tenor | coupon | bstrap |    (a) |    (b) |    (c) |    (d)
 0.083 |  2.000 |  1.964 |  1.969 |  1.983 |  2.025 |  1.311 |  1.964
 2.083 |  2.250 |  2.248 |  2.242 |  2.249 |  2.256 |  2.333 |  2.235
 4.083 |  2.500 |  2.499 |  2.497 |  2.496 |  2.481 |  2.909 |  2.530
 6.083 |  2.750 |  2.749 |  2.749 |  2.743 |  2.717 |  3.013 |  2.765
 8.083 |  3.000 |  2.999 |  3.001 |  2.991 |  2.963 |  2.949 |  2.996
10.083 |  3.250 |  3.249 |  3.251 |  3.240 |  3.217 |  3.053 |  3.233
12.083 |  3.500 |  3.499 |  3.501 |  3.490 |  3.479 |  3.404 |  3.477
14.083 |  3.750 |  3.749 |  3.750 |  3.743 |  3.746 |  3.804 |  3.730
16.083 |  4.000 |  4.000 |  4.000 |  3.997 |  4.014 |  4.089 |  3.990
18.083 |  4.250 |  4.250 |  4.249 |  4.252 |  4.281 |  4.268 |  4.254
20.083 |  4.500 |  4.500 |  4.498 |  4.508 |  4.541 |  4.454 |  4.518
22.083 |  4.750 |  4.750 |  4.748 |  4.761 |  4.790 |  4.718 |  4.776
24.083 |  5.000 |  5.000 |  4.999 |  5.011 |  5.025 |  5.014 |  5.023
26.083 |  5.250 |  5.249 |  5.250 |  5.254 |  5.239 |  5.277 |  5.253
28.083 |  5.500 |  5.499 |  5.500 |  5.484 |  5.430 |  5.485 |  5.460



Now add one more month, for a total of two years
from the original date. The first instrument is
now expired and par rates should again equal
coupon values, since clean prices did not change.

(a) exponential splines
reference date : February 19th, 2015
number of iterations : 6727

(b) simple polynomial
reference date : February 19th, 2015
number of iterations : 278

(c) Nelson-Siegel
reference date : February 19th, 2015
number of iterations : 1139

(d) cubic B-splines
reference date : February 19th, 2015
number of iterations : 785

(e) Svensson
reference date : February 19th, 2015
number of iterations : 3624

 tenor | coupon | bstrap |    (a) |    (b) |    (c) |    (d) |    (e)
 2.000 |  2.250 |  2.250 |  2.246 |  2.260 |  2.295 |  2.008 |  2.255
 4.000 |  2.500 |  2.500 |  2.501 |  2.505 |  2.508 |  2.655 |  2.483
 6.000 |  2.750 |  2.750 |  2.753 |  2.750 |  2.734 |  2.916 |  2.760
 8.000 |  3.000 |  3.000 |  3.003 |  2.995 |  2.972 |  2.998 |  3.014
10.000 |  3.250 |  3.250 |  3.251 |  3.242 |  3.219 |  3.150 |  3.256
12.000 |  3.500 |  3.500 |  3.499 |  3.491 |  3.476 |  3.444 |  3.495
14.000 |  3.750 |  3.750 |  3.748 |  3.742 |  3.738 |  3.775 |  3.738
16.000 |  4.000 |  4.000 |  3.997 |  3.996 |  4.005 |  4.049 |  3.987
18.000 |  4.250 |  4.250 |  4.248 |  4.250 |  4.271 |  4.262 |  4.243
20.000 |  4.500 |  4.500 |  4.499 |  4.505 |  4.533 |  4.476 |  4.503
22.000 |  4.750 |  4.750 |  4.751 |  4.760 |  4.786 |  4.732 |  4.763
24.000 |  5.000 |  5.000 |  5.003 |  5.010 |  5.025 |  5.006 |  5.017
26.000 |  5.250 |  5.250 |  5.252 |  5.254 |  5.245 |  5.266 |  5.258
28.000 |  5.500 |  5.500 |  5.497 |  5.487 |  5.442 |  5.492 |  5.478



Now decrease prices by a small amount, corresponding
to a theoretical five basis point parallel + shift of
the yield curve. Because bond quotes change, the new
par rates should be recalculated automatically.

 tenor | coupon | bstrap |    (a) |    (b) |    (c) |    (d) |    (e)
 2.000 |  2.250 |  2.300 |  2.297 |  2.311 |  2.345 |  2.055 |  2.305
 4.000 |  2.500 |  2.550 |  2.552 |  2.555 |  2.558 |  2.706 |  2.533
 6.000 |  2.750 |  2.800 |  2.802 |  2.799 |  2.784 |  2.968 |  2.810
 8.000 |  3.000 |  3.050 |  3.051 |  3.044 |  3.021 |  3.047 |  3.064
10.000 |  3.250 |  3.299 |  3.300 |  3.291 |  3.268 |  3.198 |  3.305
12.000 |  3.500 |  3.549 |  3.548 |  3.540 |  3.524 |  3.492 |  3.543
14.000 |  3.750 |  3.798 |  3.796 |  3.791 |  3.787 |  3.824 |  3.786
16.000 |  4.000 |  4.048 |  4.045 |  4.044 |  4.053 |  4.097 |  4.035
18.000 |  4.250 |  4.298 |  4.296 |  4.298 |  4.319 |  4.309 |  4.291
20.000 |  4.500 |  4.547 |  4.547 |  4.553 |  4.581 |  4.523 |  4.550
22.000 |  4.750 |  4.797 |  4.798 |  4.807 |  4.833 |  4.778 |  4.810
24.000 |  5.000 |  5.046 |  5.049 |  5.057 |  5.072 |  5.053 |  5.063
26.000 |  5.250 |  5.296 |  5.298 |  5.300 |  5.291 |  5.312 |  5.304
28.000 |  5.500 |  5.545 |  5.542 |  5.532 |  5.486 |  5.537 |  5.523

Run completed in 11 s
-}

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
