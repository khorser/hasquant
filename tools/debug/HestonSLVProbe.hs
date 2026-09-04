-- | GHC-hosted twin of @tools\/debug\/hestonslv-probe.cpp@.
--
-- The standalone C++ probe passes on Windows -- every @invcdf@ returns and
-- 'HestonSLVFDMModel' builds -- while the same libQuantLib call throws under the
-- hasquant test suite there. Since both link the same QuantLib, the difference has to
-- be process state rather than arithmetic, so this runs the probe's own sections from
-- inside a GHC process and dumps the x86 FP environment around them. A MXCSR or x87
-- control word here that differs from the standalone run's (notably FTZ\/DAZ, given the
-- failure's subnormal 2.2e-312 "best guess") is the answer.
--
-- Deliberately depends on @base@ only, and is built without @-threaded@ to match
-- @hasquant_test@: the point is to isolate the RTS, so pulling in hasquant would
-- confound it. If this run also passes, the RTS alone is not the cause and the next
-- step is the same driver linked against hasquant, calling 'hestonSLVFDMModel'.
module Main(main) where

import Foreign.C.String(CString, withCString)
import System.IO(BufferMode(LineBuffering), hSetBuffering, stdout)

foreign import ccall safe "hsprobe_environment" c_environment :: IO ()
foreign import ccall safe "hsprobe_staticInitReport" c_staticInitReport :: IO ()
foreign import ccall safe "hsprobe_fpState" c_fpState :: CString -> IO ()
foreign import ccall safe "hsprobe_longDouble" c_longDouble :: IO ()
foreign import ccall safe "hsprobe_setPC64" c_setPC64 :: IO ()
foreign import ccall safe "hsprobe_noPromote" c_noPromote :: IO ()
foreign import ccall safe "hsprobe_sweep" c_sweep :: IO ()
foreign import ccall safe "hsprobe_meshGrid" c_meshGrid :: IO ()
foreign import ccall safe "hsprobe_buildModel" c_buildModel :: IO ()
foreign import ccall safe "hsprobe_mcThenFdm" c_mcThenFdm :: IO ()

fpState :: String -> IO ()
fpState label = withCString label c_fpState

main :: IO ()
main = do
  hSetBuffering stdout LineBuffering
  c_environment
  c_staticInitReport
  fpState "GHC RTS startup"
  c_longDouble
  c_noPromote
  c_sweep
  c_meshGrid
  fpState "before model construction"
  c_buildModel
  fpState "after model construction"
  c_mcThenFdm

  -- The candidate fix: restore the 64-bit x87 precision a mingw-linked binary starts
  -- with, then replay everything. All of this passing is what makes it the fix.
  c_setPC64
  fpState "after restoring PC=64"
  c_longDouble
  c_sweep
  c_meshGrid
  c_buildModel
