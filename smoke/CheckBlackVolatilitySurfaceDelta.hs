-- Smoke test: construct BlackVolatilitySurfaceDelta with two different
-- SmileInterpolationMethod values (SmileLinear vs CubicSpline) from identical
-- inputs, and confirm the resulting smiles actually diverge numerically at a
-- non-grid strike -- not just that both constructors succeed. Guards against
-- SmileInterpolationMethod's (or BlackVolTimeExtrapolationType's) C enum values
-- being silently mis-numbered/aliased in cbits/qlEnumC2HS.h, per CLAUDE.md's
-- enum-mirroring rule (see smoke/CheckInflation.hs's Flat-vs-Linear check for
-- the same shape of guard).
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckBlackVolatilitySurfaceDelta.hs -o /tmp/checkbvsd -outputdir /tmp/checkbvsd_build && /tmp/checkbvsd
import qualified QuantLib.InterestRate as IR
import qualified QuantLib.Quote as Quote
import QuantLib.Math(realMatrix)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Yield(flatForward')
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..), TimeUnit(..))

import SmokeCheck (checkWith)

main :: IO ()
main = do
  setEvaluationDate $ Just refDate
  dc <- dayCounter ActualActualISDA
  cal <- calendar TARGET
  spot <- Quote.simpleQuote 1.18
  dtsQ <- Quote.simpleQuote 0.02
  dts <- flatForward' 0 cal dtsQ dc IR.Continuous Annual
  ftsQ <- Quote.simpleQuote 0.035
  fts <- flatForward' 0 cal ftsQ dc IR.Continuous Annual
  d1M <- addPeriod refDate (1, Months)
  d6M <- addPeriod refDate (6, Months)
  d1Y <- addPeriod refDate (1, Years)
  d2Y <- addPeriod refDate (2, Years)
  let vols = either error id $ realMatrix 4 3
        [ 0.15, 0.13, 0.135
        , 0.14, 0.11, 0.125
        , 0.13, 0.10, 0.12
        , 0.125, 0.095, 0.115
        ]
      linearOpts = Vol.defaultBlackVolatilitySurfaceDeltaOpts
      cubicOpts = linearOpts { Vol.bvsdInterpolationMethod = Vol.CubicSpline }
  surfaceLinear <- Vol.blackVolatilitySurfaceDeltaFull refDate [d1M, d6M, d1Y, d2Y] [-0.25] [0.25] True vols
                     dc cal spot dts fts linearOpts
  surfaceCubic <- Vol.blackVolatilitySurfaceDeltaFull refDate [d1M, d6M, d1Y, d2Y] [-0.25] [0.25] True vols
                     dc cal spot dts fts cubicOpts
  -- an off-grid strike at 6M, where the two interpolation schemes have room to disagree
  smileLinear <- Vol.blackVolSmile' surfaceLinear d6M
  smileCubic <- Vol.blackVolSmile' surfaceCubic d6M
  volLinear <- Vol.smileSectionVolatility smileLinear offGridStrike
  volCubic <- Vol.smileSectionVolatility smileCubic offGridStrike
  putStrLn ("SmileLinear vol = " ++ show volLinear ++ ", CubicSpline vol = " ++ show volCubic)
  checkWith "SmileLinear vs CubicSpline smile"
    "vols are identical (equality means SmileInterpolationMethod's mapping may be stale)"
    (volLinear /= volCubic)
  where
    refDate = 1 `january` 2010
    offGridStrike = 1.15
