-- Smoke test for the Gaussian1dModel hierarchy addition (Gsr, MarkovFunctional,
-- the Gaussian1dModel nested ADT, gaussian1dSwaptionEngine). Checks:
-- 1. Gsr materializes, calibrates against a small swaption basket via the
--    Gsr-specific calibrateVolatilitiesIterative, and its calibrated
--    volatility array can be read back.
-- 2. MarkovFunctional (the sibling leaf under the same Gaussian1dModel ADT)
--    also materializes and its volatility array can be read back.
-- 3. gaussian1dSwaptionEngine dispatches correctly for BOTH ADT constructors
--    (Gsr and MarkovFunctional) -- this is what actually proves the
--    Upcastable/Gaussian1dModel wiring is right, not just that it compiles.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/Gaussian1dModels.hs -o /tmp/gaussian1dmodels -outputdir /tmp/gaussian1dmodels_build && /tmp/gaussian1dmodels
import Control.Monad (forM, forM_)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import QuantLib.Instrument
import QuantLib.Instrument.Option (BermudanExercise(..))
import QuantLib.Instrument.Swap
import QuantLib.Math (EndCriteria(..), OptimizationMethod(..))
import QuantLib.Model hiding (setPricingEngine)
import qualified QuantLib.Model as Model
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.TermStructure.Volatility
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

main :: IO ()
main = do
  -- Market setup.
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  settl <- advance cal today (2, Days) Following False
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)
  flatQ <- simpleQuote 0.03
  ts <- TS.flatForward settl flatQ dc365 Continuous Annual
  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)

  -- A Bermudan swaption on a vanilla swap -- the instrument both models will
  -- price under gaussian1dSwaptionEngine.
  start <- advance cal settl (1, Years) ModifiedFollowing False
  maturity <- advance cal start (10, Years) ModifiedFollowing False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  swp <- vanillaSwap Payer 1.0 fixedSchedule 0.03 thirty360bb floatSchedule euribor6m 0.0 act360 ModifiedFollowing
  bermudanDates <- fixedLeg swp >>= CF.toCouponLeg >>= CF.couponAccrualStartDates
  let ex = Bermudan (BermudanExercise bermudanDates False)
  swpn <- swaption swp ex Physical PhysicalOTC

  -- A small swaption calibration basket for Gsr.
  let basketData = [(1, 9, 0.15), (2, 8, 0.14), (3, 7, 0.13)] :: [(Word, Word, Double)]
  helpers <- forM basketData $ \(s, l, v) -> do
    volQ <- simpleQuote v
    swaptionHelper (s, Years) (l, Years) volQ euribor6m (1, Years) thirty360bb act360 ts RelativePriceError
  stepDates <- forM (init [s | (s, _, _) <- basketData]) $ \s -> advance cal today (fromIntegral s, Years) Following False

  gsrModel <- gsr ts stepDates (replicate (length basketData) 0.01) 0.01 60.0
  gsrEngine <- gaussian1dSwaptionEngine (Gsr gsrModel) 32 5.0 True False (Just ts) None
  forM_ helpers (`Model.setPricingEngine` gsrEngine)
  let method = LevenbergMarquardt 1.0e-8 1.0e-8 1.0e-8 False
      ec = EndCriteria 1000 10 1e-8 1e-8 1e-8
  calibrateVolatilitiesIterative gsrModel helpers method ec
  gsrVols <- gsrVolatility gsrModel
  putStrLn ("Gsr calibrated volatilities: " ++ show gsrVols)

  setPricingEngine swpn gsrEngine
  npvGsr <- npv swpn
  putStrLn ("Bermudan swaption NPV under Gsr: " ++ show npvGsr)

  -- MarkovFunctional: the sibling leaf under the same Gaussian1dModel ADT.
  swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
  swaptionVolQ <- simpleQuote 0.20
  swaptionVolTS <- constantSwaptionVolatility 0 cal ModifiedFollowing swaptionVolQ dc365 ShiftedLognormal 0.0
  cmsExpiries <- forM [1, 2, 3 :: Int] $ \n -> advance cal today (n, Years) Following False
  let cmsTenors = replicate 3 (10, Years) :: [(Word, TimeUnit)]
  markov <- markovFunctional ts 0.01 [] [0.01] swaptionVolTS cmsExpiries cmsTenors swapBase 16
  markovVols <- markovFunctionalVolatility markov
  putStrLn ("MarkovFunctional volatilities: " ++ show markovVols)

  markovEngine <- gaussian1dSwaptionEngine (MarkovFunctional markov) 8 5.0 True False (Just ts) None
  setPricingEngine swpn markovEngine
  npvMarkov <- npv swpn
  putStrLn ("Bermudan swaption NPV under MarkovFunctional: " ++ show npvMarkov)
