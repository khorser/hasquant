{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Spec.Syntax (spec) where

import Test.Hspec
import Test.Hspec.QuickCheck(prop)
import Test.QuickCheck(Arbitrary(arbitrary))
import Test.QuickCheck.Monadic(monadicIO, pick, run)

import Data.Time.Calendar

import QuantLib.Time.Date as Date
import QuantLib.Type
import qualified QuantLib.Settings as Settings
import QuantLib.Syntax(free1st, free2nd, cutAt, cutAt', cut)
import QuantLib.Example.SyntaxHelpers(syntaxTestF, HasSyntaxLabel(..))

import QuantLib.Spec.Helpers(ValidDay(..), InvalidDay(..))

spec :: Spec
spec = do
    describe "syntax" $ do
      it "cutAt [1] matches free1st" $ do
        $(cutAt [1] 'syntaxTestF) 2 3 4 1 `shouldBe` syntaxTestF 1 2 3 4
        $(cutAt [1] 'syntaxTestF) 2 3 4 1 `shouldBe` $(free1st 'syntaxTestF) 2 3 4 1
      it "cutAt [2] matches free2nd" $ do
        $(cutAt [2] 'syntaxTestF) 1 3 4 2 `shouldBe` syntaxTestF 1 2 3 4
        $(cutAt [2] 'syntaxTestF) 1 3 4 2 `shouldBe` $(free2nd 'syntaxTestF) 1 3 4 2
      it "cutAt frees two non-adjacent positions" $
        $(cutAt [1,3] 'syntaxTestF) 2 4 1 3 `shouldBe` syntaxTestF 1 2 3 4
      it "cut substitutes holes in order of occurrence" $
        $(cut [| syntaxTestF _ 2 _ 4 |]) 1 3 `shouldBe` syntaxTestF 1 2 3 4
      it "cut treats distinct named holes the same as bare _" $
        $(cut [| syntaxTestF _a 2 _b 4 |]) 1 3 `shouldBe` syntaxTestF 1 2 3 4
      it "cut shares one parameter between repeats of a named hole" $
        $(cut [| syntaxTestF _a 2 _a 4 |]) 1 `shouldBe` syntaxTestF 1 2 1 4
      it "cut orders shared holes by first occurrence" $
        $(cut [| syntaxTestF _b 2 _a _b |]) 1 3 `shouldBe` syntaxTestF 1 2 3 1
      it "cutAt, cutAt' and cut all work on a typeclass method" $ do
        $(cutAt [1] 'syntaxLabelWith) 1 2 3 True `shouldBe` syntaxLabelWith True 1 2 3
        $(cutAt' [1] 4) syntaxLabelWith 1 2 3 True `shouldBe` syntaxLabelWith True 1 2 3
        $(cut [| syntaxLabelWith _ 1 2 3 |]) True `shouldBe` syntaxLabelWith True 1 2 3

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
