module QuantLib.Example.Repo
  (
    Result(..)
  , result
  )
where

data Result = Result

result :: IO Result
result = return Result
