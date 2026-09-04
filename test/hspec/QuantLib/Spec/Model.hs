-- Coverage for 'QuantLib.Model''s 'Gaussian1dModel' analytics (numeraire, zerobond,
-- zerobondOption, forwardRate, swapRate, swapAnnuity, yGrid, stateProcess). Self-consistency
-- checks compare the model's own outputs, at the standardized state variable y=0, against the
-- fitted yield curve's own values -- a GSR (or any Gaussian1dModel) is fitted so that the y=0
-- path exactly reproduces the initial term structure.
module QuantLib.Spec.Model (spec) where

import Test.Hspec
import qualified Data.Vector.Storable as V
import Data.Time.Calendar(addGregorianYearsClip)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Option(EuropeanExercise(..))
import QuantLib.Instrument.Swap(fairRate, fixedLegBPS, vanillaSwap, swaption, SwapType(..))
import QuantLib.Model hiding(setPricingEngine, value)
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
      Settings.keepingSettings' $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward settlement flatQ dc Continuous Annual

        volQuote <- simpleQuote 0.01
        reversionQuote <- simpleQuote 0.01
        gsrModel <- gsr ts volQuote [] reversionQuote 60.0
        model <- gsrAsGaussian1dModel gsrModel

        -- zerobond(maturity, y=0) must equal the curve's own discount factor.
        let maturity = addGregorianYearsClip 5 settlement
        curveDf <- discount' ts maturity False
        modelDf <- gaussian1dZerobond model maturity Nothing 0 Nothing
        modelDf `shouldSatisfy` closePrec curveDf 1.0e-6

        -- numeraire(referenceDate=curve's own reference date, y=0) reduces (Gsr::numeraireImpl,
        -- t=0 branch) to the curve's own discount factor at the model's forward-measure time,
        -- which for Gsr is exactly the constructor's horizon argument T (60.0 here).
        curveDfHorizon <- discount ts 60.0 True
        num <- gaussian1dNumeraire model settlement 0 Nothing
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

        -- swapAnnuity(fixing, tenor, y=0) is the fixed leg's annuity; |fixedLegBPS| / 1bp is
        -- the same quantity computed off the swap's own priced fixed leg.
        fixedBPS <- fixedLegBPS underlying
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

        proc1D <- gaussian1dStateProcess model
        proc1D `seq` return ()

affineModelSpec :: Spec
affineModelSpec =
  describe "AffineModel.discountBondOption" $
    it "reproduces JamshidianSwaptionEngine's own single-period bond-option decomposition" $
      Settings.keepingSettings' $ do
        cal <- calendar TARGET
        originalEvalDate <- Settings.evaluationDate
        evalDate <- adjust cal originalEvalDate Following
        Settings.setEvaluationDate (Just evalDate)
        settlement <- advance cal evalDate (2, Days) Following False
        dc <- dayCounter Actual365FixedStandard
        flatQ <- simpleQuote 0.03
        ts <- flatForward settlement flatQ dc Continuous Annual
        hw <- hullWhite ts 0.1 0.01

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

        maturityT <- years dc settlement start Nothing Nothing
        payT <- years dc settlement end Nothing Nothing
        accrual <- years fixedDC start end Nothing Nothing
        let amount = notional * (1 + fixedRate * accrual)
            strike = notional / amount
        -- Payer swaption <-> Put on the underlying discount bond (JamshidianSwaptionEngine's
        -- own Swap::Payer -> Option::Put convention).
        manualForward <- discountBondOptionForward hw Put strike maturityT maturityT payT
        manualPlain <- discountBondOption hw Put strike maturityT payT
        let expectedNPV = amount * manualForward

        -- bondStart == maturity here, so the 4-arg and 5-arg forms must agree exactly.
        manualPlain `shouldSatisfy` closePrec manualForward 1.0e-12
        engineNPV `shouldSatisfy` closePrec expectedNPV 1.0e-8
