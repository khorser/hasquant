{-# LANGUAGE TemplateHaskell #-}
-- |Prices an American put with a Haskell-defined @max(K-S,0)@ payoff by driving QuantLib's
-- Longstaff-Schwartz regression primitive ('QuantLib.Method.lsmRegress') from a hand-written
-- backward-induction loop, instead of going through a bound 'QuantLib.Instrument.Option.Payoff'
-- and 'QuantLib.PricingEngine.mcAmericanEngine'. Demonstrates the pattern a custom (non-vanilla)
-- early-exercise payoff would use; validated against 'mcAmericanEngine' pricing the equivalent
-- bound vanilla option on the same fixture (same as "QuantLib.Example.EquityOption"'s American
-- case: S=36, K=40, r=6%, vol=20%, val date 15-May-1998, maturity 17-May-1999).
module QuantLib.Example.AmericanLSM
  (
    Result(..)
  , run
  ) where
import qualified Data.Vector as BV
import qualified Data.Vector.Storable as V
import qualified Data.Vector.Unboxed as U

import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.Math
import QuantLib.Method
import QuantLib.Process
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Syntax

data Result = Result
  { lsmPrice :: !Double        -- ^custom LSM loop, out-of-sample pricing paths priced against a fit from a separate calibration path set (unbiased)
  , calibPrice :: !Double      -- ^same loop, but pricing the calibration paths against their own (in-sample) fit -- the naive, biased single-pass estimate
  , mcPrice :: !Double         -- ^'mcAmericanEngine' pricing the equivalent bound vanilla option
  , exerciseProb :: !Double    -- ^fraction of pricing paths exercised before maturity
  }

payoff :: Double -> Double -> Double
payoff strike s = max (strike - s) 0

mean :: RealVector -> Double
mean xs = V.sum xs / fromIntegral (V.length xs)

-- |one backward-induction step: discount both cashflow sets to this exercise date, fit the
-- continuation value against the (in-the-money) calibration paths, then decide early exercise on
-- both the calibration paths (to keep the recursion's own targets consistent) and the pricing
-- paths (using the calibration fit only -- never their own state -- to stay unbiased).
step :: PolynomialType -> Word -> Double -> Double
     -> RealVector -> RealVector -> RealVector -> RealVector -> U.Vector Bool
     -> IO (RealVector, RealVector, U.Vector Bool)
step polyT order strike df calibS priceS calibCF0 priceCF0 exFlags0 = do
  let calibCF = V.map (* df) calibCF0
      priceCF = V.map (* df) priceCF0
      calibEx = V.map (payoff strike) calibS
      priceEx = V.map (payoff strike) priceS
      fitStates = V.ifilter (\i _ -> calibEx V.! i > 0) calibS
      fitTargets = V.ifilter (\i _ -> calibEx V.! i > 0) calibCF
  if V.length fitStates <= fromIntegral order
    then return (calibCF, priceCF, exFlags0)
    else do
      contCalib <- lsmRegress polyT order fitStates fitTargets calibS
      contPrice <- lsmRegress polyT order fitStates fitTargets priceS
      let exercise _ ex cont = ex > 0 && ex > cont
          calibCF' = V.zipWith3 (\cf ex cont -> if exercise cf ex cont then ex else cf) calibCF calibEx contCalib
          priceCF' = V.zipWith3 (\cf ex cont -> if exercise cf ex cont then ex else cf) priceCF priceEx contPrice
          exercisedNow = U.generate (V.length priceCF) $ \i ->
            exercise (priceCF V.! i) (priceEx V.! i) (contPrice V.! i)
          exFlags' = U.zipWith (||) exFlags0 exercisedNow
      return (calibCF', priceCF', exFlags')

-- |walk exercise dates strictly backward, from the second-to-last grid point (index
-- @timeSteps-1@) down to index 1; index 0 (the valuation date) is discounted to but is never
-- itself an exercise opportunity. @dfs !! i@ is the one-step discount factor bringing a
-- cashflow observed at index @i+1@ back to index @i@.
goBack :: PolynomialType -> Word -> Double -> Int -> RealVector -> BV.Vector RealVector -> BV.Vector RealVector
       -> RealVector -> RealVector -> U.Vector Bool -> IO (RealVector, RealVector, U.Vector Bool)
goBack polyT order strike i dfs calibStates priceStates calibCF priceCF exFlags
  | i < 1 = return (calibCF, priceCF, exFlags)
  | otherwise = do
      let calibS = calibStates BV.! i
          priceS = priceStates BV.! i
          df = dfs V.! i
      (calibCF', priceCF', exFlags') <- step polyT order strike df calibS priceS calibCF priceCF exFlags
      goBack polyT order strike (i - 1) dfs calibStates priceStates calibCF' priceCF' exFlags'

-- |Turn path-major samples into time-major state vectors without ever materialising a list of
-- path values.  The outer boxed vector is deliberately small (one entry per grid point); every
-- path-wise numerical calculation stays in a contiguous storable vector.
timeMajor :: Int -> BV.Vector RealVector -> BV.Vector RealVector
timeMajor nTimes paths = BV.generate nTimes $ \timeIndex ->
  V.generate (BV.length paths) $ \pathIndex -> (paths BV.! pathIndex) V.! timeIndex

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Actual365FixedStandard
  underQ <- simpleQuote under
  riskFreeQ <- simpleQuote riskFreeRate
  ts <- flatForward settl riskFreeQ dc Continuous Annual
  divQ <- simpleQuote dividend
  divTS <- flatForward settl divQ dc Continuous Annual
  volQ <- simpleQuote vol
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) settl volQ dc
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False

  t <- years dc settl maturity Nothing Nothing
  grid <- timeGrid t timeSteps
  times <- points grid
  discFactors <- V.mapM (\x -> discount ts x False) times
  let dfs = V.zipWith (flip (/)) discFactors (V.tail discFactors)
      d0 = discFactors V.! 0
      d1 = discFactors V.! 1

  genCalib <- pathGenerator PseudoRandom bsmProc grid seedCalib (size grid - 1) False
  calibPaths <- BV.replicateM nCalib (next genCalib >>= \s -> asset s 0)
  genPrice <- pathGenerator PseudoRandom bsmProc grid seedPrice (size grid - 1) False
  pricePaths <- BV.replicateM nPrice (next genPrice >>= \s -> asset s 0)
  let calibStates = timeMajor (fromIntegral timeSteps + 1) calibPaths
      priceStates = timeMajor (fromIntegral timeSteps + 1) pricePaths
      nSteps = fromIntegral timeSteps
      calibCF0 = V.map (payoff strike) (calibStates BV.! nSteps)
      priceCF0 = V.map (payoff strike) (priceStates BV.! nSteps)

  -- indices 1..nSteps-1: excludes index 0 (valuation date, never an exercise opportunity) and
  -- index nSteps (maturity, already consumed above to seed calibCF0/priceCF0)
  (calibFinal, priceFinal, exFlags) <- goBack polyT order strike (nSteps - 1) dfs
    calibStates priceStates calibCF0 priceCF0 (U.replicate nPrice False)

  let df0 = d1 / d0
      lsmP = mean (V.map (* df0) priceFinal)
      calibP = mean (V.map (* df0) calibFinal)
      exProb = fromIntegral (U.length (U.filter id exFlags)) / fromIntegral nPrice

  let payoffQL = PlainVanilla $ PlainVanillaPayoff Put strike
      americanEx = American Nothing maturity False
  americanOpt <- vanillaOption payoffQL americanEx
  mcaEng <- mcAmericanEngine PseudoRandom Statistics bsmProc (Just timeSteps) Nothing True False Nothing (Just 0.02) Nothing seedCalib order polyT (Just (fromIntegral nCalib)) Nothing Nothing
  QuantLib.Instrument.setPricingEngine americanOpt mcaEng
  mcA <- npv americanOpt

  return $ Result lsmP calibP mcA exProb
  where
    evalDate = 15 `may` 1998
    settl = 17 `may` 1998
    under = 36
    strike = 40
    dividend = 0.0
    riskFreeRate = 0.06
    vol = 0.20
    maturity = 17 `may` 1999
    timeSteps = 100 :: Word
    order = 2 :: Word
    polyT = Monomial
    nCalib = 4096 :: Int
    nPrice = 8192 :: Int
    seedCalib = 42 :: Word
    seedPrice = 43 :: Word

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
