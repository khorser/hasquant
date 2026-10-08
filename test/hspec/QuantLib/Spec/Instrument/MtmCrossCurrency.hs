module QuantLib.Spec.Instrument.MtmCrossCurrency (spec) where

import Control.Monad(forM, forM_, void)
import qualified Data.List.NonEmpty as NE
import QuantLib.Math(Interpolation(..))
import Data.Time.Calendar(Day, fromGregorian, addGregorianYearsClip)
import qualified Data.Vector.Storable as V
import Test.Hspec
import qualified QuantLib.Context as Context
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.Currency hiding (rate)
import QuantLib.InterestRate(Compounding(..))
import qualified QuantLib.Index.InterestRate as IR
import qualified QuantLib.Index as Index
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.Instrument
import QuantLib.Instrument.Swap hiding (swap)
import QuantLib.PricingEngine
import qualified QuantLib.CashFlow as CF
import QuantLib.Spec.Helpers(quantLibAtMost143, unsupportedQuantLib144)

fixtureDate :: Day
fixtureDate = fromGregorian 2018 9 11

near :: Double -> Double -> Double -> Expectation
near tolerance expected actual = abs (actual - expected) `shouldSatisfy` (< tolerance)

spec :: Spec
spec = describe "MTM cross-currency 1.44" $ do
  it "prices both resettable legs and directions, and reprices at fair spreads" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just fixtureDate)
    dc <- dayCounter (Actual360 False)
    usd <- currency USD
    eur <- currency EUR
    usdCurve <- simpleQuote 0.02 >>= \q -> flatForward (ReferenceDate fixtureDate) q dc Continuous Annual
    eurCurve <- simpleQuote 0.01 >>= \q -> flatForward (ReferenceDate fixtureDate) q dc Continuous Annual
    usdIndex <- IR.iborIndex (IR.UsdLibor (3, Months)) (Just usdCurve)
    eurIndex <- IR.iborIndex IR.Euribor3M (Just eurCurve)
    cal <- calendar TARGET
    start <- advance cal fixtureDate (2, Days) Following False
    sch <- schedule (Just start) (addGregorianYearsClip 5 start) (3, Months) cal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
    spot <- simpleQuote 1.1
    let makeSwap direction resetBase baseSpread quoteSpread = mtmCrossCurrencyBasisSwap direction
          10000000 usd sch usdIndex baseSpread 1 (10000000 / 1.1) eur sch eurIndex quoteSpread 1 resetBase
    if quantLibAtMost143 then do
      makeSwap PayFxBaseCurrency False 0 0 `shouldThrow` unsupportedQuantLib144 "mtmCrossCurrencyBasisSwap"
      discountingMtmCrossCurrencyBasisSwapEngine usd usdCurve eur eurCurve spot Nothing Nothing Nothing Nothing
        `shouldThrow` unsupportedQuantLib144 "discountingMtmCrossCurrencyBasisSwapEngine"
    else do
      engine <- discountingMtmCrossCurrencyBasisSwapEngine usd usdCurve eur eurCurve spot Nothing Nothing Nothing Nothing
      forM_ [False, True] $ \resetBase -> do
        payer <- makeSwap PayFxBaseCurrency resetBase 0 0
        receiver <- makeSwap ReceiveFxBaseCurrency resetBase 0 0
        setPricingEngine payer engine
        setPricingEngine receiver engine
        price <- npv payer
        npv receiver >>= near 1e-6 (-price)
        fairBase <- fairFxBaseSpread payer
        fairQuote <- fairFxQuoteSpread payer
        fairPaySpread payer >>= near 1e-12 fairBase
        fairRecSpread payer >>= near 1e-12 fairQuote
        forM_ [(fairBase, 0), (0, fairQuote)] $ \(baseSpread, quoteSpread) -> do
          par <- makeSwap PayFxBaseCurrency resetBase baseSpread quoteSpread
          setPricingEngine par engine
          npv par >>= near 0.02 0
        rates <- fxResetRates payer
        notionals <- fxResetNotionals payer
        V.length rates `shouldBe` 20
        V.length notionals `shouldBe` V.length rates
        let notional = if resetBase then 10000000 / 1.1 else 10000000
        forM_ (zip (V.toList rates) (V.toList notionals)) $ \(rate, nominal) -> near 1e-6 (notional * rate) nominal
        _ <- legCurrency payer 0
        inCcyLegNpv payer 0 >>= (`shouldSatisfy` (\v -> not (isNaN v || isInfinite v)))
        inCcyLegBps payer 1 >>= (`shouldSatisfy` (/= 0))
        npvDateDiscounts payer 0 `shouldReturn` 1
        fxResetRates payer >>= \old -> do
          _ <- setValue spot 1.2
          changed <- fxResetRates payer
          changed `shouldSatisfy` (/= old)
          void (setValue spot 1.1)

  it "projects resets at value dates and respects spot settlement overrides" $ Context.keepingSettingsGc $ do
    let today = fromGregorian 2024 7 1
        start = fromGregorian 2024 7 8
        end = fromGregorian 2025 1 8
    Context.setEvaluationDate (Just today)
    dc <- dayCounter (Actual360 False)
    eur <- currency EUR
    usd <- currency USD
    eurCurve <- simpleQuote 0.01 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    usdCurve <- simpleQuote 0.05 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    eurIndex <- IR.iborIndex IR.Euribor3M (Just eurCurve)
    usdIndex <- IR.iborIndex (IR.UsdLibor (3, Months)) (Just usdCurve)
    cal <- calendar TARGET
    usCal <- calendar UnitedStatesSettlement
    fxCal <- calendar (Joint2 cal usCal JoinHolidays)
    sch <- schedule (Just start) end (3, Months) cal Following Following Forward False Nothing Nothing
    spot <- simpleQuote 1.1
    let makeSwap = mtmCrossCurrencyBasisSwapWithOptions PayFxBaseCurrency
          10000000 eur sch eurIndex 0 1 11000000 usd sch usdIndex 0 1 False
          defaultMtmCrossCurrencyBasisSwapOpts { mtmFxResetFixingDays = 2, mtmFxResetFixingCalendar = Just fxCal }
    if quantLibAtMost143 then makeSwap `shouldThrow` unsupportedQuantLib144 "mtmCrossCurrencyBasisSwap"
    else do
      swap <- makeSwap
      engine <- discountingMtmCrossCurrencyBasisSwapEngine usd usdCurve eur eurCurve spot Nothing Nothing Nothing Nothing
      setPricingEngine swap engine
      price <- npv swap
      valueDate <- CF.fxResetValueDate (CF.FxResetConvention 2 (Just fxCal)) today
      eurSpotDf <- discount eurCurve (DatePoint valueDate) False
      usdSpotDf <- discount usdCurve (DatePoint valueDate) False
      eurStartDf <- discount eurCurve (DatePoint start) False
      usdStartDf <- discount usdCurve (DatePoint start) False
      rates <- fxResetRates swap
      case V.toList rates of
        first:_ -> near 1e-10 (1.1 * usdSpotDf / eurSpotDf * eurStartDf / usdStartDf) first
        [] -> expectationFailure "no FX reset rates"
      explicit <- discountingMtmCrossCurrencyBasisSwapEngine usd usdCurve eur eurCurve spot Nothing Nothing Nothing (Just valueDate)
      setPricingEngine swap explicit
      npv swap >>= near 1e-6 price
      resettingLeg <- leg swap 1
      pricer <- CF.discountingFxResetPricer eur usd eurCurve usdCurve spot True (Just valueDate)
      CF.setFxResetLegPricer resettingLeg pricer
      CF.fixingDependencies resettingLeg >>= (`shouldSatisfy` (not . null))

  it "reprices instruments off MTM helper curves for all collateral, basis and reset flags" $ Context.keepingSettingsGc $
    if quantLibAtMost143 then pendingWith "MTM products require QuantLib 1.44" else do
      let today = fromGregorian 2013 9 6
          basisData = [(1, -0.00145), (2, -0.00205), (5, -0.00265)] :: [(Int, Double)]
      Context.setEvaluationDate (Just today)
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      start <- advance cal today (2, Days) Following False
      eur <- currency EUR
      usd <- currency USD
      eurForecast <- simpleQuote 0.007 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
      usdForecast <- simpleQuote 0.015 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
      eurIndex <- IR.iborIndex IR.Euribor3M (Just eurForecast)
      usdIndex <- IR.iborIndex (IR.UsdLibor (3, Months)) (Just usdForecast)
      spot <- simpleQuote 1
      forM_ [(collateralBase, basisBase, resetBase) | collateralBase <- [False, True], basisBase <- [False, True], resetBase <- [False, True]] $ \(collateralBase, basisBase, resetBase) -> do
        let collateral = if collateralBase then eurForecast else usdForecast
        helpers <- forM basisData $ \(years, basis) -> do
          quote <- simpleQuote basis
          mtmCrossCurrencyBasisSwapRateHelper quote (years, Years) 2 cal Following False
            eurIndex usdIndex collateral collateralBase basisBase resetBase Nothing 0 Nothing 2 (Just cal) Nothing Nothing Nothing
        curve <- piecewiseYieldCurve (ReferenceDate today) (NE.fromList helpers) dc []
          (Iterative Discount LogLinear defaultIterativeBootstrapOpts) True
        let eurDiscount = if collateralBase then eurForecast else curve
            usdDiscount = if collateralBase then curve else usdForecast
        engine <- discountingMtmCrossCurrencyBasisSwapEngine usd usdDiscount eur eurDiscount spot Nothing Nothing Nothing Nothing
        forM_ basisData $ \(years, basis) -> do
          sch <- schedule (Just start) (addGregorianYearsClip (fromIntegral years) start) (3, Months) cal Following Following Backward False Nothing Nothing
          instrument <- mtmCrossCurrencyBasisSwapWithOptions PayFxBaseCurrency 1 eur sch eurIndex (if basisBase then basis else 0) 1
            1 usd sch usdIndex (if basisBase then 0 else basis) 1 resetBase
            defaultMtmCrossCurrencyBasisSwapOpts { mtmFxResetFixingDays = 2, mtmFxResetFixingCalendar = Just cal }
          setPricingEngine instrument engine
          npv instrument >>= near 1e-8 0

  it "wires overnight observation, payment and stub options into native legs" $ Context.keepingSettingsGc $ do
    let today = fromGregorian 2026 5 27
        start = fromGregorian 2026 5 29
        end = fromGregorian 2026 8 28
    Context.setEvaluationDate (Just today)
    cal <- calendar NewZealandWellington
    dc <- dayCounter Actual365FixedStandard
    usd <- currency USD
    nzd <- currency NZD
    usdCurve <- simpleQuote 0.015 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    shortCurve <- simpleQuote 0.02 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    nzdCurve <- simpleQuote 0.04 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
    sofr <- IR.overnightIborIndex IR.Sofr (Just usdCurve)
    short <- IR.iborIndex (IR.Ibor "Bkbm" (2, Months) 0 nzd cal ModifiedFollowing False dc) (Just shortCurve)
    long <- IR.iborIndex (IR.Ibor "Bkbm" (3, Months) 0 nzd cal ModifiedFollowing False dc) (Just nzdCurve)
    sch <- schedule (Just start) end (3, Months) cal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
    spot <- simpleQuote 1.5
    let options = defaultMtmCrossCurrencyBasisSwapOpts
          { mtmFxBasePaymentLag = 2, mtmFxQuotePaymentLag = 3
          , mtmFxBasePaymentConvention = ModifiedFollowing
          , mtmFxBaseCompoundSpread = True
          , mtmFxBaseObservation = OvernightObservation (Just 1) 1 True
          , mtmUseIndexedCoupons = Just True
          , mtmFxQuoteStubIndexSelection = Just (CF.InterpolatedStubIndexes (short NE.:| [long])) }
        makeSwap spread = mtmCrossCurrencyBasisSwapWithOptions PayFxBaseCurrency 1000000 usd sch sofr spread 1
          1500000 nzd sch long 0 1 False options
    if quantLibAtMost143 then makeSwap 0.001 `shouldThrow` unsupportedQuantLib144 "mtmCrossCurrencyBasisSwap"
    else do
      instrument <- makeSwap 0.001
      engine <- discountingMtmCrossCurrencyBasisSwapEngine nzd nzdCurve usd usdCurve spot Nothing Nothing Nothing Nothing
      setPricingEngine instrument engine
      fairFxBaseSpread instrument >>= (`shouldSatisfy` (\parSpread -> not (isNaN parSpread || isInfinite parSpread)))
      baseLeg <- leg instrument 0
      baseFlows <- CF.cashFlows baseLeg Nothing Nothing
      payment <- advance cal end (2, Days) ModifiedFollowing False
      map (\(day, _, _) -> day) baseFlows `shouldSatisfy` elem payment
      discounted <- forM baseFlows $ \(day, cashAmount, _) -> do
        df <- discount usdCurve (DatePoint day) False
        pure (cashAmount * df)
      inCcyLegNpv instrument 0 >>= near 1e-6 (-sum discounted)
      quoteLeg <- leg instrument 1
      dependencies <- CF.fixingDependencies quoteLeg
      names <- mapM Index.name [short, long]
      forM_ names $ \name -> map fst dependencies `shouldSatisfy` elem name
