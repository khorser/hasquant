{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Utilities
  (
    version
  , boostVersion
  , checkEnums
  , nullInteger
  , nullReal
  )
where

import Foreign.C.String(peekCString)
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax
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

-- |check that enumerations are marshalled consistently
-- (for use in internal unit tests)
checkEnums :: [(String, Bool)]
checkEnums = map checkEnum $(qlEnumsInfo)
  where
    checkEnum :: (String, Integer) -> (String, Bool)
    checkEnum (n, l) = (n, length (values n) == fromIntegral l)

nullInteger :: Int
nullInteger = fromIntegral c_nullInteger

nullReal :: Double
nullReal = realToFrac c_nullReal

foreign import ccall safe "ql.h qlNullInteger"
  c_nullInteger :: CInt
foreign import ccall safe "ql.h qlNullReal"
  c_nullReal :: CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
