{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Instrument.Bond
  (
  -- makers
    bond
  , bond'
  , fixedRateBond
  , fixedRateBond'
  , fixedRateBond''
  , zeroCouponBond
  , floatingRateBond
  -- accessors
  , issueDate
  , maturityDate
  , frequency
  -- mutators
  , setCouponPricer
  )

where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Frequency(Frequency)

foreign import ccall safe "ql.h qlBond"
  c_bond :: CUInt -> Ptr CCalendar -> CDate -> Ptr CLeg -> Ptr CString
  -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBond1"
  c_bond' :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate -> Ptr CLeg
  -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBondMaturityDate"
  c_maturityDate :: Ptr CBond -> IO CDate
foreign import ccall safe "ql.h qlBondIssueDate"
  c_issueDate :: Ptr CBond -> IO CDate

-- | (qlBond)
bond :: Word -> Calendar -> Maybe Day -> Leg -> IO Bond
bond = $(ffiConstruct 'bond 'c_bond)

bond' :: Word -> Calendar -> Double -> Maybe Day -> Maybe Day -> Leg -> IO Bond
bond' = $(ffiConstruct 'bond' 'c_bond')

-- |Returns the maturity date of the bond (qlBondMaturityDate)
maturityDate :: Bond -> Maybe Day
maturityDate = $(ffiCallIO 'maturityDate 'c_maturityDate)
-- XXX any exceptions possible?

-- |Returns the issue date of the bond (qlBondIssueDate)
issueDate :: Bond -> Maybe Day
issueDate = $(ffiCallIO 'issueDate 'c_issueDate)
-- XXX any exceptions possible?

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
fixedRateBond = $(ffiConstruct 'fixedRateBond 'c_fixedRateBond)

fixedRateBond' :: Word -> Calendar -> Double -> Day -> Day -> Period -> [Double]
  -> DayCounter -> BusinessDayConvention -> BusinessDayConvention -> Double
  -> Maybe Day -> Maybe Day -> DateGenerationRule -> Bool -> Calendar
  -> IO FixedRateBond
fixedRateBond' = $(ffiConstruct 'fixedRateBond' 'c_fixedRateBond')
                                         
-- |(qlFixedRateBond2)
fixedRateBond'' :: Word -> Double -> Schedule -> [InterestRate]
  -> BusinessDayConvention -> Double -> Maybe Day -> Calendar
  -> IO FixedRateBond
fixedRateBond'' = $(ffiConstruct 'fixedRateBond'' 'c_fixedRateBond'')

frequency :: FixedRateBond -> Frequency
frequency = $(ffiCallIO 'frequency 'c_fixedBondFrequency)

foreign import ccall safe "ql.h qlZeroCouponBond"
  c_zeroCouponBond :: CUInt -> Ptr CCalendar -> CDouble -> CDate
    -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |(qlZeroCouponBond)
zeroCouponBond :: Word -> Calendar -> Double -> Day -> BusinessDayConvention
  -> Double -> Maybe Day -> IO Bond
zeroCouponBond = $(ffiConstruct 'zeroCouponBond 'c_zeroCouponBond)

foreign import ccall safe "ql.h qlBondSetCouponPricer"
  c_bondSetCouponPricer :: Ptr CBond -> Ptr CFloatingRateCouponPricer
    -> Ptr CString -> IO ()

-- |Set the coupon pricer at the given Bond object (qlBondSetCouponPricer)
-- doing like QuantLibXL here, in QuantLib it is a function working on
-- cashflows (see the implementation in qlBondSetCouponPricer)
setCouponPricer :: Bond -> FloatingRateCouponPricer -> IO ()
setCouponPricer = $(ffiCallX 'setCouponPricer 'c_bondSetCouponPricer)

foreign import ccall safe "ql.h qlFloatingRateBond"
  c_floatingRateBond :: CUInt -> CDouble -> Ptr CSchedule -> Ptr CIborIndex
    -> Ptr CDayCounter -> CInt -> CUInt -> CUInt -> Ptr CDouble
    -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble
    -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |(qlFloatingRateBond)
floatingRateBond :: Word -> Double -> Schedule -> IborIndex
  -> DayCounter -> BusinessDayConvention -> Word -> [Double] -> [Double]
  -> [Double] -> [Double] -> Bool -> Double -> Maybe Day -> IO Bond
floatingRateBond = $(ffiConstruct 'floatingRateBond 'c_floatingRateBond)
