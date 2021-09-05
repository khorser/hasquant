{-# LANGUAGE MultiParamTypeClasses, TypeOperators #-}
module QuantLib.Instrument.Credit
  (
    CreditDefaultSwap
  , ProtectionSide(..)
  , Claim(..)

  , creditDefaultSwap
  , creditDefaultSwap'

  , atmRate
  , cdsOption
  , impliedVolatility
  , riskyAnnuity

  , conventionalSpread
  , couponLegBPS
  , couponLegNPV
  , coupons
  , defaultLegNPV
  , fairUpfront
  , impliedHazardRate
  , upfrontBPS
  , upfrontNPV
  )
  where

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Instrument.Bond#}(Bond)
import QuantLib.Internal.Enum
import QuantLib.Internal.Type
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.TermStructure.Credit#}(DefaultProbabilityTermStructure)
{#import QuantLib.Instrument.Option#}(CdsOption)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

data Claim = FaceValue | FaceValueAccrual Bond

{#enum ProtectionSide {} deriving(Show, Eq)#}

{#pointer *QlCreditDefaultSwap as CreditDefaultSwap foreign finalizer qlFreeCreditDefaultSwap newtype#}
instance ForeignObject CreditDefaultSwap where
  withObject = withCreditDefaultSwap
  constructor = CreditDefaultSwap
  finalizer=qlFreeCreditDefaultSwap
instance CreditDefaultSwap`Derives` Instrument where cast = qlCreditDefaultSwapAsInstrument

{#pointer *QlClaim foreign -> CQlClaim nocode#}

{#fun qlCreditDefaultSwapAsInstrument {`CreditDefaultSwap'}->`Instrument'peekObject*#}

-- |Claim on a notional
{#fun qlFaceValueClaim {preErrorCheck-`String'errorCheck*-}->`QlClaim'peekClaim*#}

-- |Claim on the notional of a reference security, including accrual
{#fun qlFaceValueAccrualClaim {withObject*`Bond', preErrorCheck-`String'errorCheck*-}->`QlClaim'peekClaim*#}

qlClaim :: Claim -> IO QlClaim
qlClaim FaceValue = qlFaceValueClaim
qlClaim (FaceValueAccrual b) = qlFaceValueAccrualClaim b

-- |CDS quoted as running-spread only.
-- side Whether the protection is bought or sold. notional Notional value spread Running spread in fractional units. schedule Coupon schedule. paymentConvention Business-day convention for payment-date adjustment. dayCounter Day-count convention for accrual. settlesAccrual Whether or not the accrued coupon is due in the event of a default. paysAtDefaultTime If set to true, any payments triggered by a default event are due at default time. If set to false, they are due at the end of the accrual period. protectionStart The first date where a default event will trigger the contract.
creditDefaultSwap :: ProtectionSide -> Double -> Double -> Schedule -> BusinessDayConvention -> DayCounter -> Bool -> Bool -> Maybe Day -> Claim -> IO CreditDefaultSwap
creditDefaultSwap ps d1 d2 s bd dc b1 b2 d c = qlClaim c >>= qlCreditDefaultSwap ps d1 d2 s bd dc b1 b2 d
{#fun qlCreditDefaultSwap {`ProtectionSide',`Double',`Double', withSchedule*`Schedule',`BusinessDayConvention', withDayCounter*`DayCounter',`Bool',`Bool', withMaybeDay*`Maybe Day', withSimpleType*`QlClaim', preErrorCheck-`String'errorCheck*-}->`CreditDefaultSwap'#}

-- |CDS quoted as upfront and running spread.
-- side Whether the protection is bought or sold. notional Notional value upfront Upfront in fractional units. spread Running spread in fractional units. schedule Coupon schedule. paymentConvention Business-day convention for payment-date adjustment. dayCounter Day-count convention for accrual. settlesAccrual Whether or not the accrued coupon is due in the event of a default. paysAtDefaultTime If set to true, any payments triggered by a default event are due at default time. If set to false, they are due at the end of the accrual period. protectionStart The first date where a default event will trigger the contract. upfrontDate Settlement date for the upfront payment.
creditDefaultSwap' :: ProtectionSide -> Double -> Double -> Double -> Schedule -> BusinessDayConvention -> DayCounter -> Bool -> Bool -> Maybe Day -> Maybe Day -> Claim -> IO CreditDefaultSwap
creditDefaultSwap' ps d1 d2 d3 s bd dc b1 b2 ds1 ds2 c = qlClaim c >>= qlCreditDefaultSwap1 ps d1 d2 d3 s bd dc b1 b2 ds1 ds2
{#fun qlCreditDefaultSwap1 {`ProtectionSide',`Double',`Double',`Double', withSchedule*`Schedule',`BusinessDayConvention', withDayCounter*`DayCounter',`Bool',`Bool', withMaybeDay*`Maybe Day', withMaybeDay*`Maybe Day', withSimpleType*`QlClaim', preErrorCheck-`String'errorCheck*-}->`CreditDefaultSwap'#}

{#fun qlCdsOptionAtmRate as atmRate {withObject*`CdsOption', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#pointer *QlExercise foreign newtype nocode#}
{#fun qlCdsOption as cdsOption {`CreditDefaultSwap', withEnumObject*`Exercise',`Bool', preErrorCheck-`String'errorCheck*-}->`CdsOption'peekObject*#}

{#fun qlCdsOptionImpliedVolatility as impliedVolatility {withObject*`CdsOption',`Double', withObject*`YieldTermStructure', withObject*`DefaultProbabilityTermStructure',`Double',`Double', fromIntegral`Word',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCdsOptionRiskyAnnuity as riskyAnnuity {withObject*`CdsOption', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Conventional/standard upfront-to-spread conversion.
-- Under a standard ISDA model and a set of standardised instrument characteristics, it is the running only quoted spread that will make a CDS contract have an NPV of 0 when quoted for that running only spread. Refer to: "ISDA Standard CDS converter specification." May 2009.The conventional recovery rate to apply in the calculation is as specified by ISDA, not necessarily equal to the market-quoted one. It is typically 0.4 for SeniorSec and 0.2 for subordinate.The conversion employs a flat hazard rate. As a result, you will not recover the market quotes.This method performs the calculation with the instrument characteristics. It will coincide with the ISDA calculation if your object has the standard characteristics. Notably: The calendar should have no bank holidays, just weekends.The yield curve should be LIBOR piecewise constant in fwd rates, with a discount factor of 1 on the calculation date, which coincides with the trade date.Convention should be Following for yield curve and contract cashflows.The CDS should pay accrued and mature on standard IMM dates, settle on trade date +1 and upfront settle on trade date +3.
{#fun qlCreditDefaultSwapConventionalSpread as conventionalSpread {`CreditDefaultSwap',`Double', withObject*`YieldTermStructure', withDayCounter*`DayCounter', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the variation of the fixed-leg value given a one-basis-point change in the running spread.
{#fun qlCreditDefaultSwapCouponLegBPS as couponLegBPS {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCreditDefaultSwapCouponLegNPV as couponLegNPV {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCreditDefaultSwapCoupons as coupons {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlCreditDefaultSwapDefaultLegNPV as defaultLegNPV {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the upfront spread that, given the running spread and the quoted recovery rate, will make the instrument have an NPV of 0.
{#fun qlCreditDefaultSwapFairUpfront as fairUpfront {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Implied hazard rate calculation.
-- This method performs the calculation with the instrument characteristics. It will coincide with the ISDA calculation if your object has the standard characteristics. Notably: The calendar should have no bank holidays, just weekends.The yield curve should be LIBOR piecewise constant in fwd rates, with a discount factor of 1 on the calculation date, which coincides with the trade date.Convention should be Following for yield curve and contract cashflows.The CDS should pay accrued and mature on standard IMM dates, settle on trade date +1 and upfront settle on trade date +3.
{#fun qlCreditDefaultSwapImpliedHazardRate as impliedHazardRate {`CreditDefaultSwap',`Double', withObject*`YieldTermStructure', withDayCounter*`DayCounter',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCreditDefaultSwapUpfrontBPS as upfrontBPS {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCreditDefaultSwapUpfrontNPV as upfrontNPV {`CreditDefaultSwap', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
