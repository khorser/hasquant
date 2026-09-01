-- Smoke test: IterativeBootstrapOpts' settings actually reach QuantLib's IterativeBootstrap.
--
-- The nine fields are marshalled as plain scalars through qlPiecewiseYieldCurveFull1 into a
-- POD struct and on into CurveType::bootstrap_type(...). Nothing in the build catches a field
-- dropped, transposed, or silently ignored -- a curve built with the wrong settings still
-- bootstraps and still returns plausible discount factors, so the pinned curve tests in
-- main/test/ would stay green. This drives a failure deliberately with one knob
-- (ibMaxEvaluations = 1, far below what Brent needs to bracket a root) and suppresses it with
-- another (ibDontThrow), so two settings have to be threaded correctly for it to pass.
--
-- QuantLib bootstraps curves lazily: constructing one never throws, the first `discount` call
-- does. Every check below therefore reads a discount factor rather than just building a curve.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckIterativeBootstrap.hs -o /tmp/checkib -outputdir /tmp/checkib_build && /tmp/checkib
import Control.Exception (try, evaluate, SomeException)
import Data.List.NonEmpty(fromList)

import QuantLib.Math (Interpolation(..))
import qualified QuantLib.Quote as Quote
import QuantLib.Settings (setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule


import SmokeCheck (checkWith, report)

curveToday :: Day
curveToday = 23 `october` 2025

-- A small, entirely ordinary deposit curve -- it bootstraps fine under upstream's defaults.
-- The point is what the *settings* do to it, not the curve itself.
buildCurve :: IterativeBootstrapOpts -> IO YieldTermStructure
buildCurve opts = do
  cal <- calendar TARGET
  dc <- dayCounter (Actual360 False)
  q <- Quote.simpleQuote 0.03
  helpers <- mapM (\n -> depositRateHelper q (n, Months) 2 cal ModifiedFollowing False dc)
                  [1, 3, 6, 12]
  piecewiseYieldCurveFull' 0 cal (fromList helpers) dc [] Discount Linear opts False

-- Force the lazy bootstrap and report whether it survived. The `try` spans construction as
-- well as the discount call: which of the two a failing bootstrap surfaces from is
-- QuantLib's business, not something this check should pin.
--
-- Caught as SomeException, deliberately, not as QuantLib.Type.Error: a smoke script is
-- compiled standalone with `-ismoke` from the repo root, so ghc compiles QuantLib/Type.hs
-- from source rather than taking it from the installed package. The local `Error` is then a
-- *different* type from the one the library throws, and `try` silently never matches -- the
-- exception sails straight past and the script dies with the very message it was meant to
-- catch. Don't "improve" this to a typed catch.
attempt :: IterativeBootstrapOpts -> IO (Either SomeException Double)
attempt opts = try $ do
  cal <- calendar TARGET
  d <- advance cal curveToday (6, Months) ModifiedFollowing True
  ts <- buildCurve opts
  discount' ts d False >>= evaluate

-- SomeException's Show dumps a GHC backtrace; only the outcome matters here.
describe :: Either SomeException Double -> String
describe = either (const "threw") show

main :: IO ()
main = do
  setEvaluationDate (Just curveToday)

  -- 1. Defaults: an ordinary curve, ordinary discount factor.
  okDf <- attempt defaultIterativeBootstrapOpts
  report "default opts, 6m discount factor" (describe okDf)
  checkWith "defaults bootstrap a sane curve" "0 < df < 1"
            (either (const False) (\v -> v > 0 && v < 1) okDf)

  -- 2. ibMaxEvaluations = 1 starves the solver, which must then throw. If the field were
  --    dropped on the way to C++ this would quietly succeed and the check would fail.
  starved <- attempt defaultIterativeBootstrapOpts { ibMaxEvaluations = 1 }
  report "ibMaxEvaluations = 1" (describe starved)
  checkWith "ibMaxEvaluations reaches the solver" "bootstrap throws when starved"
            (either (const True) (const False) starved)

  -- 3. Same starved solver, but ibDontThrow substitutes the best value found so far instead
  --    of propagating the failure -- so this must come back with a number.
  rescued <- attempt defaultIterativeBootstrapOpts { ibMaxEvaluations = 1, ibDontThrow = True }
  report "ibMaxEvaluations = 1, ibDontThrow" (describe rescued)
  checkWith "ibDontThrow reaches the bootstrapper" "same starved curve returns a value"
            (either (const False) (const True) rescued)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
