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
