{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Index
  (
  -- mutators
    addFixing
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlIndexAddFixing"
  c_indexAddFixing :: Ptr CIndex -> CDate -> CDouble -> CInt -> Ptr CString
    -> IO ()

-- |stores the historical fixing at the given date
-- the date passed as arguments must be the actual calendar date of the fixing; no settlement days must be used.
-- Adds fixings for the given Index object. QuantLibXL: qlIndexAddFixings
addFixing :: Index
  -> Day -- ^fixingDate
  -> Double -- ^fixing
  -> Bool -- ^forceOverwrite
  -> IO ()
addFixing = $(ffiCallX 'addFixing) c_indexAddFixing
