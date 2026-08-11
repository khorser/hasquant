{-# LANGUAGE ScopedTypeVariables, TupleSections #-}
module QuantLib.Spec.InterestRateAndCashFlow (spec) where

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck.Monadic as Q(monadicIO, run)
import Test.QuickCheck((==>))

import Data.Time.Calendar

import QuantLib.Time.Date
import QuantLib.Type
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import qualified QuantLib.InterestRate as IR
import qualified QuantLib.CashFlow as CF
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility(constantOptionletVolatility')
import qualified QuantLib.Quote as Quote
import QuantLib.Math

import QuantLib.Spec.Helpers(ValidDay(..))

spec :: Day -> Spec
spec tod = do
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
        (CF.leg [(tod, 100)] >>= CF.startDate) `shouldReturn` tod

      it "two legs unsorted" $ do
        (CF.leg [(tod, 100), (addDays (-10) tod, -1000)] >>= CF.startDate) `shouldReturn` addDays (-10) tod

      it "three legs sorted" $ do
        (CF.leg [(tod, 100), (addDays (-10) tod, 1000), (addDays 10 tod, -2000)] >>= CF.startDate) `shouldReturn` addDays (-10) tod

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
