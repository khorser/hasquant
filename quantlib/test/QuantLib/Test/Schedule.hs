{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.Schedule (htf_thisModulesTests)
-- Schedule.cpp
where

import Test.Framework

import Data.Time.Calendar

import QuantLib.Settings
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.Frequency
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.Time.Unit

{-# ANN module "HLint: ignore Use camelCase" #-}

test_DailySchedule :: IO ()
test_DailySchedule = keepingSettings' $ do
  let startDate = 17 `january` 2012
  calendar <- target
  p <- fromFrequency Daily
  s <- schedule (Just startDate) (addDays 7 startDate) p calendar Following Following Backward False Nothing Nothing
  assertEqual (dates s)
    [17 `january` 2012, 18 `january` 2012, 19 `january` 2012, 20 `january` 2012, 23 `january` 2012, 24 `january` 2012]

test_EndDateWithEomAdjustment :: IO ()
test_EndDateWithEomAdjustment = keepingSettings' $ do
  calendar <- japan
  p <- period 6 Months
  s <- schedule (Just $ 30 `september` 2009) (15 `june` 2012) p calendar Following Following Forward True Nothing Nothing
  assertEqual (dates s)
    [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 29 `june` 2012]

  s2 <- schedule (Just $ 30 `september` 2009) (15 `june` 2012) p calendar Following Unadjusted Forward True Nothing Nothing
  assertEqual (dates s2)
    [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 15 `june` 2012]

test_DatesPastEndDateWithEomAdjustment:: IO ()
test_DatesPastEndDateWithEomAdjustment = keepingSettings' $ do
  calendar <- target
  p <- period 1 Years
  s <- schedule (Just $ 28 `march` 2013) (30 `march` 2015) p calendar Unadjusted Unadjusted Forward True Nothing Nothing
  assertEqual (dates s) [31 `march` 2013, 31 `march` 2014, 30 `march` 2015]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
