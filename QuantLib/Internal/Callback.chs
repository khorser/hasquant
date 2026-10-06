module QuantLib.Internal.Callback
  ( Callback, CallbackArgs(..), withCallback, withCallbackPtr, withScalarCallback ) where

import Control.Exception (SomeException, catch, mask, onException)
import Foreign.C.Types (CDouble)
import Foreign.Ptr (Ptr, FunPtr, nullPtr, freeHaskellFunPtr)
import Foreign.ForeignPtr (ForeignPtr, FinalizerPtr, newForeignPtr, withForeignPtr)
import Foreign.StablePtr (StablePtr, newStablePtr, castStablePtrToPtr)
import Foreign.Storable (poke)
import QuantLib.Internal (preErrorCheck, errorCheck)

#include "qlTypesC2HS.h"
#include "qlCallback.h"

newtype Callback = Callback (ForeignPtr ())
type CallbackFun = Ptr () -> IO (Ptr ())
data CallbackArgs = CallbackArgs
  { callbackInput :: Ptr CDouble
  , callbackOutput :: Ptr CDouble
  , callbackSize :: Int
  , callbackInput2 :: Ptr CDouble
  , callbackSize2 :: Int
  , callbackOutputSize :: Int
  , callbackDirection :: Int
  , callbackScalar :: Double
  , callbackTime1 :: Double
  , callbackTime2 :: Double
  }

foreign import ccall "wrapper" wrapCallback :: CallbackFun -> IO (FunPtr CallbackFun)
foreign import ccall "&hs_free_fun_ptr" releaseFun :: FunPtr (FunPtr CallbackFun -> IO ())
foreign import ccall "&hs_free_stable_ptr" releaseStable :: FunPtr (StablePtr SomeException -> IO ())
foreign import ccall safe "ql.h qlNewCallback" newCallback
  :: FunPtr CallbackFun -> FunPtr (FunPtr CallbackFun -> IO ())
  -> FunPtr (StablePtr SomeException -> IO ()) -> Ptr (Ptr ()) -> IO (Ptr ())
foreign import ccall safe "ql.h qlFreeCallback" freeCallback :: Ptr () -> IO ()

foreign import ccall "&qlFreeCallback" callbackFinalizer :: FinalizerPtr ()

withCallbackPtr :: Callback -> (Ptr () -> IO a) -> IO a
withCallbackPtr (Callback p) = withForeignPtr p

peekArgs :: Ptr () -> IO CallbackArgs
peekArgs p = CallbackArgs
  <$> {#get QlCallbackArgs->input#} p
  <*> {#get QlCallbackArgs->output#} p
  <*> (fromIntegral <$> {#get QlCallbackArgs->size#} p)
  <*> {#get QlCallbackArgs->input2#} p
  <*> (fromIntegral <$> {#get QlCallbackArgs->size2#} p)
  <*> (fromIntegral <$> {#get QlCallbackArgs->outputSize#} p)
  <*> (fromIntegral <$> {#get QlCallbackArgs->direction#} p)
  <*> (realToFrac <$> {#get QlCallbackArgs->s#} p)
  <*> (realToFrac <$> {#get QlCallbackArgs->t1#} p)
  <*> (realToFrac <$> {#get QlCallbackArgs->t2#} p)

withCallback :: (CallbackArgs -> IO ()) -> (Callback -> IO a) -> IO a
withCallback action use = mask $ \restore -> do
  fp <- wrapCallback call
  owner <- (preErrorCheck $ \errorPtr -> do
    result <- newCallback fp releaseFun releaseStable errorPtr
    errorCheck errorPtr
    pure result) `onException` freeHaskellFunPtr fp
  managed <- newForeignPtr callbackFinalizer owner `onException` freeCallback owner
  restore (use (Callback managed))
  where
    call p = mask $ \restore ->
      (restore (peekArgs p >>= action) >> pure nullPtr) `catch` saveException
    saveException :: SomeException -> IO (Ptr ())
    saveException = fmap castStablePtrToPtr . newStablePtr

withScalarCallback :: (CallbackArgs -> IO Double) -> (Callback -> IO a) -> IO a
withScalarCallback action = withCallback $ \args ->
  action args >>= poke (callbackOutput args) . realToFrac
