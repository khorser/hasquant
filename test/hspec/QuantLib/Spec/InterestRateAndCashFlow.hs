{-# LANGUAGE ScopedTypeVariables, TupleSections, OverloadedLists #-}
module QuantLib.Spec.InterestRateAndCashFlow (spec) where

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck.Monadic as Q(monadicIO, run)
import Test.QuickCheck((==>))

import Control.Exception(bracket_)
import Control.Monad(forM_)
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
  ,historicalRatesAnalysis)
import qualified QuantLib.Index.InterestRate as Ibor(fixingDays)
import qualified QuantLib.Index.Inflation as Inflation
import qualified QuantLib.Index.Equity as Equity
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility(blackConstantVol', constantOptionletVolatility', constantSwaptionVolatility')
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Instrument as Instr
import qualified QuantLib.Instrument.Bond as Bond
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
          iborFlow <- CF.iborCouponAsCashFlow ibor
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
          customLeg <- CF.cashFlowLeg [zeroFlow, cpiFlow, equityFlow]
          flows <- CF.cashFlows customLeg Nothing Nothing
          listCloseRel id [120.0, 120.0, 125.0] 1.0e-12 (map (\(_, amount, _) -> amount) flows) `shouldBe` True

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
      it "CMS-spread coupons reproduce the geared component fixing, including caps" $
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
              spreadCoupon mCap = CF.cappedFlooredCmsSpreadCoupon payDate 10000 valueDate payDate 2 cms10y2y
                1.0 0.0 mCap Nothing Nothing Nothing dc False Nothing Preceding
          cms10Coupon <- coupon cms10y
          cms2Coupon <- coupon cms2y
          plainCoupon <- CF.cmsSpreadCoupon payDate 10000 valueDate payDate 2 cms10y2y
            1.0 0.0 Nothing Nothing dc False Nothing Preceding
          cappedCoupon <- spreadCoupon (Just 0.015)
          CF.setFloatingRateCouponPricer cms10Coupon cmsPricer
          CF.setFloatingRateCouponPricer cms2Coupon cmsPricer
          CF.setFloatingRateCouponPricer plainCoupon spreadPricer
          CF.setFloatingRateCouponPricer cappedCoupon spreadPricer
          addFixing cms10y spreadRefDate 0.05 False
          addFixing cms2y spreadRefDate 0.03 False
          rate10 <- CF.floatingRateCouponRate cms10Coupon
          rate2 <- CF.floatingRateCouponRate cms2Coupon
          plainRate <- CF.floatingRateCouponRate plainCoupon
          cappedRate <- CF.floatingRateCouponRate cappedCoupon
          plainRate `shouldSatisfy` closePrec 1.0e-12 (rate10 - rate2)
          cappedRate `shouldSatisfy` closePrec 1.0e-12 0.015
          clearFixings cms10y
          clearFixings cms2y

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
