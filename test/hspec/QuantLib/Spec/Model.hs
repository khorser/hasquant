{-# LANGUAGE TupleSections #-}
-- Coverage for 'QuantLib.Model''s 'Gaussian1dModel' analytics (numeraire, zerobond,
-- zerobondOption, forwardRate, swapRate, swapAnnuity, yGrid, stateProcess). Self-consistency
-- checks compare the model's own outputs, at the standardized state variable y=0, against the
-- fitted yield curve's own values -- a GSR (or any Gaussian1dModel) is fitted so that the y=0
-- path exactly reproduces the initial term structure.
module QuantLib.Spec.Model (spec) where

import Test.Hspec
import qualified Data.Vector.Storable as V
import Data.Time.Calendar(addGregorianYearsClip)
import Data.List.NonEmpty(fromList)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date(september)
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Option(EuropeanExercise(..))
import QuantLib.Instrument.Swap(fairRate, fixedLegBps, vanillaSwap, swaption, SwapType(..))
import QuantLib.Model hiding(setPricingEngine, value, discount)
import qualified QuantLib.Model as Model
import qualified QuantLib.Process as Process
import QuantLib.Math(Interpolation(..))
import QuantLib.PricingEngine

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = do
  gaussian1dSpec
  affineModelSpec

gaussian1dSpec :: Spec
gaussian1dSpec =
  describe "Gaussian1dModel" $
    it "reproduces the fitted curve's own discount factors, forward rate, and fair swap rate at y=0" $
      Settings.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
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

affineModelSpec :: Spec
affineModelSpec =
  describe "AffineModel" $ do
    it "materializes every short-rate-model instance and reuses an interface handle" $
      Settings.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
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
      Settings.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
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

    -- 'discount'/'discountBond' are bound at the 'AffineModel' level precisely so that models
    -- other than 'OneFactorAffineModel' benefit too -- exercise a one-factor model (HullWhite),
    -- a genuine two-factor model (G2, which requires a two-element factors list), and a model
    -- that ignores factors entirely (LiborForwardModel), not just HullWhite.
    it "discount reproduces the fitted curve, and discountBond(t,t,.) is always 1, for HullWhite and G2" $
      Settings.keepingSettingsGc $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward (ReferenceDate settlement) flatQ dc Continuous Annual
        curveDf <- discount ts (TimePoint 5.0) False

        -- HullWhite: 'discount' fits the curve by construction (AffineModel::discount ==
        -- discountBond(0, t, r0) for the model's own initial short rate r0, which the fitting
        -- procedure makes reproduce P(0,t) exactly). 'discountBond' with a one-element [rate]
        -- reproduces the old scalar-Rate convenience overload exactly, since
        -- OneFactorAffineModel::discountBond(Array) just forwards factors[0]; at now==maturity
        -- a bond has price 1 regardless of the state (A(t,t)==1, B(t,t)==0), independent of the
        -- curve or the chosen rate -- a structural identity rather than a pinned value.
        hw <- hullWhite ts 0.1 0.01
        hwAffine <- asAffineModel hw
        hwDf <- Model.discount hwAffine 5.0
        hwDf `shouldSatisfy` closePrec curveDf 1.0e-10
        hwBond <- discountBond hwAffine 5.0 5.0 [0.02]
        hwBond `shouldSatisfy` closePrec 1.0 1.0e-10

        -- G2 (two-factor): the same two identities, but discountBond now needs a two-element
        -- factors list (G2::discountBond requires factors.size()>1).
        g2Model <- g2 ts 0.1 0.01 0.1 0.01 (-0.75)
        g2Affine <- asAffineModel g2Model
        g2Df <- Model.discount g2Affine 5.0
        g2Df `shouldSatisfy` closePrec curveDf 1.0e-10
        g2Bond <- discountBond g2Affine 5.0 5.0 [0.02, -0.01]
        g2Bond `shouldSatisfy` closePrec 1.0 1.0e-10

    it "discount/discountBond on LiborForwardModel read the index curve directly, ignoring factors" $
      Settings.keepingSettingsGc $ do
        -- Fixture shape ported from Spec.Process's LiborForwardModelProcess fixture: a fixed
        -- historical evaluation date and an index-fixing-lag-aware curve pillar, so the
        -- process's first period doesn't require a historical Euribor6M fixing that doesn't
        -- exist. The vol/correlation models' actual values don't matter here -- 'discount'/
        -- 'discountBond' never consult them, only the index's own forwarding curve.
        let fixtureDate = 4 `september` 2005
            curveEndDate = 4 `september` 2018
            size = 10 :: Word
        cal <- calendar TARGET
        evalDate <- adjust cal fixtureDate Following
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter (Actual360 False)
        emptyIndex <- IR.iborIndex IR.Euribor6M Nothing
        firstPillar <- advance cal evalDate (fromIntegral (IR.fixingDays emptyIndex), Days) Following False
        rTS <- interpolatedZeroCurve (fromList [(firstPillar, 0.039), (curveEndDate, 0.041)]) dc cal [] Linear
        idx <- IR.iborIndex IR.Euribor6M (Just rTS)
        process <- Process.liborForwardModelProcess size idx
        times <- Process.fixingTimes process
        lfmModel <- liborForwardModel process (FixedVolatility (fromList (map (, 0.1) times))) (ExponentialCorrelation size 0.3)
        lfmAffine <- asAffineModel lfmModel

        -- LiborForwardModel::discount(t) just reads process_->index()->forwardingTermStructure()
        -- ->discount(t) -- i.e. the same curve directly, independent of the vol/correlation
        -- models above -- and LiborForwardModel::discountBond(now,maturity,factors) ignores
        -- both 'now' and 'factors' entirely, returning discount(maturity).
        curveDf <- discount rTS (TimePoint 5.0) False
        lfmDf <- Model.discount lfmAffine 5.0
        lfmDf `shouldSatisfy` closePrec curveDf 1.0e-12
        b1 <- discountBond lfmAffine 0.0 5.0 []
        b2 <- discountBond lfmAffine 123.0 5.0 [999.0, -42.0]
        b1 `shouldSatisfy` closePrec curveDf 1.0e-12
        b2 `shouldSatisfy` closePrec curveDf 1.0e-12
