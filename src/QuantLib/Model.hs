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
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
