-- Smoke test: construct the newly-added Actual36525/Actual366 day
-- counters (both true/false variants of includeLastDay) and check a
-- day-count between two known dates differs correctly with/without the
-- extra day -- catching a stale c2hs-generated enum, a wrong bool<->int
-- FFI marshal, or a wrong dispatch in `dayCounter`'s pattern match that
-- a successful build alone wouldn't reveal.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckDayCounters.hs -o /tmp/checkdc -outputdir /tmp/checkdc_build && /tmp/checkdc
import QuantLib.Time.Schedule
import Data.Time.Calendar (fromGregorian)
import Control.Monad

main :: IO ()
main = do
  let d1 = fromGregorian 2026 1 1
      d2 = fromGregorian 2026 1 2 -- one day later
  forM_ [("Actual36525", Actual36525), ("Actual366", Actual366)] $ \(nm, ctor) ->
    forM_ [False, True] $ \inc -> do
      dc <- dayCounter (ctor inc)
      n <- days dc d1 d2
      putStrLn (nm ++ " includeLastDay=" ++ show inc ++ ": days(d1,d2) = " ++ show n)
