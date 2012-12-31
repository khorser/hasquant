{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Error
  (
    Error(..)
  )
where

import Control.Exception(Exception)
import Data.Typeable(Typeable)

data Error = Error{message::String} deriving (Typeable, Show)

instance Exception Error
