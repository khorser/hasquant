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
  let oneYear = (1, Years)
      sixMonths = (6, Months)
      threeMonths = (3, Months)
      nineMonths = (9, Months)
      twelveMonths = (12, Months)

      od4 = dividePeriod oneYear 4
  assertEqual od4 (Right threeMonths)

  let od2 = dividePeriod oneYear 2
  assertEqual od2 (Right sixMonths)

  let a36 = addPeriods threeMonths sixMonths
  assertEqual a36 (Right nineMonths)

  let a3612 = a36 >>= (`addPeriods` oneYear)
  assertEqual a3612 (Right (21, Months))

  let twelveMonthsN = normalize twelveMonths
  assertEqual twelveMonthsN (Right oneYear)

test_WeekDaysAlgebra :: IO ()
test_WeekDaysAlgebra = do
  let twoWeeks = (2, Weeks)
      oneWeek = (1, Weeks)
      threeDays = (3, Days)
      oneDay = (1, Days)

      t2 = dividePeriod twoWeeks 2
  assertEqual t2 (Right oneWeek)

  let t7 = dividePeriod oneWeek 7
  assertEqual t7 (Right oneDay)

  let s1 = addPeriods threeDays oneDay
  assertEqual s1 (Right (4, Days))

  let s2 = s1 >>= (`addPeriods` oneWeek)
  assertEqual s2 (Right (11, Days))

  let sevenDays = (7, Days)
      sevenDaysN = normalize sevenDays
  assertEqual sevenDaysN (Right (1, Weeks))

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
