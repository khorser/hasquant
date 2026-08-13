module QuantLib.Model
  (
    CalibrationErrorType(..)
  , GJRGARCHModel
  , HestonModel
  , GenHestonModel
  , BatesModel
  , GenBatesModel
  , PiecewiseTimeDependentHestonModel
  , ShortRateModel
  , GenShortRateModel
  , AffineModel(..)
  , Gaussian1dModel(..)
  , OneFactorAffineModel
  , GenOneFactorAffineModel
  , LiborForwardModel
  , HullWhite
  , Gsr
  , MarkovFunctional
  , CalibratedModel
  , GenCalibratedModel
  , G2
  , BatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , GenBatesDoubleExpModel
  , LmCorrelationModel(..)
  , LmVolatilityModel(..)
  , CalibrationHelper
  , BlackCalibrationHelper
  , GenCalibrationHelper
  , asCalibrationHelper

  , asCalibratedModel
  , asHestonModel
  , asShortRateModel
  , asOneFactorAffineModel
  , asBatesModel
  , asBatesDoubleExpModel

  , batesModel
  , blackKarasinski
  , coxIngersollRoss
  , extendedCoxIngersollRoss
  , g2
  , generalizedHullWhite
  , gJRGARCHModel
  , hestonModel
  , hullWhite
  , varianceGammaModel
  , vasicek
  , liborForwardModel
  , gsr
  , markovFunctional

  , calibrate
  , calibrateVolatilitiesIterative
  , capHelper
  , hestonModelHelper
  , swaptionHelper
  , times

  , discountBond
  , convexityBias
  , fixedReversion
  , gsrVolatility
  , markovFunctionalVolatility
  , params
  , value
  , blackPrice
  , calibrationError
  , impliedVolatility
  , marketValue
  , modelValue
  , setPricingEngine
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal
{#import QuantLib.Time.Schedule#}(Frequency)
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.CashFlow#}(RateAveragingType)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum

{#enum CalibrationErrorType{} deriving(Show, Eq)#}

{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *OptimizationMethod as QlOptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *EndCriteria as QlEndCriteria foreign -> CEndCriteria nocode#}
{#pointer *Constraint as QlConstraint foreign -> CConstraint nocode#}
{#pointer *QlLmCorrelationModel foreign -> CLmCorrelationModel nocode#}
{#pointer *QlLmVolatilityModel foreign -> CLmVolatilityModel nocode#}

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign -> CGJRGARCHModel' nocode#}
{#pointer *QlHestonModel as HestonModel foreign -> CHestonModel' nocode#}
{#pointer *QlBatesModel as BatesModel foreign -> CBatesModel' nocode#}
{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign -> CPiecewiseTimeDependentHestonModel' nocode#}
{#pointer *QlShortRateModel as ShortRateModel foreign -> CShortRateModel' nocode#}
{#pointer *QlOneFactorAffineModel as OneFactorAffineModel foreign -> COneFactorAffineModel' nocode#}
{#pointer *QlLiborForwardModel as LiborForwardModel foreign -> CLiborForwardModel' nocode#}
{#pointer *QlHullWhite as HullWhite foreign -> CHullWhite' nocode#}
{#pointer *QlCalibratedModel as CalibratedModel foreign -> CCalibratedModel' nocode#}
{#pointer *QlG2 as G2 foreign -> CG2' nocode#}
{#pointer *QlBatesDetJumpModel as BatesDetJumpModel foreign -> CBatesDetJumpModel' nocode#}
{#pointer *QlBatesDoubleExpDetJumpModel as BatesDoubleExpDetJumpModel foreign -> CBatesDoubleExpDetJumpModel' nocode#}
{#pointer *QlBatesDoubleExpModel as BatesDoubleExpModel foreign -> CBatesDoubleExpModel' nocode#}
{#pointer *QlGsr as Gsr foreign -> CGsr' nocode#}
{#pointer *QlMarkovFunctional as MarkovFunctional foreign -> CMarkovFunctional' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}

{#pointer *QlCalibrationHelper as CalibrationHelper foreign -> CCalibrationHelper' nocode#}
{#pointer *QlBlackCalibrationHelper as BlackCalibrationHelper foreign -> CBlackCalibrationHelper' nocode#}

{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign -> CStochasticProcess1D' nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess' nocode#}
{#pointer *QlBlackProcess as BlackProcess foreign -> CBlackProcess' nocode#}
{#pointer *QlExtOUWithJumpsProcess as ExtOUWithJumpsProcess foreign -> CExtOUWithJumpsProcess' nocode#}
{#pointer *QlExtendedOrnsteinUhlenbeckProcess as ExtendedOrnsteinUhlenbeckProcess foreign -> CExtendedOrnsteinUhlenbeckProcess' nocode#}
{#pointer *QlGJRGARCHProcess as GJRGARCHProcess foreign -> CGJRGARCHProcess' nocode#}
{#pointer *QlHestonProcess as HestonProcess foreign -> CHestonProcess' nocode#}
{#pointer *QlBatesProcess as BatesProcess foreign -> CBatesProcess' nocode#}
{#pointer *QlHybridHestonHullWhiteProcess as HybridHestonHullWhiteProcess foreign -> CHybridHestonHullWhiteProcess' nocode#}
{#pointer *QlKlugeExtOUProcess as KlugeExtOUProcess foreign -> CKlugeExtOUProcess' nocode#}
{#pointer *QlLiborForwardModelProcess as LiborForwardModelProcess foreign -> CLiborForwardModelProcess' nocode#}
{#pointer *QlStochasticProcessArray as StochasticProcessArray foreign -> CStochasticProcessArray' nocode#}
{#pointer *QlVarianceGammaProcess as VarianceGammaProcess foreign -> CVarianceGammaProcess' nocode#}
{#pointer *QlMerton76Process as Merton76Process foreign -> CMerton76Process' nocode#}
{#pointer *QlHullWhiteProcess as HullWhiteProcess foreign -> CHullWhiteProcess' nocode#}
{#pointer *QlHullWhiteForwardProcess as HullWhiteForwardProcess foreign -> CHullWhiteForwardProcess' nocode#}

{#fun qlBatesModel as batesModel{withBatesProcess*`BatesProcess',preErrorCheck-`String'errorCheck*-}->`BatesModel'peekBatesModel*#}
{#fun qlBlackKarasinski as blackKarasinski{withYieldTermStructure*`GenYieldTermStructure a',`Double' -- ^a
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`ShortRateModel'peekShortRateModel*#}
{#fun qlCoxIngersollRoss as coxIngersollRoss{`Double' -- ^r0
  ,`Double' -- ^theta
  ,`Double' -- ^k
  ,`Double' -- ^sigma
  ,`Bool' -- ^withFellerConstraint
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}
{#fun qlExtendedCoxIngersollRoss as extendedCoxIngersollRoss{withYieldTermStructure*`GenYieldTermStructure a',`Double' -- ^theta
  ,`Double' -- ^k
  ,`Double' -- ^sigma
  ,`Double' -- ^x0
  ,`Bool' -- ^withFellerConstraint
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}
-- |Price of a discount bond paying 1 at @maturity@, given the short rate @rate@ at time @now@.
{#fun pure qlOneFactorAffineModelDiscountBond as discountBond{withOneFactorAffineModel*`GenOneFactorAffineModel m',`Double' -- ^now
  ,`Double' -- ^maturity
  ,`Double' -- ^rate
  }->`Double'#}
{#fun qlG2 as g2{withYieldTermStructure*`GenYieldTermStructure a',`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^b
  ,`Double' -- ^eta
  ,`Double' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`G2'peekG2*#}
generalizedHullWhite :: GenYieldTermStructure a -> [(Day, Double)] -- ^speedstructure
  -> [(Day, Double)] -- ^volstructure
  -> IO ShortRateModel
generalizedHullWhite ts s v = qlGeneralizedHullWhite ts sd vd sq vq where {(sd, sq) = unzip s; (vd, vq) = unzip v}
{#fun qlGeneralizedHullWhite{withYieldTermStructure*`GenYieldTermStructure a',withDayArray*`[Day]'&,withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,preErrorCheck-`String'errorCheck*-}->`ShortRateModel'peekShortRateModel*#}
{#fun qlGJRGARCHModel as gJRGARCHModel{withGenStochasticProcess*`GJRGARCHProcess',preErrorCheck-`String'errorCheck*-}->`GJRGARCHModel'peekGJRGARCHModel*#}
{#fun qlHestonModel as hestonModel{withHestonProcess*`GenHestonProcess a',preErrorCheck-`String'errorCheck*-}->`HestonModel'peekHestonModel*#}
{#fun qlHullWhite as hullWhite{withYieldTermStructure*`GenYieldTermStructure a',`Double' -- ^a
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`HullWhite'peekHullWhite*#}
-- |Futures convexity bias (difference between futures implied rate and forward rate), per G. Kirikos, D. Novak, \"Convexity Conundrums\", Risk Magazine, March 1997. @t@/@T@ are in yearfraction using the deposit day counter, @futurePrice@ is the futures' market price.
{#fun pure qlHullWhiteConvexityBias as convexityBias{`Double' -- ^futurePrice
  ,`Double' -- ^t
  ,`Double' -- ^T
  ,`Double' -- ^sigma
  ,`Double' -- ^a
  }->`Double'#}
-- |Marks the reversion (@a@) fixed and volatility (@sigma@) free for 'calibrate''s @fixParameters@ argument. Mirrors @HullWhite::FixedReversion()@.
fixedReversion :: [Bool]
fixedReversion = [True, False]
{#fun qlGsr as gsr{withYieldTermStructure*`GenYieldTermStructure a',withDayArray*`[Day]'& -- ^volstepdates
  ,withDoubleArray*`[Double]'& -- ^volatilities
  ,`Double' -- ^reversion
  ,`Double' -- ^T
  ,preErrorCheck-`String'errorCheck*-}->`Gsr'peekGsr*#}
-- |Volatility step values, as calibrated so far.
{#fun qlGsrVolatility as gsrVolatility{withGenCalibratedModel*`Gsr',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |Iteratively calibrates the volatility step values, one at a time, to the given helpers (assumed to have step dates matching the model's volatility step dates).
{#fun qlGsrCalibrateVolatilitiesIterative as calibrateVolatilitiesIterative{withGenCalibratedModel*`Gsr',withBlackCalibrationHelperArray*`[BlackCalibrationHelper]'&,withOptimizationMethod*`OptimizationMethod',withEndCriteria*`EndCriteria'
  ,withMaybeConstraint*`Maybe Constraint'
  ,withDoubleArray*`[Double]'&
  ,preErrorCheck-`String'errorCheck*-}->`()'#}
markovFunctional :: GenYieldTermStructure a -> Double -- ^reversion
  -> [Day] -- ^volstepdates
  -> [Double] -- ^volatilities
  -> SwaptionVolatilityStructure
  -> [Day] -- ^swaptionExpiries
  -> [(Word, TimeUnit)] -- ^swaptionTenors
  -> GenSwapIndex s -- ^swapIndexBase
  -> Word -- ^yGridPoints
  -> IO MarkovFunctional
markovFunctional ts reversion vsd vs svol se tenors = qlMarkovFunctional ts reversion vsd vs svol se tq tu
  where (tq, tu) = unzip tenors
{#fun qlMarkovFunctional{withYieldTermStructure*`GenYieldTermStructure a',`Double'
  ,withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure b'
  ,withDayArray*`[Day]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withSwapIndex*`GenSwapIndex s'
  ,fromIntegral`Word'
  ,preErrorCheck-`String'errorCheck*-}->`MarkovFunctional'peekMarkovFunctional*#}
-- |Volatility step values, as calibrated so far.
{#fun qlMarkovFunctionalVolatility as markovFunctionalVolatility{withGenCalibratedModel*`MarkovFunctional',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlVarianceGammaModel as varianceGammaModel{withGenStochasticProcess1D*`VarianceGammaProcess',preErrorCheck-`String'errorCheck*-}->`CalibratedModel'peekCalibratedModel*#}
{#fun qlVasicek as vasicek{`Double' -- ^r0
  ,`Double' -- ^a
  ,`Double' -- ^b
  ,`Double' -- ^sigma
  ,`Double' -- ^lambda
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}

{#fun qlLiborForwardModel as liborForwardModel{withGenStochasticProcess*`LiborForwardModelProcess',withLmVolatilityModel*`LmVolatilityModel',withLmCorrelationModel*`LmCorrelationModel',preErrorCheck-`String'errorCheck*-}->`LiborForwardModel'peekLiborForwardModel*#}
-- |Calibrate to a set of market instruments (caps/swaptions)
-- An additional constraint can be passed which must be satisfied in addition to the constraints of the model.
calibrate :: GenCalibratedModel m -> [(GenCalibrationHelper a, Double)] -- ^(instrument, weight)
  -> OptimizationMethod -> EndCriteria -> Maybe Constraint
  -> [Bool] -- ^fixParameters, e.g. 'fixedReversion'; @[]@ leaves nothing fixed
  -> IO ()
calibrate m h o e c fp = qlCalibratedModelCalibrate m hh hw o e c fp where (hh, hw) = unzip h
{#fun qlCalibratedModelCalibrate{withCalibratedModel*`GenCalibratedModel m',withCalibrationHelperArray*`[GenCalibrationHelper a]'&,withDoubleArray*`[Double]'&
  ,withOptimizationMethod*`OptimizationMethod',withEndCriteria*`EndCriteria',withMaybeConstraint*`Maybe Constraint',withBoolArray*`[Bool]'&,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |Objective function value at @params@ for the given calibration instruments.
{#fun qlCalibratedModelValue as value{withCalibratedModel*`GenCalibratedModel m',withDoubleArray*`[Double]'&,withCalibrationHelperArray*`[GenCalibrationHelper a]'&,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCapHelper as capHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote a' -- ^volatility
  ,withIborIndex*`GenIborIndex b',`Frequency' -- ^fixedLegFrequency
  ,withDayCounter*`DayCounter',`Bool' -- ^includeFirstSwaplet
  ,withYieldTermStructure*`GenYieldTermStructure c',`CalibrationErrorType'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}
{#fun qlHestonModelHelper as hestonModelHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^maturity
  ,withCalendar*`Calendar',`Double' -- ^s0
  ,`Double' -- ^strikePrice
  ,withQuote*`GenQuote a' -- ^volatility
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeRate
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^dividendYield
  ,`CalibrationErrorType',preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}
-- TODO add more SwaptionHelper constructors
{#fun qlSwaptionHelper as swaptionHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^maturity
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote a' -- ^maturity
  ,withIborIndex*`GenIborIndex b',fromEnumQuantity`(Word,TimeUnit)'& -- ^fixedLegTenor
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withDayCounter*`DayCounter' -- ^floatingLegDayCounter
  ,withYieldTermStructure*`GenYieldTermStructure c',`CalibrationErrorType'
  ,fromMaybeDouble`Maybe Double' -- ^strike
  ,`Double' -- ^nominal
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,fromMaybeInt`Maybe Word' -- ^settlementDays
  ,`RateAveragingType' -- ^averagingMethod
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}
{#fun qlBlackCalibrationHelperTimes as times{withGenCalibrationHelper*`BlackCalibrationHelper',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |Returns array of arguments on which calibration is done.
{#fun qlCalibratedModelParams as params{withCalibratedModel*`GenCalibratedModel m',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |Black price given a volatility.
{#fun qlBlackCalibrationHelperBlackPrice as blackPrice{withGenCalibrationHelper*`BlackCalibrationHelper',`Double' -- ^volatility
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the error resulting from the model valuation
{#fun qlBlackCalibrationHelperCalibrationError as calibrationError{withGenCalibrationHelper*`BlackCalibrationHelper',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Black volatility implied by the model.
{#fun qlBlackCalibrationHelperImpliedVolatility as impliedVolatility{withGenCalibrationHelper*`BlackCalibrationHelper',`Double' -- ^targetValue
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the actual price of the instrument (from volatility)
{#fun qlBlackCalibrationHelperMarketValue as marketValue{withGenCalibrationHelper*`BlackCalibrationHelper',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the price of the instrument according to the model
{#fun qlBlackCalibrationHelperModelValue as modelValue{withGenCalibrationHelper*`BlackCalibrationHelper',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBlackCalibrationHelperSetPricingEngine as setPricingEngine{withGenCalibrationHelper*`BlackCalibrationHelper',withPricingEngine*`PricingEngine',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
