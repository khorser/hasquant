{-# LANGUAGE OverloadedLists #-}

-- Smoke test: 'cashFlows' on a leg built from 'cpiLeg' whose 'ZeroInflationIndex' has
-- no fixing at a coupon's observation date must raise a catchable Haskell exception,
-- not crash the process. This is exactly the marshalling/exception-safety concern
-- Hspec can't express (before the fix, this scenario took down the whole test process
-- rather than throwing): 'qlLegCashFlows' allocated the amount/date/hasOccurred
-- out-arrays directly into its out-params *before* the per-cashflow loop that can
-- throw, and its catch block freed them without also resetting the pointers (and the
-- parallel length out-params) to null/zero -- so when a 'CPICoupon' amount() threw
-- partway through the leg, the Haskell-side array marshaller (which peeks/frees
-- unconditionally, before checking the error channel) double-freed the already-freed
-- array, corrupting the heap (SIGTRAP via libmalloc's consistency check). Fixed by
-- routing the three out-arrays through 'OutArrayGuard' (cbits/qlaux.h), an RAII guard
-- that frees and nulls an array out-param pair unless explicitly committed -- see it
-- and 'qlLegCashFlows' for any new array-out shim of this shape.
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
  -- Fixings for Jan-Mar 2023 only: leaves a gap for later months that are still
  -- within the "should already be available" window given today's date and
  -- UKRPI's availability lag, so a later coupon's pastFixing genuinely returns
  -- Null (a real "Missing fixing" error), rather than needing a forecast curve.
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
