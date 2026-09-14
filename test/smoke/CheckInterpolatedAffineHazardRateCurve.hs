-- Smoke test: InterpolatedAffineHazardRateCurve wiring (constructor, model plumbing,
-- conditionalSurvivalProbability).
--
-- No upstream test-suite fixture exists for this experimental class (checked
-- ~/Src/QuantLib/test-suite/*.cpp). Instead this checks two identities read directly out of
-- QuantLib 1.43's own InterpolatedAffineHazardRateCurve<T>::conditionalSurvivalProbabilityImpl
-- (ql/experimental/credit/interpolatedaffinehazardratecurve.hpp):
--   * tFwd == 0 makes the yVal argument irrelevant and returns exactly survivalProbabilityImpl(tTarget)
--   * tFwd == tTarget always returns 1 (survival to the same point you're already conditioned on)
-- A binding that dropped the model argument, swapped tFwd/tTarget, or misrouted yVal would very
-- likely violate at least one of these, since they hold only because the C++ short-circuits on
-- those exact conditions before touching the model at all.
--
-- The curve's reference date is fixed to the first pillar date (dates.at(0) in the upstream
-- constructor), not the evaluation date -- confirmed by reading both
-- InterpolatedAffineHazardRateCurve and its InterpolatedHazardRateCurve sibling. All intervals
-- below are therefore measured from the first pillar, not from refDate.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckInterpolatedAffineHazardRateCurve.hs -o /tmp/checkaffine -outputdir /tmp/checkaffine_build && /tmp/checkaffine
import Data.List.NonEmpty (fromList)

import QuantLib.Context (setEvaluationDate)
import QuantLib.InterestRate (Compounding(..))
import QuantLib.Math (Interpolation(..))
import QuantLib.Model (hullWhite)
import QuantLib.TermStructure (TermPoint(..), TermInterval(..))
import QuantLib.TermStructure.Credit
import QuantLib.TermStructure.Yield (flatForward, Reference(..))
import QuantLib.Quote (simpleQuote)
import QuantLib.Time.Calendar (calendar, CalendarConstructor(..))
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))

import SmokeCheck (checkWith, report)

refDate :: Day
refDate = 15 `january` 2024

firstPillar, secondPillar, thirdPillar :: Day
firstPillar = 15 `january` 2025
secondPillar = 15 `january` 2026
thirdPillar = 15 `january` 2027

pillars :: [Day]
pillars = [firstPillar, secondPillar, thirdPillar]

hazardRates :: [Double]
hazardRates = [0.010, 0.015, 0.022]

targetDate :: Day
targetDate = 15 `july` 2025

main :: IO ()
main = do
  setEvaluationDate (Just refDate)
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  rfQ <- simpleQuote 0.03
  yc <- flatForward (ReferenceDate refDate) rfQ dc Continuous Annual
  model <- hullWhite yc 0.05 0.01
  curve <- interpolatedAffineHazardRateCurve (fromList (zip pillars hazardRates)) dc model cal [] Linear True

  survT <- survivalProbability curve (DatePoint targetDate) True
  report "survivalProbability(targetDate)" survT
  checkWith "survival probability is a sane probability" "0 < p <= 1" (survT > 0 && survT <= 1)

  -- Identity 1: tFwd=0 (i.e. the curve's own reference date, the first pillar) makes yVal
  -- irrelevant and reproduces survivalProbabilityImpl(tTarget).
  condFromZero1 <- conditionalSurvivalProbability curve (DateInterval firstPillar targetDate) 0.01 True
  condFromZero2 <- conditionalSurvivalProbability curve (DateInterval firstPillar targetDate) 0.5 True
  report "conditionalSurvivalProbability(firstPillar, targetDate, yVal=0.01)" condFromZero1
  report "conditionalSurvivalProbability(firstPillar, targetDate, yVal=0.5)" condFromZero2
  checkWith "conditional(0,t) matches survivalProbability(t)" "abs difference < 1e-9"
            (abs (condFromZero1 - survT) < 1e-9)
  checkWith "conditional(0,t) ignores yVal" "abs difference < 1e-9"
            (abs (condFromZero1 - condFromZero2) < 1e-9)

  -- Identity 2: tFwd == tTarget always returns 1.
  condSamePoint <- conditionalSurvivalProbability curve (DateInterval targetDate targetDate) 0.02 True
  report "conditionalSurvivalProbability(targetDate, targetDate, yVal=0.02)" condSamePoint
  checkWith "conditional(t,t) == 1" "abs difference < 1e-9" (abs (condSamePoint - 1) < 1e-9)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
