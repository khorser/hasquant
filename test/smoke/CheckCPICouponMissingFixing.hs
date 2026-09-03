{-# LANGUAGE OverloadedLists #-}

-- Smoke test: a missing CPI fixing must raise an exception without corrupting array output.
--
-- Run with: cabal exec -- ghc -itest/smoke -package hasquant test/smoke/CheckCPICouponMissingFixing.hs -o /tmp/checkcpimissing -outputdir /tmp/checkcpimissing_build && /tmp/checkcpimissing
module Main(main) where

import Control.Exception (SomeException, try)
import Control.Monad (forM_)
import qualified QuantLib.CashFlow as CF
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, fromDates, DayCounterConstructor(..), TimeUnit(Months))

import SmokeCheck (checkWith)

main :: IO ()
main = do
  setEvaluationDate $ Just today
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null

  zii <- zeroInflationIndex UKRPI
  -- The incomplete history forces a genuine missing-fixing error.
  forM_ (zip [1 :: Double ..] [1 `january` 2023, 1 `february` 2023, 1 `march` 2023]) $ \(i, d) ->
    addFixing zii d (260.0 + i) False

  schedule <- fromDates [3 `october` 2023, 20 `november` 2023] cal Unadjusted Nothing Nothing Nothing Nothing
  leg <- CF.cpiLeg schedule zii 260.0 obsLag [100.0] [0.05] dc Unadjusted cal CF.CPIFlat True

  r <- try (CF.cashFlows leg Nothing Nothing) :: IO (Either SomeException [(Day, Double, Bool)])
  checkWith "cashFlows on CPICoupon leg with a missing fixing"
    "raises a catchable exception instead of crashing the process"
    (either (const True) (const False) r)
  where
    today = 2 `january` 2024
    obsLag = (3, Months)
