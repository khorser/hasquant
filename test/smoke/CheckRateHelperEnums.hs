{-# LANGUAGE OverloadedLists #-}

-- Bootstrap a curve for each PillarChoice and FuturesType to check enum dispatch.
--
import Control.Monad
import QuantLib.Math(Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.Context(setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..))

-- c2hs only derives Show/Eq for these enums (no Bounded), so the case lists
-- are spelled out explicitly here rather than via [minBound .. maxBound].
main :: IO ()
main = do
  setEvaluationDate $ Just today
  cal <- calendar Null
  dc <- dayCounter (Actual360 False)

  forM_ ([MaturityDate, LastRelevantDate, CustomDate] :: [PillarChoice]) $ \pillar -> do
    q <- simpleQuote 0.03
    customPillarDate <- advance cal today (3, Months) ModifiedFollowing False
    h <- fraRateHelper q (FraMonths 1 4 2 cal ModifiedFollowing True dc) pillar
      (if pillar == CustomDate then Just customPillarDate else Nothing) True
    curve <- piecewiseYieldCurve (ReferenceDate today) [h] dc [] (Iterative Discount LogLinear defaultIterativeBootstrapOpts) False
    endDate <- advance cal today (5, Months) ModifiedFollowing False
    d <- discount curve (DatePoint endDate) True
    putStrLn (show pillar ++ " -> discount " ++ show d)

  imm <- nextImmDate today True
  forM_ ([(IMM, imm), (ASX, 8 `march` 2024), (Custom, imm)] :: [(FuturesType, Day)]) $ \(ty, futDate) -> do
    q <- simpleQuote 99.0
    h <- futuresRateHelper q (FuturesMonths futDate 3 cal ModifiedFollowing True dc) Nothing ty
    curve <- piecewiseYieldCurve (ReferenceDate today) [h] dc [] (Iterative Discount LogLinear defaultIterativeBootstrapOpts) False
    d <- discount curve (DatePoint futDate) True
    putStrLn (show ty ++ " -> discount " ++ show d)
  where
    today = 2 `january` 2024
