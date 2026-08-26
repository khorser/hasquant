module QuantLib.Example.OvernightIndexedSwap
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar(addGregorianYearsClip)

import QuantLib.CashFlow(RateAveragingType(..))
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.InterestRate(Compounding(..))
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

-- |Ports overnightindexedswap.cpp's testCachedValue: a 1yr ESTR-based OIS
-- against a flat 5% discount curve, checked with both telescopic and
-- non-telescopic value dates (both must reproduce the same cached NPV).
data Result = Result
  { npvNonTelescopic :: Double
  , npvTelescopic :: Double
  } deriving Show

run :: IO Result
run = do
  let valueDate = 5 `february` 2009
  setEvaluationDate (Just valueDate)

  cal <- calendar TARGET
  settlementDate <- advance cal valueDate (2, Days) Following False
  let endDate = addGregorianYearsClip 1 settlementDate

  act360 <- dayCounter (Actual360 False)
  flatQuote <- simpleQuote 0.05
  estrTS <- TS.flatForward settlementDate flatQuote act360 Continuous Annual
  estrIndex <- IR.overnightIborIndex IR.Estr (Just estrTS)

  sched <- schedule (Just settlementDate) endDate (1, Years) cal
    ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

  let fixedRate = exp 0.05 - 1

  engine <- discountingSwapEngine estrTS (Just False) Nothing Nothing

  ois <- overnightIndexedSwap Payer 100.0 sched fixedRate act360 estrIndex 0.0
    0 Following cal False AveragingCompound Nothing 0 False
  setPricingEngine ois engine
  npv1 <- npv ois

  oisTelescopic <- overnightIndexedSwap Payer 100.0 sched fixedRate act360 estrIndex 0.0
    0 Following cal True AveragingCompound Nothing 0 False
  setPricingEngine oisTelescopic engine
  npv2 <- npv oisTelescopic

  pure Result { npvNonTelescopic = npv1, npvTelescopic = npv2 }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
