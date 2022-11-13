module QuantLib.Example.TARF
  (
    run
  )
where

import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Math
import QuantLib.Process
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Method
import QuantLib.Settings

run :: IO ()
run = do
  let valDate = 15 `august` 2022
  setEvaluationDate (Just valDate)
  calILS <- calendar IsraelSettlement
  calEUR <- calendar TARGET
  calUSD <- calendar UnitedStatesSettlement
  calEURILSUSD <- calendar $ Joint3 calILS calEUR calUSD JoinHolidays
  calEURILS <- calendar $ Joint2 calILS calEUR JoinHolidays
  dcEUR <- dayCounter Actual360
  dcILS <- dayCounter Actual365FixedStandard
  sched <- schedule (Just $ 2 `november` 2022) (2 `october` 2023) (1, Months) calEUR ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  ds <- dates sched
  grid <- mapM (\x -> years dcILS valDate x Nothing Nothing) ds >>= timeGridFromList
  print ds

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
