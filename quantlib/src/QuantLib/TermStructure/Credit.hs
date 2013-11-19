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

  , defaultDensity'
  , defaultDensity
  , defaultProbability
  , defaultProbability'
  , defaultProbabilityBetween'
  , defaultProbabilityBetween
  , hazardRate'
  , hazardRate
  , survivalProbability'
  , survivalProbability
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.TermStructure.Trait(ProbabilityTrait)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Unit(Unit)
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
  -> (Int, Unit) -- ^tenor
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
  c_spreadCdsHelper :: Ptr CQuote -> CInt -> CInt -> CInt -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> CDouble -> Ptr CYieldTermStructure -> CInt -> CInt -> Ptr CString -> IO (Ptr CDefaultProbabilityHelper)

-- |the upfront must be quoted in fractional units.
upfrontCdsHelper :: Quote -- ^upfront
  -> Double -- ^runningSpread
  -> (Int, Unit) -- ^tenor
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
  c_upfrontCdsHelper :: Ptr CQuote -> CDouble -> CInt -> CInt -> CInt -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> CDouble -> Ptr CYieldTermStructure -> CUInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CDefaultProbabilityHelper)

piecewiseDefaultCurve :: Day -- ^referenceDate
  -> [DefaultProbabilityHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Double -- ^accuracy
  -> ProbabilityTrait
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
  -> ProbabilityTrait
  -> Interpolation -- ^i
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve' = $(ffiCall 'piecewiseDefaultCurve') c_piecewiseDefaultCurve'

foreign import ccall safe "ql.h qlPiecewiseDefaultCurve1"
  c_piecewiseDefaultCurve' :: CUInt -> Ptr CCalendar -> CUInt -> Ptr (Ptr CDefaultProbabilityHelper) -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble -> CString -> CString -> Ptr CString -> IO (Ptr CDefaultProbabilityTermStructure)

defaultDensity' :: DefaultProbabilityTermStructure
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> IO Double
defaultDensity' = $(ffiCallX 'defaultDensity') c_defaultDensity'

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureDefaultDensity1"
  c_defaultDensity' :: Ptr CDefaultProbabilityTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

defaultDensity :: DefaultProbabilityTermStructure
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> IO Double
defaultDensity = $(ffiCallX 'defaultDensity) c_defaultDensity

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureDefaultDensity"
  c_defaultDensity :: Ptr CDefaultProbabilityTermStructure -> CDate -> CInt -> Ptr CString -> IO CDouble

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
defaultProbability' :: DefaultProbabilityTermStructure
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> IO Double
defaultProbability' = $(ffiCallX 'defaultProbability') c_defaultProbability'

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureDefaultProbability1"
  c_defaultProbability' :: Ptr CDefaultProbabilityTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

-- |probability of default between two given dates
defaultProbabilityBetween :: DefaultProbabilityTermStructure
  -> Day
  -> Day
  -> Bool -- ^extrapolate
  -> IO Double
defaultProbabilityBetween = $(ffiCallX 'defaultProbabilityBetween) c_defaultProbabilityBetween

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureDefaultProbability2"
  c_defaultProbabilityBetween :: Ptr CDefaultProbabilityTermStructure -> CDate -> CDate -> CInt -> Ptr CString -> IO CDouble

-- |probability of default between two given times
defaultProbabilityBetween' :: DefaultProbabilityTermStructure
  -> YearFraction
  -> YearFraction
  -> Bool -- ^extrapo
  -> IO Double
defaultProbabilityBetween' = $(ffiCallX 'defaultProbabilityBetween') c_defaultProbabilityBetween'

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureDefaultProbability3"
  c_defaultProbabilityBetween' :: Ptr CDefaultProbabilityTermStructure -> CYearFraction -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

defaultProbability :: DefaultProbabilityTermStructure
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> IO Double
defaultProbability = $(ffiCallX 'defaultProbability) c_defaultProbability

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureDefaultProbability"
  c_defaultProbability :: Ptr CDefaultProbabilityTermStructure -> CDate -> CInt -> Ptr CString -> IO CDouble

hazardRate' :: DefaultProbabilityTermStructure
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> IO Double
hazardRate' = $(ffiCallX 'hazardRate') c_hazardRate'

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureHazardRate1"
  c_hazardRate' :: Ptr CDefaultProbabilityTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

hazardRate :: DefaultProbabilityTermStructure
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> IO Double
hazardRate = $(ffiCallX 'hazardRate) c_hazardRate

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureHazardRate"
  c_hazardRate :: Ptr CDefaultProbabilityTermStructure -> CDate -> CInt -> Ptr CString -> IO CDouble

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
survivalProbability' :: DefaultProbabilityTermStructure
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> IO Double
survivalProbability' = $(ffiCallX 'survivalProbability') c_survivalProbability'

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureSurvivalProbability1"
  c_survivalProbability' :: Ptr CDefaultProbabilityTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

survivalProbability :: DefaultProbabilityTermStructure
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> IO Double
survivalProbability = $(ffiCallX 'survivalProbability) c_survivalProbability

foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureSurvivalProbability"
  c_survivalProbability :: Ptr CDefaultProbabilityTermStructure -> CDate -> CInt -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
