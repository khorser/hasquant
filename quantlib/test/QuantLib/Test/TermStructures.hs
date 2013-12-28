{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.TermStructures (htf_thisModulesTests)
-- termstructures.cpp
where

import Test.Framework
import Test.HUnit.Lang

import Control.Applicative((<$>))
import Control.Monad.IO.Class
import Data.Time.Calendar
import Data.Word

import QuantLib.Compounding
import QuantLib.Currency
import QuantLib.Index.Ibor
import QuantLib.InterestRate
import QuantLib.Math.Interpolation
import QuantLib.Settings
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Trait
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date(today)
import QuantLib.Time.Frequency
import QuantLib.Time.DayCounter
import QuantLib.Time.Unit
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

assertClose :: Double -> Double -> Assertion
assertClose x1 x2 = assertBool (close x1 x2)

-- literal translation of close from ql/math/comparison.hpp
close :: Double -> Double -> Bool
close x1 x2 =
  x1 == x2
  || x1 * x2 == 0 && diff < tolerance * tolerance
  || diff <= tolerance * abs x1 && diff <= tolerance * abs x2
  where diff = abs(x1 - x2)
        tolerance = 42 * qlEpsilon

test_ReferenceChange :: IO ()
test_ReferenceChange = keepingSettings' $ runQLE $ do
  (_calendar, settlementDays, _ts) <- setup
  flatRate <- simpleQuote 0.03
  calendar <- nullCalendar
  flatQuote <- asQuote flatRate
  actual360dc <- actual360
  ts <- flatForward' settlementDays calendar flatQuote actual360dc Continuous Annual
  tod <- evaluationDate

  expected <- mapM (\d -> discount' ts (addDays d tod) False) days
  setEvaluationDate (Just $ addDays 30 tod)
  calculated <- mapM (\d -> discount' ts (addDays (30+d) tod) False) days

  mapM_ (\(x1, x2) -> liftIO $ subAssert $ assertClose x1 x2) (zip expected calculated)
  where days = [10, 30, 60, 120, 360, 720]

test_Implied :: IO ()
test_Implied = keepingSettings' $ runQLE $ do
  (calendar, settlementDays, ts) <- setup
  tod <- evaluationDate
  let newToday = addGregorianYearsClip 3 tod
  newSettlement <- advance calendar newToday (fromIntegral settlementDays) Days Following False
  let testDate = addGregorianYearsClip 5 newSettlement
  implied <- impliedTermStructure ts newSettlement
  baseDiscount <- discount' ts newSettlement False
  dsc <- discount' ts testDate False
  impliedDiscount <- discount' implied testDate False

  liftIO $ assertBool $ dsc - baseDiscount * impliedDiscount <= tolerance
  where tolerance = 1.0e-10

test_FSpreaded :: IO ()
test_FSpreaded = keepingSettings' $ runQLE $ do
  (_calendar, _settlementDays, ts) <- setup
  me <- simpleQuote 0.01 >>= asQuote
  val <- value me
  spreaded <- forwardSpreadedTermStructure ts me
  refDate <- asTermStructure ts >>= referenceDate
  let testDate = addGregorianYearsClip 5 refDate
  actual360dc <- actual360
  forward <- rate <$> forwardRate' ts testDate testDate actual360dc Continuous NoFrequency False
  spreadedForward <- rate <$> forwardRate' spreaded testDate testDate actual360dc Continuous NoFrequency False

  liftIO $ assertBool $ forward - (spreadedForward - val) <= tolerance
  where tolerance = 1.0e-10

test_ZSpreaded :: IO ()
test_ZSpreaded = keepingSettings' $ runQLE $ do
  (_calendar, _settlementDays, ts) <- setup
  q <- simpleQuote 0.01 >>= asQuote
  val <- value q
  actual360dc <- actual360
  spreaded <- zeroSpreadedTermStructure ts q Continuous NoFrequency actual360dc
  refDate <- asTermStructure ts >>= referenceDate
  let testDate = addGregorianYearsClip 5 refDate
  zero <- rate <$> zeroRate' ts testDate actual360dc Continuous NoFrequency False
  spreadedZero <- rate <$> zeroRate' spreaded testDate actual360dc Continuous NoFrequency False

  liftIO $ assertBool $ zero - (spreadedZero - val) <= tolerance
  where tolerance = 1.0e-10

setup :: QLE s (Calendar s, Word, YieldTermStructure s)
setup = do
  calendar <- target
  d <- liftIO $ today
  today' <- adjust calendar d Following
  setEvaluationDate (Just today')
  settlement <- advance calendar today' (fromIntegral settlementDays) Days Following False
  actual360dc <- actual360
  deposits <- mapM
    (\(n, u, r) -> do
      q <- simpleQuote (r/100) >>= asQuote
      depositRateHelper q (n, u) settlementDays calendar ModifiedFollowing True actual360dc)
    depositData
  ccy <- eur
  thirty360dc <- thirty360BondBasis
  index <- iborIndex "dummy" (6, Months) settlementDays ccy calendar ModifiedFollowing False actual360dc Nothing
  swaps <- mapM
    (\(n, u, r) -> do
      q <- simpleQuote (r/100) >>= asQuote
      swapRateHelper' q (n, u) calendar Annual Unadjusted thirty360dc index Nothing (0, Days) Nothing >>= asRateHelper)
    swapData

  ts <- piecewiseYieldCurve settlement (deposits ++ swaps) actual360dc [] 1.0e-12 Discount LogLinear
  return (calendar, settlementDays, ts)

  where
    settlementDays = 2
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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
