module QuantLib.Example.FRA
  (
    Result(..)
  , IterationResult(..)
  , run
  ) where
import Control.Monad(forM, forM_)
import Data.List.NonEmpty(fromList)

import QuantLib.Index
import qualified QuantLib.Index.InterestRate as I
import QuantLib.Instrument
import QuantLib.Instrument.Forward(forwardRateAgreement, forwardRate)
import QuantLib.Time.Date(may)
import QuantLib.Time.Calendar(BusinessDayConvention(..), advance)
import QuantLib.Time.Schedule(TimeUnit(..), dayCounter, DayCounterConstructor(..), Frequency(..))
import qualified QuantLib.InterestRate as IR
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Yield(piecewiseYieldCurve, fraRateHelper, BootstrapTrait(..), zeroRate', PillarChoice(..))
import QuantLib.Math

data IterationResult = IterationResult { fwdRateR :: Double
                        , zRateR :: Double
                        , npvR :: Double
                        } deriving Show

data Result = Result [IterationResult] [IterationResult] deriving Show

run :: IO Result
run = do
  setEvaluationDate $ Just todaysDate
  eu3m <- I.iborIndex I.Euribor3M Nothing
  fraCalendar <- fixingCalendar eu3m
  let fixDays = I.fixingDays eu3m
      convention = I.businessDayConvention eu3m
      eom = I.endOfMonth eu3m
  settleDate <- advance fraCalendar todaysDate (fromIntegral fixDays, Days) Following False

  fraQuotes <- mapM simpleQuote quotes

  fraDayCounter <- I.dayCounter eu3m

  fraInstruments <- mapM
    (\(q, t, p) -> fraRateHelper q t p fixDays fraCalendar convention eom fraDayCounter LastRelevantDate Nothing True) $
    zip3 fraQuotes starts periods

  tsdc <- dayCounter ActualActualISDA
  fraTS <- piecewiseYieldCurve settleDate (fromList fraInstruments) tsdc [] Discount LogLinear

  it1 <- valuateFRA convention fraDayCounter settleDate fraTS
  forM_ fraQuotes $ \sq -> value sq >>= \v -> setValue sq (v + bpsShift)
  it2 <- valuateFRA convention fraDayCounter settleDate fraTS

  return $ Result it1 it2

  where
    todaysDate = 23 `may` 2006
    starts = [1, 2, 3, 6, 9]
    periods = [4, 5, 6, 9, 12]
    quotes = [0.030, 0.031, 0.032, 0.033, 0.034]
    notional = 100.0
    fraTermMonths = 3
    bpsShift = 0.01

    valuateFRA convention dc settle ts = do
      eu3m <- I.iborIndex I.Euribor3M (Just ts)
      fraCalendar <- fixingCalendar eu3m
      dates <- forM starts $
        \months -> do
          v <- advance fraCalendar settle (fromIntegral months, Months) convention False
          m <- advance fraCalendar v (fraTermMonths, Months) convention False
          return (v, m)

      mapM (\((v, m), q) -> do
        fra <- forwardRateAgreement eu3m v m Long q notional (Just ts)

        fwdRate <- forwardRate fra
        zRate <- zeroRate' ts m dc IR.Simple Annual False
        fraNPV <- npv fra
        return $ IterationResult (IR.rate fwdRate) (IR.rate zRate) fraNPV) $
         zip dates quotes


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
