{-# LANGUAGE ForeignFunctionInterface #-}
-- Compile with MarshallingFixture.cpp and the library; internal helpers are compiled from source.
import Control.Concurrent (forkIO, newEmptyMVar, putMVar, takeMVar, throwTo)
import Control.Exception (SomeException, AsyncException(UserInterrupt), try, throwIO)
import Control.Monad (unless, void)
import Data.IORef
import qualified Data.Vector.Storable as V
import Foreign.C.Types (CInt(..), CUInt(..), CDouble(..))
import Foreign.C.String (CString)
import Foreign.Concurrent (newForeignPtr)
import Foreign.ForeignPtr (finalizeForeignPtr)
import Foreign.Marshal.Alloc (free)
import Foreign.Marshal.Array (newArray)
import Foreign.Ptr (Ptr)
import Foreign.Storable (poke, peek)
import QuantLib.Internal

foreign import ccall "testElements" elements :: Ptr CUInt -> Ptr (Ptr (Ptr CInt)) -> IO ()
foreign import ccall "testFreeElement" freeElement :: Ptr CInt -> IO ()
foreign import ccall "testLiveElements" liveElements :: IO CInt
foreign import ccall "testDoubles" doubles :: Ptr CUInt -> Ptr (Ptr CDouble) -> IO ()
foreign import ccall "testStrings" strings :: Ptr CUInt -> Ptr (Ptr CString) -> IO ()

check :: Bool -> IO ()
check ok = unless ok (error "result marshalling ownership check failed")

fails :: IO a -> IO ()
fails action = do
  result <- try (void action) :: IO (Either SomeException ())
  case result of
    Left _ -> pure ()
    Right () -> error "expected conversion failure"

main :: IO ()
main = do
  xs <- preDoubleArray $ \(n, p) -> doubles n p >> peekDoubleArray n p
  check (xs == [0, 1, 2])
  v <- preDoubleArray $ \(n, p) -> doubles n p >> peekRealVector n p
  check (V.toList v == [0, 1, 2])
  let (storage, _, _) = V.unsafeToForeignPtr v
  finalizeForeignPtr storage
  ss <- preCStringArray $ \(n, p) -> strings n p >> peekCStringArray n p
  check (ss == ["alpha", "beta"])
  freed <- newIORef (0 :: Int)
  let release _ p = modifyIORef' freed (+1) >> free p
      produce (n, p) = newArray ([1, 2, 3] :: [CInt]) >>= \a -> poke n 3 >> poke p a
      convert x = if x == 2 then throwIO UserInterrupt else pure x
  fails $ preArrayWith release $ \(n, p) -> do
    produce (n, p)
    peekStructArray convert release n p
  readIORef freed >>= check . (== 1)
  -- Both outputs exist before c2hs starts converting the first one.
  fails $ preArrayWith release $ \a@(n, p) -> preArrayWith release $ \b -> do
    produce a
    produce b
    peekStructArray convert release n p
  readIORef freed >>= check . (== 3)
  adopted <- newIORef []
  let adopt p = do
        x <- peek p
        if x == 1 then throwIO UserInterrupt else do
          fp <- newForeignPtr p (freeElement p)
          modifyIORef' adopted (fp :)
          pure fp
  fails $ prePtrArray freeElement $ \(n, p) -> elements n p >> peekPtrArray freeElement adopt n p
  liveElements >>= check . (== 1)
  readIORef adopted >>= mapM_ finalizeForeignPtr
  liveElements >>= check . (== 0)
  -- Cancellation after production must release outputs even before their first peek.
  ready <- newEmptyMVar
  block <- newEmptyMVar
  done <- newEmptyMVar
  tid <- forkIO $ do
    result <- try $ preArrayWith release $ \slots -> do
      produce slots
      putMVar ready ()
      takeMVar block
    putMVar done (result :: Either SomeException ())
  takeMVar ready
  throwTo tid UserInterrupt
  cancelled <- takeMVar done
  case cancelled of
    Left _ -> pure ()
    Right () -> error "expected asynchronous cancellation"
  readIORef freed >>= check . (== 4)
  putStrLn "Result marshalling: OK"
