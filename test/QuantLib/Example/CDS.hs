{-# LANGUAGE TemplateHaskell, TupleSections #-}
module QuantLib.Example.CDS
  (
    Result(..)
  , run
  ) where
import Control.Monad(forM, (>=>))
import Data.Time.Calendar

import QuantLib.InterestRate
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.Instrument.Credit
import QuantLib.Math
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Settings
import QuantLib.TermStructure.Credit
import QuantLib.TermStructure.Yield
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.Syntax

data Result = Result
  { probsR :: [Double]
  , fairSpreadR :: [Double]
  , npvR :: [Double]
  , defNpvR :: [Double]
  , cpnNpvR :: [Double]
  }

run :: IO Result
run = do
  cal <- calendar TARGET
  tod <- adjust cal (15 `may` 2007) Following
  setEvaluationDate $ Just tod
  flatRate <- simpleQuote 0.01
  dc <- dayCounter Actual365FixedStandard
  ts <- flatForward tod flatRate dc Continuous Annual
  maturities <- mapM (addPeriod tod . (, Months)) [3, 6, 12, 24] >>= mapM (\d -> adjust cal d Following)

  instruments <- mapM
    (\t -> simpleQuote quotedSpread >>=
        $(free1st 'spreadCdsHelper) (t, Months) 0 cal Quarterly Following TwentiethIMM dc recoveryRate ts True True)
      [3, 6, 12, 24]

  hts <- piecewiseDefaultCurve tod instruments dc [] HazardRate BackwardFlat
  probs <- mapM (\y -> survivalProbability hts (addGregorianYearsClip y tod) False) [1, 2]
  eng <- midPointCdsEngine hts recoveryRate ts Nothing

  sched <- forM maturities
    $ \m -> schedule (Just tod) m (3, Months) cal Following Unadjusted TwentiethIMM False Nothing Nothing
  cds <- forM sched
    $ \sh -> creditDefaultSwap Seller nominal quotedSpread sh Following dc True True Nothing FaceValue

  [fairSpreads, npvs, defnpvs, cpnnpvs] <- mapM
    (\f -> mapM (\c -> asInstrument c >>= (`setPricingEngine` eng) >> f c) cds)
    [fairSpread, asInstrument >=> npv, defaultLegNPV, couponLegNPV]

  return Result {
      probsR = map (100*) probs
    , fairSpreadR = map (100*) fairSpreads
    , npvR = npvs
    , defNpvR = defnpvs
    , cpnNpvR = cpnnpvs
  }
  where recoveryRate = 0.5
        nominal = 1000000.0
        quotedSpread = 0.0150

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
