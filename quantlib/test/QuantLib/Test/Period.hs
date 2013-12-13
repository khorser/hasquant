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

      (Right od4) = dividePeriod oneYear 4
  assertEqual od4 threeMonths

  let (Right od2) = dividePeriod oneYear 2
  assertEqual od2 sixMonths

  let (Right a36) = addPeriods threeMonths sixMonths
  assertEqual a36 nineMonths

  let (Right a3612) = addPeriods a36 oneYear
  assertEqual a3612 (21, Months)

  let (Right twelveMonthsN) = normalize twelveMonths
  assertEqual twelveMonthsN oneYear

test_WeekDaysAlgebra :: IO ()
test_WeekDaysAlgebra = do
  let twoWeeks = (2, Weeks)
      oneWeek = (1, Weeks)
      threeDays = (3, Days)
      oneDay = (1, Days)

      (Right t2) = dividePeriod twoWeeks 2
  assertEqual t2 oneWeek

  let (Right t7) = dividePeriod oneWeek 7
  assertEqual t7 oneDay

  let (Right s1) = addPeriods threeDays oneDay
  assertEqual s1 (4, Days)

  let (Right s2) = addPeriods s1 oneWeek
  assertEqual s2 (11, Days)

  let sevenDays = (7, Days)
      (Right sevenDaysN) = normalize sevenDays
  assertEqual sevenDaysN (1, Weeks)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
