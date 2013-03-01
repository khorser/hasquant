{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
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
  )

where

import QuantLib.Credit.ProtectionSide
import QuantLib.Time.BusinessDayConvention

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Date
import QuantLib.Types

-- |Claim on a notional
faceValueClaim :: IO Claim
faceValueClaim = $(ffiCall 'faceValueClaim) c_faceValueClaim

foreign import ccall safe "ql.h qlFaceValueClaim"
  c_faceValueClaim :: Ptr CString -> IO (Ptr CClaim)

-- |Claim on the notional of a reference security, including accrual
faceValueAccrualClaim :: Bond -- ^referenceSecurity
  -> IO Claim
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
  -> IO CreditDefaultSwap
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
  -> IO CreditDefaultSwap
creditDefaultSwap' = $(ffiCall 'creditDefaultSwap') c_creditDefaultSwap'

foreign import ccall safe "ql.h qlCreditDefaultSwap1"
  c_creditDefaultSwap' :: CInt -> CDouble -> CDouble -> CDouble -> Ptr CSchedule -> CInt -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDate -> Ptr CClaim -> Ptr CString -> IO (Ptr CCreditDefaultSwap)

atmRate :: CdsOption -> IO Double
atmRate = $(ffiCallX 'atmRate) c_atmRate

foreign import ccall safe "ql.h qlCdsOptionAtmRate"
  c_atmRate :: Ptr CCdsOption -> Ptr CString -> IO CDouble

cdsOption :: CreditDefaultSwap -- ^swap
  -> Exercise -- ^exercise
  -> Bool -- ^knocksOut
  -> IO CdsOption
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
  -> IO Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

foreign import ccall safe "ql.h qlCdsOptionImpliedVolatility"
  c_impliedVolatility :: Ptr CCdsOption -> CDouble -> Ptr CYieldTermStructure -> Ptr CDefaultProbabilityTermStructure -> CDouble -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

riskyAnnuity :: CdsOption -> IO Double
riskyAnnuity = $(ffiCallX 'riskyAnnuity) c_riskyAnnuity

foreign import ccall safe "ql.h qlCdsOptionRiskyAnnuity"
  c_riskyAnnuity :: Ptr CCdsOption -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
