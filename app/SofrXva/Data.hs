-- |Ad-hoc loaders for the fixed vendor-specific CSV layouts consumed by the sofr-xva
-- pipeline (curve dumps, quote dumps, historical fixings, and the reference NPV file).
-- Each loader filters rows by name/type in a single pass over its file(s) --
-- there is no general dataframe machinery here, deliberately: this is interim, targeted
-- only at these exact layouts, and expected to be superseded by proper dataframe support
-- later.
module SofrXva.Data
  ( loadSofrCurve
  , loadSofrQuote
  , loadIndexHist
  , loadNpvComparison
  ) where

import Data.Time.Calendar (Day)
import qualified Data.Map.Strict as Map

import SofrXva.Csv (parseDMY, splitComma)

-- |Curve dump rows look like:
-- @Scen,\<n\>,TS,\<n\>,\<valDate\>,CurveDate|CurvePoint,\<type\>,\<id\>,\<name\>,\<data...\>@
-- A @CurveDate@ row (pillar dates) is immediately followed by a @CurvePoint@ row (matching
-- discount factors) for the same (scenario, timestep). Returns, per (scenario, timestep),
-- the valuation date and its (pillar date, discount factor) pairs -- with a synthetic
-- @(valDate, 1.0)@ point prepended, since the source discount factors are relative to
-- the valuation date rather than including it.
loadSofrCurve :: FilePath -> String -> IO (Map.Map (Int, Int) (Day, [(Day, Double)]))
loadSofrCurve path curveName = do
  rows <- curveRows curveName <$> readFile path
  pure (Map.fromList (pairCurveRows rows))

data CurveRow = CurveRow
  { crScen :: !Int
  , crTS :: !Int
  , crValDate :: !Day
  , crCol :: !String -- ^"CurveDate" or "CurvePoint"
  , crData :: ![String]
  }

curveRows :: String -> String -> [CurveRow]
curveRows curveName content =
  [ CurveRow scen ts valDate col rest
  | l <- lines content
  , let fs = splitComma l
  , length fs > 9
  , fs !! 8 == curveName
  , let scen = read (fs !! 1)
  , let ts = read (fs !! 3)
  , let valDate = parseDMY (fs !! 4)
  , let col = fs !! 5
  , let rest = drop 9 fs
  ]

pairCurveRows :: [CurveRow] -> [((Int, Int), (Day, [(Day, Double)]))]
pairCurveRows rows =
  [ ((crScen dr, crTS dr), (crValDate dr, (crValDate dr, 1.0) : zip (map parseDMY (crData dr)) (map read (crData pr))))
  | (dr, pr) <- zip rows (drop 1 rows)
  , crCol dr == "CurveDate", crCol pr == "CurvePoint"
  , crScen dr == crScen pr, crTS dr == crTS pr
  ]

-- |Quote dump rows look like:
-- @Scen,\<n\>,TS,\<n\>,\<tsDate\>,Quote,\<name\>,\<date\>,\<type\>,\<value\>@
-- Returns the quote value keyed by (scenario, timestep, quote date), merged across all
-- the given files (the real data is split across several @*_1\/_2\/_3.csv@ files).
loadSofrQuote :: [FilePath] -> String -> IO (Map.Map (Int, Int, Day) Double)
loadSofrQuote paths quoteName = do
  contents <- mapM readFile paths
  pure (Map.fromList (concatMap (quoteRows quoteName) contents))

quoteRows :: String -> String -> [((Int, Int, Day), Double)]
quoteRows quoteName content =
  [ ((scen, ts, date), value)
  | l <- lines content
  , let fs = splitComma l
  , length fs > 9
  , fs !! 6 == quoteName
  , let scen = read (fs !! 1)
  , let ts = read (fs !! 3)
  , let date = parseDMY (fs !! 7)
  , let value = read (fs !! 9)
  ]

-- |Historical fixing scale: a "Yield" quote type is stored as a percentage and must be
-- divided by 100; a "Price" quote is already a plain number.
quoteScale :: String -> Double
quoteScale "Yield" = 100
quoteScale "Price" = 1
quoteScale t = error ("SofrXva.Data.quoteScale: unrecognised quote type " ++ show t)

-- |Historical fixing file: a real header row, then
-- @Date,Quote Name,Quote Type,Bid,Ask,Open,Close,High,Low,Last,...@. Returns the (scaled)
-- @Close@ value keyed by date, for rows whose @Quote Name@ matches.
loadIndexHist :: FilePath -> String -> IO (Map.Map Day Double)
loadIndexHist path histName = do
  ls <- lines <$> readFile path
  pure $ Map.fromList
    [ (date, value)
    | l <- drop 1 ls -- skip header
    , dateField : nameField : typeField : _bid : _ask : _open : closeField : _ <- [splitComma l]
    , nameField == histName
    , let date = parseDMY dateField
    , let value = read closeField / quoteScale typeField
    ]

-- |Reference NPV file: @NettingKey: ...@, then a header row
-- @TimeStep_down | Scen_across, \<scen0\>,\<scen1\>,...@, then rows
-- @\"\<ts\>: \<date\>\",v0,v1,...@ (one value per header scenario, in order). Rows past
-- a trade's maturity may carry fewer values than there are scenarios; those trailing
-- scenarios are simply absent from the result for that timestep.
loadNpvComparison :: FilePath -> IO (Map.Map (Int, Int) Double)
loadNpvComparison path = do
  ls <- lines <$> readFile path
  case ls of
    (_nettingKey : headerLine : dataLines) ->
      let scenIds = map read (drop 1 (splitComma headerLine)) :: [Int]
      in pure $ Map.fromList
           [ ((ts, scen), v)
           | l <- dataLines
           , not (null l)
           , tsField : vals <- [splitComma l]
           , let ts = read (takeWhile (/= ':') tsField)
           , (scen, v) <- zip scenIds (map read vals)
           ]
    _ -> error ("SofrXva.Data.loadNpvComparison: malformed file " ++ path)
