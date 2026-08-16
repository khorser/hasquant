-- Smoke test: SabrSmileSection, NoArbSabrSmileSection and SabrInterpolatedSmileSection.
--
-- 1. sabrSmileSection's volatility(strike)/variance(strike) must exactly match the
--    already-bound unsafeShiftedSabrVolatility formula it's built on
--    (see cbits' SabrSmileSection::volatilityImpl), for both VolatilityType cases --
--    this is enum-dispatched through a C-side (VolatilityType) cast, same class of
--    bug as the CPIInterpolationType incident, so a same-input-different-enum check
--    is needed, not just a hand-picked number.
-- 2. sabrSmileSection' (Date-based ctor) must agree with sabrSmileSection (Time-based)
--    when given the same time to expiry via Actual365Fixed, since both must construct
--    the identical underlying SabrSmileSection.
-- 3. noArbSabrSmileSection and noArbSabrSmileSection' (Time- vs Date-based NoArbSabrSmileSection
--    ctors) must likewise agree with each other, and must differ from the plain
--    sabrSmileSection at the same inputs (different, arbitrage-free model) -- so the test
--    can't accidentally pass by calling the wrong shim.
-- 4. sabrInterpolatedSmileSection calibrates to a small synthetic strike/vol set and
--    the calibrated alpha/beta/nu/rho/vols should reproduce the input reasonably well.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckSabrSmileSection.hs -o /tmp/checksabr -outputdir /tmp/checksabr_build && /tmp/checksabr
import Control.Monad(forM, forM_, unless)
import Text.Printf(printf)
import QuantLib.InterestRate(VolatilityType(..))
import QuantLib.PricingEngine(unsafeShiftedSabrVolatility)
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Time.Date
import QuantLib.Time.Schedule(TimeUnit(..), DayCounterConstructor(..), dayCounter)
import QuantLib.TermStructure.Volatility

import SmokeCheck (checkClose, checkEq)

forward, expiry, alpha, beta, nu, rho, shift :: Double
forward = 0.03
expiry = 5.0
alpha = 0.04
beta = 0.5
nu = 0.4
rho = -0.2
shift = 0.0

main :: IO ()
main = do
  forM_ [ShiftedLognormal, Normal] $ \volType -> do
    section <- sabrSmileSection expiry forward alpha beta nu rho shift volType
    forM_ [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
      got <- smileSectionVolatility section strike
      expected <- unsafeShiftedSabrVolatility strike forward expiry alpha beta nu rho shift volType
      -- exact equality is intended: both paths must hit the identical SABR formula
      checkEq (printf "%s strike=%.2f vol" (show volType) strike) expected got
      var <- smileSectionVariance section strike
      checkClose (printf "%s strike=%.2f variance" (show volType) strike)
        (expected * expected * expiry) var 1e-12

  volShiftedLognormal <- sabrSmileSection expiry forward alpha beta nu rho shift ShiftedLognormal
  volAtAtm1 <- smileSectionVolatility volShiftedLognormal forward
  volNormal <- sabrSmileSection expiry forward alpha beta nu rho shift Normal
  volAtAtm2 <- smileSectionVolatility volNormal forward
  unless (volAtAtm1 /= volAtAtm2) $
    error ("Normal and ShiftedLognormal SABR vols should differ at the same inputs, got "
      ++ show volAtAtm1 ++ " for both")
  putStrLn "SabrSmileSection: OK, matches unsafeShiftedSabrVolatility and Normal /= ShiftedLognormal"

  -- SabrSmileSection' / NoArbSabrSmileSection / NoArbSabrSmileSection': the Date-based ctors
  -- derive their Time from a Date via a DayCounter, so pin the evaluation date (used as
  -- NoArbSabrSmileSection's implicit referenceDate) and pick a whole number of days so the
  -- Actual365Fixed fraction (actualDays/365.0) matches the Time-based ctors' input exactly.
  refDate <- today
  setEvaluationDate (Just refDate)
  let expiryDays = 1826 :: Int -- ~5y in actual days
      expiryFromDays = fromIntegral expiryDays / 365.0 :: Double
  optionDate <- addPeriod refDate (expiryDays, Days)
  act365 <- dayCounter Actual365FixedStandard

  sectionByTime <- sabrSmileSection expiryFromDays forward alpha beta nu rho shift ShiftedLognormal
  sectionByDate <- sabrSmileSection' optionDate forward alpha beta nu rho (Just refDate) act365 shift ShiftedLognormal
  forM_ [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
    volT <- smileSectionVolatility sectionByTime strike
    volD <- smileSectionVolatility sectionByDate strike
    checkClose (printf "SabrSmileSection' strike=%.2f vol (date vs time)" strike) volT volD 1e-12
  putStrLn "SabrSmileSection': OK, matches sabrSmileSection at the equivalent Time"

  noArbByTime <- noArbSabrSmileSection expiryFromDays forward alpha beta nu rho shift ShiftedLognormal
  noArbByDate <- noArbSabrSmileSection' optionDate forward alpha beta nu rho act365 shift ShiftedLognormal
  differences <- forM [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
    volT <- smileSectionVolatility noArbByTime strike
    volD <- smileSectionVolatility noArbByDate strike
    checkClose (printf "NoArbSabrSmileSection' strike=%.2f vol (date vs time)" strike) volT volD 1e-12
    plainVol <- smileSectionVolatility sectionByTime strike
    return (volT /= plainVol)
  unless (or differences) $
    error "noArbSabrSmileSection vols should differ from the plain sabrSmileSection at some strike"
  putStrLn "NoArbSabrSmileSection/': OK, date/time ctors agree and differ from the plain SabrSmileSection"

  -- SabrInterpolatedSmileSection: calibrate to vols generated from known SABR params,
  -- then check the calibrated smile reprices those same strikes closely.
  let strikes = [0.01, 0.02, 0.03, 0.04, 0.05]
  refVols <- mapM (\k -> unsafeShiftedSabrVolatility k forward expiry alpha beta nu rho shift ShiftedLognormal) strikes
  atmVol <- unsafeShiftedSabrVolatility forward forward expiry alpha beta nu rho shift ShiftedLognormal
  now <- today
  optionDate <- addPeriod now (round (expiry * 365) :: Int, Days)
  forwardQuote <- simpleQuote forward
  atmVolQuote <- simpleQuote atmVol
  refVolQuotes <- mapM simpleQuote refVols
  interp <- sabrInterpolatedSmileSection optionDate forwardQuote strikes False atmVolQuote refVolQuotes
    alpha beta nu rho defaultSabrInterpolatedSmileSectionOpts
  calibratedAlpha <- sabrInterpolatedSmileSectionAlpha interp
  calibratedBeta <- sabrInterpolatedSmileSectionBeta interp
  calibratedNu <- sabrInterpolatedSmileSectionNu interp
  calibratedRho <- sabrInterpolatedSmileSectionRho interp
  rms <- sabrInterpolatedSmileSectionRmsError interp
  maxErr <- sabrInterpolatedSmileSectionMaxError interp
  endC <- sabrInterpolatedSmileSectionEndCriteria interp
  printf "SabrInterpolatedSmileSection: calibrated alpha=%.6f beta=%.6f nu=%.6f rho=%.6f rms=%.2e max=%.2e endCriteria=%s\n"
    calibratedAlpha calibratedBeta calibratedNu calibratedRho rms maxErr (show endC)
  unless (rms < 1e-6 && maxErr < 1e-6) $
    error ("Calibration to exact SABR-generated vols should fit near-perfectly, got rms="
      ++ show rms ++ " maxError=" ++ show maxErr)
  putStrLn "SabrInterpolatedSmileSection: OK, calibrated smile reproduces the generating SABR vols"

  -- the upcast escape hatch: volatility through the generic SmileSection interface (only
  -- reachable this way now that the concrete type has no smileSectionVolatility of its own)
  -- must still reproduce the generating SABR vols, same as the rms/maxError check above.
  generic <- sabrInterpolatedSmileSectionAsSmileSection interp
  forM_ (zip strikes refVols) $ \(k, expected) -> do
    got <- smileSectionVolatility generic k
    checkClose (printf "SabrInterpolatedSmileSection upcast strike=%.2f vol" k) expected got 1e-6
  putStrLn "SabrInterpolatedSmileSection: OK, sabrInterpolatedSmileSectionAsSmileSection upcast works"
