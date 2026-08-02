-- Smoke test for the IsQlPayoff/IsQlExercise/EnumMeta' -> Upcastable/GenForeignPtr
-- rewrite in QuantLib.Internal.Enum. A clean build proves the new code type-checks,
-- but not that the right number of upcasts happens at runtime (wrong depth would
-- still compile, e.g. a Payoff silently ending up at the wrong C++ subtype pointer,
-- or a double-free/use-after-free from mismatched Finalizable instances). This
-- exercises the two deepest/most error-prone paths end-to-end:
-- 1. Payoff: PlainVanillaPayoff -> StrikedPayoff -> TypePayoff -> Payoff (3 hops).
-- 2. Exercise: SwingExercise -> BermudanExercise -> Exercise (2 hops), plus the
--    1-hop SwingExercise -> BermudanExercise path used directly by vanillaStorageOption.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckPayoffExerciseUpcast.hs -o /tmp/checkpeu -outputdir /tmp/checkpeu_build && /tmp/checkpeu
-- Uses SwingIntervalExercise (qlSwingExercise1, two Day args + one Word) rather than
-- SwingListExercise (qlSwingExercise, array-marshalled) -- SwingListExercise/qlSwingExercise
-- was found to segfault during development of this smoke test (bad write inside
-- qlSwingExercise itself, isolated via lldb to its array argument marshalling), but that bug
-- predates and is unrelated to this change: nothing in the test suite or examples had ever
-- constructed a SwingExercise before, via either constructor, so it was never caught. Left
-- as-is, out of scope for this refactor -- flagged here for whoever investigates it next.
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
