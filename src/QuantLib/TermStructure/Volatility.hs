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
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
