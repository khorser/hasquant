-- |Computes CVA/DVA from an already-priced NPV grid (see 'SofrXva.Pricing.buildSofrProfile')
-- plus counterparty/own default-probability curves. Follows the standard semi-analytic
-- formula, using mean expected exposure (not a percentile) over scenarios at each timestep:
--
-- @
-- EE(t_k)  = mean over scenarios of max( NPV(scen, t_k), 0)
-- ENE(t_k) = mean over scenarios of max(-NPV(scen, t_k), 0)
-- CVA = (1 - R_cpty) * sum_k DF(t0, t_k) * EE(t_k)  * PD_cpty(t_{k-1}, t_k)
-- DVA = (1 - R_own)  * sum_k DF(t0, t_k) * ENE(t_k) * PD_own(t_{k-1}, t_k)
-- @
--
-- The percentile (PFE-style) profile is a separate report, not fed into CVA/DVA: it is the
-- unfloored quantile of the raw NPV distribution across scenarios at each timestep, matching
-- @xva_val.py@'s @PFE 95%@ line.
module SofrXva.Xva
  ( XvaResult(..)
  , computeXva
  ) where

import Control.Monad (forM)
import Data.List (nub, sort)
import Data.Time.Calendar (Day)
import qualified Data.Map.Strict as Map

import QuantLib.Math (Interpolation(..))
import QuantLib.Settings (setEvaluationDate)
import qualified QuantLib.TermStructure.Credit as Credit
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar (CalendarConstructor(..), calendar)
import QuantLib.Time.Schedule (DayCounterConstructor(..), dayCounter)

data XvaResult = XvaResult
  { xvaCva :: Double
  , xvaDva :: Double
  , xvaPfe :: [(Day, Double)] -- ^percentile PFE profile, one point per canonical timestep
  }

-- |'curves' is only consulted here for its (scen, ts) -> valuation date lookup (see
-- 'SofrXva.Data.loadSofrCurve'); the timestep dates it gives for scenario 0 are taken as
-- the canonical timestep calendar, mirroring how 'SofrXva.Pricing.buildSofrProfile' and
-- @xva_val.py@ both already treat scenario 0's dates as shared across all scenarios.
computeXva
  :: Map.Map (Int, Int) Double -- ^NPVs, keyed (scen, ts) (see 'SofrXva.Pricing.SofrProfile')
  -> Map.Map (Int, Int) (Day, [(Day, Double)]) -- ^curve map, for its (scen, ts) -> date lookup
  -> TS.YieldTermStructure -- ^t0 discount curve (see 'SofrXva.Pricing.SofrProfile')
  -> [(Day, Double)] -- ^counterparty survival-probability curve points
  -> [(Day, Double)] -- ^own survival-probability curve points
  -> Double -- ^counterparty recovery rate
  -> Double -- ^own recovery rate
  -> Double -- ^percentile for the PFE report, e.g. 0.95
  -> IO XvaResult
computeXva npvs curves t0Discount cptyPoints ownPoints cptyRecovery ownRecovery percentile = do
  let d0 = fst (curves Map.! (0, 0))
  -- buildSofrProfile's own loop leaves the global evaluation date at the last timestep it
  -- processed; reset it to t0 before building/querying anything date-sensitive here.
  setEvaluationDate (Just d0)

  dc <- dayCounter Actual365FixedStandard
  cal <- calendar UnitedStatesNYSE

  cptyDTS <- Credit.interpolatedSurvivalProbabilityCurve cptyPoints dc cal [] LogLinear
  ownDTS <- Credit.interpolatedSurvivalProbabilityCurve ownPoints dc cal [] LogLinear

  let tss = sort [ts | (s, ts) <- Map.keys curves, s == 0]
      thisDates = [fst (curves Map.! (0, ts)) | ts <- tss]
      prevDates = case thisDates of
        [] -> []
        (_ : _) -> d0 : init thisDates
      scens = sort (nub (map fst (Map.keys npvs)))

      npvsAt ts = [v | scen <- scens, Just v <- [Map.lookup (scen, ts) npvs]]
      mean [] = 0
      mean xs = sum xs / fromIntegral (length xs)
      ee ts = mean (map (max 0) (npvsAt ts))
      ene ts = mean (map (max 0 . negate) (npvsAt ts))

  buckets <- forM (zip3 tss prevDates thisDates) $ \(ts, dPrev, dThis) -> do
    pdCpty <- Credit.defaultProbabilityBetween cptyDTS dPrev dThis True
    pdOwn <- Credit.defaultProbabilityBetween ownDTS dPrev dThis True
    df <- TS.discount' t0Discount dThis True
    pure (df * ee ts * pdCpty, df * ene ts * pdOwn, (dThis, quantile percentile (npvsAt ts)))

  let (cvaTerms, dvaTerms, pfe) = unzip3 buckets
  pure XvaResult
    { xvaCva = (1 - cptyRecovery) * sum cvaTerms
    , xvaDva = (1 - ownRecovery) * sum dvaTerms
    , xvaPfe = pfe
    }

-- |Linearly-interpolated quantile (numpy\/pandas' default @linear@ method): the 'p'-th
-- quantile of 'xs' sits at fractional rank @p * (n - 1)@ among the sorted values,
-- interpolating between the two nearest ranks.
quantile :: Double -> [Double] -> Double
quantile _ [] = 0
quantile p xs =
  let sorted = sort xs
      n = length sorted
      h = p * fromIntegral (n - 1)
      lo = floor h
      hi = ceiling h
      frac = h - fromIntegral lo
  in sorted !! lo + frac * (sorted !! hi - sorted !! lo)
