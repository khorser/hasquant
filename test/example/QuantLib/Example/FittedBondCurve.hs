{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Example.FittedBondCurve
  (
    Result(..)
  , Rate(..)
  , run
  ) where
import Prelude hiding(init, head, tail, last)
import Control.Monad(forM)
import Data.Time.Calendar
import Data.List.NonEmpty(NonEmpty(..), init, head, tail, last)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.InterestRate as IR
import QuantLib.Instrument.Bond
import QuantLib.Math
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Syntax

data Result = Result { bondSettleR :: Day
  , rates1R :: Rate
  , rates2R :: Rate
  , rates3R :: Rate
  , rates4R :: Rate
  } deriving Show

data Rate = Rate{refDateR :: Day, numIterR :: [Int], tenorsR :: [Double], ratesR :: [[Double]]}
  deriving Show

run :: IO Result
run = do
  cal <- calendar Null
  tod1 <- today
  evalDate <- adjust cal tod1 Following
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Simple

  bondSettle <- advance cal evalDate (bondSettleDays, Days) Following False
  cleanQuotes <- mapM simpleQuote cleanPrices

  (rates1, ts0, instrA, instrB, curves) <- step1 evalDate dc cal bondSettle cleanQuotes
  rates2 <- step2 evalDate dc cal ts0 instrA instrB curves
  let (iA, iB) = (drop 1 instrA, drop 1 instrB)

  newtod <- advance cal evalDate (24, Months) ModifiedFollowing False
  setEvaluationDate $ Just newtod
  newBondSettle <- advance cal newtod (bondSettleDays, Days) Following False

  (rates3, ts00, curves3) <- step3 newtod dc cal newBondSettle iA iB
  mapM_ (\(price, q, i) -> do
      b <- TS.bondHelperBond i
      ytm <- yieldFromPrice' b (price, Clean) dc IR.Compounded Annual newtod 1e-10 100 0.05
      dur <- duration b ytm dc IR.Compounded Annual CF.Modified newtod
      let dp = -dur * price * 5 / 10000
      setValue q (price + dp)) $
        zip3 (drop 1 cleanPrices) (drop 1 cleanQuotes) iA
  rates4 <- rates ts00 dc newBondSettle newtod curves3 iA

  return Result{bondSettleR = bondSettle, rates1R = rates1, rates2R = rates2, rates3R = rates3, rates4R = rates4}
  where
    bondSettleDays = 0
    curveSettleDays = 0
    cleanPrices = replicate 15 100.0
    lengths = [2, 4, 6, 8, 10, 12, 14, 16,
               18, 20, 22, 24, 26, 28, 30]
    coupons = [0.0200, 0.0225, 0.0250, 0.0275, 0.0300,
                0.0325, 0.0350, 0.0375, 0.0400, 0.0425,
                0.0450, 0.0475, 0.0500, 0.0525, 0.0550]
    tolerance = 1e-10
    maxEvals = 5000

    parRate :: TS.GenYieldTermStructure y -> NonEmpty Day -> DayCounter -> IO Double
    parRate ts ds dc = do
      dfs <- mapM (\(d1, d2) -> do
              dt <- years dc d1 d2 Nothing Nothing
              df <- TS.discount' ts d2 False
              return $ df * dt) $
                zip (init ds) (tail ds)
      df1 <- TS.discount' ts (head ds) False
      df2 <- TS.discount' ts (last ds) False
      return $ 100.0 * (df1 - df2) / sum dfs

    rates :: TS.YieldTermStructure -> DayCounter -> Day -> Day -> [TS.FittedBondDiscountCurve] -> [TS.BondHelper] -> IO Rate
    rates ts0 dc bondSettle evalDate curves instrA = do
      refDate <- referenceDate ts0
      numIter <- forM curves TS.numberOfIterations

      r <- forM instrA $
        \h -> do
          cfs <- TS.bondHelperBond h >>= cashFlows >>=
            $(free1st 'CF.cashFlows) (Just False) (Just bondSettle)
          let (ds, _, _) = unzip3 $ filter (\(_, _, oc) -> not oc) cfs
              -- `ds` comes from a filter and can be empty; taking the maximum over the
              -- NonEmpty that already includes bondSettle keeps this total, and shares
              -- the one value the two parRate calls below both need
              cfDates = bondSettle :| ds
          m <- years dc evalDate (maximum cfDates) Nothing Nothing
          r1 <- parRate ts0 cfDates dc
          r2 <- forM curves $ $(free1st' 3) parRate cfDates dc --before the migration off type classes an implicit cast to YieldTermStructure was needed
          return (m, r1:r2)
      let (tenors, rs) = unzip r
      return Rate {refDateR = refDate, numIterR = numIter, tenorsR = tenors, ratesR = rs}

    step1 :: Day -> DayCounter -> Calendar -> Day -> [SimpleQuote] -> IO (Rate, TS.YieldTermStructure, [TS.BondHelper], [TS.RateHelper], [TS.FittedBondDiscountCurve])
    step1 evalDate dc cal bondSettle cleanQuotes = do
      helpers <- mapM (\(q, l, c) -> do
        mat <- advance cal bondSettle (l, Years) Following False
        s <- schedule (Just bondSettle) mat (1, Years) cal
          ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

        hA <- TS.fixedRateBondHelper q (fromIntegral bondSettleDays) 100.0 s [c] dc ModifiedFollowing 100.0 Nothing
        hB <- TS.fixedRateBondHelper q (fromIntegral bondSettleDays) 100.0 s [c] dc ModifiedFollowing 100.0 Nothing
                >>= TS.asRateHelper
        return (hA, hB)) $
          zip3 cleanQuotes lengths coupons

      let (instrA, instrB) = unzip helpers

      ts0 <- TS.piecewiseYieldCurve' curveSettleDays cal instrB dc [] TS.Discount LogLinear False

      curves <- fitCurves cal dc instrA
      rs <- rates ts0 dc bondSettle evalDate curves instrA
      return (rs, ts0, instrA, instrB, curves)

    step2 :: Day -> DayCounter -> Calendar -> TS.YieldTermStructure -> [TS.BondHelper]
             -> [TS.RateHelper] -> [TS.FittedBondDiscountCurve] -> IO Rate
    step2 evalDate dc cal ts0 instrA _ curves = do
      newtoday <- advance cal evalDate (23, Months) ModifiedFollowing False
      setEvaluationDate $ Just newtoday
      bondSettle <- advance cal newtoday (bondSettleDays, Days) Following False

      rates ts0 dc bondSettle newtoday curves instrA


    step3 :: Day -> DayCounter -> Calendar -> Day -> [TS.BondHelper] -> [TS.RateHelper]
             -> IO (Rate, TS.YieldTermStructure, [TS.FittedBondDiscountCurve])
    step3 evalDate dc cal bondSettle iA iB = do
      ts00 <- TS.piecewiseYieldCurve' curveSettleDays cal iB dc [] TS.Discount LogLinear False

      curves <- fitCurves cal dc iA
      rs <- rates ts00 dc bondSettle evalDate curves iA
      return (rs, ts00, curves)

    -- the five fitting methods the example compares, and the curves fitted with them.
    -- step1 and step3 each used to spell this list out in full (including the eleven
    -- CubicBSplines knots) and repeat the mapM below verbatim.
    -- NB results depend on the optimization options used to build QLC.
    fitCurves :: Calendar -> DayCounter -> [TS.BondHelper] -> IO [TS.FittedBondDiscountCurve]
    fitCurves cal dc instr = mapM
        (\f -> TS.fittedBondDiscountCurve curveSettleDays cal instr dc f tolerance maxEvals [] 1.0)
        fittings
      where
        noCutoff = 1.0e6 :: Double -- stands in for QuantLib's QL_MAX_REAL default (effectively "no cutoff")
        fittings = [TS.ExponentialSplines True [] [] 0.0 noCutoff 9 Nothing Nothing Nothing,
                      TS.SimplePolynomial 3 True [] [] 0.0 noCutoff Nothing Nothing,
                      TS.NelsonSiegel [] [] 0.0 noCutoff Nothing Nothing,
                      TS.CubicBSplines [-30.0, -20.0,  0.0,  5.0, 10.0, 15.0, 20.0,  25.0, 30.0, 40.0, 50.0] True [] [] 0.0 noCutoff Nothing Nothing,
                      TS.Svensson [] [] 0.0 noCutoff Nothing Nothing]
-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
