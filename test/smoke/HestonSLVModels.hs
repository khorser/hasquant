module Main(main) where

import Control.Monad(when)
import qualified Data.Vector.Storable as V
import QuantLib.InterestRate(Compounding(Continuous))
import QuantLib.Math(FdmScheme(ModifiedCraigSneyd), SobolDirectionIntegers(JoeKuoD7), realMatrixColumns, realMatrixData, realMatrixRows)
import QuantLib.Model
import QuantLib.Process(HestonProcessDiscretization(HestonFullTruncation), factors, hestonProcess, hestonSLVProcess)
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import QuantLib.TermStructure.Yield(flatForward)
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.Time.Date(addPeriod, march)
import QuantLib.Time.Schedule(DayCounterConstructor(Actual365FixedStandard), Frequency(Annual), TimeUnit(Years), dayCounter)

main :: IO ()
main = Settings.keepingSettings' $ do
  let ref = 5 `march` 2016
  Settings.setEvaluationDate (Just ref)
  dc <- dayCounter Actual365FixedStandard
  r <- Quote.simpleQuote 0.01
  q <- Quote.simpleQuote 0.02
  rts <- flatForward ref r dc Continuous Annual
  qts <- flatForward ref q dc Continuous Annual
  spot <- Quote.simpleQuote 100
  localVolQuote <- Quote.simpleQuote 0.3
  hp <- hestonProcess rts (Just qts) spot 0.09 1.0 0.06 0.4 (-0.75) HestonFullTruncation
  hm <- hestonModel hp
  end <- addPeriod ref (1, Years)
  local <- Vol.localConstantVol ref localVolQuote dc
  factory <- sobolBrownianGeneratorFactory Diagonal 1234 JoeKuoD7
  mc <- hestonSLVMCModel local hm factory end 91 201 32768 [] 1.0
  mcLeverage <- hestonSLVMCLeverageFunction mc
  slv <- hestonSLVProcess hp mcLeverage 1.0
  factors slv >>= \n -> when (n /= 2) $ error "HestonSLVProcess does not expose two factors"
  let fdmParams = HestonSLVFokkerPlanckFdmParams
        51 151 500 50 100.0 5 2 0.1 1.0e-4 10000
        1.0e-5 1.0e-5 2.5e-6 1.0 0.1 0.9 1.0e-5
        ZeroCorrelation Log ModifiedCraigSneyd
  fdm <- hestonSLVFDMModel local hm end fdmParams True [] 1.0
  fdmLeverage <- hestonSLVFDMLeverageFunction fdm
  fdmVol <- Vol.localVol fdmLeverage end 100 True
  when (not (isFinitePositive fdmVol)) $ error "FDM leverage function is not positive and finite"
  logs <- hestonSLVFDMLogEntries fdm
  case logs of
    [] -> error "FDM logging produced no diagnostic snapshots"
    entry : _ -> do
      let density = hestonSLVLogDensity entry
      when (realMatrixRows density /= fromIntegral (V.length (hestonSLVLogVarianceCoordinates entry))
         || realMatrixColumns density /= fromIntegral (V.length (hestonSLVLogSpotCoordinates entry))
         || V.length (realMatrixData density) /= V.length (hestonSLVLogVarianceCoordinates entry) * V.length (hestonSLVLogSpotCoordinates entry))
        $ error "FDM diagnostic density shape does not match its axes"
  -- logging = False must return [] rather than crash: hestonSLVFDMLogEntriesSize is then 0,
  -- and enumerating up to it as a Word previously underflowed to maxBound (see AGENTS.md).
  fdmNoLog <- hestonSLVFDMModel local hm end fdmParams False [] 1.0
  noLogs <- hestonSLVFDMLogEntries fdmNoLog
  when (not (null noLogs)) $ error "FDM logging=False unexpectedly produced diagnostic snapshots"
  putStrLn "Heston SLV MC/FDM models: OK"

isFinitePositive :: Double -> Bool
isFinitePositive x = x > 0 && not (isNaN x || isInfinite x)
