{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.CashFlows (htf_thisModulesTests)
-- cashflows.cpp
where

import Test.Framework

import Data.Time.Calendar
import Data.Time.Format()

import QuantLib.CashFlow.Leg
import QuantLib.Compounding
import QuantLib.InterestRate
import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
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
    cfs <- cashFlows l Nothing $ addDays (fromIntegral days) tod
    let (_, _, o) = cfs !! n
    assertEqual expected (not o))
    x
  
checkNPV :: Leg -> InterestRate -> Bool -> Double -> IO ()
checkNPV l r includeRef expected = do
  tod <- evaluationDate
  v <- npvFromYield' l r includeRef tod tod
  assertBool $ abs(v - expected) <= 1.0e-6

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
