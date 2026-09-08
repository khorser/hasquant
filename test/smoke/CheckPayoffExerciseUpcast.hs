{-# LANGUAGE OverloadedLists #-}

-- Runtime check for the deepest Payoff and Exercise upcast paths. Wrong hop counts and mismatched
-- finalizers can type-check but select the wrong C++ subtype or corrupt ownership:
-- 1. Payoff: PlainVanillaPayoff -> StrikedPayoff -> TypePayoff -> Payoff (3 hops).
-- 2. Exercise: SwingExercise -> BermudanExercise -> Exercise (2 hops), plus the
--    1-hop SwingExercise -> BermudanExercise path used directly by vanillaStorageOption.
--
-- SwingListExercise also covers array marshalling into its `seconds` vector.
import Data.Time.Calendar (fromGregorian)

import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.Settings

main :: IO ()
main = do
  setEvaluationDate $ Just (fromGregorian 2026 1 1)
  let d1 = fromGregorian 2026 6 1
      maturity = fromGregorian 2027 1 1
      deepPayoff = Type (Striked (PlainVanilla (PlainVanillaPayoff Call 100)))
      swingEx = SwingIntervalExercise d1 maturity 3600
      deepExercise = Bermudan (Swing swingEx)

  -- 1+2: a Payoff needing 3 upcast hops, and an Exercise needing 2, constructed
  -- and consumed together by a single oneAssetOption call.
  opt <- oneAssetOption deepPayoff deepExercise
  expired1 <- isExpired opt
  putStrLn ("oneAssetOption (deep Payoff, deep Exercise): isExpired = " ++ show expired1)

  -- 3: SwingExercise -> BermudanExercise, 1 hop, consumed directly (no further
  -- upcast to Exercise) by vanillaStorageOption's BermudanExercise-typed argument.
  storageOpt <- vanillaStorageOption (Swing swingEx) 100 0 0
  expired2 <- isExpired storageOpt
  putStrLn ("vanillaStorageOption (bare SwingExercise as BermudanExercise): isExpired = " ++ show expired2)

  -- 4: SwingListExercise through the array-marshalled constructor.
  let listSwingEx = SwingListExercise [(maturity, 0)]
  swingOpt <- vanillaSwingOption (PlainVanilla (PlainVanillaPayoff Call 100)) listSwingEx 0 1
  expired3 <- isExpired swingOpt
  putStrLn ("vanillaSwingOption (SwingListExercise): isExpired = " ++ show expired3)
