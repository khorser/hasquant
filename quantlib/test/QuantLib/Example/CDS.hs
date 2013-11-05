module QuantLib.Example.CDS
  (
    Result(..)
  , run
  )
where

import Data.Either(rights)

import QuantLib.Compounding
import QuantLib.Instances
import QuantLib.Instrument
import QuantLib.Math.Interpolation
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Settings
import QuantLib.TermStructure.Credit
import QuantLib.TermStructure.Trait
import QuantLib.TermStructure.Yield
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Period
import QuantLib.Time.Unit
import QuantLib.Types

data Result = Result
  { r :: Double
  }

run :: IO Result
run = do
  cal <- target
  tod <- adjust cal (15 `may` 2007) Following
  setEvaluationDate tod
  flatRate <- simpleQuote 0.01 >>= asQuote
  dc <- actual365Fixed
  ts <- flatForward tod flatRate dc Continuous Annual
  tenors <- mapM (`period` Months) [3, 6, 12, 24]
  let mat = rights $ map (addPeriod tod) tenors
  maturities <- mapM (\d -> adjust cal d Following) mat

  instruments <- mapM
    (\(t,s) -> do
      q <- simpleQuote s >>= asQuote
      spreadCdsHelper q t 0 cal Quarterly Following TwentiethIMM dc recoveryRate ts True True) 
    (zip tenors quotedSpreads)

  hs <- piecewiseDefaultCurve tod instruments dc [] 1.0e-12 HazardRate BackwardFlat

  return Result {
    r = 0
  }

  where recoveryRate = 0.5
        quotedSpreads = [0.0150, 0.0150, 0.0150, 0.0150]
        nominal = 1000000.0

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
