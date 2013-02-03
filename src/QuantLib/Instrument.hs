{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument
  (
  -- accessors
    npv
  -- mutators
  , setPricingEngine
  )
where

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
