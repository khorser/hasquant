module QuantLib.Internal.Utils
  (
  -- exceptions
    signalError
  , handleExceptions
  -- object construction and access
  , Finalizable(..)
  , construct
  , NamedSingleton(..)
  , constructNamed
  , name
  , withObject
  , maybeWithObject
  , withAmounts
  , withObjects
  , withString2
  , getDynIntArray
  , getStaticIntArray
  -- re-exporting some popular system stuff
  , withCString
  , CInt(CInt), CDouble(CDouble), CUInt(CUInt)
  , CString
  , Ptr, FunPtr
  , castPtr, castFunPtr, castForeignPtr, withForeignPtr, newForeignPtr_
  , unsafePerformIO
  , Word
  , ForeignPtr
  )

where

import Control.Exception(throw)
import Data.Word(Word)

import Foreign.C.String
import Foreign.C.Types
import Foreign.ForeignPtr(ForeignPtr, newForeignPtr, withForeignPtr, castForeignPtr, newForeignPtr_)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(peekArray, withArrayLen)
import Foreign.Ptr(nullPtr, Ptr, FunPtr, castPtr, castFunPtr)
import Foreign.Storable(peek, poke)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Error(Error(Error))

foreign import ccall safe "ql.h qlFreeString"
  c_freeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts"
  c_freeInts :: Ptr CInt -> IO ()

signalError :: String -> a
signalError = throw . Error

withObject :: ForeignPtr a -> (Ptr a -> IO b) -> IO b
withObject = withForeignPtr

maybeWithObject :: Maybe (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
maybeWithObject (Just o) f = withObject o f
maybeWithObject Nothing f  = f nullPtr

withObjects :: [ForeignPtr a] -> (CUInt -> Ptr (Ptr a) -> IO b) -> IO b
-- XXX rewrite using folds?
withObjects objs fn = go objs []
  where go [] ps     = withArrayLen ps (\n p -> fn (fromIntegral n) p)
        go (o:os) ps = withForeignPtr o
                        (\p -> go os (ps ++ [p]))

withAmounts :: [Double] -> (CUInt -> Ptr CDouble -> IO b) -> IO b
withAmounts amounts f = withArrayLen
                        (map realToFrac amounts)
                        (\n a -> f (fromIntegral n) a)

withString2 :: String -> String -> (CString -> CString -> IO b) -> IO b
withString2 s1 s2 f = withCString s1 (withCString s2 . f)

getDynIntArray :: (Ptr CInt -> IO (Ptr CInt)) -> IO [CInt]
getDynIntArray = getIntArray c_freeInts

getStaticIntArray :: (Ptr CInt -> IO (Ptr CInt)) -> IO [CInt]
getStaticIntArray = getIntArray (const $ return ())

-- get a function that returns an array of ints, the number of items
-- is returned via the first argument
getIntArray :: (Ptr CInt -> IO ()) -> (Ptr CInt -> IO (Ptr CInt)) -> IO [CInt]
getIntArray fin f =
  alloca
  (\pcnt -> do array <- f pcnt
               count <- peek pcnt
               ints <- peekArray (fromIntegral count) array
               fin array
               return ints)

handleExceptions :: (Ptr CString -> IO a) -> IO a
handleExceptions f =
   alloca $
     \errptr ->
     do poke errptr nullPtr
        r <- f errptr
        msg <- peek errptr
        if msg /= nullPtr 
          then do err <- peekCString msg
                  c_freeString msg
                  signalError err
          else return r

class Finalizable a where
  finalize :: FunPtr (Ptr a -> IO ())

-- |Run a C function returning a new object that needs a finalizer.
-- The function might signal an error
construct :: Finalizable a => (Ptr CString -> IO (Ptr a)) -> IO (ForeignPtr a)
construct f = handleExceptions f >>= newForeignPtr finalize

class Finalizable a => NamedSingleton a where
  c_construct :: CString -> Ptr CString -> IO (Ptr a)
  c_name :: Ptr a -> IO CString

-- XXX ???Create non-finalizable objects and then we won't have to use IO monad
constructNamed :: NamedSingleton a => String -> IO (ForeignPtr a)
constructNamed n = withCString n $ construct . c_construct

name :: NamedSingleton a => ForeignPtr a -> String
name c = unsafePerformIO
          $ withForeignPtr c
              (\cc -> do n <- c_name cc
                         str <- peekCString n
                         c_freeString n
                         return str)
