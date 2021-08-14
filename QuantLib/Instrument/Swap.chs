module QuantLib.Instrument.Swap
  (
    Swaption
  , Swap
  , VanillaSwap
  , AssetSwap
  , OvernightIndexedSwap
  , BMASwap
  )
  where

import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlSwaption as Swaption foreign finalizer qlFreeSwaption newtype#}
instance ForeignObject Swaption where
  withObject = withSwaption
  peekObject = newForeignPtr qlFreeSwaption >=> return . Swaption

{#pointer *QlSwap as Swap foreign finalizer qlFreeSwap newtype#}
instance ForeignObject Swap where
  withObject = withSwap
  peekObject = newForeignPtr qlFreeSwap >=> return . Swap

{#pointer *QlVanillaSwap as VanillaSwap foreign finalizer qlFreeVanillaSwap newtype#}
instance ForeignObject VanillaSwap where
  withObject = withVanillaSwap
  peekObject = newForeignPtr qlFreeVanillaSwap >=> return . VanillaSwap

{#pointer *QlAssetSwap as AssetSwap foreign finalizer qlFreeAssetSwap newtype#}
instance ForeignObject AssetSwap where
  withObject = withAssetSwap
  peekObject = newForeignPtr qlFreeAssetSwap >=> return . AssetSwap

{#pointer *QlBMASwap as BMASwap foreign finalizer qlFreeBMASwap newtype#}
instance ForeignObject BMASwap where
  withObject = withBMASwap
  peekObject = newForeignPtr qlFreeBMASwap >=> return . BMASwap

{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign finalizer qlFreeOvernightIndexedSwap newtype#}
instance ForeignObject OvernightIndexedSwap where
  withObject = withOvernightIndexedSwap
  peekObject = newForeignPtr qlFreeOvernightIndexedSwap >=> return . OvernightIndexedSwap

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
