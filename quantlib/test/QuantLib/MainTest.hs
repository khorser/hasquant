{-# OPTIONS_GHC -F -pgmF htfpp #-}
module Main where

import Test.Framework
import {-@ HTF_TESTS @-} QuantLib.Test.HUnit
import {-@ HTF_TESTS @-} QuantLib.Test.QuickCheck

import QuantLib.Utilities
import QuantLib.Time.Date

main :: IO ()
main = do putStrLn $ "QuantLib version " ++ version
             ++ ", Boost " ++ boostVersion
          t <- today
          putStrLn $ "Today is " ++ show (weekday t)
          putStrLn $ "Use --not=LongRunning to disable long running tests"

          htfMain htf_importedTests

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
