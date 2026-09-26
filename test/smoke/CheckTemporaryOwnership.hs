{-# LANGUAGE ForeignFunctionInterface, TypeFamilies #-}
-- Compile against Internal.Type from source and MarshallingFixture.cpp.
import Control.Concurrent (forkIO, newEmptyMVar, putMVar, takeMVar, throwTo)
import Control.Exception (SomeException, AsyncException(UserInterrupt), MaskingState(Unmasked), getMaskingState, try, throwIO)
import Control.Monad (unless)
import Foreign.C.Types (CInt(..))
import Foreign.ForeignPtr (FinalizerPtr)
import Foreign.Ptr (Ptr)
import qualified QuantLib.Internal.Type as T

data TestHandle
foreign import ccall "testNewElement" make :: CInt -> IO (Ptr TestHandle)
foreign import ccall "&testFreeElement" finalizer :: FinalizerPtr TestHandle
foreign import ccall "testLiveElements" live :: IO CInt
instance T.Finalizable TestHandle where finalize = finalizer
instance T.Upcastable TestHandle where
  type Base TestHandle = TestHandle
  upcast _ = make 0

check :: Bool -> IO ()
check ok = unless ok (error "temporary handle ownership check failed")

nested :: IO a -> IO a
nested action = T.withConstructed (make 0) $ \a -> T.withUpcast a $ \b -> T.withUpcast b $ \_ -> do
  live >>= check . (== 3)
  getMaskingState >>= check . (== Unmasked)
  action

main :: IO ()
main = do
  nested (pure ())
  live >>= check . (== 0)
  result <- try (nested (throwIO UserInterrupt)) :: IO (Either SomeException ())
  case result of
    Left _ -> pure ()
    Right () -> error "expected exception"
  live >>= check . (== 0)
  ready <- newEmptyMVar
  block <- newEmptyMVar
  done <- newEmptyMVar
  tid <- forkIO $ do
    r <- try (nested (putMVar ready () >> takeMVar block))
    putMVar done (r :: Either SomeException ())
  takeMVar ready
  throwTo tid UserInterrupt
  cancelled <- takeMVar done
  case cancelled of
    Left _ -> pure ()
    Right () -> error "expected cancellation"
  live >>= check . (== 0)
  putStrLn "Temporary ownership: OK"
