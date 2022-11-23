{-# OPTIONS_GHC -fno-warn-orphans #-}
module Main
  where

import Prelude hiding(until)

import Test.Hspec
import Test.Hspec.QuickCheck

import Test.QuickCheck
import Test.QuickCheck.Monadic as Q

import Data.Time.Calendar
import Data.List(delete)

import Control.Arrow((&&&))

import QuantLib.Time.Date as Date
import QuantLib.Type
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar as Calendar
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Time.Schedule
import QuantLib.Math
import qualified QuantLib.InterestRate as IR
import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Quote as Quote
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure hiding(maxDate)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import QuantLib.TermStructure.Volatility(constantOptionletVolatility')
import qualified QuantLib.Instrument.Bond as B

import qualified QuantLib.Example.Bond as BondExample
import qualified QuantLib.Example.FRA as FRAExample
import qualified QuantLib.Example.Swap as SwapExample
import qualified QuantLib.Example.Repo as RepoExample
--import qualified QuantLib.Example.BermudanSwaption as BermudanSwaptionExample
--import qualified QuantLib.Example.CallableBond as CallableBondExample
--import qualified QuantLib.Example.CDS as CDSExample
--import qualified QuantLib.Example.ConvertibleBond as ConvertibleBondExample
--import qualified QuantLib.Example.EquityOption as EquityOptionExample
--import qualified QuantLib.Example.Replication as ReplicationExample

instance Arbitrary Frequency where
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

-- literal translation of close from ql/math/comparison.hpp
areClose :: Double -> Double -> Bool
areClose x1 x2 = x1 == x2
            || x1 * x2 == 0 && diff < Settings.epsilon * Settings.epsilon
            || diff <= Settings.epsilon * abs x1 && diff <= Settings.epsilon * abs x2
            where diff = abs(x1 - x2)

closePrec :: Double -> Double -> Double -> Bool
closePrec r p x = abs (x - r) < p

listClose :: (a -> Double) -> [Double] -> Double -> [a] -> Bool
listClose f x1 e x2 = (length x1 == length x2) && all (\(x, y) -> abs(x - f y) < e) (zip x1 x2)

main :: IO ()
main = do
  putStrLn ">>>"
  putStrLn $ "QuantLib version " ++ Settings.version ++ ", Boost " ++ Settings.boostVersion
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
            run $ Settings.setEvaluationDate (Just d) `shouldThrow` (== DateConversion d)
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
        Settings.keepingSettings' $ read "2006-01-15" `shouldBe` january 15 2006
      it "known ECB dates" $ do
        Settings.keepingSettings' $ do
          knownDates <- knownECBDates
          knownDates `shouldNotSatisfy` null
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
        toFrequency (1, Months) `shouldReturn` Monthly
      prop "randomized frequency->period->frequency conversion" $
        \freq ->
          monadicIO $ do
            freq2 <- run $ fromFrequency freq >>= toFrequency
            Q.assert $ freq == freq2
      it "2w/2" $ do
        divide (2, Weeks) 2 `shouldReturn` (1, Weeks)
      it "1w/1" $ do
        divide (1, Weeks) 7 `shouldReturn` (1, Days)
      it "1y/4" $ do
        divide (1, Years) 4 `shouldReturn` (3, Months)
      it "1y/2" $ do
        (1, Years) `divide` 2 `shouldReturn` (6, Months)
      it "3d + 1d" $ do
        (3, Days) `add` (1, Days) `shouldReturn` (4, Days)
      it "4d + 1w" $ do
        add (4, Days) (1, Weeks) `shouldReturn` (11, Days)
      it "3m + 6m" $ do
        add (3, Months) (6, Months) `shouldReturn` (9, Months)
      it "9m + 1y" $ do
        add (9, Months) (1, Years) `shouldReturn` (21, Months)
      it "normalize 12m" $ do -- as of now, QuantLib normalizes only months to years
        normalize (12, Months) `shouldReturn` (1, Years)

    describe "schedule" $ do
      it "truncate" $ do
        cal <- calendar RussiaSettlement
        s <- schedule (Just $ 20 `december` 2012) (21 `december` 2013) (1, Months) cal
          Following Unadjusted Forward
          False (Just $ 21 `december` 2012) (Just $ 21 `december` 2013)
        truncated <- until s (15 `april` 2013)
        ds <- dates truncated
        ds `shouldBe` [fromGregorian 2012 12 20,
               fromGregorian 2012 12 21,
               fromGregorian 2013 01 21,
               fromGregorian 2013 02 21,
               fromGregorian 2013 03 21,
               fromGregorian 2013 04 15]
      prop "generate from valid days" $ do
        \ds ->
          monadicIO $ do
            c <- run $ calendar RussiaSettlement
            s <- run $ fromDates (map validDay ds) c Unadjusted
            run $ dates s `shouldReturn` map validDay ds

      it "daily" $
        Settings.keepingSettings' $ do
          let startD = 17 `january` 2012
          cal <- calendar TARGET
          (schedule (Just startD) (addDays 7 startD) (1, Days) cal Following Following Backward False Nothing Nothing >>= dates)
            `shouldReturn` [17 `january` 2012, 18 `january` 2012, 19 `january` 2012, 20 `january` 2012, 23 `january` 2012, 24 `january` 2012]
      it "end date with EoM adjustment" $
        Settings.keepingSettings' $ do
          cal <- calendar Japan
          (schedule (Just $ 30 `september` 2009) (15 `june` 2012) (6, Months) cal Following Following Forward True Nothing Nothing >>= dates)
            `shouldReturn` [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 29 `june` 2012]
          (schedule (Just $ 30 `september` 2009) (15 `june` 2012) (6, Months) cal Following Unadjusted Forward True Nothing Nothing >>= dates)
            `shouldReturn` [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 15 `june` 2012]
      it "dates past end date with EoM adjustment" $
        Settings.keepingSettings' $ do
          cal <- calendar TARGET
          (schedule (Just $ 28 `march` 2013) (30 `march` 2015) (1, Years) cal Unadjusted Unadjusted Forward True Nothing Nothing >>= dates)
            `shouldReturn` [31 `march` 2013, 31 `march` 2014, 30 `march` 2015]

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
          [tod .. addGregorianYearsClip 1 tod]

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
          [minDate .. addGregorianMonthsClip (-2) maxDate]

      it "Business days between" $ do
        cal <- calendar BrazilSettlement
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
        show c `shouldBe` "British pound sterling"

    describe "day counter" $ do
      let checkCounter :: DayCounter -> [Day] -> [(Int, TimeUnit)] -> [Double] -> IO ()
          checkCounter dc ds periods expected = Settings.keepingSettings' $
            mapM_ (\d -> do
              calculated <- mapM (\p -> do
                end <- addPeriod d p
                years dc d end Nothing Nothing)
                periods
              let diffs = zipWith (-) calculated expected
              all ((1.0e-12 >) . abs) diffs `shouldBe` True)
              ds
      it "Actual/Actual" $
        Settings.keepingSettings' $
          mapM_ (\(c, s, e, rs, re, t) -> do
                    dc <- dayCounter c
                    f <- years dc s e rs re
                    abs(t - f) `shouldSatisfy` (<= 1.0e-10))
            [(ActualActualISDA, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497724380567),
              (ActualActualISMA, 1 `november` 2003, 1 `may` 2004, Just $ 1 `november` 2003, Just $ 1 `may` 2004, 0.500000000000),
              (ActualActualAFB, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497267759563),
              (ActualActualISDA, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
              (ActualActualISMA, 1 `february` 1999, 1 `july` 1999, Just $ 1 `july` 1998, Just $ 1 `july` 1999, 0.410958904110),
              (ActualActualAFB, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
              (ActualActualISDA, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.001377348600),
              (ActualActualISMA, 1 `july` 1999, 1 `july` 2000, Just $ 1 `july` 1999, Just $ 1 `july` 2000, 1.000000000000),
              (ActualActualAFB, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.000000000000),
              (ActualActualISDA, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
              (ActualActualISMA, 15 `august` 2002, 15 `july` 2003, Just $ 15 `january` 2003, Just $ 15 `july` 2003, 0.915760869565),
              (ActualActualAFB, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
              (ActualActualISDA, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504004790778),
              (ActualActualISMA, 15 `july` 2003, 15 `january` 2004, Just $ 15 `july` 2003, Just $ 15 `january` 2004, 0.500000000000),
              (ActualActualAFB, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504109589041),
              (ActualActualISDA, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.503892506924),
              (ActualActualISMA, 30 `july` 1999, 30 `january` 2000, Just $ 30 `july` 1999, Just $ 30 `january` 2000, 0.500000000000),
              (ActualActualAFB, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.504109589041),
              (ActualActualISDA, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.415300546448),
              (ActualActualISMA, 30 `january` 2000, 30 `june` 2000, Just $ 30 `january` 2000, Just $ 30 `july` 2000, 0.417582417582),
              (ActualActualAFB, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.41530054644)]

      it "simple" $ do
        dc <- dayCounter Simple
        checkCounter dc
          [1 `january` 2002 .. 31 `december` 2005]
          [(3, Months), (6, Months), (1, Years)]
          [0.25, 0.5, 1.0]

      it "one" $ do
        dc <- dayCounter One
        checkCounter dc
          [1 `january` 2004 .. 31 `december` 2004]
          [(3, Months), (6, Months), (1, Years)]
          [1.0, 1.0, 1.0]

      it "Business 252" $
        Settings.keepingSettings' $ do
          let ds = [1 `february` 2002,
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
              expected = [0.0039682539683,
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
          dc <- calendar BrazilSettlement >>= dayCounter . Business252
          fractions <- mapM (\(s, e) -> years dc s e Nothing Nothing) (zip ds (tail ds))
          let diffs = zipWith (-) fractions expected
          all ((1.0e-12 >) . abs) diffs `shouldBe` True

    describe "rounding" $ do
      let testData :: [(Double, Int, Double, Double, Double, Double, Double)]
          testData =
            [(  0.86313513, 5,  0.86314,  0.86314,  0.86313,  0.86314,  0.86313 ),
             (  0.86313,    5,  0.86313,  0.86313,  0.86313,  0.86313,  0.86313 ),
             ( -7.64555346, 1, -7.6,     -7.7,     -7.6,     -7.6,     -7.6     ),
             (  0.13961605, 2,  0.14,     0.14,     0.13,     0.14,     0.13    ),
             (  0.14344179, 4,  0.1434,   0.1435,   0.1434,   0.1434,   0.1434  ),
             ( -4.74315016, 2, -4.74,    -4.75,    -4.74,    -4.74,    -4.74    ),
             ( -7.82772074, 5, -7.82772, -7.82773, -7.82772, -7.82772, -7.82772 ),
             (  2.74137947, 3,  2.741,    2.742,    2.741,    2.741,    2.741   ),
             (  2.13056714, 1,  2.1,      2.2,      2.1,      2.1,      2.1     ),
             ( -1.06228670, 1, -1.1,     -1.1,     -1.0,     -1.0,     -1.1     ),
             (  8.29234094, 4,  8.2923,   8.2924,   8.2923,   8.2923,   8.2923  ),
             (  7.90185598, 2,  7.90,     7.91,     7.90,     7.90,     7.90    ),
             ( -0.26738058, 1, -0.3,     -0.3,     -0.2,     -0.2,     -0.3     ),
             (  1.78128713, 1,  1.8,      1.8,      1.7,      1.8,      1.7     ),
             (  4.23537260, 1,  4.2,      4.3,      4.2,      4.2,      4.2     ),
             (  3.64369953, 4,  3.6437,   3.6437,   3.6436,   3.6437,   3.6436  ),
             (  6.34542470, 2,  6.35,     6.35,     6.34,     6.35,     6.34    ),
             ( -0.84754962, 4, -0.8475,  -0.8476,  -0.8475,  -0.8475,  -0.8475  ),
             (  4.60998652, 1,  4.6,      4.7,      4.6,      4.6,      4.6     ),
             (  6.28794223, 3,  6.288,    6.288,    6.287,    6.288,    6.287   ),
             (  7.89428221, 2,  7.89,     7.90,     7.89,     7.89,     7.89    )]
          testRounding :: RoundingType -> Double -> Int -> Double -> IO ()
          testRounding rt x prec expected = do
            applyRounding (Rounding prec rt 5) x `shouldSatisfy` areClose expected
      it "closest" $
        mapM_ (\(x, p, x1, _x2, _x3, _x4, _x5) -> testRounding Closest x p x1) testData
      it "up" $
        mapM_ (\(x, p, _x1, x2, _x3, _x4, _x5) -> testRounding Up x p x2) testData
      it "down" $
        mapM_ (\(x, p, _x1, _x2, x3, _x4, _x5) -> testRounding Down x p x3) testData
      it "floor" $
        mapM_ (\(x, p, _x1, _x2, _x3, x4, _x5) -> testRounding Floor x p x4) testData
      it "celing" $
        mapM_ (\(x, p, _x1, _x2, _x3, _x4, x5) -> testRounding Ceiling x p x5) testData

    describe "Interest rate" $ do
      let cases :: [(Double, IR.Compounding, Frequency, Double, IR.Compounding, Frequency, Double, Int)]
          cases = [ (0.0800, IR.Compounded,        Quarterly,   1.00, IR.Continuous,            Annual, 0.0792, 4),
                    (0.1200, IR.Continuous,           Annual,   1.00, IR.Compounded,            Annual, 0.1275, 4),
                    (0.0800, IR.Compounded,        Quarterly,   1.00, IR.Compounded,            Annual, 0.0824, 4),
                    (0.0700, IR.Compounded,        Quarterly,   1.00, IR.Compounded,        Semiannual, 0.0706, 4),
                    (0.0100, IR.Compounded,           Annual,   1.00,     IR.Simple,            Annual, 0.0100, 4),
                    (0.0200,     IR.Simple,           Annual,   1.00, IR.Compounded,            Annual, 0.0200, 4),
                    (0.0300, IR.Compounded,       Semiannual,   0.50,     IR.Simple,            Annual, 0.0300, 4),
                    (0.0400,     IR.Simple,           Annual,   0.50, IR.Compounded,        Semiannual, 0.0400, 4),
                    (0.0500, IR.Compounded, EveryFourthMonth,  1.0/3,     IR.Simple,            Annual, 0.0500, 4),
                    (0.0600,     IR.Simple,           Annual,  1.0/3, IR.Compounded,  EveryFourthMonth, 0.0600, 4),
                    (0.0500, IR.Compounded,        Quarterly,   0.25,     IR.Simple,            Annual, 0.0500, 4),
                    (0.0600,     IR.Simple,           Annual,   0.25, IR.Compounded,         Quarterly, 0.0600, 4),
                    (0.0700, IR.Compounded,        Bimonthly,  1.0/6,     IR.Simple,            Annual, 0.0700, 4),
                    (0.0800,     IR.Simple,           Annual,  1.0/6, IR.Compounded,         Bimonthly, 0.0800, 4),
                    (0.0900, IR.Compounded,          Monthly, 1.0/12,     IR.Simple,            Annual, 0.0900, 4),
                    (0.1000,     IR.Simple,           Annual, 1.0/12, IR.Compounded,           Monthly, 0.1000, 4), (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.25,               IR.Simple,            Annual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.25,               IR.Simple,        Semiannual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.25,               IR.Simple,         Quarterly, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.50,               IR.Simple,            Annual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.50,               IR.Simple,        Semiannual, 0.0300, 4),
                    (0.0300, IR.SimpleThenCompounded,       Semiannual,   0.75,           IR.Compounded,        Semiannual, 0.0300, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.25, IR.SimpleThenCompounded,         Quarterly, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.25, IR.SimpleThenCompounded,        Semiannual, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.25, IR.SimpleThenCompounded,            Annual, 0.0400, 4),
                    (0.0400,           IR.Compounded,        Quarterly,   0.50, IR.SimpleThenCompounded,         Quarterly, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.50, IR.SimpleThenCompounded,        Semiannual, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.50, IR.SimpleThenCompounded,            Annual, 0.0400, 4),
                    (0.0400,           IR.Compounded,        Quarterly,   0.75, IR.SimpleThenCompounded,         Quarterly, 0.0400, 4),
                    (0.0400,           IR.Compounded,       Semiannual,   0.75, IR.SimpleThenCompounded,        Semiannual, 0.0400, 4),
                    (0.0400,               IR.Simple,       Semiannual,   0.75, IR.SimpleThenCompounded,            Annual, 0.0400, 4)]

      let testCase :: (Double, IR.Compounding, Frequency, Double, IR.Compounding, Frequency, Double, Int) -> IO ()
          testCase (r, comp, freq, t, comp2, freq2, expected, prec) = do
            d1 <- today
            dc <- dayCounter Actual360
            ir <- IR.interestRate r dc comp freq
            let d2 = addDays (truncate $ 360 * t + 0.5) d1
            compoundf <- IR.compoundFactor' ir d1 d2 d1 d2
            disc <- IR.discountFactor' ir d1 d2 d1 d2
            abs (disc - 1.0/compoundf) `shouldSatisfy` (<= 1.0e-15)
            ir2 <- IR.equivalentRate' ir dc comp freq d1 d2 d1 d2
            abs (IR.rate ir - IR.rate ir2) `shouldSatisfy` (<= 1.0e-15)

            ir3 <- IR.equivalentRate' ir dc comp2 freq2 d1 d2 d1 d2
            expectedIR <- IR.interestRate expected dc comp2 freq2

            let roundingPrecision = Rounding prec Closest 5
                r3 = applyRounding roundingPrecision (IR.rate ir3)
            abs(r3 - IR.rate expectedIR) `shouldSatisfy` (<= 1.0e-17)

            ir3' <- IR.equivalentRate' ir dc comp2 freq2 d1 d2 d1 d2
            let r3' = applyRounding roundingPrecision (IR.rate ir3')
            abs(r3' - expected) `shouldSatisfy` (<= 1.0e-17)

      it "bulk test for conversions" $ do
        Settings.keepingSettings' $ mapM_ testCase cases

    describe "cash flow leg" $ do
      let checkInclusion :: CF.Leg -> Int -> [(Int, Bool)] -> IO ()
          checkInclusion l n x = do
            td <- Settings.evaluationDate
            mapM_ (\(ds, expected) -> do
              cfs <- CF.cashFlows l Nothing (Just $ addDays (fromIntegral ds) td)
              let (_, _, o) = cfs !! n
              expected `shouldNotBe` o) x

          checkNPV :: CF.Leg -> IR.InterestRate -> Bool -> Double -> IO ()
          checkNPV l r includeRef expected = do
            td <- Settings.evaluationDate
            v <- CF.npvFromYield' l r includeRef (Just td) (Just td)
            abs(v - expected) `shouldSatisfy` (<= 1.0e-6)

      it "misc variants of settings" $
        Settings.keepingSettings' $ do
          let cases12 l = do
                checkInclusion l 0 [(0, False), (1, False)]
                checkInclusion l 1 [(0, True), (1, False), (2, False)]
                checkInclusion l 2 [(1, True), (2, False), (3, False)]

              cases34 l = do
                checkInclusion l 0 [(0, True), (1, False)]
                checkInclusion l 1 [(0, True), (1, True), (2, False)]
                checkInclusion l 2 [(1, True), (2, True), (3, False)]
          td <- today
          Settings.setEvaluationDate (Just td)
          l <- CF.leg $ zip [td .. addDays 2 td] (repeat 1.0)

          Settings.setIncludeReferenceDateEvents False
          Settings.setIncludeTodaysCashFlows Nothing
          cases12 l

          -- 2)
          Settings.setIncludeReferenceDateEvents False
          Settings.setIncludeTodaysCashFlows (Just False)
          cases12 l
          -- 3)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows Nothing
          cases34 l

          -- 4)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows $ Just True
          cases34 l

          -- 5)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows $ Just False
          checkInclusion l 0 [(0, False), (1, False)]
          checkInclusion l 1 [(0, True), (1, True), (2, False)]
          checkInclusion l 2 [(1, True), (2, True), (3, False)]

          -- 5)
          Settings.setIncludeReferenceDateEvents True
          Settings.setIncludeTodaysCashFlows $ Just False
          checkInclusion l 0 [(0, False), (1, False)]
          checkInclusion l 1 [(0, True), (1, True), (2, False)]
          checkInclusion l 2 [(1, True), (2, True), (3, False)]

          dc <- dayCounter Actual365FixedStandard
          noDisc <- IR.interestRate 0.0 dc IR.Continuous Annual

          Settings.setIncludeTodaysCashFlows Nothing
          checkNPV l noDisc False 2.0
          checkNPV l noDisc True 3.0

          Settings.setIncludeTodaysCashFlows $ Just False
          checkNPV l noDisc False 2.0
          checkNPV l noDisc True 2.0

      it "fixed rate leg as of default settlement date" $ do
        td <- Settings.evaluationDate
        cal <- calendar TARGET
        sch <- schedule (Just $ addGregorianMonthsClip (-2) td) (addGregorianMonthsClip 4 td) (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
        dc <- dayCounter Actual360
        cpn <- IR.interestRate 0.03 dc IR.Simple Annual
        l <- CF.fixedRateLeg sch [100.0] [cpn] Following dc cal
        accP <- CF.accruedPeriod l False Nothing
        accP `shouldSatisfy` (/= 0)
        accD <- CF.accruedDays l False Nothing
        accD `shouldSatisfy` (/= 0)
        accA <- CF.accruedAmount l False Nothing
        accA `shouldSatisfy` (/= 0)

      it "empty leg start" $ do
        let cPlusPlusEx (CPlusPlusException m) = not $ null m
            cPlusPlusEx _ = False
        (CF.leg [] >>= CF.startDate) `shouldThrow` cPlusPlusEx

      it "single leg today" $ do
        (CF.leg [(tod, 100)] >>= CF.startDate) `shouldReturn` tod

      it "two legs unsorted" $ do
        (CF.leg [(tod, 100), (addDays (-10) tod, -1000)] >>= CF.startDate) `shouldReturn` addDays (-10) tod

      it "three legs sorted" $ do
        (CF.leg [(tod, 100), (addDays (-10) tod, 1000), (addDays 10 tod, -2000)] >>= CF.startDate) `shouldReturn` addDays (-10) tod

      prop "random single let start date" $
        \(a, ValidDay d) -> monadicIO $ do
          run $ (CF.leg [(d, a)] >>= CF.startDate) `shouldReturn` d

      prop "start date should be minimal" $
        \flows ->
          not (null flows)
            ==> monadicIO $ do
              let (d, a) = unzip (flows :: [(ValidDay, Double)])
                  ds = map validDay d
                  f = zip ds a
              run $ (CF.leg f >>= CF.startDate) `shouldReturn` minimum ds

      it "check for segfaulting regression with dynamic cast of coupon in Black pricer" $
        Settings.keepingSettings' $ do
          Settings.setEvaluationDate (Just $ 7 `april` 2010)
          cal <- calendar TARGET
          dc <- dayCounter Actual365FixedStandard
          q <- Quote.simpleQuote 0.04875825 >>= Quote.asQuote
          ts <- flatForward (9 `april` 2010) q dc IR.Continuous Annual
          v <- Quote.simpleQuote 0.10
          vol <- constantOptionletVolatility' 2 cal ModifiedFollowing v dc
          let p = (3, Months)
          index3m <- iborIndex (UsdLibor p) (Just ts)
          pricer <- CF.blackIborCouponPricer vol
          sch <- schedule (Just $ 20 `september` 2013) (20 `december` 2013) p cal Following Following Backward False Nothing Nothing
          cpns <- CF.iborLeg sch index3m [100] dc Following [2] [] [0.000115] [] [] False False
          CF.setCouponPricer cpns pricer
          ret <- CF.nextCashFlowAmount cpns True Nothing
          ret `shouldSatisfy` const True

    describe "Quote value" $ do
      prop "quote value" $ 
        \val ->
          val > 0
            ==> monadicIO $ do run $ (Quote.simpleQuote val >>= \q -> Quote.value q) `shouldReturn` val

    describe "yield term structure" $ do
      let setup :: IO (Calendar, Word, YieldTermStructure)
          setup = do
            let settlementDays = 2
                depositData = [
                  ( 1, Months, 4.581),
                  ( 2, Months, 4.573 ),
                  ( 3, Months, 4.557 ),
                  ( 6, Months, 4.496 ),
                  ( 9, Months, 4.490 )]
                swapData = [
                  ( 1, Years, 4.54 ),
                  ( 5, Years, 4.99 ),
                  (10, Years, 5.47 ),
                  (20, Years, 5.89 ),
                  (30, Years, 5.96 )]
            cal <- calendar TARGET
            d <- today
            today' <- adjust cal d Following
            Settings.setEvaluationDate (Just today')
            settlement <- advance cal today' (fromIntegral settlementDays, Days) Following False
            actual360dc <- dayCounter Actual360
            deposits <- mapM
              (\(n, u, r) -> do
                q <- Quote.simpleQuote (r/100)
                depositRateHelper q (n, u) settlementDays cal ModifiedFollowing True actual360dc)
              depositData
            ccy <- currency EUR
            thirty360dc <- dayCounter Thirty360BondBasis
            index <- iborIndex (Ibor "dummy" (6, Months) settlementDays ccy cal ModifiedFollowing False actual360dc) Nothing
            swaps <- mapM
              (\(n, u, r) -> do
                q <- Quote.simpleQuote (r/100)
                swapRateHelper' q (n, u) cal Annual Unadjusted thirty360dc index Nothing (0, Days) Nothing >>= asRateHelper)
              swapData

            ts <- piecewiseYieldCurve settlement (deposits ++ swaps) actual360dc [] Discount LogLinear
            return (cal, settlementDays, ts)
      it "referenceChange" $ do
        let ds = [10, 30, 60, 120, 360, 720]
        (_calendar, settlementDays, _ts) <- setup
        flatRate <- Quote.simpleQuote 0.03
        cal <- calendar Null
        actual360dc <- dayCounter Actual360
        ts <- flatForward' settlementDays cal flatRate actual360dc IR.Continuous Annual
        td <- Settings.evaluationDate

        expected <- mapM (\d -> discount' ts (addDays d td) False) ds
        Settings.setEvaluationDate (Just $ addDays 30 td)
        calculated <- mapM (\d -> discount' ts (addDays (30+d) td) False) ds

        mapM_ (\(x1, x2) -> x1 `shouldSatisfy` areClose x2) (zip expected calculated)

      it "implied" $
        Settings.keepingSettings' $ do
          (cal, settlementDays, ts) <- setup
          td <- Settings.evaluationDate
          let newToday = addGregorianYearsClip 3 td
          newSettlement <- advance cal newToday (fromIntegral settlementDays, Days) Following False
          let testDate = addGregorianYearsClip 5 newSettlement
          implied <- impliedTermStructure ts newSettlement
          baseDiscount <- discount' ts newSettlement False
          dsc <- discount' ts testDate False
          impliedDiscount <- discount' implied testDate False

          (dsc - baseDiscount * impliedDiscount) `shouldSatisfy` (<= 1.0e-10)

      it "fwd spreaded" $
        Settings.keepingSettings' $ do
          (_calendar, _settlementDays, ts) <- setup
          me <- Quote.simpleQuote 0.01
          val <- Quote.value me
          spreaded <- forwardSpreadedTermStructure ts me
          refDate <- asTermStructure ts >>= referenceDate
          let testDate = addGregorianYearsClip 5 refDate
          actual360dc <- dayCounter Actual360
          forward <- IR.rate <$> forwardRate' ts testDate testDate actual360dc IR.Continuous NoFrequency False
          spreadedForward <- IR.rate <$> forwardRate' spreaded testDate testDate actual360dc IR.Continuous NoFrequency False

          (forward - (spreadedForward - val)) `shouldSatisfy` (<= 1.0e-10)
      it "z-spreaded" $
        Settings.keepingSettings' $ do
          (_calendar, _settlementDays, ts) <- setup
          q <- Quote.simpleQuote 0.01
          val <- Quote.value q
          actual360dc <- dayCounter Actual360
          spreaded <- zeroSpreadedTermStructure ts q IR.Continuous NoFrequency actual360dc
          refDate <- asTermStructure ts >>= referenceDate
          let testDate = addGregorianYearsClip 5 refDate
          zero <- IR.rate <$> zeroRate' ts testDate actual360dc IR.Continuous NoFrequency False
          spreadedZero <- IR.rate <$> zeroRate' spreaded testDate actual360dc IR.Continuous NoFrequency False

          (zero - (spreadedZero - val)) `shouldSatisfy` (<= 1.0e-10)
    describe "Bond Example" $
      it "check values"  $ do
        r <- Settings.keepingSettings' BondExample.run
        let (fixnpv, znpv, fnpv) = BondExample.npvR r
            (fixy, zy, fy) = BondExample.yieldR r
            (fixclean, zclean, fclean) = BondExample.cleanPriceR r
            (fixdirty, zdirty, fdirty) = BondExample.dirtyPriceR r
            (fixaccrual, zaccrual, faccrual) = BondExample.accruedAmountR r
            (fixprev, fprev) = BondExample.previousCoupon r
            (fixnext, fnext) = BondExample.nextCoupon r
            (fixnextD, znextD, fnextD) = BondExample.nextCouponDate r
            cleanFromYield = BondExample.cleanPriceFromYieldR r
            yieldFromClean = BondExample.yieldFromCleanPriceR r
            tradable = BondExample.tradable r

        fixnpv `shouldSatisfy` closePrec 107.6682891 1e-7
        znpv `shouldSatisfy` closePrec 100.9221782 1e-7
        fnpv `shouldSatisfy` closePrec 102.3593146 1e-7
        fixy `shouldSatisfy` closePrec 0.0364756 1e-7
        zy `shouldSatisfy` closePrec 0.0300006 1e-7
        fy `shouldSatisfy` closePrec 0.0220096 1e-7

        fixclean `shouldSatisfy` closePrec 106.1275283 1e-7
        zclean `shouldSatisfy` closePrec 100.9221782 1e-7
        fclean `shouldSatisfy` closePrec 101.7972017 1e-7
        fixdirty `shouldSatisfy` closePrec 107.6682891 1e-7
        zdirty `shouldSatisfy` closePrec 100.9221782 1e-7
        fdirty `shouldSatisfy` closePrec 102.3593146 1e-7
        fixaccrual `shouldSatisfy` closePrec 1.5407609 1e-7
        zaccrual `shouldSatisfy` closePrec 0.0 1e-7
        faccrual `shouldSatisfy` closePrec 0.5621129 1e-7
        fixprev `shouldSatisfy` closePrec 0.045 1e-7
        fprev `shouldSatisfy` closePrec 0.0288625 1e-7
        fixnext `shouldSatisfy` closePrec 0.045 1e-7
        fnext `shouldSatisfy` closePrec 0.0342984 1e-7

        fixnextD `shouldBe` fromGregorian 2008 11 17
        znextD `shouldBe` fromGregorian 2013 08 15
        fnextD `shouldBe` fromGregorian 2008 10 21
        cleanFromYield `shouldSatisfy` closePrec 101.79720 1e-5 -- because of difference in QL versions?
        yieldFromClean `shouldSatisfy` closePrec 0.0220096 1e-7
        tradable `shouldBe` (True, True, False)

    describe "some more bonds" $
      it "some statics" $ do
        c <- calendar UnitedKingdomSettlement
        l <- CF.leg [(fromGregorian 2013 1 1, 1000)]
        b <- B.bond' 2 c 1000 (Just (fromGregorian 2013 1 1)) (Just (fromGregorian 2012 1 1)) l
        B.maturityDate b `shouldBe` Just (fromGregorian 2013 1 1)

    describe "FRA Example" $
      it "check values" $ do
        (FRAExample.Result it1 it2) <- Settings.keepingSettings' FRAExample.run
        let
          fwdRates1   = [3.0e-2, 3.1e-2, 3.2e-2, 3.3e-2, 3.4e-2]
          zRates1     = [3.00399e-2, 3.06805e-2, 3.11347e-2, 3.19277e-2, 3.26419e-2]
        it1 `shouldSatisfy` listClose FRAExample.fwdRateR fwdRates1 1.0e-5
        it1 `shouldSatisfy` listClose FRAExample.zRateR zRates1 1.0e-5
        it1 `shouldSatisfy` listClose FRAExample.npvR (replicate (length it1) 0.0) 1.0e-5
        let
          fwdRates2   = [4.0e-2, 4.1e-2, 4.2e-2, 4.3e-2, 4.4e-2]
          zRates2     = [4.00710e-2, 4.07408e-2, 4.12277e-2, 4.21174e-2, 4.29299e-2]
          npvs2       = [0.25208, 0.25121, 0.25567, 0.24751, 0.24215]
        it2 `shouldSatisfy` listClose FRAExample.fwdRateR fwdRates2 1.0e-5
        it2 `shouldSatisfy` listClose FRAExample.zRateR zRates2 1.0e-5
        it2 `shouldSatisfy` listClose FRAExample.npvR npvs2 1.0e-5

    describe "Swap example" $
      it "check values" $ do
        (SwapExample.Result it1 it2) <- Settings.keepingSettings' SwapExample.run
        let
          spotNpvs1         = [19065.88091, 19076.13635, 19056.02274]
          spotFairSpreads1  = [-4.19298e-3, -4.19258e-3, -4.19271e-3]
          spotFairRates1    = [4.43e-2, 4.43e-2, 4.43e-2]
          fwdNpvs1          = [40049.45742, 40092.78967, 37238.92028]
          fwdFairSpreads1   = [-9.23115e-3, -9.23433e-3, -8.58372e-3]
          fwdFairRates1     = [4.94794e-2, 4.94846e-2, 4.88132e-2]
          (spots1, fwds1)   = unzip $ map (SwapExample.spotSwap &&& SwapExample.forwardSwap) it1
        spots1 `shouldSatisfy` listClose SwapExample.spotNpvR spotNpvs1 1.0e-5
        spots1 `shouldSatisfy` listClose SwapExample.spotFairSpreadR spotFairSpreads1 1.0e-5
        spots1 `shouldSatisfy` listClose SwapExample.spotFairRateR spotFairRates1 1.0e-5
        fwds1  `shouldSatisfy` listClose SwapExample.spotNpvR fwdNpvs1 1.0e-5
        fwds1  `shouldSatisfy` listClose SwapExample.spotFairSpreadR fwdFairSpreads1 1.0e-5
        fwds1  `shouldSatisfy` listClose SwapExample.spotFairRateR fwdFairRates1 1.0e-5
        let
          spotNpvs2         = [26539.06205, 26553.33709, 26525.34]
          spotFairSpreads2  = [-5.84826e-3, -5.84770e-3, -5.84788e-3]
          spotFairRates2    = [4.6e-2, 4.6e-2, 4.6e-2]
          fwdNpvs2          = [45736.03965, 45782.39565, 42922.59585]
          fwdFairSpreads2   = [-1.05779e-2, -1.05808e-2, -9.92761e-3]
          fwdFairRates2     = [5.08660e-2, 5.08713e-2, 5.01964e-2]
          (spots2, fwds2)   = unzip $ map (SwapExample.spotSwap &&& SwapExample.forwardSwap) it2
        spots2 `shouldSatisfy` listClose SwapExample.spotNpvR spotNpvs2 1.0e-5
        spots2 `shouldSatisfy` listClose SwapExample.spotFairSpreadR spotFairSpreads2 1.0e-5
        spots2 `shouldSatisfy` listClose SwapExample.spotFairRateR spotFairRates2 1.0e-5
        fwds2  `shouldSatisfy` listClose SwapExample.spotNpvR fwdNpvs2 1.0e-5
        fwds2  `shouldSatisfy` listClose SwapExample.spotFairSpreadR fwdFairSpreads2 1.0e-5
        fwds2  `shouldSatisfy` listClose SwapExample.spotFairRateR fwdFairRates2 1.0e-5

    describe "Repo example" $
      it "check values" $ do 
        r <- Settings.keepingSettings' RepoExample.run
        RepoExample.cleanPriceR r `shouldSatisfy` closePrec 89.9769362 1e-7
        RepoExample.dirtyPriceR r `shouldSatisfy` closePrec 93.2880473 1e-7
        RepoExample.accruedAmountSettlement r `shouldSatisfy` closePrec 3.3111111 1e-7
        RepoExample.accruedAmountDelivery r `shouldSatisfy` closePrec 3.3333333 1e-7
        RepoExample.spotIncomeR r `shouldSatisfy` closePrec 3.9834025 1e-7
        RepoExample.fwdIncomeR r `shouldSatisfy` closePrec 4.0846473 1e-7
        RepoExample.npvR r `shouldSatisfy` closePrec (-0.00002806598) 1e-11
        RepoExample.cleanForwardPriceR r `shouldSatisfy` closePrec 88.2411379 1e-7
        RepoExample.forwardPriceR r `shouldSatisfy` closePrec 91.5744712 1e-7
        RepoExample.impliedYieldR r `shouldSatisfy` closePrec 0.050000633 1e-9
        RepoExample.zeroRateR r `shouldSatisfy` closePrec 0.05 1e-7

    --describe "Replication example" $
    --  it "check values" $ do
    --    (ReplicationExample.Result npvInit npvOut npvIn) <- Settings.keepingSettings' ReplicationExample.run
    --    npvInit `shouldSatisfy` listClose id [4.260726, 4.322358, 4.295464, 4.280909] 1.0e-6
    --    npvOut  `shouldSatisfy` listClose id [2.513058, 2.539365, 2.528362, 2.522105] 1.0e-6
    --    npvIn   `shouldSatisfy` listClose id [5.739125, 5.851239, 5.799867, 5.773678] 1.0e-6

    --describe "CDS example" $
    --  it "check values" $ do
    --    (CDSExample.Result _probs _fairSpread _npv _defNpv _cpnNpv) <- Settings.keepingSettings' CDSExample.run
    --    -- FIXME probs `shouldSatisfy` listClose id [97.040061, 94.175780] 1.0e-6
    --    -- FIXME fairSpread `shouldSatisfy` listClose id [1.500000, 1.500000, 1.500000, 1.500000] 1.0e-6
    --    -- FIXME npv `shouldSatisfy` listClose id [-7.18501e-11, -1.52795e-10, -2.05728e-09, -6.25732e-10] 1.0e-9
    --    -- FIXME defNpv `shouldSatisfy` listClose id [-5218.16, -8882.83, -16142.9, -30195.6] 1.0e-1
    --    -- FIXME cpnNpv `shouldSatisfy` listClose id [5218.16, 8882.83, 16142.9, 30195.6] 1.0e-1

    -- describe "Convertible bond example" $
    --   it "check values" $ do
    --     (ConvertibleBondExample.Result jr crr ad tr ti lr j) <- Settings.keepingSettings' ConvertibleBondExample.run
    --     jr `shouldSatisfy` listClose id [105.690844, 108.141608] 1.0e-6
    --     crr `shouldSatisfy` listClose id [105.698533, 108.166210] 1.0e-6
    --     ad `shouldSatisfy` listClose id [105.626388, 108.085800] 1.0e-6
    --     tr `shouldSatisfy` listClose id [105.699036, 108.166649] 1.0e-6
    --     ti `shouldSatisfy` listClose id [105.712848, 108.174293] 1.0e-6
    --     lr `shouldSatisfy` listClose id [105.668326, 108.155630] 1.0e-6
    --     j `shouldSatisfy` listClose id [105.668327, 108.155630] 1.0e-6

    --describe "Callable bond example" $
    --  it "check values" $ do
    --    (CallableBondExample.Result _ps _ys) <- Settings.keepingSettings' CallableBondExample.run
    --    pending
    --    -- FIXME ps `shouldSatisfy` listClose id [96.47, 95.64, 92.31, 87.08, 77.34] 1.0e-2
    --    -- FIXME ys `shouldSatisfy` listClose id [5.48, 5.67, 6.49, 7.85, 10.64] 1.0e-2

    --describe "Bermudan swaption example (LONG)" $
    --  it "check values" $ do
    --    (BermudanSwaptionExample.Result g2v g2p hwv hwp hw2v hw2p bkv bkp npvA npvO npvI) <- Settings.keepingSettings' BermudanSwaptionExample.run
    --    g2v `shouldSatisfy` listClose id [10.04549, 10.51234, 10.70500, 10.83817, 10.94387] 1.0e-5
    --    hwv `shouldSatisfy` listClose id [10.62037, 10.62959, 10.63414, 10.64428, 10.66132] 1.0e-5
    --    hw2v `shouldSatisfy` listClose id [10.31185, 10.54619, 10.66914, 10.74020, 10.79725] 1.0e-5
    --    bkv `shouldSatisfy` listClose id [10.32593, 10.56575, 10.67858, 10.73678, 10.77792] 1.0e-5
    --    g2p `shouldSatisfy` listClose id [0.050056, 0.0094424, 0.050053, 0.0094424, -0.763] 1.0e-4 -- NB tolerance
    --    hwp `shouldSatisfy` listClose id [0.046414, 0.0058693] 1.0e-5
    --    hw2p `shouldSatisfy` listClose id [0.055229, 0.0061063] 1.0e-5
    --    bkp `shouldSatisfy` listClose id [0.043389, 0.12075] 1.0e-5
    --    npvA `shouldSatisfy` listClose id [14.11, 14.113, 12.904, 12.91, 13.158, 13.157, 13.002] 1.0e-3
    --    npvO `shouldSatisfy` listClose id [3.194, 3.1808, 2.4921, 2.4596, 2.615, 2.5829, 3.2751] 1.0e-3
    --    npvI `shouldSatisfy` listClose id [42.609, 42.705, 42.253, 42.215, 42.364, 42.311, 41.825] 1.0e-3

    --describe "Equity option example (LONG)" $
    --  it "check values" $ do
    --    (EquityOptionExample.Result analyticEuro analyticHeston bates baw bjs bin int fd _mc) <- Settings.keepingSettings' EquityOptionExample.run
    --    analyticEuro   `shouldSatisfy` listClose id [3.844308] 1.0e-6
    --    analyticHeston `shouldSatisfy` listClose id [3.844306] 1.0e-6
    --    bates          `shouldSatisfy` listClose id [3.844306] 1.0e-6
    --    baw            `shouldSatisfy` listClose id [4.459628] 1.0e-6
    --    bjs            `shouldSatisfy` listClose id [4.453064] 1.0e-6
    --    int            `shouldSatisfy` listClose id [3.844309] 1.0e-6
    --    fd `shouldSatisfy` listClose id [3.844342, 4.360807, 4.486118] 1.0e-6
    --    -- FIXME mc `shouldSatisfy` listClose id [3.834522, 3.844613, 4.481675] 1.0e-6
    --    (head bin) `shouldSatisfy` listClose id [3.844132, 4.361174, 4.486552] 1.0e-6
    --    (bin!!1)   `shouldSatisfy` listClose id [3.843504, 4.360861, 4.486415] 1.0e-6
    --    (bin!!2)   `shouldSatisfy` listClose id [3.836911, 4.354455, 4.480097] 1.0e-6
    --    (bin!!3)   `shouldSatisfy` listClose id [3.843557, 4.360909, 4.486461] 1.0e-6
    --    (bin!!4)   `shouldSatisfy` listClose id [3.844171, 4.361176, 4.486413] 1.0e-6
    --    (bin!!5)   `shouldSatisfy` listClose id [3.844308, 4.360713, 4.486076] 1.0e-6
    --    (bin!!6)   `shouldSatisfy` listClose id [3.844308, 4.360713, 4.486076] 1.0e-6

{-
test_FixedBondWithSchedule :: IO ()
test_FixedBondWithSchedule = do
  c <- Calendar.russia
  s <- Schedule.schedule
    (Just $ fromGregorian 2012 12 20)
    (fromGregorian 2013 12 21)
    (1, Unit.Months)
    c
    BusinessDayConvention.Following
    BusinessDayConvention.Unadjusted
    DateGenerationRule.Forward
    False
    (Just $ fromGregorian 2012 12 21)
    (Just $ fromGregorian 2013 12 21)
  cnt <- DayCounter.actual365Fixed
  void $ Bond.fixedRateBondFromSchedule
        1
        100
        s
        [3]
        cnt
        BusinessDayConvention.Following
        100
        (Just $ fromGregorian 2012 10 11)
        c
  assertEqual True True

test_FixedBondWithCalendars :: IO ()
test_FixedBondWithCalendars = do
  c <- Calendar.russia
  cnt <- DayCounter.actual365Fixed
  _ <- Bond.fixedRateBond
    1
    c
    100
    (fromGregorian 2012 12 20)
    (fromGregorian 2013 12 21)
    (1, Unit.Months)
    [0.12]
    cnt
    BusinessDayConvention.Following
    BusinessDayConvention.Unadjusted
    100
    (Just $ fromGregorian 2012 10 01)
    Nothing
    DateGenerationRule.Forward
    False
    c
  assertEqual True True

test_FixedBond :: IO ()
test_FixedBond = do
  dc <- DayCounter.actual365Fixed
  r1 <- InterestRate.interestRate 0.12 dc Compounding.Simple Frequency.Annual
  r2 <- InterestRate.interestRate 0.125 dc Compounding.Simple Frequency.Monthly
  cal <- Calendar.russia
  s <- Schedule.schedule
    (Just (fromGregorian 2012 12 20))
    (fromGregorian 2013 12 21)
    (6, Unit.Months)
    cal
    BusinessDayConvention.Following
    BusinessDayConvention.Unadjusted
    DateGenerationRule.Forward
    False
    (Just (fromGregorian 2012 12 21))
    (Just (fromGregorian 2013 12 21))
  _ <- Bond.fixedRateBond
          3
          100
          s
          [r1, r2]
          BusinessDayConvention.Preceding
          100
          (Just (fromGregorian 2012 12 21))
          cal
  assertEqual True True
-}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
