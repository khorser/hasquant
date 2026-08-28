{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Example.ForwardOption
  (
    Result(..)
  , run
  ) where

import Data.Time.Calendar

import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Option
import QuantLib.Math
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

-- | Forward-starting (\"cliquet-style\") vanilla options, reproducing
-- QuantLib's own @forwardoption.cpp@ @testValues@ golden case (Haug,
-- \"Option pricing formulas\", p.37\/VBA code): moneyness 1.1, spot 60,
-- dividend yield 4%, risk-free rate 8%, reset in 0.25y, maturity in 1y,
-- 30% vol; expected NPV 4.4064 (call) \/ 8.2971 (put) under
-- 'forwardEuropeanEngine' (the @AnalyticEuropeanEngine@ instantiation of
-- @ForwardVanillaEngine\<Engine\>@). The other 5 forward-starting engines
-- added alongside it are exercised as self-consistency checks against this
-- reference: the finite-differences and Monte Carlo European forward
-- engines should reproduce the same (European-exercise) price; the two
-- American approximation engines, priced on an otherwise identical
-- American-exercise instrument, should be at least as valuable as the
-- European price (the right to exercise early is never a disadvantage);
-- and the Heston forward engine, with its process parameters chosen so
-- Heston degenerates to (near-)deterministic Black-Scholes volatility,
-- should reproduce the same price as the BS analytic engine.
data Result = Result
  { europeanCallR :: Double
  , europeanPutR :: Double
  , fdEuropeanR :: Double
  , mcEuropeanR :: Double
  , hestonEuropeanR :: Double
  , bawAmericanR :: Double
  , bjsAmericanR :: Double
  }

run :: IO Result
run = do
  setEvaluationDate $ Just today
  dc <- dayCounter (Actual360 False)
  spotQ <- simpleQuote spot
  qQ <- simpleQuote divYield
  rQ <- simpleQuote riskFreeRate
  qTS <- flatForward today qQ dc Continuous Annual
  rTS <- flatForward today rQ dc Continuous Annual
  volQ <- simpleQuote vol
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) today volQ dc
  bsmProc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

  let payoff t = PlainVanilla $ PlainVanillaPayoff t 0.0
      europeanExercise = European $ EuropeanExercise maturity
      americanExercise = American Nothing maturity False

  callOpt <- forwardVanillaOption moneyness resetDate (payoff Call) europeanExercise
  putOpt <- forwardVanillaOption moneyness resetDate (payoff Put) europeanExercise

  europeanEng <- forwardEuropeanEngine bsmProc
  QuantLib.Instrument.setPricingEngine callOpt europeanEng
  europeanCall <- npv callOpt
  QuantLib.Instrument.setPricingEngine putOpt europeanEng
  europeanPut <- npv putOpt

  fdEng <- forwardFdBlackScholesVanillaEngine bsmProc
  QuantLib.Instrument.setPricingEngine callOpt fdEng
  fdEuropean <- npv callOpt

  mcEng <- mcForwardEuropeanBSEngine LowDiscrepancy Statistics bsmProc (Just 1) Nothing False False (Just 32768) Nothing Nothing 0
  QuantLib.Instrument.setPricingEngine callOpt mcEng
  mcEuropean <- npv callOpt

  hestonProc <- hestonProcess rTS (Just qTS) spotQ (vol*vol) 1.0 (vol*vol) 0.3 0.0 QuadraticExponentialMartingale
  hestonEng <- analyticHestonForwardEuropeanEngine hestonProc 144
  QuantLib.Instrument.setPricingEngine callOpt hestonEng
  hestonEuropean <- npv callOpt

  americanOpt <- forwardVanillaOption moneyness resetDate (payoff Call) americanExercise
  bawEng <- forwardBaroneAdesiWhaleyEngine bsmProc
  QuantLib.Instrument.setPricingEngine americanOpt bawEng
  bawAmerican <- npv americanOpt

  bjsEng <- forwardBjerksundStenslandEngine bsmProc
  QuantLib.Instrument.setPricingEngine americanOpt bjsEng
  bjsAmerican <- npv americanOpt

  return Result
    { europeanCallR = europeanCall
    , europeanPutR = europeanPut
    , fdEuropeanR = fdEuropean
    , mcEuropeanR = mcEuropean
    , hestonEuropeanR = hestonEuropean
    , bawAmericanR = bawAmerican
    , bjsAmericanR = bjsAmerican
    }
  where
    today = 1 `january` 2020
    moneyness = 1.1
    spot = 60
    divYield = 0.04
    riskFreeRate = 0.08
    vol = 0.30
    -- matches upstream's `timeToDays(t, 360) = lround(t * 360)`
    timeToDays t = round (t * 360.0)
    resetDate = addDays (timeToDays (0.25 :: Double)) today
    maturity = addDays (timeToDays (1.0 :: Double)) today

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
