module QuantLib.Example.CallableBond
  (
    Result(..)
  , run
  )
where

import Data.Time.Calendar

import QuantLib.Compounding
import QuantLib.Instances
import QuantLib.Instrument
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

  return Result {
    r = 0
  }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
