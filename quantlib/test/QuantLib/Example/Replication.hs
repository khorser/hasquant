module QuantLib.Example.Replication
  (
    Result(..)
  , run
  )
where

import Control.Monad(foldM)
import Data.Time.Calendar

import QuantLib.Compounding
import QuantLib.Instrument
import QuantLib.Instrument.BarrierType
import QuantLib.Instrument.Option
import QuantLib.Instrument.OptionType
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.ProcessDiscretization
import QuantLib.Settings
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Types

data Result = Result
  { npvInit :: [Double]
  , npvOut :: [Double]
  , npvIn :: [Double]
  } deriving Show

run :: IO Result
run = do
  setEvaluationDate tod
  underlying <- simpleQuote (head underlyingValues)
  underlyingQuote <- asQuote underlying
  riskFreeRate <- simpleQuote 0.04 >>= asQuote
  vol <- simpleQuote 0.20 >>= asQuote
  dc <- actual365Fixed
  cal <- nullCalendar
  flatRate <- flatForward' 0 cal riskFreeRate dc Continuous Annual
  flatVol <- blackConstantVol' 0 cal vol dc
  ex <- europeanExercise maturity >>= asExercise
  payoff <- plainVanillaPayoff optionType strike >>= asStrikedTypePayoff
  bsProcess <- blackScholesProcess underlyingQuote flatRate flatVol EulerDiscretization
  barrierEngine <- analyticBarrierEngine bsProcess
  europeanEngine <- analyticEuropeanEngine bsProcess
  referenceOption <- barrierOption barrierType barrier rebate payoff ex
  refInstrument <- asOneAssetOption referenceOption >>= asOption >>= asInstrument
  setPricingEngine refInstrument barrierEngine
  put1 <- europeanOption payoff ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine put1 europeanEngine
  digitalPut <- cashOrNothingPayoff Put barrier 1.0 >>= (`europeanOption` ex) >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine digitalPut europeanEngine
  put2 <- plainVanillaPayoff Put barrier >>= asStrikedTypePayoff >>= (`europeanOption` ex) >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine put2 europeanEngine
  let p = [(put1, 1), (digitalPut, barrier-strike), (put2, -1)]
  portfolio1 <- foldM (addInstrument europeanEngine underlying) p
    (zip maturities1 killDates1) >>= composite
  portfolio2 <- foldM (addInstrument europeanEngine underlying) p
    (zip maturities2 killDates2) >>= composite
  portfolio3 <- foldM (addInstrument europeanEngine underlying) p
    (zip maturities3 killDates3) >>= composite

  setEvaluationDate tod

  [npv1, npv2, npv3] <- mapM
    (\v -> setValue underlying v
      >> mapM npv [refInstrument, portfolio1, portfolio2, portfolio3])
    underlyingValues

  return Result {
    npvInit = npv1
  , npvOut = npv2
  , npvIn = npv3
  }
  where barrierType = DownOut
        optionType = Put
        tod = 29 `may` 2006
        maturity = addGregorianYearsClip 1 tod
        barrier = 70.0
        rebate = 0.0
        underlyingValues = [100.0, 110.0, 90.0]
        strike = 100.0
        i1 = [12, 11 .. 1]
        maturities1 = map (`addGregorianMonthsClip` tod) i1
        killDates1 = map (\i -> addGregorianMonthsClip (i-1) tod) i1
        i2 = [52, 50 .. 2]
        maturities2 = map (\i -> addDays (i*7) tod) i2
        killDates2 = map (\i -> addDays ((i-2)*7) tod) i2
        i3 = [52, 51 .. 1]
        maturities3 = map (\i -> addDays (i*7) tod) i3
        killDates3 = map (\i -> addDays ((i-1)*7) tod) i3


        addInstrument engine under pp (m, k) = do
          (p, r) <- nextComponent engine under pp m k
          return $ (p, r) : pp

        nextComponent engine under p innerMaturity killDate = do
          innerExercise <- europeanExercise innerMaturity >>= asExercise
          innerPayoff <- plainVanillaPayoff Put barrier >>= asStrikedTypePayoff
          putn <- europeanOption innerPayoff innerExercise >>= asOneAssetOption >>= asOption >>= asInstrument
          setPricingEngine putn engine
          setEvaluationDate killDate
          _ <- setValue under barrier
          portfolioValue <- composite p >>= npv
          putValue <- npv putn
          return (putn, -portfolioValue / putValue)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
