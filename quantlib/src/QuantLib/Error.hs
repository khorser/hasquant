{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Error
  (
    QLError(..)
  )
where

import Control.Exception(Exception, IOException)
import Data.Time.Calendar(Day)
import Data.Typeable(Typeable)

data QLError = CPlusPlusException String
  | DateConversion Day
  | NullPointerReturned
  | UnknownEnum String
  | EnumConversion String String
  | CEnumConversion String Int
  | IncorrectSize
  | IoException IOException
  deriving (Typeable, Show, Eq)

instance Exception QLError

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
