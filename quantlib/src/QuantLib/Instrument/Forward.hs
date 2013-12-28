{-# LANGUAGE TemplateHaskell #-}
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
  )

where

import QuantLib.Compounding(Compounding)
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.PositionType(PositionType)
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

forwardRateAgreement :: Day -- ^valueDate
  -> Day -- ^maturityDate
  -> PositionType -- ^type
  -> Double -- ^strikeForwardRate
  -> Double -- ^notionalAmount
  -> IborIndex s -- ^index
  -> Maybe (YieldTermStructure s) -- ^discountCurve
  -> QLE s (ForwardRateAgreement s)
forwardRateAgreement = $(ffiCall 'forwardRateAgreement) c_forwardRateAgreement

foreign import ccall safe "ql.h qlForwardRateAgreement"
  c_forwardRateAgreement :: CDate -> CDate -> CInt -> CDouble -> CDouble -> Ptr CIborIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CForwardRateAgreement)

-- |If strike is given in the constructor, can calculate the NPV of the contract via NPV().If strike/forward price is desired, it can be obtained via forwardPrice(). In this case, the strike variable in the constructor is irrelevant and will be ignored.
fixedRateBondForward :: Day -- ^valueDate
  -> Day -- ^maturityDate
  -> PositionType -- ^type
  -> Double -- ^strike
  -> Word -- ^settlementDays
  -> DayCounter s -- ^dayCounter
  -> Calendar s -- ^calendar
  -> BusinessDayConvention -- ^businessDayConvention
  -> FixedRateBond s -- ^fixedCouponBond
  -> Maybe (YieldTermStructure s) -- ^discountCurve
  -> Maybe (YieldTermStructure s) -- ^incomeDiscountCurve
  -> QLE s (FixedRateBondForward s)
fixedRateBondForward = $(ffiCall 'fixedRateBondForward) c_fixedRateBondForward

foreign import ccall safe "ql.h qlFixedRateBondForward"
  c_fixedRateBondForward :: CDate -> CDate -> CInt -> CDouble -> CUInt -> Ptr CDayCounter -> Ptr CCalendar -> CInt -> Ptr CFixedRateBond -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CFixedRateBondForward)

-- |(dirty) forward bond price minus accrued on bond at delivery
cleanForwardPrice :: FixedRateBondForward s -> QLE s Double
cleanForwardPrice = $(ffiCallX 'cleanForwardPrice) c_cleanForwardPrice

foreign import ccall safe "ql.h qlFixedRateBondForwardCleanForwardPrice"
  c_cleanForwardPrice :: Ptr CFixedRateBondForward -> Ptr CString -> IO CDouble

-- |(dirty) forward bond price
forwardPrice :: FixedRateBondForward s -> QLE s Double
forwardPrice = $(ffiCallX 'forwardPrice) c_forwardPrice

foreign import ccall safe "ql.h qlFixedRateBondForwardForwardPrice"
  c_forwardPrice :: Ptr CFixedRateBondForward -> Ptr CString -> IO CDouble

-- |forward value/price of underlying, discounting income/dividends
-- if this is a bond forward price, is must be a dirty forward price.
forwardValue :: Forward s -> QLE s Double
forwardValue = $(ffiCallX 'forwardValue) c_forwardValue

foreign import ccall safe "ql.h qlForwardForwardValue"
  c_forwardValue :: Ptr CForward -> Ptr CString -> IO CDouble

-- |Simple yield calculation based on underlying spot and forward values, taking into account underlying income. When $ t>0 $, call with: underlyingSpotValue=spotValue(t), forwardValue=strikePrice, to get current yield. For a repo, if $ t=0 $, impliedYield should reproduce the spot repo rate. For FRA's, this should reproduce the relevant zero rate at the FRA's maturityDate_;
impliedYield :: Forward s
  -> Double -- ^underlyingSpotValue
  -> Double -- ^forwardValue
  -> Day -- ^settlementDate
  -> Compounding -- ^compoundingConvention
  -> DayCounter s -- ^dayCounter
  -> QLE s (InterestRate s)
impliedYield = $(ffiCall 'impliedYield) c_impliedYield

foreign import ccall safe "ql.h qlForwardImpliedYield"
  c_impliedYield :: Ptr CForward -> CDouble -> CDouble -> CDate -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CInterestRate)

settlementDate :: Forward s -> QLE s Day
settlementDate = $(ffiCallX 'settlementDate) c_settlementDate

foreign import ccall safe "ql.h qlForwardSettlementDate"
  c_settlementDate :: Ptr CForward -> Ptr CString -> IO CDate

-- |NPV of income/dividends/storage-costs etc. of underlying instrument.
spotIncome :: Forward s
  -> YieldTermStructure s -- ^incomeDiscountCurve
  -> QLE s Double
spotIncome = $(ffiCallX 'spotIncome) c_spotIncome

foreign import ccall safe "ql.h qlForwardSpotIncome"
  c_spotIncome :: Ptr CForward -> Ptr CYieldTermStructure -> Ptr CString -> IO CDouble

-- |returns spot value/price of an underlying financial instrument
spotValue :: Forward s -> QLE s Double
spotValue = $(ffiCallX 'spotValue) c_spotValue

foreign import ccall safe "ql.h qlForwardSpotValue"
  c_spotValue :: Ptr CForward -> Ptr CString -> IO CDouble

-- |Returns the relevant forward rate associated with the FRA term.
forwardRate :: ForwardRateAgreement s
  -> QLE s (InterestRate s)
forwardRate = $(ffiCall 'forwardRate) c_forwardRate

foreign import ccall safe "ql.h qlForwardRateAgreementForwardRate"
  c_forwardRate :: Ptr CForwardRateAgreement -> Ptr CString -> IO (Ptr CInterestRate)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
