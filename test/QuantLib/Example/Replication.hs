{-# LANGUAGE OverloadedLists #-}
module QuantLib.Example.Replication
  (
    Result(..)
  , run
  ) where
import Control.Monad(void, foldM)
import Data.Time.Calendar

import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Settings
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

data Result = Result
  { npvInit :: [Double]
  , npvOut :: [Double]
  , npvIn :: [Double]
  } deriving Show

run :: IO Result
run = do
  setEvaluationDate $ Just tod
  underlyingQuote <- simpleQuote initialSpot
  riskFreeRate <- simpleQuote 0.04
  vol <- simpleQuote 0.20
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  flatRate <- flatForward' 0 cal riskFreeRate dc Continuous Annual
  flatVol <- blackConstantVol' 0 cal vol dc
  let ex = European $ EuropeanExercise maturity
      payoff = PlainVanilla $ PlainVanillaPayoff optionType strike
  bsProcess <- blackScholesProcess underlyingQuote flatRate flatVol EulerDiscretization False
  barrierEngine <- analyticBarrierEngine bsProcess
  europeanEngine <- analyticEuropeanEngine bsProcess Nothing
  referenceOption <- barrierOption barrierType barrier rebate payoff ex
  refInstrument <- asOneAssetOption referenceOption >>= asOption >>= asInstrument
  setPricingEngine referenceOption barrierEngine
  put1 <- europeanOption payoff ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine put1 europeanEngine
  digitalPut <- europeanOption (CashOrNothing Put barrier 1.0) ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine digitalPut europeanEngine
  put2 <- europeanOption (PlainVanilla $ PlainVanillaPayoff Put barrier) ex >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine put2 europeanEngine
  let p = [(put1, 1), (digitalPut, barrier-strike), (put2, -1)]
  portfolio1 <- foldM (addInstrument europeanEngine underlyingQuote) p
    (zip maturities1 killDates1) >>= composite
  portfolio2 <- foldM (addInstrument europeanEngine underlyingQuote) p
    (zip maturities2 killDates2) >>= composite
  portfolio3 <- foldM (addInstrument europeanEngine underlyingQuote) p
    (zip maturities3 killDates3) >>= composite

  setEvaluationDate $ Just tod

  -- naming the three spots directly, rather than pattern-matching a 3-element list out
  -- of a mapM over `underlyingValues`, which hid which result belonged to which spot
  -- the signature is load-bearing: OverloadedLists is on for this module, so without
  -- it the instrument list literal makes the inferred type IsList-polymorphic, which
  -- GHC 8.10 rejects outright ("illegal equational constraint")
  let npvsAtSpot :: Double -> IO [Double]
      npvsAtSpot v = setValue underlyingQuote v
        >> mapM npv [refInstrument, portfolio1, portfolio2, portfolio3]
  npvAtInitial <- npvsAtSpot initialSpot
  npvAtOutOfTheMoney <- npvsAtSpot outOfTheMoneySpot
  npvAtInTheMoney <- npvsAtSpot inTheMoneySpot

  return Result {
    npvInit = npvAtInitial
  , npvOut = npvAtOutOfTheMoney
  , npvIn = npvAtInTheMoney
  }
  where barrierType = DownOut
        optionType = Put
        tod = 29 `may` 2006
        maturity = addGregorianYearsClip 1 tod
        barrier = 70.0
        rebate = 0.0
        initialSpot, outOfTheMoneySpot, inTheMoneySpot :: Double
        initialSpot = 100.0
        outOfTheMoneySpot = 110.0
        inTheMoneySpot = 90.0
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


        addInstrument engine underlyingQuote pp (m, k) = do
          (p, r) <- nextComponent engine underlyingQuote pp m k
          return $ (p, r) : pp

        nextComponent engine underlyingQuote p innerMaturity killDate = do
          let innerExercise = European $ EuropeanExercise innerMaturity
              innerPayoff = PlainVanilla $ PlainVanillaPayoff Put barrier
          putn <- europeanOption innerPayoff innerExercise >>= asOneAssetOption >>= asOption >>= asInstrument
          setPricingEngine putn engine
          setEvaluationDate $ Just killDate
          void $ setValue underlyingQuote barrier
          portfolioValue <- composite p >>= npv
          putValue <- npv putn
          return (putn, -portfolioValue / putValue)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
