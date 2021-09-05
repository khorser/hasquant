{-# LANGUAGE FunctionalDependencies #-}
module QuantLib.Type
  (
    Error(..)
--  , Settings(..)
  , Derives(..)
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

class Derives a b | a -> b where cast :: a -> IO b

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
