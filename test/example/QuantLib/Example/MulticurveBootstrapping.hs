-- Port of QuantLib's Examples/MulticurveBootstrapping/MulticurveBootstrapping.cpp.
--
-- Two curves, bootstrapped in sequence: an EONIA discount curve from deposits, dated
-- and undated OIS; then a Euribor 6M forecast curve from a deposit, FRAs and swaps
-- whose helpers discount off the EONIA curve. Two swaps are then priced on the pair.
--
-- The point of the port is that multi-curve bootstrapping needs no relinking at all,
-- which is what settles issue #1's "probably would need RelinkableHandle first". Upstream
-- holds both curves in RelinkableHandles but only ever calls linkTo once each, right after
-- its curve is bootstrapped -- semantically just a plain handle over that curve, which is
-- what every curve-taking binding here already builds. Relinking as an actual capability
-- is a separate feature, exercised by the "relinkable handles" block in
-- main/test/QuantLib/Spec/TermStructure.hs.
--
-- Two deliberate divergences from upstream:
--  * The bootstrap accuracy argument (upstream passes 1.0e-15 via an explicit
--    bootstrap_type) is not bound, so this runs at IterativeBootstrap's default 1e-12.
--    Expected values below are therefore recorded from an actual run of this code, not
--    copied from upstream's printed output.
--  * enableExtrapolation() has no binding (it would be a setter), so both curves are
--    built through piecewiseYieldCurve', which takes extrapolation as a construction
--    argument. Passing settlementDays 0 and 2 reproduces upstream's two reference
--    dates -- todaysDate for EONIA, settlementDate for Euribor 6M.
module QuantLib.Example.MulticurveBootstrapping
  (
    Result(..)
  , SwapResult(..)
  , run
  ) where
import Control.Monad(forM)
import Data.Time.Calendar(addGregorianYearsClip)
import Data.List.NonEmpty(fromList)

import QuantLib.Math
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings(setEvaluationDate)

data SwapResult = SwapResult { swapNpv :: Double
                             , swapFairSpread :: Double
                             , swapFairRate :: Double
                             } deriving Show

data Result = Result { spot5Y :: SwapResult
                     , forward1Y5Y :: SwapResult
                     -- Same two swaps, but with the Euribor helpers given no
                     -- discounting curve, so the forecast curve is bootstrapped
                     -- single-curve. A negative control: if these matched the dual
                     -- curve figures, the EONIA curve would not actually be reaching
                     -- the helpers and the whole example would prove nothing.
                     , singleCurveSpot5Y :: SwapResult
                     } deriving Show

todaysDate :: Day
todaysDate = 11 `december` 2012

run :: IO Result
run = do
  cal <- calendar TARGET
  setEvaluationDate (Just todaysDate)
  settlementDate <- advance cal todaysDate (2, Days) Following False

  termStructureDC <- dayCounter Actual365FixedStandard
  depositDC <- dayCounter (Actual360 False)
  fixedLegDC <- dayCounter Thirty360European

  -- EONIA curve: deposits, short OIS, dated OIS, long OIS
  eonia <- IR.overnightIborIndex IR.Eonia Nothing

  depoHelpers <- forM depoQuotes $ \(settlDays, rate) -> do
    q <- simpleQuote rate
    TS.depositRateHelper q (1, Days) settlDays cal Following False depositDC

  oisHelpers <- forM (shortOisQuotes ++ longOisQuotes) $ \(tenor, rate) -> do
    q <- simpleQuote rate
    TS.oisRateHelper 2 tenor q eonia (Nothing :: Maybe TS.YieldTermStructure)
      >>= TS.asRateHelper

  datedOisHelpers <- forM datedOisQuotes $ \(start, end, rate) -> do
    q <- simpleQuote rate
    TS.oisRateHelper' start end q eonia (Nothing :: Maybe TS.YieldTermStructure)
      >>= TS.asRateHelper

  eoniaCurve <- TS.piecewiseYieldCurve' 0 cal (fromList (depoHelpers ++ oisHelpers ++ datedOisHelpers))
    termStructureDC [] TS.Discount monotonicLogCubic True

  -- Euribor 6M curve: one deposit, FRAs, and swaps discounted off the EONIA curve
  euribor6M <- IR.iborIndex IR.Euribor6M Nothing

  let euriborHelpers discounting = do
        d6MQuote <- simpleQuote 0.00312
        d6M <- TS.depositRateHelper d6MQuote (6, Months) 3 cal Following False depositDC
        fras <- forM fraQuotes $ \(monthsToStart, rate) -> do
          q <- simpleQuote rate
          TS.fraRateHelper q monthsToStart (monthsToStart + 6) 2 cal ModifiedFollowing
            False depositDC TS.LastRelevantDate Nothing True
        swaps <- forM swapQuotes $ \(yrs, rate) -> do
          q <- simpleQuote rate
          TS.swapRateHelper' q (yrs, Years) cal Annual Unadjusted fixedLegDC euribor6M
            Nothing (0, Days) discounting
            Nothing TS.LastRelevantDate Nothing False Nothing Nothing Nothing
            >>= TS.asRateHelper
        pure (d6M : fras ++ swaps)

  dualHelpers <- euriborHelpers (Just eoniaCurve)
  euriborCurve <- TS.piecewiseYieldCurve' 2 cal (fromList dualHelpers) termStructureDC []
    TS.Discount monotonicLogCubic True

  -- the negative control: same helpers, no discounting curve
  singleHelpers <- euriborHelpers (Nothing :: Maybe TS.YieldTermStructure)
  singleCurve <- TS.piecewiseYieldCurve' 2 cal (fromList singleHelpers) termStructureDC []
    TS.Discount monotonicLogCubic True

  let priceOn forecastCurve start = do
        idx <- IR.iborIndex IR.Euribor6M (Just forecastCurve)
        let maturity = addGregorianYearsClip 5 start
        fixedSch <- schedule (Just start) maturity (1, Years) cal Unadjusted Unadjusted
          Forward False Nothing Nothing
        floatSch <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing
          ModifiedFollowing Forward False Nothing Nothing
        swp <- vanillaSwap Payer 1000000 fixedSch 0.007 fixedLegDC floatSch idx 0
          depositDC Nothing Nothing
        engine <- discountingSwapEngine eoniaCurve Nothing Nothing Nothing
        setPricingEngine swp engine
        SwapResult <$> npv swp <*> fairSpread swp <*> fairRate swp

  fwdStart <- advance cal settlementDate (1, Years) Following False

  Result
    <$> priceOn euriborCurve settlementDate
    <*> priceOn euriborCurve fwdStart
    <*> priceOn singleCurve settlementDate

-- QuantLib's MonotonicLogCubic: LogCubic(Spline, monotonic=true, SecondDerivative 0
-- at both ends), which is exactly what cbits/qlTermStructure.cpp emits for this pair.
monotonicLogCubic :: Interpolation
monotonicLogCubic = LogCubic (NaturalSpline True)

depoQuotes :: [(Word, Double)]  -- settlement days, rate
depoQuotes = [(0, 0.0004), (1, 0.0004), (2, 0.0004)]

shortOisQuotes :: [((Int, TimeUnit), Double)]
shortOisQuotes =
  [ ((1, Weeks), 0.00070), ((2, Weeks), 0.00069)
  , ((3, Weeks), 0.00078), ((1, Months), 0.00074) ]

datedOisQuotes :: [(Day, Day, Double)]
datedOisQuotes =
  [ (16 `january` 2013, 13 `february` 2013,  0.000460)
  , (13 `february` 2013, 13 `march` 2013,    0.000160)
  , (13 `march` 2013, 10 `april` 2013,      -0.000070)
  , (10 `april` 2013, 8 `may` 2013,         -0.000130)
  , (8 `may` 2013, 12 `june` 2013,          -0.000140) ]

longOisQuotes :: [((Int, TimeUnit), Double)]
longOisQuotes =
  [ ((15, Months), 0.00002), ((18, Months), 0.00008), ((21, Months), 0.00021)
  , ((2, Years), 0.00036), ((3, Years), 0.00127), ((4, Years), 0.00274)
  , ((5, Years), 0.00456), ((6, Years), 0.00647), ((7, Years), 0.00827)
  , ((8, Years), 0.00996), ((9, Years), 0.01147), ((10, Years), 0.01280)
  , ((11, Years), 0.01404), ((12, Years), 0.01516), ((15, Years), 0.01764)
  , ((20, Years), 0.01939), ((25, Years), 0.02003), ((30, Years), 0.02038) ]

fraQuotes :: [(Word, Double)]  -- months to start
fraQuotes =
  [ (1, 0.002930), (2, 0.002720), (3, 0.002600), (4, 0.002560), (5, 0.002520)
  , (6, 0.002480), (7, 0.002540), (8, 0.002610), (9, 0.002670), (10, 0.002790)
  , (11, 0.002910), (12, 0.003030), (13, 0.003180), (14, 0.003350)
  , (15, 0.003520), (16, 0.003710), (17, 0.003890), (18, 0.004090) ]

swapQuotes :: [(Int, Double)]  -- years
swapQuotes =
  [ (3, 0.004240), (4, 0.005760), (5, 0.007620), (6, 0.009540), (7, 0.011350)
  , (8, 0.013030), (9, 0.014520), (10, 0.015840), (12, 0.018090), (15, 0.020370)
  , (20, 0.021870), (25, 0.022340), (30, 0.022560), (35, 0.022950)
  , (40, 0.023480), (50, 0.024210), (60, 0.024630) ]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
