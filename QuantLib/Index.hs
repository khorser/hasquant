{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls,FlexibleContexts,MultiParamTypeClasses #-}
module QuantLib.Index
  (
  -- types
    CIndex
  , Index
  -- mutators
  , addFixing
  )
where

import QuantLib.Internal

data CIndex
type Index = Object CIndex

instance IsA CIndex CIndex

foreign import ccall safe "ql.h qlIndexAddFixing"
  c_indexAddFixing :: Ptr CIndex -> CDate -> CDouble -> CInt -> Ptr CString
    -> IO ()

-- |Adds fixings for the given Index object (qlIndexAddFixings)
addFixing :: IsA CIndex a => Object a -> Day -> Double -> Bool -> IO ()
addFixing i d v o =
  withObject i
    (\ii -> handleExceptions $ c_indexAddFixing (safeCastPtr ii)
                                                (toQlDate d)
                                                (realToFrac v)
                                                (fromBool o))
