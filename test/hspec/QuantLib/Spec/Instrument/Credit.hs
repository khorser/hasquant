-- | Golden-value tests for 'QuantLib.Instrument.Credit' ('creditDefaultSwap', 'fairSpread',
-- 'fairUpfront', 'impliedHazardRate'), ported from QuantLib's own
-- test-suite/creditdefaultswap.cpp -- currently zero coverage (no dedicated hspec Spec module
-- existed for this file before).
--
-- @cdo.cpp@ is not portable: hasquant has no CDO\/Pool\/loss-model bindings.
--
-- testFairSpread\/testFairUpfront use a plain 'Forward'-generated Semiannual schedule here
-- rather than upstream's own @TwentiethIMM@\/@Quarterly@ 'MakeSchedule' builder (not bound) --
-- the "fair spread\/upfront reprices to zero" property is a structural identity of CDS pricing
-- that holds for any valid coupon schedule, not one specific to that date-generation rule.
module QuantLib.Spec.Instrument.Credit (spec) where

import Control.Monad(forM_)

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Credit
import QuantLib.Instrument(npv, setPricingEngine, PricingModel(..))
import QuantLib.Instrument.Credit
import QuantLib.Instrument.Swap(fairSpread)
import QuantLib.PricingEngine(midPointCdsEngine, integralCdsEngine)

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = do
  describe "testCachedValue" $
    it "NPV and fairSpread reproduce creditdefaultswap.cpp's cached values under\
       \ MidPointCdsEngine and IntegralCdsEngine (1 day and 1 week steps)" $
      Settings.keepingSettings' $ do
        let today' = 9 `june` 2006
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        dc <- dayCounter (Actual360 False)
        hazardQ <- simpleQuote 0.01234
        probCurve <- flatHazardRate' 0 cal hazardQ dc
        discQ <- simpleQuote 0.06
        discountCurve <- flatForward today' discQ dc Continuous Annual

        issueDate <- advance cal today' (-1, Years) ModifiedFollowing False
        maturity <- advance cal issueDate (10, Years) ModifiedFollowing False
        sch <- schedule (Just issueDate) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing
          Forward False Nothing Nothing

        cds <- creditDefaultSwap Seller 10000 0.0120 sch ModifiedFollowing dc True True
          Nothing FaceValue dc True Nothing 3

        -- NPV/fairSpread differ by five orders of magnitude, so compare each against its own
        -- magnitude-appropriate tolerance rather than a single shared absolute one.
        midEng <- midPointCdsEngine probCurve 0.4 discountCurve Nothing
        setPricingEngine cds midEng
        midNpv <- npv cds
        midNpv `shouldSatisfy` closePrec 295.0153398 1.0e-6
        midFair <- fairSpread cds
        midFair `shouldSatisfy` closePrec 0.007517539081 1.0e-7

        integ1dEng <- integralCdsEngine (1, Days) probCurve 0.4 discountCurve Nothing
        setPricingEngine cds integ1dEng
        integ1dNpv <- npv cds
        integ1dNpv `shouldSatisfy` closePrec 295.0153398 (10000 * 1.0e-4)
        integ1dFair <- fairSpread cds
        integ1dFair `shouldSatisfy` closePrec 0.007517539081 1.0e-5

        integ1wEng <- integralCdsEngine (1, Weeks) probCurve 0.4 discountCurve Nothing
        setPricingEngine cds integ1wEng
        integ1wNpv <- npv cds
        integ1wNpv `shouldSatisfy` closePrec 295.0153398 (10000 * 1.0e-4)
        integ1wFair <- fairSpread cds
        integ1wFair `shouldSatisfy` closePrec 0.007517539081 1.0e-5

  describe "testFairSpread" $
    it "rebuilding at the CDS's own fairSpread reprices it to ~0" $
      Settings.keepingSettings' $ do
        today' <- today >>= \d -> do
          cal <- calendar TARGET
          adjust cal d Following
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        dc <- dayCounter (Actual360 False)
        hazardQ <- simpleQuote 0.01234
        probCurve <- flatHazardRate' 0 cal hazardQ dc
        discQ <- simpleQuote 0.06
        discountCurve <- flatForward today' discQ dc Continuous Annual
        eng <- midPointCdsEngine probCurve 0.4 discountCurve Nothing

        issueDate <- advance cal today' (-1, Years) Following False
        maturity <- advance cal issueDate (10, Years) Following False
        sch <- schedule (Just issueDate) maturity (6, Months) cal Following Following
          Forward False Nothing Nothing

        cds <- creditDefaultSwap Seller 10000 0.001 sch Following dc True True
          Nothing FaceValue dc True Nothing 3
        setPricingEngine cds eng
        fair <- fairSpread cds

        fairCds <- creditDefaultSwap Seller 10000 fair sch Following dc True True
          Nothing FaceValue dc True Nothing 3
        setPricingEngine fairCds eng
        fairNpv <- npv fairCds
        fairNpv `shouldSatisfy` closePrec 0 1.0e-6

  describe "testFairUpfront" $
    it "rebuilding at the CDS's own fairUpfront reprices it to ~0" $
      Settings.keepingSettings' $ do
        today' <- today >>= \d -> do
          cal <- calendar TARGET
          adjust cal d Following
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        dc <- dayCounter (Actual360 False)
        hazardQ <- simpleQuote 0.01234
        probCurve <- flatHazardRate' 0 cal hazardQ dc
        discQ <- simpleQuote 0.06
        discountCurve <- flatForward today' discQ dc Continuous Annual
        eng <- midPointCdsEngine probCurve 0.4 discountCurve (Just True)

        maturity <- advance cal today' (10, Years) Following False
        sch <- schedule (Just today') maturity (6, Months) cal Following Following
          Forward False Nothing Nothing

        cds <- creditDefaultSwap' Seller 10000 0.001 0.05 sch Following dc True True
          Nothing Nothing FaceValue dc True Nothing 3
        setPricingEngine cds eng
        fairUp <- fairUpfront cds

        fairCds <- creditDefaultSwap' Seller 10000 fairUp 0.05 sch Following dc True True
          Nothing Nothing FaceValue dc True Nothing 3
        setPricingEngine fairCds eng
        fairNpv <- npv fairCds
        fairNpv `shouldSatisfy` closePrec 0 1.0e-6

  describe "testImpliedHazardRate" $
    it "round-trips impliedHazardRate against the flat hazard rate used to build the CDS's NPV" $
      Settings.keepingSettings' $ do
        today' <- today >>= \d -> do
          cal <- calendar TARGET
          adjust cal d Following
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        dc <- dayCounter (Actual360 False)
        discQ <- simpleQuote 0.03
        discountCurve <- flatForward today' discQ dc Continuous Annual

        issueDate <- advance cal today' (-6, Months) ModifiedFollowing False
        forM_ [0.30, 0.35, 0.40 :: Double] $ \h -> do
          maturity <- advance cal issueDate (10, Years) ModifiedFollowing False
          sch <- schedule (Just issueDate) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing
            Forward False Nothing Nothing

          hazardQ <- simpleQuote h
          probCurve <- flatHazardRate' 0 cal hazardQ dc
          eng <- midPointCdsEngine probCurve 0.4 discountCurve Nothing

          cds <- creditDefaultSwap Seller 10000 0.0120 sch ModifiedFollowing dc True True
            Nothing FaceValue dc True Nothing 3
          setPricingEngine cds eng
          value <- npv cds
          implied <- impliedHazardRate cds value discountCurve dc 0.4 1.0e-10 Midpoint
          implied `shouldSatisfy` closePrec h 1.0e-6
