module QuantLib.Example.EquityTotalReturnSwap
  (
    Result(..)
  , run
  ) where

import QuantLib.Currency
import QuantLib.Index(addFixing)
import QuantLib.Index.Equity(EquityIndex, equityIndex)
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import qualified QuantLib.InterestRate as IR2
import QuantLib.PricingEngine
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Time.Calendar
import QuantLib.Time.Date hiding(today)
import QuantLib.Time.Schedule

-- |Port of QuantLib's test-suite/equitytotalreturnswap.cpp testFairMargin: build a
-- total-return swap struck at a zero margin, read off its fair margin, then rebuild it
-- at that fair margin and confirm the resulting NPV is ~0 -- an internal-consistency
-- check, since upstream's own test asserts the same invariant rather than a golden NPV.
data Result = Result
  { fairMarginIborR :: Double
  , parNpvIborR :: Double
  , fairMarginOvernightR :: Double
  , parNpvOvernightR :: Double
  } deriving Show

run :: IO Result
run = do
  cal <- calendar UnitedStatesGovernmentBond
  today <- adjust cal (27 `january` 2023) Following
  setEvaluationDate $ Just today
  dc <- dayCounter Actual365FixedStandard
  usd <- currency USD

  interestQ <- simpleQuote 0.0375
  dividendQ <- simpleQuote 0.005
  interestCurve <- flatForward today interestQ dc IR2.Continuous Annual
  dividendCurve <- flatForward today dividendQ dc IR2.Continuous Annual

  spotQ <- simpleQuote 8700.0
  eqIndex <- equityIndex "eqIndex" cal usd (Just interestCurve) (Just dividendCurve) (Just spotQ)
  addFixing eqIndex (5 `january` 2023) 9010.0 False
  addFixing eqIndex today 8690.0 False

  sofr <- IR.overnightIborIndex IR.Sofr (Just interestCurve)
  mapM_ (\(d, r) -> addFixing sofr d r False) sofrFixings

  usdLibor <- IR.iborIndex (IR.Libor "USDLibor" (3, Months) 2 usd cal dc) (Just interestCurve)
  addFixing usdLibor (3 `january` 2023) 0.035 False

  engine <- discountingSwapEngine interestCurve Nothing Nothing Nothing

  sched <- schedule (Just (5 `january` 2023)) (5 `april` 2023) (3, Months) cal
    Following Following Backward False Nothing Nothing

  (fairMarginIbor, parNpvIbor) <- checkFairMargin engine
    (\m -> equityTotalReturnSwapIbor Receiver nominal sched eqIndex usdLibor dc m 1.0 cal Following 0)
  (fairMarginOvernight, parNpvOvernight) <- checkFairMargin engine
    (\m -> equityTotalReturnSwapOvernight Receiver nominal sched eqIndex sofr dc m 1.0 cal Following 0)

  return Result
    { fairMarginIborR = fairMarginIbor
    , parNpvIborR = parNpvIbor
    , fairMarginOvernightR = fairMarginOvernight
    , parNpvOvernightR = parNpvOvernight
    }
  where
    nominal = 1.0e7
    sofrFixings =
      [ (3 `january` 2023, 0.030), (4 `january` 2023, 0.031), (5 `january` 2023, 0.031)
      , (6 `january` 2023, 0.031), (9 `january` 2023, 0.032), (10 `january` 2023, 0.033)
      , (11 `january` 2023, 0.033), (12 `january` 2023, 0.033), (13 `january` 2023, 0.033)
      , (17 `january` 2023, 0.033), (18 `january` 2023, 0.034), (19 `january` 2023, 0.034)
      , (20 `january` 2023, 0.034), (23 `january` 2023, 0.034), (24 `january` 2023, 0.034)
      , (25 `january` 2023, 0.034), (26 `january` 2023, 0.034)
      ]

    checkFairMargin :: PricingEngine -> (Double -> IO EquityTotalReturnSwap) -> IO (Double, Double)
    checkFairMargin engine build = do
      trs0 <- build 0.0
      setPricingEngine trs0 engine
      fm <- fairMargin trs0
      parTrs <- build fm
      setPricingEngine parTrs engine
      parNpv <- npv parTrs
      return (fm, parNpv)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
