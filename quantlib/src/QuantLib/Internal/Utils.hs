{-# LANGUAGE FlexibleContexts #-}
{-# OPTIONS_GHC -fno-cse -fno-full-laziness #-} -- for unsafePerformIO
module QuantLib.Internal.Utils
  (
    unmarshalExceptions
  , getExceptions
  , purifyExceptions
  , mkQLE
  , runQLE

  , upcast
  , construct
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
  , getIntPair
  , getString
  , withArrayULen
  , withArrayULenT
  , withArrayULenTIO

  -- re-exporting some popular stuff
  , throwIO
  , withCString
  )

where

import Control.Error
import Control.Exception(throwIO, catches, Handler(Handler))
import Control.Monad(join, liftM)
import Data.Functor((<$>))

import Foreign.C.String(peekCString, withCString)
import Foreign.C.Types
import Foreign.ForeignPtr(newForeignPtr, withForeignPtr)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(peekArray, withArrayLen)
import Foreign.Marshal.Utils(with, maybeWith, withMany)
import Foreign.Ptr(nullPtr)
import Foreign.Storable(peek)

import System.IO.Unsafe(unsafePerformIO)
import QuantLib.Internal.Types

withArrayULen :: Storable a => [a] -> (CUInt -> Ptr a -> IO b) -> IO b
withArrayULen x f = withArrayLen x (f . fromIntegral)

withArrayULenT :: Storable b => (a -> b) -> [a] -> (CUInt -> Ptr b -> IO c) -> IO c
withArrayULenT t x = withArrayULen (map t x)

withArrayULenTIO :: Storable b => (a -> IO b) -> [a] -> (CUInt -> Ptr b -> IO c) -> IO c
withArrayULenTIO t x f = mapM t x >>= (`withArrayULen` f)

withObject :: Object s a -> (Ptr a -> IO b) -> IO b
withObject = withForeignPtr . ptr

maybeWithObject :: Maybe (Object s a) -> (Ptr a -> IO b) -> IO b
maybeWithObject = maybeWith withObject

withObjects :: [Object s a] -> (CUInt -> Ptr (Ptr a) -> IO b) -> IO b
withObjects xs f = withMany withObject xs (`withArrayULen` f)

withDoubles :: [Double] -> (CUInt -> Ptr CDouble -> IO b) -> IO b
withDoubles = withArrayULenT realToFrac

foreign import ccall safe "ql.h qlFreeString"
  c_freeString :: CString -> IO ()

getString :: IO CString -> IO String
getString x = do
  s <- x
  str <- peekCString s
  c_freeString s
  return str

-- get a function that returns an array of a's
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
getObjectArrayX :: (CArrayable (Ptr a), Finalizable a) => Object s b
  -> (Ptr b -> Ptr CUInt -> Ptr CString -> IO (Ptr (Ptr a)))
  -> IO [Object s a]
getObjectArrayX o f = withObject o (getArrayX . f) >>= mapM (liftM Object . newForeignPtr finalize)

-- invoke a function producing an integral pair,
-- first one returning, the second returning by pointer
getIntPair :: (Integral a1, Integral a2, Storable a2, Integral b1, Integral b2)
  => (Ptr a2 -> Ptr CString -> IO a1) -> IO (b1, b2)
getIntPair f =
  alloca $
  \second -> do
    first <- unmarshalExceptions (f second)
    second' <- peek second
    return (fromIntegral first, fromIntegral second')

unmarshalExceptions :: (Ptr CString -> IO a) -> IO a
unmarshalExceptions f =
   with nullPtr $
     \errptr -> do
     r <- f errptr
     msg <- peek errptr
     if msg /= nullPtr
       then do
         e <- peekCString msg
         c_freeString msg
         throwIO $ CPlusPlusException e
       else return r

getExceptions :: IO a -> IO (Either QLError a)
getExceptions f = join <$> catchSync (catchQL f)
  where
    catchQL :: IO a -> IO (Either QLError a)
    catchQL g = (Right <$> g)
      `catches` [Handler (return . Left), -- catch QLError
             Handler (return . Left . IoException)] -- wrap IOException

    catchSync :: IO a -> IO (Either QLError a)
    catchSync g = fmapL SyncException <$> runEitherT (syncIO g)

mkQLE :: IO a -> QLE s a
mkQLE = EitherT . QL . getExceptions

runQLE :: QLE s a -> IO a
runQLE f = do
  rr <- runQL $ runEitherT f
  either throwIO return rr

purifyExceptions :: IO a -> Either QLError a
{-# NOINLINE purifyExceptions #-}
purifyExceptions = unsafePerformIO . getExceptions

-- |Run a C function returning a new object that needs a finalizer.
-- The function might signal an error
construct :: Finalizable a => (Ptr CString -> IO (Ptr a)) -> IO (Object s a)
construct f = do
  o <- unmarshalExceptions f
  if o == nullPtr
    then throwIO NullPointerReturned
    else Object <$> newForeignPtr finalize o

constructNamed :: NamedSingleton a => String -> QLE s (Object s a)
constructNamed n = mkQLE $ withCString n $ construct . c_construct

name :: NamedSingleton a => Object s a -> String
{-# NOINLINE name #-}
name c = unsafePerformIO $
          withObject c $
            \cc -> do
              n <- c_name cc
              str <- peekCString n
              c_freeString n
              return str

upcast :: (Upcastable a b) => Object s a -> QLE s (Object s b)
upcast x = mkQLE $ withObject x c_upcast >>= liftM Object . newForeignPtr finalize

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
