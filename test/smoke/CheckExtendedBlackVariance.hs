-- Smoke test: ExtendedBlackVarianceCurve's volatilities are live quotes, not a snapshot.
--
-- The whole point of the Extended variant over 'blackVarianceCurve' is that it registers as an
-- observer of each Handle<Quote> and re-derives its variance when one changes -- nothing in the
-- type system distinguishes a curve that actually re-registered from one that only read the
-- initial values and dropped the handles. This prices the same European option off one curve
-- before and after bumping one of its underlying SimpleQuotes, and asserts the NPV moves.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckExtendedBlackVariance.hs -o /tmp/checkebv -outputdir /tmp/checkebv_build && /tmp/checkebv
import Data.List.NonEmpty (fromList)

import QuantLib.Instrument (setPricingEngine, npv)
import QuantLib.Instrument.Option
import QuantLib.InterestRate (Compounding(..))
import QuantLib.PricingEngine (analyticEuropeanEngine)
import QuantLib.Process (blackScholesProcess, ProcessDiscretization(..))
import QuantLib.Quote (simpleQuote, setValue)
import QuantLib.Context (setEvaluationDate)
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield (flatForward)
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))

import SmokeCheck (checkWith, report)

refDate :: Day
refDate = 15 `january` 2024

pillars :: [Day]
pillars = [15 `january` 2025, 15 `january` 2026, 15 `january` 2027]

initialVols :: [Double]
initialVols = [0.20, 0.22, 0.24]

optionExpiry :: Day
optionExpiry = 15 `july` 2025

optionStrike :: Double
optionStrike = 100

main :: IO ()
main = do
  setEvaluationDate (Just refDate)
  dc <- dayCounter Actual365FixedStandard
  [q1, q2, q3] <- mapM simpleQuote initialVols
  curve <- extendedBlackVarianceCurve refDate (fromList (zip pillars [q1, q2, q3])) dc True
  spot <- simpleQuote 100.0
  rfQ <- simpleQuote 0.03
  rf <- flatForward (ReferenceDate refDate) rfQ dc Continuous Annual
  proc' <- blackScholesProcess spot rf curve EulerDiscretization False
  opt <- vanillaOption (PlainVanilla $ PlainVanillaPayoff Call optionStrike)
                       (European $ EuropeanExercise optionExpiry)
  analyticEuropeanEngine proc' Nothing >>= setPricingEngine opt
  before <- npv opt
  report "NPV before bump" before
  -- optionExpiry sits between the first two pillars, so this is the one that actually reaches
  -- the option's interpolated variance; kept below the second pillar's 0.22 to respect
  -- forceMonotoneVariance.
  _ <- setValue q1 0.10
  after <- npv opt
  report "NPV after bump" after
  checkWith "both NPVs positive" "each > 0" (before > 0 && after > 0)
  checkWith "NPV moves after quote bump"
            "relative difference > 1e-4"
            (abs (after - before) / before > 1e-4)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
