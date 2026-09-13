module Main where

import Test.Hspec

import QuantLib.Time.Date(today, weekday)
import qualified QuantLib.Context as Context

import qualified QuantLib.Spec.Context as ContextSpec
import qualified QuantLib.Spec.DatesAndSchedule as DatesAndSchedule
import qualified QuantLib.Spec.Calendars as Calendars
import qualified QuantLib.Spec.CurrencyAndDayCounter as CurrencyAndDayCounter
import qualified QuantLib.Spec.Commodity as Commodity
import qualified QuantLib.Spec.InterestRateAndCashFlow as InterestRateAndCashFlow
import qualified QuantLib.Spec.TermStructure as TermStructure
import qualified QuantLib.Spec.TermStructure.Commodity as TermStructureCommodity
import qualified QuantLib.Spec.TermStructure.Inflation as TermStructureInflation
import qualified QuantLib.Spec.TermStructure.InflationVolatility as TermStructureInflationVolatility
import qualified QuantLib.Spec.Index.Commodity as IndexCommodity
import qualified QuantLib.Spec.Index.Inflation as IndexInflation
import qualified QuantLib.Spec.Instrument as Instrument
import qualified QuantLib.Spec.Instrument.Bond as InstrumentBond
import qualified QuantLib.Spec.Instrument.CapFloor as InstrumentCapFloor
import qualified QuantLib.Spec.Instrument.Credit as InstrumentCredit
import qualified QuantLib.Spec.Credit as Credit
import qualified QuantLib.Spec.Instrument.Energy as InstrumentEnergy
import qualified QuantLib.Spec.Instrument.Forward as InstrumentForward
import qualified QuantLib.Spec.Instrument.InflationCapFloor as InstrumentInflationCapFloor
import qualified QuantLib.Spec.Instrument.Option as InstrumentOption
import qualified QuantLib.Spec.Instrument.Swap as InstrumentSwap
import qualified QuantLib.Spec.Matrix as Matrix
import qualified QuantLib.Spec.Model as Model
import qualified QuantLib.Spec.PricingEngine as PricingEngine
import qualified QuantLib.Spec.Process as Process
import qualified QuantLib.Spec.Quote as Quote
import qualified QuantLib.Spec.Statistics as Statistics
import qualified QuantLib.Spec.Examples as Examples

main :: IO ()
main = do
  putStrLn ">>>"
  putStrLn $ "QuantLib version " ++ Context.version ++ ", Boost " ++ Context.boostVersion
  evalDate <- today
  w <- weekday evalDate
  putStrLn $ "Today is " ++ show w

  hspec $ do
    ContextSpec.spec
    DatesAndSchedule.spec
    Calendars.spec evalDate
    CurrencyAndDayCounter.spec
    Commodity.spec
    InterestRateAndCashFlow.spec evalDate
    TermStructure.spec
    TermStructureCommodity.spec
    TermStructureInflation.spec
    TermStructureInflationVolatility.spec
    IndexCommodity.spec
    IndexInflation.spec
    Instrument.spec
    InstrumentBond.spec
    InstrumentCapFloor.spec
    InstrumentCredit.spec
    Credit.spec
    InstrumentEnergy.spec
    InstrumentForward.spec
    InstrumentInflationCapFloor.spec
    InstrumentOption.spec
    InstrumentSwap.spec
    Matrix.spec
    Model.spec
    PricingEngine.spec
    Process.spec
    Quote.spec
    Statistics.spec
    Examples.spec

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
