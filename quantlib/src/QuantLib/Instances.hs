{-# LANGUAGE FlexibleContexts,TypeFamilies #-}
module QuantLib.Instances
  (
    HasUnderlying
  , underlying
  , HasDateDependentUnderlying
  , dateDepUnderlying
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Types
import QuantLib.Internal.Utils

-- classes
-- we could use MultiParamTypeClass+FunctionalDependencies to ensure uniqueness here
-- I hope to use more TypeFamilies features to make HasUnderlying (and maybe even upcast)
-- operate on ForeignPtr level rather than C-types
class (Finalizable a, Finalizable (Underlying a)) => HasUnderlying a where
  type Underlying a :: *
  c_underlying :: Ptr a -> Ptr CString -> IO (Ptr (Underlying a))

underlying :: (HasUnderlying a) => ForeignPtr a -> IO (ForeignPtr (Underlying a))
underlying o = withObject o (construct . c_underlying)

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
  c_dateDependentUnderlying :: Ptr a -> CDate -> Ptr CString -> IO (Ptr (DateDependentUnderlying a))

instance HasDateDependentUnderlying CSwapIndex where
  type DateDependentUnderlying CSwapIndex = CVanillaSwap
  c_dateDependentUnderlying = c_swapIndexVanillaSwap
foreign import ccall safe "ql.h qlSwapIndexUnderlyingSwap"
  c_swapIndexVanillaSwap :: Ptr CSwapIndex -> CDate -> Ptr CString -> IO (Ptr CVanillaSwap)

instance HasDateDependentUnderlying COvernightIndexedSwapIndex where
  type DateDependentUnderlying COvernightIndexedSwapIndex = COvernightIndexedSwap
  c_dateDependentUnderlying = c_oisIndexSwap
foreign import ccall safe "ql.h qlOvernightIndexedSwapIndexUnderlyingSwap"
  c_oisIndexSwap :: Ptr COvernightIndexedSwapIndex -> CDate -> Ptr CString -> IO (Ptr COvernightIndexedSwap)

dateDepUnderlying :: (HasDateDependentUnderlying a) => ForeignPtr a -> Day -> IO (ForeignPtr (DateDependentUnderlying a))
dateDepUnderlying o d = withObject o $ \oo -> construct $ c_dateDependentUnderlying oo (toQlDate d)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
