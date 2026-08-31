-- |Ported from QuantLib's @Examples/DiscreteHedging/DiscreteHedging.cpp@ (Derman & Kamal,
-- \"When You Cannot Hedge Continuously: The Corrections to Black-Scholes\"): a hedger sells a
-- European option at its Black-Scholes premium, then rehedges at @hedgesNum@ evenly spaced
-- dates using the Black-Scholes delta, and we look at the final profit\/loss of that strategy
-- across many simulated stock paths. Continuous rehedging would zero the P&L on every path;
-- discrete rehedging leaves a replication error whose standard deviation should shrink as the
-- number of hedges grows -- the qualitative point this module checks (upstream's own @main@ only
-- prints the numbers, it has no assertions of its own to port).
--
-- Two deliberate deviations from upstream, both already established elsewhere in this test suite
-- (see CLAUDE.md): upstream's own @PseudoRandom::make_sequence_generator(nTimeSteps, 0)@ seeds
-- from entropy (seed 0 has that special meaning for 'QuantLib.Method.pathGenerator''s underlying
-- Mersenne Twister), so a fixed nonzero seed is used here instead to make the result
-- reproducible; and the sample count is reduced from upstream's 50000 to keep a two-hedging-
-- frequency hspec run fast.
module QuantLib.Example.DiscreteHedging
  (
    Result(..)
  , run
  ) where
import Control.Monad(replicateM)
import qualified Data.Vector.Storable as V

import QuantLib.Instrument.Option(OptionType(Call))
import QuantLib.Math(RngTrait(PseudoRandom), timeGrid)
import QuantLib.Method(pathGenerator, next, asset)
import QuantLib.Process(blackScholesMertonProcess, ProcessDiscretization(EulerDiscretization))
import QuantLib.PricingEngine(blackCalculator', value, blackDelta)
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Time.Date(today)
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(Actual365FixedStandard), Frequency(Annual))
import QuantLib.InterestRate(Compounding(Continuous))
import QuantLib.TermStructure.Volatility(blackConstantVol)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Time.Calendar(calendar, CalendarConstructor(TARGET))

data Result = Result
  { optionValue :: !Double        -- ^Black-Scholes premium at t=0
  , plMean21 :: !Double           -- ^mean final P&L, 21 rehedging dates
  , plStdDev21 :: !Double         -- ^std. dev. of final P&L, 21 rehedging dates
  , plMean84 :: !Double           -- ^mean final P&L, 84 rehedging dates
  , plStdDev84 :: !Double         -- ^std. dev. of final P&L, 84 rehedging dates
  }

mean :: [Double] -> Double
mean xs = sum xs / fromIntegral (length xs)

stdDev :: [Double] -> Double
stdDev xs = sqrt (mean [(x - m) * (x - m) | x <- xs]) where m = mean xs

run :: IO Result
run = do
  evalDate <- today
  setEvaluationDate (Just evalDate)
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar TARGET
  s0Q <- simpleQuote s0
  rQ <- simpleQuote r
  divQ <- simpleQuote 0.0
  sigmaQ <- simpleQuote sigma
  riskFreeTS <- flatForward evalDate rQ dc Continuous Annual
  dividendTS <- flatForward evalDate divQ dc Continuous Annual
  volTS <- blackConstantVol evalDate cal sigmaQ dc
  process <- blackScholesMertonProcess s0Q dividendTS riskFreeTS volTS EulerDiscretization False

  black0 <- blackCalculator' Call strike (s0 * exp (r * maturity)) (sqrt (sigma * sigma * maturity)) (exp (- r * maturity))
  optValue <- value black0

  (mean21, sd21) <- compute process 21 nSamples
  (mean84, sd84) <- compute process 84 nSamples

  return Result
    { optionValue = optValue
    , plMean21 = mean21, plStdDev21 = sd21
    , plMean84 = mean84, plStdDev84 = sd84
    }
  where
    maturity = 1.0 / 12.0 -- 1 month
    strike = 100
    s0 = 100
    sigma = 0.20
    r = 0.05
    nSamples = 3000 :: Int
    seed = 42 :: Word

    -- one path's replication P&L, following ReplicationPathPricer::operator() exactly: an
    -- initial deal (sell the option, delta-hedge), n-1 rehedges at each interior path point,
    -- then unwind against the option's payoff at the final point
    plOfPath :: [Double] -> IO Double
    plOfPath [] = error "plOfPath: empty path"
    plOfPath path@(s00 : _) = do
      let n = length path - 1
          dt = maturity / fromIntegral n
      black00 <- blackCalculator' Call strike s00 (sqrt (sigma * sigma * maturity)) (exp (- r * maturity))
      premium <- value black00
      delta0 <- blackDelta black00 s00
      (moneyAcct, stockAmount) <- rehedge dt (premium - delta0 * s00) delta0 0.0 (take (n - 1) (drop 1 path))
      let finalStock = path !! n
          optionPayoff = max (finalStock - strike) 0
      return (moneyAcct * exp (r * dt) - optionPayoff + stockAmount * finalStock)
      where
        rehedge _dt moneyAcct stockAmount _t [] = return (moneyAcct, stockAmount)
        rehedge dt moneyAcct stockAmount t (stock : rest) = do
          let t' = t + dt
              moneyAcct1 = moneyAcct * exp (r * dt)
              timeToMaturity = maturity - t'
          black <- blackCalculator' Call strike stock (sqrt (sigma * sigma * timeToMaturity)) (exp (- r * timeToMaturity))
          delta <- blackDelta black stock
          rehedge dt (moneyAcct1 - (delta - stockAmount) * stock) delta t' rest

    compute process' nTimeSteps n = do
      tg <- timeGrid maturity nTimeSteps
      pg <- pathGenerator PseudoRandom process' tg seed nTimeSteps False
      paths <- replicateM n (V.toList <$> (next pg >>= \sp -> asset sp 0))
      pls <- mapM plOfPath paths
      return (mean pls, stdDev pls)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
