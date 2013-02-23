{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Process
  (
    blackProcess
  , blackScholesMertonProcess
  , blackScholesProcess
  , extendedBlackScholesMertonProcess
  , garmanKohlagenProcess
  , generalizedBlackScholesProcess
  , squareRootProcess
  , vegaStressedBlackScholesProcess
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.ProcessDiscretization
import QuantLib.Types

blackProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^riskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> IO BlackProcess
blackProcess = $(ffiCall 'blackProcess) c_blackProcess

foreign import ccall safe "ql.h qlBlackProcess"
  c_blackProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CBlackProcess)

blackScholesMertonProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^dividendTS
  -> YieldTermStructure -- ^riskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> IO GeneralizedBlackScholesProcess
blackScholesMertonProcess = $(ffiCall 'blackScholesMertonProcess) c_blackScholesMertonProcess

foreign import ccall safe "ql.h qlBlackScholesMertonProcess"
  c_blackScholesMertonProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

blackScholesProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^riskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> IO GeneralizedBlackScholesProcess
blackScholesProcess = $(ffiCall 'blackScholesProcess) c_blackScholesProcess

foreign import ccall safe "ql.h qlBlackScholesProcess"
  c_blackScholesProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

extendedBlackScholesMertonProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^dividendTS
  -> YieldTermStructure -- ^riskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> ExtendedDiscretization -- ^evolDisc
  -> IO GeneralizedBlackScholesProcess
extendedBlackScholesMertonProcess = $(ffiCall 'extendedBlackScholesMertonProcess) c_extendedBlackScholesMertonProcess

foreign import ccall safe "ql.h qlExtendedBlackScholesMertonProcess"
  c_extendedBlackScholesMertonProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> CInt -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

garmanKohlagenProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^foreignRiskFreeTS
  -> YieldTermStructure -- ^domesticRiskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> IO GeneralizedBlackScholesProcess
garmanKohlagenProcess = $(ffiCall 'garmanKohlagenProcess) c_garmanKohlagenProcess

foreign import ccall safe "ql.h qlGarmanKohlagenProcess"
  c_garmanKohlagenProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

generalizedBlackScholesProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^dividendTS
  -> YieldTermStructure -- ^riskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> IO GeneralizedBlackScholesProcess
generalizedBlackScholesProcess = $(ffiCall 'generalizedBlackScholesProcess) c_generalizedBlackScholesProcess

foreign import ccall safe "ql.h qlGeneralizedBlackScholesProcess"
  c_generalizedBlackScholesProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

squareRootProcess :: Double -- ^b
  -> Double -- ^a
  -> Double -- ^sigma
  -> Double -- ^x0
  -> ProcessDiscretization -- ^d
  -> IO StochasticProcess1D
squareRootProcess = $(ffiCall 'squareRootProcess) c_squareRootProcess

foreign import ccall safe "ql.h qlSquareRootProcess"
  c_squareRootProcess :: CDouble -> CDouble -> CDouble -> CDouble -> CString -> Ptr CString -> IO (Ptr CStochasticProcess1D)

vegaStressedBlackScholesProcess :: Quote -- ^x0
  -> YieldTermStructure -- ^dividendTS
  -> YieldTermStructure -- ^riskFreeTS
  -> BlackVolTermStructure -- ^blackVolTS
  -> YearFraction -- ^lowerTimeBorderForStressTest
  -> YearFraction -- ^upperTimeBorderForStressTest
  -> Double -- ^lowerAssetBorderForStressTest
  -> Double -- ^upperAssetBorderForStressTest
  -> Double -- ^stressLevel
  -> ProcessDiscretization -- ^d
  -> IO GeneralizedBlackScholesProcess
vegaStressedBlackScholesProcess = $(ffiCall 'vegaStressedBlackScholesProcess) c_vegaStressedBlackScholesProcess

foreign import ccall safe "ql.h qlVegaStressedBlackScholesProcess"
  c_vegaStressedBlackScholesProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CYearFraction -> CYearFraction -> CDouble -> CDouble -> CDouble -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
