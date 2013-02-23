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
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
