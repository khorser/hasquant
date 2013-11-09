module QuantLib.ProcessDiscretization
  (
    ProcessDiscretization(..)
  , ExtendedDiscretization(..)
  , HestonProcessDiscretization(..)
  , GJRGARCHProcessDiscretization(..)
  , HybridHestonHullWhiteProcessDiscretization(..)
  )
where

import QuantLib.Internal.Enum

data ProcessDiscretization = EulerDiscretization -- ^Euler discretization for stochastic processes
  | EndEulerDiscretization -- ^Euler end-point discretization for stochastic processes
  deriving (Show, Eq)
instance QLLitEnum ProcessDiscretization

data ExtendedDiscretization = Euler | Milstein | PredictorCorrector
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum ExtendedDiscretization

data HestonProcessDiscretization = HestonPartialTruncation
  | HestonFullTruncation | HestonReflection
  | HestonNonCentralChiSquareVariance | HestonQuadraticExponential
  | HestonQuadraticExponentialMartingale
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum HestonProcessDiscretization

data GJRGARCHProcessDiscretization = GJRGARCHPartialTruncation
  | GJRGARCHFullTruncation | GJRGARCHReflection
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum GJRGARCHProcessDiscretization

data HybridHestonHullWhiteProcessDiscretization = HestonHullWhiteEuler
  | HestonHullWhiteBSMHullWhite
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum HybridHestonHullWhiteProcessDiscretization

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
