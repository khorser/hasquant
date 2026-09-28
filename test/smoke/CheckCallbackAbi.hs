{-# LANGUAGE ForeignFunctionInterface #-}
-- Base-only probe: no QuantLib, hasquant, or observer graph participates.
import Control.Exception (bracket)
import Control.Monad (unless)
import Foreign
import Foreign.C.Types

type Apply = Ptr CDouble -> CUInt -> CDouble -> CDouble -> Ptr CDouble -> IO ()
type Direction = Ptr CDouble -> CUInt -> CUInt -> CDouble -> CDouble -> Ptr CDouble -> IO ()
type Solve = Ptr CDouble -> CUInt -> CUInt -> CDouble -> CDouble -> CDouble -> Ptr CDouble -> IO ()
type Step = Ptr CDouble -> CUInt -> CDouble -> Ptr CDouble -> IO ()
type Record = Ptr () -> IO (Ptr ())
foreign import ccall "wrapper" wrapApply :: Apply -> IO (FunPtr Apply)
foreign import ccall "wrapper" wrapDirection :: Direction -> IO (FunPtr Direction)
foreign import ccall "wrapper" wrapSolve :: Solve -> IO (FunPtr Solve)
foreign import ccall "wrapper" wrapStep :: Step -> IO (FunPtr Step)
foreign import ccall "wrapper" wrapRecord :: Record -> IO (FunPtr Record)
foreign import ccall safe "probeCallbacks" probe :: FunPtr Apply -> FunPtr Direction -> FunPtr Solve -> FunPtr Step -> FunPtr Record -> IO CInt
foreign import ccall unsafe "probeFields" fields :: Ptr () -> Ptr CDouble -> Ptr CUInt -> Ptr (Ptr CDouble) -> Ptr (Ptr CDouble) -> IO ()

main :: IO ()
main = do
  let output :: Solve
      output xs n d s t1 t2 out = do
        values <- peekArray (fromIntegral n) xs
        pokeArray out (map (+ (fromIntegral d + s + 2*t1 + 3*t2 - 2.25)) values)
      apply xs n = output xs n 0 0
      direction xs n d = output xs n d 0
      step xs n t = output xs n 0 0 t 0
      record p = allocaArray 3 $ \vs -> allocaArray 2 $ \ns -> alloca $ \ip -> alloca $ \op -> do
        fields p vs ns ip op
        s <- peekElemOff vs 0
        t1 <- peekElemOff vs 1
        t2 <- peekElemOff vs 2
        n <- peekElemOff ns 0
        d <- peekElemOff ns 1
        xs <- peek ip
        out <- peek op
        output xs n d s t1 t2 out
        pure nullPtr
  result <- bracket (wrapApply apply) freeHaskellFunPtr $ \a ->
    bracket (wrapDirection direction) freeHaskellFunPtr $ \d ->
    bracket (wrapSolve output) freeHaskellFunPtr $ \s ->
    bracket (wrapStep step) freeHaskellFunPtr $ \t ->
    bracket (wrapRecord record) freeHaskellFunPtr $ probe a d s t
  unless (result == 0) (error ("Callback ABI probe failed at stage " ++ show result))
  putStrLn "Mixed-argument and record callback ABIs: OK (1000 repetitions)"
