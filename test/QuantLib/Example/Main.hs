module Main where

import QuantLib.Utilities
import QuantLib.Time.Date

import qualified QuantLib.Example.Bond as BondExample

main :: IO ()
main = do putStrLn $ "QuantLib version " ++ version
             ++ ", Boost " ++ boostVersion
          t <- today
          putStrLn $ "Today is " ++ show (weekday t)

          (fixnpv, znpv, fnpv) <- BondExample.npv
         
          putStrLn "Data from QL Bond Example (QuantLib-1.2 on Windows x86):    100.92217820704442  107.66828913260436 102.35931459949133"
          putStrLn "Data from QL Bond Example (QuantLib-1.2.1 on Windows x86):  100.9221782070444  107.66828913260427  102.35931459949143"
          putStrLn "Data from QL Bond Example (QuantLib-1.2 on Linux x86-64):   100.92217820704460962 107.66828913260425793 102.35931459949132716"
          putStrLn "Data from QL Bond Example (QuantLib-1.2.1 on Linux x86-64): 100.92217820704460962 107.66828913260425793 102.35931459949128453"
          putStrLn $ "Ours: " ++ show [znpv, fixnpv, fnpv]
