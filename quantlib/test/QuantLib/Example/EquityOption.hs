module QuantLib.Example.EquityOption
  (
    Result(..)
  , run
  )
where

import Data.Time.Calendar

import QuantLib.Compounding
import QuantLib.Instances
import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.Instrument.OptionType
import QuantLib.Model
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.ProcessDiscretization
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Types

data Result = Result
  { npvR :: Double
  }

run :: IO Result
run = do
  setEvaluationDate tod
  cal <- target
  dc <- actual365Fixed
  europeanEx <- europeanExercise maturity >>= asExercise
  bermudanEx <- bermudanExercise exDates False >>= asExercise
  americanEx <- americanExercise' maturity False >>= asExercise
  underQ <- simpleQuote under >>= asQuote
  riskFreeQ <- simpleQuote riskFreeRate >>= asQuote
  ts <- flatForward settl riskFreeQ dc Continuous Annual
  divQ <- simpleQuote dividend >>= asQuote
  divTS <- flatForward settl divQ dc Continuous Annual 
  volQ <- simpleQuote vol >>= asQuote
  volTS <- blackConstantVol settl cal volQ dc
  payoff <- plainVanillaPayoff optType strike >>= asStrikedTypePayoff
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization
  europeanOpt <- vanillaOption payoff europeanEx
  bermudanOpt <- vanillaOption payoff bermudanEx
  americanOpt <- vanillaOption payoff americanEx
  europeanInst <- asOneAssetOption europeanOpt >>= asOption >>= asInstrument

  euroEng <- analyticEuropeanEngine bsmProc
  setPricingEngine europeanInst euroEng
  npv europeanInst >>= print

  hestonProc <- hestonProcess ts divTS underQ (vol*vol) 1.0 (vol*vol) 0.001 0.0 HestonQuadraticExponentialMartingale
  hestonMod <- hestonModel hestonProc
  hestonEng <- analyticHestonEngine' hestonMod 144
  setPricingEngine europeanInst hestonEng
  npv europeanInst >>= print

  batesProc <- batesProcess ts divTS underQ (vol*vol) 1.0 (vol*vol) 0.001 0.0 1.0e-14 1.0e-14 1.0e-14 HestonFullTruncation
  batesMod <- batesModel batesProc
  batesEng <- batesEngine batesMod 144
  setPricingEngine europeanInst batesEng
  npv europeanInst >>= print


  return Result {
    npvR = 0
  }
  where tod = 15 `may` 1998
        settl = 17 `may` 1998
        under = 36
        strike = 40
        dividend = 0.0
        riskFreeRate = 0.06
        vol = 0.20
        maturity = 17 `may` 1999
        optType = Put
        months = [1 .. 4]
        exDates = map (\i -> addGregorianMonthsClip (3*i) settl) months

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
