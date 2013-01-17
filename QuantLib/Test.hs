{-# OPTIONS_GHC -F -pgmF htfpp #-}
module Main where

import Test.Framework
import {-@ HTF_TESTS @-} QuantLib.HUnit
import {-@ HTF_TESTS @-} QuantLib.QuickCheck

main :: IO ()
main = htfMain htf_importedTests
