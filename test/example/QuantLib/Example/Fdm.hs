{-# LANGUAGE TemplateHaskell #-}
-- |Drives 'QuantLib.Method.fdmRollback' -- hasquant's Haskell-callback-driven FDM PDE solver --
-- with a hand-rolled 1D Black-Scholes operator in log-spot space (see CLAUDE.md's "coarsen the
-- language-boundary crossing" bullet and 'QuantLib.Internal.Type.withFdmApply' et al., which
-- reuse the same 'QuantLib.Internal.Type.withCostFunction' FunPtr-bracket pattern).
--
-- The operator itself (@mu*D1 + 0.5*sigma^2*D2 - r*I@, central differences with one-sided,
-- zero-second-derivative boundary rows) is exactly QuantLib's own @FdmBlackScholesOp::apply@
-- formula (@ql/methods/finitedifferences/operators/fdmblackscholesop.cpp@), just built directly
-- in Haskell instead of via a bound 'FdmMesher'/'FdmBlackScholesOp' -- there is no mesher binding
-- (per CLAUDE.md's "don't mirror the hierarchy 1:1": the grid is a plain @[Double]@, Haskell-owned
-- end to end). The grid is centred so @log(spot)@ falls exactly on a node, avoiding a need for any
-- interpolation binding to read the answer back off the grid.
--
-- Two checks:
--
-- * European call, rolled back with 'fdmRollback' (no step condition), against
--   'QuantLib.PricingEngine.analyticEuropeanEngine''s closed-form price.
-- * American call, rolled back with an early-exercise step condition (@max(v, intrinsic)@ at
--   every step), against hasquant's already-bound 'QuantLib.PricingEngine.fdBlackScholesVanillaEngine'.
module QuantLib.Example.Fdm
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar(addDays)

import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Option
import QuantLib.Math(FdmScheme(..))
import QuantLib.Method
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Syntax
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield

data Result = Result
  { fdmEuropeanR :: !Double
  , analyticEuropeanR :: !Double
  , fdmAmericanR :: !Double
  , fdAmericanR :: !Double
  }

-- |Thomas-algorithm solve of the tridiagonal system @M x = rhs@, @M@'s sub-\/super-diagonals
-- given by 'lo'\/'up' and main diagonal by 'di' (each of the same length as 'rhs', with
-- @lo!!0@\/@up!!(n-1)@ unused). Used as 'fdmRollback''s @solve_splitting@ callback below.
thomasSolve :: [Double] -> [Double] -> [Double] -> [Double] -> [Double]
thomasSolve lo di up rhs = foldr back [] (forward lo di up rhs)
  where
    back (_, d) [] = [d]
    back (c, d) acc@(xNext : _) = (d - c * xNext) : acc

    -- forward elimination: c'_i = up_i \/ denom, d'_i = (rhs_i - lo_i*d'_{i-1}) \/ denom
    forward (_ : los) (d0 : dis) (u0 : ups) (r0 : rs) = (c0, x0) : go x0 c0 los dis ups rs
      where
        c0 = u0 / d0
        x0 = r0 / d0
        go dPrev cPrev (a : as) (d : ds) (u : us) (r : rs') =
          let denom = d - a * cPrev
              c' = u / denom
              x' = (r - a * dPrev) / denom
          in (c', x') : go x' c' as ds us rs'
        go _ _ _ _ _ _ = []
    forward _ _ _ _ = []

-- |Sub-\/main-\/super-diagonal bands of @A = mu*D1 + 0.5*sigma2*D2 - r*I@ on a uniform grid of
-- 'm' points with spacing 'h' -- central differences in the interior, one-sided first derivative
-- and zero second derivative at the two boundary rows (matches how far the grid must be from the
-- region of interest for the boundary treatment not to matter at this tolerance).
operatorBands :: Int -> Double -> Double -> Double -> Double -> ([Double], [Double], [Double])
operatorBands m h mu sigma2 r = unzip3 (map row [0 .. m - 1])
  where
    row i
      | i == 0 = (0, -mu / h - r, mu / h)
      | i == m - 1 = (-mu / h, mu / h - r, 0)
      | otherwise =
          let a = mu / (2 * h)
              b = 0.5 * sigma2 / (h * h)
          in (b - a, -sigma2 / (h * h) - r, b + a)

-- |Apply the tridiagonal operator built from 'operatorBands' to a grid vector.
applyOp :: ([Double], [Double], [Double]) -> [Double] -> [Double]
applyOp (lo, di, up) u = go lo di up (0 : u) u (drop 1 u ++ [0])
  where
    go (l : ls) (d : ds) (uu : us) (p : ps) (c : cs) (nx : nxs) =
      (l * p + d * c + uu * nx) : go ls ds us ps cs nxs
    go _ _ _ _ _ _ = []

run :: IO Result
run = do
  setEvaluationDate $ Just tod
  dc <- dayCounter Actual365FixedStandard
  underQ <- simpleQuote spot
  riskFreeQ <- simpleQuote r
  divQ <- simpleQuote q
  volQ <- simpleQuote vol
  ts <- flatForward tod riskFreeQ dc Continuous Annual
  divTS <- flatForward tod divQ dc Continuous Annual
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) tod volQ dc
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False

  let payoff = PlainVanilla $ PlainVanillaPayoff Call strike
      europeanEx = European $ EuropeanExercise maturity
      americanEx = American Nothing maturity False
      intrinsicAt x = max (exp x - strike) 0
      grid0 = map intrinsicAt xs
      bands = operatorBands nPts h mu sigma2 r
      applyFn _ u = applyOp bands u
      applyDirFn _dir _t u = applyOp bands u
      solveFn _dir s _t u =
        let (lo, di, up) = bands
        in thomasSolve (map (s *) lo) (map (\d -> 1 + s * d) di) (map (s *) up) u

  europeanOpt <- vanillaOption payoff europeanEx
  analyticEuropeanEngine bsmProc Nothing >>= QuantLib.Instrument.setPricingEngine europeanOpt
  analytic <- npv europeanOpt

  fdmEuro <- fdmRollback 1 applyFn applyDirFn solveFn Nothing [] Douglas grid0 tMat 0 nSteps 0

  americanOpt <- vanillaOption payoff americanEx
  americanInst <- asOneAssetOption americanOpt
  fdBlackScholesVanillaEngine bsmProc (fromIntegral nSteps) (fromIntegral nPts) 0 Douglas False 0.0 CashDividendSpot
    >>= QuantLib.Instrument.setPricingEngine americanInst
  fdRef <- npv americanInst

  let stepTimes = [tMat * fromIntegral i / fromIntegral nSteps | i <- [1 .. nSteps]]
      stepCond _t u = zipWith max u grid0
  fdmAmerican <- fdmRollback 1 applyFn applyDirFn solveFn (Just stepCond) stepTimes Douglas grid0 tMat 0 nSteps 0

  return Result
    { fdmEuropeanR = fdmEuro !! centerIdx
    , analyticEuropeanR = analytic
    , fdmAmericanR = fdmAmerican !! centerIdx
    , fdAmericanR = fdRef
    }
  where
    tod = 1 `january` 2020
    -- 365 calendar days, not a year-based date step: Actual365Fixed's year fraction is
    -- actualDays\/365, so this is exactly 1.0 regardless of leap years. addGregorianYearsClip's
    -- 366-day span in a leap year would instead give T ~ 1.00274, silently biasing the operator's
    -- own tMat against what analyticEuropeanEngine\/fdBlackScholesVanillaEngine compute from dc.
    maturity = addDays 365 tod
    tMat = 1.0
    spot = 100
    strike = 100
    r = 0.05
    q = 0.02
    vol = 0.25
    sigma2 = vol * vol
    mu = r - q - 0.5 * sigma2
    nPts = 201
    centerIdx = nPts `div` 2
    halfWidth = 8 * vol * sqrt tMat
    h = 2 * halfWidth / fromIntegral (nPts - 1)
    xs = [log spot - halfWidth + fromIntegral i * h | i <- [0 .. nPts - 1]]
    nSteps = 200

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
