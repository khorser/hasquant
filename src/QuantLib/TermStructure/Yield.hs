{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
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
  , fraRateHelper''
  , fraRateHelper'''
  , futuresRateHelper'
  , futuresRateHelper''
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
  , forwardRate''

  , impliedQuote

  , cubicBSplinesFitting
  , exponentialSplinesFitting
  , nelsonSiegelFitting
  , simplePolynomialFitting
  , svenssonFitting
  )
where

import QuantLib.Compounding
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.TermStructure.Trait(Trait)

foreign import ccall safe "ql.h qlDepositRateHelper"
  c_depositRateHelper :: Ptr CQuote -> Ptr CPeriod -> CUInt -> Ptr CCalendar
    -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlFixedRateBondHelper"
  c_fixedRateBondHelper :: Ptr CQuote -> CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CDouble -> CInt
    -> Ptr CString -> IO (Ptr CBondHelper)
foreign import ccall safe "ql.h qlPiecewiseYieldCurve"
  c_piecewiseYieldCurve :: CDate -> CUInt -> Ptr (Ptr CRateHelper)
    -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble
    -> CString -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

-- |QuantLibXL: qlDepositRateHelper2
depositRateHelper :: Quote -- ^rate
  -> Period -- ^tenor
  -> Word -- ^fixingDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> IO RateHelper
depositRateHelper = $(ffiConstruct 'depositRateHelper) c_depositRateHelper

-- |QuantLibXL: qlFixedRateBondHelper
fixedRateBondHelper :: Quote -- ^cleanPrice
  -> Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [Double] -- ^coupons
  -> DayCounter -- ^dayCounter
  -> BusinessDayConvention -- ^paymentConv
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> IO BondHelper
fixedRateBondHelper = $(ffiConstruct 'fixedRateBondHelper) c_fixedRateBondHelper

foreign import ccall safe "ql.h qlYieldTSDiscount"
  c_yieldTSDiscount :: Ptr CYieldTermStructure -> CDate -> CInt
    -> Ptr CString -> IO CDouble

piecewiseYieldCurve :: Day -- ^referenceDate
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> Double -- ^accuracy
  -> Trait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve =
  $(ffiConstruct 'piecewiseYieldCurve) c_piecewiseYieldCurve

foreign import ccall safe "ql.h qlPiecewiseYieldCurve1"
  c_piecewiseYieldCurve' :: CUInt -> Ptr CCalendar -> CUInt
    -> Ptr (Ptr CRateHelper) -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote)
    -> Ptr CDate -> CDouble -> CString -> CString -> Ptr CString
    -> IO (Ptr CYieldTermStructure)

-- |QuantLibXL: qlPiecewiseYieldCurve
piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> Double -- ^accuracy
  -> Trait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve' = $(ffiConstruct 'piecewiseYieldCurve') c_piecewiseYieldCurve'

-- |Returns a discount factor from the given YieldTermStructure object. QuantLibXL: qlYieldTSDiscount
discount :: YieldTermStructure
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> IO Double
discount = $(ffiCallX 'discount) c_yieldTSDiscount

foreign import ccall safe "ql.h qlSwapRateHelper1"
  c_swapRateHelper' :: Ptr CQuote -> Ptr CPeriod -> Ptr CCalendar -> CInt
    -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CQuote -> Ptr CPeriod
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapRateHelper)

-- |QuantLibXL: qlSwapRateHelper2
swapRateHelper' :: Quote -- ^rate
  -> Period -- ^tenor
  -> Calendar -- ^calendar
  -> Frequency -- ^fixedFrequency
  -> BusinessDayConvention -- ^fixedConvention
  -> DayCounter -- ^fixedDayCount
  -> IborIndex -- ^iborIndex
  -> Quote -- ^spread
  -> Period -- ^fwdStart
  -> Maybe YieldTermStructure -- ^discountingCurve
  -> IO SwapRateHelper
swapRateHelper' = $(ffiConstruct 'swapRateHelper') c_swapRateHelper'

flatForward :: Day -- ^referenceDate
  -> Quote -- ^forward
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> IO YieldTermStructure
flatForward = $(ffiConstruct 'flatForward) c_flatForward

foreign import ccall safe "ql.h qlFlatForward"
  c_flatForward :: CDate -> Ptr CQuote -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CYieldTermStructure)

flatForward' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Quote -- ^forward
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> IO YieldTermStructure
flatForward' = $(ffiConstruct 'flatForward') c_flatForward'

foreign import ccall safe "ql.h qlFlatForward1"
  c_flatForward' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CYieldTermStructure)

-- |The resulting interest rate has the required daycounting rule.
zeroRate :: YieldTermStructure
  -> Day -- ^d
  -> DayCounter -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
zeroRate = $(ffiConstruct 'zeroRate) c_zeroRate

foreign import ccall safe "ql.h qlYieldTermStructureZeroRate"
  c_zeroRate :: Ptr CYieldTermStructure -> CDate -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
forwardRate' :: YieldTermStructure
  -> Day -- ^d
  -> Period -- ^p
  -> DayCounter -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
forwardRate' = $(ffiConstruct 'forwardRate') c_forwardRate'

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate1"
  c_forwardRate' :: Ptr CYieldTermStructure -> CDate -> Ptr CPeriod -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the required day-counting rule.
forwardRate :: YieldTermStructure
  -> Day -- ^d1
  -> Day -- ^d2
  -> DayCounter -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
forwardRate = $(ffiConstruct 'forwardRate) c_forwardRate

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate"
  c_forwardRate :: Ptr CYieldTermStructure -> CDate -> CDate -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
forwardRate'' :: YieldTermStructure
  -> YearFraction -- ^t1
  -> YearFraction -- ^t2
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
forwardRate'' = $(ffiConstruct 'forwardRate'') c_forwardRate''

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate2"
  c_forwardRate'' :: Ptr CYieldTermStructure -> CYearFraction -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
zeroRate' :: YieldTermStructure
  -> YearFraction -- ^t
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
zeroRate' = $(ffiConstruct 'zeroRate') c_zeroRate'

foreign import ccall safe "ql.h qlYieldTermStructureZeroRate1"
  c_zeroRate' :: Ptr CYieldTermStructure -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
discount' :: YieldTermStructure
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> IO Double
discount' = $(ffiCallX 'discount') c_discount'

foreign import ccall safe "ql.h qlYieldTermStructureDiscount1"
  c_discount' :: Ptr CYieldTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

fraRateHelper :: Quote -- ^rate
  -> Word -- ^monthsToStart
  -> Word -- ^monthsToEnd
  -> Word -- ^fixingDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> IO RateHelper
fraRateHelper = $(ffiConstruct 'fraRateHelper) c_fraRateHelper

foreign import ccall safe "ql.h qlFraRateHelper"
  c_fraRateHelper :: Ptr CQuote -> CUInt -> CUInt -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)

interpolatedDiscountCurve :: [(Double, Day)] -- ^dates, dfs
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedDiscountCurve = $(ffiConstruct 'interpolatedDiscountCurve) c_interpolatedDiscountCurve

foreign import ccall safe "ql.h qlInterpolatedDiscountCurve"
  c_interpolatedDiscountCurve :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

interpolatedForwardCurve :: [(Double, Day)] -- ^dates, forwards
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedForwardCurve = $(ffiConstruct 'interpolatedForwardCurve) c_interpolatedForwardCurve

foreign import ccall safe "ql.h qlInterpolatedForwardCurve"
  c_interpolatedForwardCurve :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

interpolatedZeroCurve :: [(Double, Day)] -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve = $(ffiConstruct 'interpolatedZeroCurve) c_interpolatedZeroCurve

foreign import ccall safe "ql.h qlInterpolatedZeroCurve"
  c_interpolatedZeroCurve :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CDayCounter -> Ptr CCalendar -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

cubicBSplinesFitting :: [YearFraction] -- ^knotVector
  -> Bool -- ^constrainAtZero
  -> IO FittedBondDiscountCurveFittingMethod
cubicBSplinesFitting = $(ffiConstruct 'cubicBSplinesFitting) c_cubicBSplinesFitting

foreign import ccall safe "ql.h qlCubicBSplinesFitting"
  c_cubicBSplinesFitting :: CUInt -> Ptr CYearFraction -> CInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

exponentialSplinesFitting :: Bool -- ^constrainAtZero
  -> IO FittedBondDiscountCurveFittingMethod
exponentialSplinesFitting = $(ffiConstruct 'exponentialSplinesFitting) c_exponentialSplinesFitting

foreign import ccall safe "ql.h qlExponentialSplinesFitting"
  c_exponentialSplinesFitting :: CInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

nelsonSiegelFitting :: IO FittedBondDiscountCurveFittingMethod
nelsonSiegelFitting = $(ffiConstruct 'nelsonSiegelFitting) c_nelsonSiegelFitting

foreign import ccall safe "ql.h qlNelsonSiegelFitting"
  c_nelsonSiegelFitting :: Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

simplePolynomialFitting :: Word -- ^degree
  -> Bool -- ^constrainAtZero
  -> IO FittedBondDiscountCurveFittingMethod
simplePolynomialFitting = $(ffiConstruct 'simplePolynomialFitting) c_simplePolynomialFitting

foreign import ccall safe "ql.h qlSimplePolynomialFitting"
  c_simplePolynomialFitting :: CUInt -> CInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

svenssonFitting :: IO FittedBondDiscountCurveFittingMethod
svenssonFitting = $(ffiConstruct 'svenssonFitting) c_svenssonFitting

foreign import ccall safe "ql.h qlSvenssonFitting"
  c_svenssonFitting :: Ptr CString -> IO (Ptr CFittedBondDiscountCurveFittingMethod)

-- |reference date based on current evaluation date
-- unlike C++ library we do not expose /guess/ and /simplexLambda/ arguments (yet)
fittedBondDiscountCurve :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [BondHelper] -- ^bonds
  -> DayCounter -- ^dayCounter
  -> FittedBondDiscountCurveFittingMethod -- ^fittingMethod
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> IO FittedBondDiscountCurve
fittedBondDiscountCurve = $(ffiConstruct 'fittedBondDiscountCurve) c_fittedBondDiscountCurve

foreign import ccall safe "ql.h qlFittedBondDiscountCurve"
  c_fittedBondDiscountCurve :: CUInt -> Ptr CCalendar -> CUInt -> Ptr (Ptr CBondHelper) -> Ptr CDayCounter -> Ptr CFittedBondDiscountCurveFittingMethod -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurve)

-- |curve reference date fixed for life of curve
fittedBondDiscountCurve' :: Day -- ^referenceDate
  -> [BondHelper] -- ^bonds
  -> DayCounter -- ^dayCounter
  -> FittedBondDiscountCurveFittingMethod -- ^fittingMethod
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> IO FittedBondDiscountCurve
fittedBondDiscountCurve' = $(ffiConstruct 'fittedBondDiscountCurve') c_fittedBondDiscountCurve'

foreign import ccall safe "ql.h qlFittedBondDiscountCurve1"
  c_fittedBondDiscountCurve' :: CDate -> CUInt -> Ptr (Ptr CBondHelper) -> Ptr CDayCounter -> Ptr CFittedBondDiscountCurveFittingMethod -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CFittedBondDiscountCurve)

-- |final value of cost function after optimization
minimumCostValue :: FittedBondDiscountCurve -> IO Double
minimumCostValue = $(ffiCallX 'minimumCostValue) c_minimumCostValue

foreign import ccall safe "ql.h qlFittedBondDiscountCurveFittingMethodMinimumCostValue"
  c_minimumCostValue :: Ptr CFittedBondDiscountCurve -> Ptr CString -> IO CDouble

-- |final number of iterations used in the optimization problem
numberOfIterations :: FittedBondDiscountCurve -> IO Int
numberOfIterations = $(ffiCallX 'numberOfIterations) c_numberOfIterations

foreign import ccall safe "ql.h qlFittedBondDiscountCurveFittingMethodNumberOfIterations"
  c_numberOfIterations :: Ptr CFittedBondDiscountCurve -> Ptr CString -> IO CInt

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
bondHelper :: Quote -- ^cleanPrice
  -> Bond -- ^bond
  -> IO BondHelper
bondHelper = $(ffiConstruct 'bondHelper) c_bondHelper

foreign import ccall safe "ql.h qlBondHelper"
  c_bondHelper :: Ptr CQuote -> Ptr CBond -> Ptr CString -> IO (Ptr CBondHelper)

oisRateHelper :: Word -- ^settlementDays
  -> Period -- ^tenor
  -> Quote -- ^fixedRate
  -> OvernightIndex -- ^overnightIndex
  -> Maybe YieldTermStructure -- ^discountingCurve
  -> IO OISRateHelper
oisRateHelper = $(ffiConstruct 'oisRateHelper) c_oisRateHelper

foreign import ccall safe "ql.h qlOISRateHelper"
  c_oisRateHelper :: CUInt -> Ptr CPeriod -> Ptr CQuote -> Ptr COvernightIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr COISRateHelper)

swapRateHelper :: Quote -- ^rate
  -> SwapIndex -- ^swapIndex
  -> Maybe Quote -- ^spread
  -> Period -- ^fwdStart
  -> Maybe YieldTermStructure -- ^discountingCurve
  -> IO SwapRateHelper
swapRateHelper = $(ffiConstruct 'swapRateHelper) c_swapRateHelper

foreign import ccall safe "ql.h qlSwapRateHelper"
  c_swapRateHelper :: Ptr CQuote -> Ptr CSwapIndex -> Ptr CQuote -> Ptr CPeriod -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapRateHelper)

forwardSpreadedTermStructure :: YieldTermStructure
  -> Quote -- ^spread
  -> IO YieldTermStructure
forwardSpreadedTermStructure = $(ffiConstruct 'forwardSpreadedTermStructure) c_forwardSpreadedTermStructure

foreign import ccall safe "ql.h qlForwardSpreadedTermStructure"
  c_forwardSpreadedTermStructure :: Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CString -> IO (Ptr CYieldTermStructure)

zeroSpreadedTermStructure :: YieldTermStructure
  -> Quote -- ^spread
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> DayCounter -- ^dc
  -> IO YieldTermStructure
zeroSpreadedTermStructure = $(ffiConstruct 'zeroSpreadedTermStructure) c_zeroSpreadedTermStructure

foreign import ccall safe "ql.h qlZeroSpreadedTermStructure"
  c_zeroSpreadedTermStructure :: Ptr CYieldTermStructure -> Ptr CQuote -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CYieldTermStructure)

bmaSwapRateHelper :: Quote -- ^liborFraction
  -> Period -- ^tenor
  -> Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Period -- ^bmaPeriod
  -> BusinessDayConvention -- ^bmaConvention
  -> DayCounter -- ^bmaDayCount
  -> BMAIndex -- ^bmaIndex
  -> IborIndex -- ^index
  -> IO RateHelper
bmaSwapRateHelper = $(ffiConstruct 'bmaSwapRateHelper) c_bmaSwapRateHelper

foreign import ccall safe "ql.h qlBMASwapRateHelper"
  c_bmaSwapRateHelper :: Ptr CQuote -> Ptr CPeriod -> CUInt -> Ptr CCalendar -> Ptr CPeriod -> CInt -> Ptr CDayCounter -> Ptr CBMAIndex -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

datedOISRateHelper :: Day -- ^startDate
  -> Day -- ^endDate
  -> Quote -- ^fixedRate
  -> OvernightIndex -- ^overnightIndex
  -> Maybe YieldTermStructure -- ^discountingCurve
  -> IO RateHelper
datedOISRateHelper = $(ffiConstruct 'datedOISRateHelper) c_datedOISRateHelper

foreign import ccall safe "ql.h qlDatedOISRateHelper"
  c_datedOISRateHelper :: CDate -> CDate -> Ptr CQuote -> Ptr COvernightIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CRateHelper)

depositRateHelper' :: Quote -- ^rate
  -> IborIndex -- ^iborIndex
  -> IO RateHelper
depositRateHelper' = $(ffiConstruct 'depositRateHelper') c_depositRateHelper'

foreign import ccall safe "ql.h qlDepositRateHelper1"
  c_depositRateHelper' :: Ptr CQuote -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

fraRateHelper' :: Quote -- ^rate
  -> Word -- ^monthsToStart
  -> IborIndex -- ^iborIndex
  -> IO RateHelper
fraRateHelper' = $(ffiConstruct 'fraRateHelper') c_fraRateHelper'

foreign import ccall safe "ql.h qlFraRateHelper1"
  c_fraRateHelper' :: Ptr CQuote -> CUInt -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

fraRateHelper'' :: Quote -- ^rate
  -> Period -- ^periodToStart
  -> Word -- ^lengthInMonths
  -> Word -- ^fixingDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> IO RateHelper
fraRateHelper'' = $(ffiConstruct 'fraRateHelper'') c_fraRateHelper''

foreign import ccall safe "ql.h qlFraRateHelper2"
  c_fraRateHelper'' :: Ptr CQuote -> Ptr CPeriod -> CUInt -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)

fraRateHelper''' :: Quote -- ^rate
  -> Period -- ^periodToStart
  -> IborIndex -- ^iborIndex
  -> IO RateHelper
fraRateHelper''' = $(ffiConstruct 'fraRateHelper''') c_fraRateHelper'''

foreign import ccall safe "ql.h qlFraRateHelper3"
  c_fraRateHelper''' :: Ptr CQuote -> Ptr CPeriod -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CRateHelper)

futuresRateHelper' :: Quote -- ^price
  -> Day -- ^immStartDate
  -> Day -- ^endDate
  -> DayCounter -- ^dayCounter
  -> Maybe Quote -- ^convexityAdjustment
  -> IO RateHelper
futuresRateHelper' = $(ffiConstruct 'futuresRateHelper') c_futuresRateHelper'

foreign import ccall safe "ql.h qlFuturesRateHelper1"
  c_futuresRateHelper' :: Ptr CQuote -> CDate -> CDate -> Ptr CDayCounter -> Ptr CQuote -> Ptr CString -> IO (Ptr CRateHelper)

futuresRateHelper'' :: Quote -- ^price
  -> Day -- ^immDate
  -> IborIndex -- ^iborIndex
  -> Maybe Quote -- ^convexityAdjustment
  -> IO RateHelper
futuresRateHelper'' = $(ffiConstruct 'futuresRateHelper'') c_futuresRateHelper''

foreign import ccall safe "ql.h qlFuturesRateHelper2"
  c_futuresRateHelper'' :: Ptr CQuote -> CDate -> Ptr CIborIndex -> Ptr CQuote -> Ptr CString -> IO (Ptr CRateHelper)

futuresRateHelper :: Quote -- ^price
  -> Day -- ^immDate
  -> Word -- ^lengthInMonths
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> Maybe Quote -- ^convexityAdjustment
  -> IO RateHelper
futuresRateHelper = $(ffiConstruct 'futuresRateHelper) c_futuresRateHelper

foreign import ccall safe "ql.h qlFuturesRateHelper"
  c_futuresRateHelper :: Ptr CQuote -> CDate -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CQuote -> Ptr CString -> IO (Ptr CRateHelper)

impliedQuote :: RateHelper -> IO Double
impliedQuote = $(ffiCallX 'impliedQuote) c_impliedQuote

foreign import ccall safe "ql.h qlRateHelperImpliedQuote"
  c_impliedQuote :: Ptr CRateHelper -> Ptr CString -> IO CDouble
