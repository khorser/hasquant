{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.DateGenerationRule
  (
    DateGenerationRule(..)
  )
where

import Data.Typeable(Typeable)

data DateGenerationRule = Backward | Forward | Zero | ThirdWednesday
  | Twentieth | TwentiethIMM | OldCDS | CDS
  deriving (Show, Eq, Enum, Typeable)
