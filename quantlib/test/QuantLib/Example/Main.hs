module Main where

import Control.Monad(forM_)
import Text.Printf

import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Utilities

import qualified QuantLib.Example.Bond as BondExample
import qualified QuantLib.Example.Repo as RepoExample
import qualified QuantLib.Example.FRA as FRAExample
import qualified QuantLib.Example.Swap as SwapExample
import qualified QuantLib.Example.FittedBondCurve as BondCurveExample

main :: IO ()
main = do
  putStrLn $ "QuantLib version " ++ version
     ++ ", Boost " ++ boostVersion
  t <- today
  putStrLn $ "Today is " ++ show (weekday t)

  putStrLn "*** Bond Example ***"
  br <- keepingSettings' BondExample.run

  putStrLn $ "NPV: " ++ show (BondExample.npvR br)
  putStrLn $ "Yield: " ++ show (BondExample.yieldR br)
  putStrLn $ "Clean price: " ++ show (BondExample.cleanPriceR br)
  putStrLn $ "Dirty price: " ++ show (BondExample.dirtyPriceR br)
  putStrLn $ "Accrued amount: " ++ show (BondExample.accruedAmountR br)
  putStrLn $ "Previous coupon: " ++ show (BondExample.previousCoupon br)
  putStrLn $ "Next coupon: " ++ show (BondExample.nextCoupon br)
  putStrLn $ "Next coupon date: " ++ show (BondExample.nextCouponDate br)
  putStrLn $ "Floater's clean price from yield: " ++ show (BondExample.cleanPriceFromYield br)
  putStrLn $ "Floater's yield from clean price: " ++ show (BondExample.yieldFromCleanPrice br)
  putStrLn $ "Tradable: " ++ show (BondExample.tradable br)

  putStrLn $ "CashFlows: NPV: " ++ show (BondExample.cfnpvR br) ++ ", NPV_BPS: " ++ show (BondExample.cfnpvbpsR br)
  putStrLn $ "BPS: " ++ show (BondExample.bpsR br)

  putStrLn "*** Repo Example ***"
  rr <- keepingSettings' RepoExample.run
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

  putStrLn "*** FRA Example ***"
  (FRAExample.Result i1 i2) <- keepingSettings' FRAExample.run
  printFraIterationResult i1
  putStrLn "* After 100bp shift *"
  printFraIterationResult i2

  putStrLn "*** Swap Example ***"
  (SwapExample.Result si1 si2) <- keepingSettings' SwapExample.run
  printSwapIterationResult si1
  putStrLn "***Updating market data***"
  printSwapIterationResult si2

  putStrLn "*** FittedBondCurve Example ***"
  _ <- keepingSettings' BondCurveExample.run

  putStrLn "DONE"

  where
    printFraIterationResult :: [FRAExample.IterationResult] -> IO ()
    printFraIterationResult rs = forM_ rs $ \r ->
      printf "Fwd rate: %.5f Spt val: %.5f Fwd val: %.5f Impl yld: %.5f Mkt zrate: %.5f NPV: %.5f\n"
        (FRAExample.fwdRateR r)
        (FRAExample.spotR r)
        (FRAExample.fwdValueR r)
        (FRAExample.implYieldR r)
        (FRAExample.zRateR r)
        (FRAExample.npvR r)

    printSwapIterationResult :: [SwapExample.IterationResult] -> IO ()
    printSwapIterationResult rs = forM_ rs $ \r -> do
      printSwapResult "Spt" $ SwapExample.spotSwap r
      printSwapResult "Fwd" $ SwapExample.forwardSwap r

    printSwapResult :: String -> SwapExample.SwapResult -> IO ()
    printSwapResult t r =
      printf "%s Swap: NPV: %.5f Far spread: %.5f Fair rate: %.5f\n"
        t (SwapExample.spotNpvR r) (SwapExample.spotFairSpreadR r) (SwapExample.spotFairRateR r)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
