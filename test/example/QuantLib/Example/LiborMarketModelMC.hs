-- |Monte-Carlo caplet pricing under a one-factor Libor market model, discounting each simulated
-- forward-rate vector with the process's own 'liborForwardModelProcessDiscountBond' rather than
-- with a deterministic curve.
--
-- Ported from QuantLib's test-suite\/libormarketmodelprocess.cpp::testMonteCarloCapletPricing
-- (its one-factor @process1@ leg): a 'liborForwardModelProcess' over 10 Euribor-1Y forwards,
-- wired to an 'QuantLib.Model.lfmHullWhiteParameterization' built from upstream's cap-vol curve
-- via 'QuantLib.Model.setCovarParam' -- without which the process holds no covariance
-- parameterization and cannot be simulated at all.
--
-- Each path yields one forward-rate vector, read at each rate's own fixing time; the caplet
-- payoff @max(r_k - 4%, 0) * tau_k@ is discounted by @discountBond@'s /k/-th cumulative factor.
-- The golden values are upstream's cached @capletNpv@ array. Upstream draws 250k paths and
-- compares within each estimator's own standard error; this runs a smaller Sobol sample and
-- asserts an absolute tolerance instead, since a low-discrepancy sample has no meaningful
-- per-path error estimate.
module QuantLib.Example.LiborMarketModelMC
  (
    Result(..)
  , run
  ) where

import Control.Monad(foldM, forM)
import Data.List.NonEmpty(fromList)
import Data.Maybe(fromMaybe)
import qualified Data.Vector.Storable as V

import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import qualified QuantLib.Index.InterestRate as Ibor(fixingDays)
import QuantLib.InterestRate(VolatilityType(..))
import QuantLib.Math(SobolDirectionIntegers(..), Interpolation(..), timeGridFromVector', nonEmptyVector, points, boxedRealMatrix)
import QuantLib.Method(sobolPathGenerator, next, asset)
import QuantLib.Model(lfmHullWhiteParameterization, setCovarParam)
import QuantLib.Process(liborForwardModelProcess, liborForwardModelProcessFixingDates
 , liborForwardModelProcessFixingTimes, liborForwardModelProcessAccrualTimes
 , liborForwardModelProcessDiscountBond, factors)
import qualified QuantLib.Settings as Settings
import QuantLib.TermStructure.Yield(interpolatedZeroCurve)
import qualified QuantLib.TermStructure.Volatility as Vol(capletVarianceCurve)
import QuantLib.Time.Calendar(adjust, advance, calendar, BusinessDayConvention(..), CalendarConstructor(..))
import QuantLib.Time.Date(september)
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..))

data Result = Result
  { capletNpvs :: ![Double]  -- ^simulated caplet NPVs, one per forward rate
  , maxError :: !Double      -- ^largest absolute deviation from upstream's cached values
  } deriving Show

run :: IO Result
run = Settings.keepingSettings' $ do
  let fixtureDate = 4 `september` 2005
      curveEndDate = 4 `september` 2018
      len = 10 :: Word
  cal <- calendar TARGET
  evalDate <- adjust cal fixtureDate Following
  Settings.setEvaluationDate (Just evalDate)
  dc <- dayCounter (Actual360 False)
  emptyIndex <- iborIndex Euribor1Y Nothing
  firstPillar <- advance cal evalDate (fromIntegral (Ibor.fixingDays emptyIndex), Days) Following False
  rTS <- interpolatedZeroCurve (fromList [(firstPillar, 0.01), (curveEndDate, 0.08)]) dc cal [] Linear
  idx <- iborIndex Euribor1Y (Just rTS)

  -- the cap-vol curve is built off a len+1-sized process, as upstream's makeCapVolCurve does
  volProcess <- liborForwardModelProcess (len + 1) idx
  volDates <- liborForwardModelProcessFixingDates volProcess
  volDc <- dayCounter ActualActualISDA
  capletVol <- Vol.capletVarianceCurve evalDate
    (fromList (zip (take (fromIntegral len) (drop 1 volDates)) capletVols)) volDc ShiftedLognormal 0.0

  process <- liborForwardModelProcess len idx
  parameterization <- lfmHullWhiteParameterization process capletVol emptyCorrelation 1
  setCovarParam process parameterization

  fixingTimes <- liborForwardModelProcessFixingTimes process
  accruals <- liborForwardModelProcessAccrualTimes process
  grid <- timeGridFromVector' (fromMaybe (error "empty fixing times") (nonEmptyVector (V.fromList fixingTimes))) 12
  gridPts <- points grid
  -- each rate is read at its own fixing time's index in the grid, as upstream's `location` does
  let location = [fromMaybe (error "fixing time not on grid") (V.findIndex (== t) gridPts) | t <- fixingTimes]
      steps = fromIntegral (V.length gridPts) - 1
  nFactors <- factors process
  gen <- sobolPathGenerator JoeKuoD7 process grid 42 (nFactors * steps) False

  totals <- foldM (\acc _ -> do
      path <- next gen
      rateVecs <- forM [0 .. len - 1] (asset path)
      let rates = zipWith (V.!) rateVecs location
      dfs <- liborForwardModelProcessDiscountBond process rates
      let payoffs = zipWith3 (\df r (st, en) -> df * max 0.0 (r - capRate) * (en - st)) dfs rates accruals
      pure (zipWith' (+) acc payoffs))
    (replicate (fromIntegral len) 0.0) [1 .. nrTrails :: Int]

  let npvs = map (/ fromIntegral nrTrails) totals
  pure (Result npvs (maximum (map abs (zipWith (-) npvs expectedNpvs))))
  where
    zipWith' f (x:xs) (y:ys) = let z = f x y in z `seq` (z : zipWith' f xs ys)
    zipWith' _ _ _ = []
    emptyCorrelation = either error id (boxedRealMatrix 0 0 [])
    capletVols = [0.1440, 0.1715, 0.1681, 0.1664, 0.1617, 0.1578, 0.1540, 0.1521, 0.1486, 0.1454]
    capRate = 0.04 :: Double
    nrTrails = 20000 :: Int
    -- test-suite/libormarketmodelprocess.cpp's cached capletNpv[]
    expectedNpvs =
      [ 0.000000000000, 0.000002841629, 0.002533279333, 0.009577143571, 0.017746502618
      , 0.025216116835, 0.031608230268, 0.036645683881, 0.039792254012, 0.041829864365 ]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
