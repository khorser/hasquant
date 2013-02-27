module QuantLib.Math.HistogramAlgorithm
  (
    HistogramAlgorithm(..)
  )
where

import QuantLib.Internal.Enum

data HistogramAlgorithm = None | Sturges | FD | Scott
  deriving (Show, Eq, Enum)
instance QLEnum HistogramAlgorithm

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
