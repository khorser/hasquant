{-# LANGUAGE ForeignFunctionInterface #-}

module QuantLib.Utilities(version, boostVersion)
where

import Foreign.C.String
import System.IO.Unsafe

foreign import ccall safe "ql.h qlVersion"
    c_version :: CString
foreign import ccall safe "ql.h boostVersion"
    c_boostVersion :: CString

version :: String
version = unsafePerformIO $ peekCString c_version

boostVersion :: String
boostVersion = unsafePerformIO $ peekCString c_boostVersion
