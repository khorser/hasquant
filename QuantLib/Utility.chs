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

  , fromMaybeBool
  , toMaybeBool
  , peekDynString
  , peekEnum
  , preEnum
  , preArray
  , peekIntArray
  , withMaybeObject
  , withEnumArray
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import Foreign.Ptr(Ptr, nullPtr, castPtr)
import Foreign.ForeignPtr(withForeignPtr, ForeignPtr)
import Foreign.Marshal.Array(peekArray, withArray)
import Foreign.Marshal.Utils(with, toBool, fromBool)
import Foreign.Storable(peek, Storable)

import Control.Exception(throwIO)
import Control.Monad(when)
import QuantLib.Type

#include "qlTypesC2HS.h"
#include "ql.h"

{#fun pure qlVersion as version {} -> `String' #}

{#fun pure qlBoostVersion as boostVersion {} -> `String' #}

errorCheck :: Ptr CString -> IO ()
errorCheck p = do
  a <- peek p
  when
    (a /= nullPtr)
    (do
      e <- peekCString a
      c_freeString a
      throwIO $ CPlusPlusException e)

-- like alloca but initializes the allocated pointer with zero
preErrorCheck :: (Ptr (Ptr a) -> IO b) -> IO b
preErrorCheck = with nullPtr

fromMaybeBool :: Maybe Bool -> CInt
fromMaybeBool Nothing = -1
fromMaybeBool (Just x) = fromBool x

toMaybeBool :: CInt -> Maybe Bool
toMaybeBool x = if x == -1 then Nothing else Just $ toBool x

throughOne :: (Monad m) => a -> (a -> m b) -> (a -> m d) -> m b
throughOne x f g = do {v <- f x; _ <- g x; return v}

peekDynString :: CString -> IO String
peekDynString x = throughOne x peekCString c_freeString

{#fun pure qlNullInteger as nullInteger {} -> `Int' #}

{#fun pure qlNullReal as nullReal {} -> `Double' #}

{#fun pure qlEpsilon as epsilon {} -> `Double' #}

peekEnum :: (Enum a) => Ptr CInt -> IO a
peekEnum x = peek x >>= return . toEnum . fromIntegral

-- initialize pointer to a enum with a valid value before passing it to the function
preEnum :: (Storable a, Bounded a) => (Ptr a -> IO b) -> IO b
preEnum = with minBound

preNum :: (Storable a, Num a) => (Ptr a -> IO b) -> IO b
preNum = with 0

foreign import ccall safe "ql.h qlFreeString" c_freeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts" c_freeInts :: Ptr CInt -> IO ()
foreign import ccall safe "ql.h qlFreeDoubles" c_freeDoubles :: Ptr CDouble -> IO ()
foreign import ccall safe "ql.h qlFreePointerArray" c_freePointerArray :: Ptr (Ptr ()) -> IO ()

withEnumArray :: (Enum a) => [a] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withEnumArray x f = withArray (map (fromIntegral . fromEnum) x) (\xs -> f (fromIntegral $ length x, xs))

preArray :: ((Ptr CUInt, Ptr (Ptr a)) -> IO b) -> IO b
preArray f = with 0 $
  \x -> with nullPtr $
    \y -> f (x, y)

peekIntArray :: (CInt -> b) -> Ptr CUInt -> Ptr (Ptr CInt) -> IO [b]
peekIntArray f pl pp = do
  l <- peek pl
  p <- peek pp
  a <- peekArray (fromIntegral l) p
  c_freeInts p
  return $ map f a

withMaybeObject :: (ForeignObject a) => Maybe a -> (Ptr a -> IO b) -> IO b
withMaybeObject Nothing f = f nullPtr
withMaybeObject (Just x) f = withObject x f

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
