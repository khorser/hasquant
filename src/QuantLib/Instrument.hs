{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument
  (
    npv
  , setPricingEngine
  , errorEstimate
  , isExpired
  , valuationDate
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Date
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

-- |returns the error estimate on the NPV when available.
errorEstimate :: Instrument -> IO Double
errorEstimate = $(ffiCallX 'errorEstimate) c_errorEstimate

foreign import ccall safe "ql.h qlInstrumentErrorEstimate"
  c_errorEstimate :: Ptr CInstrument -> Ptr CString -> IO CDouble

-- |returns whether the instrument might have value greater than zero.
isExpired :: Instrument -> IO Bool
isExpired = $(ffiCallX 'isExpired) c_isExpired

foreign import ccall safe "ql.h qlInstrumentIsExpired"
  c_isExpired :: Ptr CInstrument -> Ptr CString -> IO CInt

-- |returns the date the net present value refers to.
valuationDate :: Instrument -> IO Day
valuationDate = $(ffiCallX 'valuationDate) c_valuationDate

foreign import ccall safe "ql.h qlInstrumentValuationDate"
  c_valuationDate :: Ptr CInstrument -> Ptr CString -> IO CDate
