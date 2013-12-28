{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.Calendars (htf_thisModulesTests)
-- calendars.cpp
where

import Test.Framework

import Control.Monad.IO.Class
import Data.Time.Calendar

import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.JointCalendarRule
import QuantLib.Time.Weekday
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

test_ModifiedCalendars :: IO ()
test_ModifiedCalendars = do
  (h1, b1, h2, b2, h1', b1', h3, b3, h1'', b1'') <- runQLE $ do
    c1 <- target
    c2 <- unitedStatesNYSE
    let d1 = 1 `may` 2004
        d2 = 26 `april` 2004
    h1 <- isHoliday c1 d1
    b1 <- isBusinessDay c1 d2
    h2 <- isHoliday c2 d1
    b2 <- isBusinessDay c2 d2

    removeHoliday c1 d1
    addHoliday c1 d2
    h1' <- isHoliday c1 d1
    b1' <- isBusinessDay c1 d2

    c3 <- target
    h3 <- isHoliday c3 d1
    b3 <- isBusinessDay c3 d2

    removeHoliday c1 d2
    addHoliday c1 d1
    h1'' <- isHoliday c1 d1
    b1'' <- isBusinessDay c1 d2
    return (h1, b1, h2, b2, h1', b1', h3, b3, h1'', b1'')

  assertBool h1
  assertBool b1
  assertBool h2
  assertBool b2
  assertBool (not h1')
  assertBool (not b1')
  assertBool (not h3)
  assertBool (not b3)
  assertBool h1''
  assertBool b1''

test_JointCalendars :: IO ()
test_JointCalendars = runQLE $ do
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

    tod <- liftIO today
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

      liftIO $ do
        assertEqual (b1 && b2) c12hb
        assertEqual (b1 || b2) c12bb
        assertEqual (b1 && b2 && b3) c123hb
        assertEqual (b1 || b2 || b3) c123bb
        assertEqual (b1 && b2 && b3 && b4) c1234hb
        assertEqual (b1 || b2 || b3 || b4) c1234bb)
      [tod .. addGregorianYearsClip 1 tod]

test_USSettlement :: IO ()
test_USSettlement = do
  h <- runQLE $ do
    cal <- unitedStatesSettlement
    holidays cal (1 `january` 2004) (31 `december` 2005) False
  assertEqual expectedHol h
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

test_USGovernmentBondMarket :: IO ()
test_USGovernmentBondMarket = do
  h <- runQLE $ do
    cal <- unitedStatesGovernmentBond
    holidays cal (1 `january` 2004) (31 `december` 2004) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2004,
      19 `january` 2004,
      16 `february` 2004,
      9 `april` 2004,
      31 `may` 2004,
      5 `july` 2004,
      6 `september` 2004,
      11 `october` 2004,
      11 `november` 2004,
      25 `november` 2004,
      24 `december` 2004]

test_USNewYorkStockExchange :: IO ()
test_USNewYorkStockExchange = runQLE $ do
  cal <- unitedStatesNYSE
  h <- holidays cal (1 `january` 2004) (31 `december` 2006) False
  liftIO $ assertEqual expectedHol h
  mapM_ (\d -> do
    b <- isHoliday cal d
    liftIO $ assertBool b) histClose
  where
    expectedHol = [
      1 `january` 2004,
      19 `january` 2004,
      16 `february` 2004,
      9 `april` 2004,
      31 `may` 2004,
      11 `june` 2004,
      5 `july` 2004,
      6 `september` 2004,
      25 `november` 2004,
      24 `december` 2004,

      17 `january` 2005,
      21 `february` 2005,
      25 `march` 2005,
      30 `may` 2005,
      4 `july` 2005,
      5 `september` 2005,
      24 `november` 2005,
      26 `december` 2005,

      2 `january` 2006,
      16 `january` 2006,
      20 `february` 2006,
      14 `april` 2006,
      29 `may` 2006,
      4 `july` 2006,
      4 `september` 2006,
      23 `november` 2006,
      25 `december` 2006]
    histClose = [
      11 `june` 2004,
      14 `september` 2001,
      13 `september` 2001,
      12 `september` 2001,
      11 `september` 2001,
      14 `july` 1977,
      25 `january` 1973,
      28 `december` 1972,
      21 `july` 1969,
      31 `march` 1969,
      10 `february` 1969,
      5 `july` 1968,
      12 `june` 1968,
      19 `june` 1968,
      26 `june` 1968,
      3 `july` 1968 ,
      10 `july` 1968,
      17 `july` 1968,
      20 `november` 1968,
      27 `november` 1968,
      4 `december` 1968 ,
      11 `december` 1968,
      18 `december` 1968,
      4 `november` 1980,
      2 `november` 1976,
      7 `november` 1972,
      5 `november` 1968,
      3 `november` 1964]

test_TARGET :: IO ()
test_TARGET = do
  h <- runQLE $ do
    cal <- target
    holidays cal (1 `january` 1999) (31 `december` 2006) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 1999,
      31 `december` 1999,

      21 `april` 2000,
      24 `april` 2000,
      1 `may` 2000,
      25 `december` 2000,
      26 `december` 2000,

      1 `january` 2001,
      13 `april` 2001,
      16 `april` 2001,
      1 `may` 2001,
      25 `december` 2001,
      26 `december` 2001,
      31 `december` 2001,

      1 `january` 2002,
      29 `march` 2002,
      1 `april` 2002,
      1 `may` 2002,
      25 `december` 2002,
      26 `december` 2002,

      1 `january` 2003,
      18 `april` 2003,
      21 `april` 2003,
      1 `may` 2003,
      25 `december` 2003,
      26 `december` 2003,

      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,

      25 `march` 2005,
      28 `march` 2005,
      26 `december` 2005,

      14 `april` 2006,
      17 `april` 2006,
      1 `may` 2006,
      25 `december` 2006,
      26 `december` 2006]

test_GermanyFrankfurt :: IO ()
test_GermanyFrankfurt = do
  h <- runQLE $ do
    cal <- germanyFrankfurtStockExchange
    holidays cal (1 `january` 2003) (31 `december` 2004) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2003,
      18 `april` 2003,
      21 `april` 2003,
      1 `may` 2003,
      24 `december` 2003,
      25 `december` 2003,
      26 `december` 2003,
      31 `december` 2003,

      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      24 `december` 2004,
      31 `december` 2004]

test_GermanyEurex :: IO ()
test_GermanyEurex = do
  h <- runQLE $ do
    cal <- germanyEurex
    holidays cal (1 `january` 2003) (31 `december` 2004) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2003,
      18 `april` 2003,
      21 `april` 2003,
      1 `may` 2003,
      24 `december` 2003,
      25 `december` 2003,
      26 `december` 2003,
      31 `december` 2003,

      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      24 `december` 2004,
      31 `december` 2004]

test_GermanyXetra :: IO ()
test_GermanyXetra = do
  h <- runQLE $ do
    cal <- germanyXetra
    holidays cal (1 `january` 2003) (31 `december` 2004) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2003,
      18 `april` 2003,
      21 `april` 2003,
      1 `may` 2003,
      24 `december` 2003,
      25 `december` 2003,
      26 `december` 2003,
      31 `december` 2003,

      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      24 `december` 2004,
      31 `december` 2004]


test_UKSettlement :: IO ()
test_UKSettlement = do
  h <- runQLE $ do
    cal <- unitedKingdomSettlement
    holidays cal (1 `january` 2004) (31 `december` 2007) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      3 `may` 2004,
      31 `may` 2004,
      30 `august` 2004,
      27 `december` 2004,
      28 `december` 2004,

      3 `january` 2005,
      25 `march` 2005,
      28 `march` 2005,
      2 `may` 2005,
      30 `may` 2005,
      29 `august` 2005,
      26 `december` 2005,
      27 `december` 2005,

      2 `january` 2006,
      14 `april` 2006,
      17 `april` 2006,
      1 `may` 2006,
      29 `may` 2006,
      28 `august` 2006,
      25 `december` 2006,
      26 `december` 2006,

      1 `january` 2007,
      6 `april` 2007,
      9 `april` 2007,
      7 `may` 2007,
      28 `may` 2007,
      27 `august` 2007,
      25 `december` 2007,
      26 `december` 2007]


test_UKExchange :: IO ()
test_UKExchange = do
  h <- runQLE $ do
    cal <- unitedKingdomExchange
    holidays cal (1 `january` 2004) (31 `december` 2007) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      3 `may` 2004,
      31 `may` 2004,
      30 `august` 2004,
      27 `december` 2004,
      28 `december` 2004,

      3 `january` 2005,
      25 `march` 2005,
      28 `march` 2005,
      2 `may` 2005,
      30 `may` 2005,
      29 `august` 2005,
      26 `december` 2005,
      27 `december` 2005,

      2 `january` 2006,
      14 `april` 2006,
      17 `april` 2006,
      1 `may` 2006,
      29 `may` 2006,
      28 `august` 2006,
      25 `december` 2006,
      26 `december` 2006,

      1 `january` 2007,
      6 `april` 2007,
      9 `april` 2007,
      7 `may` 2007,
      28 `may` 2007,
      27 `august` 2007,
      25 `december` 2007,
      26 `december` 2007]


test_UKMetals :: IO ()
test_UKMetals = do
  h <- runQLE $ do
    cal <- unitedKingdomMetals
    holidays cal (1 `january` 2004) (31 `december` 2007) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      3 `may` 2004,
      31 `may` 2004,
      30 `august` 2004,
      27 `december` 2004,
      28 `december` 2004,

      3 `january` 2005,
      25 `march` 2005,
      28 `march` 2005,
      2 `may` 2005,
      30 `may` 2005,
      29 `august` 2005,
      26 `december` 2005,
      27 `december` 2005,

      2 `january` 2006,
      14 `april` 2006,
      17 `april` 2006,
      1 `may` 2006,
      29 `may` 2006,
      28 `august` 2006,
      25 `december` 2006,
      26 `december` 2006,

      1 `january` 2007,
      6 `april` 2007,
      9 `april` 2007,
      7 `may` 2007,
      28 `may` 2007,
      27 `august` 2007,
      25 `december` 2007,
      26 `december` 2007]


test_ItalyExchange :: IO ()
test_ItalyExchange = do
  h <- runQLE $ do
    cal <- italyExchange
    holidays cal (1 `january` 2002) (31 `december` 2004) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2002,
      29 `march` 2002,
      1 `april` 2002,
      1 `may` 2002,
      15 `august` 2002,
      24 `december` 2002,
      25 `december` 2002,
      26 `december` 2002,
      31 `december` 2002,

      1 `january` 2003,
      18 `april` 2003,
      21 `april` 2003,
      1 `may` 2003,
      15 `august` 2003,
      24 `december` 2003,
      25 `december` 2003,
      26 `december` 2003,
      31 `december` 2003,

      1 `january` 2004,
      9 `april` 2004,
      12 `april` 2004,
      24 `december` 2004,
      31 `december` 2004]

test_Brazil :: IO ()
test_Brazil = do
  h <- runQLE $ do
    cal <- brazilSettlement
    holidays cal (1 `january` 2005) (31 `december` 2006) False
  assertEqual expectedHol h
  where
    expectedHol = [
      7 `february` 2005,
      8 `february` 2005,
      25 `march` 2005,
      21 `april` 2005,
      26 `may` 2005,
      7 `september` 2005,
      12 `october` 2005,
      2 `november` 2005,
      15 `november` 2005,

      27 `february` 2006,
      28 `february` 2006,
      14 `april` 2006,
      21 `april` 2006,
      1 `may` 2006,
      15 `june` 2006,
      7 `september` 2006,
      12 `october` 2006,
      2 `november` 2006,
      15 `november` 2006,
      25 `december` 2006]

test_SouthKoreanSettlement :: IO ()
test_SouthKoreanSettlement = do
  h <- runQLE $ do
    cal <- southKoreaSettlement
    holidays cal (1 `january` 2004) (31 `december` 2007) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2004,
      21 `january` 2004,
      22 `january` 2004,
      23 `january` 2004,
      1 `march` 2004,
      5 `april` 2004,
      15 `april` 2004,
      5 `may` 2004,
      26 `may` 2004,
      27 `september` 2004,
      28 `september` 2004,
      29 `september` 2004,

      8 `february` 2005,
      9 `february` 2005,
      10 `february` 2005,
      1 `march` 2005,
      5 `april` 2005,
      5 `may` 2005,
      6 `june` 2005,
      15 `august` 2005,
      19 `september` 2005,
      3 `october` 2005,

      30 `january` 2006,
      1 `march` 2006,
      1 `may` 2006,
      5 `may` 2006,
      31 `may` 2006,
      6 `june` 2006,
      17 `july` 2006,
      15 `august` 2006,
      3 `october` 2006,
      5 `october` 2006,
      6 `october` 2006,
      25 `december` 2006,

      1 `january` 2007,
      19 `february` 2007,
      1 `march` 2007,
      1 `may` 2007,
      24 `may` 2007,
      6 `june` 2007,
      17 `july` 2007,
      15 `august` 2007,
      24 `september` 2007,
      25 `september` 2007,
      26 `september` 2007,
      3 `october` 2007,
      19 `december` 2007,
      25 `december` 2007]


test_KoreaStockExchange :: IO ()
test_KoreaStockExchange = do
  h <- runQLE $ do
    cal <- southKoreaKRX
    holidays cal (1 `january` 2004) (31 `december` 2007) False
  assertEqual expectedHol h
  where
    expectedHol = [
      1 `january` 2004,
      21 `january` 2004,
      22 `january` 2004,
      23 `january` 2004,
      1 `march` 2004,
      5 `april` 2004,
      15 `april` 2004,
      5 `may` 2004,
      26 `may` 2004,
      27 `september` 2004,
      28 `september` 2004,
      29 `september` 2004,
      31 `december` 2004,

      8 `february` 2005,
      9 `february` 2005,
      10 `february` 2005,
      1 `march` 2005,
      5 `april` 2005,
      5 `may` 2005,
      6 `june` 2005,
      15 `august` 2005,
      19 `september` 2005,
      3 `october` 2005,
      30 `december` 2005,

      30 `january` 2006,
      1 `march` 2006,
      1 `may` 2006,
      5 `may` 2006,
      31 `may` 2006,
      6 `june` 2006,
      17 `july` 2006,
      15 `august` 2006,
      3 `october` 2006,
      5 `october` 2006,
      6 `october` 2006,
      25 `december` 2006,
      29 `december` 2006,

      1 `january` 2007,
      19 `february` 2007,
      1 `march` 2007,
      1 `may` 2007,
      24 `may` 2007,
      6 `june` 2007,
      17 `july` 2007,
      15 `august` 2007,
      24 `september` 2007,
      25 `september` 2007,
      26 `september` 2007,
      3 `october` 2007,
      19 `december` 2007,
      25 `december` 2007,
      31 `december` 2007]

test_EndOfMonth :: IO ()
test_EndOfMonth = runQLE $ do
  cal <- target
  mapM_ (\d -> do
    eom <- QuantLib.Time.Calendar.endOfMonth cal d
    b <- QuantLib.Time.Calendar.isEndOfMonth cal eom
    liftIO $ assertBool b)
    [minDate .. addGregorianMonthsClip (-2) maxDate]

test_BusinessDaysBetween :: IO ()
test_BusinessDaysBetween = runQLE $ do
  cal <- brazilSettlement
  mapM_ (\(d1, d2, e) -> do
    b <- businessDaysBetween cal d1 d2 True False
    liftIO $ assertEqual b e)
    (zip3 testDates (tail testDates) expected)
  where
    testDates = [
      1 `february` 2002,
      4 `february` 2002,
      16 `may` 2003,
      17 `december` 2003,
      17 `december` 2004,
      19 `december` 2005,
      2 `january` 2006,
      13 `march` 2006,
      15 `may` 2006,
      17 `march` 2006,
      15 `may` 2006,
      26 `july` 2006]
    expected = [
        1,
        321,
        152,
        251,
        252,
        10,
        48,
        42,
        -38,
        38,
        51]

test_BespokeCalendars :: IO ()
test_BespokeCalendars = runQLE $ do
  let testDate1 = 4 `october` 2008
      testDate2 = 5 `october` 2008
      testDate3 = 6 `october` 2008
      testDate4 = 7 `october` 2008
  a1 <- bespokeCalendar "a1" []
  a11 <- isBusinessDay a1 testDate1
  a12 <- isBusinessDay a1 testDate2
  a13 <- isBusinessDay a1 testDate3
  a14 <- isBusinessDay a1 testDate4
  liftIO $ assertBool $ a11 && a12 && a13 && a14

  a2 <- bespokeCalendar "a2" [Sunday]
  a21 <- isBusinessDay a2 testDate1
  a22 <- isBusinessDay a2 testDate2
  a23 <- isBusinessDay a2 testDate3
  a24 <- isBusinessDay a2 testDate4
  liftIO $ assertBool $ a21 && a23 && a24
  liftIO $ assertBool (not a22)

  a11' <- isBusinessDay a1 testDate1
  a12' <- isBusinessDay a1 testDate2
  a13' <- isBusinessDay a1 testDate3
  a14' <- isBusinessDay a1 testDate4
  liftIO $ assertBool $ a11' && a12' && a13' && a14'

  addHoliday a2 testDate3
  a21' <- isBusinessDay a2 testDate1
  a22' <- isBusinessDay a2 testDate2
  a23' <- isBusinessDay a2 testDate3
  a24' <- isBusinessDay a2 testDate4
  liftIO $ assertBool $ a21' && a24'
  liftIO $ assertBool $ not a22' && not a23'

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
