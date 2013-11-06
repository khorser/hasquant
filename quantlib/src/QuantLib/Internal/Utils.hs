{-# LANGUAGE MultiParamTypeClasses,GeneralizedNewtypeDeriving,ScopedTypeVariables,FlexibleContexts,CPP #-}
module QuantLib.Internal.Utils
  (
    signalError
  , unmarshalExceptions
  , purifyExceptions

  , Finalizable(..)
  , Upcastable(..)
  , upcast
  , construct
  , NamedSingleton(..)
  , constructNamed
  , name
  , withObject
  , maybeWithObject
  , withDoubles
  , withObjects
  , getArray
  , buildArray
  , getArrayX
  , getObjectArrayX
  , getString
  , CStaticInt(..)
  , withArrayULen
  , withArrayULenT

  -- re-exporting some popular stuff
  , Word
  , withCString
  , CInt(CInt), CDouble(CDouble), CUInt(CUInt)
  , CString
  , Ptr, FunPtr
  , ForeignPtr
  )

where

#if __GLASGOW_HASKELL__ < 706
import Prelude hiding(catch)
#endif

import Control.Exception(throw, catch)
import Data.Functor((<$>))
import Data.Word(Word)

import Foreign.C.String
import Foreign.C.Types
import Foreign.ForeignPtr(ForeignPtr, newForeignPtr, withForeignPtr)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(peekArray, withArrayLen)
import Foreign.Marshal.Utils(with, maybeWith, withMany)
import Foreign.Ptr(nullPtr, Ptr, FunPtr, castPtr)
import Foreign.Storable(Storable(..), peek)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Error(Error(Error), message)

signalError :: String -> a
signalError = throw . Error

withArrayULen :: Storable a => [a] -> (CUInt -> Ptr a -> IO b) -> IO b
withArrayULen x f = withArrayLen x (f . fromIntegral)

withArrayULenT :: Storable b => (a -> b) -> [a] -> (CUInt -> Ptr b -> IO c) -> IO c
withArrayULenT t x = withArrayULen (map t x)

withObject :: ForeignPtr a -> (Ptr a -> IO b) -> IO b
withObject = withForeignPtr

maybeWithObject :: Maybe (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
maybeWithObject = maybeWith withObject

withObjects :: [ForeignPtr a] -> (CUInt -> Ptr (Ptr a) -> IO b) -> IO b
withObjects xs f = withMany withObject xs (`withArrayULen` f)

withDoubles :: [Double] -> (CUInt -> Ptr CDouble -> IO b) -> IO b
withDoubles = withArrayULenT realToFrac

getString :: IO CString -> IO String
getString x = do
  s <- x
  str <- peekCString s
  c_freeString s
  return str

newtype CStaticInt = CStaticInt{getStaticInt::CInt} deriving (Eq, Show, Storable)

class (Storable a) => CArrayable a where
  freeArray :: Ptr a -> IO ()

instance CArrayable CInt where
  freeArray = c_freeInts
instance CArrayable CDouble where
  freeArray = c_freeDoubles
instance CArrayable CStaticInt where
  freeArray = const $ return ()
instance CArrayable (Ptr a) where
  freeArray = c_freePointerArray . castPtr

foreign import ccall safe "ql.h qlFreeString"
  c_freeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts"
  c_freeInts :: Ptr CInt -> IO ()
foreign import ccall safe "ql.h qlFreeDoubles"
  c_freeDoubles :: Ptr CDouble -> IO ()
foreign import ccall safe "ql.h qlFreePointerArray"
  c_freePointerArray :: Ptr (Ptr ()) -> IO ()

-- get a function that returns an array of a
-- with the number of items returned via the first argument
getArray :: (CArrayable a) => (Ptr CUInt -> IO (Ptr a)) -> IO [a]
getArray f =
  alloca $
    \pcnt -> do
    array <- f pcnt
    count <- peek pcnt
    buildArray count array

-- getArray with error handling
-- TODO generalize getArray and getArrayX
-- TODO add Vectors
getArrayX :: (CArrayable a) => (Ptr CUInt -> Ptr CString -> IO (Ptr a)) -> IO [a]
getArrayX f =
  alloca $
  \pcnt -> do
    array <- unmarshalExceptions (f pcnt)
    count <- peek pcnt
    buildArray count array

buildArray :: (CArrayable a) => CUInt -> Ptr a -> IO [a]
buildArray n p = do
  x <- peekArray (fromIntegral n) p
  freeArray p
  return x

-- invoke object method returning a list of objects
getObjectArrayX :: (CArrayable (Ptr a), Finalizable a) => ForeignPtr b
  -> (Ptr b -> Ptr CUInt -> Ptr CString -> IO (Ptr (Ptr a)))
  -> IO [ForeignPtr a]
getObjectArrayX o f = withObject o (getArrayX . f) >>= mapM (newForeignPtr finalize)

unmarshalExceptions :: (Ptr CString -> IO a) -> IO a
unmarshalExceptions f =
   with nullPtr $
     \errptr -> do
     r <- f errptr
     msg <- peek errptr
     if msg /= nullPtr
       then do
         err <- peekCString msg
         c_freeString msg
         signalError err
       else return r

purifyExceptions :: IO a -> Either String a
purifyExceptions f = unsafePerformIO $
  catch (Right <$> f)
        (\(e :: Error) -> return $ Left (message e))


class Finalizable a where
  finalize :: FunPtr (Ptr a -> IO ())

-- |Run a C function returning a new object that needs a finalizer.
-- The function might signal an error
construct :: Finalizable a => (Ptr CString -> IO (Ptr a)) -> IO (ForeignPtr a)
construct f = do
  o <- unmarshalExceptions f
  if o == nullPtr
    then signalError "Foreign code did not signal an error but returned null pointer"
    else newForeignPtr finalize o

class Finalizable a => NamedSingleton a where
  c_construct :: CString -> Ptr CString -> IO (Ptr a)
  c_name :: Ptr a -> IO CString

-- XXX ???Create non-finalizable objects and then we won't have to use the IO monad
constructNamed :: NamedSingleton a => String -> IO (ForeignPtr a)
constructNamed n = withCString n $ construct . c_construct

name :: NamedSingleton a => ForeignPtr a -> String
name c = unsafePerformIO $
          withForeignPtr c
            (\cc -> do
              n <- c_name cc
              str <- peekCString n
              c_freeString n
              return str)

class (Finalizable a, Finalizable b) => Upcastable a b where
  c_upcast :: Ptr a -> IO (Ptr b)

upcast :: (Upcastable a b) => ForeignPtr a -> IO (ForeignPtr b)
upcast x = withObject x c_upcast >>= newForeignPtr finalize

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
