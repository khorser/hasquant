{-# LANGUAGE OverloadedLists #-}

-- Smoke test: construct a FraRateHelper for every PillarChoice case and a
-- FuturesRateHelper for every FuturesType case, then bootstrap each into a
-- tiny piecewise yield curve and print the implied discount, so a stale
-- c2hs-generated enum (these two are declared directly in
-- QuantLib.TermStructure.Yield -- see the cross-module {#import#} gotcha in
-- CLAUDE.md -- rather than in QuantLib.Internal.Common like most others) shows
-- up immediately, not just "the build succeeded".
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckRateHelperEnums.hs -o /tmp/checkrhe -outputdir /tmp/checkrhe_build && /tmp/checkrhe
import Control.Monad
import QuantLib.Math(Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
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

  forM_ [MaturityDate, LastRelevantDate, CustomDate] $ \pillar -> do
    q <- simpleQuote 0.03
    customPillarDate <- advance cal today (3, Months) ModifiedFollowing False
    h <- fraRateHelper q 1 4 2 cal ModifiedFollowing True dc pillar
      (if pillar == CustomDate then Just customPillarDate else Nothing) True
    curve <- piecewiseYieldCurve today [h] dc [] Discount LogLinear
    endDate <- advance cal today (5, Months) ModifiedFollowing False
    d <- discount' curve endDate True
    putStrLn (show pillar ++ " -> discount " ++ show d)

  imm <- nextIMMDate today True
  forM_ [(IMM, imm), (ASX, 8 `march` 2024), (Custom, imm)] $ \(ty, futDate) -> do
    q <- simpleQuote 99.0
    h <- futuresRateHelper q futDate 3 cal ModifiedFollowing True dc Nothing ty
    curve <- piecewiseYieldCurve today [h] dc [] Discount LogLinear
    d <- discount' curve futDate True
    putStrLn (show ty ++ " -> discount " ++ show d)
  where
    today = 2 `january` 2024
