module Main where

import Control.Monad(forM_, void)
import Text.Printf(printf)
import Data.List(intercalate)

import QuantLib.Settings
import QuantLib.Time.Date

import qualified QuantLib.Example.QuickStart as QuickStart
import qualified QuantLib.Example.FRA as FRA
import qualified QuantLib.Example.Bond as Bond
import qualified QuantLib.Example.Swap as SwapExample
import qualified QuantLib.Example.Repo as RepoExample
import qualified QuantLib.Example.FittedBondCurve as BondCurveExample
import qualified QuantLib.Example.BermudanSwaption as BermudanSwaptionExample
import qualified QuantLib.Example.CallableBond as CallableBondExample
import qualified QuantLib.Example.CDS as CDSExample
import qualified QuantLib.Example.ConvertibleBond as ConvertibleBondExample
import qualified QuantLib.Example.EquityOption as EquityOptionExample
import qualified QuantLib.Example.Replication as ReplicationExample
import qualified QuantLib.Example.TARF as TARF
import qualified QuantLib.Example.CVAIRS as CVAIRSExample
import qualified QuantLib.Example.ShortRateModels as ShortRateModelsExample
import qualified QuantLib.Example.HaskellLSM as HaskellLSMExample

main :: IO ()
main = do
  putStrLn $ "QuantLib version " ++ version
     ++ ", Boost " ++ boostVersion
  t <- today
  wd <- weekday t
  putStrLn $ "Today is " ++ show wd

  putStrLn "\n*** QuickStart Example ***"
  qr <- keepingSettings' QuickStart.run
  putStrLn $ "NPV: " ++ show (QuickStart.quickNpv qr)
  putStrLn $ "Fair rate: " ++ show (QuickStart.quickFairRate qr)

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
  rr <- keepingSettings' $ RepoExample.run True
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
  (BondCurveExample.Result ss r1 r2 r3 r4) <- keepingSettings' BondCurveExample.run
  putStrLn $ "Bond settlement date: " ++ show ss
  printBondCurveInfo r1
  printBondCurveInfo r2
  printBondCurveInfo r3
  printBondCurveInfo r4

  putStrLn "\n*** Replication Example ***"
  (ReplicationExample.Result npvInit npvOut npvIn) <- keepingSettings' ReplicationExample.run
  void $ printf "%20s %19s %19s %19s %19s\n" "NPV of" "Analytic" "12-day replication" "26-day replication" "52-day replication"
  printDLine "%20s" "Initial" "%20.6f" npvInit
  printDLine "%20s" "Out of the money" "%20.6f" npvOut
  printDLine "%20s" "In the money" "%20.6f" npvIn

  putStrLn "\n*** BermudanSwaption Example ***"
  (BermudanSwaptionExample.Result g2v g2p hwv hwp hw2v hw2p bkv bkp npvA npvO npvI) <- keepingSettings' BermudanSwaptionExample.run
  void $ printf "%25s %8s %8s %8s %8s %8s\n" "Calibrated vols for" "1x5" "2x4" "3x3" "4x2" "5x1"
  printDLine "%25s" "G2" "%9.5f" g2v
  printDLine "%25s" "Hull-White" "%9.5f" hwv
  printDLine "%25s" "Numerical" "%9.5f" hw2v
  printDLine "%25s" "Black-Karasinski" "%9.5f" bkv
  putStrLn ""
  printDoubles "G2 params (a, sigma, b, beta, eta, rho)" g2p
  printDoubles "HW params (a, sigma)" hwp
  printDoubles "Num HW params (a, sigma)" hw2p
  printDoubles "BK params (a, sigma)" bkp
  putStrLn ""
  void $ printf "%15s %13s %13s %13s %13s %13s %13s %13s\n" "NPV of" "G2(tree)" "G2(fdm)" "HW(tree)" "HW(fdm)" "HW(num, tree)" "HW(num, fdm)" "BK"
  printDLine "%15s" "ATM Swaption" "%14.4f" npvA
  printDLine "%15s" "OTM Swaption" "%14.4f" npvO
  printDLine "%15s" "ITM Swaption" "%14.4f" npvI

  putStrLn "\n*** Equity Option Example ***"
  (EquityOptionExample.Result analyticEuro analyticHeston bates baw bjs bin int fd (mcE, mcE2, mcA)) <- EquityOptionExample.run
  void $ printf "%30s   %9s %9s %9s\n" "NPV of" "European" "Bermudan" "American"
  printEquityOptNPVs "Black-Scholes" (europeanOnly analyticEuro)
  printEquityOptNPVs "Heston semi-analytic" (europeanOnly analyticHeston)
  printEquityOptNPVs "Bates semi-analytic" (europeanOnly bates)
  printEquityOptNPVs "Barone-Adesi/Whaley" (americanOnly baw)
  printEquityOptNPVs "Bjerksund/Stensland" (americanOnly bjs)
  printEquityOptNPVs "Integral" (europeanOnly int)
  printEquityOptNPVs "Finite differences" (allExercises fd)
  mapM_ (uncurry printEquityOptNPVs)
    (zip
      ["Binomial Jarrow-Rudd",
        "Binomial Cox-Ross-Rubinstein",
        "Additive equiprobabilities",
        "Binomial Trigeorgis",
        "Binomial Tian",
        "Binomial Leisen-Reimer",
        "Binomial Joshi"]
      (map allExercises bin))
  printEquityOptNPVs "MC (crude)" (europeanOnly [mcE])
  printEquityOptNPVs "QMC (Sobol)" (europeanOnly [mcE2])
  printEquityOptNPVs "MC (longstaff Schwartz)" (americanOnly [mcA])

  putStrLn "\n*** CDS Example ***"
  (CDSExample.Result probs fairSpread npv defNpv cpnNpv) <- keepingSettings' CDSExample.run
  printDoubles "Survival probabilities (1Y, 2Y)" probs
  void $ printf "%15s %15s %15s %15s %15s\n" "" "3M" "6M" "1Y" "2Y"
  printDLine "%15s" "Fair spread" "%16.6f" fairSpread
  printDLine "%15s" "NPV" "%16.5e" npv
  printDLine "%15s" "Default leg NPV" "%16.2f" defNpv
  printDLine "%15s" "Coupon leg NPV" "%16.2f" cpnNpv

  putStrLn "\n*** Callable Bond Example ***"
  (CallableBondExample.Result ps ys) <- keepingSettings' CallableBondExample.run
  void $ printf "%5s   %10s %10s %10s %10s %10s\n" "" "sigma=0.0" "sigma=1.0" "sigma=3.0" "sigma=6.0" "sigma=12.0"
  printDLine "%5s" "Price" "%11.2f" ps
  printDLine "%5s" "Yield" "%11.2f" ys

  putStrLn "\n*** Convertible Bond Example ***"
  (ConvertibleBondExample.Result jr crr ad tr ti lr j) <- keepingSettings' ConvertibleBondExample.run
  void $ printf "%30s %10s %10s\n" "NPV for Tree" "European" "American"
  printDLine "%30s" "Jarrow-Rudd" "%11.6f" jr
  printDLine "%30s" "Cox-Ross-Rubinstein" "%11.6f" crr
  printDLine "%30s" "Additive equiprobabilities" "%11.6f" ad
  printDLine "%30s" "Trigeorgis" "%11.6f" tr
  printDLine "%30s" "Tian" "%11.6f" ti
  printDLine "%30s" "Leisen-Reimer" "%11.6f" lr
  printDLine "%30s" "Joshi" "%11.6f" j

  putStrLn "\n*** Straightforward Monte Carlo pricing of an FX TARF Example ***"
  (TARF.Result tnpv fwds simFwds) <- keepingSettings' TARF.run
  putStrLn $ "NPV: " ++ show tnpv
  putStrLn $ "Forward Rates:           " ++ show fwds
  putStrLn $ "Simulated Forward Rates: " ++ show simFwds

  putStrLn "\n*** LSM Regression Benchmark ***"
  lsmBench <- keepingSettings' $ HaskellLSMExample.run True
  printf "lsmRegress (QuantLib solve): %.6fs, price %.6f\n"
    (HaskellLSMExample.lsmSeconds lsmBench) (HaskellLSMExample.lsmPrice lsmBench)
  printf "Haskell normal equations: %.6fs, price %.6f\n"
    (HaskellLSMExample.haskellSeconds lsmBench) (HaskellLSMExample.haskellPrice lsmBench)
  putStrLn "(CPU time covers backward induction only; both use identical pre-generated paths.)"

  putStrLn "\n*** CVA IRS Example ***"
  (CVAIRSExample.Result rows) <- keepingSettings' CVAIRSExample.run
  putStrLn "-- Correction in the contract fix rate in bp --"
  void $ printf "%4s %8s %8s %8s %8s\n" "Tenor" "FairRate" "Low" "Medium" "High"
  forM_ rows $ \(CVAIRSExample.SwapRow tt fr lo med hi) ->
    printf "%4d %8.3f %8.2f %8.2f %8.2f\n" tt (fr*100) lo med hi

  putStrLn "\n*** Short Rate Models Example ***"
  srm <- keepingSettings' ShortRateModelsExample.run
  printCalibration "cachedHullWhite" (ShortRateModelsExample.cachedHullWhite srm)
  printCalibration "cachedHullWhiteFixedReversion" (ShortRateModelsExample.cachedHullWhiteFixedReversion srm)
  printCalibration "cachedHullWhite2" (ShortRateModelsExample.cachedHullWhite2 srm)
  let swapDiffs = map (\s -> abs (ShortRateModelsExample.expectedNPV s - ShortRateModelsExample.calculatedNPV s))
        (ShortRateModelsExample.swaps srm)
  printf "swaps: max |expected-calculated| NPV over %d entries: %.6f\n" (length swapDiffs) (maximum swapDiffs)
  forM_ (ShortRateModelsExample.futuresConvexityBias srm) $ \c ->
    printf "futuresConvexityBias: T=%.3f a=%.5f expected=%.7f calculated=%.7f\n"
      (ShortRateModelsExample.convexityT c) (ShortRateModelsExample.convexityA c)
      (ShortRateModelsExample.expectedForward c) (ShortRateModelsExample.calculatedForward c)
  printDiscountCheck "extendedCirDiscountFactor" (ShortRateModelsExample.extendedCirDiscountFactor srm)
  printDiscountCheck "vasicekDiscountFactorSmallMeanReversion" (ShortRateModelsExample.vasicekDiscountFactorSmallMeanReversion srm)

  putStrLn "\nDONE"

  where
    printCalibration :: String -> ShortRateModelsExample.CalibrationResult -> IO ()
    printCalibration label cr = printf "%s: a = %.6f (cached %.6f), sigma = %.6f (cached %.6f), value = %.6f (cached %.6f)\n"
      label (ShortRateModelsExample.calculatedA cr) (ShortRateModelsExample.cachedA cr)
      (ShortRateModelsExample.calculatedSigma cr) (ShortRateModelsExample.cachedSigma cr)
      (ShortRateModelsExample.calculatedValue cr) (ShortRateModelsExample.cachedValue cr)

    printDiscountCheck :: String -> ShortRateModelsExample.DiscountCheck -> IO ()
    printDiscountCheck label dc = printf "%s: expected=%.8f calculated=%.8f\n" label
      (ShortRateModelsExample.expectedDF dc) (ShortRateModelsExample.calculatedDF dc)

    printFraIterationResult :: [FRA.IterationResult] -> IO ()
    printFraIterationResult rs = forM_ rs $ \r ->
      printf "Fwd rate: %.5f Mkt zrate: %.5f NPV: %.5f\n"
        (FRA.fwdRateR r)
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

    -- The equity option table has three columns (European, Bermudan, American) but
    -- most engines price only one or two of them. 'Nothing' is the absent cell.
    -- Keep an absent result distinct from a legitimate zero NPV.
    europeanOnly, americanOnly, allExercises :: [Double] -> [Maybe Double]
    europeanOnly v = map Just v ++ [Nothing, Nothing]
    americanOnly v = [Nothing, Nothing] ++ map Just v
    allExercises = map Just

    printEquityOptNPVs :: String -> [Maybe Double] -> IO ()
    printEquityOptNPVs m v = do
      void $ printf "%30s: " m
      mapM_ (maybe (printf " %9s" "N/A") (printf " %9.6f")) v
      putStrLn ""

    printDoubles :: String -> [Double] -> IO ()
    printDoubles m l = printf "%s: %s\n" m (intercalate ", " $ map (printf "%8.6f") l)

    printDLine :: String -> String -> String -> [Double] -> IO ()
    printDLine mf m vf v = do
      void $ printf mf m
      mapM_ (printf vf) v
      putStrLn ""
