{-# OPTIONS_GHC -fno-warn-orphans #-}
-- | Shared arbitrary instances and value-comparison helpers used by more than
-- one @QuantLib.Spec.*@ module. Split out of the former single-file
-- @MainTest.hs@ (see CLAUDE.md's "Documentation upkeep" for the module
-- layout this belongs to).
module QuantLib.Spec.Helpers (
    ValidDay(..)
  , InvalidDay(..)
  , areClose
  , closePrec
  , listClose
  , binomialsClose
  ) where

import Data.Time.Calendar
import Data.List(delete)

import Test.QuickCheck(elements, Arbitrary(arbitrary))

import QuantLib.Time.Date(minDate, maxDate)
import QuantLib.Time.Schedule(Frequency(..))
import qualified QuantLib.Settings as Settings

instance Arbitrary Frequency where
  arbitrary = elements $ OtherFrequency `delete` [minBound .. ]

newtype ValidDay = ValidDay {validDay::Day} deriving (Show, Eq)
newtype InvalidDay = InvalidDay Day deriving (Show, Eq)
instance Arbitrary ValidDay where
  arbitrary = do
    d <- elements [toModifiedJulianDay minDate .. toModifiedJulianDay maxDate]
    return $ ValidDay (ModifiedJulianDay d)

instance Arbitrary InvalidDay where
  arbitrary = do
    d <- elements $ [minD-500 .. minD-1] ++ [maxD+1 .. maxD+500]
    return $ InvalidDay (ModifiedJulianDay d)
    where minD = toModifiedJulianDay minDate
          maxD = toModifiedJulianDay maxDate

-- literal translation of close from ql/math/comparison.hpp
areClose :: Double -> Double -> Bool
areClose x1 x2 = x1 == x2
            || x1 * x2 == 0 && diff < Settings.epsilon * Settings.epsilon
            || diff <= Settings.epsilon * abs x1 && diff <= Settings.epsilon * abs x2
            where diff = abs(x1 - x2)

closePrec :: Double -> Double -> Double -> Bool
closePrec r p x = abs (x - r) < p

listClose :: (a -> Double) -> [Double] -> Double -> [a] -> Bool
listClose f x1 e x2 = (length x1 == length x2) && all (\(x, y) -> abs(x - f y) < e) (zip x1 x2)

-- |row-wise 'listClose' at 1.0e-6, for tables of per-engine results (e.g. the
-- binomial-tree grid in the equity option example)
binomialsClose :: [[Double]] -> [[Double]] -> Bool
binomialsClose expected actual =
  length expected == length actual
    && and (zipWith (\e a -> listClose id e 1.0e-6 a) expected actual)
