module QuantLib.Instrument.Option
  (
    Option
  , asOption
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
  , TypePayoff(..)

  , barrierOption
  , dividendVanillaOption
  , forwardVanillaOption
  , delta1
  , delta2
  , gamma1
  , gamma2
  , margrabeOption

  , multiAssetOption
  , deltaForward
  , elasticity
  , itmCashProbability
  , oneAssetOption
  , strikeSensitivity
  , thetaPerDay
  , quantoBarrierOption
  , quantoForwardVanillaOption
  , quantoVanillaOption
  , vanillaOption
  , dividendBarrierOption
  , basketOption
  , himalayaOption
  , pagodaOption
  , spreadOption
  , cliquetOption
  , continuousAveragingAsianOption
  , continuousFixedLookbackOption
  , continuousFloatingLookbackOption
  , discreteAveragingAsianOption
  , vanillaStorageOption
  , vanillaSwingOption
  , europeanOption
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

-- some necessary boilerplate
{#pointer *QlPayoff foreign newtype nocode#}
{#pointer *QlPercentageStrikePayoff foreign newtype nocode#}
{#pointer *QlStrikedTypePayoff foreign newtype nocode#}
{#pointer *QlTypePayoff foreign newtype nocode#}
{#pointer *QlBasketPayoff foreign newtype nocode#}
{#pointer *QlPlainVanillaPayoff foreign newtype nocode#}
{#pointer *QlExercise foreign newtype nocode#}
{#pointer *QlEuropeanExercise foreign newtype nocode#}
{#pointer *QlSwingExercise foreign newtype nocode#}
{#pointer *QlBermudanExercise foreign newtype nocode#}

{#fun qlQuantoForwardVanillaOption as quantoForwardVanillaOption {`Double', withDay* `Day', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `QuantoForwardVanillaOption'#}

{#fun qlQuantoVanillaOption as quantoVanillaOption {withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `QuantoVanillaOption'#}

{#fun qlVanillaOption as vanillaOption {withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `VanillaOption'#}

{#fun qlBarrierOption as barrierOption {`BarrierType', `Double', `Double', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `BarrierOption'#}

{#fun qlDividendVanillaOption as dividendVanillaOption {withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, preErrorCheck- `String' errorCheck*-} -> `DividendVanillaOption'#}

{#fun qlForwardVanillaOption as forwardVanillaOption {`Double', withDay* `Day', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `ForwardVanillaOption'#}

{#fun qlMargrabeOptionDelta1 as delta1 {`MargrabeOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlMargrabeOptionDelta2 as delta2 {`MargrabeOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlMargrabeOptionGamma1 as gamma1 {`MargrabeOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlMargrabeOptionGamma2 as gamma2 {`MargrabeOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlOneAssetOptionDeltaForward as deltaForward {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlOneAssetOptionElasticity as elasticity {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlOneAssetOptionStrikeSensitivity as strikeSensitivity {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlOneAssetOptionThetaPerDay as thetaPerDay {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlMargrabeOption as margrabeOption {`Int', `Int', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `MargrabeOption'#}

{#fun qlMultiAssetOption as multiAssetOption {withEnumObject* `Payoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `MultiAssetOption'#}

{#fun qlOneAssetOptionItmCashProbability as itmCashProbability {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlOneAssetOption as oneAssetOption {withEnumObject* `Payoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlQuantoBarrierOption as quantoBarrierOption {`BarrierType', `Double', `Double', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `QuantoBarrierOption'#}

dividendBarrierOption :: BarrierType -> Double -> Double -> StrikedPayoff -> Exercise -> [(Day, Double)] -> IO BarrierOption
dividendBarrierOption bt d1 d2 p e dv = uncurry (qlDividendBarrierOption bt d1 d2 p e) (unzip dv)
{#fun qlDividendBarrierOption {`BarrierType', `Double', `Double', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, preErrorCheck- `String' errorCheck*-} -> `BarrierOption'#}

{#fun qlBasketOption as basketOption {withEnumObject* `BasketPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `MultiAssetOption'#}

{#fun qlHimalayaOption as himalayaOption {withDayArray* `[Day]'&, `Double', preErrorCheck- `String' errorCheck*-} -> `MultiAssetOption'#}

{#fun qlPagodaOption as pagodaOption {withDayArray* `[Day]'&, `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `MultiAssetOption'#}

{#fun qlSpreadOption as spreadOption {withEnumObject* `PlainVanillaPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `MultiAssetOption'#}

{#fun qlCliquetOption as cliquetOption {withEnumObject* `PercentageStrikePayoff', withEnumObject* `EuropeanExercise', withDayArray* `[Day]'&, preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlContinuousAveragingAsianOption as continuousAveragingAsianOption {`AverageType', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlContinuousFixedLookbackOption as continuousFixedLookbackOption {`Double', withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlContinuousFloatingLookbackOption as continuousFloatingLookbackOption {`Double', withEnumObject* `TypePayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlDiscreteAveragingAsianOption as discreteAveragingAsianOption {`AverageType', `Double', fromIntegral `Word', withDayArray* `[Day]'&, withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlVanillaStorageOption as vanillaStorageOption {withEnumObject* `BermudanExercise', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlVanillaSwingOption as vanillaSwingOption {withEnumObject* `StrikedPayoff', withEnumObject* `SwingExercise', fromIntegral `Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `OneAssetOption'#}

{#fun qlEuropeanOption as europeanOption {withEnumObject* `StrikedPayoff', withEnumObject* `Exercise', preErrorCheck- `String' errorCheck*-} -> `VanillaOption'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
