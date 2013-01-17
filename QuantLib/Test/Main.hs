{-# OPTIONS_GHC -F -pgmF htfpp #-}
module Main where

import Test.Framework
import {-@ HTF_TESTS @-} QuantLib.Test.HUnit
import {-@ HTF_TESTS @-} QuantLib.Test.QuickCheck

main :: IO ()
main = htfMain htf_importedTests

--main = do putStrLn $ "QuantLib version " ++ Utilities.version
--            ++ ", Boost " ++ Utilities.boostVersion
--          t <- today
--          putStrLn $ "Today is " ++ show (weekday t)
--          -- if we don't do GC we have a chance of getting 
--          -- "could not notify one or more observers: year 2200 out of bounds"
--          -- from one of the outstanding rate helpers
--          -- when QuickCheck sets evaluation date to some border value like 27Nov2199
--          performGC
--          putStrLn "-- Done with HUnit --"
--          quickCheckWith stdArgs{maxSuccess = 500} prop_validEvaluationDate
--          quickCheck prop_invalidEvaluationDate
--          quickCheck prop_singleLegStartDate
--          quickCheckWith stdArgs{maxDiscardRatio = 20} prop_legStartDate
--          quickCheckWith stdArgs{maxDiscardRatio = 20} prop_scheduleDates
--          quickCheck prop_frequencyFromPeriodFromFrequency
--          quickCheckWith stdArgs{maxSuccess = 10} prop_quoteValue
