{-# LANGUAGE TemplateHaskell #-}
module QuantLib.CashFlow.Leg
  (
    leg

  , startDate
  )
where

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
