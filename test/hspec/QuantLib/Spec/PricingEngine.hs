-- | Coverage for 'QuantLib.PricingEngine' entry points ported from proven-correct
-- @test/smoke/*.hs@ scripts that were never wired into @stack test --coverage@ (see
-- CLAUDE.md: coverage is only measured over @test\/hspec\/**@ + @test\/example\/**@).
-- Each block below preserves the source smoke script's own reasoning in its header
-- comment; only the assertion style changed (SmokeCheck's checkClose/checkEq/checkWith,
-- which 'error' on failure, become hspec 'shouldSatisfy'/'shouldBe').
module QuantLib.Spec.PricingEngine (spec) where

import Control.Monad(forM, forM_)
import Data.Time.Calendar(addDays)

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..), TimeUnit(..))
import QuantLib.InterestRate(Compounding(..), VolatilityType(..))
import QuantLib.Quote hiding(value)
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Instrument
import QuantLib.Instrument.Option hiding(deltaForward, vega, rho, dividendRho, strikeSensitivity, itmCashProbability)
import QuantLib.Instrument.Swap(varianceSwap)
import QuantLib.Process hiding(blackScholesTheta)
import QuantLib.Math(RngTrait(..), StatisticsTrait(..), PolynomialType(..), BinomialTree(..), FdmScheme(..))
import QuantLib.PricingEngine

import QuantLib.Spec.Helpers(closePrec)

normalPdf :: Double -> Double
normalPdf x = exp (-x * x / 2) / sqrt (2 * pi)

allFinite :: [Double] -> Bool
allFinite = all (\v -> not (isNaN v) && not (isInfinite v))

allTrees :: [BinomialTree]
allTrees =
  [ JarrowRudd, CoxRossRubinstein, AdditiveEQPBinomialTree, Trigeorgis, Tian
  , LeisenReimer, Joshi4, ExtendedJarrowRudd, ExtendedCoxRossRubinstein
  , ExtendedAdditiveEQPBinomialTree, ExtendedTrigeorgis, ExtendedTian
  , ExtendedLeisenReimer, ExtendedJoshi4
  ]

spec :: Spec
spec = do
  -- Ported from test/smoke/CheckCalculators.hs. Leans on invariants that hold for *any*
  -- correct implementation of the Black-76/Bachelier formula (value = discount*(forward*alpha
  -- + x*beta), with alpha/beta's *derivatives* independent of Call-vs-Put) rather than
  -- hand-derived reference numbers: ctor-pair agreement, put-call parity, Call/Put agreement
  -- on second-order greeks, agreement with the independently-implemented blackFormula/
  -- bachelierBlackFormula free functions, and closed-form vanna/volga checks from
  -- blackcalculator.cpp's own documented formula.
  describe "BlackCalculator / BlackScholesCalculator / BachelierCalculator" $ do
    let strike = 100.0; forward = 105.0; stdDev = 0.25; discount = 0.97
        spot = 103.0; maturity = 2.0

    it "BlackCalculator: ctors agree, put-call parity holds, Call/Put share second-order greeks,\
       \ value matches blackFormula, vanna/volga match their closed forms" $ do
      callBC <- blackCalculator' Call strike forward stdDev discount
      putBC <- blackCalculator' Put strike forward stdDev discount
      callBC2 <- blackCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) forward stdDev discount
      putBC2 <- blackCalculator (PlainVanilla (PlainVanillaPayoff Put strike)) forward stdDev discount

      callVal <- value callBC
      callVal2 <- value callBC2
      callVal2 `shouldBe` callVal
      putVal <- value putBC
      putVal2 <- value putBC2
      putVal2 `shouldBe` putVal

      (callVal - putVal) `shouldSatisfy` closePrec (discount * (forward - strike)) 1e-10

      callDF <- deltaForward callBC
      putDF <- deltaForward putBC
      (callDF - putDF) `shouldSatisfy` closePrec discount 1e-10

      forM_ [gammaForward, (`vega` maturity), strikeGamma] $ \f -> do
        c <- f callBC
        p <- f putBC
        p `shouldBe` c

      refCallVal <- blackFormula Call strike forward stdDev discount 0.0
      callVal `shouldSatisfy` closePrec refCallVal 1e-12
      refPutVal <- blackFormula Put strike forward stdDev discount 0.0
      putVal `shouldSatisfy` closePrec refPutVal 1e-12

      let d1 = log (forward / strike) / stdDev + 0.5 * stdDev
          d2 = d1 - stdDev
      callVega <- vega callBC maturity
      callVanna <- vanna callBC spot maturity
      callVanna `shouldSatisfy` closePrec (-d2 / (spot * stdDev) * callVega) 1e-10
      callVolga <- volga callBC maturity
      callVolga `shouldSatisfy` closePrec (callVega * d1 * d2 / stdDev) 1e-10

    it "BlackScholesCalculator: ctors agree, inherited GenBlackCalculator methods match the\
       \ equivalent BlackCalculator exactly, and its own no-spot overrides match BlackCalculator's\
       \ spot-taking versions at its stored spot" $ do
      callBC <- blackCalculator' Call strike forward stdDev discount
      callVal <- value callBC
      let growth = 1.0
          bscSpot = forward * discount / growth
      callBSC <- blackScholesCalculator' Call strike bscSpot growth stdDev discount
      callBSC2 <- blackScholesCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) bscSpot growth stdDev discount
      callBSCVal <- value callBSC
      callBSCVal2 <- value callBSC2
      callBSCVal2 `shouldBe` callBSCVal
      callBSCVal `shouldBe` callVal

      let checkInherited fBSC fBC = do
            fromBSC <- fBSC callBSC
            fromBC <- fBC callBC
            fromBSC `shouldBe` fromBC
      checkInherited deltaForward deltaForward
      checkInherited (`rho` maturity) (`rho` maturity)
      checkInherited (`dividendRho` maturity) (`dividendRho` maturity)
      checkInherited strikeSensitivity strikeSensitivity
      checkInherited strikeGamma strikeGamma
      checkInherited (`vega` maturity) (`vega` maturity)
      checkInherited (`volga` maturity) (`volga` maturity)
      checkInherited itmAssetProbability itmAssetProbability
      checkInherited itmCashProbability itmCashProbability
      checkInherited alpha alpha
      checkInherited beta beta

      bscVanna <- vanna callBSC bscSpot maturity
      bcVannaAtBscSpot <- vanna callBC bscSpot maturity
      bscVanna `shouldBe` bcVannaAtBscSpot

      bscDelta <- blackScholesDelta callBSC
      bcDeltaAtSpot <- blackDelta callBC bscSpot
      bscDelta `shouldBe` bcDeltaAtSpot
      bscElasticity <- blackScholesElasticity callBSC
      bcElasticityAtSpot <- blackElasticity callBC bscSpot
      bscElasticity `shouldBe` bcElasticityAtSpot
      bscGamma <- blackScholesGamma callBSC
      bcGammaAtSpot <- blackGamma callBC bscSpot
      bscGamma `shouldBe` bcGammaAtSpot
      bscTheta <- blackScholesTheta callBSC maturity
      bcThetaAtSpot <- blackTheta callBC bscSpot maturity
      bscTheta `shouldBe` bcThetaAtSpot
      bscThetaPerDay <- blackScholesThetaPerDay callBSC maturity
      bcThetaPerDayAtSpot <- blackThetaPerDay callBC bscSpot maturity
      bscThetaPerDay `shouldBe` bcThetaPerDayAtSpot

    it "BachelierCalculator: ctors agree, put-call parity holds, Call/Put share second-order\
       \ greeks, value matches bachelierBlackFormula, vanna/volga/vega match their closed forms" $ do
      -- BachelierCalculator's stdDev is an *absolute* normal-model volatility (e.g. rate
      -- points), not a Black-style relative one -- a stdDev of realistic magnitude for the
      -- forward/strike spread is needed or every second-order greek degenerates to ~1e-87
      -- in the tail, passing every check without exercising the formula.
      let bachelierStdDev = 8.0
      callNC <- bachelierCalculator' Call strike forward bachelierStdDev discount
      putNC <- bachelierCalculator' Put strike forward bachelierStdDev discount
      callNC2 <- bachelierCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) forward bachelierStdDev discount
      putNC2 <- bachelierCalculator (PlainVanilla (PlainVanillaPayoff Put strike)) forward bachelierStdDev discount

      callNVal <- bachelierValue callNC
      callNVal2 <- bachelierValue callNC2
      callNVal2 `shouldBe` callNVal
      putNVal <- bachelierValue putNC
      putNVal2 <- bachelierValue putNC2
      putNVal2 `shouldBe` putNVal

      (callNVal - putNVal) `shouldSatisfy` closePrec (discount * (forward - strike)) 1e-10

      callNDF <- bachelierDeltaForward callNC
      putNDF <- bachelierDeltaForward putNC
      (callNDF - putNDF) `shouldSatisfy` closePrec discount 1e-10

      forM_ [ bachelierGammaForward, (`bachelierVega` maturity)
            , bachelierStrikeGamma, (`bachelierVanna` maturity), (`bachelierVolga` maturity)
            ] $ \f -> do
        c <- f callNC
        p <- f putNC
        p `shouldBe` c

      refCallNVal <- bachelierBlackFormula Call strike forward bachelierStdDev discount
      callNVal `shouldSatisfy` closePrec refCallNVal 1e-12
      refPutNVal <- bachelierBlackFormula Put strike forward bachelierStdDev discount
      putNVal `shouldSatisfy` closePrec refPutNVal 1e-12

      let d = (forward - strike) / bachelierStdDev
          nd = normalPdf d
      callNVega <- bachelierVega callNC maturity
      callNVanna <- bachelierVanna callNC maturity
      callNVanna `shouldSatisfy` closePrec (-d * nd * sqrt maturity / bachelierStdDev) 1e-9
      callNVolga <- bachelierVolga callNC maturity
      callNVolga `shouldSatisfy` closePrec (d * d / bachelierStdDev * callNVega) 1e-9
      callNVega `shouldSatisfy` closePrec (discount * sqrt maturity * nd) 1e-9

  -- Ported from test/smoke/CheckSabrSmileSection.hs. volatility(strike)/variance(strike) must
  -- exactly match the already-bound unsafeShiftedSabrVolatility formula (enum-dispatched
  -- through a C-side VolatilityType cast, same class of bug as the CPIInterpolationType
  -- incident); the Date- and Time-based ctors of SabrSmileSection/NoArbSabrSmileSection must
  -- agree with each other and (for NoArb) differ from the plain SABR smile; and
  -- SabrInterpolatedSmileSection must calibrate back to the SABR parameters that generated its
  -- input vols.
  describe "SabrSmileSection / NoArbSabrSmileSection / SabrInterpolatedSmileSection" $ do
    let forward = 0.03; expiry = 5.0; alpha = 0.04; beta = 0.5; nu = 0.4; rho = -0.2; shift = 0.0

    it "matches unsafeShiftedSabrVolatility for both VolatilityType cases, and Normal /= ShiftedLognormal" $
      Settings.keepingSettings' $ do
        forM_ [ShiftedLognormal, Normal] $ \volType -> do
          section <- sabrSmileSection expiry forward alpha beta nu rho shift volType
          forM_ [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
            got <- smileSectionVolatility section strike
            expected <- unsafeShiftedSabrVolatility strike forward expiry alpha beta nu rho shift volType
            got `shouldBe` expected
            var <- smileSectionVariance section strike
            var `shouldSatisfy` closePrec (expected * expected * expiry) 1e-12

        volShiftedLognormal <- sabrSmileSection expiry forward alpha beta nu rho shift ShiftedLognormal
        volAtAtm1 <- smileSectionVolatility volShiftedLognormal forward
        volNormal <- sabrSmileSection expiry forward alpha beta nu rho shift Normal
        volAtAtm2 <- smileSectionVolatility volNormal forward
        volAtAtm1 `shouldNotBe` volAtAtm2

    it "SabrSmileSection'/NoArbSabrSmileSection(') Date- and Time-based ctors agree, and NoArb\
       \ differs from the plain SabrSmileSection" $
      Settings.keepingSettings' $ do
        refDate <- today
        Settings.setEvaluationDate (Just refDate)
        let expiryDays = 1826 :: Int -- ~5y in actual days
            expiryFromDays = fromIntegral expiryDays / 365.0 :: Double
        optionDate <- addPeriod refDate (expiryDays, Days)
        act365 <- dayCounter Actual365FixedStandard

        sectionByTime <- sabrSmileSection expiryFromDays forward alpha beta nu rho shift ShiftedLognormal
        sectionByDate <- sabrSmileSection' optionDate forward alpha beta nu rho (Just refDate) act365 shift ShiftedLognormal
        forM_ [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
          volT <- smileSectionVolatility sectionByTime strike
          volD <- smileSectionVolatility sectionByDate strike
          volD `shouldSatisfy` closePrec volT 1e-12

        noArbByTime <- noArbSabrSmileSection expiryFromDays forward alpha beta nu rho shift ShiftedLognormal
        noArbByDate <- noArbSabrSmileSection' optionDate forward alpha beta nu rho act365 shift ShiftedLognormal
        differences <- forM [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
          volT <- smileSectionVolatility noArbByTime strike
          volD <- smileSectionVolatility noArbByDate strike
          volD `shouldSatisfy` closePrec volT 1e-12
          plainVol <- smileSectionVolatility sectionByTime strike
          return (volT /= plainVol)
        or differences `shouldBe` True

    it "SabrInterpolatedSmileSection calibrates back to the generating SABR parameters,\
       \ including through the AsSmileSection upcast" $
      Settings.keepingSettings' $ do
        let strikes = [0.01, 0.02, 0.03, 0.04, 0.05]
        refVols <- mapM (\k -> unsafeShiftedSabrVolatility k forward expiry alpha beta nu rho shift ShiftedLognormal) strikes
        atmVol <- unsafeShiftedSabrVolatility forward forward expiry alpha beta nu rho shift ShiftedLognormal
        now <- today
        Settings.setEvaluationDate (Just now)
        optionDate <- addPeriod now (round (expiry * 365) :: Int, Days)
        forwardQuote <- simpleQuote forward
        atmVolQuote <- simpleQuote atmVol
        refVolQuotes <- mapM simpleQuote refVols
        interp <- sabrInterpolatedSmileSection optionDate forwardQuote strikes False atmVolQuote refVolQuotes
          alpha beta nu rho defaultSabrInterpolatedSmileSectionOpts
        rms <- sabrInterpolatedSmileSectionRmsError interp
        maxErr <- sabrInterpolatedSmileSectionMaxError interp
        rms `shouldSatisfy` (< 1e-6)
        maxErr `shouldSatisfy` (< 1e-6)

        -- the upcast escape hatch: volatility through the generic SmileSection interface (only
        -- reachable this way now that the concrete type has no smileSectionVolatility of its own).
        generic <- sabrInterpolatedSmileSectionAsSmileSection interp
        forM_ (zip strikes refVols) $ \(k, expected) -> do
          got <- smileSectionVolatility generic k
          got `shouldSatisfy` closePrec expected 1e-6

  -- Ported from test/smoke/CheckMCEngineStatistics.hs and CheckMCVarianceSwapEngineStatistics.hs:
  -- the StatisticsTrait axis added to every MC pricing engine actually reaches each engine's
  -- second template parameter. Nothing in the type system catches a StatisticsTrait value
  -- being silently ignored (a copy-paste slip could alias all four cases to the same
  -- instantiation), so each case is constructed and priced under a fixed nonzero seed.
  describe "MC engine StatisticsTrait dispatch" $ do
    let refDate = 15 `january` 2024
        maturity = 15 `january` 2025
        stats = [Statistics, GaussianStatistics, GeneralStatistics, IncrementalStatistics]

        flatProc = do
          dc <- dayCounter Actual365FixedStandard
          cal <- calendar Null
          spot <- simpleQuote 100.0
          rfQ <- simpleQuote 0.03
          rf <- flatForward refDate rfQ dc Continuous Annual
          volQ <- simpleQuote 0.20
          vol <- blackConstantVol refDate cal volQ dc
          blackScholesProcess spot rf vol EulerDiscretization False

        europeanNpvUnder stat = do
          proc' <- flatProc
          let payoff = PlainVanilla (PlainVanillaPayoff Call 100)
              exercise = European (EuropeanExercise maturity)
          opt <- vanillaOption payoff exercise
          eng <- mcEuropeanEngine PseudoRandom stat proc' (Just 1) Nothing False False (Just 1000) Nothing Nothing 42
          setPricingEngine opt eng
          npv opt

        americanNpvUnder stat = do
          proc' <- flatProc
          let payoff = PlainVanilla (PlainVanillaPayoff Put 100)
              exercise = American Nothing maturity False
          opt <- vanillaOption payoff exercise
          eng <- mcAmericanEngine PseudoRandom stat proc' (Just 50) Nothing True False Nothing (Just 0.02) Nothing 42
                   2 Monomial (Just 512) Nothing Nothing
          setPricingEngine opt eng
          npv opt

        varianceSwapNpvUnder stat = do
          proc' <- flatProc
          sw <- varianceSwap Long 0.04 10000 refDate maturity
          eng <- mcVarianceSwapEngine PseudoRandom stat proc'
                   (Just 52) Nothing False False (Just 1000) Nothing Nothing 42
          setPricingEngine sw eng
          npv sw

    it "mcEuropeanEngine: every StatisticsTrait case constructs and prices finitely" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just refDate)
        results <- mapM europeanNpvUnder stats
        allFinite results `shouldBe` True

    it "mcAmericanEngine: every StatisticsTrait case constructs and prices finitely" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just refDate)
        results <- mapM americanNpvUnder stats
        allFinite results `shouldBe` True

    it "mcVarianceSwapEngine: every StatisticsTrait case constructs, prices finitely, and\
       \ (same seed/process/timesteps) agrees closely across accumulators" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just refDate)
        results <- mapM varianceSwapNpvUnder stats
        allFinite results `shouldBe` True
        let mn = minimum results; mx = maximum results
        ((mx - mn) / abs mn) `shouldSatisfy` (< 1e-6)

  -- Ported from test/smoke/CheckBarrierEngines.hs: BlackDeltaCalculator against cached rows
  -- from blackdeltacalculator.cpp's testDeltaValues, VannaVolgaBarrierEngine and
  -- AnalyticDoubleBarrierEngine against cached NPVs from barrieroption.cpp/
  -- doublebarrieroption.cpp, AnalyticPartialTimeBarrierOptionEngine against
  -- partialtimebarrieroption.cpp, and every remaining barrier/double-barrier engine
  -- (AnalyticBinaryBarrierEngine, FdBlackScholesBarrierEngine, BinomialBarrierEngine over
  -- every BinomialTree, VannaVolgaDoubleBarrierEngine, BinomialDoubleBarrierEngine over every
  -- BinomialTree, MCDoubleBarrierEngine over every RngTrait) constructed and priced at least
  -- once, guarding against the binomial-tree/RNG switch tables being incomplete or
  -- mis-ordered (the CPIInterpolationType-style gotcha in CLAUDE.md).
  describe "Barrier / DoubleBarrier engines" $ do
    it "BlackDeltaCalculator reproduces cached deltas per DeltaType, and AtmType/DeltaType do not alias" $ do
      let checkOne ot dt spot dDf fDf stdDev strike expected = do
            calc <- blackDeltaCalculator ot dt spot dDf fDf stdDev
            delta <- deltaFromStrike calc strike
            delta `shouldSatisfy` closePrec expected 0.15
      checkOne Call Spot   1.421 0.997306 0.992266 0.1180654 1.608080 0.15
      checkOne Call PaSpot 1.421 0.997306 0.992266 0.1180654 1.600545 0.15
      checkOne Call Fwd    1.421 0.997306 0.992266 0.1180654 1.609029 0.15
      checkOne Call PaFwd  1.421 0.997306 0.992266 0.1180654 1.601550 0.15

      calc <- blackDeltaCalculator Call Spot 1.30265 0.99979 0.98508 0.11638
      strikes <- forM [AtmSpot, AtmFwd, AtmDeltaNeutral] $ atmStrike calc
      let dedup [] = []
          dedup (x:xs) = x : dedup (filter (\y -> abs (y - x) > 1.0e-6) xs)
      length (dedup strikes) `shouldBe` 3

      fwdCalc <- blackDeltaCalculator Call Fwd 1.30265 0.99979 0.98508 0.11638
      fwdStrike <- atmStrike fwdCalc AtmFwd
      putCall50Strike <- atmStrike fwdCalc AtmPutCall50
      abs (fwdStrike - putCall50Strike) `shouldSatisfy` (> 1.0e-6)

    it "VannaVolgaBarrierEngine reproduces the cached UpOut EUR call value from barrieroption.cpp" $
      Settings.keepingSettings' $ do
        let today' = 5 `march` 2013
            barrier = 1.5; strike = 1.13321; s = 1.30265; q = 0.0003541; r = 0.0033871; t = 1 :: Double
            vol25Put = 0.10087; volAtm = 0.08925; vol25Call = 0.08463; vol = 0.11638
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter Actual365FixedStandard
        spotQ <- simpleQuote s
        qQ <- simpleQuote q
        rQ <- simpleQuote r
        qTS <- flatForward today' qQ dc Continuous Annual
        rTS <- flatForward today' rQ dc Continuous Annual
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
            exercise = European (EuropeanExercise (addDays (round (t * 365)) today'))
        opt <- barrierOption UpOut barrier 0 payoff exercise
        optInst <- asOneAssetOption opt
        engine <- vannaVolgaBarrierEngine volAtmQuote vol25PutQuote vol25CallQuote spotQ rTS qTS True bsVanillaPrice
        setPricingEngine optInst engine
        price <- npv optInst
        price `shouldSatisfy` closePrec 0.148127 2.0e-3

    it "AnalyticDoubleBarrierEngine reproduces the cached KnockOut call value from doublebarrieroption.cpp" $
      Settings.keepingSettings' $ do
        let today' = 1 `january` 2020
            barrierLo = 50.0; barrierHi = 150.0; strike = 100.0
            s = 100.0; q = 0.0; r = 0.1; t = 0.25 :: Double; vol = 0.15
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        spotQ <- simpleQuote s
        qQ <- simpleQuote q
        rQ <- simpleQuote r
        volQ <- simpleQuote vol
        qTS <- flatForward today' qQ dc Continuous Annual
        rTS <- flatForward today' rQ dc Continuous Annual
        tgt <- calendar TARGET
        volTS <- blackConstantVol today' tgt volQ dc
        proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

        let payoff = PlainVanilla (PlainVanillaPayoff Call strike)
            exercise = European (EuropeanExercise (addDays (round (t * 360)) today'))
        opt <- doubleBarrierOption KnockOut barrierLo barrierHi 0 payoff exercise
        optInst <- asOneAssetOption opt
        engine <- analyticDoubleBarrierEngine proc 5
        setPricingEngine optInst engine
        price <- npv optInst
        price `shouldSatisfy` closePrec 4.3515 1.0e-3

    it "AnalyticPartialTimeBarrierOptionEngine reproduces the cached DownOut/EndB1 value from\
       \ partialtimebarrieroption.cpp" $
      Settings.keepingSettings' $ do
        let today' = 1 `january` 2020
            barrier = 100.0; rebate = 0.0; strike = 90.0
            s = 95.0; q = 0.0; r = 0.1 :: Double; vol = 0.25
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        spotQ <- simpleQuote s
        qQ <- simpleQuote q
        rQ <- simpleQuote r
        volQ <- simpleQuote vol
        qTS <- flatForward today' qQ dc Continuous Annual
        rTS <- flatForward today' rQ dc Continuous Annual
        tgt <- calendar TARGET
        volTS <- blackConstantVol today' tgt volQ dc
        proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

        let payoff = PlainVanilla (PlainVanillaPayoff Call strike)
            exercise = European (EuropeanExercise (addDays 360 today'))
            coverEventDate = addDays 1 today'
        opt <- partialTimeBarrierOption DownOut EndB1 barrier rebate coverEventDate payoff exercise
        engine <- analyticPartialTimeBarrierOptionEngine proc
        setPricingEngine opt engine
        price <- npv opt
        price `shouldSatisfy` closePrec 0.0393 1.0e-4

    it "every remaining barrier/double-barrier engine constructs and prices finitely, over every\
       \ BinomialTree/RngTrait case" $
      Settings.keepingSettings' $ do
        let today' = 1 `january` 2020 :: Day
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter Actual365FixedStandard
        spotQ <- simpleQuote 100
        qQ <- simpleQuote 0.01
        rQ <- simpleQuote 0.02
        volQ <- simpleQuote 0.2
        qTS <- flatForward today' qQ dc Continuous Annual
        rTS <- flatForward today' rQ dc Continuous Annual
        tgt <- calendar TARGET
        volTS <- blackConstantVol today' tgt volQ dc
        proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

        let payoff = PlainVanilla (PlainVanillaPayoff Call 100)
            exercise = European (EuropeanExercise (addDays 180 today'))
            binaryPayoff = CashOrNothing Call 100 10
            americanExercise = American Nothing (addDays 180 today') True

        binOpt <- barrierOption UpOut 130 0 binaryPayoff americanExercise >>= asOneAssetOption
        analyticBinaryBarrierEngine proc >>= setPricingEngine binOpt
        binNpv <- npv binOpt
        binNpv `shouldSatisfy` (\v -> not (isNaN v) && not (isInfinite v))

        barOpt <- barrierOption UpOut 130 0 payoff exercise >>= asOneAssetOption
        fdBlackScholesBarrierEngine proc 100 100 0 Douglas False 0.0 >>= setPricingEngine barOpt
        fdNpv <- npv barOpt
        fdNpv `shouldSatisfy` (\v -> not (isNaN v) && not (isInfinite v))

        binomialNpvs <- forM allTrees $ \ty -> do
          barOpt' <- barrierOption UpOut 130 0 payoff exercise >>= asOneAssetOption
          binomialBarrierEngine ty proc 200 0 >>= setPricingEngine barOpt'
          npv barOpt'
        allFinite binomialNpvs `shouldBe` True

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
        vannaVolgaDoubleBarrierEngine volAtmQuote vol25PutQuote vol25CallQuote spotQ rTS qTS True bsVanillaPrice 5
          >>= setPricingEngine dblOpt
        vvdbNpv <- npv dblOpt
        vvdbNpv `shouldSatisfy` (\v -> not (isNaN v) && not (isInfinite v))

        binomialDblNpvs <- forM allTrees $ \ty -> do
          dblOpt' <- doubleBarrierOption KnockOut 70 130 0 payoff exercise >>= asOneAssetOption
          binomialDoubleBarrierEngine ty proc 200 >>= setPricingEngine dblOpt'
          npv dblOpt'
        allFinite binomialDblNpvs `shouldBe` True

        mcDblNpvs <- forM [PseudoRandom, LowDiscrepancy] $ \rng -> do
          dblOpt' <- doubleBarrierOption KnockOut 70 130 0 payoff exercise >>= asOneAssetOption
          mcDoubleBarrierEngine rng Statistics proc (Just 20) Nothing False False (Just 1024) Nothing Nothing 42
            >>= setPricingEngine dblOpt'
          npv dblOpt'
        allFinite mcDblNpvs `shouldBe` True

  -- Ported from test/smoke/CheckDigitalAmericanKO.hs. Golden values are lifted verbatim from
  -- digitaloption.cpp's testCashAtExpiryOrNothingAmericanValues and
  -- testAssetAtExpiryOrNothingAmericanValues, on a payoff-at-expiry American exercise --
  -- knockin picks AnalyticDigitalAmericanEngine vs. AnalyticDigitalAmericanKOEngine.
  describe "AnalyticDigitalAmericanEngine / AnalyticDigitalAmericanKOEngine" $ do
    let today' = 28 `august` 2026
        priceCase mkPayoff (ty, strike, spot, q, r, tDays, vol, knockIn, _expected) =
          Settings.keepingSettings' $ do
            Settings.setEvaluationDate (Just today')
            dc <- dayCounter (Actual360 False)
            cal <- calendar Null
            spotQ <- simpleQuote spot
            qQ <- simpleQuote q
            rQ <- simpleQuote r
            volQ <- simpleQuote vol
            qTS <- flatForward' 0 cal qQ dc Continuous Annual
            rTS <- flatForward' 0 cal rQ dc Continuous Annual
            volTS <- blackConstantVol' 0 cal volQ dc
            process <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
            engine <- if knockIn then analyticDigitalAmericanEngine process
                                  else analyticDigitalAmericanKOEngine process
            let exDate = addDays tDays today'
            opt <- europeanOption (mkPayoff ty strike) (American Nothing exDate True)
              >>= asOneAssetOption >>= asOption >>= asInstrument
            setPricingEngine opt engine
            npv opt

        cashOrNothingCases =
          [ (Put,  100, 105, 0.00, 0.10, 180, 0.20, True,   9.3604 :: Double)
          , (Call, 100,  95, 0.00, 0.10, 180, 0.20, True,  11.2223)
          , (Put,  100, 105, 0.00, 0.10, 180, 0.20, False,  4.9081)
          , (Call, 100,  95, 0.00, 0.10, 180, 0.20, False,  3.0461)
          ]
        assetOrNothingCases =
          [ (Put,  100, 105, 0.00, 0.10, 180, 0.20, True,  64.8426 :: Double)
          , (Call, 100,  95, 0.00, 0.10, 180, 0.20, True,  77.7017)
          , (Put,  100, 105, 0.00, 0.10, 180, 0.20, False, 40.1574)
          , (Call, 100,  95, 0.00, 0.10, 180, 0.20, False, 17.2983)
          ]

    it "cash-(at-expiry)-or-nothing American digital reproduces digitaloption.cpp" $
      forM_ cashOrNothingCases $ \c@(_,_,_,_,_,_,_,_,expected) -> do
        v <- priceCase (\ty s -> CashOrNothing ty s 15.0) c
        v `shouldSatisfy` closePrec expected 1e-4

    it "asset-(at-expiry)-or-nothing American digital reproduces digitaloption.cpp" $
      forM_ assetOrNothingCases $ \c@(_,_,_,_,_,_,_,_,expected) -> do
        v <- priceCase (\ty s -> AssetOrNothing ty s) c
        v `shouldSatisfy` closePrec expected 1e-4
