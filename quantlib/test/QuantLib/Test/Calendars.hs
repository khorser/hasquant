{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.Calendars (htf_thisModulesTests)
-- calendars.cpp
where

import Test.Framework

import Data.Time.Calendar

import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.JointCalendarRule
import QuantLib.Time.Period
import QuantLib.Time.Unit
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

test_ModifiedCalendars :: IO ()
test_ModifiedCalendars = do
  c1 <- target
  c2 <- unitedStatesNYSE
  let d1 = 1 `may` 2004
      d2 = 26 `april` 2004
  h1 <- isHoliday c1 d1
  b1 <- isBusinessDay c1 d2
  h2 <- isHoliday c2 d1
  b2 <- isBusinessDay c2 d2
  assertBool h1
  assertBool b1
  assertBool h2
  assertBool b2

  removeHoliday c1 d1
  addHoliday c1 d2
  h1' <- isHoliday c1 d1
  b1' <- isBusinessDay c1 d2
  assertBool (not h1')
  assertBool (not b1')

  c3 <- target
  h3 <- isHoliday c3 d1
  b3 <- isBusinessDay c3 d2
  assertBool (not h3)
  assertBool (not b3)

  removeHoliday c1 d2
  addHoliday c1 d1
  h1'' <- isHoliday c1 d1
  b1'' <- isBusinessDay c1 d2
  assertBool h1''
  assertBool b1''

test_JointCalendars :: IO ()
test_JointCalendars = do
  c1 <- target
  c2 <- unitedKingdomExchange
  c3 <- unitedStatesNYSE
  c4 <- japan

  c12h <- jointCalendar2 c1 c2 JoinHolidays
  c12b <- jointCalendar2 c1 c2 JoinBusinessDays
  c123h <- jointCalendar3 c1 c2 c3 JoinHolidays
  c123b <- jointCalendar3 c1 c2 c3 JoinBusinessDays
  c1234h <- jointCalendar4 c1 c2 c3 c4 JoinHolidays
  c1234b <- jointCalendar4 c1 c2 c3 c4 JoinBusinessDays

  tod <- today
  mapM_ (\d -> do
    b1 <- isBusinessDay c1 d
    b2 <- isBusinessDay c2 d
    b3 <- isBusinessDay c3 d
    b4 <- isBusinessDay c4 d

    c12hb <- isBusinessDay c12h d
    c12bb <- isBusinessDay c12b d
    c123hb <- isBusinessDay c123h d
    c123bb <- isBusinessDay c123b d
    c1234hb <- isBusinessDay c1234h d
    c1234bb <- isBusinessDay c1234b d

    assertEqual (b1 && b2) c12hb
    assertEqual (b1 || b2) c12bb
    assertEqual (b1 && b2 && b3) c123hb
    assertEqual (b1 || b2 || b3) c123bb
    assertEqual (b1 && b2 && b3 && b4) c1234hb
    assertEqual (b1 || b2 || b3 || b4) c1234bb)
    [tod .. addGregorianYearsClip 1 tod]

test_USSettlement :: IO ()
test_USSettlement = do
  cal <- unitedStatesSettlement
  h <- holidays cal (1 `january` 2004) (31 `december` 2005) False
  assertEqual expectedHol h

  return ()
  where
    expectedHol = [
      1 `january` 2004,
      19 `january` 2004,
      16 `february` 2004,
      31 `may` 2004,
      5 `july` 2004,
      6 `september` 2004,
      11 `october` 2004,
      11 `november` 2004,
      25 `november` 2004,
      24 `december` 2004,
      31 `december` 2004,
      17 `january` 2005,
      21 `february` 2005,
      30 `may` 2005,
      4 `july` 2005,
      5 `september` 2005,
      10 `october` 2005,
      11 `november` 2005,
      24 `november` 2005,
      26 `december` 2005]


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
