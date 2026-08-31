{-# LANGUAGE TupleSections #-}
module QuantLib.Example.BermudanSwaption
  (
    Result(..)
  , run
  ) where
import Control.Monad((>=>), forM_, mapAndUnzipM)
import qualified Data.Vector.Storable as V

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

calibrateModel :: Model.CalibratedModel -> [Model.BlackCalibrationHelper] -> IO [Double]
calibrateModel m hs = do
  hsh <- mapM Model.asCalibrationHelper hs
  Model.calibrate m (map (, 1.0) hsh) (LevenbergMarquardt 1.0e-8 1.0e-8 1.0e-8 False) (EndCriteria 400 100 1.0e-8 1.0e-8 1.0e-8) Nothing []
  mapM calibrate hs

calibrate :: Model.BlackCalibrationHelper -> IO Double
calibrate h = do
  nPV <- Model.modelValue h
  vol <- Model.impliedVolatility h nPV 1.0e-4 1000 0.05 0.50
  return $ 100.0 * vol

-- |Builds a short-rate model, attaches a pricing engine to the calibration
-- swaptions, calibrates it and returns the (still-untouched) model alongside
-- its calibrated vols/params. The model itself -- not just its calibration
-- output -- is what the pricing phase needs next, since 'priceSwaption'
-- re-derives its own engines from it.
calibrateShortRateModel
  :: IO m                                             -- ^model constructor
  -> (m -> [Model.BlackCalibrationHelper] -> IO ())   -- ^attach a pricing engine for calibration
  -> (m -> IO Model.CalibratedModel)                  -- ^narrow to the calibratable interface
  -> [Model.BlackCalibrationHelper]
  -> IO (m, [Double], [Double])
calibrateShortRateModel buildModel attachEngine toCalibratable swaptions = do
  m <- buildModel
  attachEngine m swaptions
  calibratable <- toCalibratable m
  vols <- calibrateModel calibratable swaptions
  ps <- Model.params calibratable
  return (m, vols, ps)

run :: IO Result
run = do
  cal <- calendar TARGET
  setEvaluationDate $ Just evalDate
  flatRate <- simpleQuote 0.04875825 >>= asQuote -- just to test that explicit casting works
  dc365 <- dayCounter Actual365FixedStandard
  ts <- flatForward settl flatRate dc365 Continuous Annual
  fixedDC <- dayCounter Thirty360European
  index6m <- IRI.iborIndex IRI.Euribor6M (Just ts)
  start <- advance cal settl (1, Years) floatConv False
  maturity <- advance cal start (5, Years) floatConv False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal fixedConv fixedConv Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal floatConv floatConv Forward False Nothing Nothing
  floatDC <- IRI.dayCounter index6m
  swp <- vanillaSwap swapType 1000.0 fixedSchedule dummyFixRate fixedDC floatSchedule index6m 0.0
    floatDC (Just floatConv) Nothing
  engine <- discountingSwapEngine ts Nothing Nothing Nothing
  asSwap swp >>= asInstrument >>= (`setPricingEngine` engine)
  fixedATMRate <- fairRate swp
  (swaptionHelpers, tms) <- mapAndUnzipM (createHelpers index6m ts) calibrationGrid
  swaptions <- mapM Model.asBlackCalibrationHelper swaptionHelpers
  grid <- maybe (fail "BermudanSwaption: empty calibration grid") (flip timeGridFromVector' 30) (nonEmptyVector (V.fromList (concat tms)))

  (modelG2, g2v, g2p) <- calibrateShortRateModel
    (Model.g2 ts 0.1 0.01 0.1 0.01 (-0.75))
    (\m ss -> forM_ ss (\s -> g2SwaptionEngine m 6.0 16 >>= Model.setPricingEngine s))
    (Model.asShortRateModel >=> Model.asCalibratedModel)
    swaptions

  (modelHW, hwv, hwp) <- calibrateShortRateModel
    (Model.hullWhite ts 0.1 0.01)
    (\m ss -> do
      modelHWo <- Model.asOneFactorAffineModel m
      forM_ ss (\s -> jamshidianSwaptionEngine modelHWo Nothing >>= Model.setPricingEngine s))
    (\m -> Model.asOneFactorAffineModel m >>= Model.asShortRateModel >>= Model.asCalibratedModel)
    swaptions

  (modelHW2, hw2v, hw2p) <- calibrateShortRateModel
    (Model.hullWhite ts 0.1 0.01)
    (\m ss -> do
      modelHW2s <- Model.asOneFactorAffineModel m >>= Model.asShortRateModel
      forM_ ss (\s -> treeSwaptionEngine' modelHW2s grid Nothing >>= Model.setPricingEngine s))
    (\m -> Model.asOneFactorAffineModel m >>= Model.asShortRateModel >>= Model.asCalibratedModel)
    swaptions

  (modelBK, bkv, bkp) <- calibrateShortRateModel
    (Model.blackKarasinski ts 0.1 0.1)
    (\m ss -> forM_ ss (\s -> treeSwaptionEngine' m grid Nothing >>= Model.setPricingEngine s))
    Model.asCalibratedModel
    swaptions

  atmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedATMRate fixedDC floatSchedule index6m 0.0
    floatDC (Just floatConv) Nothing

  bermudanDates <- fixedLeg swp >>= CF.toCouponLeg >>= CF.couponAccrualStartDates
  let ex = Bermudan (BermudanExercise bermudanDates False)
  atmSwaption <- swaption atmSwap ex Physical PhysicalOTC

  npvA <- priceSwaption atmSwaption modelG2 50 modelHW modelHW2 modelBK

  let fixedOTMRate = fixedATMRate * 1.2
      fixedITMRate = fixedATMRate * 0.8
  otmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedOTMRate fixedDC floatSchedule index6m 0.0
    floatDC (Just floatConv) Nothing
  otmSwaption <- swaption otmSwap ex Physical PhysicalOTC

  itmSwap <- vanillaSwap swapType 1000.0 fixedSchedule fixedITMRate fixedDC floatSchedule index6m 0.0
    floatDC (Just floatConv) Nothing
  itmSwaption <- swaption itmSwap ex Physical PhysicalOTC

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
  where evalDate = 15 `february` 2002
        settl = 19 `february` 2002
        swapLengths :: [Word]
        swapLengths = [1, 2, 3, 4, 5]
        -- Market swaption vols: rows are option expiries; columns are swap lengths.
        swaptionVolTable = [
          [0.1490, 0.1340, 0.1228, 0.1189, 0.1148],
          [0.1290, 0.1201, 0.1146, 0.1108, 0.1040],
          [0.1149, 0.1112, 0.1070, 0.1010, 0.0957],
          [0.1047, 0.1021, 0.0980, 0.0951, 0.1270],
          [0.1000, 0.0950, 0.0900, 0.1230, 0.1160]]

        -- The example calibrates against the anti-diagonal of that table: expiry i+1
        -- years against the swap length in column (numCols - 1 - i), giving 1x5, 2x4,
        -- 3x3, 4x2, 5x1. Built by pattern-matching a `drop` rather than indexing, so
        -- there is no partial `!!` and a mis-sized row drops out instead of crashing.
        calibrationGrid :: [(Word, Word, Double)] -- (expiry years, swap length years, vol)
        calibrationGrid =
          [ (fromIntegral i + 1, len, vol)
          | (i, row) <- zip [0 :: Int ..] swaptionVolTable
          , ((len, vol) : _) <- [drop (length row - 1 - i) (zip swapLengths row)]
          ]
        fixedConv = Unadjusted
        floatConv = ModifiedFollowing
        dummyFixRate = 0.03
        swapType = Payer

        createHelpers index6m ts (expiry, len, volValue) = do
          vol <- simpleQuote volValue
          dc <- IRI.dayCounter index6m
          tenr <- IRI.tenor index6m
          h <- Model.swaptionHelper (expiry, Years) (len, Years) vol index6m tenr dc dc ts Model.RelativePriceError Nothing 1.0 ShiftedLognormal 0.0 Nothing CF.AveragingCompound
          tms <- Model.times h
          return (h, tms)

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
