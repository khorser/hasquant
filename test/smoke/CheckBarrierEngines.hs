-- Smoke test: construct BlackDeltaCalculator/DeltaVolQuote and every new
-- barrier/double-barrier pricing engine added alongside them, and check
-- outputs against real cached values from QuantLib's own test-suite
-- (test-suite/blackdeltacalculator.cpp, barrieroption.cpp,
-- doublebarrieroption.cpp) rather than only self-consistency. Also guards
-- against enum-aliasing (DeltaType/AtmType/BinomialTree/RngTrait) and
-- against the binomial-tree switch tables (qlBinomialBarrierEngineAux,
-- qlBinomialDoubleBarrierEngineAux) being incomplete/mis-ordered, per the
-- CPIInterpolationType gotcha noted in CLAUDE.md.
--
-- c2hs only derives Show/Eq for these enums (no Bounded), so the
-- BinomialTree/RngTrait case lists below are spelled out explicitly rather
-- than via [minBound .. maxBound] (see smoke/CheckInflation.hs).
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckBarrierEngines.hs -o /tmp/checkbarrier -outputdir /tmp/checkbarrier_build && /tmp/checkbarrier
-- (-ismoke puts smoke/SmokeCheck.hs, the shared assertion helpers, on the search path)
import Control.Monad
import Data.Time.Calendar (addDays)
import Text.Printf (printf)

import SmokeCheck (checkClose)

import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.Math
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield

allTrees :: [BinomialTree]
allTrees =
  [ JarrowRudd, CoxRossRubinstein, AdditiveEQPBinomialTree, Trigeorgis, Tian
  , LeisenReimer, Joshi4, ExtendedJarrowRudd, ExtendedCoxRossRubinstein
  , ExtendedAdditiveEQPBinomialTree, ExtendedTrigeorgis, ExtendedTian
  , ExtendedLeisenReimer, ExtendedJoshi4
  ]

main :: IO ()
main = do
  checkBlackDeltaCalculator
  checkVannaVolgaBarrierEngine
  checkAnalyticDoubleBarrierEngine
  checkOtherEngines
  checkPartialTimeBarrierOptionEngine

-- Cached (optionType, deltaType, spot, dDf, fDf, stdDev, strike, expectedDelta)
-- rows from test-suite/blackdeltacalculator.cpp's testDeltaValues -- one per
-- DeltaType, so a DeltaType enum-aliasing bug (wrong C value <-> case) shows
-- up as a wrong number here, not just "it compiled".
checkBlackDeltaCalculator :: IO ()
checkBlackDeltaCalculator = do
  checkOne "BlackDeltaCalculator Spot"   Call Spot   1.421 0.997306 0.992266 0.1180654 1.608080 0.15
  checkOne "BlackDeltaCalculator PaSpot" Call PaSpot 1.421 0.997306 0.992266 0.1180654 1.600545 0.15
  checkOne "BlackDeltaCalculator Fwd"    Call Fwd    1.421 0.997306 0.992266 0.1180654 1.609029 0.15
  checkOne "BlackDeltaCalculator PaFwd"  Call PaFwd  1.421 0.997306 0.992266 0.1180654 1.601550 0.15

  -- AtmType enum-aliasing guard: AtmSpot/AtmFwd/AtmDeltaNeutral are genuinely
  -- different formulas and must give different strikes for this input.
  -- (AtmVegaMax/AtmGammaMax legitimately coincide with AtmDeltaNeutral under
  -- Black-Scholes with a single stdDev -- that's not an aliasing bug, so they
  -- aren't required to differ here.) AtmPutCall50 needs a Fwd-delta
  -- calculator (QuantLib throws otherwise), so it's checked separately.
  calc <- blackDeltaCalculator Call Spot 1.30265 0.99979 0.98508 0.11638
  strikes <- forM [AtmSpot, AtmFwd, AtmDeltaNeutral, AtmVegaMax, AtmGammaMax] $ \ty -> do
    s <- atmStrike calc ty
    printf "     atmStrike %-16s -> %.6f\n" (show ty) s
    pure (ty, s)
  let coreStrikes = [s | (ty, s) <- strikes, ty `elem` [AtmSpot, AtmFwd, AtmDeltaNeutral]]
  when (length (dedup coreStrikes) < 3) $
    error "BlackDeltaCalculator: AtmSpot/AtmFwd/AtmDeltaNeutral produced identical strikes -- suspect enum aliasing"

  fwdCalc <- blackDeltaCalculator Call Fwd 1.30265 0.99979 0.98508 0.11638
  fwdStrike <- atmStrike fwdCalc AtmFwd
  putCall50Strike <- atmStrike fwdCalc AtmPutCall50
  printf "     atmStrike %-16s -> %.6f\n" (show AtmPutCall50) putCall50Strike
  when (abs (fwdStrike - putCall50Strike) < 1.0e-6) $
    error "BlackDeltaCalculator: AtmFwd/AtmPutCall50 produced identical strikes -- suspect enum aliasing"
  where
    checkOne label ot dt spot dDf fDf stdDev strike expected = do
      calc <- blackDeltaCalculator ot dt spot dDf fDf stdDev
      delta <- deltaFromStrike calc strike
      checkClose label expected delta 1.0e-3
    dedup [] = []
    dedup (x:xs) = x : dedup (filter (\y -> abs (y - x) > 1.0e-6) xs)

-- Reproduces the first row of test-suite/barrieroption.cpp's
-- testVannaVolgaSimpleBarrierValues: an UpOut EUR call priced with the
-- vanna-volga smile-adjusted barrier engine.
checkVannaVolgaBarrierEngine :: IO ()
checkVannaVolgaBarrierEngine = do
  setEvaluationDate (Just today)
  dc <- dayCounter Actual365FixedStandard
  spotQ <- simpleQuote s
  qQ <- simpleQuote q
  rQ <- simpleQuote r
  qTS <- flatForward today qQ dc Continuous Annual
  rTS <- flatForward today rQ dc Continuous Annual
  vol25PutQ <- simpleQuote vol25Put
  volAtmQ <- simpleQuote volAtm
  vol25CallQ <- simpleQuote vol25Call

  qDisc <- discount qTS t False
  rDisc <- discount rTS t False
  let forward = s * qDisc / rDisc
  bsVanillaPrice <- blackFormula Call strike forward (vol * sqrt t) rDisc 0.0

  volAtmQuote <- atmVolQuote volAtmQ Fwd t AtmDeltaNeutral
  vol25PutQuote <- deltaVolQuote (-0.25) vol25PutQ t Fwd
  vol25CallQuote <- deltaVolQuote 0.25 vol25CallQ t Fwd

  let payoff = PlainVanilla (PlainVanillaPayoff Call strike)
      exercise = European (EuropeanExercise (addDays (round (t * 365)) today))
  opt <- barrierOption UpOut barrier 0 payoff exercise
  optInst <- asOneAssetOption opt
  engine <- vannaVolgaBarrierEngine volAtmQuote vol25PutQuote vol25CallQuote spotQ rTS qTS True bsVanillaPrice
  setPricingEngine optInst engine
  price <- npv optInst
  checkClose "VannaVolgaBarrierEngine (UpOut call)" 0.148127 price 2.0e-3
  where
    today = 5 `march` 2013
    barrier = 1.5
    strike = 1.13321
    s = 1.30265
    q = 0.0003541
    r = 0.0033871
    t = 1
    vol25Put = 0.10087
    volAtm = 0.08925
    vol25Call = 0.08463
    vol = 0.11638

-- Reproduces the first row of test-suite/doublebarrieroption.cpp's
-- testEuropeanHaugValues: a KnockOut double-barrier European call priced
-- with the Ikeda/Kunitomo analytic engine.
checkAnalyticDoubleBarrierEngine :: IO ()
checkAnalyticDoubleBarrierEngine = do
  setEvaluationDate (Just today)
  dc <- dayCounter (Actual360 False)
  spotQ <- simpleQuote s
  qQ <- simpleQuote q
  rQ <- simpleQuote r
  volQ <- simpleQuote vol
  qTS <- flatForward today qQ dc Continuous Annual
  rTS <- flatForward today rQ dc Continuous Annual
  tgt <- calendar TARGET
  volTS <- blackConstantVol today tgt volQ dc
  proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

  let payoff = PlainVanilla (PlainVanillaPayoff Call strike)
      exercise = European (EuropeanExercise (addDays (round (t * 360)) today))
  opt <- doubleBarrierOption KnockOut barrierLo barrierHi 0 payoff exercise
  optInst <- asOneAssetOption opt
  engine <- analyticDoubleBarrierEngine proc 5
  setPricingEngine optInst engine
  price <- npv optInst
  checkClose "AnalyticDoubleBarrierEngine (KnockOut call)" 4.3515 price 1.0e-3
  where
    today = 1 `january` 2020
    barrierLo = 50.0
    barrierHi = 150.0
    strike = 100.0
    s = 100.0
    q = 0.0
    r = 0.1
    t = 0.25
    vol = 0.15

-- Construct every remaining new engine at least once (AnalyticBinaryBarrierEngine,
-- FdBlackScholesBarrierEngine, BinomialBarrierEngine over every BinomialTree case,
-- VannaVolgaDoubleBarrierEngine, BinomialDoubleBarrierEngine over every
-- BinomialTree case, MCDoubleBarrierEngine over every RngTrait case) and price
-- with it, so a stale/incomplete Aux switch table or missing include shows up
-- as a runtime failure here rather than only surfacing much later.
checkOtherEngines :: IO ()
checkOtherEngines = do
  setEvaluationDate (Just today)
  dc <- dayCounter Actual365FixedStandard
  spotQ <- simpleQuote 100
  qQ <- simpleQuote 0.01
  rQ <- simpleQuote 0.02
  volQ <- simpleQuote 0.2
  qTS <- flatForward today qQ dc Continuous Annual
  rTS <- flatForward today rQ dc Continuous Annual
  tgt <- calendar TARGET
  volTS <- blackConstantVol today tgt volQ dc
  proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

  let payoff = PlainVanilla (PlainVanillaPayoff Call 100)
      exercise = European (EuropeanExercise (addDays 180 today))
      -- AnalyticBinaryBarrierEngine only supports American-exercise binary
      -- (cash-or-nothing/asset-or-nothing) payoffs, unlike every other engine
      -- checked here.
      binaryPayoff = CashOrNothing Call 100 10
      americanExercise = American Nothing (addDays 180 today) True

  binOpt <- barrierOption UpOut 130 0 binaryPayoff americanExercise >>= asOneAssetOption
  analyticBinaryBarrierEngine proc >>= setPricingEngine binOpt
  npv binOpt >>= printf "     AnalyticBinaryBarrierEngine        -> %.6f\n"

  barOpt <- barrierOption UpOut 130 0 payoff exercise >>= asOneAssetOption
  fdBlackScholesBarrierEngine proc 100 100 0 Douglas False 0.0 >>= setPricingEngine barOpt
  npv barOpt >>= printf "     FdBlackScholesBarrierEngine        -> %.6f\n"

  forM_ allTrees $ \ty -> do
    barOpt' <- barrierOption UpOut 130 0 payoff exercise >>= asOneAssetOption
    binomialBarrierEngine ty proc 200 0 >>= setPricingEngine barOpt'
    npv barOpt' >>= printf "     BinomialBarrierEngine %-24s -> %.6f\n" (show ty)

  dblOpt <- doubleBarrierOption KnockOut 70 130 0 payoff exercise >>= asOneAssetOption
  let dblT = 180 / 365 :: Double
  qDisc <- discount qTS dblT False
  rDisc <- discount rTS dblT False
  bsVanillaPrice <- blackFormula Call 100 (100 * qDisc / rDisc) (0.2 * sqrt dblT) rDisc 0.0
  volAtmQ <- simpleQuote 0.2
  vol25PutQ <- simpleQuote 0.22
  vol25CallQ <- simpleQuote 0.18
  volAtmQuote <- atmVolQuote volAtmQ Fwd dblT AtmDeltaNeutral
  vol25PutQuote <- deltaVolQuote (-0.25) vol25PutQ dblT Fwd
  vol25CallQuote <- deltaVolQuote 0.25 vol25CallQ dblT Fwd
  vannaVolgaDoubleBarrierEngine volAtmQuote vol25PutQuote vol25CallQuote spotQ rTS qTS True bsVanillaPrice 5 >>= setPricingEngine dblOpt
  npv dblOpt >>= printf "     VannaVolgaDoubleBarrierEngine      -> %.6f\n"

  forM_ allTrees $ \ty -> do
    dblOpt' <- doubleBarrierOption KnockOut 70 130 0 payoff exercise >>= asOneAssetOption
    binomialDoubleBarrierEngine ty proc 200 >>= setPricingEngine dblOpt'
    npv dblOpt' >>= printf "     BinomialDoubleBarrierEngine %-18s -> %.6f\n" (show ty)

  forM_ [PseudoRandom, LowDiscrepancy] $ \rng -> do
    dblOpt' <- doubleBarrierOption KnockOut 70 130 0 payoff exercise >>= asOneAssetOption
    mcDoubleBarrierEngine rng Statistics proc (Just 20) Nothing False False (Just 1024) Nothing Nothing 42 >>= setPricingEngine dblOpt'
    npv dblOpt' >>= printf "     MCDoubleBarrierEngine %-24s -> %.6f\n" (show rng)
  where
    today = 1 `january` 2020

-- Reproduces the first row ({95, 90, 1, 0.0393}, DownOut/EndB1) of
-- test-suite/partialtimebarrieroption.cpp's testAnalyticEngine. Exercises the
-- non-consecutive PartialBarrierRange enum wiring (EndB1 = 2, not 1 -- see
-- CLAUDE.md's CPIInterpolationType gotcha) and the Date-typed
-- coverEventDate argument end-to-end. partialTimeBarrierOption returns
-- OneAssetOption directly (no dedicated leaf type, unlike barrierOption), so
-- unlike the checks above there's no asOneAssetOption upcast here.
checkPartialTimeBarrierOptionEngine :: IO ()
checkPartialTimeBarrierOptionEngine = do
  setEvaluationDate (Just today)
  dc <- dayCounter (Actual360 False)
  spotQ <- simpleQuote s
  qQ <- simpleQuote q
  rQ <- simpleQuote r
  volQ <- simpleQuote vol
  qTS <- flatForward today qQ dc Continuous Annual
  rTS <- flatForward today rQ dc Continuous Annual
  tgt <- calendar TARGET
  volTS <- blackConstantVol today tgt volQ dc
  proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

  let payoff = PlainVanilla (PlainVanillaPayoff Call strike)
      exercise = European (EuropeanExercise (addDays 360 today))
      coverEventDate = addDays 1 today
  opt <- partialTimeBarrierOption DownOut EndB1 barrier rebate coverEventDate payoff exercise
  engine <- analyticPartialTimeBarrierOptionEngine proc
  setPricingEngine opt engine
  price <- npv opt
  checkClose "AnalyticPartialTimeBarrierOptionEngine (DownOut/EndB1)" 0.0393 price 1.0e-4
  where
    today = 1 `january` 2020
    barrier = 100.0
    rebate = 0.0
    strike = 90.0
    s = 95.0
    q = 0.0
    r = 0.1
    vol = 0.25
