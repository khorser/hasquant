module QuantLib.Example.BermudanSwaption
  (
    Result(..)
  , run
  )
where

import Control.Applicative((<$>))
import Control.Monad(forM_)

import QuantLib.Compounding
import QuantLib.Index
import QuantLib.Index.Ibor
import QuantLib.Instances
import QuantLib.Instrument.Swap
import QuantLib.Instrument.VanillaSwapType
import QuantLib.Math.Optimization
import QuantLib.Model.CalibrationErrorType
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.Time.Unit
import QuantLib.Types
import QuantLib.TermStructure.Yield
import qualified QuantLib.Model as Model

data Result = Result
  { g2Vols :: [Double]
  , g2Params :: [Double]
  , hwVols :: [Double]
  , hwParams :: [Double]
  , hw2Vols :: [Double]
  , hw2Params :: [Double]
  , bkVols :: [Double]
  , bkParams :: [Double]
  }

run :: IO Result
run = do
  cal <- target
  setEvaluationDate tod
  flatRate <- simpleQuote 0.04875825 >>= asQuote
  dc365 <- actual365Fixed
  ts <- flatForward settl flatRate dc365 Continuous Annual
  fixedDC <- thirty360European
  index6m <- euribor6M $ Just ts
  start <- advance cal settl 1 Years floatConv False
  maturity <- advance cal start 5 Years floatConv False
  fixedPeriod <- fromFrequency fixedFreq
  floatPeriod <- fromFrequency floatFreq
  fixedSchedule <- schedule (Just start) maturity fixedPeriod cal fixedConv fixedConv Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity floatPeriod cal floatConv floatConv Forward False Nothing Nothing
  floatDC <- asInterestRateIndex index6m >>= dayCounter
  swp <- vanillaSwap swapType 1000.0 fixedSchedule dummyFixRate fixedDC floatSchedule index6m 0.0
    floatDC floatConv
  engine <- discountingSwapEngine ts Nothing Nothing Nothing
  asSwap swp >>= asInstrument >>= (`setPricingEngine` engine)
  fixedATMRate <- fairRate swp
  (swaptions, tms) <- unzip <$> mapM (createHelpers index6m ts) rows
  grid <- Model.timeGridFromList' (concat tms) 30

  modelG2 <- Model.g2 ts 0.1 0.01 0.1 0.01 (-0.75)
  forM_ swaptions (\s -> g2SwaptionEngine modelG2 6.0 16 >>= setPricingEngine s)
  modelG2' <- asShortRateModel modelG2 >>= asCalibratedModel
  g2v <- calibrateModel modelG2' swaptions
  g2p <- Model.params modelG2'

  modelHW <- Model.hullWhite ts 0.1 0.01 >>= asOneFactorAffineModel
  forM_ swaptions (\s -> jamshidianSwaptionEngine modelHW Nothing >>= setPricingEngine s)
  modelHW' <- asShortRateModel modelHW >>= asCalibratedModel
  hwv <- calibrateModel modelHW' swaptions
  hwp <- Model.params modelHW'

  modelHW2 <- Model.hullWhite ts 0.1 0.01 >>= asOneFactorAffineModel >>= asShortRateModel
  forM_ swaptions (\s -> treeSwaptionEngine' modelHW2 grid Nothing>>= setPricingEngine s)
  modelHW2' <- asCalibratedModel modelHW2
  hw2v <- calibrateModel modelHW2' swaptions
  hw2p <- Model.params modelHW2'

  modelBK <- Model.blackKarasinski ts 0.1 0.1
  forM_ swaptions (\s -> treeSwaptionEngine' modelBK grid Nothing>>= setPricingEngine s)
  modelBK' <- asCalibratedModel modelBK
  bkv <- calibrateModel modelBK' swaptions
  bkp <- Model.params modelBK'

  --hwVols <- asShortRateModel modelHW >>= asCalibratedModel >>= (`calibrateModel` swaptions)
  --hw2Vols <- asCalibratedModel modelHW2 >>= (`calibrateModel` swaptions)
  --bkVols <- asCalibratedModel modelBK >>= (`calibrateModel` swaptions)
  --let fixedOTMRate = fixedATMRate * 1.2
  --    fixedITMRate = fixedATMRate * 0.8
  --atmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedATMRate fixedDC floatSchedule index6m 0.0
  --  floatDC floatConv
  --otmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedOTMRate fixedDC floatSchedule index6m 0.0
  --  floatDC floatConv
  --itmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedITMRate fixedDC floatSchedule index6m 0.0
  --  floatDC floatConv

  return Result {
    g2Vols = g2v
  , g2Params = g2p
  , hwVols = hwv
  , hwParams = hwp
  , hw2Vols = hw2v
  , hw2Params = hw2p
  , bkVols = bkv
  , bkParams = bkp
  }
  where tod = 15 `february` 2002
        settl = 19 `february` 2002
        rows = [0 .. 4]
        numCols = 5
        swapLengths = [1, 2, 3, 4, 5]
        swaptionVols = [0.1490, 0.1340, 0.1228, 0.1189, 0.1148,
          0.1290, 0.1201, 0.1146, 0.1108, 0.1040,
          0.1149, 0.1112, 0.1070, 0.1010, 0.0957,
          0.1047, 0.1021, 0.0980, 0.0951, 0.1270,
          0.1000, 0.0950, 0.0900, 0.1230, 0.1160]
        fixedFreq = Annual
        fixedConv = Unadjusted
        floatConv = ModifiedFollowing
        floatFreq = Semiannual
        dummyFixRate = 0.03
        swapType = Payer

        createHelpers index6m ts i = do
          let j = numCols - i - 1
              k = i * numCols + j
          maturity <- period (i+1) Years
          vol <- simpleQuote (swaptionVols!!k) >>= asQuote
          len <- period (swapLengths!!j) Years
          index6mRI <- asInterestRateIndex index6m
          dc <- dayCounter index6mRI
          tenr <- tenor index6mRI
          h <- Model.swaptionHelper maturity len vol index6m tenr dc dc ts RelativePriceError
          tms <- Model.times h
          return (h, tms)

        calibrateModel m hs = do
          cr <- endCriteria 400 100 1.0e-8 1.0e-8 1.0e-8
          om <- levenbergMarquardt 1.0e-8 1.0e-8 1.0e-8
          Model.calibrate m (zip hs $ repeat 1.0) om cr Nothing
          mapM calibrate hs

        calibrate h = do
          npv <- Model.modelValue h
          vol <- Model.impliedVolatility h npv 1.0e-4 1000 0.05 0.50
          return $ 100.0 * vol


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
