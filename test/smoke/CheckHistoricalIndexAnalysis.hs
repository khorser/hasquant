-- Smoke test: exercises historicalIndexAnalysis's generic Index path end-to-end against a
-- mix of an IborIndex and an EquityIndex in the same call -- the hspec suite only covers
-- the InterestRate-only historicalRatesAnalysis convenience wrapper, so this is the only
-- place that proves the underlying binding really accepts non-rate indexes, not just
-- InterestRateIndex ones erased to Index via asIndex. Also confirms valueAtRisk/
-- expectedShortfall reject a centile outside [0.9, 1.0) with a proper errorCheck exception.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckHistoricalIndexAnalysis.hs -o /tmp/checkhistoricalindexanalysis -outputdir /tmp/checkhistoricalindexanalysis_build && /tmp/checkhistoricalindexanalysis
import Control.Exception (SomeException, try)
import Control.Monad (forM_)

import QuantLib.Currency
import QuantLib.Index
import QuantLib.Index.Equity (equityIndex)
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule (TimeUnit(..))

import SmokeCheck (checkWith)

main :: IO ()
main = do
  cal <- calendar TARGET
  usd <- currency USD
  ibor <- IR.iborIndex (IR.Euribor (6, Months)) Nothing
  eq <- equityIndex "eqIndex" cal usd Nothing Nothing Nothing

  let startDate = 1 `january` 2021
      n = 24 :: Int
      fixingAt k = 100.0 + 5.0 * sin (fromIntegral (k :: Int))
      genDates :: Int -> Day -> IO [Day]
      genDates 0 d = return [d]
      genDates k d = (d :) <$> (advance cal d (1, Months) Following False >>= genDates (k - 1))

  d0 <- advance cal startDate (1, Days) Following False
  ds <- genDates n d0
  forM_ (zip [0 ..] ds) $ \(k, d) -> do
    addFixing ibor d (0.01 + 0.004 * sin (fromIntegral (k :: Int))) False
    addFixing eq d (fixingAt k) False

  ibor' <- asIndex ibor
  eq' <- asIndex eq
  hia <- historicalIndexAnalysis startDate (last ds) (1, Months) [ibor', eq']

  skipped <- historicalIndexAnalysisSkipped hia
  checkWith "no skipped dates for a fully-fixed mixed index list" "expected []" (null skipped)

  -- The char** spine this returns is the only one in cbits/ that used to escape trackAllocations
  -- tracing; the paired API still reaches it while preventing callers from separating messages
  -- from their dates.
  checkWith "skipped-date diagnostics are paired"
    "expected one message per skipped date" (all (not . null . snd) skipped)

  means <- historicalIndexAnalysisMean hia
  checkWith "mean has one entry per index" "expected length 2" (length means == 2)

  vars <- historicalIndexAnalysisValueAtRisk hia 0.9
  checkWith "valueAtRisk non-negative for both indexes" "expected all >= 0" (all (>= 0) vars)

  ess <- historicalIndexAnalysisExpectedShortfall hia 0.9
  checkWith "expectedShortfall non-negative for both indexes" "expected all >= 0" (all (>= 0) ess)

  badCentile <- try (historicalIndexAnalysisValueAtRisk hia 0.5) :: IO (Either SomeException [Double])
  case badCentile of
    Left _ -> checkWith "valueAtRisk rejects centile outside [0.9, 1.0)" "threw" True
    Right _ -> checkWith "valueAtRisk rejects centile outside [0.9, 1.0)" "should have thrown" False

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
