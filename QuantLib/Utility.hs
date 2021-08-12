module QuantLib.Utility
  (
    version
  , boostVersion

  , epsilon
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)

import System.IO.Unsafe(unsafePerformIO)

foreign import ccall safe "ql.h qlVersion" qlVersion :: IO CString

foreign import ccall safe "ql.h qlBoostVersion" qlBoostVersion :: IO CString

foreign import ccall safe "ql.h qlEpsilon" qlEpsilon :: CDouble

{-# NOINLINE version #-}
version :: String
version = unsafePerformIO $ qlVersion >>= peekCString

{-# NOINLINE boostVersion #-}
boostVersion :: String
boostVersion = unsafePerformIO $ qlBoostVersion >>= peekCString

epsilon :: Double
epsilon = realToFrac qlEpsilon

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
