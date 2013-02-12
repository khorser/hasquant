module QuantLib.Example.Repo
  (
    Result(..)
  , result
  )
where

import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Compounding
import QuantLib.Time.Frequency
import QuantLib.Time.Calendar
import QuantLib.Time.BusinessDayConvention
import QuantLib.TermStructure.Yield
import QuantLib.Quote
import QuantLib.Types
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.Time.DateGenerationRule
import QuantLib.Instrument.Bond

data Result = Result

result :: IO Result
result = do
  repoDayCountConvention <- actual360
  bondCalendar <- nullCalendar
  bondDayCountConvention <- thirty360BondBasis
  setEvaluationDate $ Just repoSettlementDate
  bondSimpleQuote <- simpleQuote 0.01
  bondQuote <- asQuote bondSimpleQuote
  bondCurve <- flatForward repoSettlementDate bondQuote bondDayCountConvention Compounded bondCouponFrequency
  period <- fromFrequency bondCouponFrequency
  bondSchedule <- schedule bondDatedDate (Just bondMaturityDate) period bondCalendar bondBusinessDayConvention Backward False
  return Result
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
