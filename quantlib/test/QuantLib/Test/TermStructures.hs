{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.TermStructures (htf_thisModulesTests)
where

import Test.Framework
import Test.HUnit.Lang

import Data.Time.Calendar
import Data.Word

import QuantLib.Compounding
import QuantLib.Currency
import QuantLib.Index.Ibor
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
import QuantLib.Time.Period
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
test_ReferenceChange = keepingSettings' $ do
  (_calendar, dc, settlementDays, _ts) <- setup
  flatRate <- simpleQuote 0.03
  calendar <- nullCalendar
  flatQuote <- asQuote flatRate
  ts <- flatForward' settlementDays calendar flatQuote dc Continuous Annual
  tod <- evaluationDate

  expected <- mapM (\d -> discount' ts (addDays d tod) False) days
  setEvaluationDate (Just $ addDays 30 tod)
  calculated <- mapM (\d -> discount' ts (addDays (30+d) tod) False) days

  mapM_ (\(x1, x2) -> subAssert $ assertClose x1 x2) (zip expected calculated)
  where
    days = [10, 30, 60, 120, 360, 720]

test_Implied :: IO ()
test_Implied = keepingSettings' $ do
  (calendar, _dc, settlementDays, ts) <- setup
  tod <- evaluationDate
  let newToday = addGregorianYearsClip 3 tod
  newSettlement <- advance calendar newToday (fromIntegral settlementDays) Days Following False
  let testDate = addGregorianYearsClip 5 newSettlement
  implied <- impliedTermStructure ts newSettlement
  print "!!!"
  asTermStructure ts >>= maxDate >>= print
  print newSettlement
  --baseDiscount <- discount' ts newSettlement False
  --dsc <- discount' implied testDate False
  --impliedDiscount <- discount' implied testDate False

  --assertBool $ dsc - baseDiscount * impliedDiscount <= tolerance
  return ()
  where
    tolerance = 1.0e-10

setup :: IO (Calendar, DayCounter, Word, YieldTermStructure)
setup = do
  calendar <- target
  d <- today
  today' <- adjust calendar d Following
  setEvaluationDate (Just today')
  settlement <- advance calendar today' (fromIntegral settlementDays) Days Following False
  dc <- actual360
  deposits <- mapM
    (\(n, u, r) -> do
      q <- simpleQuote (r/100) >>= asQuote
      p <- period n u
      depositRateHelper q p settlementDays calendar ModifiedFollowing True dc)
    depositData
  p6m <- period 6 Months
  ccy <- eur
  index <- iborIndex "dummy" p6m settlementDays ccy calendar ModifiedFollowing False dc Nothing
  t360 <- thirty360
  swaps <- mapM
    (\(n, u, r) -> do
      q <- simpleQuote (r/100) >>= asQuote
      p <- period n u
      swapRateHelper' q p calendar Annual Unadjusted t360 index Nothing Nothing Nothing >>= asRateHelper)
    swapData

  ts <- piecewiseYieldCurve settlement (deposits ++ swaps) dc [] 1.0e-12 Discount LogLinear
  return (calendar, dc, settlementDays, ts)

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
