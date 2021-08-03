module QuantLib.Utilities
  (
    version
  , boostVersion
  -- marshalling helpers
  , calloca
  , errorCheck
  , freeString
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.Marshal.Utils(with)
import Foreign.Storable(peek)

import Control.Exception(throwIO)
import Control.Monad(when)

import QuantLib.Types(Error(CPlusPlusException))

#include "ql.h"

{#fun pure qlVersion as version {} -> `String' #}

{#fun pure qlBoostVersion as boostVersion {} -> `String' #}

{#fun qlFreeString as freeString {`CString'} -> `()' #}

errorCheck :: Ptr CString -> IO ()
errorCheck p = do
  a <- peek p
  when
    (a /= nullPtr)
    (do
      e <- peekCString a
      freeString a
      throwIO $ CPlusPlusException e)

-- like alloca but initializes the allocated pointer with zero
calloca :: (Ptr (Ptr a) -> IO b) -> IO b
calloca = with nullPtr

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
