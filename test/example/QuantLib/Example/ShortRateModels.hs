{-# LANGUAGE TupleSections #-}
module QuantLib.Example.ShortRateModels
  (
    CalibrationResult(..)
  , SwapCheck(..)
  , ConvexityCheck(..)
  , DiscountCheck(..)
  , Result(..)
  , run
  ) where
import Control.Monad(forM, when)
import qualified Data.List.NonEmpty as NE

import QuantLib.CashFlow(RateAveragingType(..))
import QuantLib.Index(fixingCalendar, addFixing)
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate hiding(rate)
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Swap
import QuantLib.Math
import QuantLib.Model hiding(setPricingEngine, value)
import qualified QuantLib.Model as Model
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

-- |Shape shared by @testCachedHullWhite@/@testCachedHullWhite2@/
-- @testCachedHullWhiteFixedReversion@ in @ex/shortratemodels.cpp@.
-- @cachedA@/@cachedSigma@/@cachedValue@ are the upstream file's literal
-- expected values (the @usingAtParCoupons@ branch, matching this QuantLib
-- build's default -- @IborCoupon::Settings@ isn't bound in hasquant, so the
-- other branch's literals can't be selected at runtime).
data CalibrationResult = CalibrationResult
  { calculatedA, calculatedSigma :: Double
  , cachedA, cachedSigma :: Double
  , calculatedValue, cachedValue :: Double
  } deriving Show

data SwapCheck = SwapCheck
  { startMonths :: Int
  , lengthYears :: Int
  , swapRate :: Double
  , expectedNPV, calculatedNPV :: Double
  } deriving Show

data ConvexityCheck = ConvexityCheck
  { convexityT, convexityA, expectedForward, calculatedForward :: Double
  } deriving Show

data DiscountCheck = DiscountCheck { expectedDF, calculatedDF :: Double } deriving Show

data Result = Result
  { cachedHullWhite :: CalibrationResult
  , cachedHullWhiteFixedReversion :: CalibrationResult
  , cachedHullWhite2 :: CalibrationResult
  , swaps :: [SwapCheck]
  , futuresConvexityBias :: [ConvexityCheck]
  , extendedCirDiscountFactor :: DiscountCheck
  , vasicekDiscountFactorSmallMeanReversion :: DiscountCheck
  } deriving Show

run :: IO Result
run = do
  hw <- runCachedHullWhite [] 0.1 0.01 0.0464041 0.00579912
  hwFixed <- runCachedHullWhite fixedReversion 0.05 0.01 0.05 0.00585858
  hw2 <- runCachedHullWhite2
  sw <- runSwaps
  cirDF <- runExtendedCirDiscountFactor
  vasicekDF <- runVasicekSmallMeanReversion
  fcb <- futuresConvexityChecks
  pure Result
    { cachedHullWhite = hw
    , cachedHullWhiteFixedReversion = hwFixed
    , cachedHullWhite2 = hw2
    , swaps = sw
    , futuresConvexityBias = fcb
    , extendedCirDiscountFactor = cirDF
    , vasicekDiscountFactorSmallMeanReversion = vasicekDF
    }

calibrationEvalDate :: Day
calibrationEvalDate = 15 `february` 2002

calibrationSettlement :: Day
calibrationSettlement = 19 `february` 2002

calibrationData :: [(Word, Word, Double)] -- ^(start, length, volatility)
calibrationData =
  [ (1, 5, 0.1148), (2, 4, 0.1108), (3, 3, 0.1070), (4, 2, 0.1021), (5, 1, 0.1000) ]

-- |@testCachedHullWhite@/@testCachedHullWhiteFixedReversion@: calibrate a
-- 'HullWhite' model, constructed with the given starting @(a, sigma)@, to the
-- swaption grid in 'calibrationData', using Euribor6M with its usual start delay.
runCachedHullWhite :: [Bool] -- ^fixParameters, e.g. 'fixedReversion'
  -> Double -> Double -- ^model's starting (a, sigma)
  -> Double -> Double -- ^cached expected (a, sigma)
  -> IO CalibrationResult
runCachedHullWhite fixParams a0 sigma0 cachedAv cachedSigmaV = do
  setEvaluationDate (Just calibrationEvalDate)
  ac365 <- dayCounter Actual365FixedStandard
  q <- simpleQuote 0.04875825
  ts <- TS.flatForward calibrationSettlement q ac365 Continuous Annual
  model <- hullWhite ts a0 sigma0
  index <- IR.iborIndex IR.Euribor6M (Just ts)
  runCalibration model index ts fixParams cachedAv cachedSigmaV

-- |@testCachedHullWhite2@: same as 'runCachedHullWhite' but against a
-- zero-fixing-days variant of the index (no start delay).
runCachedHullWhite2 :: IO CalibrationResult
runCachedHullWhite2 = do
  setEvaluationDate (Just calibrationEvalDate)
  ac365 <- dayCounter Actual365FixedStandard
  q <- simpleQuote 0.04875825
  ts <- TS.flatForward calibrationSettlement q ac365 Continuous Annual
  model <- hullWhite ts 0.1 0.01
  index <- IR.iborIndex IR.Euribor6M (Just ts)
  tenr <- IR.tenor index
  ccy <- IR.currency index
  cal <- fixingCalendar index
  dc <- IR.dayCounter index
  let conv = IR.businessDayConvention index
      eom = IR.endOfMonth index
  index0 <- IR.iborIndex (IR.Ibor "Euribor" tenr 0 ccy cal conv eom dc) (Just ts)
  runCalibration model index0 ts [] 0.0482063 0.00582687

runCalibration :: HullWhite -> IR.IborIndex -> TS.YieldTermStructure -> [Bool] -> Double -> Double -> IO CalibrationResult
runCalibration model index ts fixParams cachedAv cachedSigmaV = do
  engine <- jamshidianSwaptionEngine model (Just ts)
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)
  helpers <- forM calibrationData $ \(s, l, v) -> do
    vol <- simpleQuote v
    h <- swaptionHelper (s, Years) (l, Years) vol index (1, Years) thirty360bb act360 ts RelativePriceError Nothing 1.0 ShiftedLognormal 0.0 Nothing AveragingCompound
    Model.setPricingEngine h engine
    asCalibrationHelper h
  let method = LevenbergMarquardt 1.0e-8 1.0e-8 1.0e-8 False
      ec = EndCriteria 10000 100 1e-6 1e-8 1e-8
  calibrate model (NE.fromList $ map (, 1.0) helpers) method ec Nothing fixParams
  ps@[calcA, calcSigma] <- params model
  calcValue <- Model.value model ps helpers
  cachedVal <- Model.value model [cachedAv, cachedSigmaV] helpers
  pure CalibrationResult
    { calculatedA = calcA, calculatedSigma = calcSigma
    , cachedA = cachedAv, cachedSigma = cachedSigmaV
    , calculatedValue = calcValue, cachedValue = cachedVal
    }

-- |@testSwaps@: reprice 27 (start, length, rate) combinations with a
-- discounting engine (expected) and a Hull-White tree engine (calculated).
runSwaps :: IO [SwapCheck]
runSwaps = do
  cal <- calendar TARGET
  evalDate <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just evalDate)
  settlement <- advance cal evalDate (2, Days) Following False
  ac365 <- dayCounter Actual365FixedStandard
  curveDates <- (settlement :) <$> mapM (\(n, u) -> advance cal settlement (n, u) Following False)
    [(1, Weeks), (1, Months), (3, Months), (6, Months), (9, Months)
    ,(1, Years), (2, Years), (3, Years), (5, Years), (10, Years), (15, Years)]
  let discounts =
        [1.0, 0.999258, 0.996704, 0.990809, 0.981798, 0.972570
        ,0.963430, 0.929532, 0.889267, 0.803693, 0.596903, 0.433022]
  ts <- TS.interpolatedDiscountCurve (NE.fromList (zip curveDates discounts)) ac365 cal [] LogLinear False
  model <- hullWhite ts 0.1 0.01
  euribor <- IR.iborIndex IR.Euribor6M (Just ts)
  riskFreeEngine <- discountingSwapEngine ts Nothing Nothing Nothing
  treeEngine <- treeVanillaSwapEngine model 120 Nothing
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)
  results <- forM starts $ \s -> do
    start <- advance cal settlement (s, Months) Following False
    when (start< evalDate) $ advance cal start (-2, Days) Following False >>= \fd -> addFixing euribor fd 0.03 False
    forM lengths $ \l -> do
      maturity <- advance cal start(l, Years) Following False
      fixedSchedule <- schedule (Just start) maturity (1, Years) cal Unadjusted Unadjusted Forward False Nothing Nothing
      floatSchedule <- schedule (Just start) maturity (6, Months) cal Following Following Forward False Nothing Nothing
      forM rates $ \r -> do
        swp <- vanillaSwap Payer 1000000.0 fixedSchedule r thirty360bb floatSchedule euribor 0.0 act360 (Just Following) Nothing
        setPricingEngine swp riskFreeEngine
        expected <- npv swp
        setPricingEngine swp treeEngine
        calculated <- npv swp
        pure SwapCheck
          { startMonths = s, lengthYears = l, swapRate = r
          , expectedNPV = expected, calculatedNPV = calculated
          }
  pure (concatMap concat results)
  where
    starts = [-3, 0, 3] :: [Int]
    lengths = [2, 5, 10] :: [Int]
    rates = [0.02, 0.04, 0.06]

-- |@testFuturesConvexityBias@: G. Kirikos, D. Novak, \"Convexity Conundrums\", Risk Magazine, March 1997.
futuresConvexityChecks :: IO [ConvexityCheck]
futuresConvexityChecks = mapM mkCheck convexityData
  where
    futureQuote = 94.0
    sigma = 0.015
    t = 5.0
    futureImpliedRate = (100.0 - futureQuote) / 100.0
    convexityData =
      [ (5.25, 0.03, 0.0573037), (5.25, 1e-4, 0.0568627), (5.25, 0.0, 0.0568611)
      , (5.001, 0.03, 0.0575736), (5.0, 0.03, 0.0575747) ]
    mkCheck (bigT, a, expected) = do
      bias <- convexityBias futureQuote t bigT sigma a
      pure ConvexityCheck
        { convexityT = bigT, convexityA = a
        , expectedForward = expected
        , calculatedForward = futureImpliedRate - bias
        }

-- |@testExtendedCoxIngersollRossDiscountFactor@.
runExtendedCirDiscountFactor :: IO DiscountCheck
runExtendedCirDiscountFactor = do
  evalDate <- evaluationDate
  ac365 <- dayCounter Actual365FixedStandard
  q <- simpleQuote rate
  rts <- TS.flatForward evalDate q ac365 Continuous Annual
  model <- extendedCoxIngersollRoss rts rate 1.0 1e-4 rate True
  dNow <- TS.discount rts now False
  dMat <- TS.discount rts maturity False
  calculated <- discountBond model now maturity rate
  pure DiscountCheck { expectedDF = dMat / dNow, calculatedDF = calculated }
  where
    rate = 0.1
    now = 1.5
    maturity = 2.5

-- |@testVasicekDiscountFactorForSmallMeanReversion@ (closed-form reference, no curve involved).
runVasicekSmallMeanReversion :: IO DiscountCheck
runVasicekSmallMeanReversion = do
  model <- vasicek r0 a b sigma lambda
  calculated <- discountBond model now maturity r0
  pure DiscountCheck
    { expectedDF = exp (-r0 * maturity + sigma * sigma * maturity ** 3 / 6.0)
    , calculatedDF = calculated
    }
  where
    r0 = 0.05
    a = 1e-12
    b = 0.05
    sigma = 0.01
    lambda = 0.0
    now = 0.0
    maturity = 1.0

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
