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
    describe "settings" $ do
      describe "evaluaton date" $ do
        it "default is today" $ do
          t1 <- evaluationDate
          today `shouldReturn` t1
        it "set" $ do
          setEvaluationDate (Just $ december 29 2012)
          evaluationDate `shouldReturn` (fromGregorian 2012 12 29)
        it "reset to default" $ do
          t2 <- today
          setEvaluationDate Nothing
          evaluationDate `shouldReturn` t2
      describe "enforce todays historic fixings" $ do
        it "default" $ do
          enforceTodaysHistoricFixings `shouldReturn` False
        it "set to true" $ do
          save <- enforceTodaysHistoricFixings
          setEnforceTodaysHistoricFixings True
          e1 <- enforceTodaysHistoricFixings
          setEnforceTodaysHistoricFixings save
          e1 `shouldBe` True
      describe "include todays cash flows" $ do
        it "default" $ do
          includeTodaysCashFlows `shouldReturn` Nothing
        it "set to true" $ do
          save <- includeTodaysCashFlows
          setIncludeTodaysCashFlows $ Just True
          e0 <- includeTodaysCashFlows
          setIncludeTodaysCashFlows Nothing
          e0 `shouldBe` (Just True)

    describe "dates" $ do
      it "min" $ do
        minDate `shouldBe` (fromGregorian 1901 01 01)
      it "max" $ do
        maxDate `shouldBe` (fromGregorian 2199 12 31)
      it "leap years" $ do
        [False, True, False] `shouldBe` (map isLeap [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5])

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
