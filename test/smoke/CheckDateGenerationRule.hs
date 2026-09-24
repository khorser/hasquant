-- Construct schedules for every DateGenerationRule case to check the C++ enum mapping.
--
import Control.Monad
import QuantLib.Time.Schedule
import QuantLib.Time.Calendar
import Data.Time.Calendar (fromGregorian)

-- DateGenerationRule has no Bounded instance, so list its cases explicitly.
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
