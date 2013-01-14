module QuantLib.Types
  (
    CRateHelper
  , RateHelper

  , CCurrency
  , Currency

  , CIndex
  , Index

  , CInstrument
  , Instrument

  , CInterestRate
  , InterestRate

  , CPricingEngine
  , PricingEngine

  , CQuote
  , Quote

  , CFloatingRateCouponPricer
  , FloatingRateCouponPricer

  , CLeg
  , Leg

  , CIborIndex
  , IborIndex

  , CBond
  , Bond

  , CFixedRateBond
  , FixedRateBond

  , CVolTermStructure
  , VolTermStructure

  , COptionletVolStructure
  , OptionletVolStructure

  , CYieldTermStructure
  , YieldTermStructure

  , CCalendar
  , Calendar

  , CDayCounter
  , DayCounter

  , CPeriod
  , Period

  , CSchedule
  , Schedule
  )
where

import QuantLib.Internal(Object)

data CRateHelper
type RateHelper = Object CRateHelper

data CCurrency
type Currency = Object CCurrency

data CIndex
type Index = Object CIndex

data CInstrument
type Instrument = Object CInstrument

data CInterestRate
type InterestRate = Object CInterestRate

data CPricingEngine
type PricingEngine = Object CPricingEngine

data CQuote
type Quote = Object CQuote

data CFloatingRateCouponPricer
type FloatingRateCouponPricer = Object CFloatingRateCouponPricer

data CLeg
type Leg = Object CLeg

data CIborIndex
type IborIndex = Object CIborIndex

data CBond
type Bond = Object CBond

data CFixedRateBond
type FixedRateBond = Object CFixedRateBond

data CVolTermStructure
type VolTermStructure = Object CVolTermStructure

data COptionletVolStructure
type OptionletVolStructure = Object COptionletVolStructure

data CYieldTermStructure
type YieldTermStructure = Object CYieldTermStructure

data CCalendar
type Calendar = Object CCalendar

data CDayCounter
type DayCounter = Object CDayCounter

data CPeriod
type Period = Object CPeriod

data CSchedule
type Schedule = Object CSchedule
