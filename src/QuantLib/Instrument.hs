{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument
  (
    npv
  , setPricingEngine
  , forwardValue
  , impliedYield
  , settlementDate
  , spotIncome
  , spotValue
  )
where

import QuantLib.Compounding
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlInstrumentNPV"
  c_npv :: Ptr CInstrument -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlInstrumentSetPricingEngine"
  c_setPricingEngine :: Ptr CInstrument -> Ptr CPricingEngine -> Ptr CString
    -> IO ()

-- |Returns the net present value of the given Instrument. QuantLibXL: qlInstrumentNPV
npv :: Instrument -> IO Double
npv = $(ffiCallX 'npv) c_npv

-- |set the pricing engine to be used.
-- /Warning/ calling this method will have no effects in case the performCalculation method was overridden in a derived class.
-- Sets a new pricing engine to the given Instrument. QuantLibXL: qlInstrumentSetPricingEngine
setPricingEngine :: Instrument -> PricingEngine -> IO ()
setPricingEngine = $(ffiCallX 'setPricingEngine) c_setPricingEngine

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
