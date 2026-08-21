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
-- 4. gaussian1dJamshidianSwaptionEngine reprices a European swaption to the same NPV as
--    gaussian1dSwaptionEngine's direct integration (mirrors test-suite/gsr.cpp).
-- 5. gaussian1dCapFloorEngine dispatches correctly for BOTH ADT constructors (Gsr and
--    MarkovFunctional), pricing a cap to a finite, non-negative NPV under each. Upstream
--    (test-suite/markovfunctional.cpp:1234) DOES cross-check Gaussian1dCapFloorEngine against
--    BlackCapFloorEngine to 1bp, but only for a MarkovFunctional calibrated via its
--    caplet-smile-matching constructor (iborIndex/capletExpiries/capletVts) -- hasquant only
--    binds MarkovFunctional's swaption/CMS-calibrating constructor (used for basket6/swaption4
--    above), so that stronger check isn't reachable without binding the other constructor
--    first (a separate task).
--
-- Run with: cabal exec -- ghc -package hasquant smoke/Gaussian1dModels.hs -o /tmp/gaussian1dmodels -outputdir /tmp/gaussian1dmodels_build && /tmp/gaussian1dmodels
import Control.Monad (forM, forM_, replicateM)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import QuantLib.Instrument
import QuantLib.Instrument.CapFloor (cap)
import QuantLib.Instrument.Option (Exercise(..), BermudanExercise(..), EuropeanExercise(..))
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
  swp <- vanillaSwap Payer 1.0 fixedSchedule 0.03 thirty360bb floatSchedule euribor6m 0.0 act360 (Just ModifiedFollowing) Nothing
  bermudanDates <- fixedLeg swp >>= CF.toCouponLeg >>= CF.couponAccrualStartDates
  let ex = Bermudan (BermudanExercise bermudanDates False)
  swpn <- swaption swp ex Physical PhysicalOTC

  -- A small swaption calibration basket for Gsr.
  let basketData = [(1, 9, 0.15), (2, 8, 0.14), (3, 7, 0.13)] :: [(Word, Word, Double)]
  helpers <- forM basketData $ \(s, l, v) -> do
    volQ <- simpleQuote v
    swaptionHelper (s, Years) (l, Years) volQ euribor6m (1, Years) thirty360bb act360 ts RelativePriceError Nothing 1.0 ShiftedLognormal 0.0 Nothing CF.AveragingCompound
  stepDates <- forM (init [s | (s, _, _) <- basketData]) $ \s -> advance cal today (fromIntegral s, Years) Following False

  gsrVolQuotes <- replicateM (length basketData) (simpleQuote 0.01)
  gsrReversionQuote <- simpleQuote 0.01
  gsrModel <- gsr ts stepDates gsrVolQuotes gsrReversionQuote 60.0
  gsrEngine <- gaussian1dSwaptionEngine (Gsr gsrModel) 32 5.0 True False (Just ts) None
  forM_ helpers (`Model.setPricingEngine` gsrEngine)
  let method = LevenbergMarquardt 1.0e-8 1.0e-8 1.0e-8 False
      ec = EndCriteria 1000 10 1e-8 1e-8 1e-8
  calibrateVolatilitiesIterative gsrModel helpers method ec Nothing []
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

  -- gaussian1dJamshidianSwaptionEngine: a European (single-exercise) physical-settled
  -- swaption on the same underlying should reprice identically under direct integration
  -- (gaussian1dSwaptionEngine) and Jamshidian's decomposition -- mirrors upstream's own
  -- self-consistency check in test-suite/gsr.cpp's testNonstandardSwaps.
  let euroEx = European (EuropeanExercise start)
  euroSwpn <- swaption swp euroEx Physical PhysicalOTC
  jamEngine <- gaussian1dJamshidianSwaptionEngine (Gsr gsrModel)
  setPricingEngine euroSwpn gsrEngine
  npvEuroDirect <- npv euroSwpn
  setPricingEngine euroSwpn jamEngine
  npvEuroJam <- npv euroSwpn
  putStrLn ("European swaption NPV, direct integration: " ++ show npvEuroDirect
            ++ ", Jamshidian decomposition: " ++ show npvEuroJam)
  -- upstream's own tolerance for this comparison, test-suite/gsr.cpp's testNonstandardSwaps.
  if abs (npvEuroDirect - npvEuroJam) > 5.0e-5
    then error ("gaussian1dJamshidianSwaptionEngine NPV diverges from gaussian1dSwaptionEngine: "
                ++ show npvEuroDirect ++ " vs " ++ show npvEuroJam)
    else putStrLn "gaussian1dJamshidianSwaptionEngine: OK, matches direct integration"

  -- gaussian1dCapFloorEngine: a 3% cap on the swap's own floating leg, dispatched over BOTH
  -- ADT constructors (Gsr and MarkovFunctional) -- as with gaussian1dSwaptionEngine above,
  -- this is what proves the Upcastable/Gaussian1dModel wiring, not just that it compiles.
  floatLeg <- floatingLeg swp
  capfl <- cap floatLeg [0.03]
  gsrCapFloorEngine <- gaussian1dCapFloorEngine (Gsr gsrModel) 64 7.0 True False (Just ts)
  setPricingEngine capfl gsrCapFloorEngine
  npvCapGsr <- npv capfl
  putStrLn ("Cap NPV under gaussian1dCapFloorEngine (Gsr): " ++ show npvCapGsr)
  checkPlausibleCapNpv "Gsr" npvCapGsr

  markovCapFloorEngine <- gaussian1dCapFloorEngine (MarkovFunctional markov) 8 5.0 True False (Just ts)
  setPricingEngine capfl markovCapFloorEngine
  npvCapMarkov <- npv capfl
  putStrLn ("Cap NPV under gaussian1dCapFloorEngine (MarkovFunctional): " ++ show npvCapMarkov)
  checkPlausibleCapNpv "MarkovFunctional" npvCapMarkov
  where
    isFinite x = not (isNaN x || isInfinite x)
    checkPlausibleCapNpv label x =
      if not (isFinite x) || x < 0
        then error ("gaussian1dCapFloorEngine (" ++ label ++ "): implausible cap NPV " ++ show x)
        else putStrLn ("gaussian1dCapFloorEngine (" ++ label ++ "): OK, finite non-negative NPV")
