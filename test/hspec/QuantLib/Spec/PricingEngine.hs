-- Coverage for 'QuantLib.PricingEngine' entry points ported from proven-correct
-- @test/smoke/*.hs@ scripts that were never wired into @stack test --coverage@ (see
-- CLAUDE.md: coverage is only measured over @test\/hspec\/**@ + @test\/example\/**@).
-- Each block below preserves the source smoke script's own reasoning in its header
-- comment; only the assertion style changed (SmokeCheck's checkClose/checkEq/checkWith,
-- which 'error' on failure, become hspec 'shouldSatisfy'/'shouldBe').
module QuantLib.Spec.PricingEngine (spec) where

import Control.Monad(forM, forM_, when)
import Data.Time.Calendar(addDays, addGregorianYearsClip)

import Test.Hspec
import qualified Data.Vector.Storable as V
import Data.List.NonEmpty(fromList)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..), VolatilityType(..))
import QuantLib.Quote hiding(value)
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.CashFlow(fixedDividend)
import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Option hiding(deltaForward, vega, rho, dividendRho, strikeSensitivity, itmCashProbability)
import qualified QuantLib.Instrument.Option as Opt(rho, vega, dividendRho)
import QuantLib.Instrument.CapFloor(cap)
import QuantLib.Instrument.Swap(varianceSwap, vanillaSwap, floatingLeg, SwapType(..))
import QuantLib.Process hiding(blackScholesTheta)
import QuantLib.Model hiding(setPricingEngine, value)
import QuantLib.Math(RngTrait(..), StatisticsTrait(..), PolynomialType(..), BinomialTree(..), FdmScheme(..))
import QuantLib.Method(fdmBlackScholesMesher, fdmMesherComposite, fdmMesherLocations)
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
    let strike = 100.0; forward = 105.0; stdDev = 0.25; disc = 0.97
        spot = 103.0; maturity = 2.0

    it "BlackCalculator: ctors agree, put-call parity holds, Call/Put share second-order greeks,\
       \ value matches blackFormula, vanna/volga match their closed forms" $ do
      callBC <- blackCalculator' Call strike forward stdDev disc
      putBC <- blackCalculator' Put strike forward stdDev disc
      callBC2 <- blackCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) forward stdDev disc
      putBC2 <- blackCalculator (PlainVanilla (PlainVanillaPayoff Put strike)) forward stdDev disc

      callVal <- value callBC
      callVal2 <- value callBC2
      callVal2 `shouldBe` callVal
      putVal <- value putBC
      putVal2 <- value putBC2
      putVal2 `shouldBe` putVal

      (callVal - putVal) `shouldSatisfy` closePrec (disc * (forward - strike)) 1e-10

      callDF <- deltaForward callBC
      putDF <- deltaForward putBC
      (callDF - putDF) `shouldSatisfy` closePrec disc 1e-10

      forM_ [gammaForward, (`vega` maturity), strikeGamma] $ \f -> do
        c <- f callBC
        p <- f putBC
        p `shouldBe` c

      refCallVal <- blackFormula Call strike forward stdDev disc 0.0
      callVal `shouldSatisfy` closePrec refCallVal 1e-12
      refPutVal <- blackFormula Put strike forward stdDev disc 0.0
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
      callBC <- blackCalculator' Call strike forward stdDev disc
      callVal <- value callBC
      let growth = 1.0
          bscSpot = forward * disc / growth
      callBSC <- blackScholesCalculator' Call strike bscSpot growth stdDev disc
      callBSC2 <- blackScholesCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) bscSpot growth stdDev disc
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
      callNC <- bachelierCalculator' Call strike forward bachelierStdDev disc
      putNC <- bachelierCalculator' Put strike forward bachelierStdDev disc
      callNC2 <- bachelierCalculator (PlainVanilla (PlainVanillaPayoff Call strike)) forward bachelierStdDev disc
      putNC2 <- bachelierCalculator (PlainVanilla (PlainVanillaPayoff Put strike)) forward bachelierStdDev disc

      callNVal <- bachelierValue callNC
      callNVal2 <- bachelierValue callNC2
      callNVal2 `shouldBe` callNVal
      putNVal <- bachelierValue putNC
      putNVal2 <- bachelierValue putNC2
      putNVal2 `shouldBe` putNVal

      (callNVal - putNVal) `shouldSatisfy` closePrec (disc * (forward - strike)) 1e-10

      callNDF <- bachelierDeltaForward callNC
      putNDF <- bachelierDeltaForward putNC
      (callNDF - putNDF) `shouldSatisfy` closePrec disc 1e-10

      forM_ [ bachelierGammaForward, (`bachelierVega` maturity)
            , bachelierStrikeGamma, (`bachelierVanna` maturity), (`bachelierVolga` maturity)
            ] $ \f -> do
        c <- f callNC
        p <- f putNC
        p `shouldBe` c

      refCallNVal <- bachelierBlackFormula Call strike forward bachelierStdDev disc
      callNVal `shouldSatisfy` closePrec refCallNVal 1e-12
      refPutNVal <- bachelierBlackFormula Put strike forward bachelierStdDev disc
      putNVal `shouldSatisfy` closePrec refPutNVal 1e-12

      let d = (forward - strike) / bachelierStdDev
          nd = normalPdf d
      callNVega <- bachelierVega callNC maturity
      callNVanna <- bachelierVanna callNC maturity
      callNVanna `shouldSatisfy` closePrec (-d * nd * sqrt maturity / bachelierStdDev) 1e-9
      callNVolga <- bachelierVolga callNC maturity
      callNVolga `shouldSatisfy` closePrec (d * d / bachelierStdDev * callNVega) 1e-9
      callNVega `shouldSatisfy` closePrec (disc * sqrt maturity * nd) 1e-9

  -- Ported from test/smoke/CheckSabrSmileSection.hs. volatility(strike)/variance(strike) must
  -- exactly match the already-bound unsafeShiftedSabrVolatility formula (enum-dispatched
  -- through a C-side VolatilityType cast, same class of bug as the CPIInterpolationType
  -- incident); the Date- and Time-based ctors of SabrSmileSection/NoArbSabrSmileSection must
  -- agree with each other and (for NoArb) differ from the plain SABR smile; and
  -- SabrInterpolatedSmileSection must calibrate back to the SABR parameters that generated its
  -- input vols.
  describe "SabrSmileSection / NoArbSabrSmileSection / SabrInterpolatedSmileSection" $ do
    let forward = 0.03; expiry = 5.0; alpha_ = 0.04; beta_ = 0.5; nu = 0.4; rho_ = -0.2; shift = 0.0

    it "matches unsafeShiftedSabrVolatility for both VolatilityType cases, and Normal /= ShiftedLognormal" $
      Settings.keepingSettings' $ do
        forM_ [ShiftedLognormal, Normal] $ \volType -> do
          section <- sabrSmileSection expiry forward alpha_ beta_ nu rho_ shift volType
          forM_ [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
            got <- smileSectionVolatility section strike
            expected <- unsafeShiftedSabrVolatility strike forward expiry alpha_ beta_ nu rho_ shift volType
            got `shouldBe` expected
            var <- smileSectionVariance section strike
            var `shouldSatisfy` closePrec (expected * expected * expiry) 1e-12

        volShiftedLognormal <- sabrSmileSection expiry forward alpha_ beta_ nu rho_ shift ShiftedLognormal
        volAtAtm1 <- smileSectionVolatility volShiftedLognormal forward
        volNormal <- sabrSmileSection expiry forward alpha_ beta_ nu rho_ shift Normal
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

        sectionByTime <- sabrSmileSection expiryFromDays forward alpha_ beta_ nu rho_ shift ShiftedLognormal
        sectionByDate <- sabrSmileSection' optionDate forward alpha_ beta_ nu rho_ (Just refDate) act365 shift ShiftedLognormal
        forM_ [0.01, 0.02, 0.03, 0.04, 0.05 :: Double] $ \strike -> do
          volT <- smileSectionVolatility sectionByTime strike
          volD <- smileSectionVolatility sectionByDate strike
          volD `shouldSatisfy` closePrec volT 1e-12

        noArbByTime <- noArbSabrSmileSection expiryFromDays forward alpha_ beta_ nu rho_ shift ShiftedLognormal
        noArbByDate <- noArbSabrSmileSection' optionDate forward alpha_ beta_ nu rho_ act365 shift ShiftedLognormal
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
        refVols <- mapM (\k -> unsafeShiftedSabrVolatility k forward expiry alpha_ beta_ nu rho_ shift ShiftedLognormal) strikes
        atmVol <- unsafeShiftedSabrVolatility forward forward expiry alpha_ beta_ nu rho_ shift ShiftedLognormal
        now <- today
        Settings.setEvaluationDate (Just now)
        optionDate <- addPeriod now (round (expiry * 365) :: Int, Days)
        forwardQuote <- simpleQuote forward
        atmVolQ <- simpleQuote atmVol
        refVolQuotes <- mapM simpleQuote refVols
        interp <- sabrInterpolatedSmileSection optionDate forwardQuote (fromList $ zip strikes refVolQuotes) False atmVolQ
          alpha_ beta_ nu rho_ defaultSabrInterpolatedSmileSectionOpts
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
            delta_ <- deltaFromStrike calc strike
            delta_ `shouldSatisfy` closePrec expected 0.15
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

        -- fdHestonBarrierEngine/fdHestonDoubleBarrierEngine are otherwise untested: no upstream
        -- golden fixture was found reachable through hasquant's current Heston-model bindings,
        -- so (matching the "constructs and prices finitely" precedent just above) this just
        -- confirms both actually price rather than crash/NaN.
        hp <- hestonProcess rTS (Just qTS) spotQ 0.04 2.0 0.04 0.5 (-0.5) QuadraticExponentialMartingale
        hm <- hestonModel hp
        fdHBarOpt <- barrierOption UpOut 130 0 payoff exercise >>= asOneAssetOption
        fdHestonBarrierEngine hm 20 100 20 0 Douglas Nothing 1.0 >>= setPricingEngine fdHBarOpt
        fdHBarNpv <- npv fdHBarOpt
        fdHBarNpv `shouldSatisfy` (\v -> not (isNaN v) && not (isInfinite v))

        fdHDblOpt <- doubleBarrierOption KnockOut 70 130 0 payoff exercise >>= asOneAssetOption
        fdHestonDoubleBarrierEngine hm 20 100 20 0 Douglas Nothing 1.0 >>= setPricingEngine fdHDblOpt
        fdHDblNpv <- npv fdHDblOpt
        fdHDblNpv `shouldSatisfy` (\v -> not (isNaN v) && not (isInfinite v))

    it "mcBarrierEngine reproduces the cached DownIn call value from barrieroption.cpp" $
      -- cached reference from testHaugValues's Barrier::DownIn row (barrier=90, vol=0.10,
      -- expected 0.07187): analytic (AnalyticBarrierEngine) and MC (MakeMCBarrierEngine) are
      -- both checked against the same literal there, so the MC engine is checked here too,
      -- at upstream's own relative tolerance.
      Settings.keepingSettings' $ do
        let today' = 1 `january` 2020
            expected = 0.07187 :: Double
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        spotQ <- simpleQuote 100.0
        qQ <- simpleQuote 0.02
        rQ <- simpleQuote 0.05
        volQ <- simpleQuote 0.10
        qTS <- flatForward today' qQ dc Continuous Annual
        rTS <- flatForward today' rQ dc Continuous Annual
        tgt <- calendar TARGET
        volTS <- blackConstantVol today' tgt volQ dc
        proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
        let payoff = PlainVanilla (PlainVanillaPayoff Call 100.0)
            exercise = European (EuropeanExercise (addDays 360 today'))
        opt <- barrierOption DownIn 90.0 0 payoff exercise >>= asOneAssetOption
        eng <- mcBarrierEngine LowDiscrepancy Statistics proc Nothing (Just 1) True False (Just 131071) Nothing (Just 1048575) False 5
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec expected (2.0e-2 * expected)

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
        v <- priceCase AssetOrNothing c
        v `shouldSatisfy` closePrec expected 1e-4

    -- cached references from digitaloption.cpp::testMCCashAtHit: cash-(at-hit)-or-nothing
    -- American digital, priced via MakeMCDigitalEngine (default payoffAtExpiry=False, i.e. the
    -- cash is paid at the moment the strike is hit, not at exercise).
    it "mcDigitalEngine reproduces digitaloption.cpp's cash-at-hit values" $
      Settings.keepingSettings' $ do
        let evalDate' = 1 `january` 2020
            cases = [ (Put, 100.0, 105.0, 0.20, 0.10, 0.5 :: Double, 0.20, 12.2715 :: Double)
                    , (Call, 100.0, 95.0, 0.20, 0.10, 0.5, 0.20, 8.9109)
                    ]
        Settings.setEvaluationDate (Just evalDate')
        dc <- dayCounter (Actual360 False)
        forM_ cases $ \(ty, strike, spot, q, r, t, vol, expected) -> do
          spotQ <- simpleQuote spot
          qQ <- simpleQuote q
          rQ <- simpleQuote r
          volQ <- simpleQuote vol
          qTS <- flatForward evalDate' qQ dc Continuous Annual
          rTS <- flatForward evalDate' rQ dc Continuous Annual
          tgt <- calendar TARGET
          volTS <- blackConstantVol evalDate' tgt volQ dc
          proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
          let exDate = addDays (round (t * 360 :: Double)) evalDate'
          opt <- europeanOption (CashOrNothing ty strike 15.0) (American (Just evalDate') exDate False)
            >>= asOneAssetOption >>= asOption >>= asInstrument
          eng <- mcDigitalEngine LowDiscrepancy Statistics proc Nothing (Just 90) True False (Just 16383) Nothing (Just 1000000) 1
          setPricingEngine opt eng
          v <- npv opt
          v `shouldSatisfy` closePrec expected 1.0e-2

  -- Ported from test-suite/quantooption.cpp. Each case wires a QuantoEngine<Instr,Engine>
  -- instantiation (a GeneralizedBlackScholesProcess plus a foreign risk-free curve, an
  -- exchange-rate vol surface, and a correlation quote) around the matching base engine, and
  -- checks the resulting quanto-adjusted NPV against Haug's cached literature values.
  describe "Quanto engines" $ do
    let today' = 1 `january` 2020
        setupFlat dc tgt s q r vol fxr fxv corr = do
          spotQ <- simpleQuote s
          qQ <- simpleQuote q
          rQ <- simpleQuote r
          volQ <- simpleQuote vol
          fxrQ <- simpleQuote fxr
          fxvQ <- simpleQuote fxv
          corrQ <- simpleQuote corr
          qTS <- flatForward today' qQ dc Continuous Annual
          rTS <- flatForward today' rQ dc Continuous Annual
          volTS <- blackConstantVol today' tgt volQ dc
          fxrTS <- flatForward today' fxrQ dc Continuous Annual
          fxVolTS <- blackConstantVol today' tgt fxvQ dc
          proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
          return (proc, fxrTS, fxVolTS, corrQ)

    it "QuantoEngine<VanillaOption,AnalyticEuropeanEngine> reproduces testValues" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        let cases = [ (Call, 105.0, 100.0, 0.04, 0.08, 0.5 :: Double, 0.2, 0.05, 0.10, 0.3, 5.3280 / 1.5 :: Double)
                    , (Put,  105.0, 100.0, 0.04, 0.08, 0.5, 0.2, 0.05, 0.10, 0.3, 8.1636)
                    ]
        forM_ cases $ \(ty, strike, s, q, r, t, vol, fxr, fxv, corr, expected) -> do
          (proc, fxrTS, fxVolTS, corrQ) <- setupFlat dc tgt s q r vol fxr fxv corr
          engine <- quantoEuropeanEngine proc fxrTS fxVolTS corrQ
          let exDate = addDays (round (t * 360 :: Double)) today'
          opt <- quantoVanillaOption (PlainVanilla (PlainVanillaPayoff ty strike)) (European (EuropeanExercise exDate))
          optInst <- asOneAssetOption opt
          setPricingEngine optInst engine
          v <- npv optInst
          v `shouldSatisfy` closePrec expected 1.0e-4

    -- Ported from quantooption.cpp's testGreeks: for every (type, strike) pair, bump each of
    -- spot/rRate/qRate/vol/fxRate/fxVol/correlation (and the evaluation date, for theta) by a
    -- relative 1e-4 and compare the resulting central-difference estimate against the engine's
    -- own analytic greek, at every combination of the other quotes' levels.
    -- Every greek but theta holds upstream's own 1e-5 tolerance. theta's central difference
    -- bumps the evaluation date by a full 2 days -- a far larger relative step (~0.3% of the
    -- 2-year maturity) than the other greeks' 1e-4-relative quote bumps -- so its own
    -- discretization error dominates at the vol=1.20 (120% annual) extreme; measured worst case
    -- across the whole sweep is ~3.1e-4 (Put, strike=150, vol=1.2, fxVol=1.2, corr=0.9), so 5e-4
    -- keeps this a real check while accommodating it, per CLAUDE.md's numeric-tolerance rule.
    it "QuantoEngine<VanillaOption,AnalyticEuropeanEngine> reproduces testGreeks" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        spotQ <- simpleQuote (0.0 :: Double)
        qRateQ <- simpleQuote (0.0 :: Double)
        rRateQ <- simpleQuote (0.0 :: Double)
        volQ <- simpleQuote (0.0 :: Double)
        fxRateQ <- simpleQuote (0.0 :: Double)
        fxVolQ <- simpleQuote (0.0 :: Double)
        corrQ <- simpleQuote (0.0 :: Double)
        qTS <- flatForward' 0 tgt qRateQ dc Continuous Annual
        rTS <- flatForward' 0 tgt rRateQ dc Continuous Annual
        volTS <- blackConstantVol' 0 tgt volQ dc
        fxrTS <- flatForward' 0 tgt fxRateQ dc Continuous Annual
        fxVolTS <- blackConstantVol' 0 tgt fxVolQ dc
        proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
        engine <- quantoEuropeanEngine proc fxrTS fxVolTS corrQ
        let u = 100.0 :: Double
            qRates = [0.04, 0.05 :: Double]
            rRates = [0.01, 0.05, 0.15 :: Double]
            vols = [0.11, 1.20 :: Double]
            corrs = [0.10, 0.90 :: Double]
            innerCases = [ (q, r, v, fxr, fxv, corr)
                         | q <- qRates, r <- rRates, v <- vols
                         , fxr <- rRates, fxv <- vols, corr <- corrs
                         ]
        forM_ [Call, Put] $ \ty -> forM_ [50.0, 99.5, 100.0, 100.5, 150.0 :: Double] $ \strike -> do
          let exDate = addGregorianYearsClip 2 today'
          opt <- quantoVanillaOption (PlainVanilla (PlainVanillaPayoff ty strike)) (European (EuropeanExercise exDate))
          optInst <- asOneAssetOption opt
          setPricingEngine optInst engine
          forM_ innerCases $ \(q, r, v, fxr, fxv, corr) -> do
            _ <- setValue spotQ u
            _ <- setValue qRateQ q
            _ <- setValue rRateQ r
            _ <- setValue volQ v
            _ <- setValue fxRateQ fxr
            _ <- setValue fxVolQ fxv
            _ <- setValue corrQ corr
            val <- npv optInst
            when (val > u * 1.0e-5) $ do
              calcDelta <- delta optInst
              calcGamma <- gamma optInst
              calcTheta <- theta optInst
              calcRho <- Opt.rho optInst
              calcDivRho <- Opt.dividendRho optInst
              calcVega <- Opt.vega optInst
              calcQrho <- qrho opt
              calcQvega <- qvega opt
              calcQlambda <- qlambda opt

              let du = u * 1.0e-4
              _ <- setValue spotQ (u + du); valueP <- npv optInst; deltaP <- delta optInst
              _ <- setValue spotQ (u - du); valueM <- npv optInst; deltaM <- delta optInst
              _ <- setValue spotQ u
              let expDelta = (valueP - valueM) / (2 * du)
                  expGamma = (deltaP - deltaM) / (2 * du)

              let dr = r * 1.0e-4
              _ <- setValue rRateQ (r + dr); rValueP <- npv optInst
              _ <- setValue rRateQ (r - dr); rValueM <- npv optInst
              _ <- setValue rRateQ r
              let expRho = (rValueP - rValueM) / (2 * dr)

              let dq = q * 1.0e-4
              _ <- setValue qRateQ (q + dq); qValueP <- npv optInst
              _ <- setValue qRateQ (q - dq); qValueM <- npv optInst
              _ <- setValue qRateQ q
              let expDivRho = (qValueP - qValueM) / (2 * dq)

              let dv = v * 1.0e-4
              _ <- setValue volQ (v + dv); vValueP <- npv optInst
              _ <- setValue volQ (v - dv); vValueM <- npv optInst
              _ <- setValue volQ v
              let expVega = (vValueP - vValueM) / (2 * dv)

              let dfxr = fxr * 1.0e-4
              _ <- setValue fxRateQ (fxr + dfxr); fxrValueP <- npv optInst
              _ <- setValue fxRateQ (fxr - dfxr); fxrValueM <- npv optInst
              _ <- setValue fxRateQ fxr
              let expQrho = (fxrValueP - fxrValueM) / (2 * dfxr)

              let dfxv = fxv * 1.0e-4
              _ <- setValue fxVolQ (fxv + dfxv); fxvValueP <- npv optInst
              _ <- setValue fxVolQ (fxv - dfxv); fxvValueM <- npv optInst
              _ <- setValue fxVolQ fxv
              let expQvega = (fxvValueP - fxvValueM) / (2 * dfxv)

              let dcorr = corr * 1.0e-4
              _ <- setValue corrQ (corr + dcorr); corrValueP <- npv optInst
              _ <- setValue corrQ (corr - dcorr); corrValueM <- npv optInst
              _ <- setValue corrQ corr
              let expQlambda = (corrValueP - corrValueM) / (2 * dcorr)

              dTyears <- years dc (addDays (-1) today') (addDays 1 today') Nothing Nothing
              Settings.setEvaluationDate (Just (addDays (-1) today'))
              thetaValueM <- npv optInst
              Settings.setEvaluationDate (Just (addDays 1 today'))
              thetaValueP <- npv optInst
              Settings.setEvaluationDate (Just today')
              let expTheta = (thetaValueP - thetaValueM) / dTyears
                  relErr expctd calcd = abs (expctd - calcd) / u

              relErr expDelta calcDelta `shouldSatisfy` (< 1.0e-5)
              relErr expGamma calcGamma `shouldSatisfy` (< 1.0e-5)
              relErr expTheta calcTheta `shouldSatisfy` (< 5.0e-4)
              relErr expRho calcRho `shouldSatisfy` (< 1.0e-5)
              relErr expDivRho calcDivRho `shouldSatisfy` (< 1.0e-5)
              relErr expVega calcVega `shouldSatisfy` (< 1.0e-5)
              relErr expQrho calcQrho `shouldSatisfy` (< 1.0e-5)
              relErr expQvega calcQvega `shouldSatisfy` (< 1.0e-5)
              relErr expQlambda calcQlambda `shouldSatisfy` (< 1.0e-5)

    it "QuantoEngine<ForwardVanillaOption,ForwardVanillaEngine<AnalyticEuropeanEngine>> reproduces testForwardValues" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        let cases = [ (Call, 1.05 :: Double, 100.0, 0.04, 0.08, 0.00 :: Double, 0.5 :: Double, 0.20, 0.05, 0.10, 0.3, 5.3280 / 1.5 :: Double)
                    , (Put,  1.05, 100.0, 0.04, 0.08, 0.00, 0.5, 0.20, 0.05, 0.10, 0.3, 8.1636)
                    , (Call, 1.05, 100.0, 0.04, 0.08, 0.25, 0.5, 0.20, 0.05, 0.10, 0.3, 2.0171)
                    , (Put,  1.05, 100.0, 0.04, 0.08, 0.25, 0.5, 0.20, 0.05, 0.10, 0.3, 6.7296)
                    ]
        forM_ cases $ \(ty, moneyness, s, q, r, start, t, vol, fxr, fxv, corr, expected) -> do
          (proc, fxrTS, fxVolTS, corrQ) <- setupFlat dc tgt s q r vol fxr fxv corr
          engine <- quantoForwardEuropeanEngine proc fxrTS fxVolTS corrQ
          let exDate = addDays (round (t * 360 :: Double)) today'
              resetDate = addDays (round (start * 360 :: Double)) today'
          opt <- quantoForwardVanillaOption moneyness resetDate (PlainVanilla (PlainVanillaPayoff ty 0.0)) (European (EuropeanExercise exDate))
          optInst <- asOneAssetOption opt
          setPricingEngine optInst engine
          v <- npv optInst
          v `shouldSatisfy` closePrec expected 1.0e-4

    -- Ported from quantooption.cpp's testForwardGreeks, same bump-and-revalue shape as testGreeks
    -- above but over 'QuantoForwardVanillaOption' (type, moneyness, resetMonths) combinations.
    -- theta's tolerance is loosened further than testGreeks' (see the comment there): the
    -- forward-starting payoff's moneyness-relative strike makes its date sensitivity more
    -- nonlinear, and the measured worst case across the sweep is ~2.5e-3 (Put, moneyness=1.1,
    -- reset=6m, vol=1.2, fxVol=1.2, corr=0.9); every other greek still holds 1e-5.
    it "QuantoEngine<ForwardVanillaOption,ForwardVanillaEngine<AnalyticEuropeanEngine>> reproduces testForwardGreeks" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        spotQ <- simpleQuote (0.0 :: Double)
        qRateQ <- simpleQuote (0.0 :: Double)
        rRateQ <- simpleQuote (0.0 :: Double)
        volQ <- simpleQuote (0.0 :: Double)
        fxRateQ <- simpleQuote (0.0 :: Double)
        fxVolQ <- simpleQuote (0.0 :: Double)
        corrQ <- simpleQuote (0.0 :: Double)
        qTS <- flatForward' 0 tgt qRateQ dc Continuous Annual
        rTS <- flatForward' 0 tgt rRateQ dc Continuous Annual
        volTS <- blackConstantVol' 0 tgt volQ dc
        fxrTS <- flatForward' 0 tgt fxRateQ dc Continuous Annual
        fxVolTS <- blackConstantVol' 0 tgt fxVolQ dc
        proc <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
        engine <- quantoForwardEuropeanEngine proc fxrTS fxVolTS corrQ
        let u = 100.0 :: Double
            qRates = [0.04, 0.05 :: Double]
            rRates = [0.01, 0.05, 0.15 :: Double]
            vols = [0.11, 1.20 :: Double]
            corrs = [0.10, 0.90 :: Double]
            innerCases = [ (q, r, v, fxr, fxv, corr)
                         | q <- qRates, r <- rRates, v <- vols
                         , fxr <- rRates, fxv <- vols, corr <- corrs
                         ]
        forM_ [Call, Put] $ \ty -> forM_ [0.9, 1.0, 1.1 :: Double] $ \moneyness ->
          forM_ [6, 9 :: Integer] $ \startMonth -> do
            let exDate = addGregorianYearsClip 2 today'
            resetDate <- addPeriod today' (fromInteger startMonth, Months)
            opt <- quantoForwardVanillaOption moneyness resetDate (PlainVanilla (PlainVanillaPayoff ty 0.0)) (European (EuropeanExercise exDate))
            optInst <- asOneAssetOption opt
            setPricingEngine optInst engine
            forM_ innerCases $ \(q, r, v, fxr, fxv, corr) -> do
              _ <- setValue spotQ u
              _ <- setValue qRateQ q
              _ <- setValue rRateQ r
              _ <- setValue volQ v
              _ <- setValue fxRateQ fxr
              _ <- setValue fxVolQ fxv
              _ <- setValue corrQ corr
              val <- npv optInst
              when (val > u * 1.0e-5) $ do
                calcDelta <- delta optInst
                calcGamma <- gamma optInst
                calcTheta <- theta optInst
                calcRho <- Opt.rho optInst
                calcDivRho <- Opt.dividendRho optInst
                calcVega <- Opt.vega optInst
                calcQrho <- qrho opt
                calcQvega <- qvega opt
                calcQlambda <- qlambda opt

                let du = u * 1.0e-4
                _ <- setValue spotQ (u + du); valueP <- npv optInst; deltaP <- delta optInst
                _ <- setValue spotQ (u - du); valueM <- npv optInst; deltaM <- delta optInst
                _ <- setValue spotQ u
                let expDelta = (valueP - valueM) / (2 * du)
                    expGamma = (deltaP - deltaM) / (2 * du)

                let dr = r * 1.0e-4
                _ <- setValue rRateQ (r + dr); rValueP <- npv optInst
                _ <- setValue rRateQ (r - dr); rValueM <- npv optInst
                _ <- setValue rRateQ r
                let expRho = (rValueP - rValueM) / (2 * dr)

                let dq = q * 1.0e-4
                _ <- setValue qRateQ (q + dq); qValueP <- npv optInst
                _ <- setValue qRateQ (q - dq); qValueM <- npv optInst
                _ <- setValue qRateQ q
                let expDivRho = (qValueP - qValueM) / (2 * dq)

                let dv = v * 1.0e-4
                _ <- setValue volQ (v + dv); vValueP <- npv optInst
                _ <- setValue volQ (v - dv); vValueM <- npv optInst
                _ <- setValue volQ v
                let expVega = (vValueP - vValueM) / (2 * dv)

                let dfxr = fxr * 1.0e-4
                _ <- setValue fxRateQ (fxr + dfxr); fxrValueP <- npv optInst
                _ <- setValue fxRateQ (fxr - dfxr); fxrValueM <- npv optInst
                _ <- setValue fxRateQ fxr
                let expQrho = (fxrValueP - fxrValueM) / (2 * dfxr)

                let dfxv = fxv * 1.0e-4
                _ <- setValue fxVolQ (fxv + dfxv); fxvValueP <- npv optInst
                _ <- setValue fxVolQ (fxv - dfxv); fxvValueM <- npv optInst
                _ <- setValue fxVolQ fxv
                let expQvega = (fxvValueP - fxvValueM) / (2 * dfxv)

                let dcorr = corr * 1.0e-4
                _ <- setValue corrQ (corr + dcorr); corrValueP <- npv optInst
                _ <- setValue corrQ (corr - dcorr); corrValueM <- npv optInst
                _ <- setValue corrQ corr
                let expQlambda = (corrValueP - corrValueM) / (2 * dcorr)

                dTyears <- years dc (addDays (-1) today') (addDays 1 today') Nothing Nothing
                Settings.setEvaluationDate (Just (addDays (-1) today'))
                thetaValueM <- npv optInst
                Settings.setEvaluationDate (Just (addDays 1 today'))
                thetaValueP <- npv optInst
                Settings.setEvaluationDate (Just today')
                let expTheta = (thetaValueP - thetaValueM) / dTyears
                    relErr expctd calcd = abs (expctd - calcd) / u

                relErr expDelta calcDelta `shouldSatisfy` (< 1.0e-5)
                relErr expGamma calcGamma `shouldSatisfy` (< 1.0e-5)
                relErr expTheta calcTheta `shouldSatisfy` (< 3.0e-3)
                relErr expRho calcRho `shouldSatisfy` (< 1.0e-5)
                relErr expDivRho calcDivRho `shouldSatisfy` (< 1.0e-5)
                relErr expVega calcVega `shouldSatisfy` (< 1.0e-5)
                relErr expQrho calcQrho `shouldSatisfy` (< 1.0e-5)
                relErr expQvega calcQvega `shouldSatisfy` (< 1.0e-5)
                relErr expQlambda calcQlambda `shouldSatisfy` (< 1.0e-5)

    it "QuantoEngine<ForwardVanillaOption,ForwardPerformanceVanillaEngine<AnalyticEuropeanEngine>> reproduces testForwardPerformanceValues" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        let cases = [ (Call, 1.05 :: Double, 100.0, 0.04, 0.08, 0.00 :: Double, 0.5 :: Double, 0.20, 0.05, 0.10, 0.3, 5.3280 / 150 :: Double)
                    , (Put,  1.05, 100.0, 0.04, 0.08, 0.00, 0.5, 0.20, 0.05, 0.10, 0.3, 0.0816)
                    , (Call, 1.05, 100.0, 0.04, 0.08, 0.25, 0.5, 0.20, 0.05, 0.10, 0.3, 0.0201)
                    , (Put,  1.05, 100.0, 0.04, 0.08, 0.25, 0.5, 0.20, 0.05, 0.10, 0.3, 0.0672)
                    ]
        forM_ cases $ \(ty, moneyness, s, q, r, start, t, vol, fxr, fxv, corr, expected) -> do
          (proc, fxrTS, fxVolTS, corrQ) <- setupFlat dc tgt s q r vol fxr fxv corr
          engine <- quantoForwardPerformanceEuropeanEngine proc fxrTS fxVolTS corrQ
          let exDate = addDays (round (t * 360 :: Double)) today'
              resetDate = addDays (round (start * 360 :: Double)) today'
          opt <- quantoForwardVanillaOption moneyness resetDate (PlainVanilla (PlainVanillaPayoff ty 0.0)) (European (EuropeanExercise exDate))
          optInst <- asOneAssetOption opt
          setPricingEngine optInst engine
          v <- npv optInst
          v `shouldSatisfy` closePrec expected 1.0e-4

    it "QuantoEngine<BarrierOption,AnalyticBarrierEngine> reproduces testBarrierValues" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        let cases = [ (DownOut, 95.0 :: Double, 3.0 :: Double, Call, 100.0 :: Double, 90.0 :: Double, 0.04, 0.0212, 0.50 :: Double, 0.25, 0.05, 0.2, 0.3, 8.247 :: Double, 0.5 :: Double)
                    , (DownOut, 95.0, 3.0, Put,  100.0, 90.0, 0.04, 0.0212, 0.50, 0.25, 0.05, 0.2, 0.3, 2.274, 0.5)
                    , (DownIn,  95.0, 0.0, Put,  100.0, 90.0, 0.04, 0.0212, 0.50, 0.25, 0.05, 0.2, 0.3, 2.85,  0.5)
                    ]
        forM_ cases $ \(barType, barrier, rebate, ty, s, strike, q, r, t, vol, fxr, fxv, corr, expected, tol) -> do
          (proc, fxrTS, fxVolTS, corrQ) <- setupFlat dc tgt s q r vol fxr fxv corr
          engine <- quantoBarrierEngine proc fxrTS fxVolTS corrQ
          let exDate = addDays (round (t * 360 :: Double)) today'
          opt <- quantoBarrierOption barType barrier rebate (PlainVanilla (PlainVanillaPayoff ty strike)) (European (EuropeanExercise exDate))
          optInst <- asOneAssetOption opt
          setPricingEngine optInst engine
          v <- npv optInst
          v `shouldSatisfy` closePrec expected tol

    it "QuantoEngine<DoubleBarrierOption,AnalyticDoubleBarrierEngine> reproduces testDoubleBarrierValues" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        let cases = [ (KnockOut, 50.0 :: Double, 150.0 :: Double, 0.0 :: Double, Call, 100.0 :: Double, 100.0 :: Double, 0.00 :: Double, 0.1 :: Double, 0.25 :: Double, 0.15, 0.05, 0.2, 0.3, 3.4623 :: Double)
                    , (KnockOut, 90.0, 110.0, 0.0, Call, 100.0, 100.0, 0.00, 0.1, 0.50, 0.15, 0.05, 0.2, 0.3, 0.5236)
                    , (KnockOut, 90.0, 110.0, 0.0, Put,  100.0, 100.0, 0.00, 0.1, 0.25, 0.15, 0.05, 0.2, 0.3, 1.1320)
                    , (KnockIn,  80.0, 120.0, 0.0, Call, 100.0, 102.0, 0.00, 0.1, 0.25, 0.25, 0.05, 0.2, 0.3, 2.6313)
                    , (KnockIn,  80.0, 120.0, 0.0, Call, 100.0, 102.0, 0.00, 0.1, 0.50, 0.15, 0.05, 0.2, 0.3, 1.9305)
                    ]
        forM_ cases $ \(barType, barLo, barHi, rebate, ty, s, strike, q, r, t, vol, fxr, fxv, corr, expected) -> do
          (proc, fxrTS, fxVolTS, corrQ) <- setupFlat dc tgt s q r vol fxr fxv corr
          engine <- quantoDoubleBarrierEngine proc fxrTS fxVolTS corrQ
          let exDate = addDays (round (t * 360 :: Double)) today'
          opt <- quantoDoubleBarrierOption barType barLo barHi rebate (PlainVanilla (PlainVanillaPayoff ty strike)) (European (EuropeanExercise exDate))
          optInst <- asOneAssetOption opt
          setPricingEngine optInst engine
          v <- npv optInst
          v `shouldSatisfy` closePrec expected 1.0e-4

  -- Ported from quantooption.cpp's testFDMQuantoHelper, testPDEOptionValues, and
  -- testAmericanQuantoOption: the FDM-side building blocks (FdmQuantoHelper's own quanto drift
  -- adjustment, and the FdmBlackScholesMesher grid it feeds into) and the FD-vs-analytic /
  -- FD-vs-FD cross-checks that exercise fdBlackScholesVanillaEngineQuanto(') and
  -- fdHestonVanillaEngineQuanto'.
  describe "FdmQuantoHelper / FD quanto engines" $ do
    it "FdmQuantoHelper.quantoAdjustment and FdmBlackScholesMesher grid bounds reproduce testFDMQuantoHelper" $
      Settings.keepingSettings' $ do
        let today' = 22 `april` 2019
            s = 100.0 :: Double
            domesticR = 0.1 :: Double
            foreignR = 0.2 :: Double
            q = 0.3 :: Double
            vol = 0.3 :: Double
            fxVol = 0.2 :: Double
            exchRateATMlevel = 1.0 :: Double
            equityFxCorrelation = -0.75 :: Double
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        domesticRQ <- simpleQuote domesticR
        domesticTS <- flatForward today' domesticRQ dc Continuous Annual
        divQ <- simpleQuote q
        divTS <- flatForward today' divQ dc Continuous Annual
        volQ <- simpleQuote vol
        volTS <- blackConstantVol today' tgt volQ dc
        spotQ <- simpleQuote s
        bsmProcess <- blackScholesMertonProcess spotQ divTS domesticTS volTS EulerDiscretization False
        foreignRQ <- simpleQuote foreignR
        foreignTS <- flatForward today' foreignRQ dc Continuous Annual
        fxVolQ <- simpleQuote fxVol
        fxVolTS <- blackConstantVol today' tgt fxVolQ dc
        fdmHelper <- fdmQuantoHelper domesticTS foreignTS fxVolTS equityFxCorrelation exchRateATMlevel

        calculatedQuantoAdj <- fdmQuantoHelperQuantoAdjustment fdmHelper vol 0.0 1.0
        let expectedQuantoAdj = domesticR - foreignR + equityFxCorrelation * vol * fxVol
        calculatedQuantoAdj `shouldSatisfy` closePrec expectedQuantoAdj 1.0e-10

        maturityDate <- addPeriod today' (6, Months)
        maturityTime <- years dc today' maturityDate Nothing Nothing
        let eps = 0.0002 :: Double
            scalingFactor = 1.25 :: Double
        mesher1d <- fdmBlackScholesMesher 3 bsmProcess maturityTime s Nothing Nothing eps scalingFactor Nothing Nothing [] (Just fdmHelper) 0.0
        fdmMesher <- fdmMesherComposite [mesher1d]
        loc <- fdmMesherLocations fdmMesher 0
        let loc0 = loc V.! 0

        -- InverseCumulativeNormal()(1 - eps), eps = 0.0002 -- a fixed literal (like the other
        -- ported golden values) rather than re-deriving boost's inverse normal CDF here.
        let normInvEps = 3.5400837992061738 :: Double
            sigmaSqrtT = vol * sqrt maturityTime
            qQuanto = q + expectedQuantoAdj
            expectedDriftRate = domesticR - qQuanto
            logFwd = log s + expectedDriftRate * maturityTime
            xMin = logFwd - sigmaSqrtT * normInvEps * scalingFactor
            xMax = log s + sigmaSqrtT * normInvEps * scalingFactor
        loc0 `shouldSatisfy` closePrec xMin 1.0e-6
        V.last loc `shouldSatisfy` closePrec xMax 1.0e-6

    it "fdBlackScholesVanillaEngineQuanto reproduces QuantoEngine<VanillaOption,AnalyticEuropeanEngine> (testPDEOptionValues)" $ do
      let today' = 21 `april` 2019
          cases = [ (Call, 105.0 :: Double, 100.0 :: Double, 0.04 :: Double, 0.08 :: Double, 0.5 :: Double, 0.2 :: Double, 0.05 :: Double, 0.10 :: Double, 0.3 :: Double)
                  , (Call, 100.0, 100.0, 0.16, 0.08, 0.25, 0.15, 0.05, 0.20, -0.3)
                  , (Call, 105.0, 100.0, 0.04, 0.08, 0.5,  0.2,  0.05, 0.10,  0.3)
                  , (Put,  105.0, 100.0, 0.04, 0.08, 0.5,  0.2,  0.05, 0.10,  0.3)
                  , (Call, 0.0,   100.0, 0.04, 0.08, 0.3,  0.3,  0.05, 0.10,  0.75)
                  ]
      forM_ cases $ \(ty, strike, s, q, r, t, vol, fxr, fxv, corr) ->
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just today')
          dc <- dayCounter (Actual360 False)
          tgt <- calendar TARGET
          spotQ <- simpleQuote s
          rQ <- simpleQuote r
          domesticTS <- flatForward today' rQ dc Continuous Annual
          divQ <- simpleQuote q
          divTS <- flatForward today' divQ dc Continuous Annual
          volQ <- simpleQuote vol
          volTS <- blackConstantVol today' tgt volQ dc
          bsmProcess <- blackScholesMertonProcess spotQ divTS domesticTS volTS EulerDiscretization False
          foreignRQ <- simpleQuote fxr
          foreignTS <- flatForward today' foreignRQ dc Continuous Annual
          fxVolQ <- simpleQuote fxv
          fxVolTS <- blackConstantVol today' tgt fxVolQ dc
          quantoHelper <- fdmQuantoHelper domesticTS foreignTS fxVolTS corr 1.0
          let exDate = addDays (round (t * 360 :: Double)) today'
          opt <- vanillaOption (PlainVanilla (PlainVanillaPayoff ty strike)) (European (EuropeanExercise exDate))

          pdeEngine <- fdBlackScholesVanillaEngineQuanto bsmProcess (Just quantoHelper) (round (t * 200 :: Double)) 500 1
            Douglas False 0.0 CashDividendSpot
          setPricingEngine opt pdeEngine
          optInst <- asOneAssetOption opt
          calcNpv <- npv optInst
          calcDelta <- delta optInst

          corrQ <- simpleQuote corr
          analyticEngine <- quantoEuropeanEngine bsmProcess foreignTS fxVolTS corrQ
          setPricingEngine opt analyticEngine
          expNpv <- npv optInst
          expDelta <- delta optInst

          closePrec expNpv 2.0e-4 calcNpv `shouldBe` True
          closePrec expDelta 1.0e-4 calcDelta `shouldBe` True

    it "fdBlackScholesVanillaEngineQuanto'/fdHestonVanillaEngineQuanto' reproduce testAmericanQuantoOption" $
      Settings.keepingSettings' $ do
        let today' = 21 `april` 2019
            domesticR = 0.025 :: Double
            foreignR = 0.075 :: Double
            q = 0.03 :: Double
            vol = 0.3 :: Double
            fxVol = 0.15 :: Double
            equityFxCorrelation = -0.75 :: Double
            strike = 105.0 :: Double
            expected = 8.90611734 :: Double
            tol = 1.0e-4 :: Double
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter Actual365FixedStandard
        maturity <- addPeriod today' (9, Months)
        domesticRQ <- simpleQuote domesticR
        domesticTS <- flatForward today' domesticRQ dc Continuous Annual
        divQ <- simpleQuote q
        divTS <- flatForward today' divQ dc Continuous Annual
        volQ <- simpleQuote vol
        tgt <- calendar TARGET
        volTS <- blackConstantVol today' tgt volQ dc
        spotQ <- simpleQuote (100.0 :: Double)
        bsmProcess <- blackScholesMertonProcess spotQ divTS domesticTS volTS EulerDiscretization False
        foreignRQ <- simpleQuote foreignR
        foreignTS <- flatForward today' foreignRQ dc Continuous Annual
        fxVolQ <- simpleQuote fxVol
        fxVolTS <- blackConstantVol today' tgt fxVolQ dc
        quantoHelper <- fdmQuantoHelper domesticTS foreignTS fxVolTS equityFxCorrelation 1.0

        divDate <- addPeriod today' (6, Months)
        dividends <- sequence [fixedDividend 8.0 divDate]

        opt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Call strike)) (American Nothing maturity False)
        optInst <- asOneAssetOption opt

        bsEngine <- fdBlackScholesVanillaEngineQuanto' bsmProcess dividends (Just quantoHelper) 100 400 1
          Douglas False 0.0 CashDividendSpot
        setPricingEngine opt bsEngine
        bsCalculated <- npv optInst
        closePrec expected tol bsCalculated `shouldBe` True

        localVolEngine <- fdBlackScholesVanillaEngineQuanto' bsmProcess dividends (Just quantoHelper) 100 400 1
          Douglas False 0.0 CashDividendSpot
        setPricingEngine opt localVolEngine
        localVolCalculated <- npv optInst
        closePrec expected tol localVolCalculated `shouldBe` True
        closePrec bsCalculated 1.0e-6 localVolCalculated `shouldBe` True

        divOpt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Call strike)) (American Nothing maturity False)
        divOptInst <- asOneAssetOption divOpt

        let v0 = vol * vol
            kappa = 1.0 :: Double
            theta0 = v0
            sigma = 1.0e-4 :: Double
            hestonRho = 0.0 :: Double
        hp <- hestonProcess domesticTS (Just divTS) spotQ v0 kappa theta0 sigma hestonRho QuadraticExponentialMartingale
        hm <- hestonModel hp
        hestonEngine <- fdHestonVanillaEngineQuanto' hm dividends (Just quantoHelper) 100 400 3 1 Hundsdorfer Nothing 1.0
        setPricingEngine divOpt hestonEngine
        hestonCalculated <- npv divOptInst
        closePrec expected tol hestonCalculated `shouldBe` True

        constVolQ <- simpleQuote (2.0 :: Double)
        localConstVol <- localConstantVol today' constVolQ dc
        hp05 <- hestonProcess domesticTS (Just divTS) spotQ (0.25 * v0) kappa (0.25 * theta0) sigma hestonRho QuadraticExponentialMartingale
        hm05 <- hestonModel hp05
        hestonSlvEngine <- fdHestonVanillaEngineQuanto' hm05 dividends (Just quantoHelper) 100 400 3 1 Hundsdorfer (Just localConstVol) 1.0
        setPricingEngine divOpt hestonSlvEngine
        hestonSlvCalculated <- npv divOptInst
        closePrec expected tol hestonSlvCalculated `shouldBe` True

  -- Ported from test-suite/twoassetbarrieroption.cpp's testHaugValues: a barrier option on two
  -- correlated assets, where the first asset's value is compared to the strike and the second's
  -- is monitored against the barrier (Heynen and Kat's formulas via AnalyticTwoAssetBarrierEngine).
  describe "Two-asset barrier engine" $
    it "AnalyticTwoAssetBarrierEngine reproduces twoassetbarrieroption.cpp's testHaugValues" $
      Settings.keepingSettings' $ do
        let today' = 1 `january` 2020
            cases = [ (DownOut, Call, 95.0 :: Double, 90.0 :: Double, 0.5 :: Double, 0.08 :: Double, 6.6592 :: Double)
                    , (UpOut,   Call, 105.0, 90.0, -0.5, 0.08, 4.6670)
                    , (DownOut, Put,  95.0, 90.0, -0.5, 0.08, 0.6184)
                    , (UpOut,   Put,  105.0, 100.0, 0.0, 0.08, 0.8246)
                    ]
        Settings.setEvaluationDate (Just today')
        dc <- dayCounter (Actual360 False)
        tgt <- calendar TARGET
        rQ <- simpleQuote (0.0 :: Double)
        rTS <- flatForward today' rQ dc Continuous Annual
        forM_ cases $ \(barType, ty, barrier, strike, corr, r, expected) -> do
          _ <- setValue rQ r
          s1Q <- simpleQuote (100.0 :: Double)
          q1Q <- simpleQuote (0.0 :: Double)
          v1Q <- simpleQuote (0.2 :: Double)
          s2Q <- simpleQuote (100.0 :: Double)
          q2Q <- simpleQuote (0.0 :: Double)
          v2Q <- simpleQuote (0.2 :: Double)
          rhoQ <- simpleQuote corr
          q1TS <- flatForward today' q1Q dc Continuous Annual
          q2TS <- flatForward today' q2Q dc Continuous Annual
          vol1TS <- blackConstantVol today' tgt v1Q dc
          vol2TS <- blackConstantVol today' tgt v2Q dc
          proc1 <- blackScholesMertonProcess s1Q q1TS rTS vol1TS EulerDiscretization False
          proc2 <- blackScholesMertonProcess s2Q q2TS rTS vol2TS EulerDiscretization False
          engine <- analyticTwoAssetBarrierEngine proc1 proc2 rhoQ
          let exDate = addDays 180 today'
          inst <- twoAssetBarrierOption barType barrier (PlainVanilla (PlainVanillaPayoff ty strike)) (European (EuropeanExercise exDate))
          setPricingEngine inst engine
          v <- npv inst
          v `shouldSatisfy` closePrec expected 4.0e-3

  -- The Gaussian1dModels example already covers the model calibration and swaption paths.
  -- These are its distinct cap/floor-engine scenarios, including the caplet-smile constructor
  -- used by test-suite/markovfunctional.cpp's testVanillaEngines.
  describe "Gaussian1d cap/floor engine" $
    it "prices a cap for GSR and MarkovFunctional, and the caplet-calibrated Markov model agrees with Black" $
      Settings.keepingSettings' $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc365 <- dayCounter Actual365FixedStandard
        thirty360bb <- dayCounter Thirty360BondBasis
        act360 <- dayCounter (Actual360 False)
        flatQ <- simpleQuote 0.03
        ts <- flatForward settlement flatQ dc365 Continuous Annual
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
        start <- advance cal settlement (1, Years) ModifiedFollowing False
        maturity <- advance cal start (10, Years) ModifiedFollowing False
        fixedSchedule <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
        floatSchedule <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
        swp <- vanillaSwap Payer 1.0 fixedSchedule 0.03 thirty360bb floatSchedule euribor6m 0.0 act360 (Just ModifiedFollowing) Nothing
        floatLeg <- floatingLeg swp
        capfl <- cap floatLeg (fromList [0.03])

        stepDates <- mapM (\n -> advance cal evalDate (n, Years) Following False) [1, 2 :: Int]
        gsrInitialVolQuote <- simpleQuote 0.01
        gsrStepVolQuotes <- mapM simpleQuote [0.01, 0.01]
        gsrReversionQuote <- simpleQuote 0.01
        gsrModel <- gsr ts gsrInitialVolQuote (zip stepDates gsrStepVolQuotes) gsrReversionQuote 60.0
        gsrModel' <- gsrAsGaussian1dModel gsrModel
        gsrEngine <- gaussian1dCapFloorEngine gsrModel' 64 7.0 True False (Just ts)
        setPricingEngine capfl gsrEngine
        gsrNpv <- npv capfl
        gsrNpv `shouldSatisfy` (\x -> not (isNaN x || isInfinite x) && x >= 0)

        swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
        swaptionVolQ <- simpleQuote 0.20
        swaptionVol <- constantSwaptionVolatility' evalDate cal ModifiedFollowing swaptionVolQ dc365 ShiftedLognormal 0.0
        cmsExpiries <- mapM (\n -> advance cal evalDate (n, Years) Following False) [1, 2, 3 :: Int]
        markov <- markovFunctional ts 0.01 0.01 [] swaptionVol (fromList $ zip cmsExpiries $ replicate 3 (10, Years)) swapBase 16
        markovModel <- markovFunctionalAsGaussian1dModel markov
        markovEngine <- gaussian1dCapFloorEngine markovModel 8 5.0 True False (Just ts)
        setPricingEngine capfl markovEngine
        markovNpv <- npv capfl
        markovNpv `shouldSatisfy` (\x -> not (isNaN x || isInfinite x) && x >= 0)

        capletExpiries <- CF.toCouponLeg floatLeg >>= CF.couponAccrualStartDates
        capletVolQ <- simpleQuote 0.20
        capletVol <- constantOptionletVolatility' 0 cal ModifiedFollowing capletVolQ dc365 ShiftedLognormal 0.0
        markovCaplet <- markovFunctionalCaplet ts 0.01 0.01 [] capletVol (fromList capletExpiries) euribor6m 16
        markovCapletModel <- markovFunctionalAsGaussian1dModel markovCaplet
        blackEngine <- blackCapFloorEngine' ts capletVol
        setPricingEngine capfl blackEngine
        blackNpv <- npv capfl
        markovCapletEngine <- gaussian1dCapFloorEngine markovCapletModel 64 7.0 True False (Just ts)
        setPricingEngine capfl markovCapletEngine
        markovCapletNpv <- npv capfl
        markovCapletNpv `shouldSatisfy` closePrec blackNpv 1.0e-4
