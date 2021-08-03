module QuantLib.Utility
  (
    version
  , boostVersion

  , nullInteger
  , nullReal
  , epsilon

  -- marshalling helpers
  , preErrorCheck
  , errorCheck
  , freeString

  , marshalBool'
  , unmarshalBool'
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.Marshal.Utils(with, toBool, fromBool)
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
preErrorCheck :: (Ptr (Ptr a) -> IO b) -> IO b
preErrorCheck = with nullPtr

marshalBool' :: Maybe Bool -> CInt
marshalBool' Nothing = -1
marshalBool' (Just x) = fromBool x

unmarshalBool' :: CInt -> Maybe Bool
unmarshalBool' x = if x == -1 then Nothing else Just $ toBool x

{#fun pure qlNullInteger as nullInteger {} -> `Int' #}

{#fun pure qlNullReal as nullReal {} -> `Double' #}

{#fun pure qlEpsilon as epsilon {} -> `Double' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
