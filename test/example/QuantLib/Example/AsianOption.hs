{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Example.AsianOption
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar

import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Option
import QuantLib.Math
import QuantLib.Model()
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date hiding(today)
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Syntax

-- | Discrete arithmetic average-price Asian put, reproducing the 26-fixing
-- case from QuantLib's own @asianoptions.cpp@ (@testMCDiscreteArithmeticAveragePrice@,
-- data from Levy 1997 as reproduced by Haug): spot 90, strike 87, dividend
-- yield 6%, risk-free rate 2.5%, 11\/12y to maturity, 13% vol, expected NPV
-- 1.7255070456. Cross-checks 'turnbullWakemanAsianEngine' and
-- 'fdBlackScholesAsianEngine' (this module's two new engines) against the
-- already-bound 'mcDiscreteArithmeticAPEngine' on the same instrument.
data Result = Result
  { twR :: Double
  , fdR :: Double
  , mcR :: Double
  }

run :: IO Result
run = do
  setEvaluationDate $ Just today
  dc <- dayCounter (Actual360 False)
  underQ <- simpleQuote 90
  divQ <- simpleQuote 0.06
  riskFreeQ <- simpleQuote 0.025
  ts <- flatForward today riskFreeQ dc Continuous Annual
  divTS <- flatForward today divQ dc Continuous Annual
  volQ <- simpleQuote 0.13
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) today volQ dc
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False

  let payoff = PlainVanilla $ PlainVanillaPayoff Put strike
      exercise = European $ EuropeanExercise maturity
  option <- discreteAveragingAsianOption Arithmetic 0.0 0 fixingDates payoff exercise

  twEng <- turnbullWakemanAsianEngine bsmProc
  QuantLib.Instrument.setPricingEngine option twEng
  tw <- npv option

  fdEng <- fdBlackScholesAsianEngine bsmProc 100 100 100 Douglas
  QuantLib.Instrument.setPricingEngine option fdEng
  fd <- npv option

  mcEng <- mcDiscreteArithmeticAPEngine LowDiscrepancy Statistics bsmProc False False True (Just 2047) Nothing Nothing 0
  QuantLib.Instrument.setPricingEngine option mcEng
  mc <- npv option

  return Result { twR = tw, fdR = fd, mcR = mc }
  where
    today = 1 `january` 2020
    strike = 87
    fixings = 26 :: Int
    len = 11 / 12 :: Double
    dt = len / fromIntegral (fixings - 1)
    -- matches upstream's `timeToDays(t, 360) = lround(t * 360)`
    timeToDays t = round (t * 360 :: Double)
    fixingDates = [addDays (timeToDays (fromIntegral i * dt)) today | i <- [0 .. fixings - 1]]
    maturity = last fixingDates

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
