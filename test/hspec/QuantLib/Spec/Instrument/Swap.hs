-- | Coverage for 'QuantLib.Instrument.Swap''s plain 'VanillaSwap' path and the
-- ConstNotionalCrossCurrency* family, which had no dedicated hspec Spec module before this
-- (see CLAUDE.md: coverage is only measured over @test\/hspec\/**@ + @test\/example\/**@).
--
-- \"VanillaSwap\" golden values are ported from QuantLib's own test-suite/swap.cpp. The
-- ConstNotionalCrossCurrency* block is ported from @test\/smoke\/CheckConstNotionalCrossCurrencySwap.hs@,
-- which had no cached upstream golden values available (see CLAUDE.md's guidance to prefer
-- them where available -- a full port of test-suite/constnotionalcrosscurrency*.cpp's fixtures
-- is left as follow-up work) and instead used martingale-style self-consistency checks: with
-- both legs built from the same index/schedule/nominal/spread, matching discount curves, and
-- spotFX=1, the pay and receive legs must have equal in-currency NPV, so the swap's total NPV
-- (and, for the basis swap, its fair pay/rec spreads) must come out at zero.
{-# LANGUAGE OverloadedLists #-}

module QuantLib.Spec.Instrument.Swap (spec) where

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Currency hiding(rate)
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Instrument
import QuantLib.Instrument.Bond(fixedRateBond, asBond, settlementDate)
import QuantLib.Instrument.Swap
import QuantLib.PricingEngine

import QuantLib.Spec.Helpers(closePrec)

-- |test-suite/swap.cpp's CommonVars: a Euribor6M-referencing Payer VanillaSwap fixture --
-- nominal 100, fixed leg Annual/Unadjusted/Thirty360(BondBasis), floating leg
-- Semiannual/ModifiedFollowing, flat 5% Actual365Fixed discount curve, all built off a
-- 2-business-day settlement from a given "today".
makeSwap :: Day -> Int -> Double -> Double -> IO VanillaSwap
makeSwap today' lengthYears fixedRate floatingSpread = do
  cal <- calendar TARGET
  fixedDC <- dayCounter Thirty360BondBasis
  floatDC <- dayCounter (Actual360 False)
  discDC <- dayCounter Actual365FixedStandard
  q <- simpleQuote 0.05
  -- matches test-suite/swap.cpp's CommonVars: "today" is first adjusted onto a business day
  -- (calendar.adjust) before the 2-business-day settlement lag is applied -- otherwise, when
  -- the real evaluation date lands on a weekend, the resulting fixing date can fall strictly
  -- before it and require a historical Euribor6M fixing that was never registered.
  adjToday <- adjust cal today' Following
  settle <- advance cal adjToday (2, Days) Following False
  ts <- flatForward settle q discDC Continuous Annual
  idx <- IR.iborIndex IR.Euribor6M (Just ts)
  maturity <- advance cal settle (lengthYears, Years) ModifiedFollowing False
  fixedSch <- schedule (Just settle) maturity (1, Years) cal Unadjusted Unadjusted Forward False Nothing Nothing
  floatSch <- schedule (Just settle) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing
    Forward False Nothing Nothing
  swp <- vanillaSwap Payer 100 fixedSch fixedRate fixedDC floatSch idx floatingSpread floatDC Nothing Nothing
  eng <- discountingSwapEngine ts Nothing Nothing Nothing
  setPricingEngine swp eng
  pure swp

spec :: Spec
spec = do
  describe "VanillaSwap" $ do
    it "testCachedValue: 10Y swap NPV reproduces swap.cpp's cached value (either at-par or\
       \ index-fixing coupon pricing, since hasquant has no binding to select between them)" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just (17 `june` 2002))
        swp <- makeSwap (17 `june` 2002) 10 0.06 0.001
        v <- npv swp
        v `shouldSatisfy` (\x -> closePrec (-5.872863313209) 1e-8 x || closePrec (-5.872342992212) 1e-8 x)

    it "testFairRate: rebuilding at the swap's own fairRate reprices it to ~0" $
      Settings.keepingSettings' $ do
        today' <- today
        Settings.setEvaluationDate (Just today')
        mapM_ (\(len, spread) -> do
                 swap0 <- makeSwap today' len 0.0 spread
                 fair <- fairRate swap0
                 swap1 <- makeSwap today' len fair spread
                 v <- npv swap1
                 v `shouldSatisfy` closePrec 0 1.0e-8)
          [(len, spread) | len <- [1, 2, 5, 10, 20], spread <- [-0.001, -0.01, 0.0, 0.01, 0.001]]

    it "testFairSpread: rebuilding at the swap's own fairSpread reprices it to ~0" $
      Settings.keepingSettings' $ do
        today' <- today
        Settings.setEvaluationDate (Just today')
        mapM_ (\(len, rate) -> do
                 swap0 <- makeSwap today' len rate 0.0
                 fair <- fairSpread swap0
                 swap1 <- makeSwap today' len rate fair
                 v <- npv swap1
                 v `shouldSatisfy` closePrec 0 1.0e-8)
          [(len, rate) | len <- [1, 2, 5, 10, 20], rate <- [0.04, 0.05, 0.06, 0.07]]

  describe "ConstNotionalCrossCurrency{Swap,BasisSwap,FixedVsFloatingSwap}" $
    it "symmetric legs (same index/schedule/nominal/spread, matching curves, spotFX=1) NPV to zero" $
      Settings.keepingSettings' $ do
        let today' = 11 `september` 2018
        cal <- calendar UnitedStatesSettlement
        Settings.setEvaluationDate (Just today')

        usd <- currency USD
        eur <- currency EUR
        flatDC <- dayCounter Actual365FixedStandard
        q <- simpleQuote 0.03
        curve <- flatForward today' q flatDC Continuous Annual
        fxQuote <- simpleQuote 1.0
        legDC <- dayCounter (Actual360 False)
        usdLibor3m <- IR.iborIndex (IR.UsdLibor (3, Months)) (Just curve)

        spot <- advance cal today' (2, Days) Following False
        maturity <- advance cal spot (5, Years) Following False
        sched <- schedule (Just spot) maturity (3, Months) cal ModifiedFollowing ModifiedFollowing
          Forward False Nothing Nothing

        engine <- discountingConstNotionalCrossCurrencySwapEngine usd curve eur curve fxQuote
          (Just False) (Just today') (Just today') Nothing

        -- identical index/schedule/nominal/spread on both legs, one tagged USD, the other EUR --
        -- symmetric under the shared curve + spotFX=1.
        basisSwap <- constNotionalCrossCurrencyBasisSwap 100 usd sched usdLibor3m 0 1
          100 eur sched usdLibor3m 0 1 defaultConstNotionalCrossCurrencyBasisSwapOpts
        setPricingEngine basisSwap engine
        basisNPV <- npv basisSwap
        basisNPV `shouldSatisfy` closePrec 0 1e-6
        payFair <- fairPaySpread basisSwap
        payFair `shouldSatisfy` closePrec 0 1e-6
        recFair <- fairRecSpread basisSwap
        recFair `shouldSatisfy` closePrec 0 1e-6

        -- base-class getters, reached generically over the leaf.
        payCcy <- legCurrency basisSwap 0
        show payCcy `shouldBe` show usd
        inCcyNpv0 <- inCcyLegNPV basisSwap 0
        inCcyNpv1 <- inCcyLegNPV basisSwap 1
        inCcyNpv1 `shouldSatisfy` closePrec inCcyNpv0 1e-6

        -- ConstNotionalCrossCurrencyFixedVsFloatingSwap: solve the fair fixed rate against a
        -- first guess, then rebuild at that rate and confirm the rebuilt swap reprices to zero.
        guess <- constNotionalCrossCurrencyFixedVsFloatingSwap Payer 100 usd sched 0.03 legDC
          ModifiedFollowing 0 cal 100 eur sched usdLibor3m 0 ModifiedFollowing 0 cal
          False False Nothing False 0 AveragingCompound
        setPricingEngine guess engine
        fair <- xccyFairRate guess

        priced <- constNotionalCrossCurrencyFixedVsFloatingSwap Payer 100 usd sched fair legDC
          ModifiedFollowing 0 cal 100 eur sched usdLibor3m 0 ModifiedFollowing 0 cal
          False False Nothing False 0 AveragingCompound
        setPricingEngine priced engine
        pricedNPV <- npv priced
        pricedNPV `shouldSatisfy` closePrec 0 1e-6

  -- Ported from test-suite/assetswap.cpp::testConsistency's par-asset-swap portion (the
  -- NpvDate-sensitivity half of that test, and the market/non-par asset-swap cases from later
  -- in the same file, are left as follow-up work). The float schedule is rebuilt from the
  -- bond's own start/maturity here rather than passed as upstream's empty default Schedule (no
  -- hasquant binding exposes that "derive the schedule from the bond" constructor path) -- a
  -- self-consistency check either way, so any valid schedule matching the index's tenor works.
  describe "AssetSwap" $
    it "fairCleanPrice and fairSpread both reprice the par asset swap to zero NPV" $
      Settings.keepingSettings' $ do
        let evalDate = 24 `april` 2007
        Settings.setEvaluationDate (Just evalDate)
        cal <- calendar TARGET
        discDC <- dayCounter Actual365FixedStandard
        q <- simpleQuote 0.05
        ts <- flatForward evalDate q discDC Continuous Annual
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
        floatDC <- dayCounter (Actual360 False)

        let bondStart = 4 `january` 2005
            bondMaturity = 4 `january` 2037
        bondSch <- schedule (Just bondStart) bondMaturity (1, Years) cal Unadjusted Unadjusted Backward False Nothing Nothing
        aaISDA <- dayCounter ActualActualISDA
        bond <- fixedRateBond 3 100.0 bondSch [0.04] aaISDA Following 100.0 (Just bondStart) cal
          (0, Days) cal Unadjusted False aaISDA >>= asBond
        settle <- settlementDate bond evalDate

        floatSch <- schedule (Just settle) bondMaturity (6, Months) cal ModifiedFollowing ModifiedFollowing
          Forward False Nothing Nothing

        swapEngine <- discountingSwapEngine ts (Just True) (Just settle) (Just evalDate)

        let bondPrice = 95.0
        parAssetSwap <- assetSwap True bond bondPrice euribor6m 0.0 floatSch floatDC True 1.0 Nothing Nothing
        setPricingEngine parAssetSwap swapEngine
        fcp <- fairCleanPrice parAssetSwap
        fsp <- fairSpread parAssetSwap

        assetSwap2 <- assetSwap True bond fcp euribor6m 0.0 floatSch floatDC True 1.0 Nothing Nothing
        setPricingEngine assetSwap2 swapEngine
        npv2 <- npv assetSwap2
        npv2 `shouldSatisfy` closePrec 0 1e-6
        fcp2 <- fairCleanPrice assetSwap2
        fcp2 `shouldSatisfy` closePrec fcp 1e-6
        fsp2 <- fairSpread assetSwap2
        fsp2 `shouldSatisfy` closePrec 0.0 1e-6

        assetSwap3 <- assetSwap True bond bondPrice euribor6m fsp floatSch floatDC True 1.0 Nothing Nothing
        setPricingEngine assetSwap3 swapEngine
        npv3 <- npv assetSwap3
        npv3 `shouldSatisfy` closePrec 0 1e-6

  -- Ported from test-suite/zerocouponswap.cpp's spot-starting cases only (checkFairFixedPayment
  -- and checkFairFixedRate): a swap starting exactly at settlement needs no historical Euribor
  -- fixing, unlike the "ongoing" cases in the same functions, which are left as follow-up work.
  describe "ZeroCouponSwap" $ do
    it "fairFixedPayment and fairFixedRate both reprice a spot-starting swap to zero NPV" $
      Settings.keepingSettings' $ do
        let today' = 15 `march` 2021
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        dc <- dayCounter Actual365FixedStandard
        settle <- advance cal today' (2, Days) Following False
        q <- simpleQuote 0.007
        ts <- flatForward settle q dc Continuous Annual
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)

        let paymentDelay = 1 :: Word
            end = 12 `february` 2041

        engine <- discountingSwapEngine ts Nothing Nothing Nothing

        zc <- zeroCouponSwap Payer 1.0e6 settle end 1.2e6 euribor6m cal ModifiedFollowing paymentDelay
        setPricingEngine zc engine
        fairPmt <- fairFixedPayment zc

        parZc <- zeroCouponSwap Payer 1.0e6 settle end fairPmt euribor6m cal ModifiedFollowing paymentDelay
        setPricingEngine parZc engine
        parNpv <- npv parZc
        parNpv `shouldSatisfy` closePrec 0 1e-6

        fairRt <- fairFixedRate zc dc
        parZc' <- zeroCouponSwap' Receiver 1.0e6 settle end fairRt dc euribor6m cal ModifiedFollowing paymentDelay
        setPricingEngine parZc' engine
        parNpv' <- npv parZc'
        parNpv' `shouldSatisfy` closePrec 0 1e-6

    -- ZeroCouponSwap::fixedLegNPV/floatingLegNPV are literally legNPV_[0]/legNPV_[1] upstream
    -- (zerocouponswap.cpp), i.e. exactly the already-bound generic leg 0/1 legNPV -- so this
    -- checks the *identity* claim rather than binding a redundant getter.
    it "fixedLegNPV/floatingLegNPV equal the generic leg 0/1 legNPV, and sum to the swap's NPV" $
      Settings.keepingSettings' $ do
        let today' = 15 `march` 2021
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        dc <- dayCounter Actual365FixedStandard
        settle <- advance cal today' (2, Days) Following False
        q <- simpleQuote 0.007
        ts <- flatForward settle q dc Continuous Annual
        euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
        engine <- discountingSwapEngine ts Nothing Nothing Nothing
        let end = 12 `february` 2041
        zc <- zeroCouponSwap Payer 1.0e6 settle end 1.2e6 euribor6m cal ModifiedFollowing (1 :: Word)
        setPricingEngine zc engine
        fixedNPV <- legNPV zc 0
        floatNPV <- legNPV zc 1
        total <- npv zc
        (fixedNPV + floatNPV) `shouldSatisfy` closePrec total 1e-8
