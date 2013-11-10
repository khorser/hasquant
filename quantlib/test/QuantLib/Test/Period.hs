{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.Period (htf_thisModulesTests)
-- period.cpp
where

import Test.Framework

import QuantLib.Time.Period
import QuantLib.Time.Unit

{-# ANN module "HLint: ignore Use camelCase" #-}

test_YearsMonthsAlgebra :: IO ()
test_YearsMonthsAlgebra  = do
  oneYear <- period 1 Years
  sixMonths <- period 6 Months
  threeMonths <- period 3 Months
  nineMonths <- period 9 Months

  od4 <- dividePeriod oneYear 4
  let (Right od4b) = periodsEQ od4 threeMonths
  assertBool od4b

  od2 <- dividePeriod oneYear 2
  let (Right od2b) = periodsEQ od2 sixMonths
  assertBool od2b

  a36 <- addPeriods threeMonths sixMonths
  let (Right a36b) = periodsEQ a36 nineMonths
  assertBool a36b

  a3612 <- addPeriods a36 oneYear
  assertEqual (units a3612) Months
  assertEqual (periodLength a3612) 21

  twelveMonths <- period 12 Months
  assertEqual (units twelveMonths) Months
  assertEqual (periodLength twelveMonths) 12

  twelveMonthsN <- normalize twelveMonths
  assertEqual (units twelveMonthsN) Years
  assertEqual (periodLength twelveMonthsN) 1

test_WeekDaysAlgebra :: IO ()
test_WeekDaysAlgebra = do
  twoWeeks <- period 2 Weeks
  oneWeek <- period 1 Weeks
  threeDays <- period 3 Days
  oneDay <- period 1 Days

  t2 <- dividePeriod twoWeeks 2
  let (Right t2b) = periodsEQ t2 oneWeek
  assertBool t2b
  t7 <- dividePeriod oneWeek 7
  let (Right t7b) = periodsEQ t7 oneDay
  assertBool t7b

  s1 <- addPeriods threeDays oneDay
  assertEqual (units s1) Days
  assertEqual (periodLength s1) 4

  s2 <- addPeriods s1 oneWeek
  assertEqual (units s2) Days
  assertEqual (periodLength s2) 11

  sevenDays <- period 7 Days
  assertEqual (units sevenDays) Days
  assertEqual (periodLength sevenDays) 7

  sevenDaysN <- normalize sevenDays
  assertEqual (units sevenDaysN) Weeks
  assertEqual (periodLength sevenDaysN) 1

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
