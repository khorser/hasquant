{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Instrument.Option
  (
    Option
  , asOption
  , asOneAssetOption
  , CdsOption
  , BarrierOption
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
  , basketOption
  , himalayaOption
  , pagodaOption
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
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal
{#import QuantLib.Instrument#}(AverageType, BarrierType)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum

{#pointer *QlOption as Option foreign -> COption' nocode#}
{#pointer *QlCdsOption as CdsOption foreign -> CCdsOption' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}
{#pointer *QlBarrierOption as BarrierOption foreign -> CBarrierOption' nocode#}
{#pointer *QlForwardVanillaOption as ForwardVanillaOption foreign -> CForwardVanillaOption' nocode#}
{#pointer *QlMargrabeOption as MargrabeOption foreign -> CMargrabeOption' nocode#}
{#pointer *QlMultiAssetOption as MultiAssetOption foreign -> CMultiAssetOption' nocode#}
{#pointer *QlOneAssetOption as OneAssetOption foreign -> COneAssetOption' nocode#}
{#pointer *QlQuantoBarrierOption as QuantoBarrierOption foreign -> CQuantoBarrierOption' nocode#}
{#pointer *QlQuantoForwardVanillaOption as QuantoForwardVanillaOption foreign -> CQuantoForwardVanillaOption' nocode#}
{#pointer *QlQuantoVanillaOption as QuantoVanillaOption foreign -> CQuantoVanillaOption' nocode#}
{#pointer *QlVanillaOption as VanillaOption foreign -> CVanillaOption' nocode#}
{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
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

{#fun qlQuantoForwardVanillaOption as quantoForwardVanillaOption{`Double' -- ^moneyness
  ,withDay*`Day' -- ^resetDate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`QuantoForwardVanillaOption'peekQuantoForwardVanillaOption*#}
{#fun qlQuantoVanillaOption as quantoVanillaOption{withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`QuantoVanillaOption'peekQuantoVanillaOption*#}
{#fun qlVanillaOption as vanillaOption{withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`VanillaOption'peekVanillaOption*#}
{#fun qlBarrierOption as barrierOption{`BarrierType',`Double' -- ^barrier
  ,`Double' -- ^rebate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`BarrierOption'peekBarrierOption*#}
{#fun qlForwardVanillaOption as forwardVanillaOption{`Double' -- ^moneyness
  ,withDay*`Day' -- ^resetDate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`ForwardVanillaOption'peekForwardVanillaOption*#}
{#fun qlMargrabeOptionDelta1 as delta1{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMargrabeOptionDelta2 as delta2{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMargrabeOptionGamma1 as gamma1{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMargrabeOptionGamma2 as gamma2{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionDeltaForward as deltaForward{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionElasticity as elasticity{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionStrikeSensitivity as strikeSensitivity{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionThetaPerDay as thetaPerDay{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMargrabeOption as margrabeOption{`Int' -- ^Q1
  ,`Int' -- ^Q2
  ,withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`MargrabeOption'peekMargrabeOption*#}
{#fun qlMultiAssetOption as multiAssetOption{withPayoff*`Payoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}
{#fun qlOneAssetOptionItmCashProbability as itmCashProbability{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOption as oneAssetOption{withPayoff*`Payoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlQuantoBarrierOption as quantoBarrierOption{`BarrierType'
  ,`Double' -- ^barrier
  ,`Double' -- ^rebate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`QuantoBarrierOption'peekQuantoBarrierOption*#}
{#fun qlBasketOption as basketOption{withBasketPayoff*`BasketPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}
{#fun qlHimalayaOption as himalayaOption{withDayArray*`[Day]'& -- ^fixingDates
  , `Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}
{#fun qlPagodaOption as pagodaOption{withDayArray*`[Day]'& -- ^fixingDates
  ,`Double' -- ^roof
  ,`Double' -- ^fraction
  ,preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}
{#fun qlCliquetOption as cliquetOption{withPercentageStrikePayoff*`PercentageStrikePayoff',withEuropeanExercise*`EuropeanExercise' -- ^maturity
  ,withDayArray*`[Day]'& -- ^resetDates
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlContinuousAveragingAsianOption as continuousAveragingAsianOption{`AverageType',withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlContinuousFixedLookbackOption as continuousFixedLookbackOption{`Double' -- ^currentMinmax
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlContinuousFloatingLookbackOption as continuousFloatingLookbackOption{`Double' -- ^currentMinmax
  ,withTypePayoff*`TypePayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlDiscreteAveragingAsianOption as discreteAveragingAsianOption{`AverageType',`Double' -- ^runningAccumulator, the running sum or products of past fixings
  ,fromIntegral`Word' -- ^pastFixings
  ,withDayArray*`[Day]'& -- ^fixingDates
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlVanillaStorageOption as vanillaStorageOption{withBermudanExercise*`BermudanExercise',`Double' -- capacity
  ,`Double' -- ^load
  ,`Double' -- ^changeRate
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlVanillaSwingOption as vanillaSwingOption{withStrikedPayoff*`StrikedPayoff',withSwingExercise*`SwingExercise',fromIntegral`Word' -- ^minExerciseRights
  ,fromIntegral`Word' -- ^maxExerciseRights
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}
{#fun qlEuropeanOption as europeanOption{withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`VanillaOption'peekVanillaOption*#}

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

{#fun qlMultiAssetOptionDelta{withMultiAssetOption*`GenMultiAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMultiAssetOptionDividendRho{withMultiAssetOption*`GenMultiAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMultiAssetOptionGamma{withMultiAssetOption*`GenMultiAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMultiAssetOptionRho{withMultiAssetOption*`GenMultiAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMultiAssetOptionTheta{withMultiAssetOption*`GenMultiAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlMultiAssetOptionVega{withMultiAssetOption*`GenMultiAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlOneAssetOptionDelta{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionDividendRho{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionGamma{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionRho{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionTheta{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlOneAssetOptionVega{withOneAssetOption*`GenOneAssetOption a',preErrorCheck-`String'errorCheck*-}->`Double'#}

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
-- /Warning/ currently, this method returns the Black-Scholes implied volatility using analytic formulas for European options and a finite-difference method for American and Bermudan options. It will give unconsistent results if the pricing was performed with any other methods (such as jump-diffusion models.)Warningoptions with a gamma that changes sign (e.g., binary options) have values that are not monotonic in the volatility. In these cases, the calculation can fail and the result (if any) is almost meaningless. Another possible source of failure is to have a target value that is not attainable with any volatility, e.g., a target value lower than the intrinsic value in the case of American options.
  impliedVolatility :: a
    -> Double -- ^price
    -> GeneralizedBlackScholesProcess -- ^process
    -> Double -- ^accuracy
    -> Word -- ^maxEvaluations
    -> Double -- ^minVol
    -> Double -- ^maxVol
    -> IO Double
instance VolatileOption VanillaOption where
  impliedVolatility = qlVanillaOptionImpliedVolatility
instance VolatileOption BarrierOption where
  impliedVolatility = qlBarrierOptionImpliedVolatility

{#fun qlQuantoBarrierOptionQrho{withQuantoBarrierOption*`QuantoBarrierOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlQuantoBarrierOptionQvega{withQuantoBarrierOption*`QuantoBarrierOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlQuantoBarrierOptionQlambda{withQuantoBarrierOption*`QuantoBarrierOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlQuantoForwardVanillaOptionQrho{withQuantoForwardVanillaOption*`QuantoForwardVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlQuantoForwardVanillaOptionQvega{withQuantoForwardVanillaOption*`QuantoForwardVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlQuantoForwardVanillaOptionQlambda{withQuantoForwardVanillaOption*`QuantoForwardVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlQuantoVanillaOptionQrho{withQuantoVanillaOption*`QuantoVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlQuantoVanillaOptionQvega{withQuantoVanillaOption*`QuantoVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlQuantoVanillaOptionQlambda{withQuantoVanillaOption*`QuantoVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlVanillaOptionImpliedVolatility{withVanillaOption*`VanillaOption',`Double' -- ^price
  ,withGeneralizedBlackScholesProcess*`GenGeneralizedBlackScholesProcess p',`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBarrierOptionImpliedVolatility{withBarrierOption*`BarrierOption',`Double' -- ^price
  ,withGeneralizedBlackScholesProcess*`GenGeneralizedBlackScholesProcess p',`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
