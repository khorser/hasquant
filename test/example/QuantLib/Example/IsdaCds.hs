module QuantLib.Example.IsdaCds
  (
    Result(..)
  , run
  ) where
import Data.Time.Calendar
import qualified Data.List.NonEmpty as NE

import QuantLib.Currency
import QuantLib.Instrument
import QuantLib.Instrument.Credit
import QuantLib.Index.InterestRate hiding(dayCounter, currency)
import QuantLib.Math
import QuantLib.Quote
import QuantLib.PricingEngine
import QuantLib.Settings
import QuantLib.TermStructure.Credit
import QuantLib.TermStructure.Yield
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule

newtype Result = Result { conventionalUpfrontR :: Double }

-- |Single case (first: termDate\/spread\/recovery combination) of upstream's
-- @testIsdaEngine@ (@test-suite\/creditdefaultswap.cpp@), which pins 'isdaCdsEngine'
-- against a cached Markit-published upfront value rather than a self-consistency check.
-- All builder defaults below are transcribed from @ql\/instruments\/makecds.cpp@'s
-- @MakeCreditDefaultSwap@ (both trades there go through the upfront+running-spread
-- constructor, hence 'creditDefaultSwap'' rather than 'creditDefaultSwap').
run :: IO Result
run = do
  weekendsOnly <- calendar WeekendsOnly
  let tradeDate = 21 `may` 2009
  setEvaluationDate $ Just tradeDate

  act360 <- dayCounter (Actual360 False)
  act360IncludeLast <- dayCounter (Actual360 True)
  act365Fixed <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  usd <- currency USD

  let depTenors = [1, 2, 3, 6, 9, 12 :: Int]
      depQuotes = [0.003081, 0.005525, 0.007163, 0.012413, 0.014, 0.015488]
  depositHelpers <- mapM
    (\(t, q) -> simpleQuote q >>= \sq -> depositRateHelper sq (t, Months) 2 weekendsOnly ModifiedFollowing False act360)
    (zip depTenors depQuotes)

  isdaIbor <- iborIndex (Ibor "IsdaIbor" (3, Months) 2 usd weekendsOnly ModifiedFollowing False act360) Nothing

  let swapTenors = [2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20, 25, 30 :: Int]
      swapQuotes = [ 0.011907, 0.01699, 0.021198, 0.02444, 0.026937, 0.028967, 0.030504
                   , 0.031719, 0.03279, 0.034535, 0.036217, 0.036981, 0.037246, 0.037605 ]
  swapHelpers <- mapM
    (\(t, q) -> simpleQuote q >>= \sq -> swapRateHelper' sq (t, Years) weekendsOnly Semiannual ModifiedFollowing
        thirty360bb isdaIbor Nothing (0, Days) Nothing Nothing LastRelevantDate Nothing False Nothing Nothing Nothing)
    (zip swapTenors swapQuotes)

  swapHelpers' <- mapM asRateHelper swapHelpers
  discountCurve <- piecewiseYieldCurve' 0 weekendsOnly (NE.fromList (depositHelpers ++ swapHelpers'))
    act365Fixed [] Discount LogLinear False

  let termDate = fromGregorian 2010 6 20
      spread = 0.001
      recovery = 0.2
      notional = 10000000.0
      protectionStart = tradeDate
  upfrontDate <- advance weekendsOnly tradeDate (3, Days) Following False
  sched <- schedule (Just protectionStart) termDate (3, Months) weekendsOnly Following Unadjusted CDS False Nothing Nothing

  quotedTrade <- creditDefaultSwap' Buyer notional 0.0 spread sched Following act360 True True
    (Just protectionStart) (Just upfrontDate) FaceValue act360IncludeLast True (Just tradeDate) 3

  h <- impliedHazardRate quotedTrade 0.0 discountCurve act365Fixed recovery 1e-10 ISDA
  hq <- simpleQuote h
  probabilityCurve <- flatHazardRate' 0 weekendsOnly hq act365Fixed

  engine <- isdaCdsEngine probabilityCurve recovery discountCurve Nothing NumericalFixTaylor HalfDayBias Piecewise

  conventionalTrade <- creditDefaultSwap' Buyer notional 0.0 0.01 sched Following act360 True True
    (Just protectionStart) (Just upfrontDate) FaceValue act360IncludeLast True (Just tradeDate) 3
  asInstrument conventionalTrade >>= (`setPricingEngine` engine)
  upfront <- fairUpfront conventionalTrade

  return Result { conventionalUpfrontR = notional * upfront }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
