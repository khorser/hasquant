{-# LANGUAGE OverloadedLists #-}

-- End-to-end check for OISRateHelperOpts and deriveOptionsRecord. It verifies:
--  1. defaultOisRateHelperOpts's field order/types actually line up with the raw
--     full-arity binding oisRateHelperWithOptions threads them into -- a silent field
--     transposition (deriveOptionsRecord builds the record purely from the inline
--     splice list, with no reification against the underlying binding to catch
--     drift) would show up as a wrong/garbage discount factor here, not a compile
--     error.
--  2. oisRateHelperWithOptions with an all-defaults options record reproduces exactly the
--     same discount as the narrow oisRateHelper called with the same leading args --
--     both are supposed to hit the same upstream ctor with the same upstream
--     defaults, just via two different Haskell entry points.
-- It also exercises non-default telescopicValueDates, paymentFrequency and averagingMethod
-- fields without introducing a historical-fixing dependency.
import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Index.InterestRate hiding(dayCounter)
import QuantLib.Math(Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..), Frequency(..))

import SmokeCheck (checkWith)

main :: IO ()
main = do
  setEvaluationDate $ Just today
  cal <- calendar Null
  dc <- dayCounter (Actual360 False)
  idx <- overnightIborIndex Sofr Nothing
  q <- simpleQuote 0.03
  endDate <- advance cal today (13, Months) ModifiedFollowing False

  let endToEndDiscount h = do
        curve <- piecewiseYieldCurve (ReferenceDate today) [h] dc [] (Iterative Discount LogLinear defaultIterativeBootstrapOpts) False
        discount curve (DatePoint endDate) True

  hNarrow <- oisRateHelper 2 (1, Years) (0, Days) q idx Nothing
  dNarrow <- endToEndDiscount hNarrow

  hWithDefaults <- oisRateHelperWithOptions 2 (1, Years) (0, Days) q idx Nothing defaultOisRateHelperOpts
  dWithDefaults <- endToEndDiscount hWithDefaults

  putStrLn ("narrow          -> discount " ++ show dNarrow)
  putStrLn ("with options (defaults) -> discount " ++ show dWithDefaults)
  -- exact equality is intended: both paths must build an identical helper
  checkWith "with-options defaults match narrow"
    "identical discount (a difference means field order/type drift in the options record)"
    (dNarrow == dWithDefaults)

  hOverridden <- oisRateHelperWithOptions 2 (1, Years) (0, Days) q idx Nothing
    defaultOisRateHelperOpts{oisTelescopicValueDates = True, oisPaymentFrequency = Semiannual, oisAveragingMethod = AveragingSimple}
  dOverridden <- endToEndDiscount hOverridden
  putStrLn ("with options (overridden) -> discount " ++ show dOverridden)
  checkWith "override path takes effect"
    "discount differs from defaults (equality means the overrides are being dropped)"
    (dOverridden /= dWithDefaults)

  -- OvernightObservation reaches the shim: a non-default observation must move the curve.
  -- If the record were dropped or its fields transposed, this would equal the default run.
  -- lookback/observation-shift rather than lockout: lockout pushes the last coupon's required
  -- fixing range past the maturity of the very curve being bootstrapped, so it cannot solve.
  hObserved <- oisRateHelperWithOptions 2 (1, Years) (0, Days) q idx Nothing
    defaultOisRateHelperOpts{oisObservation =
      defaultOvernightObservation{lookbackDays = Just 2, applyObservationShift = True}}
  dObserved <- endToEndDiscount hObserved
  putStrLn ("with options (lookback 2, shifted) -> discount " ++ show dObserved)
  checkWith "OvernightObservation field is threaded through"
    "discount differs from defaults (equality means oisObservation is being dropped)"
    (dObserved /= dWithDefaults)
  where
    today = 2 `january` 2024
