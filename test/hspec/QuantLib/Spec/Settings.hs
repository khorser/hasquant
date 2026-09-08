module QuantLib.Spec.Settings (spec) where

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck(Arbitrary(arbitrary))
import Test.QuickCheck.Monadic(monadicIO, pick, run)

import Data.Time.Calendar

import QuantLib.Time.Date as Date
import QuantLib.Type
import qualified QuantLib.Settings as Settings
import QuantLib.Spec.Helpers(ValidDay(..), InvalidDay(..))

spec :: Spec
spec = do
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
