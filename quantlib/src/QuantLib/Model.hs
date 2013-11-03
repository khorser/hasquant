{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
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
  , setPricingEngine
  , capHelper
  , hestonModelHelper
  , swaptionHelper
  , times

  , timeGrid
  , timeGridFromList
  , timeGridFromList'
  )
where

import Data.Functor((<$>))

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Model.CalibrationErrorType
import QuantLib.Time.Frequency
import QuantLib.Types

batesModel :: BatesProcess -- ^process
  -> IO BatesModel
batesModel = $(ffiCall 'batesModel) c_batesModel

foreign import ccall safe "ql.h qlBatesModel"
  c_batesModel :: Ptr CBatesProcess -> Ptr CString -> IO (Ptr CBatesModel)

blackKarasinski :: YieldTermStructure -- ^termStructure
  -> Double -- ^a
  -> Double -- ^sigma
  -> IO ShortRateModel
blackKarasinski = $(ffiCall 'blackKarasinski) c_blackKarasinski

foreign import ccall safe "ql.h qlBlackKarasinski"
  c_blackKarasinski :: Ptr CYieldTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CShortRateModel)

coxIngersollRoss :: Double -- ^r0
  -> Double -- ^theta
  -> Double -- ^k
  -> Double -- ^sigma
  -> IO OneFactorAffineModel
coxIngersollRoss = $(ffiCall 'coxIngersollRoss) c_coxIngersollRoss

foreign import ccall safe "ql.h qlCoxIngersollRoss"
  c_coxIngersollRoss :: CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneFactorAffineModel)

extendedCoxIngersollRoss :: YieldTermStructure -- ^termStructure
  -> Double -- ^theta
  -> Double -- ^k
  -> Double -- ^sigma
  -> Double -- ^x0
  -> IO OneFactorAffineModel
extendedCoxIngersollRoss = $(ffiCall 'extendedCoxIngersollRoss) c_extendedCoxIngersollRoss

foreign import ccall safe "ql.h qlExtendedCoxIngersollRoss"
  c_extendedCoxIngersollRoss :: Ptr CYieldTermStructure -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneFactorAffineModel)

g2 :: YieldTermStructure -- ^termStructure
  -> Double -- ^a
  -> Double -- ^sigma
  -> Double -- ^b
  -> Double -- ^eta
  -> Double -- ^rho
  -> IO G2
g2 = $(ffiCall 'g2) c_g2

foreign import ccall safe "ql.h qlG2"
  c_g2 :: Ptr CYieldTermStructure -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CG2)

generalizedHullWhite' :: YieldTermStructure -- ^yieldtermStructure
  -> [Day] -- ^speedstructure
  -> [Day] -- ^volstructure
  -> [Double] -- ^speed
  -> [Double] -- ^vol
  -> IO ShortRateModel
generalizedHullWhite' = $(ffiCall 'generalizedHullWhite') c_generalizedHullWhite'

foreign import ccall safe "ql.h qlGeneralizedHullWhite1"
  c_generalizedHullWhite' :: Ptr CYieldTermStructure -> CUInt -> Ptr CDate -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CShortRateModel)

generalizedHullWhite :: YieldTermStructure -- ^yieldtermStructure
  -> [Day] -- ^speedstructure
  -> [Day] -- ^volstructure
  -> IO ShortRateModel
generalizedHullWhite = $(ffiCall 'generalizedHullWhite) c_generalizedHullWhite

foreign import ccall safe "ql.h qlGeneralizedHullWhite"
  c_generalizedHullWhite :: Ptr CYieldTermStructure -> CUInt -> Ptr CDate -> CUInt -> Ptr CDate -> Ptr CString -> IO (Ptr CShortRateModel)

gJRGARCHModel :: GJRGARCHProcess -- ^process
  -> IO GJRGARCHModel
gJRGARCHModel = $(ffiCall 'gJRGARCHModel) c_gJRGARCHModel

foreign import ccall safe "ql.h qlGJRGARCHModel"
  c_gJRGARCHModel :: Ptr CGJRGARCHProcess -> Ptr CString -> IO (Ptr CGJRGARCHModel)

hestonModel :: HestonProcess -- ^process
  -> IO HestonModel
hestonModel = $(ffiCall 'hestonModel) c_hestonModel

foreign import ccall safe "ql.h qlHestonModel"
  c_hestonModel :: Ptr CHestonProcess -> Ptr CString -> IO (Ptr CHestonModel)

hullWhite :: YieldTermStructure -- ^termStructure
  -> Double -- ^a
  -> Double -- ^sigma
  -> IO HullWhite
hullWhite = $(ffiCall 'hullWhite) c_hullWhite

foreign import ccall safe "ql.h qlHullWhite"
  c_hullWhite :: Ptr CYieldTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CHullWhite)

varianceGammaModel :: VarianceGammaProcess -- ^process
  -> IO CalibratedModel
varianceGammaModel = $(ffiCall 'varianceGammaModel) c_varianceGammaModel

foreign import ccall safe "ql.h qlVarianceGammaModel"
  c_varianceGammaModel :: Ptr CVarianceGammaProcess -> Ptr CString -> IO (Ptr CCalibratedModel)

vasicek :: Double -- ^r0
  -> Double -- ^a
  -> Double -- ^b
  -> Double -- ^sigma
  -> Double -- ^lambda
  -> IO OneFactorAffineModel
vasicek = $(ffiCall 'vasicek) c_vasicek

foreign import ccall safe "ql.h qlVasicek"
  c_vasicek :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneFactorAffineModel)

lmConstWrapperCorrelationModel :: LmCorrelationModel -- ^corrModel
  -> IO LmCorrelationModel
lmConstWrapperCorrelationModel = $(ffiCall 'lmConstWrapperCorrelationModel) c_lmConstWrapperCorrelationModel

foreign import ccall safe "ql.h qlLmConstWrapperCorrelationModel"
  c_lmConstWrapperCorrelationModel :: Ptr CLmCorrelationModel -> Ptr CString -> IO (Ptr CLmCorrelationModel)

lmConstWrapperVolatilityModel :: LmVolatilityModel -- ^volaModel
  -> IO LmVolatilityModel
lmConstWrapperVolatilityModel = $(ffiCall 'lmConstWrapperVolatilityModel) c_lmConstWrapperVolatilityModel

foreign import ccall safe "ql.h qlLmConstWrapperVolatilityModel"
  c_lmConstWrapperVolatilityModel :: Ptr CLmVolatilityModel -> Ptr CString -> IO (Ptr CLmVolatilityModel)

lmExponentialCorrelationModel :: Word -- ^size
  -> Double -- ^rho
  -> IO LmCorrelationModel
lmExponentialCorrelationModel = $(ffiCall 'lmExponentialCorrelationModel) c_lmExponentialCorrelationModel

foreign import ccall safe "ql.h qlLmExponentialCorrelationModel"
  c_lmExponentialCorrelationModel :: CUInt -> CDouble -> Ptr CString -> IO (Ptr CLmCorrelationModel)

lmFixedVolatilityModel :: [Double] -- ^volatilities
  -> [YearFraction] -- ^startTimes
  -> IO LmVolatilityModel
lmFixedVolatilityModel = $(ffiCall 'lmFixedVolatilityModel) c_lmFixedVolatilityModel

foreign import ccall safe "ql.h qlLmFixedVolatilityModel"
  c_lmFixedVolatilityModel :: CUInt -> Ptr CDouble -> CUInt -> Ptr CYearFraction -> Ptr CString -> IO (Ptr CLmVolatilityModel)

lmLinearExponentialCorrelationModel :: Word -- ^size
  -> Double -- ^rho
  -> Double -- ^beta
  -> Word -- ^factors
  -> IO LmCorrelationModel
lmLinearExponentialCorrelationModel = $(ffiCall 'lmLinearExponentialCorrelationModel) c_lmLinearExponentialCorrelationModel

foreign import ccall safe "ql.h qlLmLinearExponentialCorrelationModel"
  c_lmLinearExponentialCorrelationModel :: CUInt -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CLmCorrelationModel)

lmLinearExponentialVolatilityModel :: [YearFraction] -- ^fixingTimes
  -> Double -- ^a
  -> Double -- ^b
  -> Double -- ^c
  -> Double -- ^d
  -> IO LmVolatilityModel
lmLinearExponentialVolatilityModel = $(ffiCall 'lmLinearExponentialVolatilityModel) c_lmLinearExponentialVolatilityModel

foreign import ccall safe "ql.h qlLmLinearExponentialVolatilityModel"
  c_lmLinearExponentialVolatilityModel :: CUInt -> Ptr CYearFraction -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CLmVolatilityModel)

liborForwardModel :: LiborForwardModelProcess -- ^process
  -> LmVolatilityModel -- ^volaModel
  -> LmCorrelationModel -- ^corrModel
  -> IO LiborForwardModel
liborForwardModel = $(ffiCall 'liborForwardModel) c_liborForwardModel

foreign import ccall safe "ql.h qlLiborForwardModel"
  c_liborForwardModel :: Ptr CLiborForwardModelProcess -> Ptr CLmVolatilityModel -> Ptr CLmCorrelationModel -> Ptr CString -> IO (Ptr CLiborForwardModel)

-- |Calibrate to a set of market instruments (caps/swaptions)
-- An additional constraint can be passed which must be satisfied in addition to the constraints of the model.
calibrate :: CalibratedModel
  -> [(CalibrationHelper, Double)] -- ^(instruments, wieights)
  -> OptimizationMethod -- ^method
  -> EndCriteria -- ^endCriteria
  -> Constraint -- ^constraint
  -> IO ()
calibrate = $(ffiCallX 'calibrate) c_calibrate

foreign import ccall safe "ql.h qlCalibratedModelCalibrate"
  c_calibrate :: Ptr CCalibratedModel -> CUInt -> Ptr (Ptr CCalibrationHelper) -> Ptr CDouble -> Ptr COptimizationMethod -> Ptr CEndCriteria -> Ptr CConstraint -> Ptr CString -> IO ()

setPricingEngine :: CalibrationHelper
  -> PricingEngine -- ^engine
  -> IO ()
setPricingEngine = $(ffiCallX 'setPricingEngine) c_setPricingEngine

foreign import ccall safe "ql.h qlCalibrationHelperSetPricingEngine"
  c_setPricingEngine :: Ptr CCalibrationHelper -> Ptr CPricingEngine -> Ptr CString -> IO ()

capHelper :: Period -- ^length
  -> Quote -- ^volatility
  -> IborIndex -- ^index
  -> Frequency -- ^fixedLegFrequency
  -> DayCounter -- ^fixedLegDayCounter
  -> Bool -- ^includeFirstSwaplet
  -> YieldTermStructure -- ^termStructure
  -> CalibrationErrorType -- ^errorType
  -> IO CalibrationHelper
capHelper = $(ffiCall 'capHelper) c_capHelper

foreign import ccall safe "ql.h qlCapHelper"
  c_capHelper :: Ptr CPeriod -> Ptr CQuote -> Ptr CIborIndex -> CInt -> Ptr CDayCounter -> CInt -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CCalibrationHelper)

hestonModelHelper :: Period -- ^maturity
  -> Calendar -- ^calendar
  -> Double -- ^s0
  -> Double -- ^strikePrice
  -> Quote -- ^volatility
  -> YieldTermStructure -- ^riskFreeRate
  -> YieldTermStructure -- ^dividendYield
  -> CalibrationErrorType -- ^errorType
  -> IO CalibrationHelper
hestonModelHelper = $(ffiCall 'hestonModelHelper) c_hestonModelHelper

foreign import ccall safe "ql.h qlHestonModelHelper"
  c_hestonModelHelper :: Ptr CPeriod -> Ptr CCalendar -> CDouble -> CDouble -> Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CCalibrationHelper)

-- TODO git versin of QuantLib features more parameters and two mode SwaptionHelper constructors
swaptionHelper :: Period -- ^maturity
  -> Period -- ^length
  -> Quote -- ^volatility
  -> IborIndex -- ^index
  -> Period -- ^fixedLegTenor
  -> DayCounter -- ^fixedLegDayCounter
  -> DayCounter -- ^floatingLegDayCounter
  -> YieldTermStructure -- ^termStructure
  -> CalibrationErrorType -- ^errorType
  -> IO CalibrationHelper
swaptionHelper = $(ffiCall 'swaptionHelper) c_swaptionHelper

foreign import ccall safe "ql.h qlSwaptionHelper"
  c_swaptionHelper :: Ptr CPeriod -> Ptr CPeriod -> Ptr CQuote -> Ptr CIborIndex -> Ptr CPeriod -> Ptr CDayCounter -> Ptr CDayCounter -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CCalibrationHelper)

times :: CalibrationHelper -> IO [Double]
times x =
  map realToFrac <$> withObject x (getArrayX . c_times)

foreign import ccall safe "ql.h qlCalibrationHelperTimes"
  c_times :: Ptr CCalibrationHelper -> Ptr CUInt -> Ptr CString -> IO (Ptr CDouble)

-- |Regularly spaced time-grid.
timeGrid :: YearFraction -- ^end
  -> Word -- ^steps
  -> IO TimeGrid
timeGrid = $(ffiCall 'timeGrid) c_timeGrid

foreign import ccall safe "ql.h qlTimeGrid1"
  c_timeGrid :: CYearFraction -> CUInt -> Ptr CString -> IO (Ptr CTimeGrid)

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. No additional points are added.
timeGridFromList :: [Double]
  -> IO TimeGrid
timeGridFromList = $(ffiCall 'timeGridFromList) c_timeGridFromList

foreign import ccall safe "ql.h qlTimeGrid2"
  c_timeGridFromList :: CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CTimeGrid)

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. Additional points are then added with regular spacing between pairs of mandatory times in order to reach the desired number of steps.
timeGridFromList' :: [Double]
  -> Word -- ^steps
  -> IO TimeGrid
timeGridFromList' = $(ffiCall 'timeGridFromList') c_timeGridFromList'

foreign import ccall safe "ql.h qlTimeGrid3"
  c_timeGridFromList' :: CUInt -> Ptr CDouble -> CUInt -> Ptr CString -> IO (Ptr CTimeGrid)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
