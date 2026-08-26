module QuantLib.Example.Swaption
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar(addGregorianYearsClip)

import QuantLib.Index(fixingCalendar)
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.Instrument.Swap
import QuantLib.InterestRate(Compounding(..))
import QuantLib.PricingEngine
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

-- |Ports swaption.cpp's testCachedValue (the plain 'VanillaSwap' half of it,
-- not the overnight-indexed one): a physically-settled European payer
-- swaption on a 5y-into-10y EUR fixed-vs-Euribor6M swap, priced with a flat
-- 20% Black vol against a flat 5% discount curve.
newtype Result = Result
  { npv1 :: Double
  } deriving Show

run :: IO Result
run = do
  let today = 13 `march` 2002
      settlementDate = 15 `march` 2002
  setEvaluationDate (Just today)

  act365 <- dayCounter Actual365FixedStandard
  flatQuote <- simpleQuote 0.05
  ts <- TS.flatForward settlementDate flatQuote act365 Continuous Annual

  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
  cal <- fixingCalendar euribor6m
  floatDayCount <- IR.dayCounter euribor6m

  exerciseDate <- advance cal settlementDate (5, Years) Following False
  startDate <- advance cal exerciseDate (2, Days) Following False
  let maturityDate = addGregorianYearsClip 10 startDate

  fixedDC <- dayCounter Thirty360BondBasis
  fixedSchedule <- schedule (Just startDate) maturityDate (1, Years) cal
    ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
  floatSchedule <- schedule (Just startDate) maturityDate (6, Months) cal
    ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

  swp <- vanillaSwap Payer 1.0 fixedSchedule 0.06 fixedDC floatSchedule
    euribor6m 0.0 floatDayCount Nothing Nothing
  swapEngine <- discountingSwapEngine ts Nothing Nothing Nothing
  asSwap swp >>= asInstrument >>= (`setPricingEngine` swapEngine)

  volQuote <- simpleQuote 0.20
  engine <- blackSwaptionEngine ts volQuote act365 0.0 SwapRate

  swpn <- swaption swp (European (EuropeanExercise exerciseDate)) Physical PhysicalOTC
  setPricingEngine swpn engine
  n <- npv swpn

  pure Result { npv1 = n }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
