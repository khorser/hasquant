{-# LANGUAGE TemplateHaskell, TupleSections #-}
module QuantLib.Example.CDS
  (
    Result(..)
  , run
  ) where
import Control.Monad(forM, (>=>))
import qualified Data.List.NonEmpty as NE
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
  evalDate <- adjust cal (15 `may` 2007) Following
  setEvaluationDate $ Just evalDate
  flatRate <- simpleQuote 0.01
  dc <- dayCounter Actual365FixedStandard
  ts <- flatForward evalDate flatRate dc Continuous Annual
  settlementDate <- advance cal evalDate (1, Days) Following False
  maturities <- mapM (addPeriod settlementDate . (, Months)) [3, 6, 12, 24] >>= mapM (\d -> adjust cal d Following)

  instruments <- mapM
    (\t -> simpleQuote quotedSpread >>=
        $(free1st 'spreadCdsHelper) (t, Months) 1 cal Quarterly Following TwentiethIMM dc recoveryRate ts True True Nothing dc True Midpoint)
      [3, 6, 12, 24]

  hts <- piecewiseDefaultCurve evalDate (NE.fromList instruments) dc [] HazardRate BackwardFlat
  probs <- mapM (\y -> survivalProbability hts (addGregorianYearsClip y evalDate) False) [1, 2]
  eng <- midPointCdsEngine hts recoveryRate ts Nothing

  sched <- forM maturities
    $ \m -> schedule (Just settlementDate) m (3, Months) cal Following Unadjusted TwentiethIMM False Nothing Nothing
  cds <- forM sched
    $ \sh -> creditDefaultSwap Seller nominal quotedSpread sh Following dc True True Nothing FaceValue dc True Nothing 3

  mapM_ (asInstrument >=> (`setPricingEngine` eng)) cds
  fairSpreads <- mapM fairSpread cds
  npvs <- mapM (asInstrument >=> npv) cds
  defnpvs <- mapM defaultLegNPV cds
  cpnnpvs <- mapM couponLegNPV cds

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
