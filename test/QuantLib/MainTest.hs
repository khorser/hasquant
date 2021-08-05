import Test.Hspec
import Test.HUnit

import Data.Time.Calendar

import QuantLib.Date
import QuantLib.Utility
import QuantLib.Settings as Settings
import QuantLib.Period as Period

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
      --it "normalize 7d" $ do
      --  (Period.normalize (7, Days)) `shouldReturn` (1, Weeks)
      it "normalize 12m" $ do
        (Period.normalize (12, Months)) `shouldReturn` (1, Years)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
