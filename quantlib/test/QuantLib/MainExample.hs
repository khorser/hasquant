module Main where

import Data.List
import Control.Monad(forM_)
import Text.Printf

import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Utilities

import qualified QuantLib.Example.Bond as BondExample
import qualified QuantLib.Example.BermudanSwaption as BermudanSwaptionExample
import qualified QuantLib.Example.CallableBond as CallableBondExample
import qualified QuantLib.Example.CDS as CDSExample
import qualified QuantLib.Example.ConvertibleBond as ConvertibleBondExample
import qualified QuantLib.Example.EquityOption as EquityOptionExample
import qualified QuantLib.Example.FittedBondCurve as BondCurveExample
import qualified QuantLib.Example.FRA as FRAExample
import qualified QuantLib.Example.Replication as ReplicationExample
import qualified QuantLib.Example.Repo as RepoExample
import qualified QuantLib.Example.Swap as SwapExample

main :: IO ()
main = do
  putStrLn $ "QuantLib version " ++ version
     ++ ", Boost " ++ boostVersion
  t <- today
  putStrLn $ "Today is " ++ show (weekday t)

  putStrLn "\n*** Bond Example ***"
  br <- keepingSettings' BondExample.run

  putStrLn $ "NPV: " ++ show (BondExample.npvR br)
  putStrLn $ "Yield: " ++ show (BondExample.yieldR br)
  putStrLn $ "Clean price: " ++ show (BondExample.cleanPriceR br)
  putStrLn $ "Dirty price: " ++ show (BondExample.dirtyPriceR br)
  putStrLn $ "Accrued amount: " ++ show (BondExample.accruedAmountR br)
  putStrLn $ "Previous coupon: " ++ show (BondExample.previousCoupon br)
  putStrLn $ "Next coupon: " ++ show (BondExample.nextCoupon br)
  putStrLn $ "Next coupon date: " ++ show (BondExample.nextCouponDate br)
  putStrLn $ "Floater's clean price from yield: " ++ show (BondExample.cleanPriceFromYieldR br)
  putStrLn $ "Floater's yield from clean price: " ++ show (BondExample.yieldFromCleanPriceR br)
  putStrLn $ "Tradable: " ++ show (BondExample.tradable br)

  putStrLn $ "CashFlows: NPV: " ++ show (BondExample.cfnpvR br) ++ ", NPV_BPS: " ++ show (BondExample.cfnpvbpsR br)
  putStrLn $ "BPS: " ++ show (BondExample.bpsR br)

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
  (FRAExample.Result i1 i2) <- keepingSettings' FRAExample.run
  printFraIterationResult i1
  putStrLn "* After 100bp shift *"
  printFraIterationResult i2

  putStrLn "\n*** Swap Example ***"
  (SwapExample.Result si1 si2) <- keepingSettings' SwapExample.run
  printSwapIterationResult si1
  putStrLn "***Updating market data***"
  printSwapIterationResult si2

  putStrLn "\n*** FittedBondCurve Example ***"
  _ <- keepingSettings' BondCurveExample.run

  putStrLn "\n*** Replication Example ***"
  (ReplicationExample.Result npvInit npvOut npvIn) <- keepingSettings' ReplicationExample.run
  putStrLn $ "Initial PVs (analytic, replicating with 12 dates, 26, 52): " ++ show npvInit
  putStrLn $ "Out of the money PVs (analytic, replicating with 12 dates, 26, 52): " ++ show npvOut
  putStrLn $ "In the money PVs (analytic, replicating with 12 dates, 26, 52): " ++ show npvIn

  putStrLn "\n*** BermudanSwaption Example ***"
  (BermudanSwaptionExample.Result g2v g2p hwv hwp hw2v hw2p bkv bkp npvA npvO npvI) <- keepingSettings' $ BermudanSwaptionExample.run
  _ <- printf "%25s   %8s %8s %8s %8s %8s\n" "Calibrated vols for" "1x5" "2x4" "3x2" "4x2" "5x1"
  printBermudanVols "G2" g2v
  printBermudanVols "Hull-White" hwv
  printBermudanVols "Numerical" hw2v
  printBermudanVols "Black-Karasinski" bkv
  putStrLn ""
  printDoubles "G2 params (a, sigma, b, beta, eta, rho)" g2p
  printDoubles "HW params (a, sigma)" hwp
  printDoubles "Num HW params (a, sigma)" hw2p
  printDoubles "BK params (a, sigma)" bkp
  putStrLn ""
  _ <- printf "%15s   %13s %13s %13s %13s %13s %13s %13s\n" "NPV of" "G2(tree)" "G2(fdm)" "HW(tree)" "HW(fdm)" "HW(num, tree)" "HW(num, fdm)" "BK"
  printBermudanNPVs "ATM Swaption" npvA
  printBermudanNPVs "OTM Swaption" npvO
  printBermudanNPVs "ITM Swaption" npvI

  putStrLn "\n*** Equity Option Example ***"
  (EquityOptionExample.Result analyticEuro analyticHeston bates baw bjs bin int fd mc) <- EquityOptionExample.run
  putStrLn $ "Analytic Euro engine: " ++ show analyticEuro
  putStrLn $ "Analytic Heston model: " ++ show analyticHeston
  putStrLn $ "Bates: " ++ show bates
  putStrLn $ "Barone-Adesi-Whaley: " ++ show baw
  putStrLn $ "Bjerksund-Stensland: " ++ show bjs
  putStrLn $ "Binomial: " ++ show bin
  putStrLn $ "Integral: " ++ show int
  putStrLn $ "Finite differences: " ++ show fd
  putStrLn $ "Monte Carlo: " ++ show mc

  putStrLn "\n*** CDS Example ***"
  (CDSExample.Result probs fairSpread npv defNpv cpnNpv) <- keepingSettings' CDSExample.run
  putStrLn $ "Probabilities: " ++ show probs
  putStrLn $ "Fair spreads: " ++ show fairSpread
  putStrLn $ "NPVs: " ++ show npv
  putStrLn $ "Default leg NPVs: " ++ show defNpv
  putStrLn $ "Coupon leg NPVs: " ++ show cpnNpv

  putStrLn "\n*** Callable Bond Example ***"
  (CallableBondExample.Result ps ys) <- keepingSettings' CallableBondExample.run
  putStrLn $ "Prices: " ++ show ps
  _ <- putStrLn $ "Yields: " ++ show ys

  putStrLn "\n*** Convertible Bond Example ***"
  (ConvertibleBondExample.Result jr crr ad tr ti lr j) <- keepingSettings' ConvertibleBondExample.run
  putStrLn $ "Jarrow-Rudd: " ++ show jr
  putStrLn $ "Cox-Ross-Rubinstein: " ++ show crr
  putStrLn $ "Additive EQP Binomial Tree: " ++ show ad
  putStrLn $ "Trigeorgis: " ++ show tr
  putStrLn $ "Tian: " ++ show ti
  putStrLn $ "Leisen-Reimer: " ++ show lr
  putStrLn $ "Joshi: " ++ show j

  putStrLn "\nDONE"

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

    printBermudanVols :: String -> [Double] -> IO ()
    printBermudanVols m  v= do
      _ <- printf "%25s: " m
      mapM_ (printf " %8.5f") v
      putStrLn ""

    printBermudanNPVs :: String -> [Double] -> IO ()
    printBermudanNPVs m  v= do
      _ <- printf "%15s: " m
      mapM_ (printf " %13.4f") v
      putStrLn ""

    printDoubles :: String -> [Double] -> IO ()
    printDoubles m l = printf "%s: %s\n" m (intercalate ", " $ map (printf "%8.6f") l)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
