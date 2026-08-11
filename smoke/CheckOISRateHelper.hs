-- Smoke test for OISRateHelperOpts/deriveOptionsRecord (Batch 8's new options-record
-- TH infra -- see the add-quantlib-options-record skill). Two things this
-- checks that a green `stack build` alone would not:
--  1. defaultOISRateHelperOpts's field order/types actually line up with the raw
--     full-arity binding oisRateHelperFull threads them into -- a silent field
--     transposition (deriveOptionsRecord builds the record purely from the inline
--     splice list, with no reification against the underlying binding to catch
--     drift) would show up as a wrong/garbage discount factor here, not a compile
--     error.
--  2. oisRateHelperFull with an all-defaults options record reproduces exactly the
--     same discount as the narrow oisRateHelper called with the same leading args --
--     both are supposed to hit the same upstream ctor with the same upstream
--     defaults, just via two different Haskell entry points.
-- Also constructs one helper with several non-default fields (telescopicValueDates,
-- paymentFrequency, averagingMethod) via record-update syntax, to exercise the
-- override path itself, not just the defaults -- CDS2015/MaturityDate combinations
-- were tried first but need historical fixing data this smoke test doesn't provide,
-- so the override case below sticks to fields that don't change the accrual schedule.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckOISRateHelper.hs -o /tmp/checkois -outputdir /tmp/checkois_build && /tmp/checkois
import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Index.InterestRate hiding (dayCounter)
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
        curve <- piecewiseYieldCurve today [h] dc [] Discount LogLinear
        discount' curve endDate True

  hNarrow <- oisRateHelper 2 (1, Years) q idx Nothing
  dNarrow <- endToEndDiscount hNarrow

  hFullDefaults <- oisRateHelperFull 2 (1, Years) q idx Nothing defaultOISRateHelperOpts
  dFullDefaults <- endToEndDiscount hFullDefaults

  putStrLn ("narrow          -> discount " ++ show dNarrow)
  putStrLn ("full (defaults) -> discount " ++ show dFullDefaults)
  -- exact equality is intended: both paths must build an identical helper
  checkWith "full-with-defaults matches narrow"
    "identical discount (a difference means field order/type drift in the options record)"
    (dNarrow == dFullDefaults)

  hOverridden <- oisRateHelperFull 2 (1, Years) q idx Nothing
    defaultOISRateHelperOpts{oisTelescopicValueDates = True, oisPaymentFrequency = Semiannual, oisAveragingMethod = AveragingSimple}
  dOverridden <- endToEndDiscount hOverridden
  putStrLn ("full (overridden) -> discount " ++ show dOverridden)
  checkWith "override path takes effect"
    "discount differs from defaults (equality means the overrides are being dropped)"
    (dOverridden /= dFullDefaults)
  where
    today = 2 `january` 2024
