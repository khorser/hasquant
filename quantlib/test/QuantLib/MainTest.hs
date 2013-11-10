{-# OPTIONS_GHC -F -pgmF htfpp #-}
module Main where

import Test.Framework
import {-@ HTF_TESTS @-} QuantLib.Test.HUnit
import {-@ HTF_TESTS @-} QuantLib.Test.QuickCheck

import {-@ HTF_TESTS @-} QuantLib.Test.Dates
import {-@ HTF_TESTS @-} QuantLib.Test.DayCounters
import {-@ HTF_TESTS @-} QuantLib.Test.InterestRates
import {-@ HTF_TESTS @-} QuantLib.Test.Period
import {-@ HTF_TESTS @-} QuantLib.Test.Rounding
import {-@ HTF_TESTS @-} QuantLib.Test.TermStructures
import {-@ HTF_TESTS @-} QuantLib.Test.Schedule

import QuantLib.Utilities
import QuantLib.Time.Date

main :: IO ()
main = do putStrLn $ "QuantLib version " ++ version
             ++ ", Boost " ++ boostVersion
          t <- today
          putStrLn $ "Today is " ++ show (weekday t)
          putStrLn "\nUse --not=LongRunning to disable long running tests\n"

          htfMain htf_importedTests

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
