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
  arbitrary = elements [NoFrequency .. (pred OtherFrequency)]

newtype ValidDay = ValidDay {validDay::Day} deriving (Show, Eq)
newtype InvalidDay = InvalidDay {invalidDay::Day} deriving (Show, Eq)

instance Arbitrary ValidDay where
  arbitrary = do
    d <- elements [(toModifiedJulianDay minDate) .. (toModifiedJulianDay maxDate)]
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
          Settings.evaluationDate `shouldReturn` (fromGregorian 2012 12 29)
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
          e0 `shouldBe` (Just True)

    describe "dates" $ do
      it "min" $ do
        minDate `shouldBe` (fromGregorian 1901 01 01)
      it "max" $ do
        maxDate `shouldBe` (fromGregorian 2199 12 31)
      it "leap years" $ do
        [False, True, False] `shouldBe` (map isLeap [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5])

    describe "frequencies and periods" $ do
      it "frequency to period" $ do
        (Period.toFrequency (1, Months)) `shouldReturn` Monthly
      prop "randomized frequency->period->frequency conversion" $
        \freq ->
          monadicIO $ do
            freq2 <- run $ (Period.fromFrequency freq >>= Period.toFrequency)
            Q.assert $ freq == freq2
      it "2w/2" $ do
        (Period.divide (2, Weeks) 2) `shouldReturn` (1, Weeks)
      it "1w/1" $ do
        (Period.divide (1, Weeks) 7) `shouldReturn` (1, Days)
      it "1y/4" $ do
        (Period.divide (1, Years) 4) `shouldReturn` (3, Months)
      it "1y/2" $ do
        (Period.divide (1, Years) 2) `shouldReturn` (6, Months)
      it "3d + 1d" $ do
        (Period.add (3, Days) (1, Days)) `shouldReturn` (4, Days)
      it "4d + 1w" $ do
        (Period.add (4, Days) (1, Weeks)) `shouldReturn` (11, Days)
      it "3m + 6m" $ do
        (Period.add (3, Months) (6, Months)) `shouldReturn` (9, Months)
      it "9m + 1y" $ do
        (Period.add (9, Months) (1, Years)) `shouldReturn` (21, Months)
      it "normalize 12m" $ do -- as of now, QuantLib normalizes only months to years
        (Period.normalize (12, Months)) `shouldReturn` (1, Years)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
