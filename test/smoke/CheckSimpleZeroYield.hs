-- Check that SimpleZeroYield bootstraps distinctly from the other BootstrapTrait cases.
--

import Data.List.NonEmpty(fromList)
import qualified QuantLib.Quote as Quote
import QuantLib.Context(setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkWith)

curveToday :: Day
curveToday = 23 `october` 2025

main :: IO ()
main = do
  setEvaluationDate (Just curveToday)
  cal <- calendar TARGET
  euriborDC <- dayCounter (Actual360 False)

  q <- Quote.simpleQuote 0.03
  helpers <- mapM (\i -> fraRateHelper q (FraMonths i (i + 3) 2 cal ModifiedFollowing True euriborDC) LastRelevantDate Nothing False) [1 .. 5]

  discountCurve <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList helpers) euriborDC []
    (GlobalDiscountLogLinear 1.0e-10 []) False
  helpers2 <- mapM (\i -> fraRateHelper q (FraMonths i (i + 3) 2 cal ModifiedFollowing True euriborDC) LastRelevantDate Nothing False) [1 .. 5]
  zeroCurve <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList helpers2) euriborDC []
    (GlobalSimpleZeroLinear 1.0e-10 []) False

  -- A date strictly between two pillars: the two curves reprice the input instruments
  -- identically at the pillar dates themselves, but interpolate between them differently
  -- (log-linear discount vs. linear zero yield), so a mid-pillar discount factor is where the
  -- two constructions are actually distinguishable -- proof SimpleZeroYield's branch dispatched
  -- to a genuinely different CurveType, not a mis-numbered alias of Discount's.
  midPillar <- advance cal curveToday (75, Days) ModifiedFollowing True
  dDiscount <- discount discountCurve (DatePoint midPillar) False
  dZero <- discount zeroCurve (DatePoint midPillar) False

  checkWith "SimpleZeroYield GlobalBootstrap curve produces a sane discount factor"
            "confirms qlPiecewiseYieldCurveGlobalBootstrap2 actually dispatched, not just linked"
            (dZero > 0 && dZero < 1)
  checkWith "SimpleZeroYield and Discount GlobalBootstrap curves disagree between pillars"
            "confirms the SimpleZeroYield enum case isn't silently aliasing Discount's numeric value"
            (abs (dDiscount - dZero) > 1.0e-8)

  putStrLn "simplezeroyield: all checks passed"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
