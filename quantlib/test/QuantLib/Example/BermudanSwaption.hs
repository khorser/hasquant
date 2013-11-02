module QuantLib.Example.BermudanSwaption
  (
    Result(..)
  , run
  )
where

import QuantLib.Compounding
import QuantLib.Index.Ibor
import QuantLib.Quote
import QuantLib.Settings
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
import QuantLib.TermStructure.Yield

data Result = Result
  { g2a :: Double
  , g2sigma :: Double
  , g2b :: Double
  , g2eta :: Double
  , g2rho :: Double
  , g2npv :: (Double, Double)
  , hwa :: Double
  , hwsigma :: Double
  , hwnpv :: (Double, Double)
  , hw2a :: Double
  , hw2sigma :: Double
  , hw2npv :: (Double, Double)
  , bka :: Double
  , bksigma :: Double
  , bknpv :: (Double, Double)
  }

run :: IO Result
run = do
  cal <- target
  setEvaluationDate tod
  flatRate <- simpleQuote 0.04875825 >>= asQuote
  dc365 <- actual365Fixed
  ts <- flatForward settl flatRate dc365 Continuous Annual
  fixedDc <- thirty360European
  index6M <- euribor6M $ Just ts
  start <- advance cal settl 1 Years floatConv False
  maturity <- advance cal start 5 Years floatConv False
  fixedPeriod <- fromFrequency fixedFreq
  floatPeriod <- fromFrequency floatFreq
  fixedSchedule <- schedule (Just start) maturity fixedPeriod cal fixedConv fixedConv Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity fixedPeriod cal floatConv floatConv Forward False Nothing Nothing

  return Result {
    g2a = 0
  , g2sigma = 0
  , g2b = 0
  , g2eta = 0
  , g2rho = 0
  , g2npv = (0, 0)
  , hwa = 0
  , hwsigma = 0
  , hwnpv = (0, 0)
  , hw2a = 0
  , hw2sigma = 0
  , hw2npv = (0, 0)
  , bka = 0
  , bksigma = 0
  , bknpv = (0, 0)
  }
  where tod = 15 `february` 2002
        settl = 19 `february` 2002
        numRows = 5
        numCols = 5
        swapLenghts = [1, 2, 3, 4, 5]
        swaptionVols = [0.1490, 0.1340, 0.1228, 0.1189, 0.1148,
          0.1290, 0.1201, 0.1146, 0.1108, 0.1040,
          0.1149, 0.1112, 0.1070, 0.1010, 0.0957,
          0.1047, 0.1021, 0.0980, 0.0951, 0.1270,
          0.1000, 0.0950, 0.0900, 0.1230, 0.1160]
        fixedFreq = Annual
        fixedConv = Unadjusted
        floatConv = ModifiedFollowing
        floatFreq = Semiannual
        dummyFixRate = 0.03

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
