{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls,MultiParamTypeClasses,FlexibleContexts #-}
module QuantLib.Instrument.Bond
  (
  -- types
    CBond
  , Bond
  , FixedRateBond
  -- makers
  , bond
  , bond'
  , fixedRateBond
  , fixedRateBond'
  , fixedRateBond''
  -- accessors
  , issueDate
  , maturityDate
  , frequency
  )

where

import QuantLib.CashFlow.Leg(Leg, CLeg)
import QuantLib.Internal
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.DayCounter(DayCounter, CDayCounter)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.InterestRate(InterestRate, CInterestRate)
import QuantLib.Time.Period(Period, CPeriod)
import QuantLib.Time.Schedule(Schedule, CSchedule)

data CBond
type Bond = Object CBond

instance Finalizable CBond where
  finalize = p_freeBond

data CFixedRateBond
type FixedRateBond = Object CFixedRateBond

instance Finalizable CFixedRateBond where
  finalize = safeCastFin p_freeBond

instance IsA CBond CBond
instance IsA CBond CFixedRateBond

-- ideally I would like the "instance IsA CBond CFixedRateBond" to derive
-- finalizers for all descendants
--
-- LANGUAGE UndecidableInstances
-- class (Finalizable a) => IsA a b where
--   commonFinalizer :: FunPtr (Ptr a -> IO ())
--   commonFinalizer = finalize
--   upcast :: Ptr b -> Ptr a
--   upcast = castPtr
--
-- instance (IsA a b) => Finalizable b where
--   finalize = castFunPtr commonFinalizer
-- also it would be great to have the type class declarations for
-- Bond/FixedRateBond rather than CBond/CFixedRateBond

-- is it possible to use type class constraints in FFI declarations?
foreign import ccall safe "ql.h qlBond"
  c_bond :: CUInt -> Ptr CCalendar -> CDate -> Ptr CLeg -> Ptr CString
  -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBond1"
  c_bond' :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate -> Ptr CLeg
  -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h qlBondMaturityDate"
  c_maturityDate :: Ptr CBond -> IO CDate
foreign import ccall safe "ql.h qlBondIssueDate"
  c_issueDate :: Ptr CBond -> IO CDate

-- | (qlBond)
-- these signatures would be more approrpriate (see QuantLib::Bond::Bond)
bond :: Word -> Calendar -> Maybe Day -> Leg -> IO Bond
bond settl cal issue coupons =
  withObject2 cal coupons
  (\c -> construct . c_bond (fromIntegral settl) c (toQlDate issue))

bond' :: Word -> Calendar -> Double -> Maybe Day -> Maybe Day -> Leg -> IO Bond
bond' settl cal face maturity issue flows =
  withObject2 cal flows
  (\c -> construct . c_bond' (fromIntegral settl)
                             c
                             (realToFrac face)
                             (toQlDate maturity)
                             (toQlDate issue))

-- |Returns the maturity date of the bond (qlBondMaturityDate)
-- XXX any exceptions possible?
maturityDate :: IsA CBond a => Object a -> Maybe Day
maturityDate b = fromQlDate $ unsafePerformIO
                  (withObject b (c_maturityDate . safeCastPtr))

-- |Returns the issue date of the bond (qlBondIssueDate)
-- XXX any exceptions possible?
issueDate :: IsA CBond a => Object a -> Maybe Day
issueDate b = fromQlDate $ unsafePerformIO
                  (withObject b (c_issueDate . safeCastPtr))

foreign import ccall safe "ql.h qlFixedRateBond"
  c_fixedRateBond :: CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr CDouble -> Ptr CDayCounter
    -> CInt -> CDouble -> CDate -> Ptr CCalendar -> Ptr CString
    -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedRateBond1"
  c_fixedRateBond' :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate
    -> Ptr CPeriod -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> CDouble -> CDate -> CDate -> CInt -> CInt -> Ptr CCalendar
    -> Ptr CString -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedRateBond2"
  c_fixedRateBond'' :: CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr (Ptr CInterestRate) -> CInt -> CDouble -> CDate -> Ptr CCalendar
    -> Ptr CString -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedBondFrequency"
  c_fixedBondFrequency :: Ptr CFixedRateBond -> IO CInt

-- |(qlFixedRateBond)
fixedRateBond :: Word -> Double -> Schedule -> [Double] -> DayCounter
   -> BusinessDayConvention -> Double -> Maybe Day -> Calendar
   -> IO FixedRateBond
fixedRateBond settl face sched coupons counter conv redemption issue calendar =
  withObject3 sched counter calendar
  (\s c cal ->
        withAmounts
        coupons
        (\n cpns ->
          construct $ c_fixedRateBond (fromIntegral settl)
                                       (realToFrac face)
                                       s
                                       n
                                       cpns
                                       c
                                       (toQlEnum conv)
                                       (realToFrac redemption)
                                       (toQlDate issue)
                                       cal))

fixedRateBond' :: Word -> Calendar -> Double -> Day -> Day -> Period -> [Double]
  -> DayCounter -> BusinessDayConvention -> BusinessDayConvention -> Double
  -> Maybe Day -> Maybe Day -> DateGenerationRule -> Bool -> Calendar
  -> IO FixedRateBond
fixedRateBond' settl couponCal face start maturity tenor coupons counter accrConv paymentConv
  redemption issue stub rule eom paymentCal =
    withObject4 tenor counter couponCal paymentCal
    (\t dc cc pc ->
          withAmounts
          coupons
          (\n cpns ->
            construct $ c_fixedRateBond' (fromIntegral settl)
                                         cc
                                         (realToFrac face)
                                         (toQlDate start)
                                         (toQlDate maturity)
                                         t
                                         n
                                         cpns
                                         dc
                                         (toQlEnum accrConv)
                                         (toQlEnum paymentConv)
                                         (realToFrac redemption)
                                         (toQlDate issue)
                                         (toQlDate stub)
                                         (toQlEnum rule)
                                         (fromBool eom)
                                         pc))
                                         
-- |(qlFixedRateBond2)
fixedRateBond'' :: Word -> Double -> Schedule -> [InterestRate]
  -> BusinessDayConvention -> Double -> Maybe Day -> Calendar
  -> IO FixedRateBond
fixedRateBond'' settl face sched coupons paymentConv redemption issue cal =
  withObject2 sched cal
  (\s c ->
    withObjects coupons
    (\n cpns -> construct $ c_fixedRateBond'' (fromIntegral settl)
                                              (realToFrac face)
                                              s
                                              n
                                              cpns
                                              (toQlEnum paymentConv)
                                              (realToFrac redemption)
                                              (toQlDate issue)
                                              c))

frequency :: FixedRateBond -> Frequency
frequency x = fromQlEnum $ unsafePerformIO (withObject x c_fixedBondFrequency)
