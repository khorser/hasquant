-- Compare ActualActualBond with its schedule-aware variant for the same dates.
--
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

  yOld <- yearFraction dcOld d1 d2 Nothing Nothing
  yNew <- yearFraction dcWithSchedule d1 d2 Nothing Nothing

  putStrLn ("ActualActualBond (unchanged path):      yearFraction = " ++ show yOld)
  putStrLn ("ActualActualBond' sched (new, schedule-aware): yearFraction = " ++ show yNew)
  putStrLn ("Schedule-aware result differs from schedule-less: " ++ show (yNew /= yOld))
