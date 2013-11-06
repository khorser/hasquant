module QuantLib.Example.CallableBond
  (
    Result(..)
  , run
  )
where

import Control.Applicative((<$>))
import Control.Monad(foldM)
import Data.Time.Calendar

import QuantLib.Compounding
import QuantLib.Instances
import QuantLib.Instrument
import QuantLib.Instrument.Bond
import QuantLib.Instrument.CallabilityType
import QuantLib.Model
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Settings
import QuantLib.TermStructure.Yield
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
  { pricesR :: [Double]
  , yieldsR :: [Double]
  }

run :: IO Result
run = do
  setEvaluationDate tod
  bbdc <- actualActualBond
  q <- simpleQuote 0.055 >>= asQuote
  flatRate <- flatForward tod q bbdc Compounded Semiannual

  callDates <- reverse <$> foldM buildSchedule [15 `september` 2006] [1 .. 23]
  callSchedule <- mapM (\d -> do
    p <- callabilityPrice 100.0 Clean
    callability p Call d)
    callDates

  pQ <- fromFrequency Quarterly
  cal <- unitedStatesGovernmentBond
  sch <- schedule (Just $ 16 `september` 2004) (15 `september` 2012) pQ cal Unadjusted Unadjusted Backward False Nothing Nothing

  b <- callableFixedRateBond 3 100.0 sch [0.0465] bbdc Unadjusted 100.0 (Just $ 16 `september` 2004) callSchedule >>= asBond

  (ps, ys) <- unzip <$> mapM (priceBond flatRate bbdc b) [qlEpsilon, 0.01, 0.03, 0.06, 0.12]

  return Result {
    pricesR = ps
  , yieldsR = ys
  }
  where tod = 16 `october` 2007
        
        buildSchedule :: [Day] -> Int -> IO [Day]
        buildSchedule a@(d:_) _i = do
          cal <- nullCalendar
          n <- advance cal d 3 Months Following False
          return (n : a)
        buildSchedule [] _ = error "Impossible happened"

        priceBond ts dc b sigma = do
          hw <- hullWhite ts 0.03 sigma >>= asOneFactorAffineModel >>= asShortRateModel
          engine <- treeCallableFixedRateBondEngine hw 40 Nothing
          asInstrument b >>= (`setPricingEngine` engine)
          cp <- cleanPriceNow b
          y <- yield b dc Compounded Quarterly 1.0e-8 1000
          return (cp, 100 * y)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
