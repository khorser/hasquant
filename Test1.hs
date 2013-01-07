{-# LANGUAGE ScopedTypeVariables #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module Main(main)
where

import Data.Time.Calendar(fromGregorian)

import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import qualified QuantLib.Time.DateGenerationRule as DateGenerationRule
import qualified QuantLib.Time.Period as Period
import qualified QuantLib.Time.Schedule as Schedule
import qualified QuantLib.Time.Unit as Unit
import qualified QuantLib.Utilities as Utilities

-- Main --
main :: IO ()
main = do putStrLn $ "QuantLib version " ++ Utilities.version
            ++ ", Boost " ++ Utilities.boostVersion
          tenor <- Period.period 1 Unit.Months
          cal <- Calendar.russia
          _ <- Schedule.schedule'
               (Just (fromGregorian 2012 12 20))
               (fromGregorian 2013 12 21)
               tenor
               cal
               BusinessDayConvention.Following
               BusinessDayConvention.Unadjusted
               DateGenerationRule.Forward
               False
               (Just (fromGregorian 2012 12 21))
               (Just (fromGregorian 2013 12 21))

          cal2 <- Calendar.russia
          s <- Schedule.schedule
              [fromGregorian 2012 12 20, fromGregorian 2013 5 20]
              cal2
              BusinessDayConvention.Following
          _ <- Schedule.until s (fromGregorian 2013 4 15)
          return ()
