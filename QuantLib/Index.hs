{-# LANGUAGE ForeignFunctionInterface,FlexibleContexts,MultiParamTypeClasses #-}
module QuantLib.Index
  (
  -- mutators
    addFixing
  )
where

import QuantLib.Internal
import QuantLib.Types

instance IsA CIndex CIndex where
  cast = id

foreign import ccall safe "ql.h qlIndexAddFixing"
  c_indexAddFixing :: Ptr CIndex -> CDate -> CDouble -> CInt -> Ptr CString
    -> IO ()

-- |Adds fixings for the given Index object (qlIndexAddFixings)
addFixing :: IsA CIndex a => Object a -> Day -> Double -> Bool -> IO ()
addFixing i d v o =
  withCast i
  (\ii -> handleExceptions $ c_indexAddFixing ii
                                              (toQlDate d)
                                              (realToFrac v)
                                              (fromBool o))
