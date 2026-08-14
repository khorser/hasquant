-- Smoke test: BlackVarianceSurface's 2-D interpolator actually reaches QuantLib.
--
-- The C++ shim casts the Haskell enum straight to a dispatch index and calls
-- BlackVarianceSurface::setInterpolation<Interpolator>(); nothing in the type system or the
-- build catches a wrong enum value or an ignored parameter, and both interpolators reproduce
-- the input vol matrix *exactly* at its own (date, strike) nodes -- so an on-node check would
-- pass no matter what. This prices the same European option off two surfaces built from
-- identical inputs, at an expiry and a strike strictly *between* grid nodes, and asserts the
-- NPVs differ. Same shape as CheckInflation.hs's Flat-vs-Linear check.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckBlackVarianceSurface.hs -o /tmp/checkbvs -outputdir /tmp/checkbvs_build && /tmp/checkbvs
import Control.Monad (forM)

import QuantLib.Instrument (setPricingEngine, npv)
import QuantLib.Instrument.Option
import QuantLib.InterestRate (Compounding(..))
import QuantLib.Math (Matrix, realMatrix, Interpolation2D(..))
import QuantLib.PricingEngine (analyticEuropeanEngine)
import QuantLib.Process (blackScholesProcess, ProcessDiscretization(..))
import QuantLib.Quote (simpleQuote)
import QuantLib.Settings (setEvaluationDate)
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield (flatForward)
import QuantLib.Time.Calendar (calendar, CalendarConstructor(..))
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))

import SmokeCheck (checkWith, report)

refDate :: Day
refDate = 15 `january` 2024

-- Expiry pillars and strike pillars of the vol surface. The option below sits between both.
expiries :: [Day]
expiries = [15 `january` 2025, 15 `january` 2026, 15 `january` 2027]

strikes :: [Double]
strikes = [80, 100, 120]

-- Deliberately curved along both axes -- a surface that is affine in either direction is
-- reproduced identically by bilinear and bicubic, which would make the check vacuous.
-- Rows are strikes, columns are expiries (QuantLib's BlackVarianceSurface convention).
volMatrix :: Matrix Double
volMatrix = either error id $ realMatrix 3 3
  [ 0.30, 0.26, 0.24
  , 0.20, 0.18, 0.17
  , 0.28, 0.25, 0.23
  ]

-- Off-node on both axes: halfway between the first two expiries, halfway between the first
-- two strikes.
optionExpiry :: Day
optionExpiry = 15 `july` 2025

optionStrike :: Double
optionStrike = 90

npvUnder :: Interpolation2D -> IO Double
npvUnder interp = do
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  surf <- blackVarianceSurface refDate cal expiries strikes volMatrix dc
            BlackVarianceSurfaceInterpolatorDefaultExtrapolation
            BlackVarianceSurfaceInterpolatorDefaultExtrapolation
            interp
  spot <- simpleQuote 100.0
  rfQ <- simpleQuote 0.03
  rf <- flatForward refDate rfQ dc Continuous Annual
  proc' <- blackScholesProcess spot rf surf EulerDiscretization False
  opt <- vanillaOption (PlainVanilla $ PlainVanillaPayoff Call optionStrike)
                       (European $ EuropeanExercise optionExpiry)
  analyticEuropeanEngine proc' Nothing >>= setPricingEngine opt
  npv opt

main :: IO ()
main = do
  setEvaluationDate (Just refDate)
  [bilinear, bicubic] <- forM [Bilinear, Bicubic] npvUnder
  report "Bilinear NPV" bilinear
  report "Bicubic NPV" bicubic
  -- Both must be sane prices, not NaN/zero from a surface that failed to interpolate.
  checkWith "both NPVs positive" "each > 0" (bilinear > 0 && bicubic > 0)
  -- The whole point: the interpolator argument must change the result off-node. A relative
  -- gap this size is far above FP noise, so a silently-ignored parameter fails loudly.
  checkWith "Bilinear /= Bicubic off-node"
            "relative difference > 1e-4"
            (abs (bilinear - bicubic) / bilinear > 1e-4)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
