module QuantLib.Example.FittedBondCurve
  (
    Result(..)
  , run
  )
where

import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Frequency
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Trait
import QuantLib.Math.Interpolation
import QuantLib.Time.Unit
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.DateGenerationRule
import QuantLib.Types
import QuantLib.Quote


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
  print $ "Bond settlement date" ++ show bondSettle
  cleanQuotes <- mapM simpleQuote cleanPrices
  bondPeriod <- fromFrequency Annual

  helpers <- mapM (\(q, l, c) -> do
    pm <- period l Years
    mat <- advance' cal bondSettle pm Following False
    s <- schedule (Just bondSettle) mat bondPeriod cal
      ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

    qq <- asQuote q
    hA <- fixedRateBondHelper qq (fromIntegral bondSettleDays) 100.0 s [c] dc ModifiedFollowing 100.0 Nothing
    hB <- fixedRateBondHelper qq (fromIntegral bondSettleDays) 100.0 s [c] dc ModifiedFollowing 100.0 Nothing >>= asRateHelper
    return (hA, hB)) $
      zip3 cleanQuotes lengths coupons

  let (instrA, instrB) = unzip helpers

  ts0 <- piecewiseYieldCurve' curveSettleDays cal instrB dc [] 1e-12 Discount LogLinear

  expSplines <- exponentialSplinesFitting True
  ts1 <- fittedBondDiscountCurve curveSettleDays cal instrA dc expSplines tolerance maxEvals
  printOutput ts1

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

    printOutput ts = do
      putStr "Reference date: "
      asYieldTermStructure ts >>= asTermStructure >>= referenceDate >>= print
      putStr "Number of iterations: "
      numberOfIterations ts >>= print
