{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.DayCounters (htf_thisModulesTests)
-- daycounters.cpp
where

import Test.Framework

import Data.Either
import Data.Time.Calendar

import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Period
import QuantLib.Time.Unit
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

test_ActualActual :: IO ()
test_ActualActual = keepingSettings' $
  mapM_ (\(c, s, e, rs, re, t) -> do
    dc <- c
    let (Right f) = yearFraction dc s e rs re
    assertBool (abs(t - f) <= 1.0e-10))
    testCases
  where testCases = [
          (actualActualISDA, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497724380567),
          (actualActualISMA, 1 `november` 2003, 1 `may` 2004, Just $ 1 `november` 2003, Just $ 1 `may` 2004, 0.500000000000),
          (actualActualAFB, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497267759563),
          (actualActualISDA, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
          (actualActualISMA, 1 `february` 1999, 1 `july` 1999, Just $ 1 `july` 1998, Just $ 1 `july` 1999, 0.410958904110),
          (actualActualAFB, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
          (actualActualISDA, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.001377348600),
          (actualActualISMA, 1 `july` 1999, 1 `july` 2000, Just $ 1 `july` 1999, Just $ 1 `july` 2000, 1.000000000000),
          (actualActualAFB, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.000000000000),
          (actualActualISDA, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
          (actualActualISMA, 15 `august` 2002, 15 `july` 2003, Just $ 15 `january` 2003, Just $ 15 `july` 2003, 0.915760869565),
          (actualActualAFB, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
          (actualActualISDA, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504004790778),
          (actualActualISMA, 15 `july` 2003, 15 `january` 2004, Just $ 15 `july` 2003, Just $ 15 `january` 2004, 0.500000000000),
          (actualActualAFB, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504109589041),
          (actualActualISDA, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.503892506924),
          (actualActualISMA, 30 `july` 1999, 30 `january` 2000, Just $ 30 `july` 1999, Just $ 30 `january` 2000, 0.500000000000),
          (actualActualAFB, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.504109589041),
          (actualActualISDA, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.415300546448),
          (actualActualISMA, 30 `january` 2000, 30 `june` 2000, Just $ 30 `january` 2000, Just $ 30 `july` 2000, 0.417582417582),
          (actualActualAFB, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.41530054644)]

checkCounter :: DayCounter -> [Day] -> [(Int, Unit)] -> [Double] -> IO ()
checkCounter dc days periods expected = keepingSettings' $ do
  mapM_ (\d -> do
    calculated <- mapM (\p -> do
      pp <- uncurry period p
      let (Right end) = addPeriod d pp
      return $ yearFraction dc d end Nothing Nothing)
      periods
    let diffs = zipWith (-) (rights calculated) expected
    assertBool (all (\x -> abs x < 1.0e-12) diffs))
    days

test_Simple :: IO ()
test_Simple = do
  dc <- simple
  checkCounter dc
    [1 `january` 2002 .. 31 `december` 2005] 
    [(3, Months), (6, Months), (1, Years)]
    [0.25, 0.5, 1.0]

test_One :: IO ()
test_One = keepingSettings' $ do
  dc <- one
  checkCounter dc
    [1 `january` 2004 .. 31 `december` 2004]
    [(3, Months), (6, Months), (1, Years)]
    [1.0, 1.0, 1.0]

test_Business252 :: IO ()
test_Business252 = keepingSettings' $ do
  dc <- brazilSettlement >>= business252

  let fractions = rights $ map (\(s, e) -> yearFraction dc s e Nothing Nothing)
                (zip days (tail days))
  let diffs = zipWith (-) fractions expected
  assertBool (all (\x -> abs x < 1.0e-12) diffs)
  
  where days = [1 `february` 2002,
                4 `february` 2002,
                16 `may` 2003,
                17 `december` 2003,
                17 `december` 2004,
                19 `december` 2005,
                 2 `january` 2006,
                13 `march` 2006,
                15 `may` 2006,
                17 `march` 2006,
                15 `may` 2006,
                26 `july` 2006,
                28 `june` 2007,
                16 `september` 2009,
                26 `july` 2016]
        expected = [0.0039682539683,
                    1.2738095238095,
                    0.6031746031746,
                    0.9960317460317,
                    1.0000000000000,
                    0.0396825396825,
                    0.1904761904762,
                    0.1666666666667,
                    -0.1507936507937,
                    0.1507936507937,
                    0.2023809523810,
                    0.912698412698,
                    2.214285714286,
                    6.84126984127]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
