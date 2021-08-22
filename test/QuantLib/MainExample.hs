module Main
where

import Control.Monad(forM_)
import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Utility
import Text.Printf

import qualified QuantLib.Example.FRA as FRA

main :: IO ()
main = do
  putStrLn $ "QuantLib version " ++ version
     ++ ", Boost " ++ boostVersion
  t <- today
  wd <- weekday t
  putStrLn $ "Today is " ++ show wd

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
