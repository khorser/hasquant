module Main where

import Test.Hspec

import QuantLib.Time.Date(today, weekday)
import qualified QuantLib.Settings as Settings

import qualified QuantLib.Spec.Syntax as Syntax
import qualified QuantLib.Spec.DatesAndSchedule as DatesAndSchedule
import qualified QuantLib.Spec.Calendars as Calendars
import qualified QuantLib.Spec.CurrencyAndDayCounter as CurrencyAndDayCounter
import qualified QuantLib.Spec.InterestRateAndCashFlow as InterestRateAndCashFlow
import qualified QuantLib.Spec.TermStructure as TermStructure
import qualified QuantLib.Spec.Examples as Examples

main :: IO ()
main = do
  putStrLn ">>>"
  putStrLn $ "QuantLib version " ++ Settings.version ++ ", Boost " ++ Settings.boostVersion
  tod <- today
  w <- weekday tod
  putStrLn $ "Today is " ++ show w

  hspec $ do
    Syntax.spec
    DatesAndSchedule.spec
    Calendars.spec tod
    CurrencyAndDayCounter.spec
    InterestRateAndCashFlow.spec tod
    TermStructure.spec
    Examples.spec

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
