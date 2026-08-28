-- Smoke test for Instrument::additionalResults() (qlInstrumentAdditionalResults /
-- qlFreeAdditionalResults in cbits, and the c2hs marshalling in QuantLib/Instrument.chs).
--
-- QuantLib stores the map as ext::any; the shim projects each value into Real / std::string /
-- vector<Real> / "unknown" (RTTI name) shapes and strdup's/heap-allocates every key, sval, and
-- varr buffer. The whole array plus those buffers are released through qlFreeAdditionalResults.
-- This checks the marshalling end-to-end and, run under the trackAllocations flag, that those
-- allocations are all freed (no leak / no double free). A stale C++ build would silently serve the
-- old object with no additionalResults binding, so a value-level assertion is the only thing that
-- catches it.
--
-- Two real QuantLib 1.43 engines exercise three of the four discriminants: the Bjerksund-
-- Stensland American option engine writes exerciseType (std::string -> StringVal) and
-- strikeGamma (Real -> RealVal); the Black cap/floor engine writes optionletsPrice as a
-- vector<Real> -> RealVectorVal. No shipped 1.43 engine stores a type this binding can't name
-- (checked via `grep additionalResults\[ ~/Src/QuantLib/ql/`), so the fourth discriminant
-- (Unsupported, the RTTI-name fallback) isn't exercised here -- its C++ side is a trivial,
-- visibly-correct `else`, and its Haskell side is a compiler-checked exhaustive `case`.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckAdditionalResults.hs -o /tmp/checkar -outputdir /tmp/checkar_build && /tmp/checkar
--
-- Caught as SomeException, deliberately, not as QuantLib.Type.Error: a smoke script is compiled
-- standalone with `-ismoke` from the repo root, so ghc compiles QuantLib/Type.hs from source
-- rather than taking it from the installed package. The local `Error` is then a *different* type
-- from the one the library throws, and `try` silently never matches -- the exception sails past
-- and the script dies with the very message it was meant to catch. Don't "improve" this to a typed
-- catch. Also don't inline the `SomeException` pattern annotation at the `case` site (`Left (e ::
-- SomeException) -> ...`) -- that needs ScopedTypeVariables, which this file doesn't enable; give
-- `run` a type signature instead, same as smoke/CheckIterativeBootstrap.hs's `attempt`.
{-# LANGUAGE TemplateHaskell #-}
import Control.Exception (try, SomeException)

import qualified Data.HashMap.Strict as HM
import Data.Time.Calendar (fromGregorian)

import QuantLib.Instrument
import QuantLib.Instrument.CapFloor
import QuantLib.Instrument.Option
import QuantLib.CashFlow hiding(npv)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor6M))
import QuantLib.Math
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Syntax
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import QuantLib.InterestRate

import SmokeCheck (checkEq, checkWith)

main :: IO ()
main = do
  res <- run
  case res of
    Left e -> do
      putStrLn ("FAIL: " ++ show e)
      error "CheckAdditionalResults failed"
    Right () -> putStrLn "OK   CheckAdditionalResults passed"

run :: IO (Either SomeException ())
run = try (bjerksundStenslandCheck >> capFloorCheck)

bjerksundStenslandCheck :: IO ()
bjerksundStenslandCheck = do
  setEvaluationDate $ Just (fromGregorian 1998 5 15)
  dc <- dayCounter Actual365FixedStandard
  let evalDate = 17 `may` 1998
      maturity = 17 `may` 1999
      under = 36
      strike = 40
      dividend = 0.0
      riskFreeRate = 0.06
      vol = 0.20
      optType = Put
  underQ <- simpleQuote under
  riskFreeQ <- simpleQuote riskFreeRate
  ts <- flatForward evalDate riskFreeQ dc Continuous Annual
  divQ <- simpleQuote dividend
  divTS <- flatForward evalDate divQ dc Continuous Annual
  volQ <- simpleQuote vol
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) evalDate volQ dc
  let payoff = PlainVanilla $ PlainVanillaPayoff optType strike
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False
  americanOpt <- vanillaOption payoff (American Nothing maturity False)

  -- Price with the Bjerksund-Stensland engine, then read the results.
  bjs <- bjerksundStenslandApproximationEngine bsmProc
  QuantLib.Instrument.setPricingEngine americanOpt bjs
  _ <- npv americanOpt

  addl <- HM.fromList <$> additionalResults americanOpt
  putStrLn $ "additionalResults keys (Bjerksund-Stensland): " ++ show (HM.keys addl)

  -- The engine writes exerciseType = "American" (std::string -> StringVal).
  checkEq "additionalResults exerciseType"
    (Just (StringVal "American"))
    (HM.lookup "exerciseType" addl)

  -- It also writes strikeGamma (Real -> RealVal); sanity-check it is present and positive.
  case HM.lookup "strikeGamma" addl of
    Just (RealVal g) -> checkWith "additionalResults strikeGamma > 0" "positive" (g > 0)
    other -> checkWith "additionalResults strikeGamma" ("present as RealVal, got " ++ show other) False

  checkWith "additionalResults non-empty" "at least one entry" (HM.size addl > 0)

capFloorCheck :: IO ()
capFloorCheck = do
  let today = 11 `december` 2012
  setEvaluationDate (Just today)
  cal <- calendar TARGET
  settle <- advance cal today (2, Days) Following False
  discQ <- simpleQuote 0.02
  dc <- dayCounter Actual365FixedStandard
  discountTS <- flatForward today discQ dc Continuous Annual
  idx <- iborIndex Euribor6M (Just discountTS)
  floatDC <- dayCounter (Actual360 False)
  floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
    ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  leg <- iborLeg floatSch idx [1000000] floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
  capfl <- cap leg [0.03]
  volQ <- simpleQuote 0.20
  vol0 <- constantOptionletVolatility today cal ModifiedFollowing volQ dc ShiftedLognormal 0
  eng <- blackCapFloorEngine' discountTS vol0
  QuantLib.Instrument.setPricingEngine capfl eng
  _ <- npv capfl

  addl <- HM.fromList <$> additionalResults capfl
  putStrLn $ "additionalResults keys (Black cap/floor): " ++ show (HM.keys addl)

  -- The engine writes optionletsPrice as a vector<Real> -> RealVectorVal; exercises the vector
  -- marshalling branch (varr/vlen) that the Bjerksund-Stensland check above never touches.
  case HM.lookup "optionletsPrice" addl of
    Just (RealVectorVal xs) -> do
      checkWith "additionalResults optionletsPrice non-empty" "at least one element" (not (null xs))
      checkWith "additionalResults optionletsPrice non-negative" "all >= 0" (all (>= 0) xs)
    other -> checkWith "additionalResults optionletsPrice" ("present as RealVectorVal, got " ++ show other) False
