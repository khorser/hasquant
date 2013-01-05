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

import Foreign.C.Types(CDouble(CDouble), CUInt(CUInt))
import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr, castPtr, castFunPtr)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.CashFlow.Leg(Leg, CLeg)
import QuantLib.Internal(CDate, withObject, Object, construct, Finalizable, finalize, toQlDateSerialNumber, fromQlDateSerialNumber)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.DayCounter(DayCounter)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Period(Period)
import QuantLib.Time.Schedule(Schedule)

data CBond

type Bond = Object CBond

class BondClass c

instance BondClass CBond

-- is it possible to use type class constraints in FFI declarations?
foreign import ccall safe "ql.h qlBond"
  c_bond :: CUInt -> Ptr CCalendar -> CDate -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBond2"
  c_bond2 :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h qlBondMaturityDate"
  c_maturityDate :: Ptr CBond -> IO CDate
foreign import ccall safe "ql.h qlBondIssueDate"
  c_issueDate :: Ptr CBond -> IO CDate

instance Finalizable CBond where
  finalize = p_freeBond

data CFixedRateBond

type FixedRateBond = Object CFixedRateBond

instance Finalizable CFixedRateBond where
  finalize = castFunPtr p_freeBond

instance BondClass CFixedRateBond

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
    (construct . c_bond2 (fromIntegral settl) c (realToFrac face) (toQlDateSerialNumber maturity) (toQlDateSerialNumber issue)))

-- |Returns the maturity date of the bond (qlBondMaturityDate)
-- XXX exceptions?
maturityDate :: BondClass a => Object a -> Maybe Day
maturityDate b = fromQlDateSerialNumber $ unsafePerformIO (withObject b (c_maturityDate . castPtr))

-- |Returns the issue date of the bond (qlBondIssueDate)
-- XXX exceptions?
issueDate :: BondClass a => Object a -> Maybe Day
issueDate b = fromQlDateSerialNumber $ unsafePerformIO (withObject b (c_issueDate . castPtr))

-- |(qlFixedRateBond)
fixedRateBond :: Word -> Double -> Schedule -> [Double] -> DayCounter
   -> BusinessDayConvention -> Double -> Maybe Day -> Calendar -> IO FixedRateBond
fixedRateBond settl face sched coupons counter conv redemption issue cal = undefined

-- |(qlFixedRateBond2)
fixedRateBond' :: Word -> Double -> Day -> Day -> Period -> [Double] -> DayCounter
  -> BusinessDayConvention -> BusinessDayConvention -> Double -> Maybe Day
  -> Maybe Day -> Maybe Day -> DateGenerationRule -> Bool -> Calendar -> IO FixedRateBond
fixedRateBond' settl face start maturity tenor coupons counter accrConv paymentConv
  redemption issue stub rule eom cal = undefined

fixedRateBond'' :: Word -> Double -> Schedule -> [Double] -> BusinessDayConvention
  -> Double -> Maybe Day -> Calendar -> IO FixedRateBond
fixedRateBond'' settl face sched coupons paymentConv redemption issue cal =
  undefined

frequency :: FixedRateBond -> Frequency
frequency = undefined
