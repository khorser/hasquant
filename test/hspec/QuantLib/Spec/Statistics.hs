-- Risk-statistics checks against analytic Gaussian results.
module QuantLib.Spec.Statistics (spec) where

import Test.Hspec
import qualified Data.Vector.Storable as V

import QuantLib.Math
import QuantLib.Method(sobolGaussianRsg, nextSequence)

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec =
  describe "risk statistics (RiskStatistics over a caller-supplied sample)" $
    mapM_ scenarioSpec
      [ (0.0, 1.0)
      , (-1.0, 0.1)
      ]

-- |Enough Sobol draws for stable Gaussian moment estimates.
sampleSize :: Int
sampleSize = 8191

scenarioSpec :: (Double, Double) -> Spec
scenarioSpec (mean, sigma) =
  describe ("N(" ++ show mean ++ ", " ++ show sigma ++ ")") $
    it "matches the analytic gaussian moments and risk measures (riskstats.cpp::testResults)" $ do
      sample <- gaussianSample sampleSize mean sigma

      m <- riskStatisticsMean sample
      m `shouldSatisfy` closePrec mean (relTol mean 1.0e-3)

      v <- riskStatisticsVariance sample
      v `shouldSatisfy` closePrec (sigma * sigma) (sigma * sigma * 1.0e-2)

      sd <- riskStatisticsStandardDeviation sample
      sd `shouldSatisfy` closePrec sigma (sigma * 1.0e-2)

      -- percentile(0.5)/gaussianPercentile(0.5) of a gaussian sample is its own mean.
      p50 <- riskStatisticsPercentile sample 0.5
      p50 `shouldSatisfy` closePrec mean (relTol mean 1.0e-3)
      gp50 <- riskStatisticsGaussianPercentile sample 0.5
      gp50 `shouldSatisfy` closePrec mean (relTol mean 1.0e-3)

      -- Two-sigma quantiles give the expected upside and downside thresholds.
      let upperTail = mean + 2 * sigma
          lowerTail = mean - 2 * sigma
          twoSigma = normalCdf mean sigma upperTail

      pu <- riskStatisticsPotentialUpside sample twoSigma
      pu `shouldSatisfy` closePrec (max upperTail 0.0) (relTol (max upperTail 0.0) 1.0e-2)
      gpu <- riskStatisticsGaussianPotentialUpside sample twoSigma
      gpu `shouldSatisfy` closePrec (max upperTail 0.0) (relTol (max upperTail 0.0) 1.0e-2)

      var <- riskStatisticsValueAtRisk sample twoSigma
      let expVar = -(min lowerTail 0.0)
      var `shouldSatisfy` closePrec expVar (relTol expVar 1.0e-2)
      gvar <- riskStatisticsGaussianValueAtRisk sample twoSigma
      gvar `shouldSatisfy` closePrec expVar (relTol expVar 1.0e-2)

      -- expected shortfall's closed form (riskstats.cpp): -min(mean - sigma^2*phi(lowerTail)/(1-twoSigma), 0)
      es <- riskStatisticsExpectedShortfall sample twoSigma
      let expEs = -(min (mean - sigma * sigma * normalPdf mean sigma lowerTail / (1 - twoSigma)) 0.0)
      es `shouldSatisfy` closePrec expEs (relTol expEs 1.0e-2)
      ges <- riskStatisticsGaussianExpectedShortfall sample twoSigma
      ges `shouldSatisfy` closePrec expEs (relTol expEs 1.0e-2)

      -- shortfall(mean) is the probability of falling below the mean -- 0.5 for a gaussian.
      sf <- riskStatisticsShortfall sample mean
      sf `shouldSatisfy` closePrec 0.5 2.0e-3

  where
    relTol expected tol = if expected == 0.0 then tol else abs expected * tol

-- |Deterministic Sobol sample from @N(mean, sigma)@.
gaussianSample :: Int -> Double -> Double -> IO RealVector
gaussianSample n mean sigma = do
  rsg <- sobolGaussianRsg Jaeckel 1 42
  draws <- mapM (const (draw rsg)) [1 .. n]
  pure (V.fromList draws)
  where
    draw rsg = do
      (z, _weight) <- nextSequence rsg
      pure (mean + sigma * V.head z)

-- Abramowitz-Stegun 7.1.26 approximation; avoids an extra dependency.
erf :: Double -> Double
erf x =
  let a1 = 0.254829592; a2 = -0.284496736; a3 = 1.421413741
      a4 = -1.453152027; a5 = 1.061405429; p = 0.3275911
      sign = if x < 0 then -1 else 1
      ax = abs x
      t' = 1 / (1 + p * ax)
      y = 1 - (((((a5 * t' + a4) * t') + a3) * t' + a2) * t' + a1) * t' * exp (-ax * ax)
  in sign * y

normalCdf :: Double -> Double -> Double -> Double
normalCdf mean sigma x = 0.5 * (1 + erf ((x - mean) / (sigma * sqrt 2)))

normalPdf :: Double -> Double -> Double -> Double
normalPdf mean sigma x = exp (-(x - mean) * (x - mean) / (2 * sigma * sigma)) / (sigma * sqrt (2 * pi))
