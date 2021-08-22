module Main
where

import Control.Monad(forM_)
import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Utility
import Text.Printf

import qualified QuantLib.Example.FRA as FRA
import qualified QuantLib.Example.Bond as Bond

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

  putStrLn "\n*** FRA Example ***"
  (FRA.Result i1 i2) <- keepingSettings' FRA.run
  printFraIterationResult i1
  putStrLn "* After 100bp shift *"
  printFraIterationResult i2

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
