{-# LANGUAGE GADTs, RankNTypes #-}
{- from http://lpaste.net/11191
Paste:#11191
Author(s):Cale
Language:Haskell
Channel:-
Created:2009-10-27 12:38:25 UTC
-}

import Control.Applicative
import Control.Monad
import Data.IORef
import System.IO.Unsafe

newtype STRef s a = STRef (IORef a)

data ST s a where
  ReturnST   :: a -> ST s a
  BindST     :: ST s a -> (a -> ST s b) -> ST s b
  NewSTRef   :: a -> ST s (STRef s a)
  ReadSTRef  :: STRef s a -> ST s a
  WriteSTRef :: STRef s a -> a -> ST s ()

newSTRef = NewSTRef
readSTRef = ReadSTRef
writeSTRef = WriteSTRef

execST :: ST s a -> IO a
execST (ReturnST v) = return v
execST (BindST x f) = execST x >>= \v -> execST (f v)
execST (NewSTRef v) = fmap STRef (newIORef v)
execST (ReadSTRef (STRef r)) = readIORef r
execST (WriteSTRef (STRef r) v) = writeIORef r v

runST :: (forall s. ST s a) -> a
runST x = unsafePerformIO (execST x)

instance Functor (ST s) where
  fmap = liftM

instance Applicative (ST s) where
  pure = return
  (<*>) = ap

instance Monad (ST s) where
  return = ReturnST
  x >>= f = BindST x f
