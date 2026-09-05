-- | Coverage for model-level self-consistency/golden-value checks that don't fit naturally
-- under 'QuantLib.Instrument' or 'QuantLib.PricingEngine' -- 'HestonModel'/'HestonProcess' and
-- 'BatesModel'/'BatesProcess' against a closed-form Black price, and
-- 'GJRGARCHModel'/'GJRGARCHProcess' analytic vs. Monte Carlo. Ported from QuantLib's own
-- test-suite/hestonmodel.cpp::testAnalyticVsBlack, test-suite/batesmodel.cpp::testAnalyticVsBlack
-- (its 'BatesEngine'/plain-'BatesModel' case only -- 'BatesDetJumpModel'/'BatesDoubleExpModel'/
-- 'BatesDoubleExpDetJumpModel' have no hasquant constructor, only their pointer types and
-- engines are bound), test-suite/gjrgarchmodel.cpp::testEngines (a small representative
-- subset of the latter's 3x2x6 case table, to keep the MC engine's runtime reasonable), and a
-- self-consistency check (not upstream's cached NPV, see that describe block's own comment) built
-- around test-suite/libormarketmodel.cpp::testCapletPricing's fixture shape.
--
-- G2Process/G2ForwardProcess bind @phi@/@shortRate@/@factors@ (test-suite/g2process.cpp),
-- 'QuantLib.Process' now also binds generic @drift@\/@diffusion@\/@expectation@\/@initialValues@
-- on 'QuantLib.Process.StochasticProcess', and HullWhiteForwardProcess binds the required
-- post-construction @setForwardMeasureTime@ call -- see this module's "G2Process"/
-- "G2ForwardProcess" and "HybridHestonHullWhiteProcess" describe blocks below. 'QuantLib.Model'
-- also binds 'G2'\'s @dynamics()@ (as 'g2Dynamics', returning the new 'ShortRateDynamics' type)
-- and its @shortRate@ method, closing the last holdout -- all 8 of upstream's g2process.cpp
-- cases are now ported. Of test-suite/hybridhestonhullwhiteprocess.cpp's 10 cases,
-- 'testAnalyticHestonHullWhitePricing' is ported here (an MC-vs-analytic cross-check with the
-- short-rate leg decorrelated) and 'testZeroBondPricing' as
-- "QuantLib.Example.HestonHullWhiteMC"; the rest still need bindings this module doesn't have
-- (a bound 'FdmHestonHullWhiteVanillaEngine', ...) and are left as a further follow-up.
-- 'QuantLib.Process.hybridHestonHullWhiteNumeraire' and the Hull-White process getters
-- ('hullWhiteAlpha'\/'hullWhiteForwardAlpha'\/'hullWhiteForwardB'\/'hullWhiteForwardM') are
-- checked here against closed forms, and 'stdDeviation'\/'covariance'\/'apply'\/'evolve'
-- against each other on 'g2Process'.
{-# LANGUAGE TupleSections #-}
module QuantLib.Spec.Process (spec) where

import Test.Hspec
import qualified Data.Vector.Storable as V
import Data.Time.Calendar(addDays)
import Data.List.NonEmpty(fromList)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date(today, addPeriod, september)
import QuantLib.Time.Schedule(dayCounter, years, DayCounterConstructor(..), Frequency(..), TimeUnit(..))
import QuantLib.InterestRate(Compounding(..), VolatilityType(..), rate)
import QuantLib.Quote(simpleQuote, setValue)
import QuantLib.TermStructure.Yield(flatForward, forwardRate, discount, YieldTermStructure, interpolatedZeroCurve)
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Option(europeanOption, StrikedPayoff(PlainVanilla), PlainVanillaPayoff(..), OptionType(..), Exercise(European), EuropeanExercise(..))
import QuantLib.Process(hestonProcess, hestonProcessPdf, batesProcess, gjrGARCHProcess, HestonProcessDiscretization(..), GJRGARCHProcessDiscretization(..)
 , g2Process, g2ForwardProcess, g2Phi, g2ShortRate, g2ForwardPhi, g2ForwardShortRate, setG2ForwardMeasureTime, factors, drift, diffusion, expectation, initialValues, hullWhiteProcess, hullWhiteForwardProcess, setForwardMeasureTime, hybridHestonHullWhiteProcess, HybridHestonHullWhiteProcessDiscretization(..)
 , liborForwardModelProcess, liborForwardModelProcessFixingDates, liborForwardModelProcessFixingTimes, liborForwardModelProcessCashFlows
 , liborForwardModelProcessDiscountBond, liborForwardModelProcessAccrualTimes
 , hybridHestonHullWhiteNumeraire, hullWhiteAlpha, hullWhiteForwardAlpha, hullWhiteForwardB, hullWhiteForwardM
 , stdDeviation, covariance, apply, evolve)
import QuantLib.Model(hullWhite, g2, g2Dynamics, shortRate
 , hestonModel, batesModel, gJRGARCHModel
 , liborForwardModel, liborForwardModelS0, liborForwardModelAsAffineModel, lfmHullWhiteParameterization, lfmHullWhiteCovariance, setCovarParam, LmVolatilityModel(..), LmCorrelationModel(..)
 , discountBond)
import QuantLib.PricingEngine(analyticHestonHullWhiteEngine, mcHestonHullWhiteEngine
 , analyticHestonEngine', batesEngine, analyticGJRGARCHEngine, mcEuropeanGJRGARCHEngine, blackFormula, analyticCapFloorEngine)
import QuantLib.Method(pathGenerator, next, asset)
import QuantLib.Math(RngTrait(..), StatisticsTrait(..), timeGrid, Interpolation(..), boxedRealMatrix, realMatrixFromVector, matrixRows, matrixColumns, matrixData, realMatrixData)
import Control.Monad(replicateM, zipWithM_)
import QuantLib.Instrument.CapFloor(cap)
import QuantLib.Time.Calendar(adjust, advance, calendar, BusinessDayConvention(..), CalendarConstructor(..))
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import qualified QuantLib.Index.InterestRate as Ibor(fixingDays)
import qualified QuantLib.TermStructure.Volatility as Vol(capletVarianceCurve)

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = do
  describe "matrix construction" $ do
    it "accepts matching boxed and contiguous shapes, including an empty matrix" $ do
      fmap matrixData (boxedRealMatrix 2 2 [1, 2, 3, 4]) `shouldBe` Right [1, 2, 3, 4]
      fmap realMatrixData (realMatrixFromVector 0 0 V.empty) `shouldBe` Right V.empty
    it "rejects mismatched and overflowed shapes" $ do
      boxedRealMatrix 2 2 [1, 2, 3] `shouldBe` Left "Data length 3 does not match dimensions 2x2"
      realMatrixFromVector 2 2 (V.fromList [1, 2, 3]) `shouldBe` Left "Data length 3 does not match dimensions 2x2"
      case boxedRealMatrix (maxBound `div` 2 + 1) 2 [] of
        Left _ -> pure ()
        Right _ -> expectationFailure "overflowed dimensions accepted an empty matrix"

  describe "HestonModel (AnalyticHestonEngine vs. Black formula)" $ do
    -- cached reference from test-suite/hestonmodel.cpp::testAnalyticVsBlack: a near-zero
    -- vol-of-vol Heston process (sigma=1e-4) should reproduce the flat-vol Black price almost
    -- exactly.
    it "reproduces the Black price at near-zero vol-of-vol" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter ActualActualISDA
        let strike = 30.0
            spot = 32.0
            r = 0.1
            q = 0.04
            v0 = 0.05
        rQ <- simpleQuote r
        qQ <- simpleQuote q
        rTS <- flatForward evalDate rQ dc Continuous Annual
        qTS <- flatForward evalDate qQ dc Continuous Annual
        s0 <- simpleQuote spot
        process <- hestonProcess rTS (Just qTS) s0 v0 5.0 0.05 1.0e-4 0.0 QuadraticExponentialMartingale
        model <- hestonModel process
        eng <- analyticHestonEngine' model 144
        exerciseDate <- addPeriod evalDate (6, Months)
        opt <- europeanOption (PlainVanilla (PlainVanillaPayoff Put strike)) (European (EuropeanExercise exerciseDate))
        setPricingEngine opt eng
        calculated <- npv opt

        -- the *exact* year fraction the process's own date-based discounting uses for this
        -- exercise date -- matches test-suite/hestonmodel.cpp::testAnalyticVsBlack exactly now
        -- that 'years' (DayCounter::yearFraction) is bound, rather than a hand-picked t=0.5
        -- reconciled against a day-rounded exercise date.
        t <- years dc evalDate exerciseDate Nothing Nothing
        let forwardPrice = spot * exp ((r - q) * t)
        expected <- blackFormula Put strike forwardPrice (sqrt (v0 * t)) (exp (-r * t)) 0.0
        calculated `shouldSatisfy` closePrec expected 2.0e-7

    it "pdf(x, v, t) decays away from the peak near (log forward, v0)" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter ActualActualISDA
        let spot = 100.0
            r = 0.03
            q = 0.01
            v0 = 0.04
            -- t = 0.5 (the original choice) lands HestonProcess::pdf's Cornish-Fisher upper-bound
            -- estimate (ql/processes/hestonprocess.cpp: cornishFisherEps, a 4th-order finite
            -- difference of the CIR characteristic function divided by d^4 = 1e-8) in a
            -- numerically fragile spot: reproduced in raw C++ against the installed QuantLib, it
            -- returns NaN there on Linux/gcc and Windows but a plausible value on macOS/clang --
            -- an upstream platform-sensitivity, not a hasquant binding bug. t = 1.0 sits on a
            -- stable plateau confirmed by a parameter sweep across both platforms.
            t = 1.0
        rQ <- simpleQuote r
        qQ <- simpleQuote q
        rTS <- flatForward evalDate rQ dc Continuous Annual
        qTS <- flatForward evalDate qQ dc Continuous Annual
        s0 <- simpleQuote spot
        process <- hestonProcess rTS (Just qTS) s0 v0 1.5 0.04 0.3 (-0.5) QuadraticExponentialMartingale
        -- Approximate mean log-price at t (Ito correction for the log transform); the process's
        -- exact drift isn't bound, but this is close enough to sit near the density's peak for a
        -- "decays away from it" check.
        let x0 = log spot + (r - q - 0.5 * v0) * t
        atPeak <- hestonProcessPdf process x0 v0 t 1e-8
        -- The density well away from the peak, in v or in x, must be markedly smaller than at
        -- the peak.
        farInV <- hestonProcessPdf process x0 (v0 * 6) t 1e-8
        farInX <- hestonProcessPdf process (x0 + 4 * sqrt (v0 * t)) v0 t 1e-8
        atPeak `shouldSatisfy` (> 0)
        atPeak `shouldSatisfy` (> farInV)
        atPeak `shouldSatisfy` (> farInX)

  describe "BatesModel (BatesEngine vs. Black formula)" $
    -- cached reference from test-suite/batesmodel.cpp::testAnalyticVsBlack: same near-zero
    -- vol-of-vol setup as the Heston case above, plus a near-zero jump intensity/size so the
    -- Bates (Heston-plus-jumps) price should likewise reproduce the flat-vol Black price.
    it "reproduces the Black price at near-zero vol-of-vol and jump intensity" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter ActualActualISDA
        let strike = 30.0
            spot = 32.0
            r = 0.1
            q = 0.04
            v0 = 0.05
        rQ <- simpleQuote r
        qQ <- simpleQuote q
        rTS <- flatForward evalDate rQ dc Continuous Annual
        qTS <- flatForward evalDate qQ dc Continuous Annual
        s0 <- simpleQuote spot
        process <- batesProcess rTS qTS s0 v0 5.0 0.05 1.0e-4 0.0 0.0001 0.0 0.0001 QuadraticExponentialMartingale
        model <- batesModel process
        eng <- batesEngine model 64
        exerciseDate <- addPeriod evalDate (6, Months)
        opt <- europeanOption (PlainVanilla (PlainVanillaPayoff Put strike)) (European (EuropeanExercise exerciseDate))
        setPricingEngine opt eng
        calculated <- npv opt

        t <- years dc evalDate exerciseDate Nothing Nothing
        let forwardPrice = spot * exp ((r - q) * t)
        expected <- blackFormula Put strike forwardPrice (sqrt (v0 * t)) (exp (-r * t)) 0.0
        calculated `shouldSatisfy` closePrec expected 2.0e-7

  describe "GJRGARCHModel (AnalyticGJRGARCHEngine vs. MCEuropeanGJRGARCHEngine)" $
    -- cached references from test-suite/gjrgarchmodel.cpp::testEngines: a 2-of-36-case subset
    -- (lambda=0, maturity=90 days, strikes 35/50) of the full 3x2x6 table, checked against both
    -- upstream's own cached analytic and Monte Carlo values, at upstream's own tolerance.
    mapM_ (\(strike, analyticExpected, mcExpected) ->
      it ("matches upstream's cached analytic/MC values at strike=" ++ show strike) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          dc <- dayCounter ActualActualISDA
          rTS <- simpleQuote 0.05 >>= \rQ -> flatForward evalDate rQ dc Continuous Annual
          qTS <- simpleQuote 0.0 >>= \qQ -> flatForward evalDate qQ dc Continuous Annual
          s0 <- simpleQuote 50.0
          let omega = 2.0e-6; alpha = 0.024; beta = 0.93; gamma = 0.059; lambda = 0.0
              daysPerYear = 365.0
              -- m1/v0 per upstream's own GJR-GARCH stationary-variance formula
              cumNorm x = 0.5 * (1 + erf (x / sqrt 2))
              m1 = beta + (alpha + gamma * cumNorm lambda) * (1 + lambda * lambda)
                     + gamma * lambda * exp (-lambda * lambda / 2) / sqrt (2 * pi)
              v0 = omega / (1 - m1)
          process <- gjrGARCHProcess rTS qTS s0 v0 omega alpha beta gamma lambda daysPerYear GJRGARCHFullTruncation
          model <- gJRGARCHModel process
          analyticEng <- analyticGJRGARCHEngine model
          mcEng <- mcEuropeanGJRGARCHEngine PseudoRandom Statistics process Nothing (Just 20) False Nothing (Just 0.02) Nothing 1234
          let exerciseDate = addDays 90 evalDate
          optA <- europeanOption (PlainVanilla (PlainVanillaPayoff Call strike)) (European (EuropeanExercise exerciseDate))
          setPricingEngine optA analyticEng
          analyticNpv <- npv optA
          analyticNpv `shouldSatisfy` closePrec analyticExpected 0.15

          optM <- europeanOption (PlainVanilla (PlainVanillaPayoff Call strike)) (European (EuropeanExercise exerciseDate))
          setPricingEngine optM mcEng
          mcNpv <- npv optM
          mcNpv `shouldSatisfy` closePrec mcExpected 0.15)
      [ (35.0 :: Double, 15.4315 :: Double, 15.4332 :: Double)
      , (50.0, 2.3282, 2.3521)
      ]

  describe "LiborForwardModelProcess (LfmHullWhiteParameterization caplet pricing)" $ do
    -- Exact port of test-suite/libormarketmodel.cpp::makeIndex, makeCapVolCurve and
    -- testCapletPricing. The upstream test widens its tolerance to 1e-5 when index-fixing
    -- coupons are enabled; hasquant does not expose that global IborCoupon setting, so use the
    -- portable branch's tolerance for the shared cached value.
    it "reproduces libormarketmodel.cpp's cached cap NPV" $
      Settings.keepingSettings' $ do
        let fixtureDate = 4 `september` 2005
            curveEndDate = 4 `september` 2018
            size = 10 :: Word
            capletVols = [0.1440, 0.1715, 0.1681, 0.1664, 0.1617, 0.1578, 0.1540, 0.1521, 0.1486]
        cal <- calendar TARGET
        evalDate <- adjust cal fixtureDate Following
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        emptyIndex <- iborIndex Euribor6M Nothing
        firstPillar <- advance cal evalDate (fromIntegral (Ibor.fixingDays emptyIndex), Days) Following False
        rTS <- interpolatedZeroCurve (fromList [(firstPillar, 0.039), (curveEndDate, 0.041)]) dc cal [] Linear
        idx <- iborIndex Euribor6M (Just rTS)
        process <- liborForwardModelProcess size idx
        fixingDates <- liborForwardModelProcessFixingDates process
        fixingTimes <- liborForwardModelProcessFixingTimes process
        capletVol <- Vol.capletVarianceCurve evalDate (fromList $ zip (take 9 $ drop 1 fixingDates) capletVols) dc ShiftedLognormal 0.0
        let emptyCorrelation = either error id $ boxedRealMatrix 0 0 []
        parameterization <- lfmHullWhiteParameterization process capletVol emptyCorrelation 1
        covar <- lfmHullWhiteCovariance parameterization 0.0 []
        matrixRows covar `shouldBe` size
        matrixColumns covar `shouldBe` size
        let covarianceData = matrixData covar
            variances = [covarianceData !! (i * fromIntegral size + i) | i <- [0 .. fromIntegral size - 1]]
        leg <- liborForwardModelProcessCashFlows process 1.0
        model <- liborForwardModel process (FixedVolatility (fromList $ zip fixingTimes (map sqrt variances))) (ExponentialCorrelation size 0.3)
        -- S_0(alpha, beta) is an annuity-weighted average of the initial forward rates
        -- f[alpha+1 .. beta] (LiborForwardModel::S_0 in liborforwardmodel.cpp), so it must lie
        -- within their range.
        x0 <- initialValues process
        s0 <- liborForwardModelS0 model 0 (size - 1)
        let fwds = drop 1 x0
        s0 `shouldSatisfy` (>= minimum fwds - 1e-12)
        s0 `shouldSatisfy` (<= maximum fwds + 1e-12)
        affineModel <- liborForwardModelAsAffineModel model
        eng <- analyticCapFloorEngine affineModel (Just rTS)
        capInstr <- cap leg (fromList $ replicate (fromIntegral size) 0.04)
        setPricingEngine capInstr eng
        capNpv <- npv capInstr
        capNpv `shouldSatisfy` closePrec 0.015853935178 1.0e-5

    -- discountBond compounds along the accrual grid: element i discounts from the end of
    -- period i back to the start, so it is the running product of the one-period factors, not
    -- the factors themselves. Also covers 'setCovarParam', without which the process holds no
    -- covariance parameterization and drift/diffusion/factors dereference a null pointer.
    it "discountBond is the running product of its accrual-period discount factors" $
      Settings.keepingSettings' $ do
        let fixtureDate = 4 `september` 2005
            curveEndDate = 4 `september` 2018
            size = 10 :: Word
        cal <- calendar TARGET
        evalDate <- adjust cal fixtureDate Following
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        emptyIndex <- iborIndex Euribor6M Nothing
        firstPillar <- advance cal evalDate (fromIntegral (Ibor.fixingDays emptyIndex), Days) Following False
        rTS <- interpolatedZeroCurve (fromList [(firstPillar, 0.039), (curveEndDate, 0.041)]) dc cal [] Linear
        idx <- iborIndex Euribor6M (Just rTS)
        process <- liborForwardModelProcess size idx

        accruals <- liborForwardModelProcessAccrualTimes process
        length accruals `shouldBe` fromIntegral size
        all (\(st, en) -> en > st) accruals `shouldBe` True

        let rates = [0.03 + 0.002 * fromIntegral i | i <- [0 .. fromIntegral size - 1 :: Int]]
            expected = scanl1 (*) (zipWith (\r (st, en) -> 1 / (1 + r * (en - st))) rates accruals)
        dfs <- liborForwardModelProcessDiscountBond process rates
        zipWithM_ (\c e -> c `shouldSatisfy` closePrec e 1.0e-12) dfs expected

        -- the process is only simulable once a covariance parameterization is installed
        fixingDates <- liborForwardModelProcessFixingDates process
        capletVol <- Vol.capletVarianceCurve evalDate (fromList (map (, 0.15) (take 9 (drop 1 fixingDates)))) dc ShiftedLognormal 0.0
        let emptyCorrelation = either error id $ boxedRealMatrix 0 0 []
        parameterization <- lfmHullWhiteParameterization process capletVol emptyCorrelation 1
        setCovarParam process parameterization
        factors process `shouldReturn` 1
        diff <- diffusion process 0.0 rates
        matrixRows diff `shouldBe` size

  describe "G2Process/G2ForwardProcess (phi/shortRate/factors self-consistency)" $ do
    -- ported from test-suite/g2process.cpp::testG2ProcessObservesTermStructure: under a flat
    -- curve, phi(t) is (up to the deterministic OU variance/covariance terms, which don't move)
    -- just the curve's forward rate at t -- so bumping a flat rate by 300bp must raise phi by
    -- the same 300bp.
    it "phi(t) tracks a term-structure bump one-for-one" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        rateQ <- simpleQuote 0.02
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2Process 0.1 0.01 0.2 0.013 (-0.5) (Just curve)
        let t = 2.0
        phiBefore <- g2Phi process t
        _ <- setValue rateQ 0.05
        phiAfter <- g2Phi process t
        (phiAfter - phiBefore) `shouldSatisfy` closePrec 0.03 1.0e-10

    -- ported from test-suite/g2process.cpp::testG2ForwardProcessPhiAndShortRate: shortRate(t,
    -- z1, z2) is just z1+z2 regardless of the curve (or its absence -- unlike phi, which throws
    -- with no term structure).
    it "shortRate sums the simulated components, with or without a curve" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        rateQ <- simpleQuote 0.035
        curve <- flatForward evalDate rateQ dc Continuous Annual
        fwd <- g2ForwardProcess 0.1 0.01 0.2 0.013 (-0.5) (Just curve)
        g2ForwardShortRate fwd 1.0 0.002 (-0.001) `shouldSatisfy` closePrec 0.001 1.0e-12

        paramOnly <- g2ForwardProcess 0.1 0.01 0.2 0.013 (-0.5) Nothing
        g2ForwardPhi paramOnly 1.0 `shouldThrow` anyException
        g2ForwardShortRate paramOnly 1.0 0.01 0.01 `shouldSatisfy` closePrec 0.02 1.0e-12

    -- ported from test-suite/g2process.cpp::testG2ProcessPathGeneratorMatchesCurve: the
    -- empirical mean of r(t) = state[0]+state[1] along simulated paths must converge to the
    -- curve-implied phi(t). Sample count reduced from upstream's 20000 to keep this fast (see
    -- CLAUDE.md on DiscreteHedging for the same reduction, and its tolerance scaled up by the
    -- resulting ~1/sqrt(n) increase in MC standard error).
    it "MC path mean of r(t) converges to phi(t)" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        rateQ <- simpleQuote 0.03
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2Process 0.1 0.01 0.2 0.013 (-0.3) (Just curve)
        nf <- factors process
        nf `shouldBe` 2

        let horizon = 5.0; steps = 50 :: Word; nPaths = 4000 :: Int
        tg <- timeGrid horizon steps
        pg <- pathGenerator PseudoRandom process tg 42 (nf * steps) False
        paths <- replicateM nPaths (next pg >>= \sp -> mapM (fmap V.toList . asset sp) [0, 1])
        let sumR = foldr1 (zipWith (+)) [zipWith (+) r0 r1 | [r0, r1] <- paths]
            meanR = map (/ fromIntegral nPaths) sumR
        expected <- mapM (\i -> g2Phi process (horizon * fromIntegral i / fromIntegral steps)) [0 .. steps]
        zipWithM_ (\ m e -> m `shouldSatisfy` closePrec e 1.5e-3) meanR expected

    -- ported from test-suite/g2process.cpp::testG2ProcessPhiAndShortRate (minus its x0()/y0()
    -- checks -- those OU-component getters aren't bound, per "bind few inspectors"):
    -- phi(t) must match the closed-form G2++ fitting-parameter formula directly (not just react
    -- correctly to a bump, as the first case above checks), shortRate(t, z1, z2) is just z1+z2,
    -- and initialValues sums to phi(0).
    it "phi(t) matches the closed-form G2 fitting-parameter formula" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        let a = 0.1; sigma = 0.01; b = 0.2; eta = 0.013; rho = -0.5
        rateQ <- simpleQuote 0.03
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2Process a sigma b eta rho (Just curve)

        mapM_ (\t -> do
            expected <- referencePhi curve t a sigma b eta rho
            actual <- g2Phi process t
            actual `shouldSatisfy` closePrec expected 1.0e-12)
          [0.25, 1.0, 5.0, 10.0]

        mapM_ (\(z1, z2) -> g2ShortRate process 1.0 z1 z2 `shouldSatisfy` closePrec (z1 + z2) 1.0e-12)
          [(z1, z2) | z1 <- [-0.01, 0.0, 0.005], z2 <- [-0.002, 0.0, 0.004]]

        iv <- initialValues process
        expected0 <- referencePhi curve 0.0 a sigma b eta rho
        sum iv `shouldSatisfy` closePrec expected0 1.0e-12

    -- ported from test-suite/g2process.cpp::testG2ProcessPhiMatchesG2Model: G2Process::phi
    -- must match G2's own short-rate dynamics fitting parameter -- dyn->shortRate(t, 0, 0)
    -- collapses to fitting_(t), i.e. phi(t), since shortRate(t, x, y) = fitting_(t) + x + y.
    it "phi matches the G2 model's own short-rate dynamics at x=y=0" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        let a = 0.12; sigma = 0.011; b = 0.17; eta = 0.009; rho = -0.3
        rateQ <- simpleQuote 0.025
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2Process a sigma b eta rho (Just curve)
        model <- g2 curve a sigma b eta rho
        dyn <- g2Dynamics model

        mapM_ (\t -> do
            fromModel <- shortRate dyn t 0.0 0.0
            fromProcess <- g2Phi process t
            fromProcess `shouldSatisfy` closePrec fromModel 1.0e-12)
          [0.1, 0.5, 2.0, 7.5, 20.0]

    -- ported from test-suite/g2process.cpp::testG2ProcessPhiRequiresTermStructure: without a
    -- term structure, phi throws but shortRate still works (it no longer touches the curve),
    -- and the process degenerates to two zero-mean OU factors -- initialValues is (0,0).
    it "phi throws and initialValues degenerate to (0,0) without a term structure" $ do
      process <- g2Process 0.1 0.01 0.2 0.013 (-0.5) Nothing
      g2Phi process 1.0 `shouldThrow` anyException
      g2ShortRate process 1.0 0.01 0.02 `shouldSatisfy` closePrec 0.03 1.0e-14
      iv <- initialValues process
      iv `shouldSatisfy` all ((< 1.0e-14) . abs)

    -- ported from test-suite/g2process.cpp::testG2ProcessDriftIncludesTermStructure: drift's
    -- y-component and diffusion are entirely curve-independent; drift's x-component differs
    -- from the curveless case by exactly a*phi(t) + phi'(t) (a numerical derivative, matching
    -- G2Process's own implementation), the same shift 'g2Phi' reports.
    it "drift/diffusion pick up the term-structure shift only in the x-component" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        let a = 0.1; sigma = 0.01; b = 0.2; eta = 0.013; rho = -0.5
        rateQ <- simpleQuote 0.04
        curve <- flatForward evalDate rateQ dc Continuous Annual
        paramOnly <- g2Process a sigma b eta rho Nothing
        withCurve <- g2Process a sigma b eta rho (Just curve)
        let t = 1.5; z = [0.002, -0.003]

        d10:d11:_ <- drift paramOnly t z
        d20:d21:_ <- drift withCurve t z
        d21 `shouldSatisfy` closePrec d11 1.0e-12

        let h = 1.0e-4
        phiT <- g2Phi withCurve t
        phiTh <- g2Phi withCurve (t + h)
        let expectedDelta = a * phiT + (phiTh - phiT) / h
        (d20 - d10) `shouldSatisfy` closePrec expectedDelta 1.0e-10

        diff1 <- diffusion paramOnly t z
        diff2 <- diffusion withCurve t z
        matrixData diff1 `shouldSatisfy` \xs -> and (zipWith (\x y -> closePrec y 1.0e-14 x) xs (matrixData diff2))

    -- ported from test-suite/g2process.cpp::testG2ProcessExpectationConsistentWithCurve:
    -- starting from the process's own initial state, E[z1(t)+z2(t)] must equal phi(t) --
    -- z2(0) is zero and y is a zero-mean OU factor, so the whole expected shift lands on phi.
    it "expectation from the initial state reproduces phi(t)" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        rateQ <- simpleQuote 0.035
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2Process 0.1 0.01 0.2 0.013 (-0.4) (Just curve)
        iv <- initialValues process

        mapM_ (\t -> do
            expT <- expectation process 0.0 iv t
            expected <- g2Phi process t
            sum expT `shouldSatisfy` closePrec expected 1.0e-12)
          [0.1, 0.5, 2.0, 5.0, 10.0]

    -- G2ForwardProcess's constructor leaves the inherited forward-measure time
    -- default-initialized, and only drift (via xForwardDrift/yForwardDrift) reads it -- so
    -- 'setG2ForwardMeasureTime' is required before the process is simulated. Setting T = t
    -- zeroes both corrections, which makes the difference against any other T exactly the two
    -- closed forms from g2process.cpp.
    it "setG2ForwardMeasureTime drives drift's measure correction" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        let a = 0.1; sigma = 0.01; b = 0.2; eta = 0.013; rho = -0.5
            t = 1.5; bigT = 12.0; z = [0.003, -0.001]
        rateQ <- simpleQuote 0.03
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2ForwardProcess a sigma b eta rho (Just curve)

        setG2ForwardMeasureTime process t
        baseX:baseY:_ <- drift process t z
        setG2ForwardMeasureTime process bigT
        farX:farY:_ <- drift process t z

        let expatT = exp (-a * (bigT - t))
            expbtT = exp (-b * (bigT - t))
            xFwd = -(sigma * sigma / a) * (1 - expatT) - (rho * sigma * eta / b) * (1 - expbtT)
            yFwd = -(eta * eta / b) * (1 - expbtT) - (rho * sigma * eta / a) * (1 - expatT)
        (farX - baseX) `shouldSatisfy` closePrec xFwd 1.0e-12
        (farY - baseY) `shouldSatisfy` closePrec yFwd 1.0e-12

    -- stdDeviation/covariance/apply/evolve complete the StochasticProcess interface alongside
    -- the already-bound drift/diffusion/expectation. G2Process uses the base-class
    -- implementations of all four, so these identities are the definitions themselves:
    -- covariance = stdDeviation stdDeviation^T, apply is plain addition in this state space,
    -- and evolve with a zero draw is the expectation.
    it "stdDeviation/covariance/apply/evolve agree with each other" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        rateQ <- simpleQuote 0.03
        curve <- flatForward evalDate rateQ dc Continuous Annual
        process <- g2Process 0.1 0.01 0.2 0.013 (-0.5) (Just curve)
        let t0 = 1.0; dt = 0.25; x0 = [0.004, -0.002]

        sd <- stdDeviation process t0 x0 dt
        cov <- covariance process t0 x0 dt
        matrixRows sd `shouldBe` 2
        matrixColumns sd `shouldBe` 2
        let sdData = matrixData sd
            at i j = sdData !! (i * 2 + j)
            expectedCov = [sum [at i k * at j k | k <- [0, 1]] | i <- [0, 1], j <- [0, 1]]
        zipWithM_ (\c e -> c `shouldSatisfy` closePrec e 1.0e-12) (matrixData cov) expectedCov

        applied <- apply process x0 [0.001, 0.002]
        zipWithM_ (\c e -> c `shouldSatisfy` closePrec e 1.0e-14) applied [0.005, 0.0]

        evolved <- evolve process t0 x0 dt [0.0, 0.0]
        expected <- expectation process t0 x0 dt
        zipWithM_ (\c e -> c `shouldSatisfy` closePrec e 1.0e-12) evolved expected

  describe "HybridHestonHullWhiteProcess (AnalyticHestonHullWhiteEngine vs. MCHestonHullWhiteEngine)" $ do
    -- ported from test-suite/hybridhestonhullwhiteprocess.cpp::testAnalyticHestonHullWhitePricing:
    -- with the equity/short-rate correlation set to 0, an MC price on the joint
    -- Heston/Hull-White process must reproduce the semi-analytic AnalyticHestonHullWhiteEngine
    -- price for the corresponding pure-Heston-with-Hull-White-discounting model. Uses literal
    -- a=sigma=0.01 for both the forward process and the matching HullWhite model (upstream
    -- reads them back off the forward process via a()/sigma(), which aren't bound here -- but
    -- the fixture already knows the values it constructed the process with).
    it "MC and analytic engines agree once the short-rate leg is decorrelated" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        cal <- calendar TARGET
        let yrs = [0 .. 40 :: Int]
        dates <- mapM (\i -> addPeriod evalDate (i, Years)) yrs
        let rates = [0.03 + 0.0001 * exp (sin (fromIntegral i / 4.0)) | i <- yrs]
            divRates = [0.02 + 0.0002 * exp (sin (fromIntegral i / 3.0)) | i <- yrs]
        rTS <- interpolatedZeroCurve (fromList (zip dates rates)) dc cal [] Linear
        qTS <- interpolatedZeroCurve (fromList (zip dates divRates)) dc cal [] Linear

        maturity <- addPeriod evalDate (5, Years)
        s0 <- simpleQuote 100.0
        hProcess <- hestonProcess rTS (Just qTS) s0 0.08 1.5 0.0625 0.5 (-0.8) QuadraticExponentialMartingale
        hModel <- hestonModel hProcess

        hwFwdProcess <- hullWhiteForwardProcess rTS 0.01 0.01
        maturityT <- years dc evalDate maturity Nothing Nothing
        setForwardMeasureTime hwFwdProcess maturityT
        hwModel <- hullWhite rTS 0.01 0.01
        analyticEng <- analyticHestonHullWhiteEngine hModel hwModel 128

        sequence_ [ do
            jointProcess <- hybridHestonHullWhiteProcess hProcess hwFwdProcess 0.0 HybridHestonHullWhiteEuler
            mcEng <- mcHestonHullWhiteEngine PseudoRandom Statistics jointProcess (Just 1) Nothing True True Nothing (Just 0.002) Nothing 42

            optMC <- europeanOption (PlainVanilla (PlainVanillaPayoff typ strike)) (European (EuropeanExercise maturity))
            setPricingEngine optMC mcEng
            mcNpv <- npv optMC

            optAnalytic <- europeanOption (PlainVanilla (PlainVanillaPayoff typ strike)) (European (EuropeanExercise maturity))
            setPricingEngine optAnalytic analyticEng
            analyticNpv <- npv optAnalytic

            mcNpv `shouldSatisfy` closePrec analyticNpv 1.0e-4
          | typ <- [Put, Call], strike <- [80.0, 120.0] ]

    -- 'hybridHestonHullWhiteNumeraire' is by construction P_HW(t, T, x!!2) / P(0, T) -- the
    -- same Hull-White model the process builds internally from its forward process's a/sigma
    -- and the Heston leg's risk-free curve. Rebuilding that model here and comparing is an
    -- exact identity, not an approximation, so it pins both the formula and the fact that only
    -- the third state component is read.
    it "numeraire equals the Hull-White discount bond over the curve's own P(0,T)" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        let a = 0.05; sigma = 0.01
        rateQ <- simpleQuote 0.04
        rTS <- flatForward evalDate rateQ dc Continuous Annual
        s0 <- simpleQuote 100.0
        hProcess <- hestonProcess rTS Nothing s0 0.04 1.0 0.04 0.2 (-0.5) QuadraticExponentialMartingale
        hwFwd <- hullWhiteForwardProcess rTS a sigma
        let bigT = 10.0
        setForwardMeasureTime hwFwd bigT
        joint <- hybridHestonHullWhiteProcess hProcess hwFwd (-0.4) HybridHestonHullWhiteEuler
        hwModel <- hullWhite rTS a sigma
        endDf <- discount rTS bigT False

        sequence_ [ do
            expected <- (/ endDf) <$> discountBond hwModel t bigT r
            calculated <- hybridHestonHullWhiteNumeraire joint t [100.0, 0.04, r]
            calculated `shouldSatisfy` closePrec expected 1.0e-12
          | t <- [1.0, 3.0, 7.0], r <- [0.0, 0.02, -0.01] ]

    -- at t=0 in the process's own initial state the Hull-White factor is 0, so
    -- P(0, T, 0) = P(0, T) and the numeraire collapses to 1 -- the sanity check that the
    -- division by the curve's end discount is the right way round.
    it "numeraire is 1 at time 0 in the initial state" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        rateQ <- simpleQuote 0.03
        rTS <- flatForward evalDate rateQ dc Continuous Annual
        s0 <- simpleQuote 100.0
        hProcess <- hestonProcess rTS Nothing s0 0.04 1.0 0.04 0.2 (-0.5) QuadraticExponentialMartingale
        hwFwd <- hullWhiteForwardProcess rTS 0.05 0.01
        setForwardMeasureTime hwFwd 5.0
        joint <- hybridHestonHullWhiteProcess hProcess hwFwd 0.0 HybridHestonHullWhiteEuler
        iv <- initialValues joint
        calculated <- hybridHestonHullWhiteNumeraire joint 0.0 iv
        calculated `shouldSatisfy` closePrec 1.0 1.0e-12

    -- B(t,T) and alpha(t) are the two pieces of Hull-White's affine bond formula
    -- P(t,T) = A(t,T) exp(-B(t,T) r_t); both have closed forms independent of the process's
    -- own implementation (alpha's second term is the curve's instantaneous forward rate).
    it "alpha and B match their closed forms" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        let a = 0.07; sigma = 0.012
        rateQ <- simpleQuote 0.035
        rTS <- flatForward evalDate rateQ dc Continuous Annual
        hw <- hullWhiteProcess rTS a sigma
        hwFwd <- hullWhiteForwardProcess rTS a sigma
        setForwardMeasureTime hwFwd 10.0

        mapM_ (\t -> do
            fwdIR <- forwardRate rTS t t Continuous NoFrequency True
            let alfa = (sigma / a) * (1 - exp (-a * t))
                expected = 0.5 * alfa * alfa + rate fwdIR
            plain <- hullWhiteAlpha hw t
            fwd <- hullWhiteForwardAlpha hwFwd t
            plain `shouldSatisfy` closePrec expected 1.0e-12
            fwd `shouldSatisfy` closePrec expected 1.0e-12)
          [0.5, 2.0, 8.0]

        mapM_ (\(t, bigT) -> do
            calculated <- hullWhiteForwardB hwFwd t bigT
            calculated `shouldSatisfy` closePrec ((1 - exp (-a * (bigT - t))) / a) 1.0e-12)
          [(0.0, 1.0), (1.0, 5.0), (3.0, 3.0)]

    -- M_T is the T-forward-measure drift adjustment applied between s and t; it must vanish
    -- over a zero-length step, and upstream's own expectation() is
    -- x0 e^{-a dt} + alpha(t0+dt) - alpha(t0) e^{-a dt} - M_T(t0, t0+dt, T), which ties the
    -- three getters together without re-deriving M_T's closed form here.
    it "M_T vanishes over a zero-length step and is nonzero over a real one" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        rateQ <- simpleQuote 0.03
        rTS <- flatForward evalDate rateQ dc Continuous Annual
        hwFwd <- hullWhiteForwardProcess rTS 0.05 0.01
        setForwardMeasureTime hwFwd 10.0
        zeroStep <- hullWhiteForwardM hwFwd 1.0 1.0 10.0
        zeroStep `shouldSatisfy` closePrec 0.0 1.0e-14
        realStep <- hullWhiteForwardM hwFwd 1.0 3.0 10.0
        abs realStep `shouldSatisfy` (> 1.0e-8)

  where
    -- Abramowitz & Stegun 7.1.26 approximation, accurate to ~1.5e-7 -- ample for this
    -- table's 0.15 tolerance; avoids a new dependency for a single-call use.
    erf :: Double -> Double
    erf x =
      let a1 = 0.254829592; a2 = -0.284496736; a3 = 1.421413741
          a4 = -1.453152027; a5 = 1.061405429; p = 0.3275911
          sign = if x < 0 then -1 else 1
          ax = abs x
          t' = 1 / (1 + p * ax)
          y = 1 - (((((a5 * t' + a4) * t') + a3) * t' + a2) * t' + a1) * t' * exp (-ax * ax)
      in sign * y

    -- reference implementation of the G2++ deterministic offset phi(t), copied from
    -- G2::FittingParameter::Impl::value in ql/models/shortrate/twofactormodels/g2.hpp; used to
    -- check 'g2Phi' against a closed form independent of G2Process's own implementation.
    referencePhi :: YieldTermStructure -> Double -> Double -> Double -> Double -> Double -> Double -> IO Double
    referencePhi curve t a sigma b eta rho = do
      fwdIR <- forwardRate curve t t Continuous NoFrequency True
      let fwd = rate fwdIR
          temp1 = sigma * (1 - exp (-a * t)) / a
          temp2 = eta * (1 - exp (-b * t)) / b
      pure (0.5 * temp1 * temp1 + 0.5 * temp2 * temp2 + rho * temp1 * temp2 + fwd)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
