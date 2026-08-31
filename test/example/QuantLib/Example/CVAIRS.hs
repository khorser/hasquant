module QuantLib.Example.CVAIRS
  (
    SwapRow(..)
  , Result(..)
  , run
  ) where
import Control.Monad(forM)
import qualified Data.List.NonEmpty as NE

import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.Math
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Credit as Credit
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

-- |Reproduces Table 2 on page 11 of "A Formula for Interest Rate Swaps
-- Valuation under Counterparty Risk in presence of Netting Agreements"
-- (Brigo, Masetti; 2005).
data SwapRow = SwapRow
  { tenorR :: Int
  , fairRateR :: Double
  , lowCorrectionBp :: Double    -- ^low-risk CVA correction, in bp
  , mediumCorrectionBp :: Double -- ^medium-risk CVA correction, in bp
  , highCorrectionBp :: Double   -- ^high-risk CVA correction, in bp
  } deriving Show

newtype Result = Result { rowsR :: [SwapRow] } deriving Show

run :: IO Result
run = do
  cal <- calendar TARGET
  todaysDate <- adjust cal (10 `march` 2004) Following
  setEvaluationDate (Just todaysDate)

  actActISDA <- dayCounter ActualActualISDA
  act360 <- dayCounter (Actual360 False)

  yieldIndex <- IR.iborIndex IR.Euribor3M Nothing

  swapQuotes <- mapM simpleQuote ratesSwapMkt
  swapHelpers <- forM (zip swapQuotes tenorsSwapMkt) $ \(q, t) ->
    TS.swapRateHelper' q (t, Years) cal Quarterly ModifiedFollowing actActISDA yieldIndex
      Nothing (0, Days) Nothing
      Nothing TS.LastRelevantDate Nothing False Nothing Nothing Nothing
      >>= TS.asRateHelper

  swapTS <- TS.piecewiseYieldCurve' 2 cal (NE.fromList swapHelpers) actActISDA [] TS.Discount LogLinear True

  riskFreeEngine <- discountingSwapEngine swapTS Nothing Nothing Nothing

  defaultDates <- mapM (\m -> advance cal todaysDate (m, Months) Following False) defaultTenorsMonths
  let mkHazardCurve intensities =
        Credit.interpolatedHazardRateCurve (NE.fromList (zip defaultDates intensities)) act360 cal [] BackwardFlat True
  lowTS <- mkHazardCurve intensitiesLow
  mediumTS <- mkHazardCurve intensitiesMedium
  highTS <- mkHazardCurve intensitiesHigh

  blackVolQuote <- simpleQuote blackVol
  ctptyLow <- counterpartyAdjSwapEngine swapTS blackVolQuote lowTS ctptyRRLow Nothing 0.999
  ctptyMedium <- counterpartyAdjSwapEngine swapTS blackVolQuote mediumTS ctptyRRMedium Nothing 0.999
  ctptyHigh <- counterpartyAdjSwapEngine swapTS blackVolQuote highTS ctptyRRHigh Nothing 0.999

  yieldIndexS <- IR.iborIndex IR.Euribor3M (Just swapTS)

  rows <- forM (zip tenorsSwapMkt ratesSwapMkt) $ \(t, r) -> do
    riskySwap <- makeVanillaSwap (fromIntegral t, Years) yieldIndexS r (0, Days) (Just 2)
      (3, Months) actActISDA (Just ModifiedFollowing) (Just ModifiedFollowing)
      (Just cal) (Just cal) (Just 100.0) (Just Payer)

    setPricingEngine riskySwap riskFreeEngine
    nonRiskyFair <- fairRate riskySwap

    setPricingEngine riskySwap ctptyLow
    lowFair <- fairRate riskySwap
    setPricingEngine riskySwap ctptyMedium
    mediumFair <- fairRate riskySwap
    setPricingEngine riskySwap ctptyHigh
    highFair <- fairRate riskySwap

    pure SwapRow
      { tenorR = t
      , fairRateR = nonRiskyFair
      , lowCorrectionBp = 10000 * (lowFair - nonRiskyFair)
      , mediumCorrectionBp = 10000 * (mediumFair - nonRiskyFair)
      , highCorrectionBp = 10000 * (highFair - nonRiskyFair)
      }

  pure (Result rows)

  where
    tenorsSwapMkt = [5, 10, 15, 20, 25, 30] :: [Int]
    ratesSwapMkt = [0.03249, 0.04074, 0.04463, 0.04675, 0.04775, 0.04811]
    defaultTenorsMonths = [0, 12, 36, 60, 84, 120, 180, 240, 300, 360] :: [Int]
    -- three risk levels (trailing element unused, matching the C++ example's
    -- own array-vs-loop-bound mismatch)
    intensitiesLow = [0.0036, 0.0036, 0.0065, 0.0099, 0.0111, 0.0177, 0.0177, 0.0177, 0.0177, 0.0177, 0.0177]
    intensitiesMedium = [0.0202, 0.0202, 0.0231, 0.0266, 0.0278, 0.0349, 0.0349, 0.0349, 0.0349, 0.0349, 0.0349]
    intensitiesHigh = [0.0534, 0.0534, 0.0564, 0.06, 0.0614, 0.0696, 0.0696, 0.0696, 0.0696, 0.0696, 0.0696]
    ctptyRRLow = 0.4
    ctptyRRMedium = 0.35
    ctptyRRHigh = 0.3
    blackVol = 0.15

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
