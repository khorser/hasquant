module QuantLib.Example.QuickStart
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar(addGregorianYearsClip)

import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Math(Interpolation(..))
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.PricingEngine
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

-- |Minimal end-to-end demo: a 5yr SOFR-based OIS priced off a zero curve
-- built from a handful of hardcoded zero rates. Referenced from README.md's
-- Quick Example section -- keep the two in sync.
data Result = Result
  { quickNpv :: Double
  , quickFairRate :: Double
  } deriving Show

run :: IO Result
run = do
  let today = 2 `january` 2024
  setEvaluationDate (Just today)

  cal <- calendar TARGET
  settle <- advance cal today (2, Days) Following False
  let maturity = addGregorianYearsClip 5 settle

  dc <- dayCounter (Actual360 False)
  curve <- TS.interpolatedZeroCurve
    [ (settle, 0.030)
    , (addGregorianYearsClip 1 settle, 0.032)
    , (addGregorianYearsClip 2 settle, 0.034)
    , (addGregorianYearsClip 5 settle, 0.036)
    , (addGregorianYearsClip 10 settle, 0.038)
    ] dc cal [] Linear

  sofr <- IR.overnightIborIndex IR.Sofr (Just curve)

  sched <- schedule (Just settle) maturity (1, Years) cal
    ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

  ois <- overnightIndexedSwap Payer 10000000 sched 0.035 dc sofr 0.0
    0 Following cal False AveragingCompound Nothing 0 False

  engine <- discountingSwapEngine curve (Just False) Nothing Nothing
  setPricingEngine ois engine

  n <- npv ois
  fr <- fairRate ois
  pure Result { quickNpv = n, quickFairRate = fr }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
