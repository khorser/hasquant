module QuantLib.Example.Swap
  (
    Result(..)
  , run
  )
where


data Result = Result
  { cleanPriceR :: Double
  } deriving Show

run :: IO Result
run =
  return $ Result 5.6
