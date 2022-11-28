{-# LANGUAGE MultiParamTypeClasses, FlexibleInstances, FlexibleContexts, TypeOperators #-}
module QuantLib.Model
  (
   CalibrationErrorType(..)
  , GJRGARCHModel
  , HestonModel
  , BatesModel
  , PiecewiseTimeDependentHestonModel
  , ShortRateModel
  , AffineModel
  , OneFactorAffineModel
  , LiborForwardModel
  , HullWhite
  , CalibratedModel
  , G2
  , BatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , LmCorrelationModel(..)
  , LmVolatilityModel(..)
  , CalibrationHelper
  , BlackCalibrationHelper
  , GenCalibrationHelper
  , asCalibrationHelper

  , asAffineModel
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

  , calibrate
  , capHelper
  , hestonModelHelper
  , swaptionHelper
  , times

  , params
  , blackPrice
  , calibrationError
  , impliedVolatility
  , marketValue
  , modelValue

  , AffineModelDescendant(..)
  , setPricingEngine
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.Time.Schedule#}(Frequency)
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

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign -> CGJRGARCHModel nocode#}
{#pointer *QlHestonModel as HestonModel foreign -> CHestonModel nocode#}
{#pointer *QlBatesModel as BatesModel foreign -> CBatesModel nocode#}
{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign -> CPiecewiseTimeDependentHestonModel nocode#}
{#pointer *QlShortRateModel as ShortRateModel foreign -> CShortRateModel nocode#}
{#pointer *QlAffineModel as AffineModel foreign -> CAffineModel nocode#}
{#pointer *QlOneFactorAffineModel as OneFactorAffineModel foreign -> COneFactorAffineModel nocode#}
{#pointer *QlLiborForwardModel as LiborForwardModel foreign -> CLiborForwardModel nocode#}
{#pointer *QlHullWhite as HullWhite foreign -> CHullWhite nocode#}
{#pointer *QlCalibratedModel as CalibratedModel foreign -> CCalibratedModel nocode#}
{#pointer *QlG2 as G2 foreign -> CG2 nocode#}
{#pointer *QlBatesDetJumpModel as BatesDetJumpModel foreign -> CBatesDetJumpModel nocode#}
{#pointer *QlBatesDoubleExpDetJumpModel as BatesDoubleExpDetJumpModel foreign -> CBatesDoubleExpDetJumpModel nocode#}
{#pointer *QlBatesDoubleExpModel as BatesDoubleExpModel foreign -> CBatesDoubleExpModel nocode#}
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

-- multiple inheritance... not sure if we need that cast to AffineModel at all
newtype AffineModelDescendant a = AffineModelDescendant a
instance (AffineModelDescendant OneFactorAffineModel)`Derives` AffineModel where cast (AffineModelDescendant x) = qlOneFactorAffineModelAsAffineModel x
instance (AffineModelDescendant LiborForwardModel)`Derives` AffineModel where cast (AffineModelDescendant x) = qlLiborForwardModelAsAffineModel x
instance (AffineModelDescendant G2)`Derives` AffineModel where cast (AffineModelDescendant x) = qlG2AsAffineModel x

asAffineModel :: (a`Derives` AffineModel) => a -> IO AffineModel
asAffineModel = cast
asCalibratedModel :: (a`Derives` CalibratedModel) => a -> IO CalibratedModel
asCalibratedModel = cast
asHestonModel :: (a`Derives` HestonModel) => a -> IO HestonModel
asHestonModel = cast
asShortRateModel :: (a`Derives` ShortRateModel) => a -> IO ShortRateModel
asShortRateModel = cast
asOneFactorAffineModel :: (a`Derives` OneFactorAffineModel) => a -> IO OneFactorAffineModel
asOneFactorAffineModel = cast
asBatesModel :: (a`Derives` BatesModel) => a -> IO BatesModel
asBatesModel = cast
asBatesDoubleExpModel :: (a`Derives` BatesDoubleExpModel) => a -> IO BatesDoubleExpModel
asBatesDoubleExpModel = cast

{#fun qlOneFactorAffineModelAsAffineModel{withOneFactorAffineModel*`OneFactorAffineModel'}->`AffineModel'peekAffineModel*#}
{#fun qlLiborForwardModelAsAffineModel{withLiborForwardModel*`LiborForwardModel'}->`AffineModel'peekAffineModel*#}
instance HullWhite`Derives` OneFactorAffineModel where cast = qlHullWhiteAsOneFactorAffineModel
{#fun qlHullWhiteAsOneFactorAffineModel{withHullWhite*`HullWhite'}->`OneFactorAffineModel'peekOneFactorAffineModel*#}
{#fun qlG2AsAffineModel{withG2*`G2'}->`AffineModel'peekAffineModel*#}
{#fun qlG2AsShortRateModel{withG2*`G2'}->`ShortRateModel'peekShortRateModel*#}
instance G2`Derives` ShortRateModel where cast = qlG2AsShortRateModel
instance BatesDetJumpModel`Derives` BatesModel where cast = qlBatesDetJumpModelAsBatesModel
{#fun qlBatesDetJumpModelAsBatesModel{withBatesDetJumpModel*`BatesDetJumpModel'}->`BatesModel'peekBatesModel*#}
instance BatesDoubleExpDetJumpModel`Derives` BatesDoubleExpModel where cast = qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel
{#fun qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel{withBatesDoubleExpDetJumpModel*`BatesDoubleExpDetJumpModel'}->`BatesDoubleExpModel'peekBatesDoubleExpModel*#}
{#fun qlBatesDoubleExpModelAsHestonModel{withBatesDoubleExpModel*`BatesDoubleExpModel'}->`HestonModel'peekHestonModel*#}
instance BatesDoubleExpModel`Derives` HestonModel where cast = qlBatesDoubleExpModelAsHestonModel
{#fun qlGJRGARCHModelAsCalibratedModel{withGJRGARCHModel*`GJRGARCHModel'}->`CalibratedModel'peekCalibratedModel*#}
instance GJRGARCHModel`Derives` CalibratedModel where cast = qlGJRGARCHModelAsCalibratedModel
{#fun qlHestonModelAsCalibratedModel{withHestonModel*`HestonModel'}->`CalibratedModel'peekCalibratedModel*#}
instance HestonModel`Derives` CalibratedModel where cast = qlHestonModelAsCalibratedModel
{#fun qlBatesModelAsHestonModel{withBatesModel*`BatesModel'}->`HestonModel'peekHestonModel*#}
instance BatesModel`Derives` HestonModel where cast = qlBatesModelAsHestonModel
{#fun qlLiborForwardModelAsCalibratedModel{withLiborForwardModel*`LiborForwardModel'}->`CalibratedModel'peekCalibratedModel*#}
instance LiborForwardModel`Derives` CalibratedModel where cast = qlLiborForwardModelAsCalibratedModel
{#fun qlPiecewiseTimeDependentHestonModelAsCalibratedModel{withPiecewiseTimeDependentHestonModel*`PiecewiseTimeDependentHestonModel'}->`CalibratedModel'peekCalibratedModel*#}
instance PiecewiseTimeDependentHestonModel`Derives` CalibratedModel where cast = qlPiecewiseTimeDependentHestonModelAsCalibratedModel
{#fun qlShortRateModelAsCalibratedModel{withShortRateModel*`ShortRateModel'}->`CalibratedModel'peekCalibratedModel*#}
instance ShortRateModel`Derives` CalibratedModel where cast = qlShortRateModelAsCalibratedModel
{#fun qlOneFactorAffineModelAsShortRateModel{withOneFactorAffineModel*`OneFactorAffineModel'}->`ShortRateModel'peekShortRateModel*#}
instance OneFactorAffineModel`Derives` ShortRateModel where cast = qlOneFactorAffineModelAsShortRateModel

{#fun qlBatesModel as batesModel{withBatesProcess*`BatesProcess',preErrorCheck-`String'errorCheck*-}->`BatesModel'peekBatesModel*#}
{#fun qlBlackKarasinski as blackKarasinski{withYieldTermStructure*`GenYieldTermStructure a',`Double' -- ^a
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`ShortRateModel'peekShortRateModel*#}
{#fun qlCoxIngersollRoss as coxIngersollRoss{`Double' -- ^r0
  ,`Double' -- ^theta
  ,`Double' -- ^k
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}
{#fun qlExtendedCoxIngersollRoss as extendedCoxIngersollRoss{withYieldTermStructure*`GenYieldTermStructure a',`Double' -- ^theta
  ,`Double' -- ^k
  ,`Double' -- ^sigma
  ,`Double' -- ^x0
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}
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
calibrate :: CalibratedModel -> [(CalibrationHelper, Double)] -- ^(instrument, weight)
  -> OptimizationMethod -> EndCriteria -> Maybe Constraint -> IO ()
calibrate m h o e c = qlCalibratedModelCalibrate m hh hw o e c where (hh, hw) = unzip h
{#fun qlCalibratedModelCalibrate{withCalibratedModel*`CalibratedModel',withCalibrationHelperArray*`[GenCalibrationHelper a]'&,withDoubleArray*`[Double]'&
  ,withOptimizationMethod*`OptimizationMethod',withEndCriteria*`EndCriteria',withMaybeConstraint*`Maybe Constraint',preErrorCheck-`String'errorCheck*-}->`()'#}

{#fun qlCapHelper as capHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote a' -- ^volatility
  ,withIborIndex*`GenIborIndex b',`Frequency' -- ^fixedLegFrequency
  ,withDayCounter*`DayCounter',`Bool' -- ^includeFirstSwaplet
  ,withYieldTermStructure*`GenYieldTermStructure c',`CalibrationErrorType',preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}
{#fun qlHestonModelHelper as hestonModelHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^maturity
  ,withCalendar*`Calendar',`Double' -- ^s0
  ,`Double' -- ^strikePrice
  ,withQuote*`GenQuote a' -- ^volatility
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeRate
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^dividendYield
  ,`CalibrationErrorType',preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}
-- TODO add more parameters and more SwaptionHelper constructors
{#fun qlSwaptionHelper as swaptionHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^maturity
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote a' -- ^maturity
  ,withIborIndex*`GenIborIndex b',fromEnumQuantity`(Word,TimeUnit)'& -- ^fixedLegTenor
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withDayCounter*`DayCounter' -- ^floatingLegDayCounter
  ,withYieldTermStructure*`GenYieldTermStructure c',`CalibrationErrorType',preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}
{#fun qlBlackCalibrationHelperTimes as times{withGenCalibrationHelper*`BlackCalibrationHelper',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |Returns array of arguments on which calibration is done.
{#fun qlCalibratedModelParams as params{withCalibratedModel*`CalibratedModel',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
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
