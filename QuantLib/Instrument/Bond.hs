{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Instrument.Bond
  (
    Bond
  , bond
  , bond'
  , issueDate
  , maturityDate
  , FixedRateBond
  , fixedRateBond
  , fixedRateBond'
  , fixedRateBond''
  , frequency
  )

where

import Data.Word(Word)
import Data.Time.Calendar(Day)

import Foreign.C.Types(CDouble(CDouble), CInt(CInt), CUInt(CUInt))
import Foreign.C.String(CString)
import Foreign.Marshal.Array(withArray)
import Foreign.Ptr(Ptr, FunPtr, castPtr, castFunPtr)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.CashFlow.Leg(Leg, CLeg)
import QuantLib.Internal
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.DayCounter(DayCounter, CDayCounter)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Period(Period)
import QuantLib.Time.Schedule(Schedule, CSchedule)

data CBond
type Bond = Object CBond

instance Finalizable CBond where
  finalize = p_freeBond

data CFixedRateBond
type FixedRateBond = Object CFixedRateBond

instance Finalizable CFixedRateBond where
  finalize = safeCastFin p_freeBond

class BondClass c where
  safeCastPtr :: Ptr c -> Ptr CBond
  safeCastPtr = castPtr
  safeCastFin :: FunPtr (Ptr CBond -> IO ()) -> FunPtr (Ptr c -> IO ())
  safeCastFin = castFunPtr

instance BondClass CBond
instance BondClass CFixedRateBond

-- ideally I would like to have a class "IsA a b" and
-- "instance IsA CBond CFixedRateBond" to derive finalizers
-- and casts automatically for all descendants
-- This doesn't work:
--
-- LANGUAGE MultiParamTypeClasses,FlexibleInstances,UndecidableInstances,FlexibleContexts
-- class (Finalizable a) => IsA a b where
--   commonFinalizer :: FunPtr (Ptr a -> IO ())
--   commonFinalizer = finalize
--   upcast :: Ptr b -> Ptr a
--   upcast = castPtr
--
-- instance (IsA a b) => Finalizable b where
--   finalize = castFunPtr commonFinalizer
--
--   instance IsA CBond CFixedRateBond
--
-- maturityDate :: IsA CBond a => Object a -> Maybe Day
-- maturityDate b = fromQlDateSerialNumber $ unsafePerformIO (withObject b (c_maturityDate . upcast))

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
foreign import ccall safe "ql.h qlFixedBondFrequency"
  c_fixedBondFrequency :: Ptr CFixedRateBond -> IO CInt

-- | (qlBond)
-- these signatures would be more approrpriate (see QuantLib::Bond::Bond)
bond :: Word -> Calendar -> Maybe Day -> Leg -> IO Bond
bond settl cal issue coupons =
  withObject
  cal
  (\c ->
    withObject
    coupons
    (construct . c_bond (fromIntegral settl) c (toQlDateSerialNumber issue)))

bond' :: Word -> Calendar -> Double -> Maybe Day -> Maybe Day -> Leg -> IO Bond
bond' settl cal face maturity issue flows =
  withObject
  cal
  (\c ->
    withObject
    flows
    (construct . c_bond'  (fromIntegral settl)
                          c
                          (realToFrac face)
                          (toQlDateSerialNumber maturity)
                          (toQlDateSerialNumber issue)))

-- |Returns the maturity date of the bond (qlBondMaturityDate)
-- XXX exceptions?
maturityDate :: BondClass a => Object a -> Maybe Day
maturityDate b = fromQlDateSerialNumber $ unsafePerformIO
                  (withObject b (c_maturityDate . safeCastPtr))

-- |Returns the issue date of the bond (qlBondIssueDate)
-- XXX exceptions?
issueDate :: BondClass a => Object a -> Maybe Day
issueDate b = fromQlDateSerialNumber $ unsafePerformIO
                  (withObject b (c_issueDate . safeCastPtr))

foreign import ccall safe "ql.h qlFixedRateBond"
  c_fixedRateBond :: CUInt -> CDouble -> Ptr CSchedule
    -> CInt -> Ptr CDouble -> Ptr CDayCounter
    -> CInt -> CDouble -> CDate -> Ptr CCalendar -> Ptr CString
    -> IO (Ptr CFixedRateBond)

-- |(qlFixedRateBond)
fixedRateBond :: Word -> Double -> Schedule -> [Double] -> DayCounter
   -> BusinessDayConvention -> Double -> Maybe Day -> Calendar
   -> IO FixedRateBond
fixedRateBond settl face sched coupons counter conv redemption issue calendar =
  withObject
  sched
  (\s ->
    withObject
    counter
    (\c ->
      withObject
      calendar
      (\cal ->
        withArray
        (map realToFrac coupons)
        (\cpns ->
          construct $ c_fixedRateBond (fromIntegral settl)
                                       (realToFrac face)
                                       s
                                       (fromIntegral (length coupons))
                                       cpns
                                       c
                                       (toQlEnum conv)
                                       (realToFrac redemption)
                                       (toQlDateSerialNumber issue)
                                       cal))))

-- |(qlFixedRateBond2)
fixedRateBond' :: Word -> Double -> Day -> Day -> Period -> [Double]
  -> DayCounter -> BusinessDayConvention -> BusinessDayConvention -> Double
  -> Maybe Day -> Maybe Day -> Maybe Day -> DateGenerationRule -> Bool
  -> Calendar -> IO FixedRateBond
--fixedRateBond' settl face start maturity tenor coupons counter accrConv paymentConv
--  redemption issue stub rule eom cal = 
fixedRateBond' = undefined

fixedRateBond'' :: Word -> Double -> Schedule -> [Double]
  -> BusinessDayConvention -> Double -> Maybe Day -> Calendar
  -> IO FixedRateBond
--fixedRateBond'' settl face sched coupons paymentConv redemption issue cal =
fixedRateBond'' = undefined

frequency :: FixedRateBond -> Frequency
frequency x = fromQlEnum $ unsafePerformIO (withObject x c_fixedBondFrequency)
