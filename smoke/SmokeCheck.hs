-- Shared assertion helpers for the smoke/ scripts.
--
-- Each smoke script is compiled standalone (see the "Run with:" line in its header),
-- so this is a plain module with no cabal stanza -- ghc picks it up from the same
-- directory automatically. Before this existed, five scripts had each grown their own
-- spelling of "check a value and shout if it's wrong", in four different output
-- formats, three of which reported neither the tolerance nor the delta on failure.
--
-- Failures call `error`, which is what the scripts already did: a smoke script is a
-- pass/fail executable, and a non-zero exit with the offending numbers is the point.
module SmokeCheck
  ( checkClose
  , checkEq
  , checkWith
  , report
  ) where

import Control.Monad (unless)
import Text.Printf (printf)

-- |Check a Double against an expected value within a tolerance.
checkClose :: String -> Double -> Double -> Double -> IO ()
checkClose label expected actual tol
  | abs (expected - actual) <= tol =
      printf "OK   %-45s expected %.6f, got %.6f\n" label expected actual
  | otherwise = error $
      printf "FAIL %-45s expected %.6f, got %.6f (delta %.3e, tol %.1e)"
        label expected actual (abs (expected - actual)) tol

-- |Check any showable, comparable value for exact equality.
checkEq :: (Eq a, Show a) => String -> a -> a -> IO ()
checkEq label expected actual
  | expected == actual = printf "OK   %-45s %s\n" label (show actual)
  | otherwise = error $
      printf "FAIL %-45s expected %s, got %s" label (show expected) (show actual)

-- |Check an arbitrary predicate, describing the expectation in words. For conditions
-- that are not an equality or a tolerance -- e.g. "these two must differ".
checkWith :: String -> String -> Bool -> IO ()
checkWith label expectation ok =
  unless ok (error $ printf "FAIL %-45s %s" label expectation)
    >> printf "OK   %-45s %s\n" label expectation

-- |Print a labelled value. For the report-only scripts that enumerate enum cases
-- rather than asserting anything.
report :: Show a => String -> a -> IO ()
report label x = printf "%-45s -> %s\n" label (show x)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
