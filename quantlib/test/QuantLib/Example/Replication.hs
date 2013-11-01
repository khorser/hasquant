module QuantLib.Example.Replication
  (
    Result(..)
  , run
  )
where

data Result = Result
  { npvInit :: [Double]
  , errorInit :: [Double]
  , npvOut :: [Double]
  , errorOut :: [Double]
  , npvIn :: [Double]
  , errorIn :: [Double]
  }

run :: IO Result
run = 
  return Result {
    npvInit = [0]
  , errorInit = [0]
  , npvOut = [0]
  , errorOut = [0]
  , npvIn = [0]
  , errorIn = [0]
  }
