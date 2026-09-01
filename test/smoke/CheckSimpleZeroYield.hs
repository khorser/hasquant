-- Enum guard for the SimpleZeroYield BootstrapTrait case.
--
-- CLAUDE.md's CPIInterpolationType incident: a new enum case silently renumbered to alias an
-- existing one's C-level value shipped undetected for a full session, with a clean build and
-- passing test suite -- neither catches a mis-numbered enum, only a value-level check that the
-- new case actually behaves differently from an existing one does. SimpleZeroYield is a fourth
-- BootstrapTrait case (cbits/qlEnumObjects.h) consumed only inside a C++ if/else-if
-- (qlPiecewiseYieldCurveAux1, cbits/qlTermStructureAux.cpp) -- exactly the kind of change a
-- stale build can hide (editing a header without touching a .chs leaves cabal/stack silently
-- stale, per smoke/CheckMultiCurve.hs's own doc comment).
--
-- Run with:
--   cabal exec -- ghc -ismoke -package hasquant smoke/CheckSimpleZeroYield.hs -o /tmp/zy_smoke -outputdir /tmp/zy_smoke_build && /tmp/zy_smoke

import Data.List.NonEmpty(fromList)
import qualified QuantLib.Quote as Quote
import QuantLib.Settings(setEvaluationDate)
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

  q <- Quote.simpleQuote 0.03
  helpers <- mapM (\i -> fraRateHelper q i (i + 3) 2 cal ModifiedFollowing True euriborDC LastRelevantDate Nothing False) [1 .. 5]

  discountCurve <- piecewiseYieldCurveGlobalBootstrap' 0 cal (fromList helpers) euriborDC [] 1.0e-10 [] False
  helpers2 <- mapM (\i -> fraRateHelper q i (i + 3) 2 cal ModifiedFollowing True euriborDC LastRelevantDate Nothing False) [1 .. 5]
  zeroCurve <- piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear' 0 cal (fromList helpers2) euriborDC [] 1.0e-10 [] False

  -- A date strictly between two pillars: the two curves reprice the input instruments
  -- identically at the pillar dates themselves, but interpolate between them differently
  -- (log-linear discount vs. linear zero yield), so a mid-pillar discount factor is where the
  -- two constructions are actually distinguishable -- proof SimpleZeroYield's branch dispatched
  -- to a genuinely different CurveType, not a mis-numbered alias of Discount's.
  midPillar <- advance cal curveToday (75, Days) ModifiedFollowing True
  dDiscount <- discount' discountCurve midPillar False
  dZero <- discount' zeroCurve midPillar False

  checkWith "SimpleZeroYield GlobalBootstrap curve produces a sane discount factor"
            "confirms qlPiecewiseYieldCurveGlobalBootstrap2 actually dispatched, not just linked"
            (dZero > 0 && dZero < 1)
  checkWith "SimpleZeroYield and Discount GlobalBootstrap curves disagree between pillars"
            "confirms the SimpleZeroYield enum case isn't silently aliasing Discount's numeric value"
            (abs (dDiscount - dZero) > 1.0e-8)

  putStrLn "simplezeroyield: all checks passed"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
