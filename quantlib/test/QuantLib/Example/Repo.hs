module QuantLib.Example.Repo
  (
    Result(..)
  , run
  )
where

import Control.Monad(void)

import QuantLib.Compounding
import QuantLib.Instances
import QuantLib.Instrument
import QuantLib.Instrument.Bond
import QuantLib.Instrument.Forward
import QuantLib.InterestRate
import QuantLib.PositionType
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Yield
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Schedule
import QuantLib.Time.Unit
import QuantLib.Types

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

run :: IO Result
run = runQLE $ do
  repoDayCountConvention <- actual360
  bondCalendar <- nullCalendar
  bondDayCountConvention <- thirty360BondBasis
  setEvaluationDate $ Just repoSettlementDate
  bondSimpleQuote <- simpleQuote 0.01
  bondQuote <- asQuote bondSimpleQuote
  bondCurve <- flatForward repoSettlementDate bondQuote bondDayCountConvention Compounded bondCouponFrequency
  bondSchedule <- schedule (Just bondDatedDate) bondMaturityDate
    (6, Months) bondCalendar bondBusinessDayConvention bondBusinessDayConvention Backward False
    Nothing Nothing
  fixedBond <- fixedRateBondFromSchedule bondSettlementDays faceAmount bondSchedule [bondCoupon]
    bondDayCountConvention bondBusinessDayConvention bondRedemption (Just bondIssueDate)
    bondCalendar
  b <- asBond fixedBond
  -- liftM2 setPricingEngine (asInstrument b) (discountingBondEngine bondCurve Nothing)]
  i <- asInstrument b
  discountingBondEngine bondCurve Nothing >>= setPricingEngine i
  void $ yieldFromCleanPrice b bondCleanPrice bondDayCountConvention Compounded bondCouponFrequency repoSettlementDate 1e-8 100 >>= setValue bondSimpleQuote
  repoQuote <- simpleQuote repoRate >>= asQuote
  repoCurve <- flatForward repoSettlementDate repoQuote repoDayCountConvention
    repoCompounding repoCompoundFreq
  bondFwd <- fixedRateBondForward repoSettlementDate repoDeliveryDate fwdType dummyStrike
    repoSettlementDays
    repoDayCountConvention bondCalendar bondBusinessDayConvention fixedBond
    (Just repoCurve) (Just repoCurve)

  clP <- cleanPrice b bondCurve repoSettlementDate
  accr1 <- accruedAmount b repoSettlementDate
  let dp = clP + accr1
  accr2 <- accruedAmount b repoDeliveryDate

  fwd <- asForward bondFwd
  spotInc <- spotIncome fwd repoCurve
  disc <- discount' repoCurve repoDeliveryDate False
  ii <- asInstrument fwd
  np <- npv ii

  clF <- cleanForwardPrice bondFwd
  fP <- forwardPrice bondFwd

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
    , impliedYieldR = rate impR
    , zeroRateR = rate z
    }
  where repoSettlementDate = 14 `february` 2000
        repoDeliveryDate = 15 `august` 2000
        repoRate = 0.05
        repoSettlementDays = 0
        repoCompounding = Simple
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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
