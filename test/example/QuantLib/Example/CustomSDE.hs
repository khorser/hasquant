{-# LANGUAGE TemplateHaskell #-}
-- |Simulates a stochastic process QuantLib does /not/ bind -- a CEV diffusion
-- @dS = mu S dt + sigma S^beta dW@ -- by drawing standard normals from
-- 'QuantLib.Method.gaussianRsg' and writing the evolution step in Haskell, then pricing an
-- American put on it with 'QuantLib.Method.lsmRegress'. Nothing crosses the FFI boundary inside
-- the path loop.
--
-- This is the @StochasticProcess@ half of issue #18, and it is deliberately /not/ a callback.
-- QuantLib's @MultiPathGenerator@ (which 'QuantLib.Method.pathGenerator' wraps) calls
-- @process->evolve@ once per timestep /per path/, so a Haskell-subclassed @StochasticProcess@
-- would put an FFI crossing in the hottest loop there is -- millions of them for a realistic run.
-- The reusable inner primitive sits one level lower: the gaussian sequence generator the path
-- generator merely consumes. Exposing that and letting Haskell drive the evolution is the same
-- decomposition 'QuantLib.Method.lsmRegress' applies to @LongstaffSchwartzPathPricer@, and it
-- costs one crossing per /path/ instead of one per timestep. Little is given up: a Haskell-evolved
-- SDE yields paths rather than a @StochasticProcess@ object, but no stock QuantLib pricing engine
-- would have accepted a custom process anyway -- their constructors are typed on concrete process
-- classes (@GeneralizedBlackScholesProcess@ and friends), not on the abstract base.
--
-- Three checks, on "QuantLib.Example.AmericanLSM"'s fixture (S=36, K=40, r=6%, vol=20%, val date
-- 15-May-1998, maturity 17-May-1999) so the reference numbers carry over:
--
-- * /The draws line up with QuantLib's own./ Evolving a Black-Scholes SDE in Haskell from
--   'QuantLib.Method.nextSequence' -- with the exact lognormal step QuantLib's own
--   @GeneralizedBlackScholesProcess::evolve@ uses -- reproduces 'QuantLib.Method.pathGenerator''s
--   path for the same trait, dimension and seed, to floating-point equality. This pins the draw
--   order @MultiPathGenerator@ consumes (offset @(i-1)*factors@ per timestep) as much as it pins
--   the binding itself.
-- * /The Haskell-driven price is right./ The American put priced off those Haskell-evolved paths
--   via 'QuantLib.Method.lsmRegress' agrees with
--   'QuantLib.PricingEngine.mcAmericanEngine' on the equivalent bound vanilla option.
-- * /The custom SDE actually runs./ The same loop with the CEV step at @beta = 0.7@ prices an
--   American put on a process with no QuantLib binding at all. Its own sanity check is the
--   degenerate case: at @beta = 1@ the CEV step is Euler-discretized geometric Brownian motion, so
--   its price must sit close to the exact-lognormal Black-Scholes price above, differing only by
--   the Euler discretization error.
module QuantLib.Example.CustomSDE
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
import QuantLib.Process hiding(drift)
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Syntax
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield

data Result = Result
  { gbmPathMaxDiffR :: !Double  -- ^largest per-node gap between a Haskell-evolved BS path and 'pathGenerator''s own, same seed
  , gbmLsmPriceR :: !Double     -- ^American put off Haskell-evolved exact-lognormal BS paths, via 'lsmRegress'
  , mcPriceR :: !Double         -- ^'mcAmericanEngine' on the equivalent bound vanilla option
  , cevLsmPriceR :: !Double     -- ^same loop under the unbound CEV SDE at @beta = 0.7@
  , cevAtBeta1PriceR :: !Double -- ^the CEV step at @beta = 1@ -- Euler-discretized GBM, so close to 'gbmLsmPriceR'
  }

-- |@max(K - S, 0)@ -- the payoff no bound early-exercise engine could take here, since it is
-- applied to a process none of them accept.
payoff :: Double -> Double -> Double
payoff strike s = max (strike - s) 0

mean :: [Double] -> Double
mean xs = sum xs / fromIntegral (length xs)

-- |One Haskell-written evolution step, taking the current state, the timestep and one standard
-- normal draw. This is the function a Haskell-defined @StochasticProcess@ subclass would have
-- supplied as a per-timestep callback; here it is just an ordinary Haskell function, called from
-- an ordinary Haskell loop.
type Evolve = Double -> Double -> Double -> Double

-- |Exact lognormal step, matching @GeneralizedBlackScholesProcess::evolve@'s own closed form --
-- used for the check against 'pathGenerator', which must agree to floating-point equality.
evolveGBM :: Double -> Double -> Evolve
evolveGBM drift sigma dt x dw = x * exp ((drift - 0.5 * sigma * sigma) * dt + sigma * sqrt dt * dw)

-- |Euler step of @dS = mu S dt + sigma S^beta dW@ -- the CEV diffusion, which hasquant binds no
-- process for. Floored at 0: an Euler step can overshoot below zero near the origin, where the
-- true CEV process is absorbed.
evolveCEV :: Double -> Double -> Double -> Evolve
evolveCEV drift sigma expo dt x dw = max 0 (x + drift * x * dt + sigma * (x ** expo) * sqrt dt * dw)

-- |Draw one path: @dimension@ normals from the generator, folded through @step@ from @x0@.
drawPath :: GaussianRsg -> Evolve -> Double -> Double -> IO [Double]
drawPath rsg step x0 dt = do
  (draws, _weight) <- nextSequence rsg
  pure (scanl (step dt) x0 draws)

-- |One backward-induction step of the Longstaff-Schwartz recursion, over a single path set (this
-- example prices in-sample for brevity -- "QuantLib.Example.AmericanLSM" shows the unbiased
-- calibration\/pricing split, which is orthogonal to what is being demonstrated here).
lsmStep :: PolynomialType -> Word -> Double -> Double -> [Double] -> [Double] -> IO [Double]
lsmStep polyT order strike df states cashflows = do
  let discounted = map (* df) cashflows
      exercise = map (payoff strike) states
      (fitStates, fitTargets, _) = unzip3 $ filter (\(_, _, e) -> e > 0) $ zip3 states discounted exercise
  if length fitStates <= fromIntegral order
    then pure discounted
    else do
      continuation <- lsmRegress polyT order fitStates fitTargets states
      pure (zipWith3 (\cf ex cont -> if ex > 0 && ex > cont then ex else cf) discounted exercise continuation)

-- |Walk exercise dates strictly backward, from the second-to-last grid index down to index 1.
-- Index 0 (the valuation date) is discounted to but is never an exercise opportunity.
lsmBackward :: PolynomialType -> Word -> Double -> [Double] -> [[Double]] -> [Double] -> IO [Double]
lsmBackward _ _ _ _ [] cashflows = pure cashflows
lsmBackward polyT order strike dfs statesRest cashflows = do
  let i = length statesRest
  cashflows' <- lsmStep polyT order strike (dfs !! i) (last statesRest) cashflows
  lsmBackward polyT order strike dfs (init statesRest) cashflows'

-- |Price an American put off a freshly drawn path set under the given evolution step.
priceUnder :: PolynomialType -> Word -> Double -> Double -> Double -> Word -> Word -> Int -> [Double]
           -> Evolve -> IO Double
priceUnder _ _ _ _ _ _ _ _ [] _ = fail "priceUnder: empty discount-factor list"
priceUnder polyT order strike x0 dt nSteps seed nPaths dfs@(df0 : _) step = do
  rsg <- gaussianRsg PseudoRandom nSteps seed
  paths <- replicateM nPaths (drawPath rsg step x0 dt)
  let states = transpose paths
      terminal = map (payoff strike) (last states)
  final <- lsmBackward polyT order strike dfs (init (drop 1 states)) terminal
  pure (mean (map (* df0) final))

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
  discFactors <- mapM (\x -> discount ts x False) times
  -- dfs !! i brings a cashflow observed at grid index i+1 back to index i.
  let dfs = zipWith (flip (/)) discFactors (drop 1 discFactors)
      dt = t / fromIntegral timeSteps
      drift = riskFreeRate - dividend
      dimension = size grid - 1

  -- Check 1: the same normals QuantLib's own path generator consumes, in the same order.
  qlGen <- pathGenerator PseudoRandom bsmProc grid seedPaths dimension False
  qlPath <- next qlGen >>= \s -> asset s 0
  hsRsg <- gaussianRsg PseudoRandom dimension seedPaths
  hsPath <- drawPath hsRsg (evolveGBM drift vol) under dt
  let pathMaxDiff = maximum (0 : zipWith (\a b -> abs (a - b)) qlPath hsPath)

  -- Check 2: an American put off Haskell-evolved Black-Scholes paths.
  gbmLsm <- priceUnder polyT order strike under dt dimension seedPaths nPaths dfs (evolveGBM drift vol)

  -- Check 3: the same loop under the unbound CEV SDE, plus its beta = 1 degenerate case.
  cevLsm <- priceUnder polyT order strike under dt dimension seedPaths nPaths dfs (evolveCEV drift cevSigma cevBeta)
  cevAtBeta1 <- priceUnder polyT order strike under dt dimension seedPaths nPaths dfs (evolveCEV drift vol 1.0)

  americanOpt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Put strike)) (American Nothing maturity False)
  mcAmericanEngine PseudoRandom Statistics bsmProc (Just timeSteps) Nothing True False
      (Just (fromIntegral nPaths)) Nothing Nothing seedPaths order polyT (Just (fromIntegral nPaths)) Nothing Nothing
    >>= setPricingEngine americanOpt
  mcP <- npv americanOpt

  pure Result
    { gbmPathMaxDiffR = pathMaxDiff
    , gbmLsmPriceR = gbmLsm
    , mcPriceR = mcP
    , cevLsmPriceR = cevLsm
    , cevAtBeta1PriceR = cevAtBeta1
    }
  where
    evalDate = 15 `may` 1998
    settl = 17 `may` 1998
    under = 36
    strike = 40
    dividend = 0.0
    riskFreeRate = 0.06
    vol = 0.20
    -- CEV's sigma is not a volatility: with S^beta in place of S it carries units of S^(1-beta),
    -- so it is scaled to match the lognormal instantaneous vol at the initial spot.
    cevBeta = 0.7
    cevSigma = vol * under ** (1 - cevBeta)
    maturity = 17 `may` 1999
    timeSteps = 50 :: Word
    order = 2 :: Word
    polyT = Monomial
    nPaths = 8192 :: Int
    seedPaths = 42 :: Word

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
