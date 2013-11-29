{-# OPTIONS_GHC -F -pgmF htfpp #-}
{-# LANGUAGE CPP #-}
module Main where

import Test.Framework
import {-@ HTF_TESTS @-} QuantLib.Test.HUnit
import {-@ HTF_TESTS @-} QuantLib.Test.QuickCheck

import {-@ HTF_TESTS @-} QuantLib.Test.Calendars
import {-@ HTF_TESTS @-} QuantLib.Test.CashFlows
import {-@ HTF_TESTS @-} QuantLib.Test.Dates
import {-@ HTF_TESTS @-} QuantLib.Test.DayCounters
import {-@ HTF_TESTS @-} QuantLib.Test.InterestRates
import {-@ HTF_TESTS @-} QuantLib.Test.Period
import {-@ HTF_TESTS @-} QuantLib.Test.Rounding
import {-@ HTF_TESTS @-} QuantLib.Test.TermStructures
import {-@ HTF_TESTS @-} QuantLib.Test.Schedule

#ifdef INTERNAL_TEST
import {-@ HTF_TESTS @-} QuantLib.Test.Internal.HUnit
#endif

import Control.Applicative((<$>))
import QuantLib.Utilities
import QuantLib.Time.Date

main :: IO ()
main = do putStrLn $ "QuantLib version " ++ version
             ++ ", Boost " ++ boostVersion
          (Right w) <- weekday <$> today
          putStrLn $ "Today is " ++ show w
          putStrLn "\nUse --not=LongRunning to disable long running tests\n"

          htfMain htf_importedTests

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
