{-# LANGUAGE FlexibleContexts,MultiParamTypeClasses #-}
module QuantLib.Index
  (
  -- mutators
    addFixing
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlIndexAddFixing"
  c_indexAddFixing :: Ptr CIndex -> CDate -> CDouble -> CInt -> Ptr CString
    -> IO ()

-- |Adds fixings for the given Index object (qlIndexAddFixings)
addFixing :: Index -> Day -> Double -> Bool -> IO ()
addFixing i d v o =
  withObject i
  (\ii -> handleExceptions $ c_indexAddFixing ii
                                              (toQlDate d)
                                              (realToFrac v)
                                              (fromBool o))
