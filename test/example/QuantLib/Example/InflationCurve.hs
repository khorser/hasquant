{-# LANGUAGE OverloadedLists #-}

module QuantLib.Example.InflationCurve
  (
    Result(..)
  , run
  ) where

import Control.Monad(forM_)
import qualified QuantLib.InterestRate as IR
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import QuantLib.Math(Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Instrument.Swap(zcisFairRate, yoyFairRate)
import QuantLib.TermStructure.Inflation
import QuantLib.TermStructure.Yield(flatForward, PillarChoice(..))
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..), TimeUnit(..))

data Result = Result
  { zeroRate1Y :: Double
  , zeroRate2Y :: Double
  , yoyRate1Y :: Double
  , yoyRate2Y :: Double
  , zcisHelperFairRate :: Double -- ^fair rate of the swap 'zeroCouponInflationSwapHelperSwap' pulls out of h1
  , yoyHelperFairRate :: Double  -- ^likewise, via 'yearOnYearInflationSwapHelperSwap' on hy1
  } deriving Show

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null

  -- UKRPI needs a fixing at every month up to the reference date, not just at
  -- baseDate, or the bootstrap fails with "Missing UK RPI fixing for ...".
  fixingDates <- mapM (\n -> advance cal (1 `january` 2022) (n, Months) Unadjusted False) [0 .. 24 :: Int]

  zii <- zeroInflationIndex UKRPI
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing zii d (260.0 + i) False
  q1 <- simpleQuote flatRate
  q2 <- simpleQuote flatRate
  h1 <- zeroCouponInflationSwapHelper q1 obsLag maturity1 cal Unadjusted dc zii CPILinear LastRelevantDate Nothing
  h2 <- zeroCouponInflationSwapHelper q2 obsLag maturity2 cal Unadjusted dc zii CPILinear LastRelevantDate Nothing
  zeroCurve <- piecewiseZeroInflationCurve evalDate baseDate Monthly dc [h1, h2] Linear
  z1 <- zeroRate zeroCurve maturity1 True
  z2 <- zeroRate zeroCurve maturity2 True
  -- the helper builds its swap internally, so this accessor is the only way to reach it;
  -- once the curve is bootstrapped the swap must reprice to the quote it was built from
  zcisFair <- zcisFairRate =<< zeroCouponInflationSwapHelperSwap h1

  yii <- yoyInflationIndex YYUKRPI
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing yii d (flatRate + i * 0.0001) False
  nominalQ <- simpleQuote 0.02
  nominalCurve <- flatForward evalDate nominalQ dc IR.Continuous Annual
  qy1 <- simpleQuote flatRate
  qy2 <- simpleQuote flatRate
  hy1 <- yearOnYearInflationSwapHelper qy1 obsLag maturity1 cal Unadjusted dc yii CPILinear nominalCurve LastRelevantDate Nothing
  hy2 <- yearOnYearInflationSwapHelper qy2 obsLag maturity2 cal Unadjusted dc yii CPILinear nominalCurve LastRelevantDate Nothing
  yoyCurve <- piecewiseYoYInflationCurve evalDate baseDate flatRate Monthly dc [hy1, hy2] Linear
  y1 <- yoyRate yoyCurve maturity1 True
  y2 <- yoyRate yoyCurve maturity2 True
  yoyFair <- yoyFairRate =<< yearOnYearInflationSwapHelperSwap hy1

  return Result
    { zeroRate1Y = z1
    , zeroRate2Y = z2
    , yoyRate1Y = y1
    , yoyRate2Y = y2
    , zcisHelperFairRate = zcisFair
    , yoyHelperFairRate = yoyFair
    }
  where
    evalDate = 2 `january` 2024
    baseDate = 1 `october` 2023
    obsLag = (3, Months)
    maturity1 = 2 `january` 2025
    maturity2 = 2 `january` 2026
    flatRate = 0.03

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
