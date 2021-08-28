module QuantLib.Example.FRA
  (
    Result(..)
  , IterationResult(..)
  , run
  )
where

import Control.Monad(forM, forM_)

import QuantLib.Index
import qualified QuantLib.Index.InterestRate as I
import QuantLib.Instrument
import QuantLib.Instrument.Forward(forwardRateAgreement, asForward, forwardValue, spotValue, impliedYield, forwardRate)
import QuantLib.Time.Date(may)
import QuantLib.Time.Calendar(BusinessDayConvention(..), advance)
import QuantLib.Time.Schedule(TimeUnit(..), dayCounter, DayCounterConstructor(..), Frequency(..))
import qualified QuantLib.InterestRate as IR
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Yield(piecewiseYieldCurve, fraRateHelper, BootstrapTrait(..), zeroRate')
import QuantLib.Math

data IterationResult = IterationResult { fwdRateR :: Double
                        , spotR :: Double
                        , fwdValueR :: Double
                        , implYieldR :: Double
                        , zRateR :: Double
                        , npvR :: Double
                        } deriving Show

data Result = Result [IterationResult] [IterationResult] deriving Show

run :: IO Result
run = do
  setEvaluationDate $ Just todaysDate
  eu3m <- I.iborIndex I.Euribor3M Nothing
  eu3mRI <- I.asInterestRateIndex eu3m
  fraCalendar <- asIndex eu3mRI >>= fixingCalendar
  let fixDays = I.fixingDays eu3mRI
      convention = I.businessDayConvention eu3m
      eom = I.endOfMonth eu3m
  settleDate <- advance fraCalendar todaysDate (fromIntegral fixDays, Days) Following False

  simpleFraQuotes <- mapM simpleQuote quotes
  fraQuotes <- mapM asQuote simpleFraQuotes

  fraDayCounter <- I.dayCounter eu3mRI

  fraInstruments <- mapM
    (\(q, t, p) -> fraRateHelper q t p (fromIntegral fixDays) fraCalendar convention eom fraDayCounter) $
    zip3 fraQuotes starts periods

  tsdc <- dayCounter ActualActualISDA
  fraTS <- piecewiseYieldCurve settleDate fraInstruments tsdc [] Discount LogLinear

  it1 <- valuateFRA convention fraDayCounter settleDate fraTS
  forM_ simpleFraQuotes $ \sq -> asQuote sq >>= value >>= \v -> setValue sq (v + bpsShift)
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
      fraCalendar <- I.asInterestRateIndex eu3m >>= asIndex >>= fixingCalendar
      dates <- forM starts $
        \months -> do
          v <- advance fraCalendar settle (fromIntegral months, Months) convention False
          m <- advance fraCalendar v (fraTermMonths, Months) convention False
          return (v, m)

      mapM (\((v, m), q) -> do
        fra <- forwardRateAgreement v m Long q notional eu3m (Just ts)
        fwd <- asForward fra

        fwdRate <- forwardRate fra
        spot <- spotValue fwd
        fwdValue <- forwardValue fwd
        implYield <- impliedYield fwd spot fwdValue settle IR.Simple dc
        zRate <- zeroRate' ts m dc IR.Simple Annual False
        fraNPV <- asInstrument fwd >>= npv
        return $ IterationResult (IR.rate fwdRate) spot fwdValue (IR.rate implYield) (IR.rate zRate) fraNPV) $
         zip dates quotes


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
