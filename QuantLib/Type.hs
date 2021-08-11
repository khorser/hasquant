module QuantLib.Type
  (
    Error(..)
--  , Settings(..)
  )
where

import Control.Exception(Exception)
import Data.Time.Calendar(Day)

--data Settings = Settings {
--    evaluationDate :: Day
--  , enforceTodaysHistoricFixings :: Bool
--  , includeTodaysCashFlows :: Bool
--  , includeReferenceDateEvents :: Bool}

data Error = CPlusPlusException String
          | DateConversion Day
          | EnumConversion String
          deriving (Show, Eq)

instance Exception Error

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
