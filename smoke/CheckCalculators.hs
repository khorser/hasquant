-- Smoke test: BlackCalculator (incl. the newly-added strikeGamma/vanna/volga) and the newly
-- bound BachelierCalculator.
--
-- Neither class had a test/smoke script before this. Rather than hand-deriving reference
-- numbers, this leans on invariants that hold for *any* correct implementation of either
-- formula (both Black-76 and Bachelier share this shape: value = discount*(forward*alpha +
-- x*beta), with alpha/beta's *derivatives* w.r.t. forward/strike/stdDev independent of
-- Call-vs-Put, only alpha_/beta_ themselves differing):
--   1. blackCalculator'/bachelierCalculator' (enum+strike ctor) and blackCalculator/
--      bachelierCalculator (payoff ctor) agree, for the same inputs.
--   2. value/deltaForward satisfy put-call parity exactly:
--        value(Call) - value(Put) = discount*(forward-strike)
--        deltaForward(Call) - deltaForward(Put) = discount
--   3. gammaForward/vega/strikeGamma (and Bachelier's vanna/volga, which take no spot) are
--      IDENTICAL between Call and Put at the same strike/forward/stdDev/discount -- a direct
--      consequence of alpha/beta's derivatives being type-independent. This is what actually
--      exercises strikeGamma/vanna/volga (BlackCalculator's newest bindings) without
--      reimplementing their formulas.
--   4. value matches the already-bound, independently-implemented blackFormula/
--      bachelierBlackFormula free functions exactly (same underlying C++ formula, different
--      call path).
--   5. BlackCalculator's vanna(spot,maturity) == -d2/(spot*stdDev)*vega(maturity), and
--      volga(maturity) == vega(maturity)*d1*d2/stdDev, computing d1/d2 directly -- this is
--      cbits' own documented formula (see blackcalculator.cpp), so it pins the implementation
--      rather than just re-deriving it.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckCalculators.hs -o /tmp/checkcalc -outputdir /tmp/checkcalc_build && /tmp/checkcalc
import Control.Monad(forM_)
import Text.Printf(printf)
import QuantLib.Instrument(OptionType(..))
import QuantLib.Instrument.Option(StrikedPayoff(..), PlainVanillaPayoff(..))
import QuantLib.PricingEngine

import SmokeCheck (checkClose, checkEq)

strike, forward, stdDev, discount :: Double
strike = 100.0
forward = 105.0
stdDev = 0.25
discount = 0.97

spot, maturity :: Double
spot = 103.0
maturity = 2.0

normalPdf :: Double -> Double
normalPdf x = exp (-x * x / 2) / sqrt (2 * pi)

main :: IO ()
main = do
  -- BlackCalculator
  callBC <- blackCalculator' Call strike forward stdDev discount
  putBC <- blackCalculator' Put strike forward stdDev discount
  callBC2 <- blackCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) forward stdDev discount
  putBC2 <- blackCalculator (PlainVanilla (PlainVanillaPayoff Put strike)) forward stdDev discount

  callVal <- value callBC
  callVal2 <- value callBC2
  checkEq "BlackCalculator call: enum ctor == payoff ctor (value)" callVal callVal2
  putVal <- value putBC
  putVal2 <- value putBC2
  checkEq "BlackCalculator put: enum ctor == payoff ctor (value)" putVal putVal2

  checkClose "BlackCalculator put-call parity (value)" (callVal - putVal) (discount * (forward - strike)) 1e-10

  callDF <- deltaForward callBC
  putDF <- deltaForward putBC
  checkClose "BlackCalculator put-call parity (deltaForward)" (callDF - putDF) discount 1e-10

  forM_ [("gammaForward", gammaForward), ("vega", (`vega` maturity)), ("strikeGamma", strikeGamma)] $
    \(name, f) -> do
      c <- f callBC
      p <- f putBC
      checkEq ("BlackCalculator Call/Put agree on " ++ name) c p

  refCallVal <- blackFormula Call strike forward stdDev discount 0.0
  checkClose "BlackCalculator value matches blackFormula (Call)" callVal refCallVal 1e-12
  refPutVal <- blackFormula Put strike forward stdDev discount 0.0
  checkClose "BlackCalculator value matches blackFormula (Put)" putVal refPutVal 1e-12

  let d1 = log (forward / strike) / stdDev + 0.5 * stdDev
      d2 = d1 - stdDev
  callVega <- vega callBC maturity
  callVanna <- vanna callBC spot maturity
  checkClose "BlackCalculator vanna matches -d2/(spot*stdDev)*vega"
    callVanna (-d2 / (spot * stdDev) * callVega) 1e-10
  callVolga <- volga callBC maturity
  checkClose "BlackCalculator volga matches vega*d1*d2/stdDev"
    callVolga (callVega * d1 * d2 / stdDev) 1e-10

  putStrLn "BlackCalculator: OK, ctors agree, put-call parity holds, Call/Put share second-order\
    \ greeks, value matches blackFormula, vanna/volga match their closed forms"

  -- BlackScholesCalculator: a real subclass (unlike Bachelier), so its GenBlackCalculator-typed
  -- methods (value, deltaForward, rho, dividendRho, strikeSensitivity, strikeGamma, vanna, vega,
  -- volga, alpha, beta, itm*Probability -- i.e. everything BlackCalculator has that
  -- BlackScholesCalculator does *not* override) should already work on it directly through the
  -- Upcastable/GenBlackCalculator polymorphism, with no dedicated bindings needed; only the five
  -- no-spot-argument overrides (delta/elasticity/gamma/theta/thetaPerDay) need their own
  -- functions, and those are already bound (blackScholes*). Pick spot/growth so the internal
  -- forward this constructs (spot*growth/discount) matches `forward` above exactly, so its
  -- inherited-method results should equal callBC's/putBC's bit-for-bit.
  let growth = 1.0
      spot = forward * discount / growth
  callBSC <- blackScholesCalculator' Call strike spot growth stdDev discount
  callBSC2 <- blackScholesCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) spot growth stdDev discount
  callBSCVal <- value callBSC
  callBSCVal2 <- value callBSC2
  checkEq "BlackScholesCalculator: enum ctor == payoff ctor (value)" callBSCVal callBSCVal2
  checkEq "BlackScholesCalculator value == equivalent BlackCalculator value (inherited method)" callBSCVal callVal

  -- forM_ over a [(String, f)] list would force `f` to one monomorphic instantiation of
  -- GenBlackCalculator's type variable, which can't cover both callBSC and callBC in the same
  -- list -- so these are individual calls rather than a loop.
  let checkInherited name fBSC fBC = do
        fromBSC <- fBSC callBSC
        fromBC <- fBC callBC
        checkEq ("BlackScholesCalculator inherits " ++ name ++ " from BlackCalculator unchanged") fromBSC fromBC
  checkInherited "deltaForward" deltaForward deltaForward
  checkInherited "rho" (`rho` maturity) (`rho` maturity)
  checkInherited "dividendRho" (`dividendRho` maturity) (`dividendRho` maturity)
  checkInherited "strikeSensitivity" strikeSensitivity strikeSensitivity
  checkInherited "strikeGamma" strikeGamma strikeGamma
  checkInherited "vega" (`vega` maturity) (`vega` maturity)
  checkInherited "volga" (`volga` maturity) (`volga` maturity)
  checkInherited "itmAssetProbability" itmAssetProbability itmAssetProbability
  checkInherited "itmCashProbability" itmCashProbability itmCashProbability
  checkInherited "alpha" alpha alpha
  checkInherited "beta" beta beta

  bscVanna <- vanna callBSC spot maturity
  bcVannaAtBscSpot <- vanna callBC spot maturity
  checkEq "BlackScholesCalculator inherits vanna(spot,maturity) from BlackCalculator unchanged" bscVanna bcVannaAtBscSpot

  bscDelta <- blackScholesDelta callBSC
  bcDeltaAtSpot <- blackDelta callBC spot
  checkEq "BlackScholesCalculator's own delta() == BlackCalculator's delta(spot) at its stored spot" bscDelta bcDeltaAtSpot
  bscElasticity <- blackScholesElasticity callBSC
  bcElasticityAtSpot <- blackElasticity callBC spot
  checkEq "BlackScholesCalculator's own elasticity() == BlackCalculator's elasticity(spot)" bscElasticity bcElasticityAtSpot
  bscGamma <- blackScholesGamma callBSC
  bcGammaAtSpot <- blackGamma callBC spot
  checkEq "BlackScholesCalculator's own gamma() == BlackCalculator's gamma(spot)" bscGamma bcGammaAtSpot
  bscTheta <- blackScholesTheta callBSC maturity
  bcThetaAtSpot <- blackTheta callBC spot maturity
  checkEq "BlackScholesCalculator's own theta(maturity) == BlackCalculator's theta(spot,maturity)" bscTheta bcThetaAtSpot
  bscThetaPerDay <- blackScholesThetaPerDay callBSC maturity
  bcThetaPerDayAtSpot <- blackThetaPerDay callBC spot maturity
  checkEq "BlackScholesCalculator's own thetaPerDay(maturity) == BlackCalculator's thetaPerDay(spot,maturity)"
    bscThetaPerDay bcThetaPerDayAtSpot

  putStrLn "BlackScholesCalculator: OK, ctors agree, inherited GenBlackCalculator methods (incl.\
    \ the new strikeGamma/vanna/volga) match the equivalent BlackCalculator exactly, and its five\
    \ own no-spot overrides match BlackCalculator's spot-taking versions at its stored spot"

  -- BachelierCalculator. Its stdDev is an *absolute* normal-model volatility (e.g. rate points),
  -- not a Black-style relative one -- reusing `stdDev` (0.25) here against forward-strike=5.0
  -- pushes d=(F-K)/stdDev to 20, deep in the tail where n(d)~0 and every second-order/vega-family
  -- greek is a degenerate ~1e-87, which passes every check without actually exercising the
  -- formula. Use a stdDev of realistic magnitude for the forward/strike spread instead.
  let bachelierStdDev = 8.0
  callNC <- bachelierCalculator' Call strike forward bachelierStdDev discount
  putNC <- bachelierCalculator' Put strike forward bachelierStdDev discount
  callNC2 <- bachelierCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) forward bachelierStdDev discount
  putNC2 <- bachelierCalculator (PlainVanilla (PlainVanillaPayoff Put strike)) forward bachelierStdDev discount

  callNVal <- bachelierValue callNC
  callNVal2 <- bachelierValue callNC2
  checkEq "BachelierCalculator call: enum ctor == payoff ctor (value)" callNVal callNVal2
  putNVal <- bachelierValue putNC
  putNVal2 <- bachelierValue putNC2
  checkEq "BachelierCalculator put: enum ctor == payoff ctor (value)" putNVal putNVal2

  checkClose "BachelierCalculator put-call parity (value)" (callNVal - putNVal) (discount * (forward - strike)) 1e-10

  callNDF <- bachelierDeltaForward callNC
  putNDF <- bachelierDeltaForward putNC
  checkClose "BachelierCalculator put-call parity (deltaForward)" (callNDF - putNDF) discount 1e-10

  forM_ [ ("gammaForward", bachelierGammaForward), ("vega", (`bachelierVega` maturity))
        , ("strikeGamma", bachelierStrikeGamma), ("vanna", (`bachelierVanna` maturity))
        , ("volga", (`bachelierVolga` maturity))
        ] $ \(name, f) -> do
    c <- f callNC
    p <- f putNC
    checkEq ("BachelierCalculator Call/Put agree on " ++ name) c p

  refCallNVal <- bachelierBlackFormula Call strike forward bachelierStdDev discount
  checkClose "BachelierCalculator value matches bachelierBlackFormula (Call)" callNVal refCallNVal 1e-12
  refPutNVal <- bachelierBlackFormula Put strike forward bachelierStdDev discount
  checkClose "BachelierCalculator value matches bachelierBlackFormula (Put)" putNVal refPutNVal 1e-12

  let d = (forward - strike) / bachelierStdDev
      nd = normalPdf d
  callNVega <- bachelierVega callNC maturity
  callNVanna <- bachelierVanna callNC maturity
  checkClose "BachelierCalculator vanna matches -d*n(d)*sqrt(maturity)/stdDev"
    callNVanna (-d * nd * sqrt maturity / bachelierStdDev) 1e-9
  callNVolga <- bachelierVolga callNC maturity
  checkClose "BachelierCalculator volga matches (d*d/stdDev)*vega"
    callNVolga (d * d / bachelierStdDev * callNVega) 1e-9
  checkClose "BachelierCalculator vega matches discount*sqrt(maturity)*n(d)"
    callNVega (discount * sqrt maturity * nd) 1e-9

  printf "BlackCalculator value=%.6f BachelierCalculator value=%.6f (different models, same inputs)\n"
    callVal callNVal
  putStrLn "BachelierCalculator: OK, ctors agree, put-call parity holds, Call/Put share second-order\
    \ greeks, value matches bachelierBlackFormula, vanna/volga/vega match their closed forms"
