{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.InterestRate
  (
    interestRate

  , compoundFactor
  , compoundFactor'
  , discountFactor
  , discountFactor'
  , equivalentRate
  , equivalentRate'
  , impliedRate
  , impliedRate'
  , rate
  )
where

import QuantLib.Compounding(Compounding)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlInterestRate"
  c_interestRate :: CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> Ptr CString -> IO (Ptr CInterestRate)

-- |Standard constructor. QuantLibXL: qlInterestRate
interestRate :: Double -- ^r
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> IO InterestRate
interestRate = $(ffiCall 'interestRate) c_interestRate

-- |compound factor implied by the rate compounded between two dates
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded between two dates.
compoundFactor' :: InterestRate
  -> Day -- ^d1
  -> Day -- ^d2
  -> Day -- ^refStart
  -> Day -- ^refEnd
  -> Either String Double
compoundFactor' = $(ffiCallPureX 'compoundFactor') c_compoundFactor'

foreign import ccall safe "ql.h qlInterestRateCompoundFactor1"
  c_compoundFactor' :: Ptr CInterestRate -> CDate -> CDate -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |compound factor implied by the rate compounded at time t.
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded at time t. /Warning/ Time must be measured using InterestRate's own day counter.
compoundFactor :: InterestRate
  -> YearFraction -- ^t
  -> Either String Double
compoundFactor = $(ffiCallPureX 'compoundFactor) c_compoundFactor

foreign import ccall safe "ql.h qlInterestRateCompoundFactor"
  c_compoundFactor :: Ptr CInterestRate -> CYearFraction -> Ptr CString -> IO CDouble

-- |discount factor implied by the rate compounded between two dates
discountFactor' :: InterestRate
  -> Day -- ^d1
  -> Day -- ^d2
  -> Day -- ^refStart
  -> Day -- ^refEnd
  -> Either String Double
discountFactor' = $(ffiCallPureX 'discountFactor') c_discountFactor'

foreign import ccall safe "ql.h qlInterestRateDiscountFactor1"
  c_discountFactor' :: Ptr CInterestRate -> CDate -> CDate -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |discount factor implied by the rate compounded at time t.
-- /Warning/ Time must be measured using InterestRate's own day counter.
discountFactor :: InterestRate
  -> YearFraction -- ^t
  -> Either String Double
discountFactor = $(ffiCallPureX 'discountFactor) c_discountFactor

foreign import ccall safe "ql.h qlInterestRateDiscountFactor"
  c_discountFactor :: Ptr CInterestRate -> CYearFraction -> Ptr CString -> IO CDouble

-- |equivalent rate for a compounding period between two dates
-- The resulting rate is calculated taking the required day-counting rule into account.
equivalentRate' :: InterestRate
  -> DayCounter -- ^resultDC
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Day -- ^d1
  -> Day -- ^d2
  -> Day -- ^refStart
  -> Day -- ^refEnd
  -> IO InterestRate
equivalentRate' = $(ffiCall 'equivalentRate') c_equivalentRate'

foreign import ccall safe "ql.h qlInterestRateEquivalentRate1"
  c_equivalentRate' :: Ptr CInterestRate -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDate -> CDate -> CDate -> Ptr CString -> IO (Ptr CInterestRate)

-- |equivalent interest rate for a compounding period t.
-- The resulting InterestRate shares the same implicit day-counting rule of the original InterestRate instance. /Warning/ Time must be measured using the InterestRate's own day counter.
equivalentRate :: InterestRate
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> YearFraction -- ^t
  -> IO InterestRate
equivalentRate = $(ffiCall 'equivalentRate) c_equivalentRate

foreign import ccall safe "ql.h qlInterestRateEquivalentRate"
  c_equivalentRate :: Ptr CInterestRate -> CInt -> CInt -> CYearFraction -> Ptr CString -> IO (Ptr CInterestRate)

-- |implied rate for a given compound factor between two dates.
-- The resulting rate is calculated taking the required day-counting rule into account.
impliedRate' :: InterestRate
  -> Double -- ^compound
  -> DayCounter -- ^resultDC
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Day -- ^d1
  -> Day -- ^d2
  -> Day -- ^refStart
  -> Day -- ^refEnd
  -> IO InterestRate
impliedRate' = $(ffiCall 'impliedRate') c_impliedRate'

foreign import ccall safe "ql.h qlInterestRateImpliedRate1"
  c_impliedRate' :: Ptr CInterestRate -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDate -> CDate -> CDate -> Ptr CString -> IO (Ptr CInterestRate)

-- |implied interest rate for a given compound factor at a given time.
-- The resulting InterestRate has the day-counter provided as input. /Warning/ Time must be measured using the day-counter provided as input.
impliedRate :: InterestRate
  -> Double -- ^compound
  -> DayCounter -- ^resultDC
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> YearFraction -- ^t
  -> IO InterestRate
impliedRate = $(ffiCall 'impliedRate) c_impliedRate

foreign import ccall safe "ql.h qlInterestRateImpliedRate"
  c_impliedRate :: Ptr CInterestRate -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CYearFraction -> Ptr CString -> IO (Ptr CInterestRate)

rate :: InterestRate -> Double
rate = $(ffiCallPure 'rate) c_rate

foreign import ccall safe "ql.h qlInterestRateRate"
  c_rate :: Ptr CInterestRate -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
