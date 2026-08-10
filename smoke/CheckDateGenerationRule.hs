-- Smoke test: construct a Schedule for every DateGenerationRule case and print
-- its resulting dates, so a stale c2hs-generated enum shows up immediately, not
-- just "the build succeeded" -- CLAUDE.md's enum-staleness gotcha. This one is
-- prompted by a real bug found while investigating OISRateHelper: hasquant's
-- DateGenerationRule mirror in cbits/qlEnumC2HS.h was missing
-- ThirdWednesdayInclusive (present in QuantLib 1.43's DateGeneration::Rule right
-- after ThirdWednesday), shifting every later case's ordinal by one relative to
-- the real C++ enum -- Twentieth was silently getting cast to
-- ThirdWednesdayInclusive, TwentiethIMM to Twentieth, and so on, with no
-- Haskell constructor able to reach the real CDS2015 at all.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckDateGenerationRule.hs -o /tmp/checkdgr -outputdir /tmp/checkdgr_build && /tmp/checkdgr
import Control.Monad
import QuantLib.Time.Schedule
import QuantLib.Time.Calendar
import Data.Time.Calendar (fromGregorian)

-- c2hs only derives Show/Eq for this enum (no Bounded), so the case list is
-- spelled out explicitly here rather than via [minBound .. maxBound].
main :: IO ()
main = do
  cal <- calendar Null
  forM_ [Backward, Forward, Zero, ThirdWednesday, ThirdWednesdayInclusive
        ,Twentieth, TwentiethIMM, OldCDS, CDS, CDS2015] $ \rule -> do
    sched <- schedule (Just (fromGregorian 2024 1 1))
                       (fromGregorian 2025 1 1)
                       (3, Months)
                       cal
                       Unadjusted
                       Unadjusted
                       rule
                       False
                       Nothing
                       Nothing
    ds <- dates sched
    putStrLn (show rule ++ " -> " ++ show ds)
