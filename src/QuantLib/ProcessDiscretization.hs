module QuantLib.ProcessDiscretization
  (
    ProcessDiscretization(..)
  , ExtendedDiscretization(..)
  )
where

import QuantLib.Internal.Enum

data ProcessDiscretization = EulerDiscretization -- ^Euler discretization for stochastic processes
  | EndEulerDiscretization -- ^Euler end-point discretization for stochastic processes
  deriving (Show, Eq)

instance QLLitEnum ProcessDiscretization

data ExtendedDiscretization = Euler | Milstein | PredictorCorrector
  deriving (Show, Eq, Enum)

instance QLEnum ExtendedDiscretization
-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
