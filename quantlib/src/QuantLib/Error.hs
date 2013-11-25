{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Error
  (
    Error(..)
  )
where

import Control.Exception(Exception, IOException)
import Data.Time.Calendar(Day)
import Data.Typeable(Typeable)

data Error = CPlusPlusException String
  | DateConversion Day
  | NullPointerReturned
  | UnknownEnum String
  | EnumConversion String String
  | CEnumConversion String Int
  | IoException IOException
  deriving (Typeable, Show)

instance Exception Error

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
