module QuantLib.Spec.ApiNames (spec) where

import Control.Monad (unless)
import Data.Char (isAlphaNum, isDigit, isLower)
import Data.List (isInfixOf, isPrefixOf, nub, sort)
import System.Directory (doesDirectoryExist, doesFileExist, getCurrentDirectory)
import System.Environment (getExecutablePath)
import System.FilePath ((</>), (<.>), joinPath, takeDirectory)
import System.Process (readProcess)
import Test.Hspec

spec :: Spec
spec = describe "public API names" $ do
  it "rejects primes, unexplained numeric suffixes, and reviewed acronym spellings" $ do
    repoRoot <- findAncestorWith "package.yaml" =<< getCurrentDirectory
    buildRoot <- findBuildRoot =<< getExecutablePath
    modules <- exposedModules <$> readFile (repoRoot </> "package.yaml")
    names <- sort . nub . concat <$> mapM (interfaceNames buildRoot) modules
    migration <- migrationPairs <$> readFile (repoRoot </> "tools/api-name-map-0.7.txt")
    let oldNames = map fst migration
        newNames = map snd migration
        retiredNames = filter (`notElem` newNames) oldNames
        failures =
          [ "trailing apostrophe: " ++ name | name <- names, last name == '\'' ] ++
          [ "unexplained numeric suffix: " ++ name
          | name <- names, isDigit (last name), name `notElem` allowedNumericNames ] ++
          [ "banned acronym spelling: " ++ name
          | name <- names, any (`isInfixOf` name) bannedAcronymSpellings ] ++
          [ "retired reviewed name: " ++ name | name <- names, name `elem` retiredNames ]
    failures `shouldBe` []

  it "keeps reviewed scalar Quote alternatives rejected" $ do
    repoRoot <- findAncestorWith "package.yaml" =<< getCurrentDirectory
    rows <- methodRows <$> readFile (repoRoot </> "tools/ql-methods-1.43.txt")
    let failures =
          [ callable ++ " / " ++ argument ++ ": " ++ show statuses
          | (callable, argument, expectedCount) <- reviewedScalarQuoteAlternatives
          , let statuses =
                  [ status
                  | (status, signature) <- rows
                  , callable `isInfixOf` signature
                  , argument `isInfixOf` signature
                  ]
          , length statuses /= expectedCount || any (/= "x") statuses
          ]
    failures `shouldBe` []

allowedNumericNames :: [String]
allowedNumericNames =
  [ "g2"
  , "garch11"
  , "garmanKlassSigma1"
  , "garmanKlassSigma3"
  , "garmanKlassSigma4"
  , "garmanKlassSigma5"
  , "garmanKlassSigma6"
  , "liborForwardModelS0"
  ]

bannedAcronymSpellings :: [String]
bannedAcronymSpellings =
  [ "ATM", "BPS", "BSM", "CDO", "CPI", "FDM", "GARCH", "IMM"
  , "KO", "LHP", "NPV", "OIS", "OU", "SLV", "YoY"
  ]

-- Each marker identifies a reviewed flat market-data overload whose live sibling takes
-- Handle<Quote>.  The count distinguishes fixed-date and moving variants where both exist.
reviewedScalarQuoteAlternatives :: [(String, String, Int)]
reviewedScalarQuoteAlternatives =
  [ ("BachelierCapFloorEngine::BachelierCapFloorEngine", "Volatility vol,", 1)
  , ("BachelierSwaptionEngine::BachelierSwaptionEngine", "Volatility vol,", 1)
  , ("BlackCapFloorEngine::BlackCapFloorEngine", "Volatility vol,", 1)
  , ("BlackConstantVol::BlackConstantVol", "Volatility volatility,", 2)
  , ("BlackSwaptionEngine::BlackSwaptionEngine", "Volatility vol,", 1)
  , ("CallableBondConstantVolatility::CallableBondConstantVolatility", "Volatility volatility,", 2)
  , ("ConstantCPIVolatility::ConstantCPIVolatility", "Volatility vol,", 1)
  , ("ConstantCapFloorTermVolatility::ConstantCapFloorTermVolatility", "Volatility volatility,", 2)
  , ("ConstantOptionletVolatility::ConstantOptionletVolatility", "Volatility volatility,", 2)
  , ("ConstantSwaptionVolatility::ConstantSwaptionVolatility", "Volatility volatility,", 2)
  , ("ConstantYoYOptionletVolatility::ConstantYoYOptionletVolatility", "Volatility v,", 1)
  , ("CounterpartyAdjSwapEngine::CounterpartyAdjSwapEngine", "Volatility blackVol,", 1)
  , ("FlatForward::FlatForward", "Rate forward,", 2)
  , ("FlatHazardRate::FlatHazardRate", "Rate hazardRate,", 2)
  , ("GaussianLHPLossModel::GaussianLHPLossModel", "Real correlation,", 1)
  , ("Gsr::Gsr", "const std::vector<Real> & volatilities,", 2)
  , ("HestonModelHelper::HestonModelHelper", "Real s0,", 1)
  , ("LocalConstantVol::LocalConstantVol", "Volatility volatility,", 2)
  , ("LocalVolSurface::LocalVolSurface", "Real underlying)", 1)
  , ("NoArbSabrInterpolatedSmileSection::NoArbSabrInterpolatedSmileSection", "const Rate & forward,", 1)
  , ("NoExceptLocalVolSurface::NoExceptLocalVolSurface", "Real underlying,", 1)
  , ("SabrInterpolatedSmileSection::SabrInterpolatedSmileSection", "const Rate & forward,", 1)
  , ("SviInterpolatedSmileSection::SviInterpolatedSmileSection", "const Rate & forward,", 1)
  ]

methodRows :: String -> [(String, String)]
methodRows = foldr parseLine [] . lines
  where
    parseLine line rows = case splitOn '|' line of
      (_ : status : _header : signature : _) -> (status, signature) : rows
      _ -> rows

interfaceNames :: FilePath -> String -> IO [String]
interfaceNames buildRoot moduleName = do
  let interface = buildRoot </> joinPath (splitOn '.' moduleName) <.> "hi"
  exists <- doesFileExist interface
  unless exists $ expectationFailure ("missing interface: " ++ interface)
  output <- readProcess "ghc" ["--show-iface", interface] ""
  pure . filter startsLower . identifiers . unlines . exportLines $ lines output
  where
    startsLower (c : _) = isLower c
    startsLower [] = False

exportLines :: [String] -> [String]
exportLines =
  takeWhile (not . isDependenciesHeader) .
  drop 1 . dropWhile (/= "exports:")
  where
    isDependenciesHeader line =
      "module dependencies:" `isPrefixOf` line ||
      "direct module dependencies:" `isPrefixOf` line

identifiers :: String -> [String]
identifiers [] = []
identifiers input =
  case dropWhile (not . identifierChar) input of
    [] -> []
    rest -> let (name, suffix) = span identifierChar rest
            in name : identifiers suffix
  where
    identifierChar c = isAlphaNum c || c == '_' || c == '\''

exposedModules :: String -> [String]
exposedModules =
  map (drop 6) .
  takeWhile (isPrefixOf "    - ") .
  drop 1 . dropWhile (not . isPrefixOf "  exposed-modules:") .
  lines

migrationPairs :: String -> [(String, String)]
migrationPairs = foldr parseLine [] . lines
  where
    parseLine line pairs
      | null line || "#" `isPrefixOf` line = pairs
      | otherwise = case words line of
          [oldName, newName] -> (oldName, newName) : pairs
          _ -> pairs

findBuildRoot :: FilePath -> IO FilePath
findBuildRoot executable = findAncestorWith ("QuantLib" </> "Type.hi") (takeDirectory executable)

findAncestorWith :: FilePath -> FilePath -> IO FilePath
findAncestorWith marker start = go start
  where
    go dir = do
      let candidate = dir </> marker
      fileFound <- doesFileExist candidate
      directoryFound <- doesDirectoryExist candidate
      if fileFound || directoryFound
        then pure dir
        else if parent dir == dir
          then expectationFailure ("could not find " ++ marker ++ " above " ++ start) >> pure start
          else go (parent dir)
    parent = takeDirectory

splitOn :: Eq a => a -> [a] -> [[a]]
splitOn delimiter value =
  case break (== delimiter) value of
    (part, []) -> [part]
    (part, _ : rest) -> part : splitOn delimiter rest
