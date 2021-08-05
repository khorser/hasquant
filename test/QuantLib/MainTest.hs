import Test.Hspec
import Test.HUnit

import Data.Time.Calendar

import QuantLib.Date
import QuantLib.Utility
import QuantLib.Settings

import Control.Applicative((<$>))

main :: IO ()
main = do
  putStrLn ">>>"
  putStrLn $ "QuantLib version " ++ version ++ ", Boost " ++ boostVersion
  tod <- today
  w <- weekday tod
  putStrLn $ "Today is " ++ show w
  hspec $ do
    describe "evaluaton date" $ do
      it "default is today" $ do
        t1 <- evaluationDate
        t2 <- today
        t1 @?= t2
      it "set" $ do
        setEvaluationDate (Just $ december 29 2012)
        t0 <- evaluationDate
        t0 `shouldBe` (fromGregorian 2012 12 29)
      it "reset to default" $ do
        t2 <- today
        setEvaluationDate Nothing
        t1 <- evaluationDate
        t1 `shouldBe` t2

    describe "settings" $ do
      it "default enforce todays historic fixings" $ do
        e1 <- enforceTodaysHistoricFixings
        e1 `shouldBe` False
      it "set enforce todays historic fixings to true" $ do
        save <- enforceTodaysHistoricFixings
        setEnforceTodaysHistoricFixings True
        e1 <- enforceTodaysHistoricFixings
        setEnforceTodaysHistoricFixings save
        e1 `shouldBe` True
      it "default include todays cash flows" $ do
        e <- includeTodaysCashFlows
        e `shouldBe` Nothing
      it "set include todays cash flows" $ do
        save <- includeTodaysCashFlows
        setIncludeTodaysCashFlows $ Just True
        e0 <- includeTodaysCashFlows
        setIncludeTodaysCashFlows Nothing
        e0 `shouldBe` (Just True)

    describe "dates" $ do
      it "min date" $ do
        minDate `shouldBe` (fromGregorian 1901 01 01)
      it "max date" $ do
        maxDate `shouldBe` (fromGregorian 2199 12 31)
      it "leap years" $ do
        [False, True, False] `shouldBe` (map isLeap [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5])

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
