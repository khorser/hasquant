module QuantLib.Example.Swap
  (
    Result(..)
  , run
  )
where

import Control.Monad(forM, (>=>))
import Data.Time.Calendar

import QuantLib.Math.Interpolation
import QuantLib.Index.Ibor
import QuantLib.Instrument.Swap
import QuantLib.Instrument.VanillaSwapType
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.TermStructure.Trait
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.DayCounter
import QuantLib.Time.Date
import QuantLib.Time.Frequency
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.Time.Unit
import QuantLib.Types
import QuantLib.Settings

data Result = Result
  { cleanPriceR :: Double
  } deriving Show

run :: IO Result
run = do
  cal <- target
  settleDate <- adjust cal settleDate1 Following
  advance cal settleDate (-fixingDays) Days Following False >>= setEvaluationDate . Just

  depoQuotes <- forM depoRates $ simpleQuote >=> asQuote
  fraQuotes <- forM fraRates $ simpleQuote >=> asQuote
  futQuotes <- forM futPrices $ simpleQuote >=> asQuote
  swapSimpleQuotes <- forM swapRates simpleQuote
  swapQuotes <- mapM asQuote swapSimpleQuotes

  depoDC <- actual360

  depoHelpers <- mapM (\(q, (n, u)) -> do
    p <- period n u
    TS.depositRateHelper q p (fromIntegral fixingDays) cal ModifiedFollowing True depoDC) $
      zip depoQuotes depoTerms
  fraHelpers <- mapM (\(q, (m1, m2)) ->
    TS.fraRateHelper q m1 m2 (fromIntegral fixingDays) cal ModifiedFollowing True depoDC) $
      zip fraQuotes fraTerms

  let imm1 = nextIMMDate (Just settleDate) True
  let imms = foldl nextIMM [imm1] (replicate (length futPrices-1) 1)

  futHelpers <- mapM (\(q, imm) ->
    TS.futuresRateHelper q imm 3 cal ModifiedFollowing True depoDC Nothing) $
      zip futQuotes imms

  swFixedDC <- thirty360European
  eu6m <- euribor6M Nothing
  spread <- simpleQuote 0.0 >>= asQuote
  swapHelpers <- mapM (\(q, y) -> do
    p <- period y Years
    TS.swapRateHelper' q p cal Annual Unadjusted swFixedDC eu6m spread Nothing Nothing >>= asRateHelper) $
      zip swapQuotes swapYears

  tsDC <- actualActualISDA

  depoSwapTS <- TS.piecewiseYieldCurve settleDate (depoHelpers++swapHelpers) tsDC [] tolerance Discount LogLinear
  depoFutTS <- TS.piecewiseYieldCurve settleDate (futHelpers++swapHelpers) tsDC [] tolerance Discount LogLinear
  depoFRASwapTS <- TS.piecewiseYieldCurve settleDate (depoHelpers++fraHelpers++swapHelpers) tsDC [] tolerance Discount LogLinear

  valuateSwap settleDate depoSwapTS depoFutTS

  return $ Result 5.6
  where
    settleDate1 = 22 `september` 2004
    fixingDays = 2
    tolerance = 1e-15

    depoRates = [0.0382, 0.0372, 0.0363, 0.0353, 0.0348, 0.0345]
    fraRates = [0.037125, 0.037125, 0.037125]
    futPrices = [96.2875, 96.7875, 96.9875, 96.6875, 96.4875, 96.3875, 96.2875, 96.0875]
    swapRates = [0.037125, 0.0398, 0.0443, 0.05165, 0.055175]
    depoTerms = [(1, Weeks), (1, Months), (3, Months), (6, Months), (9, Months), (1, Years)]
    fraTerms = [(3, 6), (6, 9), (6, 12)]
    swapYears = [2, 3, 5, 10, 15]

    nextIMM :: [Day] -> Integer -> [Day]
    nextIMM l inc = l ++ [nextIMMDate (Just $ addDays inc (last l)) True]

    valuateSwap settle d f = do
      fixDC <- thirty360European
      floatDC <- actual360
      eu6m <- euribor6M $ Just f
      fixP <- fromFrequency Annual
      floatP <- fromFrequency Semiannual
      cal <- target
      let maturity = addGregorianYearsClip 5 settle
      fixSched <- schedule (Just settle) maturity fixP
        cal Unadjusted Unadjusted Forward False Nothing Nothing
      floatSched <- schedule (Just settle) maturity floatP
        cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
      spot5Y <- vanillaSwap Payer 1000000 fixSched 0.04 fixDC
        floatSched eu6m 0.0 floatDC ModifiedFollowing
      return ()
        

