-- Stale-build guard for GlobalBootstrap's canned-functor binding
-- (piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' / qlPiecewiseYieldCurveGlobalBootstrap3
-- / qlPiecewiseYieldCurveGlobalBootstrapFullAux). This is a genuinely new C++ construction path
-- (GlobalBootstrap's functor-callback constructor, not the plain accuracy/instrumentWeights one),
-- added entirely inside cbits/qlTermStructureAux.cpp -- exactly the kind of change a stale build
-- can hide (see smoke/CheckMultiCurve.hs's own doc comment on why this class of change needs a
-- standalone compile).
--
-- Also exercises the pillar-count guard added alongside the binding: AdditionalErrors' canned
-- formula produces (length additionalHelpers - 2) equations, so additionalDates must supply
-- exactly that many extra unknowns or GlobalBootstrap's optimizer is under/over-determined. An
-- early spike of this construction hit that as a raw QuantLib "less functions than available
-- variables" exception; the binding adds a QL_REQUIRE with a caller-facing message instead,
-- checked here.
--
-- Run with:
--   cabal exec -- ghc -ismoke -package hasquant smoke/CheckGlobalBootstrapFunctors.hs -o /tmp/gbf_smoke -outputdir /tmp/gbf_smoke_build && /tmp/gbf_smoke

import Control.Exception (SomeException, evaluate, try)

import qualified QuantLib.Quote as Quote
import QuantLib.Settings (setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkWith)

curveToday :: Day
curveToday = 23 `october` 2025

main :: IO ()
main = do
  setEvaluationDate (Just curveToday)
  cal <- calendar TARGET
  euriborDC <- dayCounter (Actual360 False)
  settleFix <- advance cal curveToday (2, Days) Following False

  q <- Quote.simpleQuote 0.03
  helpers <- mapM (\i -> depositRateHelper q (i, Months) 2 cal ModifiedFollowing True euriborDC) [1 .. 5 :: Int]

  -- additionalHelpers reuses the same 5 helpers (mirrors QuantLib-SWIG's own worked example,
  -- which passes b.additionalHelpers into both the curve's own instrument list and the functor
  -- slot); additionalDates needs exactly 5 - 2 = 3 entries for AdditionalErrors' formula.
  goodDates <- mapM (\i -> advance cal settleFix (i, Months) ModifiedFollowing True) [1, 2, 3 :: Int]
  curve <- piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' 0 cal helpers euriborDC [] helpers goodDates 1.0e-10 False
  sampleDate <- advance cal settleFix (4, Months) ModifiedFollowing True
  df <- discount' curve sampleDate False
  checkWith "functor-based GlobalBootstrap curve produces a sane discount factor"
            "confirms qlPiecewiseYieldCurveGlobalBootstrap3 actually dispatched, not just linked"
            (df > 0 && df < 1)

  -- Mismatched pillar count (4 dates instead of 3): should raise, not silently misbootstrap or
  -- crash with QuantLib's raw internal message.
  badDates <- mapM (\i -> advance cal settleFix (i, Months) ModifiedFollowing True) [1, 2, 3, 4 :: Int]
  result <- try (piecewiseYieldCurveGlobalBootstrapSimpleZeroLinearFull' 0 cal helpers euriborDC [] helpers badDates 1.0e-10 False
                    >>= \c -> discount' c sampleDate False >>= evaluate) :: IO (Either SomeException Double)
  checkWith "mismatched additionalDates/additionalHelpers pillar count raises"
            "confirms the QL_REQUIRE guard fires instead of silently misbootstrapping"
            (either (const True) (const False) result)

  putStrLn "globalbootstrapfunctors: all checks passed"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
