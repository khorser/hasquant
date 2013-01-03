module QuantLib.Time.DateGenerationRule
  (
    DateGenerationRule(..)
  )
where

data DateGenerationRule = Backward | Forward | Zero | ThirdWednesday | Twentieth | TwentiethIMM | OldCDS | CDS deriving Show
