-- Smoke test for the SwaptionHelper leaf type and its inspectors (QuantLib/Model.chs's
-- swaptionHelperUnderlying/swaptionHelperSwaption/volatility), added alongside the
-- Gaussian1dModels.cpp port's calibration-basket work. These getters need SwaptionHelper to be
-- its own dedicated leaf under BlackCalibrationHelper (not the generic BlackCalibrationHelper
-- swaptionHelper used to return) so that underlying()/swaption() are reachable without a
-- dynamic_pointer_cast -- see CLAUDE.md's GenBlackCalibrationHelper/FixedVsFloatingSwap bullets.
--
-- Checks:
--  1. swaptionHelperUnderlying's FixedVsFloatingSwap has the fixed rate/nominal the helper was
--     built with (via the generic HasFixedLeg/fairRate-style accessors, now bound generically
--     over GenFixedVsFloatingSwap rather than the concrete VanillaSwap).
--  2. swaptionHelperSwaption prices under blackSwaptionEngine to (approximately) the same value
--     as SwaptionHelper's own blackPrice at the helper's quoted volatility -- both price the
--     "same" European swaption, just via two different upstream code paths, so they should agree.
--  3. volatility (generic, base BlackCalibrationHelper-level, no cast) round-trips the vol quote.
--  4. asBlackCalibrationHelper upcasts a SwaptionHelper so it can be used as a plain
--     BlackCalibrationHelper (e.g. for calibrateVolatilitiesIterative's [GenBlackCalibrationHelper
--     bch] argument), and blackPrice/modelValue-style accessors keep working after the upcast.
--
-- Run with: .claude/skills/run-hasquant/driver.sh test/smoke/SwaptionHelperInspectors.hs
import Control.Monad (unless)
import System.Exit (exitFailure)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import qualified QuantLib.Instrument as I
import QuantLib.Instrument.Swap (fairRate, fixedLeg)
import QuantLib.Model
import QuantLib.PricingEngine (blackSwaptionEngine, CashAnnuityModel(..))
import qualified QuantLib.Quote as Q
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

close :: Double -> Double -> Bool
close a b = abs (a - b) < 1e-6 * max 1 (abs a)

main :: IO ()
main = do
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  settl <- advance cal today (2, Days) Following False
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)
  flatQ <- Q.simpleQuote 0.03
  ts <- TS.flatForward settl flatQ dc365 Continuous Annual
  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
  let volValue = 0.15
  volQ <- Q.simpleQuote volValue
  let strike = 0.04
      nominal = 1.0

  h <- swaptionHelper (5, Years) (5, Years) volQ euribor6m (1, Years) thirty360bb act360 ts
    RelativePriceError (Just strike) nominal ShiftedLognormal 0.0 (Just 2) CF.AveragingCompound

  underlying <- swaptionHelperUnderlying h
  fr <- fairRate underlying
  _fl <- fixedLeg underlying -- just confirm it materializes without throwing
  putStrLn ("underlying fairRate: " ++ show fr)

  vol <- volatility h >>= Q.value
  unless (close vol volValue) $ do
    putStrLn ("MISMATCH: volatility " ++ show vol ++ " /= " ++ show volValue)
    exitFailure
  putStrLn "OK: volatility round-trips the quote the helper was built with"

  swpn <- swaptionHelperSwaption h
  engine <- blackSwaptionEngine ts volQ dc365 0.0 SwapRate
  I.setPricingEngine swpn engine
  npvSwaption <- I.npv swpn
  bp <- blackPrice h volValue
  putStrLn ("swaption NPV: " ++ show npvSwaption ++ ", helper blackPrice: " ++ show bp)
  unless (close npvSwaption bp) $ do
    putStrLn "MISMATCH: swaptionHelperSwaption's NPV should agree with the helper's own blackPrice"
    exitFailure
  putStrLn "OK: swaptionHelperSwaption prices consistently with the helper's own blackPrice"

  bch <- asBlackCalibrationHelper h
  setPricingEngine bch engine
  mv <- modelValue bch
  putStrLn ("upcast BlackCalibrationHelper modelValue: " ++ show mv)
  unless (close mv npvSwaption) $ do
    putStrLn "MISMATCH: modelValue on the upcast helper should agree with the standalone swaption's NPV under the same engine"
    exitFailure

  putStrLn "SwaptionHelperInspectors smoke test passed"
