module QuantLib.Type
  (
    Error(..)
--  , Settings(..)
  , Named(..)
  )
where

import Control.Exception(Exception)
import Data.Time.Calendar(Day)

--data Settings = Settings {
--    evaluationDate :: Day
--  , enforceTodaysHistoricFixings :: Bool
--  , includeTodaysCashFlows :: Bool
--  , includeReferenceDateEvents :: Bool}

data Error = CPlusPlusException String | DateConversion Day deriving (Show, Eq)

instance Exception Error

class Named a where
  name :: a -> String

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
