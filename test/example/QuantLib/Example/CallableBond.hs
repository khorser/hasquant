{-# LANGUAGE TemplateHaskell, OverloadedLists #-}
module QuantLib.Example.CallableBond
  (
    Result(..)
  , run
  ) where
import Control.Monad(mapAndUnzipM)
import Data.Time.Calendar

import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Bond
import QuantLib.Model
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Settings
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Syntax

data Result = Result
  { pricesR :: [Double]
  , yieldsR :: [Double]
  }

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  bbdc <- dayCounter ActualActualBond
  q <- simpleQuote 0.055
  flatRate <- flatForward evalDate q bbdc Compounded Semiannual

  callDates <- (firstCallDate :) <$> buildSchedule 23 firstCallDate
  let callSchedule = map (Callability (100.0, Clean) CallabilityCall) callDates

  cal <- calendar UnitedStatesGovernmentBond
  sch <- schedule (Just $ 16 `september` 2004) (15 `september` 2012) (3, Months) cal Unadjusted Unadjusted Backward False Nothing Nothing

  b <- callableFixedRateBond 3 100.0 sch [0.0465] bbdc Unadjusted 100.0 (Just $ 16 `september` 2004) callSchedule (0, Days) cal Unadjusted False

  (ps, ys) <- mapAndUnzipM (priceBond flatRate bbdc b) [epsilon, 0.01, 0.03, 0.06, 0.12]

  return Result {
    pricesR = ps
  , yieldsR = ys
  }
  where evalDate = 16 `october` 2007
        firstCallDate = 15 `september` 2006

        -- the k call dates following `prev`, each 3 months after the one before.
        -- Replaces a foldM over a prepending accumulator, which needed a
        -- `buildSchedule [] _ = error "Impossible happened"` clause to be total and
        -- a final `reverse` to get back into ascending order.
        buildSchedule :: Int -> Day -> IO [Day]
        buildSchedule 0 _ = pure []
        buildSchedule k prev = do
          n <- calendar Null >>= $(free1st 'advance) prev (3, Months) Following False
          (n :) <$> buildSchedule (k - 1) n

        priceBond ts dc b sigma = do
          hw <- hullWhite ts 0.03 sigma >>= asOneFactorAffineModel >>= asShortRateModel
          engine <- treeCallableFixedRateBondEngine hw 40 Nothing
          asInstrument b >>= (`QuantLib.Instrument.setPricingEngine` engine)
          cp <- currentCleanPrice b
          y <- yield b dc Compounded Quarterly 1.0e-8 1000 (0.05, Clean)
          return (cp, 100 * y)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
