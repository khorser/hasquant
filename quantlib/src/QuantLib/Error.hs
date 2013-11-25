{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Error
  (
    Error(..)
  )
where

import Control.Exception(Exception, IOException)
import Data.Time.Calendar(Day)
import Data.Typeable(Typeable)

data Error = CPlusPlusException {message::String} 
  | DateConversionError Day
  | NullPointerReturned
  | UnknownEnum String
  | EnumConversion String -- TODO pass actual enum
  | CEnumConversion Int
  | IoException IOException
  deriving (Typeable, Show)

instance Exception Error

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
