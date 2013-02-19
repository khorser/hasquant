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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
