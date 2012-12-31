module Main(main)
where

import Control.Exception
import Data.Time.Calendar
import Data.Time.Clock
import Data.Time.LocalTime
import Prelude hiding(catch)
import Test.HUnit

import qualified QuantLib.Date as Date
import qualified QuantLib.Error as Error
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Utilities as Utilities

today :: IO Day
today =
  do now <- getCurrentTime
     tz <- getTimeZone now
     return $ localDay $ utcToLocalTime tz now

settings :: Test
settings = TestList
  [
    "evaluation date 1"
      ~: do t1 <- Settings.evaluationDate
            t2 <- today
            assertEqual "default valuation date" t1 t2
  , "evaluation date 2"
      ~: do Settings.setEvaluationDate (fromGregorian 2012 12 29)
            t1 <- Settings.evaluationDate
            assertEqual "new valuation date" t1 (fromGregorian 2012 12 29)
  , "invalid evaluation date"
      ~: catch
          (do Settings.setEvaluationDate (fromGregorian 1861 1 1)
              assertFailure "invalid evaluation date passed through")
          (assertBool "exception message not empty" . not . null . Error.message)
  , "enforce today's historic fixings 1"
      ~: do e1 <- Settings.enforceTodaysHistoricFixings
            assertEqual "default enforce today's historic fixings" e1 False
  , "enforce today's historic fixings 2"
      ~: do Settings.setEnforceTodaysHistoricFixings True
            e1 <- Settings.enforceTodaysHistoricFixings
            assertEqual "new enforce today's historic fixings" e1 True
  ]

dates :: Test
dates = test
  [
    "min date" ~: "min date" ~:
      Date.minDate ~?= fromGregorian 1901 01 01
  , "max date" ~: "max date" ~:
      Date.maxDate ~?= fromGregorian 2199 12 31
  , "leap years" ~: "leap year" ~:
      [False, True, False] ~=? Date.isLeap
            [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5]
  ]

main :: IO ()
main = do
        putStrLn $
          "QuantLib version " ++ Utilities.version
          ++ ", Boost " ++ Utilities.boostVersion
        _ <- runTestTT $ test [settings, dates]
        return ()
