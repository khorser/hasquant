{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Instrument.Credit
  (
    faceValueClaim
  , faceValueAccrualClaim
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

import QuantLib.Credit.ProtectionSide(ProtectionSide)
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Date
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Types

-- |Claim on a notional
faceValueClaim :: QLE s (Claim s)
faceValueClaim = $(ffiCall 'faceValueClaim) c_faceValueClaim

foreign import ccall safe "ql.h qlFaceValueClaim"
  c_faceValueClaim :: Ptr CString -> IO (Ptr CClaim)

-- |Claim on the notional of a reference security, including accrual
faceValueAccrualClaim :: Bond -- ^referenceSecurity
  -> QLE s (Claim s)
faceValueAccrualClaim = $(ffiCall 'faceValueAccrualClaim) c_faceValueAccrualClaim

foreign import ccall safe "ql.h qlFaceValueAccrualClaim"
  c_faceValueAccrualClaim :: Ptr CBond -> Ptr CString -> IO (Ptr CClaim)

-- |CDS quoted as running-spread only.
-- side Whether the protection is bought or sold. notional Notional value spread Running spread in fractional units. schedule Coupon schedule. paymentConvention Business-day convention for payment-date adjustment. dayCounter Day-count convention for accrual. settlesAccrual Whether or not the accrued coupon is due in the event of a default. paysAtDefaultTime If set to true, any payments triggered by a default event are due at default time. If set to false, they are due at the end of the accrual period. protectionStart The first date where a default event will trigger the contract.
creditDefaultSwap :: ProtectionSide -- ^side
  -> Double -- ^notional
  -> Double -- ^spread
  -> Schedule -- ^schedule
  -> BusinessDayConvention -- ^paymentConvention
  -> DayCounter -- ^dayCounter
  -> Bool -- ^settlesAccrual
  -> Bool -- ^paysAtDefaultTime
  -> Maybe Day -- ^protectionStart
  -> Claim
  -> QLE s (CreditDefaultSwap s)
creditDefaultSwap = $(ffiCall 'creditDefaultSwap) c_creditDefaultSwap

foreign import ccall safe "ql.h qlCreditDefaultSwap"
  c_creditDefaultSwap :: CInt -> CDouble -> CDouble -> Ptr CSchedule -> CInt -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CClaim -> Ptr CString -> IO (Ptr CCreditDefaultSwap)

-- |CDS quoted as upfront and running spread.
-- side Whether the protection is bought or sold. notional Notional value upfront Upfront in fractional units. spread Running spread in fractional units. schedule Coupon schedule. paymentConvention Business-day convention for payment-date adjustment. dayCounter Day-count convention for accrual. settlesAccrual Whether or not the accrued coupon is due in the event of a default. paysAtDefaultTime If set to true, any payments triggered by a default event are due at default time. If set to false, they are due at the end of the accrual period. protectionStart The first date where a default event will trigger the contract. upfrontDate Settlement date for the upfront payment.
creditDefaultSwap' :: ProtectionSide -- ^side
  -> Double -- ^notional
  -> Double -- ^upfront
  -> Double -- ^spread
  -> Schedule -- ^schedule
  -> BusinessDayConvention -- ^paymentConvention
  -> DayCounter -- ^dayCounter
  -> Bool -- ^settlesAccrual
  -> Bool -- ^paysAtDefaultTime
  -> Maybe Day -- ^protectionStart
  -> Maybe Day -- ^upfrontDate
  -> Claim
  -> QLE s (CreditDefaultSwap s)
creditDefaultSwap' = $(ffiCall 'creditDefaultSwap') c_creditDefaultSwap'

foreign import ccall safe "ql.h qlCreditDefaultSwap1"
  c_creditDefaultSwap' :: CInt -> CDouble -> CDouble -> CDouble -> Ptr CSchedule -> CInt -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDate -> Ptr CClaim -> Ptr CString -> IO (Ptr CCreditDefaultSwap)

atmRate :: CdsOption -> QLE Double
atmRate = $(ffiCallX 'atmRate) c_atmRate

foreign import ccall safe "ql.h qlCdsOptionAtmRate"
  c_atmRate :: Ptr CCdsOption -> Ptr CString -> IO CDouble

cdsOption :: CreditDefaultSwap -- ^swap
  -> Exercise -- ^exercise
  -> Bool -- ^knocksOut
  -> QLE s (CdsOption s)
cdsOption = $(ffiCall 'cdsOption) c_cdsOption

foreign import ccall safe "ql.h qlCdsOption"
  c_cdsOption :: Ptr CCreditDefaultSwap -> Ptr CExercise -> CInt -> Ptr CString -> IO (Ptr CCdsOption)

impliedVolatility :: CdsOption
  -> Double -- ^price
  -> YieldTermStructure -- ^termStructure
  -> DefaultProbabilityTermStructure
  -> Double -- ^recoveryRate
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> QLE s Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

foreign import ccall safe "ql.h qlCdsOptionImpliedVolatility"
  c_impliedVolatility :: Ptr CCdsOption -> CDouble -> Ptr CYieldTermStructure -> Ptr CDefaultProbabilityTermStructure -> CDouble -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

riskyAnnuity :: CdsOption -> QLE s Double
riskyAnnuity = $(ffiCallX 'riskyAnnuity) c_riskyAnnuity

foreign import ccall safe "ql.h qlCdsOptionRiskyAnnuity"
  c_riskyAnnuity :: Ptr CCdsOption -> Ptr CString -> IO CDouble

-- |Conventional/standard upfront-to-spread conversion.
-- Under a standard ISDA model and a set of standardised instrument characteristics, it is the running only quoted spread that will make a CDS contract have an NPV of 0 when quoted for that running only spread. Refer to: "ISDA Standard CDS converter specification." May 2009.The conventional recovery rate to apply in the calculation is as specified by ISDA, not necessarily equal to the market-quoted one. It is typically 0.4 for SeniorSec and 0.2 for subordinate.The conversion employs a flat hazard rate. As a result, you will not recover the market quotes.This method performs the calculation with the instrument characteristics. It will coincide with the ISDA calculation if your object has the standard characteristics. Notably: The calendar should have no bank holidays, just weekends.The yield curve should be LIBOR piecewise constant in fwd rates, with a discount factor of 1 on the calculation date, which coincides with the trade date.Convention should be Following for yield curve and contract cashflows.The CDS should pay accrued and mature on standard IMM dates, settle on trade date +1 and upfront settle on trade date +3.
conventionalSpread :: CreditDefaultSwap s
  -> Double -- ^conventionalRecovery
  -> YieldTermStructure s -- ^discountCurve
  -> DayCounter s -- ^dayCounter
  -> QLE s Double
conventionalSpread = $(ffiCallX 'conventionalSpread) c_conventionalSpread

foreign import ccall safe "ql.h qlCreditDefaultSwapConventionalSpread"
  c_conventionalSpread :: Ptr CCreditDefaultSwap -> CDouble -> Ptr CYieldTermStructure -> Ptr CDayCounter -> Ptr CString -> IO CDouble

-- |Returns the variation of the fixed-leg value given a one-basis-point change in the running spread.
couponLegBPS :: CreditDefaultSwap s
  -> QLE s Double
couponLegBPS = $(ffiCallX 'couponLegBPS) c_couponLegBPS

foreign import ccall safe "ql.h qlCreditDefaultSwapCouponLegBPS"
  c_couponLegBPS :: Ptr CCreditDefaultSwap -> Ptr CString -> IO CDouble

couponLegNPV :: CreditDefaultSwap s
  -> QLE s Double
couponLegNPV = $(ffiCallX 'couponLegNPV) c_couponLegNPV

foreign import ccall safe "ql.h qlCreditDefaultSwapCouponLegNPV"
  c_couponLegNPV :: Ptr CCreditDefaultSwap -> Ptr CString -> IO CDouble

coupons :: CreditDefaultSwap s
  -> QLE s (Leg s)
coupons = $(ffiCall 'coupons) c_coupons

foreign import ccall safe "ql.h qlCreditDefaultSwapCoupons"
  c_coupons :: Ptr CCreditDefaultSwap -> Ptr CString -> IO (Ptr CLeg)

defaultLegNPV :: CreditDefaultSwap s
  -> QLE s Double
defaultLegNPV = $(ffiCallX 'defaultLegNPV) c_defaultLegNPV

foreign import ccall safe "ql.h qlCreditDefaultSwapDefaultLegNPV"
  c_defaultLegNPV :: Ptr CCreditDefaultSwap -> Ptr CString -> IO CDouble

-- |Returns the upfront spread that, given the running spread and the quoted recovery rate, will make the instrument have an NPV of 0.
fairUpfront :: CreditDefaultSwap s
  -> QLE s Double
fairUpfront = $(ffiCallX 'fairUpfront) c_fairUpfront

foreign import ccall safe "ql.h qlCreditDefaultSwapFairUpfront"
  c_fairUpfront :: Ptr CCreditDefaultSwap -> Ptr CString -> IO CDouble

-- |Implied hazard rate calculation.
-- This method performs the calculation with the instrument characteristics. It will coincide with the ISDA calculation if your object has the standard characteristics. Notably: The calendar should have no bank holidays, just weekends.The yield curve should be LIBOR piecewise constant in fwd rates, with a discount factor of 1 on the calculation date, which coincides with the trade date.Convention should be Following for yield curve and contract cashflows.The CDS should pay accrued and mature on standard IMM dates, settle on trade date +1 and upfront settle on trade date +3.
impliedHazardRate :: CreditDefaultSwap s
  -> Double -- ^targetNPV
  -> YieldTermStructure s -- ^discountCurve
  -> DayCounter s -- ^dayCounter
  -> Double -- ^recoveryRate
  -> Double -- ^accuracy
  -> QLE s Double
impliedHazardRate = $(ffiCallX 'impliedHazardRate) c_impliedHazardRate

foreign import ccall safe "ql.h qlCreditDefaultSwapImpliedHazardRate"
  c_impliedHazardRate :: Ptr CCreditDefaultSwap -> CDouble -> Ptr CYieldTermStructure -> Ptr CDayCounter -> CDouble -> CDouble -> Ptr CString -> IO CDouble

upfrontBPS :: CreditDefaultSwap
  -> QLE s Double
upfrontBPS = $(ffiCallX 'upfrontBPS) c_upfrontBPS

foreign import ccall safe "ql.h qlCreditDefaultSwapUpfrontBPS"
  c_upfrontBPS :: Ptr CCreditDefaultSwap -> Ptr CString -> IO CDouble

upfrontNPV :: CreditDefaultSwap
  -> QLE s Double
upfrontNPV = $(ffiCallX 'upfrontNPV) c_upfrontNPV

foreign import ccall safe "ql.h qlCreditDefaultSwapUpfrontNPV"
  c_upfrontNPV :: Ptr CCreditDefaultSwap -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
