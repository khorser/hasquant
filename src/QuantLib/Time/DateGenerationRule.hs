{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.DateGenerationRule
  (
    DateGenerationRule(..)
  )
where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum DateGenerationRule

data DateGenerationRule = Backward | Forward | Zero | ThirdWednesday
  | Twentieth | TwentiethIMM | OldCDS | CDS
  deriving (Show, Eq, Enum, Typeable)
