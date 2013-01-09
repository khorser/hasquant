{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.TermStructure.Yield
  (
  -- types
    CRateHelper
  , RateHelper
  , Bootstrap
  , CTermStructure
  , TermStructure
  -- makers
  , depositRateHelper
  , fixedRateBondHelper
  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  )
where

import QuantLib.Internal
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Quote(Quote)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar)
import QuantLib.Time.DayCounter(DayCounter)
import QuantLib.Time.Period(Period)
import QuantLib.Time.Schedule(Schedule)

data CRateHelper
type RateHelper = Object CRateHelper

foreign import ccall safe "ql.h &qlFreeRateHelper"
  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper

data Bootstrap = Discount | ZeroYield | ForwardRate deriving (Show, Eq)

-- |(qlDepositRateHelper2)
depositRateHelper :: Quote -> Period -> Word -> Calendar
  -> BusinessDayConvention -> Bool -> DayCounter -> IO RateHelper
depositRateHelper _ _ _ _ _ _ _ = undefined

-- |(qlFixedRateBondHelper)
fixedRateBondHelper :: Quote -> Word -> Double -> Schedule -> [Double]
  -> DayCounter -> BusinessDayConvention -> Double -> Maybe Day
  -> IO RateHelper
fixedRateBondHelper _ _ _ _ _ _ _ _ _ = undefined


data CTermStructure
type TermStructure = Object CTermStructure

piecewiseYieldCurve :: Day -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Bootstrap -> Interpolation
  -> IO TermStructure
piecewiseYieldCurve = undefined

-- |(qlPiecewiseYieldCurve)
piecewiseYieldCurve' :: Word -> Calendar -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Bootstrap -> Interpolation
  -> IO TermStructure
piecewiseYieldCurve' = undefined
