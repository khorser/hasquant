module QuantLib.Utilities
  (
  -- accessors
    version
  , boostVersion
  )
where

import Foreign.C.String(peekCString)
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal.Utils

foreign import ccall safe "ql.h qlVersion"
  c_version :: CString
foreign import ccall safe "ql.h qlBoostVersion"
  c_boostVersion :: CString

-- |returns the version number of QuantLib
version :: String
version = unsafePerformIO $ peekCString c_version

-- |returns the version number of Boost
boostVersion :: String
boostVersion = unsafePerformIO $ peekCString c_boostVersion
