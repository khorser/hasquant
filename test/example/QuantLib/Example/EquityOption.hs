{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Example.EquityOption
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar

import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Option
import QuantLib.Math
import QuantLib.Model
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Syntax

data Result = Result
  { analyticEuroR :: [Double]
  , analyticHestonR :: [Double]
  , batesR :: [Double]
  , bawR :: [Double]
  , bjsR :: [Double]
  , binR :: [[Double]]
  , intR :: [Double]
  , fdR :: [Double]
  , mcR :: (Double, Double, Double)
  }

-- Each of these prices the same shared 'europeanOpt'/'americanOpt' handle by
-- attaching a fresh engine and reading 'npv' -- the QuantLib objects are pure
-- value-holders whose only "state" is the currently attached engine, so each
-- helper is self-contained even though it mutates a handle built in 'run'.

analyticEuropeanNpv :: GeneralizedBlackScholesProcess -> VanillaOption -> IO Double
analyticEuropeanNpv bsmProc europeanOpt = do
  analyticEuropeanEngine bsmProc Nothing >>= QuantLib.Instrument.setPricingEngine europeanOpt
  npv europeanOpt

hestonNpv :: YieldTermStructure -> YieldTermStructure -> SimpleQuote -> Double -> VanillaOption -> IO Double
hestonNpv ts divTS underQ vol europeanOpt = do
  hestonProc <- hestonProcess ts (Just divTS) underQ (vol*vol) 1.0 (vol*vol) 0.001 0.0 QuadraticExponentialMartingale
  hestonMod <- hestonModel hestonProc
  hestonEng <- analyticHestonEngine' hestonMod 144
  QuantLib.Instrument.setPricingEngine europeanOpt hestonEng
  npv europeanOpt

batesNpv :: YieldTermStructure -> YieldTermStructure -> SimpleQuote -> Double -> VanillaOption -> IO Double
batesNpv ts divTS underQ vol europeanOpt = do
  batesEng <- batesProcess ts divTS underQ (vol*vol) 1.0 (vol*vol) 0.001 0.0 1.0e-14 1.0e-14 1.0e-14 HestonFullTruncation >>= batesModel >>= (`batesEngine` 144)
  QuantLib.Instrument.setPricingEngine europeanOpt batesEng
  npv europeanOpt

baroneAdesiWhaleyNpv :: GeneralizedBlackScholesProcess -> VanillaOption -> IO Double
baroneAdesiWhaleyNpv bsmProc americanOpt = do
  bawEng <- baroneAdesiWhaleyApproximationEngine bsmProc
  QuantLib.Instrument.setPricingEngine americanOpt bawEng
  npv americanOpt

bjerksundStenslandNpv :: GeneralizedBlackScholesProcess -> VanillaOption -> IO Double
bjerksundStenslandNpv bsmProc americanOpt = do
  bsEng <- bjerksundStenslandApproximationEngine bsmProc
  QuantLib.Instrument.setPricingEngine americanOpt bsEng
  npv americanOpt

integralNpv :: GeneralizedBlackScholesProcess -> VanillaOption -> IO Double
integralNpv bsmProc europeanOpt = do
  iEng <- integralEngine bsmProc
  QuantLib.Instrument.setPricingEngine europeanOpt iEng
  npv europeanOpt

fdSweep :: GeneralizedBlackScholesProcess -> [OneAssetOption] -> IO [Double]
fdSweep bsmProc = mapM (\i -> do
    eng <- fdBlackScholesVanillaEngine bsmProc 801 800 0 Douglas False 0.0 CashDividendSpot
    QuantLib.Instrument.setPricingEngine i eng
    npv i)

binomialPrice :: GeneralizedBlackScholesProcess -> [OneAssetOption] -> Word -> BinomialTree -> IO [Double]
binomialPrice proc inst timeSteps tree = do
  eng <- binomialVanillaEngine tree proc timeSteps
  mapM (\i -> QuantLib.Instrument.setPricingEngine i eng >> npv i) inst

monteCarloNpvs :: GeneralizedBlackScholesProcess -> VanillaOption -> VanillaOption -> IO (Double, Double, Double)
monteCarloNpvs bsmProc europeanOpt americanOpt = do
  mceEng <- mcEuropeanEngine PseudoRandom Statistics bsmProc (Just 1) Nothing False False Nothing (Just 0.02) Nothing 42
  QuantLib.Instrument.setPricingEngine europeanOpt mceEng
  mcE <- npv europeanOpt

  mceEng2 <- mcEuropeanEngine LowDiscrepancy Statistics bsmProc (Just 1) Nothing False False (Just 32768) Nothing Nothing 0
  QuantLib.Instrument.setPricingEngine europeanOpt mceEng2
  mcE2 <- npv europeanOpt

  mcaEng <- mcAmericanEngine PseudoRandom Statistics bsmProc (Just 100) Nothing True False Nothing (Just 0.02) Nothing 42 2 Monomial (Just 4096) Nothing Nothing
  QuantLib.Instrument.setPricingEngine americanOpt mcaEng
  mcA <- npv americanOpt

  return (mcE, mcE2, mcA)

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Actual365FixedStandard
  let europeanEx = European $ EuropeanExercise maturity
      bermudanEx = Bermudan $ BermudanExercise exDates False
      americanEx = American Nothing maturity False
  underQ <- simpleQuote under
  riskFreeQ <- simpleQuote riskFreeRate
  ts <- flatForward settl riskFreeQ dc Continuous Annual
  divQ <- simpleQuote dividend
  divTS <- flatForward settl divQ dc Continuous Annual
  volQ <- simpleQuote vol
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) settl volQ dc
  let payoff = PlainVanilla $ PlainVanillaPayoff optType strike
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False
  europeanOpt <- vanillaOption payoff europeanEx
  bermudanOpt <- vanillaOption payoff bermudanEx
  americanOpt <- vanillaOption payoff americanEx
  europeanInst <- asOneAssetOption europeanOpt
  americanInst <- asOneAssetOption americanOpt
  bermudanInst <- asOneAssetOption bermudanOpt

  analyticEuro <- analyticEuropeanNpv bsmProc europeanOpt
  analyticHeston <- hestonNpv ts divTS underQ vol europeanOpt
  bates <- batesNpv ts divTS underQ vol europeanOpt
  baw <- baroneAdesiWhaleyNpv bsmProc americanOpt
  bjs <- bjerksundStenslandNpv bsmProc americanOpt
  int <- integralNpv bsmProc europeanOpt

  fd <- fdSweep bsmProc [europeanInst, bermudanInst, americanInst]

  bin <- mapM (binomialPrice bsmProc [europeanInst, bermudanInst, americanInst] timeSteps)
            [JarrowRudd, CoxRossRubinstein, AdditiveEQPBinomialTree, Trigeorgis, Tian, LeisenReimer, Joshi4]

  (mcE, mcE2, mcA) <- monteCarloNpvs bsmProc europeanOpt americanOpt

  return Result {
    analyticEuroR = [analyticEuro]
  , analyticHestonR = [analyticHeston]
  , batesR = [bates]
  , bawR = [baw]
  , bjsR = [bjs]
  , binR = bin
  , intR = [int]
  , fdR = fd
  , mcR = (mcE, mcE2, mcA)
  }
  where evalDate = 15 `may` 1998
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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
