module QuantLib.Example.CDS
  (
    Result(..)
  , run
  )
where

import Data.Either(rights)
import Data.Time.Calendar

import QuantLib.Compounding
import QuantLib.Credit.ProtectionSide
import QuantLib.Instances
import QuantLib.Instrument
import QuantLib.Instrument.Credit
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
import QuantLib.Time.Schedule
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

  hts <- piecewiseDefaultCurve tod instruments dc [] 1.0e-12 HazardRate BackwardFlat

  survivalProbability hts (addGregorianYearsClip 1 tod) False >>= print
  survivalProbability hts (addGregorianYearsClip 2 tod) False >>= print

  eng <- midPointCdsEngine hts recoveryRate ts Nothing
  claim <- faceValueClaim

  pQ <- fromFrequency Quarterly
  cdss <- schedule (Just tod) (head maturities) pQ cal Unadjusted Unadjusted TwentiethIMM False Nothing Nothing
  cds3m <- creditDefaultSwap Seller nominal (head quotedSpreads) cdss Following dc True True Nothing claim
  asInstrument cds3m >>= (`setPricingEngine` eng)
  fairSpread cds3m >>= print
  asInstrument cds3m >>= npv >>= print
  defaultLegNPV cds3m >>= print
  couponLegNPV cds3m >>= print

  return Result {
    r = 0
  }

  where recoveryRate = 0.5
        quotedSpreads = [0.0150, 0.0150, 0.0150, 0.0150]
        nominal = 1000000.0

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
