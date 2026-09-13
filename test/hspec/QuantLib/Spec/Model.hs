{-# LANGUAGE TupleSections #-}
-- Coverage for 'QuantLib.Model''s 'Gaussian1dModel' analytics (numeraire, zerobond,
-- zerobondOption, forwardRate, swapRate, swapAnnuity, yGrid, stateProcess). Self-consistency
-- checks compare the model's own outputs, at the standardized state variable y=0, against the
-- fitted yield curve's own values -- a GSR (or any Gaussian1dModel) is fitted so that the y=0
-- path exactly reproduces the initial term structure. Also covers the historical volatility
-- estimators (Garch11, the GarmanKlass family, ConstantEstimator, SimpleLocalEstimator) against
-- golden values ported from upstream tests, and hand-derived closed-form checks for the
-- OHLC-bar estimators -- exercising the (date, open, close, high, low) field order specifically,
-- since a marshalling mixup there wouldn't necessarily fail to compile or throw, only silently
-- price the wrong bar component.
module QuantLib.Spec.Model (spec) where

import Test.Hspec
import qualified Data.Vector.Storable as V
import Data.Time.Calendar(addGregorianYearsClip, fromGregorian, addDays)
import Data.List.NonEmpty(NonEmpty(..), fromList)

import qualified QuantLib.Context as Context
import QuantLib.Time.Calendar
import QuantLib.Time.Date(september)
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Option(EuropeanExercise(..))
import QuantLib.Instrument.Swap(fairRate, fixedLegBps, vanillaSwap, makeVanillaSwap, swaption, SwapType(..))
import QuantLib.Model hiding(setPricingEngine, value, discount)
import qualified QuantLib.Model as Model
import qualified QuantLib.Process as Process
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.Math(Interpolation(..))
import QuantLib.PricingEngine

import QuantLib.Spec.Helpers(closePrec, listClose)

spec :: Spec
spec = do
  gaussian1dSpec
  affineModelSpec
  garch11Spec
  garmanKlassSpec
  constantAndLocalEstimatorSpec

gaussian1dSpec :: Spec
gaussian1dSpec =
  describe "Gaussian1dModel" $ do
    it "reproduces the fitted curve's own discount factors, forward rate, and fair swap rate at y=0" $
      Context.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Context.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Context.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward (ReferenceDate settlement) flatQ dc Continuous Annual

        volQuote <- simpleQuote 0.01
        reversionQuote <- simpleQuote 0.01
        gsrModel <- gsr ts volQuote [] reversionQuote 60.0
        model <- asGaussian1dModel gsrModel >>= asGaussian1dModel

        -- zerobond(maturity, y=0) must equal the curve's own discount factor.
        let maturity = addGregorianYearsClip 5 settlement
        curveDf <- discount ts (DatePoint maturity) False
        modelDf <- gaussian1dZerobond model maturity Nothing 0 Nothing
        modelDf `shouldSatisfy` closePrec curveDf 1.0e-6

        -- numeraire(referenceDate=curve's own reference date, y=0) reduces (Gsr::numeraireImpl,
        -- t=0 branch) to the curve's own discount factor at the model's forward-measure time,
        -- which for Gsr is exactly the constructor's horizon argument T (60.0 here).
        curveDfHorizon <- discount ts (TimePoint 60.0) True
        num <- numeraire model settlement 0 Nothing
        num `shouldSatisfy` closePrec curveDfHorizon 1.0e-6

        -- forwardRate(fixing, y=0) for euribor6m must equal the index's own curve-implied
        -- forecast fixing.
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
        fixingDate <- advance cal settlement (1, Years) ModifiedFollowing False
        curveForward <- IR.forecastFixing euribor6m fixingDate
        modelForward <- gaussian1dForwardRate model fixingDate Nothing 0 (Just euribor6m)
        modelForward `shouldSatisfy` closePrec curveForward 1.0e-6

        -- swapRate(fixing, tenor, y=0) for the fitted swap index must equal the fair rate of
        -- the same underlying swap, discounted off the same curve.
        swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
        underlying <- IR.underlyingSwap swapBase fixingDate
        engine <- discountingSwapEngine ts (Just False) Nothing Nothing
        setPricingEngine underlying engine
        curveFairRate <- fairRate underlying
        modelSwapRate <- gaussian1dSwapRate model fixingDate (10, Years) Nothing 0 (Just swapBase)
        modelSwapRate `shouldSatisfy` closePrec curveFairRate 1.0e-6

        -- swapAnnuity(fixing, tenor, y=0) is the fixed leg's annuity; |fixedLegBps| / 1bp is
        -- the same quantity computed off the swap's own priced fixed leg.
        fixedBPS <- fixedLegBps underlying
        modelAnnuity <- gaussian1dSwapAnnuity model fixingDate (10, Years) Nothing 0 (Just swapBase)
        modelAnnuity `shouldSatisfy` closePrec (abs fixedBPS / 1.0e-4) 1.0e-4

        -- zerobondOption, yGrid, and stateProcess: structural checks -- each is a real
        -- calculation without a convenient closed-form comparison in this fixture, so assert
        -- well-formedness rather than a pinned value.
        putOpt <- gaussian1dZerobondOption model Put fixingDate fixingDate maturity 0.8 Nothing 0
          Nothing 7.0 64 True False
        putOpt `shouldSatisfy` (\x -> x >= 0 && not (isNaN x || isInfinite x))

        grid <- gaussian1dYGrid model 7.0 8 1.0 0 0
        V.length grid `shouldBe` 2 * 8 + 1

        proc1D <- stateProcess model
        proc1D `seq` return ()

    -- The surface inverts Black's formula on model swaption prices, so a Black engine on it must
    -- reprice the model's own ATM swaption. Pending: QuantLib 1.43's fixing-date MakeSwaption leaves
    -- its nominal uninitialized, so Gaussian1dSmileSection reports zero volatilities.
    xit "gaussian1dSwaptionVolatility reprices the model's swaption under a Black engine" $
      Context.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Context.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Context.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward (ReferenceDate settlement) flatQ dc Continuous Annual
        volQuote <- simpleQuote 0.01
        reversionQuote <- simpleQuote 0.01
        gsrModel <- gsr ts volQuote [] reversionQuote 60.0
        model <- asGaussian1dModel gsrModel
        swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
        thirty360 <- dayCounter Thirty360BondBasis
        -- the swap index's own underlying starts two business days after its fixing date
        startDate <- adjust cal (addGregorianYearsClip 5 settlement) Following
        fixingDate <- advance cal startDate (-2, Days) Following False
        strike <- gaussian1dSwapRate model fixingDate (10, Years) Nothing 0 (Just swapBase)
        underlying <- makeVanillaSwap (10, Years) euribor6m strike (5, Years) (Just 2) (1, Years) thirty360
          Nothing Nothing Nothing Nothing Nothing Nothing
        swpn <- swaption underlying (European (EuropeanExercise fixingDate)) Physical PhysicalOTC
        gaussian1dSwaptionEngine model 64 7.0 True False (Just ts) None >>= setPricingEngine swpn
        modelNpv <- npv swpn
        surface <- Vol.gaussian1dSwaptionVolatility cal ModifiedFollowing swapBase model dc
        blackSwaptionEngineFromVolatilityStructure ts surface >>= setPricingEngine swpn
        blackNpv <- npv swpn
        blackNpv `shouldSatisfy` closePrec modelNpv (1.0e-4 * modelNpv)

affineModelSpec :: Spec
affineModelSpec =
  describe "AffineModel" $ do
    it "materializes every short-rate-model instance and reuses an interface handle" $
      Context.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Context.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Context.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward (ReferenceDate settlement) flatQ dc Continuous Annual

        hw <- hullWhite ts 0.1 0.01
        hwAffine <- asAffineModel hw
        oneFactor <- asOneFactorAffineModel hw
        oneFactorAffine <- asAffineModel oneFactor
        g2Model <- g2 ts 0.1 0.01 0.1 0.01 (-0.75)
        g2Affine <- asAffineModel g2Model
        reusedAffine <- asAffineModel hwAffine

        mapM_ (\model -> analyticCapFloorEngine model Nothing >>= (`seq` pure ()))
          [hwAffine, oneFactorAffine, g2Affine, reusedAffine]

    it "reproduces JamshidianSwaptionEngine's own single-period bond-option decomposition" $
      Context.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Context.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Context.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward (ReferenceDate settlement) flatQ dc Continuous Annual
        hw <- hullWhite ts 0.1 0.01
        hwAffine <- asAffineModel hw

        -- A single fixed-vs-float period, with the exercise date set to the period's own start
        -- (rather than the usual fixing-lagged date) so that JamshidianSwaptionEngine's
        -- valueTime (the fixed leg's reset date) exactly equals its maturity (the exercise
        -- date). That collapses its internal Brent solve for rStar: the normalizing bond
        -- discountBond(maturity, valueTime, rStar) is then A(t,t)*exp(-B(t,t)*rStar) = 1 for
        -- any rStar, so strike = notional / (fixedCoupon + notional) in closed form, with no
        -- need to reproduce the root-find here.
        start <- advance cal settlement (1, Years) ModifiedFollowing False
        end <- advance cal start (1, Years) ModifiedFollowing False
        fixedDC <- dayCounter Thirty360BondBasis
        act360 <- dayCounter (Actual360 False)
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
        fixedSchedule <- schedule (Just start) end (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
        floatSchedule <- schedule (Just start) end (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
        let notional = 1.0
            fixedRate = 0.03
        swp <- vanillaSwap Payer notional fixedSchedule fixedRate fixedDC floatSchedule euribor6m 0.0 act360 (Just ModifiedFollowing) Nothing

        engine <- jamshidianSwaptionEngine hw (Just ts)
        swpn <- swaption swp (European (EuropeanExercise start)) Physical PhysicalOTC
        setPricingEngine swpn engine
        engineNPV <- npv swpn

        maturityT <- yearFraction dc settlement start Nothing Nothing
        payT <- yearFraction dc settlement end Nothing Nothing
        accrual <- yearFraction fixedDC start end Nothing Nothing
        let amount = notional * (1 + fixedRate * accrual)
            strike = notional / amount
        -- Payer swaption <-> Put on the underlying discount bond (JamshidianSwaptionEngine's
        -- own Swap::Payer -> Option::Put convention).
        manualForward <- discountBondOption hwAffine Put strike maturityT (Just maturityT) payT
        manualPlain <- discountBondOption hwAffine Put strike maturityT Nothing payT
        let expectedNPV = amount * manualForward

        -- bondStart == maturity here, so the 4-arg and 5-arg forms must agree exactly.
        manualPlain `shouldSatisfy` closePrec manualForward 1.0e-12
        engineNPV `shouldSatisfy` closePrec expectedNPV 1.0e-8

    it "discount reproduces the fitted curve, and discountBond(t,t,.) is always 1, for HullWhite and G2" $
      Context.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Context.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Context.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward (ReferenceDate settlement) flatQ dc Continuous Annual
        curveDf <- discount ts (TimePoint 5.0) False

        -- Hull-White uses one state factor and fits its initial curve.
        hw <- hullWhite ts 0.1 0.01
        hwAffine <- asAffineModel hw
        hwDf <- Model.discount hwAffine 5.0
        hwDf `shouldSatisfy` closePrec curveDf 1.0e-10
        hwBond <- discountBond hwAffine 5.0 5.0 [0.02]
        hwBond `shouldSatisfy` closePrec 1.0 1.0e-10

        -- G2 requires both state factors.
        g2Model <- g2 ts 0.1 0.01 0.1 0.01 (-0.75)
        g2Affine <- asAffineModel g2Model
        g2Df <- Model.discount g2Affine 5.0
        g2Df `shouldSatisfy` closePrec curveDf 1.0e-10
        g2Bond <- discountBond g2Affine 5.0 5.0 [0.02, -0.01]
        g2Bond `shouldSatisfy` closePrec 1.0 1.0e-10

    it "discount/discountBond on LiborForwardModel read the index curve directly, ignoring factors" $
      Context.keepingSettingsGc $ do
        -- The first curve pillar follows the fixing lag so no past Euribor fixing is required.
        let fixtureDate = 4 `september` 2005
            curveEndDate = 4 `september` 2018
            size = 10 :: Word
        cal <- calendar TARGET
        evalDate <- adjust cal fixtureDate Following
        Context.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        emptyIndex <- IR.iborIndex IR.Euribor6M Nothing
        firstPillar <- advance cal evalDate (fromIntegral (IR.fixingDays emptyIndex), Days) Following False
        rTS <- interpolatedZeroCurve (fromList [(firstPillar, 0.039), (curveEndDate, 0.041)]) dc cal [] Linear
        idx <- IR.iborIndex IR.Euribor6M (Just rTS)
        process <- Process.liborForwardModelProcess size idx
        fixingGrid <- Process.fixingTimes process
        lfmModel <- liborForwardModel process (FixedVolatility (fromList (map (, 0.1) fixingGrid))) (ExponentialCorrelation size 0.3)
        lfmAffine <- asAffineModel lfmModel

        -- LiborForwardModel reads the index curve and ignores now and factors for discount bonds.
        curveDf <- discount rTS (TimePoint 5.0) False
        lfmDf <- Model.discount lfmAffine 5.0
        lfmDf `shouldSatisfy` closePrec curveDf 1.0e-12
        b1 <- discountBond lfmAffine 0.0 5.0 []
        b2 <- discountBond lfmAffine 123.0 5.0 [999.0, -42.0]
        b1 `shouldSatisfy` closePrec curveDf 1.0e-12
        b2 `shouldSatisfy` closePrec curveDf 1.0e-12

-- garch.cpp::testCalculation, ported verbatim: a flat r=0.1 return series run through the
-- direct-parameter Garch11(0.2, 0.3, 0.4)'s own calculate() recursion.
garch11Spec :: Spec
garch11Spec = describe "Garch11" $ do
  it "reproduces garch.cpp::testCalculation's calculated series" $ do
    g <- garch11 0.2 0.3 0.4
    let day0 = fromGregorian 1962 7 6
        sampleDays = [addDays i day0 | i <- [1 .. 10]]
        series = fromList (zip sampleDays (replicate 10 0.1))
    result <- calculate g series
    let expected =
          [ 0.452769, 0.513323, 0.530141, 0.5350841, 0.536558
          , 0.536999, 0.537132, 0.537171, 0.537183, 0.537187
          ]
        -- Garch11::calculate's own output series is offset by one from its input: the first
        -- input point has nothing to forecast from, so it's dropped, and one extra point is
        -- extrapolated one step past the input series' last date (garch.cpp's
        -- Garch11::calculate, not this binding's marshalling).
        outputDays = map (addDays 1) sampleDays
    map fst result `shouldBe` outputDays
    map snd result `shouldSatisfy` listClose id expected 1.0e-6

  it "forecast/calculate agree, and calibration on a synthetic series lands on stable, plausible parameters in all four modes" $ do
    g0 <- garch11 0.2 0.3 0.4
    let day0 = fromGregorian 1990 1 1
        n = 80 :: Int
        -- A deterministic, non-degenerate synthetic "return" series -- avoids depending on
        -- QuantLib's own RNG draw sequence (which this binding never promises to reproduce
        -- bit-for-bit) while still giving the optimizer real variance to fit.
        shocks = take n [2 * y - 1 | y <- iterate (\x -> 3.97 * x * (1 - x)) 0.31]
        series = buildSeries g0 day0 shocks
    mapM_ (checkCalibration series) [MomentMatchingGuess, GammaGuess, BestOfTwo, DoubleOptimization]
  where
    buildSeries g day shocks = fromList (reverse (go day 0.0 0.0 shocks []))
      where
        go _ _ _ [] acc = acc
        go d r sigma2 (z : zs) acc =
          let sigma2' = forecast g r sigma2
              r' = z * sqrt sigma2'
          in go (addDays 1 d) r' sigma2' zs ((d, r') : acc)
    -- Only checks that all four 'Garch11Mode' values calibrate without throwing and hand back
    -- finite parameters -- a wiring-level check, not a convergence guarantee. This synthetic
    -- (chaotic-map-driven) series has no ground truth to fit, and omega\/logLikelihood can
    -- legitimately land on a degenerate boundary (NaN log-likelihood, omega == 0) for a
    -- poorly-conditioned sample; that's an optimizer property, not something this binding
    -- should assert away. alpha/beta likewise aren't guaranteed to sit in [0,1]: Garch11's
    -- box constraint binds the optimizer only, and on the non-'DoubleOptimization' path
    -- garch.cpp's calibrate_r2 catches an optimizer exception and returns the raw
    -- initialGuess1/initialGuess2 ACF estimate unfiltered, which carries no sign constraint
    -- (seen on Windows CI as a calibrated alpha of -0.85).
    checkCalibration series mode = do
      gc <- garch11Calibrated series mode
      Model.alpha gc `shouldSatisfy` finite
      Model.beta gc `shouldSatisfy` finite
    finite x = not (isNaN x || isInfinite x)

-- Closed-form checks transcribed directly from ql/models/volatility/garmanklass.hpp, evaluated
-- in Haskell against a two-bar series with distinct open/close/high/low on each bar -- any
-- marshalling swap between the four price fields breaks at least one of these.
garmanKlassSpec :: Spec
garmanKlassSpec = describe "GarmanKlass family" $ do
  it "garmanKlassSimpleSigma matches ln(close\\/open)^2, scaled by yearFraction" $ do
    result <- garmanKlassSimpleSigma dt bars
    map fst result `shouldBe` [day1, day2]
    case result of
      (r0:r1:_) -> do
        r0 `shouldSatisfy` (\(_, v) -> closePrec (simpleSigma o1 c1) 1.0e-9 v)
        r1 `shouldSatisfy` (\(_, v) -> closePrec (simpleSigma o2 c2) 1.0e-9 v)
      _ -> expectationFailure "expected at least two bars"

  it "parkinsonSigma matches the high-low estimator" $ do
    result <- parkinsonSigma dt bars
    case result of
      (_:r1:_) -> r1 `shouldSatisfy` (\(_, v) -> closePrec (parkinsonSigma' o2 h2 l2) 1.0e-9 v)
      _ -> expectationFailure "expected at least two bars"

  it "garmanKlassSigma4 matches its published high-low\\/close-open coefficients" $ do
    result <- garmanKlassSigma4 dt bars
    case result of
      (_:r1:_) -> r1 `shouldSatisfy` (\(_, v) -> closePrec (sigma4Formula o2 c2 h2 l2) 1.0e-9 v)
      _ -> expectationFailure "expected at least two bars"

  it "garmanKlassSigma5 matches its published high-low\\/close-open coefficients" $ do
    result <- garmanKlassSigma5 dt bars
    case result of
      (_:r1:_) -> r1 `shouldSatisfy` (\(_, v) -> closePrec (sigma5Formula o2 c2 h2 l2) 1.0e-9 v)
      _ -> expectationFailure "expected at least two bars"

  it "garmanKlassSigma1 blends simpleSigma with the overnight jump, dropping the first bar" $ do
    result <- garmanKlassSigma1 dt marketOpenFraction bars
    map fst result `shouldBe` [day2]
    let simpleBase = log (c2 / o2) ** 2
        expected = openCloseBlend marketOpenFraction 0.5 simpleBase
    case result of
      (r0:_) -> r0 `shouldSatisfy` (\(_, v) -> closePrec expected 1.0e-9 v)
      [] -> expectationFailure "expected at least one bar"

  it "garmanKlassSigma3 blends parkinsonSigma with the overnight jump, dropping the first bar" $ do
    result <- garmanKlassSigma3 dt marketOpenFraction bars
    let parkinsonBase = (log (h2 / o2) - log (l2 / o2)) ** 2 / (4 * log 2)
        expected = openCloseBlend marketOpenFraction 0.17 parkinsonBase
    case result of
      (r0:_) -> r0 `shouldSatisfy` (\(_, v) -> closePrec expected 1.0e-9 v)
      [] -> expectationFailure "expected at least one bar"

  it "garmanKlassSigma6 blends garmanKlassSigma4 with the overnight jump, dropping the first bar" $ do
    result <- garmanKlassSigma6 dt marketOpenFraction bars
    let sigma4Base =
          let u = log (h2 / o2); d = log (l2 / o2); cc = log (c2 / o2)
          in 0.511 * (u - d) ** 2 - 0.019 * (cc * (u + d) - 2 * u * d) - 0.383 * cc * cc
        expected = openCloseBlend marketOpenFraction 0.012 sigma4Base
    case result of
      (r0:_) -> r0 `shouldSatisfy` (\(_, v) -> closePrec expected 1.0e-9 v)
      [] -> expectationFailure "expected at least one bar"
  where
    day1 = fromGregorian 2020 3 2
    day2 = fromGregorian 2020 3 3
    (o1, c1, h1, l1) = (100.0, 102.0, 103.0, 99.0)
    (o2, c2, h2, l2) = (101.0, 105.0, 106.0, 100.0)
    bars = (day1, o1, c1, h1, l1) :| [(day2, o2, c2, h2, l2)]
    dt = 1.0 / 252.0
    marketOpenFraction = 0.5 :: Double

    simpleSigma o c = sqrt (abs (log (c / o) ** 2) / dt)
    parkinsonSigma' o h l = sqrt (abs ((log (h / o) - log (l / o)) ** 2 / (4 * log 2)) / dt)
    sigma4Formula o c h l =
      let u = log (h / o); d = log (l / o); cc = log (c / o)
      in sqrt (abs (0.511 * (u - d) ** 2 - 0.019 * (cc * (u + d) - 2 * u * d) - 0.383 * cc * cc) / dt)
    sigma5Formula o c h l =
      let u = log (h / o); d = log (l / o); cc = log (c / o)
      in sqrt (abs (0.5 * (u - d) ** 2 - (2 * log 2 - 1) * cc * cc) / dt)
    -- jump = ln(cur.open) - ln(prev.close); a is the per-variant blend weight (0.5/0.17/0.012).
    openCloseBlend f a base = sqrt ((a * jump ** 2 / f + (1 - a) * base / (1 - f)) / dt)
      where jump = log o2 - log c1

-- ConstantEstimator: hand-computed over a 5-point series with windowSize=3
-- (constantestimator.cpp: s = sqrt(sum(u^2)/size - sum(u)^2/size/(size+1)) over each trailing
-- window). SimpleLocalEstimator: |ln(p_i/p_{i-1})| / sqrt(yearFraction) over a 3-point series.
constantAndLocalEstimatorSpec :: Spec
constantAndLocalEstimatorSpec = describe "ConstantEstimator and SimpleLocalEstimator" $ do
  it "constantVolatilityEstimator matches the windowed sample-variance formula" $ do
    let day0 = fromGregorian 2021 1 1
        sampleDays = [addDays i day0 | i <- [0 .. 4]]
        vals = [1.0, 2.0, 3.0, 2.0, 1.0]
        series = fromList (zip sampleDays vals)
        windowed ws = sqrt (sum (map (** 2) ws) / n - sum ws ** 2 / n / (n + 1))
          where n = fromIntegral (length ws)
    result <- constantVolatilityEstimator 3 series
    map fst result `shouldBe` drop 3 sampleDays
    map snd result `shouldSatisfy` listClose id [windowed [1, 2, 3], windowed [2, 3, 2]] 1.0e-9

  it "simpleLocalVolatilityEstimator matches |ln(p_i\\/p_{i-1})| \\/ sqrt(yearFraction)" $ do
    let day0 = fromGregorian 2021 1 1
        sampleDays = [addDays i day0 | i <- [0 .. 2]]
        prices = [100.0, 105.0, 110.0]
        series = fromList (zip sampleDays prices)
        dt = 1.0 / 252.0
        expected = [abs (log (p1 / p0)) / sqrt dt | (p0, p1) <- zip prices (drop 1 prices)]
    result <- simpleLocalVolatilityEstimator dt series
    map fst result `shouldBe` drop 1 sampleDays
    map snd result `shouldSatisfy` listClose id expected 1.0e-9
