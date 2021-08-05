module Main
where

--import QuantLib.Utilities
--main = putStrLn version >> putStrLn boostVersion

--import Control.Exception
--import QuantLib.Types
--main = throwIO (CPlusPlusException "qqq")  `catch` \e -> putStrLn ("Caught " ++ show (e :: Error))

--import Data.Time.Calendar
--import QuantLib.Time.Date
--main = do
--  let x = fromGregorian 2021 8 3
--  w <- weekday x
--  putStrLn (show w)
--  putStrLn (show minDate)
--  d <- dayOfYear x
--  putStrLn (show d)

--import QuantLib.Settings
--import QuantLib.Date
--
--main = do
--  setEvaluationDate $ Just (1 `january` 2021)
--  vd <- evaluationDate
--  setEvaluationDate Nothing
--  vd <- evaluationDate
--  putStrLn (show vd)

--import QuantLib.Date
--import QuantLib.Period
--main = do
--  p <- fromFrequency Weekly
--  x <- immDate "H4" (20 `march` 2013)
--  putStrLn $ show p

import QuantLib.Date
import Control.Monad(liftM)

main = do
  ds <- knownECBDates
  let x = map show ds
  mapM_ putStrLn x
