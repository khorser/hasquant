module QuantLib.Method.BinomialTree
  (
    BinomialTree(..)
  )
where

import QuantLib.Internal.Enum

data BinomialTree = JarrowRudd | CoxRossRubinstein | AdditiveEQPBinomialTree
  | Trigeorgis | Tian | LeisenReimer | Joshi4 
  | ExtendedJarrowRudd | ExtendedCoxRossRubinstein
  | ExtendedAdditiveEQPBinomialTree | ExtendedTrigeorgis | ExtendedTian
  | ExtendedLeisenReimer | ExtendedJoshi4
  deriving (Show, Eq)
instance QLLitEnum BinomialTree

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
