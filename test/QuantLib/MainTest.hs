import Test.Hspec
import Test.Hspec.QuickCheck

import Test.HUnit
import Test.QuickCheck
import Test.QuickCheck.Monadic as Q

import Data.Time.Calendar
import Control.Exception(catch)

import QuantLib.Date
import QuantLib.Utility
import QuantLib.Types
import qualified QuantLib.Settings as Settings
import QuantLib.Period as Period

instance Arbitrary Period.Frequency where
  arbitrary = elements [NoFrequency .. pred OtherFrequency]

newtype ValidDay = ValidDay {validDay::Day} deriving (Show, Eq)
newtype InvalidDay = InvalidDay {invalidDay::Day} deriving (Show, Eq)

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

setAndGetEvaluationDate :: Day -> IO Day
setAndGetEvaluationDate d = Settings.setEvaluationDate (Just d) >> Settings.evaluationDate

setAndGetEvaluationDateWithExceptions :: Day -> IO Day
setAndGetEvaluationDateWithExceptions d = do
  Settings.setEvaluationDate (Just d) `catch` ign
  Settings.evaluationDate
  where ign :: Error -> IO ()
        ign _ = return ()

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
            d1 <- pick arbitrary
            d2 <- run $ setAndGetEvaluationDate (validDay d1)
            Q.assert $ validDay d1 == d2
        prop "randomized invalid evaluation date" $ do
          monadicIO $ do
            t <- run today
            _ <- run $ Settings.setEvaluationDate (Just t)
            d <- pick arbitrary
            d2 <- run $ setAndGetEvaluationDateWithExceptions (invalidDay d)
            Q.assert $ t == d2

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
          null knownDates `shouldBe` False
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
      it "IMM dates (long running)" $ do
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
            imm > d `shouldBe` True
            imm <= n `shouldBe` True
            code <- immCode imm
            immDate code d `shouldReturn` imm
            mapM_ (\i -> do
              immd <- immDate i d
              immd >= d `shouldBe` True)
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

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
