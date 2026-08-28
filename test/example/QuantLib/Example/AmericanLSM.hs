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
import Control.Monad(replicateM)
import Data.List(transpose)

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

mean :: [Double] -> Double
mean xs = sum xs / fromIntegral (length xs)

-- |one backward-induction step: discount both cashflow sets to this exercise date, fit the
-- continuation value against the (in-the-money) calibration paths, then decide early exercise on
-- both the calibration paths (to keep the recursion's own targets consistent) and the pricing
-- paths (using the calibration fit only -- never their own state -- to stay unbiased).
step :: PolynomialType -> Word -> Double -> Double -> [Double] -> [Double] -> [Double] -> [Double] -> [Bool]
     -> IO ([Double], [Double], [Bool])
step polyT order strike df calibS priceS calibCF0 priceCF0 exFlags0 = do
  let calibCF = map (* df) calibCF0
      priceCF = map (* df) priceCF0
      calibEx = map (payoff strike) calibS
      priceEx = map (payoff strike) priceS
      (fitStates, fitTargets, _) = unzip3 $ filter (\(_, _, e) -> e > 0) $ zip3 calibS calibCF calibEx
  if length fitStates <= fromIntegral order
    then return (calibCF, priceCF, exFlags0)
    else do
      contCalib <- lsmRegress polyT order fitStates fitTargets calibS
      contPrice <- lsmRegress polyT order fitStates fitTargets priceS
      let calibCF' = zipWith3 (\cf ex cont -> if ex > 0 && ex > cont then ex else cf) calibCF calibEx contCalib
          decidePrice cf ex cont = if ex > 0 && ex > cont then (ex, True) else (cf, False)
          (priceCF', exercisedNow) = unzip $ zipWith3 decidePrice priceCF priceEx contPrice
          exFlags' = zipWith (||) exFlags0 exercisedNow
      return (calibCF', priceCF', exFlags')

-- |walk exercise dates strictly backward, from the second-to-last grid point (index
-- @timeSteps-1@) down to index 1; index 0 (the valuation date) is discounted to but is never
-- itself an exercise opportunity. @dfs !! i@ is the one-step discount factor bringing a
-- cashflow observed at index @i+1@ back to index @i@.
goBack :: PolynomialType -> Word -> Double -> Int -> [Double] -> [[Double]] -> [[Double]] -> [Double] -> [Double]
       -> [Bool] -> IO ([Double], [Double], [Bool])
goBack polyT order strike i dfs calibRest priceRest calibCF priceCF exFlags
  | i < 1 = return (calibCF, priceCF, exFlags)
  | otherwise = do
      let calibS = last calibRest
          priceS = last priceRest
          df = dfs !! i
      (calibCF', priceCF', exFlags') <- step polyT order strike df calibS priceS calibCF priceCF exFlags
      goBack polyT order strike (i - 1) dfs (init calibRest) (init priceRest) calibCF' priceCF' exFlags'

run :: IO Result
run = do
  setEvaluationDate $ Just tod
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
  discFactors <- mapM (\x -> discount ts x False) times
  let dfs = zipWith (flip (/)) discFactors (drop 1 discFactors)

  genCalib <- pathGenerator PseudoRandom bsmProc grid seedCalib (size grid - 1) False
  calibPaths <- replicateM nCalib (next genCalib >>= \s -> asset s 0)
  genPrice <- pathGenerator PseudoRandom bsmProc grid seedPrice (size grid - 1) False
  pricePaths <- replicateM nPrice (next genPrice >>= \s -> asset s 0)
  let calibStates = transpose calibPaths
      priceStates = transpose pricePaths
      nSteps = fromIntegral timeSteps
      calibCF0 = map (payoff strike) (calibStates !! nSteps)
      priceCF0 = map (payoff strike) (priceStates !! nSteps)

  -- indices 1..nSteps-1: excludes index 0 (valuation date, never an exercise opportunity) and
  -- index nSteps (maturity, already consumed above to seed calibCF0/priceCF0)
  (calibFinal, priceFinal, exFlags) <- goBack polyT order strike (nSteps - 1) dfs
    (init (drop 1 calibStates)) (init (drop 1 priceStates)) calibCF0 priceCF0 (replicate nPrice False)

  let df0 = discFactors !! 1 / head discFactors
      lsmP = mean (map (* df0) priceFinal)
      calibP = mean (map (* df0) calibFinal)
      exProb = fromIntegral (length (filter id exFlags)) / fromIntegral nPrice

  let payoffQL = PlainVanilla $ PlainVanillaPayoff Put strike
      americanEx = American Nothing maturity False
  americanOpt <- vanillaOption payoffQL americanEx
  mcaEng <- mcAmericanEngine PseudoRandom Statistics bsmProc (Just timeSteps) Nothing True False Nothing (Just 0.02) Nothing seedCalib order polyT (Just (fromIntegral nCalib)) Nothing Nothing
  QuantLib.Instrument.setPricingEngine americanOpt mcaEng
  mcA <- npv americanOpt

  return $ Result lsmP calibP mcA exProb
  where
    tod = 15 `may` 1998
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
