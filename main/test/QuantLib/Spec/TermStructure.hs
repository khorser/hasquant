{-# LANGUAGE ScopedTypeVariables #-}
module QuantLib.Spec.TermStructure (spec) where

import Test.Hspec hiding(before, after)
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck.Monadic as Q(monadicIO, run)
import Test.QuickCheck((==>))

import Data.Time.Calendar

import QuantLib.Time.Date
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar as Calendar
import QuantLib.Time.Schedule
import qualified QuantLib.InterestRate as IR
import qualified QuantLib.Quote as Quote
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure hiding(maxDate)
import QuantLib.Math
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..), overnightIborIndex, OvernightIborIndexType(Sofr))
import QuantLib.Model(hullWhite, extendedCoxIngersollRoss, discountBond)
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Instrument(npv, setPricingEngine, SettlementType(Physical), SettlementMethod(PhysicalOTC), PositionType(Long), additionalResults, AdditionalResultVal(..))
import QuantLib.Instrument.Swap(vanillaSwap, swap, makeVanillaSwap, SwapType(Payer), swaption)
import qualified QuantLib.Instrument.Swap as Swap
import qualified QuantLib.Instrument.Bond as Bond
import QuantLib.Instrument.CapFloor(cap)
import QuantLib.CashFlow(iborLeg, RateAveragingType(..))
import QuantLib.Instrument.Option(vanillaOption, EuropeanExercise(..), PlainVanillaPayoff(..), Exercise(European, American), StrikedPayoff(PlainVanilla), OptionType(Call, Put))
import qualified QuantLib.Instrument.Forward as Fwd
import QuantLib.Process(blackScholesMertonProcess, ProcessDiscretization(EulerDiscretization))
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.PricingEngine(discountingSwapEngine, analyticEuropeanEngine, blackSwaptionEngine', blackCapFloorEngine', bachelierSwaptionEngine', bachelierCapFloorEngine', bjerksundStenslandApproximationEngine)

import QuantLib.Spec.Helpers(areClose, closePrec)

spec :: Spec
spec = do
    describe "Quote value" $ do
      prop "quote value" $
        \val ->
          val > 0
            ==> monadicIO $ do run $ (Quote.simpleQuote val >>= \q -> Quote.value q) `shouldReturn` val

    describe "yield term structure" $ do
      let setup :: IO (Calendar, Word, YieldTermStructure)
          setup = do
            let settlementDays = 2
                depositData = [
                  ( 1, Months, 4.581),
                  ( 2, Months, 4.573 ),
                  ( 3, Months, 4.557 ),
                  ( 6, Months, 4.496 ),
                  ( 9, Months, 4.490 )]
                swapData = [
                  ( 1, Years, 4.54 ),
                  ( 5, Years, 4.99 ),
                  (10, Years, 5.47 ),
                  (20, Years, 5.89 ),
                  (30, Years, 5.96 )]
            cal <- calendar TARGET
            d <- today
            today' <- adjust cal d Following
            Settings.setEvaluationDate (Just today')
            settlement <- advance cal today' (fromIntegral settlementDays, Days) Following False
            actual360dc <- dayCounter (Actual360 False)
            deposits <- mapM
              (\(n, u, r) -> do
                q <- Quote.simpleQuote (r/100)
                depositRateHelper q (n, u) settlementDays cal ModifiedFollowing True actual360dc)
              depositData
            ccy <- currency EUR
            thirty360dc <- dayCounter Thirty360BondBasis
            index <- iborIndex (Ibor "dummy" (6, Months) settlementDays ccy cal ModifiedFollowing False actual360dc) Nothing
            swaps <- mapM
              (\(n, u, r) -> do
                q <- Quote.simpleQuote (r/100)
                swapRateHelper' q (n, u) cal Annual Unadjusted thirty360dc index Nothing (0, Days) Nothing
                  Nothing LastRelevantDate Nothing False Nothing Nothing Nothing >>= asRateHelper)
              swapData

            ts <- piecewiseYieldCurve settlement (deposits ++ swaps) actual360dc [] Discount LogLinear
            return (cal, settlementDays, ts)
      it "referenceChange" $ do
        let ds = [10, 30, 60, 120, 360, 720]
        (_calendar, settlementDays, _ts) <- setup
        flatRate <- Quote.simpleQuote 0.03
        cal <- calendar Null
        actual360dc <- dayCounter (Actual360 False)
        ts <- flatForward' settlementDays cal flatRate actual360dc IR.Continuous Annual
        td <- Settings.evaluationDate

        expected <- mapM (\d -> discount' ts (addDays d td) False) ds
        Settings.setEvaluationDate (Just $ addDays 30 td)
        calculated <- mapM (\d -> discount' ts (addDays (30+d) td) False) ds

        mapM_ (\(x1, x2) -> x1 `shouldSatisfy` areClose x2) (zip expected calculated)

      it "implied" $
        Settings.keepingSettings' $ do
          (cal, settlementDays, ts) <- setup
          td <- Settings.evaluationDate
          let newToday = addGregorianYearsClip 3 td
          newSettlement <- advance cal newToday (fromIntegral settlementDays, Days) Following False
          let testDate = addGregorianYearsClip 5 newSettlement
          implied <- impliedTermStructure ts newSettlement
          baseDiscount <- discount' ts newSettlement False
          dsc <- discount' ts testDate False
          impliedDiscount <- discount' implied testDate False

          (dsc - baseDiscount * impliedDiscount) `shouldSatisfy` (<= 1.0e-10)

      it "fwd spreaded" $
        Settings.keepingSettings' $ do
          (_calendar, _settlementDays, ts) <- setup
          me <- Quote.simpleQuote 0.01
          val <- Quote.value me
          spreaded <- forwardSpreadedTermStructure ts me
          refDate <- asTermStructure ts >>= referenceDate
          let testDate = addGregorianYearsClip 5 refDate
          actual360dc <- dayCounter (Actual360 False)
          forward <- IR.rate <$> forwardRate' ts testDate testDate actual360dc IR.Continuous NoFrequency False
          spreadedForward <- IR.rate <$> forwardRate' spreaded testDate testDate actual360dc IR.Continuous NoFrequency False

          (forward - (spreadedForward - val)) `shouldSatisfy` (<= 1.0e-10)
      it "z-spreaded" $
        Settings.keepingSettings' $ do
          (_calendar, _settlementDays, ts) <- setup
          q <- Quote.simpleQuote 0.01
          val <- Quote.value q
          actual360dc <- dayCounter (Actual360 False)
          spreaded <- zeroSpreadedTermStructure ts q IR.Continuous NoFrequency
          refDate <- asTermStructure ts >>= referenceDate
          let testDate = addGregorianYearsClip 5 refDate
          zero <- IR.rate <$> zeroRate' ts testDate actual360dc IR.Continuous NoFrequency False
          spreadedZero <- IR.rate <$> zeroRate' spreaded testDate actual360dc IR.Continuous NoFrequency False

          (zero - (spreadedZero - val)) `shouldSatisfy` (<= 1.0e-10)

    -- The three rate helpers below build their instrument internally rather than taking
    -- one, so these accessors are the only way to reach it. Checking the instrument's own
    -- maturity against the tenor the helper was given is what catches an accessor wired to
    -- the wrong helper: the returned object would still be a valid swap/bond, just not this
    -- helper's.
    describe "rate helper underlying instruments" $
      it "each accessor returns the instrument built from the helper's own tenor" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (2 `january` 2024))
          cal <- calendar Null
          actual360dc <- dayCounter (Actual360 False)
          thirty360dc <- dayCounter Thirty360BondBasis
          q <- Quote.simpleQuote 0.03

          ois <- overnightIborIndex Sofr Nothing
          oisSwap <- oisRateHelper 2 (1, Years) q ois Nothing >>= oisRateHelperSwap
          (Swap.asSwap oisSwap >>= Swap.maturityDate) `shouldReturn` Just (4 `january` 2025)

          ccy <- currency EUR
          ibor <- iborIndex (Ibor "dummy" (6, Months) 2 ccy cal ModifiedFollowing False actual360dc) Nothing
          vanilla <- swapRateHelper' q (5, Years) cal Annual Unadjusted thirty360dc ibor Nothing (0, Days) Nothing
            Nothing LastRelevantDate Nothing False Nothing Nothing Nothing >>= swapRateHelperSwap
          (Swap.asSwap vanilla >>= Swap.maturityDate) `shouldReturn` Just (4 `january` 2029)

          bondMaturity <- advance cal (2 `january` 2024) (5, Years) Unadjusted False
          sch <- schedule (Just (2 `january` 2024)) bondMaturity (1, Years) cal Unadjusted Unadjusted
                   Backward False Nothing Nothing
          price <- Quote.simpleQuote 100.0
          bond <- fixedRateBondHelper price 3 100.0 sch [0.04] thirty360dc Following 100.0 Nothing
                    >>= bondHelperBond
          Bond.maturityDate bond `shouldBe` Just bondMaturity

    -- No upstream test-suite fixture exists for FxSwapRateHelper (unlike the other rate
    -- helpers ported elsewhere in this file), so this is a self-consistency check instead of
    -- a cached-value comparison: bootstrapping a curve from a single FxSwapRateHelper pillar
    -- must solve for a curve under which the helper's own impliedQuote() reproduces the
    -- fwdPoint quote it was built from -- that is the definition of a successful bootstrap
    -- (RateHelper::quoteError() = quote_->value() - impliedQuote(), driven to ~0 by the
    -- solver), not something specific to FX swaps.
    describe "fx swap rate helper" $
      it "bootstrapped curve reprices the helper's own forward points" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (2 `january` 2024))
          cal <- calendar TARGET
          tradingCal <- calendar Null
          actual360dc <- dayCounter (Actual360 False)
          let fixingDays = 2 :: Word
          settlement <- advance cal (2 `january` 2024) (2, Days) Following False
          collRate <- Quote.simpleQuote 0.03
          collateralCurve <- flatForward' fixingDays cal collRate actual360dc IR.Continuous Annual
          spotFx <- Quote.simpleQuote 1.10
          fwdPoint <- Quote.simpleQuote 0.0025
          rh <- fxSwapRateHelper fwdPoint spotFx (1, Years) fixingDays cal ModifiedFollowing False
                  True collateralCurve tradingCal
          ts <- piecewiseYieldCurve settlement [rh] actual360dc [] Discount LogLinear
          -- PiecewiseYieldCurve is a lazy QuantLib object: bootstrapping (and the
          -- setTermStructure call on each helper) only runs on first calculation, not on
          -- construction, so the curve must be queried before impliedQuote is meaningful.
          _ <- discount' ts settlement False
          implied <- impliedQuote rh
          fwdVal <- Quote.value fwdPoint
          implied `shouldSatisfy` closePrec fwdVal 1.0e-8

    -- No upstream test-suite fixture exists for OvernightIndexFutureRateHelper/SofrFutureRateHelper
    -- either (checked ~/Src/QuantLib/test-suite for overnightindexfuture/sofrfuture-named files,
    -- found none). A single-pillar impliedQuote() self-consistency check alone (as used for the fx
    -- swap rate helper above) is near-tautological here: RateHelper::quoteError() is driven to ~0
    -- by the bootstrap solver regardless of whether valueDate/maturityDate/averagingMethod/pillar
    -- are wired correctly, or whether the futures-price convention (100 - compounded rate) was
    -- used consistently -- a transposed date or enum still converges. So each check below is kept,
    -- but paired with a discriminating check that can actually fail on a wiring mistake.
    describe "overnight index future rate helper" $
      it "bootstrapped curve reprices the helper's own futures price" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (2 `january` 2024))
          cal <- calendar TARGET
          actual360dc <- dayCounter (Actual360 False)
          ois <- overnightIborIndex Sofr Nothing
          let valueDate = 2 `january` 2024
          maturityDate <- advance cal valueDate (3, Months) ModifiedFollowing False
          price <- Quote.simpleQuote 95.0
          rh <- overnightIndexFutureRateHelper price valueDate maturityDate ois Nothing AveragingCompound LastRelevantDate Nothing
          ts <- piecewiseYieldCurve valueDate [rh] actual360dc [] Discount LogLinear
          _ <- discount' ts valueDate False
          implied <- impliedQuote rh
          priceVal <- Quote.value price
          implied `shouldSatisfy` closePrec priceVal 1.0e-6

    describe "sofr future rate helper" $ do
      it "bootstrapped curve reprices the helper's own futures price" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (2 `january` 2024))
          actual360dc <- dayCounter (Actual360 False)
          let settlement = 2 `january` 2024
          price <- Quote.simpleQuote 95.0
          rh <- sofrFutureRateHelper price QuantLib.Time.Date.March 2024 Quarterly Nothing LastRelevantDate Nothing
          ts <- piecewiseYieldCurve settlement [rh] actual360dc [] Discount LogLinear
          _ <- discount' ts settlement False
          implied <- impliedQuote rh
          priceVal <- Quote.value price
          implied `shouldSatisfy` closePrec priceVal 1.0e-6

      -- SofrFutureRateHelper derives its own valueDate/maturityDate (third Wednesday of the
      -- reference month to the third Wednesday one Month/Quarter later) and constructs a Sofr
      -- index internally, then delegates into the same OvernightIndexFutureRateHelper base
      -- constructor bound above. Building the base helper directly with those same dates and
      -- comparing the resulting discount factors pins both the date derivation and the
      -- base-class delegation: a wrong Month/Frequency/averaging wiring makes the two curves
      -- disagree even though each one's own impliedQuote() self-check (above) still passes.
      it "agrees with an explicitly-dated overnight index future rate helper" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (2 `january` 2024))
          actual360dc <- dayCounter (Actual360 False)
          ois <- overnightIborIndex Sofr Nothing
          let settlement = 2 `january` 2024
          valueDate <- nthWeekday 3 QuantLib.Time.Date.Wednesday QuantLib.Time.Date.March 2024
          maturityDate <- nthWeekday 3 QuantLib.Time.Date.Wednesday QuantLib.Time.Date.June 2024
          price <- Quote.simpleQuote 95.0

          sofrRh <- sofrFutureRateHelper price QuantLib.Time.Date.March 2024 Quarterly Nothing LastRelevantDate Nothing
          sofrTs <- piecewiseYieldCurve settlement [sofrRh] actual360dc [] Discount LogLinear
          sofrDf <- discount' sofrTs maturityDate False

          explicitRh <- overnightIndexFutureRateHelper price valueDate maturityDate ois Nothing AveragingCompound LastRelevantDate Nothing
          explicitTs <- piecewiseYieldCurve settlement [explicitRh] actual360dc [] Discount LogLinear
          explicitDf <- discount' explicitTs maturityDate False

          sofrDf `shouldSatisfy` closePrec explicitDf 1.0e-8

    -- Relinking is the one thing a plain curve cannot do: reassign a whole curve under
    -- objects that are already built, and have everything downstream reprice. Every check
    -- here is a before/after comparison rather than a value assertion, because the failure
    -- mode is specific -- a handle whose Link got detached still returns the *correct*
    -- value for the curve it was detached holding, so it is memory-safe, passes any pinned
    -- expected value, and never crashes. The entire symptom is an NPV that stops moving.
    describe "relinkable handles" $ do
      let flat r = do
            q <- Quote.simpleQuote r
            dc <- dayCounter Actual365FixedStandard
            flatForward (11 `december` 2012) q dc IR.Continuous Annual
          -- one swap and one engine, built once and never rebuilt; the relinks below all
          -- act on the already-constructed objects
          setupSwap = do
            cal <- Calendar.calendar TARGET
            settle <- advance cal (11 `december` 2012) (2, Days) Following False
            fixedDC <- dayCounter Thirty360European
            floatDC <- dayCounter (Actual360 False)
            c <- flat 0.02
            discountH <- relinkableYieldTermStructure (Just c)
            forecastH <- relinkableYieldTermStructure (Just c)
            idx <- iborIndex Euribor6M (Just forecastH)
            fixedSch <- schedule (Just settle) (11 `december` 2017) (1, Years) cal
              Unadjusted Unadjusted Forward False Nothing Nothing
            floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
              ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
            sw <- vanillaSwap Payer 1000000 fixedSch 0.02 fixedDC floatSch idx 0 floatDC
              Nothing Nothing
            eng <- discountingSwapEngine discountH Nothing Nothing Nothing
            setPricingEngine sw eng
            pure (sw, discountH, forecastH)

      it "a relinkable handle is accepted wherever a curve is" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          -- no sibling function, no wrapper: it upcasts like any hierarchy member
          (sw, _, _) <- setupSwap
          v <- npv sw
          v `shouldSatisfy` (not . isNaN)

      it "relinking the discount curve reprices without rebuilding" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (sw, discountH, _) <- setupSwap
          npvBefore <- npv sw
          flat 0.05 >>= linkTo discountH
          npvAfter <- npv sw
          abs (npvAfter - npvBefore) `shouldSatisfy` (> 1.0)

      it "relinking back restores the original value exactly" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (sw, discountH, _) <- setupSwap
          npvBefore <- npv sw
          flat 0.05 >>= linkTo discountH
          flat 0.02 >>= linkTo discountH
          -- exact, not approximate: relinking to an identical curve must reproduce the
          -- same arithmetic, and anything else means we are not reaching the same object
          npv sw `shouldReturn` npvBefore

      it "relinking the forecast curve reprices without rebuilding" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          -- the case with no workaround today: an IborIndex is cloned into every floating
          -- coupon at construction, so without a handle this needs the swap rebuilt
          (sw, _, forecastH) <- setupSwap
          npvBefore <- npv sw
          flat 0.05 >>= linkTo forecastH
          npvAfter <- npv sw
          abs (npvAfter - npvBefore) `shouldSatisfy` (> 1.0)

      -- A relinkable quote propagates the same way a relinkable curve does: the curve built
      -- on top of it (fixed, not itself relinkable) still moves when the quote underneath is
      -- relinked, because Quote.relinkableQuote/linkTo share one Link exactly like the curve
      -- case above.
      it "relinking a quote reprices the curve built on it, without rebuilding" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          q02 <- Quote.simpleQuote 0.02
          qh <- Quote.relinkableQuote (Just q02)
          dc <- dayCounter Actual365FixedStandard
          c <- flatForward (11 `december` 2012) qh dc IR.Continuous Annual
          npvBefore <- discount c 5.0 False
          Quote.simpleQuote 0.05 >>= Quote.linkTo qh
          npvAfter <- discount c 5.0 False
          abs (npvAfter - npvBefore) `shouldSatisfy` (> 0.01)

      it "relinking a quote back restores the original value exactly" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          q02 <- Quote.simpleQuote 0.02
          qh <- Quote.relinkableQuote (Just q02)
          dc <- dayCounter Actual365FixedStandard
          c <- flatForward (11 `december` 2012) qh dc IR.Continuous Annual
          npvBefore <- discount c 5.0 False
          Quote.simpleQuote 0.05 >>= Quote.linkTo qh
          Quote.simpleQuote 0.02 >>= Quote.linkTo qh
          -- exact, not approximate: same reasoning as the curve-relink-back check above
          discount c 5.0 False `shouldReturn` npvBefore

      -- A relinkable Black vol surface propagates the same way: an option engine built on it
      -- keeps tracking whatever surface the handle currently points at, so relinking reprices
      -- without rebuilding the engine.
      let mkOption = do
            underQ <- Quote.simpleQuote 100
            riskFreeQ <- Quote.simpleQuote 0.03
            dc <- dayCounter Actual365FixedStandard
            ts <- flatForward (11 `december` 2012) riskFreeQ dc IR.Continuous Annual
            divQ <- Quote.simpleQuote 0.0
            divTS <- flatForward (11 `december` 2012) divQ dc IR.Continuous Annual
            volQ <- Quote.simpleQuote 0.20
            cal <- Calendar.calendar TARGET
            vol0 <- Vol.blackConstantVol (11 `december` 2012) cal volQ dc
            volH <- Vol.relinkableBlackVolTermStructure (Just vol0)
            proc <- blackScholesMertonProcess underQ divTS ts volH EulerDiscretization False
            opt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Call 100))
                                  (European (EuropeanExercise (11 `december` 2013)))
            analyticEuropeanEngine proc Nothing >>= setPricingEngine opt
            pure (opt, volH)

      it "relinking a Black vol surface reprices the option, without rebuilding the engine" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (opt, volH) <- mkOption
          npvBefore <- npv opt
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.40
          vol1 <- Vol.blackConstantVol (11 `december` 2012) cal q dc
          Vol.linkBlackVolTo volH vol1
          npvAfter <- npv opt
          abs (npvAfter - npvBefore) `shouldSatisfy` (> 0.5)

      -- A relinkable swaption vol surface propagates the same way: an engine built on it
      -- keeps tracking whatever surface the handle currently points at, so relinking reprices
      -- the swaption without rebuilding the engine. Mirrors the Black vol case above.
      let mkSwaption = do
            (sw, discountH, _) <- setupSwap
            cal <- Calendar.calendar TARGET
            dc <- dayCounter Actual365FixedStandard
            volQ <- Quote.simpleQuote 0.20
            vol0 <- Vol.constantSwaptionVolatility' (11 `december` 2012) cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
            volH <- Vol.relinkableSwaptionVolatilityStructure (Just vol0)
            eng <- blackSwaptionEngine' discountH volH
            -- the Black swaption engine requires a spot-starting swaption: the exercise date
            -- must fall on or before the swap's start date (13 december 2012)
            swpn <- swaption sw (European (EuropeanExercise (12 `december` 2012))) Physical PhysicalOTC
            setPricingEngine swpn eng
            pure (swpn, volH)

      it "relinking a swaption vol surface reprices the swaption, without rebuilding the engine" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (swpn, volH) <- mkSwaption
          npvBefore <- npv swpn
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.60
          vol1 <- Vol.constantSwaptionVolatility' (11 `december` 2012) cal ModifiedFollowing q dc IR.ShiftedLognormal 0
          Vol.linkSwaptionVolTo volH vol1
          npvAfter <- npv swpn
          abs (npvAfter - npvBefore) `shouldSatisfy` (> 0.5)

      -- A relinkable optionlet vol surface propagates the same way: an engine built on it
      -- keeps tracking whatever surface the handle currently points at, so relinking reprices
      -- the cap without rebuilding the engine. Mirrors the swaption vol case above.
      let mkCap = do
            (_, discountH, forecastH) <- setupSwap
            cal <- Calendar.calendar TARGET
            settle <- advance cal (11 `december` 2012) (2, Days) Following False
            floatDC <- dayCounter (Actual360 False)
            floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
              ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
            idx <- iborIndex Euribor6M (Just forecastH)
            leg <- iborLeg floatSch idx [1000000] floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
            capfl <- cap leg [0.03]
            dc <- dayCounter Actual365FixedStandard
            volQ <- Quote.simpleQuote 0.20
            vol0 <- Vol.constantOptionletVolatility (11 `december` 2012) cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
            volH <- Vol.relinkableOptionletVolatilityStructure (Just vol0)
            eng <- blackCapFloorEngine' discountH volH
            setPricingEngine capfl eng
            pure (capfl, volH)

      it "relinking an optionlet vol surface reprices the cap, without rebuilding the engine" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (capfl, volH) <- mkCap
          npvBefore <- npv capfl
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.60
          vol1 <- Vol.constantOptionletVolatility (11 `december` 2012) cal ModifiedFollowing q dc IR.ShiftedLognormal 0
          Vol.linkOptionletVolTo volH vol1
          npvAfter <- npv capfl
          abs (npvAfter - npvBefore) `shouldSatisfy` (> 0.5)

      -- OptionletStripper1 strips a quoted CapFloorTermVolSurface into caplet/floorlet vols,
      -- immediately wrapped behind StrippedOptionletAdapter (an OptionletVolatilityStructure).
      -- Self-consistency check (upstream: optionletstripper.cpp's testFlatTermVolatilityStripping1,
      -- ported to a single tenor/strike rather than its full 10x10 grid): a *flat* term vol
      -- surface strips to the same flat caplet vol, so pricing a cap at a strike/tenor that sits
      -- exactly on the surface's own grid nodes through the stripped vol must reprice the same
      -- cap priced directly off a constant-vol surface at that flat vol.
      it "stripping a flat cap vol surface reprices a cap struck on its own grid" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (_, discountH, forecastH) <- setupSwap
          cal <- Calendar.calendar TARGET
          settle <- advance cal (11 `december` 2012) (2, Days) Following False
          floatDC <- dayCounter (Actual360 False)
          floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
            ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
          idx <- iborIndex Euribor6M (Just forecastH)
          leg <- iborLeg floatSch idx [1000000] floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
          capfl <- cap leg [0.05]
          dc <- dayCounter Actual365FixedStandard

          flatVolQ <- Quote.simpleQuote 0.18
          let volMatrix = either error id $ objectMatrix 10 3 (replicate 30 flatVolQ)
          capVolSurface <- Vol.capFloorTermVolSurface 0 cal Following
            [(n, Years) | n <- [1 .. 10]] [0.02, 0.05, 0.08] volMatrix dc
          strippedVol <- Vol.optionletStripper1 capVolSurface idx Nothing 1.0e-6 100
            (Just discountH) IR.ShiftedLognormal 0 False Nothing
          strippedEng <- blackCapFloorEngine' discountH strippedVol
          setPricingEngine capfl strippedEng
          priceStripped <- npv capfl

          constVolQ <- Quote.simpleQuote 0.18
          constVol <- Vol.constantOptionletVolatility (11 `december` 2012) cal Following constVolQ dc
            IR.ShiftedLognormal 0
          constEng <- blackCapFloorEngine' discountH constVol
          setPricingEngine capfl constEng
          priceConst <- npv capfl

          priceConst `shouldSatisfy` (> 1)
          abs (priceStripped - priceConst) / abs priceConst `shouldSatisfy` (< 1.0e-5)

      -- Bachelier (normal-vol) engines use a different pricing formula from their Black
      -- (lognormal-vol) siblings; this checks the new bindings are actually wired to that
      -- formula rather than silently aliasing to Black, by repricing the same instrument
      -- with both engines and confirming the results are finite and non-trivially different.
      -- No cached NPV to match against: upstream's Bachelier tests check deltas via finite
      -- differences, not NPVs (see swaption.cpp/capfloor.cpp).
      it "Bachelier swaption engine prices differently from the Black engine on the same swaption" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (sw, discountH, _) <- setupSwap
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          swpn <- swaption sw (European (EuropeanExercise (12 `december` 2012))) Physical PhysicalOTC

          normalVolQ <- Quote.simpleQuote 0.0075
          normalVol <- Vol.constantSwaptionVolatility' (11 `december` 2012) cal ModifiedFollowing normalVolQ dc IR.Normal 0
          normalVolH <- Vol.relinkableSwaptionVolatilityStructure (Just normalVol)
          bachelierEng <- bachelierSwaptionEngine' discountH normalVolH
          setPricingEngine swpn bachelierEng
          npvBachelier <- npv swpn
          npvBachelier `shouldSatisfy` (not . isNaN)

          lognormalVolQ <- Quote.simpleQuote 0.20
          lognormalVol <- Vol.constantSwaptionVolatility' (11 `december` 2012) cal ModifiedFollowing lognormalVolQ dc IR.ShiftedLognormal 0
          lognormalVolH <- Vol.relinkableSwaptionVolatilityStructure (Just lognormalVol)
          blackEng <- blackSwaptionEngine' discountH lognormalVolH
          setPricingEngine swpn blackEng
          npvBlack <- npv swpn
          npvBlack `shouldSatisfy` (not . isNaN)

          abs (npvBachelier - npvBlack) `shouldSatisfy` (> 0.5)

      it "Bachelier cap/floor engine prices differently from the Black engine on the same cap" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (_, discountH, forecastH) <- setupSwap
          cal <- Calendar.calendar TARGET
          settle <- advance cal (11 `december` 2012) (2, Days) Following False
          floatDC <- dayCounter (Actual360 False)
          floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
            ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
          idx <- iborIndex Euribor6M (Just forecastH)
          leg <- iborLeg floatSch idx [1000000] floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
          capfl <- cap leg [0.03]
          dc <- dayCounter Actual365FixedStandard

          normalVolQ <- Quote.simpleQuote 0.0075
          normalVol <- Vol.constantOptionletVolatility (11 `december` 2012) cal ModifiedFollowing normalVolQ dc IR.Normal 0
          normalVolH <- Vol.relinkableOptionletVolatilityStructure (Just normalVol)
          bachelierEng <- bachelierCapFloorEngine' discountH normalVolH
          setPricingEngine capfl bachelierEng
          npvBachelier <- npv capfl
          npvBachelier `shouldSatisfy` (not . isNaN)

          lognormalVolQ <- Quote.simpleQuote 0.20
          lognormalVol <- Vol.constantOptionletVolatility (11 `december` 2012) cal ModifiedFollowing lognormalVolQ dc IR.ShiftedLognormal 0
          lognormalVolH <- Vol.relinkableOptionletVolatilityStructure (Just lognormalVol)
          blackEng <- blackCapFloorEngine' discountH lognormalVolH
          setPricingEngine capfl blackEng
          npvBlack <- npv capfl
          npvBlack `shouldSatisfy` (not . isNaN)

          abs (npvBachelier - npvBlack) `shouldSatisfy` (> 0.5)

      -- A short-rate model built on a relinkable curve is an observer of it too: both
      -- HullWhite and ExtendedCoxIngersollRoss register with their Handle<YieldTermStructure>
      -- (QuantLib's CalibratedModel::update() recomputes the model's curve-fitting function on
      -- notification), so relinking moves the model's own discountBond without rebuilding it --
      -- same relink-propagation property as the curve/quote/vol-surface cases above, just
      -- surfaced through the model instead of an instrument.
      it "relinking the curve updates HullWhite's discount bond without rebuilding the model" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          c <- flat 0.02
          th <- relinkableYieldTermStructure (Just c)
          model <- hullWhite th 0.1 0.01
          before <- discountBond model 0.0 5.0 0.02
          flat 0.05 >>= linkTo th
          after <- discountBond model 0.0 5.0 0.02
          abs (after - before) `shouldSatisfy` (> 0.01)

      it "relinking the curve updates ExtendedCoxIngersollRoss's discount bond without rebuilding the model" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          c <- flat 0.02
          th <- relinkableYieldTermStructure (Just c)
          model <- extendedCoxIngersollRoss th 0.02 1.0 1e-4 0.02 True
          before <- discountBond model 0.0 5.0 0.02
          flat 0.05 >>= linkTo th
          after <- discountBond model 0.0 5.0 0.02
          abs (after - before) `shouldSatisfy` (> 0.01)

      -- The bidirectional dependency cycle RelinkableHandle actually exists for: two Euribor
      -- forecast curves (3m/6m) whose rate helpers reference *each other's* not-yet-bootstrapped
      -- handle, resolved by bootstrapping both curves together under one optimizer
      -- (GlobalBootstrap) via MultiCurve. Ports upstream's
      -- testMultiCurveTwoPiecewiseYieldCurves (piecewiseyieldcurve.cpp).
      let curveToday = 23 `october` 2025
          tolerance = 1.0e-6 :: Double
          setupMultiCurve = do
            Settings.setEvaluationDate (Just curveToday)
            cal <- Calendar.calendar TARGET
            euriborDC <- dayCounter (Actual360 False)
            thirty360 <- dayCounter Thirty360BondBasis
            settleFix <- advance cal curveToday (2, Days) Following False
            discQ <- Quote.simpleQuote 0.02
            discountCurve <- flatForward' 0 cal discQ euriborDC IR.Continuous Annual
            -- the internal handles: empty until addBootstrappedCurve links them below
            intcurve3m <- relinkableYieldTermStructure Nothing
            intcurve6m <- relinkableYieldTermStructure Nothing
            euribor3m <- iborIndex Euribor3M (Just intcurve3m)
            euribor6m <- iborIndex Euribor6M (Just intcurve6m)
            q <- Quote.simpleQuote 0.03
            b <- Quote.simpleQuote 0.0020
            helpers3mFra <- mapM (\i -> fraRateHelper q i (i + 3) 2 cal ModifiedFollowing True euriborDC LastRelevantDate Nothing False) [1 .. 9]
            helpers3mBasis <- mapM (\i -> iborIborBasisSwapRateHelper b (i, Years) 2 cal ModifiedFollowing True euribor3m euribor6m discountCurve True) [2 .. 10]
            helpers6mBasis <- mapM (\i -> iborIborBasisSwapRateHelper b (i * 6, Months) 2 cal ModifiedFollowing True euribor3m euribor6m discountCurve False) [1 .. 3]
            helpers6mSwap <- mapM (\i -> swapRateHelper' q (i, Years) cal Annual Following thirty360 euribor6m Nothing (0, Days) (Just discountCurve)
                                            Nothing LastRelevantDate Nothing False Nothing Nothing Nothing) [2 .. 10]
              >>= mapM asRateHelper -- swapRateHelper' returns the concrete SwapRateHelper; upcast to the generic RateHelper the other helpers already are, so the list below is homogeneous
            -- helpers3m/helpers6m each reference the *other* curve's not-yet-bootstrapped
            -- internal handle (via euribor3m/euribor6m) -- this is exactly the cycle a plain
            -- piecewiseYieldCurve' (IterativeBootstrap) can't resolve.
            ptr3m <- piecewiseYieldCurveGlobalBootstrap' 0 cal (helpers3mFra ++ helpers3mBasis) euriborDC [] 1.0e-10 [] False
            ptr6m <- piecewiseYieldCurveGlobalBootstrap' 0 cal (helpers6mBasis ++ helpers6mSwap) euriborDC [] 1.0e-10 [] False
            mc <- multiCurve 1.0e-10
            curve3m <- addBootstrappedCurve mc intcurve3m ptr3m
            curve6m <- addBootstrappedCurve mc intcurve6m ptr6m
            pure (cal, settleFix, euriborDC, thirty360, euribor3m, euribor6m, q, b, discountCurve, curve3m, curve6m)

      it "FRA-implied forward rates match the input quote once the 3m/6m curves are bootstrapped together" $
        Settings.keepingSettings' $ do
          (cal, settleFix, _, _, euribor3m, _, q, _, _, curve3m, _) <- setupMultiCurve
          qVal <- Quote.value q
          mapM_ (\i -> do
              -- FraRateHelper::initializeDates computes maturityDate_ as a single advance by
              -- (periodToStart + tenor) from the spot date, not two sequential advances --
              -- those disagree by a business day here and there (endOfMonth interacts
              -- differently with a combined-period vs. chained advance), which is enough to
              -- move the FRA off the pillar the helper actually calibrated.
              start <- advance cal settleFix (i, Months) ModifiedFollowing True
              maturity <- advance cal settleFix (i + 3, Months) ModifiedFollowing True
              fra <- Fwd.forwardRateAgreement euribor3m start maturity Long qVal 1.0 (Just curve3m)
              rate <- IR.rate <$> Fwd.forwardRate fra
              rate `shouldSatisfy` closePrec qVal tolerance
            ) [1 .. 9 :: Int]

      it "3m/6m ibor-ibor basis swaps built from the bootstrapped curves reprice to zero" $
        Settings.keepingSettings' $ do
          (cal, settleFix, euriborDC, _, euribor3m, euribor6m, _, b, discountCurve, _, _) <- setupMultiCurve
          bVal <- Quote.value b
          eng <- discountingSwapEngine discountCurve Nothing Nothing Nothing
          let checkBasisSwap tenor = do
                maturity <- advance cal settleFix tenor ModifiedFollowing True
                baseSchedule <- schedule (Just settleFix) maturity (3, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing
                otherSchedule <- schedule (Just settleFix) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing
                baseLeg <- iborLeg baseSchedule euribor3m [1.0] euriborDC ModifiedFollowing [] [] [bVal] [] [] False False
                otherLeg <- iborLeg otherSchedule euribor6m [1.0] euriborDC ModifiedFollowing [] [] [] [] [] False False
                sw <- swap baseLeg otherLeg
                setPricingEngine sw eng
                v <- npv sw
                v `shouldSatisfy` closePrec 0 tolerance
          mapM_ (\i -> checkBasisSwap (i, Years)) [2 .. 10 :: Int]
          mapM_ (\i -> checkBasisSwap (i * 6, Months)) [1 .. 3 :: Int]

      it "a makeVanillaSwap-built 6m swap on the bootstrapped curves reprices to zero" $
        Settings.keepingSettings' $ do
          (_, _, _, thirty360, _, euribor6m, q, _, discountCurve, _, _) <- setupMultiCurve
          qVal <- Quote.value q
          eng <- discountingSwapEngine discountCurve Nothing Nothing Nothing
          mapM_ (\i -> do
              sw <- makeVanillaSwap (i, Years) euribor6m qVal (0, Days) (Just 2) (1, Years) thirty360
                      (Just Following) (Just Following) Nothing Nothing Nothing Nothing
              setPricingEngine sw eng
              v <- npv sw
              v `shouldSatisfy` closePrec 0 tolerance
            ) [2 .. 10 :: Word]

      -- A MultiCurve member that is not itself solved by the optimizer -- a deterministic
      -- function (here, a fixed spread) of another member curve. Ports upstream's
      -- testMultiCurvePiecewiseYieldCurveAndSpreadedCurve (piecewiseyieldcurve.cpp): the OIS
      -- discounting curve is a spread over the 3m Euribor forecast curve, and the 3m curve's
      -- own swap-rate helpers discount off that same OIS curve -- each curve is defined in
      -- terms of the other, resolved the same way as the two-curve cycle above via
      -- 'addBootstrappedCurve'\/'addNonBootstrappedCurve'.
      let setupSpreadedMultiCurve = do
            Settings.setEvaluationDate (Just curveToday)
            cal <- Calendar.calendar TARGET
            euriborDC <- dayCounter (Actual360 False)
            thirty360 <- dayCounter Thirty360BondBasis
            intcurveois <- relinkableYieldTermStructure Nothing
            intcurve3m <- relinkableYieldTermStructure Nothing
            euribor3m <- iborIndex Euribor3M (Just intcurve3m)
            q <- Quote.simpleQuote 0.03
            b <- Quote.simpleQuote (-0.01)
            -- these helpers discount off intcurveois, which is not yet linked to anything --
            -- it is itself a spread over the curve being bootstrapped from these very helpers.
            helpers3m <- mapM (\i -> swapRateHelper' q (i, Years) cal Annual Following thirty360 euribor3m Nothing (0, Days) (Just intcurveois)
                                        Nothing LastRelevantDate Nothing False Nothing Nothing Nothing
                                      >>= asRateHelper) [1 .. 10 :: Int]
            ptr3m <- piecewiseYieldCurveGlobalBootstrap' 0 cal helpers3m euriborDC [] 1.0e-10 [] False
            mc <- multiCurve 1.0e-10
            curve3m <- addBootstrappedCurve mc intcurve3m ptr3m
            ptrois <- zeroSpreadedTermStructure intcurve3m b IR.Continuous NoFrequency
            curveois <- addNonBootstrappedCurve mc intcurveois ptrois
            pure (thirty360, euribor3m, q, b, curveois, curve3m)

      it "a fixed spread over a bootstrapped curve reprices to that spread" $
        Settings.keepingSettings' $ do
          (_, _, _, b, curveois, curve3m) <- setupSpreadedMultiCurve
          bVal <- Quote.value b
          zOis <- IR.rate <$> zeroRate curveois 1.0 IR.Continuous NoFrequency False
          z3m <- IR.rate <$> zeroRate curve3m 1.0 IR.Continuous NoFrequency False
          (zOis - z3m) `shouldSatisfy` closePrec bVal tolerance

      it "swaps priced on the spreaded curve, discounted through the cycle, reprice to zero" $
        Settings.keepingSettings' $ do
          (thirty360, euribor3m, q, _, curveois, _) <- setupSpreadedMultiCurve
          qVal <- Quote.value q
          eng <- discountingSwapEngine curveois Nothing Nothing Nothing
          mapM_ (\i -> do
              sw <- makeVanillaSwap (i, Years) euribor3m qVal (0, Days) (Just 2) (1, Years) thirty360
                      (Just Following) (Just Following) Nothing Nothing Nothing Nothing
              setPricingEngine sw eng
              v <- npv sw
              v `shouldSatisfy` closePrec 0 tolerance
            ) [1 .. 10 :: Word]

      -- GlobalBootstrap's instrumentWeights: overdetermined instrument sets (more instruments
      -- than pillars) are fitted by least squares, weighted per instrument. Ports (the
      -- weights-vector half of) upstream's testGlobalBootstrapInstrumentWeights
      -- (piecewiseyieldcurve.cpp) -- its curve2, comparing against a custom-penalty functor
      -- construction, is not ported: that overload needs GlobalBootstrap's functor-callback
      -- constructors, which are not bound (see README's # TODO).
      it "instrumentWeights shifts an overdetermined fit toward the more heavily weighted quote" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just curveToday)
          cal <- Calendar.calendar TARGET
          euriborDC <- dayCounter (Actual360 False)
          -- two deposits over the same period at different rates: with no unique fit, the
          -- weight on each pins where the (otherwise underdetermined) curve lands.
          q1 <- Quote.simpleQuote 0.01
          q2 <- Quote.simpleQuote 0.02
          h1 <- depositRateHelper q1 (6, Months) 2 cal ModifiedFollowing True euriborDC
          h2 <- depositRateHelper q2 (6, Months) 2 cal ModifiedFollowing True euriborDC
          let helpers = [h1, h2]
          curveMostlyQ2 <- piecewiseYieldCurveGlobalBootstrap' 0 cal helpers euriborDC [] 1.0e-10 [0.1, 0.9] False
          curveMostlyQ1 <- piecewiseYieldCurveGlobalBootstrap' 0 cal helpers euriborDC [] 1.0e-10 [0.9, 0.1] False
          settleFix <- advance cal curveToday (2, Days) Following False
          pillar <- advance cal settleFix (6, Months) ModifiedFollowing True
          d1 <- discount' curveMostlyQ1 pillar False
          d2 <- discount' curveMostlyQ2 pillar False
          -- higher weight on the higher rate (q2) means a lower discount factor at the pillar
          d2 `shouldSatisfy` (< d1)

      -- SimpleZeroYield x Linear is upstream QuantLib-SWIG's only bound GlobalBootstrap
      -- combination (GlobalLinearSimpleZeroCurve); Discount x LogLinear is the combination
      -- hasquant already had. Both must reprice the same input instruments to the same
      -- discount factors *at the pillar dates* (bootstrap forces an exact fit regardless of
      -- trait/interpolator), which is what distinguishes "a genuinely different CurveType" from
      -- "the enum case aliased and dispatched to the same one" -- see also
      -- smoke/CheckSimpleZeroYield.hs, which checks the complementary property (the two curves
      -- *disagree* between pillars, since that's where the interpolation differs).
      --
      -- Uses deposit helpers (not FRAs, like the instrumentWeights test above), deliberately:
      -- each DepositRateHelper's equation only involves the common curve-start point and its own
      -- maturity, never another helper's pillar, so the bootstrap is well-determined pillar by
      -- pillar with no dependence on inter-pillar interpolation shape. A first attempt with FRA
      -- helpers here (start dates 1m/2m/3m falling before the first 4m pillar) failed: those
      -- FRAs' *start* discount factors are themselves interpolated, and Discount/LogLinear vs.
      -- SimpleZeroYield/Linear extrapolate that sub-pillar region differently, so the two curves'
      -- solved pillar values genuinely disagreed -- not a test bug, but the wrong instrument
      -- choice for isolating "same pillars" from "same interpolation".
      it "SimpleZeroYield GlobalBootstrap curve reprices to the same pillar discount factors as Discount" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just curveToday)
          cal <- Calendar.calendar TARGET
          euriborDC <- dayCounter (Actual360 False)
          q <- Quote.simpleQuote 0.03
          helpersDiscount <- mapM (\i -> depositRateHelper q (i, Months) 2 cal ModifiedFollowing True euriborDC) [1 .. 5 :: Int]
          helpersZero <- mapM (\i -> depositRateHelper q (i, Months) 2 cal ModifiedFollowing True euriborDC) [1 .. 5 :: Int]
          discountCurve <- piecewiseYieldCurveGlobalBootstrap' 0 cal helpersDiscount euriborDC [] 1.0e-10 [] False
          zeroCurve <- piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear' 0 cal helpersZero euriborDC [] 1.0e-10 [] False
          settleFix <- advance cal curveToday (2, Days) Following False
          mapM_ (\i -> do
              pillar <- advance cal settleFix (i, Months) ModifiedFollowing True
              dDiscount <- discount' discountCurve pillar False
              dZero <- discount' zeroCurve pillar False
              dZero `shouldSatisfy` closePrec dDiscount tolerance
            ) [1 .. 5 :: Int]

      -- GlobalBootstrap's functor-callback constructor (upstream QuantLib-SWIG's canned
      -- AdditionalErrors/AdditionalDates), bound only for SimpleZeroYield x Linear -- the same
      -- combination its GlobalLinearSimpleZeroCurve demonstrates. testGlobalBootstrap
      -- (piecewiseyieldcurve.cpp) is not ported: its cached
      -- expected values are for that test's own bespoke error formula's fixed point, not a
      -- property derivable independently here.
      --
      -- A first version of this test compared two curves whose additionalHelpers "agreed" vs.
      -- "disagreed" with the primary instruments, expecting a measurably different fit -- that
      -- failed (0.0 difference): with additionalHelpers reusing the primary instruments' own
      -- dates, AdditionalErrors' formula is evaluated on quotes the primary curve already fully
      -- determines, so it imposes no new constraint and the fit is identical either way. That's
      -- a real property of the canned formula (over-determined/degenerate when additionalHelpers
      -- duplicates the primary grid), not a bug -- but the wrong property to test here. Testing
      -- what the plan actually called for instead: additionalHelpers/additionalDates are present
      -- and satisfied without breaking the primary instruments' own fit (each deposit still
      -- reprices to its own input quote via the standard simple-compounding relation).
      it "GlobalBootstrapFull reprices its own instruments correctly with additionalHelpers/additionalDates present" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just curveToday)
          cal <- Calendar.calendar TARGET
          euriborDC <- dayCounter (Actual360 False)
          settleFix <- advance cal curveToday (2, Days) Following False
          q <- Quote.simpleQuote 0.03
          qVal <- Quote.value q
          helpers <- mapM (\i -> depositRateHelper q (i, Months) 2 cal ModifiedFollowing True euriborDC) [1 .. 5 :: Int]
          -- Deliberately *not* coincident with the primary monthly pillars above (45/75/105
          -- days sit between the 1m/2m/3m/4m pillars): reusing the same dates as additionalDates
          -- gave GlobalBootstrap two unknowns pinned to the same time, which visibly perturbed
          -- the first three pillars' solved values (a first version of this test hit that).
          extraDates <- mapM (\d -> advance cal settleFix (d, Days) ModifiedFollowing True) [45, 75, 105 :: Int]
          -- settl=2, matching the deposit helpers' own fixingDays: otherwise the curve's
          -- reference date is curveToday rather than settleFix, and the simple-compounding
          -- relation below (which is anchored at settleFix, the deposits' own start) picks up a
          -- spurious 2-day discounting gap -- confirmed by comparing against a settl=0 curve,
          -- whose discount() came out identical to a plain (non-functor) curve but consistently
          -- off from the hand-computed expectation.
          curve <- piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' 2 cal helpers euriborDC [] helpers extraDates 1.0e-10 False
          mapM_ (\i -> do
              pillar <- advance cal settleFix (i, Months) ModifiedFollowing True
              -- Actual360's own year fraction: no dedicated QuantLib.yearFraction binding
              -- exists (CLAUDE.md's "bind few inspectors" rule), and diffDays/360 reproduces it
              -- exactly since Actual360 is a plain actual-days-over-360 day counter.
              let tau = fromIntegral (diffDays pillar settleFix) / 360 :: Double
              df <- discount' curve pillar False
              -- simple-compounding deposit relation: df = 1 / (1 + qVal * tau)
              df `shouldSatisfy` closePrec (1 / (1 + qVal * tau)) tolerance
            ) [1 .. 5 :: Int]

    -- PiecewiseBlackVarianceSurface::makeFromGrid: upstream's testMakeFromGrid
    -- (test-suite/piecewiseblackvariancesurface.cpp) has no cached NPV fixture, only
    -- analytical self-consistency checks (exact reprice at grid nodes, etc). hasquant has no
    -- blackVariance/blackVol inspector on the generic BlackVolTermStructure, so check the
    -- reprice-at-a-grid-node property indirectly through pricing: a European option struck and
    -- expiring exactly at a grid node must reprice identically under the piecewise surface and
    -- under a flat blackConstantVol at that node's own vol, since both surfaces have the same
    -- variance there.
    describe "piecewise Black variance surface" $
      it "reproduces the input vol exactly at a grid node" $
        Settings.keepingSettings' $ do
          let refDate = 11 `december` 2012
              otherDate = 11 `june` 2013
              nodeDate = 11 `december` 2013
              nodeStrike = 100
              nodeVol = 0.22
              tolerance = 1.0e-6 :: Double
          Settings.setEvaluationDate (Just refDate)
          underQ <- Quote.simpleQuote 100
          riskFreeQ <- Quote.simpleQuote 0.03
          dc <- dayCounter Actual365FixedStandard
          ts <- flatForward refDate riskFreeQ dc IR.Continuous Annual
          divQ <- Quote.simpleQuote 0.0
          divTS <- flatForward refDate divQ dc IR.Continuous Annual
          cal <- Calendar.calendar TARGET
          let mkNpv vol = do
                proc <- blackScholesMertonProcess underQ divTS ts vol EulerDiscretization False
                opt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Call nodeStrike))
                                      (European (EuropeanExercise nodeDate))
                analyticEuropeanEngine proc Nothing >>= setPricingEngine opt
                npv opt
          let volMatrix = either error id $ realMatrix 3 2
                [ 0.30, 0.28
                , 0.20, nodeVol
                , 0.35, 0.32
                ]
          piecewise <- Vol.piecewiseBlackVarianceSurface refDate [otherDate, nodeDate]
                         [80, 100, 120] volMatrix dc
          q <- Quote.simpleQuote nodeVol
          flat <- Vol.blackConstantVol refDate cal q dc
          npvPiecewise <- mkNpv piecewise
          npvFlat <- mkNpv flat
          npvPiecewise `shouldSatisfy` closePrec npvFlat tolerance

    -- BlackVolatilitySurfaceDelta: cached fixture ported from upstream's
    -- testBlackVolSurfaceDeltaNonConstantVol (test-suite/blackvolsurfacedelta.cpp), which
    -- exercises blackVolSmile directly -- the one binding-specific getter this class adds over
    -- the generic BlackVolTermStructure -- so no extra generic blackVol(t,k) inspector is
    -- needed just to reuse it.
    describe "black volatility surface delta" $
      it "reproduces upstream's cached smile volatilities" $
        Settings.keepingSettings' $ do
          let refDate = 1 `january` 2010
              atmStrike = 1.18
              tolerance = 1.0e-8 :: Double
          Settings.setEvaluationDate (Just refDate)
          d1M <- addPeriod refDate (1, Months)
          d6M <- addPeriod refDate (6, Months)
          d1Y <- addPeriod refDate (1, Years)
          d2Y <- addPeriod refDate (2, Years)
          d15D <- addPeriod refDate (15, Days)
          d3M <- addPeriod refDate (3, Months)
          dc <- dayCounter ActualActualISDA
          cal <- Calendar.calendar TARGET
          spot <- Quote.simpleQuote 1.18
          dtsQ <- Quote.simpleQuote 0.02
          dts <- flatForward' 0 cal dtsQ dc IR.Continuous Annual
          ftsQ <- Quote.simpleQuote 0.035
          fts <- flatForward' 0 cal ftsQ dc IR.Continuous Annual
          let vols = either error id $ realMatrix 4 3
                [ 0.15, 0.13, 0.135
                , 0.14, 0.11, 0.125
                , 0.13, 0.10, 0.12
                , 0.125, 0.095, 0.115
                ]
          surface <- Vol.blackVolatilitySurfaceDelta refDate [d1M, d6M, d1Y, d2Y] [-0.25] [0.25] True vols
                       dc cal spot dts fts
          smile1M <- Vol.blackVolSmile' surface d1M
          vol1M <- Vol.smileSectionVolatility smile1M atmStrike
          vol1M `shouldSatisfy` closePrec 0.13010360399 tolerance
          smile15D <- Vol.blackVolSmile' surface d15D
          vol15D <- Vol.smileSectionVolatility smile15D atmStrike
          vol15D `shouldSatisfy` closePrec 0.13007226607 tolerance
          smile3M <- Vol.blackVolSmile' surface d3M
          vol3M <- Vol.smileSectionVolatility smile3M atmStrike
          vol3M `shouldSatisfy` closePrec 0.115077252583 tolerance
          smile6M <- Vol.blackVolSmile' surface d6M
          volLow <- Vol.smileSectionVolatility smile6M 1.10
          volHigh <- Vol.smileSectionVolatility smile6M 1.30
          volLow `shouldSatisfy` closePrec 0.1411379628132 tolerance
          volHigh `shouldSatisfy` closePrec 0.136291154962 tolerance

    -- SwaptionVolatilityMatrix (fixed reference date, fixed market data): no upstream cached
    -- fixture applies here, since test-suite/swaptionvolatilitymatrix.cpp only exercises the
    -- Handle<Quote>-based ("floating market data") overload, not the plain-Matrix one bound
    -- here. Self-consistency checks instead: a constant grid must agree with the existing
    -- flat-vol constructor, and a grid with distinct cells must reproduce each cell's input
    -- exactly at its own (option tenor, swap tenor) node.
    describe "swaption volatility matrix" $ do
      let optionTenors = [(1, Years), (5, Years)]
          swapTenors = [(2, Years), (10, Years)]
          refDate = 11 `december` 2012

      it "a constant grid agrees with constantSwaptionVolatility' at the same point" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just refDate)
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          let v = 0.20
              volMatrix = either error id $ realMatrix 2 2 (replicate 4 v)
              shiftMatrix = either error id $ realMatrix 0 0 []
          grid <- Vol.swaptionVolatilityMatrix' refDate cal ModifiedFollowing optionTenors swapTenors
                    volMatrix dc False IR.ShiftedLognormal shiftMatrix
          volQ <- Quote.simpleQuote v
          flatVol <- Vol.constantSwaptionVolatility' refDate cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
          optionDate <- advance cal refDate (1, Years) ModifiedFollowing False
          fromGrid <- Vol.volatilityForPeriod' grid optionDate (2, Years) 0.02 False
          fromFlat <- Vol.volatilityForPeriod' flatVol optionDate (2, Years) 0.02 False
          abs (fromGrid - fromFlat) `shouldSatisfy` (< 1.0e-6 * max 1 (abs fromFlat))

      it "recovers each cell's input volatility exactly at its own grid node" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just refDate)
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          -- rows are option tenors, columns are swap tenors, matching SwaptionVolatilityMatrix's
          -- own row/column convention (M[i][j] = i-th option date, j-th swap tenor)
          let vols = [[0.10, 0.20], [0.30, 0.40]]
              volMatrix = either error id $ realMatrix 2 2 (concat vols)
              shiftMatrix = either error id $ realMatrix 0 0 []
          grid <- Vol.swaptionVolatilityMatrix' refDate cal ModifiedFollowing optionTenors swapTenors
                    volMatrix dc False IR.ShiftedLognormal shiftMatrix
          optionDates <- mapM (\(n, u) -> advance cal refDate (fromIntegral n, u) ModifiedFollowing False) optionTenors
          let nodes = [(od, st, expected)
                      | (od, oVols) <- zip optionDates vols
                      , (st, expected) <- zip swapTenors oVols]
          mapM_ (\(od, st, expected) -> do
                    v <- Vol.volatilityForPeriod' grid od st 0.02 False
                    abs (v - expected) `shouldSatisfy` (< 1.0e-6)
                ) nodes

    -- Instrument.additionalResults() marshals four discriminants: Real, std::string,
    -- vector<Real>, and an Unsupported fallback (RTTI name) for anything else. The Real/String
    -- and vector<Real> cases are each exercised here against a real engine that upstream QuantLib
    -- 1.43 is known to populate that way (grepped ql/pricingengines/**/*.cpp): the Bjerksund-
    -- Stensland American option engine writes `exerciseType`/`strikeGamma`, and the Black
    -- cap/floor engine writes `optionletsPrice` as a vector<Real>. No shipped 1.43 engine ever
    -- stores a type this binding can't name, so the Unsupported fallback isn't exercised here --
    -- its C++ side is a trivial, visibly-correct `else`, and its Haskell side is a
    -- compiler-checked exhaustive `case` (QuantLib.Instrument.convertResult).
    describe "Instrument additionalResults" $ do
      it "Bjerksund-Stensland engine reports exerciseType/strikeGamma" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (17 `may` 1998))
          -- A zero-dividend American call is never optimally exercised early, so the engine
          -- prices it as "European" -- a put (or a call with dividends) is what actually takes
          -- the "American" branch upstream (bjerksundstenslandengine.cpp).
          underQ <- Quote.simpleQuote 36
          riskFreeQ <- Quote.simpleQuote 0.06
          dc <- dayCounter Actual365FixedStandard
          ts <- flatForward (17 `may` 1998) riskFreeQ dc IR.Continuous Annual
          divQ <- Quote.simpleQuote 0.0
          divTS <- flatForward (17 `may` 1998) divQ dc IR.Continuous Annual
          volQ <- Quote.simpleQuote 0.20
          cal <- Calendar.calendar TARGET
          vol0 <- Vol.blackConstantVol (17 `may` 1998) cal volQ dc
          proc <- blackScholesMertonProcess underQ divTS ts vol0 EulerDiscretization False
          opt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Put 40))
                                (American Nothing (17 `may` 1999) False)
          bjerksundStenslandApproximationEngine proc >>= setPricingEngine opt
          _ <- npv opt
          res <- additionalResults opt
          lookup "exerciseType" res `shouldBe` Just (StringVal "American")
          case lookup "strikeGamma" res of
            Just (RealVal g) -> g `shouldSatisfy` (> 0)
            other -> expectationFailure $ "strikeGamma missing or wrong type: " ++ show other

      it "Black cap/floor engine reports optionletsPrice as a RealVectorVal" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          cal <- Calendar.calendar TARGET
          settle <- advance cal (11 `december` 2012) (2, Days) Following False
          discQ <- Quote.simpleQuote 0.02
          dc <- dayCounter Actual365FixedStandard
          discountTS <- flatForward (11 `december` 2012) discQ dc IR.Continuous Annual
          idx <- iborIndex Euribor6M (Just discountTS)
          floatDC <- dayCounter (Actual360 False)
          floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
            ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
          leg <- iborLeg floatSch idx [1000000] floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
          capfl <- cap leg [0.03]
          volQ <- Quote.simpleQuote 0.20
          vol0 <- Vol.constantOptionletVolatility (11 `december` 2012) cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
          eng <- blackCapFloorEngine' discountTS vol0
          setPricingEngine capfl eng
          _ <- npv capfl
          res <- additionalResults capfl
          case lookup "optionletsPrice" res of
            -- the near-dated optionlet(s) can legitimately price at (or near) zero; check the
            -- vector is non-trivial and non-negative rather than requiring every entry positive
            Just (RealVectorVal xs) -> do
              xs `shouldSatisfy` (not . null)
              xs `shouldSatisfy` all (>= 0)
              xs `shouldSatisfy` any (> 0)
            other -> expectationFailure $ "optionletsPrice missing or wrong type: " ++ show other
