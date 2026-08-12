-- Spike probe for relinkable-plan.md's PREREQUISITE: does making QlYieldTermStructure a
-- Handle<YieldTermStructure> keep ownership sound under Haskell GC?
--
-- Two questions the ordinary test suite structurally cannot answer:
--
--  1. LIVENESS. Before the change, a consumer copied the curve's shared_ptr directly, so
--     Haskell dropping its reference could not matter. After it, the consumer copies a
--     Handle and reaches the curve through a shared Link. If the Link did not keep the
--     curve alive, dropping the Haskell reference and collecting would leave the consumer
--     pointing at freed memory. The suite never drops a curve mid-computation, so it would
--     never see this.
--
--  2. LEAKS AND CYCLES. A Link owns its curve strongly, and the Link is internal to C++ --
--     it is never traced, so tools/alloc-summary.py sees only the Handle objects (as
--     ret()/del() pairs) and structurally cannot prove the Link half. A leaked Link, or a
--     reference cycle through one, is invisible to it. The only way to see that is to build
--     and drop curves in bulk and watch the process footprint.
--
-- Run with:
--   cabal exec -- ghc -ismoke -package hasquant smoke/CheckHandleGC.hs -o /tmp/checkgc -outputdir /tmp/checkgc_build
--   /tmp/checkgc                 # checks 1-3 (liveness)
--   /usr/bin/time -l /tmp/checkgc 2000    # growth loop, N iterations; compare peak RSS across N
--
-- For the growth check, run it at several N (200 / 2000 / 20000) and compare maximum
-- resident set size. Flat across N means no Link leak and no cycle. RSS rising roughly
-- linearly in N is the signature of exactly the failure alloc-summary.py cannot see.
-- Measuring peak RSS externally avoids needing an in-process reading of the C++ heap,
-- which GHC.Stats does not cover -- it reports the Haskell heap only, and a leaked Link
-- is not on it.
import Control.Monad (forM_, when)
import System.Environment (getArgs)
import System.Mem (performGC)

import QuantLib.Instrument
import QuantLib.Instrument.Swap
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.PricingEngine
import QuantLib.InterestRate
import QuantLib.Quote
import QuantLib.Settings
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkEq, checkWith)

valueDate :: Day
valueDate = 11 `december` 2012

-- A flat 2% curve. Deliberately built inside a function that returns something *else*, so
-- that on return there is no Haskell reference left to the curve at all: whether it stays
-- alive is then entirely down to the C++ side's ownership.
mkCurve :: Double -> IO TS.YieldTermStructure
mkCurve r = do
  q <- simpleQuote r
  dc <- dayCounter Actual365FixedStandard
  TS.flatForward valueDate q dc Continuous Annual

-- |Hand the curve to a consumer and return only the consumer. The curve's ForeignPtr dies
-- here; the consumer's copied Handle, and the Link it shares, are all that keep it alive.
spreadedCurveDroppingBase :: IO TS.YieldTermStructure
spreadedCurveDroppingBase = do
  base <- mkCurve 0.02
  spread <- simpleQuote 0.0
  TS.forwardSpreadedTermStructure base spread

main :: IO ()
main = do
  args <- getArgs
  setEvaluationDate (Just valueDate)

  case args of
    (n:_) -> growthLoop (read n)
    []    -> livenessChecks

-- ---------------------------------------------------------------- liveness

livenessChecks :: IO ()
livenessChecks = do
  -- Reference values, computed with every reference held, the ordinary way.
  refSpreaded <- do
    base <- mkCurve 0.02
    spread <- simpleQuote 0.0
    c <- TS.forwardSpreadedTermStructure base spread
    TS.discount c 5.0 False

  -- Check 1: the base curve is dropped and collected, then read through the derived curve
  -- that holds it via a Handle. Exact equality: it is the same arithmetic on the same
  -- curve, so anything other than an exact match means we are not reading the same object.
  do
    c <- spreadedCurveDroppingBase
    performGC
    performGC
    d <- TS.discount c 5.0 False
    checkEq "derived curve outlives its dropped base" refSpreaded d

  -- Check 2: same, but through a real consumer -- a DiscountingSwapEngine, which stores
  -- Handle<YieldTermStructure> discountCurve_ by value. This is the shape every curve
  -- consumer in the codebase has.
  refNpv <- swapNpvWith =<< mkCurve 0.02
  do
    e <- discountingSwapEngineDroppingCurve 0.02
    performGC
    performGC
    v <- swapNpvWithEngine e
    checkEq "engine outlives its dropped curve" refNpv v

  -- Check 3: a negative control for checks 1 and 2. If the curve were somehow *not*
  -- reaching the consumer -- e.g. a stale build where the two halves disagree about the
  -- parameter type -- both checks above could pass on a coincidence. A different rate must
  -- give a different NPV.
  other <- swapNpvWith =<< mkCurve 0.05
  checkWith "a different curve gives a different NPV"
            "2% and 5% flat curves must not price the same"
            (abs (refNpv - other) > 1.0)

  putStrLn "liveness: all checks passed"

-- |Build a curve, hand it to an engine, return only the engine.
discountingSwapEngineDroppingCurve :: Double -> IO PricingEngine
discountingSwapEngineDroppingCurve r = do
  c <- mkCurve r
  discountingSwapEngine c Nothing Nothing Nothing

swapNpvWith :: TS.YieldTermStructure -> IO Double
swapNpvWith c = swapNpvWithEngine =<< discountingSwapEngine c Nothing Nothing Nothing

swapNpvWithEngine :: PricingEngine -> IO Double
swapNpvWithEngine e = do
  s <- mkSwap
  setPricingEngine s e
  npv s

mkSwap :: IO VanillaSwap
mkSwap = do
  cal <- calendar TARGET
  settle <- advance cal valueDate (2, Days) Following False
  let maturity = 11 `december` 2017
  fixedDC <- dayCounter Thirty360European
  floatDC <- dayCounter (Actual360 False)
  fwd <- mkCurve 0.03
  idx <- IR.iborIndex IR.Euribor6M (Just fwd)
  fixedSch <- schedule (Just settle) maturity (1, Years) cal Unadjusted Unadjusted
    Forward False Nothing Nothing
  floatSch <- schedule (Just settle) maturity (6, Months) cal ModifiedFollowing
    ModifiedFollowing Forward False Nothing Nothing
  vanillaSwap Payer 1000000 fixedSch 0.02 fixedDC floatSch idx 0 floatDC Nothing Nothing

-- ---------------------------------------------------------------- growth

-- |Build and drop N curves, derived curves and engines, collecting periodically. Each
-- iteration allocates: a curve (Handle + Link), a derived curve holding a copy of it, an
-- engine holding another copy, and the upcast intermediates the marshallers create and
-- free. Nothing is retained across iterations, so a correct implementation must be flat
-- in N; growth means a Link is never freed, or a cycle keeps one alive.
growthLoop :: Int -> IO ()
growthLoop n = do
  forM_ [1 .. n] $ \i -> do
    base <- mkCurve (0.02 + fromIntegral (i `mod` 7) * 1.0e-4)
    spread <- simpleQuote 0.0
    derived <- TS.forwardSpreadedTermStructure base spread
    _ <- TS.discount derived 5.0 False
    e <- discountingSwapEngine derived Nothing Nothing Nothing
    _ <- swapNpvWithEngine e
    when (i `mod` 100 == 0) performGC
  performGC
  performGC
  putStrLn ("growth loop: completed " ++ show n ++ " iterations")

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
