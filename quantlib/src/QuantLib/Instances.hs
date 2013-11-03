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

  , qrho
  , qvega
  , qlambda

  , impliedVolatility

  , setPricingEngine
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

class (Finalizable a) => QuantoOption a where
  c_qrho :: Ptr a -> Ptr CString -> IO CDouble
  c_qvega :: Ptr a -> Ptr CString -> IO CDouble
  c_qlambda :: Ptr a -> Ptr CString -> IO CDouble

qrho :: (QuantoOption a) => ForeignPtr a -> IO Double
qrho = $(ffiCallX 'qrho) c_qrho

qvega :: (QuantoOption a) => ForeignPtr a -> IO Double
qvega = $(ffiCallX 'qvega) c_qvega

qlambda :: (QuantoOption a) => ForeignPtr a -> IO Double
qlambda = $(ffiCallX 'qlambda) c_qlambda

instance QuantoOption CQuantoBarrierOption where
  c_qrho = c_quantoBarrierOptionQrho
  c_qvega = c_quantoBarrierOptionQvega
  c_qlambda = c_quantoBarrierOptionQlambda

instance QuantoOption CQuantoForwardVanillaOption where
  c_qrho = c_quantoForwardVanillaOptionQrho
  c_qvega = c_quantoForwardVanillaOptionQvega
  c_qlambda = c_quantoForwardVanillaOptionQlambda

instance QuantoOption CQuantoVanillaOption where
  c_qrho = c_quantoVanillaOptionQrho
  c_qvega = c_quantoVanillaOptionQvega
  c_qlambda = c_quantoVanillaOptionQlambda

foreign import ccall safe "ql.h qlQuantoBarrierOptionQrho"
  c_quantoBarrierOptionQrho :: Ptr CQuantoBarrierOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlQuantoBarrierOptionQvega"
  c_quantoBarrierOptionQvega :: Ptr CQuantoBarrierOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlQuantoBarrierOptionQlambda"
  c_quantoBarrierOptionQlambda :: Ptr CQuantoBarrierOption -> Ptr CString -> IO CDouble

foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionQrho"
  c_quantoForwardVanillaOptionQrho :: Ptr CQuantoForwardVanillaOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionQvega"
  c_quantoForwardVanillaOptionQvega :: Ptr CQuantoForwardVanillaOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionQlambda"
  c_quantoForwardVanillaOptionQlambda :: Ptr CQuantoForwardVanillaOption -> Ptr CString -> IO CDouble

foreign import ccall safe "ql.h qlQuantoVanillaOptionQrho"
  c_quantoVanillaOptionQrho :: Ptr CQuantoVanillaOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlQuantoVanillaOptionQvega"
  c_quantoVanillaOptionQvega :: Ptr CQuantoVanillaOption -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlQuantoVanillaOptionQlambda"
  c_quantoVanillaOptionQlambda :: Ptr CQuantoVanillaOption -> Ptr CString -> IO CDouble

class (Finalizable a) => VolatileOption a where
  c_impliedVolatility :: Ptr a -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |/Warning/ currently, this method returns the Black-Scholes implied volatility using analytic formulas for European options and a finite-difference method for American and Bermudan options. It will give unconsistent results if the pricing was performed with any other methods (such as jump-diffusion models.)Warningoptions with a gamma that changes sign (e.g., binary options) have values that are not monotonic in the volatility. In these cases, the calculation can fail and the result (if any) is almost meaningless. Another possible source of failure is to have a target value that is not attainable with any volatility, e.g., a target value lower than the intrinsic value in the case of American options.
impliedVolatility :: (VolatileOption a) => ForeignPtr a
  -> Double -- ^price
  -> GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> IO Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

instance VolatileOption CDividendVanillaOption where
  c_impliedVolatility = c_dividendVanillaOptionImpliedVolatility

instance VolatileOption CVanillaOption where
  c_impliedVolatility = c_VanillaOptionImpliedVolatility

instance VolatileOption CBarrierOption where
  c_impliedVolatility = c_barrierOptionImpliedVolatility

foreign import ccall safe "ql.h qlDividendVanillaOptionImpliedVolatility"
  c_dividendVanillaOptionImpliedVolatility :: Ptr CDividendVanillaOption -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlVanillaOptionImpliedVolatility"
  c_VanillaOptionImpliedVolatility :: Ptr CVanillaOption -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlBarrierOptionImpliedVolatility"
  c_barrierOptionImpliedVolatility :: Ptr CBarrierOption -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

class (Finalizable a) => Priceable a where
  c_setPricingEngine :: Ptr a -> Ptr CPricingEngine -> Ptr CString -> IO ()

-- |set the pricing engine to be used.
-- Sets a new pricing engine to the given Instrument. QuantLibXL: qlInstrumentSetPricingEngine
setPricingEngine :: (Priceable a) => ForeignPtr a -> PricingEngine -> IO ()
setPricingEngine = $(ffiCallX 'setPricingEngine) c_setPricingEngine

instance Priceable CInstrument where
  c_setPricingEngine = c_instrumentSetPricingEngine

instance Priceable CCalibrationHelper where
  c_setPricingEngine = c_calibrationHelperSetPricingEngine

foreign import ccall safe "ql.h qlInstrumentSetPricingEngine"
  c_instrumentSetPricingEngine :: Ptr CInstrument -> Ptr CPricingEngine -> Ptr CString -> IO ()
foreign import ccall safe "ql.h qlCalibrationHelperSetPricingEngine"
  c_calibrationHelperSetPricingEngine :: Ptr CCalibrationHelper -> Ptr CPricingEngine -> Ptr CString -> IO ()

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
