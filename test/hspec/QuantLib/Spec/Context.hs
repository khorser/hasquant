module QuantLib.Spec.Context (spec) where

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck(Arbitrary(arbitrary))
import Test.QuickCheck.Monadic(monadicIO, pick, run)

import Data.Time.Calendar

import QuantLib.Time.Date as Date
import QuantLib.Context
import qualified QuantLib.Context as Context
import QuantLib.Spec.Helpers(ValidDay(..), InvalidDay(..))

spec :: Spec
spec = do
    describe "settings" $ do
      describe "evaluaton date" $ do
        it "default is today" $ do
          t1 <- Context.evaluationDate
          today `shouldReturn` t1
        it "set" $ do
          Context.setEvaluationDate (Just $ december 29 2012)
          Context.evaluationDate `shouldReturn` fromGregorian 2012 12 29
        it "reset to default" $ do
          t2 <- today
          Context.setEvaluationDate Nothing
          Context.evaluationDate `shouldReturn` t2
        prop "randomized valid evaluation date" $ do
          monadicIO $ do
            ValidDay d1 <- pick arbitrary
            run $ (Context.setEvaluationDate (Just d1) >> Context.evaluationDate) `shouldReturn` d1
        prop "randomized invalid evaluation date" $ do
          monadicIO $ do
            t <- run today
            run $ Context.setEvaluationDate (Just t)
            (InvalidDay d) <- pick arbitrary
            run $ Context.setEvaluationDate (Just d) `shouldThrow` (== DateConversion d)
            run $ Context.evaluationDate `shouldReturn` t

      describe "enforce todays historic fixings" $ do
        it "default" $ do
          Context.enforceTodaysHistoricFixings `shouldReturn` False
        it "set to true" $ do
          save <- Context.enforceTodaysHistoricFixings
          Context.setEnforceTodaysHistoricFixings True
          e1 <- Context.enforceTodaysHistoricFixings
          Context.setEnforceTodaysHistoricFixings save
          e1 `shouldBe` True
      describe "include todays cash flows" $ do
        it "default" $ do
          Context.includeTodaysCashFlows `shouldReturn` Nothing
        it "set to true" $ do
          save <- Context.includeTodaysCashFlows
          Context.setIncludeTodaysCashFlows $ Just True
          e0 <- Context.includeTodaysCashFlows
          Context.setIncludeTodaysCashFlows save
          e0 `shouldBe` Just True
