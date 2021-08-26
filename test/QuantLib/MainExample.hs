module Main
where

import Control.Monad(forM_, void)
import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Utility
import Text.Printf

import qualified QuantLib.Example.FRA as FRA
import qualified QuantLib.Example.Bond as Bond
import qualified QuantLib.Example.Swap as SwapExample
import qualified QuantLib.Example.Repo as RepoExample
import qualified QuantLib.Example.FittedBondCurve as BondCurveExample

main :: IO ()
main = do
  putStrLn $ "QuantLib version " ++ version
     ++ ", Boost " ++ boostVersion
  t <- today
  wd <- weekday t
  putStrLn $ "Today is " ++ show wd

  putStrLn "\n*** Bond Example ***"
  br <- keepingSettings' Bond.run
  putStrLn $ "NPV: " ++ show (Bond.npvR br)
  putStrLn $ "Yield: " ++ show (Bond.yieldR br)
  putStrLn $ "Clean price: " ++ show (Bond.cleanPriceR br)
  putStrLn $ "Dirty price: " ++ show (Bond.dirtyPriceR br)
  putStrLn $ "Accrued amount: " ++ show (Bond.accruedAmountR br)
  putStrLn $ "Previous coupon: " ++ show (Bond.previousCoupon br)
  putStrLn $ "Next coupon: " ++ show (Bond.nextCoupon br)
  putStrLn $ "Next coupon date: " ++ show (Bond.nextCouponDate br)
  putStrLn $ "Floater's clean price from yield: " ++ show (Bond.cleanPriceFromYieldR br)
  putStrLn $ "Floater's yield from clean price: " ++ show (Bond.yieldFromCleanPriceR br)
  putStrLn $ "Tradable: " ++ show (Bond.tradable br)
  putStrLn $ "CashFlows: NPV: " ++ show (Bond.cfnpvR br) ++ ", NPV_BPS: " ++ show (Bond.cfnpvbpsR br)
  putStrLn $ "BPS: " ++ show (Bond.bpsR br)

  putStrLn "\n*** Repo Example ***"
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

  putStrLn "\n*** FRA Example ***"
  (FRA.Result i1 i2) <- keepingSettings' FRA.run
  printFraIterationResult i1
  putStrLn "* After 100bp shift *"
  printFraIterationResult i2

  putStrLn "\n*** Swap Example ***"
  (SwapExample.Result si1 si2) <- keepingSettings' SwapExample.run
  printSwapIterationResult si1
  putStrLn "***Updating market data***"
  printSwapIterationResult si2

  putStrLn "\n*** FittedBondCurve Example ***"
  (BondCurveExample.Result s r1 r2 r3 r4) <- keepingSettings' BondCurveExample.run
  putStrLn $ "Bond settlement date: " ++ show s
  printBondCurveInfo r1
  printBondCurveInfo r2
  printBondCurveInfo r3
  printBondCurveInfo r4

  putStrLn "\nDONE"

  where
    printFraIterationResult :: [FRA.IterationResult] -> IO ()
    printFraIterationResult rs = forM_ rs $ \r ->
      printf "Fwd rate: %.5f Spt val: %.5f Fwd val: %.5f Impl yld: %.5f Mkt zrate: %.5f NPV: %.5f\n"
        (FRA.fwdRateR r)
        (FRA.spotR r)
        (FRA.fwdValueR r)
        (FRA.implYieldR r)
        (FRA.zRateR r)
        (FRA.npvR r)

    printSwapIterationResult :: [SwapExample.IterationResult] -> IO ()
    printSwapIterationResult rs = forM_ rs $ \r -> do
      printSwapResult "Spt" $ SwapExample.spotSwap r
      printSwapResult "Fwd" $ SwapExample.forwardSwap r

    printSwapResult :: String -> SwapExample.SwapResult -> IO ()
    printSwapResult t r =
      printf "%s Swap: NPV: %.5f Far spread: %.5f Fair rate: %.5f\n"
        t (SwapExample.spotNpvR r) (SwapExample.spotFairSpreadR r) (SwapExample.spotFairRateR r)

    printBondCurveInfo :: BondCurveExample.Rate -> IO ()
    printBondCurveInfo (BondCurveExample.Rate date iter tenors rates) = do
      void $ printf "Reference date: %s, iterations: " $ show date
      forM_ iter (printf "%d ")
      putStrLn ""
      forM_ (zip tenors rates) (\(t, r) -> do
        void $ printf "Tenor %5.2fY: " t
        forM_ r (printf "%.3f ")
        putStrLn "")
      putStrLn ""

