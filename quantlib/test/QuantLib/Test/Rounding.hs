{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.Rounding (htf_thisModulesTests)
-- rounding.cpp
where

import Test.Framework
import Test.HUnit.Lang

import QuantLib.Math.Rounding
import QuantLib.Math.RoundingType
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

assertClose :: Double -> Double -> Assertion
assertClose x1 x2 = assertBool (close x1 x2)

-- literal translation of close from ql/math/comparison.hpp
close :: Double -> Double -> Bool
close x1 x2 =
  x1 == x2
  || x1 * x2 == 0 && diff < tolerance * tolerance
  || diff <= tolerance * abs x1 && diff <= tolerance * abs x2
  where diff = abs(x1 - x2)
        tolerance = qlEpsilon

test_Closest :: IO ()
test_Closest = do
  mapM_ (\(x, p, x1, _x2, _x3, _x4, _x5) -> testRounding Closest x p x1)
    testData

test_Up :: IO ()
test_Up = do
  mapM_ (\(x, p, _x1, x2, _x3, _x4, _x5) -> testRounding Up x p x2)
    testData

test_Down:: IO ()
test_Down = do
  mapM_ (\(x, p, _x1, _x2, x3, _x4, _x5) -> testRounding Down x p x3)
    testData

test_Floor:: IO ()
test_Floor = do
  mapM_ (\(x, p, _x1, _x2, _x3, x4, _x5) -> testRounding Floor x p x4)
    testData

test_Ceiling:: IO ()
test_Ceiling = do
  mapM_ (\(x, p, _x1, _x2, _x3, _x4, x5) -> testRounding Ceiling x p x5)
    testData

testRounding :: RoundingType -> Double -> Int -> Double -> IO ()
testRounding rt x prec expected = do
  r <- rounding' prec rt 5
  let rounded = applyRounding r x
  assertClose rounded expected
    
testData :: [(Double, Int, Double, Double, Double, Double, Double)]
testData =
  [(  0.86313513, 5,  0.86314,  0.86314,  0.86313,  0.86314,  0.86313 ),
   (  0.86313,    5,  0.86313,  0.86313,  0.86313,  0.86313,  0.86313 ),
   ( -7.64555346, 1, -7.6,     -7.7,     -7.6,     -7.6,     -7.6     ),
   (  0.13961605, 2,  0.14,     0.14,     0.13,     0.14,     0.13    ),
   (  0.14344179, 4,  0.1434,   0.1435,   0.1434,   0.1434,   0.1434  ),
   ( -4.74315016, 2, -4.74,    -4.75,    -4.74,    -4.74,    -4.74    ),
   ( -7.82772074, 5, -7.82772, -7.82773, -7.82772, -7.82772, -7.82772 ),
   (  2.74137947, 3,  2.741,    2.742,    2.741,    2.741,    2.741   ),
   (  2.13056714, 1,  2.1,      2.2,      2.1,      2.1,      2.1     ),
   ( -1.06228670, 1, -1.1,     -1.1,     -1.0,     -1.0,     -1.1     ),
   (  8.29234094, 4,  8.2923,   8.2924,   8.2923,   8.2923,   8.2923  ),
   (  7.90185598, 2,  7.90,     7.91,     7.90,     7.90,     7.90    ),
   ( -0.26738058, 1, -0.3,     -0.3,     -0.2,     -0.2,     -0.3     ),
   (  1.78128713, 1,  1.8,      1.8,      1.7,      1.8,      1.7     ),
   (  4.23537260, 1,  4.2,      4.3,      4.2,      4.2,      4.2     ),
   (  3.64369953, 4,  3.6437,   3.6437,   3.6436,   3.6437,   3.6436  ),
   (  6.34542470, 2,  6.35,     6.35,     6.34,     6.35,     6.34    ),
   ( -0.84754962, 4, -0.8475,  -0.8476,  -0.8475,  -0.8475,  -0.8475  ),
   (  4.60998652, 1,  4.6,      4.7,      4.6,      4.6,      4.6     ),
   (  6.28794223, 3,  6.288,    6.288,    6.287,    6.288,    6.287   ),
   (  7.89428221, 2,  7.89,     7.90,     7.89,     7.89,     7.89    )]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
