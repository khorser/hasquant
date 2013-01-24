module Main where

import QuantLib.Utilities
import QuantLib.Time.Date

main :: IO ()
main = do putStrLn $ "QuantLib version " ++ version
             ++ ", Boost " ++ boostVersion
          t <- today
          putStrLn $ "Today is " ++ show (weekday t)
