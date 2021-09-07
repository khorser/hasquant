{-# LANGUAGE MultiParamTypeClasses, FlexibleInstances, FunctionalDependencies, FlexibleContexts, TypeOperators #-}
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
  , LmCorrelationModel
  , LmVolatilityModel
  , CalibrationHelper
  , BlackCalibrationHelper
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
  , generalizedHullWhite'
--  , generalizedHullWhite
  , gJRGARCHModel
  , hestonModel
  , hullWhite
  , varianceGammaModel
  , vasicek
  , lmConstWrapperCorrelationModel
  , lmConstWrapperVolatilityModel
  , lmExponentialCorrelationModel
  , lmFixedVolatilityModel
  , lmLinearExponentialCorrelationModel
  , lmLinearExponentialVolatilityModel
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
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.Process#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Time.Schedule#}(TimeUnit, Frequency)
import QuantLib.Internal.Type
{#import QuantLib.Index.InterestRate#}
import QuantLib.Internal.Index
import QuantLib.Internal.Enum

{#pointer *QlQuote as Quote foreign -> CQuote nocode#}
{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}

{#enum CalibrationErrorType{} deriving(Show, Eq)#}

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign finalizer qlFreeGJRGARCHModel newtype#}
instance ForeignObject GJRGARCHModel where
  withObject = withGJRGARCHModel
  constructor = GJRGARCHModel
  finalizer = qlFreeGJRGARCHModel

{#pointer *QlHestonModel as HestonModel foreign finalizer qlFreeHestonModel newtype#}
instance ForeignObject HestonModel where
  withObject = withHestonModel
  constructor = HestonModel
  finalizer = qlFreeHestonModel

{#pointer *QlBatesModel as BatesModel foreign finalizer qlFreeBatesModel newtype#}
instance ForeignObject BatesModel where
  withObject = withBatesModel
  constructor = BatesModel
  finalizer = qlFreeBatesModel

{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign finalizer qlFreePiecewiseTimeDependentHestonModel newtype#}
instance ForeignObject PiecewiseTimeDependentHestonModel where
  withObject = withPiecewiseTimeDependentHestonModel
  constructor = PiecewiseTimeDependentHestonModel
  finalizer = qlFreePiecewiseTimeDependentHestonModel

{#pointer *QlShortRateModel as ShortRateModel foreign finalizer qlFreeShortRateModel newtype#}
instance ForeignObject ShortRateModel where
  withObject = withShortRateModel
  constructor = ShortRateModel
  finalizer = qlFreeShortRateModel

{#pointer *QlAffineModel as AffineModel foreign finalizer qlFreeAffineModel newtype#}
instance ForeignObject AffineModel where
  withObject = withAffineModel
  constructor = AffineModel
  finalizer = qlFreeAffineModel

{#pointer *QlOneFactorAffineModel as OneFactorAffineModel foreign finalizer qlFreeOneFactorAffineModel newtype#}
instance ForeignObject OneFactorAffineModel where
  withObject = withOneFactorAffineModel
  constructor = OneFactorAffineModel
  finalizer = qlFreeOneFactorAffineModel

{#pointer *QlLiborForwardModel as LiborForwardModel foreign finalizer qlFreeLiborForwardModel newtype#}
instance ForeignObject LiborForwardModel where
  withObject = withLiborForwardModel
  constructor = LiborForwardModel
  finalizer = qlFreeLiborForwardModel

{#pointer *QlHullWhite as HullWhite foreign finalizer qlFreeHullWhite newtype#}
instance ForeignObject HullWhite where
  withObject = withHullWhite
  constructor = HullWhite
  finalizer = qlFreeHullWhite

{#pointer *QlCalibratedModel as CalibratedModel foreign finalizer qlFreeCalibratedModel newtype#}
instance ForeignObject CalibratedModel where
  withObject = withCalibratedModel
  constructor = CalibratedModel
  finalizer = qlFreeCalibratedModel

{#pointer *QlG2 as G2 foreign finalizer qlFreeG2 newtype#}
instance ForeignObject G2 where
  withObject = withG2
  constructor = G2
  finalizer = qlFreeG2

{#pointer *QlBatesDetJumpModel as BatesDetJumpModel foreign finalizer qlFreeBatesDetJumpModel newtype#}
instance ForeignObject BatesDetJumpModel where
  withObject = withBatesDetJumpModel
  constructor = BatesDetJumpModel
  finalizer = qlFreeBatesDetJumpModel

{#pointer *QlBatesDoubleExpDetJumpModel as BatesDoubleExpDetJumpModel foreign finalizer qlFreeBatesDoubleExpDetJumpModel newtype#}
instance ForeignObject BatesDoubleExpDetJumpModel where
  withObject = withBatesDoubleExpDetJumpModel
  constructor = BatesDoubleExpDetJumpModel
  finalizer = qlFreeBatesDoubleExpDetJumpModel

{#pointer *QlBatesDoubleExpModel as BatesDoubleExpModel foreign finalizer qlFreeBatesDoubleExpModel newtype#}
instance ForeignObject BatesDoubleExpModel where
  withObject = withBatesDoubleExpModel
  constructor = BatesDoubleExpModel
  finalizer = qlFreeBatesDoubleExpModel

{#pointer *QlLmCorrelationModel as LmCorrelationModel foreign finalizer qlFreeLmCorrelationModel newtype#}
instance ForeignObject LmCorrelationModel where
  withObject = withLmCorrelationModel
  constructor = LmCorrelationModel
  finalizer = qlFreeLmCorrelationModel

{#pointer *QlLmVolatilityModel as LmVolatilityModel foreign finalizer qlFreeLmVolatilityModel newtype#}
instance ForeignObject LmVolatilityModel where
  withObject = withLmVolatilityModel
  constructor = LmVolatilityModel
  finalizer = qlFreeLmVolatilityModel

{#pointer *QlCalibrationHelper as CalibrationHelper foreign -> CCalibrationHelper nocode#}
{#pointer *QlBlackCalibrationHelper as BlackCalibrationHelper foreign -> CBlackCalibrationHelper nocode#}

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

{#fun qlOneFactorAffineModelAsAffineModel{`OneFactorAffineModel'}->`AffineModel'#}
{#fun qlLiborForwardModelAsAffineModel{`LiborForwardModel'}->`AffineModel'#}
instance HullWhite`Derives` OneFactorAffineModel where cast = qlHullWhiteAsOneFactorAffineModel
{#fun qlHullWhiteAsOneFactorAffineModel{`HullWhite'}->`OneFactorAffineModel'#}
{#fun qlG2AsAffineModel{`G2'}->`AffineModel'#}
{#fun qlG2AsShortRateModel{`G2'}->`ShortRateModel'#}
instance G2`Derives` ShortRateModel where cast = qlG2AsShortRateModel
instance BatesDetJumpModel`Derives` BatesModel where cast = qlBatesDetJumpModelAsBatesModel
{#fun qlBatesDetJumpModelAsBatesModel{`BatesDetJumpModel'}->`BatesModel'#}
instance BatesDoubleExpDetJumpModel`Derives` BatesDoubleExpModel where cast = qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel
{#fun qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel{`BatesDoubleExpDetJumpModel'}->`BatesDoubleExpModel'#}
{#fun qlBatesDoubleExpModelAsHestonModel{`BatesDoubleExpModel'}->`HestonModel'#}
instance BatesDoubleExpModel`Derives` HestonModel where cast = qlBatesDoubleExpModelAsHestonModel
{#fun qlGJRGARCHModelAsCalibratedModel{`GJRGARCHModel'}->`CalibratedModel'#}
instance GJRGARCHModel`Derives` CalibratedModel where cast = qlGJRGARCHModelAsCalibratedModel
{#fun qlHestonModelAsCalibratedModel{`HestonModel'}->`CalibratedModel'#}
instance HestonModel`Derives` CalibratedModel where cast = qlHestonModelAsCalibratedModel
{#fun qlBatesModelAsHestonModel{`BatesModel'}->`HestonModel'#}
instance BatesModel`Derives` HestonModel where cast = qlBatesModelAsHestonModel
{#fun qlLiborForwardModelAsCalibratedModel{`LiborForwardModel'}->`CalibratedModel'#}
instance LiborForwardModel`Derives` CalibratedModel where cast = qlLiborForwardModelAsCalibratedModel
{#fun qlPiecewiseTimeDependentHestonModelAsCalibratedModel{`PiecewiseTimeDependentHestonModel'}->`CalibratedModel'#}
instance PiecewiseTimeDependentHestonModel`Derives` CalibratedModel where cast = qlPiecewiseTimeDependentHestonModelAsCalibratedModel
{#fun qlShortRateModelAsCalibratedModel{`ShortRateModel'}->`CalibratedModel'#}
instance ShortRateModel`Derives` CalibratedModel where cast = qlShortRateModelAsCalibratedModel
{#fun qlOneFactorAffineModelAsShortRateModel{`OneFactorAffineModel'}->`ShortRateModel'#}
instance OneFactorAffineModel`Derives` ShortRateModel where cast = qlOneFactorAffineModelAsShortRateModel

{#fun qlBatesModel as batesModel{withObject*`BatesProcess', preErrorCheck-`String'errorCheck*-}->`BatesModel'#}

{#fun qlBlackKarasinski as blackKarasinski{`YieldTermStructure',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`ShortRateModel'#}

{#fun qlCoxIngersollRoss as coxIngersollRoss{`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'#}

{#fun qlExtendedCoxIngersollRoss as extendedCoxIngersollRoss{`YieldTermStructure',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'#}

{#fun qlG2 as g2{`YieldTermStructure',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`G2'#}

{#fun qlGeneralizedHullWhite1 as generalizedHullWhite'{`YieldTermStructure', withDayArray*`[Day]'&, withDayArray*`[Day]'&, withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`ShortRateModel'#}

-- TODO fix cbits compilation
--{#fun qlGeneralizedHullWhite as generalizedHullWhite{`YieldTermStructure', withDayArray*`[Day]'&, withDayArray*`[Day]'&, preErrorCheck-`String'errorCheck*-}->`ShortRateModel'#}

{#fun qlGJRGARCHModel as gJRGARCHModel{withObject*`GJRGARCHProcess', preErrorCheck-`String'errorCheck*-}->`GJRGARCHModel'#}

{#fun qlHestonModel as hestonModel{withObject*`HestonProcess', preErrorCheck-`String'errorCheck*-}->`HestonModel'#}

{#fun qlHullWhite as hullWhite{`YieldTermStructure',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`HullWhite'#}

{#fun qlVarianceGammaModel as varianceGammaModel{withObject*`VarianceGammaProcess', preErrorCheck-`String'errorCheck*-}->`CalibratedModel'#}

{#fun qlVasicek as vasicek{`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'#}

{#fun qlLmConstWrapperCorrelationModel as lmConstWrapperCorrelationModel{`LmCorrelationModel', preErrorCheck-`String'errorCheck*-}->`LmCorrelationModel'#}

{#fun qlLmConstWrapperVolatilityModel as lmConstWrapperVolatilityModel{`LmVolatilityModel', preErrorCheck-`String'errorCheck*-}->`LmVolatilityModel'#}

{#fun qlLmExponentialCorrelationModel as lmExponentialCorrelationModel{fromIntegral`Word',`Double', preErrorCheck-`String'errorCheck*-}->`LmCorrelationModel'#}

{#fun qlLmFixedVolatilityModel as lmFixedVolatilityModel{withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`LmVolatilityModel'#}

{#fun qlLmLinearExponentialCorrelationModel as lmLinearExponentialCorrelationModel{fromIntegral`Word',`Double',`Double', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`LmCorrelationModel'#}

{#fun qlLmLinearExponentialVolatilityModel as lmLinearExponentialVolatilityModel{withDoubleArray*`[Double]'&,`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`LmVolatilityModel'#}

{#fun qlLiborForwardModel as liborForwardModel{withObject*`LiborForwardModelProcess',`LmVolatilityModel',`LmCorrelationModel', preErrorCheck-`String'errorCheck*-}->`LiborForwardModel'#}

{#pointer *OptimizationMethod as QlOptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *EndCriteria as QlEndCriteria foreign -> CEndCriteria nocode#}
{#pointer *Constraint as QlConstraint foreign -> CConstraint nocode#}
-- |Calibrate to a set of market instruments (caps/swaptions)
-- An additional constraint can be passed which must be satisfied in addition to the constraints of the model.
calibrate :: CalibratedModel -> [(CalibrationHelper, Double)] -> OptimizationMethod -> EndCriteria -> Maybe Constraint -> IO ()
calibrate m h o e c = qlCalibratedModelCalibrate m hh hw o e c where (hh, hw) = unzip h
{#fun qlCalibratedModelCalibrate{`CalibratedModel', withCalibrationHelperArray*`[GenCalibrationHelper a]'&, withDoubleArray*`[Double]'&, withOptimizationMethod*`OptimizationMethod', withEndCriteria*`EndCriteria', withMaybeConstraint*`Maybe Constraint', preErrorCheck-`String'errorCheck*-}->`()'#}

{#fun qlCapHelper as capHelper{fromEnumQuantity`(Word, TimeUnit)'&, withQuote*`GenQuote a',`IborIndex',`Frequency', withDayCounter*`DayCounter',`Bool',`YieldTermStructure',`CalibrationErrorType', preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}

{#fun qlHestonModelHelper as hestonModelHelper{fromEnumQuantity`(Word, TimeUnit)'&, withCalendar*`Calendar',`Double',`Double', withQuote*`GenQuote a',`YieldTermStructure',`YieldTermStructure',`CalibrationErrorType', preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}

-- TODO add more parameters and more SwaptionHelper constructors
{#fun qlSwaptionHelper as swaptionHelper{fromEnumQuantity`(Word, TimeUnit)'&, fromEnumQuantity`(Word, TimeUnit)'&, withQuote*`GenQuote a',`IborIndex', fromEnumQuantity`(Word, TimeUnit)'&, withDayCounter*`DayCounter', withDayCounter*`DayCounter',`YieldTermStructure',`CalibrationErrorType', preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}

{#fun qlBlackCalibrationHelperTimes as times{withBlackCalibrationHelper*`BlackCalibrationHelper', preArray-`[Double]'&peekDoubleArray*, preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Returns array of arguments on which calibration is done.
{#fun qlCalibratedModelParams as params{`CalibratedModel', preArray-`[Double]'&peekDoubleArray*, preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Black price given a volatility.
{#fun qlBlackCalibrationHelperBlackPrice as blackPrice{withBlackCalibrationHelper*`BlackCalibrationHelper',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the error resulting from the model valuation
{#fun qlBlackCalibrationHelperCalibrationError as calibrationError{withBlackCalibrationHelper*`BlackCalibrationHelper', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black volatility implied by the model.
{#fun qlBlackCalibrationHelperImpliedVolatility as impliedVolatility{withBlackCalibrationHelper*`BlackCalibrationHelper',`Double',`Double', fromIntegral`Word',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the actual price of the instrument (from volatility)
{#fun qlBlackCalibrationHelperMarketValue as marketValue{withBlackCalibrationHelper*`BlackCalibrationHelper', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the price of the instrument according to the model
{#fun qlBlackCalibrationHelperModelValue as modelValue{withBlackCalibrationHelper*`BlackCalibrationHelper', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBlackCalibrationHelperSetPricingEngine as setPricingEngine{withBlackCalibrationHelper*`BlackCalibrationHelper',withPricingEngine*`PricingEngine', preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
