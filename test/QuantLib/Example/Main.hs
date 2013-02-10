module Main where

import QuantLib.Utilities
import QuantLib.Time.Date

import qualified QuantLib.Example.Bond as BondExample

main :: IO ()
main = do putStrLn $ "QuantLib version " ++ version
             ++ ", Boost " ++ boostVersion
          t <- today
          putStrLn $ "Today is " ++ show (weekday t)

          r <- BondExample.result
         
          putStrLn $ "NPV: " ++ show (BondExample.npv r)
          putStrLn $ "Yield: " ++ show (BondExample.yield r)
          putStrLn $ "Clean price: " ++ show (BondExample.cleanPrice r)
          putStrLn $ "Dirty price: " ++ show (BondExample.dirtyPrice r)
          putStrLn $ "Accrued amount: " ++ show (BondExample.accruedAmount r)
          putStrLn $ "Previous coupon: " ++ show (BondExample.previousCoupon r)
          putStrLn $ "Next coupon: " ++ show (BondExample.nextCoupon r)
          putStrLn $ "Next coupon date: " ++ show (BondExample.nextCouponDate r)
          putStrLn $ "Floater's clean price from yield: " ++ show (BondExample.cleanPriceFromYield r)
          putStrLn $ "Floater's yield from clean price: " ++ show (BondExample.yieldFromCleanPrice r)
          putStrLn $ "Tradable: " ++ show (BondExample.tradable r)
