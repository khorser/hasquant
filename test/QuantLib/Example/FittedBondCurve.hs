module QuantLib.Example.FittedBondCurve
  (
    Result(..)
  , run
  )
where

import Control.Monad(forM_)
import Data.Time.Calendar

import QuantLib.CashFlow.Leg
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
import QuantLib.Types


data Result = Result
  { cleanPriceR :: Double
  } deriving Show

run :: IO Result
run = do
  cal <- nullCalendar
  tod1 <- today
  tod <- adjust cal tod1 Following
  setEvaluationDate (Just tod)
  dc <- simple
  
  p <- period bondSettleDays Days
  bondSettle <- advance' cal tod p Following False
  putStrLn $ "Bond settlement date" ++ show bondSettle
  cleanQuotes <- mapM simpleQuote cleanPrices
  bondPeriod <- fromFrequency Annual

  helpers <- mapM (\(q, l, c) -> do
    pm <- period l Years
    mat <- advance' cal bondSettle pm Following False
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

  -- results do not quite match with FittedBondCurve QuantLib example
  -- if QLC is built with optimization level different from QuantLib
  fittings <- sequence [TS.exponentialSplinesFitting True,
                TS.simplePolynomialFitting 3 True,
                TS.nelsonSiegelFitting,
                TS.cubicBSplinesFitting [-30.0, -20.0,  0.0,  5.0, 10.0, 15.0, 20.0,  25.0, 30.0, 40.0, 50.0] True,
                TS.svenssonFitting]

  firstIter <- mapM
      (\f -> TS.fittedBondDiscountCurve curveSettleDays cal instrA dc f tolerance maxEvals)
      fittings
  forM_ firstIter printOutput
  let ci = [(c, i) | c<-firstIter, i<-instrA]
  forM_ ci $
    \(fbts, h) -> do
      cfs <- TS.bond h >>= cashflows >>= \l -> cashFlows l False (Just bondSettle)
      let ds = map (\(_, d, _) -> d) $ filter (\(_, _, oc) -> not oc) cfs
      ts <- asYieldTermStructure fbts
      parRate ts (bondSettle:ds) dc

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

    printOutput :: FittedBondDiscountCurve -> IO ()
    printOutput ts = do
      putStr "Reference date: "
      yts <- asYieldTermStructure ts
      asTermStructure yts >>= TS.referenceDate >>= print
      putStr "Number of iterations: "
      TS.numberOfIterations ts >>= print

    parRate :: YieldTermStructure -> [Day] -> DayCounter -> IO ()
    parRate ts ds dc = do
      dfs <- mapM (\(d1, d2) -> do
              dt <- yearFraction dc d1 d2 Nothing Nothing
              df <- TS.discount ts d2 False
              return $ df * dt) $
                zip (drop 1 ds) (init ds)
      df1 <- TS.discount ts (head ds) False
      df2 <- TS.discount ts (last ds) False
      putStrLn $ "Par rate: " ++ (show $ (df1 - df2) / sum dfs)
