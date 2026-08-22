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
  ) where
import QuantLib.Internal
import QuantLib.Internal.Common
import QuantLib.Internal.Type
{#import QuantLib.Instrument#}(PricingModel)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum ProtectionSide{} deriving(Show, Eq)#}

{#pointer *QlCreditDefaultSwap as CreditDefaultSwap foreign -> CCreditDefaultSwap' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlCdsOption as CdsOption foreign -> CCdsOption' nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}
{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *Schedule foreign -> CSchedule nocode#}
{#pointer *QlClaim as Claim foreign -> CQlClaim nocode#}
{#pointer *QlExercise nocode#}

-- |CDS quoted as running-spread only.
-- side Whether the protection is bought or sold. notional Notional value spread Running spread in fractional units. schedule Coupon schedule. paymentConvention Business-day convention for payment-date adjustment. dayCounter Day-count convention for accrual. settlesAccrual Whether or not the accrued coupon is due in the event of a default. paysAtDefaultTime If set to true, any payments triggered by a default event are due at default time. If set to false, they are due at the end of the accrual period. protectionStart The first date where a default event will trigger the contract.
{#fun qlCreditDefaultSwap as creditDefaultSwap{`ProtectionSide',`Double' -- ^notional
  ,`Double' -- ^spread
  ,withSchedule*`Schedule',fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter',`Bool' -- ^settlesAccrual
  ,`Bool' -- ^paysAtDefaultTime
  ,withMaybeDay*`Maybe Day' -- ^protectionStart
  ,withClaim*`Claim'
  ,withDayCounter*`DayCounter' -- ^lastPeriodDayCounter
  ,`Bool' -- ^rebatesAccrual
  ,withMaybeDay*`Maybe Day' -- ^tradeDate
  ,fromIntegral`Word' -- ^cashSettlementDays
  ,preErrorCheck-`String'errorCheck*-}->`CreditDefaultSwap'peekCreditDefaultSwap*#}

-- |CDS quoted as upfront and running spread.
-- side Whether the protection is bought or sold. notional Notional value upfront Upfront in fractional units. spread Running spread in fractional units. schedule Coupon schedule. paymentConvention Business-day convention for payment-date adjustment. dayCounter Day-count convention for accrual. settlesAccrual Whether or not the accrued coupon is due in the event of a default. paysAtDefaultTime If set to true, any payments triggered by a default event are due at default time. If set to false, they are due at the end of the accrual period. protectionStart The first date where a default event will trigger the contract. upfrontDate Settlement date for the upfront payment.
{#fun qlCreditDefaultSwap1 as creditDefaultSwap'{`ProtectionSide',`Double' -- ^notional
  ,`Double' -- ^upfront
  ,`Double' -- ^spread
  ,withSchedule*`Schedule',fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter',`Bool' -- ^settlesAccrual
  ,`Bool' -- ^paysAtDefaultTime
  ,withMaybeDay*`Maybe Day' -- ^protectionStart
  ,withMaybeDay*`Maybe Day' -- ^upfrontDate
  ,withClaim*`Claim'
  ,withDayCounter*`DayCounter' -- ^lastPeriodDayCounter
  ,`Bool' -- ^rebatesAccrual
  ,withMaybeDay*`Maybe Day' -- ^tradeDate
  ,fromIntegral`Word' -- ^cashSettlementDays
  ,preErrorCheck-`String'errorCheck*-}->`CreditDefaultSwap'peekCreditDefaultSwap*#}

-- |The fair running spread implied by the underlying CDS's term structures at the option's exercise.
{#fun qlCdsOptionAtmRate as atmRate{withCdsOption*`CdsOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |An option giving the right to enter the underlying CDS, buying protection and paying coupon.
{#fun qlCdsOption as cdsOption{withGenInstrument*`CreditDefaultSwap',withExercise*`Exercise',`Bool' -- ^knocksOut
  ,preErrorCheck-`String'errorCheck*-}->`CdsOption'peekCdsOption*#}

-- |Volatility that reproduces a given option price under the pricing engine's volatility model.
{#fun qlCdsOptionImpliedVolatility as impliedVolatility{withCdsOption*`CdsOption',`Double' -- ^price
  ,withYieldTermStructure*`GenYieldTermStructure y',withGenTermStructure*`DefaultProbabilityTermStructure'
  ,`Double' -- ^recoveryRate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The risky annuity used to convert between the option's price and its implied volatility.
{#fun qlCdsOptionRiskyAnnuity as riskyAnnuity{withCdsOption*`CdsOption',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Conventional/standard upfront-to-spread conversion.
-- Under a standard ISDA model and a set of standardised instrument characteristics, it is the running only quoted spread that will make a CDS contract have an NPV of 0 when quoted for that running only spread. Refer to: "ISDA Standard CDS converter specification." May 2009.The conventional recovery rate to apply in the calculation is as specified by ISDA, not necessarily equal to the market-quoted one. It is typically 0.4 for SeniorSec and 0.2 for subordinate.The conversion employs a flat hazard rate. As a result, you will not recover the market quotes.This method performs the calculation with the instrument characteristics. It will coincide with the ISDA calculation if your object has the standard characteristics. Notably: The calendar should have no bank holidays, just weekends.The yield curve should be LIBOR piecewise constant in fwd rates, with a discount factor of 1 on the calculation date, which coincides with the trade date.Convention should be Following for yield curve and contract cashflows.The CDS should pay accrued and mature on standard IMM dates, settle on trade date +1 and upfront settle on trade date +3.
{#fun qlCreditDefaultSwapConventionalSpread as conventionalSpread{withGenInstrument*`CreditDefaultSwap',`Double'
  ,withYieldTermStructure*`GenYieldTermStructure y',withDayCounter*`DayCounter'
  ,`PricingModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the variation of the fixed-leg value given a one-basis-point change in the running spread.
{#fun qlCreditDefaultSwapCouponLegBPS as couponLegBPS{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the coupon (premium) leg.
{#fun qlCreditDefaultSwapCouponLegNPV as couponLegNPV{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The coupon-leg cash flows of the CDS.
{#fun qlCreditDefaultSwapCoupons as coupons{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |NPV of the default (protection) leg.
{#fun qlCreditDefaultSwapDefaultLegNPV as defaultLegNPV{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the upfront spread that, given the running spread and the quoted recovery rate, will make the instrument have an NPV of 0.
{#fun qlCreditDefaultSwapFairUpfront as fairUpfront{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Implied hazard rate calculation.
-- This method performs the calculation with the instrument characteristics. It will coincide with the ISDA calculation if your object has the standard characteristics. Notably: The calendar should have no bank holidays, just weekends.The yield curve should be LIBOR piecewise constant in fwd rates, with a discount factor of 1 on the calculation date, which coincides with the trade date.Convention should be Following for yield curve and contract cashflows.The CDS should pay accrued and mature on standard IMM dates, settle on trade date +1 and upfront settle on trade date +3.
{#fun qlCreditDefaultSwapImpliedHazardRate as impliedHazardRate{withGenInstrument*`CreditDefaultSwap',`Double' -- ^targetNPV
  ,withYieldTermStructure*`GenYieldTermStructure y',withDayCounter*`DayCounter',`Double' -- ^recoveryRate
  ,`Double' -- ^accuracy
  ,`PricingModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the variation of the upfront payment value given a one-basis-point change in the upfront.
{#fun qlCreditDefaultSwapUpfrontBPS as upfrontBPS{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the upfront payment.
{#fun qlCreditDefaultSwapUpfrontNPV as upfrontNPV{withGenInstrument*`CreditDefaultSwap',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
