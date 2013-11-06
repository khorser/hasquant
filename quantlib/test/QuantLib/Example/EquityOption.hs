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
import QuantLib.Method.FdmScheme
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

data Result = Result
  { analyticEuroR :: [Double]
  , analyticHestonR :: [Double]
  , batesR :: [Double]
  , bawR :: [Double]
  , bjsR :: [Double]
  , binR :: [[Double]]
  , intR :: [Double]
  , fdR :: [Double]
  , mcR :: [Double]
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
  analyticEuro <- npv europeanInst

  hestonProc <- hestonProcess ts divTS underQ (vol*vol) 1.0 (vol*vol) 0.001 0.0 HestonQuadraticExponentialMartingale
  hestonMod <- hestonModel hestonProc
  hestonEng <- analyticHestonEngine' hestonMod 144
  setPricingEngine europeanInst hestonEng
  analyticHeston <- npv europeanInst

  batesProc <- batesProcess ts divTS underQ (vol*vol) 1.0 (vol*vol) 0.001 0.0 1.0e-14 1.0e-14 1.0e-14 HestonFullTruncation
  batesMod <- batesModel batesProc
  batesEng <- batesEngine batesMod 144
  setPricingEngine europeanInst batesEng
  bates <- npv europeanInst

  bawEng <- baroneAdesiWhaleyApproximationEngine bsmProc
  setPricingEngine americanInst bawEng
  baw <- npv americanInst

  bsEng <- bjerksundStenslandApproximationEngine bsmProc
  setPricingEngine americanInst bsEng
  bjs <- npv americanInst

  iEng <- integralEngine bsmProc
  setPricingEngine europeanInst iEng
  int <- npv europeanInst

  fd <- mapM (\(f, i) -> do
    eng <- f FDCrankNicolson bsmProc 801 800 False
    setPricingEngine i eng
    npv i)
    (zip [fdEuropeanEngine, fdBermudanEngine, fdAmericanEngine] [europeanInst, bermudanInst, americanInst])

  bin <- mapM (binomialPrice bsmProc [europeanInst, bermudanInst, americanInst])
    [JarrowRudd, CoxRossRubinstein, AdditiveEQPBinomialTree, Trigeorgis, Tian, LeisenReimer, Joshi4]

  mceEng <- mcEuropeanEngine PseudoRandom bsmProc (Just 1) Nothing False False Nothing (Just 0.02) Nothing 42
  setPricingEngine europeanInst mceEng
  mcE <- npv europeanInst
  
  mceEng2 <- mcEuropeanEngine LowDiscrepancy bsmProc (Just 1) Nothing False False (Just 32768) Nothing Nothing 0
  setPricingEngine europeanInst mceEng2
  mcE2 <- npv europeanInst

  mcaEng <- mcAmericanEngine PseudoRandom bsmProc (Just 100) Nothing True False Nothing (Just 0.02) Nothing 42 2 Monomial (Just 4096)
  setPricingEngine americanInst mcaEng
  mcA <- npv americanInst

  return Result {
    analyticEuroR = [analyticEuro]
  , analyticHestonR = [analyticHeston]
  , batesR = [bates]
  , bawR = [baw]
  , bjsR = [bjs]
  , binR = bin
  , intR = [int]
  , fdR = fd
  , mcR = [mcE, mcE2, mcA]
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
          mapM (\i -> setPricingEngine i eng >> npv i) inst

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
