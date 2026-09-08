{-# LANGUAGE OverloadedLists #-}

-- End-to-end marshalling checks for ultimateForwardTermStructure,
-- interpolatedSpreadDiscountCurve and multipleResetsSwapRateHelper. These supplement Hspec because
-- a stale c2hs object can otherwise make a successful build misleading.
import Data.Time.Calendar(addGregorianYearsClip)

import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Index(addFixing)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import qualified QuantLib.InterestRate as IR
import QuantLib.Math(Interpolation(..))
import qualified QuantLib.Quote as Quote
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure hiding(maxDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkClose, checkWith, report)

curveToday :: Day
curveToday = 15 `january` 2024

main :: IO ()
main = do
  setEvaluationDate (Just curveToday)
  cal <- calendar TARGET
  actual360dc <- dayCounter (Actual360 False)
  flatRate <- Quote.simpleQuote 0.03
  base <- flatForward (SettlementDays 2 cal) flatRate actual360dc IR.Continuous Annual
  refDate <- asTermStructure base >>= referenceDate

  -- 1. ultimateForwardTermStructure: below the first smoothing point (fsp) it must reproduce
  --    the base curve's own zero rate exactly (extrapolation only applies past fsp).
  llfr <- Quote.simpleQuote 0.0125
  ufr <- Quote.simpleQuote 0.02
  let fsp = (10, Years)
      cutOffDate = addYears 10 refDate
  ufrTs <- ultimateForwardTermStructure base llfr ufr fsp 0.1 Nothing IR.Compounded Annual
  baseZero <- IR.rate <$> zeroRate base (RateAtDate cutOffDate actual360dc) IR.Continuous NoFrequency True
  ufrZero <- IR.rate <$> zeroRate ufrTs (RateAtDate cutOffDate actual360dc) IR.Continuous NoFrequency True
  report "UFR curve zero rate at the first smoothing point" (show ufrZero)
  checkClose "matches the base curve's own zero rate at fsp" baseZero ufrZero 1.0e-8

  -- 2. interpolatedSpreadDiscountCurve: at an input node date the combined discount must equal
  --    baseCurve.discount(date) * the given spread df exactly.
  let d1 = addYears 1 refDate
      spreadDf1 = 0.95
  spreaded <- interpolatedSpreadDiscountCurve base [(refDate, 1.0), (d1, spreadDf1), (addYears 2 refDate, 0.90)] Linear
  baseD1 <- discount base (DatePoint d1) False
  spreadedD1 <- discount spreaded (DatePoint d1) False
  report "spread discount curve at 1y node" (show spreadedD1)
  checkClose "equals base discount * spread df" (baseD1 * spreadDf1) spreadedD1 1.0e-8

  -- 3. multipleResetsSwapRateHelper: a curve bootstrapped from a single pillar must reprice the
  --    helper's own fixed-rate quote (RateHelper::quoteError() driven to ~0 by the solver).
  ccy <- currency EUR
  euribor3m <- iborIndex (Ibor "euribor3m" (3, Months) 2 ccy cal ModifiedFollowing False actual360dc) Nothing
  addFixing euribor3m (11 `january` 2024) 0.05 False
  let inputRate = 0.05
  q <- Quote.simpleQuote inputRate
  rh <- multipleResetsSwapRateHelper 0 (2, Years) q euribor3m 2 Nothing AveragingCompound 0.0 NoFrequency actual360dc ModifiedFollowing
  ts <- piecewiseYieldCurve (ReferenceDate curveToday) [rh] actual360dc [] (Iterative Discount LogLinear defaultIterativeBootstrapOpts) False
  _ <- discount ts (DatePoint curveToday) False
  implied <- impliedQuote rh
  report "multiple-resets swap rate helper implied quote" (show implied)
  checkWith "reprices to its own input rate" "close to 0.05"
            (abs (implied - inputRate) < 1.0e-6)
  where
    addYears = addGregorianYearsClip

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
