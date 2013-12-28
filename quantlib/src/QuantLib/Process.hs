{-# LANGUAGE TemplateHaskell #-}
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

  , batesProcess
  , extOUWithJumpsProcess
  , g2ForwardProcess
  , g2Process
  , gemanRoncoroniProcess
  , geometricBrownianMotionProcess
  , gjrGARCHProcess
  , hestonProcess
  , hullWhiteForwardProcess
  , hullWhiteProcess
  , hybridHestonHullWhiteProcess
  , klugeExtOUProcess
  , liborForwardModelProcess
  , merton76Process
  , ornsteinUhlenbeckProcess
  , varianceGammaProcess
  , stochasticProcessArray

  , blackScholesTheta
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.ProcessDiscretization(ProcessDiscretization,
  ExtendedDiscretization, HestonProcessDiscretization,
  GJRGARCHProcessDiscretization, HybridHestonHullWhiteProcessDiscretization)
import QuantLib.Types

blackProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> QLE s (BlackProcess s)
blackProcess = $(ffiCall 'blackProcess) c_blackProcess

foreign import ccall safe "ql.h qlBlackProcess"
  c_blackProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CBlackProcess)

blackScholesMertonProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^dividendTS
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> QLE s (GeneralizedBlackScholesProcess s)
blackScholesMertonProcess = $(ffiCall 'blackScholesMertonProcess) c_blackScholesMertonProcess

foreign import ccall safe "ql.h qlBlackScholesMertonProcess"
  c_blackScholesMertonProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

blackScholesProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> QLE s (GeneralizedBlackScholesProcess s)
blackScholesProcess = $(ffiCall 'blackScholesProcess) c_blackScholesProcess

foreign import ccall safe "ql.h qlBlackScholesProcess"
  c_blackScholesProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

extendedBlackScholesMertonProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^dividendTS
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> ExtendedDiscretization -- ^evolDisc
  -> QLE s (GeneralizedBlackScholesProcess s)
extendedBlackScholesMertonProcess = $(ffiCall 'extendedBlackScholesMertonProcess) c_extendedBlackScholesMertonProcess

foreign import ccall safe "ql.h qlExtendedBlackScholesMertonProcess"
  c_extendedBlackScholesMertonProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> CInt -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

garmanKohlagenProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^foreignRiskFreeTS
  -> YieldTermStructure s -- ^domesticRiskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> QLE s (GeneralizedBlackScholesProcess s)
garmanKohlagenProcess = $(ffiCall 'garmanKohlagenProcess) c_garmanKohlagenProcess

foreign import ccall safe "ql.h qlGarmanKohlagenProcess"
  c_garmanKohlagenProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

generalizedBlackScholesProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^dividendTS
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> ProcessDiscretization -- ^d
  -> QLE s (GeneralizedBlackScholesProcess s)
generalizedBlackScholesProcess = $(ffiCall 'generalizedBlackScholesProcess) c_generalizedBlackScholesProcess

foreign import ccall safe "ql.h qlGeneralizedBlackScholesProcess"
  c_generalizedBlackScholesProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

squareRootProcess :: Double -- ^b
  -> Double -- ^a
  -> Double -- ^sigma
  -> Double -- ^x0
  -> ProcessDiscretization -- ^d
  -> QLE s (StochasticProcess1D s)
squareRootProcess = $(ffiCall 'squareRootProcess) c_squareRootProcess

foreign import ccall safe "ql.h qlSquareRootProcess"
  c_squareRootProcess :: CDouble -> CDouble -> CDouble -> CDouble -> CString -> Ptr CString -> IO (Ptr CStochasticProcess1D)

vegaStressedBlackScholesProcess :: Quote s -- ^x0
  -> YieldTermStructure s -- ^dividendTS
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> YearFraction -- ^lowerTimeBorderForStressTest
  -> YearFraction -- ^upperTimeBorderForStressTest
  -> Double -- ^lowerAssetBorderForStressTest
  -> Double -- ^upperAssetBorderForStressTest
  -> Double -- ^stressLevel
  -> ProcessDiscretization -- ^d
  -> QLE s (GeneralizedBlackScholesProcess s)
vegaStressedBlackScholesProcess = $(ffiCall 'vegaStressedBlackScholesProcess) c_vegaStressedBlackScholesProcess

foreign import ccall safe "ql.h qlVegaStressedBlackScholesProcess"
  c_vegaStressedBlackScholesProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CYearFraction -> CYearFraction -> CDouble -> CDouble -> CDouble -> CString -> Ptr CString -> IO (Ptr CGeneralizedBlackScholesProcess)

batesProcess :: YieldTermStructure s -- ^riskFreeRate
  -> YieldTermStructure s -- ^dividendYield
  -> Quote s -- ^s0
  -> Double -- ^v0
  -> Double -- ^kappa
  -> Double -- ^theta
  -> Double -- ^sigma
  -> Double -- ^rho
  -> Double -- ^lambda
  -> Double -- ^nu
  -> Double -- ^delta
  -> HestonProcessDiscretization -- ^d
  -> QLE s (BatesProcess s)
batesProcess = $(ffiCall 'batesProcess) c_batesProcess

foreign import ccall safe "ql.h qlBatesProcess"
  c_batesProcess :: Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CInt -> Ptr CString -> IO (Ptr CBatesProcess)

extOUWithJumpsProcess :: ExtendedOrnsteinUhlenbeckProcess s -- ^process
  -> Double -- ^Y0
  -> Double -- ^beta
  -> Double -- ^jumpIntensity
  -> Double -- ^eta
  -> QLE s (ExtOUWithJumpsProcess s)
extOUWithJumpsProcess = $(ffiCall 'extOUWithJumpsProcess) c_extOUWithJumpsProcess

foreign import ccall safe "ql.h qlExtOUWithJumpsProcess"
  c_extOUWithJumpsProcess :: Ptr CExtendedOrnsteinUhlenbeckProcess -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CExtOUWithJumpsProcess)

g2ForwardProcess :: Double -- ^a
  -> Double -- ^sigma
  -> Double -- ^b
  -> Double -- ^eta
  -> Double -- ^rho
  -> QLE s (StochasticProcess s)
g2ForwardProcess = $(ffiCall 'g2ForwardProcess) c_g2ForwardProcess

foreign import ccall safe "ql.h qlG2ForwardProcess"
  c_g2ForwardProcess :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStochasticProcess)

g2Process :: Double -- ^a
  -> Double -- ^sigma
  -> Double -- ^b
  -> Double -- ^eta
  -> Double -- ^rho
  -> QLE s (StochasticProcess s)
g2Process = $(ffiCall 'g2Process) c_g2Process

foreign import ccall safe "ql.h qlG2Process"
  c_g2Process :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStochasticProcess)

gemanRoncoroniProcess :: Double -- ^x0
  -> Double -- ^alpha
  -> Double -- ^beta
  -> Double -- ^gamma
  -> Double -- ^delta
  -> Double -- ^eps
  -> Double -- ^zeta
  -> Double -- ^d
  -> Double -- ^k
  -> Double -- ^tau
  -> Double -- ^sig2
  -> Double -- ^a
  -> Double -- ^b
  -> Double -- ^theta1
  -> Double -- ^theta2
  -> Double -- ^theta3
  -> Double -- ^psi
  -> QLE s (StochasticProcess1D s)
gemanRoncoroniProcess = $(ffiCall 'gemanRoncoroniProcess) c_gemanRoncoroniProcess

foreign import ccall safe "ql.h qlGemanRoncoroniProcess"
  c_gemanRoncoroniProcess :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStochasticProcess1D)

geometricBrownianMotionProcess :: Double -- ^initialValue
  -> Double -- ^mue
  -> Double -- ^sigma
  -> QLE s (StochasticProcess1D s)
geometricBrownianMotionProcess = $(ffiCall 'geometricBrownianMotionProcess) c_geometricBrownianMotionProcess

foreign import ccall safe "ql.h qlGeometricBrownianMotionProcess"
  c_geometricBrownianMotionProcess :: CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStochasticProcess1D)

gjrGARCHProcess :: YieldTermStructure s -- ^riskFreeRate
  -> YieldTermStructure s -- ^dividendYield
  -> Quote s -- ^s0
  -> Double -- ^v0
  -> Double -- ^omega
  -> Double -- ^alpha
  -> Double -- ^beta
  -> Double -- ^gamma
  -> Double -- ^lambda
  -> Double -- ^daysPerYear
  -> GJRGARCHProcessDiscretization -- ^d
  -> QLE s (GJRGARCHProcess s)
gjrGARCHProcess = $(ffiCall 'gjrGARCHProcess) c_gjrGARCHProcess

foreign import ccall safe "ql.h qlGJRGARCHProcess"
  c_gjrGARCHProcess :: Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CInt -> Ptr CString -> IO (Ptr CGJRGARCHProcess)

hestonProcess :: YieldTermStructure s -- ^riskFreeRate
  -> YieldTermStructure s -- ^dividendYield
  -> Quote s -- ^s0
  -> Double -- ^v0
  -> Double -- ^kappa
  -> Double -- ^theta
  -> Double -- ^sigma
  -> Double -- ^rho
  -> HestonProcessDiscretization -- ^d
  -> QLE s (HestonProcess s)
hestonProcess = $(ffiCall 'hestonProcess) c_hestonProcess

foreign import ccall safe "ql.h qlHestonProcess"
  c_hestonProcess :: Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CInt -> Ptr CString -> IO (Ptr CHestonProcess)

hullWhiteForwardProcess :: YieldTermStructure s -- ^h
  -> Double -- ^a
  -> Double -- ^sigma
  -> QLE s (HullWhiteForwardProcess s)
hullWhiteForwardProcess = $(ffiCall 'hullWhiteForwardProcess) c_hullWhiteForwardProcess

foreign import ccall safe "ql.h qlHullWhiteForwardProcess"
  c_hullWhiteForwardProcess :: Ptr CYieldTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CHullWhiteForwardProcess)

hullWhiteProcess :: YieldTermStructure s -- ^h
  -> Double -- ^a
  -> Double -- ^sigma
  -> QLE s (HullWhiteProcess s)
hullWhiteProcess = $(ffiCall 'hullWhiteProcess) c_hullWhiteProcess

foreign import ccall safe "ql.h qlHullWhiteProcess"
  c_hullWhiteProcess :: Ptr CYieldTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CHullWhiteProcess)

hybridHestonHullWhiteProcess :: HestonProcess s -- ^hestonProcess
  -> HullWhiteForwardProcess s -- ^hullWhiteProcess
  -> Double -- ^corrEquityShortRate
  -> HybridHestonHullWhiteProcessDiscretization -- ^discretization
  -> QLE s (HybridHestonHullWhiteProcess s)
hybridHestonHullWhiteProcess = $(ffiCall 'hybridHestonHullWhiteProcess) c_hybridHestonHullWhiteProcess

foreign import ccall safe "ql.h qlHybridHestonHullWhiteProcess"
  c_hybridHestonHullWhiteProcess :: Ptr CHestonProcess -> Ptr CHullWhiteForwardProcess -> CDouble -> CInt -> Ptr CString -> IO (Ptr CHybridHestonHullWhiteProcess)

klugeExtOUProcess :: Double -- ^rho
  -> ExtOUWithJumpsProcess s -- ^kluge
  -> ExtendedOrnsteinUhlenbeckProcess s -- ^extOU
  -> QLE s (KlugeExtOUProcess s)
klugeExtOUProcess = $(ffiCall 'klugeExtOUProcess) c_klugeExtOUProcess

foreign import ccall safe "ql.h qlKlugeExtOUProcess"
  c_klugeExtOUProcess :: CDouble -> Ptr CExtOUWithJumpsProcess -> Ptr CExtendedOrnsteinUhlenbeckProcess -> Ptr CString -> IO (Ptr CKlugeExtOUProcess)

liborForwardModelProcess :: Word -- ^size
  -> IborIndex s -- ^index
  -> QLE s (LiborForwardModelProcess s)
liborForwardModelProcess = $(ffiCall 'liborForwardModelProcess) c_liborForwardModelProcess

foreign import ccall safe "ql.h qlLiborForwardModelProcess"
  c_liborForwardModelProcess :: CUInt -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CLiborForwardModelProcess)

merton76Process :: Quote s -- ^stateVariable
  -> YieldTermStructure s -- ^dividendTS
  -> YieldTermStructure s -- ^riskFreeTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> Quote s -- ^jumpInt
  -> Quote s -- ^logJMean
  -> Quote s -- ^logJVol
  -> ProcessDiscretization -- ^d
  -> QLE s (Merton76Process s)
merton76Process = $(ffiCall 'merton76Process) c_merton76Process

foreign import ccall safe "ql.h qlMerton76Process"
  c_merton76Process :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> Ptr CQuote -> Ptr CQuote -> Ptr CQuote -> CString -> Ptr CString -> IO (Ptr CMerton76Process)

ornsteinUhlenbeckProcess :: Double -- ^speed
  -> Double -- ^vol
  -> Double -- ^x0
  -> Double -- ^level
  -> QLE s (StochasticProcess1D s)
ornsteinUhlenbeckProcess = $(ffiCall 'ornsteinUhlenbeckProcess) c_ornsteinUhlenbeckProcess

foreign import ccall safe "ql.h qlOrnsteinUhlenbeckProcess"
  c_ornsteinUhlenbeckProcess :: CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStochasticProcess1D)

varianceGammaProcess :: Quote s -- ^s0
  -> YieldTermStructure s -- ^dividendYield
  -> YieldTermStructure s -- ^riskFreeRate
  -> Double -- ^sigma
  -> Double -- ^nu
  -> Double -- ^theta
  -> QLE s (VarianceGammaProcess s)
varianceGammaProcess = $(ffiCall 'varianceGammaProcess) c_varianceGammaProcess

foreign import ccall safe "ql.h qlVarianceGammaProcess"
  c_varianceGammaProcess :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CVarianceGammaProcess)

stochasticProcessArray :: [StochasticProcess1D s]
  -> Matrix Double -- ^correlation
  -> QLE s (StochasticProcessArray s)
stochasticProcessArray = $(ffiCall 'stochasticProcessArray) c_stochasticProcessArray

foreign import ccall safe "ql.h qlStochasticProcessArray"
  c_stochasticProcessArray :: CUInt -> Ptr (Ptr CStochasticProcess1D) -> CUInt -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CStochasticProcessArray)

-- |default theta calculation for Black-Scholes options
blackScholesTheta :: GeneralizedBlackScholesProcess s
  -> Double -- ^value
  -> Double -- ^delta
  -> Double -- ^gamma
  -> QLE s Double
blackScholesTheta = $(ffiCallX 'blackScholesTheta) c_blackScholesTheta

foreign import ccall safe "ql.h qlQuantLibBlackScholesTheta"
  c_blackScholesTheta :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
