module QuantLib.Example.ConvertibleBond
  (
    Result(..)
  , run
  )
where

import Data.Time.Calendar

import qualified QuantLib.CashFlow as CF
import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Bond
import QuantLib.Instrument.Option
import QuantLib.Math
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Settings
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

data Result = Result
  { jarrowRuddR :: [Double]
  , coxRossRubinsteinR :: [Double]
  , additiveEQPBinomialTreeR :: [Double]
  , trigeorgisR :: [Double]
  , tianR :: [Double]
  , leisenReimerR :: [Double]
  , joshiR :: [Double]
  }

run :: IO Result
run = do
  cal <- calendar TARGET
  tod <- adjust cal (6 `november` 2013) Following
  setEvaluationDate $ Just tod
  settl <- advance cal tod (fromIntegral settlementDays, Days) Following False
  exec <- advance cal settl (len, Years) Following False
  issue <- advance cal exec (-len, Years) Following False

  sched <- schedule (Just issue) exec (1, Years) cal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
  bdc <- dayCounter Thirty360BondBasis
  schedDates <- dates sched

  let callPrices = map (`Soft` Clean) callPricesV
      putPrices = map (`Callability` Clean) putPricesV
      callability1 = zipWith (curry (\(pp, y) -> pp (schedDates!!y) 1.20)) callPrices callLength
      callability2 = zipWith (curry (\(pp, y) -> pp CallabilityPut (schedDates!!y))) putPrices putLength
  let callabilities = callability1 ++ callability2

  let divDates = [d | m <- [6, 12 .. 1000], let d = addGregorianMonthsClip m tod, d < exec]
  dividends <- mapM (CF.fixedDividend 1.0) divDates
  dc <- dayCounter Actual365FixedStandard

  underQ <- simpleQuote under >>= asQuote
  riskFreeQ <- simpleQuote riskFreeRate >>= asQuote
  divQ <- simpleQuote dividendYield >>= asQuote
  volQ <- simpleQuote vol >>= asQuote
  creditSpreadQ <- simpleQuote spreadRate >>= asQuote

  ts <- flatForward settl riskFreeQ dc Continuous Annual
  dts <- flatForward settl divQ dc Continuous Annual
  vts <- blackConstantVol settl cal volQ dc

  bsmProc <- blackScholesMertonProcess underQ dts ts vts EulerDiscretization

  let euEx = European $ EuropeanExercise exec
      amEx = AmericanExercise (Just settl) exec False
  euBond <- convertibleFixedCouponBond euEx conversionRatio callabilities issue settlementDays coupons bdc sched redemption >>= asBond >>= asInstrument
  amBond <- convertibleFixedCouponBond amEx conversionRatio callabilities issue settlementDays coupons bdc sched redemption >>= asBond >>= asInstrument

  [jr, crr, ad, tr, ti, lr, j] <- mapM
    (priceBonds euBond amBond bsmProc creditSpreadQ dividends)
    [JarrowRudd, CoxRossRubinstein, AdditiveEQPBinomialTree, Trigeorgis, Tian, LeisenReimer, Joshi4]

  return Result {
      jarrowRuddR = jr
    , coxRossRubinsteinR = crr
    , additiveEQPBinomialTreeR = ad
    , trigeorgisR = tr
    , tianR = ti
    , leisenReimerR = lr
    , joshiR = j
  }

  where under = 36.0
        spreadRate = 0.005
        dividendYield = 0.02
        riskFreeRate = 0.06
        vol = 0.20
        settlementDays = 3
        len = 5
        redemption = 100.0
        conversionRatio = redemption/under -- at the money
        timeSteps = 801
        coupons = [0.05]
        callLength = [2, 4] -- Call dates, years 2, 4.
        putLength = [3] -- Put dates year 3
        callPricesV = [101.5, 100.85]
        putPricesV = [105.0]

        priceBonds eu am p cs d b = do
          eng1 <- binomialConvertibleEngine b p timeSteps cs d
          eng2 <- binomialConvertibleEngine b p timeSteps cs d
          setPricingEngine eu eng1
          setPricingEngine am eng2
          mapM npv [eu, am]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
