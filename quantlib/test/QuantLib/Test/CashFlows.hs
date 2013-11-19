{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.CashFlows (htf_thisModulesTests)
-- cashflows.cpp
where

import Test.Framework

import Control.Monad(void)
import Data.Time.Calendar

import QuantLib.CashFlow.Leg
import QuantLib.CashFlow.CouponPricer
import QuantLib.Compounding
import QuantLib.Index.Ibor
import QuantLib.InterestRate
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Schedule
import QuantLib.Time.Unit
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

test_Settings :: IO ()
test_Settings = keepingSettings' $ do
  tod <- today
  setEvaluationDate (Just tod)
  l <- leg (zip (repeat 1.0) [tod .. addDays 2 tod])

  -- 1)
  setIncludeReferenceDateEvents False
  setIncludeTodaysCashFlows Nothing
  cases12 l

  -- 2)
  setIncludeReferenceDateEvents False
  setIncludeTodaysCashFlows (Just False)
  cases12 l

  -- 3)
  setIncludeReferenceDateEvents True
  setIncludeTodaysCashFlows Nothing
  cases34 l

  -- 4)
  setIncludeReferenceDateEvents True
  setIncludeTodaysCashFlows $ Just True
  cases34 l

  -- 5)
  setIncludeReferenceDateEvents True
  setIncludeTodaysCashFlows $ Just False
  checkInclusion l 0 [(0, False), (1, False)]
  checkInclusion l 1 [(0, True), (1, True), (2, False)]
  checkInclusion l 2 [(1, True), (2, True), (3, False)]

  dc <- actual365Fixed
  noDisc <- interestRate 0.0 dc Continuous Annual

  setIncludeTodaysCashFlows Nothing
  checkNPV l noDisc False 2.0
  checkNPV l noDisc True 3.0

  setIncludeTodaysCashFlows $ Just False
  checkNPV l noDisc False 2.0
  checkNPV l noDisc True 2.0
  where
    cases12 l = do
      checkInclusion l 0 [(0, False), (1, False)]
      checkInclusion l 1 [(0, True), (1, False), (2, False)]
      checkInclusion l 2 [(1, True), (2, False), (3, False)]
    cases34 l = do
      checkInclusion l 0 [(0, True), (1, False)]
      checkInclusion l 1 [(0, True), (1, True), (2, False)]
      checkInclusion l 2 [(1, True), (2, True), (3, False)]

checkInclusion :: Leg -> Int -> [(Int, Bool)] -> IO ()
checkInclusion l n x = do
  tod <- evaluationDate
  mapM_ (\(days, expected) -> do
    cfs <- cashFlows l Nothing (Just $ addDays (fromIntegral days) tod)
    let (_, _, o) = cfs !! n
    assertEqual expected (not o))
    x
  
checkNPV :: Leg -> InterestRate -> Bool -> Double -> IO ()
checkNPV l r includeRef expected = do
  tod <- evaluationDate
  v <- npvFromYield' l r includeRef (Just tod) (Just tod)
  assertBool $ abs(v - expected) <= 1.0e-6

-- dynamic cast of coupon in Black pricer
test_AccessViolation :: IO ()
test_AccessViolation = keepingSettings' $ do
  setEvaluationDate (Just $ 7 `april` 2010)
  cal <- target
  dc <- actual365Fixed
  q <- simpleQuote 0.04875825 >>= asQuote
  ts <- flatForward (9 `april` 2010) q dc Continuous Annual
  v <- simpleQuote 0.10 >>= asQuote
  vol <- constantOptionletVolatility' 2 cal ModifiedFollowing v dc
  let p = (3, Months)
  index3m <- usdLibor p (Just ts)
  pricer <- blackIborCouponPricer vol
  sch <- schedule (Just $ 20 `september` 2013) (20 `december` 2013) p cal Following Following Backward False Nothing Nothing
  cpns <- iborLeg sch index3m [100] dc Following [2] [] [0.000115] [] [] False False
  setCouponPricer cpns pricer
  void $ nextCashFlowAmount cpns True Nothing
  assertBool True

test_DefaultSettlementDate :: IO ()
test_DefaultSettlementDate = do
  tod <- evaluationDate
  cal <- target
  sch <- schedule (Just $ addGregorianMonthsClip (-2) tod) (addGregorianMonthsClip 4 tod) (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
  dc <- actual360
  cpn <- interestRate 0.03 dc Simple Annual
  l <- fixedRateLeg sch [100.0] [cpn] Following dc cal
  accP <- accruedPeriod l False Nothing
  assertBool $ accP /= 0
  accD <- accruedDays l False Nothing
  assertBool $ accD /= 0
  accA <- accruedAmount l False Nothing
  assertBool $ accA /= 0

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
