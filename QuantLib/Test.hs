module Main(main)
where

import Control.Exception
import Data.Time.Calendar
import Prelude hiding(catch)

import qualified QuantLib.Date as Date
import qualified QuantLib.Error as Error
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Utilities as Utilities

main :: IO ()
main = do
        putStrLn Utilities.version
        putStrLn Utilities.boostVersion
        d <- Settings.evaluationDate
        print d
        Settings.setEvaluationDate $ fromGregorian 2012 12 29
        d1 <- Settings.evaluationDate
        print d1
        catch (Settings.setEvaluationDate $ fromGregorian 1861 1 1)
            (\e -> putStrLn $ "Caught QuantLib exception: " ++ Error.message e)
        e <- Settings.enforceTodaysHistoricFixings
        print e
        Settings.setEnforceTodaysHistoricFixings True
        e1 <- Settings.enforceTodaysHistoricFixings
        print e1
        putStrLn $ "MinDate: " ++ show Date.minDate
        putStrLn $ "MaxDate: " ++ show Date.maxDate
        putStrLn $ "Leap years: " ++ show (Date.isLeap
            [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5])
        putStrLn "OK"
