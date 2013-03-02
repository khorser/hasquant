{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.TermStructure.Volatility
  (
    constantOptionletVolatility'
  , blackConstantVol'
  , blackConstantVol
  , constantOptionletVolatility
  , constantSwaptionVolatility'
  , constantSwaptionVolatility
  , blackVariance'
  , blackVariance''
  , blackVariance'''
  , blackVariance''''
  , blackVariance'''''
  , blackVariance
  , maxSwapLength
  , maxSwapTenor
  , smileSection'
{-
  , smileSection''
  , smileSection'''
  , smileSection''''
-}
  , smileSection'''''
  , smileSection
  , swapLength'
  , swapLength
  , volatility'
  , volatility''
  , volatility'''
  , volatility''''
  , volatility'''''
  , volatility

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
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.TermStructure.Trait

foreign import ccall safe "ql.h qlConstantOptionletVol1"
  c_constantOptionletVol' :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote
    -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolatilityStructure)

-- |Constant caplet volatility, no time-strike dependence. QuantLibXL: qlConstantOptionletVolatility
-- floating reference date, floating market data
constantOptionletVolatility' :: Word -- ^settlementDays
 -> Calendar -- ^cal
 -> BusinessDayConvention -- ^bdc
 -> Quote -- ^volatility
 -> DayCounter -- ^dc
 -> IO OptionletVolatilityStructure
constantOptionletVolatility' = $(ffiCall 'constantOptionletVolatility') c_constantOptionletVol'

blackConstantVol' :: Word -- ^settlementDays
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> IO BlackVolTermStructure
blackConstantVol' = $(ffiCall 'blackConstantVol') c_blackConstantVol'

foreign import ccall safe "ql.h qlBlackConstantVol1"
  c_blackConstantVol' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

blackConstantVol :: Day -- ^referenceDate
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> IO BlackVolTermStructure
blackConstantVol = $(ffiCall 'blackConstantVol) c_blackConstantVol

foreign import ccall safe "ql.h qlBlackConstantVol"
  c_blackConstantVol :: CDate -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

-- |fixed reference date, floating market data
constantOptionletVolatility :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> IO OptionletVolatilityStructure
constantOptionletVolatility = $(ffiCall 'constantOptionletVolatility) c_constantOptionletVolatility

foreign import ccall safe "ql.h qlConstantOptionletVolatility"
  c_constantOptionletVolatility :: CDate -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr COptionletVolatilityStructure)

-- |fixed reference date, floating market data
constantSwaptionVolatility' :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> IO SwaptionVolatilityStructure
constantSwaptionVolatility' = $(ffiCall 'constantSwaptionVolatility') c_constantSwaptionVolatility'

foreign import ccall safe "ql.h qlConstantSwaptionVolatility1"
  c_constantSwaptionVolatility' :: CDate -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CSwaptionVolatilityStructure)

-- |floating reference date, floating market data
constantSwaptionVolatility :: Word -- ^settlementDays
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> IO SwaptionVolatilityStructure
constantSwaptionVolatility = $(ffiCall 'constantSwaptionVolatility) c_constantSwaptionVolatility

foreign import ccall safe "ql.h qlConstantSwaptionVolatility"
  c_constantSwaptionVolatility :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CSwaptionVolatilityStructure)

-- |returns the Black variance for a given option date and swap tenor
blackVariance' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> Period -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
blackVariance' = $(ffiCallX 'blackVariance') c_blackVariance'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance1"
  c_blackVariance' :: Ptr CSwaptionVolatilityStructure -> CDate -> Ptr CPeriod -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option time and swap tenor
blackVariance'' :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> Period -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
blackVariance'' = $(ffiCallX 'blackVariance'') c_blackVariance''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance2"
  c_blackVariance'' :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> Ptr CPeriod -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option tenor and swap length
blackVariance''' :: SwaptionVolatilityStructure
  -> Period -- ^optionTenor
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
blackVariance''' = $(ffiCallX 'blackVariance''') c_blackVariance'''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance3"
  c_blackVariance''' :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option date and swap length
blackVariance'''' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
blackVariance'''' = $(ffiCallX 'blackVariance'''') c_blackVariance''''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance4"
  c_blackVariance'''' :: Ptr CSwaptionVolatilityStructure -> CDate -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option time and swap length
blackVariance''''' :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
blackVariance''''' = $(ffiCallX 'blackVariance''''') c_blackVariance'''''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance5"
  c_blackVariance''''' :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the Black variance for a given option tenor and swap tenor
blackVariance :: SwaptionVolatilityStructure
  -> Period -- ^optionTenor
  -> Period -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
blackVariance = $(ffiCallX 'blackVariance) c_blackVariance

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureBlackVariance"
  c_blackVariance :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> Ptr CPeriod -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |the largest swapLength for which the term structure can return vols
maxSwapLength :: SwaptionVolatilityStructure
  -> IO YearFraction
maxSwapLength = $(ffiCallX 'maxSwapLength) c_maxSwapLength

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureMaxSwapLength"
  c_maxSwapLength :: Ptr CSwaptionVolatilityStructure -> Ptr CString -> IO CYearFraction

-- |the largest length for which the term structure can return vols
maxSwapTenor :: SwaptionVolatilityStructure
  -> IO Period
maxSwapTenor = $(ffiCall 'maxSwapTenor) c_maxSwapTenor

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureMaxSwapTenor"
  c_maxSwapTenor :: Ptr CSwaptionVolatilityStructure -> Ptr CString -> IO (Ptr CPeriod)

-- |returns the smile for a given option date and swap tenor
smileSection' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> Period -- ^swapTenor
  -> Bool -- ^extr
  -> IO SmileSection
smileSection' = $(ffiCall 'smileSection') c_smileSection'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection1"
  c_smileSection' :: Ptr CSwaptionVolatilityStructure -> CDate -> Ptr CPeriod -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

{- The following methods are not implemented in QuantLib for some reason
-- |returns the smile for a given option time and swap tenor
smileSection'' :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> Period -- ^swapTenor
  -> Bool -- ^extr
  -> IO SmileSection
smileSection'' = $(ffiCall 'smileSection'') c_smileSection''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection2"
  c_smileSection'' :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> Ptr CPeriod -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option tenor and swap length
smileSection''' :: SwaptionVolatilityStructure
  -> Period -- ^optionTenor
  -> YearFraction -- ^swapLength
  -> Bool -- ^extr
  -> IO SmileSection
smileSection''' = $(ffiCall 'smileSection''') c_smileSection'''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection3"
  c_smileSection''' :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> CYearFraction -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option date and swap length
smileSection'''' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> YearFraction -- ^swapLength
  -> Bool -- ^extr
  -> IO SmileSection
smileSection'''' = $(ffiCall 'smileSection'''') c_smileSection''''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection4"
  c_smileSection'''' :: Ptr CSwaptionVolatilityStructure -> CDate -> CYearFraction -> CInt -> Ptr CString -> IO (Ptr CSmileSection)
-}

-- |returns the smile for a given option time and swap length
smileSection''''' :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> YearFraction -- ^swapLength
  -> Bool -- ^extr
  -> IO SmileSection
smileSection''''' = $(ffiCall 'smileSection''''') c_smileSection'''''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection5"
  c_smileSection''''' :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CYearFraction -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |returns the smile for a given option tenor and swap tenor
smileSection :: SwaptionVolatilityStructure
  -> Period -- ^optionTenor
  -> Period -- ^swapTenor
  -> Bool -- ^extr
  -> IO SmileSection
smileSection = $(ffiCall 'smileSection) c_smileSection

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSmileSection"
  c_smileSection :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> Ptr CPeriod -> CInt -> Ptr CString -> IO (Ptr CSmileSection)

-- |implements the conversion between swap dates and swap (time) length
swapLength' :: SwaptionVolatilityStructure
  -> Day -- ^start
  -> Day -- ^end
  -> IO YearFraction
swapLength' = $(ffiCallX 'swapLength') c_swapLength'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSwapLength1"
  c_swapLength' :: Ptr CSwaptionVolatilityStructure -> CDate -> CDate -> Ptr CString -> IO CYearFraction

-- |implements the conversion between swap tenor and swap (time) length
swapLength :: SwaptionVolatilityStructure
  -> Period -- ^swapTenor
  -> IO YearFraction
swapLength = $(ffiCallX 'swapLength) c_swapLength

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureSwapLength"
  c_swapLength :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> Ptr CString -> IO CYearFraction

-- |returns the volatility for a given option date and swap tenor
volatility' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> Period -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
volatility' = $(ffiCallX 'volatility') c_volatility'

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility1"
  c_volatility' :: Ptr CSwaptionVolatilityStructure -> CDate -> Ptr CPeriod -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option time and swap tenor
volatility'' :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> Period -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
volatility'' = $(ffiCallX 'volatility'') c_volatility''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility2"
  c_volatility'' :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> Ptr CPeriod -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option tenor and swap length
volatility''' :: SwaptionVolatilityStructure
  -> Period -- ^optionTenor
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
volatility''' = $(ffiCallX 'volatility''') c_volatility'''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility3"
  c_volatility''' :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option date and swap length
volatility'''' :: SwaptionVolatilityStructure
  -> Day -- ^optionDate
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
volatility'''' = $(ffiCallX 'volatility'''') c_volatility''''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility4"
  c_volatility'''' :: Ptr CSwaptionVolatilityStructure -> CDate -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option time and swap length
volatility''''' :: SwaptionVolatilityStructure
  -> YearFraction -- ^optionTime
  -> YearFraction -- ^swapLength
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
volatility''''' = $(ffiCallX 'volatility''''') c_volatility'''''

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility5"
  c_volatility''''' :: Ptr CSwaptionVolatilityStructure -> CYearFraction -> CYearFraction -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |returns the volatility for a given option tenor and swap tenor
volatility :: SwaptionVolatilityStructure
  -> Period -- ^optionTenor
  -> Period -- ^swapTenor
  -> Double -- ^strike
  -> Bool -- ^extrapolate
  -> IO Double
volatility = $(ffiCallX 'volatility) c_volatility

foreign import ccall safe "ql.h qlSwaptionVolatilityStructureVolatility"
  c_volatility :: Ptr CSwaptionVolatilityStructure -> Ptr CPeriod -> Ptr CPeriod -> CDouble -> CInt -> Ptr CString -> IO CDouble

-- |fixed reference date, floating market data
capFloorTermVolCurve' :: Day -- ^settlementDate
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [Period] -- ^optionTenors
  -> [Quote] -- ^vols
  -> DayCounter -- ^dc
  -> IO VolatilityTermStructure
capFloorTermVolCurve' = $(ffiCall 'capFloorTermVolCurve') c_capFloorTermVolCurve'

foreign import ccall safe "ql.h qlCapFloorTermVolCurve1"
  c_capFloorTermVolCurve' :: CDate -> Ptr CCalendar -> CInt -> CUInt -> Ptr (Ptr CPeriod) -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

-- |floating reference date, floating market data
capFloorTermVolCurve :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [Period] -- ^optionTenors
  -> [Quote] -- ^vols
  -> DayCounter -- ^dc
  -> IO VolatilityTermStructure
capFloorTermVolCurve = $(ffiCall 'capFloorTermVolCurve) c_capFloorTermVolCurve

foreign import ccall safe "ql.h qlCapFloorTermVolCurve"
  c_capFloorTermVolCurve :: CUInt -> Ptr CCalendar -> CInt -> CUInt -> Ptr (Ptr CPeriod) -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

-- |fixed reference date, floating market data
constantCapFloorTermVolatility' :: Day -- ^referenceDate
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> IO VolatilityTermStructure
constantCapFloorTermVolatility' = $(ffiCall 'constantCapFloorTermVolatility') c_constantCapFloorTermVolatility'

foreign import ccall safe "ql.h qlConstantCapFloorTermVolatility1"
  c_constantCapFloorTermVolatility' :: CDate -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

-- |floating reference date, floating market data
constantCapFloorTermVolatility :: Word -- ^settlementDays
  -> Calendar -- ^cal
  -> BusinessDayConvention -- ^bdc
  -> Quote -- ^volatility
  -> DayCounter -- ^dc
  -> IO VolatilityTermStructure
constantCapFloorTermVolatility = $(ffiCall 'constantCapFloorTermVolatility) c_constantCapFloorTermVolatility

foreign import ccall safe "ql.h qlConstantCapFloorTermVolatility"
  c_constantCapFloorTermVolatility :: CUInt -> Ptr CCalendar -> CInt -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CVolatilityTermStructure)

spreadedSwaptionVolatility :: SwaptionVolatilityStructure
  -> Quote -- ^spread
  -> IO SwaptionVolatilityStructure
spreadedSwaptionVolatility = $(ffiCall 'spreadedSwaptionVolatility) c_spreadedSwaptionVolatility

foreign import ccall safe "ql.h qlSpreadedSwaptionVolatility"
  c_spreadedSwaptionVolatility :: Ptr CSwaptionVolatilityStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CSwaptionVolatilityStructure)

localConstantVol' :: Word -- ^settlementDays
  -> Calendar
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> IO LocalVolTermStructure
localConstantVol' = $(ffiCall 'localConstantVol') c_localConstantVol'

foreign import ccall safe "ql.h qlLocalConstantVol1"
  c_localConstantVol' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

localConstantVol :: Day -- ^referenceDate
  -> Quote -- ^volatility
  -> DayCounter -- ^dayCounter
  -> IO LocalVolTermStructure
localConstantVol = $(ffiCall 'localConstantVol) c_localConstantVol

foreign import ccall safe "ql.h qlLocalConstantVol"
  c_localConstantVol :: CDate -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

localVolCurve :: BlackVarianceCurve -- ^curve
  -> IO LocalVolTermStructure
localVolCurve = $(ffiCall 'localVolCurve) c_localVolCurve

foreign import ccall safe "ql.h qlLocalVolCurve"
  c_localVolCurve :: Ptr CBlackVarianceCurve -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

localVolSurface :: BlackVolTermStructure -- ^blackTS
  -> YieldTermStructure -- ^riskFreeTS
  -> YieldTermStructure -- ^dividendTS
  -> Quote -- ^underlying
  -> IO LocalVolTermStructure
localVolSurface = $(ffiCall 'localVolSurface) c_localVolSurface

foreign import ccall safe "ql.h qlLocalVolSurface"
  c_localVolSurface :: Ptr CBlackVolTermStructure -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CLocalVolTermStructure)

impliedVolTermStructure :: BlackVolTermStructure -- ^origTS
  -> Day -- ^referenceDate
  -> IO BlackVolTermStructure
impliedVolTermStructure = $(ffiCall 'impliedVolTermStructure) c_impliedVolTermStructure

foreign import ccall safe "ql.h qlImpliedVolTermStructure"
  c_impliedVolTermStructure :: Ptr CBlackVolTermStructure -> CDate -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

blackVarianceCurve :: Day -- ^referenceDate
  -> [Day] -- ^dates
  -> [Double] -- ^blackVolCurve
  -> DayCounter -- ^dayCounter
  -> Bool -- ^forceMonotoneVariance
  -> Maybe Interpolation
  -> IO BlackVarianceCurve
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
  -> IO BlackVolTermStructure
blackVarianceSurface = $(ffiCall 'blackVarianceSurface) c_blackVarianceSurface

foreign import ccall safe "ql.h qlBlackVarianceSurface"
  c_blackVarianceSurface :: CDate -> Ptr CCalendar -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> CUInt -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CBlackVolTermStructure)

-- |floating reference date, floating market data
capFloorTermVolSurface :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [Period] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix Quote -- ^volatilities
  -> DayCounter -- ^dc
  -> IO CapFloorTermVolSurface
capFloorTermVolSurface = $(ffiCall 'capFloorTermVolSurface) c_capFloorTermVolSurface

foreign import ccall safe "ql.h qlCapFloorTermVolSurface"
  c_capFloorTermVolSurface :: CUInt -> Ptr CCalendar -> CInt -> CUInt -> Ptr (Ptr CPeriod) -> CUInt -> Ptr CDouble -> CUInt -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CCapFloorTermVolSurface)

-- |fixed reference date, floating market data
capFloorTermVolSurface' :: Day -- ^settlementDate
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^bdc
  -> [Period] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix Quote -- ^volatilities
  -> DayCounter -- ^dc
  -> IO CapFloorTermVolSurface
capFloorTermVolSurface' = $(ffiCall 'capFloorTermVolSurface') c_capFloorTermVolSurface'

foreign import ccall safe "ql.h qlCapFloorTermVolSurface1"
  c_capFloorTermVolSurface' :: CDate -> Ptr CCalendar -> CInt -> CUInt -> Ptr (Ptr CPeriod) -> CUInt -> Ptr CDouble -> CUInt -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CCapFloorTermVolSurface)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
