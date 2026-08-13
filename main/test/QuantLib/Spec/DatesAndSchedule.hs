{-# LANGUAGE ScopedTypeVariables #-}
module QuantLib.Spec.DatesAndSchedule (spec) where

import Prelude hiding(until, head)

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck.Monadic as Q(assert, monadicIO, run)

import Data.Time.Calendar
import Data.List.NonEmpty(fromList, head)

import QuantLib.Time.Date as Date
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule

import QuantLib.Spec.Helpers(ValidDay(..))

spec :: Spec
spec = do
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
          knownDates_ <- knownECBDates
          knownDates_ `shouldNotSatisfy` null
          let knownDates = fromList knownDates_
          knownDates'_ <- nextECBDates (Just minDate)
          knownDates'_ `shouldNotSatisfy` null
          let knownDates' = fromList knownDates'_
          knownDates `shouldBe` knownDates'
          mapM_ (\(d, p) -> do
            isECBDate d `shouldReturn` True
            let d1 = addDays (-1) d
            isECBDate d1 `shouldReturn` False
            nextECBDate (Just d1) `shouldReturn` d
            nextECBDate (Just p) `shouldReturn` d)
            (zip knownDates_ (minDate:knownDates_))
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
           ([minDate .. (addGregorianMonthsClip (-121) maxDate)] :: [Day])

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
        -- ql.Schedule(ql.Date(30, 9, 2009), ql.Date(15, 6, 2012), ql.Period(6, ql.Months), ql.Japan(), ql.Following, ql.Following, ql.DateGeneration.Forward, True).dates().dates()
          (schedule (Just $ 30 `september` 2009) (15 `june` 2012) (6, Months) cal Following Following Forward True Nothing Nothing >>= dates)
            `shouldReturn` [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 2 `april` 2012, 15 `june` 2012]
        -- ql.Schedule(ql.Date(30, 9, 2009), ql.Date(15, 6, 2012), ql.Period(6, ql.Months), ql.Japan(), ql.ModifiedFollowing, ql.ModifiedFollowing, ql.DateGeneration.Forward, True).dates()
          (schedule (Just $ 30 `september` 2009) (15 `june` 2012) (6, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing >>= dates)
            `shouldReturn` [30 `september` 2009, 31 `march` 2010, 30 `september` 2010, 31 `march` 2011, 30 `september` 2011, 30 `march` 2012, 15 `june` 2012]
      it "dates past end date with EoM adjustment" $
        Settings.keepingSettings' $ do
          cal <- calendar TARGET
          -- ql.Schedule(ql.Date(28, 3, 2013), ql.Date(30, 3, 2015), ql.Period(1, ql.Years), ql.TARGET(), ql.Unadjusted, ql.Unadjusted, ql.DateGeneration.Forward, True).dates()
          (schedule (Just $ 28 `march` 2013) (30 `march` 2015) (1, Years) cal Unadjusted Unadjusted Forward True Nothing Nothing >>= dates)
            `shouldReturn` [28 `march` 2013, 31 `march` 2014, 30 `march` 2015]
