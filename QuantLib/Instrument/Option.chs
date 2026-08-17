{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Instrument.Option
  (
    Option
  , asOption
  , asOneAssetOption
  , CdsOption
  , BarrierOption
  , DoubleBarrierOption
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

  , strikedPayoff
  , plainVanillaPayoff
  , percentageStrikePayoff
  , swingExercise

  , barrierOption
  , partialTimeBarrierOption
  , doubleBarrierOption
  , doubleBarrierOptionImpliedVolatility
  , forwardVanillaOption
  , compoundOption
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

  , HasImpliedVol(..)
  , HasQuanto(..)
  , HasGreeks(..)
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal
{#import QuantLib.Instrument#}(AverageType, BarrierType, DoubleBarrierType, PartialBarrierRange)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum

{#pointer *QlOption as Option foreign -> COption' nocode#}
{#pointer *QlCdsOption as CdsOption foreign -> CCdsOption' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}
{#pointer *QlBarrierOption as BarrierOption foreign -> CBarrierOption' nocode#}
{#pointer *QlDoubleBarrierOption as DoubleBarrierOption foreign -> CDoubleBarrierOption' nocode#}
{#pointer *QlMargrabeOption as MargrabeOption foreign -> CMargrabeOption' nocode#}
{#pointer *QlMultiAssetOption as MultiAssetOption foreign -> CMultiAssetOption' nocode#}
{#pointer *QlOneAssetOption as OneAssetOption foreign -> COneAssetOption' nocode#}
{#pointer *QlQuantoBarrierOption as QuantoBarrierOption foreign -> CQuantoBarrierOption' nocode#}
{#pointer *QlQuantoForwardVanillaOption as QuantoForwardVanillaOption foreign -> CQuantoForwardVanillaOption' nocode#}
{#pointer *QlQuantoVanillaOption as QuantoVanillaOption foreign -> CQuantoVanillaOption' nocode#}
{#pointer *QlVanillaOption as VanillaOption foreign -> CVanillaOption' nocode#}
{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
{#pointer *QlDividend as Dividend foreign -> CDividend nocode#}
{#pointer *QlPayoff nocode#}
{#pointer *QlBasketPayoff nocode#}
{#pointer *QlTypePayoff nocode#}
{#pointer *QlStrikedTypePayoff nocode#}
{#pointer *QlPercentageStrikePayoff nocode#}
{#pointer *QlPlainVanillaPayoff nocode#}
{#pointer *QlExercise nocode#}
{#pointer *QlEuropeanExercise nocode#}
{#pointer *QlSwingExercise nocode#}
{#pointer *QlBermudanExercise nocode#}

-- |Quanto version of a forward-starting (strike-resetting) vanilla option.
{#fun qlQuantoForwardVanillaOption as quantoForwardVanillaOption{`Double' -- ^moneyness
  ,withDay*`Day' -- ^resetDate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`QuantoForwardVanillaOption'peekQuantoForwardVanillaOption*#}

-- |Quanto version of a vanilla option on a single asset.
{#fun qlQuantoVanillaOption as quantoVanillaOption{withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`QuantoVanillaOption'peekQuantoVanillaOption*#}

-- |Vanilla option (no discrete dividends, no barriers) on a single asset.
{#fun qlVanillaOption as vanillaOption{withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`VanillaOption'peekVanillaOption*#}

-- |Barrier option on a single asset.
{#fun qlBarrierOption as barrierOption{`BarrierType',`Double' -- ^barrier
  ,`Double' -- ^rebate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`BarrierOption'peekBarrierOption*#}

-- |Barrier option on a single asset that is only monitored for part of its life (a partial-time barrier).
{#fun qlPartialTimeBarrierOption as partialTimeBarrierOption{`BarrierType',`PartialBarrierRange'
  ,`Double' -- ^barrier
  ,`Double' -- ^rebate
  ,withDay*`Day' -- ^coverEventDate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Double-barrier option on a single asset, with a lower and an upper barrier.
{#fun qlDoubleBarrierOption as doubleBarrierOption{`DoubleBarrierType',`Double' -- ^barrierLo
  ,`Double' -- ^barrierHi
  ,`Double' -- ^rebate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`DoubleBarrierOption'peekDoubleBarrierOption*#}

-- |Forward-starting (strike-resetting) version of a vanilla option.
{#fun qlForwardVanillaOption as forwardVanillaOption{`Double' -- ^moneyness
  ,withDay*`Day' -- ^resetDate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Compound option (an option on another option) on a single asset. The mother option is the compound option itself; the daughter option is its underlying.
{#fun qlCompoundOption as compoundOption{withStrikedPayoff*`StrikedPayoff' -- ^motherPayoff
  ,withExercise*`Exercise' -- ^motherExercise
  ,withStrikedPayoff*`StrikedPayoff' -- ^daughterPayoff
  ,withExercise*`Exercise' -- ^daughterExercise
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Sensitivity of a MargrabeOption's value to the price of the first asset.
{#fun qlMargrabeOptionDelta1 as delta1{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a MargrabeOption's value to the price of the second asset.
{#fun qlMargrabeOptionDelta2 as delta2{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second derivative of a MargrabeOption's value with respect to the price of the first asset.
{#fun qlMargrabeOptionGamma1 as gamma1{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second derivative of a MargrabeOption's value with respect to the price of the second asset.
{#fun qlMargrabeOptionGamma2 as gamma2{withMargrabeOption*`MargrabeOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of the option's value to the forward price of the underlying.
{#fun qlOneAssetOptionDeltaForward as deltaForward{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Percentage change in the option's value per percentage change in the underlying price.
{#fun qlOneAssetOptionElasticity as elasticity{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of the option's value to the strike price.
{#fun qlOneAssetOptionStrikeSensitivity as strikeSensitivity{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Theta divided by the number of days elapsed per day (as opposed to per year).
{#fun qlOneAssetOptionThetaPerDay as thetaPerDay{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Margrabe option on two assets: the right to exchange Q2 units of the second asset for Q1 units of the first at expiration.
{#fun qlMargrabeOption as margrabeOption{`Int' -- ^Q1
  ,`Int' -- ^Q2
  ,withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`MargrabeOption'peekMargrabeOption*#}

-- |Base construction for an option on multiple assets.
{#fun qlMultiAssetOption as multiAssetOption{withPayoff*`Payoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}

-- |Probability of the option expiring in-the-money in a cash-or-nothing sense.
{#fun qlOneAssetOptionItmCashProbability as itmCashProbability{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Base construction for an option on a single asset.
{#fun qlOneAssetOption as oneAssetOption{withPayoff*`Payoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Quanto version of a barrier option on a single asset.
{#fun qlQuantoBarrierOption as quantoBarrierOption{`BarrierType'
  ,`Double' -- ^barrier
  ,`Double' -- ^rebate
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`QuantoBarrierOption'peekQuantoBarrierOption*#}

-- |Basket option on a number of assets, combined by the given basket payoff (e.g. min/max/spread/average).
{#fun qlBasketOption as basketOption{withBasketPayoff*`BasketPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}

-- |Himalaya option: at the end of each of a series of periods, the best-performing asset in the basket is added to the average and dropped from the basket; the payoff is the max of the strike and the final average of best performers.
{#fun qlHimalayaOption as himalayaOption{withDayArray*`[Day]'& -- ^fixingDates
  , `Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}

-- |Roofed Asian option on a number of assets: pays the given fraction of the minimum of the roof and the positive portfolio performance, or nothing if the performance is negative.
{#fun qlPagodaOption as pagodaOption{withDayArray*`[Day]'& -- ^fixingDates
  ,`Double' -- ^roof
  ,`Double' -- ^fraction
  ,preErrorCheck-`String'errorCheck*-}->`MultiAssetOption'peekMultiAssetOption*#}

-- |Cliquet (ratchet) option: a series of forward-starting options where each period's strike is set to a fixed percentage of the spot price at the start of that period.
{#fun qlCliquetOption as cliquetOption{withPercentageStrikePayoff*`PercentageStrikePayoff',withEuropeanExercise*`EuropeanExercise' -- ^maturity
  ,withDayArray*`[Day]'& -- ^resetDates
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Continuous-averaging Asian option on a single asset, for an unseasoned (fresh) option where averaging has not yet started.
{#fun qlContinuousAveragingAsianOption as continuousAveragingAsianOption{`AverageType',withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Continuous-fixed lookback option: the payoff uses the fixed strike against the minimum/maximum price observed over the option's life.
{#fun qlContinuousFixedLookbackOption as continuousFixedLookbackOption{`Double' -- ^currentMinmax
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Continuous-floating lookback option: the strike is set to the minimum/maximum price observed over the option's life.
{#fun qlContinuousFloatingLookbackOption as continuousFloatingLookbackOption{`Double' -- ^currentMinmax
  ,withTypePayoff*`TypePayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Discrete-averaging Asian option on a single asset, taking the running sum/product of past fixings plus a list of future fixing dates.
{#fun qlDiscreteAveragingAsianOption as discreteAveragingAsianOption{`AverageType',`Double' -- ^runningAccumulator, the running sum or products of past fixings
  ,fromIntegral`Word' -- ^pastFixings
  ,withDayArray*`[Day]'& -- ^fixingDates
  ,withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Storage option (e.g. a gas storage facility): a payoff-free instrument exercisable on a Bermudan schedule, with a maximum capacity, load/withdrawal rate, and per-period rate of change.
{#fun qlVanillaStorageOption as vanillaStorageOption{withBermudanExercise*`BermudanExercise',`Double' -- capacity
  ,`Double' -- ^load
  ,`Double' -- ^changeRate
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |Swing option: a payoff exercisable a bounded number of times (between minExerciseRights and maxExerciseRights) at the dates of a SwingExercise.
{#fun qlVanillaSwingOption as vanillaSwingOption{withStrikedPayoff*`StrikedPayoff',withSwingExercise*`SwingExercise',fromIntegral`Word' -- ^minExerciseRights
  ,fromIntegral`Word' -- ^maxExerciseRights
  ,preErrorCheck-`String'errorCheck*-}->`OneAssetOption'peekOneAssetOption*#}

-- |European (single-exercise-date) vanilla option on a single asset.
{#fun qlEuropeanOption as europeanOption{withStrikedPayoff*`StrikedPayoff',withExercise*`Exercise',preErrorCheck-`String'errorCheck*-}->`VanillaOption'peekVanillaOption*#}

class HasGreeks a where
  delta :: a -> IO Double
  gamma :: a -> IO Double
  rho :: a -> IO Double
  theta :: a -> IO Double
  vega :: a -> IO Double
  dividendRho :: a -> IO Double

instance HasGreeks MultiAssetOption where
  delta = qlMultiAssetOptionDelta
  gamma = qlMultiAssetOptionGamma
  rho = qlMultiAssetOptionRho
  theta = qlMultiAssetOptionTheta
  vega = qlMultiAssetOptionVega
  dividendRho = qlMultiAssetOptionDividendRho

instance HasGreeks OneAssetOption where
  delta = qlOneAssetOptionDelta
  gamma = qlOneAssetOptionGamma
  rho = qlOneAssetOptionRho
  theta = qlOneAssetOptionTheta
  vega = qlOneAssetOptionVega
  dividendRho = qlOneAssetOptionDividendRho

-- |Sensitivity of a multi-asset option's value to the price of its underlying assets.
{#fun qlMultiAssetOptionDelta{withMultiAssetOption*`GenMultiAssetOption mo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a multi-asset option's value to the dividend yield of its underlying assets.
{#fun qlMultiAssetOptionDividendRho{withMultiAssetOption*`GenMultiAssetOption mo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second derivative of a multi-asset option's value with respect to the price of its underlying assets.
{#fun qlMultiAssetOptionGamma{withMultiAssetOption*`GenMultiAssetOption mo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a multi-asset option's value to the risk-free interest rate.
{#fun qlMultiAssetOptionRho{withMultiAssetOption*`GenMultiAssetOption mo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a multi-asset option's value to the passage of time.
{#fun qlMultiAssetOptionTheta{withMultiAssetOption*`GenMultiAssetOption mo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a multi-asset option's value to the volatility of its underlying assets.
{#fun qlMultiAssetOptionVega{withMultiAssetOption*`GenMultiAssetOption mo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a single-asset option's value to the price of its underlying.
{#fun qlOneAssetOptionDelta{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a single-asset option's value to the dividend yield of its underlying.
{#fun qlOneAssetOptionDividendRho{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second derivative of a single-asset option's value with respect to the price of its underlying.
{#fun qlOneAssetOptionGamma{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a single-asset option's value to the risk-free interest rate.
{#fun qlOneAssetOptionRho{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a single-asset option's value to the passage of time.
{#fun qlOneAssetOptionTheta{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a single-asset option's value to the volatility of its underlying.
{#fun qlOneAssetOptionVega{withOneAssetOption*`GenOneAssetOption oo',preErrorCheck-`String'errorCheck*-}->`Double'#}

class HasQuanto a where
  qrho :: a -> IO Double
  qvega :: a -> IO Double
  qlambda :: a -> IO Double
instance HasQuanto QuantoBarrierOption where
  qrho = qlQuantoBarrierOptionQrho
  qvega = qlQuantoBarrierOptionQvega
  qlambda = qlQuantoBarrierOptionQlambda
instance HasQuanto QuantoForwardVanillaOption where
  qrho = qlQuantoForwardVanillaOptionQrho
  qvega = qlQuantoForwardVanillaOptionQvega
  qlambda = qlQuantoForwardVanillaOptionQlambda
instance HasQuanto QuantoVanillaOption where
  qrho = qlQuantoVanillaOptionQrho
  qvega = qlQuantoVanillaOptionQvega
  qlambda = qlQuantoVanillaOptionQlambda

class HasImpliedVol a where
-- /Warning/ currently, this method returns the Black-Scholes implied volatility using analytic formulas for European options and a finite-difference method for American and Bermudan options. It will give unconsistent results if the pricing was performed with any other methods (such as jump-diffusion models.)Warningoptions with a gamma that changes sign (e.g., binary options) have values that are not monotonic in the volatility. In these cases, the calculation can fail and the result (if any) is almost meaningless. Another possible source of failure is to have a target value that is not attainable with any volatility, e.g., a target value lower than the intrinsic value in the case of American options.
  impliedVolatility :: a
    -> Double -- ^price
    -> GeneralizedBlackScholesProcess -- ^process
    -> [Dividend] -- ^dividends
    -> Double -- ^accuracy
    -> Word -- ^maxEvaluations
    -> Double -- ^minVol
    -> Double -- ^maxVol
    -> IO Double
instance HasImpliedVol VanillaOption where
  impliedVolatility = qlVanillaOptionImpliedVolatility
instance HasImpliedVol BarrierOption where
  impliedVolatility = qlBarrierOptionImpliedVolatility

-- |Sensitivity of a QuantoBarrierOption's value to the correlation-driven quanto adjustment's foreign rate.
{#fun qlQuantoBarrierOptionQrho{withQuantoBarrierOption*`QuantoBarrierOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoBarrierOption's value to the exchange-rate volatility.
{#fun qlQuantoBarrierOptionQvega{withQuantoBarrierOption*`QuantoBarrierOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoBarrierOption's value to the correlation between the underlying and the exchange rate.
{#fun qlQuantoBarrierOptionQlambda{withQuantoBarrierOption*`QuantoBarrierOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoForwardVanillaOption's value to the correlation-driven quanto adjustment's foreign rate.
{#fun qlQuantoForwardVanillaOptionQrho{withQuantoForwardVanillaOption*`QuantoForwardVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoForwardVanillaOption's value to the exchange-rate volatility.
{#fun qlQuantoForwardVanillaOptionQvega{withQuantoForwardVanillaOption*`QuantoForwardVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoForwardVanillaOption's value to the correlation between the underlying and the exchange rate.
{#fun qlQuantoForwardVanillaOptionQlambda{withQuantoForwardVanillaOption*`QuantoForwardVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoVanillaOption's value to the correlation-driven quanto adjustment's foreign rate.
{#fun qlQuantoVanillaOptionQrho{withQuantoVanillaOption*`QuantoVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoVanillaOption's value to the exchange-rate volatility.
{#fun qlQuantoVanillaOptionQvega{withQuantoVanillaOption*`QuantoVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of a QuantoVanillaOption's value to the correlation between the underlying and the exchange rate.
{#fun qlQuantoVanillaOptionQlambda{withQuantoVanillaOption*`QuantoVanillaOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Implied Black-Scholes volatility that reproduces the given price for a VanillaOption, computed analytically for European exercise and by finite differences for American/Bermudan; may be unreliable for a gamma that changes sign or a price unattainable at any volatility.
{#fun qlVanillaOptionImpliedVolatility{withVanillaOption*`VanillaOption',`Double' -- ^price
  ,withGeneralizedBlackScholesProcess*`GenGeneralizedBlackScholesProcess gbs'
  ,withDividendArray*`[Dividend]'& -- ^dividends
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Implied Black-Scholes volatility that reproduces the given price for a BarrierOption; see VanillaOption's implied-volatility for the caveats on reliability.
{#fun qlBarrierOptionImpliedVolatility{withBarrierOption*`BarrierOption',`Double' -- ^price
  ,withGeneralizedBlackScholesProcess*`GenGeneralizedBlackScholesProcess gbs'
  ,withDividendArray*`[Dividend]'& -- ^dividends
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Implied Black-Scholes volatility that reproduces the given price for a DoubleBarrierOption; see VanillaOption's implied-volatility for the caveats on reliability.
{#fun qlDoubleBarrierOptionImpliedVolatility as doubleBarrierOptionImpliedVolatility{withDoubleBarrierOption*`DoubleBarrierOption',`Double' -- ^price
  ,withGeneralizedBlackScholesProcess*`GenGeneralizedBlackScholesProcess gbs'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
