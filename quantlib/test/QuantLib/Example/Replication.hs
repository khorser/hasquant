module QuantLib.Example.Replication
  (
    Result(..)
  , run
  )
where

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
  , errorInit :: [Double]
  , npvOut :: [Double]
  , errorOut :: [Double]
  , npvIn :: [Double]
  , errorIn :: [Double]
  } deriving Show

run :: IO Result
run = do
  setEvaluationDate tod
  underlying <- simpleQuote underlyingValue >>= asQuote
  riskFreeRate <- simpleQuote 0.04 >>= asQuote
  vol <- simpleQuote 0.20 >>= asQuote
  dc <- actual365Fixed
  cal <- nullCalendar
  flatRate <- flatForward' 0 cal riskFreeRate dc Continuous Annual
  flatVol <- blackConstantVol' 0 cal vol dc
  ex <- europeanExercise maturity >>= asExercise
  payoff <- plainVanillaPayoff optionType strike >>= asStrikedTypePayoff
  bsProcess <- blackScholesProcess underlying flatRate flatVol EulerDiscretization
  barrierEngine <- analyticBarrierEngine bsProcess
  europeanEngine <- analyticEuropeanEngine bsProcess
  referenceOption <- barrierOption barrierType barrier rebate payoff ex
  refInstrument <- asOneAssetOption referenceOption >>= asOption >>= asInstrument
  setPricingEngine refInstrument barrierEngine
  referenceValue <- npv refInstrument
  put1 <- europeanOption payoff ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine put1 europeanEngine
  digitalPayoff <- cashOrNothingPayoff Put barrier 1.0
  digitalPut <- europeanOption digitalPayoff ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine digitalPut europeanEngine
  lowerPayoff <- plainVanillaPayoff Put barrier >>= asStrikedTypePayoff
  put2 <- europeanOption lowerPayoff ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine put2 europeanEngine
  portfolio1 <- composite [(put1, 1), (digitalPut, barrier-strike), (put2, -1)]
  portfolio2 <- composite [(put1, 1), (digitalPut, barrier-strike), (put2, -1)]
  portfolio3 <- composite [(put1, 1), (digitalPut, barrier-strike), (put2, -1)]

  return Result {
    npvInit = [referenceValue]
  , errorInit = [0]
  , npvOut = [0]
  , errorOut = [0]
  , npvIn = [0]
  , errorIn = [0]
  }
  where barrierType = DownOut
        optionType = Put
        tod = 29 `may` 2006
        maturity = addGregorianYearsClip 1 tod
        barrier = 70.0
        rebate = 0.0
        underlyingValue = 100.0
        strike = 100.0

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
