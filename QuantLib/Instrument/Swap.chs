module QuantLib.Instrument.Swap
  (
    Swaption
  , Swap
  , VanillaSwap
  , AssetSwap
  , OvernightIndexedSwap
  , BMASwap

  , asInstrument
  , asSwap

  , impliedVolatility
  , SwapType(..)

  , swap'
  )
  where

import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.CashFlow#}(Leg)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum SwapType {} deriving(Show, Eq)#}

{#pointer *QlSwaption as Swaption foreign finalizer qlFreeSwaption newtype#}
instance ForeignObject Swaption where
  withObject = withSwaption
  constructor = Swaption
  finalizer = qlFreeSwaption

{#pointer *QlSwap as Swap foreign finalizer qlFreeSwap newtype#}
instance ForeignObject Swap where
  withObject = withSwap
  constructor = Swap
  finalizer = qlFreeSwap
{#fun qlSwapAsInstrument {`Swap'} -> `Instrument' peekObject*#}
instance IsInstrument Swap where asInstrument = qlSwapAsInstrument

class IsSwap a where asSwap :: a -> IO Swap

{#pointer *QlVanillaSwap as VanillaSwap foreign finalizer qlFreeVanillaSwap newtype#}
instance ForeignObject VanillaSwap where
  withObject = withVanillaSwap
  constructor = VanillaSwap
  finalizer = qlFreeVanillaSwap
{#fun qlVanillaSwapAsSwap {`VanillaSwap'} -> `Swap'#}
instance IsSwap VanillaSwap where asSwap = qlVanillaSwapAsSwap

{#pointer *QlAssetSwap as AssetSwap foreign finalizer qlFreeAssetSwap newtype#}
instance ForeignObject AssetSwap where
  withObject = withAssetSwap
  constructor = AssetSwap
  finalizer = qlFreeAssetSwap
{#fun qlAssetSwapAsSwap {`AssetSwap'} -> `Swap'#}
instance IsSwap AssetSwap where asSwap = qlAssetSwapAsSwap

{#pointer *QlBMASwap as BMASwap foreign finalizer qlFreeBMASwap newtype#}
instance ForeignObject BMASwap where
  withObject = withBMASwap
  constructor = BMASwap
  finalizer = qlFreeBMASwap
{#fun qlBMASwapAsSwap {`BMASwap'} -> `Swap'#}
instance IsSwap BMASwap where asSwap = qlBMASwapAsSwap

{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign finalizer qlFreeOvernightIndexedSwap newtype#}
instance ForeignObject OvernightIndexedSwap where
  withObject = withOvernightIndexedSwap
  constructor = OvernightIndexedSwap
  finalizer = qlFreeOvernightIndexedSwap
{#fun qlOvernightIndexedSwapAsSwap {`OvernightIndexedSwap'} -> `Swap'#}
instance IsSwap OvernightIndexedSwap where asSwap = qlOvernightIndexedSwapAsSwap

-- |implied volatility
{#fun qlSwaptionImpliedVolatility as impliedVolatility {`Swaption', `Double', `YieldTermStructure', `Double', `Double', fromIntegral `Word', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Multi leg constructor.
swap' :: [(Leg, Bool)] -- ^(legs, payer)
  -> IO Swap
swap' = (uncurry qlSwap1) . unzip
{#fun qlSwap1 {withObjectArray* `[Leg]'&, withBoolArray* `[Bool]'&, preErrorCheck- `String' errorCheck*-} -> `Swap'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
