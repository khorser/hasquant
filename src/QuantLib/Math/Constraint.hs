{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Math.Constraint
  (
    boundaryConstraint
  , compositeConstraint
  , noConstraint
  , positiveConstraint
  )
where

import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Syntax
import QuantLib.Types

boundaryConstraint :: Double -- ^low
  -> Double -- ^high
  -> IO Constraint
boundaryConstraint = $(ffiCall 'boundaryConstraint) c_boundaryConstraint

foreign import ccall safe "ql.h qlBoundaryConstraint"
  c_boundaryConstraint :: CDouble -> CDouble -> Ptr CString -> IO (Ptr CConstraint)

compositeConstraint :: Constraint -- ^c1
  -> Constraint -- ^c2
  -> IO Constraint
compositeConstraint = $(ffiCall 'compositeConstraint) c_compositeConstraint

foreign import ccall safe "ql.h qlCompositeConstraint"
  c_compositeConstraint :: Ptr CConstraint -> Ptr CConstraint -> Ptr CString -> IO (Ptr CConstraint)

noConstraint :: IO Constraint
noConstraint = $(ffiCall 'noConstraint) c_noConstraint

foreign import ccall safe "ql.h qlNoConstraint"
  c_noConstraint :: Ptr CString -> IO (Ptr CConstraint)

positiveConstraint :: IO Constraint
positiveConstraint = $(ffiCall 'positiveConstraint) c_positiveConstraint

foreign import ccall safe "ql.h qlPositiveConstraint"
  c_positiveConstraint :: Ptr CString -> IO (Ptr CConstraint)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
