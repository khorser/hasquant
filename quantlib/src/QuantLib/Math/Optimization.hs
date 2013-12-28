{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Math.Optimization
  (
    boundaryConstraint
  , compositeConstraint
  , noConstraint
  , positiveConstraint

  , levenbergMarquardt
  , simplex

  , endCriteria
  )
where

import QuantLib.Internal.Types
import QuantLib.Internal.Syntax
import QuantLib.Types

boundaryConstraint :: Double -- ^low
  -> Double -- ^high
  -> QLE s (Constraint s)
boundaryConstraint = $(ffiCall 'boundaryConstraint) c_boundaryConstraint

foreign import ccall safe "ql.h qlBoundaryConstraint"
  c_boundaryConstraint :: CDouble -> CDouble -> Ptr CString -> IO (Ptr CConstraint)

compositeConstraint :: Constraint s -- ^c1
  -> Constraint s -- ^c2
  -> QLE s (Constraint s)
compositeConstraint = $(ffiCall 'compositeConstraint) c_compositeConstraint

foreign import ccall safe "ql.h qlCompositeConstraint"
  c_compositeConstraint :: Ptr CConstraint -> Ptr CConstraint -> Ptr CString -> IO (Ptr CConstraint)

noConstraint :: QLE s (Constraint s)
noConstraint = $(ffiCall 'noConstraint) c_noConstraint

foreign import ccall safe "ql.h qlNoConstraint"
  c_noConstraint :: Ptr CString -> IO (Ptr CConstraint)

positiveConstraint :: QLE s (Constraint s)
positiveConstraint = $(ffiCall 'positiveConstraint) c_positiveConstraint

foreign import ccall safe "ql.h qlPositiveConstraint"
  c_positiveConstraint :: Ptr CString -> IO (Ptr CConstraint)

levenbergMarquardt :: Double -- ^epsfcn
  -> Double -- ^xtol
  -> Double -- ^gtol
  -> QLE s (OptimizationMethod s)
levenbergMarquardt = $(ffiCall 'levenbergMarquardt) c_levenbergMarquardt

foreign import ccall safe "ql.h qlLevenbergMarquardt"
  c_levenbergMarquardt :: CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COptimizationMethod)

-- |Constructor taking as input the characteristic length
simplex :: Double -- ^lambda
  -> QLE s (OptimizationMethod s)
simplex = $(ffiCall 'simplex) c_simplex

foreign import ccall safe "ql.h qlSimplex"
  c_simplex :: CDouble -> Ptr CString -> IO (Ptr COptimizationMethod)

-- |Initialization constructor.
endCriteria :: Word -- ^maxIterations
  -> Word -- ^maxStationaryStateIterations
  -> Double -- ^rootEpsilon
  -> Double -- ^functionEpsilon
  -> Double -- ^gradientNormEpsilon
  -> QLE s (EndCriteria s)
endCriteria = $(ffiCall 'endCriteria) c_endCriteria

foreign import ccall safe "ql.h qlEndCriteria"
  c_endCriteria :: CUInt -> CUInt -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CEndCriteria)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
