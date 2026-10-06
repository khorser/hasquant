module QuantLib.Spec.CashFlow.FxReset (spec) where

import Control.Exception(bracket_)
import Control.Monad(forM_)
import Data.List.NonEmpty(NonEmpty(..))
import Data.Time.Calendar(fromGregorian, addDays, diffDays)
import Test.Hspec
import qualified QuantLib.Context as Context
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.Currency hiding (rate)
import QuantLib.InterestRate(Compounding(..), VolatilityType(..))
import qualified QuantLib.Index.InterestRate as IR
import qualified QuantLib.Index as Index
import QuantLib.Quote
import QuantLib.TermStructure(CalendarReference(..))
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility(constantOptionletVolatility)
import qualified QuantLib.CashFlow as CF
import QuantLib.Spec.Helpers(quantLibAtMost143, unsupportedQuantLib144)

near :: Double -> Double -> Double -> Expectation
near tolerance expected actual = abs (actual - expected) `shouldSatisfy` (< tolerance)

spec :: Spec
spec = describe "FX reset and stub cash flows 1.44" $ do
  it "calculates business-day observations with native validation" $ Context.keepingSettingsGc $ do
    cal <- calendar TARGET
    let valueDate = fromGregorian 2024 7 8
    if quantLibAtMost143 then
      CF.fxResetObservation (CF.FxResetConvention 2 (Just cal)) valueDate `shouldThrow` unsupportedQuantLib144 "fxResetObservation"
    else do
      reset <- CF.fxResetObservation (CF.FxResetConvention 2 (Just cal)) valueDate
      reset `shouldBe` CF.FxReset (fromGregorian 2024 7 4) valueDate
      CF.fxResetValueDate (CF.FxResetConvention 2 (Just cal)) (CF.fxResetFixingDate reset) `shouldReturn` valueDate
      CF.fxResetObservation (CF.FxResetConvention 0 Nothing) valueDate `shouldReturn` CF.FxReset valueDate valueDate
      CF.fxResetObservation (CF.FxResetConvention 2 Nothing) valueDate `shouldThrow` anyException

  it "scales overnight amounts and accruals, wires legs and retains pricers" $ Context.keepingSettingsGc $ do
    let today = fromGregorian 2024 7 1
        start = fromGregorian 2024 7 8
        end = fromGregorian 2024 10 8
    Context.setEvaluationDate (Just today)
    dc <- dayCounter (Actual360 False)
    eur <- currency EUR
    usd <- currency USD
    eurCurve <- simpleQuote 0.01 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    usdCurve <- simpleQuote 0.05 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    idx <- IR.overnightIborIndex IR.Sofr (Just usdCurve)
    underlying <- CF.overnightIndexedCoupon end 100 start end idx 1 0 Nothing Nothing dc False CF.AveragingCompound 0 0 False False Nothing Nothing Nothing Nothing
    spot <- simpleQuote 1.1
    let observation = CF.FxReset start start
    if quantLibAtMost143 then do
      CF.fxResetCoupon underlying 100 observation `shouldThrow` unsupportedQuantLib144 "fxResetCoupon"
      CF.fxResetNotionalExchange start 100 Nothing (Just observation) `shouldThrow` unsupportedQuantLib144 "fxResetNotionalExchange"
      CF.discountingFxResetPricer eur usd eurCurve usdCurve spot True Nothing `shouldThrow` unsupportedQuantLib144 "discountingFxResetPricer"
    else do
      coupon <- CF.fxResetCoupon underlying 100 observation
      CF.amount coupon `shouldThrow` anyException
      pricer <- CF.discountingFxResetPricer eur usd eurCurve usdCurve spot True Nothing
      CF.setFxResetPricer coupon pricer
      fx <- CF.fxResetRate pricer observation
      CF.couponNominal coupon >>= near 1e-10 (100 * fx)
      rawAmount <- CF.amount underlying
      CF.amount coupon >>= near 1e-10 (rawAmount * fx)
      let accrualDate = addDays 30 start
      rawAccrued <- CF.couponAccruedAmount underlying accrualDate
      CF.couponAccruedAmount coupon accrualDate >>= near 1e-10 (rawAccrued * fx)
      initExchange <- CF.fxResetNotionalExchange start 100 Nothing (Just observation)
      finalExchange <- CF.fxResetNotionalExchange end 100 (Just observation) Nothing
      nextExchange <- CF.fxResetNotionalExchange end 100 (Just observation) (Just (CF.FxReset end end))
      flows <- mapM CF.asCashFlow [initExchange, finalExchange, nextExchange]
      leg <- CF.cashFlowLeg flows
      CF.setFxResetLegPricer leg pricer
      CF.amount initExchange >>= near 1e-10 (-100 * fx)
      CF.amount finalExchange >>= near 1e-10 (100 * fx)
      nextFx <- CF.fxResetRate pricer (CF.FxReset end end)
      CF.amount nextExchange >>= near 1e-10 (100 * (fx - nextFx))
      CF.fxResetNotionalExchange end 100 Nothing Nothing `shouldThrow` anyException
      plain <- CF.cashFlowLeg [underlying]
      wrapped <- CF.cashFlowLeg [coupon]
      CF.fixingDependencies plain >>= \dependencies -> CF.fixingDependencies wrapped `shouldReturn` dependencies
      Context.collectGarbage
      CF.amount coupon >>= near 1e-10 (rawAmount * fx)
      _ <- setValue spot 1.2
      CF.amount coupon >>= near 1e-10 (rawAmount * fx * 1.2 / 1.1)

  it "uses historical direct, inverse and triangulated exchange rates" $ Context.keepingSettingsGc $
    bracket_ clearExchangeRates clearExchangeRates $ do
      let today = fromGregorian 2024 7 8
          fixing = fromGregorian 2024 7 1
          valueDate = fromGregorian 2024 7 3
      Context.setEvaluationDate (Just today)
      dc <- dayCounter (Actual360 False)
      eur <- currency EUR
      usd <- currency USD
      gbp <- currency GBP
      curve <- simpleQuote 0.02 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
      spot <- simpleQuote 1.5
      if quantLibAtMost143 then
        CF.discountingFxResetPricer eur usd curve curve spot True Nothing `shouldThrow` unsupportedQuantLib144 "discountingFxResetPricer"
      else do
        pricer <- CF.discountingFxResetPricer eur usd curve curve spot True Nothing
        let observation = CF.FxReset fixing valueDate
            register source target fx = exchangeRate source target fx >>= \rate -> addExchangeRate rate fixing fixing
        CF.fxResetRate pricer observation `shouldThrow` anyException
        register eur usd 1.1
        CF.fxResetRate pricer observation >>= near 1e-12 1.1
        clearExchangeRates
        register usd eur (1 / 1.1)
        CF.fxResetRate pricer observation >>= near 1e-12 1.1
        clearExchangeRates
        register eur gbp 0.8
        register gbp usd 1.375
        CF.fxResetRate pricer observation >>= near 1e-12 1.1

  it "constructs interpolated stub coupons and expands component dependencies" $ Context.keepingSettingsGc $ do
    let today = fromGregorian 2026 5 27
        start = fromGregorian 2026 5 29
        end = fromGregorian 2026 8 28
    Context.setEvaluationDate (Just today)
    cal <- calendar NewZealandWellington
    dc <- dayCounter Actual365FixedStandard
    nzd <- currency NZD
    curve2 <- simpleQuote 0.02 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    curve3 <- simpleQuote 0.04 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    short <- IR.iborIndex (IR.Ibor "Bkbm" (2, Months) 0 nzd cal ModifiedFollowing False dc) (Just curve2)
    long <- IR.iborIndex (IR.Ibor "Bkbm" (3, Months) 0 nzd cal ModifiedFollowing False dc) (Just curve3)
    let selection = Just (CF.InterpolatedStubIndexes (short :| [long]))
        makeCoupon = CF.stubIborCoupon end 1 start end 0 selection 1 0 Nothing Nothing (Just dc) False Nothing Preceding
    if quantLibAtMost143 then makeCoupon `shouldThrow` unsupportedQuantLib144 "stubIborCoupon"
    else do
      coupon <- makeCoupon
      vol <- simpleQuote 0.2 >>= \q -> constantOptionletVolatility (CalendarReferenceDate today) cal Following q dc ShiftedLognormal 0
      pricer <- CF.blackIborCouponPricer vol CF.Black76 Nothing (Just True)
      CF.setFloatingRateCouponPricer coupon pricer
      fixing <- IR.fixingDate short start
      shortMaturity <- IR.maturityDate short start
      longMaturity <- IR.maturityDate long start
      shortRate <- Index.fixing short fixing False
      longRate <- Index.fixing long fixing False
      let weight = fromIntegral (diffDays end shortMaturity) / fromIntegral (diffDays longMaturity shortMaturity)
      CF.rate coupon >>= near 1e-12 (shortRate + (longRate - shortRate) * weight)
      leg <- CF.cashFlowLeg [coupon]
      dependencies <- CF.fixingDependencies leg
      names <- mapM Index.name [short, long]
      dependencies `shouldMatchList` [(name, fixing) | name <- names]
      forM_ [CF.ClosestStubIndex (short :| [long])] $ \closest -> do
        c <- CF.stubIborCoupon end 1 start end 0 (Just closest) 1 0 Nothing Nothing Nothing False Nothing Preceding
        CF.setFloatingRateCouponPricer c pricer
        CF.rate c >>= near 1e-12 longRate
