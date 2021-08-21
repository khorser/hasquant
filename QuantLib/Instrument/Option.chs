module QuantLib.Instrument.Option
  (
    Option
  , IsOption(..)
  , CdsOption
  , BarrierOption
  , DividendVanillaOption
  , ForwardVanillaOption
  , MargrabeOption
  , MultiAssetOption
  , OneAssetOption
  , QuantoBarrierOption
  , QuantoForwardVanillaOption
  , QuantoVanillaOption
  , VanillaOption

  , ExerciseType(..)
  , Exercise(..)
  , EuropeanExercise(..)
  , BermudanExercise(..)
  , SwingExercise(..)

  , OptionType(..)
  , PositionType(..)

  , StrikedPayoff(..)
  , PlainVanillaPayoff(..)
  , PercentageStrikePayoff(..)
  , BasketPayoff(..)
  , Payoff(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal
import Control.Monad((>=>))
{#import QuantLib.Instrument#}
import QuantLib.Internal.Enum

{#pointer *QlOption as Option foreign finalizer qlFreeOption newtype#}
instance ForeignObject Option where
  withObject = withOption
  constructor = Option
  finalizer = qlFreeOption
instance IsInstrument Option where asInstrument = qlOptionAsInstrument
{#fun qlOptionAsInstrument {`Option'} -> `Instrument' peekObject*#}

class IsOption a where
  asOption :: a -> IO Option

{#pointer *QlCdsOption as CdsOption foreign finalizer qlFreeCdsOption newtype#}
instance ForeignObject CdsOption where
  withObject = withCdsOption
  constructor = CdsOption
  finalizer = qlFreeCdsOption
instance IsOption CdsOption where asOption = qlCdsOptionAsOption
{#fun qlCdsOptionAsOption {`CdsOption'} -> `Option'#}

{#pointer *QlBarrierOption as BarrierOption foreign finalizer qlFreeBarrierOption newtype#}
instance ForeignObject BarrierOption where
  withObject = withBarrierOption
  constructor = BarrierOption
  finalizer = qlFreeBarrierOption

{#pointer *QlDividendVanillaOption as DividendVanillaOption foreign finalizer qlFreeDividendVanillaOption newtype#}
instance ForeignObject DividendVanillaOption where
  withObject = withDividendVanillaOption
  constructor = DividendVanillaOption
  finalizer = qlFreeDividendVanillaOption

{#pointer *QlForwardVanillaOption as ForwardVanillaOption foreign finalizer qlFreeForwardVanillaOption newtype#}
instance ForeignObject ForwardVanillaOption where
  withObject = withForwardVanillaOption
  constructor = ForwardVanillaOption
  finalizer = qlFreeForwardVanillaOption

{#pointer *QlMargrabeOption as MargrabeOption foreign finalizer qlFreeMargrabeOption newtype#}
instance ForeignObject MargrabeOption where
  withObject = withMargrabeOption
  constructor = MargrabeOption
  finalizer = qlFreeMargrabeOption

{#pointer *QlMultiAssetOption as MultiAssetOption foreign finalizer qlFreeMultiAssetOption newtype#}
instance ForeignObject MultiAssetOption where
  withObject = withMultiAssetOption
  constructor = MultiAssetOption
  finalizer = qlFreeMultiAssetOption
{#fun qlMultiAssetOptionAsOption {`MultiAssetOption'} -> `Option'#}
instance IsOption MultiAssetOption where asOption = qlMultiAssetOptionAsOption

{#pointer *QlOneAssetOption as OneAssetOption foreign finalizer qlFreeOneAssetOption newtype#}
instance ForeignObject OneAssetOption where
  withObject = withOneAssetOption
  constructor = OneAssetOption
  finalizer = qlFreeOneAssetOption
{#fun qlOneAssetOptionAsOption {`OneAssetOption'} -> `Option'#}
instance IsOption OneAssetOption where asOption = qlOneAssetOptionAsOption

{#pointer *QlQuantoBarrierOption as QuantoBarrierOption foreign finalizer qlFreeQuantoBarrierOption newtype#}
instance ForeignObject QuantoBarrierOption where
  withObject = withQuantoBarrierOption
  constructor = QuantoBarrierOption
  finalizer = qlFreeQuantoBarrierOption

{#pointer *QlQuantoForwardVanillaOption as QuantoForwardVanillaOption foreign finalizer qlFreeQuantoForwardVanillaOption newtype#}
instance ForeignObject QuantoForwardVanillaOption where
  withObject = withQuantoForwardVanillaOption
  constructor = QuantoForwardVanillaOption
  finalizer = qlFreeQuantoForwardVanillaOption

{#pointer *QlQuantoVanillaOption as QuantoVanillaOption foreign finalizer qlFreeQuantoVanillaOption newtype#}
instance ForeignObject QuantoVanillaOption where
  withObject = withQuantoVanillaOption
  constructor = QuantoVanillaOption
  finalizer = qlFreeQuantoVanillaOption

{#pointer *QlVanillaOption as VanillaOption foreign finalizer qlFreeVanillaOption newtype#}
instance ForeignObject VanillaOption where
  withObject = withVanillaOption
  constructor = VanillaOption
  finalizer = qlFreeVanillaOption

{#fun qlBarrierOptionAsOneAssetOption {`BarrierOption'} -> `OneAssetOption'#}
instance IsOption BarrierOption where asOption = qlBarrierOptionAsOneAssetOption >=> asOption

{#fun qlDividendVanillaOptionAsOneAssetOption {`DividendVanillaOption'} -> `OneAssetOption'#}
instance IsOption DividendVanillaOption where asOption = qlDividendVanillaOptionAsOneAssetOption >=> asOption

{#fun qlForwardVanillaOptionAsOneAssetOption {`ForwardVanillaOption'} -> `OneAssetOption'#}
instance IsOption ForwardVanillaOption where asOption = qlForwardVanillaOptionAsOneAssetOption >=> asOption

{#fun qlQuantoVanillaOptionAsOneAssetOption {`QuantoVanillaOption'} -> `OneAssetOption'#}
instance IsOption QuantoVanillaOption where asOption = qlQuantoVanillaOptionAsOneAssetOption >=> asOption

{#fun qlVanillaOptionAsOneAssetOption {`VanillaOption'} -> `OneAssetOption'#}
instance IsOption VanillaOption where asOption = qlVanillaOptionAsOneAssetOption >=> asOption

{#fun qlQuantoBarrierOptionAsBarrierOption {`QuantoBarrierOption'} -> `BarrierOption'#}
instance IsOption QuantoBarrierOption where asOption = qlQuantoBarrierOptionAsBarrierOption >=> asOption

{#fun qlMargrabeOptionAsMultiAssetOption {`MargrabeOption'} -> `MultiAssetOption'#}
instance IsOption MargrabeOption where asOption = qlMargrabeOptionAsMultiAssetOption >=> asOption

{#fun qlQuantoForwardVanillaOptionAsForwardVanillaOption {`QuantoForwardVanillaOption'} -> `ForwardVanillaOption'#}
instance IsOption QuantoForwardVanillaOption where asOption = qlQuantoForwardVanillaOptionAsForwardVanillaOption >=> asOption

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
