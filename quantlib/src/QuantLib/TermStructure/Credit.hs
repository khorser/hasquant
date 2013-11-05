{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.TermStructure.Credit
  (
    factorSpreadedHazardRateCurve
  , flatHazardRate'
  , flatHazardRate
  , spreadedHazardRateCurve

  , interpolatedDefaultDensityCurve
  , interpolatedHazardRateCurve
  , interpolatedSurvivalProbabilityCurve

  , spreadCdsHelper
  , upfrontCdsHelper
  , piecewiseDefaultCurve
  , piecewiseDefaultCurve'
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.TermStructure.Trait
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.Frequency
import QuantLib.Types
import QuantLib.Math.Interpolation(Interpolation)

factorSpreadedHazardRateCurve :: DefaultProbabilityTermStructure -- ^originalCurve
  -> Quote -- ^spread
  -> IO DefaultProbabilityTermStructure
factorSpreadedHazardRateCurve = $(ffiCall 'factorSpreadedHazardRateCurve) c_factorSpreadedHazardRateCurve

foreign import ccall safe "ql.h qlFactorSpreadedHazardRateCurve"
  c_factorSpreadedHazardRateCurve :: Ptr CDefaultProbabilityTermStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

flatHazardRate' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Quote -- ^hazardRate
  -> DayCounter
  -> IO DefaultProbabilityTermStructure
flatHazardRate' = $(ffiCall 'flatHazardRate') c_flatHazardRate'

foreign import ccall safe "ql.h qlFlatHazardRate1"
  c_flatHazardRate' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

flatHazardRate :: Day -- ^referenceDate
  -> Quote -- ^hazardRate
  -> DayCounter
  -> IO DefaultProbabilityTermStructure
flatHazardRate = $(ffiCall 'flatHazardRate) c_flatHazardRate

foreign import ccall safe "ql.h qlFlatHazardRate"
  c_flatHazardRate :: CDate -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

spreadedHazardRateCurve :: DefaultProbabilityTermStructure -- ^originalCurve
  -> Quote -- ^spread
  -> IO DefaultProbabilityTermStructure
spreadedHazardRateCurve = $(ffiCall 'spreadedHazardRateCurve) c_spreadedHazardRateCurve

foreign import ccall safe "ql.h qlSpreadedHazardRateCurve"
  c_spreadedHazardRateCurve :: Ptr CDefaultProbabilityTermStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

interpolatedDefaultDensityCurve :: [Day] -- ^dates
  -> [Double] -- ^densities
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^calendar
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO DefaultProbabilityTermStructure
interpolatedDefaultDensityCurve = $(ffiCall 'interpolatedDefaultDensityCurve) c_interpolatedDefaultDensityCurve

foreign import ccall safe "ql.h qlInterpolatedDefaultDensityCurve"
  c_interpolatedDefaultDensityCurve :: CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

interpolatedHazardRateCurve :: [Day] -- ^dates
  -> [Double] -- ^hazardRates
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO DefaultProbabilityTermStructure
interpolatedHazardRateCurve = $(ffiCall 'interpolatedHazardRateCurve) c_interpolatedHazardRateCurve

foreign import ccall safe "ql.h qlInterpolatedHazardRateCurve"
  c_interpolatedHazardRateCurve :: CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

interpolatedSurvivalProbabilityCurve :: [Day] -- ^dates
  -> [Double] -- ^probabilities
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^calendar
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO DefaultProbabilityTermStructure
interpolatedSurvivalProbabilityCurve = $(ffiCall 'interpolatedSurvivalProbabilityCurve) c_interpolatedSurvivalProbabilityCurve

foreign import ccall safe "ql.h qlInterpolatedSurvivalProbabilityCurve"
  c_interpolatedSurvivalProbabilityCurve :: CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

spreadCdsHelper :: Quote -- ^runningSpread
  -> Period -- ^tenor
  -> Int -- ^settlementDays
  -> Calendar -- ^calendar
  -> Frequency -- ^frequency
  -> BusinessDayConvention -- ^paymentConvention
  -> DateGenerationRule -- ^rule
  -> DayCounter -- ^dayCounter
  -> Double -- ^recoveryRate
  -> YieldTermStructure -- ^discountCurve
  -> Bool -- ^settlesAccrual
  -> Bool -- ^paysAtDefaultTime
  -> IO DefaultProbabilityHelper
spreadCdsHelper = $(ffiCall 'spreadCdsHelper) c_spreadCdsHelper

foreign import ccall safe "ql.h qlSpreadCdsHelper"
  c_spreadCdsHelper :: Ptr CQuote -> Ptr CPeriod -> CInt -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> CDouble -> Ptr CYieldTermStructure -> CInt -> CInt -> Ptr CString -> IO (Ptr CDefaultProbabilityHelper)

-- |the upfront must be quoted in fractional units.
upfrontCdsHelper :: Quote -- ^upfront
  -> Double -- ^runningSpread
  -> Period -- ^tenor
  -> Int -- ^settlementDays
  -> Calendar -- ^calendar
  -> Frequency -- ^frequency
  -> BusinessDayConvention -- ^paymentConvention
  -> DateGenerationRule -- ^rule
  -> DayCounter -- ^dayCounter
  -> Double -- ^recoveryRate
  -> YieldTermStructure -- ^discountCurve
  -> Word -- ^upfrontSettlementDays
  -> Bool -- ^settlesAccrual
  -> Bool -- ^paysAtDefaultTime
  -> IO DefaultProbabilityHelper
upfrontCdsHelper = $(ffiCall 'upfrontCdsHelper) c_upfrontCdsHelper

foreign import ccall safe "ql.h qlUpfrontCdsHelper"
  c_upfrontCdsHelper :: Ptr CQuote -> CDouble -> Ptr CPeriod -> CInt -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> CDouble -> Ptr CYieldTermStructure -> CUInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CDefaultProbabilityHelper)

piecewiseDefaultCurve :: Day -- ^referenceDate
  -> [DefaultProbabilityHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Double -- ^accuracy
  -> ProbabiltyTrait
  -> Interpolation -- ^i
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve = $(ffiCall 'piecewiseDefaultCurve) c_piecewiseDefaultCurve

foreign import ccall safe "ql.h qlPiecewiseDefaultCurve"
  c_piecewiseDefaultCurve :: CDate -> CUInt -> Ptr (Ptr CDefaultProbabilityHelper) -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble -> CString -> CString -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

piecewiseDefaultCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [DefaultProbabilityHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps, ^jumpDates
  -> Double -- ^accuracy
  -> ProbabiltyTrait
  -> Interpolation -- ^i
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve' = $(ffiCall 'piecewiseDefaultCurve') c_piecewiseDefaultCurve'

foreign import ccall safe "ql.h qlPiecewiseDefaultCurve1"
  c_piecewiseDefaultCurve' :: CUInt -> Ptr CCalendar -> CUInt -> Ptr (Ptr CDefaultProbabilityHelper) -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble -> CString -> CString -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
