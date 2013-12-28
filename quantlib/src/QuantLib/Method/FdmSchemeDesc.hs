{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Method.FdmSchemeDesc
  (
    fdmSchemeDesc
  , craigSneyd
  , douglas
  , explicitEuler
  , hundsdorfer
  , implicitEuler
  , modifiedCraigSneyd
  , modifiedHundsdorfer
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Method.FdmScheme(FdmSchemeType)
import QuantLib.Types

fdmSchemeDesc :: FdmSchemeType -- ^type
  -> Double -- ^theta
  -> Double -- ^mu
  -> QLE s (FdmSchemeDesc s)
fdmSchemeDesc = $(ffiCall 'fdmSchemeDesc) c_fdmSchemeDesc

foreign import ccall safe "ql.h qlFdmSchemeDesc"
  c_fdmSchemeDesc :: CInt -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CFdmSchemeDesc)

craigSneyd :: QLE s (FdmSchemeDesc s)
craigSneyd = $(ffiCall 'craigSneyd) c_craigSneyd

foreign import ccall safe "ql.h qlFdmSchemeDescCraigSneyd"
  c_craigSneyd :: Ptr CString -> IO (Ptr CFdmSchemeDesc)

douglas :: QLE s (FdmSchemeDesc s)
douglas = $(ffiCall 'douglas) c_douglas

foreign import ccall safe "ql.h qlFdmSchemeDescDouglas"
  c_douglas ::  Ptr CString -> IO (Ptr CFdmSchemeDesc)

explicitEuler :: QLE s (FdmSchemeDesc s)
explicitEuler = $(ffiCall 'explicitEuler) c_explicitEuler

foreign import ccall safe "ql.h qlFdmSchemeDescExplicitEuler"
  c_explicitEuler :: Ptr CString -> IO (Ptr CFdmSchemeDesc)

hundsdorfer :: QLE s (FdmSchemeDesc s)
hundsdorfer = $(ffiCall 'hundsdorfer) c_hundsdorfer

foreign import ccall safe "ql.h qlFdmSchemeDescHundsdorfer"
  c_hundsdorfer :: Ptr CString -> IO (Ptr CFdmSchemeDesc)

implicitEuler :: QLE s (FdmSchemeDesc s)
implicitEuler = $(ffiCall 'implicitEuler) c_implicitEuler

foreign import ccall safe "ql.h qlFdmSchemeDescImplicitEuler"
  c_implicitEuler :: Ptr CString -> IO (Ptr CFdmSchemeDesc)

modifiedCraigSneyd :: QLE s (FdmSchemeDesc s)
modifiedCraigSneyd = $(ffiCall 'modifiedCraigSneyd) c_modifiedCraigSneyd

foreign import ccall safe "ql.h qlFdmSchemeDescModifiedCraigSneyd"
  c_modifiedCraigSneyd :: Ptr CString -> IO (Ptr CFdmSchemeDesc)

modifiedHundsdorfer :: QLE s (FdmSchemeDesc s)
modifiedHundsdorfer = $(ffiCall 'modifiedHundsdorfer) c_modifiedHundsdorfer

foreign import ccall safe "ql.h qlFdmSchemeDescModifiedHundsdorfer"
  c_modifiedHundsdorfer :: Ptr CString -> IO (Ptr CFdmSchemeDesc)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
