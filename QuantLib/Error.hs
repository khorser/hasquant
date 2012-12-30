{-# LANGUAGE DeriveDataTypeable #-}

module QuantLib.Error(Error(..))
where

import Control.Exception
import Data.Typeable

data Error = Error{message::String} deriving (Typeable, Show)

instance Exception Error
