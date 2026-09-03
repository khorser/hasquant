module Main where

import Test.Hspec

import QuantLib.Time.Date(today, weekday)
import qualified QuantLib.Settings as Settings

import qualified QuantLib.Spec.Syntax as Syntax
import qualified QuantLib.Spec.DatesAndSchedule as DatesAndSchedule
import qualified QuantLib.Spec.Calendars as Calendars
import qualified QuantLib.Spec.CurrencyAndDayCounter as CurrencyAndDayCounter
import qualified QuantLib.Spec.Commodity as Commodity
import qualified QuantLib.Spec.InterestRateAndCashFlow as InterestRateAndCashFlow
import qualified QuantLib.Spec.TermStructure as TermStructure
import qualified QuantLib.Spec.TermStructure.Commodity as TermStructureCommodity
import qualified QuantLib.Spec.TermStructure.InflationVolatility as TermStructureInflationVolatility
import qualified QuantLib.Spec.Index.Commodity as IndexCommodity
import qualified QuantLib.Spec.Instrument as Instrument
import qualified QuantLib.Spec.Instrument.CapFloor as InstrumentCapFloor
import qualified QuantLib.Spec.Instrument.Credit as InstrumentCredit
import qualified QuantLib.Spec.Instrument.Energy as InstrumentEnergy
import qualified QuantLib.Spec.Instrument.InflationCapFloor as InstrumentInflationCapFloor
import qualified QuantLib.Spec.Instrument.Option as InstrumentOption
import qualified QuantLib.Spec.Instrument.Swap as InstrumentSwap
import qualified QuantLib.Spec.Model as Model
import qualified QuantLib.Spec.PricingEngine as PricingEngine
import qualified QuantLib.Spec.Process as Process
import qualified QuantLib.Spec.Quote as Quote
import qualified QuantLib.Spec.Examples as Examples

main :: IO ()
main = do
  putStrLn ">>>"
  putStrLn $ "QuantLib version " ++ Settings.version ++ ", Boost " ++ Settings.boostVersion
  evalDate <- today
  w <- weekday evalDate
  putStrLn $ "Today is " ++ show w

  hspec $ do
    Syntax.spec
    DatesAndSchedule.spec
    Calendars.spec evalDate
    CurrencyAndDayCounter.spec
    Commodity.spec
    InterestRateAndCashFlow.spec evalDate
    TermStructure.spec
    TermStructureCommodity.spec
    TermStructureInflationVolatility.spec
    IndexCommodity.spec
    Instrument.spec
    InstrumentCapFloor.spec
    InstrumentCredit.spec
    InstrumentEnergy.spec
    InstrumentInflationCapFloor.spec
    InstrumentOption.spec
    InstrumentSwap.spec
    Model.spec
    PricingEngine.spec
    Process.spec
    Quote.spec
    Examples.spec

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
