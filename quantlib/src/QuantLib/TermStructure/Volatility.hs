{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Volatility
  (
    constantOptionletVolatility'
  , blackConstantVol'
  , blackConstantVol
  , constantOptionletVolatility
  , constantSwaptionVolatility'
  , constantSwaptionVolatility
  , blackVarianceForPeriod'
  , blackVarianceForPeriod
  , blackVariance
  , blackVariance'
  , blackVarianceForPeriods
  , blackVarianceForTenor
  , maxSwapLength
  , maxSwapTenor
  , smileSectionForPeriod'
  , smileSectionForPeriod
  , smileSectionForTenor
  , smileSection'
  , smileSection
  , smileSectionForPeriods
  , swapLength'
  , swapLength
  , volatilityForPeriod
  , volatilityForPeriod'
  , volatilityForTenor
  , volatilityForTenor'
  , volatility
  , volatilityForPeriods

  , capFloorTermVolCurve'
  , capFloorTermVolCurve
  , constantCapFloorTermVolatility'
  , constantCapFloorTermVolatility
  , spreadedSwaptionVolatility

  , localConstantVol'
  , localConstantVol
  , localVolCurve
  , localVolSurface
  , impliedVolTermStructure
  , blackVarianceCurve
  , blackVarianceSurface

  , capFloorTermVolSurface
  , capFloorTermVolSurface'

  , callableBondConstantVolatility'
  , callableBondConstantVolatility
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Unit(Unit)
import QuantLib.TermStructure.Trait(BlackVarSurfaceExtrapolation)

foreign import ccall safe "ql.h qlConstantOptionletVol1"
  c_constantOptionletVolatility' :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolatilityStructure)

-- |Constant caplet volatility, no time-strike dependence
-- floating reference date, floating market data
constantOptionletVolatility' :: Word -- ^settlementDays
 -> Calendar -- ^cal
 -> BusinessDayConvention -- ^bdc
 -> Quote -- ^volatility
 -> DayCounter -- ^dc
 -> QLE s (OptionletVolatilityStructure s)
constantOptionletVolatility' = $(ffiCall 'constantOptionletVolatility') c_constantOptionletVolatility'

blackConstantVol' :: Word -- ^settlementDays
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> QLE s (BlackVolTermStructure s)
blackConstantVol' = $(ffiCall 'blackConstantVol') c_blackConstantVol'

foreign import ccall safe "ql.h qlBlackConstantVol1"
  c_blackConstantVol' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

blackConstantVol :: Day -- ^referenceDate
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> QLE s (BlackVolTermStructure s)
blackConstantVol = $(ffiCall 'blackConstantVol) c_blackConstantVol

foreign import ccall safe "ql.h qlBlackConstantVol"
  c_blackConstantVol :: CDate -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

-- |fixed reference date, floating market data
constantOptionletVolatility :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> QLE s (OptionletVolatilityStructure s)
constantOptionletVolatility = $(ffiCall 'constantOptionletVolatility) c_constantOptionletVolatility

foreign import ccall safe "ql.h qlConstantOptionletVolatility"
  c_constantOptionletVolatility :: CDate -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolatilityStructure)

-- |fixed reference date, floating market data
constantSwaptionVolatility' :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> QLE s (SwaptionVolatilityStructure s)
constantSwaptionVolatility' = $(ffiCall 'constantSwaptionVolatility') c_constantSwaptionVolatility'

foreign import ccall safe "ql.h qlConstantSwaptionVolatility1"
  c_constantSwaptionVolatility' :: CDate -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CSwaptionVolatilityStructure)

-- |floating reference date, floating market data
constantSwaptionVolatility :: Word -- ^settlementDays
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> QLE s (SwaptionVolatilityStructure s)
constantSwaptionVolatility = $(ffiCall 'constantSwaptionVolatility) c_constantSwaptionVolatility

foreign import ccall safe "ql.h qlConstantSwaptionVolatility"
  c_constantSwaptionVolatility :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CSwaptionVolatilityStructure)

-- |returns the Black variance for a given option date and swap tenor
blackVarianceForPeriod' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> (Int, Unit) -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
blackVarianceForPeriod' = $(ffiCallX 'blackVarianceForPeriod') c_blackVarianceForPeriod'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance1"
  c_blackVarianceForPeriod' :: Ptr CSwaptionVolatilityStructure -> CDate -> CInt -> CInt -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option time and swap tenor
blackVarianceForPeriod :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> (Int, Unit) -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
blackVarianceForPeriod = $(ffiCallX 'blackVarianceForPeriod) c_blackVarianceForPeriod

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance2"
  c_blackVarianceForPeriod :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CInt -> CInt -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option tenor and swap length
blackVarianceForTenor :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^optionTenor
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
blackVarianceForTenor = $(ffiCallX 'blackVarianceForTenor) c_blackVarianceForTenor

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance3"
  c_blackVarianceForTenor :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option date and swap length
blackVariance' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
blackVariance' = $(ffiCallX 'blackVariance') c_blackVariance'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance4"
  c_blackVariance' :: Ptr CSwaptionVolatilityStructure -> CDate -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option time and swap length
blackVariance :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
blackVariance = $(ffiCallX 'blackVariance) c_blackVariance

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance5"
  c_blackVariance :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option tenor and swap tenor
blackVarianceForPeriods :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^optionTenor
  -> (Int, Unit) -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
blackVarianceForPeriods = $(ffiCallX 'blackVarianceForPeriods) c_blackVarianceForPeriods

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance"
  c_blackVarianceForPeriods :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> CInt -> CInt -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |the largest swapLength for which the term structure can return vols
maxSwapLength :: SwaptionVolatilityStructure
  -> QLE s YearFraction
maxSwapLength = $(ffiCallX 'maxSwapLength) c_maxSwapLength

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureMaxSwapLength"
  c_maxSwapLength :: Ptr CSwaptionVolatilityStructure -> Ptr CString -> IO CYearFraction

-- |the largest length for which the term structure can return vols
maxSwapTenor :: SwaptionVolatilityStructure -> Either QLError (Int, Unit)
maxSwapTenor o = purifyExceptions $ do
  (n, u) <- withObject o (getIntPair . c_maxSwapTenor)
  e <- fromQlEnum (show ''Unit) u
  return (n, e)

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureMaxSwapTenor"
  c_maxSwapTenor :: Ptr CSwaptionVolatilityStructure -> Ptr CInt -> Ptr CString -> IO CInt

-- |returns the smile for a given option date and swap tenor
smileSectionForPeriod' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> (Int, Unit) -- ^swapTenor
  -> Bool -- ^extr
  -> QLE s (SmileSection s)
smileSectionForPeriod' = $(ffiCall 'smileSectionForPeriod') c_smileSectionForPeriod'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection1"
  c_smileSectionForPeriod' :: Ptr CSwaptionVolatilityStructure -> CDate -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option time and swap tenor
smileSectionForPeriod :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> (Int, Unit) -- ^swapTenor
  -> Bool -- ^extr
  -> QLE s (SmileSection s)
smileSectionForPeriod = $(ffiCall 'smileSectionForPeriod) c_smileSectionForPeriod

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection2"
  c_smileSectionForPeriod :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option tenor and swap length
smileSectionForTenor :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^optionTenor
  -> YearFraction -- ^swapLength
  -> Bool -- ^extr
  -> QLE s (SmileSection s)
smileSectionForTenor = $(ffiCall 'smileSectionForTenor) c_smileSectionForTenor

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection3"
  c_smileSectionForTenor :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> CYearFraction -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option date and swap length
smileSection' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> YearFraction -- ^swapLength
  -> Bool -- ^extr
  -> QLE s (SmileSection s)
smileSection' = $(ffiCall 'smileSection') c_smileSection'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection4"
  c_smileSection' :: Ptr CSwaptionVolatilityStructure -> CDate -> CYearFraction -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option time and swap length
smileSection :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> YearFraction -- ^swapLength
  -> Bool -- ^extr
  -> QLE s (SmileSection s)
smileSection = $(ffiCall 'smileSection) c_smileSection

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection5"
  c_smileSection :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CYearFraction -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option tenor and swap tenor
smileSectionForPeriods :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^optionTenor
  -> (Int, Unit) -- ^swapTenor
  -> Bool -- ^extr
  -> QLE s (SmileSection s)
smileSectionForPeriods = $(ffiCall 'smileSectionForPeriods) c_smileSectionForPeriods

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection"
  c_smileSectionForPeriods :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |implements the conversion between swap dates and swap (time) length
swapLength' :: SwaptionVolatilityStructure
  -> Day -- ^start
  -> Day -- ^end
  -> QLE s YearFraction
swapLength' = $(ffiCallX 'swapLength') c_swapLength'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSwapLength1"
  c_swapLength' :: Ptr CSwaptionVolatilityStructure -> CDate -> CDate -> Ptr CString -> IO CYearFraction

-- |implements the conversion between swap tenor and swap (time) length
swapLength :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^swapTenor
  -> QLE s YearFraction
swapLength = $(ffiCallX 'swapLength) c_swapLength

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSwapLength"
  c_swapLength :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> Ptr CString -> IO CYearFraction

-- |returns the volatility for a given option date and swap tenor
volatilityForPeriod' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> (Int, Unit) -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
volatilityForPeriod' = $(ffiCallX 'volatilityForPeriod') c_volatilityForPeriod'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility1"
  c_volatilityForPeriod' :: Ptr CSwaptionVolatilityStructure -> CDate -> CInt -> CInt -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option time and swap tenor
volatilityForPeriod :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> (Int, Unit) -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
volatilityForPeriod = $(ffiCallX 'volatilityForPeriod) c_volatilityForPeriod

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility2"
  c_volatilityForPeriod :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CInt -> CInt -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option tenor and swap length
volatilityForTenor :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^optionTenor
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
volatilityForTenor = $(ffiCallX 'volatilityForTenor) c_volatilityForTenor

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility3"
  c_volatilityForTenor :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option date and swap length
volatilityForTenor' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
volatilityForTenor' = $(ffiCallX 'volatilityForTenor') c_volatilityForTenor'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility4"
  c_volatilityForTenor' :: Ptr CSwaptionVolatilityStructure -> CDate -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option time and swap length
volatility :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
volatility = $(ffiCallX 'volatility) c_volatility

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility5"
  c_volatility :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option tenor and swap tenor
volatilityForPeriods :: SwaptionVolatilityStructure
  -> (Int, Unit) -- ^optionTenor
  -> (Int, Unit) -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> QLE s Double
volatilityForPeriods = $(ffiCallX 'volatilityForPeriods) c_volatilityForPeriods

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility"
  c_volatilityForPeriods :: Ptr CSwaptionVolatilityStructure -> CInt -> CInt -> CInt -> CInt -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |fixed reference date, floating market data
capFloorTermVolCurve' :: Day -- ^settlementDate
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [(Int, Unit)] -- ^optionTenors
  -> [Quote] -- ^vols
  -> DayCounter -- ^dc
  -> QLE s (VolatilityTermStructure s)
capFloorTermVolCurve' = $(ffiCall 'capFloorTermVolCurve') c_capFloorTermVolCurve'

foreign import ccall safe "ql.h qlCapFloorTermVolCurve1"
  c_capFloorTermVolCurve' :: CDate -> Ptr CCalendar -> CInt -> CUInt -> Ptr CInt -> Ptr CInt -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

-- |floating reference date, floating market data
capFloorTermVolCurve :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [(Int, Unit)] -- ^optionTenors
  -> [Quote] -- ^vols
  -> DayCounter -- ^dc
  -> QLE s (VolatilityTermStructure s)
capFloorTermVolCurve = $(ffiCall 'capFloorTermVolCurve) c_capFloorTermVolCurve

foreign import ccall safe "ql.h qlCapFloorTermVolCurve"
  c_capFloorTermVolCurve :: CUInt -> Ptr CCalendar -> CInt -> CUInt -> Ptr CInt -> Ptr CInt -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

-- |fixed reference date, floating market data
constantCapFloorTermVolatility' :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> QLE s (VolatilityTermStructure s)
constantCapFloorTermVolatility' = $(ffiCall 'constantCapFloorTermVolatility') c_constantCapFloorTermVolatility'

foreign import ccall safe "ql.h qlConstantCapFloorTermVolatility1"
  c_constantCapFloorTermVolatility' :: CDate -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

-- |floating reference date, floating market data
constantCapFloorTermVolatility :: Word -- ^settlementDays
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> QLE s (VolatilityTermStructure s)
constantCapFloorTermVolatility = $(ffiCall 'constantCapFloorTermVolatility) c_constantCapFloorTermVolatility

foreign import ccall safe "ql.h qlConstantCapFloorTermVolatility"
  c_constantCapFloorTermVolatility :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

spreadedSwaptionVolatility :: SwaptionVolatilityStructure
  -> Quote -- ^spread
  -> QLE s (SwaptionVolatilityStructure s)
spreadedSwaptionVolatility = $(ffiCall 'spreadedSwaptionVolatility) c_spreadedSwaptionVolatility

foreign import ccall safe "ql.h qlSpreadedSwaptionVolatility"
  c_spreadedSwaptionVolatility :: Ptr CSwaptionVolatilityStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CSwaptionVolatilityStructure)

localConstantVol' :: Word -- ^settlementDays
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> QLE s (LocalVolTermStructure s)
localConstantVol' = $(ffiCall 'localConstantVol') c_localConstantVol'

foreign import ccall safe "ql.h qlLocalConstantVol1"
  c_localConstantVol' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

localConstantVol :: Day -- ^referenceDate
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> QLE s (LocalVolTermStructure s)
localConstantVol = $(ffiCall 'localConstantVol) c_localConstantVol

foreign import ccall safe "ql.h qlLocalConstantVol"
  c_localConstantVol :: CDate -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

localVolCurve :: BlackVarianceCurve -- ^curve
  -> QLE s (LocalVolTermStructure s)
localVolCurve = $(ffiCall 'localVolCurve) c_localVolCurve

foreign import ccall safe "ql.h qlLocalVolCurve"
  c_localVolCurve :: Ptr CBlackVarianceCurve -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

localVolSurface :: BlackVolTermStructure -- ^blackTS
  -> YieldTermStructure -- ^riskFreeTS
  -> YieldTermStructure -- ^dividendTS
  -> Quote -- ^underlying
  -> QLE s (LocalVolTermStructure s)
localVolSurface = $(ffiCall 'localVolSurface) c_localVolSurface

foreign import ccall safe "ql.h qlLocalVolSurface"
  c_localVolSurface :: Ptr CBlackVolTermStructure -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

impliedVolTermStructure :: BlackVolTermStructure -- ^origTS
  -> Day -- ^referenceDate
  -> QLE s (BlackVolTermStructure s)
impliedVolTermStructure = $(ffiCall 'impliedVolTermStructure) c_impliedVolTermStructure

foreign import ccall safe "ql.h qlImpliedVolTermStructure"
  c_impliedVolTermStructure :: Ptr CBlackVolTermStructure -> CDate -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

blackVarianceCurve :: Day -- ^referenceDate
  -> [Day] -- ^dates
  -> [Double] -- ^blackVolCurve
  -> DayCounter -- ^dayCounter
  -> Bool -- ^forceMonotoneVariance
  -> Maybe Interpolation
  -> QLE s (BlackVarianceCurve s)
blackVarianceCurve = $(ffiCall 'blackVarianceCurve) c_blackVarianceCurve

foreign import ccall safe "ql.h qlBlackVarianceCurve"
  c_blackVarianceCurve :: CDate -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CString -> Ptr CString -> IO (Ptr CBlackVarianceCurve)

blackVarianceSurface :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> [Day] -- ^dates
  -> [Double] -- ^strikes
  -> Matrix Double -- ^blackVolMatrix
  -> DayCounter -- ^dayCounter
  -> BlackVarSurfaceExtrapolation -- ^lowerExtrapolation
  -> BlackVarSurfaceExtrapolation -- ^upperExtrapolation
  -> QLE s (BlackVolTermStructure s)
blackVarianceSurface = $(ffiCall 'blackVarianceSurface) c_blackVarianceSurface

foreign import ccall safe "ql.h qlBlackVarianceSurface"
  c_blackVarianceSurface :: CDate -> Ptr CCalendar -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> CUInt -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

-- |floating reference date, floating market data
capFloorTermVolSurface :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [(Int, Unit)] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix Quote -- ^volatilities
  -> DayCounter -- ^dc
  -> IO CapFloorTermVolSurface
capFloorTermVolSurface = $(ffiCall 'capFloorTermVolSurface) c_capFloorTermVolSurface

foreign import ccall safe "ql.h qlCapFloorTermVolSurface"
  c_capFloorTermVolSurface :: CUInt -> Ptr CCalendar -> CInt -> CUInt -> Ptr CInt -> Ptr CInt -> CUInt -> Ptr CDouble -> CUInt -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CCapFloorTermVolSurface)

-- |fixed reference date, floating market data
capFloorTermVolSurface' :: Day -- ^settlementDate
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [(Int, Unit)] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix Quote -- ^volatilities
  -> DayCounter -- ^dc
  -> IO CapFloorTermVolSurface
capFloorTermVolSurface' = $(ffiCall 'capFloorTermVolSurface') c_capFloorTermVolSurface'

foreign import ccall safe "ql.h qlCapFloorTermVolSurface1"
  c_capFloorTermVolSurface' :: CDate -> Ptr CCalendar -> CInt -> CUInt -> Ptr CInt -> Ptr CInt -> CUInt -> Ptr CDouble -> CUInt -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CCapFloorTermVolSurface)

callableBondConstantVolatility' :: Word -- ^settlementDays
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> IO CallableBondVolatilityStructure
callableBondConstantVolatility' = $(ffiCall 'callableBondConstantVolatility') c_callableBondConstantVolatility'

foreign import ccall safe "ql.h qlCallableBondConstantVolatility1"
  c_callableBondConstantVolatility' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CCallableBondVolatilityStructure)

callableBondConstantVolatility :: Day -- ^referenceDate
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> IO CallableBondVolatilityStructure
callableBondConstantVolatility = $(ffiCall 'callableBondConstantVolatility) c_callableBondConstantVolatility

foreign import ccall safe "ql.h qlCallableBondConstantVolatility"
  c_callableBondConstantVolatility :: CDate -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CCallableBondVolatilityStructure)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
