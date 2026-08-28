module QuantLib.Example.InflationInstruments
  (
    Result(..)
  , run
  ) where

import Control.Monad(forM_)
import qualified QuantLib.CashFlow as CF
import QuantLib.Currency(currency, Ccy(GBP))
import QuantLib.Index(addFixing)
import qualified QuantLib.Index.InterestRate as I
import QuantLib.Index.Inflation
import QuantLib.InterestRate(Compounding(Continuous, Compounded), interestRate)
import QuantLib.Instrument
import QuantLib.Math(Interpolation(..))
import QuantLib.Instrument.Bond
import QuantLib.Instrument.Swap
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Inflation
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

-- |Two 'ZeroInflationIndex' instances sharing a name/region/currency/frequency/lag share
-- fixings via QuantLib's global @IndexManager@ (keyed by name, not per-instance) -- verified
-- with a standalone scratch check before relying on it here. This lets us build a curve from
-- an *unlinked* index (@idx0@), then construct a second, curve-linked index (@idx1@) that can
-- forecast off it, entirely sidestepping the RelinkableHandle-based bootstrap upstream tests
-- use (no @RelinkableHandle@\/@linkTo@ concept exists in hasquant -- see README.md's TODO).
data Result = Result
  { zcisNpvBeforeFairRate :: Double
  , zcisNpvAtFairRate :: Double
  , cpiSwapNpvAtFairRate :: Double
  , yoySwapNpvAtFairRate :: Double
  , cpiBondDirtyMinusCleanAccrued :: Double
  , cpiBondPriceLowInflation :: Double
  , cpiBondPriceHighInflation :: Double
  , cpiLegBondNpv :: Double
  , yoyLegSwapNpv :: Double
  } deriving Show

evalDate :: Day
evalDate = 2 `january` 2024

baseDate :: Day
baseDate = 1 `october` 2023

obsLag :: (Word, TimeUnit)
obsLag = (3, Months)

-- index availabilityLag must satisfy (swapObservationLag - indexPeriod) >= availabilityLag;
-- with a Monthly index and 3M swap observation lag, 1M availability lag is required.
obsLagI :: (Int, TimeUnit)
obsLagI = (1, Months)

maturity2Y :: Day
maturity2Y = 2 `january` 2026

maturity5Y :: Day
maturity5Y = 2 `january` 2029

flatRate :: Double
flatRate = 0.03

nominalRate :: Double
nominalRate = 0.02

nominal :: Double
nominal = 1000000.0

faceAmount :: Double
faceAmount = 100.0

couponRate :: Double
couponRate = 0.05

settlementDays :: Word
settlementDays = 2

-- |Prices the ZCIIS at its quoted rate and again at its own fair rate -- the
-- latter reprices to ~0 in one step, unlike the CPISwap refinement below.
priceZcis :: DayCounter -> Calendar -> ZeroInflationIndex -> PricingEngine -> IO (Double, Double)
priceZcis dc cal idx1 swapEngine = do
  zcis0 <- zeroCouponInflationSwap Payer nominal evalDate maturity5Y cal Unadjusted dc flatRate idx1 obsLag CPILinear False cal Following
  zcis0Inst <- asInstrument zcis0
  setPricingEngine zcis0Inst swapEngine
  npvBefore <- npv zcis0Inst
  fairZcisRate <- zcisFairRate zcis0
  zcis1 <- zeroCouponInflationSwap Payer nominal evalDate maturity5Y cal Unadjusted dc fairZcisRate idx1 obsLag CPILinear False cal Following
  zcis1Inst <- asInstrument zcis1
  setPricingEngine zcis1Inst swapEngine
  npvAtFair <- npv zcis1Inst
  return (npvBefore, npvAtFair)

-- |Context shared by every iteration of the CPISwap fair-rate refinement below.
data CpiSwapContext = CpiSwapContext
  { cpiSwapDc :: DayCounter
  , cpiSwapFloatSchedule :: Schedule
  , cpiSwapFloatIdx :: I.IborIndex
  , cpiSwapBaseCPI0 :: Double
  , cpiSwapFixedSchedule :: Schedule
  , cpiSwapIdx1 :: ZeroInflationIndex
  , cpiSwapEngine :: PricingEngine
  }

buildCpiSwap :: CpiSwapContext -> Double -> IO (CPISwap, Instrument)
buildCpiSwap ctx r = do
  s <- cpiSwap Payer nominal True 0.0 (cpiSwapDc ctx) (cpiSwapFloatSchedule ctx) Unadjusted 0
    (cpiSwapFloatIdx ctx) r (cpiSwapBaseCPI0 ctx)
    (cpiSwapDc ctx) (cpiSwapFixedSchedule ctx) Unadjusted obsLag (cpiSwapIdx1 ctx) CPILinear Nothing
  i <- asInstrument s
  setPricingEngine i (cpiSwapEngine ctx)
  _ <- npv i
  pure (s, i)

-- |Rebuilding once at @CPISwap::fairRate()@'s single-step correction leaves a
-- non-trivial residual NPV for a CPI leg (unlike ZeroCouponInflationSwap, which
-- reprices to ~0 in one step) -- iterating the correction converges it to
-- machine-epsilon scale.
refineCpiSwapRate :: CpiSwapContext -> Int -> Double -> IO (Double, Double)
refineCpiSwapRate ctx 0 r = do
  (_, i) <- buildCpiSwap ctx r
  n <- npv i
  pure (r, n)
refineCpiSwapRate ctx n r = do
  (s, _) <- buildCpiSwap ctx r
  r' <- cpiSwapFairRate s
  refineCpiSwapRate ctx (n - 1) r'

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  gbp <- currency GBP
  reg <- region' "Wonderland" "WL"

  -- unlinked index carrying only historical fixings, used to build the ZCIIS helpers
  fixingDates <- mapM (\n -> advance cal (1 `january` 2022) (n, Months) Unadjusted False) [0 .. 24 :: Int]
  idx0 <- zeroInflationIndex' "WL CPI" reg False Monthly obsLagI gbp Nothing
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing idx0 d (260.0 + i) False

  q1 <- simpleQuote flatRate
  q2 <- simpleQuote flatRate
  h1 <- zeroCouponInflationSwapHelper q1 obsLag maturity2Y cal Unadjusted dc idx0 CPILinear LastRelevantDate Nothing
  h2 <- zeroCouponInflationSwapHelper q2 obsLag maturity5Y cal Unadjusted dc idx0 CPILinear LastRelevantDate Nothing
  zeroCurve <- piecewiseZeroInflationCurve evalDate baseDate Monthly dc [h1, h2] Linear
  -- curve-linked index (same name/region/etc, picks up idx0's fixings automatically)
  idx1 <- zeroInflationIndex' "WL CPI" reg False Monthly obsLagI gbp (Just zeroCurve)

  nominalQ <- simpleQuote nominalRate
  nominalCurve <- flatForward evalDate nominalQ dc Continuous Annual
  swapEngine <- discountingSwapEngine nominalCurve Nothing Nothing Nothing
  bondEngine <- discountingBondEngine nominalCurve Nothing

  -- ZCIIS: reprices to ~0 once rebuilt at its own fair rate
  (npvBefore, npvAtFair) <- priceZcis dc cal idx1 swapEngine

  -- CPISwap: same self-consistency discipline, exercising the 19-arg shim end to end.
  floatSchedule <- schedule (Just evalDate) maturity5Y (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
  fixedSchedule <- schedule (Just evalDate) maturity5Y (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
  floatIdx <- I.iborIndex (I.GbpLibor (6, Months)) (Just nominalCurve)
  baseCPI0 <- fixing idx1 evalDate
  let cpiSwapCtx = CpiSwapContext
        { cpiSwapDc = dc
        , cpiSwapFloatSchedule = floatSchedule
        , cpiSwapFloatIdx = floatIdx
        , cpiSwapBaseCPI0 = baseCPI0
        , cpiSwapFixedSchedule = fixedSchedule
        , cpiSwapIdx1 = idx1
        , cpiSwapEngine = swapEngine
        }
  (_, cpiSwapNpv) <- refineCpiSwapRate cpiSwapCtx (15 :: Int) flatRate

  -- YoY inflation curve + swap, mirroring the same unlinked/linked-index trick
  yidx0 <- yoyInflationIndex' "WL YoY CPI" reg False Monthly obsLagI gbp Nothing
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing yidx0 d (flatRate + i * 0.0001) False
  qy1 <- simpleQuote flatRate
  qy2 <- simpleQuote flatRate
  hy1 <- yearOnYearInflationSwapHelper qy1 obsLag maturity2Y cal Unadjusted dc yidx0 CPILinear nominalCurve LastRelevantDate Nothing
  hy2 <- yearOnYearInflationSwapHelper qy2 obsLag maturity5Y cal Unadjusted dc yidx0 CPILinear nominalCurve LastRelevantDate Nothing
  yoyCurve <- piecewiseYoYInflationCurve evalDate baseDate flatRate Monthly dc [hy1, hy2] Linear
  yidx1 <- yoyInflationIndex' "WL YoY CPI" reg False Monthly obsLagI gbp (Just yoyCurve)
  yoySchedule <- schedule (Just evalDate) maturity5Y (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
  yoySwap0 <- yearOnYearInflationSwap Payer nominal fixedSchedule flatRate dc yoySchedule yidx1 obsLag CPILinear 0.0 dc cal Unadjusted
  yoySwap0Inst <- asInstrument yoySwap0
  setPricingEngine yoySwap0Inst swapEngine
  fairYoyRate <- yoyFairRate yoySwap0
  yoySwap1 <- yearOnYearInflationSwap Payer nominal fixedSchedule fairYoyRate dc yoySchedule yidx1 obsLag CPILinear 0.0 dc cal Unadjusted
  yoySwap1Inst <- asInstrument yoySwap1
  setPricingEngine yoySwap1Inst swapEngine
  yoySwapNpv <- npv yoySwap1Inst

  -- CPIBond: dirty/clean/accrued self-consistency, plus a directional inflation bump
  cpiBondSchedule <- schedule (Just evalDate) maturity5Y (6, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing
  cb <- cpiBond settlementDays faceAmount baseCPI0 obsLag idx1 CPILinear cpiBondSchedule [couponRate]
    dc Unadjusted (Just evalDate) cal (0, Days) cal Unadjusted False
  cbInst <- asBond cb >>= asInstrument
  setPricingEngine cbInst bondEngine
  _ <- npv cbInst
  cbSettlement <- advance cal evalDate (fromIntegral settlementDays, Days) Following False
  cbClean <- currentCleanPrice cb
  cbDirty <- currentDirtyPrice cb
  cbAccrued <- accruedAmount cb cbSettlement

  q3 <- simpleQuote (flatRate + 0.02) -- higher expected inflation
  h3 <- zeroCouponInflationSwapHelper q3 obsLag maturity5Y cal Unadjusted dc idx0 CPILinear LastRelevantDate Nothing
  hiZeroCurve <- piecewiseZeroInflationCurve evalDate baseDate Monthly dc [h1, h3] Linear
  hiIdx <- zeroInflationIndex' "WL CPI" reg False Monthly obsLagI gbp (Just hiZeroCurve)
  cbHi <- cpiBond settlementDays faceAmount baseCPI0 obsLag hiIdx CPILinear cpiBondSchedule [couponRate]
    dc Unadjusted (Just evalDate) cal (0, Days) cal Unadjusted False
  cbHiInst <- asBond cbHi >>= asInstrument
  setPricingEngine cbHiInst bondEngine
  _ <- npv cbHiInst
  cbHiClean <- currentCleanPrice cbHi

  -- cpiLeg exercised directly via the generic Leg-based 'bond' constructor
  cpiL <- CF.cpiLeg cpiBondSchedule idx1 baseCPI0 obsLag [faceAmount] [couponRate] dc Unadjusted cal CPILinear True
  cpiLegBond <- bond settlementDays cal (Just evalDate) cpiL >>= asInstrument
  setPricingEngine cpiLegBond bondEngine
  cpiLegNpv <- npv cpiLegBond

  -- yoyInflationLeg exercised via the generic Leg-based 'swap'' constructor
  yoyL <- CF.yoyInflationLeg yoySchedule cal yidx1 obsLag CPILinear [nominal] dc Unadjusted [0] [1.0] [0.0] [] []
  fixedIR <- interestRate flatRate dc Compounded Annual
  fixedL <- CF.fixedRateLeg fixedSchedule [nominal] [fixedIR] Unadjusted dc cal
  yoyLegSwap <- swap' [(fixedL, True), (yoyL, False)]
  yoyLegSwapInst <- asInstrument yoyLegSwap
  setPricingEngine yoyLegSwapInst swapEngine
  yoyLegNpv <- npv yoyLegSwapInst

  return Result
    { zcisNpvBeforeFairRate = npvBefore
    , zcisNpvAtFairRate = npvAtFair
    , cpiSwapNpvAtFairRate = cpiSwapNpv
    , yoySwapNpvAtFairRate = yoySwapNpv
    , cpiBondDirtyMinusCleanAccrued = cbDirty - (cbClean + cbAccrued)
    , cpiBondPriceLowInflation = cbClean
    , cpiBondPriceHighInflation = cbHiClean
    , cpiLegBondNpv = cpiLegNpv
    , yoyLegSwapNpv = yoyLegNpv
    }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
