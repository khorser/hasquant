-- Stale-build guard for relinkable handles.
--
-- The behavioural checks live in main/test/QuantLib/Spec/TermStructure.hs and run on every
-- `stack test`. This file exists for the one thing test/ structurally cannot catch: editing
-- a C header without touching any .chs leaves cabal/stack silently stale -- neither tracks
-- that a .chs file's #include'd header changed, so the build reports success without
-- re-running c2hs and the tests then pass against the *old* generated code.
--
-- Curves are the widest such surface: QlYieldTermStructure is a typedef in cbits/qlaux.h,
-- so any edit to it changes the ABI of every function taking a curve, and a partial rebuild
-- would link the two shapes against each other with no error and no crash. Compiled
-- standalone against the installed library, this script sees whatever was actually built.
--
-- Run with:
--   cabal exec -- ghc -ismoke -package hasquant smoke/CheckRelinkable.hs -o /tmp/relinkable -outputdir /tmp/relinkable_build && /tmp/relinkable
import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Swap
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor6M))
import QuantLib.PricingEngine
import QuantLib.Quote hiding(linkTo)
import QuantLib.Settings
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkEq, checkWith)

valueDate :: Day
valueDate = 11 `december` 2012

flat :: Double -> IO YieldTermStructure
flat r = do
  q <- simpleQuote r
  dc <- dayCounter Actual365FixedStandard
  flatForward valueDate q dc Continuous Annual

main :: IO ()
main = do
  setEvaluationDate (Just valueDate)
  cal <- calendar TARGET
  settle <- advance cal valueDate (2, Days) Following False
  fixedDC <- dayCounter Thirty360European
  floatDC <- dayCounter (Actual360 False)

  c <- flat 0.02
  discountH <- relinkableYieldTermStructure (Just c)
  forecastH <- relinkableYieldTermStructure (Just c)

  -- The handles go in as ordinary curve arguments. If a stale build had the two halves
  -- disagreeing about whether a curve is a Handle or a shared_ptr, this is where it shows.
  idx <- iborIndex Euribor6M (Just forecastH)
  fixedSch <- schedule (Just settle) (11 `december` 2017) (1, Years) cal
    Unadjusted Unadjusted Forward False Nothing Nothing
  floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
    ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  swap <- vanillaSwap Payer 1000000 fixedSch 0.02 fixedDC floatSch idx 0 floatDC Nothing Nothing
  eng <- discountingSwapEngine discountH Nothing Nothing Nothing
  setPricingEngine swap eng

  -- One swap, one engine, never rebuilt below.
  before <- npv swap

  flat 0.05 >>= linkTo discountH
  afterDiscount <- npv swap
  checkWith "discount relink moves the NPV"
            "a detached Link fails by NOT moving, so this is the check that matters"
            (abs (afterDiscount - before) > 1.0)

  flat 0.02 >>= linkTo discountH
  restored <- npv swap
  checkEq "relinking back restores exactly" before restored

  flat 0.05 >>= linkTo forecastH
  afterForecast <- npv swap
  checkWith "forecast relink moves the NPV"
            "the index is cloned into every floating coupon, so this has no workaround"
            (abs (afterForecast - restored) > 1.0)

  putStrLn "relinkable: all checks passed"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
