{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts #-}
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

  , VolatileOption(..)
  , QuantoOption(..)
  , OptionOnAsset(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Type
import QuantLib.Internal
import Control.Monad((>=>))
{#import QuantLib.Instrument#}
import QuantLib.Internal.Enum
{#import QuantLib.Process#}(GeneralizedBlackScholesProcess)

{#pointer *QlOption as Option foreign finalizer qlFreeOption newtype#}
instance ForeignObject Option where
  withObject = withOption
  constructor = Option
  finalizer = qlFreeOption
instance Derives Option Instrument where cast = qlOptionAsInstrument
{#fun qlOptionAsInstrument {`Option'} -> `Instrument' peekObject*#}

asOption :: (Derives a Option) => a -> IO Option
asOption = cast

{#pointer *QlCdsOption as CdsOption foreign finalizer qlFreeCdsOption newtype#}
instance ForeignObject CdsOption where
  withObject = withCdsOption
  constructor = CdsOption
  finalizer = qlFreeCdsOption
instance Derives CdsOption Option where cast = qlCdsOptionAsOption
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
instance Derives MultiAssetOption Option where cast = qlMultiAssetOptionAsOption

{#pointer *QlOneAssetOption as OneAssetOption foreign finalizer qlFreeOneAssetOption newtype#}
instance ForeignObject OneAssetOption where
  withObject = withOneAssetOption
  constructor = OneAssetOption
  finalizer = qlFreeOneAssetOption
{#fun qlOneAssetOptionAsOption {`OneAssetOption'} -> `Option'#}
instance Derives OneAssetOption Option where cast = qlOneAssetOptionAsOption

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
instance Derives BarrierOption Option where cast = qlBarrierOptionAsOneAssetOption >=> asOption

{#fun qlDividendVanillaOptionAsOneAssetOption {`DividendVanillaOption'} -> `OneAssetOption'#}
instance Derives DividendVanillaOption Option where cast = qlDividendVanillaOptionAsOneAssetOption >=> asOption

{#fun qlForwardVanillaOptionAsOneAssetOption {`ForwardVanillaOption'} -> `OneAssetOption'#}
instance Derives ForwardVanillaOption Option where cast = qlForwardVanillaOptionAsOneAssetOption >=> asOption

{#fun qlQuantoVanillaOptionAsOneAssetOption {`QuantoVanillaOption'} -> `OneAssetOption'#}
instance Derives QuantoVanillaOption Option where cast = qlQuantoVanillaOptionAsOneAssetOption >=> asOption

{#fun qlVanillaOptionAsOneAssetOption {`VanillaOption'} -> `OneAssetOption'#}
instance Derives VanillaOption Option where cast = qlVanillaOptionAsOneAssetOption >=> asOption

{#fun qlQuantoBarrierOptionAsBarrierOption {`QuantoBarrierOption'} -> `BarrierOption'#}
instance Derives QuantoBarrierOption Option where cast = qlQuantoBarrierOptionAsBarrierOption >=> asOption

{#fun qlMargrabeOptionAsMultiAssetOption {`MargrabeOption'} -> `MultiAssetOption'#}
instance Derives MargrabeOption Option where cast = qlMargrabeOptionAsMultiAssetOption >=> asOption

{#fun qlQuantoForwardVanillaOptionAsForwardVanillaOption {`QuantoForwardVanillaOption'} -> `ForwardVanillaOption'#}
instance Derives QuantoForwardVanillaOption Option where cast = qlQuantoForwardVanillaOptionAsForwardVanillaOption >=> asOption

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

class OptionOnAsset a where
  delta :: a -> IO Double
  gamma :: a -> IO Double
  rho :: a -> IO Double
  theta :: a -> IO Double
  vega :: a -> IO Double
  dividendRho :: a -> IO Double


instance OptionOnAsset MultiAssetOption where
  delta = qlMultiAssetOptionDelta
  gamma = qlMultiAssetOptionGamma
  rho = qlMultiAssetOptionRho
  theta = qlMultiAssetOptionTheta
  vega = qlMultiAssetOptionVega
  dividendRho = qlMultiAssetOptionDividendRho

instance OptionOnAsset OneAssetOption where
  delta = qlOneAssetOptionDelta
  gamma = qlOneAssetOptionGamma
  rho = qlOneAssetOptionRho
  theta = qlOneAssetOptionTheta
  vega = qlOneAssetOptionVega
  dividendRho = qlOneAssetOptionDividendRho

{#fun qlMultiAssetOptionDelta {`MultiAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlMultiAssetOptionDividendRho {`MultiAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlMultiAssetOptionGamma {`MultiAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlMultiAssetOptionRho {`MultiAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlMultiAssetOptionTheta {`MultiAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlMultiAssetOptionVega {`MultiAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlOneAssetOptionDelta {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlOneAssetOptionDividendRho {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlOneAssetOptionGamma {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlOneAssetOptionRho {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlOneAssetOptionTheta {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlOneAssetOptionVega {`OneAssetOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

class QuantoOption a where
  qrho :: a -> IO Double
  qvega :: a -> IO Double
  qlambda :: a -> IO Double

instance QuantoOption QuantoBarrierOption where
  qrho = qlQuantoBarrierOptionQrho
  qvega = qlQuantoBarrierOptionQvega
  qlambda = qlQuantoBarrierOptionQlambda

instance QuantoOption QuantoForwardVanillaOption where
  qrho = qlQuantoForwardVanillaOptionQrho
  qvega = qlQuantoForwardVanillaOptionQvega
  qlambda = qlQuantoForwardVanillaOptionQlambda

instance QuantoOption QuantoVanillaOption where
  qrho = qlQuantoVanillaOptionQrho
  qvega = qlQuantoVanillaOptionQvega
  qlambda = qlQuantoVanillaOptionQlambda

class VolatileOption a where
-- |/Warning/ currently, this method returns the Black-Scholes implied volatility using analytic formulas for European options and a finite-difference method for American and Bermudan options. It will give unconsistent results if the pricing was performed with any other methods (such as jump-diffusion models.)Warningoptions with a gamma that changes sign (e.g., binary options) have values that are not monotonic in the volatility. In these cases, the calculation can fail and the result (if any) is almost meaningless. Another possible source of failure is to have a target value that is not attainable with any volatility, e.g., a target value lower than the intrinsic value in the case of American options.
  impliedVolatility :: a 
    -> Double -- ^price
    -> GeneralizedBlackScholesProcess -- ^process
    -> Double -- ^accuracy
    -> Word -- ^maxEvaluations
    -> Double -- ^minVol
    -> Double -- ^maxVol
    -> IO Double

instance VolatileOption DividendVanillaOption where
  impliedVolatility = qlDividendVanillaOptionImpliedVolatility

instance VolatileOption VanillaOption where
  impliedVolatility = qlVanillaOptionImpliedVolatility

instance VolatileOption BarrierOption where
  impliedVolatility = qlBarrierOptionImpliedVolatility

{#fun qlQuantoBarrierOptionQrho {`QuantoBarrierOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlQuantoBarrierOptionQvega {`QuantoBarrierOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlQuantoBarrierOptionQlambda {`QuantoBarrierOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlQuantoForwardVanillaOptionQrho {`QuantoForwardVanillaOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlQuantoForwardVanillaOptionQvega {`QuantoForwardVanillaOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlQuantoForwardVanillaOptionQlambda {`QuantoForwardVanillaOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlQuantoVanillaOptionQrho {`QuantoVanillaOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlQuantoVanillaOptionQvega {`QuantoVanillaOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlQuantoVanillaOptionQlambda {`QuantoVanillaOption', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlDividendVanillaOptionImpliedVolatility {`DividendVanillaOption', `Double', withObject* `GeneralizedBlackScholesProcess', `Double', fromIntegral `Word', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlVanillaOptionImpliedVolatility {`VanillaOption', `Double', withObject* `GeneralizedBlackScholesProcess', `Double', fromIntegral `Word', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}
{#fun qlBarrierOptionImpliedVolatility {`BarrierOption', `Double', withObject* `GeneralizedBlackScholesProcess', `Double', fromIntegral `Word', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
