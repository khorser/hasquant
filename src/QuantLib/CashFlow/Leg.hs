{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.CashFlow.Leg
  (
    leg

  , startDate
  , duration
  )
where

import QuantLib.CashFlow.DurationType
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlLeg"
  c_leg :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
  c_legStartDate :: Ptr CLeg -> Ptr CString -> IO CDate

-- | QuantLibXL: qlLeg
leg :: [(Double, Day)] -- ^amounts and dates
  -> IO Leg
leg = $(ffiConstruct 'leg) c_leg

-- |Returns the start (i.e. first accrual) date for the given Leg. QuantLibXL: qlLegStartDate
startDate :: Leg -> Day
startDate = $(ffiCallXIO 'startDate) c_legStartDate
-- XXX assuming legs are immutable

-- |Cash-flow duration.
-- The simple duration of a string of cash flows is defined as \[ D_{\mathrm{simple}} = \frac{\sum t_i c_i B(t_i)}{\sum c_i B(t_i)} \] where $ c_i $ is the amount of the $ i $-th cash flow, $ t_i $ is its payment time, and $ B(t_i) $ is the corresponding discount according to the passed yield.The modified duration is defined as \[ D_{\mathrm{modified}} = -\frac{1}{P} \frac{\partial P}{\partial y} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.The Macaulay duration is defined for a compounded IRR as \[ D_{\mathrm{Macaulay}} = \left( 1 + \frac{y}{N} \right) D_{\mathrm{modified}} \] where $ y $ is the IRR and $ N $ is the number of cash flows per year.
duration :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> DurationType -- ^type
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> IO YearFraction
duration = $(ffiCallX 'duration) c_duration

foreign import ccall safe "ql.h qlCashFlowsDuration"
  c_duration :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CYearFraction
