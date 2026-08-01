-- Smoke test for the ActualActual DayCounterExtra addition (fixes the
-- long-standing TODO about the missing Schedule argument). Checks:
-- 1. The existing, unchanged schedule-less path (ActualActualBond) still
--    works -- this addition must be purely additive.
-- 2. ActualActualBond' (mandatory Schedule) produces a different, more
--    accurate year-fraction than the schedule-less ActualActualBond for
--    the same date range -- this is the one behavior the whole change
--    exists to add, so it's the one thing worth checking beyond "it
--    builds".
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckActualActual.hs -o /tmp/checkaa -outputdir /tmp/checkaa_build && /tmp/checkaa
import QuantLib.Time.Schedule
import QuantLib.Time.Calendar
import Data.Time.Calendar (fromGregorian)

main :: IO ()
main = do
  dcOld <- dayCounter ActualActualBond
  cal <- calendar TARGET
  sched <- schedule (Just (fromGregorian 2026 1 1))
                     (fromGregorian 2027 1 1)
                     (6, Months)
                     cal
                     Unadjusted
                     Unadjusted
                     Backward
                     False
                     Nothing
                     Nothing
  dcWithSchedule <- dayCounter (ActualActualBond' sched)

  let d1 = fromGregorian 2026 3 1
      d2 = fromGregorian 2026 9 1

  yOld <- years dcOld d1 d2 Nothing Nothing
  yNew <- years dcWithSchedule d1 d2 Nothing Nothing

  putStrLn ("ActualActualBond (unchanged path):      yearFraction = " ++ show yOld)
  putStrLn ("ActualActualBond' sched (new, schedule-aware): yearFraction = " ++ show yNew)
  putStrLn ("Schedule-aware result differs from schedule-less: " ++ show (yNew /= yOld))
