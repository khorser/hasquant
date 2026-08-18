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
--
-- Also covers SwingListExercise (qlSwingExercise, array-marshalled), which used to segfault:
-- cbits/qlInstrument.cpp built its `seconds` std::vector as an empty vector plus std::copy
-- into it (never allocated), instead of the range-constructor idiom used everywhere else in
-- cbits/ for this exact pattern. Nothing in the test suite or examples had ever constructed a
-- SwingExercise via either constructor before this was found, so it went uncaught until now.
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

  -- 4: SwingListExercise (qlSwingExercise, the array-marshalled constructor) -- the
  -- original repro for the qlInstrument.cpp empty-vector segfault, now fixed.
  let listSwingEx = SwingListExercise [(maturity, 0)]
  swingOpt <- vanillaSwingOption (PlainVanilla (PlainVanillaPayoff Call 100)) listSwingEx 0 1
  expired3 <- isExpired swingOpt
  putStrLn ("vanillaSwingOption (SwingListExercise): isExpired = " ++ show expired3)
