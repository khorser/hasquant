module QuantLib.Example.FRA
  (
    Result(..)
  , IterationResult(..)
  , run
  )
where

import Data.Time.Calendar(Day)
import Control.Monad(forM, forM_)

import QuantLib.Compounding
import QuantLib.Index.Ibor
import QuantLib.Instrument
import QuantLib.Instrument.Forward
import QuantLib.InterestRate
import QuantLib.Math.Interpolation
import QuantLib.PositionType
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Trait
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Unit
import QuantLib.Types


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
  -- I didn't expose most inspector methods so can't retrieve Euribor3M properties here
  fraCalendar <- target
  settleDate <- advance fraCalendar todaysDate fixingDays Days Following False

  simpleFraQuotes <- mapM simpleQuote quotes
  fraQuotes <- mapM asQuote simpleFraQuotes

  fraDayCounter <- actual360
  fraInstruments <- mapM
    (\(q, t, p) -> TS.fraRateHelper q t p (fromIntegral fixingDays) fraCalendar convention eom fraDayCounter) $
    zip3 fraQuotes starts periods

  tsdc <- actualActualISDA
  fraTS <- TS.piecewiseYieldCurve settleDate fraInstruments tsdc [] tolerance Discount LogLinear

  it1 <- valuateFRA settleDate fraTS
  forM_ simpleFraQuotes $ \sq -> asQuote sq >>= value >>= \v -> setValue sq (v + bpsShift)
  it2 <- valuateFRA settleDate fraTS

  return $ Result it1 it2

  where
    todaysDate = 23 `may` 2006
    fixingDays = 2
    starts = [1, 2, 3, 6, 9]
    periods = [4, 5, 6, 9, 12]
    quotes = [0.030, 0.031, 0.032, 0.033, 0.034]
    convention = ModifiedFollowing
    eom = True
    tolerance = 1e-15
    notional = 100.0
    fraTermMonths = 3
    bpsShift = 0.01

    valuateFRA :: Day -> YieldTermStructure -> IO [IterationResult]
    valuateFRA settle ts = do
      dc <- actual360
      eu3m <- euribor3M $ Just ts
      fraCalendar <- target
      dates <- forM starts $
        \months -> do
          v <- advance fraCalendar settle (fromIntegral months) Months convention False
          m <- advance fraCalendar v fraTermMonths Months convention False
          return (v, m)

      mapM (\((v, m), q) -> do
        fra <- forwardRateAgreement v m Long q notional eu3m (Just ts)
        fwd <- asForward fra

        fwdRate <- forwardRate fra
        spot <- spotValue fwd
        fwdValue <- forwardValue fwd
        implYield <- impliedYield fwd spot fwdValue settle Simple dc
        zRate <- TS.zeroRate ts m dc Simple Annual False
        fraNPV <- asInstrument fwd >>= npv
        return $ IterationResult (rate fwdRate) spot fwdValue (rate implYield) (rate zRate) fraNPV) $
         zip dates quotes


-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
