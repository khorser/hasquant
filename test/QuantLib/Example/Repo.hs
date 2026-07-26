{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Example.Repo
  (
    Result(..)
  , run
  ) where

import Control.Monad(void, when)
import System.Mem(performGC)
import System.IO (hPutStrLn, stderr)
import Control.Concurrent (threadDelay)

import QuantLib.Instrument
import QuantLib.Instrument.Bond
import QuantLib.Instrument.Forward
import qualified QuantLib.InterestRate as IR
import QuantLib.PricingEngine(discountingBondEngine)
import QuantLib.Quote(setValue, simpleQuote, SimpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Syntax

-- run tests with stack test --ta '--match /Repo'
data Result = Result
  { cleanPriceR :: Double
  , dirtyPriceR :: Double
  , accruedAmountSettlement :: Double
  , accruedAmountDelivery :: Double
  , spotIncomeR :: Double
  , fwdIncomeR :: Double
  , strike :: Double
  , npvR :: Double
  , cleanForwardPriceR :: Double
  , forwardPriceR :: Double
  , impliedYieldR :: Double
  , zeroRateR :: Double
  } deriving Show

run :: Bool -> IO Result
run gc = do
  repoDayCountConvention <- dayCounter Actual360
  bondCalendar <- calendar Null
  bondDayCountConvention <- dayCounter Thirty360BondBasis
  setEvaluationDate $ Just repoSettlementDate
  bondQuote <- simpleQuote 0.01
  bondCurve <- flatForward repoSettlementDate bondQuote bondDayCountConvention IR.Compounded bondCouponFrequency
  bondSchedule <- schedule (Just bondDatedDate) bondMaturityDate
    (6, Months) bondCalendar bondBusinessDayConvention bondBusinessDayConvention Backward False
    Nothing Nothing
  (fwd, clP, accr1, accr2, clF, fP, dp) <- doBond bondCalendar bondSchedule bondQuote repoDayCountConvention bondDayCountConvention bondCurve
  when gc (performGC >> threadDelay 1000000 >> performGC >> threadDelay 1000000 >> hPutStrLn stderr "GC complete")
  repoCurve <- simpleQuote repoRate >>=
        $(free2nd 'flatForward) repoSettlementDate repoDayCountConvention repoCompounding repoCompoundFreq
  spotInc <- spotIncome fwd repoCurve
  disc <- discount' repoCurve repoDeliveryDate False
  np <- npv fwd

  impR <- impliedYield fwd dp dummyStrike repoSettlementDate
    repoCompounding repoDayCountConvention

  z <- zeroRate' repoCurve repoDeliveryDate repoDayCountConvention
    repoCompounding repoCompoundFreq False

  return Result {
      cleanPriceR = clP
    , dirtyPriceR = dp
    , accruedAmountSettlement = accr1
    , accruedAmountDelivery = accr2
    , spotIncomeR = spotInc
    , fwdIncomeR = spotInc / disc
    , strike = dummyStrike
    , npvR = np
    , cleanForwardPriceR = clF
    , forwardPriceR = fP
    , impliedYieldR = IR.rate impR
    , zeroRateR = IR.rate z
    }
  where repoSettlementDate = 14 `february` 2000
        repoDeliveryDate = 15 `august` 2000
        repoRate = 0.05
        repoSettlementDays = 0
        repoCompounding = IR.Simple
        repoCompoundFreq = Annual
        bondIssueDate = 15 `september` 1995
        bondDatedDate = 15 `september` 1995
        bondMaturityDate = 15 `september` 2005
        bondCoupon = 0.08
        bondCouponFrequency = Semiannual
        bondSettlementDays = 0
        bondBusinessDayConvention = Unadjusted
        bondCleanPrice = 89.97693786
        bondRedemption = 100.0
        faceAmount = 100.0
        dummyStrike = 91.5745
        fwdType = Long

        -- make sure bond forward reference is scoped (for GC checks)
        doBond :: Calendar -> Schedule -> SimpleQuote -> DayCounter -> DayCounter -> YieldTermStructure -> IO (Forward, Double, Double, Double, Double, Double, Double)
        doBond bondCalendar bondSchedule bondQuote repoDayCountConvention bondDayCountConvention bondCurve = do
          b <- fixedRateBond bondSettlementDays faceAmount bondSchedule [bondCoupon]
            bondDayCountConvention bondBusinessDayConvention bondRedemption (Just bondIssueDate) bondCalendar
          -- liftM2 setPricingEngine (asInstrument b) (discountingBondEngine bondCurve Nothing)]
          discountingBondEngine bondCurve Nothing >>= setPricingEngine b
          void $ yieldFromPrice b (bondCleanPrice, Clean) bondDayCountConvention IR.Compounded bondCouponFrequency repoSettlementDate 1e-8 100 >>= setValue bondQuote
          repoCurve <- simpleQuote repoRate >>=
            $(free2nd 'flatForward) repoSettlementDate repoDayCountConvention repoCompounding repoCompoundFreq
          bondFwd <- bondForward repoSettlementDate repoDeliveryDate fwdType dummyStrike
            repoSettlementDays
            repoDayCountConvention bondCalendar bondBusinessDayConvention b
            (Just repoCurve) (Just repoCurve)

          clP <- cleanPrice b bondCurve repoSettlementDate
          accr1 <- accruedAmount b repoSettlementDate
          let dp = clP + accr1
          accr2 <- accruedAmount b repoDeliveryDate
          fwd <- asForward bondFwd
          clF <- cleanForwardPrice bondFwd
          fP <- forwardPrice bondFwd

          return (fwd, clP, accr1, accr2, clF, fP, dp)
-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
