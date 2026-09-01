module QuantLib.Example.RiskyBond
  (
    Result(..)
  , run
  ) where
import Data.List.NonEmpty(fromList)
import QuantLib.InterestRate
import QuantLib.Instrument
import QuantLib.Instrument.Bond
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Credit hiding(hazardRate, defaultProbability)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

data Result = Result
  { npvR :: Double
  , cleanPriceR :: Double
  }

-- ported from ~/Src/QuantLib/test-suite/bonds.cpp:testRiskyBondWithGivenDates
run :: IO Result
run = do
  target <- calendar TARGET
  usGovBond <- calendar UnitedStatesGovernmentBond
  evalDate <- adjust target (22 `november` 2005) Following
  setEvaluationDate $ Just evalDate

  actual360dc <- dayCounter (Actual360 False)
  actActBond <- dayCounter ActualActualBond

  hazardRate <- simpleQuote 0.1
  defaultProbability <- flatHazardRate' 0 target hazardRate actual360dc

  riskFreeRate <- simpleQuote 0.02
  riskFree <- flatForward evalDate riskFreeRate actual360dc Continuous Annual

  sch1 <- schedule (Just $ 30 `november` 2004) (30 `november` 2008) (6, Months)
            usGovBond Unadjusted Unadjusted Backward False Nothing Nothing

  let recoveryRate = 0.4
      faceAmount = 1000000.0
      couponRates = [0.02875, 0.03, 0.03125, 0.0325]

  bnd <- fixedRateBond 1 faceAmount sch1 (fromList couponRates) actActBond ModifiedFollowing
            100.0 (Just $ 20 `november` 2004) usGovBond (0, Days) usGovBond Unadjusted False actActBond
            >>= asBond

  eng <- riskyBondEngine defaultProbability recoveryRate riskFree
  asInstrument bnd >>= (`setPricingEngine` eng)

  bNpv <- asInstrument bnd >>= npv
  bCleanPrice <- currentCleanPrice bnd

  return Result { npvR = bNpv, cleanPriceR = bCleanPrice }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
