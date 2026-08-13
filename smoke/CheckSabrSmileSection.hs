-- Smoke test: SabrSmileSection and SabrInterpolatedSmileSection.
--
-- 1. sabrSmileSection's volatility(strike)/variance(strike) must exactly match the
--    already-bound unsafeShiftedSabrVolatility formula it's built on
--    (see cbits' SabrSmileSection::volatilityImpl), for both VolatilityType cases --
--    this is enum-dispatched through a C-side (VolatilityType) cast, same class of
--    bug as the CPIInterpolationType incident, so a same-input-different-enum check
--    is needed, not just a hand-picked number.
-- 2. sabrInterpolatedSmileSection calibrates to a small synthetic strike/vol set and
--    the calibrated alpha/beta/nu/rho/vols should reproduce the input reasonably well.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckSabrSmileSection.hs -o /tmp/checksabr -outputdir /tmp/checksabr_build && /tmp/checksabr
import Control.Monad(forM_, unless)
import Text.Printf(printf)
import QuantLib.InterestRate(VolatilityType(..))
import QuantLib.PricingEngine(unsafeShiftedSabrVolatility)
import QuantLib.Time.Date
import QuantLib.Time.Schedule(TimeUnit(..))
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

  -- SabrInterpolatedSmileSection: calibrate to vols generated from known SABR params,
  -- then check the calibrated smile reprices those same strikes closely.
  let strikes = [0.01, 0.02, 0.03, 0.04, 0.05]
  refVols <- mapM (\k -> unsafeShiftedSabrVolatility k forward expiry alpha beta nu rho shift ShiftedLognormal) strikes
  atmVol <- unsafeShiftedSabrVolatility forward forward expiry alpha beta nu rho shift ShiftedLognormal
  now <- today
  optionDate <- addPeriod now (round (expiry * 365) :: Int, Days)
  interp <- sabrInterpolatedSmileSection optionDate forward strikes False atmVol refVols
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
