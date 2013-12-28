{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Yield
  (
    depositRateHelper
  , fixedRateBondHelper
  , swapRateHelper'
  , fraRateHelper
  , bondHelper
  , oisRateHelper
  , swapRateHelper
  , bmaSwapRateHelper
  , datedOISRateHelper
  , depositRateHelper'
  , fraRateHelper'
  , fraIborRateHelper'
  , fraIborRateHelper
  , futuresRateHelper'
  , futuresIborRateHelper
  , futuresRateHelper

  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  , flatForward
  , flatForward'
  , interpolatedDiscountCurve
  , interpolatedForwardCurve
  , interpolatedZeroCurve
  , forwardSpreadedTermStructure
  , zeroSpreadedTermStructure

  , fittedBondDiscountCurve
  , fittedBondDiscountCurve'
  , minimumCostValue
  , numberOfIterations

  , discount
  , discount'
  , zeroRate
  , zeroRate'
  , forwardRate
  , forwardRate'
  , forwardRateForPeriod

  , impliedQuote

  , cubicBSplinesFitting
  , exponentialSplinesFitting
  , nelsonSiegelFitting
  , simplePolynomialFitting
  , svenssonFitting

  , referenceDate
  , maxDate
  , impliedTermStructure

  , driftTermStructure
  , piecewiseZeroSpreadedTermStructure
  , quantoTermStructure
  )
where

import QuantLib.Compounding(Compounding)
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Types
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Unit(Unit)
import QuantLib.TermStructure.Trait(Trait)

foreign import ccall safe "ql.h qlDepositRateHelper"
  c_depositRateHelper :: Ptr CQuote -> CInt -> CInt -> CUInt -> Ptr CCalendar
    -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlFixedRateBondHelper"
  c_fixedRateBondHelper :: Ptr CQuote -> CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CDouble -> CInt
    -> Ptr CString -> IO (Ptr CBondHelper)
foreign import ccall safe "ql.h qlPiecewiseYieldCurve"
  c_piecewiseYieldCurve :: CDate -> CUInt -> Ptr (Ptr CRateHelper)
    -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble
    -> CString -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

depositRateHelper :: Quote s -- ^rate
  -> (Int, Unit) -- ^tenor
  -> Word -- ^fixingDays
  -> Calendar s -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter s -- ^dayCounter
  -> QLE s (RateHelper s)
depositRateHelper = $(ffiCall 'depositRateHelper) c_depositRateHelper

fixedRateBondHelper :: Quote s -- ^cleanPrice
  -> Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule s -- ^schedule
  -> [Double] -- ^coupons
  -> DayCounter s -- ^dayCounter
  -> BusinessDayConvention -- ^paymentConv
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> QLE s (BondHelper s)
fixedRateBondHelper = $(ffiCall 'fixedRateBondHelper) c_fixedRateBondHelper

foreign import ccall safe "ql.h qlYieldTSDiscount"
  c_discount' :: Ptr CYieldTermStructure -> CDate -> CInt -> Ptr CString -> IO CDouble

piecewiseYieldCurve :: Day -- ^referenceDate
  -> [RateHelper s] -- ^instruments
  -> DayCounter s -- ^dayCounter
  -> [(Quote s, Day)] -- ^jumps and jumpDates
  -> Double -- ^accuracy
  -> Trait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> QLE s (YieldTermStructure s)
piecewiseYieldCurve = $(ffiCall 'piecewiseYieldCurve) c_piecewiseYieldCurve

foreign import ccall safe "ql.h qlPiecewiseYieldCurve1"
  c_piecewiseYieldCurve' :: CUInt -> Ptr CCalendar -> CUInt -> Ptr (Ptr CRateHelper) -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble -> CString -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar s -- ^calendar
  -> [RateHelper s] -- ^instruments
  -> DayCounter s -- ^dayCounter
  -> [(Quote s, Day)] -- ^jumps and jumpDates
  -> Double -- ^accuracy
  -> Trait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> QLE s (YieldTermStructure s)
piecewiseYieldCurve' = $(ffiCall 'piecewiseYieldCurve') c_piecewiseYieldCurve'

-- |Returns a discount factor from the given YieldTermStructure object
discount' :: YieldTermStructure s
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> QLE s Double
discount' = $(ffiCallX 'discount') c_discount'

foreign import ccall safe "ql.h qlSwapRateHelper1"
  c_swapRateHelper' :: Ptr CQuote -> CInt -> CInt -> Ptr CCalendar -> CInt
    -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CQuote -> CInt -> CInt
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapRateHelper)

swapRateHelper' :: Quote s -- ^rate
  -> (Int, Unit) -- ^tenor
  -> Calendar s -- ^calendar
  -> Frequency -- ^fixedFrequency
  -> BusinessDayConvention -- ^fixedConvention
  -> DayCounter s -- ^fixedDayCount
  -> IborIndex s -- ^iborIndex
  -> Maybe (Quote s) -- ^spread
  -> (Int, Unit) -- ^fwdStart
  -> Maybe (YieldTermStructure s) -- ^discountingCurve
  -> QLE s (SwapRateHelper s)
swapRateHelper' = $(ffiCall 'swapRateHelper') c_swapRateHelper'

flatForward :: Day -- ^referenceDate
  -> Quote s -- ^forward
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> QLE s (YieldTermStructure s)
flatForward = $(ffiCall 'flatForward) c_flatForward

foreign import ccall safe "ql.h qlFlatForward"
  c_flatForward :: CDate -> Ptr CQuote -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CYieldTermStructure)

flatForward' :: Word -- ^settlementDays
  -> Calendar s -- ^calendar
  -> Quote s -- ^forward
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> QLE s (YieldTermStructure s)
flatForward' = $(ffiCall 'flatForward') c_flatForward'

foreign import ccall safe "ql.h qlFlatForward1"
  c_flatForward' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CYieldTermStructure)

-- |The resulting interest rate has the required daycounting rule.
zeroRate' :: YieldTermStructure s
  -> Day -- ^d
  -> DayCounter s -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> QLE s (InterestRate s)
zeroRate' = $(ffiCall 'zeroRate') c_zeroRate'

foreign import ccall safe "ql.h qlYieldTermStructureZeroRate"
  c_zeroRate' :: Ptr CYieldTermStructure -> CDate -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
forwardRateForPeriod :: YieldTermStructure s
  -> Day -- ^d
  -> (Int, Unit) -- ^p
  -> DayCounter s -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> QLE s (InterestRate s)
forwardRateForPeriod = $(ffiCall 'forwardRateForPeriod) c_forwardRateForPeriod

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate1"
  c_forwardRateForPeriod :: Ptr CYieldTermStructure -> CDate -> CInt -> CInt -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the required day-counting rule.
forwardRate' :: YieldTermStructure s
  -> Day -- ^d1
  -> Day -- ^d2
  -> DayCounter s -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> QLE s (InterestRate s)
forwardRate' = $(ffiCall 'forwardRate') c_forwardRate'

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate"
  c_forwardRate' :: Ptr CYieldTermStructure -> CDate -> CDate -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
forwardRate :: YieldTermStructure s
  -> YearFraction -- ^t1
  -> YearFraction -- ^t2
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> QLE s (InterestRate s)
forwardRate = $(ffiCall 'forwardRate) c_forwardRate

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate2"
  c_forwardRate :: Ptr CYieldTermStructure -> CYearFraction -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
zeroRate :: YieldTermStructure s
  -> YearFraction -- ^t
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> QLE s (InterestRate s)
zeroRate = $(ffiCall 'zeroRate) c_zeroRate

foreign import ccall safe "ql.h qlYieldTermStructureZeroRate1"
  c_zeroRate :: Ptr CYieldTermStructure -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
discount :: YieldTermStructure s
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> QLE s Double
discount = $(ffiCallX 'discount) c_discount

foreign import ccall safe "ql.h qlYieldTermStructureDiscount1"
  c_discount :: Ptr CYieldTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

fraRateHelper :: Quote s -- ^rate
  -> Word -- ^monthsToStart
  -> Word -- ^monthsToEnd
  -> Word -- ^fixingDays
  -> Calendar s -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter s -- ^dayCounter
  -> QLE s (RateHelper s)
fraRateHelper = $(ffiCall 'fraRateHelper) c_fraRateHelper

foreign import ccall safe "ql.h qlFraRateHelper"
  c_fraRateHelper :: Ptr CQuote -> CUInt -> CUInt -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)

interpolatedDiscountCurve :: [(Double, Day)] -- ^dates, dfs
  -> DayCounter s -- ^dayCounter
  -> Calendar s -- ^cal
  -> [(Quote s, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> QLE s (YieldTermStructure s)
interpolatedDiscountCurve = $(ffiCall 'interpolatedDiscountCurve) c_interpolatedDiscountCurve

foreign import ccall safe "ql.h qlInterpolatedDiscountCurve"
  c_interpolatedDiscountCurve :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

interpolatedForwardCurve :: [(Double, Day)] -- ^dates, forwards
  -> DayCounter s -- ^dayCounter
  -> Calendar s -- ^cal
  -> [(Quote s, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> QLE s (YieldTermStructure s)
interpolatedForwardCurve = $(ffiCall 'interpolatedForwardCurve) c_interpolatedForwardCurve

foreign import ccall safe "ql.h qlInterpolatedForwardCurve"
  c_interpolatedForwardCurve :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

interpolatedZeroCurve :: [(Double, Day)] -- ^dates, yields
  -> DayCounter s -- ^dayCounter
  -> Calendar s -- ^cal
  -> [(Quote s, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> QLE s (YieldTermStructure s)
interpolatedZeroCurve = $(ffiCall 'interpolatedZeroCurve) c_interpolatedZeroCurve

foreign import ccall safe "ql.h qlInterpolatedZeroCurve"
  c_interpolatedZeroCurve :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

cubicBSplinesFitting :: [YearFraction] -- ^knotVector
  -> Bool -- ^constrainAtZero
  -> QLE s (FittedBondDiscountCurveFittingMethod s)
cubicBSplinesFitting = $(ffiCall 'cubicBSplinesFitting) c_cubicBSplinesFitting

foreign import ccall safe "ql.h qlCubicBSplinesFitting"
  c_cubicBSplinesFitting :: CUInt -> Ptr CYearFraction -> CInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

exponentialSplinesFitting :: Bool -- ^constrainAtZero
  -> QLE s (FittedBondDiscountCurveFittingMethod s)
exponentialSplinesFitting = $(ffiCall 'exponentialSplinesFitting) c_exponentialSplinesFitting

foreign import ccall safe "ql.h qlExponentialSplinesFitting"
  c_exponentialSplinesFitting :: CInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

nelsonSiegelFitting :: QLE s (FittedBondDiscountCurveFittingMethod s)
nelsonSiegelFitting = $(ffiCall 'nelsonSiegelFitting) c_nelsonSiegelFitting

foreign import ccall safe "ql.h qlNelsonSiegelFitting"
  c_nelsonSiegelFitting :: Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

simplePolynomialFitting :: Word -- ^degree
  -> Bool -- ^constrainAtZero
  -> QLE s (FittedBondDiscountCurveFittingMethod s)
simplePolynomialFitting = $(ffiCall 'simplePolynomialFitting) c_simplePolynomialFitting

foreign import ccall safe "ql.h qlSimplePolynomialFitting"
  c_simplePolynomialFitting :: CUInt -> CInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

svenssonFitting :: QLE s (FittedBondDiscountCurveFittingMethod s)
svenssonFitting = $(ffiCall 'svenssonFitting) c_svenssonFitting

foreign import ccall safe "ql.h qlSvenssonFitting"
  c_svenssonFitting :: Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

-- |reference date based on current evaluation date
fittedBondDiscountCurve' :: Word -- ^settlementDays
  -> Calendar s -- ^calendar
  -> [BondHelper s] -- ^bonds
  -> DayCounter s -- ^dayCounter
  -> FittedBondDiscountCurveFittingMethod s -- ^fittingMethod
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> [Double] -- ^guess
  -> Double -- ^simplexLambda
  -> QLE s (FittedBondDiscountCurve s)
fittedBondDiscountCurve' = $(ffiCall 'fittedBondDiscountCurve') c_fittedBondDiscountCurve'

foreign import ccall safe "ql.h qlFittedBondDiscountCurve"
  c_fittedBondDiscountCurve' :: CUInt -> Ptr CCalendar -> CUInt -> Ptr (Ptr CBondHelper) -> Ptr CDayCounter -> Ptr CFittedBondDiscountCurveFittingMethod -> CDouble -> CUInt -> CUInt -> Ptr CDouble -> CDouble -> Ptr CString -> IO (Ptr CFittedBondDiscountCurve)

-- |curve reference date fixed for life of curve
fittedBondDiscountCurve :: Day -- ^referenceDate
  -> [BondHelper s] -- ^bonds
  -> DayCounter s -- ^dayCounter
  -> FittedBondDiscountCurveFittingMethod s -- ^fittingMethod
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> [Double] -- ^guess
  -> Double -- ^simplexLambda
  -> QLE s (FittedBondDiscountCurve s)
fittedBondDiscountCurve = $(ffiCall 'fittedBondDiscountCurve) c_fittedBondDiscountCurve

foreign import ccall safe "ql.h qlFittedBondDiscountCurve1"
  c_fittedBondDiscountCurve :: CDate -> CUInt -> Ptr (Ptr CBondHelper) -> Ptr CDayCounter -> Ptr CFittedBondDiscountCurveFittingMethod -> CDouble -> CUInt -> CUInt -> Ptr CDouble -> CDouble -> Ptr CString -> IO (Ptr CFittedBondDiscountCurve)

-- |final value of cost function after optimization
minimumCostValue :: FittedBondDiscountCurve s -> QLE s Double
minimumCostValue = $(ffiCallX 'minimumCostValue) c_minimumCostValue

foreign import ccall safe "ql.h qlFittedBondDiscountCurveFittingMethodMinimumCostValue"
  c_minimumCostValue :: Ptr CFittedBondDiscountCurve -> Ptr CString -> IO CDouble

-- |final number of iterations used in the optimization problem
numberOfIterations :: FittedBondDiscountCurve s -> QLE s Int
numberOfIterations = $(ffiCallX 'numberOfIterations) c_numberOfIterations

foreign import ccall safe "ql.h qlFittedBondDiscountCurveFittingMethodNumberOfIterations"
  c_numberOfIterations :: Ptr CFittedBondDiscountCurve -> Ptr CString -> IO CInt

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
bondHelper :: Quote s -- ^cleanPrice
  -> Bond s -- ^bond
  -> QLE s (BondHelper s)
bondHelper = $(ffiCall 'bondHelper) c_bondHelper

foreign import ccall safe "ql.h qlBondHelper"
  c_bondHelper :: Ptr CQuote -> Ptr CBond -> Ptr CString -> IO (Ptr CBondHelper)

oisRateHelper :: Word -- ^settlementDays
  -> (Int, Unit) -- ^tenor
  -> Quote s -- ^fixedRate
  -> OvernightIndex s -- ^overnightIndex
  -> Maybe (YieldTermStructure s) -- ^discountingCurve
  -> QLE s (OISRateHelper s)
oisRateHelper = $(ffiCall 'oisRateHelper) c_oisRateHelper

foreign import ccall safe "ql.h qlOISRateHelper"
  c_oisRateHelper :: CUInt -> CInt -> CInt -> Ptr CQuote -> Ptr COvernightIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr COISRateHelper)

swapRateHelper :: Quote s -- ^rate
  -> SwapIndex s -- ^swapIndex
  -> Maybe (Quote s) -- ^spread
  -> (Int, Unit) -- ^fwdStart
  -> Maybe (YieldTermStructure s) -- ^discountingCurve
  -> QLE s (SwapRateHelper s)
swapRateHelper = $(ffiCall 'swapRateHelper) c_swapRateHelper

foreign import ccall safe "ql.h qlSwapRateHelper"
  c_swapRateHelper :: Ptr CQuote -> Ptr CSwapIndex -> Ptr CQuote -> CInt -> CInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapRateHelper)

forwardSpreadedTermStructure :: YieldTermStructure s
  -> Quote s -- ^spread
  -> QLE s (YieldTermStructure s)
forwardSpreadedTermStructure = $(ffiCall 'forwardSpreadedTermStructure) c_forwardSpreadedTermStructure

foreign import ccall safe "ql.h qlForwardSpreadedTermStructure"
  c_forwardSpreadedTermStructure :: Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CYieldTermStructure)

zeroSpreadedTermStructure :: YieldTermStructure s
  -> Quote s -- ^spread
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> DayCounter s -- ^dc
  -> QLE s (YieldTermStructure s)
zeroSpreadedTermStructure = $(ffiCall 'zeroSpreadedTermStructure) c_zeroSpreadedTermStructure

foreign import ccall safe "ql.h qlZeroSpreadedTermStructure"
  c_zeroSpreadedTermStructure :: Ptr CYieldTermStructure -> Ptr CQuote -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CYieldTermStructure)

bmaSwapRateHelper :: Quote s -- ^liborFraction
  -> (Int, Unit) -- ^tenor
  -> Word -- ^settlementDays
  -> Calendar s -- ^calendar
  -> (Int, Unit) -- ^bmaPeriod
  -> BusinessDayConvention -- ^bmaConvention
  -> DayCounter s -- ^bmaDayCount
  -> BMAIndex s -- ^bmaIndex
  -> IborIndex s -- ^index
  -> QLE s (RateHelper s)
bmaSwapRateHelper = $(ffiCall 'bmaSwapRateHelper) c_bmaSwapRateHelper

foreign import ccall safe "ql.h qlBMASwapRateHelper"
  c_bmaSwapRateHelper :: Ptr CQuote -> CInt -> CInt -> CUInt -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> Ptr CBMAIndex -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

datedOISRateHelper :: Day -- ^startDate
  -> Day -- ^endDate
  -> Quote s -- ^fixedRate
  -> OvernightIndex s -- ^overnightIndex
  -> Maybe (YieldTermStructure s) -- ^discountingCurve
  -> QLE s (RateHelper s)
datedOISRateHelper = $(ffiCall 'datedOISRateHelper) c_datedOISRateHelper

foreign import ccall safe "ql.h qlDatedOISRateHelper"
  c_datedOISRateHelper :: CDate -> CDate -> Ptr CQuote -> Ptr COvernightIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CRateHelper)

depositRateHelper' :: Quote s -- ^rate
  -> IborIndex s -- ^iborIndex
  -> QLE s (RateHelper s)
depositRateHelper' = $(ffiCall 'depositRateHelper') c_depositRateHelper'

foreign import ccall safe "ql.h qlDepositRateHelper1"
  c_depositRateHelper' :: Ptr CQuote -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

fraIborRateHelper' :: Quote s -- ^rate
  -> Word -- ^monthsToStart
  -> IborIndex s -- ^iborIndex
  -> QLE s (RateHelper s)
fraIborRateHelper' = $(ffiCall 'fraIborRateHelper') c_fraIborRateHelper'

foreign import ccall safe "ql.h qlFraRateHelper1"
  c_fraIborRateHelper' :: Ptr CQuote -> CUInt -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

fraRateHelper' :: Quote s -- ^rate
  -> (Int, Unit) -- ^periodToStart
  -> Word -- ^lengthInMonths
  -> Word -- ^fixingDays
  -> Calendar s -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter s -- ^dayCounter
  -> QLE s (RateHelper s)
fraRateHelper' = $(ffiCall 'fraRateHelper') c_fraRateHelper'

foreign import ccall safe "ql.h qlFraRateHelper2"
  c_fraRateHelper' :: Ptr CQuote -> CInt -> CInt -> CUInt -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)

fraIborRateHelper :: Quote s -- ^rate
  -> (Int, Unit) -- ^periodToStart
  -> IborIndex s -- ^iborIndex
  -> QLE s (RateHelper s)
fraIborRateHelper = $(ffiCall 'fraIborRateHelper) c_fraIborRateHelper

foreign import ccall safe "ql.h qlFraRateHelper3"
  c_fraIborRateHelper :: Ptr CQuote -> CInt -> CInt -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

futuresRateHelper' :: Quote s -- ^price
  -> Day -- ^immStartDate
  -> Day -- ^endDate
  -> DayCounter s -- ^dayCounter
  -> Maybe (Quote s) -- ^convexityAdjustment
  -> QLE s (RateHelper s)
futuresRateHelper' = $(ffiCall 'futuresRateHelper') c_futuresRateHelper'

foreign import ccall safe "ql.h qlFuturesRateHelper1"
  c_futuresRateHelper' :: Ptr CQuote -> CDate -> CDate -> Ptr CDayCounter -> Ptr CQuote -> Ptr CString -> IO (Ptr CRateHelper)

futuresIborRateHelper :: Quote s -- ^price
  -> Day -- ^immDate
  -> IborIndex s -- ^iborIndex
  -> Maybe (Quote s) -- ^convexityAdjustment
  -> QLE s (RateHelper s)
futuresIborRateHelper = $(ffiCall 'futuresIborRateHelper) c_futuresIborRateHelper

foreign import ccall safe "ql.h qlFuturesRateHelper2"
  c_futuresIborRateHelper :: Ptr CQuote -> CDate -> Ptr CIborIndex -> Ptr CQuote -> Ptr CString -> IO (Ptr CRateHelper)

futuresRateHelper :: Quote s -- ^price
  -> Day -- ^immDate
  -> Word -- ^lengthInMonths
  -> Calendar s -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter s -- ^dayCounter
  -> Maybe (Quote s) -- ^convexityAdjustment
  -> QLE s (RateHelper s)
futuresRateHelper = $(ffiCall 'futuresRateHelper) c_futuresRateHelper

foreign import ccall safe "ql.h qlFuturesRateHelper"
  c_futuresRateHelper :: Ptr CQuote -> CDate -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CQuote -> Ptr CString -> IO (Ptr CRateHelper)

impliedQuote :: RateHelper s -> QLE s Double
impliedQuote = $(ffiCallX 'impliedQuote) c_impliedQuote

foreign import ccall safe "ql.h qlRateHelperImpliedQuote"
  c_impliedQuote :: Ptr CRateHelper -> Ptr CString -> IO CDouble

-- |the date at which discount = 1.0 and/or variance = 0.0
referenceDate :: TermStructure s -> QLE s Day
referenceDate = $(ffiCallX 'referenceDate) c_referenceDate

foreign import ccall safe "ql.h qlTermStructureReferenceDate"
  c_referenceDate :: Ptr CTermStructure -> Ptr CString -> IO CDate

maxDate :: TermStructure s -> QLE s Day
maxDate = $(ffiCallX 'maxDate) c_maxDate

foreign import ccall safe "ql.h qlTermStructureMaxDate"
  c_maxDate :: Ptr CTermStructure -> Ptr CString -> IO CDate

impliedTermStructure :: YieldTermStructure s
  -> Day -- ^referenceDate
  -> QLE s (YieldTermStructure s)
impliedTermStructure = $(ffiCall 'impliedTermStructure) c_impliedTermStructure

foreign import ccall safe "ql.h qlImpliedTermStructure"
  c_impliedTermStructure :: Ptr CYieldTermStructure -> CDate -> Ptr CString -> IO (Ptr CYieldTermStructure)

driftTermStructure :: YieldTermStructure s -- ^riskFreeTS
  -> YieldTermStructure s -- ^dividendTS
  -> BlackVolTermStructure s -- ^blackVolTS
  -> QLE s (YieldTermStructure s)
driftTermStructure = $(ffiCall 'driftTermStructure) c_driftTermStructure

foreign import ccall safe "ql.h qlDriftTermStructure"
  c_driftTermStructure :: Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> Ptr CString -> IO (Ptr CYieldTermStructure)

piecewiseZeroSpreadedTermStructure :: YieldTermStructure s
  -> [(Quote s, Day)] -- ^spreads, ^dates
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> DayCounter s -- ^dc
  -> QLE s (YieldTermStructure s)
piecewiseZeroSpreadedTermStructure = $(ffiCall 'piecewiseZeroSpreadedTermStructure) c_piecewiseZeroSpreadedTermStructure

foreign import ccall safe "ql.h qlPiecewiseZeroSpreadedTermStructure"
  c_piecewiseZeroSpreadedTermStructure :: Ptr CYieldTermStructure -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CYieldTermStructure)

quantoTermStructure :: YieldTermStructure s -- ^underlyingDividendTS
  -> YieldTermStructure s -- ^riskFreeTS
  -> YieldTermStructure s -- ^foreignRiskFreeTS
  -> BlackVolTermStructure s -- ^underlyingBlackVolTS
  -> Double -- ^strike
  -> BlackVolTermStructure s -- ^exchRateBlackVolTS
  -> Double -- ^exchRateATMlevel
  -> Double -- ^underlyingExchRateCorrelation
  -> QLE s (YieldTermStructure s)
quantoTermStructure = $(ffiCall 'quantoTermStructure) c_quantoTermStructure

foreign import ccall safe "ql.h qlQuantoTermStructure"
  c_quantoTermStructure :: Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CBlackVolTermStructure -> CDouble -> Ptr CBlackVolTermStructure -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CYieldTermStructure)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
