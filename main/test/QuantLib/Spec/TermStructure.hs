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
import QuantLib.Instrument(npv, setPricingEngine, SettlementType(Physical), SettlementMethod(PhysicalOTC), PositionType(Long))
import QuantLib.Instrument.Swap(vanillaSwap, swap, makeVanillaSwap, SwapType(Payer), swaption)
import qualified QuantLib.Instrument.Swap as Swap
import qualified QuantLib.Instrument.Bond as Bond
import QuantLib.Instrument.CapFloor(cap)
import QuantLib.CashFlow(iborLeg)
import QuantLib.Instrument.Option(vanillaOption, EuropeanExercise(..), PlainVanillaPayoff(..), Exercise(European), StrikedPayoff(PlainVanilla), OptionType(Call))
import qualified QuantLib.Instrument.Forward as Fwd
import QuantLib.Process(blackScholesMertonProcess, ProcessDiscretization(EulerDiscretization))
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.PricingEngine(discountingSwapEngine, analyticEuropeanEngine, blackSwaptionEngine', blackCapFloorEngine', bachelierSwaptionEngine', bachelierCapFloorEngine')

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
