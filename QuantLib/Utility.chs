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
  , unmarshalDynamicString
  , unmarshalEnumByRef
  , minEnumByRef
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.Marshal.Utils(with, toBool, fromBool)
import Foreign.Storable(peek, poke, Storable)
import Foreign.Marshal.Alloc(alloca)

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

throughOne :: (Monad m) => a -> (a -> m b) -> (a -> m d) -> m b
throughOne x f g = do {v <- f x; _ <- g x; return v}

unmarshalDynamicString :: CString -> IO String
unmarshalDynamicString x = throughOne x peekCString freeString

{#fun pure qlNullInteger as nullInteger {} -> `Int' #}

{#fun pure qlNullReal as nullReal {} -> `Double' #}

{#fun pure qlEpsilon as epsilon {} -> `Double' #}

unmarshalEnumByRef :: (Enum a) => Ptr CInt -> IO a
unmarshalEnumByRef x = peek x >>= return . toEnum . fromIntegral

-- initialize pointer to a enum with a valid value before passing it to the function
minEnumByRef :: (Storable a, Bounded a) => (Ptr a -> IO b) -> IO b
minEnumByRef f = alloca $ \x -> poke x minBound >> f x

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
