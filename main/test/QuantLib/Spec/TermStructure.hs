{-# LANGUAGE ScopedTypeVariables #-}
module QuantLib.Spec.TermStructure (spec) where

import Test.Hspec
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
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Instrument(npv, setPricingEngine, SettlementType(Physical), SettlementMethod(PhysicalOTC))
import QuantLib.Instrument.Swap(vanillaSwap, SwapType(Payer), swaption)
import QuantLib.Instrument.Option(vanillaOption, EuropeanExercise(..), PlainVanillaPayoff(..), Exercise(European), StrikedPayoff(PlainVanilla), OptionType(Call))
import QuantLib.Process(blackScholesMertonProcess, ProcessDiscretization(EulerDiscretization))
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.PricingEngine(discountingSwapEngine, analyticEuropeanEngine, blackSwaptionEngine')

import QuantLib.Spec.Helpers(areClose)

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
            swap <- vanillaSwap Payer 1000000 fixedSch 0.02 fixedDC floatSch idx 0 floatDC
              Nothing Nothing
            eng <- discountingSwapEngine discountH Nothing Nothing Nothing
            setPricingEngine swap eng
            pure (swap, discountH, forecastH)

      it "a relinkable handle is accepted wherever a curve is" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          -- no sibling function, no wrapper: it upcasts like any hierarchy member
          (swap, _, _) <- setupSwap
          v <- npv swap
          v `shouldSatisfy` (not . isNaN)

      it "relinking the discount curve reprices without rebuilding" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (swap, discountH, _) <- setupSwap
          before <- npv swap
          flat 0.05 >>= linkTo discountH
          after <- npv swap
          abs (after - before) `shouldSatisfy` (> 1.0)

      it "relinking back restores the original value exactly" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (swap, discountH, _) <- setupSwap
          before <- npv swap
          flat 0.05 >>= linkTo discountH
          flat 0.02 >>= linkTo discountH
          -- exact, not approximate: relinking to an identical curve must reproduce the
          -- same arithmetic, and anything else means we are not reaching the same object
          npv swap `shouldReturn` before

      it "relinking the forecast curve reprices without rebuilding" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          -- the case with no workaround today: an IborIndex is cloned into every floating
          -- coupon at construction, so without a handle this needs the swap rebuilt
          (swap, _, forecastH) <- setupSwap
          before <- npv swap
          flat 0.05 >>= linkTo forecastH
          after <- npv swap
          abs (after - before) `shouldSatisfy` (> 1.0)

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
          before <- discount c 5.0 False
          Quote.simpleQuote 0.05 >>= Quote.linkTo qh
          after <- discount c 5.0 False
          abs (after - before) `shouldSatisfy` (> 0.01)

      it "relinking a quote back restores the original value exactly" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          q02 <- Quote.simpleQuote 0.02
          qh <- Quote.relinkableQuote (Just q02)
          dc <- dayCounter Actual365FixedStandard
          c <- flatForward (11 `december` 2012) qh dc IR.Continuous Annual
          before <- discount c 5.0 False
          Quote.simpleQuote 0.05 >>= Quote.linkTo qh
          Quote.simpleQuote 0.02 >>= Quote.linkTo qh
          -- exact, not approximate: same reasoning as the curve-relink-back check above
          discount c 5.0 False `shouldReturn` before

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
          before <- npv opt
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.40
          vol1 <- Vol.blackConstantVol (11 `december` 2012) cal q dc
          Vol.linkBlackVolTo volH vol1
          after <- npv opt
          abs (after - before) `shouldSatisfy` (> 0.5)

      -- A relinkable swaption vol surface propagates the same way: an engine built on it
      -- keeps tracking whatever surface the handle currently points at, so relinking reprices
      -- the swaption without rebuilding the engine. Mirrors the Black vol case above.
      let mkSwaption = do
            (swap, discountH, _) <- setupSwap
            cal <- Calendar.calendar TARGET
            dc <- dayCounter Actual365FixedStandard
            volQ <- Quote.simpleQuote 0.20
            vol0 <- Vol.constantSwaptionVolatility' (11 `december` 2012) cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
            volH <- Vol.relinkableSwaptionVolatilityStructure (Just vol0)
            eng <- blackSwaptionEngine' discountH volH
            -- the Black swaption engine requires a spot-starting swaption: the exercise date
            -- must fall on or before the swap's start date (13 december 2012)
            swpn <- swaption swap (European (EuropeanExercise (12 `december` 2012))) Physical PhysicalOTC
            setPricingEngine swpn eng
            pure (swpn, volH)

      it "relinking a swaption vol surface reprices the swaption, without rebuilding the engine" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just (11 `december` 2012))
          (swpn, volH) <- mkSwaption
          before <- npv swpn
          cal <- Calendar.calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.60
          vol1 <- Vol.constantSwaptionVolatility' (11 `december` 2012) cal ModifiedFollowing q dc IR.ShiftedLognormal 0
          Vol.linkSwaptionVolTo volH vol1
          after <- npv swpn
          abs (after - before) `shouldSatisfy` (> 0.5)
