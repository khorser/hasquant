{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Utilities
  (
  -- accessors
    version
  , boostVersion
  )
where

import Foreign.C.String(CString, peekCString)

import System.IO.Unsafe(unsafePerformIO)

foreign import ccall safe "ql.h qlVersion"
  c_version :: CString
foreign import ccall safe "ql.h boostVersion"
  c_boostVersion :: CString

-- |returns the version number of QuantLib
version :: String
version = unsafePerformIO $ peekCString c_version

-- |returns the version number of Boost
boostVersion :: String
boostVersion = unsafePerformIO $ peekCString c_boostVersion
