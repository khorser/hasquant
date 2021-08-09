{-# OPTIONS_GHC -fno-warn-orphans #-}
module Main
  where

import Test.Hspec
import Test.Hspec.QuickCheck

import Test.QuickCheck
import Test.QuickCheck.Monadic as Q

import Data.Time.Calendar
import Data.List(delete)

import QuantLib.Date as Date
import QuantLib.Utility
import QuantLib.Type
import qualified QuantLib.Settings as Settings
import QuantLib.Period as Period
import QuantLib.Calendar as Calendar
import QuantLib.Currency(currency, Ccy(..))
import qualified QuantLib.Schedule as Schedule

instance Arbitrary Period.Frequency where
  arbitrary = elements $ OtherFrequency `delete` [minBound .. ]

newtype ValidDay = ValidDay {validDay::Day} deriving (Show, Eq)
newtype InvalidDay = InvalidDay Day deriving (Show, Eq)

instance Arbitrary ValidDay where
  arbitrary = do
    d <- elements [toModifiedJulianDay minDate .. toModifiedJulianDay maxDate]
    return $ ValidDay (ModifiedJulianDay d)

instance Arbitrary InvalidDay where
  arbitrary = do
    d <- elements $ [minD-500 .. minD-1] ++ [maxD+1 .. maxD+500]
    return $ InvalidDay (ModifiedJulianDay d)
    where minD = toModifiedJulianDay minDate
          maxD = toModifiedJulianDay maxDate

main :: IO ()
main = do
  putStrLn ">>>"
  putStrLn $ "QuantLib version " ++ version ++ ", Boost " ++ boostVersion
  tod <- today
  w <- weekday tod
  putStrLn $ "Today is " ++ show w

  hspec $ do

    describe "settings" $ do
      describe "evaluaton date" $ do
        it "default is today" $ do
          t1 <- Settings.evaluationDate
          today `shouldReturn` t1
        it "set" $ do
          Settings.setEvaluationDate (Just $ december 29 2012)
          Settings.evaluationDate `shouldReturn` fromGregorian 2012 12 29
        it "reset to default" $ do
          t2 <- today
          Settings.setEvaluationDate Nothing
          Settings.evaluationDate `shouldReturn` t2
        prop "randomized valid evaluation date" $ do
          monadicIO $ do
            ValidDay d1 <- pick arbitrary
            run $ (Settings.setEvaluationDate (Just d1) >> Settings.evaluationDate) `shouldReturn` d1
        prop "randomized invalid evaluation date" $ do
          monadicIO $ do
            t <- run today
            run $ Settings.setEvaluationDate (Just t)
            (InvalidDay d) <- pick arbitrary
            run $ (Settings.setEvaluationDate (Just d)) `shouldThrow` (== DateConversion d)
            run $ Settings.evaluationDate `shouldReturn` t

      describe "enforce todays historic fixings" $ do
        it "default" $ do
          Settings.enforceTodaysHistoricFixings `shouldReturn` False
        it "set to true" $ do
          save <- Settings.enforceTodaysHistoricFixings
          Settings.setEnforceTodaysHistoricFixings True
          e1 <- Settings.enforceTodaysHistoricFixings
          Settings.setEnforceTodaysHistoricFixings save
          e1 `shouldBe` True
      describe "include todays cash flows" $ do
        it "default" $ do
          Settings.includeTodaysCashFlows `shouldReturn` Nothing
        it "set to true" $ do
          save <- Settings.includeTodaysCashFlows
          Settings.setIncludeTodaysCashFlows $ Just True
          e0 <- Settings.includeTodaysCashFlows
          Settings.setIncludeTodaysCashFlows save
          e0 `shouldBe` Just True

    describe "dates" $ do
      it "min" $ do
        minDate `shouldBe` fromGregorian 1901 01 01
      it "max" $ do
        maxDate `shouldBe` fromGregorian 2199 12 31
      it "leap years" $ do
        [False, True, False] `shouldBe` map isLeap [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5]
      it "read ISO date" $ do
        Settings.keepingSettings' $ (read "2006-01-15") `shouldBe` (15 `january` 2006)
      it "known ECB dates" $ do
        Settings.keepingSettings' $ do
          knownDates <- knownECBDates
          knownDates `shouldSatisfy` (not . null)
          knownDates' <- nextECBDates (Just minDate)
          knownDates `shouldBe` knownDates'
          mapM_ (\(d, p) -> do
            isECBDate d `shouldReturn` True
            let d1 = addDays (-1) d
            isECBDate d1 `shouldReturn` False
            nextECBDate (Just d1) `shouldReturn` d
            nextECBDate (Just p) `shouldReturn` d)
            (zip knownDates (minDate:knownDates))
          let h = head knownDates
          removeECBDate h
          isECBDate h `shouldReturn` False
          addECBDate h
          isECBDate h `shouldReturn` True
      it "IMM dates (LONG)" $ do
        let immCodes = [
                "F0", "G0", "H0", "J0", "K0", "M0", "N0", "Q0", "U0", "V0", "X0", "Z0",
                "F1", "G1", "H1", "J1", "K1", "M1", "N1", "Q1", "U1", "V1", "X1", "Z1",
                "F2", "G2", "H2", "J2", "K2", "M2", "N2", "Q2", "U2", "V2", "X2", "Z2",
                "F3", "G3", "H3", "J3", "K3", "M3", "N3", "Q3", "U3", "V3", "X3", "Z3",
                "F4", "G4", "H4", "J4", "K4", "M4", "N4", "Q4", "U4", "V4", "X4", "Z4",
                "F5", "G5", "H5", "J5", "K5", "M5", "N5", "Q5", "U5", "V5", "X5", "Z5",
                "F6", "G6", "H6", "J6", "K6", "M6", "N6", "Q6", "U6", "V6", "X6", "Z6",
                "F7", "G7", "H7", "J7", "K7", "M7", "N7", "Q7", "U7", "V7", "X7", "Z7",
                "F8", "G8", "H8", "J8", "K8", "M8", "N8", "Q8", "U8", "V8", "X8", "Z8",
                "F9", "G9", "H9", "J9", "K9", "M9", "N9", "Q9", "U9", "V9", "X9", "Z9"]
        Settings.keepingSettings' $ do
          mapM_ (\d -> do
            imm <- nextIMMDate d False
            isIMMDate imm False `shouldReturn` True
            n <- nextIMMDate d True
            imm `shouldSatisfy` (> d)
            imm `shouldSatisfy` (<= n)
            code <- immCode imm
            immDate code d `shouldReturn` imm
            mapM_ (\i -> do
              immd <- immDate i d
              immd `shouldSatisfy` (>= d))
              $ take 40 immCodes)
            [minDate .. (addGregorianMonthsClip (-121) maxDate)]

    describe "frequencies and periods" $ do
      it "frequency to period" $ do
        Period.toFrequency (1, Months) `shouldReturn` Monthly
      prop "randomized frequency->period->frequency conversion" $
        \freq ->
          monadicIO $ do
            freq2 <- run $ Period.fromFrequency freq >>= Period.toFrequency
            Q.assert $ freq == freq2
      it "2w/2" $ do
        Period.divide (2, Weeks) 2 `shouldReturn` (1, Weeks)
      it "1w/1" $ do
        Period.divide (1, Weeks) 7 `shouldReturn` (1, Days)
      it "1y/4" $ do
        Period.divide (1, Years) 4 `shouldReturn` (3, Months)
      it "1y/2" $ do
        (1, Years) `Period.divide` 2 `shouldReturn` (6, Months)
      it "3d + 1d" $ do
        (3, Days) `Period.add` (1, Days) `shouldReturn` (4, Days)
      it "4d + 1w" $ do
        Period.add (4, Days) (1, Weeks) `shouldReturn` (11, Days)
      it "3m + 6m" $ do
        Period.add (3, Months) (6, Months) `shouldReturn` (9, Months)
      it "9m + 1y" $ do
        Period.add (9, Months) (1, Years) `shouldReturn` (21, Months)
      it "normalize 12m" $ do -- as of now, QuantLib normalizes only months to years
        Period.normalize (12, Months) `shouldReturn` (1, Years)

    describe "schedule" $ do
      it "truncate" $ do
        cal <- calendar $ Russia RussiaSettlement
        s <- Schedule.schedule (Just $ 20 `december` 2012) (21 `december` 2013) (1, Months) cal
          Following Unadjusted Forward
          False (Just $ 21 `december` 2012) (Just $ 21 `december` 2013)
        truncated <- Schedule.until s (15 `april` 2013)
        ds <- Schedule.dates truncated
        ds `shouldBe` [fromGregorian 2012 12 20,
               fromGregorian 2012 12 21,
               fromGregorian 2013 01 21,
               fromGregorian 2013 02 21,
               fromGregorian 2013 03 21,
               fromGregorian 2013 04 15]
      prop "generate from valid days" $ do
        \dates ->
          monadicIO $ do
            c <- run $ calendar $ Russia RussiaSettlement
            s <- run $ Schedule.fromDates (map validDay dates) c Unadjusted
            run $ Schedule.dates s `shouldReturn` map validDay dates

      it "daily" $
        Settings.keepingSettings' $ do
          let startDate = 17 `january` 2012
          cal <- calendar $ TARGET
          (Schedule.schedule (Just startDate) (addDays 7 startDate) (1, Days) cal Following Following Backward False Nothing Nothing >>= Schedule.dates)
            `shouldReturn` [17 `january` 2012, 18 `january` 2012, 19 `january` 2012, 20 `january` 2012, 23 `january` 2012, 24 `january` 2012]
      it "end date with EoM adjustment" $
        Settings.keepingSettings' $ do
          cal <- calendar $ Japan
          (Schedule.schedule (Just $ 30 `september` 2009) (15 `june` 2012) (6, Months) cal Following Following Forward True Nothing Nothing >>= Schedule.dates)
            `shouldReturn` [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 29 `june` 2012]
          (Schedule.schedule (Just $ 30 `september` 2009) (15 `june` 2012) (6, Months) cal Following Unadjusted Forward True Nothing Nothing >>= Schedule.dates)
            `shouldReturn` [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 15 `june` 2012]
      it "dates past end date with EoM adjustment" $
        Settings.keepingSettings' $ do
          cal <- calendar TARGET
          (Schedule.schedule (Just $ 28 `march` 2013) (30 `march` 2015) (1, Years) cal Unadjusted Unadjusted Forward True Nothing Nothing >>= Schedule.dates)
            `shouldReturn` [31 `march` 2013, 31 `march` 2014, 30 `march` 2015]

    describe "calendars" $ do
      it "adjust" $ do
        c <- calendar $ Russia RussiaSettlement
        a <- adjust c (fromGregorian 2012 12 22) Preceding
        a `shouldBe` (fromGregorian 2012 12 21)
      it "advance" $ do
        c <- calendar $ Russia RussiaSettlement
        a <- advance c (fromGregorian 2012 12 20) 1 Months Preceding False
        a `shouldBe` (fromGregorian 2013 01 18)
      it "modifying" $ do
        c1 <- calendar TARGET
        c2 <- calendar $ UnitedStates UnitedStatesNYSE
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
        c2 <- calendar $ UnitedKingdom UnitedKingdomExchange
        c3 <- calendar $ UnitedStates UnitedStatesNYSE
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
          [tod .. addGregorianYearsClip 1 tod]

      it "US Settlement" $ do
        cal <- calendar $ UnitedStates UnitedStatesSettlement
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
        cal <- calendar $ UnitedStates UnitedStatesGovernmentBond
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
        cal <- calendar $ UnitedStates UnitedStatesNYSE
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
          [11 `june` 2004,
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
        cal <- calendar $ Germany GermanyFrankfurtStockExchange
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
        cal <- calendar $ Germany GermanyEurex
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
        cal <- calendar $ Germany GermanyXetra
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
        cal <- calendar $ UnitedKingdom UnitedKingdomSettlement
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
        cal <- calendar $ UnitedKingdom UnitedKingdomExchange
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
        cal <- calendar $ UnitedKingdom UnitedKingdomMetals
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
        cal <- calendar $ Italy ItalyExchange
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
        cal <- calendar $ Brazil BrazilSettlement
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
        cal <- calendar $ SouthKorea SouthKoreaSettlement
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
        cal <- calendar $ SouthKorea SouthKoreaKRX
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
          [minDate .. addGregorianMonthsClip (-2) maxDate]

      it "Business days between" $ do
        cal <- calendar $ Brazil BrazilSettlement
        let testDates = [1 `february` 2002,
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
        let expected = [1,
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
            (zip3 testDates (tail testDates) expected)

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

    describe "currency" $ do
      it "GBP name" $ do
        c <- currency GBP
        (show c) `shouldBe` "British pound sterling"

    describe "day counter" $ do
      let checkCounter :: Schedule.DayCounter -> [Day] -> [(Int, TimeUnit)] -> [Double] -> IO ()
          checkCounter dc days periods expected = Settings.keepingSettings' $
            mapM_ (\d -> do
              calculated <- mapM (\p -> do
                end <- addPeriod d p
                Schedule.years dc d end Nothing Nothing)
                periods
              let diffs = zipWith (-) calculated expected
              all ((1.0e-12 >) . abs) diffs `shouldBe` True)
              days
      it "Actual/Actual" $
        Settings.keepingSettings' $
          mapM_ (\(c, s, e, rs, re, t) -> do
                    dc <- Schedule.dayCounter c
                    f <- Schedule.years dc s e rs re
                    abs(t - f) `shouldSatisfy` (<= 1.0e-10))
            [(Schedule.ActualActual Schedule.ActualActualISDA, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497724380567),
              (Schedule.ActualActual Schedule.ActualActualISMA, 1 `november` 2003, 1 `may` 2004, Just $ 1 `november` 2003, Just $ 1 `may` 2004, 0.500000000000),
              (Schedule.ActualActual Schedule.ActualActualAFB, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497267759563),
              (Schedule.ActualActual Schedule.ActualActualISDA, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
              (Schedule.ActualActual Schedule.ActualActualISMA, 1 `february` 1999, 1 `july` 1999, Just $ 1 `july` 1998, Just $ 1 `july` 1999, 0.410958904110),
              (Schedule.ActualActual Schedule.ActualActualAFB, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
              (Schedule.ActualActual Schedule.ActualActualISDA, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.001377348600),
              (Schedule.ActualActual Schedule.ActualActualISMA, 1 `july` 1999, 1 `july` 2000, Just $ 1 `july` 1999, Just $ 1 `july` 2000, 1.000000000000),
              (Schedule.ActualActual Schedule.ActualActualAFB, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.000000000000),
              (Schedule.ActualActual Schedule.ActualActualISDA, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
              (Schedule.ActualActual Schedule.ActualActualISMA, 15 `august` 2002, 15 `july` 2003, Just $ 15 `january` 2003, Just $ 15 `july` 2003, 0.915760869565),
              (Schedule.ActualActual Schedule.ActualActualAFB, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
              (Schedule.ActualActual Schedule.ActualActualISDA, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504004790778),
              (Schedule.ActualActual Schedule.ActualActualISMA, 15 `july` 2003, 15 `january` 2004, Just $ 15 `july` 2003, Just $ 15 `january` 2004, 0.500000000000),
              (Schedule.ActualActual Schedule.ActualActualAFB, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504109589041),
              (Schedule.ActualActual Schedule.ActualActualISDA, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.503892506924),
              (Schedule.ActualActual Schedule.ActualActualISMA, 30 `july` 1999, 30 `january` 2000, Just $ 30 `july` 1999, Just $ 30 `january` 2000, 0.500000000000),
              (Schedule.ActualActual Schedule.ActualActualAFB, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.504109589041),
              (Schedule.ActualActual Schedule.ActualActualISDA, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.415300546448),
              (Schedule.ActualActual Schedule.ActualActualISMA, 30 `january` 2000, 30 `june` 2000, Just $ 30 `january` 2000, Just $ 30 `july` 2000, 0.417582417582),
              (Schedule.ActualActual Schedule.ActualActualAFB, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.41530054644)]

      it "simple" $ do
        dc <- Schedule.dayCounter Schedule.Simple
        checkCounter dc
          [1 `january` 2002 .. 31 `december` 2005]
          [(3, Months), (6, Months), (1, Years)]
          [0.25, 0.5, 1.0]
    
      it "one" $ do
        dc <- Schedule.dayCounter Schedule.One
        checkCounter dc
          [1 `january` 2004 .. 31 `december` 2004]
          [(3, Months), (6, Months), (1, Years)]
          [1.0, 1.0, 1.0]

      it "Business 252" $
        Settings.keepingSettings' $ do
          let days = [1 `february` 2002,
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
                        26 `july` 2006,
                        28 `june` 2007,
                        16 `september` 2009,
                        26 `july` 2016]
          let expected = [0.0039682539683,
                        1.2738095238095,
                        0.6031746031746,
                        0.9960317460317,
                        1.0000000000000,
                        0.0396825396825,
                        0.1904761904762,
                        0.1666666666667,
                        -0.1507936507937,
                        0.1507936507937,
                        0.2023809523810,
                        0.912698412698,
                        2.214285714286,
                        6.84126984127]
          dc <- (calendar $ Brazil BrazilSettlement) >>= Schedule.dayCounter . Schedule.Business252
          fractions <- mapM (\(s, e) -> Schedule.years dc s e Nothing Nothing) (zip days (tail days))
          let diffs = zipWith (-) fractions expected
          all ((1.0e-12 >) . abs) diffs `shouldBe` True

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
