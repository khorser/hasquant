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
module QuantLib.Spec.Instrument.Swap (spec) where

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Currency
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Instrument
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
  swap <- vanillaSwap Payer 100 fixedSch fixedRate fixedDC floatSch idx floatingSpread floatDC Nothing Nothing
  eng <- discountingSwapEngine ts Nothing Nothing Nothing
  setPricingEngine swap eng
  pure swap

spec :: Spec
spec = do
  describe "VanillaSwap" $ do
    it "testCachedValue: 10Y swap NPV reproduces swap.cpp's cached value (either at-par or\
       \ index-fixing coupon pricing, since hasquant has no binding to select between them)" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just (17 `june` 2002))
        swap <- makeSwap (17 `june` 2002) 10 0.06 0.001
        v <- npv swap
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
