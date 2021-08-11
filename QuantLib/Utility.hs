module QuantLib.Utility
  (
    version
  , boostVersion

  , nullInteger
  , nullReal
  , epsilon
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)

import System.IO.Unsafe(unsafePerformIO)

foreign import ccall safe "ql.h qlVersion" qlVersion :: IO CString

foreign import ccall safe "ql.h qlBoostVersion" qlBoostVersion :: IO CString

foreign import ccall safe "ql.h qlNullInteger" qlNullInteger :: CInt

foreign import ccall safe "ql.h qlNullReal" qlNullReal :: CDouble

foreign import ccall safe "ql.h qlEpsilon" qlEpsilon :: CDouble

{-# NOINLINE version #-}
version :: String
version = unsafePerformIO $ qlVersion >>= peekCString

{-# NOINLINE boostVersion #-}
boostVersion :: String
boostVersion = unsafePerformIO $ qlBoostVersion >>= peekCString

nullInteger :: Int
nullInteger = fromIntegral qlNullInteger

nullReal :: Double
nullReal = realToFrac qlNullReal

epsilon :: Double
epsilon = realToFrac qlEpsilon

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
