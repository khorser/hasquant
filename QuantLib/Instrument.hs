{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls,FlexibleContexts,MultiParamTypeClasses #-}
module QuantLib.Instrument
  (
  -- types
    CInstrument
  , Instrument
  -- accessors
  , npv
  -- mutators
  , setPricingEngine
  )
where

import Control.Monad(liftM)

import QuantLib.Internal
import QuantLib.PricingEngine(PricingEngine, CPricingEngine)

data CInstrument
type Instrument = Object CInstrument

instance IsA CInstrument CInstrument where
  cast = id

foreign import ccall safe "ql.h qlInstrumentNPV"
  c_npv :: Ptr CInstrument -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h qlInstrumentSetPricingEngine"
  c_setPricingEngine :: Ptr CInstrument -> Ptr CPricingEngine -> Ptr CString
    -> IO ()

-- |Returns the NPV for the given Instrument object (qlInstrumentNPV)
npv :: IsA CInstrument a => Object a -> IO Double
npv i = liftM realToFrac $ withCast i (handleExceptions . c_npv)

-- |Sets a new pricing engine to the given Instrument pbject
-- (qlInstrumentSetPricingEngine)
setPricingEngine :: IsA CInstrument a => Object a-> PricingEngine -> IO ()
setPricingEngine i e =
  withCast i
  (\ii ->
    withObject e (handleExceptions . c_setPricingEngine ii))
