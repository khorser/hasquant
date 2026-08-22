{-# LANGUAGE TupleSections #-}
module QuantLib.Example.Gaussian1dModels
  (
    Result(..)
  , CalibrationCheck(..)
  , run
  ) where
import Control.Monad (forM, forM_, replicateM)
import Data.Maybe (mapMaybe)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import QuantLib.Instrument
import QuantLib.Instrument.Option (BermudanExercise(..))
import QuantLib.Instrument.Swap
import QuantLib.Math (EndCriteria(..), OptimizationMethod(..))
import QuantLib.Model hiding(setPricingEngine)
import qualified QuantLib.Model as Model
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.TermStructure.Volatility
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

-- |Per-helper (modelValue, marketValue, impliedVolatility) after calibrating a basket --
-- what upstream's @printModelCalibration@ prints, and the strongest reachable calibration
-- check: 'calibrationBasket' returns generic 'BlackCalibrationHelper's (upstream erases to
-- the base inside @basketgeneratingengine.cpp@ before the vector is returned), so nominal\/
-- strike\/expiry on individual basket elements are not recoverable from hasquant -- see
-- CLAUDE.md's "A C++ return type erased by upstream itself" note.
data CalibrationCheck = CalibrationCheck
  { ccModelValue :: Double
  , ccMarketValue :: Double
  , ccImpliedVol :: Double
  } deriving Show

data Result = Result
  { basketNaiveLen :: Int             -- ^calibration basket size, Naive mode (bermudan swaption)
  , basketMsdgLen :: Int              -- ^..., MaturityStrikeByDeltaGamma mode
  , basketCalibration :: [CalibrationCheck] -- ^Naive basket, after calibrateVolatilitiesIterative
  , npvAtmGsr :: Double               -- ^bermudan swaption NPV, ATM-calibrated GSR
  , npvDealStrikeGsr :: Double        -- ^..., after recalibrating to the MaturityStrikeByDeltaGamma basket
  , amortizingBasketLen :: Int        -- ^MSDG basket size for the amortizing-nominal underlying
  , callRightBasketLen0 :: Int        -- ^MSDG basket size for the bond call right, oas=0
  , npvCallRight0 :: Double           -- ^bond call right NPV, oas=0
  , callRightBasketLen100 :: Int      -- ^..., oas=100bp
  , npvCallRight100 :: Double         -- ^bond call right NPV, oas=100bp
  , underlyingCmsSwapNpv :: Double    -- ^FloatFloatSwap underlying NPV (LinearTsrPricer/BlackIborCouponPricer)
  , cmsLegNpv :: Double
  , euriborLegNpv :: Double
  , floatBasketNaiveLen :: Int        -- ^Naive basket size for the CMS-vs-Euribor float swaption
  , npvFloatGsr :: Double             -- ^float swaption NPV under (Naive-basket-calibrated) GSR
  , underlyingValueGsr :: Double      -- ^float swaption's "underlyingValue" additional result, GSR
  , npvFloatMarkov :: Double          -- ^float swaption NPV under MarkovFunctional
  , underlyingValueMarkovPreCalib :: Double  -- ^"underlyingValue" before coterminal calibration
  , underlyingValueMarkovPostCalib :: Double -- ^"underlyingValue" after coterminal calibration
  } deriving Show

underlyingValueOf :: FloatFloatSwaption -> IO Double
underlyingValueOf i = do
  results <- additionalResults i
  case mapMaybe (\(k, v) -> if k == "underlyingValue" then Just v else Nothing) results of
    [RealVal v] -> return v
    _ -> error "underlyingValueOf: expected exactly one RealVal \"underlyingValue\" additional result"

calibrationCheck :: BlackCalibrationHelper -> IO CalibrationCheck
calibrationCheck h = do
  mv <- Model.modelValue h
  ccv <- Model.marketValue h
  vol <- Model.impliedVolatility h mv 1.0e-6 1000 0.0 2.0
  return CalibrationCheck { ccModelValue = mv, ccMarketValue = ccv, ccImpliedVol = vol }

lmMethod :: OptimizationMethod
lmMethod = LevenbergMarquardt 1.0e-8 1.0e-8 1.0e-8 False

lmEndCriteria :: EndCriteria
-- Only the max-iterations field is actually consulted by LevenbergMarquardt (per the
-- upstream example's own comment at ex/Gaussian1dModels.cpp:257-258).
lmEndCriteria = EndCriteria 1000 10 1.0e-8 1.0e-8 1.0e-8

run :: IO Result
run = do
  cal <- calendar TARGET
  setEvaluationDate (Just refDate)
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)

  forward6mQuote <- simpleQuote forward6mLevel
  oisQuote <- simpleQuote oisLevel
  yts6m <- TS.flatForward refDate forward6mQuote dc365 Continuous Annual
  ytsOis <- TS.flatForward refDate oisQuote dc365 Continuous Annual
  euribor6m <- IR.iborIndex IR.Euribor6M (Just yts6m)

  volQuote <- simpleQuote volLevel
  swaptionVol <- constantSwaptionVolatility 0 cal ModifiedFollowing volQuote dc365 ShiftedLognormal 0.0

  effectiveDate <- advance cal refDate (2, Days) Following False
  maturity <- advance cal effectiveDate (10, Years) Following False
  fixedSchedule <- schedule (Just effectiveDate) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  floatSchedule <- schedule (Just effectiveDate) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing

  -- 1. A standard 10y bermudan payer swaption, struck at 4%, exercisable yearly.
  vanilla <- vanillaSwap Payer 1.0 fixedSchedule strike thirty360bb floatSchedule euribor6m 0.00 act360 Nothing Nothing
  underlying <- nonstandardSwapFromVanilla vanilla

  -- Exercise dates: fixedSchedule[1..9], each shifted back 2 business days -- upstream loops
  -- i = 1..9 over the *schedule*'s own dates, not the underlying's coupon accrual starts.
  fixedDates <- dates fixedSchedule
  exerciseDates <- forM (take 9 (drop 1 fixedDates)) $ \d -> advance cal d (-2, Days) Following False
  let ex = Bermudan (BermudanExercise exerciseDates False)
  swaption1 <- nonstandardSwaption underlying ex Physical PhysicalOTC

  -- One-factor GSR model with piecewise volatility adapted to the exercise dates.
  let stepDates = init exerciseDates
  gsrVolQuotes <- replicateM (length stepDates + 1) (simpleQuote 0.01)
  gsrReversionQuote <- simpleQuote reversion
  gsrModel <- gsr yts6m stepDates gsrVolQuotes gsrReversionQuote 60.0
  gsrGm <- gsrAsGaussian1dModel gsrModel

  swaptionEngine <- gaussian1dSwaptionEngine gsrGm 64 7.0 True False (Just ytsOis) None
  nonstandardSwaptionEngine <- gaussian1dNonstandardSwaptionEngine gsrGm 64 7.0 True False Nothing (Just ytsOis) None
  setPricingEngine swaption1 nonstandardSwaptionEngine

  swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just yts6m) (Just ytsOis)

  -- Naive calibration basket: ATM swaptions adapted to the exercise dates and maturity.
  basket1 <- calibrationBasket swaption1 swapBase swaptionVol CalibrationBasketNaive
  forM_ basket1 (`Model.setPricingEngine` swaptionEngine)
  calibrateVolatilitiesIterative gsrModel basket1 lmMethod lmEndCriteria Nothing []
  calib1 <- mapM calibrationCheck basket1
  npv1 <- npv swaption1

  -- MaturityStrikeByDeltaGamma basket: maturity/strike/nominal match the underlying's NPV,
  -- delta and gamma at each exercise date -- recalibrate and reprice.
  basket2 <- calibrationBasket swaption1 swapBase swaptionVol MaturityStrikeByDeltaGamma
  forM_ basket2 (`Model.setPricingEngine` swaptionEngine)
  calibrateVolatilitiesIterative gsrModel basket2 lmMethod lmEndCriteria Nothing []
  npv2 <- npv swaption1

  -- 2. Linear amortizing nominal schedule, same exercise dates.
  let n = length fixedDates - 1
      nominalFixed = [1.0 - fromIntegral i / fromIntegral n | i <- [0 .. n - 1]]
      nominalFloating = concatMap (\x -> [x, x]) nominalFixed -- 6m vs. 1y: two float periods per fixed one
      strikes = replicate n strike
  underlying2 <- nonstandardSwap Payer nominalFixed nominalFloating fixedSchedule strikes thirty360bb
    floatSchedule euribor6m 1.0 0.0 act360 False False Nothing
  swaption2 <- nonstandardSwaption underlying2 ex Physical PhysicalOTC
  setPricingEngine swaption2 nonstandardSwaptionEngine
  basket3 <- calibrationBasket swaption2 swapBase swaptionVol MaturityStrikeByDeltaGamma

  -- 3. Bond call right, modeled as a rebated-exercise swaption on a one-leg swap with
  -- notional reimbursement at maturity.
  let nominalFixed2 = replicate n 1.0
      nominalFloating2 = replicate (2 * n) 0.0 -- null the second leg
  underlying3 <- nonstandardSwap Receiver nominalFixed2 nominalFloating2 fixedSchedule strikes thirty360bb
    floatSchedule euribor6m 1.0 0.0 act360 False True Nothing -- final capital exchange
  let exercise2 = Rebated ex (-1.0) 2 cal Following
  swaption3 <- nonstandardSwaption underlying3 exercise2 Physical PhysicalOTC

  oasQuote <- simpleQuote 0.0
  nonstandardSwaptionEngine2 <- gaussian1dNonstandardSwaptionEngine gsrGm 64 7.0 True False (Just oasQuote) Nothing None -- discount on 6m, not OIS
  setPricingEngine swaption3 nonstandardSwaptionEngine2

  basket4 <- calibrationBasket swaption3 swapBase swaptionVol MaturityStrikeByDeltaGamma
  forM_ basket4 (`Model.setPricingEngine` swaptionEngine)
  calibrateVolatilitiesIterative gsrModel basket4 lmMethod lmEndCriteria Nothing []
  npv3 <- npv swaption3

  -- Add a 100bp credit spread and regenerate the basket.
  _ <- setValue oasQuote 0.01
  basket5 <- calibrationBasket swaption3 swapBase swaptionVol MaturityStrikeByDeltaGamma
  forM_ basket5 (`Model.setPricingEngine` swaptionEngine)
  calibrateVolatilitiesIterative gsrModel basket5 lmMethod lmEndCriteria Nothing []
  npv4 <- npv swaption3

  -- 4. CMS 10y vs Euribor 6m float-float swaption, exercisable yearly.
  underlying4 <- floatFloatSwap Payer 1.0 1.0 fixedSchedule swapBase thirty360bb floatSchedule euribor6m act360
    defaultFloatFloatSwapOpts{ffsSpread2 = 0.0010}
  swaption4 <- floatFloatSwaption underlying4 ex Physical PhysicalOTC
  floatSwaptionEngine <- gaussian1dFloatFloatSwaptionEngine gsrGm 64 7.0 True False Nothing (Just ytsOis) True None
  setPricingEngine swaption4 floatSwaptionEngine

  reversionQuote <- simpleQuote reversion
  cmsPricer <- CF.linearTsrPricer swaptionVol reversionQuote Nothing (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
  -- Only the CMS leg (leg 0) needs an explicit pricer -- a plain (uncapped/unfloored) Euribor
  -- leg computes its forecast fixing directly, with no pricer required (confirmed in the
  -- increment 2 smoke test).
  leg0 <- leg underlying4 0
  CF.setCouponPricer leg0 cmsPricer

  swapPricer <- discountingSwapEngine ytsOis Nothing Nothing Nothing
  setPricingEngine underlying4 swapPricer
  npv5 <- npv underlying4
  legNpv0 <- legNPV underlying4 0
  legNpv1 <- legNPV underlying4 1

  basket6 <- floatFloatSwaptionCalibrationBasket swaption4 swapBase swaptionVol CalibrationBasketNaive
  forM_ basket6 (`Model.setPricingEngine` swaptionEngine)
  calibrateVolatilitiesIterative gsrModel basket6 lmMethod lmEndCriteria Nothing []
  npv6 <- npv swaption4
  underlyingValGsr <- underlyingValueOf swaption4

  -- 5. The Markov-functional model: calibrates to the underlying's own smile directly
  -- (via its step-date/tenor/swapIndexBase construction), unlike GSR which only sees the
  -- coterminal calibration basket.
  let markovStepDates = exerciseDates
      markovSigmas = replicate (length markovStepDates + 1) 0.01
      cmsTenors = replicate (length markovStepDates) (10, Years) :: [(Word, TimeUnit)]
  markov <- markovFunctional yts6m reversion markovStepDates markovSigmas swaptionVol markovStepDates cmsTenors swapBase 16
  markovGm <- markovFunctionalAsGaussian1dModel markov

  swaptionEngineMarkov <- gaussian1dSwaptionEngine markovGm 8 5.0 True False (Just ytsOis) None
  floatEngineMarkov <- gaussian1dFloatFloatSwaptionEngine markovGm 16 7.0 True False Nothing (Just ytsOis) True None
  setPricingEngine swaption4 floatEngineMarkov
  npv7 <- npv swaption4
  underlyingValMarkovPre <- underlyingValueOf swaption4

  -- Calibrate the Markov model's own sigma function to the coterminal ATM swaptions basket
  -- (basket6, from above) -- this shouldn't move the underlying-smile match much, since that
  -- was already fixed by the model's construction.
  basket6ch <- mapM Model.asCalibrationHelper basket6
  forM_ basket6 (`Model.setPricingEngine` swaptionEngineMarkov)
  Model.calibrate markov (map (, 1.0) basket6ch) lmMethod lmEndCriteria Nothing []
  underlyingValMarkovPost <- underlyingValueOf swaption4

  return Result
    { basketNaiveLen = length basket1
    , basketMsdgLen = length basket2
    , basketCalibration = calib1
    , npvAtmGsr = npv1
    , npvDealStrikeGsr = npv2
    , amortizingBasketLen = length basket3
    , callRightBasketLen0 = length basket4
    , npvCallRight0 = npv3
    , callRightBasketLen100 = length basket5
    , npvCallRight100 = npv4
    , underlyingCmsSwapNpv = npv5
    , cmsLegNpv = legNpv0
    , euriborLegNpv = legNpv1
    , floatBasketNaiveLen = length basket6
    , npvFloatGsr = npv6
    , underlyingValueGsr = underlyingValGsr
    , npvFloatMarkov = npv7
    , underlyingValueMarkovPreCalib = underlyingValMarkovPre
    , underlyingValueMarkovPostCalib = underlyingValMarkovPost
    }
  where
    refDate = 30 `april` 2014
    forward6mLevel = 0.025
    oisLevel = 0.02
    volLevel = 0.20
    strike = 0.04
    reversion = 0.01

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
