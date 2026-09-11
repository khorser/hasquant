-- Exercises owned materialization through IborCoupon -> FloatingRateCoupon -> Coupon -> CashFlow.
-- The leaf and both intermediate handles leave scope before collection, after which the root
-- must still be usable without a dangling pointer or double free.  Each upcast allocates a
-- fresh shared_ptr, so the four-level chain is where a mislabeled finalizer would show up.
import Data.Time.Calendar (fromGregorian)

import qualified QuantLib.CashFlow as CashFlow
import QuantLib.Index.InterestRate (IborConstructor (UsdLibor), iborIndex)
import qualified QuantLib.InterestRate as InterestRate
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import QuantLib.TermStructure.Yield (Reference (ReferenceDate), flatForward)
import QuantLib.Time.Calendar (BusinessDayConvention (Preceding))
import QuantLib.Time.Schedule
  (DayCounterConstructor (Actual360), Frequency (Annual), TimeUnit (Months), dayCounter)

main :: IO ()
main = Settings.keepingSettingsGc $ do
  let evaluationDate = fromGregorian 2025 1 2
      accrualStart = fromGregorian 2025 4 1
      accrualEnd = fromGregorian 2025 7 1
  Settings.setEvaluationDate (Just evaluationDate)
  root <- do
    dc <- dayCounter (Actual360 False)
    quote <- Quote.simpleQuote 0.03 >>= Quote.asQuote
    curve <- flatForward (ReferenceDate evaluationDate) quote dc InterestRate.Continuous Annual
    index <- iborIndex (UsdLibor (3, Months)) (Just curve)
    leaf <- CashFlow.iborCoupon accrualEnd 100 accrualStart accrualEnd 2 index
      1 0 Nothing Nothing dc False Nothing Preceding
    floating <- CashFlow.asFloatingRateCoupon leaf
    coupon <- CashFlow.asCoupon floating
    CashFlow.asCashFlow coupon
  Settings.collectGarbage
  let paymentDate = CashFlow.date root
  leg <- CashFlow.cashFlowLeg [root]
  legStart <- CashFlow.startDate leg
  if paymentDate == accrualEnd && legStart == accrualStart
    then pure ()
    else error "cash-flow hierarchy materialization did not preserve the root value"
