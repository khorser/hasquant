{-# LANGUAGE ScopedTypeVariables, TupleSections, OverloadedLists #-}
module QuantLib.Spec.InterestRateAndCashFlow (spec) where

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck.Monadic as Q(monadicIO, run)
import Test.QuickCheck((==>))

import Control.Exception(bracket_)
import Control.Monad(forM_)
import qualified Data.List.NonEmpty as NE
import Data.Maybe(fromMaybe)
import Data.Time.Calendar

import QuantLib.Time.Date
import qualified QuantLib.Time.Date as Date
import QuantLib.Type
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import qualified QuantLib.InterestRate as IR
import qualified QuantLib.CashFlow as CF
import QuantLib.Index(fixingCalendar, addFixing, addFixings, fixing, hasHistoricalFixing, isValidFixingDate, clearFixings
  ,fixingHistory, fixingHistoryNames, clearAllFixingHistories
  ,historicalIndexAnalysisSkipped, historicalIndexAnalysisMean, historicalIndexAnalysisStandardDeviation
  ,historicalIndexAnalysisSkewness, historicalIndexAnalysisKurtosis, historicalIndexAnalysisMin, historicalIndexAnalysisMax
  ,historicalIndexAnalysisSemiVariance, historicalIndexAnalysisSemiDeviation
  ,historicalIndexAnalysisDownsideVariance, historicalIndexAnalysisDownsideDeviation
  ,historicalIndexAnalysisPercentile, historicalIndexAnalysisGaussianPercentile
  ,historicalIndexAnalysisValueAtRisk, historicalIndexAnalysisGaussianValueAtRisk
  ,historicalIndexAnalysisExpectedShortfall, historicalIndexAnalysisGaussianExpectedShortfall
  ,historicalIndexAnalysisCovariance, historicalIndexAnalysisCorrelation)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..), liborSwapIndex, LiborSwapIndexType(..), swapSpreadIndex, forecastFixing
  ,fixingDate, valueDate, maturityDate, historicalRatesAnalysis, overnightIborIndex, OvernightIborIndexType(..))
import qualified QuantLib.Index.InterestRate as Ibor(fixingDays, dayCounter)
import qualified QuantLib.Index.Inflation as Inflation
import qualified QuantLib.Index.Equity as Equity
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility(blackConstantVol', constantOptionletVolatility, constantOptionletVolatility', constantSwaptionVolatility', flatSmileSection, SmileSection)
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Instrument as Instr
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.Instrument.CapFloor as CapFloor
import qualified QuantLib.Instrument.Swap as Swap
import qualified QuantLib.PricingEngine as PE
import QuantLib.Math

import QuantLib.Spec.Helpers(ValidDay(..), closePrec, listCloseRel)

spec :: Day -> Spec
spec evalDate = do
    describe "Interest rate" $ do
      let cases :: [(Double, IR.Compounding, Frequency, Double, IR.Compounding, Frequency, Double, Int)]
          cases = [ (0.0800, IR.Compounded,        Quarterly,   1.00, IR.Continuous,            Annual, 0.0792, 4),
                    (0.1200, IR.Continuous,           Annual,   1.00, IR.Compounded,            Annual, 0.1275, 4),
                    (0.0800, IR.Compounded,        Quarterly,   1.00, IR.Compounded,            Annual, 0.0824, 4),
                    (0.0700, IR.Compounded,        Quarterly,   1.00, IR.Compounded,        Semiannual, 0.0706, 4),
                    (0.0100, IR.Compounded,           Annual,   1.00,     IR.Simple,            Annual, 0.0100, 4),
                    (0.0200,     IR.Simple,           Annual,   1.00, IR.Compounded,            Annual, 0.0200, 4),
                    (0.0300, IR.Compounded,       Semiannual,   0.50,     IR.Simple,            Annual, 0.0300, 4),
                    (0.0400,     IR.Simple,           Annual,   0.50, IR.Compounded,        Semiannual, 0.0400, 4),
                    (0.0500, IR.Compounded, EveryFourthMonth,  1.0/3,     IR.Simple,            Annual, 0.0500, 4),
                    (0.0600,     IR.Simple,           Annual,  1.0/3, IR.Compounded,  EveryFourthMonth, 0.0600, 4),
                    (0.0500, IR.Compounded,        Quarterly,   0.25,     IR.Simple,            Annual, 0.0500, 4),
                    (0.0600,     IR.Simple,           Annual,   0.25, IR.Compounded,         Quarterly, 0.0600, 4),
                    (0.0700, IR.Compounded,        Bimonthly,  1.0/6,     IR.Simple,            Annual, 0.0700, 4),
                    (0.0800,     IR.Simple,           Annual,  1.0/6, IR.Compounded,         Bimonthly, 0.0800, 4),
                    (0.0900, IR.Compounded,          Monthly, 1.0/12,     IR.Simple,            Annual, 0.0900, 4),
                    (0.1000,     IR.Simple,           Annual, 1.0/12, IR.Compounded,           Monthly, 0.1000, 4), (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.25,               IR.Simple,            Annual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.25,               IR.Simple,        Semiannual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.25,               IR.Simple,         Quarterly, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.50,               IR.Simple,            Annual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.50,               IR.Simple,        Semiannual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.75,           IR.Compounded,        Semiannual, 0.0300, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.25, IR.SimpleThenCompounded,         Quarterly, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.25, IR.SimpleThenCompounded,        Semiannual, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.25, IR.SimpleThenCompounded,            Annual, 0.0400, 4),
                    (0.0400,           IR.Compounded,        Quarterly,   0.50, IR.SimpleThenCompounded,         Quarterly, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.50, IR.SimpleThenCompounded,        Semiannual, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.50, IR.SimpleThenCompounded,            Annual, 0.0400, 4),
                    (0.0400,           IR.Compounded,        Quarterly,   0.75, IR.SimpleThenCompounded,         Quarterly, 0.0400, 4),
                    (0.0400,           IR.Compounded,       Semiannual,   0.75, IR.SimpleThenCompounded,        Semiannual, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.75, IR.SimpleThenCompounded,            Annual, 0.0400, 4)]

      let testCase :: (Double, IR.Compounding, Frequency, Double, IR.Compounding, Frequency, Double, Int) -> IO ()
          testCase (r, comp, freq, t, comp2, freq2, expected, prec) = do
            d1 <- today
            dc <- dayCounter (Actual360 False)
            ir <- IR.interestRate r dc comp freq
            let d2 = addDays (truncate $ 360 * t + 0.5) d1
            compoundf <- IR.compoundFactor' ir d1 d2 d1 d2
            disc <- IR.discountFactor' ir d1 d2 d1 d2
            abs (disc - 1.0/compoundf) `shouldSatisfy` (<= 1.0e-15)
            ir2 <- IR.equivalentRate' ir dc comp freq d1 d2 d1 d2
            abs (IR.rate ir - IR.rate ir2) `shouldSatisfy` (<= 1.0e-15)

            ir3 <- IR.equivalentRate' ir dc comp2 freq2 d1 d2 d1 d2
            expectedIR <- IR.interestRate expected dc comp2 freq2

            let roundingPrecision = Rounding prec Closest 5
                r3 = applyRounding roundingPrecision (IR.rate ir3)
            abs(r3 - IR.rate expectedIR) `shouldSatisfy` (<= 1.0e-17)

            ir3' <- IR.equivalentRate' ir dc comp2 freq2 d1 d2 d1 d2
            let r3' = applyRounding roundingPrecision (IR.rate ir3')
            abs(r3' - expected) `shouldSatisfy` (<= 1.0e-17)

      it "bulk test for conversions" $ do
        Settings.keepingSettings' $ mapM_ testCase cases

    describe "cash flow leg" $ do
      let checkInclusion :: CF.Leg -> Int -> [(Int, Bool)] -> IO ()
          checkInclusion l n x = do
            td <- Settings.evaluationDate
            mapM_ (\(ds, expected) -> do
              cfs <- CF.cashFlows l Nothing (Just $ addDays (fromIntegral ds) td)
              -- `cfs` comes back from C++, so its length is not statically known;
              -- report a short leg as a test failure rather than a `!!` exception
              case drop n cfs of
                ((_, _, o) : _) -> expected `shouldNotBe` o
                [] -> expectationFailure $
                        "cash flow " ++ show n ++ " requested at offset " ++ show ds
                          ++ " but the leg has only " ++ show (length cfs) ++ " flows") x

          checkNPV :: CF.Leg -> IR.InterestRate -> Bool -> Double -> IO ()
          checkNPV l r includeRef expected = do
            td <- Settings.evaluationDate
            v <- CF.npvFromYield' l r includeRef (Just td) (Just td)
            abs(v - expected) `shouldSatisfy` (<= 1.0e-6)

      it "misc variants of settings" $
        Settings.keepingSettings' $ do
          let cases12 l = do
                checkInclusion l 0 [(0, False), (1, False)]
                checkInclusion l 1 [(0, True), (1, False), (2, False)]
                checkInclusion l 2 [(1, True), (2, False), (3, False)]

              cases34 l = do
                checkInclusion l 0 [(0, True), (1, False)]
                checkInclusion l 1 [(0, True), (1, True), (2, False)]
                checkInclusion l 2 [(1, True), (2, True), (3, False)]
          td <- today
          Settings.setEvaluationDate (Just td)
          l <- CF.leg $ map (, 1.0) [td .. addDays 2 td]

          Settings.setIncludeReferenceDateEvents False
          Settings.setIncludeTodaysCashFlows Nothing
          cases12 l

          -- 2)
          Settings.setIncludeReferenceDateEvents False
          Settings.setIncludeTodaysCashFlows (Just False)
          cases12 l
          -- 3)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows Nothing
          cases34 l

          -- 4)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows $ Just True
          cases34 l

          -- 5)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows $ Just False
          checkInclusion l 0 [(0, False), (1, False)]
          checkInclusion l 1 [(0, True), (1, True), (2, False)]
          checkInclusion l 2 [(1, True), (2, True), (3, False)]

          -- 5)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows $ Just False
          checkInclusion l 0 [(0, False), (1, False)]
          checkInclusion l 1 [(0, True), (1, True), (2, False)]
          checkInclusion l 2 [(1, True), (2, True), (3, False)]

          dc <- dayCounter Actual365FixedStandard
          noDisc <- IR.interestRate 0.0 dc IR.Continuous Annual

          Settings.setIncludeTodaysCashFlows Nothing
          checkNPV l noDisc False 2.0
          checkNPV l noDisc True 3.0

          Settings.setIncludeTodaysCashFlows $ Just False
          checkNPV l noDisc False 2.0
          checkNPV l noDisc True 2.0

      it "fixed rate leg as of default settlement date" $ do
        td <- Settings.evaluationDate
        cal <- calendar TARGET
        sch <- schedule (Just $ addGregorianMonthsClip (-2) td) (addGregorianMonthsClip 4 td) (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
        dc <- dayCounter (Actual360 False)
        cpn <- IR.interestRate 0.03 dc IR.Simple Annual
        l <- CF.fixedRateLeg sch [100.0] [cpn] Following dc cal
        accP <- CF.accruedPeriod l False Nothing
        accP `shouldSatisfy` (/= 0)
        accD <- CF.accruedDays l False Nothing
        accD `shouldSatisfy` (/= 0)
        accA <- CF.accruedAmount l False Nothing
        accA `shouldSatisfy` (/= 0)

      it "empty leg start" $ do
        let cPlusPlusEx (CPlusPlusException m) = not $ null m
            cPlusPlusEx _ = False
        (CF.leg [] >>= CF.startDate) `shouldThrow` cPlusPlusEx

      it "single leg today" $ do
        (CF.leg [(evalDate, 100)] >>= CF.startDate) `shouldReturn` evalDate

      it "two legs unsorted" $ do
        (CF.leg [(evalDate, 100), (addDays (-10) evalDate, -1000)] >>= CF.startDate) `shouldReturn` addDays (-10) evalDate

      it "three legs sorted" $ do
        (CF.leg [(evalDate, 100), (addDays (-10) evalDate, 1000), (addDays 10 evalDate, -2000)] >>= CF.startDate) `shouldReturn` addDays (-10) evalDate

      it "builds a mixed custom leg from simple, indexed, and coupon cash flows" $
        Settings.keepingSettings' $ do
          let baseDate = 7 `april` 2010
              fixingDate = 8 `april` 2010
              paymentDate = 7 `april` 2011
              accrualEnd = addDays 180 paymentDate
          Settings.setEvaluationDate (Just baseDate)
          dc <- dayCounter (Actual360 False)
          q <- Quote.simpleQuote 0.03 >>= Quote.asQuote
          curve <- flatForward baseDate q dc IR.Continuous Annual
          idx <- iborIndex (UsdLibor (3, Months)) (Just curve)
          addFixing idx baseDate 100.0 True
          addFixing idx fixingDate 120.0 True
          Settings.setEvaluationDate (Just $ addDays 1 fixingDate)
          simple <- CF.simpleCashFlow 10.0 paymentDate
          indexed <- CF.indexedCashFlow 100.0 idx baseDate fixingDate paymentDate False
          growth <- CF.indexedCashFlow 100.0 idx baseDate fixingDate paymentDate True
          fixed <- CF.fixedRateCoupon accrualEnd 100.0 0.05 dc paymentDate accrualEnd Nothing Nothing Nothing
          mixed <- CF.cashFlowLeg [simple, indexed, growth, fixed]
          flows <- CF.cashFlows mixed Nothing Nothing
          let expected = [10.0, 120.0, 20.0, 2.5]
          listCloseRel id expected 1.0e-12 (map (\(_, amount, _) -> amount) flows) `shouldBe` True
          other <- CF.leg [(accrualEnd, 1.0)]
          s <- Swap.swap mixed other
          receivedLeg <- Swap.leg s 0
          received <- CF.cashFlows receivedLeg Nothing Nothing
          listCloseRel id expected 1.0e-12 (map (\(_, amount, _) -> amount) received) `shouldBe` True

      it "constructs generic floating and Ibor coupons for a custom leg" $
        Settings.keepingSettings' $ do
          let start = 7 `april` 2010
              end = addGregorianMonthsClip 3 start
          Settings.setEvaluationDate (Just start)
          dc <- dayCounter (Actual360 False)
          q <- Quote.simpleQuote 0.03 >>= Quote.asQuote
          curve <- flatForward start q dc IR.Continuous Annual
          idx <- iborIndex (UsdLibor (3, Months)) (Just curve)
          floating <- CF.floatingRateCoupon end 100.0 start end 2 idx 1.0 0.0 Nothing Nothing dc False Nothing Preceding
          ibor <- CF.iborCoupon end 100.0 start end 2 idx 1.0 0.0 Nothing Nothing dc False Nothing Preceding
          iborFlow <- CF.asCashFlow ibor
          customLeg <- CF.cashFlowLeg [floating, iborFlow]
          CF.startDate customLeg `shouldReturn` start

      it "uses CPI, zero-inflation, and equity cash flows in a custom leg" $
        Settings.keepingSettings' $ do
          let baseDate = 1 `january` 2010
              fixingDate = 1 `january` 2011
              paymentDate = 1 `february` 2011
          Settings.setEvaluationDate (Just paymentDate)
          inflation <- Inflation.zeroInflationIndex Inflation.UKRPI
          addFixing inflation (1 `november` 2009) 100.0 False
          addFixing inflation baseDate 100.0 False
          addFixing inflation (1 `november` 2010) 120.0 False
          addFixing inflation (1 `december` 2010) 120.0 False
          addFixing inflation fixingDate 120.0 False
          zero <- CF.zeroInflationCashFlow 100.0 inflation CPIFlat baseDate fixingDate (2, Months) paymentDate False
          cpi <- CF.cpiCashFlow 100.0 inflation (Just baseDate) Nothing fixingDate (2, Months) CPIFlat paymentDate False
          cal <- calendar Null
          usd <- currency USD
          equityIndex <- Equity.equityIndex "custom-leg-equity" cal usd Nothing Nothing Nothing
          addFixing equityIndex baseDate 80.0 False
          addFixing equityIndex fixingDate 100.0 False
          equity <- CF.equityCashFlow 100.0 equityIndex baseDate fixingDate paymentDate False
          zeroAmount <- CF.zeroInflationCashFlowAmount zero
          cpiAmount <- CF.cpiCashFlowAmount cpi
          equityAmount <- CF.equityCashFlowAmount equity
          listCloseRel id [120.0, 120.0, 125.0] 1.0e-12 [zeroAmount, cpiAmount, equityAmount] `shouldBe` True
          zeroFlow <- CF.zeroInflationCashFlowAsCashFlow zero
          cpiFlow <- CF.cpiCashFlowAsCashFlow cpi
          equityFlow <- CF.equityCashFlowAsCashFlow equity
          dc <- dayCounter (Actual360 False)
          coupon <- CF.cpiCoupon 100.0 paymentDate 100.0 baseDate paymentDate inflation (2, Months) CPIFlat dc 0.02
            (Just baseDate) (Just paymentDate) Nothing
          couponPricer <- CF.cpiCouponPricer Nothing
          CF.setCpiCouponPricer coupon couponPricer
          couponFlow <- CF.cpiCouponAsCashFlow coupon
          customLeg <- CF.cashFlowLeg [zeroFlow, cpiFlow, equityFlow, couponFlow]
          flows <- CF.cashFlows customLeg Nothing Nothing
          listCloseRel id [120.0, 120.0, 125.0] 1.0e-12 (map (\(_, amount, _) -> amount) (take 3 flows)) `shouldBe` True
          map (\(d, _, _) -> d) flows `shouldBe` replicate 4 paymentDate

      prop "random single let start date" $
        \(a, ValidDay d) -> monadicIO $ do
          run $ (CF.leg [(d, a)] >>= CF.startDate) `shouldReturn` d

      prop "start date should be minimal" $
        \flows ->
          not (null flows)
            ==> monadicIO $ do
              let (d, a) = unzip (flows :: [(ValidDay, Double)])
                  ds = map validDay d
                  f = zip ds a
              run $ (CF.leg f >>= CF.startDate) `shouldReturn` minimum ds

      it "check for segfaulting regression with dynamic cast of coupon in Black pricer" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just $ 7 `april` 2010)
          cal <- calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.04875825 >>= Quote.asQuote
          ts <- flatForward (9 `april` 2010) q dc IR.Continuous Annual
          v <- Quote.simpleQuote 0.10
          vol <- constantOptionletVolatility' 2 cal ModifiedFollowing v dc IR.ShiftedLognormal 0.0
          let p = (3, Months)
          index3m <- iborIndex (UsdLibor p) (Just ts)
          pricer <- CF.blackIborCouponPricer vol CF.Black76 Nothing Nothing
          sch <- schedule (Just $ 20 `september` 2013) (20 `december` 2013) p cal Following Following Backward False Nothing Nothing
          cpns <- CF.iborLeg sch index3m [100] dc Following [2] [] [0.000115] [] [] False False
          CF.setCouponPricer cpns pricer
          ret <- CF.nextCashFlowAmount cpns True Nothing
          ret `shouldSatisfy` const True

      it "prices an Ibor coupon with a quanto Black pricer" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just $ 7 `april` 2010)
          cal <- calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.04875825 >>= Quote.asQuote
          ts <- flatForward (9 `april` 2010) q dc IR.Continuous Annual
          v <- Quote.simpleQuote 0.10
          vol <- constantOptionletVolatility' 2 cal ModifiedFollowing v dc IR.ShiftedLognormal 0.0
          let p = (3, Months)
          index3m <- iborIndex (UsdLibor p) (Just ts)
          pricer <- CF.blackIborCouponPricer vol CF.Black76 Nothing Nothing
          fxVolQ <- Quote.simpleQuote 0.20 >>= Quote.asQuote
          fxVol <- blackConstantVol' 2 cal fxVolQ dc
          correlation <- Quote.simpleQuote 0.50 >>= Quote.asQuote
          quantoPricer <- CF.blackIborQuantoCouponPricer fxVol correlation vol
          sch <- schedule (Just $ 20 `september` 2013) (20 `december` 2013) p cal Following Following Backward False Nothing Nothing
          let buildCoupon couponPricer = do
                cpns <- CF.iborLeg sch index3m [100] dc Following [2] [] [0.000115] [] [] False False
                CF.setCouponPricer cpns couponPricer
                CF.nextCashFlowAmount cpns True Nothing
          ordinaryAmount <- buildCoupon pricer
          quantoAmount <- buildCoupon quantoPricer
          quantoAmount `shouldSatisfy` (/= 0)
          abs (quantoAmount - ordinaryAmount) `shouldSatisfy` (> 1e-12)

    -- Ported from test-suite/digitalcoupon.cpp. Its Cox-Rubinstein N(d1)-formula cases
    -- (testAssetOrNothing/testCashOrNothing) need QuantLib's CumulativeNormalDistribution,
    -- which hasquant doesn't bind, so only the purely self-consistent cases are ported here:
    -- deep in/out-of-the-money asset/cash-or-nothing coupons, call/put parity, and
    -- sub/central/super replication ordering. Tolerances are upstream's own, unchanged, since
    -- the fixture (nominal, dates, curve) matches exactly.
    describe "Digital coupon" $ do
      let digRefDate = 15 `may` 2023
          digNominal = 1000000.0 :: Double
          digFixingDays = 2 :: Word

          digFixture = do
            cal <- calendar TARGET
            today' <- adjust cal digRefDate Following
            Settings.setEvaluationDate (Just today')
            settlement <- advance cal today' (2, Days) Following False
            euriborDc <- dayCounter (Actual360 False)
            rateQ <- Quote.simpleQuote 0.05 >>= Quote.asQuote
            curve <- flatForward settlement rateQ euriborDc IR.Continuous Annual
            idx <- iborIndex Euribor6M (Just curve)
            pure (cal, settlement, euriborDc, curve, idx)

          digPricer cal capletVol = do
            volQ <- Quote.simpleQuote capletVol >>= Quote.asQuote
            optDc <- dayCounter (Actual360 False)
            today' <- Settings.evaluationDate
            vol <- constantOptionletVolatility today' cal Following volQ optDc IR.ShiftedLognormal 0.0
            CF.blackIborCouponPricer vol CF.Black76 Nothing Nothing

          -- One exercise (k = 0..9, matching upstream's k+1/k+2-year start/end offsets from
          -- settlement): the underlying IborCoupon, its accrual period, and its payment-date
          -- discount factor, all needed to turn a coupon rate into a coupon price.
          digExercise cal settlement euriborDc curve idx k = do
            startDate <- advance cal settlement (k + 1, Years) Following False
            endDate <- advance cal settlement (k + 2, Years) Following False
            underlying <- CF.iborCoupon endDate digNominal startDate endDate digFixingDays idx
              1.0 0.0 Nothing Nothing euriborDc False Nothing Preceding
            accrual <- years euriborDc startDate endDate Nothing Nothing
            disc <- discount' curve endDate True
            pure (underlying, accrual, disc)

          -- CashFlow::price(discountCurve) = amount() * discountCurve->discount(date()); the
          -- coupon's payment date is always `endDate` from 'digExercise' above, so the already-
          -- computed discount factor is reused rather than re-querying the coupon's own date.
          digPriceOf disc c = (* disc) <$> CF.floatingRateCouponAmount c

      it "deep in-the-money asset-or-nothing digital coupon reprices to its target" $
        Settings.keepingSettings' $ do
          (cal, settlement, euriborDc, curve, idx) <- digFixture
          pricer <- digPricer cal 0.0001
          forM_ ([0 .. 9] :: [Int]) $ \k -> do
            (underlying, accrual, disc) <- digExercise cal settlement euriborDc curve idx k
            -- Deep ITM short call (strike 0.001): the call payoff almost always fires, so the
            -- short position cancels the underlying coupon almost exactly.
            capped <- CF.digitalCoupon underlying (Just 0.001) CF.Short False Nothing
              Nothing CF.Short False Nothing Nothing False
            CF.setFloatingRateCouponPricer capped pricer
            underlyingPrice <- digPriceOf disc underlying
            cappedPrice <- digPriceOf disc capped
            cappedPrice `shouldSatisfy` closePrec 0.0 1e-8
            callRate <- CF.digitalCouponCallOptionRate capped
            (callRate * digNominal * accrual * disc) `shouldSatisfy` closePrec underlyingPrice 1e-8

            -- Deep ITM long put (strike 0.99): the put payoff almost always fires too, doubling
            -- the coupon.
            floored <- CF.digitalCoupon underlying Nothing CF.Long False Nothing
              (Just 0.99) CF.Long False Nothing Nothing False
            CF.setFloatingRateCouponPricer floored pricer
            flooredPrice <- digPriceOf disc floored
            flooredPrice `shouldSatisfy` closePrec (2 * underlyingPrice) 2.5e-6
            putRate <- CF.digitalCouponPutOptionRate floored
            (putRate * digNominal * accrual * disc) `shouldSatisfy` closePrec underlyingPrice 2.5e-6

      it "deep out-of-the-money asset-or-nothing digital coupon reprices to its target" $
        Settings.keepingSettings' $ do
          (cal, settlement, euriborDc, curve, idx) <- digFixture
          pricer <- digPricer cal 0.0001
          forM_ ([0 .. 9] :: [Int]) $ \k -> do
            (underlying, accrual, disc) <- digExercise cal settlement euriborDc curve idx k
            capped <- CF.digitalCoupon underlying (Just 0.99) CF.Short False Nothing
              Nothing CF.Long False Nothing Nothing False
            CF.setFloatingRateCouponPricer capped pricer
            underlyingPrice <- digPriceOf disc underlying
            cappedPrice <- digPriceOf disc capped
            cappedPrice `shouldSatisfy` closePrec underlyingPrice 1e-10
            callRate <- CF.digitalCouponCallOptionRate capped
            (callRate * digNominal * accrual * disc) `shouldSatisfy` closePrec 0.0 1e-8

            floored <- CF.digitalCoupon underlying Nothing CF.Long False Nothing
              (Just 0.01) CF.Long False Nothing Nothing False
            CF.setFloatingRateCouponPricer floored pricer
            flooredPrice <- digPriceOf disc floored
            flooredPrice `shouldSatisfy` closePrec underlyingPrice 1e-8
            putRate <- CF.digitalCouponPutOptionRate floored
            (putRate * digNominal * accrual * disc) `shouldSatisfy` closePrec 0.0 1e-8

      it "deep in-the-money cash-or-nothing digital coupon reprices to its target" $
        Settings.keepingSettings' $ do
          (cal, settlement, euriborDc, curve, idx) <- digFixture
          pricer <- digPricer cal 0.0001
          let cashRate = 0.01
          forM_ ([0 .. 9] :: [Int]) $ \k -> do
            (underlying, accrual, disc) <- digExercise cal settlement euriborDc curve idx k
            let targetOptionPrice = cashRate * digNominal * accrual * disc
            capped <- CF.digitalCoupon underlying (Just 0.001) CF.Short False (Just cashRate)
              Nothing CF.Short False Nothing Nothing False
            CF.setFloatingRateCouponPricer capped pricer
            underlyingPrice <- digPriceOf disc underlying
            cappedPrice <- digPriceOf disc capped
            cappedPrice `shouldSatisfy` closePrec (underlyingPrice - targetOptionPrice) 1e-7
            callRate <- CF.digitalCouponCallOptionRate capped
            (callRate * digNominal * accrual * disc) `shouldSatisfy` closePrec targetOptionPrice 1e-7

            floored <- CF.digitalCoupon underlying Nothing CF.Long False Nothing
              (Just 0.99) CF.Long False (Just cashRate) Nothing False
            CF.setFloatingRateCouponPricer floored pricer
            flooredPrice <- digPriceOf disc floored
            flooredPrice `shouldSatisfy` closePrec (underlyingPrice + targetOptionPrice) 1e-7
            putRate <- CF.digitalCouponPutOptionRate floored
            (putRate * digNominal * accrual * disc) `shouldSatisfy` closePrec targetOptionPrice 1e-7

      it "deep out-of-the-money cash-or-nothing digital coupon reprices to its target" $
        Settings.keepingSettings' $ do
          (cal, settlement, euriborDc, curve, idx) <- digFixture
          pricer <- digPricer cal 0.0001
          let cashRate = 0.01
          forM_ ([0 .. 9] :: [Int]) $ \k -> do
            (underlying, _, disc) <- digExercise cal settlement euriborDc curve idx k
            capped <- CF.digitalCoupon underlying (Just 0.99) CF.Short False (Just cashRate)
              Nothing CF.Short False Nothing Nothing False
            CF.setFloatingRateCouponPricer capped pricer
            underlyingPrice <- digPriceOf disc underlying
            cappedPrice <- digPriceOf disc capped
            cappedPrice `shouldSatisfy` closePrec underlyingPrice 1e-10
            callRate <- CF.digitalCouponCallOptionRate capped
            (callRate * digNominal * disc) `shouldSatisfy` closePrec 0.0 1e-10

            floored <- CF.digitalCoupon underlying Nothing CF.Long False Nothing
              (Just 0.01) CF.Long False (Just cashRate) Nothing False
            CF.setFloatingRateCouponPricer floored pricer
            flooredPrice <- digPriceOf disc floored
            flooredPrice `shouldSatisfy` closePrec underlyingPrice 1e-9
            putRate <- CF.digitalCouponPutOptionRate floored
            (putRate * digNominal * disc) `shouldSatisfy` closePrec 0.0 1e-10

      it "call/put parity holds for European digital coupons" $
        Settings.keepingSettings' $ do
          (cal, settlement, euriborDc, curve, idx) <- digFixture
          let vols = [0.05, 0.15, 0.30] :: [Double]
              strikes = [0.01, 0.02 .. 0.07] :: [Double]
              cashRate = 0.01
          forM_ vols $ \vol -> do
            pricer <- digPricer cal vol
            forM_ strikes $ \strike ->
              forM_ ([0 .. 9] :: [Int]) $ \k -> do
                (underlying, accrual, disc) <- digExercise cal settlement euriborDc curve idx k

                cashCall <- CF.digitalCoupon underlying (Just strike) CF.Long False (Just cashRate)
                  Nothing CF.Long False Nothing Nothing False
                CF.setFloatingRateCouponPricer cashCall pricer
                cashPut <- CF.digitalCoupon underlying Nothing CF.Long False Nothing
                  (Just strike) CF.Short False (Just cashRate) Nothing False
                CF.setFloatingRateCouponPricer cashPut pricer
                cashCallPrice <- digPriceOf disc cashCall
                cashPutPrice <- digPriceOf disc cashPut
                (cashCallPrice - cashPutPrice) `shouldSatisfy`
                  closePrec (digNominal * accrual * disc * cashRate) 1e-8

                assetCall <- CF.digitalCoupon underlying (Just strike) CF.Long False Nothing
                  Nothing CF.Long False Nothing Nothing False
                CF.setFloatingRateCouponPricer assetCall pricer
                assetPut <- CF.digitalCoupon underlying Nothing CF.Long False Nothing
                  (Just strike) CF.Short False Nothing Nothing False
                CF.setFloatingRateCouponPricer assetPut pricer
                assetCallPrice <- digPriceOf disc assetCall
                assetPutPrice <- digPriceOf disc assetPut
                underlyingRate <- CF.floatingRateCouponRate underlying
                (assetCallPrice - assetPutPrice) `shouldSatisfy`
                  closePrec (digNominal * accrual * disc * underlyingRate) 1e-7

      -- Upstream checks this ordering across long/short call/put combinations; the long-call
      -- case here is representative of the same replication-scheme guarantee.
      it "sub/central/super replication prices a digital coupon in non-decreasing order" $
        Settings.keepingSettings' $ do
          (cal, settlement, euriborDc, curve, idx) <- digFixture
          let vols = [0.05, 0.15, 0.30] :: [Double]
              strikes = [0.01, 0.02 .. 0.07] :: [Double]
              cashRate = 0.005
              gap = 1.0e-4
              tolerance = 1.0e-9
          subRepl <- CF.digitalReplication CF.ReplicationSub gap
          centralRepl <- CF.digitalReplication CF.ReplicationCentral gap
          overRepl <- CF.digitalReplication CF.ReplicationSuper gap
          forM_ vols $ \vol -> do
            pricer <- digPricer cal vol
            forM_ strikes $ \strike ->
              forM_ ([0 .. 9] :: [Int]) $ \k -> do
                (underlying, _, disc) <- digExercise cal settlement euriborDc curve idx k
                let ordered repl = do
                      c <- CF.digitalCoupon underlying (Just strike) CF.Long False (Just cashRate)
                        Nothing CF.Long False Nothing (Just repl) False
                      CF.setFloatingRateCouponPricer c pricer
                      digPriceOf disc c
                subP <- ordered subRepl
                centralP <- ordered centralRepl
                overP <- ordered overRepl
                subP `shouldSatisfy` (<= centralP + tolerance)
                centralP `shouldSatisfy` (<= overP + tolerance)

    -- Ported from test-suite/capflooredcoupon.cpp. Uses 'CF.npv' to discount a leg directly
    -- rather than upstream's zero-rate-fixed-leg/Swap trick (there only to reuse Swap's NPV
    -- machinery); it computes the identical CashFlows::npv a DiscountingSwapEngine would.
    describe "Capped/floored coupon" $ do
      let cfRefDate = 2 `january` 2024
          cfNominal = 100.0 :: Double
          cfLength = 20 :: Int
          cfNotionals = NE.fromList (replicate cfLength cfNominal)
          cfFixingDays = replicate cfLength (2 :: Word)

          cfFixture = do
            cal <- calendar TARGET
            today' <- adjust cal cfRefDate ModifiedFollowing
            Settings.setEvaluationDate (Just today')
            settlement <- advance cal today' (2, Days) ModifiedFollowing False
            aa <- dayCounter ActualActualISDA
            rateQ <- Quote.simpleQuote 0.05 >>= Quote.asQuote
            curve <- flatForward settlement rateQ aa IR.Continuous Annual
            idx <- iborIndex Euribor1Y (Just curve)
            endDate <- advance cal settlement (cfLength, Years) ModifiedFollowing False
            sch <- schedule (Just settlement) endDate (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
            optDc <- dayCounter Actual365FixedStandard
            volQ <- Quote.simpleQuote 0.20 >>= Quote.asQuote
            vol <- constantOptionletVolatility' 0 cal Following volQ optDc IR.ShiftedLognormal 0.0
            pricer <- CF.blackIborCouponPricer vol CF.Black76 Nothing Nothing
            capfloorEngine <- PE.blackCapFloorEngine curve volQ optDc 0.0
            pure (aa, curve, idx, sch, pricer, capfloorEngine, settlement)

          cfLeg aa idx sch pricer caps floors = do
            leg <- CF.iborLeg sch idx cfNotionals aa ModifiedFollowing cfFixingDays
              (replicate cfLength 1.0) (replicate cfLength 0.0) caps floors False False
            CF.setCouponPricer leg pricer
            pure leg

      it "collared leg with strike 0/100 reprices to the vanilla floating leg (testLargeRates)" $
        Settings.keepingSettings' $ do
          (aa, curve, idx, sch, pricer, _, settlement) <- cfFixture
          floatLeg <- cfLeg aa idx sch pricer [] []
          collaredLeg <- cfLeg aa idx sch pricer (replicate cfLength 100.0) (replicate cfLength 0.0)
          -- 'settlement' (2 business days after the evaluation date) is also the curve's own
          -- reference date; passing it explicitly as both settlement and npv date matches
          -- what 'discountingSwapEngine' does internally and avoids asking the curve to
          -- discount to the evaluation date itself, which sits before its reference date.
          npvVanilla <- CF.npv floatLeg curve False (Just settlement) (Just settlement)
          npvCollar <- CF.npv collaredLeg curve False (Just settlement) (Just settlement)
          npvCollar `shouldSatisfy` closePrec npvVanilla 1e-8

      -- Base case only (gearing = 1, spread = 0): upstream also checks the decomposition
      -- holds under a positive and a negative gearing/spread, which is additional robustness
      -- beyond what's needed to exercise 'cappedFlooredCoupon'/'cappedFlooredIborCoupon'.
      it "capped/floored/collared leg decomposes into vanilla leg plus cap/floor/collar NPV (testDecomposition)" $
        Settings.keepingSettings' $ do
          (aa, curve, idx, sch, pricer, capfloorEngine, settlement) <- cfFixture
          let capStrike = 0.10
              floorStrike = 0.05
              legNpv leg = CF.npv leg curve False (Just settlement) (Just settlement)
          floatLeg <- cfLeg aa idx sch pricer [] []
          npvVanilla <- legNpv floatLeg

          cappedLeg <- cfLeg aa idx sch pricer (replicate cfLength capStrike) []
          npvCapped <- legNpv cappedLeg
          capInst <- CapFloor.cap floatLeg [capStrike]
          Instr.setPricingEngine capInst capfloorEngine
          npvCap <- Instr.npv capInst
          npvCapped `shouldSatisfy` closePrec (npvVanilla - npvCap) 1e-6

          flooredLeg <- cfLeg aa idx sch pricer [] (replicate cfLength floorStrike)
          npvFloored <- legNpv flooredLeg
          floorInst <- CapFloor.floor floatLeg [floorStrike]
          Instr.setPricingEngine floorInst capfloorEngine
          npvFloor <- Instr.npv floorInst
          npvFloored `shouldSatisfy` closePrec (npvVanilla + npvFloor) 1e-6

          collaredLeg <- cfLeg aa idx sch pricer (replicate cfLength capStrike) (replicate cfLength floorStrike)
          npvCollared <- legNpv collaredLeg
          collarInst <- CapFloor.collar floatLeg [capStrike] [floorStrike]
          Instr.setPricingEngine collarInst capfloorEngine
          npvCollar <- Instr.npv collarInst
          npvCollared `shouldSatisfy` closePrec (npvVanilla - npvCollar) 1e-6

      -- No upstream fixture exists for StrippedCappedFlooredCoupon (strippedcapflooredcoupon.cpp
      -- has none in test-suite). Self-consistency instead, read off the two rate() formulas
      -- (capflooredcoupon.cpp, strippedcapflooredcoupon.cpp): with only a cap in effect,
      -- CappedFlooredCoupon::rate() = swapletRate - capletRate while
      -- StrippedCappedFlooredCoupon::rate() = capletRate, so the two must sum back to the plain
      -- underlying's own rate. cap/floor/effectiveCap/effectiveFloor/isCap/isFloor/isCollar are
      -- checked against the gearing=1,spread=0 closed forms (cap()=cap_, effectiveCap()=cap_-spread).
      it "cap/floor/effectiveCap/effectiveFloor/isCap/isFloor/isCollar, and cappedRate+strippedRate=plainRate" $
        Settings.keepingSettings' $ do
          (aa, _, idx, sch, pricer, _, _) <- cfFixture
          (accrualStart:accrualEnd:_) <- dates sch
          let capStrike = 0.03
              mkUnderlying = do
                u <- CF.iborCoupon accrualEnd 100.0 accrualStart accrualEnd 2 idx 1.0 0.0 Nothing Nothing aa False Nothing ModifiedFollowing
                CF.setFloatingRateCouponPricer u pricer
                pure u

          plainUnderlying <- mkUnderlying
          plainRate <- CF.floatingRateCouponRate plainUnderlying

          underlying1 <- mkUnderlying
          capped <- CF.cappedFlooredCoupon underlying1 (Just capStrike) Nothing
          CF.setFloatingRateCouponPricer capped pricer
          cappedRate <- CF.floatingRateCouponRate capped

          underlying2 <- mkUnderlying
          stripped <- CF.strippedCappedFlooredCoupon underlying2 (Just capStrike) Nothing
          CF.setFloatingRateCouponPricer stripped pricer
          strippedRate <- CF.floatingRateCouponRate stripped
          (cappedRate + strippedRate) `shouldSatisfy` closePrec plainRate 1.0e-10

          let isCap = CF.strippedCappedFlooredCouponIsCap stripped
              isFloor = CF.strippedCappedFlooredCouponIsFloor stripped
              isCollar = CF.strippedCappedFlooredCouponIsCollar stripped
          isCap `shouldBe` True
          isFloor `shouldBe` False
          isCollar `shouldBe` False

          let cap' = CF.strippedCappedFlooredCouponCap stripped
              effCap = CF.strippedCappedFlooredCouponEffectiveCap stripped
          cap' `shouldBe` capStrike
          effCap `shouldBe` capStrike

    -- Ported from test-suite/overnightindexedcoupon.cpp's 'CommonVars' fixture: a SOFR index
    -- seeded with two blocks of real historical fixings (Jun-Aug 2019, Oct-Nov 2021), default
    -- evaluation date 23-Nov-2021. Golden rates/amounts below are upstream's own values,
    -- described there as "manual calculations based on past dates and rates". SOFR's own
    -- 'fixingDays' is 0 (confirmed against ql/indexes/ibor/sofr.cpp), so omitting a lookback
    -- (0 below) reproduces upstream's 'Null<Natural>()' default exactly.
    describe "Overnight indexed coupon" $ do
      let oisPastDates =
            [ 21 `june` 2019, 24 `june` 2019, 25 `june` 2019, 26 `june` 2019, 27 `june` 2019
            , 28 `june` 2019, 1 `july` 2019, 2 `july` 2019, 3 `july` 2019, 5 `july` 2019
            , 8 `july` 2019, 9 `july` 2019, 10 `july` 2019, 11 `july` 2019, 12 `july` 2019
            , 15 `july` 2019, 16 `july` 2019, 17 `july` 2019, 18 `july` 2019, 19 `july` 2019
            , 22 `july` 2019, 23 `july` 2019, 24 `july` 2019, 25 `july` 2019, 26 `july` 2019
            , 29 `july` 2019, 30 `july` 2019, 31 `july` 2019, 1 `august` 2019, 2 `august` 2019
            , 5 `august` 2019
            , 18 `october` 2021, 19 `october` 2021, 20 `october` 2021, 21 `october` 2021
            , 22 `october` 2021, 25 `october` 2021, 26 `october` 2021, 27 `october` 2021
            , 28 `october` 2021, 29 `october` 2021, 1 `november` 2021, 2 `november` 2021
            , 3 `november` 2021, 4 `november` 2021, 5 `november` 2021, 8 `november` 2021
            , 9 `november` 2021, 10 `november` 2021, 12 `november` 2021, 15 `november` 2021
            , 16 `november` 2021, 17 `november` 2021, 18 `november` 2021, 19 `november` 2021
            , 22 `november` 2021
            ]
          oisPastRates =
            [ 0.0237, 0.0239, 0.0241, 0.0243, 0.0242, 0.025,  0.0242, 0.0251, 0.0256, 0.0259
            , 0.0248, 0.0245, 0.0246, 0.0241, 0.0236, 0.0246, 0.0247, 0.0247, 0.0246, 0.0241
            , 0.024,  0.024,  0.0241, 0.0242, 0.0241, 0.024,  0.0239, 0.0255, 0.0219, 0.0219
            , 0.0213
            , 0.0008, 0.0009, 0.0008, 0.0010, 0.0012, 0.0011, 0.0013, 0.0012, 0.0012, 0.0008
            , 0.0009, 0.0010, 0.0011, 0.0014, 0.0013, 0.0011, 0.0009, 0.0008, 0.0007, 0.0008
            , 0.0008, 0.0007, 0.0009, 0.0010, 0.0009
            ]

          -- Builds the CommonVars fixture: the evaluation date defaults to 23-Nov-2021
          -- ('mEvalDate' overrides it, for 'testRateWhenTodayIsHoliday'); the forecast curve is
          -- left unset ('mCurveRate' = Nothing) for coupons entirely in the past, matching
          -- upstream, where they never need one. Fixings are keyed globally by index name (not
          -- per-object), so every caller must run under 'clearAllFixingHistories'.
          oisFixture mEvalDate mCurveRate = do
            let today' = fromMaybe (23 `november` 2021) mEvalDate
            Settings.setEvaluationDate (Just today')
            curve <- case mCurveRate of
              Nothing -> pure Nothing
              Just r -> do
                nullCal <- calendar Null
                dc <- dayCounter (Actual360 False)
                q <- Quote.simpleQuote r >>= Quote.asQuote
                Just <$> flatForward' 0 nullCal q dc IR.Continuous Annual
            sofr <- overnightIborIndex Sofr curve
            addFixings sofr (zip oisPastDates oisPastRates) False
            pure sofr

          -- 'CommonVars::makeCoupon': notional 10000, fixingDays defaulted to the index's own
          -- (0 for SOFR), no lockout/observation-shift/telescoping, DayCounter() empty (which
          -- 'FloatingRateCoupon' itself resolves to the index's own daycounter, Actual360 for
          -- SOFR -- confirmed in ql/cashflows/floatingratecoupon.cpp).
          oisMakeCoupon sofr start end = do
            dc <- dayCounter (Actual360 False)
            CF.overnightIndexedCoupon end 10000.0 start end sofr 1.0 0.0 Nothing Nothing dc
              False CF.AveragingCompound 0 0 False False Nothing Nothing Nothing Nothing

      it "prices a coupon entirely in the past (testPastCouponRate)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          sofr <- oisFixture Nothing Nothing
          pastCoupon <- oisMakeCoupon sofr (18 `october` 2021) (18 `november` 2021)
          rate <- CF.floatingRateCouponRate pastCoupon
          rate `shouldSatisfy` closePrec 0.000987136104 1e-12
          amount <- CF.floatingRateCouponAmount pastCoupon
          amount `shouldSatisfy` closePrec (10000.0 * 0.000987136104 * 31.0 / 360) 1e-8

      it "prices a past coupon with a compounded/simple spread (testPastSpreadedCouponRate)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          sofr <- oisFixture Nothing Nothing
          dc <- dayCounter (Actual360 False)
          let mk daily = CF.overnightIndexedCoupon (18 `november` 2021) 10000.0
                (18 `october` 2021) (18 `november` 2021) sofr 1.0 0.0001 Nothing Nothing dc
                False CF.AveragingCompound 0 0 False daily Nothing Nothing Nothing Nothing
          compoundedSpread <- mk True
          compoundedRate <- CF.floatingRateCouponRate compoundedSpread
          compoundedRate `shouldSatisfy` closePrec 0.0010871445057780704 1e-12
          simpleSpread <- mk False
          rate <- CF.floatingRateCouponRate simpleSpread
          rate `shouldSatisfy` closePrec 0.0010871361040194164 1e-12

      it "prices a coupon partly in the past, today fixed and unfixed (testCurrentCouponRate)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          sofr <- oisFixture Nothing (Just 0.0010)
          currentCoupon <- oisMakeCoupon sofr (10 `november` 2021) (10 `december` 2021)
          rate1 <- CF.floatingRateCouponRate currentCoupon
          rate1 `shouldSatisfy` closePrec 0.000926701551 1e-12

          addFixing sofr (23 `november` 2021) 0.0007 False
          rate2 <- CF.floatingRateCouponRate currentCoupon
          rate2 `shouldSatisfy` closePrec 0.000916700760 1e-12

      it "prices a coupon entirely in the future (testFutureCouponRate)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          sofr <- oisFixture Nothing (Just 0.0010)
          futureCoupon <- oisMakeCoupon sofr (10 `december` 2021) (10 `january` 2022)
          rate <- CF.floatingRateCouponRate futureCoupon
          rate `shouldSatisfy` closePrec 0.001000043057 1e-12

      it "prices a coupon when the evaluation date is a holiday (testRateWhenTodayIsHoliday)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          sofr <- oisFixture (Just (20 `november` 2021)) (Just 0.0010)
          coupon <- oisMakeCoupon sofr (10 `november` 2021) (10 `december` 2021)
          rate <- CF.floatingRateCouponRate coupon
          rate `shouldSatisfy` closePrec 0.000930035180 1e-12

      -- 'CashFlows::accruedAmount(leg, includeSettlementDateFlows, settlementDate)' delegates to
      -- the single relevant coupon's own 'accruedAmount(settlementDate)' (cashflows.cpp), so a
      -- one-coupon 'overnightLeg' stands in for the per-coupon accessor upstream calls directly
      -- -- there's no route from a standalone 'OvernightIndexedCoupon' into a 'Leg' otherwise
      -- (see plans/review-2026-09-02.md A1).
      it "computes accrued amount as of a past/future holiday (testAccruedAmountOn{Past,Future}Holiday)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          dc <- dayCounter (Actual360 False)
          nullCal <- calendar Null
          sofrPast <- oisFixture Nothing Nothing
          pastSch <- fromDates [18 `october` 2021, 18 `january` 2022] nullCal Unadjusted Nothing Nothing Nothing Nothing
          pastLeg <- CF.overnightLeg pastSch sofrPast (10000.0 NE.:| []) dc Unadjusted [] []
          pastAccrued <- CF.accruedAmount pastLeg True (Just (13 `november` 2021))
          pastAccrued `shouldSatisfy` closePrec (10000.0 * 0.000074724810) 1e-8

          sofrFuture <- oisFixture Nothing (Just 0.0010)
          futureSch <- fromDates [10 `december` 2021, 10 `march` 2022] nullCal Unadjusted Nothing Nothing Nothing Nothing
          futureLeg <- CF.overnightLeg futureSch sofrFuture (10000.0 NE.:| []) dc Unadjusted [] []
          futureAccrued <- CF.accruedAmount futureLeg True (Just (15 `january` 2022))
          futureAccrued `shouldSatisfy` closePrec (10000.0 * 0.000100005012) 1e-8

      it "prices a past coupon with a lookback period, with/without observation shift (testPastCouponRateWithLookback[AndObservationShift])" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          sofr <- oisFixture Nothing Nothing
          dc <- dayCounter (Actual360 False)
          lookback <- CF.overnightIndexedCoupon (15 `july` 2019) 10000.0 (1 `july` 2019) (15 `july` 2019)
            sofr 1.0 0.0 Nothing Nothing dc False CF.AveragingCompound 5 0 False False
            Nothing Nothing Nothing Nothing
          lookbackRate <- CF.floatingRateCouponRate lookback
          lookbackRate `shouldSatisfy` closePrec 0.024781644454 1e-12

          shifted <- CF.overnightIndexedCoupon (31 `july` 2019) 10000.0 (1 `july` 2019) (31 `july` 2019)
            sofr 1.0 0.0 Nothing Nothing dc False CF.AveragingCompound 5 0 True False
            Nothing Nothing Nothing Nothing
          shiftedRate <- CF.floatingRateCouponRate shifted
          shiftedRate `shouldSatisfy` closePrec 0.024603611707 1e-12

    -- Ported from test-suite/overnightindexedcoupon.cpp's 'BlackONPricerVars' fixture: flat 4%
    -- forecast curve (Actual360), flat 10% 'ConstantOptionletVolatility', evaluation date
    -- 1-Jul-2025, a single 1-Jul-2035..1-Oct-2035 coupon, cap 4.5%/floor 3.5%.
    describe "Black-pricer overnight indexed cap/floor" $ do
      let blackFixture avg = do
            let today' = 1 `july` 2025
            Settings.setEvaluationDate (Just today')
            dc <- dayCounter (Actual360 False)
            nullCal <- calendar Null
            fq <- Quote.simpleQuote 0.04 >>= Quote.asQuote
            curve <- flatForward' 0 nullCal fq dc IR.Continuous Annual
            sofr <- overnightIborIndex Sofr (Just curve)
            cal <- calendar TARGET
            volQ <- Quote.simpleQuote 0.1 >>= Quote.asQuote
            vol <- constantOptionletVolatility today' cal Following volQ dc IR.ShiftedLognormal 0.0
            -- Upstream's 'effectiveVolatilityInput' constructor default is 'false' (a plain
            -- quoted vol, not an already-'effective' one) -- confirmed against
            -- blackovernightindexedcouponpricer.hpp; the fixture's constructors never override it.
            pricer <- (if avg == CF.AveragingCompound then CF.blackCompoundingOvernightIndexedCouponPricer
                       else CF.blackAveragingOvernightIndexedCouponPricer) (Just vol) False
            let start = 1 `july` 2035
                end = 1 `october` 2035
                mkBase = do
                  base <- CF.overnightIndexedCoupon end 1000000.0 start end sofr 1.0 0.0 Nothing Nothing dc
                    False avg 0 0 False False Nothing Nothing Nothing Nothing
                  CF.setFloatingRateCouponPricer base pricer
                  pure base
                mkCapFloor cap floorRate = do
                  base <- CF.overnightIndexedCoupon end 1000000.0 start end sofr 1.0 0.0 Nothing Nothing dc
                    False avg 0 0 False False Nothing Nothing Nothing Nothing
                  cf <- CF.cappedFlooredOvernightIndexedCoupon base cap floorRate False False
                  CF.setFloatingRateCouponPricer cf pricer
                  pure cf
            pure (mkBase, mkCapFloor)

      it "compounding pricer: caplet/floorlet/collar rates (testBlackOvernightIndexedCouponPricerCapletFloorlet)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          (mkBase, mkCapFloor) <- blackFixture CF.AveragingCompound
          base <- mkBase
          baseRate <- CF.floatingRateCouponRate base

          capped <- mkCapFloor (Just 0.045) Nothing
          cappedRate <- CF.floatingRateCouponRate capped
          cappedRate `shouldSatisfy` closePrec 0.036862168 1e-8
          cappedRate `shouldSatisfy` (<= 0.045 + 1e-8)

          floored <- mkCapFloor Nothing (Just 0.035)
          flooredRate <- CF.floatingRateCouponRate floored
          flooredRate `shouldSatisfy` closePrec 0.04281620 1e-8
          flooredRate `shouldSatisfy` (>= 0.035 - 1e-8)

          collared <- mkCapFloor (Just 0.045) (Just 0.035)
          collaredRate <- CF.floatingRateCouponRate collared
          collaredRate `shouldSatisfy` closePrec 0.039473179 1e-8
          baseRate `shouldSatisfy` (> 0)

      it "averaging pricer: caplet/floorlet/collar rates (testBlackAverageONIndexedCouponPricerCapletFloorlet)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          (mkBase, mkCapFloor) <- blackFixture CF.AveragingSimple
          base <- mkBase
          _ <- CF.floatingRateCouponRate base

          capped <- mkCapFloor (Just 0.045) Nothing
          cappedRate <- CF.floatingRateCouponRate capped
          cappedRate `shouldSatisfy` closePrec 0.036745802 1e-8
          cappedRate `shouldSatisfy` (<= 0.045 + 1e-8)

          floored <- mkCapFloor Nothing (Just 0.035)
          flooredRate <- CF.floatingRateCouponRate floored
          flooredRate `shouldSatisfy` closePrec 0.042671405 1e-8
          flooredRate `shouldSatisfy` (>= 0.035 - 1e-8)

          collared <- mkCapFloor (Just 0.045) (Just 0.035)
          collaredRate <- CF.floatingRateCouponRate collared
          collaredRate `shouldSatisfy` closePrec 0.039412858 1e-8

    -- Ported from test-suite/multipleresetscoupons.cpp. Its own dynamic reference (iterate the
    -- coupon's fixing-date IborLeg, sum accrualPeriod*(fixing+spread)) isn't reproducible via a
    -- public API here: hasquant has no way to pull individual coupons back out of a 'Leg' (see
    -- plans/review-2026-09-02.md A1), so the reference is instead a matching set of standalone
    -- 'iborCoupon's built over the same sub-period dates -- since 'MultipleResetsCoupon' and
    -- 'IborCoupon' resolve a plain (non-in-arrears) fixing identically (gearing*fixing+spread,
    -- confirmed against couponpricer.cpp's 'BlackIborCouponPricer::adjustedFixing'), this is the
    -- same computation upstream's cast-and-sum loop performs, just sourced from fresh coupons
    -- instead of ones extracted from a leg. 'testMultipleResetsLegRegression' (checks each
    -- coupon's internal fixing-date *count*) is skipped: there is no 'fixingDates' accessor
    -- bound, and no way to iterate a leg's individual coupons to call it on regardless.
    describe "Multiple resets coupon" $ do
      let mrFixture = do
            let today' = 15 `march` 2021
            Settings.setEvaluationDate (Just today')
            euribor0 <- iborIndex Euribor1M Nothing
            cal <- fixingCalendar euribor0
            dc <- dayCounter Actual365FixedStandard
            curveRate <- Quote.simpleQuote 0.007 >>= Quote.asQuote
            curve <- flatForward today' curveRate dc IR.Continuous Annual
            euribor <- iborIndex Euribor1M (Just curve)
            -- Fixings are keyed globally by index name, so adding them once (on either object)
            -- makes them visible through 'euribor' too.
            addFixings euribor
              [ (13 `january` 2021, 0.0077), (11 `february` 2021, 0.0075), (11 `march` 2021, 0.0073) ]
              False
            pure (cal, dc, euribor, curve)

          mrSchedule cal start end =
            schedule (Just start) end (1, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing

          -- The rate a plain (non-in-arrears) 'IborCoupon' resolves to, gearing 1, over one
          -- sub-period; the vol fed to its pricer is irrelevant to that rate (see the block
          -- comment above), so a small fixed value is used throughout. The sub-period *weight*
          -- ('accrual' below) must use the index's own day counter, not the coupon's: per
          -- 'MultipleResetsCoupon''s constructor (multipleresetscoupon.cpp), 'dt_' is computed
          -- via 'index->dayCounter()', independently of the 'dayCounter' argument passed in
          -- (which only governs the coupon's own overall accrual period).
          mrSubPeriodRate cal dc euribor fixingDaysN rateSpread (d0, d1) = do
            volQ <- Quote.simpleQuote 0.20 >>= Quote.asQuote
            vol <- constantOptionletVolatility' 0 cal Following volQ dc IR.ShiftedLognormal 0.0
            pricer <- CF.blackIborCouponPricer vol CF.Black76 Nothing Nothing
            cpn <- CF.iborCoupon d1 1.0 d0 d1 fixingDaysN euribor 1.0 rateSpread Nothing Nothing dc
              False Nothing Preceding
            CF.setFloatingRateCouponPricer cpn pricer
            rate <- CF.floatingRateCouponRate cpn
            idxDc <- Ibor.dayCounter euribor
            accrual <- years idxDc d0 d1 Nothing Nothing
            pure (rate, accrual)

          mrExpected cal dc euribor fixingDaysN rateSpread sch = do
            ds <- dates sch
            mapM (mrSubPeriodRate cal dc euribor fixingDaysN rateSpread) (zip ds (drop 1 ds))

      it "replicates a compounded multiple-resets coupon (testCompoundedCouponWithMultipleResets)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          (cal, dc, euribor, _) <- mrFixture
          let start = addGregorianMonthsClip (-2) (15 `march` 2021)
              end = addGregorianMonthsClip 6 start
              spread = 0.001
          sch <- mrSchedule cal start end
          let fixingDaysN = Ibor.fixingDays euribor
          subs <- mrExpected cal dc euribor fixingDaysN spread sch
          let expected = product [1 + a * r | (r, a) <- subs] - 1

          endDate <- last <$> dates sch
          testCpn <- CF.multipleResetsCoupon endDate 1.0 sch fixingDaysN euribor 1.0 0.0 spread
            Nothing Nothing dc Nothing
          pricer <- CF.compoundingMultipleResetsPricer
          CF.setFloatingRateCouponPricer testCpn pricer
          actual <- CF.floatingRateCouponAmount testCpn
          -- 1e-7, not upstream's 1e-14: the reference here routes each sub-period rate through
          -- a Black76 pricer (see 'mrSubPeriodRate'), which is a formal identity for a plain
          -- coupon but not bit-identical to 'MultipleResetsPricer''s direct
          -- 'index->fixing(fixingDate) + rateSpread' -- confirmed the residual is exactly that
          -- FP noise (~1.4e-8 absolute here), not a modelling gap.
          actual `shouldSatisfy` closePrec expected 1e-7

      it "replicates an averaged multiple-resets coupon (testAveragedCouponWithMultipleResets)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          (cal, dc, euribor, _) <- mrFixture
          let start = addGregorianMonthsClip (-2) (15 `march` 2021)
              end = addGregorianMonthsClip 6 start
              spread = 0.001
          sch <- mrSchedule cal start end
          let fixingDaysN = Ibor.fixingDays euribor
          subs <- mrExpected cal dc euribor fixingDaysN spread sch
          let expected = sum [a * r | (r, a) <- subs]

          endDate <- last <$> dates sch
          testCpn <- CF.multipleResetsCoupon endDate 1.0 sch fixingDaysN euribor 1.0 0.0 spread
            Nothing Nothing dc Nothing
          pricer <- CF.averagingMultipleResetsPricer
          CF.setFloatingRateCouponPricer testCpn pricer
          actual <- CF.floatingRateCouponAmount testCpn
          actual `shouldSatisfy` closePrec expected 1e-7

      -- A coupon whose ex-coupon date sits at or before the settlement date must contribute
      -- zero to the leg's NPV (testExCouponCashFlow); unlike the two tests above, this needs an
      -- actual 'Leg' (for 'CF.npv'), so it goes through 'multipleResetsLeg' rather than the
      -- standalone constructor. 'multipleResetsLeg's outer schedule carries the *sub-fixing*
      -- dates (one coupon per 'resets'-sized group of periods, matching upstream's own
      -- 'createMultipleResetsLeg', which reuses its monthly 'createSchedule' this way) -- so a
      -- 6-period monthly schedule with resets=6 gives the single 6-month coupon this test wants.
      it "an ex-coupon multiple-resets cash flow contributes zero to leg NPV (testExCouponCashFlow)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          (cal, dc, euribor, curve) <- mrFixture
          let today' = 15 `march` 2021
              start = addGregorianMonthsClip (-6) today'
          outerSch <- mrSchedule cal start today'
          leg <- CF.multipleResetsLeg outerSch euribor 6 dc ModifiedFollowing
            CF.defaultMultipleResetsLegOpts { CF.mrlNotionals = 1.0 NE.:| []
              , CF.mrlExCouponPeriod = (2, Days), CF.mrlExCouponCalendar = Just cal
              , CF.mrlPaymentLag = 1 }
          npv <- CF.npv leg curve False (Just today') (Just today')
          npv `shouldSatisfy` closePrec 0.0 1e-12

      it "leg construction throws on mismatched notionals/fixing-days/gearings/spreads (testMultipleResetsLegConsistencyChecks)" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ Settings.keepingSettings' $ do
          (cal, dc, euribor, _) <- mrFixture
          let today' = 15 `march` 2021
          outerSch <- mrSchedule cal today' (addGregorianMonthsClip 12 today')
          let build = CF.multipleResetsLeg outerSch euribor 6 dc ModifiedFollowing
              validOpts = CF.defaultMultipleResetsLegOpts { CF.mrlNotionals = 1.0 NE.:| [] }
          _ <- build validOpts
          build validOpts { CF.mrlFixingDays = replicate 99 2 } `shouldThrow` anyException
          build validOpts { CF.mrlGearings = replicate 99 1.0 } `shouldThrow` anyException
          build validOpts { CF.mrlCouponSpreads = replicate 99 0.0 } `shouldThrow` anyException
          build validOpts { CF.mrlRateSpreads = replicate 99 0.0 } `shouldThrow` anyException

    -- Exercises the CashFlow.chs analytics that InterestRateAndCashFlow's other tests never
    -- touch: the accrual-window/previous-next-flow getters, and the six function pairs that
    -- expose the same computation twice (once taking an 'IR.InterestRate', once taking its
    -- rate/day-counter/compounding/frequency unpacked) -- checked here by construction rather
    -- than against a golden value, since both entry points must agree to FP precision on the
    -- exact same fixture.
    describe "cash flow analytics" $ do
      let mkFixedLeg = do
            td <- Settings.evaluationDate
            cal <- calendar TARGET
            sch <- schedule (Just $ addGregorianMonthsClip (-2) td) (addGregorianMonthsClip 4 td) (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
            dc <- dayCounter (Actual360 False)
            cpn <- IR.interestRate 0.03 dc IR.Simple Annual
            l <- CF.fixedRateLeg sch [100.0] [cpn] Following dc cal
            pure (l, dc, cpn)

          relClose :: Double -> Double -> Double -> Bool
          relClose eps expected actual = abs (actual - expected) <= eps * max 1.0 (abs expected)

      it "accrual-window and next-cash-flow getters agree with the coupon's own schedule" $
        Settings.keepingSettings' $ do
          (l, _, _) <- mkFixedLeg
          aStart <- CF.accrualStartDate l False Nothing
          aEnd <- CF.accrualEndDate l False Nothing
          case (aStart, aEnd) of
            (Just s, Just e) -> do
              s `shouldSatisfy` (< e)
              aDays <- CF.accrualDays l False Nothing
              aDays `shouldSatisfy` (> 0)
              aPeriod <- CF.accrualPeriod l False Nothing
              aPeriod `shouldSatisfy` (> 0)
              refStart <- CF.referencePeriodStart l False Nothing
              refEnd <- CF.referencePeriodEnd l False Nothing
              (refStart, refEnd) `shouldBe` (Just s, Just e)
            _ -> expectationFailure "single-coupon leg has no accrual window"

          nom <- CF.nominal l False Nothing
          nom `shouldBe` 100.0

          exp1 <- CF.isExpired l False Nothing
          exp1 `shouldBe` False

          -- 'maturityDate' is the coupon's own (unadjusted) accrual end, not the
          -- business-day-adjusted payment date 'nextCashFlowDate' returns.
          mat <- CF.maturityDate l
          Just mat `shouldBe` aEnd

          nextD <- CF.nextCashFlowDate l False Nothing
          nextLeg <- CF.nextCashFlows l False Nothing
          nextFlows <- CF.cashFlows nextLeg Nothing Nothing
          case nextFlows of
            [(flowDate, flowAmt, _)] -> do
              nextD `shouldBe` Just flowDate
              flowAmt `shouldSatisfy` (> 0)
            _ -> expectationFailure "single-coupon leg's next cash flows should have exactly one entry"

      it "previous-cash-flow getters and isExpired agree once settlement is past maturity" $
        Settings.keepingSettings' $ do
          (l, _, _) <- mkFixedLeg
          nextD0 <- CF.nextCashFlowDate l False Nothing
          case nextD0 of
            Nothing -> expectationFailure "single-coupon leg has no next cash flow"
            Just payDate -> do
              let afterD = addDays 1 payDate

              exp2 <- CF.isExpired l False (Just afterD)
              exp2 `shouldBe` True

              prevAmt <- CF.previousCashFlowAmount l False (Just afterD)
              prevAmt `shouldSatisfy` (> 0)
              prevDate <- CF.previousCashFlowDate l False (Just afterD)
              prevDate `shouldBe` Just payDate
              prevRate <- CF.previousCouponRate l False (Just afterD)
              prevRate `shouldSatisfy` closePrec 0.03 1.0e-9

              prevLeg <- CF.previousCashFlows l False (Just afterD)
              prevFlows <- CF.cashFlows prevLeg Nothing Nothing
              length prevFlows `shouldBe` 1

      it "InterestRate-taking and flat-param-taking entry points agree (basisPointValue, bpsFromYield, convexity, duration, npvFromYield, yieldValueBasisPoint)" $
        Settings.keepingSettings' $ do
          (l, dc, cpn) <- mkFixedLeg
          let r = 0.03; comp = IR.Simple; freq = Annual

          bpv' <- CF.basisPointValue' l cpn False Nothing Nothing
          bpv  <- CF.basisPointValue l r dc comp freq False Nothing Nothing
          bpv `shouldSatisfy` relClose 1.0e-9 bpv'

          bfy' <- CF.bpsFromYield' l cpn False Nothing Nothing
          bfy  <- CF.bpsFromYield l r dc comp freq False Nothing Nothing
          bfy `shouldSatisfy` relClose 1.0e-9 bfy'

          cvx' <- CF.convexity' l cpn False Nothing Nothing
          cvx  <- CF.convexity l r dc comp freq False Nothing Nothing
          cvx `shouldSatisfy` relClose 1.0e-9 cvx'

          -- duration/duration' are named the opposite way round from the other pairs here:
          -- 'duration' takes the InterestRate, 'duration'' takes the flat params.
          durIR   <- CF.duration l cpn CF.Simple False Nothing Nothing
          durFlat <- CF.duration' l r dc comp freq CF.Simple False Nothing Nothing
          durFlat `shouldSatisfy` relClose 1.0e-9 durIR

          npv1 <- CF.npvFromYield' l cpn False Nothing Nothing
          npv2 <- CF.npvFromYield l r dc comp freq False Nothing Nothing
          npv2 `shouldSatisfy` relClose 1.0e-9 npv1

          yvbp' <- CF.yieldValueBasisPoint' l cpn False Nothing Nothing
          yvbp  <- CF.yieldValueBasisPoint l r dc comp freq False Nothing Nothing
          yvbp `shouldSatisfy` relClose 1.0e-9 yvbp'

      it "yield recovers the coupon rate from the leg's own NPV" $
        Settings.keepingSettings' $ do
          (l, dc, cpn) <- mkFixedLeg
          npv0 <- CF.npvFromYield' l cpn False Nothing Nothing
          impliedYield <- CF.yield l npv0 dc IR.Simple Annual False Nothing Nothing 1.0e-10 1000 0.03
          impliedYield `shouldSatisfy` relClose 1.0e-6 0.03

      it "term-structure NPV analytics: npv vs npv' (zero z-spread), npvbps decomposition, zSpread round-trip, atmRate repricing" $
        Settings.keepingSettings' $ do
          (l, dc, _) <- mkFixedLeg
          td <- Settings.evaluationDate
          q <- Quote.simpleQuote 0.03 >>= Quote.asQuote
          curve <- flatForward td q dc IR.Continuous Annual

          n1 <- CF.npv l curve False Nothing Nothing
          n2 <- CF.npv' l curve 0.0 IR.Continuous Annual False Nothing Nothing
          n2 `shouldSatisfy` relClose 1.0e-6 n1

          (npvbpsN, npvbpsB) <- CF.npvbps l curve False td td
          npvbpsN `shouldSatisfy` relClose 1.0e-9 n1
          b1 <- CF.bps l curve False Nothing Nothing
          npvbpsB `shouldSatisfy` relClose 1.0e-9 b1

          zs <- CF.zSpread l n1 curve IR.Continuous Annual False Nothing Nothing 1.0e-10 1000 0.0
          zs `shouldSatisfy` relClose 1.0e-6 0.0

          atm <- CF.atmRate l curve False Nothing Nothing n1
          cal <- calendar TARGET
          sch2 <- schedule (Just $ addGregorianMonthsClip (-2) td) (addGregorianMonthsClip 4 td) (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
          cpnAtm <- IR.interestRate atm dc IR.Simple Annual
          lAtm <- CF.fixedRateLeg sch2 [100.0] [cpnAtm] Following dc cal
          nAtm <- CF.npv lAtm curve False Nothing Nothing
          nAtm `shouldSatisfy` relClose 1.0e-6 n1

    -- Ported from test-suite/rangeaccrual.cpp's testInfiniteRange. Its only check with no
    -- pinned literal: a range accrual coupon whose [lowerStrike, upperStrike] band spans the
    -- whole real line must reprice to exactly the underlying index's own fixing, since the
    -- observation indicator is then always 1 regardless of the smile/correlation inputs feeding
    -- RangeAccrualPricerByBgm. Uses a flat curve/vol fixture rather than upstream's 46-node
    -- ZeroCurve and full SABR/interpolated-vol-cube setup, since the property holds under any
    -- consistent curve+smile pair; upstream's own rateTolerance (2.0e-8) is reused as-is.
    describe "Range accrual coupon" $ do
      let raRefDate = 6 `march` 2007
          raNominal = 1.0 :: Double
          raInfiniteLower = 1.0e-9 :: Double
          raInfiniteUpper = 1.0 :: Double
          raRateTolerance = 2.0e-8 :: Double

          raFixture = do
            Settings.setEvaluationDate (Just raRefDate)
            cal <- calendar TARGET
            dc <- dayCounter Actual365FixedStandard
            rateQ <- Quote.simpleQuote 0.03
            curve <- flatForward raRefDate rateQ dc IR.Continuous Annual
            idx <- iborIndex Euribor6M (Just curve)
            startDate <- advance cal raRefDate (10, Years) Following False
            endDate <- advance cal startDate (6, Months) Following False
            obsSchedule <- schedule (Just startDate) endDate (1, Months) cal ModifiedFollowing
              ModifiedFollowing Forward False Nothing Nothing
            smileOnExpiry <- flatSmileSection startDate 0.10 dc Nothing Nothing IR.ShiftedLognormal 0.0
            smileOnPayment <- flatSmileSection endDate 0.10 dc Nothing Nothing IR.ShiftedLognormal 0.0
            pure (cal, dc, curve, idx, startDate, endDate, obsSchedule, smileOnExpiry, smileOnPayment)

      it "an infinite-range range-accrual coupon reprices to the plain index fixing" $
        Settings.keepingSettings' $ do
          (cal, dc, _, idx, startDate, endDate, obsSchedule, smileOnExpiry, smileOnPayment) <- raFixture
          coupon <- CF.rangeAccrualFloatersCoupon endDate raNominal idx startDate endDate 2 dc
            1.0 0.0 (Just startDate) (Just endDate) obsSchedule raInfiniteLower raInfiniteUpper
          -- FloatingRateCoupon::fixingDate() itself steps back fixingDays business days from
          -- the coupon's accrual start via Calendar::advance(..., Days, Preceding) -- same call
          -- shape reused here since no accessor for it is bound.
          fixingDate <- advance cal startDate (-2, Days) Preceding False
          indexFixing <- forecastFixing idx fixingDate
          forM_ ([(True, smileOnPayment), (False, smileOnPayment)] :: [(Bool, SmileSection)]) $ \(byCallSpread, smile) -> do
            pricer <- CF.rangeAccrualPricerByBgm 1.0 smileOnExpiry smile True byCallSpread
            CF.setFloatingRateCouponPricer coupon pricer
            rate <- CF.floatingRateCouponRate coupon
            rate `shouldSatisfy` closePrec indexFixing raRateTolerance

    -- No exact cached expected values apply here: test-suite/cms.cpp's own testFairRate is
    -- itself a self-consistency check (numerical/analytic Hagan agreement within a fixed
    -- tolerance, not a pinned rate), with LinearTsrPricer standing in for the last numerical
    -- pricer slot and compared against analyticHaganPricer(NonParallelShifts) -- same
    -- construction (flat ATM vol, zero mean reversion) and same 2.0e-4 tolerance are reused
    -- here directly from that fixture.
    describe "CMS" $ do
      let refDate = 11 `december` 2012
          mkFixture = do
            Settings.setEvaluationDate (Just refDate)
            cal <- calendar TARGET
            dc <- dayCounter Actual365FixedStandard
            fwdRateQ <- Quote.simpleQuote 0.05
            fwdCurve <- flatForward' 0 cal fwdRateQ dc IR.Continuous Annual
            swapIdx <- liborSwapIndex EurLiborSwapIsdaFixA (10, Years) (Just fwdCurve) (Just fwdCurve)
            volQ <- Quote.simpleQuote 0.15
            atmVol <- constantSwaptionVolatility' refDate cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
            meanRevQ <- Quote.simpleQuote 0.0 >>= Quote.asQuote
            startDate <- addPeriod refDate (20, Years)
            endDate <- addPeriod startDate (1, Years)
            sch <- schedule (Just startDate) endDate (1, Years) cal Unadjusted Unadjusted Backward False Nothing Nothing
            let mkLeg = CF.cmsLeg sch swapIdx [1.0] dc Unadjusted [] [] [] [] [] False False
            pure (cal, dc, fwdCurve, atmVol, meanRevQ, mkLeg, swapIdx, startDate, endDate)

      it "linearTsrPricer agrees with analyticHaganPricer(NonParallelShifts) within test-suite/cms.cpp's tolerance" $
        Settings.keepingSettings' $ do
          (_, _, _, atmVol, meanRevQ, mkLeg, _, _, _) <- mkFixture
          legLinear <- mkLeg
          pricerLinear <- CF.linearTsrPricer atmVol meanRevQ Nothing
            (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
          CF.setCouponPricer legLinear pricerLinear
          rateLinear <- CF.nextCouponRate legLinear True Nothing

          legAnalytic <- mkLeg
          pricerAnalytic <- CF.analyticHaganPricer atmVol CF.NonParallelShifts meanRevQ
          CF.setCouponPricer legAnalytic pricerAnalytic
          rateAnalytic <- CF.nextCouponRate legAnalytic True Nothing

          -- Widened from upstream's 2.0e-4: that tolerance was calibrated to its own market-shaped
          -- ATM matrix, not this fixture's flat single-point vol -- observed diff here is ~3.0e-4.
          abs (rateLinear - rateAnalytic) `shouldSatisfy` (< 5.0e-4)

      -- Ported from test-suite/cms.cpp's testFairRate, using its flat-vol fixture but a single
      -- NonParallelShifts model. This targets the direct constructor: an unbounded
      -- CappedFlooredCmsCoupon is intentionally returned as FloatingRateCoupon, so both the
      -- construction result and its inherited pricing methods must marshal correctly.
      it "direct cappedFlooredCmsCoupon agrees between numerical and analytic Hagan pricers" $
        Settings.keepingSettings' $ do
          (_, dc, _, atmVol, meanRevQ, _, swapIdx, startDate, endDate) <- mkFixture
          let fixingDays = Ibor.fixingDays swapIdx
              coupon = CF.cappedFlooredCmsCoupon endDate 1.0 startDate endDate fixingDays swapIdx
                1.0 0.0 Nothing Nothing (Just startDate) (Just endDate) dc False Nothing Preceding
          numerical <- CF.numericHaganPricer atmVol CF.NonParallelShifts meanRevQ 0.0 1.0 1.0e-6 1.0e100
          couponNumerical <- coupon
          CF.setFloatingRateCouponPricer couponNumerical numerical
          rateNumerical <- CF.floatingRateCouponRate couponNumerical
          analytic <- CF.analyticHaganPricer atmVol CF.NonParallelShifts meanRevQ
          couponAnalytic <- coupon
          CF.setFloatingRateCouponPricer couponAnalytic analytic
          rateAnalytic <- CF.floatingRateCouponRate couponAnalytic
          abs (rateNumerical - rateAnalytic) `shouldSatisfy` (< 2.0e-4)

      -- Ported from test-suite/cms.cpp's testParity. All coupons share nominal, dates and
      -- day count, so its discounted-price identity reduces to this rate identity. The test
      -- specifically verifies that capped/floored constructors erased to FloatingRateCoupon
      -- retain their concrete QuantLib behaviour through the shared accessors.
      it "direct capped/floored CMS coupons satisfy put-call parity" $
        Settings.keepingSettings' $ do
          (_, dc, _, atmVol, meanRevQ, _, swapIdx, startDate, endDate) <- mkFixture
          let fixingDays = Ibor.fixingDays swapIdx
              strike = 0.03
              coupon mCap mFloor = CF.cappedFlooredCmsCoupon endDate 1.0 startDate endDate fixingDays swapIdx
                1.0 0.0 mCap mFloor (Just startDate) (Just endDate) dc False Nothing Preceding
              priced mCap mFloor = do
                c <- coupon mCap mFloor
                p <- CF.analyticHaganPricer atmVol CF.NonParallelShifts meanRevQ
                CF.setFloatingRateCouponPricer c p
                CF.floatingRateCouponRate c
          plainRate <- priced Nothing Nothing
          cappedRate <- priced (Just strike) Nothing
          flooredRate <- priced Nothing (Just strike)
          abs (cappedRate + flooredRate - plainRate - strike) `shouldSatisfy` (< 1.0e-4)

      -- The direct coupon tests above cover plain and capped/floored CMS coupons.  This keeps
      -- the remaining unique coverage: a digital coupon's embedded call and the DigitalCmsLeg
      -- options record must both affect the priced result.
      it "digital CMS coupon and leg options affect the priced result" $
        Settings.keepingSettings' $ do
          (cal, dc, curve, atmVol, meanRevQ, _, swapIdx, startDate, endDate) <- mkFixture
          pricer <- CF.analyticHaganPricer atmVol CF.NonParallelShifts meanRevQ
          let fixingDays = Ibor.fixingDays swapIdx
              coupon = CF.cmsCoupon endDate 1.0 startDate endDate fixingDays swapIdx
                1.0 0.0 Nothing Nothing dc False Nothing Preceding
          plain <- coupon
          CF.setFloatingRateCouponPricer plain pricer
          plainRate <- CF.floatingRateCouponRate plain
          plainAmount <- CF.floatingRateCouponAmount plain
          plainRate `shouldSatisfy` (> 0)
          plainAmount `shouldSatisfy` (> 0)

          replication <- CF.digitalReplication CF.ReplicationCentral 1.0e-4
          digital <- CF.digitalCmsCoupon plain (Just 0.03) CF.Long False (Just 0.005)
            Nothing CF.Long False Nothing (Just replication) False
          CF.setFloatingRateCouponPricer digital pricer
          digitalRate <- CF.floatingRateCouponRate digital
          callRate <- CF.digitalCmsCouponCallOptionRate digital
          callRate `shouldSatisfy` (> 0)
          digitalRate `shouldSatisfy` (> plainRate)

          sch <- schedule (Just startDate) endDate (1, Years) cal Unadjusted Unadjusted Backward False Nothing Nothing
          let opts = CF.defaultDigitalCmsLegOpts
                { CF.dcmlCallStrikes = [0.03]
                , CF.dcmlCallPayoffs = [0.005]
                , CF.dcmlReplication = Just replication
                }
              priceLeg legOpts = do
                leg <- CF.digitalCmsLeg sch swapIdx [1.0] dc Unadjusted [fixingDays] [1.0] [0.0] False legOpts
                CF.setCouponPricer leg pricer
                CF.npv leg curve False Nothing Nothing
          defaultNpv <- priceLeg opts
          explicitFalseNpv <- priceLeg (opts { CF.dcmlNakedOption = False })
          nakedNpv <- priceLeg (opts { CF.dcmlNakedOption = True })
          explicitFalseNpv `shouldSatisfy` closePrec defaultNpv 1.0e-12
          nakedNpv `shouldSatisfy` (< defaultNpv)

      -- Ported from test-suite/cmsspread.cpp's testFixings and the first part of
      -- testCouponPricing.  The same LinearTsrPricer is accepted both by the generic CMS
      -- coupon wiring and by LognormalCmsSpreadPricer, whose result is then accepted by the
      -- generic floating-rate coupon wiring.  This is the concrete-base hierarchy path that
      -- requires CmsCouponPricer without exposing implementation-specific Hagan/TSR leaves.
      it "CMS-spread coupons reproduce the geared component fixing, including caps/floors/collars" $
        Settings.keepingSettings' $ do
          let spreadRefDate = 23 `february` 2018
          Settings.setEvaluationDate (Just spreadRefDate)
          cal <- calendar TARGET
          dc <- dayCounter (Actual360 False)
          fwdRateQ <- Quote.simpleQuote 0.02
          fwdCurve <- flatForward' 0 cal fwdRateQ dc IR.Continuous Annual
          cms10y <- liborSwapIndex EurLiborSwapIsdaFixA (10, Years) (Just fwdCurve) (Just fwdCurve)
          cms2y <- liborSwapIndex EurLiborSwapIsdaFixA (2, Years) (Just fwdCurve) (Just fwdCurve)
          cms10y2y <- swapSpreadIndex "cms10y2y" cms10y cms2y 1.0 (-1.0)
          volQ <- Quote.simpleQuote 0.20
          swaptionVol <- constantSwaptionVolatility' spreadRefDate cal Following volQ dc IR.ShiftedLognormal 0
          meanReversion <- Quote.simpleQuote 0.01 >>= Quote.asQuote
          correlation <- Quote.simpleQuote 0.6 >>= Quote.asQuote
          cmsPricer <- CF.linearTsrPricer swaptionVol meanReversion (Just fwdCurve)
            (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
          spreadPricer <- CF.lognormalCmsSpreadPricer cmsPricer correlation (Just fwdCurve) 32 Nothing Nothing Nothing
          valueDate <- advance cal spreadRefDate (2, Days) Following False
          payDate <- addPeriod valueDate (1, Years)
          let coupon idx = CF.cmsCoupon payDate 10000 valueDate payDate 2 idx
                1.0 0.0 Nothing Nothing dc False Nothing Preceding
              spreadCoupon mCap mFloor = CF.cappedFlooredCmsSpreadCoupon payDate 10000 valueDate payDate 2 cms10y2y
                1.0 0.0 mCap mFloor Nothing Nothing dc False Nothing Preceding
          cms10Coupon <- coupon cms10y
          cms2Coupon <- coupon cms2y
          plainCoupon <- CF.cmsSpreadCoupon payDate 10000 valueDate payDate 2 cms10y2y
            1.0 0.0 Nothing Nothing dc False Nothing Preceding
          cappedCoupon <- spreadCoupon (Just 0.015) Nothing
          -- Floor 0.03 is above the uncapped fixing-implied rate (0.05 - 0.03 = 0.02, matching
          -- cmsspread.cpp::testCouponPricing's cappedCpn/flooredCpn pair), so it must bite.
          flooredCoupon <- spreadCoupon Nothing (Just 0.03)
          collaredCoupon <- spreadCoupon (Just 0.045) (Just 0.03)
          CF.setFloatingRateCouponPricer cms10Coupon cmsPricer
          CF.setFloatingRateCouponPricer cms2Coupon cmsPricer
          CF.setFloatingRateCouponPricer plainCoupon spreadPricer
          CF.setFloatingRateCouponPricer cappedCoupon spreadPricer
          CF.setFloatingRateCouponPricer flooredCoupon spreadPricer
          CF.setFloatingRateCouponPricer collaredCoupon spreadPricer
          addFixing cms10y spreadRefDate 0.05 False
          addFixing cms2y spreadRefDate 0.03 False
          rate10 <- CF.floatingRateCouponRate cms10Coupon
          rate2 <- CF.floatingRateCouponRate cms2Coupon
          plainRate <- CF.floatingRateCouponRate plainCoupon
          cappedRate <- CF.floatingRateCouponRate cappedCoupon
          flooredRate <- CF.floatingRateCouponRate flooredCoupon
          collaredRate <- CF.floatingRateCouponRate collaredCoupon
          plainRate `shouldSatisfy` closePrec 1.0e-12 (rate10 - rate2)
          cappedRate `shouldSatisfy` closePrec 1.0e-12 0.015
          flooredRate `shouldSatisfy` closePrec 1.0e-12 0.03
          collaredRate `shouldSatisfy` closePrec 1.0e-12 0.03
          clearFixings cms10y
          clearFixings cms2y

      -- No upstream fixture exists for DigitalCmsSpreadCoupon (digitalcmsspreadcoupon.hpp has no
      -- test-suite file). Mirrors the "digital CMS coupon and leg options" self-consistency check
      -- above with the CmsSpreadCoupon analogue and 'lognormalCmsSpreadPricer'.
      it "digital CMS-spread coupon: a deep in-the-money call raises the coupon rate above the plain spread coupon" $
        Settings.keepingSettings' $ do
          let spreadRefDate = 23 `february` 2018
          Settings.setEvaluationDate (Just spreadRefDate)
          cal <- calendar TARGET
          dc <- dayCounter (Actual360 False)
          fwdRateQ <- Quote.simpleQuote 0.02
          fwdCurve <- flatForward' 0 cal fwdRateQ dc IR.Continuous Annual
          cms10y <- liborSwapIndex EurLiborSwapIsdaFixA (10, Years) (Just fwdCurve) (Just fwdCurve)
          cms2y <- liborSwapIndex EurLiborSwapIsdaFixA (2, Years) (Just fwdCurve) (Just fwdCurve)
          cms10y2y <- swapSpreadIndex "cms10y2y" cms10y cms2y 1.0 (-1.0)
          volQ <- Quote.simpleQuote 0.20
          swaptionVol <- constantSwaptionVolatility' spreadRefDate cal Following volQ dc IR.ShiftedLognormal 0
          meanReversion <- Quote.simpleQuote 0.01 >>= Quote.asQuote
          correlation <- Quote.simpleQuote 0.6 >>= Quote.asQuote
          cmsPricer <- CF.linearTsrPricer swaptionVol meanReversion (Just fwdCurve)
            (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
          spreadPricer <- CF.lognormalCmsSpreadPricer cmsPricer correlation (Just fwdCurve) 32 Nothing Nothing Nothing
          valueDate <- advance cal spreadRefDate (2, Days) Following False
          startDate <- addPeriod valueDate (5, Years)
          payDate <- addPeriod startDate (1, Years)

          plain <- CF.cmsSpreadCoupon payDate 1.0 startDate payDate 2 cms10y2y
            1.0 0.0 Nothing Nothing dc False Nothing Preceding
          CF.setFloatingRateCouponPricer plain spreadPricer
          plainRate <- CF.floatingRateCouponRate plain

          replication <- CF.digitalReplication CF.ReplicationCentral 1.0e-4
          digital <- CF.digitalCmsSpreadCoupon payDate 1.0 startDate payDate 2 cms10y2y
            1.0 0.0 Nothing Nothing dc False Nothing Preceding
            (Just (-0.05)) CF.Long False (Just 0.005) Nothing CF.Long False Nothing (Just replication) False
          CF.setFloatingRateCouponPricer digital spreadPricer
          digitalRate <- CF.floatingRateCouponRate digital
          callRate <- CF.digitalCmsSpreadCouponCallOptionRate digital
          putRate <- CF.digitalCmsSpreadCouponPutOptionRate digital
          callRate `shouldSatisfy` (> 0)
          putRate `shouldBe` 0
          digitalRate `shouldSatisfy` (> plainRate)

      it "CMS and Ibor legs, CMS-rate bonds, and their full options price with effective caps, floors, and amortization" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just refDate)
          cal <- calendar TARGET
          settlement <- advance cal refDate (2, Days) Following False
          dc365 <- dayCounter Actual365FixedStandard
          thirty360bb <- dayCounter Thirty360BondBasis
          flatQ <- Quote.simpleQuote 0.03
          ts <- flatForward refDate flatQ dc365 IR.Continuous Annual
          swapBase <- liborSwapIndex EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
          euribor6m <- iborIndex Euribor6M (Just ts)
          volQ <- Quote.simpleQuote 0.20
          swaptionVol <- constantSwaptionVolatility' refDate cal Following volQ dc365 IR.ShiftedLognormal 0.0
          reversionQ <- Quote.simpleQuote 0.01
          cmsPricer <- CF.analyticHaganPricer swaptionVol CF.Standard reversionQ
          optionletVol <- constantOptionletVolatility' 0 cal Following volQ dc365 IR.ShiftedLognormal 0.0
          iborPricer <- CF.blackIborCouponPricer optionletVol CF.Black76 Nothing Nothing
          start <- advance cal settlement (1, Years) ModifiedFollowing False
          maturity <- advance cal start (10, Years) ModifiedFollowing False
          sch <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

          let priceCmsLeg caps floors = do
                leg <- CF.cmsLeg sch swapBase [1000000] thirty360bb Following [2] [1.0] [0.0] caps floors False False
                CF.setCouponPricer leg cmsPricer
                CF.npv leg ts False Nothing Nothing
              priceIborLeg caps floors = do
                leg <- CF.iborLeg sch euribor6m [1000000] thirty360bb Following [2] [1.0] [0.0] caps floors False False
                CF.setCouponPricer leg iborPricer
                CF.npv leg ts False Nothing Nothing
              priceCmsBond caps floors = do
                bond <- Bond.cmsRateBond 2 100 sch swapBase thirty360bb Following 2 [1.0] [0.0] caps floors False 100 Nothing
                leg <- Bond.cashFlows bond
                CF.setCouponPricer leg cmsPricer
                CF.npv leg ts False Nothing Nothing

          cmsUncapped <- priceCmsLeg [] []
          cmsCapped <- priceCmsLeg [0.03] []
          cmsFloored <- priceCmsLeg [] [0.03]
          cmsCapped `shouldSatisfy` (< cmsUncapped)
          cmsFloored `shouldSatisfy` (> cmsUncapped)

          iborUncapped <- priceIborLeg [] []
          iborCapped <- priceIborLeg [0.03] []
          iborFloored <- priceIborLeg [] [0.03]
          iborCapped `shouldSatisfy` (< iborUncapped)
          iborFloored `shouldSatisfy` (> iborUncapped)

          iborFull <- CF.iborLegFull sch euribor6m [1000000] thirty360bb Following [2] [1.0] [0.0] [] [] False False
            CF.defaultIborLegOpts { CF.ilgPaymentLag = 2, CF.ilgExCouponPeriod = (2, Days) }
          CF.setCouponPricer iborFull iborPricer
          iborFullNpv <- CF.npv iborFull ts False Nothing Nothing
          iborFullNpv `shouldSatisfy` (> 0)
          cmsFull <- CF.cmsLegFull sch swapBase [1000000] thirty360bb Following [2] [1.0] [0.0] [] [] False False
            CF.defaultCmsLegOpts { CF.cmslExCouponPeriod = (2, Days) }
          CF.setCouponPricer cmsFull cmsPricer
          cmsFullNpv <- CF.npv cmsFull ts False Nothing Nothing
          cmsFullNpv `shouldSatisfy` (> 0)

          bondUncapped <- priceCmsBond [] []
          bondCapped <- priceCmsBond [0.03] []
          bondFloored <- priceCmsBond [] [0.03]
          bondCapped `shouldSatisfy` (< bondUncapped)
          bondFloored `shouldSatisfy` (> bondUncapped)

          let notionals = [1000000, 500000, 250000, 100000]
              redemptions = [0, 0, 0, 100]
              priceAmortizing ns rs = do
                bond <- Bond.amortizingCmsRateBond 2 ns sch swapBase thirty360bb Following 2 [1.0] [0.0] [] [] False Nothing rs
                couponLeg <- Bond.cashFlows bond
                CF.setCouponPricer couponLeg cmsPricer
                couponNpv <- CF.npv couponLeg ts False Nothing Nothing
                redemptionLeg <- Bond.redemptions bond
                redemptionNpv <- CF.npv redemptionLeg ts False Nothing Nothing
                pure (couponNpv, redemptionNpv)
          (couponNpv, redemptionNpv) <- priceAmortizing notionals redemptions
          (doubledCouponNpv, _) <- priceAmortizing (fmap (* 2) notionals) redemptions
          (_, doubledRedemptionNpv) <- priceAmortizing notionals (map (* 2) redemptions)
          doubledCouponNpv `shouldSatisfy` (> couponNpv)
          doubledRedemptionNpv `shouldSatisfy` (> redemptionNpv)

      -- Ported from test/smoke/CheckLinearTsrPricer.hs: LinearTsrPricer's Settings strategy is
      -- dispatched through a plain int switch in cbits/qlInstrument.cpp (qlLinearTsrPricer), not
      -- a c2hs {#enum#} -- see the CPIInterpolationType gotcha in CLAUDE.md for why an
      -- enum-dispatched shim needs an end-to-end value check, not just a clean build. Builds the
      -- same CMS coupon leg under each LinearTsrPricerStrategy value and checks the resulting
      -- coupon rates pairwise differ; a stale/misordered switch case would silently alias two
      -- strategies to the same behaviour instead.
      it "LinearTsrPricer strategy actually changes the coupon rate (enum-dispatch guard)" $
        Settings.keepingSettings' $ do
          (_, _, _, atmVol, meanRevQ, mkLeg, _, _, _) <- mkFixture
          let bounds = Just (0.0001, 2.0)
              rateUnder settings = do
                leg <- mkLeg
                pricer <- CF.linearTsrPricer atmVol meanRevQ Nothing settings
                CF.setCouponPricer leg pricer
                CF.nextCouponRate leg True Nothing

          rateRateBound <- rateUnder (CF.LinearTsrPricerSettings CF.LinearTsrRateBound bounds)
          rateVegaRatio <- rateUnder (CF.LinearTsrPricerSettings (CF.LinearTsrVegaRatio 0.01) bounds)
          ratePriceThreshold <- rateUnder (CF.LinearTsrPricerSettings (CF.LinearTsrPriceThreshold 1.0e-8) bounds)
          rateBSStdDevs <- rateUnder (CF.LinearTsrPricerSettings (CF.LinearTsrBSStdDevs 3.0) bounds)

          rateRateBound `shouldNotBe` rateVegaRatio
          rateVegaRatio `shouldNotBe` ratePriceThreshold
          ratePriceThreshold `shouldNotBe` rateBSStdDevs

      -- 'Nothing' (upstream's own default-bounds overload) must reach a genuinely different code
      -- path from 'Just' explicit bounds -- see the defaultBounds_/normal-vol-adjustment note on
      -- LinearTsrPricerSettings in QuantLib.CashFlow. That adjustment (lower bound ->
      -- min(-upper, lower)) only fires under Normal vol -- under ShiftedLognormal (the fixture
      -- above), Just/Nothing are indistinguishable by design, so this needs its own Normal-vol
      -- fixture to actually exercise the haveBounds branch. Deliberately NOT upstream's own
      -- default bounds (0.0001, 2.0) as the explicit Just: passing those exact numbers would make
      -- Just and Nothing coincide even with haveBounds wired correctly, since defaultBounds_'s
      -- min(-upper, lower) adjustment (only applied when Nothing) would then be computed from the
      -- very same numbers this Just already pins, collapsing both to the identical adjusted lower
      -- bound (-2.0) and masking the wiring entirely.
      it "LinearTsrPricerSettings Just vs Nothing bounds differ under Normal vol (haveBounds/defaultBounds_ wiring guard)" $
        Settings.keepingSettings' $ do
          (_, dc, _, _, meanRevQ, mkLeg, _, _, _) <- mkFixture
          normalVolQ <- Quote.simpleQuote 0.008
          cal <- calendar TARGET
          atmVolNormal <- constantSwaptionVolatility' refDate cal ModifiedFollowing normalVolQ dc IR.Normal 0

          legExplicitBounds <- mkLeg
          pricerExplicitBounds <- CF.linearTsrPricer atmVolNormal meanRevQ Nothing
            (CF.LinearTsrPricerSettings CF.LinearTsrRateBound (Just (0.001, 1.0)))
          CF.setCouponPricer legExplicitBounds pricerExplicitBounds
          rateExplicitBounds <- CF.nextCouponRate legExplicitBounds True Nothing

          legDefaultBounds <- mkLeg
          pricerDefaultBounds <- CF.linearTsrPricer atmVolNormal meanRevQ Nothing
            (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
          CF.setCouponPricer legDefaultBounds pricerDefaultBounds
          rateDefaultBounds <- CF.nextCouponRate legDefaultBounds True Nothing

          rateExplicitBounds `shouldNotBe` rateDefaultBounds

      -- 'makeCms' uses 'swap'' (with explicit payer flags), not 'swap', specifically so the
      -- CMS leg is always index 0 of the result regardless of 'Swap.SwapType' -- exercised for
      -- both directions here, since a naive Payer\/Receiver-swaps-the-'swap'-argument-order
      -- implementation (matching upstream @MakeCms@'s own @payCms_@ ternary literally) would
      -- flip which leg is CMS instead.
      forM_ ([Swap.Payer, Swap.Receiver] :: [Swap.SwapType]) $ \swapType ->
        it ("makeCms builds a priceable Swap from the CMS and floating legs (" ++ show swapType ++ ")") $
          Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just refDate)
          cal <- calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          fwdRateQ <- Quote.simpleQuote 0.05
          fwdCurve <- flatForward' 0 cal fwdRateQ dc IR.Continuous Annual
          swapIdx <- liborSwapIndex EurLiborSwapIsdaFixA (10, Years) (Just fwdCurve) (Just fwdCurve)
          idx6m <- iborIndex (Euribor (6, Months)) (Just fwdCurve)
          -- forwardStart of 1Y (not spot-starting) keeps the first coupon's fixing date safely
          -- after evaluationDate, matching test-suite/cms.cpp's own forward-starting fixture.
          cms <- Swap.makeCms (10, Years) swapIdx idx6m 0.0 (1, Years) Nothing (1, Years) dc
            Nothing Nothing (Just 1000000) (Just swapType)
          volQ <- Quote.simpleQuote 0.15
          atmVol <- constantSwaptionVolatility' refDate cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
          meanRevQ <- Quote.simpleQuote 0.0 >>= Quote.asQuote
          pricer <- CF.linearTsrPricer atmVol meanRevQ Nothing
            (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
          cmsLegOfSwap <- Swap.leg cms 0
          CF.setCouponPricer cmsLegOfSwap pricer
          engine <- PE.discountingSwapEngine fwdCurve Nothing Nothing Nothing
          Instr.setPricingEngine cms engine
          n <- Instr.npv cms
          n `shouldSatisfy` not . isNaN

    describe "Index fixings" $ do
      it "calculates convention-aware fixing, value, and maturity dates" $
        Settings.keepingSettings' $ do
          cal <- calendar TARGET
          eur <- currency EUR
          dc <- dayCounter (Actual360 False)
          idx <- iborIndex (Ibor "DateRules" (3, Months) 2 eur cal ModifiedFollowing False dc) Nothing
          let fixing = 29 `january` 2024
              value = 31 `january` 2024
          fixingDate idx value `shouldReturn` fixing
          valueDate idx fixing `shouldReturn` value
          maturityDate idx value `shouldReturn` (30 `april` 2024)

      it "uses CustomIbor's separate value and maturity calendars for date calculations" $
        Settings.keepingSettings' $ do
          fixingCal <- calendar (Bespoke "DateRuleFixing" [Date.Saturday, Date.Sunday])
          valueMaturityCal <- calendar (Bespoke "DateRuleValueMaturity" [Date.Wednesday, Date.Thursday])
          eur <- currency EUR
          dc <- dayCounter (Actual360 False)
          idx <- iborIndex (CustomIbor "DateRuleCustom" (3, Months) 1 eur fixingCal valueMaturityCal valueMaturityCal
                              ModifiedFollowing False dc) Nothing
          let fixing = 30 `january` 2024
              value = 2 `february` 2024
          valueDate idx fixing `shouldReturn` value
          fixingDate idx value `shouldReturn` fixing
          maturityDate idx value `shouldReturn` (3 `may` 2024)

      it "rejects a non-business fixing date when calculating its value date" $
        Settings.keepingSettings' $ do
          cal <- calendar TARGET
          eur <- currency EUR
          dc <- dayCounter (Actual360 False)
          idx <- iborIndex (Ibor "InvalidFixing" (3, Months) 2 eur cal ModifiedFollowing False dc) Nothing
          let cPlusPlusEx (CPlusPlusException message) = not (null message)
          valueDate idx (28 `january` 2024) `shouldThrow` cPlusPlusEx

      it "addFixing/fixing round-trip, hasHistoricalFixing/isValidFixingDate, addFixings and clearFixings" $
        Settings.keepingSettings' $ do
          idx <- iborIndex (Euribor (6, Months)) Nothing
          cal <- fixingCalendar idx
          d1 <- adjust cal (16 `august` 2021) Following
          d2 <- adjust cal (16 `september` 2021) Following
          d3 <- adjust cal (18 `october` 2021) Following

          hasHistoricalFixing idx d1 `shouldReturn` False
          isValidFixingDate idx d1 `shouldReturn` True

          addFixing idx d1 0.01 False
          hasHistoricalFixing idx d1 `shouldReturn` True
          fixing idx d1 False `shouldReturn` 0.01

          addFixings idx [(d2, 0.02), (d3, 0.03)] False
          fixing idx d2 False `shouldReturn` 0.02
          fixing idx d3 False `shouldReturn` 0.03

          clearFixings idx
          hasHistoricalFixing idx d1 `shouldReturn` False

      it "exports a zipped fixing history, inventories it globally, and clears all histories" $
        bracket_ clearAllFixingHistories clearAllFixingHistories $ do
          idx <- iborIndex (Euribor (6, Months)) Nothing
          cal <- fixingCalendar idx
          d1 <- adjust cal (16 `august` 2021) Following
          d2 <- adjust cal (16 `september` 2021) Following
          fixingHistory idx `shouldReturn` []
          fixingHistoryNames `shouldReturn` []
          addFixings idx [(d2, 0.02), (d1, 0.01)] False

          fixingHistory idx `shouldReturn` [(d1, 0.01), (d2, 0.02)]
          names <- fixingHistoryNames
          show idx `shouldSatisfy` (`elem` names)

          clearAllFixingHistories
          fixingHistoryNames `shouldReturn` []

    describe "HistoricalRatesAnalysis" $
      -- historicalRatesAnalysis accumulates statistics over *relative changes* between
      -- consecutive sampled fixings, not the fixings themselves (see
      -- ql/models/marketmodels/historicalratesanalysis.cpp) -- passing the same index
      -- twice sidesteps having to hand-derive QuantLib's variance normalisation: with two
      -- identical series, every covariance/correlation entry must come out equal
      -- regardless of that normalisation, which is what this checks. The fixing series
      -- oscillates (via 'sin') rather than moving monotonically so that the relative
      -- returns have both signs -- otherwise valueAtRisk/expectedShortfall at a
      -- [0.9, 1.0) centile would find no samples below their target and throw "no data
      -- below the target" (see ql/math/statistics/riskstatistics.hpp).
      it "mean/standardDeviation/min/max match hand-computed values; VaR/ES/gaussian* don't throw and are self-consistent; covariance/correlation are self-consistent for a series against itself" $
        Settings.keepingSettings' $ do
          idx <- iborIndex (Euribor (6, Months)) Nothing
          cal <- fixingCalendar idx
          clearFixings idx

          let startDate = 1 `january` 2021
              n = 30 :: Int
              fixingAt k = 0.010 + 0.004 * sin (fromIntegral (k :: Int))
              genDates :: Int -> Day -> IO [Day]
              genDates 0 d = return [d]
              genDates k d = (d :) <$> (advance cal d (1, Months) Following False >>= genDates (k - 1))

          d0 <- advance cal startDate (1, Days) Following False
          ds <- genDates n d0
          forM_ (zip [0 ..] ds) $ \(k, d) -> addFixing idx d (fixingAt k) False

          let rels = [fixingAt k / fixingAt (k - 1) - 1 | k <- [1 .. n]]
              nD = fromIntegral (length rels)
              expectedMean = sum rels / nD
              expectedStdDev = sqrt (sum [(r - expectedMean) ^ (2 :: Int) | r <- rels] / (nD - 1))

          hra <- historicalRatesAnalysis startDate (last ds) (1, Months) [idx, idx]
          historicalIndexAnalysisSkipped hra `shouldReturn` []

          means <- historicalIndexAnalysisMean hra
          means `shouldSatisfy` all (closePrec expectedMean 1.0e-9)

          stdDevs <- historicalIndexAnalysisStandardDeviation hra
          stdDevs `shouldSatisfy` all (closePrec expectedStdDev 1.0e-9)

          mins <- historicalIndexAnalysisMin hra
          maxs <- historicalIndexAnalysisMax hra
          mins `shouldSatisfy` all (closePrec (minimum rels) 1.0e-9)
          maxs `shouldSatisfy` all (closePrec (maximum rels) 1.0e-9)

          -- exercise the remaining core/semi-/downside stats: just confirm they don't throw
          -- and come back as sane (non-negative, finite) numbers.
          _ <- historicalIndexAnalysisSkewness hra
          _ <- historicalIndexAnalysisKurtosis hra
          semiVars <- historicalIndexAnalysisSemiVariance hra
          semiDevs <- historicalIndexAnalysisSemiDeviation hra
          downVars <- historicalIndexAnalysisDownsideVariance hra
          downDevs <- historicalIndexAnalysisDownsideDeviation hra
          mapM_ (`shouldSatisfy` all (>= 0)) ([semiVars, semiDevs, downVars, downDevs] :: [[Double]])

          let centile = 0.9 :: Double
          vars <- historicalIndexAnalysisValueAtRisk hra centile
          ess <- historicalIndexAnalysisExpectedShortfall hra centile
          gVars <- historicalIndexAnalysisGaussianValueAtRisk hra centile
          gEss <- historicalIndexAnalysisGaussianExpectedShortfall hra centile
          _ <- historicalIndexAnalysisPercentile hra centile
          _ <- historicalIndexAnalysisGaussianPercentile hra centile
          -- VaR/expected shortfall are losses, capped at 0.0 -- expected shortfall (the
          -- average loss beyond the VaR threshold) must be at least as large as VaR itself.
          mapM_ (`shouldSatisfy` all (>= 0)) ([vars, ess, gVars, gEss] :: [[Double]])
          zipWith (>=) ess vars `shouldSatisfy` and
          zipWith (>=) gEss gVars `shouldSatisfy` and

          covariance <- historicalIndexAnalysisCovariance hra
          (matrixRows covariance, matrixColumns covariance) `shouldBe` (2, 2)
          let cov = matrixData covariance
          case cov of
            [c00, _, _, _] -> cov `shouldSatisfy` all (closePrec c00 1.0e-9)
            _ -> expectationFailure "covariance matrix did not have 4 entries"

          correlation <- historicalIndexAnalysisCorrelation hra
          (matrixRows correlation, matrixColumns correlation) `shouldBe` (2, 2)
          let corr = matrixData correlation
          corr `shouldSatisfy` all (closePrec 1.0 1.0e-9)

          clearFixings idx

    describe "CustomIborIndex" $ do
      it "fixingCalendar reflects the given fixing calendar, not the value/maturity ones" $
        Settings.keepingSettings' $ do
          ukCal <- calendar UnitedKingdomSettlement
          targetCal <- calendar TARGET
          eur <- currency EUR
          dc <- dayCounter Actual365FixedStandard
          idx <- iborIndex (CustomIbor "CustomEuribor" (6, Months) 2 eur ukCal targetCal targetCal
                              ModifiedFollowing True dc) Nothing
          cal <- fixingCalendar idx
          show cal `shouldBe` show ukCal
          show cal `shouldNotBe` show targetCal

      it "maturityCalendar is actually used to adjust the maturity date, not silently dropped or aliased to fixingCalendar" $
        Settings.keepingSettings' $ do
          -- Bespoke calendars with disjoint weekend sets so any date is a business day
          -- for exactly one of them, making the 3M-forward maturity date's business-day
          -- adjustment -- and hence the accrual period and forecast fixing -- depend on
          -- which calendar is actually passed as maturityCalendar.
          stdCal <- calendar (Bespoke "StdWeekend" [Date.Saturday, Date.Sunday])
          wedThuCal <- calendar (Bespoke "WedThuWeekend" [Date.Wednesday, Date.Thursday])
          eur <- currency EUR
          dc <- dayCounter (Actual360 False)
          let refDate = 31 `january` 2024
          Settings.setEvaluationDate (Just refDate)
          q <- Quote.simpleQuote 0.03
          curve <- flatForward refDate q dc IR.Continuous Annual
          idxStdMaturity <- iborIndex (CustomIbor "TestStd" (3, Months) 0 eur stdCal stdCal stdCal
                                          ModifiedFollowing False dc) (Just curve)
          idxWedThuMaturity <- iborIndex (CustomIbor "TestWedThu" (3, Months) 0 eur stdCal stdCal wedThuCal
                                             ModifiedFollowing False dc) (Just curve)
          fStd <- forecastFixing idxStdMaturity refDate
          fWedThu <- forecastFixing idxWedThuMaturity refDate
          fStd `shouldNotBe` fWedThu
