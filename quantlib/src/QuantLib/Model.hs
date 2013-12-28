{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Model
  (
    batesModel
  , blackKarasinski
  , coxIngersollRoss
  , extendedCoxIngersollRoss
  , g2
  , generalizedHullWhite'
  , generalizedHullWhite
  , gJRGARCHModel
  , hestonModel
  , hullWhite
  , varianceGammaModel
  , vasicek
  , lmConstWrapperCorrelationModel
  , lmConstWrapperVolatilityModel
  , lmExponentialCorrelationModel
  , lmFixedVolatilityModel
  , lmLinearExponentialCorrelationModel
  , lmLinearExponentialVolatilityModel
  , liborForwardModel

  , calibrate
  , capHelper
  , hestonModelHelper
  , swaptionHelper
  , times

  , timeGrid
  , timeGridFromList
  , timeGridFromList'

  , params
  , blackPrice
  , calibrationError
  , impliedVolatility
  , marketValue
  , modelValue
  )
where

import Data.Functor((<$>))

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Model.CalibrationErrorType(CalibrationErrorType)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Unit(Unit)
import QuantLib.Types

batesModel :: BatesProcess s -- ^process
  -> QLE s (BatesModel s)
batesModel = $(ffiCall 'batesModel) c_batesModel

foreign import ccall safe "ql.h qlBatesModel"
  c_batesModel :: Ptr CBatesProcess -> Ptr CString -> IO (Ptr CBatesModel)

blackKarasinski :: YieldTermStructure s -- ^termStructure
  -> Double -- ^a
  -> Double -- ^sigma
  -> QLE s (ShortRateModel s)
blackKarasinski = $(ffiCall 'blackKarasinski) c_blackKarasinski

foreign import ccall safe "ql.h qlBlackKarasinski"
  c_blackKarasinski :: Ptr CYieldTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CShortRateModel)

coxIngersollRoss :: Double -- ^r0
  -> Double -- ^theta
  -> Double -- ^k
  -> Double -- ^sigma
  -> QLE s (OneFactorAffineModel s)
coxIngersollRoss = $(ffiCall 'coxIngersollRoss) c_coxIngersollRoss

foreign import ccall safe "ql.h qlCoxIngersollRoss"
  c_coxIngersollRoss :: CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneFactorAffineModel)

extendedCoxIngersollRoss :: YieldTermStructure s -- ^termStructure
  -> Double -- ^theta
  -> Double -- ^k
  -> Double -- ^sigma
  -> Double -- ^x0
  -> QLE s (OneFactorAffineModel s)
extendedCoxIngersollRoss = $(ffiCall 'extendedCoxIngersollRoss) c_extendedCoxIngersollRoss

foreign import ccall safe "ql.h qlExtendedCoxIngersollRoss"
  c_extendedCoxIngersollRoss :: Ptr CYieldTermStructure -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneFactorAffineModel)

g2 :: YieldTermStructure s -- ^termStructure
  -> Double -- ^a
  -> Double -- ^sigma
  -> Double -- ^b
  -> Double -- ^eta
  -> Double -- ^rho
  -> QLE s (G2 s)
g2 = $(ffiCall 'g2) c_g2

foreign import ccall safe "ql.h qlG2"
  c_g2 :: Ptr CYieldTermStructure -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CG2)

generalizedHullWhite' :: YieldTermStructure s -- ^yieldtermStructure
  -> [Day] -- ^speedstructure
  -> [Day] -- ^volstructure
  -> [Double] -- ^speed
  -> [Double] -- ^vol
  -> QLE s (ShortRateModel s)
generalizedHullWhite' = $(ffiCall 'generalizedHullWhite') c_generalizedHullWhite'

foreign import ccall safe "ql.h qlGeneralizedHullWhite1"
  c_generalizedHullWhite' :: Ptr CYieldTermStructure -> CUInt -> Ptr CDate -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CShortRateModel)

generalizedHullWhite :: YieldTermStructure s -- ^yieldtermStructure
  -> [Day] -- ^speedstructure
  -> [Day] -- ^volstructure
  -> QLE s (ShortRateModel s)
generalizedHullWhite = $(ffiCall 'generalizedHullWhite) c_generalizedHullWhite

foreign import ccall safe "ql.h qlGeneralizedHullWhite"
  c_generalizedHullWhite :: Ptr CYieldTermStructure -> CUInt -> Ptr CDate -> CUInt -> Ptr CDate -> Ptr CString -> IO (Ptr CShortRateModel)

gJRGARCHModel :: GJRGARCHProcess s -- ^process
  -> QLE s (GJRGARCHModel s)
gJRGARCHModel = $(ffiCall 'gJRGARCHModel) c_gJRGARCHModel

foreign import ccall safe "ql.h qlGJRGARCHModel"
  c_gJRGARCHModel :: Ptr CGJRGARCHProcess -> Ptr CString -> IO (Ptr CGJRGARCHModel)

hestonModel :: HestonProcess s -- ^process
  -> QLE s (HestonModel s)
hestonModel = $(ffiCall 'hestonModel) c_hestonModel

foreign import ccall safe "ql.h qlHestonModel"
  c_hestonModel :: Ptr CHestonProcess -> Ptr CString -> IO (Ptr CHestonModel)

hullWhite :: YieldTermStructure s -- ^termStructure
  -> Double -- ^a
  -> Double -- ^sigma
  -> QLE s (HullWhite s)
hullWhite = $(ffiCall 'hullWhite) c_hullWhite

foreign import ccall safe "ql.h qlHullWhite"
  c_hullWhite :: Ptr CYieldTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CHullWhite)

varianceGammaModel :: VarianceGammaProcess s -- ^process
  -> QLE s (CalibratedModel s)
varianceGammaModel = $(ffiCall 'varianceGammaModel) c_varianceGammaModel

foreign import ccall safe "ql.h qlVarianceGammaModel"
  c_varianceGammaModel :: Ptr CVarianceGammaProcess -> Ptr CString -> IO (Ptr CCalibratedModel)

vasicek :: Double -- ^r0
  -> Double -- ^a
  -> Double -- ^b
  -> Double -- ^sigma
  -> Double -- ^lambda
  -> QLE s (OneFactorAffineModel s)
vasicek = $(ffiCall 'vasicek) c_vasicek

foreign import ccall safe "ql.h qlVasicek"
  c_vasicek :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneFactorAffineModel)

lmConstWrapperCorrelationModel :: LmCorrelationModel s -- ^corrModel
  -> QLE s (LmCorrelationModel s)
lmConstWrapperCorrelationModel = $(ffiCall 'lmConstWrapperCorrelationModel) c_lmConstWrapperCorrelationModel

foreign import ccall safe "ql.h qlLmConstWrapperCorrelationModel"
  c_lmConstWrapperCorrelationModel :: Ptr CLmCorrelationModel -> Ptr CString -> IO (Ptr CLmCorrelationModel)

lmConstWrapperVolatilityModel :: LmVolatilityModel s -- ^volaModel
  -> QLE s (LmVolatilityModel s)
lmConstWrapperVolatilityModel = $(ffiCall 'lmConstWrapperVolatilityModel) c_lmConstWrapperVolatilityModel

foreign import ccall safe "ql.h qlLmConstWrapperVolatilityModel"
  c_lmConstWrapperVolatilityModel :: Ptr CLmVolatilityModel -> Ptr CString -> IO (Ptr CLmVolatilityModel)

lmExponentialCorrelationModel :: Word -- ^size
  -> Double -- ^rho
  -> QLE s (LmCorrelationModel s)
lmExponentialCorrelationModel = $(ffiCall 'lmExponentialCorrelationModel) c_lmExponentialCorrelationModel

foreign import ccall safe "ql.h qlLmExponentialCorrelationModel"
  c_lmExponentialCorrelationModel :: CUInt -> CDouble -> Ptr CString -> IO (Ptr CLmCorrelationModel)

lmFixedVolatilityModel :: [Double] -- ^volatilities
  -> [YearFraction] -- ^startTimes
  -> QLE s (LmVolatilityModel s)
lmFixedVolatilityModel = $(ffiCall 'lmFixedVolatilityModel) c_lmFixedVolatilityModel

foreign import ccall safe "ql.h qlLmFixedVolatilityModel"
  c_lmFixedVolatilityModel :: CUInt -> Ptr CDouble -> CUInt -> Ptr CYearFraction -> Ptr CString -> IO (Ptr CLmVolatilityModel)

lmLinearExponentialCorrelationModel :: Word -- ^size
  -> Double -- ^rho
  -> Double -- ^beta
  -> Word -- ^factors
  -> QLE s (LmCorrelationModel s)
lmLinearExponentialCorrelationModel = $(ffiCall 'lmLinearExponentialCorrelationModel) c_lmLinearExponentialCorrelationModel

foreign import ccall safe "ql.h qlLmLinearExponentialCorrelationModel"
  c_lmLinearExponentialCorrelationModel :: CUInt -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CLmCorrelationModel)

lmLinearExponentialVolatilityModel :: [YearFraction] -- ^fixingTimes
  -> Double -- ^a
  -> Double -- ^b
  -> Double -- ^c
  -> Double -- ^d
  -> QLE s (LmVolatilityModel s)
lmLinearExponentialVolatilityModel = $(ffiCall 'lmLinearExponentialVolatilityModel) c_lmLinearExponentialVolatilityModel

foreign import ccall safe "ql.h qlLmLinearExponentialVolatilityModel"
  c_lmLinearExponentialVolatilityModel :: CUInt -> Ptr CYearFraction -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CLmVolatilityModel)

liborForwardModel :: LiborForwardModelProcess s -- ^process
  -> LmVolatilityModel s -- ^volaModel
  -> LmCorrelationModel s -- ^corrModel
  -> QLE s (LiborForwardModel s)
liborForwardModel = $(ffiCall 'liborForwardModel) c_liborForwardModel

foreign import ccall safe "ql.h qlLiborForwardModel"
  c_liborForwardModel :: Ptr CLiborForwardModelProcess -> Ptr CLmVolatilityModel -> Ptr CLmCorrelationModel -> Ptr CString -> IO (Ptr CLiborForwardModel)

-- |Calibrate to a set of market instruments (caps/swaptions)
-- An additional constraint can be passed which must be satisfied in addition to the constraints of the model.
calibrate :: CalibratedModel s
  -> [(CalibrationHelper s, Double)] -- ^(instruments, weights)
  -> OptimizationMethod s -- ^method
  -> EndCriteria s -- ^endCriteria
  -> Maybe (Constraint s) -- ^constraint
  -> QLE s ()
calibrate = $(ffiCallX 'calibrate) c_calibrate

foreign import ccall safe "ql.h qlCalibratedModelCalibrate"
  c_calibrate :: Ptr CCalibratedModel -> CUInt -> Ptr (Ptr CCalibrationHelper) -> Ptr CDouble -> Ptr COptimizationMethod -> Ptr CEndCriteria -> Ptr CConstraint -> Ptr CString -> IO ()

capHelper :: (Int, Unit) -- ^length
  -> Quote s -- ^volatility
  -> IborIndex s -- ^index
  -> Frequency -- ^fixedLegFrequency
  -> DayCounter s -- ^fixedLegDayCounter
  -> Bool -- ^includeFirstSwaplet
  -> YieldTermStructure s -- ^termStructure
  -> CalibrationErrorType -- ^errorType
  -> QLE s (CalibrationHelper s)
capHelper = $(ffiCall 'capHelper) c_capHelper

foreign import ccall safe "ql.h qlCapHelper"
  c_capHelper :: CInt -> CInt -> Ptr CQuote -> Ptr CIborIndex -> CInt -> Ptr CDayCounter -> CInt -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CCalibrationHelper)

hestonModelHelper :: (Int, Unit) -- ^maturity
  -> Calendar s -- ^calendar
  -> Double -- ^s0
  -> Double -- ^strikePrice
  -> Quote s -- ^volatility
  -> YieldTermStructure s -- ^riskFreeRate
  -> YieldTermStructure s -- ^dividendYield
  -> CalibrationErrorType -- ^errorType
  -> QLE s (CalibrationHelper s)
hestonModelHelper = $(ffiCall 'hestonModelHelper) c_hestonModelHelper

foreign import ccall safe "ql.h qlHestonModelHelper"
  c_hestonModelHelper :: CInt -> CInt -> Ptr CCalendar -> CDouble -> CDouble -> Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CCalibrationHelper)

-- TODO git version of QuantLib features more parameters and two mode SwaptionHelper constructors
swaptionHelper :: (Int, Unit) -- ^maturity
  -> (Int, Unit) -- ^length
  -> Quote s -- ^volatility
  -> IborIndex s -- ^index
  -> (Int, Unit) -- ^fixedLegTenor
  -> DayCounter s -- ^fixedLegDayCounter
  -> DayCounter s -- ^floatingLegDayCounter
  -> YieldTermStructure s -- ^termStructure
  -> CalibrationErrorType -- ^errorType
  -> QLE s (CalibrationHelper s)
swaptionHelper = $(ffiCall 'swaptionHelper) c_swaptionHelper

foreign import ccall safe "ql.h qlSwaptionHelper"
  c_swaptionHelper :: CInt -> CInt -> CInt -> CInt -> Ptr CQuote -> Ptr CIborIndex -> CInt -> CInt -> Ptr CDayCounter -> Ptr CDayCounter -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CCalibrationHelper)

times :: CalibrationHelper s -> QLE s [Double]
times x = mkQLE $ map realToFrac <$> withObject x (getArrayX . c_times)

foreign import ccall safe "ql.h qlCalibrationHelperTimes"
  c_times :: Ptr CCalibrationHelper -> Ptr CUInt -> Ptr CString -> IO (Ptr CDouble)

-- |Regularly spaced time-grid.
timeGrid :: YearFraction -- ^end
  -> Word -- ^steps
  -> QLE s (TimeGrid s)
timeGrid = $(ffiCall 'timeGrid) c_timeGrid

foreign import ccall safe "ql.h qlTimeGrid1"
  c_timeGrid :: CYearFraction -> CUInt -> Ptr CString -> IO (Ptr CTimeGrid)

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. No additional points are added.
timeGridFromList :: [Double]
  -> QLE s (TimeGrid s)
timeGridFromList = $(ffiCall 'timeGridFromList) c_timeGridFromList

foreign import ccall safe "ql.h qlTimeGrid2"
  c_timeGridFromList :: CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CTimeGrid)

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. Additional points are then added with regular spacing between pairs of mandatory times in order to reach the desired number of steps.
timeGridFromList' :: [Double]
  -> Word -- ^steps
  -> QLE s (TimeGrid s)
timeGridFromList' = $(ffiCall 'timeGridFromList') c_timeGridFromList'

foreign import ccall safe "ql.h qlTimeGrid3"
  c_timeGridFromList' :: CUInt -> Ptr CDouble -> CUInt -> Ptr CString -> IO (Ptr CTimeGrid)

-- |Returns array of arguments on which calibration is done.
params :: CalibratedModel s
  -> QLE s [Double]
params x = mkQLE $ map realToFrac <$> withObject x (getArrayX . c_params)

foreign import ccall safe "ql.h qlCalibratedModelParams"
  c_params :: Ptr CCalibratedModel -> Ptr CUInt -> Ptr CString -> IO (Ptr CDouble)

-- |Black price given a volatility.
blackPrice :: CalibrationHelper s
  -> Double -- ^volatility
  -> QLE s Double
blackPrice = $(ffiCallX 'blackPrice) c_blackPrice

foreign import ccall safe "ql.h qlCalibrationHelperBlackPrice"
  c_blackPrice :: Ptr CCalibrationHelper -> CDouble -> Ptr CString -> IO CDouble

-- |returns the error resulting from the model valuation
calibrationError :: CalibrationHelper s -> QLE s Double
calibrationError = $(ffiCallX 'calibrationError) c_calibrationError

foreign import ccall safe "ql.h qlCalibrationHelperCalibrationError"
  c_calibrationError :: Ptr CCalibrationHelper -> Ptr CString -> IO CDouble

-- |Black volatility implied by the model.
impliedVolatility :: CalibrationHelper s
  -> Double -- ^targetValue
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> QLE s Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

foreign import ccall safe "ql.h qlCalibrationHelperImpliedVolatility"
  c_impliedVolatility :: Ptr CCalibrationHelper -> CDouble -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |returns the actual price of the instrument (from volatility)
marketValue :: CalibrationHelper s
  -> QLE s Double
marketValue = $(ffiCallX 'marketValue) c_marketValue

foreign import ccall safe "ql.h qlCalibrationHelperMarketValue"
  c_marketValue :: Ptr CCalibrationHelper -> Ptr CString -> IO CDouble

-- |returns the price of the instrument according to the model
modelValue :: CalibrationHelper s
  -> QLE s Double
modelValue = $(ffiCallX 'modelValue) c_modelValue

foreign import ccall safe "ql.h qlCalibrationHelperModelValue"
  c_modelValue :: Ptr CCalibrationHelper -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
