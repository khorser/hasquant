module QuantLib.Example.FxForward
  (
    Result(..)
  , run
  ) where

import QuantLib.Currency
import QuantLib.Instrument
import QuantLib.Instrument.Forward
import qualified QuantLib.InterestRate as IR
import QuantLib.PricingEngine(discountingFxForwardEngine)
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..), TimeUnit(..))

data Result = Result
  { npvR :: Double
  , fairForwardRateR :: Double
  , npvSourceCurrencyR :: Double
  , npvTargetCurrencyR :: Double
  , npvAtFairRateR :: Double
  } deriving Show

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  sourceQ <- simpleQuote sourceRate
  targetQ <- simpleQuote targetRate
  sourceCurve <- flatForward evalDate sourceQ dc IR.Continuous Annual
  targetCurve <- flatForward evalDate targetQ dc IR.Continuous Annual
  spotFxQ <- simpleQuote spotFx
  eur <- currency EUR
  usd <- currency USD
  maturity <- advance cal evalDate (1, Years) Unadjusted False

  fwd <- fxForward sourceNominal eur targetNominal usd maturity True 2 cal
  engine <- discountingFxForwardEngine sourceCurve targetCurve spotFxQ
  setPricingEngine fwd engine

  npvV <- npv fwd
  ffr <- fairForwardRate fwd
  npvSrc <- npvSourceCurrency fwd
  npvTgt <- npvTargetCurrency fwd

  -- exercise the rate-based constructor (fxForward'): a contract struck at
  -- the just-computed fair rate must have ~0 NPV, an economic invariant
  -- independent of the nominal-based constructor tested above.
  fwdAtFairRate <- fxForward' sourceNominal eur usd ffr maturity True 2 cal
  setPricingEngine fwdAtFairRate engine
  npvFair <- npv fwdAtFairRate

  return Result
    { npvR = npvV
    , fairForwardRateR = ffr
    , npvSourceCurrencyR = npvSrc
    , npvTargetCurrencyR = npvTgt
    , npvAtFairRateR = npvFair
    }
  where
    evalDate = 2 `january` 2024
    sourceRate = 0.03
    targetRate = 0.05
    spotFx = 1.10
    sourceNominal = 1000000.0
    targetNominal = 1100000.0

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
