-- Smoke test for RebatedExercise (Internal.Common's Rebated ADT case), added as part of the
-- Gaussian1dModels.cpp port. Checks that wrapping a European exercise in Rebated materializes,
-- upcasts to Exercise, and can be used to build a real instrument (a Swaption) without crashing
-- -- i.e. the recursive withExercise call and the CRebatedExercise' Upcastable wiring are correct.
--
-- Run with: cabal exec -- ghc -package hasquant test/smoke/RebatedExercise.hs -o /tmp/rebatedexercise -outputdir /tmp/rebatedexercise_build && /tmp/rebatedexercise
import QuantLib.Instrument (npv, setPricingEngine, SettlementType(..), SettlementMethod(..))
import QuantLib.Instrument.Option (EuropeanExercise(..), Exercise(..))
import QuantLib.Instrument.Swap
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

main :: IO ()
main = do
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

  start <- advance cal settl (1, Years) ModifiedFollowing False
  maturity <- advance cal start (10, Years) ModifiedFollowing False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  swp <- vanillaSwap Payer 1.0 fixedSchedule 0.03 thirty360bb floatSchedule euribor6m 0.0 act360 (Just ModifiedFollowing) Nothing

  let europeanEx = European (EuropeanExercise start)
      rebatedEx = Rebated europeanEx (-1.0) 2 cal Following

  swpnPlain <- swaption swp europeanEx Physical PhysicalOTC
  swpnRebated <- swaption swp rebatedEx Physical PhysicalOTC

  volQ <- simpleQuote 0.20
  blackEngine <- blackSwaptionEngine ts volQ dc365 0.0 SwapRate
  setPricingEngine swpnPlain blackEngine
  setPricingEngine swpnRebated blackEngine
  npvPlain <- npv swpnPlain
  npvRebated <- npv swpnRebated
  putStrLn ("Plain European swaption NPV: " ++ show npvPlain)
  putStrLn ("Rebated-wrapped European swaption NPV: " ++ show npvRebated)
  -- RebatedExercise only changes what happens on early exercise (a cash rebate paid instead of
  -- the notional exchange this example never triggers via blackSwaptionEngine), so both prices
  -- should match under this engine -- this is the actual proof the ADT round-trips correctly
  -- rather than silently constructing something else.
  if abs (npvPlain - npvRebated) < 1e-8
    then putStrLn "OK: RebatedExercise-wrapped swaption reprices identically to the plain exercise"
    else error ("MISMATCH: " ++ show npvPlain ++ " vs " ++ show npvRebated)
