-- | The hspec test's own HestonSLV body, run through hasquant, outside hspec.
--
-- Third rung of the Windows ladder: @hestonslv-probe.cpp@ (plain C++) and
-- @HestonSLVProbe.hs@ (the same C++ under the GHC RTS) both pass on Windows while
-- @QuantLib.Spec.PricingEngine@'s \"builds MC\/FDM Heston-SLV models\" throws there. If
-- this one throws, the cause is in hasquant's own path -- shim marshalling, or something
-- its dylib does to the process -- rather than in libQuantLib or the RTS; if it passes,
-- the trigger is something else in the suite's (randomized) order, not this call.
--
-- Linked against the probe object purely for 'hsprobe_fpState', so its FP dumps line up
-- with the other two binaries'. Built by the \"Windows HestonSLV probe\" workflow when
-- its @hasquant@ input is set; locally it is the usual smoke-test invocation:
--
-- > cabal build lib:hasquant
-- > cabal exec -- ghc -package hasquant tools/debug/HestonSLVHasquant.hs hsprobe.o \
-- >   -o /tmp/hqprobe -outputdir /tmp/hqprobe_build
module Main(main) where

import Control.Exception(SomeException, try)
import Foreign.C.String(CString, withCString)
import System.IO(BufferMode(LineBuffering), hSetBuffering, stdout)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.TermStructure.Volatility
import QuantLib.Process
import QuantLib.Model
import QuantLib.Math(SobolDirectionIntegers(..), FdmScheme(..))

foreign import ccall safe "hsprobe_fpState" c_fpState :: CString -> IO ()

fpState :: String -> IO ()
fpState label = withCString label c_fpState

main :: IO ()
main = do
  hSetBuffering stdout LineBuffering
  putStrLn "== E: the hspec test body, through hasquant"
  fpState "hasquant driver startup"
  r <- try body :: IO (Either SomeException ())
  case r of
    Left ex -> putStrLn ("  THREW: " ++ show ex)
    Right () -> putStrLn "  completed"
  fpState "after hasquant driver"

body :: IO ()
body = Settings.keepingSettings' $ do
  let today = 5 `march` 2016
  Settings.setEvaluationDate (Just today)
  dc <- dayCounter Actual365FixedStandard
  rQ <- simpleQuote 0.01
  qQ <- simpleQuote 0.02
  rTS <- flatForward today rQ dc Continuous Annual
  qTS <- flatForward today qQ dc Continuous Annual
  s0 <- simpleQuote 100.0
  localVolQ <- simpleQuote 0.3
  hp <- hestonProcess rTS (Just qTS) s0 0.09 1.0 0.06 0.4 (-0.75) HestonFullTruncation
  hm <- hestonModel hp
  end <- addPeriod today (1, Years)
  localVolTS <- localConstantVol today localVolQ dc
  factory <- sobolBrownianGeneratorFactory Diagonal 1234 JoeKuoD7
  mc <- hestonSLVMCModel localVolTS hm factory end 91 201 32768 [] 1.0
  mcLeverage <- hestonSLVMCLeverageFunction mc
  mcVol <- localVol mcLeverage end 100 True
  putStrLn ("  MC model built, leverage(end, 100) = " ++ show mcVol)
  slv <- hestonSLVProcess hp mcLeverage 1.0
  n <- factors slv
  putStrLn ("  SLV process factors = " ++ show n)
  fpState "after MC calibration"

  let fdmParams = HestonSLVFokkerPlanckFdmParams
        51 151 500 50 100.0 5 2 0.1 1.0e-4 10000
        1.0e-5 1.0e-5 2.5e-6 1.0 0.1 0.9 1.0e-5
        ZeroCorrelation Log ModifiedCraigSneyd
  fdm <- hestonSLVFDMModel localVolTS hm end fdmParams True [] 1.0
  fdmLeverage <- hestonSLVFDMLeverageFunction fdm
  fdmVol <- localVol fdmLeverage end 100 True
  putStrLn ("  FDM model built, leverage(end, 100) = " ++ show fdmVol)
