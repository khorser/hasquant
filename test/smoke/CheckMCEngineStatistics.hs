-- Smoke test: the StatisticsTrait axis added to every MC pricing engine (beyond the original
-- mcVarianceSwapEngine) actually reaches each engine's second template parameter.
--
-- CheckMCVarianceSwapEngineStatistics.hs already proves the dispatch mechanism works for one
-- engine. This extends the check to a couple of structurally different engines -- mcEuropeanEngine
-- (plain MCVanillaEngine<SingleVariate,RNG,S>) and mcAmericanEngine (a least-squares engine with
-- its own control-variate/calibration machinery, and a third RNG_Calibration template parameter
-- defaulted to RNG) -- since a copy-paste slip in the per-engine dispatch (wrong class name, wrong
-- template argument order) would compile fine for engines whose S happens to be unused in a visible
-- way, but this can't distinguish a genuinely-dispatched S from an accidentally-ignored one; it only
-- proves each of the four enum cases constructs a working engine instantiation without crashing.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckMCEngineStatistics.hs -o /tmp/checkmcstat && /tmp/checkmcstat
import Control.Monad (forM)

import QuantLib.Instrument (setPricingEngine, npv, OptionType(..))
import QuantLib.Instrument.Option (vanillaOption, StrikedPayoff(..), PlainVanillaPayoff(..), Exercise(..), EuropeanExercise(..))
import QuantLib.InterestRate (Compounding(..))
import QuantLib.Math (RngTrait(..), StatisticsTrait(..), PolynomialType(..))
import QuantLib.PricingEngine (mcEuropeanEngine, mcAmericanEngine)
import QuantLib.Process (blackScholesProcess, ProcessDiscretization(..))
import QuantLib.Quote (simpleQuote)
import QuantLib.Settings (setEvaluationDate)
import QuantLib.TermStructure.Volatility (blackConstantVol)
import QuantLib.TermStructure.Yield (flatForward)
import QuantLib.Time.Calendar (calendar, CalendarConstructor(..))
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))

import SmokeCheck (checkWith, report)

refDate :: Day
refDate = 15 `january` 2024

maturity :: Day
maturity = 15 `january` 2025

allFinite :: [Double] -> Bool
allFinite = all (\v -> not (isNaN v) && not (isInfinite v))

europeanNpvUnder :: StatisticsTrait -> IO Double
europeanNpvUnder stat = do
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  spot <- simpleQuote 100.0
  rfQ <- simpleQuote 0.03
  rf <- flatForward refDate rfQ dc Continuous Annual
  volQ <- simpleQuote 0.20
  vol <- blackConstantVol refDate cal volQ dc
  proc' <- blackScholesProcess spot rf vol EulerDiscretization False
  let payoff = PlainVanilla (PlainVanillaPayoff Call 100)
      exercise = European (EuropeanExercise maturity)
  opt <- vanillaOption payoff exercise
  eng <- mcEuropeanEngine PseudoRandom stat proc' (Just 1) Nothing False False (Just 1000) Nothing Nothing 42
  setPricingEngine opt eng
  npv opt

americanNpvUnder :: StatisticsTrait -> IO Double
americanNpvUnder stat = do
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  spot <- simpleQuote 100.0
  rfQ <- simpleQuote 0.03
  rf <- flatForward refDate rfQ dc Continuous Annual
  volQ <- simpleQuote 0.20
  vol <- blackConstantVol refDate cal volQ dc
  proc' <- blackScholesProcess spot rf vol EulerDiscretization False
  let payoff = PlainVanilla (PlainVanillaPayoff Put 100)
      exercise = American Nothing maturity False
  opt <- vanillaOption payoff exercise
  eng <- mcAmericanEngine PseudoRandom stat proc' (Just 50) Nothing True False Nothing (Just 0.02) Nothing 42
           2 Monomial (Just 512) Nothing Nothing
  setPricingEngine opt eng
  npv opt

main :: IO ()
main = do
  setEvaluationDate (Just refDate)
  let stats = [Statistics, GaussianStatistics, GeneralStatistics, IncrementalStatistics]
  euResults <- forM stats $ \stat -> do
    v <- europeanNpvUnder stat
    report ("mcEuropeanEngine " ++ show stat ++ " NPV") v
    pure v
  checkWith "mcEuropeanEngine: all StatisticsTrait cases finite" "each is neither NaN nor infinite"
            (allFinite euResults)

  amResults <- forM stats $ \stat -> do
    v <- americanNpvUnder stat
    report ("mcAmericanEngine " ++ show stat ++ " NPV") v
    pure v
  checkWith "mcAmericanEngine: all StatisticsTrait cases finite" "each is neither NaN nor infinite"
            (allFinite amResults)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
