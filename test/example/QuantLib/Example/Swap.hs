module QuantLib.Example.Swap
  (
    Result(..)
  , SwapResult(..)
  , IterationResult(..)
  , run
  ) where
import Control.Monad(void, forM)
import Data.Time.Calendar
import Data.List.NonEmpty(fromList)

import QuantLib.Math
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.TermStructure
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

data SwapResult = SwapResult { spotNpvR :: Double
                              , spotFairSpreadR :: Double
                              , spotFairRateR :: Double
                              } deriving Show

data IterationResult = IterationResult {spotSwap :: SwapResult, forwardSwap :: SwapResult} deriving Show

data Result = Result [IterationResult] [IterationResult] deriving Show

run :: IO Result
run = do
  cal <- calendar TARGET
  settleDate <- adjust cal settleDate1 Following
  advance cal settleDate (-fixingDays, Days) Following False >>= setEvaluationDate . Just

  depoQuotes <- forM depoRates simpleQuote
  fraQuotes <- forM fraRates simpleQuote
  futQuotes <- forM futPrices simpleQuote
  swapQuotes <- forM swapRates simpleQuote

  depoDC <- dayCounter (Actual360 False)

  depoHelpers <- mapM (\(q, p) ->
    TS.depositRateHelper q p (fromIntegral fixingDays) cal ModifiedFollowing True depoDC) $
      zip depoQuotes depoTerms
  fraHelpers <- mapM (\(q, (m1, m2)) ->
    TS.fraRateHelper q m1 m2 (fromIntegral fixingDays) cal ModifiedFollowing True depoDC TS.LastRelevantDate Nothing True) $
      zip fraQuotes fraTerms

  imm1 <- nextIMMDate settleDate True
  -- chain of IMM dates, each derived from the one before. Written as an explicit
  -- Avoid a partial `last` and repeated list append.
  let nextIMMs :: Int -> Day -> IO [Day]
      nextIMMs 0 _ = pure []
      nextIMMs k prev = do
        v <- nextIMMDate (addDays 1 prev) True
        (v :) <$> nextIMMs (k - 1) v
  imms <- (imm1 :) <$> nextIMMs (length futPrices - 1) imm1

  futHelpers <- mapM (\(q, imm) ->
    TS.futuresRateHelper q imm 3 cal ModifiedFollowing True depoDC Nothing TS.IMM >>= TS.asRateHelper) $
      zip futQuotes imms

  swFixedDC <- dayCounter Thirty360European
  eu6m <- IR.iborIndex IR.Euribor6M Nothing
  swapHelpers <- mapM (\(q, y) ->
    TS.swapRateHelper' q (y, Years) cal Annual Unadjusted swFixedDC eu6m Nothing (0, Days) Nothing
      Nothing TS.LastRelevantDate Nothing False Nothing Nothing Nothing >>= TS.asRateHelper) $
      zip swapQuotes swapYears

  tsDC <- dayCounter ActualActualISDA

  depoSwapTS <- TS.piecewiseYieldCurve settleDate (fromList (depoHelpers++swapHelpers)) tsDC [] TS.Discount LogLinear
  depoFutSwapTS <- TS.piecewiseYieldCurve settleDate (fromList (take 2 depoHelpers++futHelpers++drop 1 swapHelpers)) tsDC [] TS.Discount LogLinear
  depoFraSwapTS <- TS.piecewiseYieldCurve settleDate (fromList (take 3 depoHelpers++fraHelpers++swapHelpers)) tsDC [] TS.Discount LogLinear

  i1 <- forM [depoSwapTS, depoFutSwapTS, depoFraSwapTS] (\ts -> valuateSwap settleDate ts ts)

  let market5YQuote = swapQuotes !! 2
  void $ setValue market5YQuote 0.0460

  i2 <- forM [depoSwapTS, depoFutSwapTS, depoFraSwapTS] (\ts -> valuateSwap settleDate ts ts)

  return $ Result i1 i2

  where
    settleDate1 = 22 `september` 2004
    fixingDays = 2

    depoRates = [0.0382, 0.0372, 0.0363, 0.0353, 0.0348, 0.0345]
    fraRates = [0.037125, 0.037125, 0.037125]
    futPrices = [96.2875, 96.7875, 96.9875, 96.6875, 96.4875, 96.3875, 96.2875, 96.0875]
    swapRates = [0.037125, 0.0398, 0.0443, 0.05165, 0.055175]
    depoTerms = [(1, Weeks), (1, Months), (3, Months), (6, Months), (9, Months), (1, Years)]
    fraTerms = [(3, 6), (6, 9), (6, 12)]
    swapYears = [2, 3, 5, 10, 15]

    valuateSwap :: Day -> TS.GenYieldTermStructure y1 -> TS.GenYieldTermStructure y2 -> IO IterationResult
    valuateSwap settle d f = do
      fixDC <- dayCounter Thirty360European
      floatDC <- dayCounter (Actual360 False)
      eu6m <- IR.iborIndex IR.Euribor6M (Just f)
      fixP <- fromFrequency Annual
      floatP <- fromFrequency Semiannual
      cal <- calendar TARGET
      let maturity = addGregorianYearsClip 5 settle
      fixSched <- schedule (Just settle) maturity fixP cal Unadjusted Unadjusted Forward False Nothing Nothing
      floatSched <- schedule (Just settle) maturity floatP cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
      spot5Y <- vanillaSwap Payer 1000000 fixSched 0.04 fixDC
        floatSched eu6m 0.0 floatDC (Just ModifiedFollowing) Nothing

      fwdStart <- advance cal settle (1, Years) Following False
      let fwdMat = addGregorianYearsClip 5 fwdStart
      fwdFixS <- schedule (Just fwdStart) fwdMat fixP
        cal Unadjusted Unadjusted Forward False Nothing Nothing
      fwdFloatS <- schedule (Just fwdStart) fwdMat floatP
        cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
      fwd1Y5Y <- vanillaSwap Payer 1000000 fwdFixS 0.04 fixDC
        fwdFloatS eu6m 0.0 floatDC (Just ModifiedFollowing) Nothing
      refDate <- referenceDate d
      pricer <- discountingSwapEngine d (Just False) (Just refDate) (Just refDate)

      setPricingEngine spot5Y pricer
      setPricingEngine fwd1Y5Y pricer

      spotNPV <- npv spot5Y
      spotFairSpread <- fairSpread spot5Y
      spotFairRate <- fairRate spot5Y
      let sr = SwapResult spotNPV spotFairSpread spotFairRate

      fwdNPV <- npv fwd1Y5Y
      fwdFairSpread <- fairSpread fwd1Y5Y
      fwdFairRate <- fairRate fwd1Y5Y
      let fr = SwapResult fwdNPV fwdFairSpread fwdFairRate
      return $ IterationResult sr fr

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
