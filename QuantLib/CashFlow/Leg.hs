{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.CashFlow.Leg
  (
  -- makers
    leg
  -- accessors
  , startDate
  )
where

import QuantLib.Internal
import QuantLib.Types

foreign import ccall safe "ql.h qlLeg"
  c_leg :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
  c_legStartDate :: Ptr CLeg -> Ptr CString -> IO CDate
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

instance Finalizable CLeg where
  finalize = p_freeLeg

-- | (qlLeg)
leg :: [(Double, Day)] -> IO Leg
leg flows = withAmounts
            amounts
            (\_ ams ->
              withDays
              dates
              (\n ds -> construct $ c_leg n ams ds))
  where (amounts, dates) = unzip flows

-- |Returns the start (i.e. first accrual) date for the given Leg object (qlLegStartDate)
-- XXX assuming legs are immutable
startDate :: Leg -> Day
startDate l = fromQlDate $ unsafePerformIO (withObject l (handleExceptions . c_legStartDate))
