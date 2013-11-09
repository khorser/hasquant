module QuantLib.Test.TermStructures
  (
    run
  )
where

import QuantLib.Currency
import QuantLib.Index.Ibor
import QuantLib.Settings
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Frequency
import QuantLib.Time.DayCounter
import QuantLib.Time.Period
import QuantLib.Time.Unit
import QuantLib.Types

run :: IO ()
run = do
  calendar <- target
  d <- today
  today' <- adjust calendar d Following
  setEvaluationDate (Just today')
  settlement <- advance calendar today' (fromIntegral settlementDays) Days Following False
  dc <- actual360
  deposits <- mapM
    (\(n, u, r) -> do
      q <- simpleQuote (r/100) >>= asQuote
      p <- period n u
      depositRateHelper q p settlementDays calendar ModifiedFollowing True dc)
    depositData
  p6m <- period 6 Months
  ccy <- eur
  ibor <- iborIndex "dummy" p6m settlementDays ccy calendar ModifiedFollowing False dc Nothing
  swaps <- mapM
    (\(n, u, r) -> do
      q <- simpleQuote (r/100) >>= asQuote
      p <- period n u
      swapRateHelper' q p calendar Annual Unadjusted dc ibor Nothing Nothing Nothing)
    swapData
  return ()

  where
    settlementDays = 2
    depositData = [
      ( 1, Months, 4.581),
      ( 2, Months, 4.573 ),
      ( 3, Months, 4.557 ),
      ( 6, Months, 4.496 ),
      ( 9, Months, 4.490 )]
    swapData = [
      ( 1, Years, 4.54 ),
      ( 5, Years, 4.99 ),
      (10, Years, 5.47 ),
      (20, Years, 5.89 ),
      (30, Years, 5.96 )]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
