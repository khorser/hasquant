-- |Monte-Carlo zero-bond and zero-bond-option pricing on the three-factor
-- 'hybridHestonHullWhiteProcess', discounting each simulated path by the process's own
-- 'hybridHestonHullWhiteNumeraire' rather than by a deterministic curve.
--
-- Ported from QuantLib's test-suite\/hybridhestonhullwhiteprocess.cpp::testZeroBondPricing,
-- including its deliberately awkward zero curve (a sine-perturbed monthly 10y-20y grid plus a
-- 30y node) chosen upstream to exercise the joint process's drift and discounting. Two checks,
-- both against quantities the simulation never sees:
--
-- * the MC mean of @1 \/ numeraire(t, x_t)@ must reproduce the curve's own @P(0, t)@;
-- * the MC mean of that times a zero-bond call payoff must reproduce the closed-form
--   'QuantLib.Model.discountBondOption' of the matching 'QuantLib.Model.hullWhite' model.
--
-- Upstream draws 8191 Sobol-Brownian-bridge paths and allows 0.03 \/ 0.0035 absolute error; both
-- tolerances are kept. hasquant's 'sobolPathGenerator' stands in for upstream's
-- @SobolBrownianBridgeRsg@ with a plain Sobol sequence -- the bridge flag must be 'False' here,
-- since @MultiPathGenerator@ rejects it ("Brownian bridge not supported"); upstream gets its
-- bridging inside the sequence generator instead, which hasquant does not bind separately.
module QuantLib.Example.HestonHullWhiteMC
  (
    Result(..)
  , run
  ) where

import Control.Monad(foldM, forM)
import Data.List.NonEmpty(fromList)
import qualified Data.Vector.Storable as V

import QuantLib.Instrument.Option(OptionType(..))
import QuantLib.Math(SobolDirectionIntegers(..), Interpolation(..), timeGridFromVector, nonEmptyVector)
import QuantLib.Method(sobolPathGenerator, next, asset)
import QuantLib.Model(hullWhite, discountBond, discountBondOption)
import QuantLib.Process(hestonProcess, hullWhiteForwardProcess, setForwardMeasureTime
 , hybridHestonHullWhiteProcess, hybridHestonHullWhiteNumeraire, factors
 , HestonProcessDiscretization(..), HybridHestonHullWhiteProcessDiscretization(..))
import QuantLib.Quote(simpleQuote)
import qualified QuantLib.Settings as Settings
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Time.Schedule(Frequency(..))
import QuantLib.TermStructure.Yield(interpolatedZeroCurve, flatForward, discount)
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Date(today, addPeriod)
import QuantLib.Time.Schedule(dayCounter, years, DayCounterConstructor(..), TimeUnit(..))

data Result = Result
  { zeroBondError :: !Double    -- ^largest @|MC mean of 1\/numeraire - P(0,t)|@ over the grid
  , zeroOptionError :: !Double  -- ^largest @|MC mean of the option payoff - closed form|@ over the grid
  , gridPoints :: !Int          -- ^number of grid points checked
  } deriving Show

-- running sums of the two estimators at one grid point
data Acc = Acc !Double !Double

run :: IO Result
run = Settings.keepingSettings' $ do
  evalDate <- today
  Settings.setEvaluationDate (Just evalDate)
  dc <- dayCounter (Actual360 False)
  cal <- calendar TARGET

  let months = [120 .. 239 :: Int]
  monthDates <- mapM (\i -> addPeriod evalDate (i, Months)) months
  maturity <- addPeriod (last monthDates) (10, Years)
  let rates = 0.02 : [0.02 + 0.0002 * exp (sin (fromIntegral i / 8.0)) | i <- months] ++ [0.04]
      dates = evalDate : monthDates ++ [maturity]
  rTS <- interpolatedZeroCurve (fromList (zip dates rates)) dc cal [] Linear
  times <- mapM (\d -> years dc evalDate d Nothing Nothing) dates

  s0 <- simpleQuote 100.0
  -- a flat 0% dividend curve, as upstream: the joint process dereferences the handle, so it
  -- cannot be left empty here
  zeroQ <- simpleQuote 0.0
  qTS <- flatForward evalDate zeroQ dc Continuous Annual
  hProcess <- hestonProcess rTS (Just qTS) s0 0.02 1.0 0.2 0.5 (-0.8) QuadraticExponentialMartingale
  hwFwd <- hullWhiteForwardProcess rTS hwA hwSigma
  -- must precede the joint process's construction, which captures T at that point
  setForwardMeasureTime hwFwd (last times)
  joint <- hybridHestonHullWhiteProcess hProcess hwFwd (-0.4) BSMHullWhite
  hwModel <- hullWhite rTS hwA hwSigma

  -- the grid drops the final (maturity) node, as upstream's `times.end()-1` does
  let gridTimes = init times
      steps = length gridTimes - 1
  grid <- timeGridFromVector (maybe (error "empty time grid") id (nonEmptyVector (V.fromList gridTimes)))
  nFactors <- factors joint
  gen <- sobolPathGenerator JoeKuoD7 joint grid 0 (nFactors * fromIntegral steps) False

  let zero = replicate (m - 1) (Acc 0.0 0.0)
  totals <- foldM (\accs _ -> do
      path <- next gen
      states <- forM [0 .. nFactors - 1] (asset path)
      sample <- forM [1 .. m - 1] $ \j -> do
        let t = gridTimes !! j
            bigT = gridTimes !! (j + optionTenor)
        zeroBond <- recip <$> hybridHestonHullWhiteNumeraire joint t [st V.! j | st <- states]
        bondAtT <- discountBond hwModel t bigT (states !! 2 V.! j)
        pure (Acc zeroBond (zeroBond * max 0.0 (bondAtT - strike)))
      pure (zipWith' addAcc accs sample))
    zero [1 .. nrTrails :: Int]

  errs <- forM (zip [1 ..] totals) $ \(j, Acc zb zo) -> do
    let t = gridTimes !! j
        bigT = gridTimes !! (j + optionTenor)
        n = fromIntegral nrTrails
    expectedBond <- discount rTS t False
    expectedOption <- discountBondOption hwModel Call strike t bigT
    pure (abs (zb / n - expectedBond), abs (zo / n - expectedOption))

  pure (Result (maximum (map fst errs)) (maximum (map snd errs)) (length errs))
  where
    addAcc (Acc a b) (Acc c d) = Acc (a + c) (b + d)
    -- strict in the accumulated elements: a lazy zipWith over 8191 paths would build one thunk
    -- chain per grid point ('Acc' has strict fields, so a single seq forces both running sums)
    zipWith' f (x:xs) (y:ys) = let z = f x y in z `seq` (z : zipWith' f xs ys)
    zipWith' _ _ _ = []
    hwA = 0.05
    hwSigma = 0.05
    m = 90 :: Int
    optionTenor = 24 :: Int
    nrTrails = 8191 :: Int
    strike = 0.5 :: Double

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
