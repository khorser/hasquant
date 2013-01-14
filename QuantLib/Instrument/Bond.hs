{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls,MultiParamTypeClasses,FlexibleContexts #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
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

import QuantLib.Internal
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Frequency(Frequency)

instance Finalizable CBond where
  finalize = p_freeBond

instance Finalizable CFixedRateBond where
  finalize = castFinalizer p_freeBond

instance IsA CBond CBond where
  cast = id
instance IsA CBond CFixedRateBond where
  cast = castPtr

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
maturityDate b = fromQlDate $ unsafePerformIO (withCast b c_maturityDate)

-- |Returns the issue date of the bond (qlBondIssueDate)
-- XXX any exceptions possible?
issueDate :: IsA CBond a => Object a -> Maybe Day
issueDate b = fromQlDate $ unsafePerformIO (withCast b c_issueDate)

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

foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> Ptr CInstrument

instance IsA CInstrument CBond where
  cast = c_bondAsInstrument

instance IsA CInstrument CFixedRateBond where
  cast = c_bondAsInstrument . cast -- delegating to the Bond casting interface

foreign import ccall safe "ql.h qlZeroCouponBond"
  c_zeroCouponBond :: CUInt -> Ptr CCalendar -> CDouble -> CDate
    -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |(qlZeroCouponBond)
zeroCouponBond :: Word -> Calendar -> Double -> Day -> BusinessDayConvention
  -> Double -> Maybe Day -> IO Bond
zeroCouponBond settlDays cal face maturity payConv redemption issue =
  withObject cal
    (\c -> construct $ c_zeroCouponBond (fromIntegral settlDays)
                                        c
                                        (realToFrac face)
                                        (toQlDate maturity)
                                        (toQlEnum payConv)
                                        (realToFrac redemption)
                                        (toQlDate issue))

foreign import ccall safe "ql.h qlBondSetCouponPricer"
  c_bondSetCouponPricer :: Ptr CBond -> Ptr CFloatingRateCouponPricer
    -> Ptr CString -> IO ()

-- |Set the coupon pricer at the given Bond object (qlBondSetCouponPricer)
-- doing like QuantLibXL here, in QuantLib it is a function working on
-- cashflows (see the implementation in qlBondSetCouponPricer)
setCouponPricer :: IsA CBond a => Object a -> FloatingRateCouponPricer -> IO ()
setCouponPricer b p = 
  withCast b
  (\bb -> withObject p (handleExceptions . c_bondSetCouponPricer bb))

foreign import ccall safe "ql.h qlFloatingRateBond"
  c_floatingRateBond :: CUInt -> CDouble -> Ptr CSchedule -> Ptr CIborIndex
    -> Ptr CDayCounter -> CInt -> CUInt -> CUInt -> Ptr CDouble
    -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble
    -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |(qlFloatingRateBond)
floatingRateBond :: Word -> Double -> Schedule -> IborIndex
  -> DayCounter -> BusinessDayConvention -> Word -> [Double] -> [Double]
  -> [Double] -> [Double] -> Bool -> Double -> Maybe Day -> IO Bond
floatingRateBond settlDays face schedule index accrDayCounter paymentConv
  fixDays gearings spreads caps floors inArrears redemption issue =
    withObject3 schedule index accrDayCounter
    (\sched indx dc ->
      withAmounts gearings
      (\ng gs ->
        withAmounts spreads
        (\ns sps ->
          withAmounts caps
          (\nc cs ->
            withAmounts floors
            (\nf fs ->
              construct $ c_floatingRateBond (fromIntegral settlDays)
                                             (realToFrac face)
                                             sched
                                             indx
                                             dc
                                             (toQlEnum paymentConv)
                                             (fromIntegral fixDays)
                                             ng
                                             gs
                                             ns
                                             sps
                                             nc
                                             cs
                                             nf
                                             fs
                                             (fromBool inArrears)
                                             (realToFrac redemption)
                                             (toQlDate issue))))))
