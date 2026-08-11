{-# LANGUAGE ScopedTypeVariables, OverloadedLists #-}
module QuantLib.Spec.Calendars (spec) where

import Prelude hiding(tail)

import Test.Hspec

import Data.Time.Calendar
import Data.List.NonEmpty(NonEmpty, toList, tail)

import QuantLib.Time.Date as Date
import QuantLib.Time.Calendar as Calendar
import QuantLib.Time.Schedule(TimeUnit(..))

spec :: Day -> Spec
spec tod = do
    describe "calendars" $ do
      it "adjust" $ do
        c <- calendar RussiaSettlement
        a <- adjust c (fromGregorian 2012 12 22) Preceding
        a `shouldBe` fromGregorian 2012 12 21
      it "advance" $ do
        c <- calendar RussiaSettlement
        a <- advance c (fromGregorian 2012 12 20) (1, Months) Preceding False
        a `shouldBe` fromGregorian 2013 01 18
      it "modifying" $ do
        c1 <- calendar TARGET
        c2 <- calendar UnitedStatesNYSE
        let d1 = may 1 2004
            d2 = april 26 2004
        isHoliday c1 d1 `shouldReturn` True
        isBusinessDay c1 d2 `shouldReturn` True
        isHoliday c2 d1 `shouldReturn` True
        isBusinessDay c2 d2 `shouldReturn` True

        removeHoliday c1 d1
        addHoliday c1 d2
        isHoliday c1 d1 `shouldReturn` False
        isBusinessDay c1 d2 `shouldReturn` False

        c3 <- calendar TARGET
        isHoliday c3 d1 `shouldReturn` False
        isBusinessDay c3 d2 `shouldReturn` False

        removeHoliday c1 d2
        addHoliday c1 d1
        isHoliday c1 d1 `shouldReturn` True
        isBusinessDay c1 d2 `shouldReturn` True

      it "joint calendars" $ do
        c1 <- calendar TARGET
        c2 <- calendar UnitedKingdomExchange
        c3 <- calendar UnitedStatesNYSE
        c4 <- calendar Japan

        c12h <- calendar $ Joint2 c1 c2 JoinHolidays
        c12b <- calendar $ Joint2 c1 c2 JoinBusinessDays
        c123h <- calendar $ Joint3 c1 c2 c3 JoinHolidays
        c123b <- calendar $ Joint3 c1 c2 c3 JoinBusinessDays
        c1234h <- calendar $ Joint4 c1 c2 c3 c4 JoinHolidays
        c1234b <- calendar $ Joint4 c1 c2 c3 c4 JoinBusinessDays

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

          b1 && b2 `shouldBe` c12hb
          b1 || b2 `shouldBe` c12bb
          b1 && b2 && b3 `shouldBe` c123hb
          b1 || b2 || b3 `shouldBe` c123bb
          b1 && b2 && b3 && b4 `shouldBe` c1234hb
          b1 || b2 || b3 || b4 `shouldBe` c1234bb)
          ([tod .. addGregorianYearsClip 1 tod] :: [Day])

      it "US Settlement" $ do
        cal <- calendar UnitedStatesSettlement
        holidays cal (1 `january` 2004) (31 `december` 2005) False
          `shouldReturn` [1 `january` 2004,
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

      it "US Government Bond Market" $ do
        cal <- calendar UnitedStatesGovernmentBond
        holidays cal (1 `january` 2004) (31 `december` 2004) False
          `shouldReturn` [1 `january` 2004,
                          19 `january` 2004,
                          16 `february` 2004,
                          9 `april` 2004,
                          31 `may` 2004,
                          11 `june` 2004,
                          5 `july` 2004,
                          6 `september` 2004,
                          11 `october` 2004,
                          11 `november` 2004,
                          25 `november` 2004,
                          24 `december` 2004]

      it "US NYSE" $ do
        cal <- calendar UnitedStatesNYSE
        holidays cal (1 `january` 2004) (31 `december` 2006) False
          `shouldReturn` [1 `january` 2004,
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

        mapM_ (\d -> isHoliday cal d `shouldReturn` True)
          ([11 `june` 2004,
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
          3 `november` 1964] :: [Day])

      it "TARGET" $ do
        cal <- calendar TARGET
        holidays cal (1 `january` 1999) (31 `december` 2006) False
          `shouldReturn` [1 `january` 1999,
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

      it "Germany Frankfurt" $ do
        cal <- calendar GermanyFrankfurtStockExchange
        holidays cal (1 `january` 2003) (31 `december` 2004) False
          `shouldReturn` [1 `january` 2003,
                          18 `april` 2003,
                          21 `april` 2003,
                          1 `may` 2003,
                          24 `december` 2003,
                          25 `december` 2003,
                          26 `december` 2003,
                          1 `january` 2004,
                          9 `april` 2004,
                          12 `april` 2004,
                          24 `december` 2004]

      it "Germany EUREX" $ do
        cal <- calendar GermanyEurex
        holidays cal (1 `january` 2003) (31 `december` 2004) False
          `shouldReturn` [1 `january` 2003,
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

      it "XETRA" $ do
        cal <- calendar GermanyXetra
        holidays cal (1 `january` 2003) (31 `december` 2004) False
          `shouldReturn` [1 `january` 2003,
                            18 `april` 2003,
                            21 `april` 2003,
                            1 `may` 2003,
                            24 `december` 2003,
                            25 `december` 2003,
                            26 `december` 2003,

                            1 `january` 2004,
                            9 `april` 2004,
                            12 `april` 2004,
                            24 `december` 2004]
      it "UK Settlement" $ do
        cal <- calendar UnitedKingdomSettlement
        holidays cal (1 `january` 2004) (31 `december` 2007) False
          `shouldReturn` [1 `january` 2004,
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

      it "UK Exchange" $ do
        cal <- calendar UnitedKingdomExchange
        holidays cal (1 `january` 2004) (31 `december` 2007) False
          `shouldReturn` [1 `january` 2004,
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

      it "UK Metals" $ do
        cal <- calendar UnitedKingdomMetals
        holidays cal (1 `january` 2004) (31 `december` 2007) False
          `shouldReturn` [1 `january` 2004,
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

      it "Italy Exchange" $ do
        cal <- calendar ItalyExchange
        holidays cal (1 `january` 2002) (31 `december` 2004) False
          `shouldReturn` [1 `january` 2002,
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

      it "Brazil Settlement" $ do
        cal <- calendar BrazilSettlement
        holidays cal (1 `january` 2005) (31 `december` 2006) False
          `shouldReturn` [7 `february` 2005,
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

      it "South Korean Settlement" $ do
        cal <- calendar SouthKoreaSettlement
        holidays cal (1 `january` 2004) (31 `december` 2007) False
          `shouldReturn` [1 `january` 2004,
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

      it "Korea Stock Exchange" $ do
        cal <- calendar SouthKoreaKRX
        holidays cal (1 `january` 2004) (31 `december` 2007) False
          `shouldReturn` [1 `january` 2004,
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

      it "end of month" $ do
        cal <- calendar TARGET
        mapM_ (\d -> do
                eom <- Calendar.endOfMonth cal d
                Calendar.isEndOfMonth cal eom `shouldReturn` True)
          ([minDate .. addGregorianMonthsClip (-2) maxDate] :: [Day])

      it "Business days between" $ do
        cal <- calendar BrazilSettlement
        let testDates :: NonEmpty Day = [1 `february` 2002,
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
            expected = [1,
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
        mapM_ (\(d1, d2, e) -> do
                businessDaysBetween cal d1 d2 True False `shouldReturn` e)
            (zip3 (toList testDates) (tail testDates) expected)

      it "bespoke calendars" $ do
        let testDate1 = 4 `october` 2008
            testDate2 = 5 `october` 2008
            testDate3 = 6 `october` 2008
            testDate4 = 7 `october` 2008
        a1 <- calendar $ Bespoke "a1" []
        isBusinessDay a1 testDate1 `shouldReturn` True
        isBusinessDay a1 testDate2 `shouldReturn` True
        isBusinessDay a1 testDate3 `shouldReturn` True
        isBusinessDay a1 testDate4 `shouldReturn` True

        a2 <- calendar $ Bespoke "a2" [Date.Sunday]
        isBusinessDay a2 testDate1 `shouldReturn` True
        isBusinessDay a2 testDate2 `shouldReturn` False
        isBusinessDay a2 testDate3 `shouldReturn` True
        isBusinessDay a2 testDate4 `shouldReturn` True

        isBusinessDay a1 testDate1 `shouldReturn` True
        isBusinessDay a1 testDate2 `shouldReturn` True
        isBusinessDay a1 testDate3 `shouldReturn` True
        isBusinessDay a1 testDate4 `shouldReturn` True

        addHoliday a2 testDate3
        isBusinessDay a2 testDate1 `shouldReturn` True
        isBusinessDay a2 testDate2 `shouldReturn` False
        isBusinessDay a2 testDate3 `shouldReturn` False
        isBusinessDay a2 testDate4 `shouldReturn` True
