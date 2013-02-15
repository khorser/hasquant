{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Forward
  (
    fixedRateBondForward
  , forwardRateAgreement

  , cleanForwardPrice
  , forwardPrice
  , forwardValue
  , impliedYield
  , settlementDate
  , spotIncome
  , spotValue

  , forwardRate
  , isExpired
  )

where

import QuantLib.Compounding
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.PositionType
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

forwardRateAgreement :: Day -- ^valueDate
  -> Day -- ^maturityDate
  -> PositionType -- ^type
  -> Double -- ^strikeForwardRate
  -> Double -- ^notionalAmount
  -> IborIndex -- ^index
  -> Maybe YieldTermStructure -- ^discountCurve
  -> IO ForwardRateAgreement
forwardRateAgreement = $(ffiConstruct 'forwardRateAgreement) c_forwardRateAgreement

foreign import ccall safe "ql.h qlForwardRateAgreement"
  c_forwardRateAgreement :: CDate -> CDate -> CInt -> CDouble -> CDouble -> Ptr CIborIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CForwardRateAgreement)

-- |If strike is given in the constructor, can calculate the NPV of the contract via NPV().If strike/forward price is desired, it can be obtained via forwardPrice(). In this case, the strike variable in the constructor is irrelevant and will be ignored.
fixedRateBondForward :: Day -- ^valueDate
  -> Day -- ^maturityDate
  -> PositionType -- ^type
  -> Double -- ^strike
  -> Word -- ^settlementDays
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^businessDayConvention
  -> FixedRateBond -- ^fixedCouponBond
  -> Maybe YieldTermStructure -- ^discountCurve
  -> Maybe YieldTermStructure -- ^incomeDiscountCurve
  -> IO FixedRateBondForward
fixedRateBondForward = $(ffiConstruct 'fixedRateBondForward) c_fixedRateBondForward

foreign import ccall safe "ql.h qlFixedRateBondForward"
  c_fixedRateBondForward :: CDate -> CDate -> CInt -> CDouble -> CUInt -> Ptr CDayCounter -> Ptr CCalendar -> CInt -> Ptr CFixedRateBond -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CFixedRateBondForward)

-- |(dirty) forward bond price minus accrued on bond at delivery
cleanForwardPrice :: FixedRateBondForward -> IO Double
cleanForwardPrice = $(ffiCallX 'cleanForwardPrice) c_cleanForwardPrice

foreign import ccall safe "ql.h qlFixedRateBondForwardCleanForwardPrice"
  c_cleanForwardPrice :: Ptr CFixedRateBondForward -> Ptr CString -> IO CDouble

-- |(dirty) forward bond price
forwardPrice :: FixedRateBondForward -> IO Double
forwardPrice = $(ffiCallX 'forwardPrice) c_forwardPrice

foreign import ccall safe "ql.h qlFixedRateBondForwardForwardPrice"
  c_forwardPrice :: Ptr CFixedRateBondForward -> Ptr CString -> IO CDouble

-- |forward value/price of underlying, discounting income/dividends
-- if this is a bond forward price, is must be a dirty forward price.
forwardValue :: Forward -> IO Double
forwardValue = $(ffiCallX 'forwardValue) c_forwardValue

foreign import ccall safe "ql.h qlForwardForwardValue"
  c_forwardValue :: Ptr CForward -> Ptr CString -> IO CDouble

-- |Simple yield calculation based on underlying spot and forward values, taking into account underlying income. When $ t>0 $, call with: underlyingSpotValue=spotValue(t), forwardValue=strikePrice, to get current yield. For a repo, if $ t=0 $, impliedYield should reproduce the spot repo rate. For FRA's, this should reproduce the relevant zero rate at the FRA's maturityDate_;
impliedYield :: Forward
  -> Double -- ^underlyingSpotValue
  -> Double -- ^forwardValue
  -> Day -- ^settlementDate
  -> Compounding -- ^compoundingConvention
  -> DayCounter -- ^dayCounter
  -> IO InterestRate
impliedYield = $(ffiConstruct 'impliedYield) c_impliedYield

foreign import ccall safe "ql.h qlForwardImpliedYield"
  c_impliedYield :: Ptr CForward -> CDouble -> CDouble -> CDate -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CInterestRate)

settlementDate :: Forward -> IO Day
settlementDate = $(ffiCallX 'settlementDate) c_settlementDate

foreign import ccall safe "ql.h qlForwardSettlementDate"
  c_settlementDate :: Ptr CForward -> Ptr CString -> IO CDate

-- |NPV of income/dividends/storage-costs etc. of underlying instrument.
spotIncome :: Forward
  -> YieldTermStructure -- ^incomeDiscountCurve
  -> IO Double
spotIncome = $(ffiCallX 'spotIncome) c_spotIncome

foreign import ccall safe "ql.h qlForwardSpotIncome"
  c_spotIncome :: Ptr CForward -> Ptr CYieldTermStructure -> Ptr CString -> IO CDouble

-- |returns spot value/price of an underlying financial instrument
spotValue :: Forward -> IO Double
spotValue = $(ffiCallX 'spotValue) c_spotValue

foreign import ccall safe "ql.h qlForwardSpotValue"
  c_spotValue :: Ptr CForward -> Ptr CString -> IO CDouble

-- |Returns the relevant forward rate associated with the FRA term.
forwardRate :: ForwardRateAgreement
  -> IO InterestRate
forwardRate = $(ffiConstruct 'forwardRate) c_forwardRate

foreign import ccall safe "ql.h qlForwardRateAgreementForwardRate"
  c_forwardRate :: Ptr CForwardRateAgreement -> Ptr CString -> IO (Ptr CInterestRate)

-- |A FRA expires/settles on the valueDate
isExpired :: ForwardRateAgreement
  -> IO Bool
isExpired = $(ffiCallX 'isExpired) c_isExpired

foreign import ccall safe "ql.h qlForwardRateAgreementIsExpired"
  c_isExpired :: Ptr CForwardRateAgreement -> Ptr CString -> IO CInt
