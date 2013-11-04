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
import QuantLib.Math.RNGTrait
import QuantLib.Method.BinomialTree
import QuantLib.Method.LsmBasisSystemPolynomType
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
import QuantLib.Utilities

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
  americanInst <- asOneAssetOption americanOpt >>= asOption >>= asInstrument
  bermudanInst <- asOneAssetOption bermudanOpt >>= asOption >>= asInstrument

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

  bawEng <- baroneAdesiWhaleyApproximationEngine bsmProc
  setPricingEngine americanInst bawEng
  npv americanInst >>= print

  bsEng <- bjerksundStenslandApproximationEngine bsmProc
  setPricingEngine americanInst bsEng
  npv americanInst >>= print

  iEng <- integralEngine bsmProc
  setPricingEngine europeanInst iEng
  npv europeanInst >>= print

  print "FD not implemented yet"
  {-
        method = "Finite differences";
        europeanOption.setPricingEngine(boost::shared_ptr<PricingEngine>(
                 new FDEuropeanEngine<CrankNicolson>(bsmProcess,
                                                     timeSteps,timeSteps-1)));
        bermudanOption.setPricingEngine(boost::shared_ptr<PricingEngine>(
                 new FDBermudanEngine<CrankNicolson>(bsmProcess,
                                                     timeSteps,timeSteps-1)));
        americanOption.setPricingEngine(boost::shared_ptr<PricingEngine>(
                 new FDAmericanEngine<CrankNicolson>(bsmProcess,
  -}

  _ <- mapM (binomialPrice bsmProc [europeanInst, bermudanInst, americanInst])
    [JarrowRudd, CoxRossRubinstein, AdditiveEQPBinomialTree, Trigeorgis, Tian, LeisenReimer, Joshi4]

  mceEng <- mcEuropeanEngine' PseudoRandom bsmProc 1 (fromIntegral nullInteger) False False (fromIntegral nullInteger) 0.02 (fromIntegral nullInteger) 42
  setPricingEngine europeanInst mceEng
  npv europeanInst >>= print
  
  mceEng2 <- mcEuropeanEngine' LowDiscrepancy bsmProc 1 (fromIntegral nullInteger) False False 32768 nullReal (fromIntegral nullInteger) (fromIntegral nullInteger)
  setPricingEngine europeanInst mceEng2
  npv europeanInst >>= print

  mcaEng <- mcAmericanEngine' PseudoRandom bsmProc 100 (fromIntegral nullInteger) True False (fromIntegral nullInteger) 0.02 (fromIntegral nullInteger) 42 2 Monomial 4096
  setPricingEngine americanInst mcaEng
  npv americanInst >>= print

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
        timeSteps = 801

        binomialPrice proc inst tree = do
          eng <- binomialVanillaEngine tree proc timeSteps
          mapM (\i -> setPricingEngine i eng >> npv i) inst >>= print

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
