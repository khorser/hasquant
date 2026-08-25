-- |Ad-hoc, minimal line/field parsing for the fixed vendor-specific CSV layouts consumed by
-- 'SofrXva.Data'. Deliberately not a general CSV library -- these files never quote or escape
-- fields, so a plain comma-split is enough. This module (and the loaders built on it) is interim
-- and expected to be superseded by proper dataframe support later.
module SofrXva.Csv
  ( splitComma
  , parseDMY
  ) where

import Data.Time.Calendar (Day)
import Data.Time.Format (defaultTimeLocale, parseTimeM)

-- |Split a line on commas. No quoting/escaping -- none of the consumed files need it.
splitComma :: String -> [String]
splitComma s = case break (== ',') s of
  (field, ',':rest) -> field : splitComma rest
  (field, "") -> [field]
  (field, _) -> [field] -- unreachable: break only stops on ',' or end of string

-- |Parse a @dd\/mm\/yyyy@ date, the format used throughout the source files.
parseDMY :: String -> Day
parseDMY s = case parseTimeM True defaultTimeLocale "%d/%m/%Y" s of
  Just d -> d
  Nothing -> error ("SofrXva.Csv.parseDMY: not a dd/mm/yyyy date: " ++ show s)
