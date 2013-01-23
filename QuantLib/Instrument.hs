{-# LANGUAGE FlexibleContexts,MultiParamTypeClasses #-}
module QuantLib.Instrument
  (
  -- accessors
    npv
  -- mutators
  , setPricingEngine
  )
where

import Control.Monad(liftM)

import QuantLib.Internal
import QuantLib.Types

foreign import ccall safe "ql.h qlInstrumentNPV"
  c_npv :: Ptr CInstrument -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlInstrumentSetPricingEngine"
  c_setPricingEngine :: Ptr CInstrument -> Ptr CPricingEngine -> Ptr CString
    -> IO ()

-- |Returns the NPV for the given Instrument object (qlInstrumentNPV)
npv :: Instrument -> IO Double
npv i = liftM realToFrac $ withObject i (handleExceptions . c_npv)

-- |Sets a new pricing engine to the given Instrument pbject
-- (qlInstrumentSetPricingEngine)
setPricingEngine :: Instrument -> PricingEngine -> IO ()
setPricingEngine i e =
  withObject i
  (\ii ->
    withObject e (handleExceptions . c_setPricingEngine ii))
