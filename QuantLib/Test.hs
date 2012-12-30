module Main(main)
where

import Prelude hiding(catch)

import Data.Time.Calendar
import Control.Exception

import qualified QuantLib.Utilities as Utilities
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Error as Error

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
        putStrLn "OK"
