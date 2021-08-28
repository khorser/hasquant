module QuantLib.Example.BermudanSwaption
  (
    Result(..)
  , run
  )
where

import Control.Monad(forM_)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IRI
import QuantLib.InterestRate
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.Instrument.Option
import QuantLib.Math
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
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
  , npvAtm :: [Double]
  , npvOtm :: [Double]
  , npvItm :: [Double]
  }

run :: IO Result
run = do
  cal <- calendar TARGET
  setEvaluationDate $ Just tod
  flatRate <- simpleQuote 0.04875825 >>= asQuote
  dc365 <- dayCounter Actual365FixedStandard
  ts <- flatForward settl flatRate dc365 Continuous Annual
  fixedDC <- dayCounter Thirty360European
  index6m <- IRI.iborIndex IRI.Euribor6M (Just ts)
  start <- advance cal settl (1, Years) floatConv False
  maturity <- advance cal start (5, Years) floatConv False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal fixedConv fixedConv Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal floatConv floatConv Forward False Nothing Nothing
  floatDC <- IRI.asInterestRateIndex index6m >>= IRI.dayCounter
  swp <- vanillaSwap swapType 1000.0 fixedSchedule dummyFixRate fixedDC floatSchedule index6m 0.0
    floatDC floatConv
  engine <- discountingSwapEngine ts Nothing Nothing Nothing
  asSwap swp >>= asInstrument >>= (`setPricingEngine` engine)
  fixedATMRate <- fairRate swp
  (swaptions, tms) <- unzip <$> mapM (createHelpers index6m ts) rows
  grid <- timeGridFromList' (concat tms) 30

  modelG2 <- Model.g2 ts 0.1 0.01 0.1 0.01 (-0.75)
  forM_ swaptions (\s -> g2SwaptionEngine modelG2 6.0 16 >>= setPricingEngine s)
  modelG2' <- Model.asShortRateModel modelG2 >>= Model.asCalibratedModel
  g2v <- calibrateModel modelG2' swaptions
  g2p <- Model.params modelG2'

  modelHW <- Model.hullWhite ts 0.1 0.01
  modelHWo <- Model.asOneFactorAffineModel modelHW
  forM_ swaptions (\s -> jamshidianSwaptionEngine modelHWo Nothing >>= setPricingEngine s)
  modelHW' <- Model.asShortRateModel modelHWo >>= Model.asCalibratedModel
  hwv <- calibrateModel modelHW' swaptions
  hwp <- Model.params modelHW'

  modelHW2 <- Model.hullWhite ts 0.1 0.01
  modelHW2s <- Model.asOneFactorAffineModel modelHW2 >>= Model.asShortRateModel
  forM_ swaptions (\s -> treeSwaptionEngine' modelHW2s grid Nothing>>= setPricingEngine s)
  modelHW2' <- Model.asCalibratedModel modelHW2s
  hw2v <- calibrateModel modelHW2' swaptions
  hw2p <- Model.params modelHW2'

  modelBK <- Model.blackKarasinski ts 0.1 0.1
  forM_ swaptions (\s -> treeSwaptionEngine' modelBK grid Nothing>>= setPricingEngine s)
  modelBK' <- Model.asCalibratedModel modelBK
  bkv <- calibrateModel modelBK' swaptions
  bkp <- Model.params modelBK'

  atmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedATMRate fixedDC floatSchedule index6m 0.0
    floatDC floatConv

  bermudanDates <- fixedLeg swp >>= CF.asCouponLeg >>= CF.couponAccrualStartDates
  let ex = Bermudan (BermudanExercise bermudanDates False)
  atmSwaption <- swaption atmSwap ex Physical >>= asOption >>= asInstrument

  npvA <- priceSwaption atmSwaption modelG2 50 modelHW modelHW2 modelBK

  let fixedOTMRate = fixedATMRate * 1.2
      fixedITMRate = fixedATMRate * 0.8
  otmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedOTMRate fixedDC floatSchedule index6m 0.0
    floatDC floatConv
  otmSwaption <- swaption otmSwap ex Physical >>= asOption >>= asInstrument

  itmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedITMRate fixedDC floatSchedule index6m 0.0
    floatDC floatConv
  itmSwaption <- swaption itmSwap ex Physical >>= asOption >>= asInstrument

  npvO <- priceSwaption otmSwaption modelG2 300 modelHW modelHW2 modelBK
  npvI <- priceSwaption itmSwaption modelG2 50 modelHW modelHW2 modelBK

  return Result {
    g2Vols = g2v
  , g2Params = g2p
  , hwVols = hwv
  , hwParams = hwp
  , hw2Vols = hw2v
  , hw2Params = hw2p
  , bkVols = bkv
  , bkParams = bkp
  , npvAtm = npvA
  , npvOtm = npvO
  , npvItm = npvI
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
        fixedConv = Unadjusted
        floatConv = ModifiedFollowing
        dummyFixRate = 0.03
        swapType = Payer

        createHelpers index6m ts i = do
          let j = numCols - i - 1
              k = fromIntegral $ i * numCols + j
          vol <- simpleQuote (swaptionVols!!k) >>= asQuote
          index6mRI <- IRI.asInterestRateIndex index6m
          dc <- IRI.dayCounter index6mRI
          tenr <- IRI.tenor index6mRI
          h <- Model.swaptionHelper (i+1, Years) (swapLengths!!(fromIntegral j), Years) vol index6m tenr dc dc ts Model.RelativePriceError
          tms <- Model.times h
          return (h, tms)

        calibrateModel m hs = do
          hsh <- mapM Model.asCalibrationHelper hs
          Model.calibrate m (zip hsh $ repeat 1.0) (LevenbergMarquardt 1.0e-8 1.0e-8 1.0e-8) (EndCriteria 400 100 1.0e-8 1.0e-8 1.0e-8) Nothing
          mapM calibrate hs

        calibrate h = do
          nPV <- Model.modelValue h
          vol <- Model.impliedVolatility h nPV 1.0e-4 1000 0.05 0.50
          return $ 100.0 * vol

        priceSwaption swption modelG2 g2n modelHW modelHW2 modelBK = do
          modelG2s <- Model.asShortRateModel modelG2
          treeSwaptionEngine modelG2s g2n Nothing >>= setPricingEngine swption
          npvG2tree <- npv swption
          fdG2SwaptionEngine modelG2 100 50 50 0 1.0e-5 Hundsdorfer >>= setPricingEngine swption
          npvG2fd <- npv swption

          modelHWs <- Model.asOneFactorAffineModel modelHW >>= Model.asShortRateModel
          treeSwaptionEngine modelHWs 50 Nothing >>= setPricingEngine swption
          npvHWtree <- npv swption
          fdHullWhiteSwaptionEngine modelHW 100 100 0 1.0e-5 Douglas >>= setPricingEngine swption
          npvHWfd <- npv swption

          modelHW2s <- Model.asOneFactorAffineModel modelHW2 >>= Model.asShortRateModel
          treeSwaptionEngine modelHW2s 50 Nothing >>= setPricingEngine swption
          npvHW2numtree <- npv swption
          fdHullWhiteSwaptionEngine modelHW2 100 100 0 1.0e-5 Douglas >>= setPricingEngine swption
          npvHW2numfd <- npv swption

          treeSwaptionEngine modelBK 50 Nothing >>= setPricingEngine swption
          npvBK <- npv swption
          return [npvG2tree, npvG2fd, npvHWtree, npvHWfd, npvHW2numtree, npvHW2numfd, npvBK]


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
