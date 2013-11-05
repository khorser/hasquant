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
import QuantLib.Instrument.CallabilityType
import QuantLib.InterestRate
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
  { r :: Double
  }

run :: IO Result
run = do
  setEvaluationDate tod
  bbdc <- actualActualBond
  q <- simpleQuote 0.055 >>= asQuote
  flatRate <- flatForward tod q bbdc Compounded Semiannual

  callDates <- reverse <$> foldM buildSchedule [15 `september` 2006] [1 .. 24]
  callSchedule <- mapM (\d -> do
    p <- callabilityPrice 100.0 Clean
    callability p Call d)
    callDates

  return Result {
    r = 0
  }
  where tod = 16 `october` 2007
        
        buildSchedule :: [Day] -> Int -> IO [Day]
        buildSchedule a@(d:_) _i = do
          cal <- nullCalendar
          n <- advance cal d 3 Months Following False
          return $ (n : a)


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
