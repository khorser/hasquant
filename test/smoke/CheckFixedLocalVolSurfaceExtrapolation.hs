-- Smoke test: FixedLocalVolSurface::Extrapolation actually reaches QuantLib.
--
-- The C++ shim casts the Haskell enum straight to a dispatch index; nothing in the type system
-- or the build catches a wrong enum value. ConstantExtrapolation and
-- InterpolatorDefaultExtrapolation agree everywhere *inside* the strike grid (both reproduce the
-- interpolated surface there), so an in-grid query would pass no matter how the enum is wired --
-- this queries a strike strictly *above* the grid's maximum strike, where the two diverge, and
-- asserts the local vols differ. Same shape as CheckBlackVarianceSurface.hs's off-node check.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckFixedLocalVolSurfaceExtrapolation.hs -o /tmp/checkflvs -outputdir /tmp/checkflvs_build && /tmp/checkflvs
import Control.Monad (forM)

import QuantLib.Math (Matrix, realMatrix)
import QuantLib.TermStructure.Volatility
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..))

import SmokeCheck (checkWith, report)

refDate :: Day
refDate = 15 `january` 2024

dates :: [Day]
dates = [15 `january` 2025, 15 `january` 2026, 15 `january` 2027]

strikes :: [Double]
strikes = [80, 100, 120]

-- Deliberately curved along both axes -- an affine surface would extrapolate identically under
-- either scheme, which would make the check vacuous.
localVolMatrix :: Matrix Double
localVolMatrix = either error id $ realMatrix 3 3
  [ 0.30, 0.26, 0.24
  , 0.20, 0.18, 0.17
  , 0.28, 0.25, 0.23
  ]

-- Above the top of the strike grid (120), where Constant vs InterpolatorDefault diverge.
offGridStrike :: Double
offGridStrike = 200

-- Inside the date range so only the strike axis is being probed off-grid.
queryDate :: Day
queryDate = 15 `july` 2025

localVolUnder :: FixedLocalVolSurfaceExtrapolation -> IO Double
localVolUnder extrap = do
  dc <- dayCounter Actual365FixedStandard
  surf <- fixedLocalVolSurface refDate dates strikes localVolMatrix dc extrap extrap
  localVol surf queryDate offGridStrike True

main :: IO ()
main = do
  [constant, interpDefault] <- forM
    [FixedLocalVolSurfaceConstantExtrapolation, FixedLocalVolSurfaceInterpolatorDefaultExtrapolation]
    localVolUnder
  report "Constant extrapolation local vol" constant
  report "InterpolatorDefault extrapolation local vol" interpDefault
  checkWith "Constant /= InterpolatorDefault off-grid"
            "relative difference > 1e-4"
            (abs (constant - interpDefault) / constant > 1e-4)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
