module QuantLib.Example.BermudanSwaption
  (
    Result(..)
  , run
  )
where

data Result = Result
  { g2a :: Double
  , g2sigma :: Double
  , g2b :: Double
  , g2eta :: Double
  , g2rho :: Double
  , g2npv :: (Double, Double)
  , hwa :: Double
  , hwsigma :: Double
  , hwnpv :: (Double, Double)
  , hw2a :: Double
  , hw2sigma :: Double
  , hw2npv :: (Double, Double)
  , bka :: Double
  , bksigma :: Double
  , bknpv :: (Double, Double)
  }

run :: IO Result
run = 
  return Result {
    g2a = 0
  , g2sigma = 0
  , g2b = 0
  , g2eta = 0
  , g2rho = 0
  , g2npv = (0, 0)
  , hwa = 0
  , hwsigma = 0
  , hwnpv = (0, 0)
  , hw2a = 0
  , hw2sigma = 0
  , hw2npv = (0, 0)
  , bka = 0
  , bksigma = 0
  , bknpv = (0, 0)
  }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
