-- Interpolated zero inflation curves and construction-time price seasonality. Expected
-- seasonal rates follow MultiplicativePriceSeasonality::seasonalityCorrection on a flat curve.
module QuantLib.Spec.TermStructure.Inflation (spec) where

import Control.Monad(forM_)
import Data.List.NonEmpty(fromList)
import Data.Time.Calendar(Day, fromGregorian, addGregorianMonthsClip, diffDays)
import Test.Hspec

import qualified QuantLib.Context as Context
import QuantLib.Math(Interpolation(..), Approximation(..))
import QuantLib.TermStructure.Inflation
import QuantLib.Time.Schedule

import QuantLib.Spec.Helpers(closePrec)

baseDate :: Day
baseDate = fromGregorian 2020 1 1

monthly :: Integer -> Day
monthly k = addGregorianMonthsClip k baseDate

spec :: Spec
spec = describe "zero inflation term structures" $ do
  it "interpolatedZeroInflationCurve reproduces its node rates" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just baseDate)
    dc <- dayCounter Actual365FixedStandard
    let nodes = [(baseDate, 0.010), (monthly 12, 0.015), (monthly 36, 0.020), (monthly 120, 0.025)]
    forM_ [Linear, Cubic Kruger] $ \i -> do
      curve <- interpolatedZeroInflationCurve baseDate (fromList nodes) Monthly dc Nothing i
      forM_ (drop 1 nodes) $ \(d, r) -> zeroRate curve d False >>= (`shouldSatisfy` closePrec r 1.0e-10)

  it "applies multiplicative price seasonality normalized to the curve's base date" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just baseDate)
    dc <- dayCounter Actual365FixedStandard
    let flatRate = 0.02
        nodes = [(baseDate, flatRate), (monthly 120, flatRate)]
        factors = [1.0, 1.01, 1.02, 1.015, 1.005, 0.995, 0.99, 0.985, 0.99, 1.0, 1.005, 1.01] :: [Double]
        curveWith s = interpolatedZeroInflationCurve baseDate (fromList nodes) Monthly dc s Linear
    plain <- curveWith Nothing
    unit <- curveWith (Just (MultiplicativePriceSeasonality baseDate Monthly (replicate 12 1.0)))
    seasonal <- curveWith (Just (MultiplicativePriceSeasonality baseDate Monthly factors))
    forM_ [1 .. 11 :: Int] $ \k -> do
      let d = monthly (fromIntegral k)
          t = fromIntegral (diffDays d baseDate) / 365
          -- factors !! 0 is 1, so the base-date normalization is the factor itself
          expected = (1 + flatRate) * (factors !! k) ** (1 / t) - 1
      r <- zeroRate plain d False
      r `shouldSatisfy` closePrec flatRate 1.0e-12
      zeroRate unit d False >>= (`shouldSatisfy` closePrec r 1.0e-12)
      zeroRate seasonal d False >>= (`shouldSatisfy` closePrec expected 1.0e-10)

    kerkhof <- curveWith (Just (KerkhofSeasonality baseDate factors))
    rk <- zeroRate kerkhof (monthly 5) False
    abs (rk - flatRate) `shouldSatisfy` (> 1.0e-6)

  it "rejects multi-year seasonality inconsistent at whole years from the base date" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just baseDate)
    dc <- dayCounter Actual365FixedStandard
    let nodes = [(baseDate, 0.02), (monthly 120, 0.02)]
        factors = replicate 12 1.0 ++ replicate 12 1.1
    interpolatedZeroInflationCurve baseDate (fromList nodes) Monthly dc
      (Just (MultiplicativePriceSeasonality baseDate Monthly factors)) Linear `shouldThrow` anyException
