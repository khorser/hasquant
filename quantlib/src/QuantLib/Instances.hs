{-# LANGUAGE FlexibleContexts,TypeFamilies, TemplateHaskell #-}
module QuantLib.Instances
  (
    underlying
  , dateDepUnderlying

  , fixedLeg
  , fixedLegNPV
  , fixedLegBPS
  , fairRate

  , fairSpread

  , floatingLeg
  , floatingLegNPV
  , floatingLegBPS

  , delta
  , gamma
  , rho
  , theta
  , vega
  , dividendRho
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

-- classes
-- we could use MultiParamTypeClass+FunctionalDependencies to ensure uniqueness here
-- I hope to use more TypeFamilies features to make HasUnderlying (and maybe even upcast)
-- operate on ForeignPtr level rather than C-types
class (Finalizable a, Finalizable (Underlying a)) => HasUnderlying a where
  type Underlying a :: *
  c_underlying :: Ptr a -> Ptr CString -> IO (Ptr (Underlying a))

underlying :: (HasUnderlying a) => ForeignPtr a -> IO (ForeignPtr (Underlying a))
underlying = $(ffiCall 'underlying) c_underlying

instance HasUnderlying CBondHelper where
  type Underlying CBondHelper = CBond
  c_underlying = c_bondHelperBond
foreign import ccall safe "ql.h qlBondHelperBond"
  c_bondHelperBond :: Ptr CBondHelper -> Ptr CString -> IO (Ptr CBond)

instance HasUnderlying COISRateHelper where
  type Underlying COISRateHelper = COvernightIndexedSwap
  c_underlying = c_oiSwapHelperSwap
foreign import ccall safe "ql.h qlOISRateHelperSwap"
  c_oiSwapHelperSwap :: Ptr COISRateHelper -> Ptr CString -> IO (Ptr COvernightIndexedSwap)

instance HasUnderlying CSwapRateHelper where
  type Underlying CSwapRateHelper = CVanillaSwap
  c_underlying = c_swapHelperSwap
foreign import ccall safe "ql.h qlSwapRateHelperSwap"
  c_swapHelperSwap :: Ptr CSwapRateHelper -> Ptr CString -> IO (Ptr CVanillaSwap)

class (Finalizable a, Finalizable (DateDependentUnderlying a)) => HasDateDependentUnderlying a where
  type DateDependentUnderlying a :: *
  c_dateDepUnderlying :: Ptr a -> CDate -> Ptr CString -> IO (Ptr (DateDependentUnderlying a))

instance HasDateDependentUnderlying CSwapIndex where
  type DateDependentUnderlying CSwapIndex = CVanillaSwap
  c_dateDepUnderlying = c_swapIndexVanillaSwap
foreign import ccall safe "ql.h qlSwapIndexUnderlyingSwap"
  c_swapIndexVanillaSwap :: Ptr CSwapIndex -> CDate -> Ptr CString -> IO (Ptr CVanillaSwap)

instance HasDateDependentUnderlying COvernightIndexedSwapIndex where
  type DateDependentUnderlying COvernightIndexedSwapIndex = COvernightIndexedSwap
  c_dateDepUnderlying = c_oisIndexSwap
foreign import ccall safe "ql.h qlOvernightIndexedSwapIndexUnderlyingSwap"
  c_oisIndexSwap :: Ptr COvernightIndexedSwapIndex -> CDate -> Ptr CString -> IO (Ptr COvernightIndexedSwap)

dateDepUnderlying :: (HasDateDependentUnderlying a) => ForeignPtr a -> Day -> IO (ForeignPtr (DateDependentUnderlying a))
dateDepUnderlying = $(ffiCall 'dateDepUnderlying) c_dateDepUnderlying

class (Finalizable a) => SwapWithFixedLeg a where
  c_fairRate :: Ptr a -> Ptr CString -> IO CDouble
  c_fixedLeg :: Ptr a -> Ptr CString -> IO (Ptr CLeg)
  c_fixedLegBPS :: Ptr a -> Ptr CString -> IO CDouble
  c_fixedLegNPV :: Ptr a -> Ptr CString -> IO CDouble

instance SwapWithFixedLeg CVanillaSwap where
  c_fairRate = c_vanillaSwapFairRate
  c_fixedLeg = c_vanillaSwapFixedLeg
  c_fixedLegBPS = c_vanillaSwapFixedLegBPS
  c_fixedLegNPV = c_vanillaSwapFixedLegNPV

fairRate :: (SwapWithFixedLeg a) => ForeignPtr a -> IO Double
fairRate = $(ffiCallX 'fairRate) c_fairRate

fixedLeg :: (SwapWithFixedLeg a) => ForeignPtr a -> IO Leg
fixedLeg = $(ffiCall 'fixedLeg) c_fixedLeg

fixedLegBPS :: (SwapWithFixedLeg a) => ForeignPtr a -> IO Double
fixedLegBPS = $(ffiCallX 'fixedLegBPS) c_fixedLegBPS

fixedLegNPV :: (SwapWithFixedLeg a) => ForeignPtr a -> IO Double
fixedLegNPV = $(ffiCallX 'fixedLegNPV) c_fixedLegNPV

foreign import ccall safe "ql.h qlVanillaSwapFairRate"
  c_vanillaSwapFairRate :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlVanillaSwapFixedLeg"
  c_vanillaSwapFixedLeg :: Ptr CVanillaSwap -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlVanillaSwapFixedLegBPS"
  c_vanillaSwapFixedLegBPS :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlVanillaSwapFixedLegNPV"
  c_vanillaSwapFixedLegNPV :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

instance SwapWithFixedLeg COvernightIndexedSwap where
  c_fairRate = c_oisFairRate
  c_fixedLeg = c_oisFixedLeg
  c_fixedLegBPS = c_oisFixedLegBPS
  c_fixedLegNPV = c_oisFixedLegNPV

foreign import ccall safe "ql.h qlOvernightIndexedSwapFairRate"
  c_oisFairRate :: Ptr COvernightIndexedSwap -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOvernightIndexedSwapFixedLeg"
  c_oisFixedLeg :: Ptr COvernightIndexedSwap -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlOvernightIndexedSwapFixedLegBPS"
  c_oisFixedLegBPS :: Ptr COvernightIndexedSwap -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOvernightIndexedSwapFixedLegNPV"
  c_oisFixedLegNPV :: Ptr COvernightIndexedSwap -> Ptr CString -> IO CDouble

class (Finalizable a) => SwapWithSpread a where
  c_fairSpread :: Ptr a -> Ptr CString -> IO CDouble

fairSpread :: (SwapWithSpread a) => ForeignPtr a -> IO Double
fairSpread = $(ffiCallX 'fairSpread) c_fairSpread

instance SwapWithSpread CVanillaSwap where
  c_fairSpread = c_vanillaSwapFairSpread
foreign import ccall safe "ql.h qlVanillaSwapFairSpread"
  c_vanillaSwapFairSpread :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

instance SwapWithSpread COvernightIndexedSwap where
  c_fairSpread = c_oisFairSpread
foreign import ccall safe "ql.h qlOvernightIndexedSwapFairSpread"
  c_oisFairSpread :: Ptr COvernightIndexedSwap -> Ptr CString -> IO CDouble

instance SwapWithSpread CAssetSwap where
  c_fairSpread = c_assetSwapFairSpread
foreign import ccall safe "ql.h qlAssetSwapFairSpread"
  c_assetSwapFairSpread :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

class (Finalizable a) => SwapWithFloatingLeg a where
  c_floatingLeg :: Ptr a -> Ptr CString -> IO (Ptr CLeg)
  c_floatingLegBPS :: Ptr a -> Ptr CString -> IO CDouble
  c_floatingLegNPV :: Ptr a -> Ptr CString -> IO CDouble

floatingLeg :: (SwapWithFloatingLeg a) => ForeignPtr a -> IO Leg
floatingLeg = $(ffiCall 'floatingLeg) c_floatingLeg

floatingLegBPS :: (SwapWithFloatingLeg a) => ForeignPtr a -> IO Double
floatingLegBPS = $(ffiCallX 'floatingLegBPS) c_floatingLegBPS

floatingLegNPV :: (SwapWithFloatingLeg a) => ForeignPtr a -> IO Double
floatingLegNPV = $(ffiCallX 'floatingLegNPV) c_floatingLegNPV

instance SwapWithFloatingLeg CVanillaSwap where
  c_floatingLeg = c_vanillaSwapFloatingLeg
  c_floatingLegBPS = c_vanillaSwapFloatingLegBPS
  c_floatingLegNPV = c_vanillaSwapFloatingLegNPV

foreign import ccall safe "ql.h qlVanillaSwapFloatingLeg"
  c_vanillaSwapFloatingLeg :: Ptr CVanillaSwap -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlVanillaSwapFloatingLegBPS"
  c_vanillaSwapFloatingLegBPS :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlVanillaSwapFloatingLegNPV"
  c_vanillaSwapFloatingLegNPV :: Ptr CVanillaSwap -> Ptr CString -> IO CDouble

instance SwapWithFloatingLeg CAssetSwap where
  c_floatingLeg = c_assetSwapFloatingLeg
  c_floatingLegBPS = c_assetSwapFloatingLegBPS
  c_floatingLegNPV = c_assetSwapFloatingLegNPV

foreign import ccall safe "ql.h qlAssetSwapFloatingLeg"
  c_assetSwapFloatingLeg :: Ptr CAssetSwap -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlAssetSwapFloatingLegBPS"
  c_assetSwapFloatingLegBPS :: Ptr CAssetSwap -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlAssetSwapFloatingLegNPV"
  c_assetSwapFloatingLegNPV :: Ptr CAssetSwap -> Ptr CString -> IO CDouble

class (Finalizable a) => OptionWithGreeks a where
  c_delta :: Ptr a -> Ptr CString -> IO CDouble
  c_gamma :: Ptr a -> Ptr CString -> IO CDouble
  c_rho :: Ptr a -> Ptr CString -> IO CDouble
  c_theta :: Ptr a -> Ptr CString -> IO CDouble
  c_vega :: Ptr a -> Ptr CString -> IO CDouble
  c_dividendRho :: Ptr a -> Ptr CString -> IO CDouble

delta :: (OptionWithGreeks a) => ForeignPtr a -> IO Double
delta = $(ffiCallX 'delta) c_delta

gamma :: (OptionWithGreeks a) => ForeignPtr a -> IO Double
gamma = $(ffiCallX 'gamma) c_gamma

rho :: (OptionWithGreeks a) => ForeignPtr a -> IO Double
rho = $(ffiCallX 'rho) c_rho

theta :: (OptionWithGreeks a) => ForeignPtr a -> IO Double
theta = $(ffiCallX 'theta) c_theta

vega :: (OptionWithGreeks a) => ForeignPtr a -> IO Double
vega = $(ffiCallX 'vega) c_vega

dividendRho :: (OptionWithGreeks a) => ForeignPtr a -> IO Double
dividendRho = $(ffiCallX 'dividendRho) c_dividendRho

instance OptionWithGreeks CMultiAssetOption where
  c_delta = c_multiAssetOptionDelta
  c_gamma = c_multiAssetOptionGamma
  c_rho = c_multiAssetOptionRho
  c_theta = c_multiAssetOptionTheta
  c_vega = c_multiAssetOptionVega
  c_dividendRho = c_multiAssetOptionDividendRho

instance OptionWithGreeks COneAssetOption where
  c_delta = c_oneAssetOptionDelta
  c_gamma = c_oneAssetOptionGamma
  c_rho = c_oneAssetOptionRho
  c_theta = c_oneAssetOptionTheta
  c_vega = c_oneAssetOptionVega
  c_dividendRho = c_oneAssetOptionDividendRho

foreign import ccall safe "ql.h qlMultiAssetOptionDelta"
  c_multiAssetOptionDelta :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlMultiAssetOptionDividendRho"
  c_multiAssetOptionDividendRho :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlMultiAssetOptionGamma"
  c_multiAssetOptionGamma :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlMultiAssetOptionRho"
  c_multiAssetOptionRho :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlMultiAssetOptionTheta"
  c_multiAssetOptionTheta :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlMultiAssetOptionVega"
  c_multiAssetOptionVega :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

foreign import ccall safe "ql.h qlOneAssetOptionDelta"
  c_oneAssetOptionDelta :: Ptr COneAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOneAssetOptionDividendRho"
  c_oneAssetOptionDividendRho :: Ptr COneAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOneAssetOptionGamma"
  c_oneAssetOptionGamma :: Ptr COneAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOneAssetOptionRho"
  c_oneAssetOptionRho :: Ptr COneAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOneAssetOptionTheta"
  c_oneAssetOptionTheta :: Ptr COneAssetOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlOneAssetOptionVega"
  c_oneAssetOptionVega :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
