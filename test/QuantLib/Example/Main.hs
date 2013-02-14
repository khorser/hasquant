module Main where

import QuantLib.Utilities
import QuantLib.Time.Date

import qualified QuantLib.Example.Bond as BondExample
import qualified QuantLib.Example.Repo as RepoExample

main :: IO ()
main = do
  putStrLn $ "QuantLib version " ++ version
     ++ ", Boost " ++ boostVersion
  t <- today
  putStrLn $ "Today is " ++ show (weekday t)

  r <- BondExample.result
  
  putStrLn $ "NPV: " ++ show (BondExample.npvR r)
  putStrLn $ "Yield: " ++ show (BondExample.yieldR r)
  putStrLn $ "Clean price: " ++ show (BondExample.cleanPriceR r)
  putStrLn $ "Dirty price: " ++ show (BondExample.dirtyPriceR r)
  putStrLn $ "Accrued amount: " ++ show (BondExample.accruedAmountR r)
  putStrLn $ "Previous coupon: " ++ show (BondExample.previousCoupon r)
  putStrLn $ "Next coupon: " ++ show (BondExample.nextCoupon r)
  putStrLn $ "Next coupon date: " ++ show (BondExample.nextCouponDate r)
  putStrLn $ "Floater's clean price from yield: " ++ show (BondExample.cleanPriceFromYield r)
  putStrLn $ "Floater's yield from clean price: " ++ show (BondExample.yieldFromCleanPrice r)
  putStrLn $ "Tradable: " ++ show (BondExample.tradable r)

  putStrLn $ "CashFlows: NPV: " ++ show (BondExample.cfnpvR r) ++ ", NPV_BPS: " ++ show (BondExample.cfnpvbpsR r)
  putStrLn $ "BPS: " ++ show (BondExample.bpsR r)

  rr <- RepoExample.result
  putStrLn $ "Underlying bond clean price: " ++ show (RepoExample.cleanPriceR rr)
  putStrLn $ "Underlying bond dirty price: " ++ show (RepoExample.dirtyPriceR rr)
  putStrLn $ "Underlying bond accrued at settlement: " ++ show (RepoExample.accruedAmountSettlement rr)
  putStrLn $ "Underlying bond accrued at delivery:   " ++ show (RepoExample.accruedAmountDelivery rr)
  putStrLn $ "Underlying bond spot income: " ++ show (RepoExample.spotIncomeR rr)
  putStrLn $ "Underlying bond fwd income:  " ++ show (RepoExample.fwdIncomeR rr)
  putStrLn $ "Repo strike: " ++ show (RepoExample.strike rr)
  putStrLn $ "Repo NPV:    " ++ show (RepoExample.npvR rr)
  putStrLn $ "Repo clean forward price: " ++ show (RepoExample.cleanForwardPriceR rr)
  putStrLn $ "Repo dirty forward price: " ++ show (RepoExample.forwardPriceR rr)
  putStrLn $ "Repo implied yield: " ++ show (RepoExample.impliedYieldR rr)
  putStrLn $ "Market repo rate:   " ++ show (RepoExample.zeroRateR rr)

  putStrLn "DONE"
