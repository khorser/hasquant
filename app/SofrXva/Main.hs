-- |Wiring for the SOFR-OIS exposure-profile pipeline: loads the vendor-format CSV
-- dumps (via 'SofrXva.Data'), prices the swap on every (scenario, timestep) pair (via
-- 'SofrXva.Pricing'), and compares against the reference NPV file, printing a summary
-- and writing @_NPVDiff.csv@.
--
-- The curve\/quote\/index name fields each loader filters rows by (see 'SofrXva.Data')
-- are a source-specific naming convention, not something this program can guess --
-- @--curve-name@\/@--quote-name@\/@--quote-name-full@ override the generic defaults
-- (which match the synthetic fixtures under @app\/SofrXva\/example-data@) with whatever
-- convention a real data source actually uses, e.g. @--quote-name-full MY-SOURCE.USD.SOFR.1D@.
module Main (main) where

import Control.Monad (forM_, unless)
import Data.List (sortOn)
import qualified Data.Map.Strict as Map
import System.Environment (getArgs)
import System.FilePath ((</>))
import Text.Printf (printf)

import SofrXva.Data (loadIndexHist, loadNpvComparison, loadSofrCurve, loadSofrQuote)
import SofrXva.Pricing (buildSofrProfile)

-- |Which files to load. A real data source's on-disk file names are as much a
-- source-specific convention as the row-level name fields below, so these generic
-- basenames (which match the synthetic fixtures under @app\/SofrXva\/example-data@)
-- are only defaults -- @--curve-file@\/@--quote-file@\/@--history-file@\/@--npv-file@
-- override them for any other source. @--quote-file@ may be repeated (a source may
-- split its quote dump across several files); repeating it replaces the default
-- single-file list rather than appending to it.
data FilePaths = FilePaths
  { fpCurve :: FilePath
  , fpQuotes :: [FilePath]
  , fpHistory :: FilePath
  , fpNpv :: FilePath
  }

defaultPaths :: FilePath -> FilePaths
defaultPaths dataDir = FilePaths
  { fpCurve = dataDir </> "curve.csv"
  , fpQuotes = [dataDir </> "quotes.csv"]
  , fpHistory = dataDir </> "history.csv"
  , fpNpv = dataDir </> "npv.csv"
  }

-- |The row-level name fields 'SofrXva.Data''s loaders filter by. A real data source
-- will use its own convention here; these generic defaults only match the synthetic
-- example fixtures, and are overridden via CLI flags for any other source.
data Names = Names
  { nCurve :: String
  , nQuote :: String
  , nQuoteFull :: String
  }

defaultNames :: Names
defaultNames = Names
  { nCurve = "USD.SOFR.1D"
  , nQuote = "USD.SOFR.1D"
  , nQuoteFull = "INDEX.USD.SOFR.1D"
  }

data Args = Args
  { aDataDir :: FilePath
  , aExample :: Bool
  , aCurveFile :: Maybe FilePath
  , aQuoteFiles :: Maybe [FilePath]
  , aHistoryFile :: Maybe FilePath
  , aNpvFile :: Maybe FilePath
  , aCurveName :: Maybe String
  , aQuoteName :: Maybe String
  , aQuoteNameFull :: Maybe String
  }

defaultArgs :: Args
defaultArgs = Args
  { aDataDir = "py"
  , aExample = False
  , aCurveFile = Nothing
  , aQuoteFiles = Nothing
  , aHistoryFile = Nothing
  , aNpvFile = Nothing
  , aCurveName = Nothing
  , aQuoteName = Nothing
  , aQuoteNameFull = Nothing
  }

usage :: String
usage = "usage: sofr-xva [--data-dir DIR | --example] "
  ++ "[--curve-file FILE] [--quote-file FILE]... [--history-file FILE] [--npv-file FILE] "
  ++ "[--curve-name NAME] [--quote-name NAME] [--quote-name-full NAME]"

parseArgs :: [String] -> Args
parseArgs = go defaultArgs
  where
    go acc [] = acc
    go acc ("--data-dir" : d : rest) = go acc{aDataDir = d} rest
    go acc ("--example" : rest) = go acc{aExample = True} rest
    go acc ("--curve-file" : f : rest) = go acc{aCurveFile = Just f} rest
    go acc ("--quote-file" : f : rest) =
      go acc{aQuoteFiles = Just (concat (aQuoteFiles acc) ++ [f])} rest
    go acc ("--history-file" : f : rest) = go acc{aHistoryFile = Just f} rest
    go acc ("--npv-file" : f : rest) = go acc{aNpvFile = Just f} rest
    go acc ("--curve-name" : n : rest) = go acc{aCurveName = Just n} rest
    go acc ("--quote-name" : n : rest) = go acc{aQuoteName = Just n} rest
    go acc ("--quote-name-full" : n : rest) = go acc{aQuoteNameFull = Just n} rest
    go _ _ = error usage

main :: IO ()
main = do
  args <- parseArgs <$> getArgs
  let dataDir = if aExample args then "app/SofrXva/example-data" else aDataDir args
      base = defaultPaths dataDir
      paths = base
        { fpCurve = maybe (fpCurve base) id (aCurveFile args)
        , fpQuotes = maybe (fpQuotes base) id (aQuoteFiles args)
        , fpHistory = maybe (fpHistory base) id (aHistoryFile args)
        , fpNpv = maybe (fpNpv base) id (aNpvFile args)
        }
      names = defaultNames
        { nCurve = maybe (nCurve defaultNames) id (aCurveName args)
        , nQuote = maybe (nQuote defaultNames) id (aQuoteName args)
        , nQuoteFull = maybe (nQuoteFull defaultNames) id (aQuoteNameFull args)
        }

  curveMap <- loadSofrCurve (fpCurve paths) (nCurve names)
  quoteMap <- loadSofrQuote (fpQuotes paths) (nQuote names)
  histMap <- loadIndexHist (fpHistory paths) (nQuoteFull names)
  refNpvMap <- loadNpvComparison (fpNpv paths)

  npvMap <- buildSofrProfile curveMap histMap quoteMap

  -- refNpvMap is keyed (TS,Scen) (loadNpvComparison's file layout), npvMap (Scen,TS)
  -- (buildSofrProfile's natural iteration order) -- transpose here rather than in
  -- either loader/pricer, since each key order is the natural one for its own file.
  let diffs = [ ((scen, ts), abs ((ref - v) / ref))
              | ((scen, ts), v) <- Map.toList npvMap
              , Just ref <- [Map.lookup (ts, scen) refNpvMap]
              ]

  if null diffs
    then putStrLn "sofr-xva: no (scen,ts) pairs overlapped the reference NPV file"
    else do
      -- a handful of reference cells are 0 (trade fully rolled off in that scenario),
      -- which blows the relative diff up to Infinity/NaN -- exclude them from the
      -- summary stats here, but still write every cell to the CSV.
      let rels = filter (not . isNaN) [d | (_, d) <- diffs, isFinite d]
          isFinite d = not (isNaN d) && not (isInfinite d)
          worst = take 10 (sortOn (negate . snd) [dd | dd@(_, d) <- diffs, isFinite d])
      printf "sofr-xva: %d (scen,ts) pairs priced, %d compared against reference\n"
        (Map.size npvMap) (length diffs)
      unless (null rels) $ do
        printf "  max relative diff  = %.6f\n" (maximum rels)
        printf "  mean relative diff = %.6f\n" (sum rels / fromIntegral (length rels))
      putStrLn "  worst 10 (excluding non-finite):"
      forM_ worst $ \((scen, ts), d) ->
        printf "    scen=%d ts=%d relDiff=%.6f\n" scen ts d

  writeFile (dataDir </> "_NPVDiff.csv") $ unlines $
    "TS,Scen,RelDiff" : [ printf "%d,%d,%.10f" ts scen d | ((scen, ts), d) <- sortOn fst diffs ]
